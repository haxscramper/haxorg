add_executable(profdata_merger profdata_merger.cpp)
llvm_map_components_to_libnames(profdata_merger_llvm_libs support core irreader profiledata coverage)

message(STATUS ${profdata_merger_llvm_libs})

target_link_libraries(profdata_merger
    ${profdata_merger_llvm_libs}
    SQLiteCpp
    sqlite3
    perfetto
    tbb
    absl::base
    absl::log
    nlohmann_json
    hstd
)

target_include_directories(profdata_merger PUBLIC "${BASE}/src" "${BASE}/thirdparty/abseil-cpp")
set_target_properties(profdata_merger PROPERTIES CXX_STANDARD 20)
