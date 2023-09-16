import setup_imports
from py_textlayout import *
from dataclasses import dataclass, field
from beartype.typing import *
from enum import Enum
from beartype import beartype

if not TYPE_CHECKING:
    BlockId = NewType('BlockId', int)

import logging

log = logging.getLogger(__name__)
log.setLevel(logging.DEBUG)
handler = logging.StreamHandler()
formatter = logging.Formatter('%(name)s - %(levelname)s [%(filename)s:%(lineno)d in %(funcName)s] - >%(message)s<')
handler.setFormatter(formatter)
log.addHandler(handler)


@beartype
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


@beartype
@dataclass
class ParmVarParams:
    type: 'QualType'
    name: str
    isConst: bool = False
    storage: StorageClass = StorageClass.None_
    defArg: Optional[str] = None


@beartype
@dataclass
class FunctionParams:
    Name: str
    doc: DocParams
    Template: TemplateParams = field(default_factory=TemplateParams)
    ResultTy: QualType = field(default_factory=QualType("void"))
    Args: List[ParmVarParams] = field(default_factory=list)
    Storage: StorageClass = StorageClass.None_
    Body: Optional[List[BlockId]] = None
    Inline: bool = False


class AccessSpecifier(Enum):
    Unspecified = 0
    Public = 1
    Private = 2
    Protected = 3


@beartype
@dataclass
class MethodDeclParams:
    Params: FunctionParams
    isConst: bool = False
    isStatic: bool = False
    isVirtual: bool = False
    isPureVirtual: bool = False
    access: AccessSpecifier = AccessSpecifier.Unspecified


@beartype
@dataclass
class MethodDefParams:
    Params: FunctionParams
    Class: QualType
    IsConst: bool = False


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

    doc: DocParams
    name: str
    params: List[Param] = field(default_factory=list)
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
    name: str
    doc: DocParams
    NameParams: List[QualType] = field(default_factory=list)
    bases: List[QualType] = field(default_factory=list)
    members: List[RecordMember] = field(default_factory=list)
    nested: List[RecordNested] = field(default_factory=list)
    Template: TemplateParams = field(default_factory=TemplateParams)
    IsDefinition: bool = True


@beartype
@dataclass
class UsingParams:
    Template: TemplateParams
    newName: str
    baseType: QualType


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
class ASTBuilder:
    b: TextLayout

    def string(self, text: str) -> BlockId:
        return self.b.text(text)

    def CaseStmt(self, params: CaseStmtParams) -> BlockId:
        head = self.string("default:") if params.IsDefault else self.b.line(
            [self.string("case "), params.Expr or self.string(""), self.string(":")])
        Body: List[BlockId] = params.Body + ([self.XStmt('break')] if params.Autobreak else [])

        if params.Compound:
            return self.block(head, Body)
        else:
            if params.OneLine:
                return self.b.line([head, self.string(" "), self.b.join(params.Body, self.string(" "))])
            else:
                return self.b.stack([head, self.b.indent(2, self.b.stack(Body))])

    def SwitchStmt(self, params: SwitchStmtParams) -> BlockId:
        cases = []
        for Case in params.Cases:
            cases.append(self.CaseStmt(Case))

        if params.Default:
            cases.append(self.CaseStmt(params.Default))

        return self.block(self.b.line([self.string("switch "), self.pars(params.Expr)]), cases)

    def XCall(self, opc: str, args: List[BlockId], Stmt: bool = False, Line: bool = True) -> BlockId:
        if opc[0].isalpha():
            return self.b.line([self.string(opc), self.string("("), self.csv(args, Line), self.string(");" if Stmt else ")")])
        else:
            if len(args) == 1:
                return self.b.line([self.string(opc), args[0]])

            elif len(args) == 2:
                return self.b.line([args[0], self.string(" "), self.string(opc), self.string(" "), args[1]])
            else:
                raise Exception("Unexpected number of arguments for operator-like function call. Expected 1 or 2 but got different amount")

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

    def Comment(self, text: List[str], Inline: bool = True, Doc: bool = False) -> BlockId:
        if Inline:
            content = self.b.stack([])
            for line in text:
                self.b.add_at(content, self.string(line))

            return self.b.line([self.string("/*! " if Doc else "/* "), content, self.string(" */")])
        else:
            result = self.b.stack([])
            for line in text:
                self.b.add_at(result, self.string(f"/// {line}" if Doc else f"// {line}"))
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

            head = self.b.line([self.string("if " if first else ("} else if " if Branch.Cond else "} else "))
                               ]) if not p.LookupIfStructure else self.b.line([self.string("if" if Branch.Cond else "")])

            if Branch.Cond:
                self.b.add_at(head, self.string(" ("))
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

    def brace(self, elements: List[BlockId]) -> BlockId:
        return self.b.stack([self.string("{"), self.b.stack(elements), self.string("}")])

    def pars(self, arg: BlockId) -> BlockId:
        return self.b.line([self.string("("), arg, self.string(")")])

    def csv(self, items: Union[List[str], List[BlockId]], isLine=True, isTrailing=False) -> BlockId:
        return self.b.join([self.string(Base) if isinstance(Base, str) else Base for Base in items], self.string(", "), isLine, isTrailing)

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

    def block(self, head: BlockId, content: List[BlockId], trailingLine=False) -> BlockId:
        if len(content) < 2:
            result = self.b.line([head, self.string(" { "), self.b.stack(content), self.string(" }")])

        else:
            result = self.b.stack([self.b.line([head, self.string(" {")]), self.b.indent(2, self.b.stack(content)), self.string("}")])

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

        arguments = [self.string(line.name if not line.isEllipsis else "...") for line in params.params]

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
            self.b.line(
                [self.string("using "),
                 self.string(params.newName),
                 self.string(" = "),
                 self.Type(params.baseType),
                 self.string(";")]))

    def Field(self, field: RecordField) -> BlockId:
        return self.WithAccess(
            self.WithDoc(self.b.line([self.string("static " if field.isStatic else ""),
                                      self.VarDecl(field.params)]), field.doc), field.access)

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
            self.string(" const" if method.isConst else ""),
            self.string(" = 0" if method.isPureVirtual else "")
        ])

        return self.WithAccess(
            self.WithDoc(
                self.block(head, method.Params.Body, True) if method.Params.Body is not None else self.b.line([head, self.string(";")]),
                method.Params.doc), method.access)

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
            classes = [self.b.line([self.string("public "), self.Type(base)]) for base in params.bases]
            bases = self.b.line([self.string(" : "), self.b.join(classes, self.string(", "))])

        head = self.b.line([
            self.string("struct "),
            self.string(params.name),
            self.b.surround_non_empty(self.b.join([self.Type(t) for t in params.NameParams], self.string(", ")), self.string("<"),
                                      self.string(">")), bases or self.string(""),
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
            ]) if content else self.b.stack(
                [self.Doc(params.doc),
                 self.b.line([
                     head,
                     self.string("};" if params.IsDefinition else ";"),
                 ]), self.string("")]))

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

        fields = self.b.stack([])
        for field in params.fields:
            content: List[BlockId] = []
            content.append(self.Doc(field.doc))
            content.append(self.string(field.name + ","))
            stack = self.b.stack(content)

            self.b.add_at(fields, stack)

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
        head = self.b.line([self.Type(p.ResultTy), self.string(" "), self.string(p.Name), self.Arguments(p)])

        return self.WithTemplate(p.Template, self.block(head, p.Body, True) if p.Body else self.b.line([head, self.string(";")]))

    def Arguments(self, p: FunctionParams) -> BlockId:
        return self.b.line(
            [self.string("("),
             self.b.join([self.ParmVar(Arg) for Arg in p.Args], self.string(", "), True),
             self.string(")")])

    def Type(self, type_: QualType) -> BlockId:
        return self.b.line([
            self.b.join([self.Type(Space) for Space in type_.Spaces] + [self.string(type_.name)], self.string("::")),
            self.string("") if (len(type_.Parameters) == 0) else self.b.line([
                self.string("<"),
                self.b.join(list(map(lambda in_: self.Type(in_), type_.Parameters)), self.string(", "), not type_.verticalParamList),
                self.string(">")
            ]),
            self.string((" const" if type_.isConst else "") + ("*" if type_.isPtr else "") + ("&" if type_.isRef else ""))
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
        return self.b.line([self.Type(p.type), self.string(" "), self.string(p.name), self.string(" = " + p.defArg if p.defArg else "")])

    def Template(self, Param: Union[TemplateTypename, TemplateGroup, TemplateParams]) -> BlockId:
        if isinstance(Param, TemplateTypename):
            concept_str = Param.Concept if Param.Concept else ("typename" if not Param.Nested else "template")
            placeholder_str = "" if Param.Placeholder else " "
            name_str = "" if Param.Placeholder else Param.Name

            nested_content = self.b.join([self.Template(Sub) for Sub in Param.Nested], self.string(", "))
            return self.b.line([
                self.string(concept_str),
                self.string(placeholder_str),
                self.string(name_str),
                self.b.surround_non_empty(nested_content, self.string("<"), self.string(">"))
            ])

        elif isinstance(Param, TemplateGroup):
            return self.b.line([
                self.string("template <"),
                self.b.join([self.Template(Param) for Param in Param.Params], self.string(", ")),
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
