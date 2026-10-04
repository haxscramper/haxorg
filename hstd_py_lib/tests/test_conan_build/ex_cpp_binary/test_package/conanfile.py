import os
import shlex
from pathlib import Path

from conan import ConanFile
from conan.tools.build import can_run


class BinaryTestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    test_type = "explicit"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def test(self):
        if not can_run(self):
            return

        dependency = self.dependencies["ex_cpp_binary"]
        executable = Path(dependency.package_folder) / "bin" / "ex_cpp_binary"
        expected = int(os.environ["EX_EXPECTED_VERSION"])

        self.run(
            f'test "$({shlex.quote(str(executable))})" = {shlex.quote(str(expected))}'
        )
        self.output.info(f"EX_CONAN_TEST_PACKAGE:ex_cpp_binary:{expected}")
