from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class HstdConan(ConanFile):
    name = "hstd"
    version = "0.1.0"
    package_type = "static-library"

    settings = "os", "arch", "compiler", "build_type"

    exports_sources = (
        "*",
        "!tests",
    )

    generators = ()

    def requirements(self):
        self.requires("yaml-cpp/[>=0.8.0 <0.9]")
        self.requires("range-v3/[>=0.12.0 <0.13]")
        self.requires("nlohmann_json/[>=3.11.3 <4]")
        self.requires("cctz/[>=2.4.0 <3]")
        self.requires("fmt/[>=11 <13]")
        self.requires("boost/[>=1.86.0 <2]")
        self.requires("cpptrace/[>=0.8.0 <2]")
        self.requires("protobuf/[>=5 <7]")
        self.requires("graphviz/[>=12 <15]")
        self.requires("perfetto/[>=46 <100]")
        self.requires("tracy/[>=0.11 <1]")

    def build_requirements(self):
        self.test_requires("gtest/[>=1.15 <2]")
        self.test_requires("benchmark/[>=1.9 <2]")
        self.test_requires("abseil/[>=20240722.0 <20270000]")
        self.test_requires("immer/[>=0.8 <1]")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        dependencies = CMakeDeps(self)

        dependencies.set_property("yaml-cpp", "cmake_file_name", "yaml-cpp")
        dependencies.set_property(
            "yaml-cpp",
            "cmake_target_name",
            "yaml-cpp::yaml-cpp",
        )

        dependencies.set_property("range-v3", "cmake_file_name", "range-v3")
        dependencies.set_property(
            "range-v3",
            "cmake_target_name",
            "range-v3::range-v3",
        )

        dependencies.set_property(
            "nlohmann_json",
            "cmake_file_name",
            "nlohmann_json",
        )
        dependencies.set_property(
            "nlohmann_json",
            "cmake_target_name",
            "nlohmann_json::nlohmann_json",
        )

        dependencies.set_property("cctz", "cmake_file_name", "cctz")
        dependencies.set_property(
            "cctz",
            "cmake_target_name",
            "cctz::cctz",
        )

        dependencies.set_property("fmt", "cmake_file_name", "fmt")
        dependencies.set_property("fmt", "cmake_target_name", "fmt::fmt")

        dependencies.set_property("cpptrace", "cmake_file_name", "cpptrace")
        dependencies.set_property(
            "cpptrace",
            "cmake_target_name",
            "cpptrace::cpptrace",
        )

        dependencies.set_property("perfetto", "cmake_file_name", "Perfetto")
        dependencies.set_property(
            "perfetto",
            "cmake_target_name",
            "Perfetto::perfetto",
        )

        dependencies.set_property("tracy", "cmake_file_name", "Tracy")
        dependencies.set_property(
            "tracy",
            "cmake_target_name",
            "Tracy::TracyClient",
        )

        dependencies.generate()

        toolchain = CMakeToolchain(self)
        toolchain.variables["ORG_BUILD_WITH_QT"] = False
        toolchain.variables["ORG_BUILD_EMCC"] = False

        toolchain.variables["ORG_BUILD_WITH_PERFETTO"] = True
        toolchain.variables["ORG_BUILD_WITH_TRACY"] = True
        toolchain.variables["ORG_BUILD_WITH_PROTOBUF"] = True

        toolchain.variables["ORG_BUILD_TESTS"] = True
        toolchain.variables["BUILD_TESTING"] = True

        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

        if can_run(self):
            cmake.test(cli_args=["--output-on-failure"])

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "hstd")
        self.cpp_info.set_property("cmake_target_name", "hstd::hstd")
        self.cpp_info.libs = ["hstd"]
        self.cpp_info.includedirs = ["src"]
