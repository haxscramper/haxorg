import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.script_logging import log
from pathlib import Path
from beartype.typing import List
from py_haxorg.babel import evalCode
import pytest

CAT = __name__

def test_trivial_code_eval() -> None:
    parse = org.ParseContext()
    node = parse.parseString("""#+begin_src test :results value raw
content
#+end_src""", "<test>")

    conf = org.PyCodeEvalParameters()
    buf: List[org.OrgCodeEvalInput] = []
    def eval_block(input: org.OrgCodeEvalInput) -> org.VecOfOrgCodeEvalOutputVec:
        result = org.VecOfOrgCodeEvalOutputVec()
        item  = org.OrgCodeEvalOutput()
        item.stdoutText = "*bold*"
        result.append(item)
        buf.append(input)
        return result

    conf.evalBlock = eval_block

    ev = org.evaluateCodeBlocks(node, conf, parse)

    Path("/tmp/result.txt").write_text(org.treeRepr(ev, colored=False))

    assert buf[0].language == "test"
    assert buf[0].resultFormat == org.OrgCodeEvalInputResultFormat.Raw
    assert buf[0].resultType == org.OrgCodeEvalInputResultType.Scalar

    assert ev.getKind() == org.OrgSemKind.Document
    assert ev.at(0).getKind() == org.OrgSemKind.BlockCode

    bc: org.BlockCode = ev.at(0)

    assert bc.result
    res: org.BlockCodeEvalResult = bc.result[0]

    assert res.node.getKind() == org.OrgSemKind.StmtList
    w: org.Word = res.node.at(0).at(0).at(0)
    assert w.text == "bold"

@pytest.mark.skip()
def test_babel_eval_trivial() -> None:
    parse = org.ParseContext()
    node = parse.parseString("""#+begin_src plantuml
@startuml
Alice -> Bob: Authentication Request
Bob --> Alice: Authentication Response

Alice -> Bob: Another authentication Request
Alice <-- Bob: Another authentication Response
@enduml
#+end_src""", "<test>")

    evaluated = evalCode(node, Path("/tmp/babel_trivial_eval.log"))
