from pathlib import Path
from tempfile import TemporaryDirectory

from beartype.typing import Optional
from plumbum import CommandNotFound, local
import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.script_logging import log

CAT = __name__


def babel_eval(
        input: org.OrgCodeEvalInput) -> org.VecOfOrgCodeEvalOutputVec:  # type: ignore
    res = org.VecOfOrgCodeEvalOutputVec()  # type: ignore

    try:
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

    except CommandNotFound:
        pass

    return res
