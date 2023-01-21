add_requires("catch2")
add_rules("mode.debug")


target(
    "test",
    function()
        set_languages("c++20")
        add_includedirs("src/")
        add_includedirs("deps/result/include")
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
        after_build(
            function(target)
                os.exec(target:targetfile())
            end
        )

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
                        path.join(target:autogendir(), "autogen_enum_help.hpp"),
                        path.join(target:autogendir(), "autogen_enum_help.cpp")
                    }
                )

                target:add("sysincludedirs", target:autogendir())
            end
        )

    end
)
