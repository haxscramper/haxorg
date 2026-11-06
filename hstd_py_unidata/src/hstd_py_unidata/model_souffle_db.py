import sqlite3
from contextlib import contextmanager
from dataclasses import dataclass
from pathlib import Path

import pandas as pd
from beartype import beartype
from beartype.typing import Annotated, ClassVar, Iterator
from sqlalchemy import (
    URL,
    Enum,
    Integer,
    MetaData,
    Text,
    create_engine,
    select,
)
from sqlalchemy.engine import Engine
from sqlalchemy.orm import DeclarativeBase, Mapped, MappedColumn, mapped_column

from hstd_py_unidata import model_ir
from hstd_py_unidata.model_ops import TYPE_CLASS_CONSTRUCTORS, TypeClass
from hstd_py_unidata.model_souffle_db_map import (
    AdtCodec,
    AdtRegistry,
    AdtSql,
    ModelConstructor,
    OptionalShape,
    SequenceShape,
    UnionShape,
    UnionVariant,
)

type DiagnosticDetail = str | model_ir.TypeRef | TypeClass | None


PRIM_CONSTRUCTORS: dict[model_ir.PrimKind, str] = {
    model_ir.PrimKind.INT8: "PInt8",
    model_ir.PrimKind.INT16: "PInt16",
    model_ir.PrimKind.INT32: "PInt32",
    model_ir.PrimKind.INT64: "PInt64",
    model_ir.PrimKind.UINT8: "PUInt8",
    model_ir.PrimKind.UINT16: "PUInt16",
    model_ir.PrimKind.UINT32: "PUInt32",
    model_ir.PrimKind.UINT64: "PUInt64",
    model_ir.PrimKind.FLOAT32: "PFloat32",
    model_ir.PrimKind.FLOAT64: "PFloat64",
    model_ir.PrimKind.STRING: "PString",
    model_ir.PrimKind.BOOL: "PBool",
    model_ir.PrimKind.ANY: "PAny",
    model_ir.PrimKind.NONE: "PNone",
    model_ir.PrimKind.PATH: "PPath",
}


MODEL_CONSTRUCTORS: tuple[ModelConstructor, ...] = (
    ModelConstructor("QNameValue", model_ir.QName),
    *(
        ModelConstructor(
            head,
            model,
            omit=frozenset({"annotation"}),
        )
        for head, model in (
            ("TPrim", model_ir.PrimT),
            ("TList", model_ir.ListT),
            ("TArray", model_ir.ArrayT),
            ("TMap", model_ir.MapT),
            ("TOpt", model_ir.OptT),
            ("TTuple", model_ir.TupleT),
            ("TNamed", model_ir.NamedT),
            ("TExternal", model_ir.ExternalT),
            ("TVariant", model_ir.VariantT),
            ("TDyn", model_ir.DynT),
            ("TParam", model_ir.TypeParamT),
        )
    ),
)

MODEL_ADT_REGISTRY = AdtRegistry(
    models=MODEL_CONSTRUCTORS,
    enums=(
        *PRIM_CONSTRUCTORS.items(),
        *TYPE_CLASS_CONSTRUCTORS.items(),
    ),
    field_shapes={
        (model_ir.QName, "scope"): OptionalShape("NoScope", "SomeScope"),
        (model_ir.TupleT, "elems"): SequenceShape("TNil", "TCons"),
    },
)

TYPE_CODEC = AdtCodec[model_ir.TypeRef](MODEL_ADT_REGISTRY, model_ir.TypeRef, "DbType")
QNAME_CODEC = AdtCodec[model_ir.QName](MODEL_ADT_REGISTRY, model_ir.QName, "DbQName")
PRIM_CODEC = AdtCodec[model_ir.PrimKind](MODEL_ADT_REGISTRY, model_ir.PrimKind, "DbPrim")
CLASS_CODEC = AdtCodec[TypeClass](MODEL_ADT_REGISTRY, TypeClass, "DbClass")
DETAIL_CODEC = AdtCodec[DiagnosticDetail](
    MODEL_ADT_REGISTRY,
    DiagnosticDetail,
    "DbDiagnosticDetail",
    UnionShape(
        (
            UnionVariant(type(None), "NoDetail", value_field=None),
            UnionVariant(TypeClass, "ClassDetail"),
            UnionVariant(str, "TextDetail"),
            UnionVariant(model_ir.TypeRef, "TypeDetail"),
        )
    ),
)
OPTIONAL_TYPE_CODEC = AdtCodec[model_ir.TypeRef | None](
    MODEL_ADT_REGISTRY,
    model_ir.TypeRef | None,
    "DbOptionalType",
    OptionalShape("NoType", "SomeType"),
)


input_metadata = MetaData()
output_metadata = MetaData()


class InputBase(DeclarativeBase):
    metadata = input_metadata


class OutputBase(DeclarativeBase):
    metadata = output_metadata


FactNumber = Annotated[
    int,
    mapped_column(Integer, primary_key=True, nullable=False),
]
FactText = Annotated[
    str,
    mapped_column(Text, primary_key=True, nullable=False),
]
FactOperation = Annotated[
    model_ir.OpId,
    mapped_column(
        Enum(
            model_ir.OpId,
            native_enum=False,
            values_callable=lambda values: [value.value for value in values],
        ),
        primary_key=True,
        nullable=False,
    ),
]


@beartype
def adt_column[T](codec: AdtCodec[T]) -> MappedColumn[T]:
    return mapped_column(
        AdtSql[T](codec),
        primary_key=True,
        nullable=False,
    )


class SerdeSchema(InputBase):
    __tablename__ = "serde_schema"

    schema: Mapped[FactText]


class InputRecord(InputBase):
    __tablename__ = "input_record"

    qname: Mapped[model_ir.QName] = adt_column(QNAME_CODEC)
    kind: Mapped[FactText]


class InputInherits(InputBase):
    __tablename__ = "input_inherits"

    sub: Mapped[model_ir.QName] = adt_column(QNAME_CODEC)
    sup: Mapped[model_ir.QName] = adt_column(QNAME_CODEC)


class InputField(InputBase):
    __tablename__ = "input_field"

    qname: Mapped[model_ir.QName] = adt_column(QNAME_CODEC)
    name: Mapped[FactText]
    t: Mapped[model_ir.TypeRef] = adt_column(TYPE_CODEC)


class InputVariantCase(InputBase):
    __tablename__ = "input_variant_case"

    owner: Mapped[model_ir.QName] = adt_column(QNAME_CODEC)
    vfield: Mapped[FactText]
    tag: Mapped[FactText]
    case_qname: Mapped[model_ir.QName] = adt_column(QNAME_CODEC)


class InputVariantKind(InputBase):
    __tablename__ = "input_variant_kind"

    owner: Mapped[model_ir.QName] = adt_column(QNAME_CODEC)
    vfield: Mapped[FactText]
    kind_enum: Mapped[model_ir.QName] = adt_column(QNAME_CODEC)


class InputEnumValue(InputBase):
    __tablename__ = "input_enum_value"

    qname: Mapped[model_ir.QName] = adt_column(QNAME_CODEC)
    name: Mapped[FactText]


class InputQNameText(InputBase):
    __tablename__ = "input_qname_text"

    qname: Mapped[model_ir.QName] = adt_column(QNAME_CODEC)
    text: Mapped[FactText]


class InputPrimText(InputBase):
    __tablename__ = "input_prim_text"

    prim: Mapped[model_ir.PrimKind] = adt_column(PRIM_CODEC)
    text: Mapped[FactText]


class InputPrimClass(InputBase):
    __tablename__ = "input_prim_class"

    prim: Mapped[model_ir.PrimKind] = adt_column(PRIM_CODEC)
    cls: Mapped[TypeClass] = adt_column(CLASS_CODEC)


class InputClassText(InputBase):
    __tablename__ = "input_class_text"

    cls: Mapped[TypeClass] = adt_column(CLASS_CODEC)
    text: Mapped[FactText]


class InputNumericJoin(InputBase):
    __tablename__ = "input_numeric_join"

    left: Mapped[model_ir.PrimKind] = adt_column(PRIM_CODEC)
    right: Mapped[model_ir.PrimKind] = adt_column(PRIM_CODEC)
    result: Mapped[model_ir.PrimKind] = adt_column(PRIM_CODEC)


class InputOpBindsElem(InputBase):
    __tablename__ = "input_op_binds_elem"

    op: Mapped[FactOperation]


class InputOpBinary(InputBase):
    __tablename__ = "input_op_binary"

    op: Mapped[FactOperation]


class InputExpr(InputBase):
    __tablename__ = "input_expr"

    e: Mapped[FactNumber]
    op: Mapped[FactOperation]


class InputExprArity(InputBase):
    __tablename__ = "input_expr_arity"

    e: Mapped[FactNumber]
    arity: Mapped[FactNumber]


class InputExprArg(InputBase):
    __tablename__ = "input_expr_arg"

    e: Mapped[FactNumber]
    idx: Mapped[FactNumber]
    arg: Mapped[FactNumber]


class InputExprStr(InputBase):
    __tablename__ = "input_expr_str"

    e: Mapped[FactNumber]
    value: Mapped[FactText]


class InputExprInt(InputBase):
    __tablename__ = "input_expr_int"

    e: Mapped[FactNumber]
    value: Mapped[FactNumber]


class InputExprTypeVal(InputBase):
    __tablename__ = "input_expr_type_val"

    e: Mapped[FactNumber]
    t: Mapped[model_ir.TypeRef] = adt_column(TYPE_CODEC)


class InputExprFlag(InputBase):
    __tablename__ = "input_expr_flag"

    e: Mapped[FactNumber]
    flag: Mapped[FactText]


class InputBinds(InputBase):
    __tablename__ = "input_binds"

    e: Mapped[FactNumber]
    slot: Mapped[FactNumber]
    binder: Mapped[FactNumber]


class InputVarRef(InputBase):
    __tablename__ = "input_var_ref"

    e: Mapped[FactNumber]
    binder: Mapped[FactNumber]


class InputThisType(InputBase):
    __tablename__ = "input_this_type"

    e: Mapped[FactNumber]
    t: Mapped[model_ir.TypeRef] = adt_column(TYPE_CODEC)


class InputRoot(InputBase):
    __tablename__ = "input_root"

    e: Mapped[FactNumber]
    expected: Mapped[model_ir.TypeRef] = adt_column(TYPE_CODEC)


class InputExprArgClass(InputBase):
    __tablename__ = "input_expr_arg_class"

    e: Mapped[FactNumber]
    idx: Mapped[FactNumber]
    cls: Mapped[TypeClass] = adt_column(CLASS_CODEC)


class InputExprFixedResult(InputBase):
    __tablename__ = "input_expr_fixed_result"

    e: Mapped[FactNumber]
    t: Mapped[model_ir.TypeRef] = adt_column(TYPE_CODEC)


class SqDiag(OutputBase):
    __tablename__ = "sq_diag"

    code: Mapped[FactText]
    e: Mapped[FactNumber]
    idx: Mapped[FactNumber]
    detail: Mapped[DiagnosticDetail] = adt_column(DETAIL_CODEC)
    actual: Mapped[model_ir.TypeRef] = adt_column(TYPE_CODEC)
    subject: Mapped[model_ir.TypeRef | None] = adt_column(OPTIONAL_TYPE_CODEC)


class Untyped(OutputBase):
    __tablename__ = "untyped"

    e: Mapped[FactNumber]


class TypedAs(OutputBase):
    __tablename__ = "typed_as"

    e: Mapped[FactNumber]
    text: Mapped[FactText]


class SqInferredType(OutputBase):
    __tablename__ = "sq_inferred_type"

    e: Mapped[FactNumber]
    t: Mapped[model_ir.TypeRef] = adt_column(TYPE_CODEC)


class SqInferredBinderType(OutputBase):
    __tablename__ = "sq_inferred_binder_type"

    e: Mapped[FactNumber]
    slot: Mapped[FactNumber]
    t: Mapped[model_ir.TypeRef] = adt_column(TYPE_CODEC)


@beartype
@dataclass(frozen=True)
class InputDatabase:
    """Typed dataframe snapshot of the lowering database."""

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

    schema: ClassVar[MetaData] = input_metadata


@beartype
@dataclass(frozen=True)
class OutputDatabase:
    """Typed dataframe snapshot of the checker output database."""

    sq_diag: pd.DataFrame
    untyped: pd.DataFrame
    typed_as: pd.DataFrame
    sq_inferred_type: pd.DataFrame
    sq_inferred_binder_type: pd.DataFrame

    schema: ClassVar[MetaData] = output_metadata


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
    """Read typed selections so dataframe cells contain decoded ADT values."""

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
