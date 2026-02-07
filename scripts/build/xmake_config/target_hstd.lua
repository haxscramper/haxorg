includes("config_utils.lua")

target("hstd", function()
  set_kind("static")
  add_rules("haxorg.common_files", "haxorg.flags")
  local PROJECTDIR = get_project_dir()

  -- Sources
  add_files(path.join(PROJECTDIR, "src/hstd/stdlib/**.cpp"))
  add_files(path.join(PROJECTDIR, "src/hstd/system/**.cpp"))
  add_files(path.join(PROJECTDIR, "src/hstd/ext/**.cpp"))

  -- Qt support
  if get_config("org_use_qt") then
    add_rules("qt.static")
    add_frameworks("QtCore")
    add_defines("ORG_USE_QT=1", {public = true})
    set_values("qt.autogen", true)
  end

  -- Public dependencies always linked
  add_packages("yaml-cpp", "range-v3", "nlohmann_json", "cctz", {public = true})

  -- Non-emscripten dependencies
  if not get_config("org_emcc_build") then
    add_syslinks("cgraph", "gvc")
    add_packages("boost", "cpptrace", {public = true})
    -- boost log component
    add_links("boost_log", {public = true})
  end

  -- Adaptagrams
  if get_config("org_deps_use_adaptagrams") and not get_config("org_emcc_build") then
    add_deps("adaptagrams", {public = true})
  end

  -- Packaged Boost describe/preprocessor
  if get_config("org_deps_use_packaged_boost") then
    add_packages("boost", {
      public = true,
      configs = {describe = true, preprocessor = true}
    })
  end

  -- Perfetto
  if get_config("org_use_perfetto") and not get_config("org_emcc_build") then
    add_packages("perfetto", {public = true})
  end

  -- Tracy
  if get_config("org_use_tracy") and not get_config("org_emcc_build") then
    add_packages("tracy", {public = true})
  end

  -- Thirdparty header-only includes
  add_includedirs(path.join(PROJECTDIR, "thirdparty/immer"),
                  path.join(PROJECTDIR, "thirdparty/lager"), {public = true})
end)

-- Tests
if get_config("org_build_tests") and not get_config("org_emcc_build") then

  target("tests_hstd", function()
    set_kind("binary")
    add_rules("haxorg.common_files", "haxorg.flags")

    add_files(path.join(PROJECTDIR, "tests/hstd/**.cpp"))
    add_files(path.join(PROJECTDIR, "tests/common.cpp"))

    if get_config("org_use_qt") then
      add_defines("ORG_USE_QT=1", {public = true})
    end

    add_deps("hstd")
    add_packages("gtest", "gmock", "abseil", "immer")

    add_tests("hstd_tests", {runargs = {}})
  end)

  target("benchmark_hstd", function()
    set_kind("binary")
    add_rules("haxorg.common_files", "haxorg.flags")

    add_files(path.join(PROJECTDIR, "benchmark/hstd/**.cpp"))

    add_deps("hstd")
    add_packages("benchmark", "immer")

    add_tests("hstd_benchmark", {runargs = {}})
  end)

end
