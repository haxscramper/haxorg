import py_haxorg.pyhaxorg_wrap as org
from beartype import beartype
from beartype.typing import Optional
from pathlib import Path


@beartype
def evalCode(node: org.Org, debug: Optional[Path] = None) -> org.Org:

    def callback_impl(
        input: org.OrgCodeEvalInput
    ) -> org.VecOfOrgCodeEvalOutputVec:  # type: ignore[name-defined]
        result = org.VecOfOrgCodeEvalOutputVec()  # type: ignore[name-defined]

        match input.language:
            case "plantuml":
                import py_haxorg.babel_plantuml
                result = py_haxorg.babel_plantuml.babel_eval(input)

        return result

    conf = org.PyCodeEvalParameters(evalBlock=callback_impl)
    if debug:
        conf.setTraceFile(str(debug))

    return org.evaluateCodeBlocks(node, conf)
