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

            print("LLVM downloaded and unpacked successfully!")
        else
            print("LLVM already exists. Skipping download.")
        end
    end)

local function tuple_iter(tuples)
    local i = 0
    return function()
        i = i + 1
        if tuples[i] then
            return unpack(tuples[i])
        end
    end
end

function def_option(name, doc, default)
  option(name)
    set_description(doc)
    set_default(default)
  option_end()
end

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

for name, doc, default in tuple_iter(cmake_options) do
  def_option("haxorg." .. name, doc, default)
end

target("cmake_configure_haxorg", function() 
    set_kind("phony")
    add_deps("download_llvm")
    add_files("CMakeFiles.txt")

    on_build(function(target)
      local dbg = false
      local pass_flags = {
        "-B", 
        os.scriptdir() .. "/build/haxorg_" .. (dbg and "debug" or "release"),
        "-S",
        os.scriptdir(),
        "-DCMAKE_BUILD_TYPE=" .. (dbg and "Debug" or "RelWithDebInfo"),
        "-DCMAKE_CXX_COMPILER=" .. path.join(os.scriptdir(), "toolchain/llvm", "bin/clang++")
      }

      for name in tuple_iter(cmake_options) do
        table.insert(pass_flags, "-D" .. name .. "=" .. (get_config("haxorg." .. name) and "ON" or "OFF"))
      end

      os.execv("cmake", pass_flags)
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
