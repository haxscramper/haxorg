-- Define a rule that encapsulates all the flag logic
rule("haxorg.flags", function()
  on_config(function(target)
    local force_no_asan = target:extraconf("rules", "haxorg.flags",
                                           "force_no_asan") or false

    -- Emscripten build
    if get_config("org_emcc_build") then
      local emflags = {
        "-g4", "-gsource-map", "-s WASM=1", "-s STACK_SIZE=200MB",
        "-s ALLOW_MEMORY_GROWTH=1", "-s MODULARIZE=1", "-s ASSERTIONS=1",
        "-s EXPORT_NAME='haxorg_wasm'", "-s USE_PTHREADS=0", "--bind",
        "-sNO_DISABLE_EXCEPTION_CATCHING"
      }
      if get_config("org_use_perfetto") then
        table.insert(emflags, "-s INITIAL_HEAP=600MB")
      end
      table.insert(emflags, "-s EXCEPTION_DEBUG=1")
      if get_config("org_use_sanitizers") then
        table.join2(emflags, {
          "-fsanitize=undefined,address", "-sSAFE_HEAP", "-s SAFE_HEAP_LOG=1"
        })
      end
      target:add("ldflags", emflags, {force = true})
    end

    -- Non-develop build: suppress warnings
    if not get_config("org_build_is_develop") then
      if target:tool("cxx"):find("g++") or target:tool("cxx"):find("gcc") then
        target:add("cxflags", "-w", "-fmax-errors=1")
      end
      if target:tool("cxx"):find("clang") then target:add("cxflags", "-w") end
    end

    -- SARIF diagnostics
    if get_config("org_use_sarif") then
      target:add("cxflags", "-fdiagnostics-format=sarif")
    end

    -- Warning control
    if get_config("org_disable_warnings") then
      target:add("cxflags", "-Wno-everything")
    elseif get_config("org_build_assume_clang") then
      target:add("cxflags", "-Wno-reorder-init-list", "-Wno-c99-designator",
                 "-Wno-deprecated-declarations", "-Wno-unknown-attributes",
                 "-Wno-macro-redefined", "-Wno-unused-command-line-argument",
                 "-Wno-defaulted-function-deleted",
                 "-Wno-ambiguous-reversed-operator", "-Qunused-arguments")
    end
    target:add("cxflags", "-Werror=implicit-fallthrough")

    -- Output directories
    target:set("targetdir", get_config("builddir"))

    -- Instrument trace
    if get_config("org_instrument_trace") then
      target:add("cxflags", "-finstrument-functions")
    end

    -- Linker selection
    if get_config("org_use_xray") then
      -- xray path handled below
    elseif get_config("org_build_is_develop") then
      if get_config("org_build_use_gold_wrapper") then
        local base = get_config("base") or os.projectdir()
        local gold_dir = path.join(PROJECTDIR, "scripts/py_ci/py_ci")
        target:add("cxflags", "-fuse-ld=gold_wrap", "-B", gold_dir)
        target:add("ldflags", "-fuse-ld=gold_wrap", "-B", gold_dir)
      else
        target:add("cxflags", "-fuse-ld=lld")
        target:add("ldflags", "-fuse-ld=lld", "-Wl,--time-trace")
      end
    end

    -- C++23
    target:set("languages", "c++23")

    -- Clang time-trace
    if get_config("org_build_assume_clang") then
      target:add("cxflags", "-ftime-trace")
      target:add("ldflags", "-ftime-trace")
    end

    -- Clang-specific flags
    local cxx = target:tool("cxx") or ""
    if cxx:find("clang") then
      target:add("cxflags", "-fno-omit-frame-pointer", "-fPIC",
                 "-ftemplate-backtrace-limit=0")

      -- Sanitizers
      if get_config("org_use_sanitizer") and not force_no_asan then
        local base = get_config("base") or os.projectdir()
        target:add("cxflags", "-fsanitize=undefined,address", "-shared-libasan",
                   "-fsanitize-ignorelist=" ..
                       path.join(PROJECTDIR, "ignorelist.txt"))
        target:add("ldflags", "-fsanitize=undefined,address",
                   "-fsanitize-ignorelist=" ..
                       path.join(PROJECTDIR, "ignorelist.txt"))
        if get_config("asan_library") then
          target:add("links", get_config("asan_library"))
        end
      end

      -- XRay
      if get_config("org_use_xray") then
        local base = get_config("base") or os.projectdir()
        target:add("cxflags", "-fxray-instrument",
                   "-fxray-instruction-threshold=50", "-fxray-attr-list=" ..
                       path.join(PROJECTDIR,
                                 "scripts/cxx_repository/xray_list.txt"))
        target:add("ldflags", "-fxray-instrument")
      end

      -- Defines
      target:add("defines", "IMMER_TAGGED_NODE=0")
      if get_config("org_use_perfetto") then
        target:add("defines", "ORG_USE_PERFETTO")
      end
      if get_config("org_use_tracy") then
        target:add("defines", "ORG_USE_TRACY")
      end
      if get_config("org_use_xray") then
        target:add("defines", "ORG_USE_XRAY")
      end

      -- PGO
      if get_config("org_use_pgo") then
        target:add("defines", "ORG_USE_PGO")
        target:add("cxflags", "-fprofile-instr-generate", "-fcoverage-mapping")
        target:add("ldflags", "-fprofile-instr-generate", "-fcoverage-mapping")
      end

      target:add("defines", "QT_FORCE_ASSERTS")

      -- Profile use
      if get_config("profile_use") then
        local base = get_config("base") or os.projectdir()
        target:add("cxflags", "-fprofile-use=" ..
                       path.join(PROJECTDIR, "haxorg-compile.profdata"))
      end

      -- Coverage
      if get_config("org_use_coverage") then
        target:add("cxflags", "-fprofile-instr-generate", "-fcoverage-mapping",
                   "-ftest-coverage", "--coverage",
                   "-fprofile-filter-files=thirdparty", "--coverage",
                   "-fprofile-filter-files=base_lexer_gen", "--coverage",
                   "-fprofile-filter-files=pb\\.(cc|cpp|h|hpp)$")
        target:add("ldflags", "-lgcov", "--coverage",
                   "-fprofile-instr-generate", "-fcoverage-mapping")
      end
    end
  end)
end)

-- Rule for common files (sources, includes, standard)
rule("haxorg.common_files", function()
  on_config(function(target)
    local base = get_config("base") or os.projectdir()
    local autogen_build_dir = get_config("autogen_build_dir") or
                                  path.join(get_config("builddir"), "autogen")

    target:set("languages", "c++23")
    target:add("includedirs", path.join(PROJECTDIR, "src"))
    target:add("includedirs", autogen_build_dir)

    -- SRC_FILES and HEADER_FILES would be added per-target via add_files
  end)
end)

-- Rule for split debug info
rule("haxorg.split_debug", function()
  after_build(function(target)
    if get_config("org_separate_debug_symbols") then
      local targetfile = target:targetfile()
      local objcopy = target:tool("objcopy") or "objcopy"
      os.execv(objcopy,
               {"--only-keep-debug", targetfile, targetfile .. ".debug"})
      os.execv(objcopy, {"--strip-debug", targetfile})
      os.execv(objcopy,
               {"--add-gnu-debuglink=" .. targetfile .. ".debug", targetfile})
    end
  end)
end)
