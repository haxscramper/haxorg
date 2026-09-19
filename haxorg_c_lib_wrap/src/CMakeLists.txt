haxorg_add_library(haxorg_c)

glob_add_sources2(
  TARGET
  haxorg_c
  LS_REGEX
  "${BASE}/src/wrappers/c/.*"
  SEARCH_BASE
  "${BASE}"
  ARG_EXTENSIONS
  "hpp;cpp;c;h")

target_link_libraries(haxorg_c PUBLIC hstd haxorg)
