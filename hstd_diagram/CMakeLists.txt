if(${ORG_BUILD_WITH_KIWI})
  target_link_libraries(hstd PUBLIC kiwi::kiwi)
endif()

# Graph processing and visualization
if(${ORG_BUILD_WITH_ELK})
  add_subdirectory("${BASE}/src/hstd/ext/graph/jni_elk")
  target_link_libraries(hstd PUBLIC jni_elk_lib)
endif()

if(${ORG_BUILD_WITH_CGRAPH})
  find_package(graphviz REQUIRED)
  target_link_libraries(hstd PUBLIC graphviz::cgraph graphviz::gvc)
endif()

if(${ORG_BUILD_WITH_ADAPTAGRAMS})
  target_link_libraries(hstd PUBLIC adaptagrams)
endif()

haxorg_add_protobuf(
  TARGET
  hstd
  UNIQUE_TARGET
  hstd_proto_graphviz_graph
  IMPORT_DIRS
  "${BASE}"
  PROTO_SOURCES
  "${BASE}/src/hstd/ext/graph/visual/graph_graphviz.proto")

haxorg_add_protobuf(
  TARGET
  hstd
  UNIQUE_TARGET
  hstd_proto_avoid_graph
  IMPORT_DIRS
  "${BASE}"
  PROTO_SOURCES
  "${BASE}/src/hstd/ext/graph/visual/graph_avoid.proto")

haxorg_add_protobuf(
  TARGET
  hstd
  UNIQUE_TARGET
  hstd_proto_elk_graph
  IMPORT_DIRS
  "${BASE}"
  PROTO_SOURCES
  "${BASE}/src/hstd/ext/graph/visual/graph_elk.proto")

haxorg_add_protobuf(
  TARGET
  hstd
  UNIQUE_TARGET
  hstd_proto_kiwi_graph
  IMPORT_DIRS
  "${BASE}"
  PROTO_SOURCES
  "${BASE}/src/hstd/ext/geometry/kiwi_ir.proto"
  "${BASE}/src/hstd/ext/graph/visual/graph_kiwi.proto")

haxorg_add_protobuf(
  TARGET
  hstd
  UNIQUE_TARGET
  hstd_proto_diagram_graph
  IMPORT_DIRS
  "${BASE}"
  PROTO_SOURCES
  "${BASE}/src/hstd/ext/graph/visual/graph_diagram.proto")
