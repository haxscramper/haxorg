from os import rename

from py_codegen.astbuilder_base_config import AstbulderConfig
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir
from beartype import beartype
from pydantic import BaseModel, Field
from beartype.typing import List, Optional, Callable
from dataclasses import dataclass, field
from pathlib import Path
import re

from py_haxorg.layout.wrap import BlockId


class WrapRenameRule(BaseModel):
    original: str = Field(description="Regex pattern for input text matching")
    renamed: str = Field(description="Replacement pattern")


class NimAstbuilderStaticConfig(BaseModel):
    function_renames: List[WrapRenameRule] = Field(
        default=[], description="List of renaming rules for generated wrappers")
    universal_import: List[str] = Field(default=[],
                                        description="Import added to all generated files")

    common_function_pragmas: List[str] = Field(
        default=[],
        description="List of pragma annotations added to every function",
    )

    with_header_imports: bool = Field(
        default=True,
        description="Add header pragma annotations to generated entry wraps",
    )

    is_cpp_wrap: bool = Field(
        default=False,
        description="Generating wrappers for C++ or C code",
    )

    importx_structs: bool = Field(
        default=True, description="Generate 'importcpp' or 'import' for structures")


@beartype
@dataclass
class PragmaParams:
    Name: str
    Arguments: List[BlockId] = field(default_factory=list)


@beartype
class NimAstbuilderConfig(AstbulderConfig):
    "Codegen configuration for nim wrappers"
    opts: NimAstbuilderStaticConfig

    def __init__(self,
                 type_map: codegen_ir.GenTypeMap,
                 opts: NimAstbuilderStaticConfig = NimAstbuilderStaticConfig()):
        super().__init__(type_map)
        self.opts = opts

    def getFunctionPragmas(self, func: codegen_ir.GenTuFunction) -> List[PragmaParams]:
        return [PragmaParams(pragma) for pragma in self.opts.common_function_pragmas]

    def getHeaderStrForPath(self, path: Path) -> str:
        return str(path)

    def isAcceptedByBackend(self, entry: codegen_ir.GenTuDeclaration) -> bool:
        return self._isExposedByBackendImpl(entry, "nim")

    def getBackendType(self, t: QualType) -> QualType:
        pass

    def getFunctionIdent(self, name: str) -> str:
        for rule in self.opts.function_renames:
            if re.match(rule.original, name):
                name = re.sub(rule.original, rule.renamed, name)
                break

        return self.getSanitizedIdent(name)

    def getSanitizedIdent(self, name: str) -> str:
        if name in {
                "addr",
                "and",
                "as",
                "asm",
                "bind",
                "block",
                "break",
                "case",
                "cast",
                "concept",
                "const",
                "continue",
                "converter",
                "defer",
                "discard",
                "distinct",
                "div",
                "do",
                "elif",
                "else",
                "end",
                "enum",
                "except",
                "export",
                "finally",
                "for",
                "from",
                "func",
                "if",
                "import",
                "in",
                "include",
                "interface",
                "is",
                "isnot",
                "iterator",
                "let",
                "macro",
                "method",
                "mixin",
                "mod",
                "nil",
                "not",
                "notin",
                "object",
                "of",
                "or",
                "out",
                "proc",
                "ptr",
                "raise",
                "ref",
                "return",
                "shl",
                "shr",
                "static",
                "template",
                "try",
                "tuple",
                "type",
                "using",
                "var",
                "when",
                "while",
                "xor",
                "yield",
        }:
            return f"`{name}`"

        elif not all([c.isalnum() or c == "_" for c in name]):
            return f"`{name}`"

        else:
            return name
