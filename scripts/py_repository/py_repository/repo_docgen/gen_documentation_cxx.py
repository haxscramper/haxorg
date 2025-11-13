from beartype import beartype
import py_repository.repo_docgen.gen_documentation_utils as docutils
from py_codegen.gen_tu_cpp import QualType, ReferenceKind, QualTypeKind
from beartype.typing import Union, Tuple, Optional, List, Iterable
from pathlib import Path

import dominate.util as util
from pydantic import BaseModel
from enum import Enum
from dataclasses import replace
from pydantic import Field, SerializeAsAny
from beartype.typing import Type, TypeVar, Dict
from py_codegen.refl_read import strip_comment_prefixes

import py_haxorg.pyhaxorg_wrap as org
from sqlalchemy.orm import Session
import py_repository.coverage_collection.gen_coverage_cxx as cov
from py_scriptutils.script_logging import log

CAT = "docgen"

T = TypeVar("T")



