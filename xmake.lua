
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

local target_metadata = {}

function meta_target(name, doc, metadata, callback)
  target(name, function()
    on_load(function(target)
      target:data_set("description", doc)
      target_metadata[name] = target
    end)
    callback()
  end)
end

meta_target("list_targets", "List all available targets", {}, function()
  set_kind("phony")
  on_run(function(x)
    for name, target in pairs(target_metadata) do
      cprint(vformat("${green}%-30s${clear} ${yellow}%s${clear}"), name, target:data("description"))
    end
  end)
end)

meta_target("haxorg_codegen", "Execute haxorg code generation step. Might update source in the repo", {}, function() 
  set_kind("phony")
  on_build(function(target) 
    os.execv("conda", {"run", "-n", "main", "scripts/code/py_codegen/test_codegen.py"})
  end)
end)

meta_target("conan_remove", "Remove installed conan dependencies", {}, function()
  set_kind("phony")
  on_run(function(target)
    os.execv("conan", {"remove", "'*'", "--force"})
  end)
end)

local function rel_conan()
  return path.join(os.scriptdir(), "build/dependencies/conan")
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
      path.join(os.scriptdir(), "conanprofile.txt")
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
    utils.rebuild_quard(target, function(target)
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
  end)
end)



meta_target("reflection_protobuf", "Update protobuf data definition for reflection", {}, function()
  set_kind("phony")
  add_files("scripts/code/reflection_defs.proto")
  on_build(function(target)
    local utils = import("scripts.utils")
    utils.rebuild_quard(target, function(target)
      utils.info("Rebulding reflection protobuf data")
      utils.with_dir("scripts/code/py_codegen", function() 
        os.execv("bash", {"build_reflection_defs.sh"})
      end)  
    end, function(target)
      utils.info("Skipping protobuf reflection rebuild")
    end)

  end)
end)


meta_target("cmake_configure_haxorg", "Execute cmake configuration step for haxorg", {}, function() 
    set_kind("phony")
    add_deps("download_llvm")
    add_files("CMakeLists.txt")

    on_build(function(target)
      local utils = import("scripts.utils")
      utils.rebuild_quard(target, function(target) 
        local dbg = false
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
      end, function(target) 
        utils.info("Skipping CMake run")
      end)
    end)
end)

meta_target("cmake_haxorg", "Compile libraries and binaries for haxorg", {}, function()
  set_kind("phony")
  add_deps("cmake_configure_haxorg")
  on_build(function(target)
    local dbg = false
    os.execv("cmake", {
      "--build",
      path.join(os.scriptdir(), "build/haxorg_" .. (dbg and "debug" or "release"))
    })
  end)
end)

