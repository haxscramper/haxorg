from conan import ConanFile


class HaxdexCppReflReadConan(ConanFile):
    name = "haxdex_read_code_cpp"
    version = "0.1.0"
    package_type = "application"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"
    provided_binaries = ["haxdex_read_code_cpp"]

    default_options = {
        "hwloc/*:shared": True,
    }

    exports_sources = (
        "CMakeLists.txt",
        "cmake/*",
        "src/*",
        "tests/*",
    )

    def requirements(self):
        self.requires(
            "hstd_cpp_lib/0.1.0",
            transitive_headers=True,
            transitive_libs=True,
        )
        self.requires(
            "haxdex_read_code_cpp_common/0.1.0",
            transitive_headers=True,
            transitive_libs=True,
        )
