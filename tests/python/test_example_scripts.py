from py_cli.scratch_scripts import story_grid
from py_cli.scratch_scripts import activity_analysis
from py_exporters import export_sqlite
from click.testing import CliRunner
from tempfile import TemporaryDirectory
from pathlib import Path
from py_scriptutils.sqlalchemy_utils import Engine, format_db_all, open_sqlite
from sqlalchemy.orm import sessionmaker
from more_itertools import first_true

CAT = __name__
from py_scriptutils.script_logging import log


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

        assert result.exit_code == 0, result.output


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

        if result.exception:
            raise result.exception

        assert result.exit_code == 0, result.output
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
