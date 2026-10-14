from conan import ConanFile


class HaxorgCppCWrapConan(ConanFile):
    name = "haxorg_cpp_c_wrap"
    version = "0.1.0"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"

    def requirements(self):
        self.requires(
            "haxorg_cpp_org_lib/0.1.0",
            transitive_headers=True,
            transitive_libs=True,
        )
