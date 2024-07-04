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


org_corpus_dir = get_haxorg_repo_root_path().joinpath("tests/org/corpus/org")
all_org_file = org_corpus_dir.joinpath("all.org")
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


def has_cmd(cmd: str) -> bool:
    try:
        local[cmd]
        return True
    except CommandNotFound:
        return False


def test_pandoc_export():
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        out_file = dir.joinpath("out_file.json")
        click_run_test(cli, [
            "export",
            "pandoc",
            f"--infile={all_org_file}",
            f"--outfile={out_file}",
        ])

        if has_cmd("pandoc"):
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


def test_typst_export_1():
    with TemporaryDirectory() as dst_dir_tmp, TemporaryDirectory() as src_dir_tmp:
        dst_dir = Path(dst_dir_tmp)
        dst_dir = Path("/tmp/test_typst_export_1")
        dst_dir.mkdir(exist_ok=True)

        src_dir = Path(src_dir_tmp)

        outfile = dst_dir.joinpath("result.typ")
        infile = src_dir.joinpath("file.org")
        attach_src = src_dir.joinpath("attach.typ")
        attach2_src = src_dir.joinpath("attach2.typ")
        attach_src.write_text("attach")
        attach2_src.write_text("attach2")

        attach_dst = dst_dir.joinpath("attach.typ")
        attach2_dst = dst_dir.joinpath("attach2.typ")

        if attach_dst.exists():
            attach_dst.unlink()

        if attach2_dst.exists():
            attach2_dst.unlink()

        infile.write_text("""
#+attr_link: :attach-method copy :attach-on-export t
[[attachment:attach.typ]]

#+attr_link: :attach-method symlink :attach-on-export t
[[attachment:attach2.typ]]

#+begin_export typst
#include "attach.typ"
#include "attach2.typ"
#+end_export

* Subtree1 :tag:

        """)

        args = [
            "export",
            "typst",
            f"--infile={infile}",
            f"--outfile={outfile}",
            "--do_compile=False",
        ]

        click_run_test(cli, args)

        assert attach_dst.exists()
        assert attach2_dst.exists()

        assert attach2_dst.read_text() == attach2_src.read_text()
        assert attach_dst.read_text() == attach_src.read_text()

        attach2_src.write_text("changed attach2 text")
        assert attach2_dst.read_text() == attach2_src.read_text()

        attach_src.write_text("changed attach text")
        assert attach_dst.read_text() != attach_src.read_text()

        text = outfile.read_text()
        assert "#include \"attach.typ\"" in text
        assert "[[attachment" not in text
        assert "#orgParagraph[Subtree1]" in text
        assert "tags: (\"tag\"," in text
        assert "#orgSubtree" in text
        
        click_run_test(cli, args)

        assert attach2_dst.read_text() == attach2_src.read_text()
        assert attach_dst.read_text() == attach_src.read_text()




def test_typst_export_2():
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        dir = Path("/tmp/test_typst_export_2")
        dir.mkdir(exist_ok=True)
        outfile = dir.joinpath("result.typ")
        infile = dir.joinpath("file.org")

        infile.write_text("""
#+begin_export typst :edit-config pre-visit
[tags]
subtree = "customSubtree"
#+end_export

* Subtree

#+begin_export typst :edit-config in-visit
[tags]
subtree = "changeSubtree"
#+end_export

* Subtree2

        """)

        click_run_test(cli, [
            "export",
            "typst",
            f"--infile={infile}",
            f"--outfile={outfile}",
            "--do_compile=False",
        ])

        text = outfile.read_text()
        assert "customSubtree" in text
        assert "changeSubtree" in text
