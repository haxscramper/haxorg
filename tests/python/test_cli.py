from tempfile import TemporaryDirectory
from pathlib import Path
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.click_utils import click_run_test
from plumbum import local
from plumbum import CommandNotFound
import py_haxorg.pyhaxorg_wrap as org
from py_cli import haxorg_opts, haxorg_cli
from beartype.typing import Dict, Any

org_corpus_dir = get_haxorg_repo_root_path().joinpath("tests/org/corpus/org")
all_org_file = org_corpus_dir.joinpath("all.org")
all_org = all_org_file.read_text()


def get_export_debug(dir: Path) -> Dict[str, Any]:
    return dict(exportTraceFile=str(dir.joinpath("export_trace.log")))


def test_tex_export(stable_test_dir: Path) -> None:
    dir = stable_test_dir
    tex_file = dir.joinpath("tex_file.tex")
    org_file = dir.joinpath("org_file.org")
    org_file.write_text(all_org)

    from py_cli.export.haxorg_export_tex import export_tex

    export_tex(
        haxorg_opts.RootOptions(
            export=haxorg_opts.ExportOptions(**get_export_debug(stable_test_dir),
                                             tex=haxorg_opts.TexExportOptions(
                                                 infile=org_file,
                                                 outfile=tex_file,
                                                 do_compile=False,
                                             ))))


def test_html_export(stable_test_dir: Path) -> None:
    from py_cli.export.haxorg_export_html import export_html
    export_html(
        haxorg_opts.RootOptions(export=haxorg_opts.ExportOptions(
            html=haxorg_opts.ExportHtmlOptions(
                infile=all_org_file,
                outfile=stable_test_dir.joinpath("html_file.html"),
            ))))


def test_sqlite_export(stable_test_dir: Path) -> None:
    from py_cli.export.haxorg_export_sqlite import export_sqlite
    export_sqlite(
        haxorg_opts.RootOptions(export=haxorg_opts.ExportOptions(
            **get_export_debug(stable_test_dir),
            sqlite=haxorg_opts.ExportSQliteOptions(
                infile=[all_org_file],
                outfile=stable_test_dir.joinpath("out_file.sqlite"),
            ))))


def has_cmd(cmd: str) -> bool:
    try:
        local[cmd]
        return True
    except CommandNotFound:
        return False


def test_pandoc_export(stable_test_dir: Path) -> None:
    from py_cli.export.haxorg_export_pandoc import export_pandoc
    dir = stable_test_dir
    dir.mkdir(parents=True, exist_ok=True)
    out_file = dir.joinpath("out_file.json")
    dir.joinpath("tree.txt").write_text(
        org.treeRepr(
            org.parseString(all_org_file.read_text(), "<mock>"),
            colored=False,
        ))

    opts = haxorg_opts.RootOptions(
        export=haxorg_opts.ExportOptions(**get_export_debug(stable_test_dir),
                                         pandoc=haxorg_opts.ExportPandocOptions(
                                             infile=all_org_file,
                                             outfile=out_file,
                                         )))

    export_pandoc(opts, haxorg_cli.get_run(opts))

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


def test_typst_export_1(stable_test_dir: Path) -> None:
    from py_cli.export.haxorg_export_typst import export_typst
    dst_dir = stable_test_dir.joinpath("dst")
    dst_dir.mkdir(exist_ok=True, parents=True)
    src_dir = stable_test_dir.joinpath("src")
    src_dir.mkdir(exist_ok=True, parents=True)

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

        opts = haxorg_opts.RootOptions(
            export=haxorg_opts.ExportOptions(**get_export_debug(stable_test_dir),
                                             typst=haxorg_opts.TypstExportOptions(
                                                 infile=all_org_file,
                                                 outfile=outfile,
                                                 do_compile=has_cmd("typst"),
                                             )))

        export_typst(opts)

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

        export_typst(opts)

        assert attach2_dst.read_text() == attach2_src.read_text()
        assert attach_dst.read_text() == attach_src.read_text()


def test_typst_export_2(stable_test_dir: Path) -> None:
    from py_cli.export.haxorg_export_typst import export_typst
    outfile = stable_test_dir.joinpath("result.typ")
    infile = stable_test_dir.joinpath("file.org")

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

    opts = haxorg_opts.RootOptions(
        export=haxorg_opts.ExportOptions(**get_export_debug(stable_test_dir),
                                         typst=haxorg_opts.TypstExportOptions(
                                             infile=infile,
                                             outfile=outfile,
                                             do_compile=False,
                                         )))

    export_typst(opts)

    text = outfile.read_text()
    assert "customSubtree" in text
    assert "changeSubtree" in text
