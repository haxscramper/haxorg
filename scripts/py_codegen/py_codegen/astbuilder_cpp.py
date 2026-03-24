from copy import copy
from dataclasses import dataclass, field, replace
from enum import Enum
import inspect
import os

from beartype import beartype
from beartype.typing import Any, Iterable, List, Optional, Tuple, Union
from py_codegen import codegen_ir
from py_codegen.codegen_ir import GenTuTemplateParams, QualType, StorageClass
import py_haxorg.astbuilder.astbuilder_base as base
from py_haxorg.layout.wrap import BlockId, TextLayout


@beartype
@dataclass
class DocParams:
    brief: str
    full: str = ""
    IsInline: bool = False


@beartype
@dataclass
class ParmVarParams:
    type: "QualType"
    name: str
    IsConst: bool = False
    storage: StorageClass = StorageClass.None_
    defArg: Optional[BlockId] = None
    defWithAssign: bool = True


@beartype
@dataclass
class FunctionParams:
    """
    Common function parameters for CPP.
    """
    Name: str
    doc: DocParams = field(default_factory=lambda: DocParams(""))
    Template: Optional[GenTuTemplateParams] = field(default_factory=GenTuTemplateParams)
    "Template parameters for function"
    ResultTy: QualType = field(default_factory=lambda: QualType.ForName("void"))
    Args: List[ParmVarParams] = field(default_factory=list)
    Storage: StorageClass = StorageClass.None_
    Body: Optional[List[BlockId]] = None
    Inline: bool = False
    InitList: List[BlockId] = field(default_factory=list)
    AllowOneLine: bool = True
    IsConstructor: bool = False
    Linkage: Optional[str] = None
    Annotations: List[codegen_ir.GenTuAnnotation] = field(default_factory=list)


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
    Template: GenTuTemplateParams = field(default_factory=GenTuTemplateParams)
    Body: List[BlockId] = field(default_factory=list)
    CaptureList: List[LambdaCapture] = field(default_factory=list)
    IsLine: bool = True
    IsPtrCast: bool = False


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
    IsLine: bool = False
    "Render method definition on line line"


@beartype
@dataclass
class MethodDeclParams:
    Params: FunctionParams
    IsConst: bool = False
    IsStatic: bool = False
    IsVirtual: bool = False
    IsPureVirtual: bool = False
    IsOverride: bool = False
    access: AccessSpecifier = AccessSpecifier.Unspecified

    def asMethodDef(self, Class: QualType) -> MethodDefParams:
        return MethodDefParams(
            IsConst=self.IsConst,
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
    doc: Optional[DocParams] = None
    isStatic: bool = False
    access: AccessSpecifier = AccessSpecifier.Unspecified


RecordMember = Union[MethodDeclParams, MethodDefParams, RecordField]
RecordNested = Union[EnumParams, "RecordParams", BlockId]


@beartype
@dataclass
class RecordParams:
    name: QualType
    doc: DocParams = field(default_factory=lambda: DocParams(""))
    NameParams: List[QualType] = field(default_factory=list)
    bases: List[QualType] = field(default_factory=list)
    members: List[RecordMember] = field(default_factory=list)
    nested: List[RecordNested] = field(default_factory=list)
    Template: Optional[GenTuTemplateParams] = field(default_factory=GenTuTemplateParams)
    IsDefinition: bool = True
    TrailingLine: bool = True
    IsTemplateSpecialization: bool = False
    OneLine: bool = False

    def methods(self) -> Iterable[Union[MethodDeclParams, MethodDefParams]]:
        return (m for m in self.members
                if isinstance(m, MethodDeclParams) or isinstance(m, MethodDefParams))


@beartype
@dataclass
class UsingParams:
    baseType: QualType
    newName: Optional[str] = None
    Template: GenTuTemplateParams = field(default_factory=GenTuTemplateParams)


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

    def __init__(self, in_b: TextLayout) -> None:
        self.b = in_b

    def __repr__(self) -> str:
        return "cpp.ASTBuilder()"

    def CaseStmt(self, params: CaseStmtParams) -> BlockId:
        head = self.string("default:") if params.IsDefault else self.b.line(
            [self.string("case "), params.Expr or self.string(""),
             self.string(":")])
        Body: List[BlockId] = params.Body + ([self.XStmt("break")]
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
    ) -> BlockId:
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

    def XConstructObj(self,
                      obj: QualType | BlockId,
                      Args: List[BlockId] = [],
                      Line: bool = True) -> BlockId:
        if Line:
            return self.line([
                self.Type(obj) if isinstance(obj, QualType) else obj,
                self.string("{"),
                self.csv(Args),
                self.string("}"),
            ])

        else:
            return self.stack([
                self.line([self.Type(obj), self.string("{")]),
                self.csv(Args, isLine=False, isTrailing=True),
                self.string("}")
            ])

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
        args: List[BlockId] = list(),
        Stmt: bool = False,
        Line: bool = True,
        Params: Optional[List[QualType]] = None,
        LineParameters: bool = True,
    ) -> BlockId:
        if opc[0].isalpha() or opc[0] == "." or opc[0] == "_":
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

    def Scoped(self, scope: QualType, expr: BlockId) -> BlockId:
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
        decl = []

        match p.storage:
            case StorageClass.Static:
                decl.append(self.string("static "))

        if p.type.Kind == codegen_ir.QualTypeKind.FunctionPtr:
            assert p.type.Func
            decl.extend([
                self.Type(p.type.Func.ReturnType),
                self.string(" (*"),
                self.string(p.name),
                self.string(")"),
                self.string("("),
                self.csv([self.Type(a) for a in p.type.Func.Args]),
                self.string(")"),
                self.string("const " if p.IsConst else ""),
            ])

        else:
            decl.extend([
                self.Type(p.type),
                self.string(" "),
                self.string("const " if p.IsConst else ""),
                self.string(p.name),
            ])

        if p.defArg:
            if p.defWithAssign:
                decl.append(self.string(" = "))

            decl.append(p.defArg)

        decl.append(self.string(";"))

        return self.line(decl)

    def block(
        self,
        head: Optional[BlockId],
        content: List[BlockId],
        trailingLine: bool = False,
        allowOneLine: bool = True,
    ) -> BlockId:
        if allowOneLine and len(content) < 2:
            result = self.b.line([
                head or self.string(""),
                self.string(" { " if head else "{"),
                self.b.stack(content),
                self.string(" }"),
            ])

        else:
            result = self.b.stack([
                self.b.line([
                    head or self.string(""),
                    self.string(" {" if head else "{"),
                ]),
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
                self.string(";"),
            ] if params.newName else [
                self.string("using "),
                self.Type(params.baseType),
                self.string(";"),
            ]))

    def Typedef(self, params: UsingParams) -> BlockId:
        return self.line([
            self.string("typedef "),
            self.Type(params.baseType),
            self.string(" "),
            self.string(params.newName),
            self.string(";"),
        ])

    def Field(self, field: RecordField) -> BlockId:
        field_body = self.b.line([
            self.string("static " if field.isStatic else ""),
            self.VarDecl(field.params)
        ])

        return self.WithAccess(self.WithDoc(field_body, field.doc), field.access)

    def MethodDef(self, m: MethodDefParams) -> BlockId:
        "Convert method definition parameters to layout block"
        head = self.b.line([
            *([] if m.Params.IsConstructor else
              [self.Type(m.Params.ResultTy),
               self.string(" ")]),
            self.Type(m.Class),
            self.string("::"),
            self.string(m.Params.Name),
            self.Arguments(m.Params),
            self.string(" const" if m.IsConst else ""),
            self.InitList(m.Params),
            self.string(" {"),
        ])

        if m.IsLine:
            body = self.b.line([head, self.b.line(m.Params.Body), self.string("}")])

        else:
            body = self.b.stack(
                [head,
                 self.b.indent(2, self.b.stack(m.Params.Body)),
                 self.string("}")])

        return self.WithTemplate(m.Params.Template, body)

    def MethodDecl(self, method: MethodDeclParams) -> BlockId:
        head = self.b.line([
            self.string("static " if method.IsStatic else ""),
            self.string("virtual " if method.IsVirtual else ""),
            *([] if method.Params.IsConstructor else [
                self.Type(method.Params.ResultTy),
                self.string(" "),
            ]),
            self.string(method.Params.Name),
            self.Arguments(method.Params),
            self.string(" const" if method.IsConst else ""),
            self.string(" override" if method.IsOverride else ""),
            self.string(" = 0" if method.IsPureVirtual else ""),
            self.InitList(method.Params),
        ])

        if method.Params.IsConstructor:
            has_body = bool(method.Params.InitList) or bool(method.Params.Body)

        else:
            has_body = bool(method.Params.Body)

        if has_body:
            impl_block = self.block(
                head,
                method.Params.Body or list(),
                allowOneLine=method.Params.AllowOneLine,
            )
        else:
            impl_block = self.b.line([head, self.string(";")])

        return self.WithAccess(
            self.WithDoc(impl_block, method.Params.doc),
            method.access,
        )

    def Record(self, params: RecordParams) -> BlockId:
        content: List[BlockId] = []

        if params.IsDefinition:
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
        if params.bases and params.IsDefinition:
            classes = [
                self.b.line([self.string("public "),
                             self.Type(base)]) for base in params.bases
            ]
            bases = self.b.line(
                [self.string(" : "),
                 self.b.join(classes, self.string(", "))])

        head = self.b.line([
            self.string("struct "),
            self.Type(params.name)
            if params.IsTemplateSpecialization else self.string(params.name.Name),
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

        if content:
            return self.WithTemplate(
                params.Template,
                cond([
                    self.Doc(params.doc),
                    head,
                    self.b.indent(0 if params.OneLine else 2, cond(content)),
                    self.string("};" if params.IsDefinition else ";"),
                    *([self.string("")] if params.TrailingLine else []),
                ]))

        else:
            return self.WithTemplate(
                params.Template,
                cond([
                    self.Doc(params.doc),
                    self.b.line([
                        head,
                        self.string("};" if params.IsDefinition else ";"),
                    ]),
                    *([self.string("")] if params.TrailingLine else []),
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
            self.string("+[" if p.IsPtrCast else "["),
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

    def InitList(self, p: FunctionParams) -> BlockId:
        if p.InitList:
            head = self.b.line([])
            self.b.add_at(head, self.string(" : "))
            self.b.add_at(head, self.csv([self.b.line([item]) for item in p.InitList]))

            return head

        else:
            return self.b.text("")

    def Attribute(self, Attr: codegen_ir.GenTuAnnotation) -> BlockId:
        It = Attr.Attribute
        match It:
            case codegen_ir.GenTuAnnotation.Freeform():
                return self.ToBlockId(It.Body)

            case codegen_ir.GenTuAnnotation.StandardAttribute():
                return self.line([
                    self.string("[["),
                    self.csv([self.Type(It.Name)] + [self.ToBlockId(a) for a in It.Args]),
                ])

            case codegen_ir.GenTuAnnotation.CompilerSpecificAttribute():
                return self.line([
                    self.ToBlockId(It.DeclStart),
                    self.csv([
                        self.string(It.DeclName),
                    ] + [self.ToBlockId(a) for a in It.Args]),
                    self.ToBlockId(It.DeclEnd),
                ])

    def Function(self, p: FunctionParams) -> BlockId:
        head = []

        for attr in p.Annotations:
            head.append(self.Attribute(attr))
            head.append(self.string(" "))

        if p.Linkage:
            head.append(self.string(f"extern \"{p.Linkage}\" "))

        if p.ResultTy is not None:
            head.append(self.Type(p.ResultTy))
            head.append(self.string(" "))

        head.append(self.string(p.Name))
        head.append(self.Arguments(p))
        head.append(self.InitList(p))

        if p.Body:
            return self.WithTemplate(
                p.Template,
                self.block(self.line(head), p.Body, True, allowOneLine=p.AllowOneLine))

        else:
            return self.WithTemplate(p.Template, self.b.line(head + [self.string(";")]))

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
            if type_.IsConst:
                qualifiers += " const"

            qualifiers += "*" * type_.PtrCount
            match type_.RefKind:
                case codegen_ir.ReferenceKind.LValue:
                    qualifiers += "&"

                case codegen_ir.ReferenceKind.RValue:
                    qualifiers += "&&"

        def get_dbg_str() -> str:
            if codegen_ir.DEBUG_TYPE_ORIGIN and type_.DbgOrigin:
                return f" /* {type_.DbgOrigin} {type_.flatQualNameWithParams()} */"

            else:
                return ""

        def get_dbg() -> BlockId:
            return self.string(get_dbg_str())

        match type_.Kind:
            case codegen_ir.QualTypeKind.FunctionPtr:
                assert type_.Func
                pointer_type = [self.Type(type_.Func.Class),
                                self.string("::")] if type_.Func.Class else []

                return self.b.line([
                    self.Type(type_.Func.ReturnType)
                    if type_.Func.ReturnType else self.string("void"),
                    self.pars(self.b.line(pointer_type + [self.string("*")])),
                    self.pars(self.csv([self.Type(T) for T in type_.Func.Args])),
                    self.string(" const" if type_.Func.IsConst else ""),
                    get_dbg(),
                ])

            case codegen_ir.QualTypeKind.TypeExpr:
                assert type_.Expr
                return self.string(type_.Expr + get_dbg_str())

            case codegen_ir.QualTypeKind.Array:
                return self.b.line([
                    self.Type(type_.Params[0]),
                    self.string("["),
                    self.Type(type_.Params[1]),
                    self.string("]"),
                    self.string(qualifiers),
                    get_dbg(),
                ])

            case codegen_ir.QualTypeKind.RegularType:
                type_scopes: List[BlockId] = []
                if type_.IsGlobalNamespace:
                    # Double colon is added by join later on
                    type_scopes.append(self.string(""))

                for Space in type_.Spaces:
                    type_scopes.append(self.Type(Space, noQualifiers=noQualifiers))

                type_scopes.append(self.string(type_.Name))

                if len(type_.Params) == 0:
                    template_parameters = self.string("")

                else:
                    template_parameters = self.b.line([
                        self.string("<"),
                        self.b.join(
                            [
                                self.Type(in_, noQualifiers=noQualifiers)
                                for in_ in type_.Params
                            ],
                            self.string(", "),
                            not type_.VerticalParamList,
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
        self, Param: Union[codegen_ir.GenTuTemplateTypename,
                           codegen_ir.GenTuTemplateGroup, GenTuTemplateParams]
    ) -> BlockId:
        if isinstance(Param, codegen_ir.GenTuTemplateTypename):
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

        elif isinstance(Param, codegen_ir.GenTuTemplateGroup):
            return self.b.line([
                self.string("template <"),
                self.b.join([self.Template(Param) for Param in Param.Params],
                            self.string(", ")),
                self.string(">")
            ])

        else:
            assert (isinstance(Param, GenTuTemplateParams))
            return self.b.stack([self.Template(Spec) for Spec in Param.Stacks])

    def WithTemplate(self, Templ: Optional[GenTuTemplateParams],
                     Body: BlockId) -> BlockId:
        if Templ and Templ.Stacks:
            return self.b.stack([self.Template(Templ), Body])
        else:
            return Body

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
