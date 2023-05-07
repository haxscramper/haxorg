add_executable(cli)
target_link_libraries(cli PUBLIC haxorg)
set_common_files(cli)
set_target_output(cli)
set_target_flags(cli)
glob_add_sources(cli "*.cpp" "${BASE}/cli/.*")
glob_add_sources(cli "*.hpp" "${BASE}/cli/.*")
target_link_libraries(cli PUBLIC fmt::fmt yaml-cpp::yaml-cpp haxorg
                                   Qt6::Core Qt6::Gui)

target_include_directories(cli PUBLIC "${BASE}")
