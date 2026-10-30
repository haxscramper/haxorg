import json
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
    ArrayT,
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
    CPP_CONTEXT_T,
    CPP_RESULT_T,
    CPP_SPACE_T,
    ExpressionEvaluation,
    TypeTranslation,
    cpp_config,
    enum_member_name,
    format_expr_repr,
    named_cpp_type,
    normalize_ident,
)

GEN_EXPRESSION_COMMENTS = False


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

    def _expression_name(self, stem: str = "expr") -> str:
        result = f"{stem}{self.expression_counter}"
        self.expression_counter += 1
        return result

    def _expression_local(
        self,
        value: BlockId,
        statements: Sequence[BlockId] = (),
        *,
        expr: Optional[ExprNode] = None,
    ) -> ExpressionEvaluation:
        name = self._expression_name()

        declaration = self.ast.VarDecl(
            cpp.ParmVarParams(
                type=QualType(Name="auto").asConstRef(),
                name=name,
                defArg=value,
            )
        )

        result_statements = list(statements)

        if expr is not None and GEN_EXPRESSION_COMMENTS:
            result_statements.append(
                self.ast.Comment(
                    format_expr_repr(expr).splitlines(),
                    Inline=False,
                )
            )

        result_statements.append(declaration)

        return ExpressionEvaluation(
            statements=result_statements,
            value=self.ast.string(name),
        )

    def _expression_call(
        self,
        name: str,
        args: Sequence[BlockId] = (),
        params: Sequence[QualType] = (),
    ) -> BlockId:
        return self.ast.CallStatic(
            CPP_SPACE_T,
            name,
            Args=list(args),
            Params=list(params) if params else None,
        )

    def _expression_native_type(
        self,
        typ: TypeRef,
        package: Optional[str] = None,
    ) -> QualType:
        package = self.model.package if package is None else package

        match typ:
            case DynT():
                return QualType(Name="EvalDynamic", Spaces=[CPP_SPACE_T])

            case ListT():
                return named_cpp_type(
                    "hstd::Vec",
                    [self._expression_native_type(typ.elem, package)],
                )

            case ArrayT():
                return named_cpp_type(
                    "std::array",
                    [
                        self._expression_native_type(typ.elem, package),
                        QualType(
                            Kind=QualTypeKind.TypeExpr,
                            Expr=str(typ.size),
                        ),
                    ],
                )

            case MapT():
                return named_cpp_type(
                    "hstd::UnorderedMap",
                    [
                        self._expression_native_type(typ.key, package),
                        self._expression_native_type(typ.value, package),
                    ],
                )

            case OptT():
                return named_cpp_type(
                    "hstd::Opt",
                    [self._expression_native_type(typ.elem, package)],
                )

            case TupleT():
                return named_cpp_type(
                    "std::tuple",
                    [self._expression_native_type(elem, package) for elem in typ.elems],
                )

            case _:
                return self.type_map.type(typ, package)

    def _expression_result_type(self, expr: ExprNode) -> QualType:
        if expr.typed_as is None:
            raise ValueError(
                f"Cannot lower '{expr.op.value}' at {expr.loc.render()}: "
                "the finalized expression has no inferred type. Expr tree:\n"
                f"{render_rich(expr_tree_repr(expr))}"
            )

        else:
            return self._expression_native_type(expr.typed_as)

    def _expression_slot(
        self,
        typ: QualType,
    ) -> Tuple[BlockId, BlockId]:
        name = self._expression_name("result")
        value = self.ast.string(name)

        declaration = self.ast.VarDecl(
            cpp.ParmVarParams(
                type=named_cpp_type("std::optional", [typ]),
                name=name,
                defArg=self.ast.string("std::nullopt"),
            )
        )

        return value, declaration

    def _expression_args(
        self,
        args: Sequence[ExprNode],
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> Tuple[List[BlockId], List[BlockId]]:
        statements: List[BlockId] = []
        values: List[BlockId] = []

        for arg in args:
            lowered = self._gen_expression_eval(arg, this_expr, bindings)
            statements.extend(lowered.statements)
            values.append(lowered.value)

        return statements, values

    def _expression_callback(
        self,
        body: ExprNode,
        binders: Sequence[str],
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> BlockId:
        local_bindings = dict(bindings)
        parameters: List[cpp.ParmVarParams] = []

        for binder in binders:
            name = self._expression_name("item")
            parameters.append(
                cpp.ParmVarParams(
                    type=QualType(Name="auto").asConstRef(),
                    name=name,
                )
            )
            local_bindings[binder] = self.ast.string(name)

        lowered = self._gen_expression_eval(
            body,
            this_expr,
            local_bindings,
        )

        return self.ast.Lambda(
            cpp.LambdaParams(
                Args=parameters,
                ResultTy=None,
                CaptureList=[cpp.LambdaCapture(ByRef=True)],
                Body=[
                    *lowered.statements,
                    self.ast.Return(lowered.value),
                ],
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

        index = self.indexes[package]
        enum = index.enums.get(qname)

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
            cpp_config(enum)
            .get("value_names", {})
            .get(
                name,
                enum_member_name(name),
            )
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

    def _expression_field_access(
        self,
        expr: ExprNode,
        source: BlockId,
    ) -> BlockId:
        assert expr.str_val is not None

        source_type = expr.args[0].typed_as
        package: Optional[str] = None
        qname: Optional[QName] = None

        match source_type:
            case NamedT():
                package = self.model.package
                qname = source_type.qname

            case ExternalT():
                package = source_type.package
                qname = source_type.qname

            case _:
                pass

        if package is not None and qname is not None:
            index = self.indexes[package]

            if not index.is_enum(qname):
                record = index.record(qname)
                found = self._expression_record_field(
                    package,
                    record,
                    expr.str_val,
                )

                if found is not None:
                    owner, member = found
                    cpp_name = (
                        cpp_config(owner)
                        .get("field_names", {})
                        .get(member.name, member.name)
                    )

                    if self.type_map.is_ast(package, qname):
                        return self.ast.Arrow(
                            source,
                            self.ast.string(cpp_name),
                        )

                    return self.ast.Dot(
                        source,
                        self.ast.string(cpp_name),
                    )

        # return self.ast.Dot(source, self.ast.string(expr.str_val))

        return self._expression_call(
            "eval_get_field",
            args=[source, self.ast.StringLiteral(expr.str_val)],
            params=[self._expression_result_type(expr)],
        )

    def _expression_case_test(
        self,
        expr: ExprNode,
        source: BlockId,
    ) -> BlockId:
        assert expr.str_val is not None

        source_type = expr.args[0].typed_as

        match source_type:
            case VariantT():
                package = self.model.package
                record = self.indexes[package].record(source_type.owner)
                variant = next(
                    variant
                    for variant in record.variants
                    if variant.field == source_type.field
                )

                case = next(
                    (case for case in variant.cases if case.case.name == expr.str_val),
                    None,
                )

                if case is None:
                    expected = ", ".join(case.case.name for case in variant.cases)
                    raise ValueError(
                        f"Unknown variant case {expr.str_val!r} at "
                        f"{expr.loc.render()}; expected one of: {expected}"
                    )

                return self.ast.XCall(
                    "std::holds_alternative",
                    args=[source],
                    Params=[
                        self.type_map.declaration_type(package, case.case),
                    ],
                )

            case NamedT() | ExternalT():
                return self.ast.XCallRef(
                    source,
                    f"is{expr.str_val}",
                )

            case _:
                raise TypeError(
                    f"Cannot lower case test at {expr.loc.render()}: "
                    f"unsupported subject type {source_type!r}"
                )

    def _expression_case_kind(
        self,
        expr: ExprNode,
        source: BlockId,
    ) -> BlockId:
        source_type = expr.args[0].typed_as

        match source_type:
            case VariantT():
                return self.ast.XCall(
                    "static_cast",
                    args=[self.ast.XCallRef(source, "index")],
                    Params=[self._expression_result_type(expr)],
                )

            case NamedT() | ExternalT():
                package = (
                    source_type.package
                    if isinstance(source_type, ExternalT)
                    else self.model.package
                )

                record = self.indexes[package].record(source_type.qname)

                if len(record.variants) != 1:
                    fields = ", ".join(variant.field for variant in record.variants)
                    raise ValueError(
                        f"Cannot choose a variant kind getter for "
                        f"{record.qname.to_id()} at {expr.loc.render()}: "
                        f"expected one variant, got fields [{fields}]"
                    )

                variant = record.variants[0]
                getter = self.variant_config(
                    package,
                    record.qname,
                    variant.field,
                ).get("kind_getter", "getKind")

                return self.ast.XCallRef(source, getter)

            case _:
                raise TypeError(
                    f"Cannot lower case-kind access at {expr.loc.render()}: "
                    f"unsupported subject type {source_type!r}"
                )

    def _expression_runtime_call(
        self,
        method: str,
        args: Sequence[BlockId],
        params: Sequence[QualType] = (),
    ) -> BlockId:
        return self.ast.XCallRef(
            self.ast.string("expression_runtime"),
            method,
            args=list(args),
            Params=list(params) if params else None,
        )

    def _gen_expression_eval(
        self,
        expr: ExprNode,
        this_expr: BlockId,
        bindings: Optional[dict[str, BlockId]] = None,
    ) -> ExpressionEvaluation:
        bindings = {} if bindings is None else bindings

        match expr.op:
            case OpId.THIS:
                return ExpressionEvaluation([], this_expr)

            case OpId.VAR:
                assert expr.str_val is not None

                if expr.str_val not in bindings:
                    available = ", ".join(sorted(bindings))
                    raise ValueError(
                        f"Unbound expression variable {expr.str_val!r} at "
                        f"{expr.loc.render()}; available bindings: [{available}]"
                    )

                return ExpressionEvaluation([], bindings[expr.str_val])

            case OpId.CONST_INT:
                assert expr.int_val is not None
                return self._expression_local(
                    self.ast.XCall(
                        "static_cast",
                        args=[self.ast.Literal(expr.int_val)],
                        Params=[self._expression_result_type(expr)],
                    ),
                    expr=expr,
                )

            case OpId.CONST_FLOAT:
                assert expr.float_val is not None
                return self._expression_local(
                    self.ast.XCall(
                        "static_cast",
                        args=[
                            self.ast.string(json.dumps(expr.float_val, allow_nan=False))
                        ],
                        Params=[self._expression_result_type(expr)],
                    ),
                    expr=expr,
                )

            case OpId.CONST_BOOL:
                assert expr.bool_val is not None
                return self._expression_local(
                    self.ast.string("true" if expr.bool_val else "false"),
                    expr=expr,
                )

            case OpId.CONST_STR:
                assert expr.str_val is not None
                return self._expression_local(
                    self.ast.XConstructObj(
                        self._expression_result_type(expr),
                        Args=[self.ast.StringLiteral(expr.str_val)],
                    ),
                    expr=expr,
                )

            case OpId.AND | OpId.OR:
                return self._gen_expression_eval_logic(expr, this_expr, bindings)

            case OpId.NOT:
                arg = self._gen_expression_eval(
                    expr.args[0],
                    this_expr,
                    bindings,
                )

                return self._expression_local(
                    self.ast.XCall("!", args=[self.ast.pars(arg.value)]),
                    arg.statements,
                    expr=expr,
                )

            case OpId.COND:
                return self._gen_expression_eval_cond(expr, this_expr, bindings)

            case OpId.LET:
                return self._gen_expression_eval_let(expr, this_expr, bindings)

            case OpId.TYPE_COND:
                return self._gen_expression_eval_type_cond(
                    expr,
                    this_expr,
                    bindings,
                )

            case OpId.TYPE_CASE:
                raise ValueError(
                    f"TYPE_CASE at {expr.loc.render()} cannot be evaluated "
                    "independently; it must be a branch of TYPE_COND"
                )

            case (
                OpId.ALL
                | OpId.EXISTS
                | OpId.EXISTS_ONE
                | OpId.MAP
                | OpId.FILTER
                | OpId.FILTER_MAP
                | OpId.TAKE_WHILE
                | OpId.GROUP_BY
            ):
                return self._gen_expression_eval_collection(
                    expr,
                    this_expr,
                    bindings,
                )

            case OpId.FOLD:
                return self._gen_expression_eval_fold(expr, this_expr, bindings)

            case OpId.LIST_EMPTY | OpId.MAP_EMPTY:
                return self._expression_local(
                    self.ast.XConstructObj(
                        self._expression_result_type(expr),
                        Args=[],
                    ),
                    expr=expr,
                )

            case _:
                statements, args = self._expression_args(
                    expr.args,
                    this_expr,
                    bindings,
                )

        match expr.op:
            case OpId.EQ | OpId.NE:
                value = self._expression_call(
                    "eval_equal",
                    args=args,
                )

                if expr.op == OpId.NE:
                    value = self.ast.XCall("!", args=[self.ast.pars(value)])

            case OpId.LT | OpId.LE:
                operator = "<" if expr.op == OpId.LT else "<="
                value = self.ast.pars(self.ast.XCall(operator, args=args))

            case OpId.ADD | OpId.SUB | OpId.MUL | OpId.DIV:
                value = self._gen_expression_arithmetic(expr, args)

            case OpId.GET_FIELD:
                value = self._expression_field_access(expr, args[0])

            case OpId.STR_SIZE:
                value = self._expression_call(
                    "eval_str_size",
                    args=[self.ast.Addr(args[0])],
                )

            case OpId.LIST_SIZE | OpId.MAP_SIZE:
                value = self.ast.XCall(
                    "static_cast",
                    args=[self.ast.XCallRef(args[0], "size")],
                    Params=[self._expression_result_type(expr)],
                )

            case OpId.STR_MATCHES:
                assert expr.str_val is not None
                value = self._expression_call(
                    "eval_str_matches",
                    args=[
                        args[0],
                        self.ast.StringLiteral(expr.str_val),
                    ],
                )

            case OpId.STR_FORMAT:
                assert expr.str_val is not None
                value = self._expression_call(
                    "eval_str_format",
                    args=[
                        self._expression_call(
                            "eval_str_pattern",
                            args=[self.ast.StringLiteral(expr.str_val)],
                        ),
                        *args,
                    ],
                )

            case OpId.LIST_CONTAINS:
                value = self._expression_call(
                    "eval_list_contains",
                    args=args,
                )

            case OpId.LIST_AT | OpId.MAP_GET:
                value = self.ast.XCallRef(
                    args[0],
                    "at",
                    args=[args[1]],
                )

            case OpId.MAP_CONTAINS:
                value = self.ast.XCallRef(
                    args[0],
                    "contains",
                    args=[args[1]],
                )

            case (
                OpId.LIST_SLICE
                | OpId.LIST_CONCAT
                | OpId.MAP_INSERT
                | OpId.MAP_KEYS
                | OpId.MAP_VALUES
                | OpId.SUM
                | OpId.MIN
                | OpId.MAX
            ):
                function = {
                    OpId.LIST_SLICE: "eval_list_slice",
                    OpId.LIST_CONCAT: "eval_list_concat",
                    OpId.MAP_INSERT: "eval_map_insert",
                    OpId.MAP_KEYS: "eval_map_keys",
                    OpId.MAP_VALUES: "eval_map_values",
                    OpId.SUM: "eval_sum",
                    OpId.MIN: "eval_min",
                    OpId.MAX: "eval_max",
                }[expr.op]

                value = self._expression_call(
                    function,
                    args=args,
                    params=[self._expression_result_type(expr)],
                )

            case OpId.OPT_HAS_VALUE:
                value = self.ast.XCallRef(args[0], "has_value")

            case OpId.OPT_VALUE:
                value = self.ast.XCallRef(args[0], "value")

            case OpId.CASE_IS:
                value = self._expression_case_test(expr, args[0])

            case OpId.CASE_WHICH:
                value = self._expression_case_kind(expr, args[0])

            case OpId.ENUM_IS:
                value = self._gen_expression_enum_is(expr, args)

            case OpId.NTH_GET:
                assert expr.int_val is not None
                value = self.ast.XCall(
                    "std::get",
                    args=[args[0]],
                    Params=[
                        QualType(
                            Kind=QualTypeKind.TypeExpr,
                            Expr=str(expr.int_val),
                        )
                    ],
                )

            case OpId.WALK:
                value = self._expression_call(
                    "eval_walk",
                    args=[
                        self.ast.string("expression_runtime"),
                        args[0],
                    ],
                )

            case OpId.IS_DERIVED:
                if expr.type_val is None:
                    raise ValueError(
                        f"Derived-type test at {expr.loc.render()} has no target type"
                    )

                value = self.ast.pars(
                    self.ast.XCall(
                        "!=",
                        args=[
                            self._expression_runtime_call(
                                "try_as",
                                args=[args[0]],
                                params=[self._expression_native_type(expr.type_val)],
                            ),
                            self.ast.string("nullptr"),
                        ],
                    )
                )

            case OpId.PATH_OF:
                value = self._expression_runtime_call(
                    "path_of",
                    args=[args[0]],
                )

            case OpId.TYPE_OF:
                value = self._expression_runtime_call(
                    "type_of",
                    args=[args[0]],
                )

            case _:
                raise ValueError(
                    f"Unhandled expression '{expr.op.value}' at "
                    f"{expr.loc.render()}: "
                    f"{render_rich(expr_tree_repr(expr))}"
                )

        return self._expression_local(value, statements, expr=expr)

    def _gen_expression_eval_logic(
        self,
        expr: ExprNode,
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> ExpressionEvaluation:
        name = self._expression_name("condition")
        result = self.ast.string(name)
        is_and = expr.op == OpId.AND

        statements = [
            self.ast.VarDecl(
                cpp.ParmVarParams(
                    type=QualType(Name="bool"),
                    name=name,
                    defArg=self.ast.string("true" if is_and else "false"),
                )
            )
        ]

        for arg in expr.args:
            lowered = self._gen_expression_eval(
                arg,
                this_expr,
                bindings,
            )

            condition = (
                result if is_and else self.ast.XCall("!", args=[self.ast.pars(result)])
            )

            statements.append(
                self.ast.IfStmt(
                    cpp.IfStmtParams(
                        Branches=[
                            cpp.IfStmtParams.Branch(
                                Cond=condition,
                                Then=self.ast.stack(
                                    [
                                        *lowered.statements,
                                        self.ast.Trail(
                                            self.ast.XCall(
                                                "=", args=[result, lowered.value]
                                            ),
                                            self.ast.string(";"),
                                            space="",
                                        ),
                                    ]
                                ),
                            )
                        ]
                    )
                )
            )

        return ExpressionEvaluation(statements, result)

    def _gen_expression_eval_cond(
        self,
        expr: ExprNode,
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> ExpressionEvaluation:
        condition = self._gen_expression_eval(
            expr.args[0],
            this_expr,
            bindings,
        )
        then_value = self._gen_expression_eval(
            expr.args[1],
            this_expr,
            bindings,
        )
        else_value = self._gen_expression_eval(
            expr.args[2],
            this_expr,
            bindings,
        )

        slot, declaration = self._expression_slot(self._expression_result_type(expr))

        branch = self.ast.IfStmt(
            cpp.IfStmtParams(
                Branches=[
                    cpp.IfStmtParams.Branch(
                        Cond=condition.value,
                        Then=self.ast.stack(
                            [
                                *then_value.statements,
                                self.ast.XCallRef(
                                    slot,
                                    "emplace",
                                    args=[then_value.value],
                                    Stmt=True,
                                ),
                            ]
                        ),
                    ),
                    cpp.IfStmtParams.Branch(
                        Then=self.ast.stack(
                            [
                                *else_value.statements,
                                self.ast.XCallRef(
                                    slot,
                                    "emplace",
                                    args=[else_value.value],
                                    Stmt=True,
                                ),
                            ]
                        )
                    ),
                ]
            )
        )

        return ExpressionEvaluation(
            [
                *condition.statements,
                declaration,
                branch,
            ],
            self.ast.XCallRef(slot, "value"),
        )

    def _gen_expression_eval_let(
        self,
        expr: ExprNode,
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> ExpressionEvaluation:
        value = self._gen_expression_eval(
            expr.args[0],
            this_expr,
            bindings,
        )

        local_bindings = dict(bindings)
        local_bindings[expr.binders[0]] = value.value

        body = self._gen_expression_eval(
            expr.args[1],
            this_expr,
            local_bindings,
        )

        return ExpressionEvaluation(
            [*value.statements, *body.statements],
            body.value,
        )

    def _gen_expression_eval_type_cond(
        self,
        expr: ExprNode,
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> ExpressionEvaluation:
        subject = self._gen_expression_eval(
            expr.args[0],
            this_expr,
            bindings,
        )

        ignore_unhandled = bool(expr.bool_val)

        if ignore_unhandled:
            if not isinstance(expr.typed_as, OptT):
                raise TypeError(
                    f"Optional type dispatch at {expr.loc.render()} "
                    f"must have an optional result, got {expr.typed_as!r}"
                )

            value_type = self._expression_native_type(expr.typed_as.elem)
        else:
            value_type = self._expression_result_type(expr)

        slot, declaration = self._expression_slot(value_type)
        statements = [*subject.statements, declaration]

        for case in expr.args[1:]:
            if case.op != OpId.TYPE_CASE or case.type_val is None:
                raise ValueError(
                    f"Invalid type-dispatch branch at "
                    f"{case.loc.render()}: expected TYPE_CASE with "
                    f"a target type, got {case.op.value}"
                )

            candidate_name = self._expression_name("candidate")
            candidate = self.ast.string(candidate_name)

            candidate_declaration = self.ast.VarDecl(
                cpp.ParmVarParams(
                    type=QualType(Name="auto").asConstPtr(),
                    name=candidate_name,
                    defArg=self._expression_runtime_call(
                        "try_as",
                        args=[subject.value],
                        params=[self._expression_native_type(case.type_val)],
                    ),
                )
            )

            local_bindings = dict(bindings)
            local_bindings[case.binders[0]] = self.ast.pars(
                self.ast.XCall("*", args=[candidate])
            )

            body = self._gen_expression_eval(
                case.args[0],
                this_expr,
                local_bindings,
            )

            match_branch = self.ast.IfStmt(
                cpp.IfStmtParams(
                    Branches=[
                        cpp.IfStmtParams.Branch(
                            Cond=self.ast.XCall(
                                "!=",
                                args=[candidate, self.ast.string("nullptr")],
                            ),
                            Then=self.ast.stack(
                                [
                                    *body.statements,
                                    self.ast.XCallRef(
                                        slot,
                                        "emplace",
                                        args=[body.value],
                                        Stmt=True,
                                    ),
                                ]
                            ),
                        )
                    ]
                )
            )

            statements.append(
                self.ast.IfStmt(
                    cpp.IfStmtParams(
                        Branches=[
                            cpp.IfStmtParams.Branch(
                                Cond=self.ast.XCall(
                                    "!",
                                    args=[
                                        self.ast.pars(
                                            self.ast.XCallRef(slot, "has_value")
                                        )
                                    ],
                                ),
                                Then=self.ast.stack(
                                    [
                                        candidate_declaration,
                                        match_branch,
                                    ]
                                ),
                            )
                        ]
                    )
                )
            )

        if not ignore_unhandled:
            expected = ", ".join(
                type_text(case.type_val)
                for case in expr.args[1:]
                if case.type_val is not None
            )

            message = (
                f"No type case matched at {expr.loc.render()}; "
                f"expected one of: {expected}"
            )

            statements.append(
                self.ast.IfStmt(
                    cpp.IfStmtParams(
                        Branches=[
                            cpp.IfStmtParams.Branch(
                                Cond=self.ast.XCall(
                                    "!",
                                    args=[
                                        self.ast.pars(
                                            self.ast.XCallRef(slot, "has_value")
                                        )
                                    ],
                                ),
                                Then=self.ast.Throw(
                                    self.ast.XConstructObj(
                                        self.ast.string("std::runtime_error"),
                                        Args=[self.ast.StringLiteral(message)],
                                    )
                                ),
                            )
                        ]
                    )
                )
            )

        return ExpressionEvaluation(
            statements,
            slot if ignore_unhandled else self.ast.XCallRef(slot, "value"),
        )

    def _gen_expression_eval_collection(
        self,
        expr: ExprNode,
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> ExpressionEvaluation:
        collection = self._gen_expression_eval(
            expr.args[0],
            this_expr,
            bindings,
        )

        callback = self._expression_callback(
            expr.args[1],
            expr.binders,
            this_expr,
            bindings,
        )

        callback_name = self._expression_name("callback")
        callback_value = self.ast.string(callback_name)

        declaration = self.ast.VarDecl(
            cpp.ParmVarParams(
                type=QualType(Name="auto"),
                name=callback_name,
                defArg=callback,
            )
        )

        function = {
            OpId.ALL: "eval_all",
            OpId.EXISTS: "eval_exists",
            OpId.EXISTS_ONE: "eval_exists_one",
            OpId.MAP: "eval_map",
            OpId.FILTER: "eval_filter",
            OpId.FILTER_MAP: "eval_filter_map",
            OpId.TAKE_WHILE: "eval_take_while",
            OpId.GROUP_BY: "eval_group_by",
        }[expr.op]

        match expr.op:
            case OpId.ALL | OpId.EXISTS | OpId.EXISTS_ONE:
                params = []

            case OpId.MAP | OpId.FILTER:
                params = [self._expression_result_type(expr).par0()]

            case _:
                params = [self._expression_result_type(expr)]

        return self._expression_local(
            self._expression_call(
                function,
                args=[collection.value, callback_value],
                params=params,
            ),
            [*collection.statements, declaration],
            expr=expr,
        )

    def _gen_expression_eval_fold(
        self,
        expr: ExprNode,
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> ExpressionEvaluation:
        statements, args = self._expression_args(
            expr.args[:2],
            this_expr,
            bindings,
        )

        callback_name = self._expression_name("callback")
        callback = self._expression_callback(
            expr.args[2],
            expr.binders,
            this_expr,
            bindings,
        )

        statements.append(
            self.ast.VarDecl(
                cpp.ParmVarParams(
                    type=QualType(Name="auto"),
                    name=callback_name,
                    defArg=callback,
                )
            )
        )

        return self._expression_local(
            self._expression_call(
                "eval_fold",
                args=[
                    *args,
                    self.ast.string(callback_name),
                ],
                params=[self._expression_result_type(expr)],
            ),
            statements,
            expr=expr,
        )

    def _gen_expression_arithmetic(
        self,
        expr: ExprNode,
        args: list[BlockId],
    ) -> BlockId:
        operator = {
            OpId.ADD: "+",
            OpId.SUB: "-",
            OpId.MUL: "*",
            OpId.DIV: "/",
        }[expr.op]

        result_type = self._expression_result_type(expr)

        left = args[0]
        right = args[1]

        if expr.op == OpId.DIV:
            left = self.ast.XCall("static_cast", args=[left], Params=[result_type])
            right = self.ast.XCall("static_cast", args=[right], Params=[result_type])

        return self.ast.XCall(
            "static_cast",
            args=[self.ast.pars(self.ast.XCall(operator, args=[left, right]))],
            Params=[result_type],
        )

    def _gen_expression_enum_is(
        self,
        expr: ExprNode,
        args: list[BlockId],
    ) -> BlockId:
        assert expr.str_val is not None
        source_type = expr.args[0].typed_as

        if source_type is None:
            raise ValueError(
                f"Enum comparison at {expr.loc.render()} has no inferred subject type"
            )

        return self.ast.pars(
            self.ast.XCall(
                "==",
                args=[
                    args[0],
                    self._expression_enum_value(source_type, expr.str_val),
                ],
            )
        )

    def _expression_needs_runtime(self, expr: ExprNode) -> bool:
        match expr.op:
            case (
                OpId.WALK | OpId.TYPE_COND | OpId.IS_DERIVED | OpId.PATH_OF | OpId.TYPE_OF
            ):
                return True

            case _:
                return any(self._expression_needs_runtime(arg) for arg in expr.args)

    def _gen_expression_runtime(self) -> List[BlockId]:
        runtime = self.ast.string("expression_runtime")

        statements = [
            self.ast.VarDecl(
                cpp.ParmVarParams(
                    type=QualType(
                        Name="EvalRuntime",
                        Spaces=[CPP_SPACE_T],
                    ),
                    name="expression_runtime",
                    defArg=self.ast.XConstructObj(
                        QualType(
                            Name="EvalRuntime",
                            Spaces=[CPP_SPACE_T],
                        ),
                        Args=[self.ast.string("ctx")],
                    ),
                )
            )
        ]

        gen_registration = False

        if gen_registration:
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

            statements.append(
                self.ast.XCallRef(
                    runtime,
                    "index",
                    args=[
                        self.ast.pars(
                            self.ast.XCall("*", args=[self.ast.string("this_obj")])
                        )
                    ],
                    Stmt=True,
                )
            )

        return statements

    def _gen_check_eval(self, check: CheckDef, this_expr: BlockId) -> BlockId:
        self.expression_counter = 0

        statements: List[BlockId] = []

        if self._expression_needs_runtime(check.cond) or self._expression_needs_runtime(
            check.message
        ):
            statements.extend(self._gen_expression_runtime())

        root = self._expression_local(
            self.ast.pars(self.ast.XCall("*", args=[self.ast.pars(this_expr)]))
        )
        statements.extend(root.statements)

        condition = self._gen_expression_eval(
            check.cond,
            root.value,
        )
        message = self._gen_expression_eval(
            check.message,
            root.value,
        )

        statements.extend(condition.statements)

        statements.append(
            self.ast.IfStmt(
                cpp.IfStmtParams(
                    Branches=[
                        cpp.IfStmtParams.Branch(
                            Cond=condition.value,
                            Then=self.ast.Return(
                                self.ast.CallStatic(
                                    CPP_RESULT_T,
                                    "Ok",
                                )
                            ),
                        ),
                        cpp.IfStmtParams.Branch(
                            Then=self.ast.stack(
                                [
                                    *message.statements,
                                    self.ast.Return(
                                        self.ast.CallStatic(
                                            CPP_RESULT_T,
                                            "Error",
                                            Args=[message.value],
                                        )
                                    ),
                                ]
                            )
                        ),
                    ]
                )
            )
        )

        return self.ast.stack(statements)

    def gen_record_check(
        self,
        owner: RecordDef,
        check: CheckDef,
        parentClass: QualType,
    ) -> GenTuFunction:
        return GenTuFunction(
            Name=f"__check_record_{normalize_ident(check.id)}",
            ReturnType=CPP_RESULT_T,
            Args=[
                GenTuIdent(Type=CPP_CONTEXT_T.asConstPtr(), Name="ctx"),
                GenTuIdent(Type=QualType(Name="void").asConstPtr(), Name="value"),
            ],
            IsStatic=True,
            ParentClass=parentClass,
            Body=self.ast.stack(
                [
                    self.ast.VarDecl(
                        cpp.ParmVarParams(
                            type=QualType(Name="auto").asConstPtr(),
                            name="this_obj",
                            defArg=self.ast.XCall(
                                "static_cast",
                                args=[self.ast.string("value")],
                                Params=[
                                    self.type_map.declaration_type(
                                        self.model.package,
                                        owner.qname,
                                    ).asConstPtr()
                                ],
                            ),
                        )
                    ),
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
        "Generate a single static function used to perform the runtime check on the field state"

        cpp_name = (
            cpp_config(owner)
            .get("field_names", {})
            .get(
                field.name,
                field.name,
            )
        )

        this_expr = self.ast.Addr(
            self.ast.Arrow(
                self.ast.string("this_obj"),
                self.ast.string(cpp_name),
            )
        )

        return GenTuFunction(
            Name=f"__check_{field.name}_{normalize_ident(check.id)}",
            ReturnType=CPP_RESULT_T,
            Args=[
                GenTuIdent(Type=CPP_CONTEXT_T.asConstPtr(), Name="ctx"),
                GenTuIdent(Type=QualType(Name="void").asConstPtr(), Name="value"),
            ],
            IsStatic=True,
            ParentClass=parentClass,
            Body=self.ast.stack(
                [
                    self.ast.VarDecl(
                        cpp.ParmVarParams(
                            type=QualType(Name="auto").asConstPtr(),
                            name="this_obj",
                            defArg=self.ast.XCall(
                                "static_cast",
                                args=[self.ast.string("value")],
                                Params=[
                                    self.type_map.declaration_type(
                                        self.model.package, owner.qname
                                    ).asConstPtr()
                                ],
                            ),
                        )
                    ),
                    self._gen_check_eval(check, this_expr=this_expr),
                ]
            ),
        )
