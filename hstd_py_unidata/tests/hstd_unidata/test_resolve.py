import pytest
from beartype.typing import List, Optional
from hstd_py_unidata.model_dsl import (
    Int32,
    __check__,
    __variant__,
    get_dsl_model,
    op_all,
)
from hstd_py_unidata.model_ir import NamedT, RecordKind, VariantT
from hstd_py_unidata.model_resolve import DslModelError


def test_variant_creates_data_field_and_kind_enum() -> None:
    M = get_dsl_model("test.variant")

    class Shape(M.Class):
        class Circle(M.Case):
            radius: Int32

        class Square(M.Case):
            side: Int32

        __variant__(Circle, Square)

    index = M.index
    shape = M.type_of(Shape)
    assert isinstance(shape, NamedT)
    data = index.field(shape.qname, "data")
    assert data is not None and isinstance(data.type, VariantT)
    kind = index.enum_by_id("Shape::Kind")
    assert kind.kind == RecordKind.ENUM
    assert [v.name for v in kind.enum_values] == ["Circle", "Square"]


def test_variant_field_and_kind_names_are_configurable() -> None:
    M = get_dsl_model("test.variant.names")

    class Element(M.Class):
        class NoAlgo(M.Case):
            pass

        class Kiwi(M.Case):
            strength: float

        __variant__(NoAlgo, Kiwi, field="algo", kind="AlgoKind")

    index = M.index
    qname = M.type_of(Element).qname
    assert index.field(qname, "algo") is not None
    assert index.field(qname, "data") is None
    assert index.enum_by_id("Element::AlgoKind").kind == RecordKind.ENUM


def test_variant_kind_clash_is_a_model_error() -> None:
    M = get_dsl_model("test.variant.clash")

    class Holder(M.Class):
        class Kind(M.Enum):
            A: int = 0

        class Only(M.Case):
            value: int

        __variant__(Only)

    with pytest.raises(DslModelError, match="generated kind enum 'Kind'.*clashes"):
        M.finalize()


def test_none_default_requires_optional_field() -> None:
    M = get_dsl_model("test.none.default")

    class Bad(M.Class):
        count: int = None  # type: ignore

    with pytest.raises(DslModelError, match="only optional fields accept None"):
        M.finalize()


def test_untagged_union_suggests_variant() -> None:
    M = get_dsl_model("test.union")

    class A(M.Class):
        x: int

    class B(M.Class):
        y: int

    class Holder(M.Class):
        item: A | B

    with pytest.raises(DslModelError, match="__variant__"):
        M.finalize()


def test_unknown_name_lists_searched_scopes() -> None:
    M = get_dsl_model("test.unknown.name")

    class Outer(M.Class):
        class Inner(M.Class):
            ref: "Missing"

    with pytest.raises(
        DslModelError,
        match="name 'Missing' is not defined; searched declaration scopes Outer::Inner, Outer, <model root>",
    ):
        M.finalize()


def test_dotted_string_annotation_resolves_nested_declaration() -> None:
    M = get_dsl_model("test.dotted")

    class View(M.Class):
        class Summary(M.Class):
            total: int

        class Column(M.Class):
            summary: Optional["View.Summary"] = None

        columns: List[Column]

    column = M.index.record_by_id("View::Column")
    assert column.fields[0].type.elem == NamedT(qname=M.type_of(View.Summary).qname)


def test_structural_hash_and_eq_fields_are_parsed() -> None:
    M = get_dsl_model("test.hash")

    class Key(M.Class):
        a: int
        b: str
        note: str

        def __hash__(self) -> int:
            return hash((self.a, self.b))

        def __eq__(self, other: "Key") -> bool:
            return (self.a, self.b) == (other.a, other.b)

    rec = M.index.record_by_id("Key")
    assert rec.hash_fields == ("a", "b")
    assert rec.eq_fields == ("a", "b")


def test_unsupported_eq_body_is_rejected() -> None:
    M = get_dsl_model("test.eq.bad")

    class Key(M.Class):
        a: int

        def __eq__(self, other: "Key") -> bool:
            return self.a < other.a

    with pytest.raises(DslModelError, match="unsupported __eq__ body"):
        M.finalize()


def test_unbound_binder_is_a_model_error() -> None:
    M = get_dsl_model("test.binder")

    class Holder(M.Class):
        items: List[int]

        __check__(
            cond=op_all(M.This["items"], "item", M.Iter("other") < 3), message="bad"
        )

    with pytest.raises(
        DslModelError,
        match=r"M.Iter\('other'\) refers to a binder that is not in scope; binders in scope: item",
    ):
        M.finalize()


def test_expression_in_boolean_context_raises() -> None:
    M = get_dsl_model("test.truthiness")
    with pytest.raises(TypeError, match="Python boolean context"):
        bool(M.This["a"] < 3)
