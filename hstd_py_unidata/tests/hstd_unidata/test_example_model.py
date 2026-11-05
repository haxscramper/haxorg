import json
from pathlib import Path

from beartype.typing import Annotated, Any, Callable, Dict, List, Optional, Tuple
from hstd_py_lib.external_packages.rich_utils import render_rich
from hstd_py_lib.pydantic_utils import format_json_with_fjson
from hstd_py_lib.script_logging import to_debug_json
from hstd_py_unidata.model_dsl import (
    EnFieldAnnotation,
    FixedArray,
    Float32,
    Float64,
    GenConfig,
    Int8,
    Int16,
    Int32,
    Int64,
    UInt8,
    UInt16,
    UInt32,
    UInt64,
    __check__,
    __config__,
    __variant__,
    get_dsl_model,
    op_and,
    op_not,
    op_or,
)
from hstd_py_unidata.model_gen import GenContext
from hstd_py_unidata.model_ir import ExternalT, model_tree_repr
from hstd_py_unidata.model_value import Value
from loguru import logger

GvModel = get_dsl_model("graphviz.pkg")
KwModel = get_dsl_model("kiwi.pkg")
M = get_dsl_model("org.sem.model")


class TaskStatus(M.Enum):
    PENDING: Annotated[int, EnFieldAnnotation(doc="Task is pending")] = 1
    DONE: Annotated[int, EnFieldAnnotation(doc="Task is completed")] = 2


class ScalarShowcase(M.Class):
    i8: Int8
    i16: Int16
    i32: Int32
    i64: Int64
    u8: UInt8
    u16: UInt16
    u32: UInt32
    u64: UInt64
    f32: Float32
    f64: Float64
    matrix_row: FixedArray[Int32, 4]
    coords: Tuple[Int32, Float64, str]
    metadata: Dict[str, Int64]
    opaque_payload: Any
    status: TaskStatus = M.Field(default=TaskStatus.PENDING)

    __check__(
        id="scalar-constraints",
        cond=op_and(
            M.This["coords"]._Nth.get(0) <= 100,
            M.This["metadata"]._Map.contains("version"),
            M.This["status"]._Enum.is_val("PENDING"),
        ),
        message="Scalar showcase validation failed",
    )


class ColumnView(M.Class):
    class Summary(M.Class):
        class CheckboxAggregate(M.Case):
            class Kind(M.Enum):
                IfAllNested: Annotated[int, EnFieldAnnotation(doc="All nested")] = 0
                AggregateFractionRec: Annotated[
                    int, EnFieldAnnotation(doc="Fraction")
                ] = 1
                AggregatePercentRec: Annotated[int, EnFieldAnnotation(doc="Percent")] = 2

            kind: Kind

        class MathAggregate(M.Case):
            class Kind(M.Enum):
                Min: Annotated[int, EnFieldAnnotation(doc="Minimum")] = 0
                Max: Annotated[int, EnFieldAnnotation(doc="Maximum")] = 1
                Mean: Annotated[int, EnFieldAnnotation(doc="Mean")] = 2
                Sum: Annotated[int, EnFieldAnnotation(doc="Sum")] = 3
                LowHighEst: Annotated[int, EnFieldAnnotation(doc="Low-High estimate")] = 4

            kind: Kind
            formatDigits: Optional[Int32] = None
            formatPrecision: Optional[Int32] = None

        __variant__(CheckboxAggregate, MathAggregate)

        def __eq__(self, other: "ColumnView.Summary") -> bool: ...

    class Column(M.Class):
        summary: Optional["ColumnView.Summary"] = None
        width: Optional[Int32] = M.Field(  # type: ignore
            default=None,
            check=op_or(
                op_not(M.This._Opt.has_value()),
                0 < M.This._Opt.value(),
            ),
            message="column width must be positive when it is set",
        )
        property: Optional[str] = None
        propertyTitle: Optional[str] = None

        def __hash__(self) -> int:
            return hash((self.property, self.propertyTitle))

        def __eq__(self, other: "ColumnView.Column") -> bool:
            return (
                self.property,
                self.propertyTitle,
            ) == (
                other.property,
                other.propertyTitle,
            )

    columns: List[Column]

    __check__(
        id="column-limit",
        cond=M.This["columns"]._List.size() <= 16,
        message="a column view supports at most 16 columns",
    )


class LayoutPayload(M.Class):
    """Layout data delegated to external graphviz and kiwi models."""

    class NoLayout(M.Case):
        pass

    class GraphvizLayout(M.Case):
        graphviz: GvModel._T["GroupAttributePayload"]
        graphviz2: GvModel._T["some.Nested.Thing"]

    class KiwiLayout(M.Case):
        kiwi: KwModel._T["KiwiThing"]

    title: str
    __variant__(NoLayout, GraphvizLayout, KiwiLayout, field="layout", kind="LayoutKind")

    __check__(
        id="graphviz-title",
        cond=op_or(
            op_not(M.This["layout"]._Case.is_case("GraphvizLayout")),
            0 < M.This["title"]._Str.size(),
        ),
        message="graphviz layouts are rendered with a title, so the title must not be empty",
    )


class Org(M.Class):
    fields: List["Org"]

    __config__(
        backend=dict(
            cpp=dict(
                section_code=[
                    dict(
                        kind="public",
                        text=(
                            "[[refl]] virtual OrgSemKind getKind() const = 0;\n"
                            "[[refl]] hstd::Opt<parse::SourceLoc> loc = std::nullopt;"
                        ),
                    )
                ]
            )
        )
    )

    def __init__(self, fields: List["Org"]) -> None: ...

    @staticmethod
    @M.Method(
        backend=dict(
            cpp=dict(
                attributes=["refl"],
                is_pure_virtual=True,
            )
        )
    )
    def getKind() -> str: ...

    @M.Method()
    def transform[T](self, item: T, *extra: Int32) -> T: ...


class Text(Org, M.Class):
    text: str

    __check__(
        id="empty-subfields",
        cond=M.This["fields"]._List.size() == 0,
        message="text nodes don't allow sub-fields",
    )


def external_generators() -> Dict[ExternalT, Callable[[GenContext], Value]]:
    """External payloads are opaque to the model, so their generators come from the user."""

    def payload(t: ExternalT, data: Dict[str, Any]) -> Callable[[GenContext], Value]:
        def generate(ctx: GenContext) -> Value:
            return ctx.decode(t, dict(data, seed=ctx.rng.randint(0, 9)))

        return generate

    types = (
        (GvModel._T["GroupAttributePayload"], {"rank": "same"}),
        (GvModel._T["some.Nested.Thing"], {"thing": True}),
        (KwModel._T["KiwiThing"], {"strength": "strong"}),
    )
    return {t: payload(t, data) for t, data in types}


def test_example_model_main(stable_test_dir: Path):
    diag = M.get_typed()

    Path("/tmp/type_check.json").write_text(
        format_json_with_fjson(
            to_debug_json(
                diag,
                skip_cyclic_data=False,
                skip_none_valued_items=True,
            )
        )
    )

    Path("/tmp/type_check.txt").write_text(render_rich(model_tree_repr(diag)))

    logger.info("Souffle type check passed")
    for cls in (ScalarShowcase, ColumnView, LayoutPayload, Text):
        value = M.generate(cls, GenConfig(seed=7), type_overrides=external_generators())
        warnings = M.validate(cls, value)
        logger.info(
            f"{cls.__name__}: {json.dumps(M.encode(cls, value))} with {len(warnings)} warning(s)"
        )
    Path("/tmp/result.json").write_text(json.dumps(M.to_dict(), indent=2))
    logger.info("Model written to /tmp/result.json")
