if(${ORG_EMCC_BUILD})

  add_executable(haxorg_wasm haxorg_wasm.cpp node_utils.hpp node_org_include.hpp)
  target_include_directories(haxorg_wasm PRIVATE "node_modules/node-addon-api" "/usr/include/node")

  target_link_libraries(haxorg_wasm PUBLIC hstd haxorg)

  set_common_files(haxorg_wasm)
  set_target_output(haxorg_wasm)
  set_target_flags(haxorg_wasm)

  set_target_properties(
    haxorg_wasm
    PROPERTIES PREFIX ""
               SUFFIX ".js"
               OUTPUT_NAME "haxorg_wasm")

  set_target_properties(haxorg_wasm PROPERTIES SUFFIX ".js" LINK_FLAGS "--bind")

endif()
