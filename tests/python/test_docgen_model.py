import pydantic
import py_repository.gen_documentation as gen
from pydantic import BaseModel
from py_scriptutils.rich_utils import render_rich_pprint, render_rich
import py_scriptutils.json_utils as ju
from beartype.typing import Tuple, Optional
from pathlib import Path
from tempfile import TemporaryDirectory


def dbg(map: BaseModel) -> str:
    return render_rich_pprint(map.model_dump(), width=200, color=False)


def dbg_tree(tree: gen.tree_sitter.Tree) -> str:
    return render_rich(gen.tree_repr(tree), color=False) if tree else ""


def dbg_parse(map: BaseModel, tree: gen.tree_sitter.Tree) -> str:
    return dbg(map) + "\n\n" + dbg_tree(tree)


def print_parse(value: str) -> str:
    return print(render_rich(gen.tree_repr(gen.parse_cxx(value))))


def parse(code: str) -> Tuple[gen.DocCodeCxxFile, gen.tree_sitter.Tree]:
    tree = gen.parse_cxx(code)
    try:
        with TemporaryDirectory() as tmp_dir:
            dir = Path(tmp_dir)
            dir.joinpath("file.hpp").write_text(code)
            return (gen.convert_cxx_tree(tree, dir, dir.joinpath("file.hpp")), tree)

    except Exception as e:
        print_parse(code)
        raise e from None


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


def test_template_type():
    code = """
std::vector<int> get_value(std::unordered_map<A<B<C>>, Q::C::D::E::Z> arg) {}
"""
    file, tree = parse(code)
    func = file.Content[0]
    assert isinstance(func, gen.DocCxxFunction)
    assert_submodel(
        func.ReturnTy,
        dict(name="vector", Spaces=[dict(name="std")], Parameters=[dict(name="int")]),
        tree)

    assert_submodel(
        func.Arguments[0].Type,
        dict(name="unordered_map",
             Spaces=[dict(name="std")],
             Parameters=[
                 dict(name="A", Parameters=[dict(name="B", Parameters=[dict(name="C")])]),
                 dict(name="Z",
                      Spaces=[
                          dict(name="E"),
                          dict(name="D"),
                          dict(name="C"),
                          dict(name="Q"),
                      ]),
             ]),
        tree,
    )


def test_code_1():
    code = """
        VisitScope(Exporter<V, R>* exporter, VisitEvent event)
            : exp(exporter), event(event) {
            event.level   = exp->visitDepth;
            event.isStart = true;
            exp->visitEvent(event);
            ++exp->visitDepth;
        }
    """

    file, tree = parse(code)


def test_code_2():
    code = """
    V**** _this() { return static_cast<V*>(this); }
    """

    file, tree = parse(code)

    func = file.Content[0]
    assert isinstance(func, gen.DocCxxFunction)
    assert_submodel(func.ReturnTy, dict(name="V", ptrCount=4), tree)


def test_implicit_conversion_operator():
    code = """
    operator int() {}
    """

    file, tree = parse(code)
    func = file.Content[0]
    assert isinstance(func, gen.DocCxxFunction)

    assert_submodel(
        func,
        dict(
            ReturnTy=dict(name="int"),
            Kind="ImplicitConvertOperator",
        ),
        tree,
    )


def test_refl_annotation():
    code = """
    enum class [[refl]] Kind
    {
        Field, ///< Visiting named field
        Index, ///< Visiting indexed subnode.
        Key,   ///< Visiting Str->Node table
    };
    """

    file, tree = parse(code)


def test_pointer_functions():
    code = """
    int*** result(int const** value, char const& entry) {}
    """

    file, tree = parse(code)
    func = file.Content[0]
    assert isinstance(func, gen.DocCxxFunction)
    assert func.Name == "result", dbg_tree(tree)
    assert func.ReturnTy.ptrCount == 3
    assert len(func.Arguments) == 2, dbg_tree(tree)
    assert_submodel(
        func.Arguments[0],
        dict(
            Name="value",
            Type=dict(
                ptrCount=2,
                isConst=True,
                name="int",
            ),
        ),
        tree,
    )

    assert_submodel(
        func.Arguments[1],
        dict(
            Name="entry",
            Type=dict(
                RefKind="LValue",
                isConst=True,
                name="char",
            ),
        ),
        tree,
    )
