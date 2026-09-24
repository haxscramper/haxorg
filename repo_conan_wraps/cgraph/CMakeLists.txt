cmake_minimum_required(VERSION 3.18) # file(CONFIGURE)
project(cgraph_wrapper LANGUAGES C)

set(GRAPHVIZ_SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/graphviz"
    CACHE PATH
    "Graphviz source tree"
)
set(GRAPHVIZ_VERSION "0.0.0" CACHE STRING "Graphviz version")

set(GV_LIB "${GRAPHVIZ_SOURCE_DIR}/lib")
if(NOT EXISTS "${GV_LIB}/cgraph/cgraph.h")
    message(FATAL_ERROR "Graphviz sources not found in ${GRAPHVIZ_SOURCE_DIR}")
endif()

include(GNUInstallDirs)
include(CheckIncludeFile)
include(CheckFunctionExists)
include(CheckCCompilerFlag)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(BISON 3.0 REQUIRED)
find_package(FLEX REQUIRED)

# ------------------------------------------------------------------ config.h
check_include_file(
    sys/inotify.h
    HAVE_SYS_INOTIFY_H
)
check_include_file(
    sys/ioctl.h
    HAVE_SYS_IOCTL_H
)
check_include_file(
    sys/mman.h
    HAVE_SYS_MMAN_H
)
check_include_file(
    sys/select.h
    HAVE_SYS_SELECT_H
)
check_include_file(
    sys/time.h
    HAVE_SYS_TIME_H
)
check_include_file(
    getopt.h
    HAVE_GETOPT_H
)
check_function_exists(
    dl_iterate_phdr
    HAVE_DL_ITERATE_PHDR
)
check_function_exists(
    drand48
    HAVE_DRAND48
)
check_function_exists(
    inotify_init1
    HAVE_INOTIFY_INIT1
)
check_function_exists(
    memrchr
    HAVE_MEMRCHR
)
check_function_exists(
    setenv
    HAVE_SETENV
)
check_function_exists(
    setmode
    HAVE_SETMODE
)
check_function_exists(
    srand48
    HAVE_SRAND48
)
check_function_exists(
    strcasestr
    HAVE_STRCASESTR
)

if(WIN32)
    set(GV_BROWSER start)
elseif(APPLE)
    set(GV_BROWSER open)
    set(DARWIN 1)
    set(DARWIN_DYLIB 1)
else()
    set(GV_BROWSER xdg-open)
endif()

file(
    CONFIGURE
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/config.h"
    CONTENT
        [=[
#pragma once
#cmakedefine HAVE_SYS_INOTIFY_H
#cmakedefine HAVE_SYS_IOCTL_H
#cmakedefine HAVE_SYS_MMAN_H
#cmakedefine HAVE_SYS_SELECT_H
#cmakedefine HAVE_SYS_TIME_H
#cmakedefine HAVE_GETOPT_H
#cmakedefine HAVE_DL_ITERATE_PHDR
#cmakedefine HAVE_DRAND48
#cmakedefine HAVE_INOTIFY_INIT1
#cmakedefine HAVE_MEMRCHR
#cmakedefine HAVE_SETENV
#cmakedefine HAVE_SETMODE
#cmakedefine HAVE_SRAND48
#cmakedefine HAVE_STRCASESTR

#ifdef _MSC_VER
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#define BROWSER "@GV_BROWSER@"
#define DEFAULT_DPI 96
#define GVPLUGIN_CONFIG_FILE "config8"
#define PACKAGE_VERSION "@GRAPHVIZ_VERSION@"

#cmakedefine DARWIN
#cmakedefine DARWIN_DYLIB
]=]
    @ONLY
)

# ------------------------------------------------------------ common flags
if(MSVC)
    add_compile_options(/wd4996)
    check_c_compiler_flag(
        /experimental:c11atomics
        HAVE_MSVC_C11ATOMICS
    )
    if(HAVE_MSVC_C11ATOMICS)
        add_compile_options(/experimental:c11atomics)
    endif()
endif()

set(GV_WIN_UNISTD "${GRAPHVIZ_SOURCE_DIR}/windows/include/unistd")

# --------------------------------------------------------------------- cdt
set(CDT_SOURCES
    dtclose.c
    dtdisc.c
    dtextract.c
    dtflatten.c
    dthash.c
    dtmethod.c
    dtopen.c
    dtrenew.c
    dtrestore.c
    dtsize.c
    dtstat.c
    dtstrhash.c
    dttree.c
    dtview.c
    dtwalk.c
)
list(TRANSFORM CDT_SOURCES PREPEND "${GV_LIB}/cdt/")

add_library(cdt ${CDT_SOURCES})
target_compile_definitions(cdt PRIVATE EXPORT_CDT)
target_include_directories(
    cdt
    PRIVATE
        "${GV_LIB}"
        "${CMAKE_CURRENT_BINARY_DIR}"
    PUBLIC
        $<BUILD_INTERFACE:${GV_LIB}/cdt>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/graphviz>
)

# ------------------------------------------------------------------ cgraph
set(GV_GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/cgraph")
file(MAKE_DIRECTORY "${GV_GEN_DIR}")

bison_target(
    Grammar
    "${GV_LIB}/cgraph/grammar.y"
    "${GV_GEN_DIR}/grammar.c"
)
flex_target(
    Scan
    "${GV_LIB}/cgraph/scan.l"
    "${GV_GEN_DIR}/scan.c"
    COMPILE_FLAGS --case-insensitive
)
add_flex_bison_dependency(
    Scan
    Grammar
)

set(CGRAPH_SOURCES
    acyclic.c
    agerror.c
    apply.c
    attr.c
    edge.c
    graph.c
    id.c
    imap.c
    ingraphs.c
    io.c
    node.c
    node_induce.c
    obj.c
    rec.c
    refstr.c
    subg.c
    tred.c
    unflatten.c
    utils.c
    write.c
)
list(TRANSFORM CGRAPH_SOURCES PREPEND "${GV_LIB}/cgraph/")

# upstream builds lib/util as a private static lib; we fold it into cgraph
set(UTIL_SOURCES
    arena.c
    base64.c
    gv_find_me.c
    gv_fopen.c
    list.c
    random.c
    xml.c
)
list(TRANSFORM UTIL_SOURCES PREPEND "${GV_LIB}/util/")
if(APPLE)
    set_source_files_properties(
        ${UTIL_SOURCES}
        PROPERTIES
            COMPILE_OPTIONS
                "-fno-common"
    )
endif()

add_library(
    cgraph
    ${CGRAPH_SOURCES}
    ${UTIL_SOURCES}
    ${BISON_Grammar_OUTPUTS}
    ${FLEX_Scan_OUTPUTS}
)

target_compile_definitions(
    cgraph
    PRIVATE
        EXPORT_CGRAPH
        EXPORT_CGHDR
)
if(WIN32 AND NOT MINGW)
    target_compile_definitions(cgraph PRIVATE YY_NO_UNISTD_H)
    if(EXISTS "${GV_WIN_UNISTD}")
        target_include_directories(cgraph PRIVATE "${GV_WIN_UNISTD}")
    endif()
endif()

target_include_directories(
    cgraph
    PRIVATE
        "${GV_LIB}"
        "${GV_LIB}/cgraph"
        "${GV_GEN_DIR}"
        "${CMAKE_CURRENT_BINARY_DIR}"
    PUBLIC
        $<BUILD_INTERFACE:${GV_LIB}/cgraph>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/graphviz>
)

target_link_libraries(cgraph PUBLIC cdt)

if(UNIX)
    find_library(MATH_LIB m)
    if(MATH_LIB)
        target_link_libraries(cgraph PRIVATE ${MATH_LIB})
    endif()
endif()

# Windows DLL import/export switch used by cgraph.h / cdt.h
if(WIN32 AND BUILD_SHARED_LIBS)
    target_compile_definitions(cdt PUBLIC GVDLL)
    target_compile_definitions(cgraph PUBLIC GVDLL)
endif()

# ----------------------------------------------------------------- install
install(
    TARGETS
        cdt
        cgraph
    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    FILES
        "${GV_LIB}/cgraph/cgraph.h"
        "${GV_LIB}/cdt/cdt.h"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/graphviz
)
