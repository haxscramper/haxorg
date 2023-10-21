add_executable(tests_hstd)
set_common_files(tests_hstd)
set_target_output(tests_hstd)
set_target_flags(tests_hstd)
glob_add_sources2(tests_hstd "${BASE}/tests/hstd/.*")

target_link_libraries(
    tests_hstd PUBLIC
    gtest
    hstd
)

include_directories("${BASE}/deps/fuzztest")

link_fuzztest(tests_hstd)
