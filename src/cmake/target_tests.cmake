add_executable(tests)
target_link_libraries(tests PUBLIC haxorg)
set_common_files(tests)
set_target_output(tests)
set_target_flags(tests)
glob_add_sources2(tests "${BASE}/tests/.*")
target_link_libraries(tests PUBLIC fmt::fmt yaml-cpp::yaml-cpp haxorg gtest perfetto)
