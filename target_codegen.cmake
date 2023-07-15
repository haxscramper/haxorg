add_executable(codegen)
target_link_libraries(codegen PUBLIC haxorg)
set_common_files(codegen)
set_target_output(codegen)
set_target_flags(codegen)
glob_add_sources(codegen "*.cpp" "${BASE}/src/codegen/.*")
glob_add_sources(codegen "*.hpp" "${BASE}/src/codegen/.*")

target_include_directories(codegen PUBLIC "${BASE}" "${LLVM_DIR}/include")

target_link_directories(codegen PUBLIC "${LLVM_DIR}/lib")

add_target_property(codegen COMPILE_OPTIONS "-fno-rtti")
add_target_property(codegen LINK_OPTIONS "-fno-rtti")

target_link_libraries(codegen
    PUBLIC
    fmt::fmt
    yaml-cpp::yaml-cpp
    haxorg
    Qt6::Core Qt6::Gui
    perfetto
    "clang-cpp"
    "LLVMSupport"
)
