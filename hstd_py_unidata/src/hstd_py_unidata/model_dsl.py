from __future__ import annotations

import ast
import enum
import inspect
import sys
import types
from dataclasses import dataclass, field
from pathlib import Path

from beartype import beartype
from beartype.typing import (
    Annotated,
    Any,
    Callable,
    ClassVar,
    Dict,
    List,
    Optional,
    Sequence,
    Tuple,
    get_args,
    get_origin,
)
from hstd_py_lib.external_packages.rich_utils import render_rich

from hstd_py_unidata.model_diagnostics import (
    Diagnostic,
    DslTypeError,
    build_diagnostics,
)
from hstd_py_unidata.model_eval import CheckFailure, validate
from hstd_py_unidata.model_expr import (
    Expr,
    current_loc,
    frontend_entry,
    this_expr,
    to_node,
    var_expr,
)
from hstd_py_unidata.model_frontend import (
    NO_DEFAULT,
    DslAttr,
    EnFieldAnnotation,
    ExternalTypeLookup,
    MethodWrapper,
    RawCheck,
    RawField,
    RawMethod,
    RawRecord,
    RawVariant,
)
from hstd_py_unidata.model_gen import (
    GenConfig,
    GeneratorFunc,
    GenOverrides,
    generate_value,
)
from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    ClassConfig,
    EnumValueDef,
    ModelDef,
    NamedT,
    OpId,
    QName,
    RecordKind,
    Severity,
    SourceLoc,
    TypeRef,
    model_tree_repr,
)
from hstd_py_unidata.model_ops import Operator, default_operators, operator_table
from hstd_py_unidata.model_reduce import (
    Predicate,
    ReduceConfig,
    ReductionResult,
    reduce_value,
)
from hstd_py_unidata.model_resolve import AnnotationResolver, ModelFinalizer, NameLookup
from hstd_py_unidata.model_souffle import TypeCheckOutput, run_type_check
from hstd_py_unidata.model_value import Value, decode_json, encode_json

DIRECTIVE_NAMES = ("__check__", "__variant__", "__config__")


@beartype
@dataclass
class FieldSpec:
    """Field declaration options; the default is in the JSON value encoding and `None` means no value."""

    doc: str
    default: Any
    check: Optional[Expr]
    message: Optional[Expr]
    loc: SourceLoc


@beartype
@dataclass
class ClassBuildState:
    """Class-local directive collector injected into the class body namespace by the metaclass."""

    checks: List[RawCheck] = field(default_factory=list)
    variants: List[RawVariant] = field(default_factory=list)
    backend: Dict[str, Any] = field(default_factory=dict)
    class_config: ClassConfig = field(default_factory=lambda: ClassConfig())

    @frontend_entry
    def check(
        self,
        cond: Any,
        message: Any = "",
        id: str = "",
        level: Severity = Severity.ERROR,
    ) -> None:
        text = (
            message
            if not (isinstance(message, str) and message == "")
            else f"check '{id or len(self.checks)}' failed"
        )
        self.checks.append(
            RawCheck(
                id=id,
                cond=to_node(cond),
                message=to_node(text),
                level=level,
                loc=current_loc(),
            )
        )

    @frontend_entry
    def variant(self, *cases: Any, field: str = "data", kind: str = "Kind") -> None:
        if not field.isidentifier() or not kind.isidentifier():
            raise ValueError(
                f"__variant__ field name {field!r} and kind enum name {kind!r} must be valid identifiers"
            )
        self.variants.append(
            RawVariant(cases=cases, field=field, kind=kind, loc=current_loc())
        )

    @frontend_entry
    def config(
        self,
        backend: Dict[str, Any] = dict(),
        class_config: ClassConfig = ClassConfig(),
    ) -> None:
        overlap = sorted(set(backend) & set(self.backend))
        if overlap:
            raise ValueError(
                f"__config__ sets backend key(s) {overlap} that an earlier __config__ of the same class already set, at {current_loc().render()}"
            )
        self.backend.update(backend)
        self.class_config = class_config


@beartype
def directive_outside_class(name: str) -> None:
    raise RuntimeError(
        f"{name}(...) was called outside of a DSL class body; directives are only available directly in the body of classes deriving from M.Class, M.Case or M.Enum"
    )


def __check__(
    cond: Any, message: Any = "", id: str = "", level: Severity = Severity.ERROR
) -> None:
    """Declares a check of the enclosing class, the class body version shadows this one."""
    directive_outside_class("__check__")


def __variant__(*cases: Any, field: str = "data", kind: str = "Kind") -> None:
    """Declares a variant field with a generated kind enum, the class body version shadows this one."""
    directive_outside_class("__variant__")


def __config__(
    backend: Dict[str, Any] = dict(),
    class_config: ClassConfig = ClassConfig(),
) -> None:
    """Attaches opaque backend data to the enclosing class, the class body version shadows this one."""
    directive_outside_class("__config__")


@beartype
def qname_from_qualname(qualname: str) -> QName:
    parts = qualname.split(".")
    if "<locals>" in parts:
        parts = parts[len(parts) - 1 - parts[::-1].index("<locals>") + 1 :]
    qname: Optional[QName] = None
    for part in parts:
        qname = QName(name=part, scope=qname)
    assert qname is not None
    return qname


@beartype
def enum_value_doc(annotation: Any) -> str:
    if isinstance(annotation, str):
        try:
            tree = ast.parse(annotation, mode="eval")
        except SyntaxError:
            return ""
        for node in ast.walk(tree):
            if (
                isinstance(node, ast.Call)
                and getattr(node.func, "id", getattr(node.func, "attr", ""))
                == "EnFieldAnnotation"
            ):
                for kw in node.keywords:
                    if (
                        kw.arg == "doc"
                        and isinstance(kw.value, ast.Constant)
                        and isinstance(kw.value.value, str)
                    ):
                        return kw.value.value
        return ""
    if get_origin(annotation) is Annotated:
        for meta in get_args(annotation)[1:]:
            if isinstance(meta, EnFieldAnnotation):
                return meta.doc
    return ""


@beartype
def is_class_var(annotation: Any) -> bool:
    if isinstance(annotation, str):
        return annotation.startswith(("ClassVar", "typing.ClassVar"))
    return annotation is ClassVar or get_origin(annotation) is ClassVar


class DslMeta(type):
    """Collects class declarations of a model; the classes themselves are never instantiated as data."""

    @classmethod
    def __prepare__(
        mcls, name: str, bases: Tuple[type, ...], **kwargs: Any
    ) -> Dict[str, Any]:
        state = ClassBuildState()
        return {
            DslAttr.BUILD.value: state,
            "__check__": state.check,
            "__variant__": state.variant,
            "__config__": state.config,
        }

    def __new__(
        mcls, name: str, bases: Tuple[type, ...], ns: Dict[str, Any], **kwargs: Any
    ) -> DslMeta:
        state = ns.pop(DslAttr.BUILD.value, ClassBuildState())
        for directive in DIRECTIVE_NAMES:
            ns.pop(directive, None)
        if ns.get(DslAttr.ROOT.value, False):
            return super().__new__(mcls, name, bases, ns)
        where = f"{ns.get('__module__', '?')}.{ns.get('__qualname__', name)}"
        models = {
            id(getattr(b, DslAttr.MODEL.value)): getattr(b, DslAttr.MODEL.value)
            for b in bases
            if hasattr(b, DslAttr.MODEL.value)
        }
        if len(models) != 1:
            raise TypeError(
                f"Class {where} must derive from declarations of exactly one DSL model (M.Class, M.Case, M.Enum or their subclasses), got {len(models)} model(s)"
            )
        model: DslModel = next(iter(models.values()))
        kinds = {
            getattr(b, DslAttr.KIND.value)
            for b in bases
            if hasattr(b, DslAttr.KIND.value)
        }
        if len(kinds) != 1:
            raise TypeError(
                f"Class {where} mixes declaration kinds {sorted(k.value for k in kinds)}; derive from one of M.Class, M.Case or M.Enum"
            )
        kind: RecordKind = next(iter(kinds))
        qname = qname_from_qualname(str(ns.get("__qualname__", name)))
        ns[DslAttr.QNAME.value] = qname
        ns[DslAttr.KIND.value] = kind
        cls = super().__new__(mcls, name, bases, ns)
        module = sys.modules.get(str(ns.get("__module__", "")))
        module_globals: Dict[str, Any] = dict(vars(module)) if module is not None else {}
        try:
            first_line = inspect.getsourcelines(cls)[1]
            loc = SourceLoc(
                file=inspect.getsourcefile(cls) or "<unknown>",
                line=first_line,
                function=qname.to_id(),
            )
        except (OSError, TypeError):
            loc = SourceLoc(
                file=str(getattr(module, "__file__", "<unknown>")),
                line=0,
                function=qname.to_id(),
            )
        raw = RawRecord(
            kind=kind,
            qname=qname,
            bases=tuple(
                getattr(b, DslAttr.QNAME.value)
                for b in bases
                if DslAttr.QNAME.value in b.__dict__
            ),
            doc=inspect.cleandoc(ns.get("__doc__") or ""),
            loc=loc,
            module_globals=module_globals,
            checks=state.checks,
            variants=state.variants,
            backend=state.backend,
        )
        annotations = inspect.get_annotations(cls)
        enum_auto_counter = 0
        for fname, ann in annotations.items():
            if is_class_var(ann):
                continue
            value = ns.get(fname, NO_DEFAULT)
            if kind == RecordKind.ENUM:
                if isinstance(value, (int, enum.auto)):
                    if isinstance(value, int):
                        field_value = value
                    else:
                        field_value = enum_auto_counter
                        enum_auto_counter += 1

                    raw.enum_values.append(
                        EnumValueDef(
                            name=fname,
                            value=field_value,
                            doc=enum_value_doc(ann),
                            loc=loc,
                        )
                    )
                else:
                    raise TypeError(
                        f"Enum value {qname.to_id()}.{fname} at {loc.render()} must be assigned an integer or `enum.auto()`, got {value!r}"
                    )

                continue

            match value:
                case FieldSpec():
                    raw.fields.append(
                        RawField(
                            name=fname,
                            annotation=ann,
                            doc=value.doc,
                            default=value.default,
                            check=None if value.check is None else value.check.node,
                            message=None if value.message is None else value.message.node,
                            loc=value.loc,
                        )
                    )
                case _:
                    raw.fields.append(
                        RawField(
                            name=fname,
                            annotation=ann,
                            doc="",
                            default=value,
                            check=None,
                            message=None,
                            loc=loc,
                        )
                    )
        for mname, member in ns.items():
            method = mcls.method_of(mname, member, loc)
            match mname:
                case "__hash__" if isinstance(member, types.FunctionType):
                    raw.hash_func = member
                case "__eq__" if isinstance(member, types.FunctionType):
                    raw.eq_func = member
                case _ if method is not None:
                    raw.methods.append(method)
                case _:
                    pass
        model.register(raw)
        return cls

    @staticmethod
    def method_of(name: str, member: Any, loc: SourceLoc) -> Optional[RawMethod]:
        is_static = False
        if isinstance(member, staticmethod):
            is_static = True
            member = member.__func__
        match member:
            case MethodWrapper():
                func = member.func
                if isinstance(func, staticmethod):
                    is_static = True
                    func = func.__func__
                return RawMethod(
                    name=name,
                    func=func,
                    backend=member.backend,
                    is_static=is_static,
                    loc=member.loc,
                )
            case types.FunctionType() if name == "__init__" or not name.startswith("__"):
                return RawMethod(
                    name=name, func=member, backend={}, is_static=is_static, loc=loc
                )
            case _:
                return None


@beartype
@dataclass
class TypeDiagResult:
    diagnostics: List[Diagnostic]
    type_check: TypeCheckOutput


@beartype
class DslModel:
    """Declarations of one model package with type checking, validation, generation and reduction."""

    def __init__(
        self, package: str, operators: Optional[Sequence[Operator]] = None
    ) -> None:
        self.package = package
        self.table: Dict[OpId, Operator] = operator_table(
            list(operators) if operators is not None else default_operators()
        )
        self.raws: List[RawRecord] = []
        self.cached_model: Optional[ModelDef] = None
        self.cached_index: Optional[ModelIndex] = None
        self.Class = self.make_root("Class", RecordKind.CLASS)
        self.Case = self.make_root("Case", RecordKind.CASE)
        self.Enum = self.make_root("Enum", RecordKind.ENUM)
        self._T = ExternalTypeLookup(package)

    def make_root(self, name: str, kind: RecordKind) -> type:
        return DslMeta(
            name,
            (),
            {
                DslAttr.ROOT.value: True,
                DslAttr.MODEL.value: self,
                DslAttr.KIND.value: kind,
                "__module__": __name__,
                "__qualname__": f"{self.package}.{name}",
            },
        )

    def register(self, raw: RawRecord) -> None:
        self.raws.append(raw)
        self.cached_model = None
        self.cached_index = None

    @property
    def This(self) -> Expr:
        return this_expr()

    def Iter(self, name: str) -> Expr:
        """
        Access to the bound iteration variable in expression. Operations like `type_case`, `op_map` etc.
        have an argument to the specify the variable -- `Iter("<varname>")` is used to access the value.
        """
        return var_expr(name)

    @frontend_entry
    def Field(
        self,
        doc: str = "",
        default: Any = NO_DEFAULT,
        check: Optional[Expr] = None,
        message: Optional[Expr | str] = None,
        # Use `Any` to make type checkers work
    ) -> Any:

        match message:
            case None if check is not None:
                raise ValueError(
                    "Empty message with non-empty check, error message is mandatory"
                )

            case None:
                conv_message = None

            case str():
                conv_message = Expr(to_node(message))

            case Expr():
                conv_message = message

            case _:
                raise TypeError(f"Unexpected message type: {type(message)}")

        return FieldSpec(
            doc=doc,
            default=default,
            check=check,
            message=conv_message,
            loc=current_loc(),
        )

    @frontend_entry
    def Method(
        self, backend: Optional[Dict[str, Any]] = None
    ) -> Callable[[Any], MethodWrapper]:
        loc = current_loc()

        def wrap(func: Any) -> MethodWrapper:
            return MethodWrapper(func=func, backend=dict(backend or {}), loc=loc)

        return wrap

    def finalize(self) -> ModelDef:
        """
        Verify structural elements of the model and return untyped model
        definition. To get the typed definition use `type_check()` method.
        """
        if self.cached_model is None:
            self.cached_model = ModelFinalizer(
                self.package,
                self.raws,
                self.table,
            ).finalize()

            self.cached_index = ModelIndex(self.cached_model)
        return self.cached_model

    @property
    def index(self) -> ModelIndex:
        self.finalize()
        assert self.cached_index is not None
        return self.cached_index

    def type_check_diagnostics(self, capture_databases: bool = False) -> TypeDiagResult:
        output = run_type_check(
            self.index,
            self.table,
            capture_databases=capture_databases,
        )
        return TypeDiagResult(
            diagnostics=build_diagnostics(self.index, self.table, output),
            type_check=output,
        )

    def type_check(
        self,
        capture_databases: bool = False,
        raise_on_type_error: bool = True,
    ) -> TypeDiagResult:
        """Raises `DslTypeError` with one diagnostic per root cause when any check expression is ill-typed."""
        diagnostics = self.type_check_diagnostics(capture_databases=capture_databases)

        # Path("/tmp/debug.dl").write_text(render_program(diagnostics.type_check.program))

        if diagnostics.diagnostics and raise_on_type_error:
            raise DslTypeError(self.package, diagnostics.diagnostics)

        Path("/tmp/type_check.txt").write_text(
            render_rich(model_tree_repr(diagnostics.type_check.model))
        )

        return diagnostics

    def get_typed(self) -> ModelDef:
        """
        Run type check for the model and return a fully resolved type-checked model.
        This method is the main entry point to access the result of the model DSL
        definition.
        """
        return self.type_check().type_check.model

    def to_dict(self) -> Dict[str, Any]:
        return self.finalize().model_dump(mode="json")

    def type_of(self, target: Any) -> TypeRef:
        """
        Model type of a declaration class or of any annotation-like type expression.

        This function returns a static type of the expression or unwraps the stored
        static type from the `DynT` (e.g. from op_walk). It does not provide dynamic
        sub-typing support. So if the `type_case()` has a type pattern matching the
        base class, the binding will have `type_of()` for the base class, it will
        not evaluate to the actual runtime clas of the derived.
        """
        index = self.index
        lookup = NameLookup()
        for rec in index.model.records:
            lookup.add(rec.qname)

        for enum_def in index.model.enums:
            lookup.add(enum_def.qname)

        return AnnotationResolver(lookup, self.package).resolve(target)

    def decode(self, target: Any, data: Any) -> Value:
        return decode_json(self.index, self.type_of(target), data)

    def encode(self, target: Any, value: Value) -> Any:
        return encode_json(self.index, self.type_of(target), value)

    def validate(self, target: Any, value: Value) -> List[CheckFailure]:
        return validate(self.index, self.table, self.type_of(target), value)

    def generate(
        self,
        target: Any,
        config: GenConfig = GenConfig(),
        type_overrides: Optional[Dict[Any, GeneratorFunc]] = None,
        field_overrides: Optional[Dict[Tuple[Any, str], GeneratorFunc]] = None,
    ) -> Value:
        """Random value satisfying every error-level check, with user generators for external types and chosen fields."""
        overrides = GenOverrides()
        for key, func in (type_overrides or {}).items():
            overrides.types[self.type_of(key)] = func
        for (owner, fname), func in (field_overrides or {}).items():
            t = self.type_of(owner)
            if not isinstance(t, NamedT) or self.index.field(t.qname, fname) is None:
                known = (
                    ", ".join(f.name for f in self.index.effective_fields(t.qname))
                    if isinstance(t, NamedT)
                    else "(not a record)"
                )
                raise KeyError(
                    f"Field override ({owner!r}, {fname!r}) does not name a record field, fields of that record: {known}"
                )
            overrides.fields[(t.qname, fname)] = func
        return generate_value(
            self.index, self.table, self.type_of(target), config, overrides
        )

    def reduce(
        self,
        target: Any,
        value: Value,
        predicate: Predicate,
        config: ReduceConfig = ReduceConfig(),
    ) -> ReductionResult:
        """Smallest value found that is still valid for the model and still accepted by the predicate."""
        return reduce_value(
            self.index, self.table, self.type_of(target), value, predicate, config
        )


@beartype
def get_dsl_model(
    package: str = "", operators: Optional[Sequence[Operator]] = None
) -> DslModel:
    """New model for the package; types of other packages are referenced through `model._T[...]`."""
    return DslModel(package, operators)
