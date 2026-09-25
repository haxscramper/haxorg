#!/usr/bin/env python
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class HstdCppDiagramLibConan(ConanFile):
    name = "hstd_cpp_diagram_lib"
    version = "0.1.0"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    options = {"fPIC": [True, False]}
    default_options = {"fPIC": True}
    exports_sources = (
        "CMakeLists.txt",
        "cmake/*",
        "jni_elk/*",
        "proto/*",
        "src/*",
        "tests/*",
    )

    def requirements(self):
        self.requires("hstd_cpp_lib/0.1.0", transitive_headers=True, transitive_libs=True)
        self.requires("protobuf/[>=5 <6]", transitive_headers=True, transitive_libs=True)
        self.requires("kiwi/1.5.1", transitive_headers=True, transitive_libs=True)
        self.requires("cgraph/15.1.0", transitive_headers=True, transitive_libs=True)
        self.requires(
            "adaptagrams/0.0.20251029", transitive_headers=True, transitive_libs=True
        )

    def build_requirements(self):
        self.tool_requires("protobuf/<host_version>")
        self.test_requires("gtest/1.15.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        CMakeDeps(self).generate()
        tc = CMakeToolchain(self)
        tc.cache_variables["BUILD_TESTING"] = not self.conf.get(
            "tools.build:skip_test", default=False
        )
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if not self.conf.get("tools.build:skip_test", default=False):
            cmake.test()

    def package(self):
        CMake(self).install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "hstd_cpp_diagram_lib")
        self.cpp_info.set_property(
            "cmake_target_name", "hstd_cpp_diagram_lib::hstd_cpp_diagram_lib"
        )
        self.cpp_info.libs = ["hstd_cpp_diagram_lib", "jni_elk_lib"]
        self.cpp_info.resdirs = ["share"]
