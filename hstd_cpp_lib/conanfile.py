from typing import Protocol, cast

from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain


class RecipeOptions(Protocol):
    with_protobuf: bool
    with_protovalidate: bool
    with_perfetto: bool


class HstdConan(ConanFile):
    name = "hstd_cpp_lib"
    version = "0.1.0"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"

    haxorg_cmake_build_modules = (
        "functions_aux.cmake",
        "functions_setup.cmake",
    )

    options = cast(
        RecipeOptions,
        {
            "with_protobuf": [True, False],
            "with_protovalidate": [True, False],
            # TODO: This option is very similar to qt -- it might be unnecessary
            # to actually compile the perfetto utilities into the main package
            # instead i can define everything using inline functions or
            # configure the dependent packages to include a special header for the
            # sources.
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
            self.requires("re2/[>=20230301]")
            self.requires("protovalidate-cc/1.1.0")

    def build_requirements(self):
        self.test_requires("gtest/[>=1.15 <2]")
        self.test_requires("benchmark/[>=1.9 <2]")
        self.test_requires("abseil/[>=20240722.0 <20260000]")
        self.test_requires("immer/[>=0.8 <1]")
        self.tool_requires("protobuf/[>=5 <6]")

    def haxorg_configure_deps(self, deps: CMakeDeps):
        deps.set_property("perfetto", "cmake_file_name", "Perfetto")
        deps.set_property("perfetto", "cmake_target_name", "Perfetto::perfetto")

    def haxorg_configure_toolchain(self, toolchain: CMakeToolchain):
        # TODO: remove this option entirely, create a separate package for qt utils
        toolchain.variables["ORG_BUILD_WITH_QT"] = False
        # TODO: Infer the compilation configuration from the compiler
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

    def haxorg_package_info(self):
        self.cpp_info.defines = [
            f"HSTD_CPP_BUILD_WITH_PROTOBUF={int(bool(self.options.with_protobuf))}",
            f"HSTD_CPP_BUILD_WITH_PROTOVALIDATE={int(bool(self.options.with_protovalidate))}",
            f"HSTD_CPP_BUILD_WITH_PERFETTO={int(bool(self.options.with_perfetto))}",
        ]
