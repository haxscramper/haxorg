from __future__ import annotations

import enum
import sqlite3
import tempfile
from contextlib import closing
from dataclasses import dataclass, field, replace
from os import getenv
from pathlib import Path

from beartype import beartype
from beartype.typing import Dict, List, Optional, Set, Tuple
from hstd_py_lib.external_packages.rich_utils import render_rich
from hstd_py_lib.external_packages.sqlalchemy_utils import format_db_all
from loguru import logger
from plumbum import local

from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    FLOAT_PRIMS,
    INTEGER_RANGES,
    ArrayT,
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
    expr_tree_repr,
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
from hstd_py_unidata.souffle_path import get_serde_library_path

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

INPUT_COLUMNS: Dict[str, Tuple[str, ...]] = {
    "input_qname": (
        "id TEXT",
        "name TEXT",
        "scope TEXT",
        "scoped INTEGER",
    ),
    "input_type_shape": (
        "id INTEGER",
        "kind TEXT",
        "name TEXT",
        "detail TEXT",
        "size INTEGER",
    ),
    "input_type_edge": (
        "owner INTEGER",
        "slot INTEGER",
        "nested INTEGER",
    ),
    "input_record": ("qname TEXT", "kind TEXT"),
    "input_inherits": ("sub TEXT", "sup TEXT"),
    "input_field": ("qname TEXT", "name TEXT", "t INTEGER"),
    "input_variant_case": (
        "owner TEXT",
        "vfield TEXT",
        "tag TEXT",
        "case_qname TEXT",
    ),
    "input_variant_kind": (
        "owner TEXT",
        "vfield TEXT",
        "kind_enum TEXT",
    ),
    "input_enum_value": ("qname TEXT", "name TEXT"),
    "input_qname_text": ("qname TEXT", "text TEXT"),
    "input_prim_text": ("prim TEXT", "text TEXT"),
    "input_prim_class": ("prim TEXT", "cls TEXT"),
    "input_class_text": ("cls TEXT", "text TEXT"),
    "input_numeric_join": (
        "left TEXT",
        "right TEXT",
        "result TEXT",
    ),
    "input_op_binds_elem": ("op TEXT",),
    "input_op_binary": ("op TEXT",),
    "input_expr": ("e INTEGER", "op TEXT"),
    "input_expr_arity": ("e INTEGER", "arity INTEGER"),
    "input_expr_arg": ("e INTEGER", "idx INTEGER", "arg INTEGER"),
    "input_expr_str": ("e INTEGER", "value TEXT"),
    "input_expr_int": ("e INTEGER", "value INTEGER"),
    "input_expr_type_val": ("e INTEGER", "t INTEGER"),
    "input_expr_flag": ("e INTEGER", "flag TEXT"),
    "input_binds": ("e INTEGER", "slot INTEGER", "binder INTEGER"),
    "input_var_ref": ("e INTEGER", "binder INTEGER"),
    "input_this_type": ("e INTEGER", "t INTEGER"),
    "input_root": ("e INTEGER", "expected INTEGER"),
    "input_expr_arg_class": ("e INTEGER", "idx INTEGER", "cls TEXT"),
    "input_expr_fixed_result": ("e INTEGER", "t INTEGER"),
}

OUTPUT_WIDTHS: Dict[str, int] = {
    "diag": 6,
    "untyped": 1,
    "typed_as": 2,
    "sq_inferred_type": 2,
    "sq_inferred_binder_type": 3,
    "sq_inferred_type_shape": 5,
    "sq_inferred_type_edge": 3,
}


class CheckPart(enum.StrEnum):
    COND = "condition"
    MESSAGE = "message"


@beartype
@dataclass(frozen=True)
class CheckRoot:
    """Check expression root that a lowered occurrence belongs to."""

    record: QName
    check: CheckDef
    part: CheckPart


@beartype
@dataclass(frozen=True)
class Occurrence:
    """One expression occurrence; reused Python nodes receive distinct IDs."""

    id: int
    node: ExprNode
    parent: Optional[int]
    arg_index: int
    root: CheckRoot
    binder_of: Optional[int]
    """Occurrence introducing the binder referenced by this variable."""


@beartype
@dataclass
class LoweredProgram:
    database: bytes = b""
    """Serialized SQLite database containing the normalized input relations."""

    occurrences: Dict[int, Occurrence] = field(default_factory=dict)


@beartype
@dataclass(frozen=True)
class DiagRow:
    """Structured diagnostic produced by the Soufflé type checker."""

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
    """Model rewritten with inferred expression and binder types."""

    program: LoweredProgram
    diags: List[DiagRow]
    untyped: Set[int]
    typed_as: Dict[int, str]


@beartype
@dataclass(frozen=True)
class DiagnosticsResult:
    diags: List[DiagRow]
    """Structured diagnostics returned by Soufflé."""

    untyped: Set[int]
    """Expression occurrences without an inferred type."""

    typed_as: Dict[int, str]
    """Human-readable inferred expression types."""

    inferred_types: Dict[int, TypeRef]
    """Reconstructed expression types."""

    binder_types: Dict[int, Tuple[TypeRef, ...]]
    """Reconstructed binder types, ordered by binder slot."""


@beartype
class SouffleProtocolError(Exception):
    """Soufflé output does not follow the expected relation layout."""


@beartype
def sym(text: str) -> str:
    return '"' + text.replace("\\", "\\\\").replace('"', '\\"') + '"'


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
            for elem in t.elems:
                collect_external_qnames(elem, result)
        case DynT():
            collect_external_qnames(t.root, result)
        case _:
            pass


@beartype
class Lowering:
    """Stores the finalized model and its expressions in SQLite relations."""

    def __init__(self, index: ModelIndex, table: Dict[OpId, Operator]) -> None:
        self.index = index
        self.table = table
        self.program = LoweredProgram()
        self.database: sqlite3.Connection
        self.next_expr = 0
        self.next_binder = 0
        self.next_type = 0
        self.binder_owner: Dict[int, int] = {}
        self.qnames: Set[QName] = set()
        self.types: Dict[TypeRef, int] = {}

    def qname_id(self, qname: QName) -> str:
        identity = qname.to_id()
        if qname in self.qnames:
            return identity

        scope = ""
        scoped = 0
        if qname.scope is not None:
            scope = self.qname_id(qname.scope)
            scoped = 1

        self.database.execute(
            "INSERT INTO input_qname VALUES (?, ?, ?, ?)",
            (identity, qname.name, scope, scoped),
        )
        self.database.execute(
            "INSERT INTO input_qname_text VALUES (?, ?)",
            (identity, identity),
        )
        self.qnames.add(qname)
        return identity

    def type_id(self, value: TypeRef) -> int:
        if value in self.types:
            return self.types[value]

        identity = self.next_type
        self.next_type += 1

        name = ""
        detail = ""
        size = 0
        nested: Tuple[TypeRef, ...] = ()

        match value:
            case PrimT():
                kind = "prim"
                name = PRIM_CONSTRUCTORS[value.prim]
            case ListT():
                kind = "list"
                nested = (value.elem,)
            case ArrayT():
                kind = "array"
                size = value.size
                nested = (value.elem,)
            case MapT():
                kind = "map"
                nested = (value.key, value.value)
            case OptT():
                kind = "optional"
                nested = (value.elem,)
            case TupleT():
                kind = "tuple"
                size = len(value.elems)
                nested = tuple(value.elems)
            case NamedT():
                kind = "named"
                name = self.qname_id(value.qname)
            case ExternalT():
                kind = "external"
                name = self.qname_id(value.qname)
                detail = value.package
            case VariantT():
                kind = "variant"
                name = self.qname_id(value.owner)
                detail = value.field
            case DynT():
                kind = "dyn"
                nested = (value.root,)
            case TypeParamT():
                kind = "param"
                name = value.name
            case UnresolvedT():
                raise ValueError(
                    f"Type {value.text!r} was not resolved before lowering to SQLite"
                )
            case _:
                raise TypeError(
                    f"Cannot lower type {value!r}: unsupported type reference"
                )

        self.database.execute(
            "INSERT INTO input_type_shape VALUES (?, ?, ?, ?, ?)",
            (identity, kind, name, detail, size),
        )
        for slot, argument in enumerate(nested):
            argument_id = self.type_id(argument)
            self.database.execute(
                "INSERT INTO input_type_edge VALUES (?, ?, ?)",
                (identity, slot, argument_id),
            )

        self.types[value] = identity
        return identity

    def lower(self) -> LoweredProgram:
        with closing(sqlite3.connect(":memory:")) as database:
            self.database = database

            for relation, columns in INPUT_COLUMNS.items():
                database.execute(f'CREATE TABLE "{relation}" ({", ".join(columns)})')

            self.lower_builtin_facts()

            for record in self.index.model.records:
                self.lower_record(record)

            for enum_def in self.index.model.enums:
                qname = self.qname_id(enum_def.qname)
                database.execute(
                    "INSERT INTO input_record VALUES (?, ?)",
                    (qname, "enum"),
                )
                database.executemany(
                    "INSERT INTO input_enum_value VALUES (?, ?)",
                    [(qname, value.name) for value in enum_def.enum_values],
                )

            for record in self.index.model.records:
                for check in record.checks:
                    self.lower_check(
                        record,
                        check,
                        NamedT(qname=record.qname),
                    )

                for field_def in record.fields:
                    for check in field_def.checks:
                        self.lower_check(record, check, field_def.type)

            database.commit()
            self.program.database = database.serialize()

        return self.program

    def lower_builtin_facts(self) -> None:
        for prim, constructor in PRIM_CONSTRUCTORS.items():
            self.database.execute(
                "INSERT INTO input_prim_text VALUES (?, ?)",
                (constructor, prim.value),
            )

            classes: List[TypeClass] = []
            if prim in INTEGER_RANGES:
                classes = [
                    TypeClass.NUMERIC,
                    TypeClass.INTEGER,
                    TypeClass.ORDERED,
                ]
            elif prim in FLOAT_PRIMS:
                classes = [
                    TypeClass.NUMERIC,
                    TypeClass.FLOAT,
                    TypeClass.ORDERED,
                ]
            elif prim == PrimKind.STRING:
                classes = [TypeClass.STRING, TypeClass.ORDERED]
            elif prim == PrimKind.BOOL:
                classes = [TypeClass.BOOL]

            self.database.executemany(
                "INSERT INTO input_prim_class VALUES (?, ?)",
                [(constructor, TYPE_CLASS_CONSTRUCTORS[cls]) for cls in classes],
            )

        numeric = [
            prim
            for prim in PRIM_CONSTRUCTORS
            if prim in INTEGER_RANGES or prim in FLOAT_PRIMS
        ]
        self.database.executemany(
            "INSERT INTO input_numeric_join VALUES (?, ?, ?)",
            [
                (
                    PRIM_CONSTRUCTORS[left],
                    PRIM_CONSTRUCTORS[right],
                    PRIM_CONSTRUCTORS[numeric_join(left, right)],
                )
                for left in numeric
                for right in numeric
            ],
        )
        self.database.executemany(
            "INSERT INTO input_class_text VALUES (?, ?)",
            [
                (
                    TYPE_CLASS_CONSTRUCTORS[cls],
                    TYPE_CLASS_DESCRIPTIONS[cls],
                )
                for cls in TypeClass
            ],
        )
        self.database.executemany(
            "INSERT INTO input_op_binds_elem VALUES (?)",
            [
                (operator.op_id.value,)
                for operator in self.table.values()
                if operator.elem_binder
            ],
        )
        self.database.executemany(
            "INSERT INTO input_op_binary VALUES (?)",
            [
                (operator.op_id.value,)
                for operator in self.table.values()
                if operator.binary_operands
            ],
        )

    def lower_record(self, record: RecordDef) -> None:
        qname = self.qname_id(record.qname)
        self.database.execute(
            "INSERT INTO input_record VALUES (?, ?)",
            (qname, record.kind.value),
        )

        for base in record.bases:
            self.database.execute(
                "INSERT INTO input_inherits VALUES (?, ?)",
                (qname, self.qname_id(base)),
            )

        for field_def in record.fields:
            self.database.execute(
                "INSERT INTO input_field VALUES (?, ?, ?)",
                (qname, field_def.name, self.type_id(field_def.type)),
            )

        for variant in record.variants:
            self.database.execute(
                "INSERT INTO input_variant_kind VALUES (?, ?, ?)",
                (
                    qname,
                    variant.field,
                    self.qname_id(variant.kind_enum),
                ),
            )
            for case in variant.cases:
                self.database.execute(
                    "INSERT INTO input_variant_case VALUES (?, ?, ?, ?)",
                    (
                        qname,
                        variant.field,
                        case.tag,
                        self.qname_id(case.case),
                    ),
                )

    def lower_check(
        self,
        record: RecordDef,
        check: CheckDef,
        this_type: TypeRef,
    ) -> None:
        for part, node, expected in (
            (CheckPart.COND, check.cond, BOOL_T),
            (CheckPart.MESSAGE, check.message, STRING_T),
        ):
            root = CheckRoot(record=record.qname, check=check, part=part)
            identity = self.lower_expr(
                node,
                None,
                0,
                root,
                this_type,
                {},
            )
            self.database.execute(
                "INSERT INTO input_root VALUES (?, ?)",
                (identity, self.type_id(expected)),
            )

    def lower_expr(
        self,
        node: ExprNode,
        parent: Optional[int],
        arg_index: int,
        root: CheckRoot,
        this_type: TypeRef,
        scope: Dict[str, int],
    ) -> int:
        identity = self.next_expr
        self.next_expr += 1

        operator = self.table[node.op]
        binder_of: Optional[int] = None

        self.database.execute(
            "INSERT INTO input_expr VALUES (?, ?)",
            (identity, node.op.value),
        )
        self.database.execute(
            "INSERT INTO input_expr_arity VALUES (?, ?)",
            (identity, len(node.args)),
        )

        if node.str_val is not None:
            self.database.execute(
                "INSERT INTO input_expr_str VALUES (?, ?)",
                (identity, node.str_val),
            )
        if node.int_val is not None:
            self.database.execute(
                "INSERT INTO input_expr_int VALUES (?, ?)",
                (identity, node.int_val),
            )
        if node.type_val is not None:
            self.database.execute(
                "INSERT INTO input_expr_type_val VALUES (?, ?)",
                (identity, self.type_id(node.type_val)),
            )
        if node.op == OpId.TYPE_COND and node.bool_val:
            self.database.execute(
                "INSERT INTO input_expr_flag VALUES (?, ?)",
                (identity, "unhandled_ignore"),
            )
        if node.op == OpId.THIS:
            self.database.execute(
                "INSERT INTO input_this_type VALUES (?, ?)",
                (identity, self.type_id(this_type)),
            )
        if node.op == OpId.VAR:
            assert node.str_val is not None
            binder = scope[node.str_val]
            binder_of = self.binder_owner[binder]
            self.database.execute(
                "INSERT INTO input_var_ref VALUES (?, ?)",
                (identity, binder),
            )

        inner = dict(scope)
        for slot, name in enumerate(node.binders):
            binder = self.next_binder
            self.next_binder += 1
            self.binder_owner[binder] = identity
            inner[name] = binder
            self.database.execute(
                "INSERT INTO input_binds VALUES (?, ?, ?)",
                (identity, slot, binder),
            )

        self.database.executemany(
            "INSERT INTO input_expr_arg_class VALUES (?, ?, ?)",
            [
                (identity, index, TYPE_CLASS_CONSTRUCTORS[cls])
                for index, cls in operator.arg_class_facts(node)
            ],
        )
        if operator.fixed_result is not None:
            self.database.execute(
                "INSERT INTO input_expr_fixed_result VALUES (?, ?)",
                (identity, self.type_id(operator.fixed_result)),
            )

        self.program.occurrences[identity] = Occurrence(
            id=identity,
            node=node,
            parent=parent,
            arg_index=arg_index,
            root=root,
            binder_of=binder_of,
        )

        for index, argument in enumerate(node.args):
            argument_id = self.lower_expr(
                argument,
                identity,
                index,
                root,
                this_type,
                inner if index in operator.scoped_args else scope,
            )
            self.database.execute(
                "INSERT INTO input_expr_arg VALUES (?, ?, ?)",
                (identity, index, argument_id),
            )

        return identity


@beartype
def read_rows(
    database: sqlite3.Connection,
    relation: str,
) -> List[List[str]]:
    if relation not in OUTPUT_WIDTHS:
        raise SouffleProtocolError(
            f"Cannot read output relation {relation!r}: "
            f"expected one of {sorted(OUTPUT_WIDTHS)}"
        )

    exists = database.execute(
        "SELECT 1 FROM sqlite_master WHERE name = ? AND type IN ('table', 'view')",
        (relation,),
    ).fetchone()
    if exists is None:
        raise SouffleProtocolError(
            f"Soufflé did not produce SQLite output relation {relation!r}"
        )

    cursor = database.execute(f'SELECT * FROM "{relation}"')
    width = OUTPUT_WIDTHS[relation]
    actual_width = len(cursor.description)

    if actual_width != width:
        raise SouffleProtocolError(
            f"SQLite relation {relation!r}: expected {width} columns, got {actual_width}"
        )

    rows: List[List[str]] = []
    for index, row in enumerate(cursor, start=1):
        if any(value is None for value in row):
            raise SouffleProtocolError(
                f"SQLite relation {relation!r}, row {index}: "
                f"unexpected NULL value in {row!r}"
            )
        rows.append([str(value) for value in row])

    return rows


@beartype
def render_program(input_database: Path, output_database: Path) -> str:
    statements = ['#include "logic_model/model_sqlite.dl"']

    for relation in INPUT_COLUMNS:
        statements.append(
            f".input {relation}(IO=sqlite, dbname={sym(str(input_database))})"
        )

    for relation in OUTPUT_WIDTHS:
        statements.append(
            f".output {relation}(IO=sqlite, dbname={sym(str(output_database))})"
        )

    return "\n".join(statements) + "\n"


@beartype
def read_inferred_types(
    database: sqlite3.Connection,
    index: ModelIndex,
    program: LoweredProgram,
) -> Tuple[Dict[int, TypeRef], Dict[int, Tuple[TypeRef, ...]]]:
    """Reconstruct expression and binder types from normalized SQLite outputs."""
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

    shapes = {row[0]: row[1:] for row in read_rows(database, "sq_inferred_type_shape")}

    edges: Dict[str, Dict[int, str]] = {}
    for key, slot, nested in read_rows(
        database,
        "sq_inferred_type_edge",
    ):
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
                f"Cannot reconstruct inferred type ID {key!r}: "
                "Soufflé did not export its structural description"
            )

        kind, name, detail, size = shapes[key]
        slots = edges.get(key, {})

        def argument(slot: int) -> TypeRef:
            if slot not in slots:
                raise SouffleProtocolError(
                    f"Cannot reconstruct inferred type ID {key!r} ({kind}): "
                    f"Soufflé did not export required type argument {slot}"
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
                        f"Cannot reconstruct tuple type ID {key!r}: "
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
                    f"Cannot reconstruct inferred type ID {key!r}: "
                    f"unsupported structural kind {kind!r}"
                )

        cache[key] = result
        return result

    result: Dict[int, TypeRef] = {}
    for expression, key in read_rows(database, "sq_inferred_type"):
        identity = int(expression)
        if identity not in program.occurrences:
            raise SouffleProtocolError(
                f"Inferred type ID {key!r} refers to expression {identity}, "
                "which was never lowered"
            )
        if identity in result:
            raise SouffleProtocolError(
                f"Expression {identity} has multiple inferred types: "
                f"{result[identity]!r} and {build(key)!r}; "
                "ExprNode.typed_as requires a single type"
            )
        result[identity] = build(key)

    binder_slots: Dict[int, Dict[int, TypeRef]] = {}
    for expression, slot_text, key in read_rows(
        database,
        "sq_inferred_binder_type",
    ):
        identity = int(expression)
        slot = int(slot_text)

        if identity not in program.occurrences:
            raise SouffleProtocolError(
                f"Inferred binder type ID {key!r} refers to expression "
                f"{identity}, which was never lowered"
            )

        node = program.occurrences[identity].node
        if not 0 <= slot < len(node.binders):
            raise SouffleProtocolError(
                f"Inferred binder type ID {key!r} refers to slot {slot} "
                f"of expression {identity}, which has {len(node.binders)} binders"
            )

        slots = binder_slots.setdefault(identity, {})
        if slot in slots:
            raise SouffleProtocolError(
                f"Binder slot {slot} of expression {identity} has multiple "
                f"inferred types: {slots[slot]!r} and {build(key)!r}; "
                "ExprNode.binder_types requires a single type per binder"
            )

        slots[slot] = build(key)

    binder_types: Dict[int, Tuple[TypeRef, ...]] = {}
    for identity, occurrence in program.occurrences.items():
        slots = binder_slots.get(identity, {})
        count = len(occurrence.node.binders)
        binder_types[identity] = (
            tuple(slots[slot] for slot in range(count)) if len(slots) == count else ()
        )

    return result, binder_types


@beartype
def run_for_diagnostics(
    source: Path,
    output_database: Path,
    index: ModelIndex,
    program: LoweredProgram,
) -> DiagnosticsResult:
    local["souffle"][
        "-w",
        "-I",
        str(RULES_DIR),
        str(source),
    ]()

    with closing(
        sqlite3.connect(
            output_database.as_uri() + "?mode=ro",
            uri=True,
        )
    ) as database:
        diags = [
            DiagRow(
                code=row[0],
                expr=int(row[1]),
                arg=int(row[2]),
                detail=row[3],
                actual=row[4],
                subject=row[5],
            )
            for row in read_rows(database, "diag")
        ]
        untyped = {int(row[0]) for row in read_rows(database, "untyped")}
        typed_as = {int(row[0]): row[1] for row in read_rows(database, "typed_as")}
        inferred_types, binder_types = read_inferred_types(
            database,
            index,
            program,
        )

    return DiagnosticsResult(
        diags=diags,
        untyped=untyped,
        typed_as=typed_as,
        inferred_types=inferred_types,
        binder_types=binder_types,
    )


@beartype
def run_type_check(
    index: ModelIndex,
    table: Dict[OpId, Operator],
) -> TypeCheckOutput:
    """Run the SQLite-backed type checker and rewrite expression annotations."""
    program = Lowering(index, table).lower()

    path = get_serde_library_path()
    assert path.exists(), str(path)

    with tempfile.TemporaryDirectory() as temporary:
        directory = Path(temporary)
        input_database = directory / "input.sqlite"
        output_database = directory / "output.sqlite"
        source = directory / "program.dl"

        input_database.write_bytes(program.database)
        source.write_text(
            render_program(input_database, output_database),
            encoding="utf-8",
        )
        diagnostics = run_for_diagnostics(
            source,
            output_database,
            index,
            program,
        )

        osd = getenv("HSTD_STABLE_TEST_DIR_PATH", None)
        if osd:
            debug_directory = Path(osd)
            debug_directory.mkdir(parents=True, exist_ok=True)
            debug_directory.joinpath("input.txt").write_text(
                format_db_all(input_database),
                encoding="utf-8",
            )
            debug_directory.joinpath("output.txt").write_text(
                format_db_all(output_database),
                encoding="utf-8",
            )

        else:
            assert False

    for diagnostic in diagnostics.diags:
        if diagnostic.expr not in program.occurrences:
            raise SouffleProtocolError(
                f"Diagnostic {diagnostic!r} refers to expression "
                f"{diagnostic.expr}, which was never lowered"
            )

    arguments: Dict[int, Dict[int, int]] = {}
    roots: Dict[QName, Dict[str, Dict[CheckPart, int]]] = {}

    for identity, occurrence in program.occurrences.items():
        if occurrence.parent is None:
            roots.setdefault(occurrence.root.record, {}).setdefault(
                occurrence.root.check.id,
                {},
            )[occurrence.root.part] = identity
        else:
            arguments.setdefault(
                occurrence.parent,
                {},
            )[occurrence.arg_index] = identity

    nodes: Dict[int, ExprNode] = {}
    for identity in sorted(program.occurrences, reverse=True):
        occurrence = program.occurrences[identity]
        slots = arguments.get(identity, {})
        nodes[identity] = occurrence.node.model_copy(
            update={
                "args": tuple(
                    nodes[slots[slot]] for slot in range(len(occurrence.node.args))
                ),
                "typed_as": diagnostics.inferred_types.get(identity),
                "binder_types": diagnostics.binder_types[identity],
                "expr_id": identity,
            }
        )

    def warn_untyped(expr: ExprNode) -> None:
        if diagnostics.diags:
            return

        if expr.typed_as is None:
            logger.warning(
                f"Expression has no inferred type:\n{render_rich(expr_tree_repr(expr))}"
            )

        for argument in expr.args:
            warn_untyped(argument)

    checks: Dict[QName, Dict[str, CheckDef]] = {}
    records: List[RecordDef] = []

    def rewrite_check(record: QName, check: CheckDef) -> CheckDef:
        parts = roots[record][check.id]
        updated = check.model_copy(
            update={
                "cond": nodes[parts[CheckPart.COND]],
                "message": nodes[parts[CheckPart.MESSAGE]],
            }
        )

        warn_untyped(updated.cond)
        warn_untyped(updated.message)
        checks.setdefault(record, {})[check.id] = updated
        return updated

    for record in index.model.records:
        records.append(
            record.model_copy(
                update={
                    "checks": tuple(
                        rewrite_check(record.qname, check) for check in record.checks
                    ),
                    "fields": tuple(
                        field_def.model_copy(
                            update={
                                "checks": [
                                    rewrite_check(record.qname, check)
                                    for check in field_def.checks
                                ]
                            }
                        )
                        for field_def in record.fields
                    ),
                }
            )
        )

    model = index.model.model_copy(update={"records": tuple(records)})
    occurrences: Dict[int, Occurrence] = {}

    for identity, occurrence in program.occurrences.items():
        root = occurrence.root
        occurrences[identity] = replace(
            occurrence,
            node=nodes[identity],
            root=replace(
                root,
                check=checks[root.record][root.check.id],
            ),
        )

    return TypeCheckOutput(
        model=model,
        program=LoweredProgram(
            database=program.database,
            occurrences=occurrences,
        ),
        diags=diagnostics.diags,
        untyped=diagnostics.untyped,
        typed_as=diagnostics.typed_as,
    )
