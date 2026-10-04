import shlex
import sys
from pathlib import Path

from conan import ConanFile
from conan.tools.build import can_run


class NanobindTestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    test_type = "explicit"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def test(self):
        if not can_run(self):
            return

        dependency = self.dependencies["ex_cpp_nanobind"]
        package = Path(dependency.package_folder)
        python = self.conf.get(
            "user.haxorg:python_executable",
            default=sys.executable,
            check_type=str,
        )

        self.run(
            shlex.join(
                [
                    python,
                    str(Path(self.source_folder) / "main.py"),
                    str(package / "lib"),
                ]
            )
        )
