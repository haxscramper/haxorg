find_package(PythonLibs 3.11)
find_package(pybind11 CONFIG)

pybind11_add_module(
    pyhaxorg
    "${BASE}/src/py_libs/pyhaxorg/pyhaxorg.cpp"
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
    ${PYTHON_INCLUDE_DIRS}
)

if (${USE_PCH})
    target_precompile_headers(
        pyhaxorg
        PRIVATE
        <sem/SemConvert.hpp>
        <parse/OrgParser.hpp>
        <parse/OrgTokenizer.hpp>
        <parse/OrgTypes.hpp>
    )
endif()

target_link_libraries(pyhaxorg PRIVATE hstd ${PYTHON_LIBRARIES} ubsan)
target_compile_options(pyhaxorg PRIVATE -shared-libasan)
