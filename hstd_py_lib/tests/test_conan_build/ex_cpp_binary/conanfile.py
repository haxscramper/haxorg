from conan import ConanFile


class ExampleCppBinary(ConanFile):
    name = "ex_cpp_binary"
    version = "0.1.0"
    package_type = "application"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"

    provided_binaries = ["ex_cpp_binary"]

    def requirements(self):
        self.requires("ex_cpp_library/0.1.0")

    def haxorg_configure_layout(self):
        self.cpp.build.bindirs = ["."]
