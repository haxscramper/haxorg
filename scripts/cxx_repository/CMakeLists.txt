set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD 23)

add_executable(code_forensics
    git_ir.hpp
    repo_graph.hpp
    git_interface.hpp
    repo_graph.cpp)

set_common_files(code_forensics)
set_target_output(code_forensics)
set_target_flags(code_forensics)

glob_add_sources2(code_forensics "${BASE}/scripts/cxx_repository/.*")

add_subdirectory("${BASE}/thirdparty/libgit2" "${CMAKE_BINARY_DIR}/libgit2_build")

target_link_libraries(code_forensics PUBLIC
    hstd
    perfetto::perfetto
    CONAN_PKG::range-v3
    libgit2package
)

target_include_directories(code_forensics PUBLIC
    "${BASE}/thirdparty/immer"
    "${BASE}/thirdparty/lager"
)

