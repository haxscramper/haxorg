import pytest

from tests.python.conftest import stable_test_dir
from py_codegen import astbuilder_nim, astbuilder_embind, astbuilder_py, astbuilder_nanobind
from pathlib import Path
from beartype.typing import cast


@pytest.mark.test_release
def test_structure_wrapping(stable_test_dir: Path):
    from tests.python.refl import refl_test_driver

    wraps = refl_test_driver.get_all_code(
        {"header.hpp": "struct [[refl]] Defined {};"},
        stable_test_dir=stable_test_dir,
    )

    struct_nim = cast(astbuilder_nim.ObjectParams, wraps.getNimEntries("Defined")[0])

    assert struct_nim
    assert struct_nim.Name == "Defined"

    struct_py = cast(astbuilder_nanobind.NbClass, wraps.getPythonEntries("Defined")[0])

    assert struct_py
    assert struct_py.getPyName() == "Defined"

    struct_em = cast(astbuilder_embind.WasmClass, wraps.getWasmEntries("Defined")[0])

    assert struct_em
    assert struct_em.getWasmName() == "Defined"


@pytest.mark.test_release
def test_function_wrapping(stable_test_dir: Path):
    from tests.python.refl import refl_test_driver
    wraps = refl_test_driver.get_all_code("[[refl]] int defined();",
                                          stable_test_dir=stable_test_dir)

    fun_nim = cast(astbuilder_nim.FunctionParams, wraps.getNimEntries("defined")[0])

    assert fun_nim
    assert fun_nim.Name == "defined"

    fun_py = cast(astbuilder_nanobind.NbFunction, wraps.getPythonEntries("defined")[0])

    assert fun_py
    assert fun_py.PyName == "defined"

    fun_em = cast(astbuilder_embind.WasmFunction, wraps.getWasmEntries("defined")[0])

    assert fun_em
    assert fun_em.getWasmName() == "defined"


@pytest.mark.test_release
def test_function_with_arguments(stable_test_dir: Path):
    from tests.python.refl import refl_test_driver
    wraps = refl_test_driver.get_all_code(
        "[[refl]] void func_args(int a, float b);",
        stable_test_dir=stable_test_dir,
    )

    fun_nim = cast(astbuilder_nim.FunctionParams, wraps.getNimEntries("func_args")[0])
    assert fun_nim
    assert fun_nim.Name == "func_args"
    assert len(fun_nim.Arguments) == 2

    fun_py = cast(astbuilder_nanobind.NbFunction, wraps.getPythonEntries("func_args")[0])
    assert fun_py
    assert fun_py.PyName == "func_args"
    assert len(fun_py.Func.Args) == 2

    fun_em = cast(astbuilder_embind.WasmFunction, wraps.getWasmEntries("func_args")[0])
    assert fun_em
    assert fun_em.getWasmName() == "func_args"


@pytest.mark.test_release
def test_function_with_stdlib_return(stable_test_dir: Path):
    from tests.python.refl import refl_test_driver
    wraps = refl_test_driver.get_all_code(
        {"header.hpp": "#include <string>\n[[refl]] std::string get_string();"},
        stable_test_dir=stable_test_dir,
    )

    fun_nim = cast(astbuilder_nim.FunctionParams, wraps.getNimEntries("get_string")[0])
    assert fun_nim
    assert fun_nim.Name == "get_string"

    fun_py = cast(astbuilder_nanobind.NbFunction, wraps.getPythonEntries("get_string")[0])
    assert fun_py
    assert fun_py.PyName == "get_string"

    fun_em = cast(astbuilder_embind.WasmFunction, wraps.getWasmEntries("get_string")[0])
    assert fun_em
    assert fun_em.getWasmName() == "get_string"


@pytest.mark.test_release
def test_function_with_complex_stdlib_arg(stable_test_dir: Path):
    from tests.python.refl import refl_test_driver
    wraps = refl_test_driver.get_all_code(
        {
            "header.hpp":
                "#include <map>\n#include <string>\n[[refl]] void complex_arg(std::map<int, std::string> m);"
        },
        stable_test_dir=stable_test_dir,
    )

    fun_nim = cast(astbuilder_nim.FunctionParams, wraps.getNimEntries("complex_arg")[0])
    assert fun_nim
    assert fun_nim.Name == "complex_arg"

    fun_py = cast(astbuilder_nanobind.NbFunction,
                  wraps.getPythonEntries("complex_arg")[0])
    assert fun_py
    assert fun_py.PyName == "complex_arg"

    fun_em = cast(astbuilder_embind.WasmFunction, wraps.getWasmEntries("complex_arg")[0])
    assert fun_em
    assert fun_em.getWasmName() == "complex_arg"


@pytest.mark.test_release
def test_function_with_nested_vector_arg(stable_test_dir: Path):
    from tests.python.refl import refl_test_driver
    wraps = refl_test_driver.get_all_code(
        {
            "header.hpp":
                "#include <vector>\n[[refl]] void nested_vector(std::vector<std::vector<std::vector<int>>> v);"
        },
        stable_test_dir=stable_test_dir,
    )

    fun_nim = cast(astbuilder_nim.FunctionParams, wraps.getNimEntries("nested_vector")[0])
    assert fun_nim
    assert fun_nim.Name == "nested_vector"

    fun_py = cast(astbuilder_nanobind.NbFunction,
                  wraps.getPythonEntries("nested_vector")[0])
    assert fun_py
    assert fun_py.PyName == "nested_vector"

    fun_em = cast(astbuilder_embind.WasmFunction,
                  wraps.getWasmEntries("nested_vector")[0])
    assert fun_em
    assert fun_em.getWasmName() == "nested_vector"


@pytest.mark.test_release
def test_structure_with_single_field(stable_test_dir: Path):
    from tests.python.refl import refl_test_driver
    wraps = refl_test_driver.get_all_code(
        {"header.hpp": "struct [[refl]] SingleField { [[refl]] int field; };"},
        stable_test_dir=stable_test_dir,
    )

    struct_nim = cast(astbuilder_nim.ObjectParams, wraps.getNimEntries("SingleField")[0])
    assert struct_nim
    assert len(struct_nim.Fields) == 1
    assert struct_nim.Fields[0].Name == "field"

    struct_py = cast(astbuilder_nanobind.NbClass,
                     wraps.getPythonEntries("SingleField")[0])
    assert struct_py
    assert any(f.Field.Name == "field" for f in struct_py.Fields)

    struct_em = cast(astbuilder_embind.WasmClass, wraps.getWasmEntries("SingleField")[0])
    assert struct_em
    assert any(
        f.Field.Name == "field" for f in
        [astbuilder_embind.WasmField(f, struct_em.conf) for f in struct_em.Record.Fields])


@pytest.mark.test_release
def test_structure_with_multiple_fields(stable_test_dir: Path):
    from tests.python.refl import refl_test_driver
    wraps = refl_test_driver.get_all_code(
        {
            "header.hpp":
                """
        struct [[refl]] MultiField {
            [[refl]] int field1;
            [[refl]] float field2;
        };
        """
        },
        stable_test_dir=stable_test_dir,
    )

    struct_nim = cast(astbuilder_nim.ObjectParams, wraps.getNimEntries("MultiField")[0])
    assert struct_nim
    assert len(struct_nim.Fields) == 2

    struct_py = cast(astbuilder_nanobind.NbClass, wraps.getPythonEntries("MultiField")[0])
    assert struct_py
    assert len(struct_py.Fields) == 2

    struct_em = cast(astbuilder_embind.WasmClass, wraps.getWasmEntries("MultiField")[0])
    assert struct_em
    assert len(struct_em.Record.Fields) == 2


@pytest.mark.test_release
def test_structure_with_methods(stable_test_dir: Path):
    from tests.python.refl import refl_test_driver
    wraps = refl_test_driver.get_all_code(
        {"header.hpp": "struct [[refl]] WithMethods { [[refl]] void method(); };"},
        stable_test_dir=stable_test_dir,
    )

    struct_nim = cast(astbuilder_nim.ObjectParams, wraps.getNimEntries("WithMethods")[0])
    assert struct_nim

    method_nim = cast(astbuilder_nim.FunctionParams, wraps.getNimEntries("`method`")[0])
    assert method_nim

    struct_py = cast(astbuilder_nanobind.NbClass,
                     wraps.getPythonEntries("WithMethods")[0])
    assert struct_py
    assert any(m.PyName == "method" for m in struct_py.Methods)

    struct_em = cast(astbuilder_embind.WasmClass, wraps.getWasmEntries("WithMethods")[0])
    assert struct_em
    assert any(m.Name == "method" for m in struct_em.Record.Methods)


@pytest.mark.test_release
def test_structure_with_static_methods(stable_test_dir: Path):
    from tests.python.refl import refl_test_driver
    wraps = refl_test_driver.get_all_code(
        {"header.hpp": "struct [[refl]] WithStatic { [[refl]] static void meth(); };"},
        stable_test_dir=stable_test_dir,
    )

    method_nim = cast(astbuilder_nim.FunctionParams, wraps.getNimEntries("meth")[0])
    assert method_nim

    struct_py = cast(astbuilder_nanobind.NbClass, wraps.getPythonEntries("WithStatic")[0])
    assert struct_py
    method_py = cast(astbuilder_nanobind.NbMethod,
                     wraps.getPythonEntries("methStatic")[0])
    assert method_py

    struct_em = cast(astbuilder_embind.WasmClass, wraps.getWasmEntries("WithStatic")[0])
    assert struct_em
    method_em = cast(astbuilder_embind.WasmMethod, wraps.getWasmEntries("meth")[0])
    assert method_em
