from dataclasses import dataclass, field
from astbuilder_cpp import *
from beartype.typing import *
from pprint import pprint
from beartype import beartype


@beartype
@dataclass
class GenTuParam:
    name: str


@beartype
@dataclass
class GenTuIdent:
    type: QualType
    name: str
    value: Optional[str] = None


@beartype
@dataclass
class GenTuDoc:
    brief: str
    full: str = ""


@beartype
@dataclass
class GenTuEnumField:
    name: str
    doc: GenTuDoc
    value: Optional[str] = None


@beartype
@dataclass
class GenTuEnum:
    name: str
    doc: GenTuDoc
    fields: List[GenTuEnumField]
    base: Optional[str] = "short int"


@beartype
@dataclass
class GenTuFunction:
    result: QualType
    name: str
    doc: GenTuDoc
    params: List[GenTuParam] = field(default_factory=list)
    arguments: List[GenTuIdent] = field(default_factory=list)
    impl: Optional[str] = None
    isVirtual: bool = False
    isConst: bool = False
    isStatic: bool = False
    isPureVirtual: bool = False


@beartype
@dataclass
class GenTuInclude:
    what: str
    isSystem: bool = False


@beartype
@dataclass
class GenTuPass:
    what: Union[str, BlockId]


@beartype
@dataclass
class GenTuField:
    type: QualType
    name: str
    doc: GenTuDoc
    value: Optional[str] = None
    isConst: bool = False
    isStatic: bool = False


GenTuEntry = Union[
    GenTuEnum,
    "GenTuStruct",
    "GenTuTypeGroup",
    GenTuFunction,
    "GenTuNamespace",
    GenTuInclude,
    GenTuPass,
]


@beartype
@dataclass
class GenTuStruct:
    name: str
    doc: GenTuDoc
    fields: List[GenTuField] = field(default_factory=list)
    methods: List[GenTuFunction] = field(default_factory=list)
    bases: List[str] = field(default_factory=list)
    nested: List[GenTuEntry] = field(default_factory=list)
    concreteKind: bool = True


@beartype
@dataclass
class GenTuTypeGroup:
    types: List[GenTuStruct]
    iteratorMacroName: Optional[str] = None
    enumName: str = "Kind"
    variantField: str = "data"
    variantName: str = "Data"
    variantValue: Optional[str] = None
    kindGetter: str = "getKind"


@beartype
@dataclass
class GenTuNamespace:
    name: str
    entries: Sequence[GenTuEntry]


@beartype
@dataclass
class GenTu:
    path: str
    entries: Sequence[GenTuEntry]


@beartype
@dataclass
class GenUnit:
    header: GenTu
    source: Optional[GenTu] = None


@beartype
@dataclass
class GenFiles:
    files: List[GenUnit]


@beartype
@dataclass
class GenConverterWithContext:
    conv: "GenConverter"
    typ: QualType

    def __exit__(self, type, value, traceback):
        self.conv.context.pop()

    def __enter__(self):
        self.conv.context.append(self.typ)


@beartype
@dataclass
class GenConverter:
    ast: ASTBuilder
    isSource: bool = False
    pendingToplevel: List[BlockId] = field(default_factory=list)
    context: List[QualType] = field(default_factory=list)

    def convertParams(self, Params: List[GenTuParam]) -> TemplateGroup:
        return TemplateGroup(Params=[TemplateTypename(Name=Param.name) for Param in Params])

    def convertFunctionBlock(self, func: FunctionParams) -> BlockId:
        return self.ast.Function(func)

    def convertFunction(self, func: GenTuFunction) -> FunctionParams:
        decl = FunctionParams(ResultTy=func.result, Name=func.name, doc=self.convertDoc(func.doc))

        if func.params:
            decl.Template.Stacks = [self.convertParams(func.params)]

        if func.impl is not None:
            decl.Body = [self.ast.string(str) for str in func.impl.split("\n")]

        decl.Args = [self.convertIdent(parm) for parm in func.arguments]

        return decl

    def convertDoc(self, doc: GenTuDoc) -> DocParams:
        return DocParams(brief=doc.brief, full=doc.full)

    def convertIdent(self, ident: GenTuIdent) -> ParmVarParams:
        return ParmVarParams(name=ident.name, type=ident.type, defArg=self.ast.string(ident.value) if ident.value else None)

    def convertTu(self, tu: GenTu) -> BlockId:
        decls: List[BlockId] = []
        for item in tu.entries:
            decls += self.convertWithToplevel(item)

        return self.ast.TranslationUnit(decls)

    def convertStruct(self, record: GenTuStruct) -> BlockId:
        params = RecordParams(
            name=record.name,
            doc=self.convertDoc(record.doc),
            bases=[QualType(base) for base in record.bases],
        )

        with GenConverterWithContext(self, QualType(record.name)):
            for type in record.nested:
                for sub in self.convert(type):
                    params.nested.append(sub)

            for member in record.fields:
                params.members.append(
                    RecordField(
                        params=ParmVarParams(
                            type=member.type,
                            name=member.name,
                            isConst=member.isConst,
                            defArg=self.ast.string(member.value) if member.value else None,
                        ),
                        doc=DocParams(brief=member.doc.brief, full=member.doc.full),
                        isStatic=member.isStatic,
                    ))

            for method in record.methods:
                params.members.append(
                    MethodDeclParams(
                        Params=self.convertFunction(method),
                        isStatic=method.isStatic,
                        isConst=method.isConst,
                        isVirtual=method.isVirtual,
                    ))

            extraFields = []
            extraMethods = []
            for nested in record.nested:
                if isinstance(nested, GenTuTypeGroup):
                    group: GenTuTypeGroup = nested
                    if group.kindGetter:
                        extraMethods.append(
                            GenTuFunction(
                                name=group.kindGetter,
                                result=QualType(group.enumName),
                                isConst=True,
                                doc=GenTuDoc(""),
                            ))
                    if group.variantName:
                        extraFields.append(
                            GenTuField(
                                name=group.variantField,
                                doc=GenTuDoc(""),
                                type=QualType(group.variantName),
                            ))

            fields = [self.ast.string(field.name) for field in record.fields + extraFields]
            methods = [
                self.ast.b.line([
                    self.ast.string("("),
                    self.ast.Type(method.result),
                    self.ast.pars(
                        self.ast.csv([self.ast.Type(ident.type) for ident in method.arguments])),
                    self.ast.string(" const" if method.isConst else ""),
                    self.ast.string(") "),
                    self.ast.string(method.name),
                ]) for method in record.methods + extraMethods
            ]

            params.nested.append(
                self.ast.XCall(
                    "BOOST_DESCRIBE_CLASS",
                    [
                        self.ast.string(record.name),
                        self.ast.pars(self.ast.csv(record.bases, False)),
                        self.ast.pars(self.ast.string("")),
                        self.ast.pars(self.ast.string("")),
                        self.ast.pars(
                            self.ast.csv(fields + methods,
                                         len(fields) < 6 and len(methods) < 2)),
                    ],
                    False,
                    len(fields) < 4 and len(methods) < 1,
                ))

        return self.ast.Record(params)

    def convertEnum(self, entry: GenTuEnum) -> BlockId:
        FromParams = FunctionParams(
            Name="from_string",
            doc=DocParams(""),
            ResultTy=QualType("Opt", Parameters=[QualType(entry.name)]),
            Args=[ParmVarParams(type=QualType("QString"), name="value")],
        )

        ToParams = FunctionParams(
            Name="to_string",
            doc=DocParams(""),
            ResultTy=QualType("QString"),
            Args=[ParmVarParams(type=QualType(entry.name), name="value")],
        )

        isToplevel = True
        for ctx in self.context:
            if not ctx.isNamespace:
                isToplevel = False
                break

        if self.isSource:
            if isToplevel:
                Class = QualType(name="enum_serde", Parameters=[QualType(entry.name)])

                SwichFrom = IfStmtParams(LookupIfStructure=True, Branches=[])
                for field in entry.fields:
                    SwichFrom.Branches.append(
                        IfStmtParams.Branch(
                            OneLine=True,
                            Then=self.ast.Return(self.ast.string(f"{entry.name}::{field.name}")),
                            Cond=self.ast.XCall(
                                "==",
                                [
                                    self.ast.string("value"),
                                    self.ast.Literal(field.name),
                                ],
                            ),
                        ))

                SwichFrom.Branches.append(
                    IfStmtParams.Branch(
                        OneLine=True,
                        Then=self.ast.Return(self.ast.string("std::nullopt")),
                    ))

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
                                Expr=self.ast.string(f"{entry.name}::{field.name}"),
                                Body=[self.ast.Return(self.ast.Literal(field.name))],
                            ),
                            entry.fields,
                        )),
                )

                FromDefinition = FromParams
                FromDefinition.Body = [self.ast.IfStmt(SwichFrom)]

                self.pendingToplevel.append(
                    self.ast.MethodDef(MethodDefParams(Class=Class, Params=FromDefinition)))

                ToDefininition = ToParams
                ToDefininition.Body = [self.ast.SwitchStmt(SwitchTo)]

                self.pendingToplevel.append(
                    self.ast.MethodDef(MethodDefParams(Class=Class, Params=ToDefininition)))

            return self.ast.string("")

        else:
            params = EnumParams(name=entry.name, doc=self.convertDoc(entry.doc), base=entry.base)

            for field in entry.fields:
                params.fields.append(
                    EnumParams.Field(
                        doc=DocParams(brief=field.doc.brief, full=field.doc.full),
                        name=field.name,
                        value=field.value,
                    ))

            if isToplevel:
                Domain = RecordParams(
                    name="value_domain",
                    doc=DocParams(""),
                    Template=TemplateParams.FinalSpecialization(),
                    NameParams=[QualType(entry.name)],
                    bases=[
                        QualType(
                            name="value_domain_ungapped",
                            Parameters=[
                                QualType(name=entry.name),
                                QualType(
                                    Spaces=[QualType(entry.name)],
                                    name=entry.fields[0].name,
                                ),
                                QualType(
                                    Spaces=[QualType(entry.name)],
                                    name=entry.fields[-1].name,
                                ),
                            ],
                        ).withVerticalParams()
                    ],
                )

                FromDefinition = FromParams
                ToDefininition = ToParams

                Serde = RecordParams(
                    name="enum_serde",
                    doc=DocParams(""),
                    Template=TemplateParams.FinalSpecialization(),
                    NameParams=[QualType(entry.name)],
                )

                Serde.members.append(MethodDeclParams(isStatic=True, Params=FromDefinition))
                Serde.members.append(MethodDeclParams(isStatic=True, Params=ToDefininition))

                res = self.ast.b.stack([
                    self.ast.Enum(params),
                    self.ast.Record(Serde),
                    self.ast.Record(Domain),
                ])

                return res
            else:
                arguments = [self.ast.string(entry.name)
                            ] + [self.ast.string(Field.name) for Field in entry.fields]

                return self.ast.b.stack([
                    self.ast.Enum(params),
                    self.ast.XCall("BOOST_DESCRIBE_NESTED_ENUM", arguments),
                ])

    def convertNamespace(self, space: GenTuNamespace) -> BlockId:
        result = self.ast.b.stack([])
        with GenConverterWithContext(self, QualType(space.name).asNamespace()):
            self.ast.b.add_at(result, self.ast.string(f"namespace {space.name}{{"))

            for sub in space.entries:
                self.ast.b.add_at_list(result, self.convertWithToplevel(sub))

            self.ast.b.add_at(result, self.ast.string("}"))

        return result

    def convertTypeGroup(self, record: GenTuTypeGroup) -> List[BlockId]:
        decls: List[BlockId] = []
        typeNames: List[str] = []

        for item in record.types:
            if item.concreteKind:
                typeNames.append(item.name)

        if False and len(record.enumName) > 0:
            enumDecl = EnumParams(name=record.enumName, doc=DocParams(""))

            for typeItem in typeNames:
                enumDecl.fields.append(EnumParams.Field(name=typeItem, doc=DocParams("")))

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
                        OneLine=True,
                    ))

            fromEnum = FunctionParams(
                Name="from_enum",
                doc=DocParams(""),
                ResultTy=QualType("char").Ptr().Const(),
                Args=[ParmVarParams(type=QualType(record.enumName), name=resName)],
                Body=[self.ast.SwitchStmt(switchTo)],
            )

            decls.append(self.ast.Function(fromEnum))

        if record.iteratorMacroName:
            iteratorMacro = MacroParams(
                name=record.iteratorMacroName,
                params=[MacroParams.Param("__IMPL")],
                doc=DocParams(""),
            )

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
                self.ast.string(record.kindGetter),
            ]

            for kind in typeNames:
                Arguments.append(self.ast.string(kind))

            if False:
                using_params = UsingParams(
                    newName=record.variantName,
                    baseType=QualType("Variant", [QualType(Type) for Type in typeNames]),
                )
                decls.append(self.ast.Using(using_params))

            decls.append(self.ast.XCall("SUB_VARIANTS", Arguments, True))
            decls.append(
                self.ast.Field(
                    RecordField(
                        params=ParmVarParams(
                            type=QualType(record.variantName),
                            name=record.variantField,
                            defArg=self.ast.string(record.variantValue) if record.variantValue else None,
                        ),
                        doc=DocParams(""),
                    )))

        return decls

    def convertWithToplevel(self, entry: GenTuEntry) -> List[BlockId]:
        decls: List[BlockId] = self.convert(entry)
        decls += self.pendingToplevel
        self.pendingToplevel = []
        return decls

    def convert(self, entry: GenTuEntry) -> List[BlockId]:
        decls: List[BlockId] = []

        if isinstance(entry, GenTuInclude):
            decls.append(self.ast.Include(entry.what, entry.isSystem))
        elif isinstance(entry, GenTuEnum):
            decls.append(self.convertEnum(entry))
        elif isinstance(entry, GenTuFunction):
            decls.append(self.convertFunctionBlock(self.convertFunction(entry)))
        elif isinstance(entry, GenTuStruct):
            decls.append(self.convertStruct(entry))
        elif isinstance(entry, GenTuTypeGroup):
            decls.extend(self.convertTypeGroup(entry))
        elif isinstance(entry, GenTuPass):
            if isinstance(entry.what, str):
                decls.append(self.ast.string(entry.what))
            else:
                decls.append(entry.what)

        elif isinstance(entry, GenTuNamespace):
            decls.append(self.convertNamespace(entry))
        else:
            raise ValueError("Unexpected kind '%s'" % type(entry))

        return decls