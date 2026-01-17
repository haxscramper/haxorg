from pathlib import Path

import more_itertools
import pandas as pd
import py_haxorg.pyhaxorg_wrap as org
import pytest
from beartype.typing import Any, Dict, List
from plumbum import CommandNotFound, local
from py_cli import haxorg_cli, haxorg_opts
from py_exporters import export_sqlite
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.sqlalchemy_utils import format_db_all, open_sqlite
from sqlalchemy.orm import sessionmaker

CAT = __name__

org_corpus_dir = get_haxorg_repo_root_path().joinpath("tests/org/corpus/org")
all_org_file = org_corpus_dir.joinpath("all.org")
all_org = all_org_file.read_text()


def get_export_debug(dir: Path) -> Dict[str, Any]:
    return dict(exportTraceFile=str(dir.joinpath("export_trace.log")))


def get_root_debug(dir: Path) -> Dict[str, Any]:
    return dict(
        baseToken_traceDir=str(dir),
        tokenizer_traceDir=str(dir),
        parse_traceDir=str(dir),
        sem_traceDir=str(dir),
        treeDump_traceDir=str(dir),
        jsonDump_traceDir=str(dir),
        yamlDump_traceDir=str(dir),
    )


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


@pytest.mark.test_release
def test_story_grid(stable_test_dir: Path) -> None:
    from py_cli.generate.story_grid import story_grid
    org_file = stable_test_dir.joinpath("org_file.org")
    res_file = stable_test_dir.joinpath("html_result.html")
    org_file.write_text("""
* Arc 1
  :properties:
  :story_duration: 1d
  :story_polarity_shift: -/+
  :end:

- =story_event= :: Event description
- =story_location= :: Location
- =story_pov= :: Pov
- =story_note= :: Note
""")

    story_grid(
        haxorg_opts.RootOptions(generate=haxorg_opts.GenerateOptions(
            story_grid=haxorg_opts.StoryGridOpts(
                infile=org_file,
                outfile=res_file,
            ))))


def test_node_clouds(stable_test_dir: Path) -> None:
    from py_cli.generate.node_clouds import node_clouds
    org_file = stable_test_dir.joinpath("org_file.org")
    csv_file = stable_test_dir.joinpath("result.csv")

    org_file.write_text("""
Word1 Word1 Word1
#tag1 #tag1 #tag1##sub1 #tag1##sub2 #tag1##[sub1,sub2]                            

""")

    node_clouds(
        haxorg_opts.RootOptions(generate=haxorg_opts.GenerateOptions(
            node_clouds=haxorg_opts.GenerateNodeCloudOptions(
                infile=[org_file],
                outfile=csv_file,
            ))))

    df = pd.read_csv(csv_file)
    mapping = {key: group for key, group in df.groupby("kind")}
    words = mapping["word"]
    assert len(words) == 1
    assert list(words["text"]) == ["Word1"]
    assert list(words["count"]) == [3]

    tags = mapping["tag"].sort_values(by="text")
    assert len(tags) == 3
    assert list(tags["text"]) == ["tag1", "tag1##sub1", "tag1##sub2"]
    assert list(tags["count"]) == [2, 2, 2]


def test_subtree_clocking(stable_test_dir: Path) -> None:
    from py_cli.generate.subtree_clocking import subtree_clocking
    org_file = stable_test_dir.joinpath("org_file.org")
    csv_file = stable_test_dir.joinpath("result.csv")

    org_file.write_text("""
*** Subtree :tag##sub1:tag2:
  :LOGBOOK:
  CLOCK: [2023-09-25 Mon 19:01:09 +04]--[2023-09-25 Mon 19:27:45 +04] =>  0:26
  CLOCK: [2023-10-02 Mon 18:58:12 +04]--[2023-10-02 Mon 19:28:52 +04] =>  0:30
  CLOCK: [2023-10-09 Mon 19:09:35 +04]--[2023-10-09 Mon 19:30:32 +04] =>  0:21
  CLOCK: [2023-10-16 Mon 19:00:04 +04]--[2023-10-16 Mon 19:21:25 +04] =>  0:21
  CLOCK: [2023-10-23 Mon 19:00:29 +04]--[2023-10-23 Mon 19:23:47 +04] =>  0:23
  CLOCK: [2023-10-30 Mon 19:03:32 +04]--[2023-10-30 Mon 19:36:02 +04] =>  0:33
  CLOCK: [2023-11-06 Mon 19:59:26 +04]--[2023-11-06 Mon 20:25:54 +04] =>  0:26
  CLOCK: [2023-11-13 Mon 19:59:48 +04]--[2023-11-13 Mon 21:04:17 +04] =>  1:05
  CLOCK: [2023-11-20 Mon 20:00:53 +04]--[2023-11-20 Mon 20:30:57 +04] =>  0:30
  CLOCK: [2023-11-27 Mon 20:00:16 +04]--[2023-11-27 Mon 20:51:48 +04] =>  0:51
  CLOCK: [2023-12-04 Mon 19:59:13 +04]--[2023-12-04 Mon 20:57:38 +04] =>  0:58
  CLOCK: [2023-12-11 Mon 19:59:44 +04]--[2023-12-11 Mon 20:57:20 +04] =>  0:58
  CLOCK: [2023-12-18 Mon 19:59:52 +04]--[2023-12-18 Mon 20:50:35 +04] =>  0:51
  CLOCK: [2024-01-08 Mon 20:00:21 +04]--[2024-01-08 Mon 20:58:04 +04] =>  0:58
  CLOCK: [2024-01-22 Mon 19:59:18 +04]--[2024-01-22 Mon 20:37:35 +04] =>  0:38
  CLOCK: [2024-01-29 Mon 20:00:41 +04]--[2024-01-29 Mon 20:23:59 +04] =>  0:23
  CLOCK: [2024-02-05 Mon 20:00:34 +04]--[2024-02-05 Mon 20:35:41 +04] =>  0:35
  CLOCK: [2024-02-12 Mon 20:00:14 +04]--[2024-02-12 Mon 20:39:16 +04] =>  0:39
  :END:
""")

    subtree_clocking(
        haxorg_opts.RootOptions(generate=haxorg_opts.GenerateOptions(
            subtree_clocking=haxorg_opts.ClockTimeAnalysisOptions(
                infile=[org_file],
                outfile=csv_file,
            ))))

    df = pd.read_csv(csv_file)
    assert df["tags"][0] == "tag##sub1,tag2"


def test_codex_tracking(stable_test_dir: Path) -> None:
    from py_cli.generate.codex_tracking import codex_tracking
    target_file = stable_test_dir.joinpath("target.org")
    codex_file = stable_test_dir.joinpath("codex.org")
    outfile = stable_test_dir.joinpath("result.txt")

    target_file.write_text("""
Some random text that can mention, using ABBR radio ID

Sentence with Character name should trigger radio target detection
    """)

    codex_file.write_text("""
* Subtree
  :properties:
  :radio_id: ABBR 
  :end:

* Character description
  :properties:
  :radio_id: Character name
  :end:

        """)

    codex_tracking(
        haxorg_opts.RootOptions(generate=haxorg_opts.GenerateOptions(
            codex_tracking=haxorg_opts.CodexTrackingOptions(
                target_file=target_file,
                codex_files=[codex_file],
                outfile=outfile,
            ))))


@pytest.mark.unstable
def test_base_activity_analysis(stable_test_dir: Path) -> None:
    from py_cli.generate.activity_analysis import activity_analysis
    org_file = stable_test_dir.joinpath("org_file.org")
    db_file = stable_test_dir.joinpath("db.sqlite")

    org_file.write_text("""
*** TODO Report aggregated cxx code coverage
  :PROPERTIES:
  :CREATED:  [2024-03-13 Wed 12:25:29 +04]
  :END:
  :LOGBOOK:
  - Tag "#project##haxorg" Removed on [2024-03-13 Wed 18:01:35 +04]
  - Tag "#project##haxorg" Added on [2024-03-13 Wed 18:01:34 +04]
  CLOCK: [2024-03-13 Wed 18:00:25 +04]--[2024-03-13 Wed 18:01:13 +04] =>  0:01
  - State "WIP"        from "TODO"       [2024-03-13 Wed 18:00:25 +04]
  - Note taken on [2024-03-13 Wed 18:01:02 +04] \\\\
    Add logbook note
  - State "WIP"        from "WIP"        [2024-03-13 Wed 18:01:09 +04]
  - State "PAUSED"     from "WIP"        [2024-03-13 Wed 18:01:13 +04] \\\\
    Paused work, adding test logging
  - State "FAILED"     from "PAUSED"     [2024-03-13 Wed 18:01:21 +04] \\\\
    Test failure
  - State "TODO"       from "FAILED"     [2024-03-13 Wed 18:01:27 +04]
  - Note taken on [2024-03-13 Wed 18:01:30 +04] \\\\
    Back to todo
  - Priority "B" Added on [2024-03-13 Wed 18:01:40 +04]
  - Priority "C" Changed From "B" on [2024-03-13 Wed 18:01:41 +04]
  - Refiled on [2024-03-13 Wed 18:01:56 +04] from [[id:75397715-6471-4a1a-be00-ca4bb656d810][projects:Haxorg/Documentation]]
  - Refiled on [2024-03-13 Wed 18:02:09 +04] from [[file:staging.org][staging:staging.org]]
  :END:

- [2024-03-13 Wed 18:00:27 +04] Test list item with message
- [2024-03-13 Wed 18:00:53 +04] More logging in the text
- [2024-03-13 Wed 18:02:21 +04] Extra logging extra logging
- [2024-03-13 Wed 18:02:26 +04] Message 3
  - [2024-03-13 Wed 18:02:30 +04] Nested logging
  - [2024-03-13 Wed 18:02:33 +04] Some more nested logging

""")

    activity_analysis(
        haxorg_opts.RootOptions(generate=haxorg_opts.GenerateOptions(
            activity_analysis=haxorg_opts.GenerateActivityAnalysisOptions(
                infile=[org_file],
                db_path=db_file,
                outdir=stable_test_dir,
            ))))

    assert db_file.exists()
    engine = open_sqlite(db_file)

    dbg = format_db_all(engine, style=False)

    session = sessionmaker(bind=engine)()

    def get_t(T: Any) -> List[Any]:
        return [it for it in session.query(T).all()]

    blocks = get_t(export_sqlite.Block)
    for expected_text in [
            "Nested logging",
            "Message 3",
            "Some more nested logging",
            "More logging in the text",
            "Test list item with message",
    ]:
        assert more_itertools.first_true(
            iterable=blocks,
            pred=lambda it: expected_text in it.plaintext,
            default=None,
        ), "{} {}".format(expected_text, dbg)

    def get_subtree(title: str) -> export_sqlite.Subtree:

        def pred(it: export_sqlite.Subtree) -> None:
            return it.plaintext_title == title

        return more_itertools.first_true(
            iterable=get_t(export_sqlite.Subtree),
            pred=pred,
            default=None,
        )

    subtree1 = get_subtree("TODO Report aggregated cxx code coverage")
    assert subtree1, dbg

    assert more_itertools.first_true(
        iterable=get_t(export_sqlite.NoteModified),
        pred=lambda it: it.plaintext == "Back to todo",
        default=None,
    ), dbg


def test_mind_map(stable_test_dir: Path, cached_test_dir: Path) -> None:
    from py_cli.generate.mind_map.gen_mind_map import gen_mind_map

    opts = haxorg_opts.RootOptions(
        cache=cached_test_dir,
        generate=haxorg_opts.GenerateOptions(mind_map=haxorg_opts.GenerateMindMapOptions(
            infile=get_haxorg_repo_root_path().joinpath(
                "tests/org/corpus/org/mind_map_test_1.org"),
            outfile=stable_test_dir.joinpath("result.pdf"),
            typst_do_compile=has_cmd("typst"),
        )),
    )

    if not opts.generate.mind_map.org_diagram_tool.exists():
        pytest.skip(f"Org diagram tool at {opts.generate.mind_map.org_diagram_tool} does not exist")

    gen_mind_map(opts)


def test_tag_sorting(stable_test_dir: Path) -> None:
    from py_cli.generate.sort_repository_tags import sort_reposutory_tags, TagDuplicate, DuplicateType
    import functools

    tag_dir = get_haxorg_repo_root_path().joinpath("tests/org/corpus/cli/tag_collection")

    result = sort_reposutory_tags(
        haxorg_opts.RootOptions(generate=haxorg_opts.GenerateOptions(
            sort_tags=haxorg_opts.TagSortingOptions(
                input_dir=tag_dir,
                tag_glossary_file=tag_dir.joinpath("glossary.org"),
                output_dir=stable_test_dir,
            ))))

    def tag_pair(one: tuple[str, ...], two: tuple[str, ...], it: TagDuplicate) -> bool:
        return (it.tag1.tag == one and it.tag2.tag == two) or (it.tag2.tag == one and
                                                               it.tag1.tag == two)

    feature_overlap = more_itertools.first_true(
        iterable=result.duplicate_tag_list,
        pred=functools.partial(tag_pair, ("development", "feature"), ("feature",)),
        default=None,
    )

    assert feature_overlap
    assert feature_overlap.type == DuplicateType.PART_OVERLAP

    nlohmann_json = more_itertools.first_true(
        iterable=result.duplicate_tag_list,
        pred=functools.partial(
            tag_pair,
            ("code", "cpp", "lib", "nlohmann_json"),
            ("code", "cpp", "lib", "nlohmann_jso"),
        ),
        default=None,
    )

    assert nlohmann_json
    assert nlohmann_json.type == DuplicateType.SIMILAR


def test_todo_collector(stable_test_dir: Path) -> None:
    from py_cli.generate.todo_collector import todo_collector

    stable_test_dir.joinpath("file1.org").write_text("""
* TODO Random todo annotation with some title
  :PROPERTIES:
  :CREATED:  [2026-01-10 Sat 17:32:00 +04]
  :END:
- [2026-01-10 Sat 17:32:08 +04] TODO: Some item inside of the main annotation
  - [2026-01-10 Sat 17:32:23 +04] NOTE: Note attached to parent todo item
  - [2026-01-10 Sat 17:32:34 +04] TODO: Nested todo item.
- [2026-01-10 Sat 17:32:18 +04] TODO: Another item
- [2026-01-10 Sat 17:32:38 +04] DONE: Completed collection
- [2026-01-10 Sat 17:32:46 +04] QUESTION: Paragraph with another admonition type
    """)

    result = todo_collector(
        haxorg_opts.RootOptions(**get_root_debug(stable_test_dir),
                                generate=haxorg_opts.GenerateOptions(
                                    todo_collector=haxorg_opts.TodoCollectorOptions(
                                        infile=[stable_test_dir],
                                        outdir=stable_test_dir.joinpath("report.txt"),
                                    ))))
