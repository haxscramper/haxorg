from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class HstdCppTextLayoutConan(ConanFile):
    name = "hstd_cpp_text_layout"
    version = "0.1.0"

    settings = "os", "compiler", "build_type", "arch"

    exports_sources = (
        "CMakeLists.txt",
        "cmake/*",
        "src/*",
        "tests/*",
    )

    def requirements(self):
        self.requires("hstd_cpp_lib/0.1.0", transitive_headers=True, transitive_libs=True)

    def build_requirements(self):
        self.test_requires("gtest/[>=1.15 <2]")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        toolchain = CMakeToolchain(self)
        toolchain.generate()

        dependencies = CMakeDeps(self)
        dependencies.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(cli_args=["--fresh"])
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["hstd_cpp_text_layout"]
        self.cpp_info.set_property("cmake_file_name", "hstd_cpp_text_layout")
        self.cpp_info.set_property(
            "cmake_target_name",
            "hstd::hstd_cpp_text_layout",
        )
