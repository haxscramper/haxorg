from pathlib import Path
from conan import ConanFile


from conan.tools.build import can_run
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class HstdCppTextLayoutTestPackageConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    test_type = "explicit"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def layout(self):
        cmake_layout(self)

    def generate(self):
        toolchain = CMakeToolchain(self)
        toolchain.generate()

        dependencies = CMakeDeps(self)
        dependencies.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        executable = Path(self.build_folder) / "hstd_cpp_text_layout_test_package"
        self.run(str(executable), env="conanrun")
