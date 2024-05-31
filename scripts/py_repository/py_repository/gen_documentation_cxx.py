from beartype import beartype
import py_repository.gen_documentation_utils as docutils
from py_codegen.gen_tu_cpp import QualType, ReferenceKind, QualTypeKind
from beartype.typing import Union, Tuple, Optional, List, Iterable
from pathlib import Path
import dominate.tags as tags
import dominate.util as util
import py_repository.gen_documentation_data as docdata
from pydantic import BaseModel
from enum import Enum
from dataclasses import replace
from pydantic import Field, SerializeAsAny
from beartype.typing import Type, TypeVar, Dict
from py_codegen.refl_read import strip_comment_prefixes
from pygments import lex
from pygments.lexers import CppLexer
import py_haxorg.pyhaxorg_wrap as org
from sqlalchemy.orm import Session
import py_repository.gen_coverage_cxx as cov
from py_scriptutils.script_logging import log

CAT = "docgen"

T = TypeVar("T")




class DocCodeRunCall(BaseModel, extra="forbid"):
    Count: int
    CalledBy: str


class DocCodeCxxCoverage(BaseModel, extra="forbid"):
    Call: List[DocCodeRunCall] = Field(default_factory=list)


class DocCodeCxxLine(docdata.DocCodeLine, extra="forbid"):
    Text: str
    Coverage: Optional[DocCodeCxxCoverage] = None


class DocCodeCxxFile(docdata.DocCodeFile, extra="forbid"):
    Lines: List[DocCodeCxxLine] = Field(default_factory=list)
    Coverage: Optional[cov.CoverageSegmentTree] = Field(default=None)

    # FIXME temporary workaround until I implement coverage segment tree serde.
    class Config:
        orm_mode = True
        arbitrary_types_allowed = True
        json_encoders = {cov.CoverageSegmentTree: lambda v: "Not serializable"}


class DocCxxConcept(docdata.DocBase, extra="forbid"):
    Name: QualType



DocCodeCxxFile.model_rebuild()



@beartype
def convert_cxx_tree(
    RootPath: Path,
    AbsPath: Path,
    coverage_session: Optional[Session],
) -> DocCodeCxxFile:
    outfile = DocCodeCxxFile(
        RelPath=AbsPath.relative_to(RootPath),
        Lines=[
            DocCodeCxxLine(Text=line, Index=idx)
            for idx, line in enumerate(AbsPath.read_text().splitlines())
        ],
    )

    if coverage_session:
        query = cov.get_coverage_of(coverage_session, AbsPath)
        if query is not None:
            log(CAT).info(f"Has coverage for {AbsPath}")
            outfile.Coverage = cov.CoverageSegmentTree(
                it[0]
                for it in coverage_session.execute(query.where(
                    cov.CovSegment.IsLeaf == True)))
            

    return outfile


@beartype
def get_html_code_div(code_file: DocCodeCxxFile) -> tags.div:
    highlight_lexer = CppLexer()

    def get_line_spans(line: DocCodeCxxLine) -> List[tags.span]:
        return list(
            docdata.get_code_line_span(
                line=line,
                highilght_lexer=highlight_lexer,
            ))

    return docdata.get_html_code_div_base(
        Lines=code_file.Lines,
        get_line_spans=get_line_spans,
    )
