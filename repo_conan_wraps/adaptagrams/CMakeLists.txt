cmake_minimum_required(VERSION 3.20)

set(ADAPTAGRAMS_VERSION
    "0.0.20251029"
    CACHE STRING
    "Version of this Adaptagrams package snapshot"
)

project(Adaptagrams VERSION "${ADAPTAGRAMS_VERSION}" LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(ADAPTAGRAMS_SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/upstream"
    CACHE PATH
    "Root of the upstream Adaptagrams checkout"
)

get_filename_component(
    ADAPTAGRAMS_SOURCE_DIR
    "${ADAPTAGRAMS_SOURCE_DIR}"
    ABSOLUTE
    BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
)

set(COLA_DIR "${ADAPTAGRAMS_SOURCE_DIR}/cola")

if(NOT EXISTS "${COLA_DIR}/libcola/cola.h")
    message(
        FATAL_ERROR
        "ADAPTAGRAMS_SOURCE_DIR must point to the upstream Adaptagrams "
        "repository root. Expected: ${COLA_DIR}/libcola/cola.h"
    )
endif()

# This wrapper deliberately builds static libraries only.
if(BUILD_SHARED_LIBS)
    message(FATAL_ERROR "This wrapper currently supports static libraries only.")
endif()

# Default to PIC, but respect a value supplied by Conan or the caller.
if(NOT DEFINED CMAKE_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# Require relative installation directories so the exports stay relocatable.
foreach(_dir CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_BINDIR)
    if(IS_ABSOLUTE "${${_dir}}")
        message(FATAL_ERROR "${_dir} must be relative to CMAKE_INSTALL_PREFIX.")
    endif()
endforeach()

# Do not allow a previous Autotools configuration to override our generated
# configuration through a source-relative #include.
if(EXISTS "${COLA_DIR}/libcola/config.h")
    message(
        FATAL_ERROR
        "Found ${COLA_DIR}/libcola/config.h from another build. "
        "Use a clean checkout, or move that generated file out of the source "
        "tree before configuring this wrapper."
    )
endif()

set(ADAPTAGRAMS_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY "${ADAPTAGRAMS_GENERATED_DIR}/libcola")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cola_config.h.in"
    "${ADAPTAGRAMS_GENERATED_DIR}/libcola/config.h"
    @ONLY
)

function(add_adaptagrams_library name)
    set(_sources)

    foreach(_source IN LISTS ARGN)
        list(APPEND _sources "${COLA_DIR}/lib${name}/${_source}")
    endforeach()

    add_library(${name} STATIC ${_sources})
    add_library(Adaptagrams::${name} ALIAS ${name})

    target_compile_features(${name} PUBLIC cxx_std_11)

    # Keep filenames consistent with the Conan component metadata, including
    # when the caller has configured a global debug postfix.
    set_target_properties(
        ${name}
        PROPERTIES
            OUTPUT_NAME
                "${name}"
            DEBUG_POSTFIX
                ""
    )

    target_include_directories(
        ${name}
        PUBLIC
            "$<BUILD_INTERFACE:${ADAPTAGRAMS_GENERATED_DIR}>"
            "$<BUILD_INTERFACE:${COLA_DIR}>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        PRIVATE
            "${ADAPTAGRAMS_GENERATED_DIR}/libcola"
    )

    target_compile_definitions(${name} PRIVATE HAVE_CONFIG_H)

    if(MSVC)
        target_compile_definitions(
            ${name}
            PRIVATE
                _USE_MATH_DEFINES
                _CRT_SECURE_NO_WARNINGS
        )
    endif()

    # Only glob headers, not translation units. In particular, do not pick up
    # upstream tests, examples or alternative implementations as sources.
    file(GLOB _headers CONFIGURE_DEPENDS "${COLA_DIR}/lib${name}/*.h")

    # Our generated configuration is installed separately.
    list(FILTER _headers EXCLUDE REGEX "/config\\.h$")

    # FILES avoids the include/libcola/libcola nesting in the original stub.
    install(FILES ${_headers} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/lib${name}")
endfunction()

# Source lists mirror the upstream library Makefile.am files.
add_adaptagrams_library(
    vpsc
    block.cpp
    blocks.cpp
    constraint.cpp
    rectangle.cpp
    solve_VPSC.cpp
    variable.cpp
    cbuffer.cpp
)

add_adaptagrams_library(
    avoid
    connectionpin.cpp
    connector.cpp
    connend.cpp
    geometry.cpp
    geomtypes.cpp
    graph.cpp
    junction.cpp
    makepath.cpp
    obstacle.cpp
    orthogonal.cpp
    router.cpp
    shape.cpp
    timer.cpp
    vertices.cpp
    viscluster.cpp
    visibility.cpp
    vpsc.cpp
    hyperedge.cpp
    hyperedgeimprover.cpp
    mtst.cpp
    hyperedgetree.cpp
    scanline.cpp
    actioninfo.cpp
)

add_adaptagrams_library(
    cola
    cola.cpp
    colafd.cpp
    conjugate_gradient.cpp
    gradient_projection.cpp
    straightener.cpp
    connected_components.cpp
    convex_hull.cpp
    cluster.cpp
    compound_constraints.cpp
    pseudorandom.cpp
    output_svg.cpp
    cc_clustercontainmentconstraints.cpp
    cc_nonoverlapconstraints.cpp
    box.cpp
    shapepair.cpp
)

add_adaptagrams_library(
    topology
    topology_graph.cpp
    topology_constraints.cpp
    compute_forces.cpp
    topology_constraints_constructor.cpp
    resize.cpp
    cola_topology_addon.cpp
    orthogonal_topology.cpp
)

add_adaptagrams_library(
    dialect
    aca.cpp
    bendseqlookup.cpp
    chains.cpp
    constraints.cpp
    edges.cpp
    expansion.cpp
    faces.cpp
    graphs.cpp
    hola.cpp
    io.cpp
    logging.cpp
    nearalign.cpp
    nexes.cpp
    nodeconfig.cpp
    nodes.cpp
    ortho.cpp
    peeling.cpp
    planarise.cpp
    qalookup.cpp
    quadaction.cpp
    routing.cpp
    sides.cpp
    treeplacement.cpp
    trees.cpp
)

# Upstream libavoid otherwise uses dllimport declarations under MSVC.
# This must reach consumers as well as the library's own compilation.
target_compile_definitions(avoid PUBLIC LIBAVOID_NO_DLL)

# Static-library dependencies must propagate to the final executable.
target_link_libraries(cola PUBLIC vpsc)
target_link_libraries(
    topology
    PUBLIC
        avoid
        cola
        vpsc
)
target_link_libraries(
    dialect
    PUBLIC
        avoid
        cola
        vpsc
)

# Convenience target matching Conan's aggregate target.
add_library(Adaptagrams INTERFACE)
add_library(Adaptagrams::Adaptagrams ALIAS Adaptagrams)

target_link_libraries(
    Adaptagrams
    INTERFACE
        dialect
        topology
        cola
        avoid
        vpsc
)

install(
    FILES
        "${ADAPTAGRAMS_GENERATED_DIR}/libcola/config.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/libcola"
)

install(
    TARGETS
        vpsc
        avoid
        cola
        topology
        dialect
        Adaptagrams
    EXPORT AdaptagramsTargets
    ARCHIVE
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME
        DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

set(ADAPTAGRAMS_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/Adaptagrams")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/AdaptagramsConfig.cmake"
    INSTALL_DESTINATION "${ADAPTAGRAMS_CMAKE_INSTALL_DIR}"
)

# Snapshot versions do not imply compatibility with other snapshots.
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/AdaptagramsConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY ExactVersion
)

install(
    EXPORT AdaptagramsTargets
    FILE AdaptagramsTargets.cmake
    NAMESPACE Adaptagrams::
    DESTINATION "${ADAPTAGRAMS_CMAKE_INSTALL_DIR}"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/AdaptagramsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/AdaptagramsConfigVersion.cmake"
    DESTINATION "${ADAPTAGRAMS_CMAKE_INSTALL_DIR}"
)
