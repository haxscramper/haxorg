import os
import sys

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.env import Environment
from conan.tools.files import copy, get
from conan.tools.gnu import PkgConfigDeps

required_conan_version = ">=2.0"


class GraphvizConan(ConanFile):
    name = "graphviz"
    version = "15.1.0"
    description = "Graphviz graph visualization libraries and plugins"
    license = "EPL-1.0"
    url = "https://gitlab.com/graphviz/graphviz"
    homepage = "https://graphviz.org"
    topics = ("graphviz", "graph", "dot", "cgraph")
    package_type = "shared-library"

    settings = "os", "arch", "compiler", "build_type"

    default_options = {
        "libtool/*:shared": True,
    }

    _features_off = (
        "WITH_EXPAT",
        "WITH_ZLIB",
        "WITH_GVEDIT",
        "WITH_SMYRNA",
        "WITH_GDK",
        "WITH_GHOSTSCRIPT",
        "WITH_GTK",
        "WITH_POPPLER",
        "WITH_QUARTZ",
        "WITH_RSVG",
        "WITH_WEBP",
        "WITH_X",
        "ENABLE_TCL",
        "ENABLE_SWIG",
        "ENABLE_SHARP",
        "ENABLE_D",
        "ENABLE_GO",
        "ENABLE_GUILE",
        "ENABLE_JAVA",
        "ENABLE_JAVASCRIPT",
        "ENABLE_LUA",
        "ENABLE_PERL",
        "ENABLE_PHP",
        "ENABLE_PYTHON",
        "ENABLE_R",
        "ENABLE_RUBY",
    )

    _packages_off = (
        "ANN",
        "GTS",
        "GD",
        "AA",
        "DevIL",
        "GLUT",
        "GTK2",
        "EXPAT",
        "ZLIB",
        "GS",
        "TCL",
        "SWIG",
        # TODO: make this an optional (on by default) configuration
        # part, so the graphviz could be built without the PNG deps.
        #
        # "CAIRO",
        # "PANGOCAIRO",
        # "Freetype",
        # "Fontconfig",
        # "PkgConfig",
    )

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def requirements(self):
        self.requires("libtool/[>=2.4.7 <3]")

        # To diagnose ordering issue with link ordering, add the tracing link flags to the
        # conan profile.
        # `glib/*:tools.build:exelinkflags=["-Wl,--trace","-Wl,--trace-symbol=g_trace_define_int64_counter"]`
        #
        # These dependencies require
        # `glib/*:tools.build:exelinkflags=["-L./glib","-L./gobject","-L./gmodule","-L./gio"]` to be
        # added to the conan profile, otherwise the build picks system-provided `glib` instead of
        # the one installed by conan, which in turn fails because `g_trace_set_int64_counter` is
        # not defined in the system libraries.
        if True:
            self.requires("cairo/[>=1.18 <2]")
            self.requires("pango/[>=1.54 <2]")

    def layout(self):
        cmake_layout(self, src_folder="src")

        component_names = (
            "cdt",
            "cgraph",
            "pathplan",
            "xdot",
            "gvc",
        )

        workspace_include_dirs = [
            "../../include",
            "../../include/graphviz",
        ]
        workspace_libdirs = ["../../lib"]
        workspace_bindirs = ["../../bin"]

        self.cpp.build.includedirs = workspace_include_dirs
        self.cpp.build.libdirs = workspace_libdirs
        self.cpp.build.bindirs = workspace_bindirs

        for name in component_names:
            component = self.cpp.build.components[name]
            component.includedirs = workspace_include_dirs
            component.libdirs = workspace_libdirs
            component.bindirs = workspace_bindirs

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.21 <5]")
        self.tool_requires("pkgconf/[>=2.2 <3]")

        if self.settings_build.os == "Windows":
            self.tool_requires("winflexbison/2.5.25")
        else:
            self.tool_requires("bison/3.8.2")
            self.tool_requires("flex/2.6.4")

    def source(self):
        get(
            self,
            **self.conan_data["sources"][self.version],
            strip_root=True,
        )

    def generate(self):
        pkg_config = PkgConfigDeps(self)
        pkg_config.generate()

        toolchain = CMakeToolchain(self)

        # graphviz -> pango -> glib -- glib enables the sysprof
        # by default it seems, and conan recipe does not
        # expose this option, so for now it will have this
        # hardcoded hack.
        sysprof_capture = "/usr/lib/libsysprof-capture-4.a"

        for language in ("C", "CXX"):
            toolchain.cache_variables[f"CMAKE_{language}_STANDARD_LIBRARIES"] = (
                sysprof_capture
            )

        toolchain.cache_variables["BUILD_SHARED_LIBS"] = True
        toolchain.cache_variables["BUILD_TESTING"] = False

        # The dot executable is required to generate Graphviz's plugin registry.
        toolchain.cache_variables["GRAPHVIZ_CLI"] = True

        toolchain.cache_variables["with_cxx_api"] = False
        toolchain.cache_variables["with_cxx_tests"] = False
        toolchain.cache_variables["use_win_pre_inst_libs"] = False
        toolchain.cache_variables["install_win_dependency_dlls"] = False

        for feature in self._features_off:
            toolchain.cache_variables[feature] = False

        for package in self._packages_off:
            variable = f"CMAKE_DISABLE_FIND_PACKAGE_{package}"
            toolchain.cache_variables[variable] = True

        if os.path.basename(sys.executable).lower().startswith("python"):
            python_executable = sys.executable.replace("\\", "/")
            toolchain.cache_variables["Python3_EXECUTABLE"] = python_executable

        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.install()

        self._generate_plugin_registry()

    def package(self):
        copy(
            self,
            "LICENSE*",
            src=self.source_folder,
            dst=os.path.join(self.package_folder, "licenses"),
        )
        copy(
            self,
            "COPYING*",
            src=self.source_folder,
            dst=os.path.join(self.package_folder, "licenses"),
        )

        cmake = CMake(self)
        cmake.install()

        self._generate_plugin_registry()

    def _generate_plugin_registry(self):
        bin_directory = os.path.join(self.package_folder, "bin")
        lib_directory = os.path.join(self.package_folder, "lib")
        plugin_directory = os.path.join(
            lib_directory,
            "graphviz",
        )

        executable_name = "dot.exe" if self.settings.os == "Windows" else "dot"
        dot_executable = os.path.join(
            bin_directory,
            executable_name,
        )

        environment = Environment()
        environment.define("GVBINDIR", plugin_directory)
        environment.prepend_path("PATH", bin_directory)

        if self.settings.os == "Linux":
            environment.prepend_path(
                "LD_LIBRARY_PATH",
                lib_directory,
            )
        elif self.settings.os == "Macos":
            environment.prepend_path(
                "DYLD_LIBRARY_PATH",
                lib_directory,
            )
        elif self.settings.os == "Windows":
            environment.prepend_path(
                "PATH",
                lib_directory,
            )

        with environment.vars(self).apply():
            self.run(f'"{dot_executable}" -c')

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "graphviz")

        # Existing component configuration follows.

        components = {
            "cdt": {
                "libs": ["cdt"],
                "requires": [],
            },
            "cgraph": {
                "libs": ["cgraph"],
                "requires": ["cdt"],
            },
            "pathplan": {
                "libs": ["pathplan"],
                "requires": [],
            },
            "xdot": {
                "libs": ["xdot"],
                "requires": [],
            },
            "gvc": {
                "libs": ["gvc"],
                "requires": ["cgraph"],
            },
        }

        for name, data in components.items():
            component = self.cpp_info.components[name]
            component.set_property(
                "cmake_target_name",
                f"graphviz::{name}",
            )
            component.includedirs = [
                "include",
                "include/graphviz",
            ]
            component.libs = data["libs"]
            component.requires = data["requires"]

        if self.settings.os == "Windows":
            self.cpp_info.components["gvc"].defines = ["GVDLL"]
