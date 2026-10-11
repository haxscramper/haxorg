import os

from conan import ConanFile
from conan.tools.cmake import (
    CMake,
    CMakeDeps,
    CMakeToolchain,
    cmake_layout,
)
from conan.tools.files import download, get, mkdir, replace_in_file


class ProtovalidateCcConan(ConanFile):
    name = "protovalidate-cc"
    version = "1.1.0"
    package_type = "static-library"

    license = "Apache-2.0"
    homepage = "https://github.com/bufbuild/protovalidate-cc"
    description = "Protocol Buffer validation for C++"

    settings = "os", "arch", "compiler", "build_type"

    options = {
        "fPIC": [True, False],
    }

    default_options = {
        "fPIC": True,
    }

    exports_sources = (
        "CMakeLists.txt",
        "protovalidate_cc-config.cmake.in",
    )

    def requirements(self):
        # Specific version pinned because protovalidate internally vendors google CEL
        # which in turn expects a specific version of the abseil to be present, with
        # features like `Nonnull`. Protobuf version 7.35 does not fit -- it pulls
        # abseil that is too recent, without `Nonnull`. Since neither CEL nor
        # protovalidate were properly packaged before, there is no clear mapping as to
        # what dependency version specifically is required. So protovalidate is
        # packaged with a specific pinned version.
        #
        # Nonnull was officially removed in LTS version 20250814.1
        # https://github.com/bufbuild/protovalidate-cc/blob/v1.1.0/cmake/README.md
        # known compatible version for 1.1.0 is 29.2 (5.29.6 is close-ish?)
        self.requires("protobuf/5.29.6", transitive_headers=True, transitive_libs=True)
        self.requires("re2/[>=20230301]", transitive_headers=True, transitive_libs=True)
        self.requires("abseil/[>=20250127.0 <20260000]")

    def build_requirements(self):
        self.tool_requires("openjdk/21.0.2")
        self.tool_requires("protobuf/5.29.6")
        # `patch` is not available in conan, but required for the build
        # keeping here for the compat
        # self.tool_requires("patch/[>=2.7 <3]")

    def source(self):
        assert self.source_folder
        self.output.info(f"source() running: source_folder={self.source_folder}")
        version = str(self.version)

        source_data = self.conan_data["sources"][version]
        get(
            self,
            url=source_data["url"],
            sha256=source_data["sha256"],
            strip_root=True,
            destination=os.path.join(self.source_folder, "_source"),
        )

        # Abseil's configured headers use C++20 comparison types.
        # The upstream C++17 probe cannot compile against that configuration.
        replace_in_file(
            self,
            os.path.join(self.source_folder, "_source", "cmake", "Deps.cmake"),
            "    CXX_STANDARD 17\n",
            "    CXX_STANDARD 20\n",
        )

        schema_dir = os.path.join(self.source_folder, "_schema", "buf", "validate")
        mkdir(self, schema_dir)

        schema_data = self.conan_data["schemas"][version]
        download(
            self,
            url=schema_data["url"],
            filename=os.path.join(schema_dir, "validate.proto"),
            sha256=schema_data["sha256"],
        )

    def layout(self):
        cmake_layout(self)

        self.cpp.source.resdirs = ["_schema"]
        self.cpp.build.builddirs = ["."]

        self.cpp.package.resdirs = [os.path.join("res", "proto")]
        self.cpp.package.builddirs = [os.path.join("lib", "cmake", "protovalidate_cc")]

    def generate(self):
        CMakeDeps(self).generate()

        toolchain = CMakeToolchain(self)

        # Vendored cel-cpp uses unique_ptr to incomplete types, which fails
        # under C++23 constexpr unique_ptr. Standard is pinned in CMakeLists.txt.
        toolchain.blocks.remove("cppstd")

        toolchain.extra_cflags.append("-w")
        toolchain.extra_cxxflags.append("-w")

        protobuf = self.dependencies["protobuf"]
        toolchain.cache_variables["Protobuf_IMPORT_DIRS"] = os.path.join(
            protobuf.package_folder,
            protobuf.cpp_info.includedirs[0],
        )

        toolchain.cache_variables["PROTOVALIDATE_CC_VERSION"] = str(self.version)
        toolchain.cache_variables["BUILD_SHARED_LIBS"] = False
        toolchain.cache_variables["CMAKE_POSITION_INDEPENDENT_CODE"] = bool(
            self.options.fPIC
        )

        # cmake/Deps.cmake:125 (try_compile): in the protovalidate checks for the
        # sub-project compilation test, but the cmake cache gnerates build that
        # depends on the build configuration, so
        # INCLUDE_DIRECTORIES:UNINITIALIZED=$<$<CONFIG:Debug>:/tmp/conan-ci/p/b/absei0589bbf79ba0a/p/include>
        toolchain.cache_variables["CMAKE_TRY_COMPILE_CONFIGURATION"] = str(
            self.settings.build_type
        )

        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "protovalidate_cc")
        self.cpp_info.set_property(
            "cmake_target_name",
            "protovalidate_cc::protovalidate_cc",
        )
        self.cpp_info.set_property("cmake_find_mode", "none")
