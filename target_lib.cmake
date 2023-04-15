add_library(haxorg)
set_common_files(haxorg)
glob_add_sources(haxorg *.cpp "${BASE}/src/.*")
glob_add_sources(haxorg *.hpp "${BASE}/src/.*")
set_target_output(haxorg)
set_target_flags(haxorg)
target_link_libraries(haxorg PUBLIC fmt::fmt yaml-cpp::yaml-cpp
                                   "Qt${QT_VERSION_MAJOR}::Core")
