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

target_link_libraries(pyhaxorg PRIVATE hstd ${PYTHON_LIBRARIES} ubsan haxorg perfetto)
target_compile_options(pyhaxorg PRIVATE -shared-libasan)

add_executable(
    pyhaxorg_test_main
    "${BASE}/src/py_libs/pyhaxorg/pyhaxorg_manual_impl.cpp"
    "${BASE}/src/py_libs/pyhaxorg/pyhaxorg_test_main.cpp"
)

set_common_files(pyhaxorg_test_main)
set_target_output(pyhaxorg_test_main)
set_target_flags(pyhaxorg_test_main)

target_include_directories(
    pyhaxorg_test_main
    PUBLIC
    "${BASE}"
    "${BASE}/src/py_libs"
    "${DEPS_DIR}/pybind11/include"
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(pyhaxorg_test_main PRIVATE hstd ${PYTHON_LIBRARIES} ubsan haxorg perfetto)
target_compile_options(pyhaxorg_test_main PRIVATE -shared-libasan)
