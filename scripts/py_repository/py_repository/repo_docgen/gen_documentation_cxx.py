from dataclasses import replace
from enum import Enum
from pathlib import Path

from beartype import beartype
from beartype.typing import Dict
from beartype.typing import Iterable
from beartype.typing import List
from beartype.typing import Optional
from beartype.typing import Tuple
from beartype.typing import Type
from beartype.typing import TypeVar
from beartype.typing import Union
import dominate.util as util
from py_codegen.gen_tu_cpp import QualType
from py_codegen.gen_tu_cpp import QualTypeKind
from py_codegen.gen_tu_cpp import ReferenceKind
from py_codegen.refl_read import strip_comment_prefixes
import py_haxorg.pyhaxorg_wrap as org
import py_repository.code_analysis.gen_coverage_cxx as cov
import py_repository.repo_docgen.gen_documentation_utils as docutils
from py_scriptutils.script_logging import log
from pydantic import BaseModel
from pydantic import Field
from pydantic import SerializeAsAny
from sqlalchemy.orm import Session

CAT = "docgen"

T = TypeVar("T")
