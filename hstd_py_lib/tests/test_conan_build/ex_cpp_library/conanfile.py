from conan import ConanFile


class ExampleCppLibrary(ConanFile):
    name = "ex_cpp_library"
    version = "0.1.0"
    package_type = "static-library"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"
