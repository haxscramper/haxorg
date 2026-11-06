from conan import ConanFile


class HstdCppSoufleSerdeConan(ConanFile):
    name = "hstd_cpp_souffle_serde"
    version = "0.1.0"
    package_type = "shared-library"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"
    provided_libraries = ["libhstd_cpp_souffle_serde.so"]

    exports_sources = (
        "CMakeLists.txt",
        "cmake/*",
        "src/*",
        "tests/*",
    )

    def requirements(self):
        self.requires("nlohmann_json/[>=3.11.3 <4]", transitive_headers=True)
        self.requires("fmt/[>=11 <17]", transitive_headers=True)
