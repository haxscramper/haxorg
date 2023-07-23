add_executable(codegen)
set_common_files(codegen)
set_target_output(codegen)
set_target_flags(codegen)

glob_add_sources2(codegen "${BASE}/src/codegen/.*")

target_include_directories(
    codegen
    PUBLIC
    "${BASE}"
    "/usr/include/guile/3.0"
)

target_link_libraries(codegen
    PUBLIC
    fmt::fmt
    yaml-cpp::yaml-cpp
    hstd
    Qt6::Core Qt6::Gui
    perfetto
    guile-3.0
)
