import os

from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy
from conan.tools.scm import Git


class AdaptagramsConan(ConanFile):
    name = "adaptagrams"
    version = "0.0.20251029"

    description = "Constraint-based graph layout and object-avoiding connector routing"
    homepage = "https://github.com/mjwybrow/adaptagrams"
    license = "LGPL-2.1-or-later"
    topics = ("graph", "layout", "routing", "constraints")

    required_conan_version = ">=2.0"
    package_type = "static-library"

    settings = "os", "arch", "compiler", "build_type"

    options = {
        "fPIC": [True, False],
    }
    default_options = {
        "fPIC": True,
    }

    exports_sources = (
        "CMakeLists.txt",
        "adaptagrams-config.cmake.in",
        "cola_config.h.in",
    )

    _upstream_url = "https://github.com/mjwybrow/adaptagrams.git"
    _upstream_commit = "840ebcff20dbba36ad03a2160edf7cbaf9859984"

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

        component_names = (
            "vpsc",
            "avoid",
            "cola",
            "topology",
            "dialect",
        )

        self.cpp.source.includedirs = ["upstream/cola"]
        self.cpp.build.includedirs = ["generated"]
        self.cpp.build.libdirs = ["."]

        for name in component_names:
            self.cpp.source.components[name].includedirs = ["upstream/cola"]
            self.cpp.build.components[name].includedirs = ["generated"]
            self.cpp.build.components[name].libdirs = ["."]

    def validate(self):
        if self.settings.compiler.get_safe("cppstd"):
            check_min_cppstd(self, "11")

    def source(self):
        upstream = os.path.join(self.source_folder, "upstream")

        if not os.path.exists(upstream):
            Git(self).clone(self._upstream_url, target=upstream)

        Git(self, folder=upstream).checkout(self._upstream_commit)

    def generate(self):
        tc = CMakeToolchain(self)

        upstream = os.path.join(self.source_folder, "upstream")
        tc.variables["ADAPTAGRAMS_SOURCE_DIR"] = upstream.replace("\\", "/")
        tc.variables["ADAPTAGRAMS_VERSION"] = str(self.version)
        tc.variables["BUILD_SHARED_LIBS"] = False

        # Keep these paths consistent with package_info().
        tc.variables["CMAKE_INSTALL_LIBDIR"] = "lib"
        tc.variables["CMAKE_INSTALL_INCLUDEDIR"] = "include"
        tc.variables["CMAKE_INSTALL_BINDIR"] = "bin"

        if self.options.get_safe("fPIC") is not None:
            tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = bool(self.options.fPIC)

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        upstream = os.path.join(self.source_folder, "upstream")
        licenses = os.path.join(self.package_folder, "licenses")

        # Keep relative paths to avoid collisions between license files in
        # different upstream directories.
        for pattern in ("LICENSE*", "COPYING*"):
            copy(
                self,
                pattern=pattern,
                src=upstream,
                dst=licenses,
                keep_path=True,
            )

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "adaptagrams")
        self.cpp_info.set_property(
            "cmake_target_name",
            "adaptagrams::adaptagrams",
        )

        # Conan consumers use CMakeDeps. Native CMake consumers can still
        # discover the files installed under lib/cmake/adaptagrams.
        self.cpp_info.builddirs = []

        dependencies = {
            "vpsc": [],
            "avoid": [],
            "cola": ["vpsc"],
            "topology": ["avoid", "cola", "vpsc"],
            "dialect": ["avoid", "cola", "vpsc"],
        }

        for name, requires in dependencies.items():
            component = self.cpp_info.components[name]
            component.libs = [name]
            component.includedirs = ["include"]
            component.libdirs = ["lib"]
            component.requires = requires

            component.set_property(
                "cmake_target_name",
                f"adaptagrams::{name}",
            )

        self.cpp_info.components["avoid"].defines = ["LIBAVOID_NO_DLL"]
