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
    code = """
    /*!STRUCT-COMMENT*/
    struct A {}; 
    """

    file, tree = parse(code)
    record = file.Content[0]
    assert isinstance(record, gen.DocCxxRecord)
    assert_submodel(record.Name, dict(name="A", Spaces=[], Parameters=[]), tree)
    assert record.Doc, dbg_parse(file, tree)
    assert record.Doc.Text == "STRUCT-COMMENT", dbg_parse(file, tree)


def test_structure_extraction_fields():
    code = """
    /*!STRUCT-COMMENT*/
    struct A { 
        /*!FIELD-COMMENT-1*/
        int field; 

        /// FIELD-COMMENT-2.1
        int field1 = value; ///< FIELD-COMMENT-2.2
    };"""

    file, tree = parse(code)
    record = file.Content[0]
    assert isinstance(record, gen.DocCxxRecord)
    assert len(record.Nested) == 2, dbg(record)
    field1 = record.Nested[0]
    assert_submodel(field1, dict(Name="field", Type=dict(name="int")), tree)

    assert field1.Doc, dbg_parse(file, tree)
    assert field1.Doc.Text == "FIELD-COMMENT-1", dbg_parse(file, tree)

    field2 = record.Nested[1]
    assert_submodel(field2, dict(Name="field1", Type=dict(name="int"), Value="value"),
                    tree)

    assert field2.Doc, dbg_parse(file, tree)
    assert field2.Doc.Text == "FIELD-COMMENT-2.1\nFIELD-COMMENT-2.2", dbg_parse(
        file, tree)


def test_qualified_identifier_function_parse():
    code = """
/*!FUNCTION-COMMENT*/
B::A get(
    int arg = 12, ///< ARG-1-COMMENT
    /// ARG-2-COMMENT
    int arg1 = 22
    ) {}
"""

    file, tree = parse(code)

    func = file.Content[0]
    assert isinstance(func, gen.DocCxxFunction)
    assert_submodel(func.ReturnTy, dict(name="A", Spaces=[dict(name="B")]), tree)
    assert len(func.Arguments) == 2, dbg_parse(func, tree)
    arg1 = func.Arguments[0]
    arg2 = func.Arguments[1]
    assert_submodel(
        arg1,
        dict(Name="arg",
             Value="12",
             Type=dict(name="int"),
             Doc=dict(Text="ARG-1-COMMENT")),
        tree,
    )

    assert_submodel(
        arg2,
        dict(Name="arg1",
             Value="22",
             Type=dict(name="int"),
             Doc=dict(Text="ARG-2-COMMENT")),
        tree,
    )

    assert func.Doc, dbg_parse(file, tree)
    assert func.Doc.Text == "FUNCTION-COMMENT", dbg_parse(file, tree)
