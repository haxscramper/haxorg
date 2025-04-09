add_library(nodehaxorg MODULE nodehaxorg.cpp node_utils.hpp node_org_include.hpp)
target_include_directories(nodehaxorg PRIVATE "node_modules/node-addon-api" "/usr/include/node")

target_link_libraries(nodehaxorg PUBLIC hstd haxorg)

set_common_files(nodehaxorg)
set_target_output(nodehaxorg)
set_target_flags(nodehaxorg)

set_target_properties(
  nodehaxorg
  PROPERTIES PREFIX ""
             SUFFIX ".node"
             OUTPUT_NAME "nodehaxorg")
