import pytest
import test_example_dia as test_example_dia
from beartype.typing import List
from hstd_py_unidata.model_dsl import GenConfig, __check__, get_dsl_model, op_all
from hstd_py_unidata.model_eval import errors_only
from hstd_py_unidata.model_gen import GenerationError


@pytest.mark.parametrize("seed", range(5))
def test_generated_diagrams_are_valid(seed: int) -> None:
    value = test_example_dia.generate_diagram(seed)
    assert (
        errors_only(test_example_dia.M.validate(test_example_dia.Diagram, value)) == []
    )


def test_generation_is_deterministic_for_a_seed() -> None:
    first = test_example_dia.generate_diagram(3)
    second = test_example_dia.generate_diagram(3)
    assert test_example_dia.M.encode(
        test_example_dia.Diagram, first
    ) == test_example_dia.M.encode(test_example_dia.Diagram, second)


def test_generation_repairs_failing_checks_without_overrides() -> None:
    M = get_dsl_model("test.gen.repair")

    class Bounded(M.Class):
        values: List[int]

        __check__(
            cond=op_all(
                M.This["values"],
                "value",
                (0 <= M.Iter("value")) & (M.Iter("value") < 5),
            ),
            message="range",
        )

    for seed in range(5):
        value = M.generate(Bounded, GenConfig(seed=seed))
        assert M.validate(Bounded, value) == []


def test_missing_external_generator_is_reported() -> None:
    Ext = get_dsl_model("test.gen.external")
    M = get_dsl_model("test.gen.uses.external")

    class Holder(M.Class):
        payload: Ext._T["Payload"]

    with pytest.raises(GenerationError, match="@test.gen.external:Payload"):
        M.generate(Holder)


def test_unsatisfiable_check_is_reported() -> None:
    M = get_dsl_model("test.gen.impossible")

    class Impossible(M.Class):
        value: int

        __check__(
            id="never", cond=M.This["value"] < M.This["value"], message="never holds"
        )

    with pytest.raises(GenerationError, match="'never' failed"):
        M.generate(Impossible, GenConfig(repair_attempts=5, restarts=2))
