set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD 23)

add_executable(code_forensics)

set_common_files(code_forensics)
set_target_output(code_forensics)
set_target_flags(code_forensics)

glob_add_sources2(code_forensics "${BASE}/scripts/cxx_repository/.*")

set(BUILD_TESTS OFF CACHE BOOL "Do not build tests in the subdirectory" FORCE)
add_subdirectory("${BASE}/thirdparty/libgit2" "${CMAKE_BINARY_DIR}/libgit2_build")

set(SQLCPP_DIR "${BASE}/thirdparty/SQLiteCpp")

add_subdirectory("${SQLCPP_DIR}" "${CMAKE_BINARY_DIR}/sqlitecpp_build")

target_link_libraries(code_forensics PUBLIC
    hstd
    perfetto
    range-v3
    libgit2package
    libgit2
    SQLiteCpp
    sqlite3
    pthread
    dl
)

target_include_directories(code_forensics PUBLIC
    "${BASE}/thirdparty/immer"
    "${BASE}/thirdparty/lager"
    "${DUCK_DIR}"
)

