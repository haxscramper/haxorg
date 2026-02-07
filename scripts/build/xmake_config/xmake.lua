set_project("haxorg")
set_xmakever("3.0.6")
set_languages("c++23")

-- Global settings
set_policy("build.c++.modules", false)
add_rules("mode.debug", "mode.release")

add_cxflags("-Wno-unknown-attributes")
-- set_config("ld", "ld.lld")
set_config("cxxflags", "-fPIC")

-- Options
option("org_instrument_trace",
       {default = false, description = "Generate instrumentation trace"})
option("org_use_coverage",
       {default = false, description = "Enable test coverage"})
option("max_compile_errors", {
  default = nil,
  description = "Max number of compilation errors before compiler stops"
})
option("org_use_perfetto",
       {default = false, description = "Enable perfetto profiling"})
option("org_use_tracy", {
  default = false,
  description = "Enable performance profiling using tracy"
})
option("org_use_pgo_generation", {
  default = false,
  description = "Compile binary with profile data generation"
})
option("org_use_pgo_reader", {
  default = false,
  description = "Compile binary using profile data generation"
})
option("org_use_xray", {
  default = false,
  description = "Use LLVM XRay instrumentation for profiling"
})
option("org_use_sanitizer", {default = true, description = "Use sanitizers"})
option("org_use_python_bindings",
       {default = true, description = "Enable build of the python bindings"})
option("org_force_adaptagrams_build", {
  default = false,
  description = "Force update and build of the external adaptagrams library"
})
option("org_emcc_build",
       {default = false, description = "Building for emscripten target"})
option("org_use_qt",
       {default = false, description = "Enable Qt-related features and API"})
option("org_use_imgui",
       {default = false, description = "Build imgui apps and API"})
option("org_deps_install_root", {
  default = "",
  description = "Root path for custom dependency installation root"
})
option("org_deps_use_protobuf", {
  default = true,
  description = "Include protobuf functionality in the build"
})
option("org_deps_use_msgpack", {
  default = true,
  description = "Include msgpack serialization functionality in the build"
})
option("org_deps_use_adaptagrams",
       {default = false, description = "Enable adaptagrams-based features"})
option("org_build_is_develop", {
  default = true,
  description = "Build and configure internal development dependencies"
})
option("org_build_use_gold_wrapper",
       {default = false, description = "Link profiling"})
option("org_build_tests",
       {default = false, description = "Build cmake tests and benchmarks"})
option("org_build_assume_clang",
       {default = true, description = "Assume clang++ compiler for the build"})
option("org_deps_use_packaged_boost", {
  default = false,
  description = "Use boost library headers from the third-party"
})
option("org_build_use_napi_wrapper", {default = true, description = ""})
option("org_use_sarif",
       {default = false, description = "Enable SARIF reporting for build"})
option("org_disable_warnings",
       {default = false, description = "Disable warnings in the build"})
option("org_separate_debug_symbols", {
  default = false,
  description = "Strip debug symbols into separate .debug file"
})
option("org_use_conan_install", {
  default = false,
  description = "Auto-install dependencies by calling conan from cmake"
})
option("org_is_conan_build",
       {default = false, description = "The project is being built by conan"})

-- Validate mutually exclusive options
on_load(function()
  if has_config("org_use_tracy") and has_config("org_use_perfetto") then
    raise("Tracy and perfetto profiling are mutually exclusive.")
  end
end)

-- Package dependencies
add_requires("conan::cctz [>=2.4 <3]",
             {alias = "cctz", configs = {settings = {"compiler.cppstd=23"}}})

add_requires("conan::zstd [>=1.5.7 <2]",
             {alias = "zstd", configs = {settings = {"compiler.cppstd=23"}}})

add_requires("conan::range-v3 [>=0.12.0 <1]", {
  alias = "range-v3",
  configs = {settings = {"compiler.cppstd=23"}}
})

add_requires("conan::immer [>=0.8.1 <1]",
             {alias = "immer", configs = {settings = {"compiler.cppstd=23"}}})

add_requires("conan::lager [>=0.1.1 <1]",
             {alias = "lager", configs = {settings = {"compiler.cppstd=23"}}})

add_requires("conan::yaml-cpp [>=0.8.0 <1]", {
  alias = "yaml-cpp",
  configs = {settings = {"compiler.cppstd=23"}}
})

add_requires("conan::nlohmann_json [>=3.12.0 <4]", {
  alias = "nlohmann_json",
  configs = {settings = {"compiler.cppstd=23"}}
})

add_requires("conan::foonathan-lexy [>=2025.05.0 <2026]", {
  alias = "foonathan-lexy",
  configs = {settings = {"compiler.cppstd=23"}}
})

add_requires("conan::boost [>=1.90.0 <2]", {
  alias = "boost",
  configs = {
    settings = {"compiler.cppstd=23"},
    settings_build = {"compiler.cppstd=23"},
    options = "boost/*:without_cobalt = True"
  }
})

add_requires("cpptrace >=1.0.4 <2", {
  alias = "cpptrace",
  configs = {settings = {"compiler.cppstd=23"}}
})

if not has_config("org_emcc_build") then
  add_requires("python 3.x", {system = true})
  add_requires("conan::pybind11 [>=3.0.1 <4]", {
    alias = "pybind11",
    configs = {settings = {"compiler.cppstd=23"}}
  })
  add_requires("abseil")
  -- cairomm via system pkg-config
  add_requires("pkgconfig::cairomm-1.0", {alias = "cairomm"})
end

if has_config("org_deps_use_msgpack") then add_requires("msgpack-cxx") end

if has_config("org_use_tracy") then add_requires("tracy") end

if has_config("org_use_perfetto") and not has_config("org_emcc_build") then
  add_requires("perfetto")
end

if has_config("org_build_tests") and not has_config("org_emcc_build") then
  add_requires("gtest")
  add_requires("benchmark")
end

if has_config("org_build_is_develop") and not has_config("org_emcc_build") then
  add_requires("sqlitecpp")
  add_requires("pkgconfig::libgit2", {alias = "libgit2"})
end

if has_config("org_deps_use_protobuf") and not has_config("org_emcc_build") then
  add_requires("protobuf-cpp")
end

if has_config("org_deps_use_adaptagrams") and not has_config("org_emcc_build") then
  -- adaptagrams may need a custom package definition
  add_requires("adaptagrams")
end

if has_config("org_deps_use_packaged_boost") then
  add_requires("boost",
               {configs = {mp11 = true, describe = true, preprocessor = true}})
end

-- Global defines based on options
if has_config("org_emcc_build") then
  add_defines("ORG_EMCC_BUILD=1")
else
  add_defines("ORG_EMCC_BUILD=0")
end

if has_config("org_deps_use_protobuf") and not has_config("org_emcc_build") then
  add_defines("ORG_DEPS_USE_PROTOBUF=1")
else
  add_defines("ORG_DEPS_USE_PROTOBUF=0")
end

if has_config("org_deps_use_msgpack") then
  add_defines("ORG_DEPS_USE_MSGPACK=1")
else
  add_defines("ORG_DEPS_USE_MSGPACK=0")
end

if has_config("org_deps_use_adaptagrams") then
  add_defines("ORG_DEPS_USE_ADAPTAGRAMS")
end

-- Subdirectories / targets
local dir = os.scriptdir()
includes(path.join(dir, "config_rules.lua"))
includes(path.join(dir, "target_hstd.lua"))
includes(path.join(dir, "target_haxorg.lua"))

if not has_config("org_emcc_build") then
  includes(path.join(dir, "target_py_libs.lua"))
end

-- Install rules
after_install(function(target)
  -- Install headers
  os.cp("src/**.hpp", path.join(target:installdir(), "include/"))
  os.cp("src/**.tcc", path.join(target:installdir(), "include/"))
  -- Install generated protobuf headers
  os.cp(path.join(target:builddir(), "**.pb.h"),
        path.join(target:installdir(), "include/"))
end)
