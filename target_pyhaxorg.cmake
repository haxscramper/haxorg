find_package(PythonLibs 3.11)
find_package(pybind11 CONFIG)


# Check if plugin has changed and consider it as a dependency when
# rebuilding the python wrappers. This helps keeping reflection data
# up to date if the plugin logic has changed
add_custom_command(
  OUTPUT "${CMAKE_BINARY_DIR}/binary.stamp"
  COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_BINARY_DIR}/binary.stamp"
  DEPENDS "${BASE}/scripts/code/lib/libreflection_plugin.so"
  COMMENT "Checking if external binary has changed in ${CMAKE_BINARY_DIR}/binary.stamp ..."
)

add_custom_target(check_plugin ALL
  DEPENDS "${CMAKE_BINARY_DIR}/binary.stamp"
)

# List of flags is long, so assembling it in a coule of steps
set(PLUGIN_FLAGS_LIST
    "-Xclang" "-add-plugin"
    "-Xclang" "refl-plugin"
    "-fplugin=${BASE}/scripts/code/lib/libreflection_plugin.so"
   " -Xclang" "-plugin-arg-refl-plugin" "-Xclang" "out=/tmp/result.pb"
)

string(JOIN " " PLUGIN_FLAGS ${PLUGIN_FLAGS_LIST})

# Declare python wrapper module
pybind11_add_module(
    pyhaxorg
    "${BASE}/src/py_libs/pyhaxorg/pyhaxorg.cpp"
    "${BASE}/src/py_libs/pyhaxorg/pyhaxorg_manual_impl.cpp"
)

# Here, only once file needs to be considered and only one set
# of reflection metadata, so assigning all parameters directly
# to a single file.
set_source_files_properties(
    "${BASE}/src/py_libs/pyhaxorg/pyhaxorg.cpp"
    PROPERTIES COMPILE_FLAGS "${PLUGIN_FLAGS}"
)

set_common_files(pyhaxorg)
set_target_output(pyhaxorg)
set_target_flags(pyhaxorg)

add_dependencies(pyhaxorg check_plugin)

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

target_link_libraries(pyhaxorg PRIVATE hstd ${PYTHON_LIBRARIES} ubsan haxorg)
target_compile_options(pyhaxorg PRIVATE -shared-libasan)
