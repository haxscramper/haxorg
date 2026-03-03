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
from py_haxorg.layout.wrap import BlockId
from py_scriptutils.algorithm import iterate_object_tree
from pydantic import AliasChoices, BaseModel, Field

CAT = __name__

DEBUG_TYPE_ORIGIN = False


class QualTypeKind(str, Enum):
    "Type of the fully qualified kind"
    RegularType = "RegularType"
    "Built-in or user-defined type for struct, class, union, enum"
    FunctionPtr = "FunctionPtr"
    "Pointer to function"
    MethodPtr = "MethodPtr"
    "Pointer to method"
    Array = "Array"
    "Constant or dynamic array type"
    TypeExpr = "TypeExpr"
    "Compile-time literal in template parameters"

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
    """
    Recursive structure representing a fully qualified type name for named types,
    or more complex variants like function signature etc.
    """
    name: str = ""
    Parameters: List["QualType"] = Field(default_factory=list)
    """
    List of template type parameters for the type. Depending on the type kind
    the parameters stored might be explicit template type parameters for the
    custom structure, or they might be used to store parameters for the array
    type.
    """
    Spaces: List["QualType"] = Field(default_factory=list)
    "List of parent namespaces"
    isNamespace: bool = False
    "Whether the entry itself is a namespace or a type"

    isConst: bool = False
    "Does type have a const annotation?"
    ptrCount: int = 0
    "How many pointer indirection annotations is on the type"
    RefKind: ReferenceKind = ReferenceKind.NotRef
    "is this type a L-Value/R-Value reference?"
    dbg_origin: str = Field(default="", exclude=True)
    "Extra field to put debug information about the type origin"
    verticalParamList: bool = Field(default=False, exclude=True)
    isBuiltin: bool = Field(default=False)
    "Whether the qualified type represents a built-in one"
    isGlobalNamespace: bool = Field(default=False)
    "Prefix the type with leading `::` to refer to the global namespace"
    IsPackExpansion: bool = Field(default=False)
    "Is this type an expansion of variadic template type parameter"

    expr: Optional[str] = None
    "Expression text for the literal value"
    Kind: QualTypeKind = QualTypeKind.RegularType
    "Kind of the qualified type"

    @beartype
    class Function(BaseModel, extra="forbid"):
        "Pointer to function signature"
        ReturnTy: Optional['QualType']
        "Type of the function return type"
        Args: List['QualType']
        "Types of the function arguments"
        Class: Optional['QualType'] = None
        "Type of the method's class"
        IsConst: bool = False
        "For const methods"

    func: Optional[Function] = None
    "Typed representation of the pointer-to-function type"

    meta: Dict[str, Any] = Field(default={})
    "Extra qualified type metadata"

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

    def flatQualNameWithParams(self) -> List:
        """
        Generate recursively nested list of the type names for spaces and parameters:

        ```
        std::optional<T> -> ["std", "optional", ["T"]]
        std::unordered_map<int, std::map<int, char>> -> ["std", "unordered", [["int"], ["std", "map", [["int"], ["char"]]]]
        ```
        """
        return self.flatQualName() + [[P.flatQualNameWithParams()]
                                      for P in self.Parameters]

    def asSpaceFor(self, other: "QualType") -> "QualType":
        "Use the current type as a wrapper space for other type"
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

    def withExtraSpace(self, name: Union["QualType", str]) -> "QualType":
        "Return copy with prepended space"
        flat = self.flatten()
        added: QualType = QualType(name=name) if isinstance(name, str) else name
        assert isinstance(added, QualType), type(added)
        return flat.model_copy(update=dict(Spaces=[added] + flat.Spaces))

    def withoutCVRef(self) -> "QualType":
        return self.model_copy(update=dict(
            isConst=False,
            RefKind=ReferenceKind.NotRef,
        ))

    def withoutCVRefRec(self) -> "QualType":
        "Recursively remove all CV-qualifiers from the qualified type"
        base_override = dict(
            isConst=False,
            RefKind=ReferenceKind.NotRef,
            ptrCount=0,
            isNamespace=False,
            meta=dict(),
        )

        match self.Kind:
            case QualTypeKind.RegularType | QualTypeKind.Array:
                return self.model_copy(
                    update={
                        "Spaces": [S.withoutCVRefRec() for S in self.Spaces],
                        "Parameters": [P.withoutCVRefRec() for P in self.Parameters],
                        **base_override,
                    })

            case QualTypeKind.FunctionPtr | QualTypeKind.MethodPtr:
                return self.model_copy(
                    update={
                        "func":
                            QualType.Function(
                                ReturnTy=self.func.ReturnTy.withoutCVRef(),
                                Args=[A.withoutCVRefRec() for A in self.func.Args],
                                IsConst=False,
                                Class=self.func.Class.withoutCVRefRec() if self.func.
                                Class else None,
                            ),
                        **base_override,
                    })

            case QualTypeKind.TypeExpr:
                return self.model_copy()

    def withoutSpace(self, name: str) -> "QualType":
        "Return the type excluding all the spaces with the provided `name`"
        flat = self.flatten()
        return flat.model_copy(update=dict(
            Spaces=[S for S in flat.Spaces if S.name != name]))

    def withoutAllScopeQualifiers(self) -> "QualType":
        "Return the type with no parent spaces"
        return self.model_copy(update=dict(Spaces=[]))

    def withChangedSpace(self, name: Union["QualType", str]) -> "QualType":
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

    @staticmethod
    def FromTypeList(Params: List[QualType]) -> "GenTuTemplateParams":
        "Create template type parameter from list of qualified types"
        return GenTuTemplateParams(Stacks=[
            GenTuTemplateGroup(
                Params=[GenTuTemplateTypename(Name=p.name) for p in Params])
        ])

    @staticmethod
    def FromTypeNameList(Params: List[str]) -> "GenTuTemplateParams":
        "Create template type parameter from list of template parameter names"
        return GenTuTemplateParams(Stacks=[
            GenTuTemplateGroup(Params=[GenTuTemplateTypename(Name=p) for p in Params])
        ])


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
    "IR for typedef/using mapping"
    name: QualType
    base: QualType
    original: Optional[Path] = None
    OriginName: Optional[str] = None
    reflectionParams: GenTuReflParams = field(default_factory=lambda: GenTuReflParams())
    ExposeHeaderDeclaration: bool = True
    "When generating header source files, the structure would be exposed for public API"


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
    "IR for enum"
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

    ExposeHeaderDeclaration: bool = True
    "When generating header source files, the enum would be exposed for public API"

    def __str__(self) -> str:
        return f"GenTuEnum({self.name.format()})"

    def format(self, dbgOrigin: bool = False) -> str:
        return "enum " + self.name.format(dbgOrigin=dbgOrigin)


@beartype
@dataclass
class GenTuFunction:
    """
    Intermediate representation for the callable entry: function, lambda or method in the C++ code.
    Whether specific function entry is considered either of those depends on the parent context --
    if it is placed in class it is a method, if it is a toplevel it is a function etc.
    """
    result: Optional[QualType] = None
    "Return type of the function. `None` means void, although `void` might be used explicitly"
    name: str = ""
    "Non-demangled function name as seen in the source file"
    doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))
    "Documentation comment above the function"
    params: Optional[GenTuTemplateParams] = field(default=None)
    "Function template parameters"
    arguments: List[GenTuIdent] = field(default_factory=list)
    "Runtime function arguments"
    impl: Optional[Union[str, BlockId]] = None
    """
    Implementation body for the function -- might be set up for the codegen,
    is not set up by the reflection tool.
    """
    isVirtual: bool = False
    "Whether method is marked as virtual in this specific declaration"
    isConst: bool = False
    "Is method virtual"
    isStatic: bool = False
    "Is class method static"
    isPureVirtual: bool = False
    "Is class method pure virtual"
    isOverride: bool = False
    "Does method override parent implementation"
    parentClass: Optional['GenTuStruct'] = None
    """
    Optional specification for the parent struct -- might be set up by the codegen, is
    not set up by the reflection tool.
    """
    original: Optional[Path] = None
    "Path to the file where function was declared"
    spaces: List[QualType] = field(default_factory=list)
    "Fully qualified namespace for the function declaration"
    isExposedForWrap: bool = True
    "Whether function is exposed for the public wrap interface"
    OriginName: Optional[str] = None

    IsConstructor: bool = False
    "Is function a constructor"
    InitList: List[BlockId] = field(default_factory=list)
    "Init list for the constructor definition"

    reflectionParams: GenTuReflParams = field(default_factory=GenTuReflParams)
    "Additional reflection parameters for the function wrapping"

    ExposeHeaderDeclaration: bool = True
    """
    When generating header source files, the function would be exposed for public API.
    For methods the behavior is inherited from the parent structure
    """

    def get_full_qualified_name(self) -> QualType:
        "Get a single type with the fully qualified spaces and function name"
        return QualType(name=self.name, Spaces=self.spaces)

    def get_function_type(self, Class: Optional[QualType] = None) -> QualType:
        "Get a qualified type for the function signature"
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
        "Format function representation as a string"
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
    "Single field in the structure"
    type: Optional[QualType]
    "Type field, if specified"
    name: str
    "Field name as seen in the source code"
    doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))
    decl: Optional[Union['GenTuStruct', 'GenTuEnum']] = None
    value: Optional[Union[str, BlockId]] = None
    isConst: bool = False
    isStatic: bool = False
    isTypeDecl: bool = False
    isExposedForWrap: bool = True
    isExposedForDescribe: bool = True
    "Whether to include the field in the auto-generated BOOST_DESCRIBE_CLASS"
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
    "Include boost describe for the class methods"
    GenDescribeFields: bool = True
    "Include boost describe for the class fields"
    reflectionParams: GenTuReflParams = field(default_factory=GenTuReflParams)
    "Extra reflection parameters for the code generation"
    IsExplicitInstantiation: bool = False
    "Whether the class is an explicit instantiation of the template"
    IsTemplateRecord: bool = False
    ExplicitTemplateParams: List[QualType] = field(default_factory=list)
    """
    Template parameters explicitly specified in the structure declaration.
    Note that IsExplicitInstantiation must also be set to codegen type
    specializations.
    """
    OriginName: Optional[str] = None
    IsDescribedRecord: bool = False
    "For structs from reflection parser -- is there a boost describe annotation in code"
    TemplateParams: Optional[GenTuTemplateParams] = None
    "Template parameters for the structure"
    ExposeHeaderDeclaration: bool = True
    "When generating header source files, the structure would be exposed for public API"

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
@dataclass(kw_only=True)
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
def n_org_imm() -> List[QualType]:
    return [n_org(), n_imm()]


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
def get_type_map(expanded: Sequence[GenTuUnion]) -> GenTypeMap:
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
    type_map: GenTypeMap,
) -> List[GenTuField]:
    fields = []
    for base_sym in value.bases:
        base: Optional[GenTuStruct] = type_map.get_one_type_for_name(
            base_sym.name)  # type: ignore
        if base:
            fields.extend(base.fields)
            fields.extend(get_type_base_fields(base, type_map))

    return fields


@beartype
def get_base_list(
    value: GenTuStruct,
    type_map: GenTypeMap,
) -> List[QualType]:
    fields = []

    def aux(typ: QualType) -> List[QualType]:
        result: List[QualType] = [typ]
        base: Optional[GenTuStruct] = type_map.get_one_type_for_name(
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
