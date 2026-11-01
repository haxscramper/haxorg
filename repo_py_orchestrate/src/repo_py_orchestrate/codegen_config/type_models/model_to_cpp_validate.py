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
    ExpressionEvaluation,
    TypeTranslation,
    cpp_config,
    enum_member_name,
    format_expr_repr,
    named_cpp_type,
    normalize_ident,
)

GEN_EXPRESSION_COMMENTS = False
GEN_EXPRESSION_OP_NAME = False
RUNTIME_DEPENDANT_KINDS = [
    OpId.WALK,
    OpId.TYPE_COND,
    OpId.IS_DERIVED,
    OpId.PATH_OF,
    OpId.TYPE_OF,
]

CPP_SHORT_SPACE_T = QualType(Name="ud", IsNamespace=True)


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

    def _get_uni_value_ptr(self, value: BlockId) -> BlockId:
        return self.ast.XCallRef(value, "get")

    def _get_uni_value_ref(self, value: BlockId) -> BlockId:
        return self._expression_call("get_stored_value", [value])

    def _expression_name(self, stem: str = "expr") -> str:
        result = f"{stem}{self.expression_counter}"
        self.expression_counter += 1
        return result

    def _wrap_uni_static(self, type: QualType) -> QualType:
        return QualType(Name="S", Spaces=[CPP_SHORT_SPACE_T], Params=[type])

    def _map_model_type(self, type: TypeRef) -> QualType:
        """
        Map a model type to its materialized expression representation.

        Container elements are expression values themselves, allowing
        rearrangement without losing their original access paths.
        """
        result = self._expression_native_type(type)

        match type:
            case DynT():
                return result

            case ListT():
                result = result.withTemplateParams([self._map_model_type(type.elem)])

            case MapT():
                result = result.withTemplateParams(
                    [
                        self._map_model_type(type.key),
                        self._map_model_type(type.value),
                    ]
                )

            case OptT():
                result = result.withTemplateParams([self._map_model_type(type.elem)])

            case TupleT():
                result = result.withTemplateParams(
                    [self._map_model_type(elem) for elem in type.elems]
                )

            case _:
                pass

        return self._wrap_uni_static(result)

    def _expression_local(
        self,
        value: BlockId,
        statements: Sequence[BlockId] = (),
        *,
        expr: Optional[ExprNode] = None,
    ) -> ExpressionEvaluation:
        name = self._expression_name()

        if expr:
            var_type = self._expression_result_type(expr)

        else:
            var_type = CPP_AUTO_T()

        declaration = self.ast.VarDecl(
            cpp.ParmVarParams(
                type=var_type.asConstRef(),
                name=name,
                defArg=value,
            )
        )

        result_statements = list(statements)

        if expr is not None:
            if GEN_EXPRESSION_COMMENTS:
                result_statements.append(
                    self.ast.Comment(
                        format_expr_repr(expr).splitlines(),
                        Inline=False,
                    )
                )
            elif GEN_EXPRESSION_OP_NAME:
                result_statements.append(self.ast.Comment(str(expr.op), Inline=False))

        result_statements.append(declaration)

        return ExpressionEvaluation(
            statements=result_statements,
            value=self.ast.string(name),
        )

    def _op_call(
        self,
        op: OpId,
        args: Sequence[BlockId] = (),
        params: Sequence[QualType] = (),
        is_stmt: bool = False,
        Line: bool = True,
    ) -> BlockId:
        return self.ast.CallStatic(
            CPP_SHORT_SPACE_T,
            "eval_op",
            Args=list(args),
            Params=[self._gen_op_id(op)] + (list(params) if params else []),
            Stmt=is_stmt,
            Line=Line,
        )

    def _expression_call(
        self,
        name: str,
        args: Sequence[BlockId] = (),
        params: Sequence[QualType] = (),
        is_stmt: bool = False,
    ) -> BlockId:
        return self.ast.CallStatic(
            CPP_SHORT_SPACE_T,
            name,
            Args=list(args),
            Params=list(params) if params else None,
            Stmt=is_stmt,
        )

    def _gen_op_id(self, op: OpId) -> QualType:
        return QualType(Name=f"OpId::{op.name}", Spaces=[CPP_SHORT_SPACE_T])

    def _expr_scope(self, expr: ExprNode) -> BlockId:
        return self.ast.XCall(
            "UNIDATA_SCOPE",
            args=[
                self.ast.string("ctx"),
                self.ast.StringLiteral(Path(expr.loc.file).name),
                self.ast.Literal(expr.loc.line),
                self.ast.Type(self._gen_op_id(expr.op)),
            ],
            Stmt=True,
        )

    def _expr_context_gen(self, expr: ExprNode) -> BlockId:
        return self._expression_call(
            "get_context",
            args=[
                self.ast.string("ctx"),
                self.ast.StringLiteral(Path(expr.loc.file).name),
                self.ast.Literal(expr.loc.line),
            ],
        )

    def _expression_native_type(
        self,
        typ: TypeRef,
        package: Optional[str] = None,
        space: QualType = CPP_SHORT_SPACE_T,
    ) -> QualType:
        """
        Given a model type, map it directly to the C++ type, without adding
        any extra wrappers or rewriting this result. This performs direct
        1:1 translation of the type as-is.
        """
        package = self.model.package if package is None else package
        return self.type_map.type(typ, package, space=space)

    def _expression_result_type(
        self, expr: ExprNode, space: QualType = CPP_SHORT_SPACE_T
    ) -> QualType:
        """
        Given an expression `expr`, what is the full C++ type that the
        generated code would instantiate?
        """
        if expr.typed_as is None:
            raise ValueError(
                f"Cannot lower '{expr.op.value}' at {expr.loc.render()}: "
                "the finalized expression has no inferred type. Expr tree:\n"
                f"{render_rich(expr_tree_repr(expr))}"
            )

        else:
            return self._map_model_type(expr.typed_as)

    def _set_slot(self, slot: BlockId, value: BlockId) -> BlockId:
        return self._expression_call("set_value", args=[slot, value], is_stmt=True)

    def _read_slot(self, slot: BlockId) -> BlockId:
        return self._expression_call("get_value_ref", args=[slot])

    def _read_slot_as_bool(self, slot: BlockId) -> BlockId:
        return self.ast.XCall(
            "!",
            args=[self._expression_call("get_stored_as_bool", [slot])],
        )

    def _expression_slot(
        self,
        typ: QualType,
    ) -> Tuple[BlockId, BlockId]:
        name = self._expression_name("result")
        value = self.ast.string(name)

        slot_type = self._wrap_uni_static(
            named_cpp_type("UniOpt", [typ]).withChangedSpace(CPP_SHORT_SPACE_T)
        )

        declaration = self.ast.VarDecl(
            cpp.ParmVarParams(
                type=slot_type,
                name=name,
                defArg=self.ast.CallStatic(
                    slot_type,
                    "FromConst",
                    [
                        self.ast.string("std::nullopt"),
                        self.ast.StringLiteral("std::nullopt"),
                    ],
                ),
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

    def _expression_as_iife(
        self,
        body: ExprNode,
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> BlockId:
        lowered = self._gen_expression_eval(
            body,
            this_expr,
            bindings,
        )

        return self.ast.Lambda(
            cpp.LambdaParams(
                ResultTy=self._expression_result_type(body),
                CaptureList=[cpp.LambdaCapture(ByRef=True)],
                Body=[
                    *lowered.statements,
                    self.ast.Return(lowered.value),
                ],
                IsLine=False,
            )
        )

    def _expression_callback(
        self,
        body: ExprNode,
        binders: Sequence[str],
        this_expr: BlockId,
        bindings: dict[str, BlockId],
        binder_types: Sequence[TypeRef],
    ) -> BlockId:
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
            local_bindings[binder] = self.ast.string(name)

        lowered = self._gen_expression_eval(
            body,
            this_expr,
            local_bindings,
        )

        return self.ast.Lambda(
            cpp.LambdaParams(
                Args=parameters,
                ResultTy=self._expression_result_type(body),
                CaptureList=[cpp.LambdaCapture(ByRef=True)],
                Body=[
                    self._gen_expr_comment_tree(body),
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

                    return self._op_call(
                        OpId.GET_FIELD,
                        args=[
                            self._expr_context_gen(expr),
                            source,
                            self.ast.StringLiteral(cpp_name),
                        ],
                        params=[self._expression_result_type(expr)],
                    )

        return self._op_call(
            expr.op,
            args=[
                self._expr_context_gen(expr),
                source,
                self.ast.StringLiteral(expr.str_val),
            ],
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

                return self._op_call(
                    expr.op,
                    args=[self._expr_context_gen(expr), source],
                    params=[
                        self._expression_result_type(expr),
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
                return self._op_call(
                    expr.op,
                    args=[
                        self._expr_context_gen(expr),
                        source,
                    ],
                    params=[self._expression_result_type(expr)],
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

        def from_const(value: BlockId, expr_str: str):
            return self._expression_local(
                self.ast.CallStatic(
                    typ=self._expression_result_type(expr),
                    opc="FromConst",
                    Args=[
                        self.ast.XCall(
                            "static_cast",
                            args=[value],
                            Params=[self._expression_native_type(expr.typed_as)],
                        ),
                        self.ast.StringLiteral(expr_str),
                    ],
                ),
                expr=expr,
            )

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
                return from_const(
                    value=self.ast.Literal(expr.int_val),
                    expr_str=str(expr.int_val),
                )

            case OpId.CONST_FLOAT:
                assert expr.float_val is not None
                value = json.dumps(expr.float_val, allow_nan=False)
                return from_const(
                    value=self.ast.string(value),
                    expr_str=value,
                )

            case OpId.CONST_BOOL:
                assert expr.bool_val is not None
                return from_const(
                    value=self.ast.string("true" if expr.bool_val else "false"),
                    expr_str="true" if expr.bool_val else "false",
                )

            case OpId.CONST_STR:
                assert expr.str_val is not None
                return from_const(
                    value=self.ast.StringLiteral(expr.str_val),
                    expr_str=expr.str_val,
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
                    self._op_call(
                        expr.op,
                        args=[self._expr_context_gen(expr), self.ast.pars(arg.value)],
                        params=[self._expression_result_type(expr)],
                    ),
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

            case _:
                statements, args = self._expression_args(
                    expr.args,
                    this_expr,
                    bindings,
                )

        match expr.op:
            case OpId.GET_FIELD:
                value = self._expression_field_access(expr, args[0])

            case OpId.STR_MATCHES:
                assert expr.str_val is not None
                value = self._op_call(
                    expr.op,
                    args=[
                        self._expr_context_gen(expr),
                        args[0],
                        self.ast.StringLiteral(expr.str_val),
                    ],
                    params=[self._expression_result_type(expr)],
                )

            case OpId.STR_FORMAT:
                assert expr.str_val is not None
                value = self._op_call(
                    expr.op,
                    args=[
                        self._expr_context_gen(expr),
                        self.ast.XCall(
                            "eval_str_pattern",
                            args=[self.ast.StringLiteral(expr.str_val)],
                        ),
                        *args,
                    ],
                    params=[self._expression_result_type(expr)],
                )

            case (
                OpId.LIST_CONTAINS
                | OpId.MAP_GET
                | OpId.LIST_AT
                | OpId.MAP_CONTAINS
                | OpId.LIST_SLICE
                | OpId.LIST_CONCAT
                | OpId.MAP_INSERT
                | OpId.MAP_KEYS
                | OpId.MAP_VALUES
                | OpId.SUM
                | OpId.MIN
                | OpId.MAX
                | OpId.OPT_HAS_VALUE
                | OpId.OPT_VALUE
                | OpId.PATH_OF
                | OpId.TYPE_OF
                | OpId.LIST_SIZE
                | OpId.STR_SIZE
                | OpId.MAP_SIZE
                | OpId.LT
                | OpId.LE
                | OpId.ADD
                | OpId.SUB
                | OpId.MUL
                | OpId.DIV
                | OpId.EQ
                | OpId.NE
                | OpId.LIST_EMPTY
                | OpId.MAP_EMPTY
            ):
                if expr.op in RUNTIME_DEPENDANT_KINDS:
                    args.insert(0, self.ast.string("expression_runtime"))

                args.insert(0, self._expr_context_gen(expr))

                value = self._op_call(
                    expr.op,
                    args=args,
                    params=[self._expression_result_type(expr)],
                )

            case OpId.CASE_IS:
                value = self._expression_case_test(expr, args[0])

            case OpId.CASE_WHICH:
                value = self._expression_case_kind(expr, args[0])

            case OpId.ENUM_IS:
                value = self._gen_expression_enum_is(expr, args)

            case OpId.NTH_GET:
                assert expr.int_val is not None
                value = self._op_call(
                    expr.op,
                    args=[self._expr_context_gen(expr), args[0]],
                    params=[
                        self._expression_result_type(expr),
                        QualType(
                            Kind=QualTypeKind.TypeExpr,
                            Expr=str(expr.int_val),
                        ),
                    ],
                )

            case OpId.WALK:
                value = self._op_call(
                    expr.op,
                    args=[
                        self._expr_context_gen(expr),
                        self.ast.string("expression_runtime"),
                        args[0],
                    ],
                    params=[self._expression_result_type(expr)],
                )

            case OpId.IS_DERIVED:
                if expr.type_val is None:
                    raise ValueError(
                        f"Derived-type test at {expr.loc.render()} has no target type"
                    )

                value = self._op_call(
                    expr.op,
                    args=[
                        self._expr_context_gen(expr),
                        self.ast.string("expression_runtime"),
                        args[0],
                    ],
                    params=[
                        self._expression_result_type(expr),
                        self._expression_native_type(expr.type_val),
                    ],
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

        op_call_expr = self._op_call(
            expr.op,
            args=[self._expr_context_gen(expr)]
            + [self._expression_as_iife(arg, this_expr, bindings) for arg in expr.args],
            params=[self._expression_result_type(expr)],
            Line=False,
        )

        return self._expression_local(value=op_call_expr)

    def _gen_expression_eval_cond(
        self,
        expr: ExprNode,
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> ExpressionEvaluation:
        return self._expression_local(
            self._op_call(
                expr.op,
                args=[self._expr_context_gen(expr)]
                + [
                    self._expression_as_iife(arg, this_expr, bindings)
                    for arg in expr.args
                ],
                params=[self._expression_result_type(expr)],
                Line=False,
            )
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

            value_type = self._map_model_type(expr.typed_as.elem)
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
                    type=self._wrap_uni_static(
                        self._expression_native_type(case.type_val)
                    ).withWrapperType(QualType(Name="hstd::Opt")),
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
                            Cond=self.ast.XCallRef(candidate, "has_value", args=[]),
                            Then=self.ast.stack(
                                [
                                    *body.statements,
                                    self._set_slot(slot, body.value),
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
                                Cond=self._read_slot_as_bool(slot),
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
                                Cond=self._read_slot_as_bool(slot),
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
            slot if ignore_unhandled else self._read_slot(slot),
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
            binder_types=expr.binder_types,
        )

        callback_name = self._expression_name("callback")
        callback_value = self.ast.string(callback_name)

        declaration = self.ast.VarDecl(
            cpp.ParmVarParams(
                type=CPP_AUTO_T(),
                name=callback_name,
                defArg=callback,
            )
        )

        return self._expression_local(
            self._op_call(
                expr.op,
                args=[self._expr_context_gen(expr), collection.value, callback_value],
                params=[self._expression_result_type(expr)],
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
            binder_types=expr.binder_types,
        )

        statements.append(
            self.ast.VarDecl(
                cpp.ParmVarParams(
                    type=CPP_AUTO_T(),
                    name=callback_name,
                    defArg=callback,
                )
            )
        )

        return self._expression_local(
            self._op_call(
                expr.op,
                args=[
                    self._expr_context_gen(expr),
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
            OpId.ADD: "eval_add",
            OpId.SUB: "eval_sub",
            OpId.MUL: "eval_mul",
            OpId.DIV: "eval_div",
        }[expr.op]
        result_type = self._expression_result_type(expr)
        return self._expression_call(operator, args=args, params=[result_type])

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

        return self._op_call(
            OpId.EQ,
            args=[
                self._expr_context_gen(expr),
                args[0],
                self._expression_enum_value(source_type, expr.str_val),
            ],
            params=[self._expression_result_type(expr)],
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

    def _gen_expression_runtime_registrations(self) -> List[BlockId]:
        runtime = self.ast.string("expression_runtime")

        statements: List[BlockId] = []

        gen_registration = True

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

        return statements

    def _gen_expr_comment_tree(self, expr: ExprNode) -> BlockId:
        return self.ast.Comment(
            render_rich(
                expr_tree_repr(
                    expr,
                    with_expr_id=False,
                )
            ),
            Inline=False,
        )

    def _gen_check_eval(self, check: CheckDef, this_expr: BlockId) -> BlockId:
        self.expression_counter = 0

        statements: List[BlockId] = []

        statements.append(self._gen_expr_comment_tree(check.cond))

        if self._expression_needs_runtime(check.cond) or self._expression_needs_runtime(
            check.message
        ):
            statements.extend(self._gen_expression_runtime())

        root = self._expression_local(self.ast.pars(this_expr))
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
                            Cond=self._get_uni_value_ref(condition.value),
                            Then=self.ast.Return(
                                self.ast.CallStatic(
                                    CPP_RESULT_T(CPP_SHORT_SPACE_T),
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
                                            CPP_RESULT_T(CPP_SHORT_SPACE_T),
                                            "Error",
                                            Args=[self._get_uni_value_ref(message.value)],
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

    def _get_check_args(self) -> List[GenTuIdent]:
        return [
            GenTuIdent(Type=CPP_CONTEXT_T().asConstPtr(), Name="ctx"),
            GenTuIdent(Type=QualType(Name="void").asConstPtr(), Name="value"),
        ]

    def _decl_this_object(self, owner: RecordDef) -> List[BlockId]:
        return [
            self.ast.VarDecl(
                cpp.ParmVarParams(
                    type=CPP_AUTO_T().asConstPtr(),
                    name="this_obj_ptr",
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
            self.ast.VarDecl(
                cpp.ParmVarParams(
                    type=CPP_AUTO_T(),
                    name="this_obj",
                    defArg=self.ast.CallStatic(
                        typ=self._wrap_uni_static(
                            self.type_map.declaration_type(
                                self.model.package, owner.qname
                            )
                        ),
                        opc="RootValue",
                        Args=[
                            self.ast.string("this_obj_ptr"),
                            self.ast.XCallPtr(self.ast.string("ctx"), "getPath"),
                        ],
                    ),
                )
            ),
        ]

    def gen_record_check(
        self,
        owner: RecordDef,
        check: CheckDef,
        parentClass: QualType,
    ) -> GenTuFunction:
        return GenTuFunction(
            Name=f"__check_record_{normalize_ident(check.id)}",
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
        "Generate a single static function used to perform the runtime check on the field state"

        cpp_name = (
            cpp_config(owner)
            .get("field_names", {})
            .get(
                field.name,
                field.name,
            )
        )

        this_expr = self.ast.XCallRef(
            self.ast.string("this_obj"),
            opc="Field",
            args=[
                self.ast.Addr(
                    self.ast.Arrow(
                        self._get_uni_value_ptr(self.ast.string("this_obj")),
                        self.ast.string(cpp_name),
                    )
                ),
                self.ast.StringLiteral(cpp_name),
            ],
        )

        return GenTuFunction(
            Name=f"__check_{field.name}_{normalize_ident(check.id)}",
            ReturnType=CPP_RESULT_T(),
            Args=self._get_check_args(),
            IsStatic=True,
            ParentClass=parentClass,
            Body=self.ast.stack(
                [
                    *self._decl_this_object(owner),
                    self._gen_check_eval(check, this_expr=this_expr),
                ]
            ),
        )
