add_executable(code_forensics)

set_common_files(code_forensics)
set_target_output(code_forensics)
set_target_flags(code_forensics)

glob_add_sources2(code_forensics "${BASE}/scripts/cxx_repository/.*")

target_link_libraries(code_forensics PUBLIC
    hstd
    perfetto::perfetto
    CONAN_PKG::range-v3
)
