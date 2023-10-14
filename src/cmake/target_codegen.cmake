pybind11_add_module(
    py_textlayout
    "${BASE}/src/py_libs/py_textlayout/py_textlayout.cpp"
)

set_common_files(py_textlayout)
set_target_output(py_textlayout)
set_target_flags(py_textlayout)


set_target_properties(py_textlayout PROPERTIES
    OUTPUT_NAME "py_textlayout"
    SUFFIX ".so"
)

target_include_directories(
    py_textlayout
    PUBLIC
    "${BASE}"
    "${BASE}/src/py_libs"
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(py_textlayout PRIVATE hstd ${PYTHON_LIBRARIES} ubsan)
target_compile_options(py_textlayout PRIVATE -shared-libasan)
