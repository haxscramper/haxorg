from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class HaxorgCppOrgCliConan(ConanFile):
    name = "haxorg_cpp_org_cli"
    version = "0.1.0"

    settings = "os", "compiler", "build_type", "arch"

    exports_sources = (
        "CMakeLists.txt",
        "cmake/*",
        "src/*",
    )

    def requirements(self):
        self.requires("hstd_cpp_lib/0.1.0")
        self.requires(
            "haxorg_cpp_org_lib/0.1.0",
            transitive_headers=True,
            transitive_libs=True,
        )
        self.requires("abseil/[>=20250127.0 <20260000]")
        self.requires("argparse/[>=3.2 <4]")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        toolchain = CMakeToolchain(self)
        toolchain.generate()

        dependencies = CMakeDeps(self)
        dependencies.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(cli_args=["--fresh"])
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.bindirs = ["bin"]
        self.cpp_info.builddirs = ["lib/cmake/HaxorgCppOrgCli"]
        self.cpp_info.set_property("cmake_find_mode", "none")
