from __future__ import annotations

import ast
import collections.abc
import inspect
import textwrap
import types
from dataclasses import dataclass

from beartype import beartype
from beartype.typing import (
    Annotated,
    Any,
    Callable,
    Dict,
    ForwardRef,
    List,
    Optional,
    Sequence,
    Tuple,
    TypeVar,
    Union,
    get_args,
    get_origin,
)

from hstd_py_unidata.model_frontend import (
    NO_DEFAULT,
    DslAttr,
    FixedArrayFactory,
    FixedArrayMeta,
    Float32,
    Float64,
    Int8,
    Int16,
    Int32,
    Int64,
    RawField,
    RawMethod,
    RawRecord,
    UInt8,
    UInt16,
    UInt32,
    UInt64,
)
from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    ArrayT,
    CheckContext,
    CheckDef,
    DynT,
    EnumDef,
    EnumValueDef,
    ExplicitDefault,
    ExprNode,
    ExternalT,
    FieldDef,
    ItemPath,
    ListT,
    MapT,
    MethodArgDef,
    MethodDef,
    ModelDef,
    NamedT,
    OpId,
    OptT,
    PrimKind,
    PrimT,
    QName,
    RecordDef,
    RecordKind,
    SourceLoc,
    TupleT,
    TypeAnnotation,
    TypeParamT,
    TypeRef,
    UnresolvedT,
    VariantCaseDef,
    VariantDef,
    VariantT,
    type_text,
)
from hstd_py_unidata.model_ops import Operator
from hstd_py_unidata.model_value import (
    ValueDecodeError,
    decode_json,
    encode_json,
    record_default,
)

PRIMITIVE_TYPES: Dict[Any, PrimKind] = {
    int: PrimKind.INT64,
    Int64: PrimKind.INT64,
    Int8: PrimKind.INT8,
    Int16: PrimKind.INT16,
    Int32: PrimKind.INT32,
    UInt8: PrimKind.UINT8,
    UInt16: PrimKind.UINT16,
    UInt32: PrimKind.UINT32,
    UInt64: PrimKind.UINT64,
    float: PrimKind.FLOAT64,
    Float64: PrimKind.FLOAT64,
    Float32: PrimKind.FLOAT32,
    str: PrimKind.STRING,
    bool: PrimKind.BOOL,
    Any: PrimKind.ANY,
}

BUILTIN_NAMES: Dict[str, Any] = {
    "int": int,
    "float": float,
    "str": str,
    "bool": bool,
    "None": None,
    "Any": Any,
    "List": List,
    "list": list,
    "Dict": Dict,
    "dict": dict,
    "Tuple": Tuple,
    "tuple": tuple,
    "Optional": Optional,
    "Annotated": Annotated,
}


@beartype
@dataclass(frozen=True)
class ModelIssue:
    loc: SourceLoc
    message: str


@beartype
class DslModelError(Exception):
    """Model declarations are inconsistent; every detected issue is listed with its location."""

    def __init__(self, package: str, issues: Sequence[ModelIssue]) -> None:
        lines = "\n".join(f"  {i.loc.render()}: {i.message}" for i in issues)
        super().__init__(
            f"Model '{package}' has {len(issues)} declaration error(s):\n{lines}"
        )
        self.issues = list(issues)


@beartype
class AnnotationError(Exception):
    pass


@beartype
class NameLookup:
    """Lexical scopes of the model: each declaration scope maps short names to nested declarations."""

    def __init__(self) -> None:
        self.members: Dict[Optional[QName], Dict[str, QName]] = {}

    def add(self, qname: QName) -> None:
        self.members.setdefault(qname.scope, {})[qname.name] = qname

    def member(self, scope: Optional[QName], name: str) -> Optional[QName]:
        return self.members.get(scope, {}).get(name)

    def scope_chain(self, scope: Optional[QName]) -> List[Optional[QName]]:
        chain: List[Optional[QName]] = []
        cur = scope
        while cur is not None:
            chain.append(cur)
            cur = cur.scope
        chain.append(None)
        return chain

    def find(self, name: str, scope: Optional[QName]) -> Optional[QName]:
        for s in self.scope_chain(scope):
            found = self.member(s, name)
            if found is not None:
                return found
        return None


@beartype
def map_leaves(t: TypeRef, fn: Callable[[TypeRef], TypeRef]) -> TypeRef:
    """Applies the function to the unresolved and external leaves of a composite type."""
    match t:
        case UnresolvedT() | ExternalT():
            return fn(t)
        case ListT():
            return ListT(elem=map_leaves(t.elem, fn))
        case ArrayT():
            return ArrayT(elem=map_leaves(t.elem, fn), size=t.size)
        case MapT():
            return MapT(key=map_leaves(t.key, fn), value=map_leaves(t.value, fn))
        case OptT():
            return OptT(elem=map_leaves(t.elem, fn))
        case TupleT():
            return TupleT(elems=tuple(map_leaves(e, fn) for e in t.elems))
        case DynT():
            return DynT(root=map_leaves(t.root, fn))
        case _:
            return t


@beartype
class AnnotationResolver:
    """Converts Python annotations to type references; without a lookup, names stay unresolved.

    External references into the package being resolved become references to its own declarations."""

    def __init__(
        self, lookup: Optional[NameLookup], package: Optional[str] = None
    ) -> None:
        self.lookup = lookup
        self.package = package

    def resolve_own(self, t: ExternalT) -> TypeRef:
        assert self.lookup is not None
        scope: Optional[QName] = None
        for part in t.qname.parts():
            found = self.lookup.member(scope, part)
            if found is None:
                known = ", ".join(sorted(self.lookup.members.get(scope, {}))) or "(none)"
                where = scope.to_id() if scope else "the model root"
                raise AnnotationError(
                    f"'{t.qname.to_id()}' does not name a declaration of model '{t.package}': '{part}' is not declared in {where}, declarations there: {known}"
                )
            scope = found
        assert scope is not None
        return NamedT(qname=scope)

    def resolve(
        self,
        ann: Any,
        scope: Optional[QName] = None,
        module_globals: Optional[Dict[str, Any]] = None,
        type_params: Sequence[str] = (),
    ) -> TypeRef:
        globals_map = module_globals or {}
        match ann:
            case UnresolvedT():
                if self.lookup is None:
                    return ann
                return self.resolve_text(ann.text, scope, globals_map, type_params)
            case ListT() | ArrayT() | MapT() | OptT() | TupleT() | DynT():
                return map_leaves(
                    ann, lambda u: self.resolve(u, scope, globals_map, type_params)
                )
            case ExternalT() if self.lookup is not None and ann.package == self.package:
                return self.resolve_own(ann)
            case PrimT() | NamedT() | ExternalT() | VariantT() | TypeParamT():
                return ann
            case None:
                return PrimT(prim=PrimKind.NONE)
            case str():
                if self.lookup is None:
                    return UnresolvedT(text=ann)
                return self.resolve_text(ann, scope, globals_map, type_params)
            case ForwardRef():
                return self.resolve(ann.__forward_arg__, scope, globals_map, type_params)
            case FixedArrayMeta():
                return ArrayT(
                    elem=self.resolve(ann.elem_type, scope, globals_map, type_params),
                    size=ann.size,
                )
            case TypeVar():
                if ann.__name__ not in type_params:
                    raise AnnotationError(
                        f"type variable '{ann.__name__}' is not a type parameter of the enclosing method, declared parameters: {', '.join(type_params) or '(none)'}"
                    )
                return TypeParamT(name=ann.__name__)
        if ann is types.NoneType:
            return PrimT(prim=PrimKind.NONE)

        if isinstance(ann, collections.abc.Hashable) and ann in PRIMITIVE_TYPES:
            return PrimT(prim=PRIMITIVE_TYPES[ann])

        if isinstance(ann, type) and hasattr(ann, DslAttr.QNAME.value):
            return NamedT(qname=getattr(ann, DslAttr.QNAME.value))

        origin = get_origin(ann)
        args = get_args(ann)
        if origin is Annotated:
            result = self.resolve(args[0], scope, globals_map, type_params)
            if 1 < len(args) and isinstance(args[1], TypeAnnotation):
                result = result.model_copy(update={"annotation": args[1]})

            return result

        if origin is list or origin is List:
            return ListT(elem=self.resolve(args[0], scope, globals_map, type_params))

        if origin is dict or origin is Dict:
            return MapT(
                key=self.resolve(args[0], scope, globals_map, type_params),
                value=self.resolve(args[1], scope, globals_map, type_params),
            )
        if origin is tuple or origin is Tuple:
            return TupleT(
                elems=tuple(
                    self.resolve(a, scope, globals_map, type_params) for a in args
                )
            )
        if origin is Union or origin is types.UnionType:
            return self.resolve_union(list(args), scope, globals_map, type_params)
        raise AnnotationError(
            f"unsupported type annotation {ann!r}; expected a primitive marker, a DSL class, List/Dict/Tuple/Optional, FixedArray or an external type"
        )

    def resolve_union(
        self,
        args: List[Any],
        scope: Optional[QName],
        module_globals: Dict[str, Any],
        type_params: Sequence[str],
    ) -> TypeRef:
        non_none = [a for a in args if a is not types.NoneType and a is not None]
        if len(non_none) == 1 and len(non_none) < len(args):
            return OptT(
                elem=self.resolve(non_none[0], scope, module_globals, type_params)
            )
        names = " | ".join(getattr(a, "__name__", repr(a)) for a in args)
        raise AnnotationError(
            f"untagged union '{names}' is not supported because variant cases need stable tags; "
            f"declare the cases as M.Case records and use __variant__(...) in the class body instead"
        )

    def resolve_text(
        self,
        text: str,
        scope: Optional[QName],
        module_globals: Dict[str, Any],
        type_params: Sequence[str],
    ) -> TypeRef:
        try:
            tree = ast.parse(text, mode="eval")
        except SyntaxError as err:
            raise AnnotationError(
                f"annotation string {text!r} is not a valid Python expression: {err.msg}"
            ) from err
        value = self.eval_ast(tree.body, scope, module_globals, type_params)
        return self.resolve(value, scope, module_globals, type_params)

    def eval_ast(
        self,
        node: ast.expr,
        scope: Optional[QName],
        module_globals: Dict[str, Any],
        type_params: Sequence[str],
    ) -> Any:
        assert self.lookup is not None
        match node:
            case ast.Name():
                if node.id in type_params:
                    return TypeParamT(name=node.id)
                found = self.lookup.find(node.id, scope)
                if found is not None:
                    return NamedT(qname=found)
                if node.id in BUILTIN_NAMES:
                    return BUILTIN_NAMES[node.id]
                if node.id in module_globals:
                    return module_globals[node.id]
                searched = ", ".join(
                    s.to_id() if s else "<model root>"
                    for s in self.lookup.scope_chain(scope)
                )
                raise AnnotationError(
                    f"name '{node.id}' is not defined; searched declaration scopes {searched}, then builtin type names and module globals"
                )

            case ast.Attribute():
                base = self.eval_ast(node.value, scope, module_globals, type_params)
                if isinstance(base, NamedT):
                    found = self.lookup.member(base.qname, node.attr)
                    if found is None:
                        nested = (
                            ", ".join(sorted(self.lookup.members.get(base.qname, {})))
                            or "(none)"
                        )
                        raise AnnotationError(
                            f"'{base.qname.to_id()}' has no nested declaration '{node.attr}', nested declarations: {nested}"
                        )
                    return NamedT(qname=found)
                if not hasattr(base, node.attr):
                    raise AnnotationError(
                        f"object {base!r} has no attribute '{node.attr}' used in annotation '{ast.unparse(node)}'"
                    )
                return getattr(base, node.attr)

            case ast.Subscript():
                base = self.eval_ast(node.value, scope, module_globals, type_params)
                elts = (
                    node.slice.elts if isinstance(node.slice, ast.Tuple) else [node.slice]
                )
                args = [
                    self.eval_ast(e, scope, module_globals, type_params) for e in elts
                ]
                return self.apply_generic(
                    base, args, node, scope, module_globals, type_params
                )

            case ast.Constant():
                if isinstance(node.value, str):
                    return self.resolve_text(
                        node.value, scope, module_globals, type_params
                    )
                return node.value

            case ast.BinOp() if isinstance(node.op, ast.BitOr):
                left = self.eval_ast(node.left, scope, module_globals, type_params)
                right = self.eval_ast(node.right, scope, module_globals, type_params)
                return self.resolve_union(
                    [left, right], scope, module_globals, type_params
                )

        raise AnnotationError(
            f"unsupported annotation syntax '{ast.unparse(node)}, node type: {type(node)}'"
        )

    def apply_generic(
        self,
        base: Any,
        args: List[Any],
        node: ast.expr,
        scope: Optional[QName],
        module_globals: Dict[str, Any],
        type_params: Sequence[str],
    ) -> Any:
        def res(value: Any) -> TypeRef:
            return self.resolve(value, scope, module_globals, type_params)

        def expect_count(count: int) -> None:
            if len(args) != count:
                raise AnnotationError(
                    f"'{ast.unparse(node)}' expects {count} type argument(s), got {len(args)}"
                )

        if base is list or base is List:
            expect_count(1)
            return ListT(elem=res(args[0]))
        if base is dict or base is Dict:
            expect_count(2)
            return MapT(key=res(args[0]), value=res(args[1]))
        if base is tuple or base is Tuple:
            return TupleT(elems=tuple(res(a) for a in args))
        if base is Optional:
            expect_count(1)
            return OptT(elem=res(args[0]))
        if base is Annotated:
            return res(args[0])
        if isinstance(base, FixedArrayFactory):
            expect_count(2)
            if not isinstance(args[1], int):
                raise AnnotationError(
                    f"FixedArray size in '{ast.unparse(node)}' must be an integer literal, got {args[1]!r}"
                )
            return ArrayT(elem=res(args[0]), size=args[1])
        if hasattr(base, "__getitem__"):
            return base[args[0] if len(args) == 1 else tuple(args)]
        raise AnnotationError(
            f"'{ast.unparse(node)}' subscripts {base!r}, which is not a generic type"
        )


@beartype
def parse_key_method(func: Callable[..., Any], kind: str) -> Optional[Tuple[str, ...]]:
    """Parses the structural `__hash__`/`__eq__` forms; `None` means a declared method with an `...` body."""
    source = textwrap.dedent(inspect.getsource(func))
    module = ast.parse(source)
    fn = module.body[0]
    if not isinstance(fn, ast.FunctionDef):
        raise AnnotationError(f"expected a function definition for '{func.__name__}'")
    body = list(fn.body)
    if (
        body
        and isinstance(body[0], ast.Expr)
        and isinstance(body[0].value, ast.Constant)
        and isinstance(body[0].value.value, str)
    ):
        body = body[1:]
    if (
        len(body) == 1
        and isinstance(body[0], ast.Expr)
        and isinstance(body[0].value, ast.Constant)
        and body[0].value.value is Ellipsis
    ):
        return None
    arg_names = [a.arg for a in fn.args.args]
    allowed = (
        "return hash((self.field1, self.field2, ...))"
        if kind == "hash"
        else "return (self.field1, self.field2, ...) == (other.field1, other.field2, ...)"
    )

    def attrs(node: ast.expr, owner: str) -> Optional[List[str]]:
        elts = node.elts if isinstance(node, ast.Tuple) else [node]
        names: List[str] = []
        for e in elts:
            if not (
                isinstance(e, ast.Attribute)
                and isinstance(e.value, ast.Name)
                and e.value.id == owner
            ):
                return None
            names.append(e.attr)
        return names

    if (
        len(body) == 1
        and isinstance(body[0], ast.Return)
        and body[0].value is not None
        and arg_names
    ):
        ret = body[0].value
        if (
            kind == "hash"
            and isinstance(ret, ast.Call)
            and isinstance(ret.func, ast.Name)
            and ret.func.id == "hash"
            and len(ret.args) == 1
        ):
            names = attrs(ret.args[0], arg_names[0])
            if names:
                return tuple(names)
        if (
            kind == "eq"
            and len(arg_names) == 2
            and isinstance(ret, ast.Compare)
            and len(ret.ops) == 1
            and isinstance(ret.ops[0], ast.Eq)
        ):
            left = attrs(ret.left, arg_names[0])
            right = attrs(ret.comparators[0], arg_names[1])
            if left and right and left == right:
                return tuple(left)
            if left and right:
                raise AnnotationError(
                    f"__eq__ compares different field lists {left} and {right}; both sides must list the same fields in the same order"
                )
    raise AnnotationError(
        f"unsupported __{kind}__ body {ast.unparse(fn.body[-1])!r}; the only accepted forms are `...` for a declared method or `{allowed}`"
    )


@beartype
class ModelFinalizer:
    """Resolves collected declarations into a `ModelDef`, reporting every issue at once."""

    def __init__(
        self, package: str, raws: Sequence[RawRecord], table: Dict[OpId, Operator]
    ) -> None:
        self.package = package
        self.raws = list(raws)
        self.table = table
        self.issues: List[ModelIssue] = []
        self.lookup = NameLookup()
        self.resolver = AnnotationResolver(self.lookup, package)
        self.by_qname: Dict[QName, RawRecord] = {}

    def issue(self, loc: SourceLoc, message: str) -> None:
        self.issues.append(ModelIssue(loc=loc, message=message))

    def finalize(self) -> ModelDef:
        for raw in self.raws:
            if raw.qname in self.by_qname:
                self.issue(
                    raw.loc,
                    f"declaration '{raw.qname.to_id()}' is declared twice, first at {self.by_qname[raw.qname].loc.render()}",
                )
                continue
            self.by_qname[raw.qname] = raw
            self.lookup.add(raw.qname)
        variant_records: Dict[QName, List[EnumDef]] = {}
        variant_defs: Dict[QName, List[VariantDef]] = {}
        variant_fields: Dict[QName, List[FieldDef]] = {}
        for raw in self.raws:
            if raw.kind != RecordKind.ENUM:
                self.resolve_variants(raw, variant_records, variant_defs, variant_fields)
        records: List[RecordDef] = []
        enums: List[EnumDef] = []
        for raw in self.raws:
            if raw.kind == RecordKind.ENUM:
                enums.append(self.resolve_enum(raw))
            else:
                records.append(
                    self.resolve_record(
                        raw,
                        variant_defs.get(raw.qname, []),
                        variant_fields.get(raw.qname, []),
                    )
                )
                enums.extend(variant_records.get(raw.qname, []))
        if self.issues:
            raise DslModelError(self.package, self.issues)
        model = ModelDef(
            package=self.package,
            records=tuple(records),
            enums=tuple(enums),
        )
        model = self.verify_with_index(model)
        if self.issues:
            raise DslModelError(self.package, self.issues)
        return model

    def resolve_enum(self, raw: RawRecord) -> EnumDef:
        name = raw.qname.to_id()
        if raw.bases:
            bases = ", ".join(base.to_id() for base in raw.bases)
            self.issue(
                raw.loc,
                f"enum '{name}' cannot inherit from {bases} because enum declarations do not support bases",
            )
        for check in raw.checks:
            self.issue(
                check.loc,
                f"enum '{name}' cannot declare check '{check.id}' because checks apply to records and fields",
            )
        for variant in raw.variants:
            self.issue(
                variant.loc,
                f"enum '{name}' cannot declare variant field '{variant.field}' because variants belong to records",
            )
        for method in raw.methods:
            self.issue(
                method.loc,
                f"enum '{name}' cannot declare method '{method.name}' because enum declarations only contain values",
            )
        if raw.hash_func is not None:
            self.issue(
                raw.loc,
                f"enum '{name}' cannot declare '__hash__' because structural hash fields apply to records",
            )
        if raw.eq_func is not None:
            self.issue(
                raw.loc,
                f"enum '{name}' cannot declare '__eq__' because structural equality fields apply to records",
            )
        nested = self.lookup.members.get(raw.qname, {})
        if nested:
            names = ", ".join(sorted(nested))
            self.issue(
                raw.loc,
                f"enum '{name}' cannot contain nested declarations because enums only contain values; nested declarations: {names}",
            )
        return EnumDef(
            qname=raw.qname,
            doc=raw.doc,
            enum_values=tuple(raw.enum_values),
            backend=raw.backend,
            loc=raw.loc,
        )

    def resolve_variants(
        self,
        raw: RawRecord,
        variant_records: Dict[QName, List[EnumDef]],
        variant_defs: Dict[QName, List[VariantDef]],
        variant_fields: Dict[QName, List[FieldDef]],
    ) -> None:
        field_names = {f.name for f in raw.fields}
        for rv in raw.variants:
            cases: List[VariantCaseDef] = []
            for case in rv.cases:
                try:
                    t = self.resolver.resolve(case, raw.qname, raw.module_globals)
                except AnnotationError as err:
                    self.issue(
                        rv.loc,
                        f"variant case of '{raw.qname.to_id()}.{rv.field}' cannot be resolved: {err}",
                    )
                    continue
                if not isinstance(t, NamedT) or t.qname not in self.by_qname:
                    self.issue(
                        rv.loc,
                        f"variant case '{type_text(t)}' of '{raw.qname.to_id()}.{rv.field}' must be a record declared in this model",
                    )
                    continue
                case_raw = self.by_qname[t.qname]
                if case_raw.kind != RecordKind.CASE:
                    self.issue(
                        rv.loc,
                        f"variant case '{t.qname.to_id()}' of '{raw.qname.to_id()}.{rv.field}' must be declared as M.Case, it is declared as M.{case_raw.kind.value.capitalize()} at {case_raw.loc.render()}",
                    )
                    continue
                if any(c.tag == t.qname.name for c in cases):
                    self.issue(
                        rv.loc,
                        f"variant '{raw.qname.to_id()}.{rv.field}' lists case tag '{t.qname.name}' twice; case tags are the short case class names and must be unique",
                    )
                    continue
                cases.append(VariantCaseDef(tag=t.qname.name, case=t.qname))
            if len(cases) == 0:
                self.issue(
                    rv.loc,
                    f"variant '{raw.qname.to_id()}.{rv.field}' has no valid cases",
                )
                continue
            if rv.field in field_names:
                self.issue(
                    rv.loc,
                    f"variant data field '{rv.field}' clashes with a declared field of '{raw.qname.to_id()}'; pass field=\"...\" to __variant__ to choose another name",
                )
                continue
            field_names.add(rv.field)
            kind_q = raw.qname.nested(rv.kind)
            clash = self.lookup.member(raw.qname, rv.kind)
            if clash is not None:
                where = (
                    self.by_qname[clash].loc.render()
                    if clash in self.by_qname
                    else "another __variant__"
                )
                self.issue(
                    rv.loc,
                    f"generated kind enum '{rv.kind}' for variant field '{rv.field}' clashes with nested declaration '{clash.to_id()}' from {where}; pass kind=\"...\" to __variant__ to choose another name",
                )
                continue
            self.lookup.add(kind_q)
            variant_records.setdefault(raw.qname, []).append(
                EnumDef(
                    qname=kind_q,
                    doc=f"Case tags of variant field '{rv.field}' in '{raw.qname.to_id()}'.",
                    enum_values=tuple(
                        EnumValueDef(name=c.tag, value=i, loc=rv.loc)
                        for i, c in enumerate(cases)
                    ),
                    loc=rv.loc,
                )
            )

            variant_defs.setdefault(raw.qname, []).append(
                VariantDef(
                    field=rv.field, kind_enum=kind_q, cases=tuple(cases), loc=rv.loc
                )
            )
            variant_fields.setdefault(raw.qname, []).append(
                FieldDef(
                    name=rv.field,
                    type=VariantT(owner=raw.qname, field=rv.field),
                    doc=f"Variant data, active case is one of {', '.join(c.tag for c in cases)}.",
                    loc=rv.loc,
                )
            )

    def resolve_record(
        self, raw: RawRecord, variants: List[VariantDef], extra_fields: List[FieldDef]
    ) -> RecordDef:
        fields: List[FieldDef] = []
        checks: List[CheckDef] = []
        for rf in raw.fields:
            fdef = self.resolve_field(raw, rf)
            if fdef is None:
                continue
            if rf.check is not None:
                cond = self.resolve_expr(raw, rf.check, ())
                text = (
                    rf.message
                    or f"check of field '{rf.name}' in '{raw.qname.to_id()}' failed"
                )
                fdef.checks.append(
                    CheckDef(
                        id=f"{rf.name}-check",
                        context=CheckContext.FIELD,
                        field=rf.name,
                        cond=cond,
                        message=ExprNode(op=OpId.CONST_STR, str_val=text, loc=rf.loc),
                        loc=rf.loc,
                    )
                )

            fields.append(fdef)

        fields.extend(extra_fields)
        seen_ids: Dict[str, SourceLoc] = {c.id: c.loc for c in checks}
        for idx, rc in enumerate(raw.checks):
            check_id = rc.id or f"check-{idx}"
            if check_id in seen_ids:
                self.issue(
                    rc.loc,
                    f"check id '{check_id}' is used twice in '{raw.qname.to_id()}', first at {seen_ids[check_id].render()}",
                )
            seen_ids[check_id] = rc.loc
            checks.append(
                CheckDef(
                    id=check_id,
                    level=rc.level,
                    cond=self.resolve_expr(raw, rc.cond, ()),
                    message=self.resolve_expr(raw, rc.message, ()),
                    loc=rc.loc,
                )
            )
        methods: List[MethodDef] = []
        for rm in raw.methods:
            mdef = self.resolve_method(raw, rm)
            if mdef is not None:
                methods.append(mdef)
        hash_fields = self.key_fields(raw, raw.hash_func, "hash", methods)
        eq_fields = self.key_fields(raw, raw.eq_func, "eq", methods)
        for b in raw.bases:
            if b not in self.by_qname:
                self.issue(
                    raw.loc,
                    f"base '{b.to_id()}' of '{raw.qname.to_id()}' is not declared in model '{self.package}'; inheritance across models is not supported",
                )
            elif self.by_qname[b].kind == RecordKind.ENUM:
                self.issue(
                    raw.loc,
                    f"'{raw.qname.to_id()}' cannot derive from enum '{b.to_id()}'",
                )
        nested = tuple(self.lookup.members.get(raw.qname, {}).values())
        return RecordDef(
            kind=raw.kind,
            qname=raw.qname,
            doc=raw.doc,
            bases=raw.bases,
            fields=tuple(fields),
            nested=nested,
            variants=tuple(variants),
            methods=tuple(methods),
            checks=tuple(checks),
            backend=raw.backend,
            hash_fields=hash_fields,
            eq_fields=eq_fields,
            loc=raw.loc,
        )

    def key_fields(
        self,
        raw: RawRecord,
        func: Optional[Callable[..., Any]],
        kind: str,
        methods: List[MethodDef],
    ) -> Optional[Tuple[str, ...]]:
        if func is None:
            return None
        try:
            parsed = parse_key_method(func, kind)
        except AnnotationError as err:
            self.issue(raw.loc, f"'{raw.qname.to_id()}.__{kind}__': {err}")
            return None
        if parsed is None:
            mdef = self.resolve_method(
                raw,
                RawMethod(
                    name=f"__{kind}__",
                    func=func,
                    backend={},
                    is_static=False,
                    loc=raw.loc,
                ),
            )
            if mdef is not None:
                methods.append(mdef)
        return parsed

    def resolve_field(self, raw: RawRecord, rf: RawField) -> Optional[FieldDef]:
        try:
            ftype = self.resolver.resolve(rf.annotation, raw.qname, raw.module_globals)
        except AnnotationError as err:
            self.issue(
                rf.loc,
                f"type of field '{rf.name}' in '{raw.qname.to_id()}' cannot be resolved: {err}",
            )
            return None
        default = None if rf.default is NO_DEFAULT else ExplicitDefault(value=rf.default)
        return FieldDef(name=rf.name, type=ftype, doc=rf.doc, default=default, loc=rf.loc)

    def resolve_method(self, raw: RawRecord, rm: RawMethod) -> Optional[MethodDef]:
        func = rm.func
        type_params = tuple(tp.__name__ for tp in getattr(func, "__type_params__", ()))
        annotations = inspect.get_annotations(func)
        is_constructor = rm.name == "__init__"
        where = f"method '{rm.name}' of '{raw.qname.to_id()}'"
        try:
            if is_constructor:
                ret = NamedT(qname=raw.qname)
            elif "return" not in annotations:
                self.issue(rm.loc, f"{where} is missing a return type annotation")
                return None
            else:
                ret = self.resolver.resolve(
                    annotations["return"], raw.qname, raw.module_globals, type_params
                )
            args: List[MethodArgDef] = []
            for idx, param in enumerate(inspect.signature(func).parameters.values()):
                if idx == 0 and not rm.is_static and param.name == "self":
                    continue
                if param.name not in annotations:
                    self.issue(
                        rm.loc,
                        f"argument '{param.name}' of {where} is missing a type annotation",
                    )
                    return None
                args.append(
                    MethodArgDef(
                        name=param.name,
                        type=self.resolver.resolve(
                            annotations[param.name],
                            raw.qname,
                            raw.module_globals,
                            type_params,
                        ),
                        default=None
                        if param.default is inspect.Parameter.empty
                        else ExplicitDefault(value=param.default),
                        is_vararg=param.kind == inspect.Parameter.VAR_POSITIONAL,
                        is_kwarg=param.kind == inspect.Parameter.VAR_KEYWORD,
                    )
                )
        except AnnotationError as err:
            self.issue(rm.loc, f"{where} has an unresolvable annotation: {err}")
            return None
        return MethodDef(
            name=rm.name,
            args=tuple(args),
            return_type=ret,
            type_params=type_params,
            is_static=rm.is_static,
            is_constructor=is_constructor,
            backend=rm.backend,
            doc=inspect.getdoc(func) or "",
            loc=rm.loc,
        )

    def resolve_expr(
        self, raw: RawRecord, node: ExprNode, bound: Tuple[str, ...]
    ) -> ExprNode:
        op = self.table.get(node.op)
        if op is None:
            self.issue(
                node.loc,
                f"operator '{node.op.value}' is not registered in model '{self.package}', registered operators: {', '.join(sorted(o.value for o in self.table))}",
            )
            return node
        if not op.arity_ok(len(node.args)):
            self.issue(
                node.loc,
                f"operator '{node.op.value}' expects {op.arity_text()}, got {len(node.args)}",
            )
        if len(node.binders) != op.binder_count:
            self.issue(
                node.loc,
                f"operator '{node.op.value}' introduces {op.binder_count} binder(s), got {len(node.binders)}: {list(node.binders)}",
            )
        for b in node.binders:
            if b in bound:
                self.issue(
                    node.loc,
                    f"binder '{b}' of '{node.op.value}' shadows an enclosing binder with the same name; enclosing binders: {', '.join(bound)}",
                )
        if node.op == OpId.VAR and node.str_val not in bound:
            self.issue(
                node.loc,
                f"M.Iter({node.str_val!r}) refers to a binder that is not in scope; binders in scope: {', '.join(bound) or '(none)'}",
            )
        type_val = node.type_val
        if type_val is not None:
            try:
                type_val = self.resolver.resolve(type_val, raw.qname, raw.module_globals)
            except AnnotationError as err:
                self.issue(
                    node.loc,
                    f"type argument of '{node.op.value}' cannot be resolved: {err}",
                )
        match node.op:
            case OpId.TYPE_CASE if not isinstance(type_val, (NamedT, PrimT)):
                self.issue(
                    node.loc,
                    f"type_case pattern '{type_text(type_val) if type_val else '?'}' must be a record, enum or primitive type, "
                    f"because container values carry no runtime element type; match the element type instead",
                )
            case OpId.IS_DERIVED if not (
                isinstance(type_val, NamedT)
                and type_val.qname in self.by_qname
                and self.by_qname[type_val.qname].kind != RecordKind.ENUM
            ):
                self.issue(
                    node.loc,
                    f"is_derived_from target '{type_text(type_val) if type_val else '?'}' must be a record declared in this model",
                )
            case OpId.TYPE_COND:
                for case in node.args[1:]:
                    if case.op != OpId.TYPE_CASE:
                        self.issue(
                            case.loc,
                            f"type_cond arguments after the subject must be type_case(...) expressions, got '{case.op.value}'",
                        )
            case _:
                pass
        args = tuple(
            self.resolve_expr(
                raw, a, bound + node.binders if i in op.scoped_args else bound
            )
            for i, a in enumerate(node.args)
        )
        return node.model_copy(update={"args": args, "type_val": type_val})

    def verify_with_index(self, model: ModelDef) -> ModelDef:
        index = ModelIndex(model)
        records: List[RecordDef] = []
        for rec in model.records:
            inherited: Dict[str, QName] = {}
            for anc in index.ancestors(rec.qname)[1:]:
                for f in index.record(anc).fields:
                    inherited.setdefault(f.name, anc)
            for f in rec.fields:
                if f.name in inherited:
                    self.issue(
                        f.loc,
                        f"field '{f.name}' of '{rec.qname.to_id()}' redeclares the field inherited from '{inherited[f.name].to_id()}'",
                    )
            names = [f.name for f in index.effective_fields(rec.qname)]
            for label, key_fields in (
                ("__hash__", rec.hash_fields),
                ("__eq__", rec.eq_fields),
            ):
                for name in key_fields or ():
                    if name not in names:
                        self.issue(
                            rec.loc,
                            f"{label} of '{rec.qname.to_id()}' uses field '{name}' which does not exist, available fields: {', '.join(names)}",
                        )
            fields: List[FieldDef] = []
            for f in rec.fields:
                if f.default is None:
                    fields.append(f)
                    continue
                try:
                    decoded = decode_json(
                        index, f.type, f.default.value, ItemPath().field(f.name)
                    )
                    normalized = ExplicitDefault(
                        value=encode_json(index, f.type, decoded)
                    )
                    fields.append(f.model_copy(update={"default": normalized}))
                except (ValueDecodeError, TypeError, KeyError) as err:
                    reason = (
                        "only optional fields accept None"
                        if f.default.value is None
                        else str(err)
                    )
                    self.issue(
                        f.loc,
                        f"default value {f.default.value!r} of field '{f.name}' in '{rec.qname.to_id()}' is invalid for type '{type_text(f.type)}': {reason}",
                    )
                    fields.append(f)
            records.append(rec.model_copy(update={"fields": tuple(fields)}))
        if self.issues:
            return model
        normalized_model = ModelDef(
            package=model.package,
            records=tuple(records),
            enums=model.enums,
        )
        normalized_index = ModelIndex(normalized_model)
        for rec in normalized_model.records:
            if rec.kind != RecordKind.ENUM:
                try:
                    record_default(normalized_index, rec.qname)
                except TypeError as err:
                    self.issue(rec.loc, str(err))
        return normalized_model
