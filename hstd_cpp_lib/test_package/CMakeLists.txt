cmake_minimum_required(VERSION 3.24)
project(hstd_cpp_lib_package_test LANGUAGES CXX)

find_package(hstd_cpp_lib CONFIG REQUIRED)

add_executable(hstd_cpp_lib_package_test)

haxorg_glob_add_sources2(
    TARGET hstd_cpp_lib_package_test
    LS_REGEX "${CMAKE_CURRENT_SOURCE_DIR}/hstd_test_package_main.*"
    SEARCH_BASE "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_compile_features(hstd_cpp_lib_package_test PRIVATE cxx_std_20)

target_link_libraries(hstd_cpp_lib_package_test PRIVATE hstd::hstd_cpp_lib)
