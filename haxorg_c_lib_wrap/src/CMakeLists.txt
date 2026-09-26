haxorg_add_library(haxorg_c_haxorg)

haxorg_glob_add_sources2(
    TARGET haxorg_c_haxorg
    LS_REGEX "${CMAKE_CURRENT_SOURCE_DIR}/src/.*"
    SEARCH_BASE "${CMAKE_CURRENT_SOURCE_DIR}"
    ARG_EXTENSIONS
    "hpp;cpp;c;h"
)

haxorg_set_target_output(haxorg_c_haxorg)
haxorg_set_target_flags(haxorg_c_haxorg)

target_link_libraries(haxorg_c_haxorg PUBLIC haxorg::haxorg_cpp_lib)

target_include_directories(
    haxorg_c_haxorg
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

add_library(haxorg::haxorg_c_haxorg ALIAS haxorg_c_haxorg)

install(
    TARGETS
        haxorg_c_haxorg
    EXPORT haxorg_c_haxorg_targets
    LIBRARY
        DESTINATION lib
    ARCHIVE
        DESTINATION lib
    RUNTIME
        DESTINATION bin
    INCLUDES DESTINATION
        include
)
