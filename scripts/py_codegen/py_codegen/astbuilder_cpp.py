from copy import copy
from dataclasses import dataclass, field, replace
from beartype.typing import List, Union, NewType, Optional, Tuple, Dict, Any, Iterable
from enum import Enum
from beartype import beartype
import inspect
import os
import py_codegen.astbuilder_base as base
from typing import TYPE_CHECKING
from pydantic import BaseModel, Field
import itertools

from py_textlayout.py_textlayout_wrap import BlockId, TextLayout

DEBUG_TYPE_ORIGIN = False

class QualTypeKind(str, Enum):
    RegularType = "RegularTyp0e"
    FunctionPtr = "FunctionPtr"
    MethodPtr = "MethodPtr"
    Array = "Array"
    TypeExpr = "TypeExpr"

    def __rich_repr__(self):
        yield self.name

class ReferenceKind(str, Enum):
    NotRef = "NotRef"
    LValue = "LValue"
    RValue = "RValue"

    def __rich_repr__(self):
        yield self.name


@beartype
class QualType(BaseModel, extra="forbid"):
    name: str = ""
    Parameters: List['QualType'] = Field(default_factory=list)
    Spaces: List['QualType'] = Field(default_factory=list)
    isNamespace: bool = False

    isConst: bool = False
    ptrCount: int = 0
    RefKind: ReferenceKind = ReferenceKind.NotRef
    dbg_origin: str = Field(default="", exclude=True)
    verticalParamList: bool = Field(default=False, exclude=True)
    isBuiltin: bool = Field(default=False)
    #: Prefix the type with leading `::` to refer to the global namespace
    isGlobalNamespace: bool = Field(default=False)
    IsPackExpansion: bool = Field(default=False)

    expr: Optional[str] = None
    Kind: QualTypeKind = QualTypeKind.RegularType

    meta: Dict[str, Any] = Field(default={})

    def par0(self) -> Optional["QualType"]:
        if 0 < len(self.Parameters):
            return self.Parameters[0]

    def par1(self) -> Optional["QualType"]:
        if 1 < len(self.Parameters):
            return self.Parameters[1]

    def test(self, met: bool) -> bool:
        return self.meta.get(met, False)

    def isOrgType(self) -> bool:
        return self.meta.get("isOrgType", False)

    @staticmethod
    def ForName(name: str, **args) -> 'QualType':
        return QualType(name=name, **args)

    @staticmethod
    def ForExpr(expr: str, **args) -> 'QualType':
        return QualType(expr=expr, Kind=QualTypeKind.TypeExpr, **args)

    def flatten(self) -> "QualType":
        return self.model_copy(update=dict(Spaces=self.flatQualSpaces()))

    def withDbgOrigin(self, msg: str) -> "QualType":
        return self.model_copy(update=dict(dbg_origin=self.dbg_origin + msg))

    def asConstRef(self) -> 'QualType':
        return self.model_copy(update=dict(isConst=True, RefKind=ReferenceKind.LValue))

    def asRef(self) -> 'QualType':
        return self.model_copy(update=dict(isConst=False, RefKind=ReferenceKind.LValue))

    def flatQualSpaces(self) -> List["QualType"]:
        def aux(it: QualType) -> List[QualType]:
            return list(itertools.chain(*(aux(s) for s in it.Spaces))) + [it.withoutAllSpaces()]

        return list(itertools.chain(*(aux(s) for s in self.Spaces)))

    def asPtr(self, ptrCount: int = 1) -> 'QualType':
        return self.model_copy(update=dict(ptrCount=ptrCount))

    def withGlobalSpace(self) -> 'QualType':
        return self.model_copy(update=dict(isGlobalNamespace=True))

    def flatSpaces(self) -> List[str]:
        return [S.name for S in self.Spaces]

    def flatQualName(self) -> List[str]:
        return self.flatSpaces() + [self.name]

    def asSpaceFor(self, other: 'QualType') -> 'QualType':
        return other.model_copy(update=dict(
            Spaces=self.Spaces +
            [self.model_copy(update=dict(
                Spaces=[],
                isGlobalNamespace=False,
            ))],
            isGlobalNamespace=self.isGlobalNamespace,
        ))

    def withWrapperType(self, name: str) -> "QualType":
        return QualType(name=name, Parameters=[self])

    def withExtraSpace(self, name: Union['QualType', str]) -> 'QualType':
        flat = self.flatten()
        added: QualType = QualType(name=name) if isinstance(name, str) else name
        assert isinstance(added, QualType), type(added)
        return flat.model_copy(update=dict(Spaces=[added] + flat.Spaces))

    def withoutSpace(self, name: str) -> 'QualType':
        flat = self.flatten()
        return flat.model_copy(update=dict(
            Spaces=[S for S in flat.Spaces if S.name != name]))

    def withoutAllSpaces(self) -> 'QualType':
        return self.model_copy(update=dict(Spaces=[]))

    def withChangedSpace(self, name: Union['QualType', str]) -> 'QualType':
        """Change the namespace of the qualified type from the current list to the [name]
        Resulting type will have only [name] as the space"""
        added: QualType = QualType(name=name) if isinstance(name, str) else name
        assert isinstance(added, QualType), type(added)
        return self.flatten().model_copy(update=dict(Spaces=[added]))

    def isArray(self) -> bool:
        return self.Kind == QualTypeKind.Array

    def isFunction(self) -> bool:
        return self.Kind == QualTypeKind.FunctionPtr

    def isPrimitive(self) -> bool:
        return self.isBuiltin or self.name in [
            "size_t",
            "uint32_t",
            "uint16_t",
            "int32_t",
            "int64_t",
            "uint64_t",
        ]

    @beartype
    class Function(BaseModel, extra="forbid"):
        ReturnTy: Optional['QualType']
        Args: List['QualType']
        Ident: str = ""
        Class: Optional['QualType'] = None
        IsConst: bool = False

    func: Optional[Function] = None

    def __hash__(self) -> int:
        return hash(
            (self.name, self.isConst, self.ptrCount, self.RefKind, self.isNamespace,
             tuple([hash(T) for T in self.Spaces]),
             tuple([hash(T) for T in self.Parameters])))

    def __repr__(self) -> str:
        return self.format()

    def __str__(self) -> str:
        return self.format()

    def format(self, dbgOrigin: bool = False) -> str:
        cvref = "{const}{ptr}{ref}".format(
            const=" const" if self.isConst else "",
            ptr=("*" * self.ptrCount),
            ref={
                ReferenceKind.LValue: "&",
                ReferenceKind.RValue: "&&",
                ReferenceKind.NotRef: ""
            }[self.RefKind],
        )

        origin = f"FROM:[{self.dbg_origin}]" if dbgOrigin else ""

        spaces = "".join([S.format(dbgOrigin) + "::" for S in self.Spaces])
        if spaces:
            spaces = f"[{spaces}]<<"

        match self.Kind:
            case QualTypeKind.FunctionPtr:
                return spaces + "F:[{}({})]".format(
                    self.func.ReturnTy.format(),
                    ", ".join([T.format(dbgOrigin) for T in self.func.Args]),
                )

            case QualTypeKind.Array:
                return spaces + "A:[{first}[{expr}]{cvref}{origin}]".format(
                    first=self.Parameters[0].format(dbgOrigin),
                    expr=self.Parameters[1].format(dbgOrigin)
                    if 1 < len(self.Parameters) else "",
                    cvref=cvref,
                    origin=origin,
                )

            case QualTypeKind.RegularType:
                return spaces + "R:[{name}{args}{cvref}{origin}]".format(
                    name=self.name,
                    args=("<" + ", ".join([T.format() for T in self.Parameters]) +
                          ">") if self.Parameters else "",
                    cvref=cvref,
                    origin=origin,
                )

            case QualTypeKind.TypeExpr:
                return f"E:{self.expr}"

            case _:
                assert False, self.Kind

    def asNamespace(self, is_namespace=True):
        self.isNamespace = is_namespace
        return self

    def withVerticalParams(self, params=True):
        self.verticalParamList = params
        return self

    @classmethod
    def from_name(cls, name: str):
        return cls(name=name)

    @classmethod
    def from_name_and_parameters(cls, name: str, parameters: List['QualType']):
        return cls(name=name, Parameters=parameters)

    @classmethod
    def from_spaces_and_name(cls, spaces: List[str], name: str):
        return cls(name=name, Spaces=[cls.from_name(space) for space in spaces])


@beartype
@dataclass
class TemplateTypename:
    Placeholder: bool = False
    Variadic: bool = False
    Name: str = ""
    Nested: List['TemplateTypename'] = field(default_factory=list)
    Concept: Optional[str] = None


@beartype
@dataclass
class TemplateGroup:
    Params: List[TemplateTypename] = field(default_factory=list)


@beartype
@dataclass
class TemplateParams:
    Stacks: List[TemplateGroup] = field(default_factory=list)

    @staticmethod
    def FinalSpecialization():
        return TemplateParams(Stacks=[TemplateGroup()])


class StorageClass(Enum):
    None_ = 0
    Static = 1


@beartype
@dataclass
class DocParams:
    brief: str
    full: str = ""
    IsInline: bool = False


@beartype
@dataclass
class ParmVarParams:
    type: 'QualType'
    name: str
    isConst: bool = False
    storage: StorageClass = StorageClass.None_
    defArg: Optional[BlockId] = None


@beartype
@dataclass
class FunctionParams:
    Name: str
    doc: DocParams = field(default_factory=lambda: DocParams(""))
    Template: TemplateParams = field(default_factory=TemplateParams)
    ResultTy: Optional[QualType] = field(default_factory=lambda: QualType.ForName("void"))
    Args: List[ParmVarParams] = field(default_factory=list)
    Storage: StorageClass = StorageClass.None_
    Body: Optional[List[BlockId]] = None
    Inline: bool = False
    InitList: List[Tuple[str, BlockId]] = field(default_factory=list)
    AllowOneLine: bool = True


@beartype
@dataclass
class LambdaCapture:
    Name: Optional[str] = None
    ByRef: bool = True


@beartype
@dataclass
class LambdaParams:
    Args: List[ParmVarParams] = field(default_factory=list)
    ResultTy: Optional[QualType] = field(default_factory=lambda: QualType.ForName("auto"))
    Template: TemplateParams = field(default_factory=TemplateParams)
    Body: List[BlockId] = field(default_factory=list)
    CaptureList: List[LambdaCapture] = field(default_factory=list)
    IsLine: bool = True


class AccessSpecifier(Enum):
    Unspecified = 0
    Public = 1
    Private = 2
    Protected = 3


@beartype
@dataclass
class MethodDefParams:
    Params: FunctionParams
    Class: QualType
    IsConst: bool = False


@beartype
@dataclass
class MethodDeclParams:
    Params: FunctionParams
    isConst: bool = False
    isStatic: bool = False
    isVirtual: bool = False
    isPureVirtual: bool = False
    isOverride: bool = False
    access: AccessSpecifier = AccessSpecifier.Unspecified

    def asMethodDef(self, Class: QualType) -> MethodDefParams:
        return MethodDefParams(
            IsConst=self.isConst,
            Class=Class,
            Params=copy(self.Params),
        )


@beartype
@dataclass
class EnumParams:

    @dataclass
    class Field:
        doc: DocParams
        name: str
        value: Optional[str] = None

    name: str
    doc: DocParams
    base: Optional[str] = None
    isEnumClass: bool = True
    fields: List[Field] = field(default_factory=list)
    IsLine: bool = False


@beartype
@dataclass
class IfStmtParams:

    @dataclass
    class Branch:
        Then: BlockId
        Cond: Optional[BlockId] = None
        Var: Optional[BlockId] = None
        Init: Optional[BlockId] = None
        OneLine: bool = False

    Branches: List[Branch]
    LookupIfStructure: bool = False


class PPKind(Enum):
    IfDef = 0
    IfNotDef = 1
    If = 2


@beartype
@dataclass
class PPIfBranch:
    Then: BlockId
    Kind: PPKind = PPKind.If
    Cond: Optional[BlockId] = None


@beartype
@dataclass
class PPIfStmtParams:
    Branches: List[PPIfBranch]


@beartype
@dataclass
class CompoundStmtParams:
    Stmts: List[BlockId]


@beartype
@dataclass
class MacroParams:

    @dataclass
    class Param:
        name: str
        isEllipsis: bool = False

    name: str
    params: List[Param] = field(default_factory=list)
    doc: Optional[DocParams] = None
    definition: List[str] = field(default_factory=list)


@beartype
@dataclass
class RecordField:
    params: ParmVarParams
    doc: DocParams
    isStatic: bool = False
    access: AccessSpecifier = AccessSpecifier.Unspecified


RecordMember = Union[MethodDeclParams, MethodDefParams, RecordField]
RecordNested = Union[EnumParams, 'RecordParams', BlockId]


@beartype
@dataclass
class RecordParams:
    name: QualType
    doc: DocParams = field(default_factory=lambda: DocParams(""))
    NameParams: List[QualType] = field(default_factory=list)
    bases: List[QualType] = field(default_factory=list)
    members: List[RecordMember] = field(default_factory=list)
    nested: List[RecordNested] = field(default_factory=list)
    Template: TemplateParams = field(default_factory=TemplateParams)
    IsDefinition: bool = True
    TrailingLine: bool = True
    OneLine: bool = False

    def methods(self) -> Iterable[Union[MethodDeclParams, MethodDefParams]]:
        return (m for m in self.members
                if isinstance(m, MethodDeclParams) or isinstance(m, MethodDefParams))


@beartype
@dataclass
class UsingParams:
    newName: str
    baseType: QualType
    Template: TemplateParams = field(default_factory=TemplateParams)


@beartype
@dataclass
class MacroParam:
    name: str
    is_ellipsis: bool


@beartype
@dataclass
class IfStmtBranch:
    Then: BlockId
    Cond: Optional[BlockId] = None
    Var: Optional[BlockId] = None
    Init: Optional[BlockId] = None
    OneLine: bool = False


@beartype
@dataclass
class CaseStmtParams:
    Expr: Optional[BlockId] = None
    Body: List[BlockId] = field(default_factory=list)
    Compound: bool = True
    Autobreak: bool = True
    OneLine: bool = False
    IsDefault: bool = False


@beartype
@dataclass
class SwitchStmtParams:
    Expr: BlockId
    Cases: List[CaseStmtParams] = field(default_factory=list)
    Default: Optional[CaseStmtParams] = None


@beartype
@dataclass
class ASTBuilder(base.AstbuilderBase):

    def __init__(self, in_b: TextLayout):
        self.b = in_b

    def __repr__(self):
        return "cpp.ASTBuilder()"

    def CaseStmt(self, params: CaseStmtParams) -> BlockId:
        head = self.string("default:") if params.IsDefault else self.b.line(
            [self.string("case "), params.Expr or self.string(""),
             self.string(":")])
        Body: List[BlockId] = params.Body + ([self.XStmt('break')]
                                             if params.Autobreak else [])

        if params.Compound:
            return self.block(head, Body)
        else:
            if params.OneLine:
                return self.b.line(
                    [head, self.string(" "),
                     self.b.join(Body, self.string(" "))])
            else:
                return self.b.stack([head, self.b.indent(2, self.b.stack(Body))])

    def SwitchStmt(self, params: SwitchStmtParams) -> BlockId:
        cases = []
        for Case in params.Cases:
            cases.append(self.CaseStmt(Case))

        if params.Default:
            cases.append(self.CaseStmt(params.Default))

        return self.block(self.b.line([self.string("switch "),
                                       self.pars(params.Expr)]), cases)

    def Call(
        self,
        func: BlockId,
        Args: List[BlockId] = [],
        Params: Optional[List[QualType]] = None,
        Stmt: bool = False,
        Line: bool = True,
        LineParameters: bool = True,
    ):
        result = self.b.line([func])
        if Params is not None:
            self.b.add_at(result, self.string("<"))
            self.b.add_at(
                result, self.csv(
                    [self.Type(t) for t in Params],
                    isLine=LineParameters,
                ))
            self.b.add_at(result, self.string(">"))

        self.b.add_at(result, self.string("("))
        self.b.add_at(result, self.csv(Args, Line))
        self.b.add_at(result, self.string(");" if Stmt else ")"))

        return result

    def CallStatic(self,
                   typ: QualType,
                   opc: str,
                   Args: List[BlockId] = [],
                   Stmt: bool = False,
                   Line: bool = True,
                   Params: Optional[List[QualType]] = None) -> BlockId:
        return self.Call(self.b.line(
            [self.Type(typ), self.string("::"),
             self.string(opc)]),
                         Args=Args,
                         Stmt=Stmt,
                         Line=Line,
                         Params=Params)

    def XCallObj(self,
                 obj: BlockId,
                 opc: str,
                 func: str,
                 args: List[BlockId] = [],
                 Stmt: bool = False,
                 Line: bool = True,
                 Params: Optional[List[QualType]] = None) -> BlockId:

        return self.Call(self.b.line([
            obj,
            self.string(opc),
            self.string(func),
        ]),
                         Args=args,
                         Stmt=Stmt,
                         Line=Line,
                         Params=Params)

    def XCallRef(self,
                 obj: BlockId,
                 opc: str,
                 args: List[BlockId] = [],
                 Stmt: bool = False,
                 Line: bool = True,
                 Params: Optional[List[QualType]] = None) -> BlockId:
        return self.XCallObj(obj,
                             ".",
                             func=opc,
                             args=args,
                             Stmt=Stmt,
                             Line=Line,
                             Params=Params)

    def XCallPtr(self,
                 obj: BlockId,
                 opc: str,
                 args: List[BlockId] = [],
                 Stmt: bool = False,
                 Line: bool = True,
                 Params: Optional[List[QualType]] = None) -> BlockId:
        return self.XCallObj(obj,
                             "->",
                             func=opc,
                             args=args,
                             Stmt=Stmt,
                             Line=Line,
                             Params=Params)

    def XCall(
        self,
        opc: str,
        args: List[BlockId],
        Stmt: bool = False,
        Line: bool = True,
        Params: Optional[List[QualType]] = None,
        LineParameters: bool = True,
    ) -> BlockId:
        if opc[0].isalpha() or opc[0] == ".":
            return self.Call(
                self.string(opc),
                Args=args,
                Stmt=Stmt,
                Line=Line,
                Params=Params,
                LineParameters=LineParameters,
            )

        elif Params:
            return self.Call(
                self.string("operator" + opc),
                Args=args,
                Stmt=Stmt,
                Line=Line,
                Params=Params,
                LineParameters=LineParameters,
            )

        else:
            if len(args) == 1:
                return self.b.line([self.string(opc), args[0]])

            elif len(args) == 2:
                return self.b.line([
                    args[0],
                    self.string(" "),
                    self.string(opc),
                    self.string(" "), args[1]
                ])
            else:
                raise Exception(
                    "Unexpected number of arguments for operator-like function call. Expected 1 or 2 but got different amount"
                )

    def XStmt(self, opc: str, arg: Optional[BlockId] = None) -> BlockId:
        if arg:
            return self.b.line([
                self.string(opc),
                self.string(" "),
                arg,
                self.string(";"),
            ])
        else:
            return self.b.line([self.string(opc), self.string(";")])

    def Trail(self, first: BlockId, second: BlockId, space: str = " ") -> BlockId:
        return self.b.line([first, self.string(space), second])

    def Comment(self,
                text: List[str] | str,
                Inline: bool = True,
                Doc: bool = False) -> BlockId:
        if isinstance(text, str):
            text = [text]

        if Inline:
            content = self.b.stack([])
            for line in text:
                self.b.add_at(content, self.string(line))

            return self.b.line(
                [self.string("/*! " if Doc else "/* "), content,
                 self.string(" */")])
        else:
            result = self.b.stack([])
            for line in text:
                self.b.add_at(result, self.string(f"/// {line}" if Doc else f"// {line}"))
            return result

    def StringLiteral(
        self,
        value: str,
        forceRawStr: bool = False,
        rawStrDelmiter: str = "RAW",
        prefix: str = "",
        suffix: str = "",
    ) -> BlockId:
        if forceRawStr:
            return self.string(f"R\"{rawStrDelmiter}({value}){rawStrDelmiter}\"")

        else:
            # TODO Implement heuristics to detect whether the string wrap is necessary here.
            # this would allow to just throw `Literal()` calls all over the place
            return self.string(f"\"{value}\"")

    def Literal(self, value: Union[int, str]) -> BlockId:
        if isinstance(value, int) or isinstance(value, float):
            return self.string(str(value))

        elif isinstance(value, bool):
            return self.string("true" if value else "false")

        elif isinstance(value, str):
            return self.StringLiteral(value)

    def GenHere(self,
                body: Optional[BlockId] = None,
                enabled: bool = True,
                frames: Union[int, Tuple[int, int]] = 1) -> BlockId:
        """
        Return inline comment with runtime call stack informat in format 'file:line'.

        `/* test_codegen.py:200 */` -- this would allow to quickly add debugging information
        with detauls where each element was generated. 
        
        Parameters:
        - frames: int or tuple. Number of frames to unwind, or a tuple specifying the range.
        - body: Block id that will be wrapped in a stack [comment, body] if present
        - enabled: do nothing if false, allows for simpler dry-run operations. If body is
          present, will return it, otherwise empty block node. 
        """

        if enabled:
            stack = inspect.stack()

            comment: BlockId

            filter_stack = list(
                reversed([
                    f"{os.path.basename(frame_info.filename)}:{frame_info.lineno}"
                    for frame_info in stack[1:]
                    if not frame_info.filename.startswith("<@")
                ]))

            slice = None
            if isinstance(frames, tuple):
                slice = (len(filter_stack) - frames[1] - 1, len(filter_stack) - frames[0])
            else:
                slice = (len(filter_stack) - frames, len(filter_stack))

            comment = self.string("/* " + " ".join(filter_stack[slice[0]:slice[1]]) +
                                  " */")

            if body:
                return self.b.stack([comment, body])

            else:
                return comment

        else:
            if body:
                return body
            else:
                return self.b.empty()

    def Addr(self, expr: BlockId) -> BlockId:
        return self.b.line([self.string("&"), expr])

    def Scoped(self, scope: QualType, expr: BlockId):
        return self.b.line([self.Type(scope, noQualifiers=True), self.string("::"), expr])

    def Throw(self, expr: BlockId) -> BlockId:
        return self.XStmt("throw", expr)

    def Return(self, expr: BlockId) -> BlockId:
        return self.XStmt("return", expr)

    def Continue(self, expr: BlockId) -> BlockId:
        return self.XStmt("continue", expr)

    def TranslationUnit(self, stmts: List[BlockId]) -> BlockId:
        return self.b.stack(stmts)

    def Include(self, file: str, isSystem: bool = False) -> BlockId:
        include_str = f"<{file}>" if isSystem else f"\"{file}\""
        return self.b.line([self.string(f"#include {include_str}")])

    def Define(self, name: str, value: Optional[str] = None) -> BlockId:
        return self.string(f"#define {name}" if value is
                           None else f"#define {name}={value}")

    def PPIfDef(self, expr: str, Then: List[BlockId] = []) -> PPIfBranch:
        return PPIfBranch(Kind=PPKind.IfDef,
                          Cond=self.string(expr),
                          Then=self.b.stack(Then))

    def PPIfNDef(self, expr: str, Then: List[BlockId] = []) -> PPIfBranch:
        return PPIfBranch(Kind=PPKind.IfNotDef,
                          Cond=self.string(expr),
                          Then=self.b.stack(Then))

    def PPIfStmt(self, p: PPIfStmtParams) -> BlockId:
        result = self.b.stack([])
        for idx, branch in enumerate(p.Branches):
            token = "#"
            match (branch.Kind, bool(idx == 0), bool(branch.Cond)):
                case (_, _, False):
                    token += "else"
                case (PPKind.If, True, True):
                    token += "if"
                case (PPKind.IfDef, True, True):
                    token += "ifdef"
                case (PPKind.IfNotDef, True, True):
                    token += "ifndef"
                case (PPKind.If, False, True):
                    token += "elif"
                case (PPKind.IfDef, False, True):
                    token += "elifdef"
                case (PPKind.IfNotDef, False, True):
                    token += "elifndef"

            self.b.add_at(
                result,
                self.b.stack([
                    self.b.line([
                        self.string(token),
                        *([self.string(" "), branch.Cond] if branch.Cond else [])
                    ]),
                    self.b.indent(2, branch.Then)
                ]))

        self.b.add_at(result, self.string("#endif"))

        return result

    def IfStmt(self, p: IfStmtParams) -> BlockId:
        result = self.b.stack([])

        for i in range(len(p.Branches)):
            first = i == 0
            last = i == len(p.Branches) - 1
            Branch = p.Branches[i]

            head = self.b.line([
                self.string("if " if first else (
                    "} else if " if Branch.Cond else "} else "))
            ]) if not p.LookupIfStructure else self.b.line(
                [self.string("if " if Branch.Cond else "")])

            if Branch.Cond:
                self.b.add_at(head, self.string("("))
                self.b.add_at(head, Branch.Cond)
                self.b.add_at(head, self.string(") "))

            self.b.add_at(head, self.string("{"))

            if p.LookupIfStructure:
                self.b.add_at(head, self.string(" "))
                self.b.add_at(head, Branch.Then)
                self.b.add_at(head, self.string(" }"))
                if not last:
                    self.b.add_at(head, self.string(" else "))
                self.b.add_at(result, head)
            else:
                if Branch.OneLine:
                    self.b.add_at(head, self.string(" "))
                    self.b.add_at(head, Branch.Then)
                    self.b.add_at(result, head)
                else:
                    self.b.add_at(result, head)
                    self.b.add_at(result, self.b.indent(2, Branch.Then))

        if not p.LookupIfStructure:
            self.b.add_at(result, self.string("}"))

        return result

    def CompoundStmt(self, p: CompoundStmtParams) -> BlockId:
        return self.brace(p.Stmts)

    def VarDecl(self, p: ParmVarParams) -> BlockId:
        return self.b.line([
            self.Type(p.type),
            self.string(" "),
            self.string("const " if p.isConst else ""),
            self.string(p.name), *([self.string(" = "), p.defArg] if p.defArg else []),
            self.string(";")
        ])

    def block(
        self,
        head: BlockId,
        content: List[BlockId],
        trailingLine: bool = False,
        allowOneLine: bool = True,
    ) -> BlockId:
        if allowOneLine and len(content) < 2:
            result = self.b.line(
                [head, self.string(" { "),
                 self.b.stack(content),
                 self.string(" }")])

        else:
            result = self.b.stack([
                self.b.line([head, self.string(" {")]),
                self.b.indent(2, self.b.stack(content)),
                self.string("}")
            ])

        if trailingLine:
            if self.b.isStack(result):
                self.b.add_at(result, self.string(""))
            else:
                result = self.b.stack([result, self.string("")])

        return result

    def Macro(self, params: MacroParams) -> BlockId:
        definition = self.b.stack([])
        for line in params.definition:
            self.b.add_at(definition, self.string(line + "  \\"))

        arguments = [
            self.string(line.name if not line.isEllipsis else "...")
            for line in params.params
        ]

        return self.WithDoc(
            self.b.stack([
                self.b.line([
                    self.string("#define "),
                    self.string(params.name),
                    self.string("("),
                    self.b.join(arguments, self.string(", ")),
                    self.string(") \\")
                ]),
                self.b.indent(8, definition),
                self.string("")
            ]), params.doc)

    def Using(self, params: UsingParams) -> BlockId:
        return self.WithTemplate(
            params.Template,
            self.b.line([
                self.string("using "),
                self.string(params.newName),
                self.string(" = "),
                self.Type(params.baseType),
                self.string(";")
            ]))

    def Field(self, field: RecordField) -> BlockId:
        return self.WithAccess(
            self.WithDoc(
                self.b.line([
                    self.string("static " if field.isStatic else ""),
                    self.VarDecl(field.params)
                ]), field.doc), field.access)

    def MethodDef(self, m: MethodDefParams) -> BlockId:
        return self.WithTemplate(
            m.Params.Template,
            self.b.stack([
                self.b.line([
                    *([] if m.Params.ResultTy is None else
                      [self.Type(m.Params.ResultTy),
                       self.string(" ")]),
                    self.Type(m.Class),
                    self.string("::"),
                    self.string(m.Params.Name),
                    self.Arguments(m.Params),
                    self.string(" const {" if m.IsConst else " {")
                ]),
                self.b.indent(2, self.b.stack(m.Params.Body)),
                self.string("}")
            ]))

    def MethodDecl(self, method: MethodDeclParams) -> BlockId:
        head = self.b.line([
            self.string("static " if method.isStatic else ""),
            self.string("virtual " if method.isVirtual else ""),
            *([] if method.Params.ResultTy is None else [
                self.Type(method.Params.ResultTy),
                self.string(" "),
            ]),
            self.string(method.Params.Name),
            self.Arguments(method.Params),
            self.string(" const" if method.isConst else ""),
            self.string(" override" if method.isOverride else ""),
            self.string(" = 0" if method.isPureVirtual else "")
        ])

        return self.WithAccess(
            self.WithDoc(
                self.b.line([head, self.string(";")])
                if method.Params.Body is None else self.block(
                    head,
                    method.Params.Body,
                    allowOneLine=method.Params.AllowOneLine,
                ), method.Params.doc),
            method.access,
        )

    def Record(self, params: RecordParams) -> BlockId:
        content: List[BlockId] = []

        for nested in params.nested:
            if isinstance(nested, EnumParams):
                content.append(self.Enum(nested))
            elif isinstance(nested, RecordParams):
                content.append(self.Record(nested))
            else:
                content.append(nested)

        for member in params.members:
            if isinstance(member, RecordField):
                content.append(self.Field(member))

            elif isinstance(member, MethodDeclParams):
                content.append(self.MethodDecl(member))

            elif isinstance(member, MethodDefParams):
                content.append(self.MethodDef(member))

        bases: Optional[BlockId] = None
        if params.bases:
            classes = [
                self.b.line([self.string("public "),
                             self.Type(base)]) for base in params.bases
            ]
            bases = self.b.line(
                [self.string(" : "),
                 self.b.join(classes, self.string(", "))])

        head = self.b.line([
            self.string("struct "),
            self.Type(params.name),
            self.b.surround_non_empty(
                self.b.join([self.Type(t) for t in params.NameParams], self.string(", ")),
                self.string("<"), self.string(">")), bases or self.string(""),
            self.string(" {" if params.IsDefinition else "")
        ])

        def cond(args: List[BlockId]) -> BlockId:
            if params.OneLine:
                return self.b.join(args, self.b.text(" "))

            else:
                return self.b.stack(args)

        return self.WithTemplate(
            params.Template,
            cond([
                self.Doc(params.doc),
                head,
                self.b.indent(0 if params.OneLine else 2, cond(content)),
                self.string("};" if params.IsDefinition else ";"),
                *([self.string("")] if params.TrailingLine else []),
            ]) if content else cond([
                self.Doc(params.doc),
                self.b.line([
                    head,
                    self.string("};" if params.IsDefinition else ";"),
                ]), *([self.string("")] if params.TrailingLine else [])
            ]))

    def WithAccess(self, content: BlockId, spec: AccessSpecifier) -> BlockId:
        if spec == AccessSpecifier.Unspecified:
            return content
        else:
            return self.b.stack([
                self.string("public:" if spec == AccessSpecifier.Public else (
                    "protected:" if spec == AccessSpecifier.Protected else "private:")),
                self.b.indent(2, content)
            ])

    def Enum(self, params: EnumParams) -> BlockId:
        assert len(params.name) > 0, "EnumDecl: non-empty enum name required"

        fields = self.b.line([]) if params.IsLine else self.b.stack([])
        for _field in params.fields:
            content: List[BlockId] = []
            content.append(self.Doc(replace(_field.doc, IsInline=params.IsLine)))
            content.append(self.string(_field.name + (", " if params.IsLine else ",")))
            stack = self.b.stack(content)

            self.b.add_at(fields, stack)

        head = self.b.line([
            self.string("enum "),
            self.string("class " if params.isEnumClass else ""),
            self.string(params.name + " "),
            self.string(": " + params.base + " " if params.base else ""),
            self.string("{")
        ])

        if params.IsLine:
            return self.b.stack([
                self.Doc(params.doc),
                self.b.line([head, self.string(" "), fields,
                             self.string("};")])
            ])
        else:
            return self.b.stack([
                self.Doc(params.doc),
                head,
                self.b.indent(2, fields),
                self.string("};"),
            ])

    def Capture(self, p: LambdaCapture) -> BlockId:
        result = self.b.line([])
        if p.Name:
            self.b.add_at(result, self.string(p.Name))

        return result

    def Lambda(self, p: LambdaParams) -> BlockId:
        head = self.b.line([
            self.string("["),
            self.csv([self.Capture(cap) for cap in p.CaptureList]),
            self.string("]"),
            self.Arguments(p)
        ])

        if p.ResultTy:
            self.b.add_at(head, self.string(" -> "))
            self.b.add_at(head, self.Type(p.ResultTy))

        self.b.add_at(head, self.b.text(" { "))

        if p.IsLine:
            self.b.add_at(head, self.b.stack(p.Body))
            self.b.add_at(head, self.b.text(" }"))

        else:
            head = self.b.stack([head, self.b.stack(p.Body), self.b.text("}")])

        return head

    def Function(self, p: FunctionParams) -> BlockId:
        head = self.b.line([
            *([] if p.ResultTy is None else [self.Type(p.ResultTy),
                                             self.string(" ")]),
            self.string(p.Name),
            self.Arguments(p)
        ])

        if p.InitList:
            self.b.add_at(head, self.string(" : "))
            self.b.add_at(
                head,
                self.csv([
                    self.b.line([
                        self.string(item[0]),
                        self.string("("), item[1],
                        self.string(")")
                    ]) for item in p.InitList
                ]))

        return self.WithTemplate(
            p.Template,
            self.block(head, p.Body, True, allowOneLine=p.AllowOneLine)
            if p.Body else self.b.line([head, self.string(";")]))

    def Arguments(self, p: Union[FunctionParams, LambdaParams]) -> BlockId:
        return self.b.line([
            self.string("("),
            self.b.join([self.ParmVar(Arg) for Arg in p.Args], self.string(", "), True),
            self.string(")")
        ])

    def Type(self, type_: QualType, noQualifiers: bool = False) -> BlockId:
        if noQualifiers:
            qualifiers = ""

        else:
            qualifiers = ""
            if type_.isConst:
                qualifiers += " const"

            qualifiers += "*" * type_.ptrCount
            match type_.RefKind:
                case ReferenceKind.LValue:
                    qualifiers += "&"

                case ReferenceKind.RValue:
                    qualifiers += "&&"

        def get_dbg_str() -> str:
            if DEBUG_TYPE_ORIGIN and type_.dbg_origin:
                return f" /* {type_.dbg_origin} */"

            else:
                return ""

        def get_dbg() -> BlockId:
            return self.string(get_dbg_str())

        match type_.Kind:
            case QualTypeKind.FunctionPtr:
                pointer_type = [self.Type(type_.func.Class),
                                self.string("::")] if type_.func.Class else []

                return self.b.line([
                    self.Type(type_.func.ReturnTy),
                    self.pars(self.b.line(pointer_type + [self.string("*")])),
                    self.pars(self.csv([self.Type(T) for T in type_.func.Args])),
                    self.string(" const" if type_.func.IsConst else ""),
                    get_dbg(),
                ])

            case QualTypeKind.TypeExpr:
                return self.string(type_.expr + get_dbg_str())

            case QualTypeKind.Array:
                return self.b.line([
                    self.Type(type_.Parameters[0]),
                    self.string("["),
                    self.Type(type_.Parameters[1]),
                    self.string("]"),
                    self.string(qualifiers),
                    get_dbg(),
                ])

            case QualTypeKind.RegularType:
                type_scopes: List[BlockId] = []
                if type_.isGlobalNamespace:
                    # Double colon is added by join later on
                    type_scopes.append(self.string(""))

                for Space in type_.Spaces:
                    type_scopes.append(self.Type(Space, noQualifiers=noQualifiers))

                type_scopes.append(self.string(type_.name))

                if len(type_.Parameters) == 0:
                    template_parameters = self.string("")

                else:
                    template_parameters = self.b.line([
                        self.string("<"),
                        self.b.join(
                            [
                                self.Type(in_, noQualifiers=noQualifiers)
                                for in_ in type_.Parameters
                            ],
                            self.string(", "),
                            not type_.verticalParamList,
                        ),
                        self.string(">")
                    ])

                return self.b.line([
                    self.b.join(type_scopes, self.string("::")),
                    template_parameters,
                    self.string(qualifiers),
                    get_dbg(),
                ])

    def Dot(self, lhs: BlockId, rhs: BlockId) -> BlockId:
        return self.b.line([lhs, self.string("."), rhs])

    def Doc(self, doc: DocParams) -> BlockId:
        content: List[str] = []
        isFirst = True
        for line in doc.brief.split("\n"):
            if len(line) == 0:
                continue
            elif isFirst:
                content.append("\\brief " + line)
                isFirst = False
            else:
                content.append(line)

        if content:
            content.append("")

        for line in doc.full.split("\n"):
            content.append(line)

        while content and not content[-1]:
            content.pop()

        result = self.b.stack([])
        for line in content:
            t: BlockId = self.string(("" if doc.IsInline else "/// ") + line)
            self.b.add_at(result, t)

        if doc.IsInline and 0 < len(content):
            result = self.b.line([self.string("//!"), result, self.string("*/")])

        return result

    def ParmVar(self, p: ParmVarParams) -> BlockId:
        return self.b.line([
            self.Type(p.type),
            self.string(" "),
            self.string(p.name), *([self.string(" = "), p.defArg] if p.defArg else [])
        ])

    def Template(
            self, Param: Union[TemplateTypename, TemplateGroup,
                               TemplateParams]) -> BlockId:
        if isinstance(Param, TemplateTypename):
            concept_str = Param.Concept if Param.Concept else (
                "typename" if not Param.Nested else "template")
            placeholder_str = "" if Param.Placeholder else " "
            name_str = "" if Param.Placeholder else Param.Name

            nested_content = self.b.join([self.Template(Sub) for Sub in Param.Nested],
                                         self.string(", "))
            return self.b.line([
                self.string(concept_str),
                self.string(placeholder_str),
                self.string(name_str),
                self.b.surround_non_empty(nested_content, self.string("<"),
                                          self.string(">"))
            ])

        elif isinstance(Param, TemplateGroup):
            return self.b.line([
                self.string("template <"),
                self.b.join([self.Template(Param) for Param in Param.Params],
                            self.string(", ")),
                self.string(">")
            ])

        else:
            assert (isinstance(Param, TemplateParams))
            return self.b.stack([self.Template(Spec) for Spec in Param.Stacks])

    def WithTemplate(self, Templ: TemplateParams, Body: BlockId) -> BlockId:
        if not Templ.Stacks:
            return Body
        else:
            return self.b.stack([self.Template(Templ), Body])

    def WithDoc(self, content: BlockId, doc: Optional[DocParams]) -> BlockId:
        if not doc or not doc.brief and not doc.full:
            return content

        else:
            return self.b.stack([self.Doc(doc), content])

    def Any(self, it: Any) -> BlockId:
        match it:
            case RecordParams():
                return self.Record(it)

            case MethodDefParams():
                return self.MethodDef(it)

            case MethodDeclParams():
                return self.MethodDecl(it)

            case _:
                assert False, type(it)
