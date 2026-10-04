from conan import ConanFile
from conan.errors import ConanException


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

    def haxorg_configure_toolchain(self, toolchain):
        python_executable = self.conf.get(
            "user.haxorg:python_executable",
            check_type=str,
        )
        if not python_executable:
            raise ConanException(
                f"{self.name}: user.haxorg:python_executable is required"
            )

        toolchain.cache_variables["Python_EXECUTABLE"] = python_executable

    def package_id(self):
        python_abi = self.conf.get(
            "user.haxorg:python_abi",
            check_type=str,
        )
        if not python_abi:
            raise ConanException(f"{self.name}: user.haxorg:python_abi is required")

        self.info.conf.define("user.haxorg:python_abi", python_abi)
