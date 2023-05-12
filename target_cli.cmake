add_executable(cli)
target_link_libraries(cli PUBLIC haxorg)
set_common_files(cli)
set_target_output(cli)
set_target_flags(cli)
glob_add_sources(cli "*.cpp" "${BASE}/cli/.*")
glob_add_sources(cli "*.hpp" "${BASE}/cli/.*")

target_include_directories(cli PUBLIC "${BASE}")


FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GLIB REQUIRED glib-2.0)
message(INFO ${GLIB_INCLUDE_DIRS})

add_target_property(cli INCLUDE_DIRECTORIES "${GLIB_INCLUDE_DIRS}")

#TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${GLIB_LIBRARIES})

target_link_libraries(cli
    PUBLIC
    fmt::fmt
    yaml-cpp::yaml-cpp
    haxorg
    Qt6::Core Qt6::Gui
    perfetto
    ${GLIB_LIBRARIES}
)
