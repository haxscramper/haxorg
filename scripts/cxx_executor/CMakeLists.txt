add_executable(executor_tracker ${ORG_PROTO_GENERATED_FILES})

glob_add_sources2(TARGET executor_tracker LS_REGEX "${BASE}/scripts/cxx_executor/.*" SEARCH_BASE
                  "${BASE}")
haxorg_target_setup_v2(TARGET executor_tracker)

target_link_libraries(executor_tracker PUBLIC hstd)
