from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class HaxdexCppReflReadConan(ConanFile):
    name = "haxdex-cpp-refl-read"
    version = "0.1.0"

    settings = "os", "compiler", "build_type", "arch"

    exports_sources = (
        "CMakeLists.txt",
        "cmake/*",
        "src/*",
    )

    def requirements(self):
        self.requires(
            "hstd/0.1.0",
            transitive_headers=True,
            transitive_libs=True,
        )
        self.requires("protobuf/[>=5 <6]")
        self.requires("sqlitecpp/[>=3.3 <4]")
        self.requires("onetbb/[>=2022.0 <2023]")

    def build_requirements(self):
        self.tool_requires("protobuf/[>=5 <6]")

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
        self.cpp_info.builddirs = ["lib/cmake/HaxdexCppReflRead"]
        self.cpp_info.set_property("cmake_find_mode", "none")
