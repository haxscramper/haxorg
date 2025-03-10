import py_haxorg.pyhaxorg_wrap as org
from plumbum import local
from beartype.typing import Optional
from pathlib import Path
from tempfile import TemporaryDirectory
from py_scriptutils.script_logging import log

CAT = __name__


def babel_eval(input: org.OrgCodeEvalInput) -> org.VecOfOrgCodeEvalOutputVec:
    res = org.VecOfOrgCodeEvalOutputVec()

    cmd = local["plantuml"]

    with TemporaryDirectory() as puml_dir:
        dir = Path(puml_dir)
        dir = Path("/tmp")
        input_file = dir.joinpath("input.puml")
        input_file.write_text(input.tangledCode)
        log(CAT).info("Running plantuml evaluation")

        cmd.run([
            str(input_file),
            "-o",
            str(dir),
        ])

    return res
