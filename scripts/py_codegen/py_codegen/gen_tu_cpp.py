from collections import defaultdict
from dataclasses import dataclass
from dataclasses import field
from pathlib import Path

from beartype import beartype
from beartype.typing import List
from beartype.typing import Literal
from beartype.typing import Mapping
from beartype.typing import Sequence
from beartype.typing import Set
from beartype.typing import TypeAlias
from py_codegen.astbuilder_cpp import *
from py_scriptutils.algorithm import cond
from py_scriptutils.algorithm import iterate_object_tree
from py_scriptutils.script_logging import log
from py_textlayout.py_textlayout_wrap import *
from pydantic import AliasChoices

CAT = __name__

if not TYPE_CHECKING:
    BlockId = NewType('BlockId', int)


@beartype
@dataclass
class GenTuParam:
    name: str


@beartype
class GenTuBackendPythonParams(BaseModel, extra="forbid"):
    holder_type: Optional[Literal["shared", "unique"] | str | QualType] = Field(
        alias="holder-type", default=None)


@beartype
class GenTuBackendWasmParams(BaseModel, extra="forbid"):
    holder_type: Optional[Literal["shared", "unique"] | str | QualType] = Field(
        alias="holder-type", default=None)


@beartype
class GenTuBackendParams(BaseModel, extra="forbid"):
    python: GenTuBackendPythonParams = Field(default_factory=GenTuBackendPythonParams)
    wasm: GenTuBackendPythonParams = Field(default_factory=GenTuBackendPythonParams)
    target_backends: List[str] = Field(  # type: ignore
        default_factory=list,
        description="Which backends should generate wrappers for the entry?",
        alias=AliasChoices("target_backends", "target-backends"),
    )


@beartype
class GenTuTypeApiTraits(BaseModel, extra="forbid"):
    has_begin_end_iteration: bool = Field(  # type: ignore
        alias=AliasChoices("has-begin-end-iteration", "has_begin_end_iteration"),
        default=False,
        description="Type provides `begin()` and `end()` method to construct iterator pair"
    )

    is_org_ast_value: bool = Field(default=False,)


@beartype
class GenTuFunctionApiTraits(BaseModel, extra="forbid"):
    is_get_item: bool = Field(  # type: ignore
        alias=AliasChoices("is-getitem", "is_getitem"),
        default=False,
        description="This method can provide __getitem__ implementation")


@beartype
class GenTuReflParams(BaseModel, extra="forbid"):
    default_constructor: bool = Field(  # type: ignore
        default=True,
        alias=AliasChoices("default-constructor", "default_constructor"))
    wrapper_name: Optional[str] = Field(  # type: ignore
        default=None, alias=AliasChoices("wrapper-name", "wrapper_name"))
    wrapper_has_params: bool = Field(  # type: ignore
        default=True,
        alias=AliasChoices("wrapper-has-params", "wrapper_has_params"))
    unique_name: Optional[str] = Field(  # type: ignore
        default=None,
        alias=AliasChoices("unique-name", "unique_name"),
        description=
        "Reflection entry name unique in the scope of the class/namespace -- for wrapper backends that don't support overloading"
    )
    backend: GenTuBackendParams = Field(default_factory=GenTuBackendParams)
    function_api: Optional[GenTuFunctionApiTraits] = Field(  # type: ignore
        default=None,
        alias=AliasChoices("function-api", "function_api"),
        description="Reflection entity has a function/method API")
    type_api: Optional[GenTuTypeApiTraits] = Field(
        default=None, alias="type-api", description="Reflection entity has a type API")

    def isAcceptedBackend(self, backend: str) -> bool:
        return len(
            self.backend.target_backends) == 0 or backend in self.backend.target_backends


@beartype
@dataclass
class GenTuIdent:
    type: QualType
    name: str
    value: Optional[Union[BlockId, str]] = None
    OriginName: Optional[str] = None


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
    OriginName: Optional[str] = None
    reflectionParams: GenTuReflParams = field(default_factory=lambda: GenTuReflParams())


@beartype
@dataclass
class GenTuEnumField:
    name: str
    doc: GenTuDoc
    value: Optional[int] = None
    OriginName: Optional[str] = None


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
    reflectionParams: GenTuReflParams = field(default_factory=GenTuReflParams)
    OriginName: Optional[str] = None
    IsDescribedEnum: bool = False

    def __str__(self) -> str:
        return f"GenTuEnum({self.name.format()})"

    def format(self, dbgOrigin: bool = False) -> str:
        return "enum " + self.name.format(dbgOrigin=dbgOrigin)


@beartype
@dataclass
class GenTuFunction:
    result: Optional[QualType] = None
    name: str = ""
    doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))
    params: List[GenTuParam] = field(default_factory=list)
    arguments: List[GenTuIdent] = field(default_factory=list)
    impl: Optional[Union[str, BlockId]] = None
    isVirtual: bool = False
    isConst: bool = False
    isStatic: bool = False
    isPureVirtual: bool = False
    isOverride: bool = False
    parentClass: Optional['GenTuStruct'] = None
    original: Optional[Path] = None
    spaces: List[QualType] = field(default_factory=list)
    isExposedForWrap: bool = True
    OriginName: Optional[str] = None

    IsConstructor: bool = False

    reflectionParams: GenTuReflParams = field(default_factory=GenTuReflParams)

    def get_full_qualified_name(self) -> QualType:
        return QualType(name=self.name, Spaces=self.spaces)

    def get_function_type(self, Class: Optional[QualType] = None) -> QualType:
        return QualType(
            func=QualType.Function(
                ReturnTy=self.result,
                Args=[A.type for A in self.arguments],
                Class=Class,
                IsConst=self.isConst,
            ),
            Kind=QualTypeKind.FunctionPtr,
        )

    def format(self) -> str:
        assert self.result, "Missing function return type"
        return "function %s %s(%s)" % (self.result.format(), self.name, ", ".join(
            [Arg.name + " " + Arg.type.format() for Arg in self.arguments]))


@beartype
@dataclass
class GenTuInclude:
    what: str
    isSystem: bool = False
    absolutePath: Optional[str] = None


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
    isExposedForWrap: bool = True
    reflectionParams: GenTuReflParams = field(default_factory=GenTuReflParams)
    OriginName: Optional[str] = None


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
    doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))
    fields: List[GenTuField] = field(default_factory=list)
    methods: List[GenTuFunction] = field(default_factory=list)
    bases: List[QualType] = field(default_factory=list)
    nested: List[GenTuEntry] = field(default_factory=list)
    IsForwardDecl: bool = False
    IsAbstract: bool = False
    has_name: bool = True
    original: Optional[Path] = field(default=None)
    GenDescribeMethods: bool = False
    GenDescribeFields: bool = True
    reflectionParams: GenTuReflParams = field(default_factory=GenTuReflParams)
    IsExplicitInstantiation: bool = False
    IsTemplateRecord: bool = False
    ExplicitTemplateParams: List[QualType] = field(default_factory=list)
    OriginName: Optional[str] = None
    IsDescribedRecord: bool = False

    def __str__(self) -> str:
        return f"GenTuStruct({self.name.format()})"

    def declarationQualName(self) -> QualType:
        return self.name.model_copy(update=dict(Parameters=self.ExplicitTemplateParams))

    def format(self, dbgOrigin: bool = False) -> str:
        return "record " + self.name.format(dbgOrigin=dbgOrigin)

    def getGetitemMethods(self) -> List[GenTuFunction]:
        return [
            m for m in self.methods if m.reflectionParams.function_api and
            m.reflectionParams.function_api.is_get_item
        ]

    def getBeginEndPair(self) -> Optional[Tuple[GenTuFunction, GenTuFunction]]:
        begin_func: Optional[GenTuFunction] = None
        end_func: Optional[GenTuFunction] = None

        for m in self.methods:
            if m.name == "begin":
                begin_func = m

            elif m.name == "end":
                end_func = m

        if begin_func and end_func:
            return (begin_func, end_func)

        else:
            return None


@beartype
@dataclass
class GenTuTypeGroup:
    types: List[GenTuStruct]
    enumName: QualType
    variantName: QualType
    iteratorMacroName: Optional[str] = None
    variantField: str = "data"
    variantValue: Optional[str] = None
    kindGetter: str = "getKind"
    meta: Dict[str, Any] = field(default_factory=dict)


@beartype
@dataclass
class GenTuNamespace:
    name: QualType
    entries: Sequence[GenTuEntry]


GenTuUnion: TypeAlias = Union[GenTuStruct, GenTuEnum, GenTuTypedef, GenTuFunction]


@beartype
@dataclass
class GenTypeMap:
    entries: List[GenTuUnion] = field(default_factory=list)
    name_to_index: defaultdict[str, List[int]] = field(
        default_factory=lambda: defaultdict(list))
    qual_hash_to_index: defaultdict[int, List[int]] = field(
        default_factory=lambda: defaultdict(list))

    def is_typedef(self, t: QualType) -> bool:
        decl = self.get_one_type_for_qual_name(t)
        return bool(decl and isinstance(decl, GenTuTypedef))

    def get_underlying_type(self, t: QualType) -> Optional[QualType]:
        decl = self.get_one_type_for_qual_name(t)
        if decl and isinstance(decl, GenTuTypedef):
            return decl.base

        else:
            return None

    def get_types_for_name(self, name: str) -> List[GenTuUnion]:
        return [self.entries[i] for i in self.name_to_index.get(name, [])]

    def get_types_for_qual_name(self, name: QualType) -> List[GenTuUnion]:
        return [
            self.entries[i] for i in self.qual_hash_to_index.get(name.qual_hash(), [])
        ]

    def get_struct_for_qual_name(self, name: QualType) -> Optional[GenTuStruct]:
        def_types = self.get_types_for_qual_name(name)
        if 0 < len(def_types):
            assert len(def_types) == 1, f"{t} maps to more than one definitive type"

            if isinstance(def_types[0], GenTuStruct):
                return def_types[0]

            else:
                return None

        else:
            return None

    def get_wrapper_type(self, t: QualType) -> Optional[str]:
        struct = self.get_struct_for_qual_name(t)
        return struct and struct.reflectionParams.wrapper_name  # type: ignore

    def is_known_type(self, t: QualType) -> bool:
        return t.qual_hash() in self.qual_hash_to_index

    def get_one_type_for_qual_name(self, name: QualType) -> Optional[GenTuUnion]:
        items = self.get_types_for_qual_name(name)
        if 0 < len(items):
            return items[0]

        else:
            return None

    def get_one_type_for_name(self, name: str) -> Optional[GenTuUnion]:
        items = self.get_types_for_name(name)
        for item in items:
            if isinstance(item, GenTuStruct) and not item.IsExplicitInstantiation:
                return item

        if 0 < len(items):
            return items[0]

        else:
            return None

    def add_type(self, typ: GenTuUnion) -> None:
        qual_name = None

        match typ:
            case GenTuStruct():
                qual_name = typ.declarationQualName()

                # if typ.reflectionParams.wrapper_name:
                #     log(CAT).info(f"{qual_name} has explicit wrapper")

            case GenTuEnum():
                qual_name = typ.name.model_copy()

            case GenTuTypedef():
                qual_name = typ.name.model_copy()
                # log(CAT).info(f"Adding typedef for {qual_name}")

            case _:
                raise ValueError(f"{type(typ)} is not a type definition")

        qual_hash = qual_name.qual_hash()
        new_index = len(self.entries)
        if qual_hash in self.qual_hash_to_index:
            return
            # raise ValueError(f"Qual type {qual_name} is already mapped to {self.qual_hash_to_index[qual_hash]}")

        self.qual_hash_to_index[qual_hash].append(new_index)
        self.name_to_index[qual_name.name].append(new_index)

        self.entries.append(typ)

    @staticmethod
    def FromTypes(types: Sequence[GenTuUnion]) -> "GenTypeMap":
        # log(CAT).info("Called `fromType`", stack_info=True)
        result = GenTypeMap()

        def callback(obj: Any) -> None:
            nonlocal result
            match obj:
                case GenTuStruct() | GenTuTypedef():
                    result.add_type(obj)

        context: List[Any] = []
        iterate_object_tree(types, context, pre_visit=callback)
        return result


@beartype
@dataclass
class GenTu:
    path: str
    entries: Sequence[GenTuEntry]
    clangFormatGuard: bool = True


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

    def __exit__(self, exc_type: object, exc_val: object, exc_tb: object) -> None:
        self.conv.context.pop()

    def __enter__(self) -> "GenConverterWithContext":
        self.conv.context.append(self.typ)
        return self


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
        decl = FunctionParams(
            ResultTy=func.result,
            Name=func.name,
            doc=self.convertDoc(func.doc),
        )

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
        if tu.clangFormatGuard:
            decls.append(self.ast.Comment(["clang-format off"]))
        for item in tu.entries:
            decls += self.convertWithToplevel(item)

        if tu.clangFormatGuard:
            decls.append(self.ast.Comment(["clang-format on"]))

        return self.ast.TranslationUnit(decls)

    def convertTypedef(self, typedef: GenTuTypedef) -> BlockId:
        return self.ast.Using(
            UsingParams(newName=typedef.name.name, baseType=typedef.base))

    def convertMethod(self, method: GenTuFunction) -> MethodDeclParams:
        return MethodDeclParams(
            Params=self.convertFunction(method),
            isStatic=method.isStatic,
            isConst=method.isConst,
            isVirtual=method.isVirtual,
            isOverride=method.isOverride,
        )

    def convertStruct(self, record: GenTuStruct) -> BlockId:
        params = RecordParams(
            name=record.name,
            doc=self.convertDoc(record.doc),
            bases=record.bases,
        )

        with GenConverterWithContext(self, record.name):
            for type in record.nested:
                for sub in self.convert(type):
                    params.nested.append(sub)

            for member in record.fields:
                params.members.append(
                    RecordField(
                        params=ParmVarParams(
                            type=member.type if member.type else QualType.ForName("void"),
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
                params.members.append(self.convertMethod(method))

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
                ]) for method in record.methods if method.result is not None
            ]

            if record.GenDescribeFields or record.GenDescribeMethods:
                params.nested.append(
                    self.ast.XCall(
                        "BOOST_DESCRIBE_CLASS",
                        [
                            self.ast.string(record.name.name),
                            self.ast.pars(
                                self.ast.csv([B.name for B in record.bases], False)),
                            self.ast.pars(self.ast.string("")),
                            self.ast.pars(self.ast.string("")),
                            self.ast.pars(
                                self.ast.csv(
                                    cond(record.GenDescribeFields, fields, []) +
                                    cond(record.GenDescribeMethods, methods, []),
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
            ResultTy=t_opt(entry.name),
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

    def convertNamespace(self, space: GenTuNamespace) -> BlockId:
        result = self.ast.b.stack([])
        with GenConverterWithContext(self, space.name.asNamespace()):
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
def n_hstd() -> QualType:
    return QualType(name="hstd", isNamespace=True)


@beartype
def n_hstd_ext() -> QualType:
    return QualType(name="ext", isNamespace=True, Spaces=[n_hstd()])


@beartype
def n_org() -> QualType:
    return QualType(name="org", isNamespace=True)


def n_org_algo() -> QualType:
    return QualType(
        name="algo",
        isNamespace=True,
        meta=dict(isSemNamespace=True),
        Spaces=[n_org()],
    )


@beartype
def t_opt(arg: QualType) -> QualType:
    return QualType(name="Opt", Parameters=[arg], Spaces=[n_hstd()])


@beartype
def t_vec(arg: QualType) -> QualType:
    return QualType(name="Vec", Parameters=[arg], Spaces=[n_hstd()])


@beartype
def n_sem() -> QualType:
    return QualType(
        name="sem",
        isNamespace=True,
        meta=dict(isSemNamespace=True),
        Spaces=[n_org()],
    )


@beartype
def n_imm() -> QualType:
    return QualType(
        name="imm",
        isNamespace=True,
        meta=dict(isSemNamespace=True),
        Spaces=[n_org()],
    )


@beartype
def t_org(name: str) -> QualType:
    return QualType(
        name=name,
        meta=dict(isOrgType=True),
        # dbg_origin="t_org",
    )


@beartype
def t(
    name: str | QualType,
    namespaces: List[QualType] = [],
    isOrgType: bool = False,
) -> QualType:
    if isinstance(name, QualType):
        return name.model_copy(update=dict(Spaces=namespaces))

    else:
        return QualType(name=name, Spaces=namespaces)


@beartype
def t_namespace(name: str | QualType) -> QualType:
    return t(name).asNamespace()


@beartype
def t_space(name: str | QualType, Spaces: List[QualType]) -> QualType:
    if isinstance(name, QualType):
        return name.model_copy(update=dict(Spaces=Spaces))
    else:
        return QualType(name=name, Spaces=Spaces)


@beartype
def t_nest(name: Union[str, QualType], Spaces: List[QualType] = []) -> QualType:
    return t_space(name, [n_sem()] + Spaces)


@beartype
def t_id(target: Optional[Union[QualType, str]] = None) -> QualType:
    org_t = target if target else t_nest(t_org("Org"))
    org_t = org_t if isinstance(org_t, QualType) else t_nest(t_org(org_t))

    return (QualType(name="SemId", Parameters=[org_t], Spaces=[n_sem()]))


@beartype
def get_base_map(expanded: Sequence[GenTuUnion]) -> GenTypeMap:
    return GenTypeMap.FromTypes(expanded)


@beartype
def filter_walk_scope(iterate_context: List[Any]) -> List[QualType]:
    scope: List[QualType] = []

    for s in iterate_context:
        match s:
            case GenTuStruct():
                scope.append(s.name)

            case GenTuNamespace():
                scope.append(QualType.ForName(s.name.name))

    return scope


@beartype
def get_type_base_fields(
    value: GenTuStruct,
    base_map: GenTypeMap,
) -> List[GenTuField]:
    fields = []
    for base_sym in value.bases:
        base: Optional[GenTuStruct] = base_map.get_one_type_for_name(
            base_sym.name)  # type: ignore
        if base:
            fields.extend(base.fields)
            fields.extend(get_type_base_fields(base, base_map))

    return fields


@beartype
def get_base_list(
    value: GenTuStruct,
    base_map: GenTypeMap,
) -> List[QualType]:
    fields = []

    def aux(typ: QualType) -> List[QualType]:
        result: List[QualType] = [typ]
        base: Optional[GenTuStruct] = base_map.get_one_type_for_name(
            typ.name)  # type: ignore
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


@beartype
@dataclass
class TypeSpecialization():
    used_type: QualType
    bind_name: str
    std_type: Optional[QualType] = None

    def getFlatUsed(self) -> str:
        return "".join(self.used_type.flatQualName())


IGNORED_NAMESPACES = ["sem", "org", "hstd", "ext", "algo", "bind", "python", "imm"]


@beartype
def sanitize_ident(
    name: str,
    lang_keywords: Set[str],
    map_operator: Optional[Callable[[str], str]] = None,
) -> str:

    # Operator mappings from C++ to Python
    operator_mappings = {
        # Comparison operators
        "operator==": "eq",
        "operator!=": "ne",
        "operator>": "gt",
        "operator<": "lt",
        "operator>=": "ge",
        "operator<=": "le",

        # Arithmetic operators
        "operator+": "add",
        "operator-": "sub",
        "operator*": "mul",
        "operator/": "truediv",
        "operator%": "mod",
        "operator//": "floordiv",
        "operator**": "pow",

        # Unary operators
        "operator++": "next",  # Note: not exact equivalent
        "operator--": "prev",  # Note: not exact equivalent
        "operator-@": "neg",  # Unary minus
        "operator+@": "pos",  # Unary plus
        "operator~": "invert",  # Bitwise NOT

        # Bitwise operators
        "operator&": "and",
        "operator|": "or",
        "operator^": "xor",
        "operator<<": "lshift",
        "operator>>": "rshift",

        # Assignment operators (in-place operations)
        "operator+=": "iadd",
        "operator-=": "isub",
        "operator*=": "imul",
        "operator/=": "itruediv",
        "operator%=": "imod",
        "operator&=": "iand",
        "operator|=": "ior",
        "operator^=": "ixor",
        "operator<<=": "ilshift",
        "operator>>=": "irshift",

        # Subscript operator
        "operator[]": "getitem",

        # Function call operator
        "operator()": "call",

        # Conversion operators
        "operator bool": "bool",
        "operator int": "int",
        "operator float": "float",
        "operator str": "str",

        # Smart pointer operations
        "operator*": "deref",  # Dereference (conflicts with multiply)
        "operator->": "arrow",  # Arrow operator (no direct Python equivalent)

        # Memory management
        "operator new": "new",
        "operator delete": "del",

        # Stream operators
        "operator<<": "lshift",  # Also used for stream insertion
        "operator>>": "rshift",  # Also used for stream extraction

        # Comma operator
        "operator,": "comma",  # No direct Python equivalent
    }

    if map_operator and name in operator_mappings:
        tmp_res = map_operator(name)
        if tmp_res:
            return tmp_res

        else:
            return f"__{operator_mappings[name]}__"

    elif name in operator_mappings:
        return f"__{operator_mappings[name]}__"

    # Check if it's a Python keyword
    if name in lang_keywords:
        return name + "_"

    # Handle special characters
    # Replace invalid characters with underscores
    result = ""
    for char in name:
        if char.isalnum() or char == '_':
            result += char
        else:
            result += '_'

    # Ensure the identifier doesn't start with a digit
    if result and result[0].isdigit():
        result = '_' + result

    # Ensure the identifier isn't empty
    if not result:
        result = '_empty_'

    return result


@beartype
def collect_type_specializations(entries: List[GenTuUnion],
                                 base_map: GenTypeMap) -> List[TypeSpecialization]:
    res = []

    @beartype
    def name_bind(Typ: QualType) -> str:
        return Typ.getBindName(
            withParams=True,
            ignored_spaces=IGNORED_NAMESPACES,
            rename_map={
                ("immer", "box"): "ImmBox",
                ("immer", "flex_vector"): "ImmFlexVector",
                ("immer", "map"): "ImmMap",
            },
        )

    type_use_context: List[Any] = []
    seen_types: Set[int] = set()

    def record_specializations(value: Any) -> None:
        nonlocal type_use_context
        if isinstance(value, QualType):

            def rec_type(T: QualType) -> None:

                def rec_drop(T: QualType) -> QualType:
                    return T.model_copy(update=dict(
                        isConst=False,
                        RefKind=ReferenceKind.NotRef,
                        ptrCount=0,
                        isNamespace=False,
                        meta=dict(),
                        Spaces=[rec_drop(S) for S in T.Spaces],
                        Parameters=[rec_drop(P) for P in T.Parameters],
                    ))

                T = rec_drop(T)

                if hash(T) in seen_types:
                    return

                else:
                    seen_types.add(hash(T))

                if T.name in [
                        "Vec",
                        "UnorderedMap",
                        "IntSet",
                        "vector",
                        "flex_vector",
                        "map",
                        "box",
                        "Opt",
                        "optional",
                ]:
                    std_type: Optional[str] = {
                        "Vec": "vector",
                        "UnorderedMap": "unordered_map",
                        "IntSet": "int_set",
                        "vector": "imm_vector",
                        "flex_vector": "imm_flex_vector",
                        "map": "imm_map",
                        "box": "imm_box",
                    }.get(T.name, None)

                    if T.name in ["Vec", "UnorderedMap"]:
                        assert std_type
                        if T.name in ["Vec", "vector", "box", "flex_vector", "IntSet"]:
                            assert len(T.Parameters) == 1, T.format(dbgOrigin=True)

                        elif T.name in ["UnorderedMap", "map"]:
                            assert len(T.Parameters) == 2, T.format(dbgOrigin=True)

                        stdvec_t = QualType.ForName(
                            std_type,
                            Spaces=[QualType.ForName("std")],
                            Parameters=T.Parameters,
                        )

                        res.append(
                            TypeSpecialization(
                                std_type=stdvec_t,
                                used_type=T,
                                bind_name=name_bind(T),
                            ))

                    else:
                        res.append(
                            TypeSpecialization(
                                used_type=T,
                                bind_name=name_bind(T),
                            ))

                else:
                    for P in T.Parameters:
                        rec_type(P)

            if base_map.is_typedef(value):
                rec_type(base_map.get_underlying_type(value))  # type: ignore

            else:
                rec_type(value)

    iterate_object_tree(
        entries,
        type_use_context,
        pre_visit=record_specializations,
    )

    return res
