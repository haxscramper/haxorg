if(${ORG_EMCC_BUILD})

  add_library(wasmorg MODULE wasmorg.cpp node_utils.hpp node_org_include.hpp)
  target_include_directories(wasmorg PRIVATE "node_modules/node-addon-api" "/usr/include/node")

  target_link_libraries(wasmorg PUBLIC hstd haxorg)

  set_common_files(wasmorg)
  set_target_output(wasmorg)
  set_target_flags(wasmorg)

  set_target_properties(
    wasmorg
    PROPERTIES PREFIX ""
               SUFFIX ".node"
               OUTPUT_NAME "wasmorg")

endif()
