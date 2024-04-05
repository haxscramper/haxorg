import pydantic
import py_repository.gen_documentation as gen
from pydantic import BaseModel
from py_scriptutils.rich_utils import render_rich_pprint, render_rich
import py_scriptutils.json_utils as ju
from beartype.typing import Tuple, Optional


def dbg(map: BaseModel) -> str:
    return render_rich_pprint(map.model_dump(), width=200, color=False)


def dbg_parse(map: BaseModel, tree: gen.tree_sitter.Tree) -> str:
    return dbg(map) + ("\n\n" +
                       render_rich(gen.tree_repr(tree), color=False) if tree else "")


def print_parse(value: str) -> str:
    return print(render_rich(gen.tree_repr(gen.parse_cxx(value))))


def parse(code: str) -> Tuple[gen.DocCxxFile, gen.tree_sitter.Tree]:
    tree = gen.parse_cxx(code)
    return (gen.convert_cxx_tree(tree), tree)


def assert_submodel(model: BaseModel,
                    subset: ju.Json,
                    tree: Optional[gen.tree_sitter.Tree] = None):
    ju.assert_subset(model.model_dump(), subset=subset, message=dbg_parse(model, tree))


def test_structure_extraction_name():
    file, tree = parse("struct A {}; ")
    record = file.Content[0]
    assert isinstance(record, gen.DocCxxRecord)
    assert_submodel(record.Name, dict(name="A", Spaces=[], Parameters=[]), tree)


def test_structure_extraction_fields():
    file, tree = parse("struct A { int field; };")
    record = file.Content[0]
    assert isinstance(record, gen.DocCxxRecord)
    assert len(record.Nested) == 1, dbg(record)
    assert_submodel(record.Nested[0], dict(Name="field", Type=dict(name="int")), tree)


def test_qualified_identifier_function_parse():
    file, tree = parse("B::A get(int arg = 12) {}")
    func = file.Content[0]
    assert isinstance(func, gen.DocCxxFunction)
    assert_submodel(func.ReturnTy, dict(name="A", Spaces=[dict(name="B")]), tree)
    assert len(func.Arguments) == 1, dbg_parse(func, tree)
    assert_submodel(func.Arguments[0], dict(Name="arg", Value="12", Type=dict(name="int")),
                    tree )
