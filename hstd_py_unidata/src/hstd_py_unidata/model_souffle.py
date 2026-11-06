from __future__ import annotations

import enum
import tempfile
from dataclasses import dataclass, field, replace
from os import getenv
from pathlib import Path

from beartype import beartype
from hstd_py_lib.external_packages.rich_utils import render_rich
from hstd_py_lib.external_packages.sqlalchemy_utils import format_db_all
from loguru import logger
from plumbum import local
from sqlalchemy import insert, select
from sqlalchemy.engine import Connection

from hstd_py_unidata import model_souffle_db as db
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
    QName,
    RecordDef,
    TupleT,
    TypeRef,
    VariantT,
    expr_tree_repr,
    numeric_join,
)
from hstd_py_unidata.model_ops import (
    BOOL_T,
    STRING_T,
    TYPE_CLASS_DESCRIPTIONS,
    Operator,
    TypeClass,
)
from hstd_py_unidata.model_souffle_db_map import prepare_serde_schema
from hstd_py_unidata.souffle_path import get_serde_library_path

RULES_DIR = Path(__file__).parent
SQLITE_PROGRAM = RULES_DIR / "logic_model" / "model_sqlite.dl"


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
    parent: int | None
    arg_index: int
    root: CheckRoot
    binder_of: int | None
    """Occurrence introducing the binder referenced by this variable."""


@beartype
@dataclass
class LoweredProgram:
    occurrences: dict[int, Occurrence] = field(default_factory=dict)

    input_database: db.InputDatabase | None = None
    """Optional dataframe snapshot; never used to execute the checker."""

    output_database: db.OutputDatabase | None = None
    """Optional dataframe snapshot captured before temporary files are removed."""


@beartype
@dataclass(frozen=True)
class DiagRow:
    """Structured diagnostic whose types are decoded from the serde ADTs."""

    code: str
    expr: int
    arg: int
    detail: db.DiagnosticDetail
    actual: TypeRef
    subject: TypeRef | None


@beartype
@dataclass(frozen=True)
class TypeCheckOutput:
    model: ModelDef
    """Model rewritten with inferred expression and binder types."""

    program: LoweredProgram
    diags: list[DiagRow]
    untyped: set[int]
    typed_as: dict[int, str]


@beartype
@dataclass(frozen=True)
class DiagnosticsResult:
    diags: list[DiagRow]
    untyped: set[int]
    typed_as: dict[int, str]
    inferred_types: dict[int, TypeRef]
    binder_types: dict[int, tuple[TypeRef, ...]]


@beartype
class SouffleProtocolError(Exception):
    """Soufflé output does not follow the expected relation layout."""


@beartype
class Lowering:
    """Write the finalized model directly to typed SQLite input tables."""

    def __init__(
        self,
        index: ModelIndex,
        table: dict[OpId, Operator],
        database: Connection,
    ) -> None:
        self.index = index
        self.table = table
        self.database = database
        self.program = LoweredProgram()
        self.next_expr = 0
        self.next_binder = 0
        self.binder_owner: dict[int, int] = {}
        self.qnames: set[QName] = set()
        self.types: set[TypeRef] = set()

    def lower_qname(self, qname: QName) -> QName:
        if qname in self.qnames:
            return qname

        if qname.scope is not None:
            self.lower_qname(qname.scope)

        self.database.execute(
            insert(db.input_qname_text),
            {"qname": qname, "text": qname.to_id()},
        )
        self.qnames.add(qname)
        return qname

    def lower_type(self, value: TypeRef) -> TypeRef:
        """Register display names without decomposing the stored structural ADT."""

        if value in self.types:
            return value

        match value:
            case NamedT() | ExternalT():
                self.lower_qname(value.qname)
            case VariantT():
                self.lower_qname(value.owner)
            case ListT() | ArrayT() | OptT():
                self.lower_type(value.elem)
            case MapT():
                self.lower_type(value.key)
                self.lower_type(value.value)
            case TupleT():
                for element in value.elems:
                    self.lower_type(element)
            case DynT():
                self.lower_type(value.root)
            case _:
                pass

        self.types.add(value)
        return value

    def lower(self) -> LoweredProgram:
        self.lower_builtin_facts()

        for record in self.index.model.records:
            self.lower_record(record)

        for enum_def in self.index.model.enums:
            qname = self.lower_qname(enum_def.qname)
            self.database.execute(
                insert(db.input_record),
                {"qname": qname, "kind": "enum"},
            )
            for value in enum_def.enum_values:
                self.database.execute(
                    insert(db.input_enum_value),
                    {"qname": qname, "name": value.name},
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

        return self.program

    def lower_builtin_facts(self) -> None:
        for prim in db.PRIM_CONSTRUCTORS:
            self.database.execute(
                insert(db.input_prim_text),
                {"prim": prim, "text": prim.value},
            )

            classes: list[TypeClass] = []
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

            for cls in classes:
                self.database.execute(
                    insert(db.input_prim_class),
                    {"prim": prim, "cls": cls},
                )

        numeric = [
            prim
            for prim in db.PRIM_CONSTRUCTORS
            if prim in INTEGER_RANGES or prim in FLOAT_PRIMS
        ]
        for left in numeric:
            for right in numeric:
                self.database.execute(
                    insert(db.input_numeric_join),
                    {
                        "left": left,
                        "right": right,
                        "result": numeric_join(left, right),
                    },
                )

        for cls in TypeClass:
            self.database.execute(
                insert(db.input_class_text),
                {
                    "cls": cls,
                    "text": TYPE_CLASS_DESCRIPTIONS[cls],
                },
            )

        for operator in self.table.values():
            if operator.elem_binder:
                self.database.execute(
                    insert(db.input_op_binds_elem),
                    {"op": operator.op_id},
                )
            if operator.binary_operands:
                self.database.execute(
                    insert(db.input_op_binary),
                    {"op": operator.op_id},
                )

    def lower_record(self, record: RecordDef) -> None:
        qname = self.lower_qname(record.qname)
        self.database.execute(
            insert(db.input_record),
            {"qname": qname, "kind": record.kind.value},
        )

        for base in record.bases:
            self.database.execute(
                insert(db.input_inherits),
                {
                    "sub": qname,
                    "sup": self.lower_qname(base),
                },
            )

        for field_def in record.fields:
            self.database.execute(
                insert(db.input_field),
                {
                    "qname": qname,
                    "name": field_def.name,
                    "t": self.lower_type(field_def.type),
                },
            )

        for variant in record.variants:
            self.database.execute(
                insert(db.input_variant_kind),
                {
                    "owner": qname,
                    "vfield": variant.field,
                    "kind_enum": self.lower_qname(variant.kind_enum),
                },
            )
            for case in variant.cases:
                self.database.execute(
                    insert(db.input_variant_case),
                    {
                        "owner": qname,
                        "vfield": variant.field,
                        "tag": case.tag,
                        "case_qname": self.lower_qname(case.case),
                    },
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
                insert(db.input_root),
                {
                    "e": identity,
                    "expected": self.lower_type(expected),
                },
            )

    def lower_expr(
        self,
        node: ExprNode,
        parent: int | None,
        arg_index: int,
        root: CheckRoot,
        this_type: TypeRef,
        scope: dict[str, int],
    ) -> int:
        identity = self.next_expr
        self.next_expr += 1

        operator = self.table[node.op]
        binder_of: int | None = None

        self.database.execute(
            insert(db.input_expr),
            {"e": identity, "op": node.op},
        )
        self.database.execute(
            insert(db.input_expr_arity),
            {"e": identity, "arity": len(node.args)},
        )

        if node.str_val is not None:
            self.database.execute(
                insert(db.input_expr_str),
                {"e": identity, "value": node.str_val},
            )
        if node.int_val is not None:
            self.database.execute(
                insert(db.input_expr_int),
                {"e": identity, "value": node.int_val},
            )
        if node.type_val is not None:
            self.database.execute(
                insert(db.input_expr_type_val),
                {"e": identity, "t": self.lower_type(node.type_val)},
            )
        if node.op == OpId.TYPE_COND and node.bool_val:
            self.database.execute(
                insert(db.input_expr_flag),
                {"e": identity, "flag": "unhandled_ignore"},
            )
        if node.op == OpId.THIS:
            self.database.execute(
                insert(db.input_this_type),
                {"e": identity, "t": self.lower_type(this_type)},
            )
        if node.op == OpId.VAR:
            assert node.str_val is not None
            binder = scope[node.str_val]
            binder_of = self.binder_owner[binder]
            self.database.execute(
                insert(db.input_var_ref),
                {"e": identity, "binder": binder},
            )

        inner = dict(scope)
        for slot, name in enumerate(node.binders):
            binder = self.next_binder
            self.next_binder += 1
            self.binder_owner[binder] = identity
            inner[name] = binder
            self.database.execute(
                insert(db.input_binds),
                {"e": identity, "slot": slot, "binder": binder},
            )

        for index, cls in operator.arg_class_facts(node):
            self.database.execute(
                insert(db.input_expr_arg_class),
                {"e": identity, "idx": index, "cls": cls},
            )

        if operator.fixed_result is not None:
            self.database.execute(
                insert(db.input_expr_fixed_result),
                {
                    "e": identity,
                    "t": self.lower_type(operator.fixed_result),
                },
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
                insert(db.input_expr_arg),
                {
                    "e": identity,
                    "idx": index,
                    "arg": argument_id,
                },
            )

        return identity


@beartype
def souffle_arguments(
    input_database: Path,
    output_database: Path,
) -> list[str]:
    library = get_serde_library_path()
    if not library.exists():
        raise FileNotFoundError(
            f"Cannot run the Soufflé checker: serde library {library} does not exist"
        )

    macros = " ".join(
        (
            f'INPUT_DATABASE=\\"{input_database.resolve()}\\"',
            f'OUTPUT_DATABASE=\\"{output_database.resolve()}\\"',
        )
    )

    return [
        "-w",
        "-I",
        str(RULES_DIR),
        "-L",
        str(library.parent),
        "-l",
        "hstd_cpp_souffle_serde",
        "-M",
        macros,
    ]


@beartype
def read_inferred_types(
    database: Connection,
    program: LoweredProgram,
) -> tuple[dict[int, TypeRef], dict[int, tuple[TypeRef, ...]]]:
    """Read SQLAlchemy-decoded types and validate occurrence and binder identities."""

    result: dict[int, TypeRef] = {}
    for row in database.execute(select(db.sq_inferred_type)).mappings():
        identity = row["e"]
        inferred = row["t"]

        if identity not in program.occurrences:
            raise SouffleProtocolError(
                f"Inferred type {inferred!r} refers to expression {identity}, "
                "which was never lowered"
            )
        if identity in result:
            raise SouffleProtocolError(
                f"Expression {identity} has multiple inferred types: "
                f"{result[identity]!r} and {inferred!r}; "
                "ExprNode.typed_as requires a single type"
            )

        result[identity] = inferred

    binder_slots: dict[int, dict[int, TypeRef]] = {}
    for row in database.execute(select(db.sq_inferred_binder_type)).mappings():
        identity = row["e"]
        slot = row["slot"]
        inferred = row["t"]

        if identity not in program.occurrences:
            raise SouffleProtocolError(
                f"Inferred binder type {inferred!r} refers to expression "
                f"{identity}, which was never lowered"
            )

        node = program.occurrences[identity].node
        if not 0 <= slot < len(node.binders):
            raise SouffleProtocolError(
                f"Inferred binder type {inferred!r} refers to slot {slot} "
                f"of expression {identity}, which has {len(node.binders)} binders"
            )

        slots = binder_slots.setdefault(identity, {})
        if slot in slots:
            raise SouffleProtocolError(
                f"Binder slot {slot} of expression {identity} has multiple "
                f"inferred types: {slots[slot]!r} and {inferred!r}; "
                "ExprNode.binder_types requires a single type per binder"
            )

        slots[slot] = inferred

    binder_types: dict[int, tuple[TypeRef, ...]] = {}
    for identity, occurrence in program.occurrences.items():
        slots = binder_slots.get(identity, {})
        count = len(occurrence.node.binders)
        binder_types[identity] = (
            tuple(slots[slot] for slot in range(count)) if len(slots) == count else ()
        )

    return result, binder_types


@beartype
def run_for_diagnostics(
    input_database: Path,
    output_database: Path,
    program: LoweredProgram,
) -> DiagnosticsResult:
    local["souffle"][
        *souffle_arguments(input_database, output_database),
        str(SQLITE_PROGRAM),
    ]()

    with db.database_engine(output_database, read_only=True) as engine:
        with engine.connect() as database:
            diags = [
                DiagRow(
                    code=row["code"],
                    expr=row["e"],
                    arg=row["idx"],
                    detail=row["detail"],
                    actual=row["actual"],
                    subject=row["subject"],
                )
                for row in database.execute(select(db.sq_diag)).mappings()
            ]
            untyped = set(database.execute(select(db.untyped.c.e)).scalars())
            typed_as = {
                row["e"]: row["text"]
                for row in database.execute(select(db.typed_as)).mappings()
            }
            inferred_types, binder_types = read_inferred_types(
                database,
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
    table: dict[OpId, Operator],
    capture_databases: bool = False,
) -> TypeCheckOutput:
    """Run the checker; optionally retain typed dataframe snapshots for inspection."""

    with tempfile.TemporaryDirectory() as temporary:
        directory = Path(temporary)
        input_database = directory / "input.sqlite"
        output_database = directory / "output.sqlite"

        schema = prepare_serde_schema(
            SQLITE_PROGRAM,
            souffle_arguments(input_database, output_database),
        )

        with db.database_engine(input_database) as engine:
            db.input_metadata.create_all(engine)
            with engine.begin() as database:
                database.execute(
                    insert(db.serde_schema),
                    {"schema": schema},
                )
                program = Lowering(index, table, database).lower()

        diagnostics = run_for_diagnostics(
            input_database,
            output_database,
            program,
        )

        if capture_databases:
            program.input_database = db.load_database_as_dataframe_structure(
                input_database,
                db.InputDatabase,
            )
            program.output_database = db.load_database_as_dataframe_structure(
                output_database,
                db.OutputDatabase,
            )

        debug_path = getenv("HSTD_STABLE_TEST_DIR_PATH")
        if debug_path:
            debug_directory = Path(debug_path)
            debug_directory.mkdir(parents=True, exist_ok=True)
            debug_directory.joinpath("input.txt").write_text(
                format_db_all(input_database),
                encoding="utf-8",
            )
            debug_directory.joinpath("output.txt").write_text(
                format_db_all(output_database),
                encoding="utf-8",
            )
            debug_directory.joinpath("schema.json").write_text(
                schema + "\n",
                encoding="utf-8",
            )

    for diagnostic in diagnostics.diags:
        if diagnostic.expr not in program.occurrences:
            raise SouffleProtocolError(
                f"Diagnostic {diagnostic!r} refers to expression "
                f"{diagnostic.expr}, which was never lowered"
            )

    arguments: dict[int, dict[int, int]] = {}
    roots: dict[QName, dict[str, dict[CheckPart, int]]] = {}

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

    nodes: dict[int, ExprNode] = {}
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

    checks: dict[QName, dict[str, CheckDef]] = {}
    records: list[RecordDef] = []

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
    occurrences: dict[int, Occurrence] = {}

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
            occurrences=occurrences,
            input_database=program.input_database,
            output_database=program.output_database,
        ),
        diags=diagnostics.diags,
        untyped=diagnostics.untyped,
        typed_as=diagnostics.typed_as,
    )
