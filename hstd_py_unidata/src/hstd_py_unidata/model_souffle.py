from __future__ import annotations

import csv
import enum
import tempfile
from dataclasses import dataclass, field, replace
from pathlib import Path

from beartype import beartype
from beartype.typing import Dict, List, Optional, Set, Union
from plumbum import local

from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    FLOAT_PRIMS,
    INTEGER_RANGES,
    ArrayT,
    CheckContext,
    CheckDef,
    DynT,
    ExprNode,
    ExternalT,
    ListT,
    MapT,
    ModelDef,
    NamedT,
    OpId,
    OptT,
    PrimKind,
    PrimT,
    QName,
    RecordDef,
    TupleT,
    TypeParamT,
    TypeRef,
    UnresolvedT,
    VariantT,
    numeric_join,
)
from hstd_py_unidata.model_ops import (
    BOOL_T,
    STRING_T,
    TYPE_CLASS_CONSTRUCTORS,
    TYPE_CLASS_DESCRIPTIONS,
    Operator,
    TypeClass,
)

RULES_DIR = Path(__file__).parent

PRIM_CONSTRUCTORS: Dict[PrimKind, str] = {
    PrimKind.INT8: "PInt8",
    PrimKind.INT16: "PInt16",
    PrimKind.INT32: "PInt32",
    PrimKind.INT64: "PInt64",
    PrimKind.UINT8: "PUInt8",
    PrimKind.UINT16: "PUInt16",
    PrimKind.UINT32: "PUInt32",
    PrimKind.UINT64: "PUInt64",
    PrimKind.FLOAT32: "PFloat32",
    PrimKind.FLOAT64: "PFloat64",
    PrimKind.STRING: "PString",
    PrimKind.BOOL: "PBool",
    PrimKind.ANY: "PAny",
    PrimKind.NONE: "PNone",
    PrimKind.PATH: "PPath",
}


class CheckPart(enum.StrEnum):
    COND = "condition"
    MESSAGE = "message"


@beartype
@dataclass(frozen=True)
class CheckRoot:
    """Check expression root that a lowered expression occurrence belongs to."""

    record: QName
    check: CheckDef
    part: CheckPart


@beartype
@dataclass(frozen=True)
class Occurrence:
    """One occurrence of an expression node, reused Python expressions get distinct occurrences."""

    id: int
    node: ExprNode
    parent: Optional[int]
    arg_index: int
    root: CheckRoot
    binder_of: Optional[int]
    """For variable references, the occurrence that introduces the referenced binder."""


@beartype
@dataclass
class LoweredProgram:
    facts: List[str] = field(default_factory=list)
    occurrences: Dict[int, Occurrence] = field(default_factory=dict)


@beartype
@dataclass(frozen=True)
class DiagRow:
    """
    Structured diagnostic produced by the Souffle type checker.

    Created from the CSV generated in the `model_diag.dl` output
    """

    code: str
    expr: int
    arg: int
    detail: str
    actual: str
    subject: str


@beartype
@dataclass(frozen=True)
class TypeCheckOutput:
    model: ModelDef
    "Type-checked rewrite of the original model definition, fills every `typed_as` expression"
    program: LoweredProgram
    diags: List[DiagRow]
    untyped: Set[int]
    typed_as: Dict[int, str]


@beartype
class SouffleProtocolError(Exception):
    """Souffle produced output that does not follow the expected relation layout."""


@beartype
def sym(text: str) -> str:
    return '"' + text.replace("\\", "\\\\").replace('"', '\\"') + '"'


@beartype
def qname_term(q: QName) -> str:
    scope = "$NoScope()" if q.scope is None else f"$SomeScope({qname_term(q.scope)})"
    return f"$QNameValue({sym(q.name)}, {scope})"


@beartype
def type_term(t: TypeRef) -> str:
    match t:
        case PrimT():
            return f"$TPrim(${PRIM_CONSTRUCTORS[t.prim]}())"
        case ListT():
            return f"$TList({type_term(t.elem)})"
        case ArrayT():
            return f"$TArray({type_term(t.elem)}, {t.size})"
        case MapT():
            return f"$TMap({type_term(t.key)}, {type_term(t.value)})"
        case OptT():
            return f"$TOpt({type_term(t.elem)})"
        case TupleT():
            tail = "$TNil()"
            for e in reversed(t.elems):
                tail = f"$TCons({type_term(e)}, {tail})"
            return f"$TTuple({tail})"
        case NamedT():
            return f"$TNamed({qname_term(t.qname)})"
        case ExternalT():
            return f"$TExternal({sym(t.package)}, {qname_term(t.qname)})"
        case VariantT():
            return f"$TVariant({qname_term(t.owner)}, {sym(t.field)})"
        case DynT():
            return f"$TDyn({type_term(t.root)})"
        case TypeParamT():
            return f"$TParam({sym(t.name)})"
        case UnresolvedT():
            raise ValueError(
                f"Type '{t.text}' was not resolved before lowering to Souffle"
            )
        case _:
            raise TypeError(f"Unhandled type reference {t!r}")


@beartype
def class_term(cls: TypeClass) -> str:
    return f"${TYPE_CLASS_CONSTRUCTORS[cls]}()"


@beartype
def fact(relation: str, *args: Union[str, int]) -> str:
    rendered = [a if isinstance(a, str) else str(a) for a in args]
    return f"{relation}({', '.join(rendered)})."


@beartype
def collect_external_qnames(t: TypeRef, result: Set[QName]) -> None:
    match t:
        case ExternalT():
            result.add(t.qname)
        case ListT() | ArrayT() | OptT():
            collect_external_qnames(t.elem, result)
        case MapT():
            collect_external_qnames(t.key, result)
            collect_external_qnames(t.value, result)
        case TupleT():
            for e in t.elems:
                collect_external_qnames(e, result)
        case DynT():
            collect_external_qnames(t.root, result)
        case _:
            pass


@beartype
class Lowering:
    """Translates the finalized model and its check expressions into Souffle facts."""

    def __init__(self, index: ModelIndex, table: Dict[OpId, Operator]) -> None:
        self.index = index
        self.table = table
        self.program = LoweredProgram()
        self.next_expr = 0
        self.next_binder = 0
        self.binder_owner: Dict[int, int] = {}

    def emit(self, relation: str, *args: Union[str, int]) -> None:
        self.program.facts.append(fact(relation, *args))

    def lower(self) -> LoweredProgram:
        self.lower_builtin_facts()
        external: Set[QName] = set()
        for rec in self.index.model.records:
            self.lower_record(rec, external)

        for enum_def in self.index.model.enums:
            q = qname_term(enum_def.qname)
            self.emit("record", q, sym("enum"))
            self.emit("qname_text", q, sym(enum_def.qname.to_id()))
            for value in enum_def.enum_values:
                self.emit("enum_value", q, sym(value.name))

        for q in sorted(external, key=lambda q: q.to_id()):
            self.emit("qname_text", qname_term(q), sym(q.to_id()))
        for rec in self.index.model.records:
            for check in rec.checks:
                self.lower_check(rec, check)
        return self.program

    def lower_builtin_facts(self) -> None:
        for prim, ctor in PRIM_CONSTRUCTORS.items():
            self.emit("prim_text", f"${ctor}()", sym(prim.value))
            classes: List[TypeClass] = []
            if prim in INTEGER_RANGES:
                classes = [TypeClass.NUMERIC, TypeClass.INTEGER, TypeClass.ORDERED]
            elif prim in FLOAT_PRIMS:
                classes = [TypeClass.NUMERIC, TypeClass.FLOAT, TypeClass.ORDERED]
            elif prim == PrimKind.STRING:
                classes = [TypeClass.STRING, TypeClass.ORDERED]
            elif prim == PrimKind.BOOL:
                classes = [TypeClass.BOOL]
            for cls in classes:
                self.emit("prim_class", f"${ctor}()", class_term(cls))
        numeric = [
            p for p in PRIM_CONSTRUCTORS if p in INTEGER_RANGES or p in FLOAT_PRIMS
        ]
        for left in numeric:
            for right in numeric:
                result = numeric_join(left, right)
                self.emit(
                    "numeric_join",
                    f"${PRIM_CONSTRUCTORS[left]}()",
                    f"${PRIM_CONSTRUCTORS[right]}()",
                    f"${PRIM_CONSTRUCTORS[result]}()",
                )
        for cls in TypeClass:
            self.emit("class_text", class_term(cls), sym(TYPE_CLASS_DESCRIPTIONS[cls]))
        for op in self.table.values():
            if op.elem_binder:
                self.emit("op_binds_elem", sym(op.op_id.value))
            if op.binary_operands:
                self.emit("op_binary", sym(op.op_id.value))

    def lower_record(self, rec: RecordDef, external: Set[QName]) -> None:
        q = qname_term(rec.qname)
        self.emit("record", q, sym(rec.kind.value))
        self.emit("qname_text", q, sym(rec.qname.to_id()))
        for b in rec.bases:
            self.emit("inherits", q, qname_term(b))
        for f in rec.fields:
            self.emit("field", q, sym(f.name), type_term(f.type))
            collect_external_qnames(f.type, external)
        for v in rec.variants:
            self.emit("variant_kind", q, sym(v.field), qname_term(v.kind_enum))
            for c in v.cases:
                self.emit("variant_case", q, sym(v.field), sym(c.tag), qname_term(c.case))

    def lower_check(self, rec: RecordDef, check: CheckDef) -> None:
        match check.context:
            case CheckContext.RECORD:
                this_t: TypeRef = NamedT(qname=rec.qname)
            case CheckContext.FIELD:
                assert check.field is not None
                fdef = self.index.field(rec.qname, check.field)
                assert fdef is not None
                this_t = fdef.type
        for part, node, expected in (
            (CheckPart.COND, check.cond, BOOL_T),
            (CheckPart.MESSAGE, check.message, STRING_T),
        ):
            root = CheckRoot(record=rec.qname, check=check, part=part)
            eid = self.lower_expr(node, None, 0, root, this_t, {})
            self.emit("root", eid, type_term(expected))

    def lower_expr(
        self,
        node: ExprNode,
        parent: Optional[int],
        arg_index: int,
        root: CheckRoot,
        this_t: TypeRef,
        scope: Dict[str, int],
    ) -> int:
        """
        Recursively iterate over all sub-expressions creating the facts about the whole model.
        """
        # `DiagRow.expr` field is created here
        eid = self.next_expr
        self.next_expr += 1
        op = self.table[node.op]
        binder_of: Optional[int] = None
        self.emit("expr", eid, sym(node.op.value))
        self.emit("expr_arity", eid, len(node.args))
        if node.str_val is not None:
            self.emit("expr_str", eid, sym(node.str_val))
        if node.int_val is not None:
            self.emit("expr_int", eid, node.int_val)
        if node.type_val is not None:
            self.emit("expr_type_val", eid, type_term(node.type_val))
        if node.op == OpId.TYPE_COND and node.bool_val:
            self.emit("expr_flag", eid, sym("unhandled_ignore"))
        if node.op == OpId.THIS:
            self.emit("this_type", eid, type_term(this_t))
        if node.op == OpId.VAR:
            assert node.str_val is not None
            binder = scope[node.str_val]
            binder_of = self.binder_owner[binder]
            self.emit("var_ref", eid, binder)
        inner = dict(scope)
        for slot, name in enumerate(node.binders):
            binder = self.next_binder
            self.next_binder += 1
            self.binder_owner[binder] = eid
            inner[name] = binder
            self.emit("binds", eid, slot, binder)
        for idx, cls in op.arg_class_facts(node):
            self.emit("expr_arg_class", eid, idx, class_term(cls))
        if op.fixed_result is not None:
            self.emit("expr_fixed_result", eid, type_term(op.fixed_result))
        self.program.occurrences[eid] = Occurrence(
            id=eid,
            node=node,
            parent=parent,
            arg_index=arg_index,
            root=root,
            binder_of=binder_of,
        )
        for idx, arg in enumerate(node.args):
            arg_id = self.lower_expr(
                arg, eid, idx, root, this_t, inner if idx in op.scoped_args else scope
            )
            self.emit("expr_arg", eid, idx, arg_id)
        return eid


@beartype
def read_rows(path: Path, width: int) -> List[List[str]]:
    if not path.exists():
        raise SouffleProtocolError(
            f"Souffle did not produce the output relation file {path}"
        )
    rows: List[List[str]] = []
    with path.open("r", newline="") as fobj:
        for lineno, row in enumerate(
            csv.reader(fobj, delimiter="\t", quoting=csv.QUOTE_NONE), start=1
        ):
            if len(row) != width:
                raise SouffleProtocolError(
                    f"{path.name}:{lineno}: expected {width} tab-separated columns, got {len(row)}: {row!r}"
                )
            rows.append(row)
    return rows


@beartype
def render_program(program: LoweredProgram) -> str:
    """Complete Souffle program: the shared rules followed by the model-specific facts."""
    return '#include "logic_model/model_dsl.dl"\n' + "\n".join(program.facts) + "\n"


@beartype
def read_inferred_types(
    directory: Path,
    index: ModelIndex,
    program: LoweredProgram,
) -> Dict[int, TypeRef]:
    """Reconstruct inferred types from structural Souffle relations."""
    qnames = dict(index.by_id)
    external: Set[QName] = set()

    for record in index.model.records:
        for field_def in record.fields:
            collect_external_qnames(field_def.type, external)

    for occurrence in program.occurrences.values():
        if occurrence.node.type_val is not None:
            collect_external_qnames(occurrence.node.type_val, external)

    for qname in external:
        qnames[qname.to_id()] = qname

    shapes = {
        row[0]: row[1:] for row in read_rows(directory / "inferred_type_shape.csv", 5)
    }
    edges: Dict[str, Dict[int, str]] = {}
    for key, slot, nested in read_rows(directory / "inferred_type_edge.csv", 3):
        edges.setdefault(key, {})[int(slot)] = nested

    cache: Dict[str, TypeRef] = {}

    def resolve_qname(text: str) -> QName:
        if text not in qnames:
            raise SouffleProtocolError(
                f"Cannot reconstruct inferred type QName {text!r}: "
                "it is neither a model declaration nor a referenced external type"
            )
        return qnames[text]

    def build(key: str) -> TypeRef:
        if key in cache:
            return cache[key]
        if key not in shapes:
            raise SouffleProtocolError(
                f"Cannot reconstruct inferred type {key!r}: "
                "Souffle did not export its structural description"
            )

        kind, name, detail, size = shapes[key]
        slots = edges.get(key, {})

        def argument(slot: int) -> TypeRef:
            if slot not in slots:
                raise SouffleProtocolError(
                    f"Cannot reconstruct inferred type {key!r} ({kind}): "
                    f"Souffle did not export required type argument {slot}"
                )
            return build(slots[slot])

        result: TypeRef
        match kind:
            case "prim":
                result = PrimT(prim=PrimKind(name))
            case "list":
                result = ListT(elem=argument(0))
            case "array":
                result = ArrayT(elem=argument(0), size=int(size))
            case "map":
                result = MapT(key=argument(0), value=argument(1))
            case "optional":
                result = OptT(elem=argument(0))
            case "tuple":
                expected = list(range(len(slots)))
                actual = sorted(slots)
                if actual != expected:
                    raise SouffleProtocolError(
                        f"Cannot reconstruct tuple type {key!r}: "
                        f"expected argument slots {expected}, got {actual}"
                    )
                result = TupleT(elems=tuple(argument(slot) for slot in expected))
            case "named":
                result = NamedT(qname=resolve_qname(name))
            case "external":
                result = ExternalT(
                    package=detail,
                    qname=resolve_qname(name),
                )
            case "variant":
                result = VariantT(
                    owner=resolve_qname(name),
                    field=detail,
                )
            case "dyn":
                result = DynT(root=argument(0))
            case "param":
                result = TypeParamT(name=name)
            case _:
                raise SouffleProtocolError(
                    f"Cannot reconstruct inferred type {key!r}: "
                    f"unsupported structural kind {kind!r}"
                )

        cache[key] = result
        return result

    result: Dict[int, TypeRef] = {}
    for expression, key in read_rows(directory / "inferred_type.csv", 2):
        eid = int(expression)
        if eid not in program.occurrences:
            raise SouffleProtocolError(
                f"Inferred type {key!r} refers to expression {eid}, "
                "which was never lowered"
            )
        if eid in result:
            raise SouffleProtocolError(
                f"Expression {eid} has multiple inferred types: "
                f"{result[eid]!r} and {build(key)!r}; "
                "ExprNode.typed_as requires a single type"
            )
        result[eid] = build(key)

    return result


def _run_for_diagnostics(
    tmp: Path,
    source: Path,
    index: ModelIndex,
    program: LoweredProgram,
):
    local["souffle"]["-w", "-I", str(RULES_DIR), "-D", str(tmp), str(source)]()

    diags = [
        DiagRow(
            code=r[0],
            expr=int(r[1]),
            arg=int(r[2]),
            detail=r[3],
            actual=r[4],
            subject=r[5],
        )
        for r in read_rows(tmp / "diag.csv", 6)
    ]
    untyped = {int(r[0]) for r in read_rows(tmp / "untyped.csv", 1)}
    typed_as = {int(r[0]): r[1] for r in read_rows(tmp / "typed_as.csv", 2)}
    inferred_types = read_inferred_types(tmp, index, program)

    return diags, untyped, typed_as, inferred_types


@beartype
def run_type_check(index: ModelIndex, table: Dict[OpId, Operator]) -> TypeCheckOutput:
    """Lowers the model to Souffle facts, runs the type checker and parses the structured results."""
    program = Lowering(index, table).lower()
    with tempfile.TemporaryDirectory() as tmpdir:
        tmp = Path(tmpdir)
        source = tmp / "program.dl"
        source.write_text(render_program(program))

        diags, untyped, typed_as, inferred_types = _run_for_diagnostics(
            tmp, source, index, program
        )

    for d in diags:
        if d.expr not in program.occurrences:
            raise SouffleProtocolError(
                f"Diagnostic {d} refers to expression {d.expr} that was never lowered"
            )

    arguments: Dict[int, Dict[int, int]] = {}
    roots: Dict[QName, Dict[str, Dict[CheckPart, int]]] = {}

    for eid, occurrence in program.occurrences.items():
        if occurrence.parent is None:
            roots.setdefault(occurrence.root.record, {}).setdefault(
                occurrence.root.check.id, {}
            )[occurrence.root.part] = eid
        else:
            arguments.setdefault(occurrence.parent, {})[occurrence.arg_index] = eid

    nodes: Dict[int, ExprNode] = {}

    for eid in sorted(program.occurrences, reverse=True):
        occurrence = program.occurrences[eid]
        slots = arguments.get(eid, {})
        nodes[eid] = occurrence.node.model_copy(
            update={
                "args": tuple(
                    nodes[slots[slot]] for slot in range(len(occurrence.node.args))
                ),
                "typed_as": inferred_types.get(eid),
                "expr_id": eid,
            }
        )

    checks: Dict[QName, Dict[str, CheckDef]] = {}
    records: List[RecordDef] = []

    for record in index.model.records:
        record_checks: List[CheckDef] = []
        for check in record.checks:
            parts = roots[record.qname][check.id]
            updated = check.model_copy(
                update={
                    "cond": nodes[parts[CheckPart.COND]],
                    "message": nodes[parts[CheckPart.MESSAGE]],
                }
            )
            checks.setdefault(record.qname, {})[check.id] = updated
            record_checks.append(updated)

        records.append(record.model_copy(update={"checks": tuple(record_checks)}))

    model = index.model.model_copy(update={"records": tuple(records)})
    occurrences: Dict[int, Occurrence] = {}

    for eid, occurrence in program.occurrences.items():
        root = occurrence.root
        occurrences[eid] = replace(
            occurrence,
            node=nodes[eid],
            root=replace(
                root,
                check=checks[root.record][root.check.id],
            ),
        )

    return TypeCheckOutput(
        model=model,
        program=LoweredProgram(
            facts=list(program.facts),
            occurrences=occurrences,
        ),
        diags=diags,
        untyped=untyped,
        typed_as=typed_as,
    )
