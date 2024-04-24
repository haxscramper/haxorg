import pydantic
import py_repository.gen_documentation_cxx as cxx
import py_repository.gen_documentation_python as py
from pydantic import BaseModel
from py_scriptutils.rich_utils import render_rich_pprint, render_rich
import py_scriptutils.json_utils as ju
from beartype.typing import Tuple, Optional
from pathlib import Path
from tempfile import TemporaryDirectory
import tree_sitter
from py_repository.gen_documentation_utils import tree_repr
from beartype import beartype


def dbg(map: BaseModel) -> str:
    return render_rich_pprint(map and map.model_dump(), width=200, color=False)


def dbg_tree(tree: tree_sitter.Tree) -> str:
    return render_rich(tree_repr(tree), color=False) if tree else ""


def dbg_parse(map: BaseModel, tree: tree_sitter.Tree) -> str:
    return dbg(map) + "\n\n" + dbg_tree(tree)


@beartype
def render_parse(tree: tree_sitter.Tree) -> str:
    return render_rich(tree_repr(tree))


def parse_cxx(code: str) -> Tuple[cxx.DocCodeCxxFile, tree_sitter.Tree]:
    tree = cxx.parse_cxx(code)
    try:
        with TemporaryDirectory() as tmp_dir:
            dir = Path(tmp_dir)
            dir.joinpath("file.hpp").write_text(code)
            return (cxx.convert_cxx_tree(
                tree,
                dir,
                dir.joinpath("file.hpp"),
                coverage_session=None,
            ), tree)

    except Exception as e:
        e.add_note(render_parse(tree))
        raise e from None


def parse_py(code: str) -> Tuple[py.DocCodePyFile, tree_sitter.Tree]:
    tree = py.parse_py(code)
    try:
        with TemporaryDirectory() as tmp_dir:
            dir = Path(tmp_dir)
            dir.joinpath("file.py").write_text(code)
            return (py.convert_py_tree(
                tree,
                dir,
                dir.joinpath("file.py"),
                py_coverage_session=None,
            ), tree)

    except Exception as e:
        e.add_note(render_parse(tree))
        raise e from None


def assert_submodel(model: BaseModel,
                    subset: ju.Json,
                    tree: Optional[tree_sitter.Tree] = None):
    ju.assert_subset(
        model and model.model_dump(),
        subset=subset,
        message=dbg_parse(model, tree),
    )


def test_structure_extraction_name():
    code = """
    /*!STRUCT-COMMENT*/
    struct A {}; 
    """

    file, tree = parse_cxx(code)
    record = file.Content[0]
    assert isinstance(record, cxx.DocCxxRecord)
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

    file, tree = parse_cxx(code)
    record = file.Content[0]
    assert isinstance(record, cxx.DocCxxRecord)
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

    file, tree = parse_cxx(code)

    func = file.Content[0]
    assert isinstance(func, cxx.DocCxxFunction)
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
    file, tree = parse_cxx(code)
    func = file.Content[0]
    assert isinstance(func, cxx.DocCxxFunction)
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

    file, tree = parse_cxx(code)


def test_code_2():
    code = """
    V**** _this() { return static_cast<V*>(this); }
    """

    file, tree = parse_cxx(code)

    func = file.Content[0]
    assert isinstance(func, cxx.DocCxxFunction)
    assert_submodel(func.ReturnTy, dict(name="V", ptrCount=4), tree)


def test_implicit_conversion_operator():
    code = """
    operator int() {}
    """

    file, tree = parse_cxx(code)
    func = file.Content[0]
    assert isinstance(func, cxx.DocCxxFunction)

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

    file, tree = parse_cxx(code)


def test_pointer_functions():
    code = """
    int*** result(int const** value, char const& entry) {}
    """

    file, tree = parse_cxx(code)
    func = file.Content[0]
    assert isinstance(func, cxx.DocCxxFunction)
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


def test_py_function():
    code = """
    def whatever(arg: List[int], arg2: List[Dict[int, float]] = []) -> int:
        return 123123123123
    """

    file, tree = parse_py(code)
    func = file.Content[0]
    assert isinstance(func, py.DocPyFunction)
    assert func.Name == "whatever", dbg_tree(tree)
    assert_submodel(func.ReturnTy, dict(Name="int"), tree)

    assert len(func.Arguments) == 2, dbg_tree(tree)
    assert_submodel(
        func.Arguments[0],
        dict(Name="arg", Type=dict(Name="List", Parameters=[dict(Name="int")])),
        tree,
    )

    assert_submodel(
        func.Arguments[1],
        dict(
            Name="arg2",
            Type=dict(Name="List",
                      Parameters=[
                          dict(Name="Dict",
                               Parameters=[dict(Name="int"),
                                           dict(Name="float")])
                      ]),
            Default="[]",
        ),
        tree,
    )


def test_class_definition():
    code = """
    @beartype
    @dataclass
    class AstbuilderBase:
        "Docstring"
        b: TextLayout
        context_stack: List[Union[AstLineCtx, AstStackCtx,
                                AstIndentCtx]] = field(default_factory=list)
        last_result: Optional[BlockId] = None

        def __repr__(self):
            # Beartype cannot run default repr because it fails with missing context state value.
            return "astbuilder-base"

        def Spatial(self, stack: bool) -> int:
            if stack:
                return self.Stack()

            else:
                return self.Line()
    """

    file, tree = parse_py(code)
    cls = file.Content[0]
    assert isinstance(cls, py.DocPyClass)
    assert len(cls.getNested(py.DocPyFunction)) == 2, dbg_tree(tree)
    assert len(cls.getNested(py.DocPyIdent)) == 3, dbg_tree(tree)
    assert cls.Doc, dbg_tree(tree)
    assert cls.Doc.Text == "Docstring", dbg_tree(tree)
    b = cls.getNested(py.DocPyIdent)[0]
    context_stack = cls.getNested(py.DocPyIdent)[1]
    last_result = cls.getNested(py.DocPyIdent)[2]

    assert_submodel(b, dict(Name="b", Type=dict(Name="TextLayout")), tree)
    assert_submodel(
        context_stack,
        dict(
            Name="context_stack",
            Type=dict(Name="List", Parameters=[dict(Name="Union")]),
        ),
        tree,
    )

    repr = cls.getNested(py.DocPyFunction)[0]
    Spatial = cls.getNested(py.DocPyFunction)[1]

    assert_submodel(repr, dict(Name="__repr__"), tree)
    assert_submodel(Spatial, dict(Name="Spatial", ReturnTy=dict(Name="int")), tree)
