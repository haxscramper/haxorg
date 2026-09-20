import os

from conan import ConanFile
from conan.tools.cmake import (
    CMake,
    CMakeDeps,
    CMakeToolchain,
    cmake_layout,
)
from conan.tools.files import (
    copy,
    download,
    get,
    mkdir,
    rmdir,
    save,
    replace_in_file,
)


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

    def requirements(self):
        # Specific version pinned because protovalidate internally vendors google CEL
        # which in turn expects a specific version of the abseil to be present, with
        # features like `Nonnull`. Protobuf version 7.35 does not fit -- it pulls
        # abseil that is too recent, without `Nonnul`. Since neither CEL nor
        # protovalidate were properly packaged before, there is no clear mapping as to
        # what dependency version specifically is required. So protovalidate is
        # packaged with a specific pinned version
        #
        # Nonnull was officially removed in LTS version 20250814.1
        # https://github.com/bufbuild/protovalidate-cc/blob/v1.1.0/cmake/README.md
        # known compatible version for 1.1.0 is 29.2 (5.29.6 is close-ish?)
        self.requires("protobuf/5.29.6")
        self.requires("re2/[>=20230301]")

    def build_requirements(self):
        self.tool_requires("openjdk/21.0.2")
        self.tool_requires("protobuf/5.29.6")

    def source(self):
        version = str(self.version)

        source_data = self.conan_data["sources"][version]
        get(
            self,
            url=source_data["url"],
            sha256=source_data["sha256"],
            strip_root=True,
        )

        replace_in_file(
            self,
            os.path.join(self.source_folder, "CMakeLists.txt"),
            "    # CMake configuration scripts\n",
            (
                "    # CMake configuration scripts\n"
                f'    set(PROTOVALIDATE_CC_GIT_VERSION "{version}")\n'
            ),
        )

        replace_in_file(
            self,
            os.path.join(self.source_folder, "CMakeLists.txt"),
            ("        TARGETS protovalidate_cc ${PROTOVALIDATE_CC_EXPORT_TARGETS}\n"),
            (
                "        TARGETS\n"
                "            protovalidate_cc\n"
                "            ${PROTOVALIDATE_CC_EXPORT_TARGETS}\n"
                "            cel_cpp_empty_descriptor_set\n"
                "            cel_cpp_spec_proto\n"
            ),
        )

        replace_in_file(
            self,
            os.path.join(
                self.source_folder,
                "protovalidate_cc-config.cmake.in",
            ),
            "protovalidate-cc-targets.cmake",
            "protovalidate_cc-targets.cmake",
        )

        cel_cmake_file = os.path.join(
            self.source_folder,
            "cmake",
            "cel-cpp",
            "CMakeLists.txt",
        )

        replace_in_file(
            self,
            cel_cmake_file,
            (
                "target_include_directories(cel_cpp_spec_proto\n"
                "    PUBLIC ${CEL_SPEC_PROTO_GEN_DIR}/proto\n"
                ")\n"
            ),
            (
                "target_include_directories(cel_cpp_spec_proto PUBLIC\n"
                "    $<BUILD_INTERFACE:${CEL_SPEC_PROTO_GEN_DIR}/proto>\n"
                "    $<INSTALL_INTERFACE:include>\n"
                ")\n"
            ),
        )

        root_cmake_file = os.path.join(
            self.source_folder,
            "CMakeLists.txt",
        )

        replace_in_file(
            self,
            root_cmake_file,
            (
                "    install(\n"
                "        DIRECTORY ${PROTOVALIDATE_PROTO_GEN_DIR}/buf\n"
                "        DESTINATION include\n"
                '        FILES_MATCHING PATTERN "*.h"\n'
                "    )\n"
            ),
            (
                "    install(\n"
                "        DIRECTORY ${PROTOVALIDATE_PROTO_GEN_DIR}/buf\n"
                "        DESTINATION include\n"
                '        FILES_MATCHING PATTERN "*.h"\n'
                "    )\n"
                "\n"
                "    install(\n"
                "        DIRECTORY ${CEL_SPEC_PROTO_GEN_DIR}/proto/\n"
                "        DESTINATION include\n"
                '        FILES_MATCHING PATTERN "*.h"\n'
                "    )\n"
            ),
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
        CMakeDeps(self).generate()

        toolchain = CMakeToolchain(self)
        protobuf = self.dependencies["protobuf"]
        toolchain.variables["Protobuf_IMPORT_DIRS"] = os.path.join(
            protobuf.package_folder,
            protobuf.cpp_info.includedirs[0],
        )

        toolchain.variables["BUILD_SHARED_LIBS"] = False

        toolchain.variables["BUILD_SHARED_LIBS"] = False
        toolchain.variables["PROTOVALIDATE_CC_ENABLE_VENDORING"] = False
        toolchain.variables["PROTOVALIDATE_CC_ENABLE_INSTALL"] = True
        toolchain.variables["PROTOVALIDATE_CC_ENABLE_TESTS"] = False
        toolchain.variables["PROTOVALIDATE_CC_ENABLE_CONFORMANCE"] = False
        toolchain.variables["PROTOVALIDATE_CC_SETUP_COMPILE_COMMANDS"] = False

        if self.options.get_safe("fPIC") is not None:
            toolchain.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = bool(
                self.options.fPIC
            )

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

        save(
            self,
            resources_file,
            content=r"""
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
""",
        )

        native_config_file = os.path.join(
            cmake_config_dir,
            "protovalidate_cc-config.cmake",
        )

        if not os.path.isfile(native_config_file):
            raise RuntimeError(
                f"Missing native protovalidate-cc CMake config: {native_config_file}"
            )

        save(
            self,
            native_config_file,
            content=r"""

include(
    "${CMAKE_CURRENT_LIST_DIR}/protovalidate_cc-resources.cmake"
)
""",
            append=True,
        )

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "none")

        self.cpp_info.builddirs = [
            os.path.join("lib", "cmake", "protovalidate_cc"),
        ]

        self.cpp_info.resdirs = [
            os.path.join("res", "proto"),
        ]
