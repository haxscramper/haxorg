from collections import defaultdict
from dataclasses import dataclass, field
from enum import Enum
import itertools
from pathlib import Path

from beartype import beartype
from beartype.typing import (
    Any,
    Callable,
    Dict,
    List,
    Literal,
    Optional,
    Sequence,
    Set,
    Tuple,
    TypeAlias,
    Union,
)
from py_haxorg.astbuilder.astbuilder_utils import pascal_case
from py_haxorg.layout.wrap import BlockId
from py_scriptutils.algorithm import iterate_object_tree
from pydantic import AliasChoices, BaseModel, Field

CAT = __name__

DEBUG_TYPE_ORIGIN = False


class QualTypeKind(str, Enum):
    RegularType = "RegularTyp0e"
    FunctionPtr = "FunctionPtr"
    MethodPtr = "MethodPtr"
    Array = "Array"
    TypeExpr = "TypeExpr"

    def __rich_repr__(self) -> Any:
        yield self.name


class ReferenceKind(str, Enum):
    NotRef = "NotRef"
    LValue = "LValue"
    RValue = "RValue"

    def __rich_repr__(self) -> Any:
        yield self.name

    def __repr__(self) -> str:
        return self.name


@beartype
class QualType(BaseModel, extra="forbid"):
    name: str = ""
    Parameters: List['QualType'] = Field(default_factory=list)
    Spaces: List['QualType'] = Field(default_factory=list)
    isNamespace: bool = False

    isConst: bool = False
    ptrCount: int = 0
    RefKind: ReferenceKind = ReferenceKind.NotRef
    dbg_origin: str = Field(default="", exclude=True)
    verticalParamList: bool = Field(default=False, exclude=True)
    isBuiltin: bool = Field(default=False)
    #: Prefix the type with leading `::` to refer to the global namespace
    isGlobalNamespace: bool = Field(default=False)
    IsPackExpansion: bool = Field(default=False)

    expr: Optional[str] = None
    Kind: QualTypeKind = QualTypeKind.RegularType

    meta: Dict[str, Any] = Field(default={})

    def getBindName(
            self,
            ignored_spaces: List[str] = [],
            withParams: bool = False,
            rename_map: Dict[Tuple[str, ...], str] = dict(),
    ) -> str:

        def aux(t: QualType) -> str:
            res = ""

            flat = tuple(t.flatQualName())

            if flat in rename_map:
                res += rename_map[flat]

            else:
                for N in t.Spaces:
                    res += aux(N)

                if t.name not in ignored_spaces:
                    res += pascal_case(t.name)

            if withParams and 0 < len(t.Parameters):
                res += "Of"
                res += "".join([aux(T) for T in t.Parameters])

            return res

        return aux(self)

    def par0(self) -> Optional["QualType"]:
        if 0 < len(self.Parameters):
            return self.Parameters[0]

        else:
            return None

    def par1(self) -> Optional["QualType"]:
        if 1 < len(self.Parameters):
            return self.Parameters[1]

        else:
            return None

    def test(self, met: str) -> bool:
        return bool(self.meta.get(met, False))

    def isOrgType(self) -> bool:
        return self.meta.get("isOrgType", False)

    @staticmethod
    def ForName(name: str, **args: Any) -> "QualType":
        return QualType(name=name, **args)

    @staticmethod
    def ForExpr(expr: str, **args: Any) -> "QualType":
        return QualType(expr=expr, Kind=QualTypeKind.TypeExpr, **args)

    def flatten(self) -> "QualType":
        return self.model_copy(update=dict(Spaces=self.flatQualScope()))

    def withDbgOrigin(self, msg: str) -> "QualType":
        return self.model_copy(update=dict(dbg_origin=self.dbg_origin + msg))

    def asConstRef(self) -> "QualType":
        return self.model_copy(update=dict(isConst=True, RefKind=ReferenceKind.LValue))

    def asConstPtr(self) -> "QualType":
        return self.model_copy(update=dict(isConst=True, ptrCount=1))

    def asRef(self) -> "QualType":
        return self.model_copy(update=dict(isConst=False, RefKind=ReferenceKind.LValue))

    def flatQualScope(self) -> List["QualType"]:
        "Flatten fully qualified name for the type"

        def aux(it: QualType) -> List[QualType]:
            return list(itertools.chain(
                *(aux(s) for s in it.Spaces))) + [it.withoutAllScopeQualifiers()]

        return list(itertools.chain(*(aux(s) for s in self.Spaces)))

    def flatQualFullName(self) -> List["QualType"]:
        return self.flatQualScope() + [self.withoutAllScopeQualifiers()]

    def flatQualNameNoNamespace(self) -> List["QualType"]:
        "Return qualified name for the type, dropping all namespace parents (but leaving non-namespaces)"
        return [it for it in self.flatQualScope() if not it.isNamespace]

    def asPtr(self, ptrCount: int = 1) -> "QualType":
        return self.model_copy(update=dict(ptrCount=ptrCount))

    def withGlobalSpace(self) -> "QualType":
        return self.model_copy(update=dict(isGlobalNamespace=True))

    def flatSpaceNames(self) -> List[str]:
        "Get flat list of names for fully qualified type"

        def aux(Typ: QualType) -> List[str]:
            res: List[str] = []
            for S in Typ.Spaces:
                res += aux(S)

            res += [Typ.name]
            return res

        return list(itertools.chain(*[aux(S) for S in self.Spaces]))

    def flatQualName(self) -> List[str]:
        return self.flatSpaceNames() + [self.name]

    def asSpaceFor(self, other: 'QualType') -> 'QualType':
        return other.model_copy(update=dict(
            Spaces=self.Spaces +
            [self.model_copy(update=dict(
                Spaces=[],
                isGlobalNamespace=False,
            ))],
            isGlobalNamespace=self.isGlobalNamespace,
        ))

    def withTemplateParams(self, Params: List["QualType"]) -> "QualType":
        return self.model_copy(update=dict(Parameters=Params))

    def withWrapperType(self, name: Union[str, "QualType"]) -> "QualType":
        if isinstance(name, str):
            return QualType(name=name, Parameters=[self])

        else:
            return name.model_copy(update=dict(Parameters=[self]))

    def withExtraSpace(self, name: Union['QualType', str]) -> 'QualType':
        flat = self.flatten()
        added: QualType = QualType(name=name) if isinstance(name, str) else name
        assert isinstance(added, QualType), type(added)
        return flat.model_copy(update=dict(Spaces=[added] + flat.Spaces))

    def withoutCVRef(self) -> "QualType":
        return self.model_copy(update=dict(
            isConst=False,
            RefKind=ReferenceKind.NotRef,
        ))

    def withoutSpace(self, name: str) -> 'QualType':
        flat = self.flatten()
        return flat.model_copy(update=dict(
            Spaces=[S for S in flat.Spaces if S.name != name]))

    def withoutAllScopeQualifiers(self) -> 'QualType':
        return self.model_copy(update=dict(Spaces=[]))

    def withChangedSpace(self, name: Union['QualType', str]) -> 'QualType':
        """Change the namespace of the qualified type from the current list to the [name]
        Resulting type will have only [name] as the space"""
        added: QualType = QualType(name=name) if isinstance(name, str) else name
        assert isinstance(added, QualType), type(added)
        return self.flatten().model_copy(update=dict(Spaces=[added]))

    def isArray(self) -> bool:
        return self.Kind == QualTypeKind.Array

    def isFunction(self) -> bool:
        return self.Kind == QualTypeKind.FunctionPtr

    def isPrimitive(self) -> bool:
        return self.isBuiltin or self.name in [
            "size_t",
            "uint32_t",
            "uint16_t",
            "int32_t",
            "int64_t",
            "uint64_t",
        ]

    @beartype
    class Function(BaseModel, extra="forbid"):
        ReturnTy: Optional['QualType']
        Args: List['QualType']
        Ident: str = ""
        Class: Optional['QualType'] = None
        IsConst: bool = False

    func: Optional[Function] = None

    def flat_repr_flatten(self, with_modifiers: bool = True) -> Any:
        ## NOTE: Used for hashing, order of append is important, it must match the actual representation,
        ## otherwise namespace nesting might throw off the hashing results, and make `[org::[sem::[Id]]]`
        ## not match with the type `[org::sem::[Id]]` because of how namespaces are walked.
        result = []

        def aux(T: QualType) -> None:
            for S in T.Spaces:
                aux(S)

            for P in T.Parameters:
                aux(P)

            if with_modifiers:
                result.append((
                    T.name,
                    T.isConst,
                    T.ptrCount,
                    T.RefKind,
                ))

            else:
                result.append((T.name,))  # type: ignore[arg-type]

        aux(self)
        return tuple(result)

    def get_recursive_uses(self) -> List["QualType"]:
        result: List[QualType] = []
        match self.Kind:
            case QualTypeKind.RegularType:
                result.append(self)
                for p in self.Parameters:
                    result.extend(p.get_recursive_uses())

            case QualTypeKind.FunctionPtr:
                assert self.func
                for arg in self.func.Args:
                    result.extend(arg.get_recursive_uses())

            case QualTypeKind.Array:
                for p in self.Parameters:
                    result.extend(p.get_recursive_uses())

            case QualTypeKind.TypeExpr:
                pass

            case _:
                assert False, self.Kind

        return result

    def qual_hash(self) -> int:
        return hash(self.flat_repr_flatten(with_modifiers=False))

    def __hash__(self) -> int:
        return hash(self.flat_repr_flatten())

    def __repr__(self) -> str:
        return self.format()

    def __str__(self) -> str:
        return self.format()

    def format_native(
        self,
        with_cvref: bool = True,
        max_depth: Optional[int] = None,
        max_params: Optional[int] = None,
        max_param_size: Optional[int] = None,
    ) -> str:

        def aux(Typ: QualType, depth: int) -> str:
            if max_depth and max_depth < depth:
                return ""

            if with_cvref:
                cvref = "{const}{ptr}{ref}".format(
                    const=" const" if Typ.isConst else "",
                    ptr=("*" * Typ.ptrCount),
                    ref={
                        ReferenceKind.LValue: "&",
                        ReferenceKind.RValue: "&&",
                        ReferenceKind.NotRef: ""
                    }[Typ.RefKind],
                )
            else:
                cvref = ""

            spaces = "".join([f"{aux(S, depth=depth + 1)}::" for S in Typ.Spaces])

            match Typ.Kind:
                case QualTypeKind.FunctionPtr:
                    assert Typ.func
                    result = "{result}({args})(*)".format(
                        result=aux(Typ.func.ReturnTy or QualType.ForName("void"),
                                   depth=depth + 1),
                        args=", ".join([aux(T, depth=depth + 1) for T in Typ.func.Args]),
                    )

                case QualTypeKind.Array:
                    result = "{first}[{expr}]{cvref}".format(
                        first=aux(Typ.Parameters[0], depth=depth + 1),
                        expr=aux(Typ.Parameters[1], depth=depth +
                                 1) if 1 < len(Typ.Parameters) else "",
                        cvref=cvref,
                    )

                case QualTypeKind.RegularType:
                    if max_params:
                        params_list = Typ.Parameters[:min(len(Typ.Parameters), max_params
                                                         )]

                    else:
                        params_list = Typ.Parameters

                    params_format = [aux(T, depth=depth + 1) for T in params_list]
                    if max_param_size:
                        params_format = [
                            p[:min(len(p), max_param_size)] for p in params_format
                        ]

                    result = "{spaces}{name}{args}{cvref}".format(
                        name=Typ.name or "?",
                        args="<{}>".format(", ".join(params_format))
                        if params_format else "",
                        cvref=cvref,
                        spaces=spaces,
                    )

                case QualTypeKind.TypeExpr:
                    result = f"{Typ.expr}"

                case _:
                    assert False, Typ.Kind

            return result

        # return self.model_dump_json() + "  --- " + aux(self)
        return aux(self, depth=0)
        # return str(self.flat_repr_flatten())

    def format(self, dbgOrigin: bool = DEBUG_TYPE_ORIGIN) -> str:

        def aux(Typ: QualType) -> str:
            cvref = "{const}{ptr}{ref}".format(
                const=" const" if Typ.isConst else "",
                ptr=("*" * Typ.ptrCount),
                ref={
                    ReferenceKind.LValue: "&",
                    ReferenceKind.RValue: "&&",
                    ReferenceKind.NotRef: ""
                }[Typ.RefKind],
            )

            origin = f" FROM:{Typ.dbg_origin}" if (dbgOrigin and Typ.dbg_origin) else ""

            spaces = "".join([f"{aux(S)}::" for S in Typ.Spaces])
            # if spaces:
            #     spaces = f"{spaces}"

            match Typ.Kind:
                case QualTypeKind.FunctionPtr:
                    assert Typ.func
                    assert Typ.func.ReturnTy, "Missing return type for function pointer"
                    result = "{spaces}FUNC:{origin}({args})".format(
                        spaces=spaces,
                        origin=aux(Typ.func.ReturnTy),
                        args=", ".join([aux(T) for T in Typ.func.Args]),
                    )

                case QualTypeKind.Array:
                    result = "{spaces}ARR:{first}[{expr}]{cvref}{origin}".format(
                        first=aux(Typ.Parameters[0]),
                        expr=aux(Typ.Parameters[1]) if 1 < len(Typ.Parameters) else "",
                        cvref=cvref,
                        origin=origin,
                        spaces=spaces,
                    )

                case QualTypeKind.RegularType:
                    result = "{spaces}REC:({name}{args}{cvref}{origin})".format(
                        name=Typ.name or "?",
                        args="<{}>".format(", ".join([aux(T) for T in Typ.Parameters]))
                        if Typ.Parameters else "",
                        cvref=cvref,
                        origin=origin,
                        spaces=spaces,
                        # namespace=("NSP" if Typ.isNamespace else ""),
                    )

                case QualTypeKind.TypeExpr:
                    result = f"[E:{Typ.expr}]"

                case _:
                    assert False, Typ.Kind

            return "{" + result + "}"

        # return self.model_dump_json() + "  --- " + aux(self)
        return aux(self)
        # return str(self.flat_repr_flatten())

    def asNamespace(self, is_namespace: bool = True) -> "QualType":
        self.isNamespace = is_namespace
        return self

    def withVerticalParams(self, params: bool = True) -> "QualType":
        self.verticalParamList = params
        return self

    @classmethod
    def from_name(cls, name: str) -> "QualType":
        return cls(name=name)

    @classmethod
    def from_name_and_parameters(cls, name: str,
                                 parameters: List['QualType']) -> "QualType":
        return cls(name=name, Parameters=parameters)

    @classmethod
    def from_spaces_and_name(cls, spaces: List[str], name: str) -> "QualType":
        return cls(name=name, Spaces=[cls.from_name(space) for space in spaces])


@beartype
@dataclass
class GenTuTemplateTypename:
    Placeholder: bool = False
    Variadic: bool = False
    Name: str = ""
    Nested: List['GenTuTemplateTypename'] = field(default_factory=list)
    Concept: Optional[str] = None


@beartype
@dataclass
class GenTuTemplateGroup:
    Params: List[GenTuTemplateTypename] = field(default_factory=list)


@beartype
@dataclass
class GenTuTemplateParams:
    Stacks: List[GenTuTemplateGroup] = field(default_factory=list)

    @staticmethod
    def FinalSpecialization() -> "GenTuTemplateParams":
        return GenTuTemplateParams(Stacks=[GenTuTemplateGroup()])


class StorageClass(Enum):
    None_ = 0
    Static = 1


@beartype
@dataclass
class GenTuParam:
    name: str


@beartype
class GenTuBackendPythonParams(BaseModel, extra="forbid"):
    "Extra parameters for python backend"
    holder_type: Optional[Literal["shared", "unique"]] = Field(
        alias="holder-type",
        default=None,
        description="Which holder type to use for python backend")


@beartype
class GenTuBackendWasmParams(BaseModel, extra="forbid"):
    "Extra parameters for WASM backend"
    holder_type: Optional[Literal["shared", "unique"] | str | QualType] = Field(
        alias="holder-type",
        default=None,
        description="Which type to use as a holder type for WASM")


@beartype
class GenTuBackendParams(BaseModel, extra="forbid"):
    """
    Optional parameters for the backend generation config.
    `[[refl]]` string parameter is parsed into JSON and this
    class describes the allowed schema for this JSON.
    """
    python: GenTuBackendPythonParams = Field(
        default_factory=GenTuBackendPythonParams,
        description="Additional wrapper options for python backend")
    wasm: GenTuBackendWasmParams = Field(
        default_factory=GenTuBackendWasmParams,
        description="Additional wrapper options for WASM backend")
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
    InitList: List[BlockId] = field(default_factory=list)

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
    isExposedForDescribe: bool = True
    reflectionParams: GenTuReflParams = field(default_factory=GenTuReflParams)
    OriginName: Optional[str] = None


@beartype
@dataclass
class GenTuStruct():
    """
    Intermediate representation of the C++ record
    """
    name: QualType
    doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))
    fields: List[GenTuField] = field(default_factory=list)
    "Field directly in the structure"
    methods: List[GenTuFunction] = field(default_factory=list)
    bases: List[QualType] = field(default_factory=list)
    nested: List[Union[
        GenTuEnum,
        "GenTuStruct",
        "GenTuTypeGroup",
        GenTuTypedef,
        GenTuPass,
    ]] = field(default_factory=list)
    "All extra elements in the class "
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
    TemplateParams: Optional[GenTuTemplateParams] = None

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
    """
    Intermediate representation of the C++ namespace block.
    """
    name: QualType
    entries: Sequence[Union[
        GenTuEnum,
        GenTuStruct,
        GenTuTypeGroup,
        GenTuFunction,
        "GenTuNamespace",
        GenTuInclude,
        GenTuTypedef,
        GenTuPass,
    ]]
    """
    Entries in the namespace. Note that each individual entry should have a
    fully qualified name with all the parent spaces in it, so this class
    is mainly used for the physical placement of elements.
    """


type GenTuEntry = GenTuEnum | GenTuStruct | GenTuTypeGroup | GenTuFunction | GenTuNamespace | GenTuInclude |  GenTuTypedef |    GenTuPass
type GenTuUnion = GenTuStruct | GenTuEnum | GenTuTypedef | GenTuFunction


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
    """
    Check if the input type is present in the type list.
    Check is performed by flat name, additional qualifications are not used.
    """
    return any(typ.flatQualName() == it.flatQualName() for it in enum_type_list)


@beartype
@dataclass
class TypeSpecialization():
    "Fixed type specialization used in the wrapped C++ code"
    used_type: QualType
    "Fully qualified underlying type in the specialization"
    bind_name: str
    "Flat name for the wrapper class"
    std_type: Optional[QualType] = None
    """
    Underlying standard library type that already has converters, binders
    and specialization.
    """

    def getFlatUsed(self) -> str:
        "Get flat joined name of the used type"
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
