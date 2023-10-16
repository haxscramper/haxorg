add_executable(bench)
target_link_libraries(bench PUBLIC haxorg)
set_common_files(bench)
set_target_output(bench)
set_target_flags(bench)
glob_add_sources2(bench "${BASE}/src/bench/.*")
target_link_libraries(bench PUBLIC fmt::fmt yaml-cpp::yaml-cpp haxorg gtest perfetto benchmark::benchmark_main)
