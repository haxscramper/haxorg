import os

from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import (
    CMake,
    CMakeDeps,
    CMakeToolchain,
    cmake_layout,
)


class AdaptagramsTestConan(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    test_type = "explicit"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def layout(self):
        cmake_layout(self)

    def generate(self):
        native = self.conf.get(
            "user.adaptagrams:native_config",
            default=False,
            check_type=bool,
        )

        if not native:
            deps = CMakeDeps(self)
            deps.check_components_exist = True
            deps.generate()

        tc = CMakeToolchain(self)

        if native:
            package = self.dependencies["adaptagrams"].package_folder
            config_dir = os.path.join(
                package,
                "lib",
                "cmake",
                "Adaptagrams",
            )
            tc.variables["ADAPTAGRAMS_NATIVE_CONFIG_DIR"] = config_dir.replace("\\", "/")

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            cmake = CMake(self)
            cmake.test()
