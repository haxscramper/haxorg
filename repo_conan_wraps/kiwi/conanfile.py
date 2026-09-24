import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get


class KiwiConan(ConanFile):
    name = "kiwi"
    version = "1.5.1"
    package_type = "header-library"

    license = "BSD-3-Clause"
    url = "https://github.com/nucleic/kiwi"
    description = "Header-only C++ Cassowary constraint solver"

    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "CMakeLists.txt"

    def layout(self):
        cmake_layout(self)

    def source(self):
        get(
            self,
            url=f"https://github.com/nucleic/kiwi/archive/refs/tags/{self.version}.tar.gz",
            destination=os.path.join(self.source_folder, "upstream"),
            strip_root=True,
        )

    def generate(self):
        CMakeToolchain(self).generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        copy(
            self,
            "LICENSE",
            src=os.path.join(self.source_folder, "upstream"),
            dst=os.path.join(self.package_folder, "licenses"),
        )

    def package_id(self):
        self.info.clear()

    def package_info(self):
        self.cpp_info.libdirs = []
        self.cpp_info.bindirs = []
        self.cpp_info.set_property("cmake_file_name", "kiwi")
        self.cpp_info.set_property("cmake_target_name", "kiwi::kiwi")
