add_executable(haxorg_cpp_org_cli)
target_link_libraries(haxorg_cpp_org_cli PUBLIC haxorg absl::base absl::log absl::flags)
set_common_files(haxorg_cpp_org_cli)
set_target_output(haxorg_cpp_org_cli)
set_target_flags(haxorg_cpp_org_cli)
glob_add_sources2(TARGET haxorg_cpp_org_cli LS_REGEX "${BASE}/src/app/org_cli/.*" SEARCH_BASE
                  "${BASE}")
