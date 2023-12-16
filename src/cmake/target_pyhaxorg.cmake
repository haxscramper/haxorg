find_package(PythonLibs 3.11)

# Declare python wrapper module
pybind11_add_module(
    pyhaxorg
    "${BASE}/src/py_libs/pyhaxorg/pyhaxorg.cpp"
    "${BASE}/src/py_libs/py_type_casters.hpp"
    "${BASE}/src/py_libs/py_type_casters.cpp"
    "${BASE}/src/py_libs/pyhaxorg/pyhaxorg_manual_impl.cpp"
    "${BASE}/src/py_libs/pyhaxorg/pyhaxorg_manual_impl.hpp"
)

set_common_files(pyhaxorg)
set_target_output(pyhaxorg)
set_target_flags(pyhaxorg)

set_target_properties(pyhaxorg PROPERTIES
    OUTPUT_NAME "pyhaxorg"
    SUFFIX ".so"
)

target_include_directories(
    pyhaxorg
    PUBLIC
    "${BASE}"
    "${BASE}/src/py_libs"
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(pyhaxorg PRIVATE hstd ${PYTHON_LIBRARIES} ubsan haxorg)
target_compile_options(pyhaxorg PRIVATE -shared-libasan)
