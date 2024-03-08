from py_cli.haxorg import cli
from click.testing import CliRunner
from tempfile import TemporaryFile, TemporaryDirectory
from pathlib import Path
from py_scriptutils.repo_files import get_haxorg_repo_root_path


def test_help():
    runner = CliRunner()
    result = runner.invoke(cli, ["--help"])
    assert result.exit_code == 0


all_org = get_haxorg_repo_root_path().joinpath("tests/org/corpus/org/all.org").read_text()


def test_tex_export():
    runner = CliRunner()
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        tex_file = dir.joinpath("tex_file.tex")
        org_file = dir.joinpath("org_file.org")
        org_file.write_text(all_org)

        result = runner.invoke(cli, [
            "export",
            "tex",
            f"--infile={org_file}",
            f"--outfile={tex_file}",
            "--do_compile=false",
        ])

        assert result.exit_code == 0, result.output


def test_html_export():
    runner = CliRunner()
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        html_file = dir.joinpath("html_file.html")
        org_file = dir.joinpath("org_file.org")
        org_file.write_text(all_org)
        result = runner.invoke(cli, [
            "export",
            "html",
            f"--infile={org_file}",
            f"--outfile={html_file}",
        ])
