add_requires("catch2")

target(
    "test",
    function()
        set_languages("c++20")
        add_includedirs("src/")
        add_includedirs("deps/result/include")
        add_files("tests/t*.cpp")
        add_packages("catch2", "result")
        after_build(
            function(target)
                os.exec(target:targetfile())
            end
        )
    end
)
