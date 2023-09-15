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
from py_textlayout import TextLayout, TextOptions, BlockId


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
    full: str = ""


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
    Template: TemplateParams = TemplateParams()
    ResultTy: QualType = QualType("void")
    Args: List[ParmVarParams] = field(default_factory=list)
    Storage: StorageClass = StorageClass.None_
    Body: List[BlockId] = field(default_factory=list)
    Inline: bool = False


class AccessSpecifier(Enum):
    Unspecified = 0
    Public = 1
    Private = 2
    Protected = 3


@dataclass
class MethodDeclParams:
    Params: FunctionParams
    Class: QualType
    IsConst: bool = False
    isStatic: bool = False
    isVirtual: bool = False
    isPureVirtual: bool = False
    access: AccessSpecifier = AccessSpecifier.Unspecified


@dataclass
class MethodDefParams:
    Params: FunctionParams
    Class: QualType
    IsConst: bool = False


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
    name: str
    params: List[Param] = field(default_factory=list)
    definition: List[str] = field(default_factory=list)


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


RecordMember = Union[RecordMethod, RecordField]
RecordNested = Union[EnumParams, 'RecordParams', BlockId]


@dataclass
class RecordParams:
    name: str
    doc: DocParams
    NameParams: List[QualType] = field(default_factory=list)
    bases: List[QualType] = field(default_factory=list)
    members: List[RecordMember] = field(default_factory=list)
    nested: List[RecordNested] = field(default_factory=list)
    Template: TemplateParams = TemplateParams
    IsDefinition: bool = True


@dataclass
class UsingParams:
    Template: TemplateParams
    newName: str
    baseType: QualType


@dataclass
class MacroParam:
    name: str
    is_ellipsis: bool


@dataclass
class IfStmtBranch:
    Then: BlockId
    Cond: Optional[BlockId] = None
    Var: Optional[BlockId] = None
    Init: Optional[BlockId] = None
    OneLine: bool = False


@dataclass
class CaseStmtParams:
    Expr: Optional[BlockId] = None
    Body: List[BlockId] = field(default_factory=list)
    Compound: bool = True
    Autobreak: bool = True
    OneLine: bool = False
    IsDefault: bool = False


@dataclass
class SwitchStmtParams:
    Expr: BlockId
    Cases: List[CaseStmtParams] = field(default_factory=list)
    Default: Optional[CaseStmtParams] = None


@dataclass
class ASTBuilder:
    b: TextLayout = field(default_factory=lambda: TextLayout())

    def string(self, text: str) -> BlockId:
        return self.string(text)

    def CaseStmt(self, params: CaseStmtParams) -> BlockId:
        head = self.string("default:") if params.IsDefault else self.b.line([
            self.string("case "), params.Expr or self.string(""),
            self.string(":")
        ])
        Body: List[BlockId] = params.Body + ([self.XStmt('break')]
                                             if params.Autobreak else [])

        if params.Compound:
            return self.block(head, Body)
        else:
            if params.OneLine:
                return self.b.line([
                    head,
                    self.string(" "),
                    self.b.join(params.Body, self.string(" "))
                ])
            else:
                return self.b.stack(
                    [head, self.b.indent(2, self.b.stack(Body))])

    def SwitchStmt(self, params: SwitchStmtParams) -> BlockId:
        cases = []
        for Case in params.Cases:
            cases.append(self.CaseStmt(Case))

        if params.Default:
            cases.append(self.CaseStmt(params.Default))

        return self.block(
            self.b.line([self.string("switch "),
                         self.pars(params.Expr)]), cases)

    def XCall(self,
              opc: str,
              args: List[BlockId],
              Stmt: bool = False,
              Line: bool = True) -> BlockId:
        if opc[0].isalpha():
            return self.b.line([
                self.string(opc),
                self.string("("),
                self.csv(args, Line),
                self.string(");" if Stmt else ")")
            ])
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

    def Trail(self,
              first: BlockId,
              second: BlockId,
              space: str = " ") -> BlockId:
        return self.b.line([first, self.string(space), second])

    def Comment(self,
                text: List[str],
                Inline: bool = True,
                Doc: bool = False) -> BlockId:
        if Inline:
            content = self.b.stack([])
            for line in text:
                self.b.add_at(content, self.string(line))

            return self.b.line([
                self.string("/*! " if Doc else "/* "), content,
                self.string(" */")
            ])
        else:
            result = self.b.stack([])
            for line in text:
                self.b.add_at(
                    result,
                    self.string(f"/// {line}" if Doc else f"// {line}"))
            return result

    def Literal(self, value: Union[int, str]) -> BlockId:
        if isinstance(value, int) or isinstance(value, float):
            return self.string(str(value))

        elif isinstance(value, bool):
            return self.string("true" if value else "false")

        elif isinstance(value, str):
            return self.string(f"\"{value}\"")

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
        return self.b.line([self.string(f"#include {include_str}")])

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
                [self.string("if" if Branch.Cond else "")])

            if Branch.Cond:
                self.b.add_at(head, self.string(" ("))
                self.b.add_at(head, Branch.Cond)
                self.b.add_at(head, self.string(") "))

            self.b.add_at(head, self.string(" {"))

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

    def brace(self, elements: List[BlockId]) -> BlockId:
        return self.b.stack(
            [self.string("{"),
             self.b.stack(elements),
             self.string("}")])

    def pars(self, arg: BlockId) -> BlockId:
        return self.b.line([self.string("("), arg, self.string(")")])

    def csv(self,
            items: Union[List[str], List[BlockId]],
            isLine=True,
            isTrailing=False) -> BlockId:
        return self.b.join([
            self.string(Base) if isinstance(Base, str) else Base
            for Base in items
        ], self.string(", "), isLine, isTrailing)

    def CompoundStmt(self, p: CompoundStmtParams) -> BlockId:
        return self.brace(p.Stmts)

    def VarDecl(self, p: ParmVarParams) -> BlockId:
        return self.b.line([
            self.Type(p.type),
            self.string(" "),
            self.string("const " if p.isConst else ""),
            self.string(p.name),
            self.string(" = " + p.defArg if p.defArg else ""),
            self.string(";")
        ])

    def block(self,
              head: BlockId,
              content: List[BlockId],
              trailingLine=False) -> BlockId:
        if len(content) < 2:
            result = self.b.line([
                head,
                self.string(" { "),
                self.b.stack(content),
                self.string(" }")
            ])

        else:
            result = self.b.stack([
                self.b.line([head, self.string(" {")]),
                self.b.indent(2, self.b.stack(content)),
                self.string("}")
            ])

        if trailingLine:
            if self.b.at(result).isStack():
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

        return self.b.stack([
            self.Doc(params.doc),
            self.b.line([
                self.string("#define "),
                self.string(params.name),
                self.string("("),
                self.b.join(arguments, self.string(", ")),
                self.string(") \\")
            ]),
            self.b.indent(8, definition),
            self.string("")
        ])

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
                    self.Type(m.Params.ResultTy),
                    self.string(" "),
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
            self.Type(method.Params.ResultTy),
            self.string(" "),
            self.string(method.Params.Name),
            self.Arguments(method.Params),
            self.string(" const" if method.IsConst else ""),
            self.string(" = 0" if method.isPureVirtual else "")
        ])

        return self.WithAccess(
            self.WithDoc(
                self.block(head, method.Params.Body, True)
                if method.Params.Body else self.b.line(
                    [head, self.string(";")]), method.Params.doc),
            method.access)

    def Record(self, params: RecordParams) -> BlockId:
        content: List[BlockId] = []

        for m in params.nested:
            if isinstance(m, EnumParams):
                content.append(self.Enum(m))
            elif isinstance(m, RecordParams):
                content.append(self.Record(m))
            else:
                content.append(m)

        for m in params.members:
            if isinstance(m, RecordField):
                content.append(self.Field(m))

            elif isinstance(m, MethodDeclParams):
                content.append(self.MethodDecl(m))

        bases: Optional[BlockId] = None
        if params.bases:
            classes = [
                self.b.line([self.string("public "),
                             self.Type(base)]) for base in params.bases
            ]
            bases = self.b.line(
                [self.string(": "),
                 self.b.join(classes, self.string(", "))])

        head = self.b.line([
            self.string("struct "),
            self.string(params.name),
            self.b.surround_non_empty(
                self.b.join([self.Type(t) for t in params.NameParams],
                            self.string(", ")), "<", ">"), bases,
            self.string(" {" if params.IsDefinition else "")
        ])

        return self.WithTemplate(
            params.Template,
            self.b.stack([
                self.Doc(params.doc),
                head,
                self.b.indent(2, self.b.stack(content)),
                self.string("};" if params.IsDefinition else ";"),
                self.string(""),
            ]) if content else self.b.stack([
                self.Doc(params.doc),
                self.b.line([
                    head,
                    self.string("};" if params.IsDefinition else ";"),
                ]),
                self.string("")
            ]))

    def WithAccess(self, content: BlockId, spec: AccessSpecifier) -> BlockId:
        if spec == AccessSpecifier.Unspecified:
            return content
        else:
            return self.b.stack([
                self.string("public:" if spec == AccessSpecifier.Public else (
                    "protected:" if spec ==
                    AccessSpecifier.Protected else "private:")),
                self.b.indent(2, content)
            ])

    def Enum(self, params: EnumParams) -> BlockId:
        assert len(params.name) > 0, "EnumDecl: non-empty enum name required"

        fields = self.b.stack([])
        for field in params.fields:
            self.b.add_at(
                fields,
                self.b.stack([
                    self.Doc(field.doc),
                    self.string(field.name + ","),  # TODO field value
                ]))

        return self.b.stack([
            self.Doc(params.doc),
            self.b.line([
                self.string("enum "),
                self.string("class " if params.isEnumClass else ""),
                self.string(params.name + " "),
                self.string(": " + params.base + " " if params.base else ""),
                self.string("{")
            ]),
            self.b.indent(2, fields),
            self.string("};"),
            self.string("")
        ])

    def Function(self, p: FunctionParams) -> BlockId:
        head = self.b.line([
            self.Type(p.ResultTy),
            self.string(" "),
            self.string(p.Name),
            self.Arguments(p)
        ])

        return self.WithTemplate(
            p.Template,
            self.block(head, p.Body, True)
            if p.Body else self.b.line([head, self.string(";")]))

    def Arguments(self, p: FunctionParams) -> BlockId:
        return self.b.line([
            self.string("("),
            self.b.join([self.ParmVar(Arg) for Arg in p.Args],
                        self.string(", "), True),
            self.string(")")
        ])

    def Type(self, type_: QualType) -> BlockId:
        return self.b.line([
            self.b.join([self.Type(Space) for Space in type_.Spaces] +
                        [self.string(type_.name)], self.string("::")),
            self.string("") if (len(type_.Parameters) == 0) else self.b.line([
                self.string("<"),
                self.b.join(
                    list(map(lambda in_: self.Type(in_), type_.Parameters)),
                    self.string(", "), not type_.verticalParamList),
                self.string(">")
            ]),
            self.string((" const" if type_.isConst else "") +
                        ("*" if type_.isPtr else "") +
                        ("&" if type_.isRef else ""))
        ])

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
            t: BlockId = self.string("/// " + line)
            self.b.add_at(result, t)

        return result

    def ParmVar(self, p: ParmVarParams) -> BlockId:
        return self.b.line([
            self.Type(p.type),
            self.string(" "),
            self.string(p.name),
            self.string(" = " + p.defArg if p.defArg else "")
        ])

    def Template(
        self, Param: Union[TemplateTypename, TemplateGroup,
                           TemplateParams]) -> BlockId:
        if isinstance(Param, TemplateTypename):
            concept_str = Param.Concept if Param.Concept else (
                "typename" if not Param.Nested else "template")
            placeholder_str = "" if Param.Placeholder else " "
            name_str = "" if Param.Placeholder else Param.Name

            nested_content = self.b.join(
                [self.Template(Sub) for Sub in Param.Nested],
                self.string(", "))
            return self.b.line([
                self.string(concept_str),
                self.string(placeholder_str),
                self.string(name_str),
                self.b.surround_non_empty(nested_content, "<", ">")
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

    def WithDoc(self, content: BlockId, doc: DocParams) -> BlockId:
        if not doc.brief and not doc.full:
            return content
        else:
            return self.b.stack([self.Doc(doc), content])


@dataclass
class GenTuTParam:
    name: str


@dataclass
class GenTuIdent:
    name: str
    type: str
    value: Optional[str]


@dataclass
class GenTuDoc:
    brief: str
    full: str = ""


@dataclass
class GenTuEnumField:
    name: str
    value: Optional[str]
    doc: GenTuDoc


@dataclass
class GenTuEnum:
    name: str
    fields: List[GenTuEnumField]
    doc: GenTuDoc
    base: Optional[str]


@dataclass
class GenTuFunction:
    doc: GenTuDoc
    name: str
    result: str
    params: List[GenTuTParam] = field(default_factory=list)
    arguments: List[GenTuIdent] = field(default_factory=list)
    impl: Optional[str] = None
    isVirtual: bool = False
    isConst: bool = False
    isStatic: bool = False
    isPureVirtual: bool = False


@dataclass
class GenTuInclude:
    what: str
    isSystem: bool = False


@dataclass
class GenTuPass:
    what: str


@dataclass
class GenTuField:
    name: str
    type: str
    doc: GenTuDoc
    value: Optional[str] = None
    isConst: bool = False
    isStatic: bool = False


@dataclass
class GenTuStruct:
    name: str
    doc: GenTuDoc
    fields: List[GenTuField] = field(default_factory=list)
    methods: List[GenTuFunction] = field(default_factory=list)
    bases: List[str] = field(default_factory=list)
    nested: List['GenTuEntry'] = field(default_factory=list)
    concreteKind: bool = True


@dataclass
class GenTuTypeGroup:
    types: List[GenTuStruct]
    iteratorMacroName: Optional[str] = None
    enumName: str = "Kind"
    variantField: str = "data"
    variantName: str = "Data"
    variantValue: Optional[str] = None
    kindGetter: str = "getKind"


@dataclass
class GenTuNamespace:
    name: str
    entries: List['GenTuEntry']


GenTuEntry = Union[GenTuEnum, GenTuStruct, GenTuTypeGroup, GenTuFunction,
                   GenTuNamespace, GenTuInclude, GenTuPass]


@dataclass
class GenTu:
    entries: List[GenTuEntry]
    path: str


@dataclass
class GenUnit:
    header: GenTu
    source: Optional[GenTu]


@dataclass
class GenFiles:
    files: List[GenUnit]


@dataclass
class GenConverterWithContext:
    conv: 'GenConverter'
    typ: QualType

    def __exit__(self):
        self.conv.context.pop_back()

    def __enter__(self):
        self.conv.context.append(self.typ)


@dataclass
class GenConverter:
    ast: ASTBuilder
    pendingToplevel: List[BlockId]
    isSource: bool = False
    context: List[QualType] = field(default_factory=list)

    def convertParams(self, Params: List[GenTuTParam]) -> TemplateGroup:
        return TemplateGroup(
            Params=[TemplateTypename(Name=Param.name) for Param in Params])

    def convertFunctionBlock(self, func: FunctionParams) -> BlockId:
        return self.ast.Function(func)

    def convertFunction(self, func: GenTuFunction) -> FunctionParams:
        decl = FunctionParams(ResultTy=QualType(func.result),
                              Name=func.name,
                              doc=self.convertDoc(func.doc))

        if func.params:
            decl.Template.Stacks = [self.convertParams(func.params)]

        if func.impl:
            decl.Body = [self.ast.string(str) for str in func.impl.split("\n")]

        decl.Args = [self.convertIdent(parm) for parm in func.arguments]

        return decl

    def convertDoc(self, doc: GenTuDoc) -> DocParams:
        return DocParams(brief=doc.brief, full=doc.full)

    def convertIdent(self, ident: GenTuIdent) -> ParmVarParams:
        return ParmVarParams(name=ident.name,
                             type=QualType(ident.type),
                             defArg=ident.value)

    def convertStruct(self, record: GenTuStruct) -> BlockId:
        params = RecordParams(name=record.name,
                              doc=self.convertDoc(record.doc),
                              bases=[QualType(base) for base in record.bases])

        with GenConverterWithContext(self, QualType(record.name)):
            for type in record.nested:
                for sub in self.convert(type):
                    params.nested.append(sub)

            for member in record.fields:
                params.members.append(
                    RecordField(params=ParmVarParams(type=QualType(
                        member.type),
                                                     name=member.name,
                                                     isConst=member.isConst,
                                                     defArg=member.value),
                                doc=DocParams(brief=member.doc.brief,
                                              full=member.doc.full),
                                isStatic=member.isStatic))

            for method in record.methods:
                params.members.append(
                    RecordMethod(params=self.convertFunction(method),
                                 isStatic=method.isStatic,
                                 isConst=method.isConst,
                                 isVirtual=method.isVirtual))

            extraFields = []
            extraMethods = []
            for nested in record.nested:
                if isinstance(nested, GenTuTypeGroup):
                    group: GenTuTypeGroup = nested
                    if group.kindGetter:
                        extraMethods.append(
                            GenTuFunction(name=group.kindGetter,
                                          result=group.enumName,
                                          isConst=True))
                    if group.variantName:
                        extraFields.append(
                            GenTuField(name=group.variantField,
                                       doc=GenTuDoc(""),
                                       type=group.variantName))

            fields = [
                self.ast.string(field.name)
                for field in record.fields + extraFields
            ]
            methods = [
                self.ast.b.line([
                    self.ast.string("("),
                    self.ast.string(method.result),
                    self.ast.pars(
                        self.ast.csv([
                            self.ast.string(ident.type)
                            for ident in method.arguments
                        ])),
                    self.ast.string(" const" if method.isConst else ""),
                    self.ast.string(") "),
                    self.ast.string(method.name)
                ]) for method in record.methods + extraMethods
            ]

            params.nested.append(
                self.ast.XCall("BOOST_DESCRIBE_CLASS", [
                    self.ast.string(record.name),
                    self.ast.pars(self.ast.csv(record.bases, False)),
                    self.ast.pars(self.ast.string("")),
                    self.ast.pars(self.ast.string("")),
                    self.ast.pars(
                        self.ast.csv(fields + methods,
                                     len(fields) < 6 and len(methods) < 2))
                ], False,
                               len(fields) < 4 and len(methods) < 1))

        return self.ast.Record(params)

    def convertEnum(self, entry: GenTuEnum) -> BlockId:
        FromParams = FunctionParams(
            Name="from_string",
            doc=DocParams(""),
            ResultTy=QualType("Opt", Parameters=[QualType(entry.name)]),
            Args=[ParmVarParams(type=QualType("QString"), name="value")])

        ToParams = FunctionParams(
            Name="to_string",
            doc=DocParams(),
            ResultTy=QualType("QString"),
            Args=[ParmVarParams(type=QualType(entry.name), name="value")])

        isToplevel = True
        for ctx in self.context:
            if not ctx.isNamespace:
                isToplevel = False
                break

        if self.isSource:
            if isToplevel:
                Class = QualType(name="enum_serde",
                                 Parameters=[QualType(entry.name)])

                SwichFrom = IfStmtParams(LookupIfStructure=True, Branches=[])
                for field in entry.fields:
                    SwichFrom.Branches.append(
                        IfStmtParams.Branch(
                            OneLine=True,
                            Then=self.ast.Return(
                                self.ast.string(
                                    f"{entry.name}::{field.name}")),
                            Cond=self.ast.XCall("==", [
                                self.ast.string("value"),
                                self.ast.Literal(field.name)
                            ]),
                        ))

                SwichFrom.Branches.append(
                    IfStmtParams.Branch(OneLine=True,
                                        Then=self.ast.Return(
                                            self.ast.string("std::nullopt"))))

                SwitchTo = SwitchStmtParams(
                    Expr=self.ast.string("value"),
                    Default=CaseStmtParams(
                        IsDefault=True,
                        Compound=False,
                        Autobreak=False,
                        OneLine=True,
                        Body=[
                            self.ast.Throw(
                                self.ast.XCall(
                                    "std::domain_error",
                                    [
                                        self.ast.Literal(
                                            "Unexpected enum value -- cannot be converted to string"
                                        )
                                    ],
                                ))
                        ],
                    ),
                    Cases=list(
                        map(
                            lambda field: CaseStmtParams(
                                Autobreak=False,
                                Compound=False,
                                OneLine=True,
                                Expr=self.ast.string(
                                    f"{entry.name}::{field.name}"),
                                Body=[
                                    self.ast.Return(
                                        self.ast.Literal(field.name))
                                ],
                            ),
                            entry.fields,
                        )),
                )

                FromDefinition = FromParams
                FromDefinition.Body = [self.ast.IfStmt(SwichFrom)]

                self.pendingToplevel.append(
                    self.ast.MethodDef(
                        MethodDefParams(Class=Class, Params=FromDefinition)))

                ToDefininition = ToParams
                ToDefininition.Body = [self.ast.SwitchStmt(SwitchTo)]

                self.pendingToplevel.append(
                    self.ast.MethodDef(
                        MethodDefParams(Class=Class, Params=ToDefininition)))

            return self.ast.string("")

        else:
            params = EnumParams(name=entry.name,
                                doc=self.convertDoc(entry.doc),
                                base=entry.base)

            for field in entry.fields:
                params.fields.append(
                    EnumParams.Field(doc=DocParams(brief=field.doc.brief,
                                                   full=field.doc.full),
                                     name=field.name,
                                     value=field.value))

            if isToplevel:
                Domain = RecordParams(
                    name="value_domain",
                    doc=DocParams(""),
                    Template=TemplateParams.FinalSpecialization(),
                    NameParams=[QualType(entry.name)],
                    bases=[
                        QualType(name="value_domain_ungapped",
                                 Parameters=[
                                     QualType(name=entry.name),
                                     QualType(Spaces=[QualType(entry.name)],
                                              name=entry.fields[0].name),
                                     QualType(Spaces=[QualType(entry.name)],
                                              name=entry.fields[-1].name),
                                 ]).withVerticalParams()
                    ])

                FromDefinition = FromParams
                ToDefininition = ToParams

                Serde = RecordParams(
                    name="enum_serde",
                    doc=DocParams(""),
                    Template=TemplateParams.FinalSpecialization(),
                    NameParams=[QualType(entry.name)])

                Serde.members.append(
                    RecordMethod(isStatic=True, params=FromDefinition))
                Serde.members.append(
                    RecordMethod(isStatic=True, params=ToDefininition))

                return self.ast.b.stack([
                    self.ast.Enum(params),
                    self.ast.Record(Serde),
                    self.ast.Record(Domain)
                ])
            else:
                arguments = [self.ast.string(entry.name)] + [
                    self.ast.string(Field.name) for Field in entry.fields
                ]

                return self.ast.b.stack([
                    self.ast.Enum(params),
                    self.ast.XCall("BOOST_DESCRIBE_NESTED_ENUM", arguments)
                ])

    def convertNamespace(self, space: GenTuNamespace) -> BlockId:
        result = self.ast.b.stack()
        with GenConverterWithContext(self, QualType(space.name).asNamespace()):
            self.ast.b.add_at(result,
                              self.ast.string(f"namespace {space.name}{{"))

            for sub in space.entries:
                self.ast.b.add_at(result, self.convert(sub))
                self.ast.b.add_at(result, self.pendingToplevel)
                self.pendingToplevel = []

            self.ast.b.add_at(result, self.ast.string("}"))

        return result

    def convertTypeGroup(self, record: GenTuTypeGroup) -> List[BlockId]:
        decls: List[BlockId] = []
        typeNames: List[str] = []

        for item in record.types:
            if item.concreteKind:
                typeNames.append(item.name)

        if len(record.enumName) > 0:
            enumDecl = EnumParams(name=record.enumName, doc=DocParams(""))

            for typeItem in typeNames:
                enumDecl.fields.append(
                    EnumParams.Field(name=typeItem, doc=DocParams("")))

            strName = "_text"
            resName = "_result"

            decls.append(self.ast.Enum(enumDecl))

            switchTo = SwitchStmtParams(Expr=self.ast.string(resName))

            for field in enumDecl.fields:
                switchTo.Cases.append(
                    CaseStmtParams(
                        Expr=self.ast.string(f"{enumDecl.name}::{field.name}"),
                        Body=[self.ast.Return(self.ast.Literal(field.name))],
                        Compound=False,
                        Autobreak=False,
                        OneLine=True))

            fromEnum = FunctionParams(Name="from_enum",
                                      doc=DocParams(""),
                                      ResultTy=QualType("char").Ptr().Const(),
                                      Args=[
                                          ParmVarParams(type=QualType(
                                              record.enumName),
                                                        name=resName)
                                      ],
                                      Body=[self.ast.SwitchStmt(switchTo)])

            decls.append(self.ast.Function(fromEnum))

        if record.iteratorMacroName:
            iteratorMacro = MacroParams(name=record.iteratorMacroName,
                                        params=[MacroParams.Param("__IMPL")])

            for typeItem in typeNames:
                iteratorMacro.definition.append(f"__IMPL({typeItem})")

            decls.append(self.ast.Macro(iteratorMacro))

        for sub in record.types:
            decls += self.convert(sub)

        if record.variantName and record.enumName:
            Arguments: List[BlockId] = [
                self.ast.string(record.enumName),
                self.ast.string(record.variantName),
                self.ast.string(record.variantField),
                self.ast.string(record.kindGetter)
            ]

            for kind in typeNames:
                Arguments.append(self.ast.string(kind))

            if False:
                using_params = UsingParams(
                    newName=record.variantName,
                    baseType=QualType("Variant",
                                      [QualType(Type) for Type in typeNames]))
                decls.append(self.ast.Using(using_params))

            decls.append(self.ast.XCall("SUB_VARIANTS", Arguments, True))
            decls.append(
                self.ast.Field(
                    RecordField(params=ParmVarParams(
                        type=QualType(record.variantName),
                        name=record.variantField,
                        defArg=record.variantValue),
                                doc=DocParams(""))))

        return decls

    def convert(self, entry: GenTuEntry) -> List[BlockId]:
        decls: List[BlockId] = []

        if isinstance(entry, GenTuInclude):
            decls.append(self.ast.Include(entry.what, entry.isSystem))
        elif isinstance(entry, GenTuEnum):
            decls.append(self.convertEnum(entry))
        elif isinstance(entry, GenTuFunction):
            decls.append(self.convertFunctionBlock(
                self.convertFunction(entry)))
        elif isinstance(entry, GenTuStruct):
            decls.append(self.convertStruct(entry))
        elif isinstance(entry, GenTuTypeGroup):
            decls.extend(self.convertTypeGroup(entry))
        elif isinstance(entry, GenTuPass):
            decls.append(self.ast.string(entry.what))
        elif isinstance(entry, GenTuNamespace):
            decls.append(self.convertNamespace(entry))
        else:
            raise ValueError("Unexpected kind")

        return decls


ast = ASTBuilder()
build = ast.Doc(DocParams(brief="Text"))
print("Q")
print(ast.b.toTreeRepr(build))
print("A")
print(ast.b.toString(build, TextOptions()))
print("B")
print("Done")
