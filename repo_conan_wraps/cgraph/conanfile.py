import os

from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get
from conan.tools.scm import Version

required_conan_version = ">=2.0"


class CgraphConan(ConanFile):
    name = "cgraph"
    version = "15.1.0"
    description = "Graphviz cgraph: abstract graph library (with its cdt dependency)"
    license = "EPL-2.0"
    url = "https://gitlab.com/graphviz/graphviz"
    homepage = "https://graphviz.org"
    topics = ("graphviz", "graph", "dot", "cgraph")
    package_type = "library"

    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    exports_sources = "CMakeLists.txt"

    @property
    def _gv_src(self):
        return os.path.join(self.source_folder, "graphviz")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")
        # pure C library
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self)

    def validate(self):
        # Graphviz 15 is compiled as C17
        if (
            self.settings.compiler == "msvc"
            and Version(self.settings.compiler.version) < "192"
        ):
            raise ConanInvalidConfiguration(
                "cgraph requires MSVC >= 192 (VS 2019 16.8) for C17"
            )

    def build_requirements(self):
        # cgraph's DOT parser is generated from grammar.y (bison) and scan.l (flex)
        if self.settings_build.os == "Windows":
            self.tool_requires("winflexbison/2.5.25")
        else:
            self.tool_requires("bison/3.8.2")
            self.tool_requires("flex/2.6.4")

    def source(self):
        data = dict(self.conan_data["sources"][self.version])
        get(self, **data, destination=self._gv_src, strip_root=True)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["GRAPHVIZ_SOURCE_DIR"] = self._gv_src.replace("\\", "/")
        tc.cache_variables["GRAPHVIZ_VERSION"] = str(self.version)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        for pattern in ("COPYING*", "LICENSE*"):
            copy(
                self,
                pattern,
                src=self._gv_src,
                dst=os.path.join(self.package_folder, "licenses"),
            )
        CMake(self).install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "cgraph")
        self.cpp_info.set_property("cmake_target_name", "cgraph::cgraph")
        self.cpp_info.set_property("pkg_config_name", "libcgraph")

        # order matters for static linking: cgraph depends on cdt
        self.cpp_info.libs = ["cgraph", "cdt"]
        # like upstream (>= 14.1.2): both <graphviz/cgraph.h> and <cgraph.h> work
        self.cpp_info.includedirs = ["include", os.path.join("include", "graphviz")]

        if self.settings.os in ("Linux", "FreeBSD"):
            self.cpp_info.system_libs = ["m"]
        if self.settings.os == "Windows" and self.options.shared:
            # selects __declspec(dllimport) in cgraph.h / cdt.h
            self.cpp_info.defines = ["GVDLL"]
