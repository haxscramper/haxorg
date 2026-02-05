from dataclasses import replace
from enum import Enum
from pathlib import Path

from beartype import beartype
from beartype.typing import Dict, Iterable, List, Optional, Tuple, Type, TypeVar, Union
import dominate.util as util
from py_codegen.gen_tu_cpp import QualType, QualTypeKind, ReferenceKind
from py_codegen.refl_read import strip_comment_prefixes
import py_haxorg.pyhaxorg_wrap as org
import py_repository.code_analysis.gen_coverage_cxx as cov
import py_repository.repo_docgen.gen_documentation_utils as docutils
from py_scriptutils.script_logging import log
from pydantic import BaseModel, Field, SerializeAsAny
from sqlalchemy.orm import Session

CAT = "docgen"

T = TypeVar("T")
