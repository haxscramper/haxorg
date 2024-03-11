pybind11_add_module(
    py_textlayout_cpp
    "${BASE}/src/py_libs/py_textlayout/py_textlayout.cpp"
)

set_common_files(py_textlayout_cpp)
set_target_output(py_textlayout_cpp)
set_target_flags(py_textlayout_cpp)


set_target_properties(py_textlayout_cpp PROPERTIES
    OUTPUT_NAME "py_textlayout_cpp"
    SUFFIX ".so"
)

target_include_directories(
    py_textlayout_cpp
    PUBLIC
    "${BASE}"
    "${BASE}/src/py_libs"
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(py_textlayout_cpp PRIVATE hstd ${PYTHON_LIBRARIES} ubsan)
