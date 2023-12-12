-- -*- indent-tabs-mode: nil; tab-width: 2 -*-

set_xmakever("2.8.2")
set_arch("x64")

add_rules("mode.debug")

-- TODO Add these parts into implementation 
      -- # Unclutter program output, save command execution to separate file
      -- - llvm-profdata merge -sparse *.profraw -o coverage.profdata > profdata_output.txt
      -- - llvm-cov show {{.BINARY}} -instr-profile=coverage.profdata -format=html > coverage.html
      -- - llvm-cov export -format=lcov -instr-profile=coverage.profdata {{.BINARY}} > coverage.lcov
      -- - llvm-cov export -format=text -instr-profile=coverage.profdata {{.BINARY}} > coverage.json
      -- - genhtml -o html coverage.lcov > genhtml_output.txt

        -- doxygen Doxyfile 2>&1 |
        -- rg --line-buffered warning |
        -- grep --line-buffered -v "not declared or defined"
-- TODO Add code checker run 


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

rule("dummy", function() 
  set_extensions(".txt", ".cpp", ".hpp")
end)

function any_files(file) add_files(file, { rule = "dummy" }) end
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
          target:get("deps"), 
          function(sub) 
            return vformat("\"%s\"", sub)
          end), ", ")
      ))
    end

    local formatted = vformat("digraph G {rankdir=TD;\nnode[shape=rect, fontname=consolas];\n%s\n}", table.concat(edges, "\n"))
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
  add_rules("dummy")

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

meta_target("haxorg_base_lexer", "Generate base lexer for haxorg", {}, function () 
  set_kind("phony")
  on_build(function(target)
    local utils = import("scripts.utils")
    local reflex = path.join(utils.abs_script(), "toolchain/RE-flex/bin/reflex")
    os.execv("poetry", {
      "run",
      "src/base_lexer/base_lexer.py"
    })
    os.execv(reflex, {
      "--fast",
      -- "--full",
      -- "--batch=1024",
      -- "--debug",
      "--nodefault",
      "--case-insensitive",
      "--outfile=" .. utils.abs_script("src/base_lexer/base_lexer_gen.cpp"),
      "--namespace=base_lexer",
      utils.abs_script("src/base_lexer/base_lexer.l")
    }, {
      ENVS = {
        LD_LIBRARY_PATH = path.join(utils.abs_script(), "toolchain/RE-flex/lib")
      }
    })
  end)
end)

meta_target("haxorg_codegen", "Execute haxorg code generation step.", {}, function() 
  set_kind("phony")
  add_deps("py_reflection")
  add_deps("cmake_utils")
  add_rules("dummy")
  any_files("scripts/py_codegen/codegen.py")
  any_files("build/reflection.pb")
  on_build(function(target) 
    local utils = import("scripts.utils")
    os.execv("poetry", {
      "run", 
      "scripts/py_codegen/codegen.py", 
      utils.abs_build(),
      utils.abs_script()
    })
    utils.info("Updated code definitions")
  end)
end)

meta_target("download_llvm", "Download LLVM toolchain dependency", {}, function()
    set_kind("phony")
    add_rules("dummy")
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
  add_rules("dummy")
  add_deps("download_llvm")
  add_files("scripts/cxx_codegen/CMakeLists.txt")

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
  add_rules("dummy")
  add_deps("cmake_configure_utils")
  any_files("scripts/cxx_codegen/**.hpp")
  any_files("scripts/cxx_codegen/**.cpp")
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
  add_rules("dummy")
  any_files("scripts/cxx_codegen/reflection_defs.proto")
  on_build(function(target)
    local utils = import("scripts.utils")
    local loc = utils.iorun_stripped("poetry", {"env", "info", "--path"})
    utils.info("Using protoc plugin path '%s'", loc)
    utils.rebuild_guard(target, function(target)
      os.execv("protoc", {
        "--plugin=" .. path.join(loc, "/bin/protoc-gen-python_betterproto"),
        "-I",
        utils.abs_script("scripts/cxx_codegen"),
        "--proto_path=" .. utils.abs_script("scripts/py_codegen"),
        "--python_betterproto_out=" .. utils.abs_script("scripts/py_codegen/proto_lib"),
        utils.abs_script("scripts/cxx_codegen/reflection_defs.proto")
      })
    end)
  end)
end)


meta_target("cmake_configure_haxorg", "Execute cmake configuration step for haxorg", {}, function() 
    set_kind("phony")
    add_rules("dummy")
    add_deps("download_llvm")
    add_deps("haxorg_codegen")
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
  add_rules("dummy")
  any_files("src/**.hpp")
  any_files("src/**.cpp")
  on_build(function(target)
    local utils = import("scripts.utils")
    utils.info("Running cmake haxorg build")
    local dbg = true
    os.execv("cmake", {
      "--build",
      path.join(os.scriptdir(), "build/haxorg_" .. (dbg and "debug" or "release")), {
        ENVS = { NINJA_FORCE_COLOR = "1" }
      }
    })
  end)
end)

meta_target("debug_pytests", "Execute lldb on the debug test target", {}, function () 
  on_run(function (target) 
    os.execv("poetry", {
      "run",
      "lldb",
      "--batch",
      "-o",
      "run tests/python/test_test.py",
      "--one-line-on-crash",
      "bt",
      "--one-line-on-crash",
      "exit",
      "--",
      "python",
    })
  end)
end)

meta_target("std_coverage", "Collect hstd coverage information", {}, function () 
  on_build(function(target)
    local utills = import("scripts.utils")
    local dir = path.join(os.scriptdir(), "build/haxorg/bin")
    local tools = path.join(os.scriptdir(), "toolchain/llvm/bin")
    local test = path.join(dir, "tests_hstd")

    for _, file in ipairs(os.files(path.join(dir, "*.profdata"))) do
      os.rm(file)
    end

    utils.with_dir(dir, function () 
      os.execv(test, {
        -- "--gtest_filter=VectorTest.*"
      })  
    end)

    os.execv(path.join(tools, "llvm-profdata"), {
      "merge",
      "-output=" .. path.join(dir, "test.profdata"),
      path.join(dir, "default.profraw")
    })

    os.execv(path.join(tools, "llvm-cov"), {
      "show",
      test,
      "-ignore-filename-regex", 
      ".*/_?deps/.*",
      "-instr-profile=" .. path.join(dir, "test.profdata"),
      "-format=html",
      "-output-dir=" .. path.join(dir, "coverage_report"),
    })
  end)
end)

meta_target("bench_profdata", "Collect performance profile", {}, function () 
  on_build(function(target)
    local utils = import("scripts.utils")
    local dir = path.join(os.scriptdir(), "build/haxorg/bin")
    local tools = path.join(os.scriptdir(), "toolchain/llvm/bin")
    local bench = path.join(dir, "bench")
    utils.info("Running benchmark from directory %s", dir)

    for _, file in ipairs(os.files(path.join(dir, "xray-log.bench.*"))) do
        os.rm(file)
    end

    for _, file in ipairs(os.files(path.join(dir, "*.profdata"))) do
        os.rm(file)
    end

    utils.with_dir(dir, function () 
      os.execv(bench, {}, {
        envs = {
          XRAY_OPTIONS = "patch_premain=true xray_mode=xray-basic verbosity=1"
        }
      })  
    end)


    local log_files = os.files(path.join(dir, "xray-log.bench.*"))  -- Adjust the pattern if necessary

    table.sort(log_files, function(a, b)
        return os.mtime(a) > os.mtime(b)
    end)

    if #log_files > 0 then
        utils.info("Latest XRay log file '%s'", log_files[1])
    else
        raise("No XRay log files found in '" .. dir .. "'")
    end

    local logfile = log_files[1]
    os.execv(path.join(tools, "llvm-xray"), {
      "convert",
      "--symbolize",
      "--instr_map=" .. bench,
      "--output-format=trace_event",
      "--output=" .. path.join(dir, "trace_events.json"),
      logfile,
    })

    os.execv(path.join(tools, "llvm-xray"), {
      "graph",
      "--instr_map=" .. bench,
      "--output=" .. path.join(dir, "trace_events.dot"),
      logfile,
    })

    os.execv(path.join(tools, "llvm-profdata"), {
      "merge",
      "-output=" .. path.join(dir, "bench.profdata"),
      path.join(dir, "default.profraw")
    })

    os.execv(path.join(tools, "llvm-cov"), {
      "show",
      bench,
      "-instr-profile=" .. path.join(dir, "bench.profdata"),
      "-format=html",
      "-output-dir=" .. path.join(dir, "coverage_report")
    })
  end)
  
end)

meta_target("test_python", "Execute python tests", {}, function()
  set_kind("phony")
  add_deps("cmake_haxorg")
  add_rules("dummy")
  on_run(function(target)
    os.execv("poetry", {"run", "pytest", "-s"})
  end)
end)
