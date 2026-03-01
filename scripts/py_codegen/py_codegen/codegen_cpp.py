from dataclasses import dataclass, field

from beartype import beartype
from beartype.typing import List
from py_codegen import codegen_cpp, codegen_ir
import py_codegen.astbuilder_cpp as cpp
from py_codegen.codegen_ir import QualType
from py_haxorg.layout.wrap import BlockId


@beartype
@dataclass
class GenConverter:
    """
    Convert from codegen IR structure to the CPP backend-specific types.
    """
    ast: cpp.ASTBuilder
    isSource: bool = False
    pendingToplevel: List[BlockId] = field(default_factory=list)
    context: List[QualType] = field(default_factory=list)

    def convertFunctionBlock(self, func: cpp.FunctionParams) -> BlockId:
        return self.ast.Function(func)

    def convertFunction(self, func: codegen_ir.GenTuFunction) -> cpp.FunctionParams:
        """
        Map codegen IR free function to common CPP codegen function parameters.
        """
        decl = cpp.FunctionParams(
            ResultTy=func.result,
            Name=func.name,
            doc=self.convertDoc(func.doc),
            InitList=func.InitList,
            IsConstructor=func.IsConstructor,
            Template=func.params,
        )

        if func.impl is not None:
            if isinstance(func.impl, str):
                decl.Body = [self.ast.string(str) for str in func.impl.split("\n")]
            else:
                decl.Body = [func.impl]

        decl.Args = [self.convertIdent(parm) for parm in func.arguments]

        return decl

    def convertDoc(self, doc: codegen_ir.GenTuDoc) -> cpp.DocParams:
        return cpp.DocParams(brief=doc.brief, full=doc.full)

    def convertIdent(self, ident: codegen_ir.GenTuIdent) -> cpp.ParmVarParams:
        return cpp.ParmVarParams(
            name=ident.name,
            type=ident.type,
            defArg=self.ast.string(ident.value) if ident.value else None)

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
            cpp.UsingParams(newName=typedef.name.name, baseType=typedef.base))

    def convertMethod(self, method: codegen_ir.GenTuFunction) -> cpp.MethodDeclParams:
        return cpp.MethodDeclParams(
            Params=self.convertFunction(method),
            isStatic=method.isStatic,
            isConst=method.isConst,
            isVirtual=method.isVirtual,
            isOverride=method.isOverride,
        )

    def convertStruct(self, record: codegen_ir.GenTuStruct) -> BlockId:
        params = cpp.RecordParams(
            name=record.declarationQualName()
            if record.IsExplicitInstantiation else record.name,
            doc=self.convertDoc(record.doc),
            bases=record.bases,
            IsTemplateSpecialization=record.IsExplicitInstantiation,
            Template=record.TemplateParams,
        )

        with codegen_cpp.GenConverterWithContext(self, record.name):
            for nest_type in record.nested:
                for sub in self.convert(nest_type):
                    params.nested.append(sub)

            for member in record.fields:
                params.members.append(
                    cpp.RecordField(
                        params=cpp.ParmVarParams(
                            type=member.type if member.type else QualType.ForName("void"),
                            name=member.name,
                            isConst=member.isConst,
                            defArg=(self.ast.string(member.value) if isinstance(
                                member.value, str) else member.value)
                            if member.value else None,
                        ),
                        doc=cpp.DocParams(brief=member.doc.brief, full=member.doc.full),
                        isStatic=member.isStatic,
                    ))

            for method in record.methods:
                params.members.append(self.convertMethod(method))

            for nested in record.nested:
                assert not isinstance(nested, codegen_ir.GenTuTypeGroup)

            fields = [self.ast.string(field.name) for field in record.fields]
            methods = [
                self.ast.b.line([
                    self.ast.string("("),
                    self.ast.Type(method.result),
                    self.ast.pars(
                        self.ast.csv(
                            [self.ast.Type(ident.type) for ident in method.arguments])),
                    self.ast.string(" const" if method.isConst else ""),
                    self.ast.string(") "),
                    self.ast.string(method.name),
                ]) for method in record.methods if method.result is not None
            ]

            if record.GenDescribeFields or record.GenDescribeMethods:
                if record.GenDescribeFields:
                    described_fields = [
                        self.ast.string(f.name)
                        for f in record.fields
                        if f.isExposedForDescribe
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
                            self.ast.string(record.name.name),
                            self.ast.pars(
                                self.ast.csv([B.name for B in record.bases],
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

    def convertEnum(self, entry: codegen_ir.GenTuEnum) -> BlockId:
        FromParams = cpp.FunctionParams(
            Name="from_string",
            doc=cpp.DocParams(""),
            ResultTy=codegen_ir.t_opt(entry.name),
            Args=[cpp.ParmVarParams(type=QualType(name="std::string"), name="value")],
        )

        ToParams = cpp.FunctionParams(
            Name="to_string",
            doc=cpp.DocParams(""),
            ResultTy=QualType(name="std::string"),
            Args=[cpp.ParmVarParams(type=entry.name, name="value")],
        )

        isToplevel = True
        for ctx in self.context:
            if not ctx.isNamespace:
                isToplevel = False
                break

        if self.isSource:
            return self.ast.string("")

        else:
            params = cpp.EnumParams(name=entry.name.name,
                                    doc=self.convertDoc(entry.doc),
                                    base=entry.base,
                                    IsLine=not any([F.doc.brief for F in entry.fields]))

            for _field in entry.fields:
                params.fields.append(
                    cpp.EnumParams.Field(
                        doc=cpp.DocParams(brief=_field.doc.brief, full=_field.doc.full),
                        name=_field.name,
                        value=str(_field.value) if _field.value else "None",
                    ))

            if isToplevel:
                Describe = []
                Describe.append(
                    self.ast.line([
                        self.ast.string("BOOST_DESCRIBE_ENUM_BEGIN"),
                        self.ast.pars(self.ast.Type(entry.name)),
                    ]))

                for field in entry.fields:
                    Describe.append(
                        self.ast.line([
                            self.ast.string("  BOOST_DESCRIBE_ENUM_ENTRY"),
                            self.ast.pars(
                                self.ast.csv([
                                    self.ast.Type(entry.name),
                                    self.ast.string(field.name),
                                ]))
                        ]))

                Describe.append(
                    self.ast.line([
                        self.ast.string("BOOST_DESCRIBE_ENUM_END"),
                        self.ast.pars(self.ast.Type(entry.name)),
                    ]))

                FromDefinition = FromParams
                ToDefininition = ToParams

                res = self.ast.b.stack([
                    self.ast.Enum(params),
                    self.ast.stack(Describe),
                ])

                return res
            else:
                arguments = [self.ast.string(entry.name.name)
                            ] + [self.ast.string(Field.name) for Field in entry.fields]

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
        decls: List[BlockId] = []

        match entry:
            case codegen_ir.GenTuInclude():
                decls.append(self.ast.Include(entry.what, entry.isSystem))

            case codegen_ir.GenTuEnum():
                decls.append(self.convertEnum(entry))

            case codegen_ir.GenTuFunction():
                decls.append(self.convertFunctionBlock(self.convertFunction(entry)))

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
