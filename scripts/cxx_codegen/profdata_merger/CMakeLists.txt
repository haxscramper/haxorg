add_executable(profdata_merger profdata_merger.cpp)
llvm_map_components_to_libnames(profdata_merger_llvm_libs support core irreader profiledata coverage)

set(SQLCPP_DIR "${BASE}/thirdparty/SQLiteCpp")
add_subdirectory("${SQLCPP_DIR}" "${CMAKE_BINARY_DIR}/sqlitecpp_build")

message(STATUS ${profdata_merger_llvm_libs})


add_library(perfetto STATIC "${DEPS_DIR}/perfetto/sdk/perfetto.cc")
target_include_directories(perfetto PUBLIC "${DEPS_DIR}/perfetto/sdk")

target_link_libraries(profdata_merger
    ${profdata_merger_llvm_libs}
    SQLiteCpp
    sqlite3
    perfetto
    tbb
)

target_include_directories(profdata_merger PUBLIC "${BASE}/src" "${BASE}/thirdparty/abseil-cpp")
set_target_properties(profdata_merger PROPERTIES CXX_STANDARD 20)
