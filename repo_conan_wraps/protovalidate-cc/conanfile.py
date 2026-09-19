import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, download, get, mkdir, rmdir, save


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

    exports_sources = ("patches/*",)

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def requirements(self):
        self.requires("abseil/[>=20240722.0 <20270000]")
        self.requires("protobuf/[>=5 <6]")
        self.requires("re2/[>=2024 <2027]")

    def build_requirements(self):
        # ANTLR parser generation requires Java.
        self.tool_requires("openjdk/21.0.2")

    def source(self):
        version = str(self.version)

        source_data = self.conan_data["sources"][version]
        get(
            self,
            url=source_data["url"],
            sha256=source_data["sha256"],
            strip_root=True,
        )

        schema_data = self.conan_data["schemas"][version]

        schema_dir = os.path.join(
            self.source_folder,
            "_conan",
            "protovalidate-schema",
            "buf",
            "validate",
        )
        mkdir(self, schema_dir)

        download(
            self,
            url=schema_data["url"],
            filename=os.path.join(schema_dir, "validate.proto"),
            sha256=schema_data["sha256"],
        )

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        toolchain = CMakeToolchain(self)
        toolchain.variables["BUILD_SHARED_LIBS"] = False

        if self.options.get_safe("fPIC") is not None:
            toolchain.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = bool(
                self.options.fPIC
            )

        # Externalize dependencies that have Conan packages.
        #
        # The upstream project still fetches CEL, ANTLR, googleapis and
        # Protovalidate schema sources.
        toolchain.variables["PROTOVALIDATE_CC_ENABLE_VENDORING"] = False

        toolchain.variables["PROTOVALIDATE_CC_ENABLE_INSTALL"] = True
        toolchain.variables["PROTOVALIDATE_CC_ENABLE_TESTS"] = False
        toolchain.variables["PROTOVALIDATE_CC_ENABLE_CONFORMANCE"] = False
        toolchain.variables["PROTOVALIDATE_CC_SETUP_COMPILE_COMMANDS"] = False

        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        rmdir(
            self,
            os.path.join(self.package_folder, "lib", "pkgconfig"),
        )

        schema_source_dir = os.path.join(
            self.source_folder,
            "_conan",
            "protovalidate-schema",
            "buf",
            "validate",
        )

        schema_package_dir = os.path.join(
            self.package_folder,
            "res",
            "proto",
            "buf",
            "validate",
        )

        copy(
            self,
            pattern="validate.proto",
            src=schema_source_dir,
            dst=schema_package_dir,
        )

        self._install_cmake_resource_metadata()


def _install_cmake_resource_metadata(self):
    cmake_config_dir = os.path.join(
        self.package_folder,
        "lib",
        "cmake",
        "protovalidate_cc",
    )

    resources_file = os.path.join(
        cmake_config_dir,
        "protovalidate_cc-resources.cmake",
    )

    resources_content = r"""
# Conan-packaged Protovalidate schema resources.
#
# This file resides at:
#   <prefix>/lib/cmake/protovalidate_cc/
#
# Therefore ../../.. is the package prefix.
get_filename_component(
    _protovalidate_cc_package_prefix
    "${CMAKE_CURRENT_LIST_DIR}/../../.."
    ABSOLUTE
)

set(
    protovalidate_cc_PROTO_IMPORT_DIR
    "${_protovalidate_cc_package_prefix}/res/proto"
)

if(NOT EXISTS
   "${protovalidate_cc_PROTO_IMPORT_DIR}/buf/validate/validate.proto")
    message(
        FATAL_ERROR
        "The protovalidate_cc package is missing "
        "'buf/validate/validate.proto' under "
        "'${protovalidate_cc_PROTO_IMPORT_DIR}'"
    )
endif()

unset(_protovalidate_cc_package_prefix)
"""

    save(
        self,
        resources_file,
        resources_content,
    )

    native_config_file = os.path.join(
        cmake_config_dir,
        "protovalidate_cc-config.cmake",
    )

    if not os.path.isfile(native_config_file):
        raise RuntimeError(
            "protovalidate-cc did not install its expected CMake "
            f"configuration file: {native_config_file}"
        )

    save(
        self,
        native_config_file,
        content=r"""

# Conan-provided schema location.
include(
    "${CMAKE_CURRENT_LIST_DIR}/protovalidate_cc-resources.cmake"
)
""",
        append=True,
    )
