from pathlib import Path

import glom
import pytest
from hstd_py_lib.external_packages.rich_utils import render_rich
from hstd_py_unidata.model_diagnostics import DiagCode, DslTypeError
from hstd_py_unidata.model_dsl import (
    get_dsl_model,
)
from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    ExprNode,
    FieldDef,
    ListT,
    OpId,
    PrimKind,
    PrimT,
    QName,
    expr_tree_repr,
    is_integer_prim,
)


def test_list_type_check(stable_test_dir: Path):
    M = get_dsl_model("test.tc.model")

    class Entry(M.Class):
        eq_const_list_err: list[int] = M.Field(
            check=M.This == [1, 2, "str"], message="err"
        )

    with pytest.raises(DslTypeError, match="list init pattern mismatch") as ex:
        M.type_check()

    ex.value.get_diag1(DiagCode.LIST_ITEM_MISMATCH)


def test_const_ops(stable_test_dir: Path, subtests: pytest.Subtests) -> None:
    M = get_dsl_model("test.tc.model")

    class Entry(M.Class):
        eq_const_int: int = M.Field(check=M.This == 1, message="err")
        eq_const_list: list[int] = M.Field(check=M.This == [1, 2, 3], message="err")
        eq_const_list_err: list[int] = M.Field(
            check=M.This == [1, 2, "str"], message="err"
        )

    mapped = M.type_check(
        capture_databases=False,
        raise_on_type_error=False,
    )
    index = ModelIndex(mapped.type_check.model)

    def field(name: str) -> tuple[str, FieldDef, ExprNode]:
        value = index.field(QName(name="Entry"), name)
        assert value is not None
        assert len(value.checks) == 1
        ch0 = value.checks[0]
        assert isinstance(ch0.cond.typed_as, PrimT)

        _err = f"""
field {name} cond:
{render_rich(expr_tree_repr(ch0.cond))}
        """

        return _err, value, ch0.cond

    def subexpr(value: ExprNode, path) -> ExprNode:
        result = glom.glom(value, path)
        assert isinstance(result, ExprNode)
        return result

    with subtests.test("eq to const int"):
        _err, f_eq_const_int, c_eq_const_int = field("eq_const_int")
        assert c_eq_const_int.op == OpId.EQ, _err
        assert f_eq_const_int.name == "eq_const_int"

        assert len(c_eq_const_int.args) == 2, _err
        assert c_eq_const_int.args[0].op == OpId.THIS, _err
        assert c_eq_const_int.args[1].op == OpId.CONST_INT, _err
        assert isinstance(c_eq_const_int.args[1].typed_as, PrimT), _err
        assert c_eq_const_int.args[1].typed_as.prim == PrimKind.INT64, _err

    with subtests.test("eq to const int list"):
        _err, _, c_eq_const_list = field("eq_const_list")
        rhs = subexpr(c_eq_const_list, glom.T.args[1])
        assert rhs.op == OpId.LIST_INIT, _err
        assert isinstance(rhs.typed_as, ListT), _err
        assert isinstance(rhs.typed_as.elem, PrimT), _err

    with subtests.test("eq to const int list err"):
        # raise on type errors is disabled, but the partial typing is still evaluated
        _err, _, c_eq_const_list = field("eq_const_list_err")
        rhs = subexpr(c_eq_const_list, glom.T.args[1])
        assert rhs.op == OpId.LIST_INIT, _err
        assert is_integer_prim(subexpr(rhs, glom.T.args[0]).typed_as.prim), _err
        assert is_integer_prim(subexpr(rhs, glom.T.args[1]).typed_as.prim), _err
        assert not is_integer_prim(subexpr(rhs, glom.T.args[2]).typed_as.prim), _err
