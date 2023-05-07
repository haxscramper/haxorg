add_library(haxorg)
set_common_files(haxorg)
glob_add_sources(haxorg *.cpp "${BASE}/src/.*")
glob_add_sources(haxorg *.hpp "${BASE}/src/.*")
set_target_output(haxorg)
set_target_flags(haxorg)

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)

target_link_libraries(haxorg PUBLIC
    ${GRAPHVIZ_CGRAPH_LIBRARY}
    ${GRAPHVIZ_GVC_LIBRARY}
    fmt::fmt
    yaml-cpp::yaml-cpp
    Qt6::Core Qt6::Gui)


