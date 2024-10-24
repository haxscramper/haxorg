from py_cli.scratch_scripts import story_grid
from py_cli.scratch_scripts import activity_analysis
from py_cli.scratch_scripts import subtree_clocking
from py_cli.scratch_scripts import node_clouds
from py_cli.scratch_scripts import import_alxreader_bookmarks
from py_cli.scratch_scripts import mind_map
from py_exporters import export_sqlite
from click.testing import CliRunner, Result
from tempfile import TemporaryDirectory
from pathlib import Path
from py_scriptutils.sqlalchemy_utils import Engine, format_db_all, open_sqlite
from sqlalchemy.orm import sessionmaker
from more_itertools import first_true
import pandas as pd
from py_scriptutils.pandas_utils import dataframe_to_rich_table
from py_scriptutils.rich_utils import render_rich
import py_haxorg.pyhaxorg_wrap as org
from py_haxorg.pyhaxorg_utils import NodeIdProvider
import pytest
from flask import Flask
from py_scriptutils.repo_files import get_haxorg_repo_root_path
import json

CAT = __name__
from py_scriptutils.script_logging import log


def check_cli(result: Result):
    if result.exception:
        raise result.exception

    assert result.exit_code == 0, result.output


def test_story_grid():
    runner = CliRunner()
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        org_file = dir.joinpath("org_file.org")
        res_file = dir.joinpath("html_result.html")
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
        result = runner.invoke(story_grid.cli, [
            f"--infile={org_file}",
            f"--outfile={res_file}",
        ])

        check_cli(result)


def test_node_clouds():
    runner = CliRunner()
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        org_file = dir.joinpath("org_file.org")
        csv_file = dir.joinpath("result.csv")

        org_file.write_text("""
Word1 Word1 Word1
#tag1 #tag1 #tag1##sub1 #tag1##sub2 #tag1##[sub1,sub2]                            

""")
        result = runner.invoke(node_clouds.cli, [
            f"--infile={org_file}",
            f"--outfile={csv_file}",
        ])

        check_cli(result)

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


def test_subtree_clocking():
    runner = CliRunner()
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        org_file = dir.joinpath("org_file.org")
        csv_file = dir.joinpath("result.csv")

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

        result = runner.invoke(subtree_clocking.cli, [
            f"--infile={org_file}",
            f"--outfile={csv_file}",
        ])

        check_cli(result)

        df = pd.read_csv(csv_file)
        assert df["tags"][0] == "tag##sub1,tag2"


def test_base_activity_analysis():
    runner = CliRunner()
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        org_file = dir.joinpath("org_file.org")
        db_file = dir.joinpath("db.sqlite")

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
  - Priority "B" Added at [2024-03-13 Wed 18:01:40 +04]
  - Priority "C" Changed From "B" at [2024-03-13 Wed 18:01:41 +04]
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

        result = runner.invoke(activity_analysis.cli, [
            f"--infile={org_file}",
            f"--db_path={db_file}",
            f"--outdir={dir}",
        ])

        check_cli(result)

        assert db_file.exists()
        engine = open_sqlite(db_file)
        # print(format_db_all(engine))

        dbg = format_db_all(engine, style=False)

        session = sessionmaker(bind=engine)()

        def get_t(T):
            return [it for it in session.query(T).all()]

        blocks = get_t(export_sqlite.Block)
        for expected_text in [
                "Nested logging", "Message 3", "Some more nested logging",
                "More logging in the text", "Test list item with message"
        ]:
            assert (
                first_true(
                    iterable=blocks,
                    pred=lambda it: it.plaintext == expected_text,
                    default=None,
                ),
                "{} {}".format(expected_text, dbg),
            )

        def get_subtree(title: str) -> export_sqlite.Subtree:
            return first_true(
                iterable=get_t(export_sqlite.Subtree),
                pred=lambda it: it.plaintext_title == title,
                default=None,
            )

        subtree1 = get_subtree("Report aggregated cxx code coverage")
        assert subtree1, dbg

        assert (
            first_true(
                iterable=get_t(export_sqlite.NoteModified),
                pred=lambda it: it.plaintext == "Back to todo",
                default=None,
            ),
            dbg,
        )


from py_cli.scratch_scripts.import_alxreader_bookmarks import BookmarkRecord
from datetime import datetime


def test_bookmark_import_1():
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        org_file = dir.joinpath("file.org")
        org_file.write_text("")

        bookmarks = [
            BookmarkRecord(
                book="book1",
                author="author1",
                dateadd=0,
                dateedit=0,
                start=0,
                stop=1,
                booksize=2,
                text="text",
                bookpos=0,
                datelast=datetime(
                    year=2024,
                    month=2,
                    day=10,
                    hour=13,
                    minute=30,
                    second=40,
                ),
                datefirst=0,
            )
        ]

        opts = import_alxreader_bookmarks.AlXreaderImportOptions(
            infile=Path(""),
            target=org_file,
        )

        assert len(bookmarks) == 1
        import_alxreader_bookmarks.impl(opts, bookmarks)
        assert len(bookmarks) == 1
        assert org_file.exists()
        pre_content = org_file.read_text()
        assert len(bookmarks) == 1
        import_alxreader_bookmarks.impl(opts, bookmarks)
        lhs = [it for it in pre_content.split("\n") if it]
        rhs = [it for it in org_file.read_text().split("\n") if it]
        assert lhs == rhs

        node = org.parseString(org_file.read_text())

        book = import_alxreader_bookmarks.get_subtree_at_path(
            node, ["\"book1\" by \"author1\""])
        assert book

        bookmark = import_alxreader_bookmarks.get_subtree_at_path(
            node, [
                "\"book1\" by \"author1\"",
                "[1970-01-01 Thu 00:00:00] 00.000/50.000",
            ])

        assert bookmark

        def get_property_str(name: str) -> str:
            prop: org.NamedProperty = bookmark.getProperty(name)
            assert prop
            return prop.getCustomRaw().value

        assert get_property_str("bookmark_start") == "0"
        assert get_property_str("bookmark_stop") == "1"
        assert get_property_str("bookmark_booksize") == "2"

mind_map_org = get_haxorg_repo_root_path().joinpath("tests/assets/mind_map.org")

def test_mind_map_collection():
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        node = org.parseString(mind_map_org.read_text())
        idProvider = NodeIdProvider()
        graph = mind_map.getGraph(idProvider, [node])
        graph.toJsonGraph().model_dump_json(indent=2)
        graph.toGraphvizGraph()


test_mind_map_collection()
