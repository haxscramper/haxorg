from conan import ConanFile, Workspace
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout


class MonorepoConan(ConanFile):
    settings = "os", "arch", "compiler", "build_type"

    def requirements(self):
        self.requires("haxorg_cpp_org_cli/[>=0.1.0 <999]")
        self.requires("haxdex_cpp_refl_wrap/[>=0.1.0 <999]")
        # self.requires("haxorg_c_lib_wrap/[>=0.1.0 <999]")
        # self.requires("haxorg_py_lib_wrap/[>=0.1.0 <999]")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        toolchain = CMakeToolchain(self)
        toolchain.cache_variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
        toolchain.generate()


class MonorepoWorkspace(Workspace):
    def root_conanfile(self):
        return MonorepoConan
