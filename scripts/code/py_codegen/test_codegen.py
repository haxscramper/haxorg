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
        return cls(name=name,
                   Spaces=[cls.from_name(space) for space in spaces])

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
        head = "default:" if params.IsDefault else self.b.line(
            ["case ", params.Expr, ":"])
        Body = params.Body + (["XStmt('break')"] if params.Autobreak else [])

        if params.Compound:
            return self.block(head, Body)
        else:
            if params.OneLine:
                return self.b.line([head, " ", self.b.join(params.Body, " ")])
            else:
                return self.b.stack(
                    [head, self.b.indent(2, self.b.stack(Body))])

    def SwitchStmt(self, params: SwitchStmtParams) -> BlockId:
        cases = []
        for Case in params.Cases:
            cases.append(self.CaseStmt(Case))

        if params.Default:
            cases.append(self.CaseStmt(params.Default))

        return self.block(self.b.line(["switch ",
                                       self.pars(params.Expr)]), cases)

    def XCall(self,
              opc: str,
              args: List[BlockId],
              Stmt: bool = False,
              Line: bool = True) -> BlockId:
        if opc[0].isalpha():
            return self.b.line(
                [opc, "(",
                 self.csv(args, Line), ");" if Stmt else ")"])
        else:
            if len(args) == 1:
                return self.b.line([opc, args[0]])
            elif len(args) == 2:
                return self.b.line([args[0], " ", opc, " ", args[1]])
            else:
                raise Exception(
                    "Unexpected number of arguments for operator-like function call. Expected 1 or 2 but got different amount"
                )

    def XStmt(self, opc: str, arg: Optional[BlockId] = None) -> BlockId:
        if arg:
            return self.b.line([str(opc), " ", arg, ";"])
        else:
            return self.b.line([str(opc), ";"])

    def Trail(self,
              first: BlockId,
              second: BlockId,
              space: str = " ") -> BlockId:
        return self.b.line([first, str(space), second])

    def Comment(self,
                text: List[str],
                Inline: bool = True,
                Doc: bool = False) -> BlockId:
        if Inline:
            content = self.b.stack()
            for line in text:
                self.b.add_at(content, line)

            return self.b.line(["/*! " if Doc else "/* ", content, " */"])
        else:
            result = self.b.stack()
            for line in text:
                self.b.add_at(result, (f"/// {line}" if Doc else f"// {line}"))
            return result

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
        result = self.b.stack()

        for i in range(len(p.Branches)):
            first = i == 0
            last = i == len(p.Branches) - 1
            Branch = p.Branches[i]

            head = self.b.line([
                "if " if first else
                ("} else if " if Branch.Cond else "} else ")
            ]) if not p.LookupIfStructure else self.b.line(
                ["if" if Branch.Cond else ""])

            if Branch.Cond:
                self.b.add_at(head, " (")
                self.b.add_at(head, Branch.Cond)
                self.b.add_at(head, ") ")

            self.b.add_at(head, " {")

            if p.LookupIfStructure:
                self.b.add_at(head, " ")
                self.b.add_at(head, Branch.Then)
                self.b.add_at(head, " }")
                if not last:
                    self.b.add_at(head, " else ")
                self.b.add_at(result, head)
            else:
                if Branch.OneLine:
                    self.b.add_at(head, " ")
                    self.b.add_at(head, Branch.Then)
                    self.b.add_at(result, head)
                else:
                    self.b.add_at(result, head)
                    self.b.add_at(result, self.b.indent(2, Branch.Then))

        if not p.LookupIfStructure:
            self.b.add_at(result, "}")

        return result

    def brace(self, elements: List[BlockId]) -> BlockId:
        return self.b.stack(["{", self.b.stack(elements), "}"])

    def pars(self, arg: BlockId) -> BlockId:
        return self.b.line(["(", arg, ")"])

    def csv(self, items: List[str], isLine=True, isTrailing=False) -> BlockId:
        return self.b.join([str(Base) for Base in items], ", ", isLine,
                           isTrailing)

    def CompoundStmt(self, p: CompoundStmtParams) -> BlockId:
        return self.brace(p.Stmts)

    def VarDecl(self, p: ParmVarParams) -> BlockId:
        return self.b.line([
            Type(p.type), " ", "const " if p.isConst else "", p.name,
            " = " + p.defArg if p.defArg else "", ";"
        ])

    def block(self,
              head: BlockId,
              content: List[BlockId],
              trailingLine=False) -> BlockId:
        if len(content) < 2:
            result = self.b.line([head, " { ", self.b.stack(content), " }"])
        else:
            result = self.b.stack([
                self.b.line([head, " {"]),
                self.b.indent(2, self.b.stack(content)), "}"
            ])

        if trailingLine:
            if self.b.at(result).isStack():
                self.b.add_at(result, "")
            else:
                result = self.b.stack([result, ""])

        return result

    def Macro(self, params: MethodParams) -> BlockId:
        definition = self.b.stack()
        for line in params.definition:
            self.b.add_at(definition, line + "  \\")

        arguments = [
            line.name if not line.isEllipsis else "..."
            for line in params.params
        ]

        return self.b.stack([
            self.Doc(params.doc),
            self.b.line([
                "#define ", params.name, "(",
                self.b.join(arguments, ", "), ") \\"
            ]),
            self.b.indent(8, definition), ""
        ])

    def Using(self, params: UsingParams) -> BlockId:
        return self.WithTemplate(
            params.Template,
            self.b.line(
                ["using ", params.newName, " = ",
                 Type(params.baseType), ";"]))

    def Field(self, field: RecordField) -> BlockId:
        return self.WithAccess(
            self.WithDoc(
                self.b.line([
                    "static " if field.isStatic else "",
                    self.VarDecl(field.params)
                ]), field.doc), field.access)

    def Method(self, method: MethodParams) -> BlockId:
        head = self.b.line([
            "static " if method.isStatic else "",
            "virtual " if method.isVirtual else "",
            Type(method.params.ResultTy), " ", method.params.Name,
            self.Arguments(method.params), " const" if method.isConst else "",
            " = 0" if method.isPureVirtual else ""
        ])

        return self.WithAccess(
            self.WithDoc(
                self.block(head, method.params.Body, True)
                if method.params.Body else self.b.line([head, ";"]),
                method.params.doc), method.access)

    def Record(self, params: RecordParams) -> BlockId:
        content = []

        for m in params.nested:
            if isinstance(m, EnumParams):
                content.append(self.Enum(m))
            elif isinstance(m, RecordParams):
                content.append(self.Record(m.value))
            else:
                content.append(m)

        for m in params.members:
            if m.getKind() == RecordParams.Member.Kind.Field:
                content.append(self.Field(m.getField()))
            elif m.getKind() == RecordParams.Member.Kind.Method:
                content.append(self.Method(m.getMethod()))

        bases = ""
        if params.bases:
            classes = [
                self.b.line(["public ", Type(base)]) for base in params.bases
            ]
            bases = self.b.line([": ", self.b.join(classes, ", ")])

        head = self.b.line([
            "struct ", params.name,
            self.b.surround_non_empty(
                self.b.map_join(params.NameParams, lambda t: Type(t), ", "),
                "<", ">"), bases, " {" if params.IsDefinition else ""
        ])

        return self.WithTemplate(
            params.Template,
            self.b.stack([
                self.Doc(params.doc), head,
                self.b.indent(2, self.b.stack(content)),
                "};" if params.IsDefinition else ";", ""
            ]) if content else self.b.stack([
                self.Doc(params.doc),
                self.b.line([head, "};" if params.IsDefinition else ";"]), ""
            ]))

    def WithAccess(self, content: BlockId, spec: AccessSpecifier) -> BlockId:
        if spec == AccessSpecifier.Unspecified:
            return content
        else:
            return self.b.stack([
                "public:" if spec == AccessSpecifier.Public else
                ("protected:"
                 if spec == AccessSpecifier.Protected else "private:"),
                self.b.indent(2, content)
            ])

    def Enum(self, params: EnumParams) -> BlockId:
        assert len(params.name) > 0, "EnumDecl: non-empty enum name required"

        fields = self.b.stack()
        for field in params.fields:
            self.b.add_at(
                fields,
                self.b.stack([
                    self.Doc(field.doc),
                    field.name + ",",  # TODO field value
                ]))

        return self.b.stack([
            self.Doc(params.doc),
            self.b.line([
                "enum ", "class " if params.isEnumClass else "",
                params.name + " ",
                ": " + params.base + " " if params.base else "", "{"
            ]),
            self.b.indent(2, fields), "};", ""
        ])

    def Function(self, p: FunctionParams) -> BlockId:
        head = self.b.line(
            [self.Type(p.ResultTy), " ", p.Name,
             self.Arguments(p)])

        return self.WithTemplate(
            p.Template,
            self.block(head, p.Body, True)
            if p.Body else self.b.line([head, ";"]))

    def Arguments(self, p: FunctionParams) -> BlockId:
        return self.b.line([
            "(",
            self.b.join(list(map(lambda Arg: self.ParmVar(Arg), p.Args)), ", ",
                        True), ")"
        ])

    def Method(self, m: MethodParams) -> BlockId:
        return self.WithTemplate(
            m.Params.Template,
            self.b.stack([
                self.b.line([
                    self.Type(m.Params.ResultTy), " ",
                    self.Type(m.Class), "::", m.Params.Name,
                    self.Arguments(m.Params), " const {" if m.IsConst else " {"
                ]),
                self.b.indent(2, self.b.stack(m.Params.Body)), "}"
            ]))

    def Type(self, type_: str) -> QualType:
        return QualType(type_)

    def Type(self, type_: QualType) -> BlockId:
        return self.b.line([
            self.b.join(
                list(map(lambda Space: self.Type(Space), type_.Spaces)) +
                [type_.name], "::"),
            "" if type_.Parameters.empty() else self.b.line([
                "<",
                self.b.join(
                    list(map(lambda in_: self.Type(in_), type_.Parameters)),
                    ", ", not type_.verticalParamList), ">"
            ]),
            ((" const" if type_.isConst else "") +
             ("*" if type_.isPtr else "") + ("&" if type_.isRef else ""))
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
            self.Type(p.type), " ", p.name,
            " = " + p.defArg if p.defArg else ""
        ])

    def Template(self, Param: TemplateTypename) -> BlockId:
        if isinstance(Param, TemplateTypename):
            concept_str = Param.Concept if Param.Concept else (
                "typename" if not Param.Nested else "template")
            placeholder_str = "" if Param.Placeholder else " "
            name_str = "" if Param.Placeholder else Param.Name

            nested_content = self.b.map_join(Param.Nested,
                                             lambda Sub: self.Template(Sub),
                                             ", ")
            return self.b.line([
                concept_str, placeholder_str, name_str,
                self.b.surround_non_empty(nested_content, "<", ">")
            ])

        elif isinstance(Param, TemplateGroup):
            params_content = self.b.map_join(
                Param.Params, lambda Param: self.Template(Param), ", ")
            return self.b.line(["template <", params_content, ">"])

        else:
            assert (isinstance(Param, TemplateParams))
            return self.b.map_join(Param.Stacks,
                                   lambda Spec: self.Template(Spec),
                                   self.b.empty(),
                                   isLine=False)

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
