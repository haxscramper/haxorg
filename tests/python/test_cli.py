from py_cli.haxorg import cli
from click.testing import CliRunner
from tempfile import TemporaryFile, TemporaryDirectory
from pathlib import Path
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.click_utils import click_run_test
from plumbum import local
import pytest
from plumbum import CommandNotFound


def test_help():
    runner = CliRunner()
    click_run_test(cli, ["--help"])


all_org_file = get_haxorg_repo_root_path().joinpath("tests/org/corpus/org/all.org")
all_org = all_org_file.read_text()


def test_tex_export():
    runner = CliRunner()
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        tex_file = dir.joinpath("tex_file.tex")
        org_file = dir.joinpath("org_file.org")
        org_file.write_text(all_org)

        click_run_test(cli, [
            "export",
            "tex",
            f"--infile={org_file}",
            f"--outfile={tex_file}",
            "--do_compile=false",
        ])


def test_html_export():
    runner = CliRunner()
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        out_file = dir.joinpath("html_file.html")
        click_run_test(cli, [
            "export",
            "html",
            f"--infile={all_org_file}",
            f"--outfile={out_file}",
        ])


def test_sqlite_export():
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        out_file = dir.joinpath("out_file.sqlite")
        click_run_test(cli, [
            "export",
            "sqlite",
            f"--infile={all_org_file}",
            f"--outfile={out_file}",
        ])

def has_pandoc() -> bool:
    try:
        local["pandoc"]
        return True
    except CommandNotFound:
        return False

@pytest.mark.skipif(not has_pandoc(), reason="`pandoc` binary is not installed, skipping tests")
def test_pandoc_export():
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        dir = Path("/tmp")
        out_file = dir.joinpath("out_file.json")
        click_run_test(cli, [
            "export",
            "pandoc",
            f"--infile={all_org_file}",
            f"--outfile={out_file}",
        ])

        pandoc = local["pandoc"]
        pandoc.run([
            "-f",
            "json",
            "-t",
            "markdown",
            str(out_file),
            "-o",
            out_file.with_suffix(".md"),
        ])
