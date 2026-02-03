from pathlib import Path

from beartype import beartype
from beartype.typing import Optional
import py_haxorg.pyhaxorg_wrap as org


@beartype
def evalCode(node: org.Org, debug: Optional[Path] = None) -> org.Org:

    def callback_impl(
        input: org.OrgCodeEvalInput
    ) -> org.VecOfOrgCodeEvalOutputVec:  # type: ignore[name-defined]
        result = org.VecOfOrgCodeEvalOutputVec()  # type: ignore

        match input.language:
            case "plantuml":
                import py_haxorg.babel_plantuml
                result = py_haxorg.babel_plantuml.babel_eval(input)

        return result

    conf = org.PyCodeEvalParameters(evalBlock=callback_impl)
    if debug:
        conf.setTraceFile(str(debug))

    return org.evaluateCodeBlocks(node, conf)
