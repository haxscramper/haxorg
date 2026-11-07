from pathlib import Path
from typing import TYPE_CHECKING, Protocol, cast

from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain


class RecipeOptions(Protocol):
    with_protobuf: bool
    with_protovalidate: bool


if TYPE_CHECKING:
    from haxorg_conan_base.conanfile import HaxorgPackage as HstdBase
else:
    HstdBase = ConanFile


class HstdConan(HstdBase):
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
        },
    )

    default_options = {
        "with_protobuf": True,
        "with_protovalidate": True,
    }

    def requirements(self):
        th = dict(transitive_headers=True)

        self.haxorg_requires("yaml-cpp/[>=0.8.0 <0.9]", components=("yaml-cpp",), **th)
        # TODO: range-v3 could be made non-transitive, in theory, but it
        # would require separate cleanup of the headers.
        self.haxorg_requires(
            "range-v3/[>=0.12.0 <0.13]",
            components=("range-v3-meta", "range-v3-concepts"),
            **th,
        )
        self.haxorg_requires(
            "nlohmann_json/[>=3.11.3 <4]", components=("nlohmann_json",), **th
        )
        self.haxorg_requires("cctz/[>=2.4.0 <3]", components=("cctz",), **th)
        self.haxorg_requires("fmt/[>=11 <17]", components=("_fmt",), **th)
        self.haxorg_requires("boost/[>=1.86.0 <2]", components=("headers", "log"), **th)
        self.haxorg_requires("cpptrace/[>=0.8.0 <2]", components=("cpptrace",), **th)

        if self.options.with_protobuf:
            self.haxorg_requires("protobuf/[>=5 <6]", components=("libprotobuf",))

        if self.options.with_protovalidate:
            self.haxorg_requires("re2/[>=20230301]", components=("re2",))
            self.haxorg_requires(
                "protovalidate-cc/1.1.0",
                components=(("protovalidate-cc",) if self.options.with_protobuf else ()),
            )

    def build_requirements(self):
        self.haxorg_test_requires("gtest/[>=1.15 <2]")
        self.haxorg_test_requires("benchmark/[>=1.9 <2]")
        self.haxorg_test_requires("abseil/[>=20240722.0 <20260000]")
        self.haxorg_test_requires("immer/[>=0.8 <1]")
        self.tool_requires("protobuf/[>=5 <6]")

    def haxorg_configure_deps(self, deps: CMakeDeps):
        deps.set_property("perfetto", "cmake_file_name", "Perfetto")
        deps.set_property("perfetto", "cmake_target_name", "perfetto::perfetto")

    def haxorg_configure_toolchain(self, toolchain: CMakeToolchain):
        # TODO: remove this option entirely, create a separate package for qt utils
        self.set_cmake_var(toolchain, "ORG_BUILD_WITH_QT", False)
        # TODO: Infer the compilation configuration from the compiler
        self.set_cmake_var(toolchain, "ORG_BUILD_EMCC", False)
        self.set_cmake_var(
            toolchain, "HSTD_CPP_BUILD_WITH_PROTOBUF", bool(self.options.with_protobuf)
        )
        self.set_cmake_var(
            toolchain,
            "HSTD_CPP_BUILD_WITH_PROTOVALIDATE",
            bool(self.options.with_protovalidate),
        )

        if self.options.with_protobuf:
            protobuf_tool = self.dependencies.build["protobuf"]
            protoc = Path(protobuf_tool.package_folder) / "bin" / "protoc"
            self.set_cmake_var(toolchain, "Protobuf_PROTOC_EXECUTABLE", str(protoc))

    def haxorg_package_info(self):
        self.cpp_info.defines = [
            f"HSTD_CPP_BUILD_WITH_PROTOBUF={int(bool(self.options.with_protobuf))}",
            f"HSTD_CPP_BUILD_WITH_PROTOVALIDATE={int(bool(self.options.with_protovalidate))}",
        ]
