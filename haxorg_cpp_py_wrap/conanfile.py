from conan import ConanFile


class HaxorgCppPyWrapConan(ConanFile):
    name = "haxorg_cpp_py_wrap"
    version = "0.1.0"
    package_type = "shared-library"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"

    haxorg_use_cmake_install = True
    haxorg_header_patterns = ()
    haxorg_package_libs = ()
    haxorg_runenv_paths = {
        "PYTHONPATH": ("python",),
    }

    def requirements(self):
        self.requires(
            "haxorg_cpp_org_lib/0.1.0",
            transitive_headers=True,
            transitive_libs=True,
        )
        self.requires("nanobind/[>=2.9.2 <3]")

    def haxorg_configure_layout(self):
        assert self.cpp
        assert self.cpp.source
        assert self.cpp.build
        assert self.cpp.package

        self.cpp.source.includedirs = []
        self.cpp.source.resdirs = []

        self.cpp.build.includedirs = []
        self.cpp.build.libdirs = []
        self.cpp.build.bindirs = []

        self.cpp.package.includedirs = []
        self.cpp.package.libdirs = []
        self.cpp.package.bindirs = []
        self.cpp.package.resdirs = []
