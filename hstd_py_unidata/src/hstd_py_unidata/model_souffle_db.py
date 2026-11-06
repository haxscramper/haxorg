from __future__ import annotations

import sqlite3
from contextlib import contextmanager
from dataclasses import dataclass
from pathlib import Path

import pandas as pd
from beartype import beartype
from beartype.typing import ClassVar, Iterator
from sqlalchemy import (
    URL,
    Column,
    Enum,
    Integer,
    MetaData,
    Table,
    Text,
    create_engine,
    select,
)
from sqlalchemy.engine import Engine

from hstd_py_unidata.model_ir import OpId, PrimKind, QName, TypeRef
from hstd_py_unidata.model_ops import TypeClass
from hstd_py_unidata.model_souffle_db_map import (
    AdtRoot,
    AdtSql,
    DiagnosticDetail,
)

input_metadata = MetaData()
output_metadata = MetaData()


@beartype
def number(name: str) -> Column[int]:
    return Column(name, Integer, nullable=False)


@beartype
def text(name: str) -> Column[str]:
    return Column(name, Text, nullable=False)


@beartype
def type_column(name: str) -> Column[TypeRef]:
    return Column(name, AdtSql[TypeRef](AdtRoot.TYPE), nullable=False)


@beartype
def qname_column(name: str) -> Column[QName]:
    return Column(name, AdtSql[QName](AdtRoot.QNAME), nullable=False)


@beartype
def prim_column(name: str) -> Column[PrimKind]:
    return Column(name, AdtSql[PrimKind](AdtRoot.PRIM), nullable=False)


@beartype
def class_column(name: str) -> Column[TypeClass]:
    return Column(name, AdtSql[TypeClass](AdtRoot.CLASS), nullable=False)


@beartype
def op_column(name: str) -> Column[OpId]:
    return Column(
        name,
        Enum(
            OpId,
            native_enum=False,
            values_callable=lambda values: [value.value for value in values],
        ),
        nullable=False,
    )


serde_schema = Table(
    "serde_schema",
    input_metadata,
    text("schema"),
)

input_record = Table(
    "input_record",
    input_metadata,
    qname_column("qname"),
    text("kind"),
)
input_inherits = Table(
    "input_inherits",
    input_metadata,
    qname_column("sub"),
    qname_column("sup"),
)
input_field = Table(
    "input_field",
    input_metadata,
    qname_column("qname"),
    text("name"),
    type_column("t"),
)
input_variant_case = Table(
    "input_variant_case",
    input_metadata,
    qname_column("owner"),
    text("vfield"),
    text("tag"),
    qname_column("case_qname"),
)
input_variant_kind = Table(
    "input_variant_kind",
    input_metadata,
    qname_column("owner"),
    text("vfield"),
    qname_column("kind_enum"),
)
input_enum_value = Table(
    "input_enum_value",
    input_metadata,
    qname_column("qname"),
    text("name"),
)
input_qname_text = Table(
    "input_qname_text",
    input_metadata,
    qname_column("qname"),
    text("text"),
)
input_prim_text = Table(
    "input_prim_text",
    input_metadata,
    prim_column("prim"),
    text("text"),
)
input_prim_class = Table(
    "input_prim_class",
    input_metadata,
    prim_column("prim"),
    class_column("cls"),
)
input_class_text = Table(
    "input_class_text",
    input_metadata,
    class_column("cls"),
    text("text"),
)
input_numeric_join = Table(
    "input_numeric_join",
    input_metadata,
    prim_column("left"),
    prim_column("right"),
    prim_column("result"),
)
input_op_binds_elem = Table(
    "input_op_binds_elem",
    input_metadata,
    op_column("op"),
)
input_op_binary = Table(
    "input_op_binary",
    input_metadata,
    op_column("op"),
)
input_expr = Table(
    "input_expr",
    input_metadata,
    number("e"),
    op_column("op"),
)
input_expr_arity = Table(
    "input_expr_arity",
    input_metadata,
    number("e"),
    number("arity"),
)
input_expr_arg = Table(
    "input_expr_arg",
    input_metadata,
    number("e"),
    number("idx"),
    number("arg"),
)
input_expr_str = Table(
    "input_expr_str",
    input_metadata,
    number("e"),
    text("value"),
)
input_expr_int = Table(
    "input_expr_int",
    input_metadata,
    number("e"),
    number("value"),
)
input_expr_type_val = Table(
    "input_expr_type_val",
    input_metadata,
    number("e"),
    type_column("t"),
)
input_expr_flag = Table(
    "input_expr_flag",
    input_metadata,
    number("e"),
    text("flag"),
)
input_binds = Table(
    "input_binds",
    input_metadata,
    number("e"),
    number("slot"),
    number("binder"),
)
input_var_ref = Table(
    "input_var_ref",
    input_metadata,
    number("e"),
    number("binder"),
)
input_this_type = Table(
    "input_this_type",
    input_metadata,
    number("e"),
    type_column("t"),
)
input_root = Table(
    "input_root",
    input_metadata,
    number("e"),
    type_column("expected"),
)
input_expr_arg_class = Table(
    "input_expr_arg_class",
    input_metadata,
    number("e"),
    number("idx"),
    class_column("cls"),
)
input_expr_fixed_result = Table(
    "input_expr_fixed_result",
    input_metadata,
    number("e"),
    type_column("t"),
)

sq_diag = Table(
    "sq_diag",
    output_metadata,
    text("code"),
    number("e"),
    number("idx"),
    Column(
        "detail",
        AdtSql[DiagnosticDetail](AdtRoot.DIAGNOSTIC_DETAIL),
        nullable=False,
    ),
    type_column("actual"),
    Column(
        "subject",
        AdtSql[TypeRef | None](AdtRoot.OPTIONAL_TYPE),
        nullable=False,
    ),
)
untyped = Table(
    "untyped",
    output_metadata,
    number("e"),
)
typed_as = Table(
    "typed_as",
    output_metadata,
    number("e"),
    text("text"),
)
sq_inferred_type = Table(
    "sq_inferred_type",
    output_metadata,
    number("e"),
    type_column("t"),
)
sq_inferred_binder_type = Table(
    "sq_inferred_binder_type",
    output_metadata,
    number("e"),
    number("slot"),
    type_column("t"),
)


@beartype
@dataclass(frozen=True)
class InputDatabase:
    """Optional typed dataframe snapshot of the lowering database."""

    schema: ClassVar[MetaData] = input_metadata

    serde_schema: pd.DataFrame
    input_record: pd.DataFrame
    input_inherits: pd.DataFrame
    input_field: pd.DataFrame
    input_variant_case: pd.DataFrame
    input_variant_kind: pd.DataFrame
    input_enum_value: pd.DataFrame
    input_qname_text: pd.DataFrame
    input_prim_text: pd.DataFrame
    input_prim_class: pd.DataFrame
    input_class_text: pd.DataFrame
    input_numeric_join: pd.DataFrame
    input_op_binds_elem: pd.DataFrame
    input_op_binary: pd.DataFrame
    input_expr: pd.DataFrame
    input_expr_arity: pd.DataFrame
    input_expr_arg: pd.DataFrame
    input_expr_str: pd.DataFrame
    input_expr_int: pd.DataFrame
    input_expr_type_val: pd.DataFrame
    input_expr_flag: pd.DataFrame
    input_binds: pd.DataFrame
    input_var_ref: pd.DataFrame
    input_this_type: pd.DataFrame
    input_root: pd.DataFrame
    input_expr_arg_class: pd.DataFrame
    input_expr_fixed_result: pd.DataFrame


@beartype
@dataclass(frozen=True)
class OutputDatabase:
    """Optional typed dataframe snapshot of the checker output database."""

    schema: ClassVar[MetaData] = output_metadata

    sq_diag: pd.DataFrame
    untyped: pd.DataFrame
    typed_as: pd.DataFrame
    sq_inferred_type: pd.DataFrame
    sq_inferred_binder_type: pd.DataFrame


@contextmanager
@beartype
def database_engine(
    database_path: str | Path,
    read_only: bool = False,
) -> Iterator[Engine]:
    path = Path(database_path).resolve()

    if read_only:
        uri = path.as_uri() + "?mode=ro"
        engine = create_engine(
            "sqlite+pysqlite://",
            creator=lambda: sqlite3.connect(uri, uri=True),
        )
    else:
        engine = create_engine(URL.create("sqlite+pysqlite", database=str(path)))

    try:
        yield engine
    finally:
        engine.dispose()


@beartype
def load_database_as_dataframe_structure[T: InputDatabase | OutputDatabase](
    database_path: str | Path,
    dataclass_type: type[T],
) -> T:
    """Read typed table selections so dataframe cells contain decoded ADT values."""

    with database_engine(database_path, read_only=True) as engine:
        with engine.connect() as connection:
            dataframes = {
                table.name: pd.read_sql_query(
                    select(table),
                    connection,
                    coerce_float=False,
                )
                for table in dataclass_type.schema.sorted_tables
            }

    return dataclass_type(**dataframes)
