add_executable(codegen)
set_common_files(codegen)
set_target_output(codegen)
set_target_flags(codegen)

glob_add_sources2(codegen "${BASE}/src/codegen/.*")

find_package(Boost REQUIRED COMPONENTS python)
find_package(PythonLibs 3.11)

target_include_directories(
    codegen
    PUBLIC
    "${BASE}"
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(codegen
    PUBLIC
    fmt::fmt
    yaml-cpp::yaml-cpp
    hstd
    Qt6::Core Qt6::Gui
    perfetto
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)

add_library(py_textlayout MODULE "${BASE}/src/py_libs/py_textlayout/py_textlayout.cpp")
set_common_files(py_textlayout)
set_target_output(py_textlayout)
set_target_flags(py_textlayout)

target_include_directories(
    py_textlayout
    PUBLIC
    "${BASE}"
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(py_textlayout hstd ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
