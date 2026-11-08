from pathlib import Path
from tempfile import TemporaryDirectory

from loguru import logger
from plumbum import CommandNotFound, local

import haxorg_py_lib.pyhaxorg_wrap as org


def babel_eval(input: org.OrgCodeEvalInput) -> org.HstdVecOfOrgCodeEvalOutput:
    "Evaluate babel code for plantuml"
    res = org.HstdVecOfOrgCodeEvalOutput()

    try:
        cmd = local["plantuml"]

        with TemporaryDirectory() as puml_dir:
            dir = Path(puml_dir)
            dir = Path("/tmp")
            input_file = dir.joinpath("input.puml")
            input_file.write_text(input.tangledCode)
            logger.info("Running plantuml evaluation")

            cmd.run(
                [
                    str(input_file),
                    "-o",
                    str(dir),
                ]
            )

    except CommandNotFound:
        pass

    return res
