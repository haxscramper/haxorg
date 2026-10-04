import sys

from conan import ConanFile


class ExampleCppNanobind(ConanFile):
    name = "ex_cpp_nanobind"
    version = "0.1.0"
    package_type = "shared-library"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"

    haxorg_use_cmake_install = True
    haxorg_package_libs = ()

    def requirements(self):
        self.requires("ex_cpp_library/0.1.0")
        self.requires("nanobind/[>=2.9.2 <3]")

    def haxorg_configure_toolchain(self, toolchain):
        toolchain.cache_variables["Python_EXECUTABLE"] = self.conf.get(
            "user.haxorg:python_executable",
            default=sys.executable,
            check_type=str,
        )
