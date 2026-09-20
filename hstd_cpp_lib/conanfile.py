from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import (
    CMake,
    CMakeDeps,
    CMakeToolchain,
    cmake_layout,
)
from conan.tools.env import Environment


class HstdConan(ConanFile):
    name = "hstd_cpp_lib"
    version = "0.1.0"
    package_type = "static-library"

    settings = "os", "arch", "compiler", "build_type"

    exports_sources = (
        "src/*",
        "tests/*",
        "proto/*",
        "CMakeLists.txt",
        "cmake/*",
    )

    def requirements(self):
        self.requires("yaml-cpp/[>=0.8.0 <0.9]", transitive_headers=True)
        # TODO: range-v3 could be made non-transitive, in theory, but it
        # would require separate cleanup of the headers.
        self.requires("range-v3/[>=0.12.0 <0.13]", transitive_headers=True)
        self.requires("nlohmann_json/[>=3.11.3 <4]", transitive_headers=True)
        self.requires("cctz/[>=2.4.0 <3]", transitive_headers=True)
        self.requires("fmt/[>=11 <13]", transitive_headers=True)
        self.requires("boost/[>=1.86.0 <2]", transitive_headers=True)
        self.requires("cpptrace/[>=0.8.0 <2]", transitive_headers=True)
        self.requires("protobuf/[>=5 <6]")
        self.requires("perfetto/[>=46 <100]", transitive_headers=True)
        self.requires("tracy/[>=0.11 <1]")
        # for protovalidate dependency
        self.requires("re2/[>=20230301]")
        self.requires("protovalidate-cc/1.1.0")

    def build_requirements(self):
        self.test_requires("gtest/[>=1.15 <2]")
        self.test_requires("benchmark/[>=1.9 <2]")
        self.test_requires("abseil/[>=20240722.0 <20270000]")
        self.test_requires("immer/[>=0.8 <1]")
        self.tool_requires("protobuf/[>=5 <6]")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        dependencies = CMakeDeps(self)

        # Keep only overrides that are actually necessary. Conan Center
        # recipes generally already publish their canonical target names.
        dependencies.set_property(
            "perfetto",
            "cmake_file_name",
            "Perfetto",
        )
        dependencies.set_property(
            "perfetto",
            "cmake_target_name",
            "Perfetto::perfetto",
        )

        dependencies.set_property(
            "tracy",
            "cmake_file_name",
            "Tracy",
        )
        dependencies.set_property(
            "tracy",
            "cmake_target_name",
            "Tracy::TracyClient",
        )

        dependencies.generate()

        skip_tests = self.conf.get(
            "tools.build:skip_test",
            default=False,
            check_type=bool,
        )

        toolchain = CMakeToolchain(self)

        warning_suppressions = self.conf.get(
            "user.hstd:warning_suppressions",
            default="",
            check_type=str,
        )

        if warning_suppressions:
            toolchain.variables["ORG_WARNING_SUPPRESSIONS"] = warning_suppressions

        toolchain.variables["ORG_BUILD_WITH_QT"] = False
        toolchain.variables["ORG_BUILD_EMCC"] = False

        toolchain.variables["ORG_BUILD_WITH_PERFETTO"] = True
        toolchain.variables["ORG_BUILD_WITH_TRACY"] = True
        toolchain.variables["ORG_BUILD_WITH_PROTOBUF"] = True
        toolchain.variables["ORG_BUILD_WITH_PROTOVALIDATE"] = True

        toolchain.variables["ORG_BUILD_TESTS"] = not skip_tests
        toolchain.variables["BUILD_TESTING"] = not skip_tests
        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        ninja_args = self.conf.get(
            "user.hstd:ninja_args",
            default=[],
            check_type=list,
        )
        cmake.build(build_tool_args=ninja_args)

        skip_tests = self.conf.get(
            "tools.build:skip_test",
            default=False,
            check_type=bool,
        )

        if not skip_tests and can_run(self):
            environment = Environment()
            environment.define("CTEST_OUTPUT_ON_FAILURE", "1")

            with environment.vars(self).apply():
                cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "hstd_cpp_lib")
        self.cpp_info.set_property("cmake_target_name", "hstd::hstd_cpp_lib")

        cmake_modules = [
            "lib/cmake/hstd_cpp_lib/functions_aux.cmake",
            "lib/cmake/hstd_cpp_lib/functions_setup.cmake",
        ]

        self.cpp_info.set_property("cmake_build_modules", cmake_modules)

        self.cpp_info.libs = ["hstd_cpp_lib"]
        self.cpp_info.includedirs = ["include"]

    # custom functionality
