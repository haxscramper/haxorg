
set_xmakever("2.8.2")
set_arch("x64")

add_rules("mode.debug")

target("test_codegen", function() 
  set_kind("phony")
  on_build(function(target) 
    os.execv("conda", {"run", "-n", "main", "scripts/code/py_codegen/test_codegen.py"})
  end)
end)

target("download_llvm")
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

            -- Optionally, remove the downloaded archive
            os.rm("llvm.tar.xz")

            utils.info("LLVM downloaded and unpacked successfully!")
        else
            utils.info("LLVM already exists. Skipping download.")
        end
    end)


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

target("cmake_configure_haxorg", function() 
    set_kind("phony")
    add_deps("download_llvm")
    add_files("CMakeLists.txt")

    on_build(function(target)
      local utils = import("scripts.utils")
      utils.rebuild_quard(target, function() 
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
      end, function() 
        utils.info("Skipping CMake run")
      end)
    end)
end)

target("cmake_haxorg", function()
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
