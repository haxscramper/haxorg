cmake_minimum_required(VERSION 3.20)
project(adaptagrams_package_test LANGUAGES CXX)

enable_testing()

if(ADAPTAGRAMS_NATIVE_CONFIG_DIR)
    # Ignore a stale cached location from a previous CMakeDeps test.
    unset(adaptagrams_DIR CACHE)

    find_package(
        adaptagrams
        CONFIG
        REQUIRED
        PATHS
            "${ADAPTAGRAMS_NATIVE_CONFIG_DIR}"
        NO_DEFAULT_PATH
    )
else()
    find_package(adaptagrams CONFIG REQUIRED)
endif()

foreach(
    _component
    IN
    ITEMS
        avoid
        vpsc
        cola
        topology
        dialect
)
    add_executable(test_${_component} "test_${_component}.cpp")

    target_compile_features(test_${_component} PRIVATE cxx_std_11)

    # Deliberately link exactly one component per executable.
    target_link_libraries(test_${_component} PRIVATE adaptagrams::${_component})

    add_test(NAME ${_component} COMMAND test_${_component})

    set_tests_properties(
        ${_component}
        PROPERTIES
            TIMEOUT
                60
    )
endforeach()

if(NOT TARGET adaptagrams::adaptagrams)
    message(FATAL_ERROR "Missing adaptagrams aggregate target")
endif()
