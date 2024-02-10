from dataclasses import dataclass, field
from py_codegen.astbuilder_cpp import *
from beartype.typing import Sequence, List, TypeAlias, Mapping
from beartype import beartype
from py_textlayout.py_textlayout_wrap import *
from pathlib import Path
from py_scriptutils.algorithm import iterate_object_tree

if not TYPE_CHECKING:
    BlockId = NewType('BlockId', int)


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
class GenTuTypedef:
    name: QualType
    base: QualType
    original: Optional[Path] = None


@beartype
@dataclass
class GenTuEnumField:
    name: str
    doc: GenTuDoc
    value: Optional[int] = None


@beartype
@dataclass
class GenTuEnum:
    name: QualType
    doc: GenTuDoc
    fields: List[GenTuEnumField]
    base: Optional[str] = "short int"
    refl: bool = False
    IsForwardDecl: bool = False
    original: Optional[Path] = None

    def format(self, dbgOrigin: bool = False) -> str:
        return "enum " + self.name.format(dbgOrigin=dbgOrigin)


@beartype
@dataclass
class GenTuFunction:
    result: QualType
    name: str
    doc: GenTuDoc
    params: List[GenTuParam] = field(default_factory=list)
    arguments: List[GenTuIdent] = field(default_factory=list)
    impl: Optional[Union[str, BlockId]] = None
    isVirtual: bool = False
    isConst: bool = False
    isStatic: bool = False
    isPureVirtual: bool = False
    parentClass: Optional['GenTuStruct'] = None
    original: Optional[Path] = None

    def format(self) -> str:
        return "function %s %s(%s)" % (self.result.format(), self.name, ", ".join(
            [Arg.name + " " + Arg.type.format() for Arg in self.arguments]))


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
    type: Optional[QualType]
    name: str
    doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))
    decl: Optional[Union['GenTuStruct', 'GenTuEnum']] = None
    value: Optional[Union[str, BlockId]] = None
    isConst: bool = False
    isStatic: bool = False
    isTypeDecl: bool = False


GenTuEntry = Union[
    GenTuEnum,
    "GenTuStruct",
    "GenTuTypeGroup",
    GenTuFunction,
    "GenTuNamespace",
    GenTuInclude,
    GenTuTypedef,
    GenTuPass,
]


@beartype
@dataclass
class GenTuStruct:
    name: QualType
    doc: GenTuDoc
    fields: List[GenTuField] = field(default_factory=list)
    methods: List[GenTuFunction] = field(default_factory=list)
    bases: List[QualType] = field(default_factory=list)
    nested: List[GenTuEntry] = field(default_factory=list)
    concreteKind: bool = True
    IsForwardDecl: bool = False
    IsAbstract: bool = False
    has_name: bool = True
    original: Optional[Path] = field(default=None)

    def format(self, dbgOrigin: bool = False) -> str:
        return "record " + self.name.format(dbgOrigin=dbgOrigin)


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


GenTuUnion: TypeAlias = Union[GenTuStruct, GenTuEnum, GenTuTypedef, GenTuFunction]


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
        return TemplateGroup(
            Params=[TemplateTypename(Name=Param.name) for Param in Params])

    def convertFunctionBlock(self, func: FunctionParams) -> BlockId:
        return self.ast.Function(func)

    def convertFunction(self, func: GenTuFunction) -> FunctionParams:
        decl = FunctionParams(ResultTy=func.result,
                              Name=func.name,
                              doc=self.convertDoc(func.doc))

        if func.params:
            decl.Template.Stacks = [self.convertParams(func.params)]

        if func.impl is not None:
            if isinstance(func.impl, str):
                decl.Body = [self.ast.string(str) for str in func.impl.split("\n")]
            else:
                decl.Body = [func.impl]

        decl.Args = [self.convertIdent(parm) for parm in func.arguments]

        return decl

    def convertDoc(self, doc: GenTuDoc) -> DocParams:
        return DocParams(brief=doc.brief, full=doc.full)

    def convertIdent(self, ident: GenTuIdent) -> ParmVarParams:
        return ParmVarParams(name=ident.name,
                             type=ident.type,
                             defArg=self.ast.string(ident.value) if ident.value else None)

    def convertTu(self, tu: GenTu) -> BlockId:
        decls: List[BlockId] = []
        decls.append(self.ast.Comment(["clang-format off"]))
        for item in tu.entries:
            decls += self.convertWithToplevel(item)

        decls.append(self.ast.Comment(["clang-format on"]))

        return self.ast.TranslationUnit(decls)

    def convertTypedef(self, typedef: GenTuTypedef) -> BlockId:
        return self.ast.Using(
            UsingParams(newName=typedef.name.name, baseType=typedef.base))

    def convertStruct(self, record: GenTuStruct) -> BlockId:
        params = RecordParams(
            name=record.name.name,
            doc=self.convertDoc(record.doc),
            bases=record.bases,
        )

        with GenConverterWithContext(self, QualType.ForName(record.name.name)):
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
                            defArg=(self.ast.string(member.value) if isinstance(
                                member.value, str) else member.value)
                            if member.value else None,
                        ),
                        doc=DocParams(brief=member.doc.brief, full=member.doc.full),
                        isStatic=member.isStatic,
                    ))

            for method in record.methods:
                params.members.append(
                    MethodDeclParams(Params=self.convertFunction(method),
                                     isStatic=method.isStatic,
                                     isConst=method.isConst,
                                     isVirtual=method.isVirtual))

            for nested in record.nested:
                assert not isinstance(nested, GenTuTypeGroup)

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
                ]) for method in record.methods
            ]

            params.nested.append(
                self.ast.XCall(
                    "BOOST_DESCRIBE_CLASS",
                    [
                        self.ast.string(record.name.name),
                        self.ast.pars(self.ast.csv([B.name for B in record.bases],
                                                   False)),
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
            ResultTy=QualType(name="Opt", Parameters=[entry.name]),
            Args=[ParmVarParams(type=QualType(name="std::string"), name="value")],
        )

        ToParams = FunctionParams(
            Name="to_string",
            doc=DocParams(""),
            ResultTy=QualType(name="std::string"),
            Args=[ParmVarParams(type=entry.name, name="value")],
        )

        isToplevel = True
        for ctx in self.context:
            if not ctx.isNamespace:
                isToplevel = False
                break

        if self.isSource:
            if isToplevel:
                Class = QualType(name="enum_serde", Parameters=[entry.name])

                SwichFrom = IfStmtParams(LookupIfStructure=True, Branches=[])
                for _field in entry.fields:
                    SwichFrom.Branches.append(
                        IfStmtParams.Branch(
                            OneLine=True,
                            Then=self.ast.Return(
                                self.ast.string(f"{entry.name.name}::{_field.name}")),
                            Cond=self.ast.XCall(
                                "==",
                                [
                                    self.ast.string("value"),
                                    self.ast.Literal(_field.name),
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
                                Expr=self.ast.string(f"{entry.name.name}::{field.name}"),
                                Body=[self.ast.Return(self.ast.Literal(field.name))],
                            ),
                            entry.fields,
                        )),
                )

                FromDefinition = FromParams
                FromDefinition.Body = [self.ast.IfStmt(SwichFrom)]

                self.pendingToplevel.append(
                    self.ast.MethodDef(MethodDefParams(Class=Class,
                                                       Params=FromDefinition)))

                ToDefininition = ToParams
                ToDefininition.Body = [self.ast.SwitchStmt(SwitchTo)]

                self.pendingToplevel.append(
                    self.ast.MethodDef(MethodDefParams(Class=Class,
                                                       Params=ToDefininition)))

            return self.ast.string("")

        else:
            params = EnumParams(name=entry.name.name,
                                doc=self.convertDoc(entry.doc),
                                base=entry.base,
                                IsLine=not any([F.doc.brief for F in entry.fields]))

            for _field in entry.fields:
                params.fields.append(
                    EnumParams.Field(
                        doc=DocParams(brief=_field.doc.brief, full=_field.doc.full),
                        name=_field.name,
                        value=_field.value,
                    ))

            if isToplevel:
                Domain = RecordParams(
                    name="value_domain",
                    doc=DocParams(""),
                    Template=TemplateParams.FinalSpecialization(),
                    NameParams=[entry.name],
                    bases=[
                        QualType(
                            name="value_domain_ungapped",
                            Parameters=[
                                entry.name,
                                QualType(
                                    Spaces=[entry.name],
                                    name=entry.fields[0].name,
                                ),
                                QualType(
                                    Spaces=[entry.name],
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
                    NameParams=[entry.name],
                )

                Serde.members.append(
                    MethodDeclParams(isStatic=True, Params=FromDefinition))
                Serde.members.append(
                    MethodDeclParams(isStatic=True, Params=ToDefininition))

                res = self.ast.b.stack([
                    self.ast.Enum(params),
                    self.ast.Record(Serde),
                    self.ast.Record(Domain),
                ])

                return res
            else:
                arguments = [self.ast.string(entry.name.name)
                            ] + [self.ast.string(Field.name) for Field in entry.fields]

                return self.ast.b.stack([
                    self.ast.Enum(params),
                    self.ast.XCall("BOOST_DESCRIBE_NESTED_ENUM", arguments),
                ])

    def convertNamespace(self, space: GenTuNamespace) -> BlockId:
        result = self.ast.b.stack([])
        with GenConverterWithContext(self, QualType(name=space.name).asNamespace()):
            self.ast.b.add_at(result, self.ast.string(f"namespace {space.name}{{"))

            for sub in space.entries:
                self.ast.b.add_at_list(result, self.convertWithToplevel(sub))

            self.ast.b.add_at(result, self.ast.string("}"))

        return result

    def convertTypeGroup(self, record: GenTuTypeGroup) -> List[BlockId]:
        decls: List[BlockId] = []

        for sub in record.types:
            decls += self.convert(sub)

        return decls

    def convertWithToplevel(self, entry: GenTuEntry) -> List[BlockId]:
        decls: List[BlockId] = self.convert(entry)
        decls += self.pendingToplevel
        self.pendingToplevel = []
        return decls

    def convert(self, entry: GenTuEntry) -> List[BlockId]:
        decls: List[BlockId] = []

        match entry:
            case GenTuInclude():
                decls.append(self.ast.Include(entry.what, entry.isSystem))

            case GenTuEnum():
                decls.append(self.convertEnum(entry))

            case GenTuFunction():
                decls.append(self.convertFunctionBlock(self.convertFunction(entry)))

            case GenTuStruct():
                decls.append(self.convertStruct(entry))

            case GenTuTypeGroup():
                decls.extend(self.convertTypeGroup(entry))

            case GenTuPass():
                if isinstance(entry.what, str):
                    decls.append(self.ast.string(entry.what))
                else:
                    decls.append(entry.what)

            case GenTuTypedef():
                decls.append(self.convertTypedef(entry))

            case GenTuNamespace():
                decls.append(self.convertNamespace(entry))

            case _:
                raise ValueError("Unexpected kind '%s'" % type(entry))

        return decls


@beartype
def t_opt(arg: QualType) -> QualType:
    return QualType(name="Opt", Parameters=[arg])


@beartype
def t_vec(arg: QualType) -> QualType:
    return QualType(name="Vec", Parameters=[arg])


def n_sem() -> QualType:
    return QualType(name="sem", isNamespace=True)


@beartype
def t_id(target: Optional[Union[QualType, str]] = None) -> QualType:
    org_t = target if target else QualType(name="Org", Spaces=[n_sem()])
    org_t = org_t if isinstance(
        org_t,
        QualType,
    ) else QualType(
        name=org_t,
        Spaces=[n_sem()],
    )

    return (QualType(name="SemId", Parameters=[org_t], Spaces=[n_sem()]))


@beartype
def get_base_map(expanded: List[GenTuUnion]) -> Mapping[str, GenTuStruct]:
    base_map: Mapping[str, GenTuStruct] = {}

    def callback(obj):
        if isinstance(obj, GenTuStruct):
            base_map[obj.name.name] = obj

    context = []
    iterate_object_tree(expanded, callback, context)
    base_map["Org"] = GenTuStruct(
        QualType.ForName("Org"),
        GenTuDoc(""),
        [
            GenTuField(t_vec(t_id()), "subnodes", GenTuDoc("")),
        ],
    )

    return base_map


@beartype
def filter_walk_scope(iterate_context) -> List[QualType]:
    scope: List[QualType] = []

    for s in iterate_context:
        match s:
            case GenTuStruct():
                scope.append(s.name)

            case GenTuNamespace():
                scope.append(QualType.ForName(s.name))

    return scope


@beartype
def get_type_base_fields(
    value: GenTuStruct,
    base_map: Mapping[str, GenTuStruct],
) -> List[GenTuField]:
    fields = []
    for base_sym in value.bases:
        base = base_map.get(base_sym.name)
        if base:
            fields.extend(base.fields)
            fields.extend(get_type_base_fields(base, base_map))

    return fields


@beartype
def get_base_list(
    value: GenTuStruct,
    base_map: Mapping[str, GenTuStruct],
) -> List[QualType]:
    fields = []

    def aux(typ: QualType) -> List[QualType]:
        result: List[QualType] = [typ]
        base = base_map.get(typ.name)
        if base:
            for it in base.bases:
                result.extend(aux(it))

        return result

    for base_sym in value.bases:
        fields.extend(aux(base_sym))

    return fields


@beartype
def in_type_list(typ: QualType, enum_type_list: List[QualType]) -> bool:
    return any(typ.flatQualName() == it.flatQualName() for it in enum_type_list)
