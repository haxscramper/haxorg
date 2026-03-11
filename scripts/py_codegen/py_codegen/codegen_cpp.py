from dataclasses import dataclass, field
from symtable import Class

from beartype import beartype
from beartype.typing import List
from py_codegen import codegen_cpp, codegen_ir
import py_codegen.astbuilder_cpp as cpp
from py_codegen.codegen_ir import QualType
from py_haxorg.layout.wrap import BlockId
from py_scriptutils.script_logging import log

CAT = __name__


@beartype
@dataclass
class GenConverter:
    """
    Convert from codegen IR structure to the CPP backend-specific types.
    """
    ast: cpp.ASTBuilder
    isHeader: bool = False
    "Generating source code for source/header?"
    isSplitHeaderSource: bool = False
    "Translation unit is split into source and header, or it is only one file?"
    pendingToplevel: List[BlockId] = field(default_factory=list)
    context: List[QualType] = field(default_factory=list)

    def convertFunctionBlock(self, func: cpp.FunctionParams) -> BlockId:
        return self.ast.Function(func)

    def convertFunction(self, func: codegen_ir.GenTuFunction,
                        inline_impl: bool) -> cpp.FunctionParams:
        """
        Map codegen IR free function to common CPP codegen function parameters.
        """
        decl = cpp.FunctionParams(
            ResultTy=func.ReturnType,
            Name=func.Name,
            doc=self.convertDoc(func.Doc),
            InitList=func.InitList if inline_impl else [],
            IsConstructor=func.IsConstructor,
            Template=func.Params,
        )

        if func.Body is not None and inline_impl:
            if isinstance(func.Body, str):
                decl.Body = [self.ast.string(s) for s in func.Body.split("\n")]
            else:
                decl.Body = [func.Body]

        decl.Args = [self.convertIdent(parm) for parm in func.Args]

        return decl

    def convertDoc(self, doc: codegen_ir.GenTuDoc) -> cpp.DocParams:
        return cpp.DocParams(brief=doc.brief, full=doc.full)

    def convertIdent(self, ident: codegen_ir.GenTuIdent) -> cpp.ParmVarParams:
        return cpp.ParmVarParams(
            name=ident.Name,
            type=ident.Type,
            defArg=self.ast.string(ident.Value) if ident.Value else None)

    def convertTu(self, tu: codegen_ir.GenTu) -> BlockId:
        decls: List[BlockId] = []
        if tu.clangFormatGuard:
            decls.append(self.ast.Comment(["clang-format off"]))
        for item in tu.entries:
            decls += self.convertWithToplevel(item)

        if tu.clangFormatGuard:
            decls.append(self.ast.Comment(["clang-format on"]))

        return self.ast.TranslationUnit(decls)

    def convertTypedef(self, typedef: codegen_ir.GenTuTypedef) -> BlockId:
        return self.ast.Using(
            cpp.UsingParams(newName=typedef.Name.Name, baseType=typedef.Base))

    def convertMethod(self, method: codegen_ir.GenTuFunction, Class: QualType,
                      inline_methods: bool) -> cpp.MethodDeclParams | cpp.MethodDefParams:
        "nodoc"
        if self.isHeader:
            return cpp.MethodDeclParams(
                Params=self.convertFunction(method, inline_impl=inline_methods),
                IsStatic=method.IsStatic,
                IsConst=method.IsConst,
                IsVirtual=method.IsVirtual,
                IsOverride=method.IsOverride,
            )
        else:
            return cpp.MethodDefParams(
                Params=self.convertFunction(method, inline_impl=True),
                Class=Class,
                IsConst=method.IsConst,
            )

    def convertStructDeclaration(self, record: codegen_ir.GenTuStruct,
                                 inline_methods: bool) -> BlockId:
        "nodoc"
        params = cpp.RecordParams(
            name=record.declarationQualName()
            if record.IsExplicitInstantiation else record.Name,
            doc=self.convertDoc(record.Doc),
            bases=record.Bases,
            IsTemplateSpecialization=record.IsExplicitInstantiation,
            Template=record.TemplateParams,
        )

        with codegen_cpp.GenConverterWithContext(self, record.Name):
            for nest_type in record.Nested:
                for sub in self.convert(nest_type):
                    params.nested.append(sub)

            for member in record.Fields:
                params.members.append(
                    cpp.RecordField(
                        params=cpp.ParmVarParams(
                            type=member.Type if member.Type else QualType.ForName("void"),
                            name=member.Name,
                            IsConst=member.IsConst,
                            defArg=(self.ast.string(member.Value) if isinstance(
                                member.Value, str) else member.Value)
                            if member.Value else None,
                        ),
                        doc=cpp.DocParams(brief=member.Doc.brief, full=member.Doc.full),
                        isStatic=member.IsStatic,
                    ))

            for method in record.Methods:
                params.members.append(
                    self.convertMethod(method,
                                       Class=record.declarationQualName(),
                                       inline_methods=inline_methods))

            for nested in record.Nested:
                assert not isinstance(nested, codegen_ir.GenTuTypeGroup)

            fields = [self.ast.string(field.Name) for field in record.Fields]
            methods = [
                self.ast.b.line([
                    self.ast.string("("),
                    self.ast.Type(method.ReturnType),
                    self.ast.pars(
                        self.ast.csv([self.ast.Type(ident.Type)
                                      for ident in method.Args])),
                    self.ast.string(" const" if method.IsConst else ""),
                    self.ast.string(") "),
                    self.ast.string(method.Name),
                ])
                for method in record.Methods
                if method.ReturnType is not None
            ]

            if record.GenDescribeFields or record.GenDescribeMethods:
                if record.GenDescribeFields:
                    described_fields = [
                        self.ast.string(rf.Name)
                        for rf in record.Fields
                        if rf.IsExposedForDescribe
                    ]
                else:
                    described_fields = []

                if record.GenDescribeMethods:
                    described_methods = methods

                else:
                    described_methods = []

                LineParameters = len(described_fields) < 4 and len(described_methods) < 1

                params.nested.append(
                    self.ast.XCall(
                        "BOOST_DESCRIBE_CLASS",
                        [
                            self.ast.string(record.Name.Name),
                            self.ast.pars(
                                self.ast.csv([B.Name for B in record.Bases],
                                             LineParameters)),
                            self.ast.pars(self.ast.string("")),
                            self.ast.pars(self.ast.string("")),
                            self.ast.pars(
                                self.ast.csv(described_fields + described_methods,
                                             len(fields) < 6 and len(methods) < 2)),
                        ],
                        Stmt=True,
                        LineParameters=LineParameters,
                    ))

        return self.ast.Record(params)

    def convertStruct(self, record: codegen_ir.GenTuStruct) -> BlockId:
        "nodoc"
        if self.isHeader:
            if record.ExposeHeaderDeclaration:
                # Structure is exposed in public API, but the implementation
                # might be split into the source file.
                return self.convertStructDeclaration(
                    record, inline_methods=not self.isSplitHeaderSource)

            else:
                # Generating header but structure is not exposed
                return self.ast.string("")

        else:
            # Structure has already been generated in the header file, adding implementation
            # for direct and nested methods.
            if record.ExposeHeaderDeclaration:
                definitions = [
                    self.ast.MethodDef(
                        self.convertMethod(m,
                                           Class=record.declarationQualName(),
                                           inline_methods=True)) for m in record.Methods
                ]

                for n in record.Nested:
                    if isinstance(n, (codegen_ir.GenTuStruct,)):
                        definitions.extend(self.convert(n))

                return self.ast.stack(*definitions)

            else:
                # Structure is not exposed publicly, generating full definition and declaration
                # in the source code file.
                return self.convertStructDeclaration(record, inline_methods=True)

    def convertEnum(self, entry: codegen_ir.GenTuEnum) -> BlockId:
        "nodoc"
        FromParams = cpp.FunctionParams(
            Name="from_string",
            doc=cpp.DocParams(""),
            ResultTy=codegen_ir.t_opt(entry.Name),
            Args=[cpp.ParmVarParams(type=QualType(Name="std::string"), name="value")],
        )

        ToParams = cpp.FunctionParams(
            Name="to_string",
            doc=cpp.DocParams(""),
            ResultTy=QualType(Name="std::string"),
            Args=[cpp.ParmVarParams(type=entry.Name, name="value")],
        )

        isToplevel = True
        for ctx in self.context:
            if not ctx.IsNamespace:
                isToplevel = False
                break

        if not self.isHeader:
            return self.ast.string("")

        params = cpp.EnumParams(name=entry.Name.Name,
                                doc=self.convertDoc(entry.Doc),
                                base=entry.Base,
                                IsLine=not any([F.Doc.brief for F in entry.Fields]))

        for _field in entry.Fields:
            params.fields.append(
                cpp.EnumParams.Field(
                    doc=cpp.DocParams(brief=_field.Doc.brief, full=_field.Doc.full),
                    name=_field.Name,
                    value=str(_field.Value) if _field.Value else "None",
                ))

        if isToplevel:
            Describe = []
            Describe.append(
                self.ast.line([
                    self.ast.string("BOOST_DESCRIBE_ENUM_BEGIN"),
                    self.ast.pars(self.ast.Type(entry.Name)),
                ]))

            for field in entry.Fields:
                Describe.append(
                    self.ast.line([
                        self.ast.string("  BOOST_DESCRIBE_ENUM_ENTRY"),
                        self.ast.pars(
                            self.ast.csv([
                                self.ast.Type(entry.Name),
                                self.ast.string(field.Name),
                            ]))
                    ]))

            Describe.append(
                self.ast.line([
                    self.ast.string("BOOST_DESCRIBE_ENUM_END"),
                    self.ast.pars(self.ast.Type(entry.Name)),
                ]))

            FromDefinition = FromParams
            ToDefininition = ToParams

            res = self.ast.b.stack([
                self.ast.Enum(params),
                self.ast.stack(Describe),
            ])

            return res
        else:
            arguments = [self.ast.string(entry.Name.Name)
                        ] + [self.ast.string(Field.Name) for Field in entry.Fields]

            return self.ast.b.stack([
                self.ast.Enum(params),
                self.ast.XCall("BOOST_DESCRIBE_NESTED_ENUM", arguments),
            ])

    def convertNamespace(self, space: codegen_ir.GenTuNamespace) -> BlockId:
        result = self.ast.b.stack([])
        with codegen_cpp.GenConverterWithContext(self, space.name.asNamespace()):
            self.ast.b.add_at(
                result,
                self.ast.b.line([
                    self.ast.string("namespace "),
                    self.ast.Type(space.name),
                    self.ast.string(" {"),
                ]))

            for sub in space.entries:
                self.ast.b.add_at_list(result, self.convertWithToplevel(sub))

            self.ast.b.add_at(result, self.ast.string("}"))

        return result

    def convertTypeGroup(self, record: codegen_ir.GenTuTypeGroup) -> List[BlockId]:
        decls: List[BlockId] = []

        for sub in record.types:
            decls += self.convert(sub)

        return decls

    def convertWithToplevel(self, entry: codegen_ir.GenTuEntry) -> List[BlockId]:
        decls: List[BlockId] = self.convert(entry)
        decls += self.pendingToplevel
        self.pendingToplevel = []
        return decls

    def convert(self, entry: codegen_ir.GenTuEntry) -> List[BlockId]:
        "Generate C++ code for the IR entry"
        decls: List[BlockId] = []

        match entry:
            case codegen_ir.GenTuInclude():
                decls.append(self.ast.Include(entry.what, entry.isSystem))

            case codegen_ir.GenTuEnum():
                decls.append(self.convertEnum(entry))

            case codegen_ir.GenTuFunction():
                decls.append(
                    self.convertFunctionBlock(
                        self.convertFunction(entry,
                                             inline_impl=not self.isSplitHeaderSource)))

            case codegen_ir.GenTuStruct():
                decls.append(self.convertStruct(entry))

            case codegen_ir.GenTuTypeGroup():
                decls.extend(self.convertTypeGroup(entry))

            case codegen_ir.GenTuPass():
                if isinstance(entry.what, str):
                    decls.append(self.ast.string(entry.what))
                else:
                    decls.append(entry.what)

            case codegen_ir.GenTuTypedef():
                decls.append(self.convertTypedef(entry))

            case codegen_ir.GenTuNamespace():
                decls.append(self.convertNamespace(entry))

            case _:
                raise ValueError("Unexpected kind '%s'" % type(entry))

        return decls


@beartype
@dataclass
class GenConverterWithContext:
    "Context manager to add elements to the converter context"
    conv: "GenConverter"
    "Converter context"
    typ: QualType
    "Extra type to append to the converter context"

    def __exit__(self, exc_type: object, exc_val: object, exc_tb: object) -> None:
        self.conv.context.pop()

    def __enter__(self) -> "GenConverterWithContext":
        self.conv.context.append(self.typ)
        return self
