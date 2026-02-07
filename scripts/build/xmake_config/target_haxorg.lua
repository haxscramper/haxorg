includes("config_utils.lua")

local get_autogen_dir = get_autogen_dir

target("haxorg", function()
  set_kind("static")
  local PROJECTDIR = get_project_dir()
  add_files(path.join(PROJECTDIR, "src/haxorg/**.cpp"))
  add_includedirs(path.join(PROJECTDIR, "src"), {public = true})
  add_deps("hstd")
  add_packages("range-v3", "nlohmann_json", "lexy", "immer", {public = true})
  add_syslinks("cgraph", "gvc")
  add_packages("protobuf-cpp", {public = true})
  add_packages("msgpack-cxx", {public = true})
  add_includedirs("$(builddir)", {public = true})
  add_rules("haxorg.common_files", "haxorg.flags")

  on_load(function(target)
    local builddir = target:targetdir()
    local protos = {
      path.join(PROJECTDIR, "src/haxorg/serde/SemOrgProto.proto"),
      path.join(PROJECTDIR, "src/haxorg/serde/SemOrgProtoManual.proto")
    }
    for _, proto in ipairs(protos) do
      local name = path.basename(proto)
      target:add("files", path.join(builddir, name .. ".pb.cc"))
    end
  end)

  before_build(function(target)
    local builddir = target:targetdir()
    os.mkdir(builddir)
    local proto_import = path.join(PROJECTDIR, "src/haxorg/serde")
    local protos = {
      path.join(PROJECTDIR, "src/haxorg/serde/SemOrgProto.proto"),
      path.join(PROJECTDIR, "src/haxorg/serde/SemOrgProtoManual.proto")
    }
    os.execv("protoc", {
      "--proto_path=" .. proto_import, "--cpp_out=" .. get_autogen_dir(),
      table.unpack(protos)
    })
  end)
end)

target("tests_org", function()
  set_kind("binary")
  local PROJECTDIR = get_project_dir()
  add_files(path.join(PROJECTDIR, "tests/org/**.cpp"))
  add_files(path.join(PROJECTDIR, "tests/common.cpp"))
  add_files(path.join(PROJECTDIR, "tests/testprofiler.cpp"))
  add_deps("haxorg")
  add_packages("gtest", "abseil")
  add_includedirs(path.join(PROJECTDIR, "thirdparty/immer"),
                  path.join(PROJECTDIR, "thirdparty/lager"))
  add_rules("haxorg.common_files", "haxorg.flags")
  after_build(function(target)
    os.ln(path.absolute("$(builddir)"), path.join(PROJECTDIR, "build/haxorg"))
  end)
end)

target("specrunner_org", function()
  set_kind("binary")
  local PROJECTDIR = get_project_dir()
  add_files(path.join(PROJECTDIR, "tests/specrunner/**.cpp"))
  add_deps("haxorg")
  add_rules("haxorg.common_files", "haxorg.flags")
end)
