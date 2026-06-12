from pathlib import Path

import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.script_logging import log

CAT = __name__


def test_immutable_ast_conversion() -> None:
    parse = org.ParseContext()
    node = parse.parseString("random paragraph", "<test>")
    context = org.initImmutableAstContext()
    version = context.addRoot(node)
    root_adapter = version.getRootAdapter()
    assert root_adapter.getKind() == org.OrgSemKind.Document
    paragraph0 = root_adapter.at(0)
    assert paragraph0.getKind() == org.OrgSemKind.Paragraph
