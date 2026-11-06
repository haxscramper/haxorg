from pathlib import Path

import glom
import pytest
from hstd_py_unidata.model_dsl import (
    get_dsl_model,
)
from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    ExprNode,
    FieldDef,
    OpId,
    PrimKind,
    PrimT,
    QName,
)


def test_const_ops(stable_test_dir: Path, subtests: pytest.Subtests) -> None:
    M = get_dsl_model("test.tc.const_ops")

    class Entry(M.Class):
        eq_const_int: int = M.Field(check=M.This == 1, message="err")
        eq_const_list: list[int] = M.Field(check=M.This == [1, 2, 3], message="err")

    mapped = M.type_check(capture_databases=True)
    index = ModelIndex(mapped.type_check.model)

    def field(name: str) -> tuple[FieldDef, ExprNode]:
        value = index.field(QName(name="Entry"), "eq_const_int")
        assert value is not None
        assert len(value.checks) == 1
        ch0 = value.checks[0]
        assert isinstance(ch0.cond.typed_as, PrimT)
        return value, ch0.cond

    def subexpr(value: ExprNode, path) -> ExprNode:
        result = glom.glom(value, path)
        assert isinstance(result, ExprNode)
        return result

    with subtests.test("eq to const int"):
        f_eq_const_int, c_eq_const_int = field("eq_const_int")
        assert c_eq_const_int.op == OpId.EQ
        assert f_eq_const_int.name == "eq_const_int"

        assert len(c_eq_const_int.args) == 2
        assert c_eq_const_int.args[0].op == OpId.THIS
        assert c_eq_const_int.args[1].op == OpId.CONST_INT
        assert isinstance(c_eq_const_int.args[1].typed_as, PrimT)
        assert c_eq_const_int.args[1].typed_as.prim == PrimKind.INT64

    with subtests.test("eq to const int list"):
        f_eq_const_list, c_eq_const_list = field("eq_const_list")
        rhs = subexpr(c_eq_const_list, glom.T[1])
