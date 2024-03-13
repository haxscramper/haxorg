from py_cli.scratch_scripts import story_grid
from click.testing import CliRunner
from tempfile import TemporaryDirectory
from pathlib import Path

def test_story_grid():
    runner = CliRunner()
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        org_file = dir.joinpath("org_file.org")
        res_file = dir.joinpath("html_result.html")
        org_file.write_text(
            """
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
