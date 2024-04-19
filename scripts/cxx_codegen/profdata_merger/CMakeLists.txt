add_executable(profdata_merger profdata_merger.cpp)
llvm_map_components_to_libnames(profdata_merger_llvm_libs support core irreader
                                profiledata coverage)

message(STATUS ${profdata_merger_llvm_libs})

target_link_libraries(profdata_merger ${profdata_merger_llvm_libs} SQLiteCpp
                      sqlite3 hstd)

set_target_properties(profdata_merger PROPERTIES CXX_STANDARD 20)
target_compile_definitions(profdata_merger PUBLIC ${LLVM_DEFINITIONS})
target_include_directories(profdata_merger PUBLIC ${LLVM_INCLUDE_DIRS}
                                                  ${CLANG_INCLUDE_DIRS})

set_common_files(profdata_merger)
