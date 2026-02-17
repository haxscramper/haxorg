import os

from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout, CMakeDeps, CMakeToolchain
from conan.tools.files import copy


class HaxorgConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    name = "haxorg"
    version = "0.1.0"
    license = "MIT"
    author = "haxscramper <haxscramper@gmail.com>"
    url = "https://github.com/haxscramper/haxorg"
    description = "org-mode parser"
    exports_sources = "CMakeLists.txt", "src/*", "HaxorgConfig.cmake.in"

    options = {
        "use_perfetto": [True, False],
        "use_adaptagrams": [True, False],
        "use_cgraph": [True, False],
        "use_tracy": [True, False],
        "use_protobuf": [True, False],
        "use_msgpack": [True, False],
        "use_python_bindings": [True, False],
    }

    default_options = {
        "use_perfetto": False,
        "use_tracy": False,
        "use_python_bindings": False,
        "use_protobuf": True,
        "use_msgpack": True,
        "use_adaptagrams": False,
        "use_cgraph": False,
    }

    def requirements(self):
        self.requires("cpptrace/[>=1.0.4 <2]",
                      transitive_headers=True,
                      transitive_libs=True)
        self.requires("foonathan-lexy/[>=2025.05.0 <2026]")
        self.requires("cctz/[>=2.4 <3]", transitive_headers=True, transitive_libs=True)
        self.requires("zstd/[>=1.5.7 <2]")
        self.requires("pybind11/[>=3.0.1 <4]")
        self.requires("openssl/[>=3.6.1 <4]")
        self.requires("yaml-cpp/[>=0.8.0 <1]")
        self.requires("range-v3/[>=0.12.0 <1]")
        self.requires("immer/[>=0.8.1 <1]", transitive_headers=True, transitive_libs=True)
        self.requires("lager/[>=0.1.1 <1]", transitive_headers=True, transitive_libs=True)
        self.requires("nlohmann_json/[>=3.12.0 <4]",
                      transitive_headers=True,
                      transitive_libs=True)
        self.requires("boost/[>=1.90.0 <2]", override=True)

        if self.options.use_perfetto:
            self.requires("perfetto/[>=52.0 <53]")

        if self.options.use_tracy:
            self.requires("tracy/[>=0.13.1 <1]")

        if self.options.use_protobuf:
            self.requires("protobuf/[>=6.32.1 <7]")

        if self.options.use_msgpack:
            self.requires("msgpack-cxx/[>=7.0.0 <8]")

    def configure(self):
        self.options["boost/*"].without_cobalt = True

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["ORG_BUILD_WITH_PERFETTO"] = self.options.use_perfetto
        tc.cache_variables["ORG_BUILD_WITH_TRACY"] = self.options.use_tracy

        tc.cache_variables[
            "ORG_BUILD_PYHAXORG_BINDINGS"] = self.options.use_python_bindings
        tc.cache_variables[
            "ORG_BUILD_TEXT_LAYOUTER_BINDINGS"] = self.options.use_python_bindings

        tc.cache_variables["ORG_BUILD_WITH_PROTOBUF"] = self.options.use_protobuf
        tc.cache_variables["ORG_BUILD_WITH_MSGPACK"] = self.options.use_msgpack
        tc.cache_variables["ORG_BUILD_WITH_CGRAPH"] = self.options.use_cgraph
        tc.cache_variables["ORG_BUILD_WITH_ADAPTAGRAMS"] = self.options.use_adaptagrams

        # tc.cache_variables["CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH"] = False
        tc.cache_variables["CMAKE_FIND_USE_SYSTEM_PACKAGE_REGISTRY"] = False
        tc.cache_variables["ORG_IS_CONAN_BUILD"] = True
        tc.cache_variables["ORG_BUILD_INTERNAL_TOOLS"] = False
        # tc.cache_variables["CMAKE_FIND_USE_CMAKE_SYSTEM_PATH"] = False
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(cli_args=["--fresh"])
        cmake.build()

    def build_requirements(self):
        if self.options.use_protobuf:
            self.tool_requires("protobuf/[>=6.32.1 <7]")

    def package(self):
        copy(self,
             "*.hpp",
             src=os.path.join(self.source_folder, "src"),
             dst=os.path.join(self.package_folder, "include"))
        copy(self,
             "*.h",
             src=os.path.join(self.source_folder, "src"),
             dst=os.path.join(self.package_folder, "include"))
        copy(self,
             "*.lib",
             src=self.build_folder,
             dst=os.path.join(self.package_folder, "lib"),
             keep_path=False)
        copy(self,
             "*.a",
             src=self.build_folder,
             dst=os.path.join(self.package_folder, "lib"),
             keep_path=False)
        copy(self,
             "*.so*",
             src=self.build_folder,
             dst=os.path.join(self.package_folder, "lib"),
             keep_path=False)

    def package_info(self):
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.libs = ["haxorg", "hstd"]
