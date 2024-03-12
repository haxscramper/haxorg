add_executable(lsp)
target_link_libraries(lsp PUBLIC haxorg)
set_common_files(lsp)
set_target_output(lsp)
set_target_flags(lsp)
glob_add_sources2(lsp "${BASE}/src/lsp/.*")
target_link_libraries(lsp PUBLIC haxorg absl_all)

