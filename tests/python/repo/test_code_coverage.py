import py_repository.gen_coverage_cxx as cov
from plumbum import local
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from pathlib import Path
from beartype.typing import Optional, List
from beartype import beartype
from dataclasses import dataclass, field
from tempfile import TemporaryDirectory
import pandas as pd
from py_scriptutils.sqlalchemy_utils import open_sqlite_session
from sqlalchemy import select
from py_scriptutils.pandas_utils import dataframe_to_rich_table, assert_frame
from py_scriptutils.rich_utils import render_rich

profdata_merger = get_haxorg_repo_root_path().joinpath(
    "build/utils/profdata_merger/profdata_merger")

tool_dir = get_haxorg_repo_root_path().joinpath("toolchain/llvm/bin")


@beartype
@dataclass
class ProfileRunParams():
    dir: Path
    text: str
    run_params: List[str] = field(default_factory=list)
    stdout: Optional[str] = None
    stderr: Optional[str] = None

    def get_code(self) -> Path:
        return self.dir.joinpath("file.cpp")

    def get_binary(self) -> Path:
        return self.dir.joinpath("file.bin")

    def get_profraw(self) -> Path:
        return self.dir.joinpath("file.profraw")

    def get_sqlite(self) -> Path:
        return self.dir.joinpath("file.sqlite")

    def get_summary(self) -> Path:
        return self.dir.joinpath("coverage-summary.json")

    def run_compile(self):
        cmd = local[tool_dir.joinpath("clang++")]
        self.get_code().write_text(self.text)
        cmd.run([
            self.get_code(),
            "-fprofile-instr-generate",
            "-fcoverage-mapping",
            "-o",
            self.get_binary(),
        ])

    def run_binary(self):
        cmd = local[self.get_binary()].with_env(LLVM_PROFILE_FILE=str(self.get_profraw()))
        code, stdout, stderr = cmd.run(self.run_params)
        self.stdout = stdout
        self.stderr = stderr
        assert self.get_profraw().exists()

    def run_profmerge(self):
        self.get_summary().write_text(
            cov.ProfdataFullProfile(runs=[
                cov.ProfdataCookie(
                    test_binary=str(self.get_binary()),
                    test_name="test",
                    test_class="class",
                    test_profile=str(self.get_profraw()),
                    test_params=None,
                )
            ]).model_dump_json(indent=2))

        cmd = local[profdata_merger]
        cmd.run([
            cov.ProfdataParams(
                coverage=str(self.get_summary()),
                coverage_db=str(self.get_sqlite()),
            ).model_dump_json()
        ])

    def run(self):
        self.dir.mkdir(exist_ok=True, parents=True)
        self.run_compile()
        self.run_binary()
        self.run_profmerge()


def test_base_run():
    with TemporaryDirectory() as tmp:
        dir = Path("/tmp/test_base_run_coverage")
        cmd = ProfileRunParams(dir=dir, text="int main() {}")
        cmd.run()
        assert cmd.get_sqlite().exists()

        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)

        frame = pd.read_sql_query(session.query(cov.CovFunction).statement, session.bind)
        assert_frame(frame, [dict(mangled="main", demangled="main")])
