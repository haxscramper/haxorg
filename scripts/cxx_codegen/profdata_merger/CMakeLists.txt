add_executable(profdata_merger profdata_merger.cpp)
llvm_map_components_to_libnames(profdata_merger_llvm_libs support core irreader profiledata coverage)

message(STATUS ${profdata_merger_llvm_libs})

set_common_files(profdata_merger)
set_target_output(profdata_merger)
set_target_flags(profdata_merger)


target_link_libraries(profdata_merger
    ${profdata_merger_llvm_libs}
    SQLiteCpp
    sqlite3
    hstd
)

set_target_properties(profdata_merger PROPERTIES CXX_STANDARD 20)
