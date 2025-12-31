add_executable(profdata_merger profdata_merger.cpp)
llvm_map_components_to_libnames(profdata_merger_llvm_libs support core irreader profiledata
                                coverage)

message(STATUS ${profdata_merger_llvm_libs})

haxorg_target_setup_v2(TARGET profdata_merger)
target_link_libraries(
  profdata_merger
  PUBLIC ${profdata_merger_llvm_libs}
         SQLiteCpp
         sqlite3
         tbb
         absl::base
         absl::log
         nlohmann_json::nlohmann_json
         hstd
         reflection_lib)

if(${ORG_USE_PERFETTO})
  target_link_libraries(profdata_merger PRIVATE Perfetto::perfetto)
endif()

if(${ORG_USE_TRACY})
  target_link_libraries(profdata_merger PRIVATE Tracy::TracyClient)
endif()

target_include_directories(profdata_merger PUBLIC "${BASE}/src" "${BASE}/thirdparty/abseil-cpp")
