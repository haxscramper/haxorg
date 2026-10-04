from typing import Protocol, cast

from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMakeDeps, CMakeToolchain


class RecipeOptions(Protocol):
    with_protobuf: bool
    with_protovalidate: bool
    with_perfetto: bool


class HaxorgCppOrgLibConan(ConanFile):
    name = "haxorg_cpp_org_lib"
    version = "0.1.0"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"

    haxorg_header_patterns = ("*.hpp", "*.h", "*.tcc", "*Exporter.cpp")

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
        "with_perfetto": False,
    }

    def validate(self):
        if self.options.with_protovalidate and not self.options.with_protobuf:
            raise ConanInvalidConfiguration("with_protovalidate requires with_protobuf")

    def configure(self):
        self.options["hstd_cpp_lib/*"].with_perfetto = bool(self.options.with_perfetto)
        self.options["hstd_cpp_lib/*"].with_protovalidate = bool(
            self.options.with_protovalidate
        )
        self.options["hstd_cpp_lib/*"].with_protobuf = bool(self.options.with_protobuf)

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

    def haxorg_configure_deps(self, deps: CMakeDeps):
        deps.set_property("perfetto", "cmake_file_name", "Perfetto")
        deps.set_property("perfetto", "cmake_target_name", "Perfetto::perfetto")

    def build_requirements(self):
        self.test_requires("gtest/[>=1.17 <2]")
        self.test_requires("abseil/[>=20250127.0 <20260000]")

        if self.options.with_protobuf:
            self.tool_requires("protobuf/[>=5 <6]")

    def haxorg_configure_toolchain(self, toolchain: CMakeToolchain):
        toolchain.variables["HAXORG_WITH_PROTOBUF"] = bool(self.options.with_protobuf)
        toolchain.variables["HAXORG_WITH_PROTOVALIDATE"] = bool(
            self.options.with_protovalidate
        )
        toolchain.variables["HAXORG_WITH_PERFETTO"] = bool(self.options.with_perfetto)

    def haxorg_package_info(self):
        self.cpp_info.defines = [
            f"HAXORG_CPP_BUILD_WITH_PROTOBUF={int(bool(self.options.with_protobuf))}",
            f"ORG_BUILD_WITH_PERFETTO={int(bool(self.options.with_perfetto))}",
        ]
