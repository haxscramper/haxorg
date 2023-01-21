add_requires("catch2")
add_rules("mode.debug")

function on_g4_build(target, batchcmds, sourcefile_antlr4, opt)
    local sourcedir_cx =
        path.join(
        target:autogendir(),
        "rules",
        "antlr4",
        path.basename(sourcefile_antlr4)
    )

    -- target:add_files(sourcedir_cx .. "/*.cpp")

    -- add commands
    batchcmds:show_progress(
        opt.progress,
        "${color.build.object}compiling.antlr4 %s",
        sourcefile_antlr4
    )
    batchcmds:mkdir(path.directory(sourcedir_cx))

    batchcmds:vrunv(
        "/usr/lib/jvm/java-11-openjdk/bin/java",
        {
            "-jar",
            "/usr/share/java/antlr-complete.jar",
            "-Dlanguage=Cpp",
            "-visitor",
            "-o",
            path(sourcedir_cx),
            path(sourcefile_antlr4)
        }
    )

    for _, file in ipairs(os.files(sourcedir_cx .. "/*.cpp")) do
        local objectfile = target:objectfile(file)
        table.insert(target:objectfiles(), objectfile)
        batchcmds:compile(file, objectfile)
    end

    -- add deps
    batchcmds:add_depfiles(sourcefile_antlr4)
    -- batchcmds:set_depmtime(os.mtime(objectfile))
    -- batchcmds:set_depcache(target:dependfile(objectfile))
end

rule(
    "antlr4",
    function()
        set_extensions(".g4")
        on_buildcmd_file(on_g4_build)
    end
)

function run_target_after_build()
    after_build(
        function(target)
            os.exec(target:targetfile())
        end
    )
end

function add_antlr_configurations()
    set_kind("binary")
    add_links("antlr4-runtime")
    add_rules("antlr4")
    add_includedirs("/usr/include/antlr4-runtime")
end

target(
    "plantuml_parser",
    function()
        set_languages("c++20")
        add_antlr_configurations()
        add_files("src/grammars/PlantUML.g4")
        run_target_after_build()
    end
)

target(
    "test",
    function()
        set_languages("c++20")
        add_includedirs("src/")
        add_includedirs("deps/result/include")

        -- FIXME attempt to use backward-cpp library failed because it does
        -- not seem to work properly with debug mode enabled (`malloc():
        -- unaligned tcache chunk detected` error with `-m debugg`) and
        -- does not have enough information to proceed without debug
        -- information. Using it in a standalone manner worked fine, which
        -- means `xmake` breaks the compilation in some way.
        --
        -- add_includedirs("deps/backward-cpp")

        -- add_links("dw")
        -- add_defines("BACKWARD_HAS_DW=1")

        -- add_links("bfd", "dl")
        -- add_defines("BACKWARD_HAS_BFD=1")

        -- add_links("dwarf", "backward", "")
        -- add_defines("BACKWARD_HAS_DWARF=1")
        -- add_includedirs("/usr/include/libdwarf/libdwarf-0/")

        -- add_files("deps/backward-cpp/backward.cpp")

        add_files("tests/t*.cpp")
        add_files("src/**/*.cpp")
        add_packages("catch2", "result")
        run_target_after_build()

        before_build(
            function(target)
                os.execv(
                    "src/scripts/generate_type_info.py",
                    {
                        "src/types/enums.hpp",
                        path.join(target:autogendir(), "enum.json")
                    }
                )
                os.execv(
                    "src/scripts/generate_type_aux.py",
                    {
                        path.join(target:autogendir(), "enum.json"),
                        path.join(
                            target:autogendir(),
                            "autogen_enum_help.hpp"
                        ),
                        path.join(
                            target:autogendir(),
                            "autogen_enum_help.cpp"
                        )
                    }
                )

                target:add("sysincludedirs", target:autogendir())
            end
        )
    end
)
