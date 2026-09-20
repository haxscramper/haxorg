haxorg_add_library(haxorg_c_haxorg)

haxorg_glob_add_sources2(
    TARGET haxorg_c_haxorg
    LS_REGEX "${BASE}/src/.*"
    SEARCH_BASE "${BASE}"
    ARG_EXTENSIONS
    "hpp;cpp;c;h"
)

haxorg_set_target_output(haxorg_c_haxorg)
haxorg_set_target_flags(haxorg_c_haxorg)

target_link_libraries(haxorg_c_haxorg PUBLIC haxorg::haxorg_cpp_lib)

target_include_directories(
    haxorg_c_haxorg
    PUBLIC
        $<BUILD_INTERFACE:${BASE}/src>
        $<INSTALL_INTERFACE:include>
)

add_library(haxorg::haxorg_c_haxorg ALIAS haxorg_c_haxorg)

install(
    TARGETS
        haxorg_c_haxorg
    EXPORT HaxorgCHaxorgTargets
    LIBRARY
        DESTINATION lib
    ARCHIVE
        DESTINATION lib
    RUNTIME
        DESTINATION bin
    INCLUDES DESTINATION
        include
)
