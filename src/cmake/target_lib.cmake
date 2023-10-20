add_library(haxorg)
set_common_files(haxorg)

glob_add_sources2(haxorg "${BASE}/src/exporters/.*")
glob_add_sources2(haxorg "${BASE}/src/annotators/.*")
glob_add_sources2(haxorg "${BASE}/src/lexbase/.*")
glob_add_sources2(haxorg "${BASE}/src/parse/.*")
glob_add_sources2(haxorg "${BASE}/src/sem/.*")
glob_add_sources2(haxorg "${BASE}/src/tools/.*")
glob_add_sources2(haxorg "${BASE}/src/types/.*")

set_target_output(haxorg)
set_target_flags(haxorg)

find_library(GRAPHVIZ_CGRAPH_LIBRARY cgraph)
find_library(GRAPHVIZ_GVC_LIBRARY gvc)

if (${USE_PCH})
    target_precompile_headers(haxorg PRIVATE
      <std::string>
      <QDateTime>
      <QDebug>
      <nlohmann/json.hpp>
      <optional>
      <vector>
      <boost/mp11.hpp>
      <boost/describe.hpp>
      <sem/SemOrg.hpp>
    )
endif()


target_link_libraries(haxorg PUBLIC
    ${GRAPHVIZ_CGRAPH_LIBRARY}
    ${GRAPHVIZ_GVC_LIBRARY}
    fmt::fmt
    perfetto
    hstd
    yaml-cpp::yaml-cpp
    )


