import sys

from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain


class LldbTraceFixture(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("nanobind/[>=2.9.2 <3]")

    def generate(self):
        dependencies = CMakeDeps(self)
        dependencies.generate()

        toolchain = CMakeToolchain(self)
        toolchain.user_presets_path = False
        self.set_cmake_var(
            toolchain,
            "Python_EXECUTABLE",
            self.conf.get(
                "user.haxorg:python_executable",
                default=sys.executable,
                check_type=str,
            ),
        )
        toolchain.generate()
