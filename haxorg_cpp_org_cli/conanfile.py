from conan import ConanFile


class HaxorgCppOrgCliConan(ConanFile):
    name = "haxorg_cpp_org_cli"
    version = "0.1.0"
    package_type = "application"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"

    haxorg_use_cmake_install = True

    def requirements(self):
        self.requires("hstd_cpp_lib/0.1.0", options={"with_perfetto": True})
        self.requires("hstd_cpp_diagram_lib/0.1.0")
        self.requires(
            "haxorg_cpp_org_lib/0.1.0",
            transitive_headers=True,
            transitive_libs=True,
            options={"with_perfetto": True},
        )
        self.requires("abseil/[>=20250127.0 <20260000]")
        self.requires("argparse/[>=3.2 <4]")

    def haxorg_package_info(self):
        self.cpp_info.builddirs = ["lib/cmake/haxorg_cpp_org_cli"]
        self.cpp_info.set_property("cmake_find_mode", "none")
