import json
from pathlib import Path
from typing import Sequence

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from beartype import beartype
from beartype.typing import Dict, List, Optional, Tuple
from hstd_py_codegen.gen_cpp.codegen_ir import (
    GenTuFunction,
    GenTuIdent,
    QualType,
    QualTypeKind,
)
from hstd_py_lib.external_packages.rich_utils import render_rich
from hstd_py_text_layout.base.wrap import BlockId
from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    CheckDef,
    DynT,
    ExprNode,
    ExternalT,
    FieldDef,
    ListT,
    MapT,
    ModelDef,
    NamedT,
    OpId,
    OptT,
    QName,
    RecordDef,
    TupleT,
    TypeRef,
    VariantT,
    expr_tree_repr,
    type_text,
)
from repo_py_orchestrate.codegen_config.type_models.model_to_gentu_common import (
    CPP_AUTO_T,
    CPP_CONTEXT_T,
    CPP_RESULT_T,
    CPP_SPACE_T,
    TypeTranslation,
    cpp_config,
    enum_member_name,
    normalize_ident,
)

CPP_SHORT_SPACE_T = QualType(Name="ud", IsNamespace=True)
CPP_EXPR_SPACE_T = QualType(Name="ux", IsNamespace=True)

RUNTIME_DEPENDANT_KINDS = {
    OpId.WALK,
    OpId.TYPE_COND,
    OpId.IS_DERIVED,
    OpId.PATH_OF,
    OpId.TYPE_OF,
}

COLLECTION_KINDS = {
    OpId.ALL,
    OpId.EXISTS,
    OpId.EXISTS_ONE,
    OpId.MAP,
    OpId.FILTER,
    OpId.FILTER_MAP,
    OpId.TAKE_WHILE,
    OpId.GROUP_BY,
}

SIMPLE_KINDS = {
    OpId.NOT,
    OpId.LIST_CONTAINS,
    OpId.MAP_GET,
    OpId.LIST_AT,
    OpId.MAP_CONTAINS,
    OpId.LIST_SLICE,
    OpId.LIST_CONCAT,
    OpId.MAP_INSERT,
    OpId.MAP_KEYS,
    OpId.MAP_VALUES,
    OpId.SUM,
    OpId.MIN,
    OpId.MAX,
    OpId.OPT_HAS_VALUE,
    OpId.OPT_VALUE,
    OpId.PATH_OF,
    OpId.TYPE_OF,
    OpId.LIST_SIZE,
    OpId.STR_SIZE,
    OpId.MAP_SIZE,
    OpId.LT,
    OpId.LE,
    OpId.ADD,
    OpId.SUB,
    OpId.MUL,
    OpId.DIV,
    OpId.EQ,
    OpId.NE,
    OpId.LIST_EMPTY,
    OpId.MAP_EMPTY,
    OpId.WALK,
}


@beartype
class CheckGen:
    def __init__(
        self,
        *,
        ast: cpp.ASTBuilder,
        model: ModelDef,
        indexes: Dict[str, ModelIndex],
        type_map: TypeTranslation,
    ):
        self.ast = ast
        self.model = model
        self.indexes = indexes
        self.type_map = type_map
        self.expression_counter = 0

    def _expression_name(self, stem: str) -> str:
        result = f"{stem}{self.expression_counter}"
        self.expression_counter += 1
        return result

    def _wrap_uni_static(self, typ: QualType) -> QualType:
        return QualType(
            Name="S",
            Spaces=[CPP_SHORT_SPACE_T],
            Params=[typ],
        )

    def _expression_native_type(self, typ: TypeRef) -> QualType:
        return self.type_map.type(
            typ,
            self.model.package,
            space=CPP_SHORT_SPACE_T,
        )

    def _map_model_type(self, typ: TypeRef) -> QualType:
        result = self._expression_native_type(typ)

        match typ:
            case DynT():
                return result

            case ListT():
                result = result.withTemplateParams([self._map_model_type(typ.elem)])

            case MapT():
                result = result.withTemplateParams(
                    [
                        self._map_model_type(typ.key),
                        self._map_model_type(typ.value),
                    ]
                )

            case OptT():
                result = result.withTemplateParams([self._map_model_type(typ.elem)])

            case TupleT():
                result = result.withTemplateParams(
                    [self._map_model_type(elem) for elem in typ.elems]
                )

        return self._wrap_uni_static(result)

    def _expression_result_type(self, expr: ExprNode) -> QualType:
        if expr.typed_as is None:
            raise ValueError(
                f"Cannot lower '{expr.op.value}' at {expr.loc.render()}: "
                "the finalized expression has no inferred type. Expr tree:\n"
                f"{render_rich(expr_tree_repr(expr))}"
            )

        return self._map_model_type(expr.typed_as)

    def _expr_call(
        self,
        name: str,
        args: Sequence[BlockId] = (),
        params: Sequence[QualType] = (),
        Line: bool = True,
    ) -> BlockId:
        return self.ast.CallStatic(
            CPP_EXPR_SPACE_T,
            name,
            Args=list(args),
            Params=list(params) if params else None,
            Line=Line,
        )

    def _runtime_call(
        self,
        name: str,
        args: Sequence[BlockId] = (),
        Line: bool = True,
    ) -> BlockId:
        return self.ast.CallStatic(
            CPP_SHORT_SPACE_T,
            name,
            Args=list(args),
            Line=Line,
        )

    def _value(self, value: BlockId) -> BlockId:
        return self._expr_call("value", [value])

    def _gen_op_id(self, op: OpId) -> QualType:
        return QualType(
            Name=f"OpId::{op.name}",
            Spaces=[CPP_SHORT_SPACE_T],
        )

    def _template_literal(self, text: str) -> QualType:
        return QualType(
            Kind=QualTypeKind.TypeExpr,
            Expr=text,
        )

    def _expr_context_gen(self, expr: ExprNode) -> BlockId:
        return self._runtime_call(
            "get_context",
            [
                self.ast.string("ctx"),
                self.ast.StringLiteral(Path(expr.loc.file).name),
                self.ast.Literal(expr.loc.line),
            ],
        )

    def _op(
        self,
        expr: ExprNode,
        args: Sequence[BlockId],
        *,
        kind: Optional[OpId] = None,
        extra_params: Sequence[QualType] = (),
    ) -> BlockId:
        return self._expr_call(
            "op",
            [
                self._expr_context_gen(expr),
                *args,
            ],
            [
                self._gen_op_id(expr.op if kind is None else kind),
                self._expression_result_type(expr),
                *extra_params,
            ],
            Line=False,
        )

    def _expression_callback(
        self,
        body: ExprNode,
        binders: Sequence[str],
        binder_types: Sequence[TypeRef],
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> BlockId:
        if len(binders) != len(binder_types):
            raise ValueError(
                f"Invalid callback at {body.loc.render()}: "
                f"{len(binders)} binders but "
                f"{len(binder_types)} binder types"
            )

        local_bindings = dict(bindings)
        parameters: List[cpp.ParmVarParams] = []

        for binder, binder_type in zip(binders, binder_types):
            name = self._expression_name("item")

            parameters.append(
                cpp.ParmVarParams(
                    type=self._map_model_type(binder_type).asConstRef(),
                    name=name,
                )
            )

            local_bindings[binder] = self._value(self.ast.string(name))

        expression = self._gen_expression(
            body,
            this_expr,
            local_bindings,
        )

        return self.ast.Lambda(
            cpp.LambdaParams(
                Args=parameters,
                ResultTy=CPP_AUTO_T(),
                CaptureList=[cpp.LambdaCapture(ByRef=False)],
                Body=[self.ast.Return(expression)],
                IsLine=False,
            )
        )

    def _expression_enum_value(
        self,
        typ: TypeRef,
        name: str,
    ) -> BlockId:
        match typ:
            case NamedT():
                package = self.model.package
                qname = typ.qname

            case ExternalT():
                package = typ.package
                qname = typ.qname

            case _:
                raise TypeError(
                    f"Cannot generate enum member {name!r}: "
                    f"expected a named enum type, got {type_text(typ)}"
                )

        enum = self.indexes[package].enums.get(qname)

        if enum is None:
            raise ValueError(
                f"Cannot generate enum member {name!r}: "
                f"{package}:{qname.to_id()} is not an indexed enum"
            )

        if not any(member.name == name for member in enum.enum_values):
            expected = ", ".join(member.name for member in enum.enum_values)
            raise ValueError(
                f"Unknown member {name!r} of {qname.to_id()}; expected one of: {expected}"
            )

        cpp_name = (
            cpp_config(enum).get("value_names", {}).get(name, enum_member_name(name))
        )

        return self.ast.Scoped(
            self.type_map.declaration_type(package, qname),
            self.ast.string(cpp_name),
        )

    def _expression_record_field(
        self,
        package: str,
        record: RecordDef,
        name: str,
    ) -> Optional[Tuple[RecordDef, FieldDef]]:
        for member in record.fields:
            if member.name == name:
                return record, member

        index = self.indexes[package]

        for base in record.bases:
            found = self._expression_record_field(
                package,
                index.record(base),
                name,
            )

            if found is not None:
                return found

        return None

    def _named_subject(
        self,
        expr: ExprNode,
    ) -> Tuple[str, QName]:
        subject_type = expr.args[0].typed_as

        match subject_type:
            case NamedT():
                return self.model.package, subject_type.qname

            case ExternalT():
                return subject_type.package, subject_type.qname

            case _:
                raise TypeError(
                    f"Expected a named subject at {expr.loc.render()}, "
                    f"got {subject_type!r}"
                )

    def _field_name(self, expr: ExprNode) -> str:
        assert expr.str_val is not None

        subject_type = expr.args[0].typed_as

        if isinstance(subject_type, (NamedT, ExternalT)):
            package, qname = self._named_subject(expr)
            index = self.indexes[package]

            if not index.is_enum(qname):
                found = self._expression_record_field(
                    package,
                    index.record(qname),
                    expr.str_val,
                )

                if found is not None:
                    owner, member = found
                    return (
                        cpp_config(owner)
                        .get("field_names", {})
                        .get(member.name, member.name)
                    )

        return expr.str_val

    def _member_operation(
        self,
        expr: ExprNode,
        source: BlockId,
        method: str,
    ) -> BlockId:
        subject_type = expr.args[0].typed_as

        if subject_type is None:
            raise ValueError(f"Missing subject type at {expr.loc.render()}")

        pointer = self.ast.Addr(
            self.ast.Scoped(
                self._expression_native_type(subject_type),
                self.ast.string(method),
            )
        )

        return self._expr_call(
            "member",
            [
                self._expr_context_gen(expr),
                source,
                pointer,
                self.ast.StringLiteral(method),
            ],
            [
                self._gen_op_id(expr.op),
                self._expression_result_type(expr),
            ],
        )

    def _case_is(
        self,
        expr: ExprNode,
        source: BlockId,
    ) -> BlockId:
        assert expr.str_val is not None
        subject_type = expr.args[0].typed_as

        match subject_type:
            case VariantT():
                package = self.model.package
                record = self.indexes[package].record(subject_type.owner)

                variant = next(
                    variant
                    for variant in record.variants
                    if variant.field == subject_type.field
                )

                branch = next(
                    (
                        branch
                        for branch in variant.cases
                        if branch.case.name == expr.str_val
                    ),
                    None,
                )

                if branch is None:
                    expected = ", ".join(branch.case.name for branch in variant.cases)
                    raise ValueError(
                        f"Unknown variant case {expr.str_val!r} at "
                        f"{expr.loc.render()}; expected one of: {expected}"
                    )

                return self._op(
                    expr,
                    [source],
                    extra_params=[
                        self.type_map.declaration_type(
                            package,
                            branch.case,
                        )
                    ],
                )

            case NamedT() | ExternalT():
                return self._member_operation(
                    expr,
                    source,
                    f"is{expr.str_val}",
                )

            case _:
                raise TypeError(
                    f"Cannot lower case test at {expr.loc.render()}: "
                    f"unsupported subject type {subject_type!r}"
                )

    def _case_which(
        self,
        expr: ExprNode,
        source: BlockId,
    ) -> BlockId:
        subject_type = expr.args[0].typed_as

        match subject_type:
            case VariantT():
                return self._op(expr, [source])

            case NamedT() | ExternalT():
                package, qname = self._named_subject(expr)
                record = self.indexes[package].record(qname)

                if len(record.variants) != 1:
                    fields = ", ".join(variant.field for variant in record.variants)
                    raise ValueError(
                        f"Cannot choose a variant kind getter for "
                        f"{record.qname.to_id()} at {expr.loc.render()}: "
                        f"expected one variant, got fields [{fields}]"
                    )

                variant = record.variants[0]
                getter = self.type_map.variant_config(
                    package,
                    record.qname,
                    variant.field,
                ).get("kind_getter", "getKind")

                return self._member_operation(
                    expr,
                    source,
                    getter,
                )

            case _:
                raise TypeError(
                    f"Cannot lower case-kind access at "
                    f"{expr.loc.render()}: "
                    f"unsupported subject type {subject_type!r}"
                )

    def _constant(
        self,
        expr: ExprNode,
        value: BlockId,
        text: str,
    ) -> BlockId:
        assert expr.typed_as is not None

        return self._expr_call(
            "constant",
            [
                self.ast.XCall(
                    "static_cast",
                    args=[value],
                    Params=[self._expression_native_type(expr.typed_as)],
                ),
                self.ast.StringLiteral(text),
            ],
            [self._expression_result_type(expr)],
        )

    def _type_conditional(
        self,
        expr: ExprNode,
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> BlockId:
        optional = bool(expr.bool_val)

        if optional and not isinstance(expr.typed_as, OptT):
            raise TypeError(
                f"Optional type dispatch at {expr.loc.render()} "
                f"must have an optional result, got {expr.typed_as!r}"
            )

        subject = self._gen_expression(
            expr.args[0],
            this_expr,
            bindings,
        )

        branches: List[BlockId] = []

        for branch in expr.args[1:]:
            if branch.op != OpId.TYPE_CASE or branch.type_val is None:
                raise ValueError(
                    f"Invalid type-dispatch branch at "
                    f"{branch.loc.render()}: expected TYPE_CASE "
                    f"with a target type, got {branch.op.value}"
                )

            body = self._expression_callback(
                branch.args[0],
                branch.binders,
                [branch.type_val],
                this_expr,
                bindings,
            )

            branches.append(
                self._expr_call(
                    "type_case",
                    [body],
                    [self._expression_native_type(branch.type_val)],
                )
            )

        expected = ", ".join(
            type_text(branch.type_val)
            for branch in expr.args[1:]
            if branch.type_val is not None
        )

        message = (
            f"No type case matched at {expr.loc.render()}; expected one of: {expected}"
        )

        return self._expr_call(
            "type_conditional",
            [
                self._expr_context_gen(expr),
                subject,
                self.ast.StringLiteral(message),
                *branches,
            ],
            [
                self._expression_result_type(expr),
                self._template_literal("true" if optional else "false"),
            ],
        )

    def _gen_expression(
        self,
        expr: ExprNode,
        this_expr: BlockId,
        bindings: Optional[dict[str, BlockId]] = None,
    ) -> BlockId:
        bindings = {} if bindings is None else bindings

        # Retain the finalized-type invariant even for structural nodes.
        self._expression_result_type(expr)

        match expr.op:
            case OpId.THIS:
                return this_expr

            case OpId.VAR:
                assert expr.str_val is not None

                if expr.str_val not in bindings:
                    available = ", ".join(sorted(bindings))
                    raise ValueError(
                        f"Unbound expression variable {expr.str_val!r} "
                        f"at {expr.loc.render()}; "
                        f"available bindings: [{available}]"
                    )

                return bindings[expr.str_val]

            case OpId.CONST_INT:
                assert expr.int_val is not None
                return self._constant(
                    expr,
                    self.ast.Literal(expr.int_val),
                    str(expr.int_val),
                )

            case OpId.CONST_FLOAT:
                assert expr.float_val is not None
                text = json.dumps(
                    expr.float_val,
                    allow_nan=False,
                )
                return self._constant(
                    expr,
                    self.ast.string(text),
                    text,
                )

            case OpId.CONST_BOOL:
                assert expr.bool_val is not None
                text = "true" if expr.bool_val else "false"
                return self._constant(
                    expr,
                    self.ast.string(text),
                    text,
                )

            case OpId.CONST_STR:
                assert expr.str_val is not None
                return self._constant(
                    expr,
                    self.ast.StringLiteral(expr.str_val),
                    expr.str_val,
                )

            case OpId.AND | OpId.OR:
                nested = [
                    self._expr_call(
                        "scoped",
                        [
                            self._expr_context_gen(arg),
                            self._gen_expression(
                                arg,
                                this_expr,
                                bindings,
                            ),
                        ],
                        [self._gen_op_id(arg.op)],
                        Line=False,
                    )
                    for arg in expr.args
                ]

                return self._expr_call(
                    "logic",
                    nested,
                    [self._gen_op_id(expr.op)],
                )

            case OpId.COND:
                return self._expr_call(
                    "conditional",
                    [
                        self._gen_expression(
                            arg,
                            this_expr,
                            bindings,
                        )
                        for arg in expr.args
                    ],
                    [self._expression_result_type(expr)],
                )

            case OpId.LET:
                bound_type = expr.args[0].typed_as

                if bound_type is None:
                    raise ValueError(f"Missing LET binding type at {expr.loc.render()}")

                bound = self._gen_expression(
                    expr.args[0],
                    this_expr,
                    bindings,
                )

                body = self._expression_callback(
                    expr.args[1],
                    expr.binders,
                    [bound_type],
                    this_expr,
                    bindings,
                )

                return self._expr_call("let", [bound, body])

            case OpId.TYPE_COND:
                return self._type_conditional(
                    expr,
                    this_expr,
                    bindings,
                )

            case OpId.TYPE_CASE:
                raise ValueError(
                    f"TYPE_CASE at {expr.loc.render()} cannot be "
                    "evaluated independently; it must be a branch "
                    "of TYPE_COND"
                )

        if expr.op in COLLECTION_KINDS or expr.op == OpId.FOLD:
            callback_index = 2 if expr.op == OpId.FOLD else 1

            arguments = [
                self._gen_expression(
                    arg,
                    this_expr,
                    bindings,
                )
                for arg in expr.args[:callback_index]
            ]

            callback = self._expression_callback(
                expr.args[callback_index],
                expr.binders,
                expr.binder_types,
                this_expr,
                bindings,
            )

            arguments.append(self._expr_call("closure", [callback]))

            return self._op(expr, arguments)

        arguments = [
            self._gen_expression(
                arg,
                this_expr,
                bindings,
            )
            for arg in expr.args
        ]

        match expr.op:
            case OpId.GET_FIELD:
                return self._op(
                    expr,
                    [
                        arguments[0],
                        self._value(self.ast.StringLiteral(self._field_name(expr))),
                    ],
                )

            case OpId.STR_MATCHES:
                assert expr.str_val is not None

                return self._op(
                    expr,
                    [
                        arguments[0],
                        self._value(self.ast.StringLiteral(expr.str_val)),
                    ],
                )

            case OpId.STR_FORMAT:
                assert expr.str_val is not None

                pattern = self.ast.XCall(
                    "eval_str_pattern",
                    args=[self.ast.StringLiteral(expr.str_val)],
                )

                return self._op(
                    expr,
                    [
                        self._value(pattern),
                        *arguments,
                    ],
                )

            case OpId.CASE_IS:
                return self._case_is(expr, arguments[0])

            case OpId.CASE_WHICH:
                return self._case_which(expr, arguments[0])

            case OpId.ENUM_IS:
                assert expr.str_val is not None
                subject_type = expr.args[0].typed_as

                if subject_type is None:
                    raise ValueError(
                        f"Enum comparison at {expr.loc.render()} "
                        "has no inferred subject type"
                    )

                return self._op(
                    expr,
                    [
                        arguments[0],
                        self._value(
                            self._expression_enum_value(
                                subject_type,
                                expr.str_val,
                            )
                        ),
                    ],
                    kind=OpId.EQ,
                )

            case OpId.NTH_GET:
                assert expr.int_val is not None

                return self._expr_call(
                    "indexed_op",
                    [
                        self._expr_context_gen(expr),
                        arguments[0],
                    ],
                    [
                        self._gen_op_id(expr.op),
                        self._expression_result_type(expr),
                        self._template_literal(str(expr.int_val)),
                    ],
                )

            case OpId.IS_DERIVED:
                if expr.type_val is None:
                    raise ValueError(
                        f"Derived-type test at {expr.loc.render()} has no target type"
                    )

                return self._op(
                    expr,
                    arguments,
                    extra_params=[self._expression_native_type(expr.type_val)],
                )

        if expr.op in SIMPLE_KINDS:
            return self._op(expr, arguments)

        raise ValueError(
            f"Unhandled expression '{expr.op.value}' at "
            f"{expr.loc.render()}: "
            f"{render_rich(expr_tree_repr(expr))}"
        )

    def _expression_needs_runtime(self, expr: ExprNode) -> bool:
        return expr.op in RUNTIME_DEPENDANT_KINDS or any(
            self._expression_needs_runtime(arg) for arg in expr.args
        )

    def _gen_expression_runtime(self) -> List[BlockId]:
        runtime_type = QualType(
            Name="EvalRuntime",
            Spaces=[CPP_SPACE_T],
        )

        return [
            self.ast.VarDecl(
                cpp.ParmVarParams(
                    type=runtime_type,
                    name="expression_runtime",
                    defArg=self.ast.XConstructObj(
                        runtime_type,
                        Args=[self.ast.string("ctx")],
                    ),
                )
            ),
            self.ast.XCall(
                "__populate_expression_runtime",
                args=[self.ast.string("expression_runtime")],
                Stmt=True,
            ),
        ]

    def gen_populate_expression_runtime(
        self,
        parentClass: QualType,
    ) -> GenTuFunction:
        return GenTuFunction(
            Name="__populate_expression_runtime",
            ReturnType=QualType(Name="void"),
            Args=[
                GenTuIdent(
                    Type=QualType(
                        Name="EvalRuntime",
                        Spaces=[CPP_SPACE_T],
                    ).asRef(),
                    Name="expression_runtime",
                )
            ],
            IsStatic=True,
            ParentClass=parentClass,
            Body=self.ast.stack(self._gen_expression_runtime_registrations()),
        )

    def _gen_expression_runtime_registrations(
        self,
    ) -> List[BlockId]:
        runtime = self.ast.string("expression_runtime")
        statements: List[BlockId] = []

        for package, model in self.type_map.models.items():
            for declaration in (*model.records, *model.enums):
                statements.append(
                    self.ast.XCallRef(
                        runtime,
                        "register_type",
                        args=[self.ast.StringLiteral(declaration.qname.to_id())],
                        Params=[
                            self.type_map.declaration_type(
                                package,
                                declaration.qname,
                            )
                        ],
                        Stmt=True,
                    )
                )

            index = self.indexes[package]

            for record in model.records:
                for base in model.records:
                    if record.qname != base.qname and index.derived_from(
                        record.qname,
                        base.qname,
                    ):
                        statements.append(
                            self.ast.XCallRef(
                                runtime,
                                "register_base",
                                Params=[
                                    self.type_map.declaration_type(
                                        package,
                                        record.qname,
                                    ),
                                    self.type_map.declaration_type(
                                        package,
                                        base.qname,
                                    ),
                                ],
                                Stmt=True,
                            )
                        )

        return statements

    def _local(
        self,
        name: str,
        value: BlockId,
    ) -> BlockId:
        return self.ast.VarDecl(
            cpp.ParmVarParams(
                type=CPP_AUTO_T(),
                name=name,
                defArg=value,
            )
        )

    def _gen_check_eval(
        self,
        check: CheckDef,
        this_expr: BlockId,
    ) -> BlockId:
        self.expression_counter = 0

        statements: List[BlockId] = [
            self.ast.string("namespace ux = hstd::ext::unidata::expr;")
        ]

        needs_runtime = self._expression_needs_runtime(
            check.cond
        ) or self._expression_needs_runtime(check.message)

        if needs_runtime:
            statements.extend(self._gen_expression_runtime())

        state_type = QualType(
            Name="State",
            Spaces=[CPP_EXPR_SPACE_T],
        )

        runtime_pointer = (
            self.ast.Addr(self.ast.string("expression_runtime"))
            if needs_runtime
            else self.ast.string("nullptr")
        )

        statements.append(
            self._local(
                "expression_state",
                self.ast.XConstructObj(
                    state_type,
                    Args=[
                        self.ast.string("ctx"),
                        runtime_pointer,
                    ],
                ),
            )
        )

        statements.append(
            self._local(
                "root_expression",
                self._value(this_expr),
            )
        )

        root = self.ast.string("root_expression")

        condition = self._gen_expression(
            check.cond,
            root,
        )

        message = self._gen_expression(
            check.message,
            root,
        )

        statements.extend(
            [
                self._local(
                    "condition_expression",
                    condition,
                ),
                self._local(
                    "message_expression",
                    message,
                ),
                self.ast.Return(
                    self._expr_call(
                        "verify",
                        [
                            self.ast.string("expression_state"),
                            self.ast.string("condition_expression"),
                            self.ast.string("message_expression"),
                        ],
                    )
                ),
            ]
        )

        return self.ast.stack(statements)

    def _get_check_args(self) -> List[GenTuIdent]:
        return [
            GenTuIdent(
                Type=CPP_CONTEXT_T().asConstPtr(),
                Name="ctx",
            ),
            GenTuIdent(
                Type=QualType(Name="void").asConstPtr(),
                Name="value",
            ),
        ]

    def _decl_this_object(
        self,
        owner: RecordDef,
    ) -> List[BlockId]:
        owner_type = self.type_map.declaration_type(
            self.model.package,
            owner.qname,
        )

        return [
            self.ast.VarDecl(
                cpp.ParmVarParams(
                    type=CPP_AUTO_T().asConstPtr(),
                    name="this_obj_ptr",
                    defArg=self.ast.XCall(
                        "static_cast",
                        args=[self.ast.string("value")],
                        Params=[owner_type.asConstPtr()],
                    ),
                )
            ),
            self._local(
                "this_obj",
                self.ast.CallStatic(
                    typ=self._wrap_uni_static(owner_type),
                    opc="RootValue",
                    Args=[
                        self.ast.string("this_obj_ptr"),
                        self.ast.XCallPtr(
                            self.ast.string("ctx"),
                            "getPath",
                        ),
                    ],
                ),
            ),
        ]

    def gen_record_check(
        self,
        owner: RecordDef,
        check: CheckDef,
        parentClass: QualType,
    ) -> GenTuFunction:
        return GenTuFunction(
            Name=(f"__check_record_{normalize_ident(check.id)}"),
            ReturnType=CPP_RESULT_T(),
            Args=self._get_check_args(),
            IsStatic=True,
            ParentClass=parentClass,
            Body=self.ast.stack(
                [
                    *self._decl_this_object(owner),
                    self._gen_check_eval(
                        check,
                        this_expr=self.ast.string("this_obj"),
                    ),
                ]
            ),
        )

    def gen_field_check(
        self,
        owner: RecordDef,
        field: FieldDef,
        check: CheckDef,
        parentClass: QualType,
    ) -> GenTuFunction:
        cpp_name = cpp_config(owner).get("field_names", {}).get(field.name, field.name)

        this_object = self.ast.string("this_obj")

        this_expr = self.ast.XCallRef(
            this_object,
            opc="Field",
            args=[
                self.ast.Addr(
                    self.ast.Arrow(
                        self.ast.XCallRef(
                            this_object,
                            "get",
                        ),
                        self.ast.string(cpp_name),
                    )
                ),
                self.ast.StringLiteral(cpp_name),
            ],
        )

        return GenTuFunction(
            Name=(f"__check_{field.name}_{normalize_ident(check.id)}"),
            ReturnType=CPP_RESULT_T(),
            Args=self._get_check_args(),
            IsStatic=True,
            ParentClass=parentClass,
            Body=self.ast.stack(
                [
                    *self._decl_this_object(owner),
                    self._gen_check_eval(
                        check,
                        this_expr=this_expr,
                    ),
                ]
            ),
        )
