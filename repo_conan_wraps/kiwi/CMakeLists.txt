cmake_minimum_required(VERSION 3.15)
project(kiwi LANGUAGES CXX)

include(GNUInstallDirs)

add_library(kiwi INTERFACE)
add_library(kiwi::kiwi ALIAS kiwi)

target_include_directories(
    kiwi
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/upstream>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(kiwi INTERFACE cxx_std_11)

install(
    DIRECTORY
        upstream/kiwi
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING
    PATTERN "*.h"
)
