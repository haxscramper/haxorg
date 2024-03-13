from py_cli.scratch_scripts import story_grid
from py_cli.scratch_scripts import activity_analysis
from py_exporters import export_sqlite 
from click.testing import CliRunner
from tempfile import TemporaryDirectory
from pathlib import Path
from py_scriptutils.sqlalchemy_utils import Engine, format_db_all, open_sqlite
from sqlalchemy.orm import sessionmaker


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
[2013-01-02 12:30:40] Timestamped paragraph
""")

        result = runner.invoke(activity_analysis.cli, [
            f"--infile={org_file}",
            f"--db_path={db_file}",
            f"--outdir={dir}",
        ])

        assert result.exit_code == 0, result.output
        assert db_file.exists()
        engine = open_sqlite(db_file)

        session = sessionmaker(bind=engine)()
        blocks = [it for it in session.query(export_sqlite.Block).all()]
        assert len(blocks) == 1, format_db_all(engine, style=False)


        
