from conan import ConanFile


class HaxdexCppReflReadConan(ConanFile):
    name = "haxdex_read_code_cpp"
    version = "0.1.0"
    package_type = "application"

    python_requires = "haxorg_conan_base/0.1.0"
    python_requires_extend = "haxorg_conan_base.HaxorgPackage"

    default_options = {
        "hwloc/*:shared": True,
    }

    def requirements(self):
        self.requires(
            "hstd_cpp_lib/0.1.0",
            transitive_headers=True,
            transitive_libs=True,
        )
        self.requires("protobuf/[>=5 <6]")
        self.requires("sqlitecpp/[>=3.3 <4]")
        self.requires("onetbb/[>=2022.0 <2024]")

    def build_requirements(self):
        self.tool_requires("protobuf/[>=5 <6]")
