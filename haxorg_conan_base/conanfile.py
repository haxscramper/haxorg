import os
import re
from pathlib import Path

from conan import ConanFile
from conan.errors import ConanException
from conan.tools.build import can_run
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import Environment
from conan.tools.files import copy

PACKAGE_NAME_RE = re.compile(r"[a-z][a-z0-9]*(_[a-z0-9]+)*")


class HaxorgPackage:
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = (
        "CMakeLists.txt",
        "cmake/*",
        "src/*",
        "proto/*",
        "tests/*",
    )

    # File names in `cmake/` exported to consumers as CMake build modules.
    haxorg_cmake_build_modules: tuple[str, ...] = ()

    # Patterns copied from `src/` into the installed `include/`
    haxorg_header_patterns: tuple[str, ...] = ("*.hpp", "*.h")

    @property
    def haxorg_namespace(self) -> str:
        return self.name.split("_")[0]

    @property
    def haxorg_cmake_target(self) -> str:
        return f"{self.haxorg_namespace}::{self.name}"

    @property
    def haxorg_kebab_name(self) -> str:
        return self.name.replace("_", "-")

    @property
    def haxorg_skip_tests(self) -> bool:
        return self.conf.get("tools.build:skip_test", default=False, check_type=bool)

    # Hooks for package-specific configuration
    def haxorg_configure_deps(self, deps: CMakeDeps):
        pass

    def haxorg_configure_toolchain(self, toolchain: CMakeToolchain):
        pass

    def haxorg_package_info(self):
        pass

    def haxorg_validate_structure(self, root_dir: str):
        root = Path(root_dir)
        errors: list[str] = []

        if not PACKAGE_NAME_RE.fullmatch(self.name):
            errors.append(f"package name '{self.name}' must be lowercase snake_case")

        def check_single_subdir(dirname: str, required: bool):
            base = root / dirname
            if not base.is_dir():
                if required:
                    errors.append(f"'{dirname}/{self.name}' must exist")
                return

            if not (base / self.name).is_dir():
                errors.append(f"'{dirname}/{self.name}' must exist")

            extra = sorted(p.name for p in base.iterdir() if p.name != self.name)
            if extra:
                errors.append(
                    f"'{dirname}/' may only contain '{self.name}', found: {extra}"
                )

        check_single_subdir("src", required=True)
        check_single_subdir("proto", required=False)

        cmake_dir = root / "cmake"
        for template in cmake_dir.glob("*.cmake.in"):
            if template.name != template.name.lower() or not template.name.startswith(
                f"{self.haxorg_kebab_name}-"
            ):
                errors.append(
                    f"'cmake/{template.name}' must be named "
                    f"'{self.haxorg_kebab_name}-<suffix>.cmake.in'"
                )

        for module in self.haxorg_cmake_build_modules:
            if not (cmake_dir / module).is_file():
                errors.append(f"build module 'cmake/{module}' does not exist")

        if errors:
            raise ConanException(
                f"{self.name}: invalid package structure:\n  " + "\n  ".join(errors)
            )

    def haxorg_dependency_proto_dirs(self) -> list[str]:
        result = []
        for dep in self.dependencies.host.values():
            if not dep.cpp_info.get_property("haxorg_package"):
                continue

            for resdir in dep.cpp_info.resdirs:
                if os.path.isdir(os.path.join(resdir, dep.ref.name)):
                    result.append(resdir.replace("\\", "/"))

        return result

    def layout(self):
        cmake_layout(self)
        build_modules = [f"cmake/{name}" for name in self.haxorg_cmake_build_modules]

        self.cpp.source.includedirs = ["src"]
        self.cpp.source.resdirs = ["proto"]
        self.cpp.source.set_property("cmake_build_modules", build_modules)

        self.cpp.build.includedirs = ["generated/proto"]
        self.cpp.build.libdirs = ["."]

        self.cpp.package.includedirs = ["include"]
        self.cpp.package.libdirs = ["lib"]
        self.cpp.package.resdirs = ["proto"]
        self.cpp.package.set_property("cmake_build_modules", build_modules)

    def generate(self):
        self.haxorg_validate_structure(self.source_folder)

        deps = CMakeDeps(self)
        self.haxorg_configure_deps(deps)
        deps.generate()

        toolchain = CMakeToolchain(self)
        toolchain.variables["HAXORG_PACKAGE_NAME"] = self.name
        toolchain.variables["HAXORG_PACKAGE_NAMESPACE"] = self.haxorg_namespace
        toolchain.variables["HAXORG_DEPS_PROTO_IMPORT_DIRS"] = ";".join(
            self.haxorg_dependency_proto_dirs()
        )
        toolchain.variables["BUILD_TESTING"] = not self.haxorg_skip_tests

        warning_suppressions = self.conf.get(
            "user.haxorg:warning_suppressions", default="", check_type=str
        )
        if warning_suppressions:
            toolchain.variables["ORG_WARNING_SUPPRESSIONS"] = warning_suppressions

        self.haxorg_configure_toolchain(toolchain)
        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build(
            build_tool_args=self.conf.get(
                "user.haxorg:ninja_args", default=[], check_type=list
            )
        )

        if not self.haxorg_skip_tests and can_run(self):
            environment = Environment()
            environment.define("CTEST_OUTPUT_ON_FAILURE", "1")
            with environment.vars(self).apply():
                cmake.test()

    def package(self):
        src = self.source_folder
        build = self.build_folder
        pkg = self.package_folder

        for pattern in self.haxorg_header_patterns:
            copy(self, pattern, os.path.join(src, "src"), os.path.join(pkg, "include"))

        copy(
            self,
            "*.pb.h",
            os.path.join(build, "generated", "proto"),
            os.path.join(pkg, "include"),
        )
        copy(self, "*.proto", os.path.join(src, "proto"), os.path.join(pkg, "proto"))

        for module in self.haxorg_cmake_build_modules:
            copy(self, module, os.path.join(src, "cmake"), os.path.join(pkg, "cmake"))

        copy(self, f"lib{self.name}.a", build, os.path.join(pkg, "lib"), keep_path=False)

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", self.name)
        self.cpp_info.set_property("cmake_target_name", self.haxorg_cmake_target)
        self.cpp_info.set_property("haxorg_package", True)
        self.cpp_info.libs = [self.name]
        self.haxorg_package_info()


class HaxorgConanBase(ConanFile):
    name = "haxorg_conan_base"
    version = "0.1.0"
    package_type = "python-require"
