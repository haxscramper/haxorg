add_library(nodehaxorg MODULE nodehaxorg.cpp node_utils.hpp)
target_include_directories(nodehaxorg PRIVATE "node_modules/node-addon-api" "/usr/include/node")

set_target_properties(
  nodehaxorg
  PROPERTIES PREFIX ""
             SUFFIX ".node"
             OUTPUT_NAME "nodehaxorg")
