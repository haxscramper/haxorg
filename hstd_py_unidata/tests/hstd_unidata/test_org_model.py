from __future__ import annotations

import enum
from pathlib import Path

from beartype.typing import Annotated
from hstd_py_unidata.model_dsl import __variant__, get_dsl_model
from hstd_py_unidata.model_frontend import EnFieldAnnotation
from hstd_py_unidata.model_index import ModelIndex

M = get_dsl_model("org.sem")


class OrgTokenKind(M.Enum):
    Ampersand: Annotated[int, EnFieldAnnotation()] = enum.auto()
    AngleBegin: Annotated[int, EnFieldAnnotation()] = enum.auto()
    AngleEnd: Annotated[int, EnFieldAnnotation()] = enum.auto()
    AnyPunct: Annotated[int, EnFieldAnnotation()] = enum.auto()
    Asterisk: Annotated[int, EnFieldAnnotation()] = enum.auto()
    At: Annotated[int, EnFieldAnnotation()] = enum.auto()
    Backtick: Annotated[int, EnFieldAnnotation()] = enum.auto()
    BigIdent: Annotated[int, EnFieldAnnotation()] = enum.auto()
    BoldBegin: Annotated[int, EnFieldAnnotation()] = enum.auto()
    BoldEnd: Annotated[int, EnFieldAnnotation()] = enum.auto()
    BoldUnknown: Annotated[int, EnFieldAnnotation()] = enum.auto()
    BraceBegin: Annotated[int, EnFieldAnnotation()] = enum.auto()
    BraceEnd: Annotated[int, EnFieldAnnotation()] = enum.auto()
    Checkbox: Annotated[int, EnFieldAnnotation()] = enum.auto()
    Circumflex: Annotated[int, EnFieldAnnotation()] = enum.auto()
    CmdAdmonitionEnd: Annotated[int, EnFieldAnnotation()] = enum.auto()
    CmdAttr: Annotated[int, EnFieldAnnotation()] = enum.auto()
    CmdAuthor: Annotated[int, EnFieldAnnotation()] = enum.auto()
    CmdBindRaw: Annotated[int, EnFieldAnnotation()] = enum.auto()
    CmdCall: Annotated[int, EnFieldAnnotation()] = enum.auto()
    CmdCaption: Annotated[int, EnFieldAnnotation()] = enum.auto()


class OrgDiagnostics(M.Class):
    class ParseTokenError(M.Case):
        brief: str
        detail: str
        parserFunction: str
        parserLine: int
        tokenKind: OrgTokenKind
        tokenText: str

    class ParseError(M.Case):
        brief: str
        detail: str
        parserFunction: str
        parserLine: int
        errName: str
        errCode: str

    __variant__(ParseTokenError, ParseError)


def test_example_model_main(stable_test_dir: Path):
    M.type_check()

    res = M.finalize()

    idx = ModelIndex(res)

    assert len(idx.enum_by_id("OrgDiagnostics::Kind").enum_values) == 2

    Path("/tmp/test_example_model_main.json").write_text(res.model_dump_json(indent=2))
