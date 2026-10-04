from conan import ConanFile


class HstdCppDiagramLibConan(ConanFile):
    name = "hstd_cpp_diagram_lib"
    version = "0.1.0"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"

    exports_sources = (
        "CMakeLists.txt",
        "cmake/*",
        "jni_elk/*",
        "proto/*",
        "src/*",
        "tests/*",
    )

    haxorg_package_libs = (
        "hstd_cpp_diagram_lib",
        "jni_elk_lib",
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
        self.requires(
            "kiwi/1.5.1",
            transitive_headers=True,
            transitive_libs=True,
        )
        self.requires(
            "graphviz/15.1.0",
            transitive_headers=True,
            transitive_libs=True,
        )
        self.requires(
            "adaptagrams/0.0.20251029",
            transitive_headers=True,
            transitive_libs=True,
        )

    def build_requirements(self):
        self.tool_requires("protobuf/<host_version>")
        self.test_requires("gtest/1.15.0")
