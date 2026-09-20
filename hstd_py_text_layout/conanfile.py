from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class HstdPyTextLayoutConan(ConanFile):
    name = "hstd-py-text-layout"
    version = "0.1.0"

    settings = "os", "compiler", "build_type", "arch"

    exports_sources = (
        "CMakeLists.txt",
        "cmake/*",
        "src/*",
    )

    def requirements(self):
        self.requires(
            "hstd/0.1.0",
            transitive_headers=True,
            transitive_libs=True,
        )
        self.requires(
            "hstd-cpp-text-layout/0.1.0",
            transitive_headers=True,
            transitive_libs=True,
        )
        self.requires("nanobind/[>=2.9.2 <3]")

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
        self.cpp_info.builddirs = ["lib/cmake/HstdPyTextLayout"]
        self.cpp_info.set_property("cmake_find_mode", "none")
