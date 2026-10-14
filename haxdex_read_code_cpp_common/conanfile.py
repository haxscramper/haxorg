from conan import ConanFile


class HaxdexReadCodeCppCommonConan(ConanFile):
    name = "haxdex_read_code_cpp_common"
    version = "0.1.0"
    package_type = "static-library"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"

    exports_sources = (
        "CMakeLists.txt",
        "cmake/*",
        "src/*",
        "proto/*",
    )

    def requirements(self):
        self.requires(
            "hstd_cpp_lib/0.1.0",
            transitive_headers=True,
            transitive_libs=True,
        )
        self.requires(
            "protobuf/[>=5 <6]",
            transitive_headers=True,
            transitive_libs=True,
        )

    def build_requirements(self):
        self.tool_requires("protobuf/[>=5 <6]")
