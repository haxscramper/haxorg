import os

from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import CMake, cmake_layout


class ConanTestProject(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            bin_dir = self.cpp.build.bindir
            cmd = os.path.join(bin_dir, "conan_test_package")
            self.run(cmd, env="conanrunenv")

            pkg = self.dependencies[self.tested_reference_str]
            cli = os.path.join(pkg.package_folder, "bin", "haxorg_cpp_org_cli")
            input_file = os.path.join(self.source_folder, "doc1.org")
            output_file = os.path.join(self.build_folder, "result.json")
            self.run(
                f'{cli} export --input "{input_file}" --output "{output_file}" json',
                env="conanrunenv",
            )
