add_requires("catch2")

target(
    "test",
    function()
        set_languages("c++20")
        add_includedirs("src/")
        add_includedirs("deps/result/include")
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
