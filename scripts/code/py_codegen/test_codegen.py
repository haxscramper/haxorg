#!/usr/bin/env python

import os
import sys
from dataclasses import field, dataclass
from typing import *
from enum import Enum


# Get the absolute path of the directory containing the Python script
script_dir = os.path.dirname(os.path.abspath(__file__))

# Construct the absolute path to the 'lib' directory
lib_dir = os.path.abspath(os.path.join(script_dir, '..', '..', '..', 'lib'))

# Add this directory to sys.path
sys.path.append(lib_dir)

print(lib_dir)
import ctypes
ctypes.CDLL(lib_dir + '/py_textlayout.so')

# Now you should be able to import your C++ library
from py_textlayout import TextLayout, TextOptions

BlockId = NewType("BlockId", int)

b = TextLayout()


@dataclass
class QualType:
    name: str = ""
    isConst: bool = False
    isPtr: bool = False
    isRef: bool = False
    isNamespace: bool = False
    Spaces: List['QualType'] = field(default_factory=list)
    Parameters: List['QualType'] = field(default_factory=list)
    verticalParamList: bool = False

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

    def Ref(self, set_ref=True):
        self.isRef = set_ref
        return self

    def Ptr(self, set_ptr=True):
        self.isPtr = set_ptr
        return self

    def Const(self, set_const=True):
        self.isConst = set_const
        return self


@dataclass
class TemplateTypename:
    Placeholder: bool = False
    Variadic: bool = False
    Name: str = ""
    Nested: List['TemplateTypename'] = field(default_factory=list)
    Concept: Optional[str] = None

@dataclass
class TemplateGroup:
    Params: List[TemplateTypename] = field(default_factory=list)

@dataclass
class TemplateParams:
    Stacks: List[TemplateGroup] = field(default_factory=list)

    @staticmethod
    def FinalSpecialization():
        return TemplateParams(Stacks=[TemplateGroup()])

class StorageClass(Enum):
    None_ = 0
    Static = 1


@dataclass
class DocParams:
    brief: str
    full: str

@dataclass
class ParmVarParams:
    type: 'QualType'
    name: str
    isConst: bool = False
    storage: StorageClass = StorageClass.None_
    defArg: Optional[str] = None

@dataclass
class FunctionParams:
    Name: str
    doc: DocParams
    Template: TemplateParams
    BlockIdultTy: 'QualType'
    Args: List[ParmVarParams] = field(default_factory=list)
    Storage: StorageClass = StorageClass.None_
    Body: Optional[List[BlockId]] = None
    Inline: bool = False

@dataclass
class MethodParams:
    Params: FunctionParams
    Class: 'QualType'
    IsConst: bool

class AccessSpecifier(Enum):
    Unspecified = 0
    Public = 1
    Private = 2
    Protected = 3

@dataclass
class EnumParams:
    @dataclass
    class Field:
        doc: DocParams 
        name: str
        value: Optional[str]
    
    name: str
    doc: DocParams 
    base: Optional[str] = None
    isEnumClass: bool = True
    fields: List[Field] = field(default_factory=list)

@dataclass
class MethodParams:
    Params: FunctionParams
    Class: QualType
    IsConst: bool

@dataclass
class IfStmtParams:
    @dataclass
    class Branch:
        Cond: Optional[BlockId]
        Then: BlockId
        Var: Optional[BlockId]
        Init: Optional[BlockId]
        OneLine: bool = False
    
    Branches: List[Branch]
    LookupIfStructure: bool = False

@dataclass
class CompoundStmtParams:
    Stmts: List[BlockId]

@dataclass
class MacroParams:
    @dataclass
    class Param:
        name: str
        isEllipsis: bool

    doc: DocParams
    params: List[Param]
    name: str
    definition: List[str]

@dataclass
class UsingParams:
    Template: TemplateParams
    newName: str
    baseType: QualType

@dataclass
class RecordMethod:
    params: FunctionParams
    isStatic: bool = False
    isConst: bool = False
    isVirtual: bool = False
    isPureVirtual: bool = False
    access: AccessSpecifier = AccessSpecifier.Unspecified

@dataclass
class RecordField:
    params: ParmVarParams
    doc: DocParams
    isStatic: bool = False
    access: AccessSpecifier = AccessSpecifier.Unspecified

@dataclass
class RecordMember:
    data: Union[RecordMethod, RecordField]

@dataclass
class RecordParams:      
    name: str
    NameParams: List[QualType]
    doc: DocParams
    bases: List[QualType]
    members: List[RecordMember]
    nested: List[Union[EnumParams, 'RecordParams', BlockId]]
    Template: TemplateParams
    IsDefinition: bool = True

@dataclass
class UsingParams:
    Template: TemplateParams
    new_name: str
    base_type: QualType

@dataclass
class MacroParam:
    name: str
    is_ellipsis: bool

@dataclass
class MacroParams:
    doc: DocParams
    params: List[MacroParam]
    name: str
    definition: List[str]

@dataclass
class CompoundStmtParams:
    Stmts: List[BlockId]

@dataclass
class IfStmtBranch:
    Then: BlockId
    Cond: Optional[BlockId] = None
    Var: Optional[BlockId] = None
    Init: Optional[BlockId] = None
    OneLine: bool = False

@dataclass
class IfStmtParams:
    Branches: List[IfStmtBranch]
    LookupIfStructure: bool = False

@dataclass
class CaseStmtParams:
    Expr: BlockId
    Body: List[BlockId]
    Compound: bool = True
    Autobreak: bool = True
    OneLine: bool = False
    IsDefault: bool = False

@dataclass
class SwitchStmtParams:
    Expr: BlockId
    Cases: List[CaseStmtParams]
    Default: Optional[CaseStmtParams] = None

@dataclass
class ASTBuilder:
    b: TextLayout = field(default_factory=TextLayout())

    def CaseStmt(self, params: CaseStmtParams) -> BlockId:
        # Implementation here
        pass

    def SwitchStmt(self, params: SwitchStmtParams) -> BlockId:
        # Implementation here
        pass

    def XCall(self, opc: str, args: List[BlockId], Stmt: bool = False, Line: bool = True) -> BlockId:
        # Implementation here
        pass

    def XStmt(self, opc: str, arg: Optional[BlockId] = None) -> BlockId:
        if arg:
            return self.b.line([str(opc), " ", arg, ";"])
        else:
            return self.b.line([str(opc), ";"])

    def Trail(self, first: BlockId, second: BlockId, space: str = " ") -> BlockId:
        return self.b.line([first, str(space), second])

    def Comment(self, text: List[str], Inline: bool = True, Doc: bool = False) -> BlockId:
        # Implementation here
        pass

    def Literal(self, value: Union[int, str]) -> BlockId:
        if isinstance(value, int):
            return str(value)
        elif isinstance(value, str):
            return f"\"{value}\""

    def Throw(self, expr: BlockId) -> BlockId:
        return self.XStmt("throw", expr)

    def Return(self, expr: BlockId) -> BlockId:
        return self.XStmt("return", expr)

    def Continue(self, expr: BlockId) -> BlockId:
        return self.XStmt("continue", expr)

    def TranslationUnit(self, stmts: List[BlockId]) -> BlockId:
        return self.b.stack(stmts)

    def Include(self, file: str, isSystem: bool) -> BlockId:
        include_str = f"<{file}>" if isSystem else f"\"{file}\""
        return self.b.line([f"#include {include_str}"])


    def IfStmt(self, p: IfStmtParams) -> BlockId:
        # Implementation here
        pass

    def brace(self, elements: List[BlockId]) -> BlockId:
        return self.b.stack(["{", self.b.stack(elements), "}"])

    def pars(self, arg: BlockId) -> BlockId:
        return self.b.line(["(", arg, ")"])

    def block(self, head: BlockId, content: List[BlockId], trailingLine=False) -> BlockId:
        # Implementation here
        pass

    def csv(self, items: List[str], isLine=True, isTrailing=False) -> BlockId:
        return self.b.join(items, ", ", isLine, isTrailing)

    def CompoundStmt(self, p: CompoundStmtParams) -> BlockId:
        return self.brace(p.Stmts)

    def VarDecl(self, p: ParmVarParams) -> BlockId:
        # Implementation here
        pass

    def Macro(self, params: MacroParams) -> BlockId:
        # Implementation here
        pass

    def Using(self, params: UsingParams) -> BlockId:
        # Implementation here
        pass

    def Field(self, field: RecordField) -> BlockId:
        # Implementation here
        pass

    def Method(self, method: RecordMethod) -> BlockId:
        # Implementation here
        pass

    def Record(self, params: RecordParams) -> BlockId:
        # Implementation here
        pass

    def WithAccess(self, content: BlockId, spec: AccessSpecifier) -> BlockId:
        # Implementation here
        pass

    def Enum(self, params: EnumParams) -> BlockId:
        # Implementation here
        pass

    def Function(self, p: FunctionParams) -> BlockId:
        head = self.b.line([
            self.Type(p.ResultTy),
            " ",
            p.Name,
            self.Arguments(p)
        ])

        return self.WithTemplate(
            p.Template,
            self.block(head, p.Body, True) if p.Body else self.b.line([head, ";"])
        )


    def Arguments(self, p: FunctionParams) -> BlockId:
        return self.b.line([
            "(",
            self.b.join(
                list(map(
                    lambda Arg: self.ParmVar(Arg),
                    p.Args
                )),
                ", ",
                True
            ),
            ")"
        ])


    def Method(self, m: MethodParams) -> BlockId:
        return self.WithTemplate(
            m.Params.Template,
            self.b.stack([
                self.b.line([
                    self.Type(m.Params.ResultTy),
                    " ",
                    self.Type(m.Class),
                    "::",
                    m.Params.Name,
                    self.Arguments(m.Params),
                    " const {" if m.IsConst else " {"
                ]),
                self.b.indent(2, self.b.stack(m.Params.Body)),
                "}"
            ])
        )


    def Type(self, type_: str) -> QualType:
        return QualType(type_)


    def Type(self, type_: QualType) -> BlockId:
        return self.b.line([
            self.b.join(
                list(map(
                    lambda Space: self.Type(Space),
                    type_.Spaces
                )) + [type_.name],
                "::"
            ),
            "" if type_.Parameters.empty() else self.b.line([
                "<",
                self.b.join(
                    list(map(
                        lambda in_: self.Type(in_),
                        type_.Parameters
                    )),
                    ", ",
                    not type_.verticalParamList
                ),
                ">"
            ]),
            (
                (" const" if type_.isConst else "") +
                ("*" if type_.isPtr else "") +
                ("&" if type_.isRef else "")
            )
        ])


    def Doc(self, doc: DocParams) -> BlockId:
        content = []
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

        result = self.b.stack()
        for line in content:
            self.b.add_at(result, "/// " + line)
        return result

    def ParmVar(self, p: ParmVarParams) -> BlockId:
        return self.b.line([
            self.Type(p.type),
            " ",
            p.name,
            " = " + p.defArg if p.defArg else ""
        ])

    def Template(self, Param: TemplateTypename) -> BlockId:
        concept_str = Param.Concept if Param.Concept else ("typename" if not Param.Nested else "template")
        placeholder_str = "" if Param.Placeholder else " "
        name_str = "" if Param.Placeholder else Param.Name

        nested_content = self.b.map_join(
            Param.Nested, 
            lambda Sub: self.Template(Sub),
            ", "
        )
        return self.b.line([
            concept_str,
            placeholder_str,
            name_str,
            self.b.surround_non_empty(nested_content, "<", ">")
        ])

    def Template(self, Spec: TemplateGroup) -> BlockId:
        params_content = self.b.map_join(
            Spec.Params, 
            lambda Param: self.Template(Param),
            ", "
        )
        return self.b.line([
            "template <",
            params_content,
            ">"
        ])

    def Template(self, Templ: TemplateParams) -> BlockId:
        return self.b.map_join(
            Templ.Stacks,
            lambda Spec: self.Template(Spec),
            self.b.empty(),
            isLine=False
        )

    def WithTemplate(self, Templ: TemplateParams, Body: BlockId) -> BlockId:
        if not Templ.Stacks:
            return Body
        else:
            return self.b.stack([self.Template(Templ), Body])

    def WithDoc(self, content: BlockId, doc: DocParams) -> BlockId:
        if not doc.brief and not doc.full:
            return content
        else:
            return self.b.stack([self.Doc(doc), content])


print(b.toString(b.text("Test"), TextOptions()))

import faulthandler
faulthandler.enable()

print("Done")
