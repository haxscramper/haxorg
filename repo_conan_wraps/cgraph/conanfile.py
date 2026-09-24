import glob
import os
import shutil
import sys

from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, replace_in_file
from conan.tools.microsoft import is_msvc
from conan.tools.scm import Version

required_conan_version = ">=2.0"


class CgraphConan(ConanFile):
    name = "cgraph"
    version = "15.1.0"
    description = "Graphviz cgraph graph library (built with upstream CMake)"
    license = "EPL-1.0"
    url = "https://gitlab.com/graphviz/graphviz"
    homepage = "https://graphviz.org"
    topics = ("graphviz", "graph", "dot", "cgraph")
    package_type = "library"

    settings = "os", "arch", "compiler", "build_type"
    # no fPIC option: upstream forces CMAKE_POSITION_INDEPENDENT_CODE ON
    options = {"shared": [True, False]}
    default_options = {"shared": False}

    # Upstream AUTO-detected features, none of which cgraph needs
    _features_off = (
        "ENABLE_LTDL",
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
    # Unconditional find_package() calls in upstream's top-level CMakeLists
    _packages_off = (
        "ANN",
        "CAIRO",
        "GTS",
        "PANGOCAIRO",
        "GD",
        "AA",
        "DevIL",
        "Freetype",
        "GLUT",
        "GTK2",
        "Fontconfig",
        "PkgConfig",
        "EXPAT",
        "ZLIB",
        "LTDL",
        "GS",
        "TCL",
        "SWIG",
    )

    def configure(self):
        # the packaged artifacts are pure C
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def validate(self):
        # upstream passes /experimental:c11atomics unconditionally (VS 2022 17.5+)
        if (
            self.settings.compiler == "msvc"
            and Version(self.settings.compiler.version) < "193"
        ):
            raise ConanInvalidConfiguration("graphviz 15 requires MSVC >= 193")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.21 <5]")
        if self.settings_build.os == "Windows":
            self.tool_requires("winflexbison/2.5.25")
        else:
            self.tool_requires("bison/3.8.2")
            self.tool_requires("flex/2.6.4")

    def source(self):
        get(self, **self.conan_data["sources"][self.version], strip_root=True)
        # Upstream forces LTO in Release. LTO bitcode inside a static library
        # ties consumers to the exact same compiler/linker, so leave it opt-in.
        replace_in_file(
            self,
            os.path.join(self.source_folder, "CMakeLists.txt"),
            "set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)",
            "",
            strict=False,
        )

    def generate(self):
        tc = CMakeToolchain(self)  # sets BUILD_SHARED_LIBS from options.shared
        tc.cache_variables["GRAPHVIZ_CLI"] = "OFF"
        tc.cache_variables["BUILD_TESTING"] = "OFF"
        tc.cache_variables["with_cxx_api"] = "OFF"
        tc.cache_variables["with_cxx_tests"] = "OFF"
        tc.cache_variables["use_win_pre_inst_libs"] = "OFF"
        tc.cache_variables["install_win_dependency_dlls"] = "OFF"
        for opt in self._features_off:
            tc.cache_variables[opt] = "OFF"
        for pkg in self._packages_off:
            tc.cache_variables[f"CMAKE_DISABLE_FIND_PACKAGE_{pkg}"] = "ON"

        # gen_version.py is run at configure time; reuse Conan's interpreter if possible
        if os.path.basename(sys.executable).lower().startswith("python"):
            tc.cache_variables["Python3_EXECUTABLE"] = sys.executable.replace("\\", "/")

        if is_msvc(self):
            # FindGETOPT is REQUIRED when <getopt.h> is missing, but only the
            # CLI tools (disabled) use it. Satisfy the check without a dependency.
            tc.cache_variables["GETOPT_INCLUDE_DIR"] = self.source_folder.replace(
                "\\", "/"
            )
            tc.cache_variables["GETOPT_LIBRARY"] = "getopt-unused"
            tc.cache_variables["GETOPT_RUNTIME_LIBRARY"] = "getopt-unused"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build(target="cgraph")  # pulls in cdt + util only

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

        inc = os.path.join(self.package_folder, "include", "graphviz")
        copy(
            self,
            "cgraph.h",
            src=os.path.join(self.source_folder, "lib", "cgraph"),
            dst=inc,
        )
        copy(self, "cdt.h", src=os.path.join(self.source_folder, "lib", "cdt"), dst=inc)
        copy(self, "graphviz_version.h", src=self.build_folder, dst=inc, keep_path=False)

        lib_dst = os.path.join(self.package_folder, "lib")
        bin_dst = os.path.join(self.package_folder, "bin")
        for sub in ("cgraph", "cdt"):
            src = os.path.join(self.build_folder, "lib", sub)
            for pattern in ("*.a", "*.lib", "*.so*", "*.dylib"):
                copy(self, pattern, src=src, dst=lib_dst, keep_path=False)
            copy(self, "*.dll", src=src, dst=bin_dst, keep_path=False)

        if not self.options.shared:
            # upstream never installs its private static 'util' lib, which
            # libcgraph.a needs; ship it under a non-clashing name
            util_dir = os.path.join(self.build_folder, "lib", "util")
            for f in glob.glob(os.path.join(util_dir, "**", "*util.*"), recursive=True):
                if f.endswith(".lib"):
                    shutil.copy2(f, os.path.join(lib_dst, "gvutil.lib"))
                elif f.endswith(".a"):
                    shutil.copy2(f, os.path.join(lib_dst, "libgvutil.a"))

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "cgraph")
        self.cpp_info.set_property("cmake_target_name", "cgraph::cgraph")
        self.cpp_info.set_property("pkg_config_name", "libcgraph")
        self.cpp_info.includedirs = ["include", os.path.join("include", "graphviz")]

        # link order: cgraph -> cdt -> util
        self.cpp_info.libs = (
            ["cgraph", "cdt"] if self.options.shared else ["cgraph", "cdt", "gvutil"]
        )

        if self.settings.os in ("Linux", "FreeBSD"):
            self.cpp_info.system_libs = ["m"]
        if self.settings.os == "Windows" and self.options.shared:
            self.cpp_info.defines = ["GVDLL"]  # dllimport in cgraph.h / cdt.h
