from typing import Protocol, cast

from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import Environment


class RecipeOptions(Protocol):
    with_protobuf: bool
    with_protovalidate: bool
    with_perfetto: bool


class HaxorgCppOrgLibConan(ConanFile):
    name = "haxorg_cpp_org_lib"
    version = "0.1.0"

    settings = "os", "compiler", "build_type", "arch"

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
        "with_protovalidate": False,
        "with_perfetto": False,
    }

    exports_sources = (
        "CMakeLists.txt",
        "cmake/*",
        "src/*",
        "proto/*",
        "tests/*",
    )

    def validate(self):
        if self.options.with_protovalidate and not self.options.with_protobuf:
            raise ConanInvalidConfiguration("with_protovalidate requires with_protobuf")

    def requirements(self):
        transitive = {
            "transitive_headers": True,
            "transitive_libs": True,
        }

        self.requires("hstd_cpp_lib/0.1.0", **transitive)
        self.requires("hstd_cpp_text_layout/0.1.0", **transitive)

        self.requires("foonathan-lexy/[>=2025.05.0 <2026]", **transitive)
        self.requires("range-v3/[>=0.12.0 <1]", **transitive)
        self.requires("immer/[>=0.8.1 <1]", **transitive)
        self.requires("nlohmann_json/[>=3.12.0 <4]", **transitive)

        if self.options.with_protobuf:
            self.requires("protobuf/[>=5 <6]", **transitive)

        if self.options.with_protovalidate:
            self.requires("protovalidate-cc/1.1.0", **transitive)

        if self.options.with_perfetto:
            self.requires("perfetto/[>=52.0 <53]", **transitive)

    def build_requirements(self):
        self.test_requires("gtest/[>=1.17 <2]")
        self.test_requires("abseil/[>=20250127.0 <20260000]")

        if self.options.with_protobuf:
            self.tool_requires("protobuf/[>=5 <6]")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        skip_tests = self.conf.get(
            "tools.build:skip_test",
            default=False,
            check_type=bool,
        )

        toolchain = CMakeToolchain(self)
        toolchain.cache_variables["HAXORG_WITH_PROTOBUF"] = self.options.with_protobuf
        toolchain.cache_variables["HAXORG_WITH_PROTOVALIDATE"] = (
            self.options.with_protovalidate
        )
        toolchain.cache_variables["HAXORG_WITH_PERFETTO"] = self.options.with_perfetto
        toolchain.cache_variables["BUILD_TESTING"] = not skip_tests
        toolchain.generate()

        dependencies = CMakeDeps(self)
        dependencies.generate()

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
        self.cpp_info.builddirs = ["lib/cmake/HaxorgCppOrgLib"]
        self.cpp_info.set_property("cmake_find_mode", "none")
