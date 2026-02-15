from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout, CMakeDeps, CMakeToolchain


class HaxorgConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    options = {
        "use_perfetto": [True, False],
        "use_tracy": [True, False],
        "use_python_bindings": [True, False],
        "deps_use_protobuf": [True, False],
        "deps_use_msgpack": [True, False],
    }

    default_options = {
        "use_perfetto": False,
        "use_tracy": False,
        "use_python_bindings": True,
        "deps_use_protobuf": True,
        "deps_use_msgpack": True,
    }

    def requirements(self):
        self.requires("cpptrace/[>=1.0.4 <2]")
        self.requires("foonathan-lexy/[>=2025.05.0 <2026]")
        self.requires("cctz/[>=2.4 <3]")
        self.requires("zstd/[>=1.5.7 <2]")
        self.requires("pybind11/[>=3.0.1 <4]")
        self.requires("openssl/[>=3.6.1 <4]")
        self.requires("yaml-cpp/[>=0.8.0 <1]")
        self.requires("range-v3/[>=0.12.0 <1]")
        self.requires("immer/[>=0.8.1 <1]")
        self.requires("lager/[>=0.1.1 <1]")
        self.requires("nlohmann_json/[>=3.12.0 <4]")
        self.requires("boost/[>=1.90.0 <2]", override=True)

        if self.options.use_perfetto:
            self.requires("perfetto/[>=52.0 <53]")
        if self.options.use_tracy:
            self.requires("tracy/[>=0.13.1 <1]")
        if self.options.deps_use_protobuf:
            self.requires("protobuf/[>=6.32.1 <7]")
        if self.options.deps_use_msgpack:
            self.requires("msgpack-cxx/[>=7.0.0 <8]")

    def configure(self):
        self.options["boost/*"].without_cobalt = True

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["ORG_USE_PERFETTO"] = self.options.use_perfetto
        tc.cache_variables["ORG_USE_TRACY"] = self.options.use_tracy
        tc.cache_variables[
            "ORG_BUILD_PYHAXORG_BINDINGS"] = self.options.use_python_bindings
        tc.cache_variables["ORG_BUILD_WITH_PROTOBUF"] = self.options.deps_use_protobuf
        tc.cache_variables["ORG_BUILD_WITH_MSGPACK"] = self.options.deps_use_msgpack
        # tc.cache_variables["CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH"] = False
        tc.cache_variables["CMAKE_FIND_USE_SYSTEM_PACKAGE_REGISTRY"] = False
        tc.cache_variables["ORG_IS_CONAN_BUILD"] = True
        tc.cache_variables["ORG_BUILD_INTERNAL_TOOLS"] = False
        # tc.cache_variables["CMAKE_FIND_USE_CMAKE_SYSTEM_PATH"] = False
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(cli_args=["--fresh"])
        cmake.build()

    def build_requirements(self):
        if self.options.deps_use_protobuf:
            self.tool_requires("protobuf/[>=6.32.1 <7]")
