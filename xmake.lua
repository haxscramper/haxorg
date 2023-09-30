-- -*- indent-tabs-mode: nil; tab-width: 2 -*-

set_xmakever("2.8.2")
set_arch("x64")

add_rules("mode.debug")



local cmake_options = {
    {"USE_PCH", "Use precompiled headers", true},
    {"TRACE_INSTRUMENT", "Generate instrumentation trace", false},
    {"TEST_COVERAGE", "Enable test coverage", false},
    {"MAX_COMPILE_ERRORS", "Max number of compilation errors before compiler stops", false},
    {"USE_PERFETTO", "Enable perfetto profiling", false},
    {"PROFILE_GENERATE", "Compile binary with profile data generation", false},
    {"PROFILE_USE", "Compile binary using profile data generation", false},
    {"USE_XRAY", "Use LLVM XRay instrumentation for profiling", false},
    {"USE_SANITIZER", "Use sanitizers", true}
}

for _, it in ipairs(cmake_options) do
  option("haxorg." .. it[1])
    set_description(it[2])
    set_default(it[3])
  option_end()
end

function meta_target(name, doc, metadata, callback)
  target(name, function()
    on_load(function(target)
      target:data_set("description", doc)
    end)
    callback()
  end)
end

rule("dummy", function() end)

function any_files(file) add_files(file, { rule = "dummy"}) end
function abs_build(...) return path.absolute(vformat("$(buildir)"), ...) end
function abs_script(...) return path.absolute(vformat("$(scriptir)"), ...) end

task("list_targets", function()
  set_category("action")
  on_run(function(target)
    import("core.project.project")
    import("core.project.config")
    config.load()
    project.load_targets()
    for _, target in ipairs(project.ordertargets()) do
      cprint(vformat("${green}%-30s${clear} ${yellow}%s${clear}"), target:name(), target:data("description"))
    end
  end)

  set_menu({
    description = "List all available targets",
    usage = "xmake list_targets"
  })
end)

task("graphviz_targets", function()
  set_menu({
    description = "Generate graphviz for described project dependencies",
    usage = "xmake graphviz_targets"
  })

  on_run(function(x)
    import("core.project.project")
    import("core.project.config")
    config.load()
    project.load_targets()

    local utils = import("scripts.utils")
    local edges = {}
    for _, target in ipairs(project.ordertargets()) do
      table.insert(edges, vformat(
        "\"%s\"[label=\"%s\"];",
        target:name(),
        target:name() .. "\n" .. target:data("description")
      ))
      table.insert(edges, vformat(
        "\"%s\" -> {%s};", 
        target:name(), 
        table.concat(utils.list_map(
          target:deps(), 
          function(sub) 
            return vformat("\"%s\"", sub:name())
          end), ", ")
      ))
    end

    local formatted = vformat("digraph G {rankdir=LR;\nnode[shape=rect, fontname=consolas];\n%s\n}", table.concat(edges, "\n"))
    local dot = path.join(vformat("$(buildir)"), "deps.dot")
    local file = io.open(dot, "w")
    if file then
      file:write(formatted)
      file:close()
    else
      print("????????????????")
    end
    local png = path.join(vformat("$(buildir)"), "deps.png")
    os.execv("dot", {"-Tpng", "-o", png, dot})
    utils.info("Wrote dependency graph to %s", png)
  end)
end)




meta_target("py_reflection", "Update reflection artifacts using standalone build tool", {}, function()
  set_kind("phony")
  add_files("src/py_libs/pyhaxorg/pyhaxorg_manual_impl.hpp")
  any_files("build/utils/reflection_tool")
  any_files("xmake.lua")

  add_deps("cmake_utils")
  add_deps("reflection_protobuf")
  on_build(function(target)
    local utils = import("scripts.utils")
    utils.rebuild_guard(target, function(target)
      local ok = utils.maybe_try(
        function () 
          os.execv("build/utils/reflection_tool", {
            "-p=build/haxorg/compile_commands.json",
            "--compilation-database=build/haxorg/compile_commands.json",
            "--toolchain-include=" .. utils.abs_script("toolchain/llvm/lib/clang/16/include"),
            "--out=" .. utils.abs_build("reflection.pb"),
            "src/py_libs/pyhaxorg/pyhaxorg.cpp"
          })       
        end,
        function (errors)
          utils.error(errors)      
        end,
        nil,
        true
      )
    end)
  end)
end)

meta_target("haxorg_codegen", "Execute haxorg code generation step.", {}, function() 
  set_kind("phony")
  add_deps("py_reflection")
  add_deps("cmake_utils")
  any_files("scripts/code/py_codegen/codegen.py")
  any_files("build/reflection.pb")
  on_build(function(target) 
    local utils = import("scripts.utils")
    os.execv("poetry", {
      "run", 
      "scripts/code/py_codegen/codegen.py", 
      utils.abs_build(),
      utils.abs_script()
    })
    utils.info("Updated code definitions")
  end)
end)

meta_target("conan_remove", "Remove installed conan dependencies", {}, function()
  set_kind("phony")
  on_run(function(target)
    os.execv("conan", {"remove", "'*'", "--force"})
  end)
end)

local function rel_conan()
  return abs_script("build/dependencies/conan")
end

meta_target("conan_install", "Install conan dependencies", {}, function() 
  set_kind("phony")
  add_files("conanprofile.txt", "conanfile.txt")
  on_run(function(target)
    os.execv("conan", {
      "install",
      ".",
      "--install-folder",
      rel_conan(),
      "--build=missing",
      "--profile",
      abs_script("conanprofile.txt")
    })
  end)
end)

meta_target("download_llvm", "Download LLVM toolchain dependency", {}, function()
    set_kind("phony")
    on_build(function(target)
        local utils = import("scripts.utils")
        -- Check if the directory exists
        if not os.isdir("toolchain/llvm") then
            print("LLVM not found. Downloading...")
            
            -- Download the archive
            os.exec("curl -L -o llvm.tar.xz https://github.com/llvm/llvm-project/releases/download/llvmorg-16.0.3/clang+llvm-16.0.3-x86_64-linux-gnu-ubuntu-22.04.tar.xz")
            
            -- Create the toolchain directory if it doesn't exist
            if not os.isdir("toolchain") then
                os.mkdir("toolchain")
            end

            -- Unpack the archive
            os.exec("tar -xf llvm.tar.xz -C toolchain && mv toolchain/clang+llvm-16.0.3-x86_64-linux-gnu-ubuntu-22.04 toolchain/llvm")

            os.rm("llvm.tar.xz")

            utils.info("LLVM downloaded and unpacked successfully!")
        else
            utils.info("LLVM already exists. Skipping download.")
        end
    end)
end)

meta_target("cmake_configure_utils", "Execute configuration for utility binary compilation", {}, function()
  set_kind("phony")
  add_deps("download_llvm")
  add_files("scripts/code/CMakeLists.txt")

  on_run(function(target)
    local utils = import("scripts.utils")
    utils.rebuild_guard(target, function(target)
      local dbg = true
      local pass_flags = {
        "-B", 
        os.scriptdir() .. "/build/utils_" .. (dbg and "debug" or "release"),
        "-S",
        os.scriptdir(),
        "-DCMAKE_BUILD_TYPE=" .. (dbg and "Debug" or "RelWithDebInfo"),
        "-DCMAKE_CXX_COMPILER=" .. path.join(os.scriptdir(), "toolchain/llvm", "bin/clang++")
      }

      os.execv("cmake", pass_flags)
    end)
  end)
end)

meta_target("cmake_utils", "Compile libraries and binaries for utils", {}, function()
  set_kind("phony")
  add_deps("cmake_configure_utils")
  on_build(function(target)
    local dbg = true
    os.execv("cmake", {
      "--build",
      path.join(os.scriptdir(), "build/utils_" .. (dbg and "debug" or "release"))
    })
    import("scripts.utils").info("CMake utils build ok")
  end)
end)



meta_target("reflection_protobuf", "Update protobuf data definition for reflection", {}, function()
  set_kind("phony")
  any_files("scripts/code/reflection_defs.proto")
  on_build(function(target)
    local utils = import("scripts.utils")
    local loc = utils.iorun_stripped("poetry", {"env", "info", "--path"})
    utils.info("Using protoc plugin path '%s'", loc)
    utils.rebuild_guard(target, function(target)
      os.execv("protoc", {
        "--plugin=" .. path.join(loc, "/bin/protoc-gen-python_betterproto"),
        "-I",
        utils.abs_script("scripts/code/py_codegen"),
        "--proto_path=" .. utils.abs_script("scripts/code"),
        "--python_betterproto_out=" .. utils.abs_script("scripts/code/py_codegen/proto_lib"),
        utils.abs_script("scripts/code/reflection_defs.proto")
      })
    end)
  end)
end)


meta_target("cmake_configure_haxorg", "Execute cmake configuration step for haxorg", {}, function() 
    set_kind("phony")
    add_deps("download_llvm")
    add_files("CMakeLists.txt")

    on_build(function(target)
      local utils = import("scripts.utils")
      utils.rebuild_guard(target, function(target) 
        local dbg = true
        local pass_flags = {
          "-B", 
          os.scriptdir() .. "/build/haxorg_" .. (dbg and "debug" or "release"),
          "-S",
          os.scriptdir(),
          "-DCMAKE_BUILD_TYPE=" .. (dbg and "Debug" or "RelWithDebInfo"),
          "-DCMAKE_CXX_COMPILER=" .. path.join(os.scriptdir(), "toolchain/llvm", "bin/clang++")
        }

        for name in utils.tuple_iter(cmake_options) do
          table.insert(pass_flags, "-D" .. name .. "=" .. (get_config("haxorg." .. name) and "ON" or "OFF"))
        end

        os.execv("cmake", pass_flags)
      end)
    end)
end)

meta_target("cmake_haxorg", "Compile libraries and binaries for haxorg", {}, function()
  set_kind("phony")
  add_deps("cmake_configure_haxorg")
  -- any_files("src/**.hpp")
  -- any_files("src/**.cpp")
  on_build(function(target)
    local dbg = true
    os.execv("cmake", {
      "--build",
      path.join(os.scriptdir(), "build/haxorg_" .. (dbg and "debug" or "release"))
    })
  end)
end)

meta_target("test_python", "Execute python tests", {}, function()
  set_kind("phony")
  add_deps("cmake_haxorg")
  on_run(function(target)
    os.execv("poetry", {"run", "pytest"})
  end)
end)
