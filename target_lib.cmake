add_library(haxorg)
set_common_files(haxorg)

glob_add_sources2(haxorg "${BASE}/src/exporters/.*")
glob_add_sources2(haxorg "${BASE}/src/lexbase/.*")
glob_add_sources2(haxorg "${BASE}/src/parse/.*")
glob_add_sources2(haxorg "${BASE}/src/sem/.*")
glob_add_sources2(haxorg "${BASE}/src/tools/.*")
glob_add_sources2(haxorg "${BASE}/src/types/.*")

set_target_output(haxorg)
set_target_flags(haxorg)

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)

add_target_property(haxorg INCLUDE_DIRECTORIES "/usr/include/enchant-2")

target_link_libraries(haxorg PUBLIC
    ${GRAPHVIZ_CGRAPH_LIBRARY}
    ${GRAPHVIZ_GVC_LIBRARY}
    fmt::fmt
    enchant-2
    perfetto
    hstd
    yaml-cpp::yaml-cpp
    Qt6::Core Qt6::Gui)


