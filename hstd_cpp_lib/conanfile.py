from typing import Protocol, cast

from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import (
    CMake,
    CMakeDeps,
    CMakeToolchain,
    cmake_layout,
)
from conan.tools.env import Environment


class RecipeOptions(Protocol):
    with_protobuf: bool
    with_protovalidate: bool
    with_perfetto: bool


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

    options = cast(
        RecipeOptions,
        {
            "with_protobuf": [True, False],
            "with_protovalidate": [True, False],
            "with_perfetto": [True, False],
        },
    )

    default_options = {
        "with_protobuf": True,
        "with_protovalidate": True,
        "with_perfetto": True,
    }

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
        if self.options.with_perfetto:
            self.requires("perfetto/[>=46 <100]", transitive_headers=True)

        if self.options.with_protobuf:
            self.requires("protobuf/[>=5 <6]")

        if self.options.with_protovalidate:
            # for protovalidate dependency
            self.requires("re2/[>=20230301]")
            self.requires("protovalidate-cc/1.1.0")

    def build_requirements(self):
        self.test_requires("gtest/[>=1.15 <2]")
        self.test_requires("benchmark/[>=1.9 <2]")
        self.test_requires("abseil/[>=20240722.0 <20260000]")
        self.test_requires("immer/[>=0.8 <1]")
        self.tool_requires("protobuf/[>=5 <6]")

    def layout(self):
        cmake_layout(self)

        cmake_module_names = [
            "functions_aux.cmake",
            "functions_setup.cmake",
            "hstd_cpp_lib_proto.cmake",
        ]

        # Editable / workspace consumption: source tree
        self.cpp.source.includedirs = ["src", "."]
        self.cpp.source.set_property(
            "cmake_build_modules",
            [f"cmake/{name}" for name in cmake_module_names],
        )

        # Editable / workspace consumption: build tree (generated proto headers + built lib)
        self.cpp.build.includedirs = ["."]
        self.cpp.build.libdirs = ["."]

        # Regular installed package
        self.cpp.package.includedirs = ["include"]
        self.cpp.package.set_property(
            "cmake_build_modules",
            [f"lib/cmake/hstd_cpp_lib/{name}" for name in cmake_module_names],
        )

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

        # TODO: remove this option entirely, create a separate package for qt utils
        toolchain.variables["ORG_BUILD_WITH_QT"] = False
        # TODO: Infer the compilation configuration from the compiler, do not
        # request explicit flag
        toolchain.variables["ORG_BUILD_EMCC"] = False

        toolchain.variables["HSTD_CPP_BUILD_WITH_PERFETTO"] = bool(
            self.options.with_perfetto
        )
        toolchain.variables["HSTD_CPP_BUILD_WITH_PROTOBUF"] = bool(
            self.options.with_protobuf
        )
        toolchain.variables["HSTD_CPP_BUILD_WITH_PROTOVALIDATE"] = bool(
            self.options.with_protovalidate
        )

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

        self.cpp_info.defines = [
            f"HSTD_CPP_BUILD_WITH_PROTOBUF={int(bool(self.options.with_protobuf))}",
            f"HSTD_CPP_BUILD_WITH_PROTOVALIDATE={int(bool(self.options.with_protovalidate))}",
            f"HSTD_CPP_BUILD_WITH_PERFETTO={int(bool(self.options.with_perfetto))}",
        ]

        self.cpp_info.libs = ["hstd_cpp_lib"]

    # custom functionality
