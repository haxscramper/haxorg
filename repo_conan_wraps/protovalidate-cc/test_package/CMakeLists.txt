cmake_minimum_required(VERSION 3.24)

project(protovalidate_cc_test LANGUAGES CXX)

find_package(re2 CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(protovalidate_cc CONFIG REQUIRED)

if(NOT DEFINED protovalidate_cc_PROTO_IMPORT_DIR)
    message(FATAL_ERROR "protovalidate_cc_PROTO_IMPORT_DIR is not defined")
endif()

set(validate_schema "${protovalidate_cc_PROTO_IMPORT_DIR}/buf/validate/validate.proto")

if(NOT EXISTS "${validate_schema}")
    message(FATAL_ERROR "Missing protovalidate schema: ${validate_schema}")
endif()

add_executable(protovalidate_cc_test main.cpp)

target_compile_features(protovalidate_cc_test PRIVATE cxx_std_17)

target_link_libraries(protovalidate_cc_test PRIVATE protovalidate_cc::protovalidate_cc)
