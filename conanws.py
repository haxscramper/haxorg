from pathlib import Path

from conan import ConanFile, Workspace
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout


class MonorepoConan(ConanFile):
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        CMakeDeps(self).generate()

        toolchain = CMakeToolchain(self)
        toolchain.cache_variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = True

        protobuf_dep = self.dependencies.build.get(
            "protobuf"
        ) or self.dependencies.host.get("protobuf")
        if protobuf_dep:
            protoc = str(Path(protobuf_dep.package_folder) / "bin" / "protoc")
            toolchain.cache_variables["Protobuf_PROTOC_EXECUTABLE"] = protoc
            toolchain.cache_variables["PROTOC_PROGRAM"] = protoc

        toolchain.generate()


class MonorepoWorkspace(Workspace):
    def root_conanfile(self):
        return MonorepoConan
