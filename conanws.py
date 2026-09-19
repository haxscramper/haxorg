from conan import ConanFile, Workspace
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout


class MonorepoConan(ConanFile):
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        toolchain = CMakeToolchain(self)
        toolchain.variables["ORG_BUILD_WITH_QT"] = False
        toolchain.variables["ORG_BUILD_EMCC"] = False
        toolchain.variables["ORG_BUILD_WITH_PERFETTO"] = True
        toolchain.variables["ORG_BUILD_WITH_TRACY"] = True
        toolchain.variables["ORG_BUILD_WITH_PROTOBUF"] = True
        toolchain.variables["ORG_BUILD_WITH_PROTOVALIDATE"] = True
        toolchain.variables["ORG_BUILD_TESTS"] = True
        toolchain.variables["BUILD_TESTING"] = True
        toolchain.generate()


class MonorepoWorkspace(Workspace):
    def root_conanfile(self):
        return MonorepoConan
