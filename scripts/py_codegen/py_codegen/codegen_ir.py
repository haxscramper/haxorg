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
    Name: str = ""
    Params: List["QualType"] = Field(default_factory=list)
    """
    List of template type parameters for the type. Depending on the type kind
    the parameters stored might be explicit template type parameters for the
    custom structure, or they might be used to store parameters for the array
    type.
    """
    Spaces: List["QualType"] = Field(default_factory=list)
    "List of parent namespaces"
    IsNamespace: bool = False
    "Whether the entry itself is a namespace or a type"

    IsConst: bool = False
    "Does type have a const annotation?"
    PtrCount: int = 0
    "How many pointer indirection annotations is on the type"
    RefKind: ReferenceKind = ReferenceKind.NotRef
    "is this type a L-Value/R-Value reference?"
    DbgOrigin: str = Field(default="", exclude=True)
    "Extra field to put debug information about the type origin"
    IsBuiltin: bool = Field(default=False)
    "Whether the qualified type represents a built-in one"
    IsGlobalNamespace: bool = Field(default=False)
    "Prefix the type with leading `::` to refer to the global namespace"
    IsPackExpansion: bool = Field(default=False)
    "Is this type an expansion of variadic template type parameter"

    Expr: Optional[str] = None
    "Expression text for the literal value"
    Kind: QualTypeKind = QualTypeKind.RegularType
    "Kind of the qualified type"

    @beartype
    class Function(BaseModel, extra="forbid"):
        "Pointer to function signature"
        ReturnType: Optional['QualType']
        "Type of the function return type"
        Args: List['QualType']
        "Types of the function arguments"
        Class: Optional['QualType'] = None
        "Type of the method's class"
        IsConst: bool = False
        "For const methods"

    Func: Optional[Function] = None
    "Typed representation of the pointer-to-function type"

    Meta: Dict[str, Any] = Field(default={})
    "Extra qualified type metadata"

    VerticalParamList: bool = Field(default=False, exclude=True)
    "Generate the qual type source by vertically stacking params (only relevant for codegen)"

    @beartype
    def copy_update(self, **kwargs: Any) -> "QualType":
        current_data = {
            field_name: getattr(self, field_name)
            for field_name in self.model_fields.keys()
        }

        current_data.update(kwargs)
        return self.__class__(**current_data)

    def par0(self) -> "QualType":
        if 0 < len(self.Params):
            return self.Params[0]

        else:
            raise IndexError("Type does not have parameters")

    def par1(self) -> Optional["QualType"]:
        if 1 < len(self.Params):
            return self.Params[1]

        else:
            raise IndexError(f"Type has {len(self.Params)} parameters")

    def parLen(self) -> int:
        return len(self.Params)

    def test(self, met: str) -> bool:
        return bool(self.Meta.get(met, False))

    def isOrgType(self) -> bool:
        return self.Meta.get("isOrgType", False)

    @staticmethod
    def ForName(name: str, **args: Any) -> "QualType":
        return QualType(Name=name, **args)

    @staticmethod
    def ForExpr(expr: str, **args: Any) -> "QualType":
        return QualType(Expr=expr, Kind=QualTypeKind.TypeExpr, **args)

    def flatten(self) -> "QualType":
        return self.copy_update(Spaces=self.flatQualScope())

    def withDbgOrigin(self, msg: str) -> "QualType":
        return self.copy_update(DbgOrigin=self.DbgOrigin + msg)

    def asConstRef(self) -> "QualType":
        return self.copy_update(IsConst=True, RefKind=ReferenceKind.LValue)

    def asConstPtr(self) -> "QualType":
        return self.copy_update(IsConst=True, ptrCount=1)

    def asRef(self) -> "QualType":
        return self.copy_update(IsConst=False, RefKind=ReferenceKind.LValue)

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
        return [it for it in self.flatQualScope() if not it.IsNamespace]

    def asPtr(self, ptrCount: int = 1) -> "QualType":
        return self.copy_update(PtrCount=ptrCount)

    def withGlobalSpace(self) -> "QualType":
        return self.copy_update(IsGlobalNamespace=True)

    def flatSpaceNames(self) -> List[str]:
        "Get flat list of names for fully qualified type"

        def aux(Typ: QualType) -> List[str]:
            res: List[str] = []
            for S in Typ.Spaces:
                res += aux(S)

            res += [Typ.Name]
            return res

        return list(itertools.chain(*[aux(S) for S in self.Spaces]))

    def flatQualName(self) -> List[str]:
        return self.flatSpaceNames() + [self.Name]

    def flatQualNameWithParams(self) -> List:
        """
        Generate recursively nested list of the type names for spaces and parameters:

        ```
        std::optional<T> -> ["std", "optional", ["T"]]
        std::unordered_map<int, std::map<int, char>> -> ["std", "unordered", [["int"], ["std", "map", [["int"], ["char"]]]]
        ```
        """
        return self.flatQualName() + [[P.flatQualNameWithParams()] for P in self.Params]

    def asSpaceFor(self, other: "QualType") -> "QualType":
        "Use the current type as a wrapper space for other type"
        return other.copy_update(
            Spaces=self.Spaces + [self.copy_update(
                Spaces=[],
                IsGlobalNamespace=False,
            )],
            IsGlobalNamespace=self.IsGlobalNamespace,
        )

    def withTemplateParams(self, Params: List["QualType"]) -> "QualType":
        return self.copy_update(Params=Params)

    def withWrapperType(self, name: Union[str, "QualType"]) -> "QualType":
        if isinstance(name, str):
            return QualType(Name=name, Params=[self])

        else:
            return name.copy_update(Params=[self])

    def withExtraSpace(self, name: Union["QualType", str]) -> "QualType":
        "Return copy with prepended space"
        flat = self.flatten()
        added: QualType = QualType(Name=name) if isinstance(name, str) else name
        assert isinstance(added, QualType), type(added)
        return flat.copy_update(Spaces=[added] + flat.Spaces)

    def withoutCVRef(self) -> "QualType":
        return self.copy_update(
            IsConst=False,
            RefKind=ReferenceKind.NotRef,
        )

    def withoutCVRefRec(self) -> "QualType":
        "Recursively remove all CV-qualifiers from the qualified type"
        base_override = dict(
            IsConst=False,
            RefKind=ReferenceKind.NotRef,
            PtrCount=0,
            IsNamespace=False,
            Meta=dict(),
        )

        match self.Kind:
            case QualTypeKind.RegularType | QualTypeKind.Array:
                return self.copy_update(
                    Spaces=[S.withoutCVRefRec() for S in self.Spaces],
                    Params=[P.withoutCVRefRec() for P in self.Params],
                    **base_override,
                )

            case QualTypeKind.FunctionPtr | QualTypeKind.MethodPtr:
                return self.copy_update(
                    func=QualType.Function(
                        ReturnType=self.Func.ReturnType.withoutCVRef(),
                        Args=[A.withoutCVRefRec() for A in self.Func.Args],
                        IsConst=False,
                        Class=self.Func.Class.withoutCVRefRec()
                        if self.Func.Class else None,
                    ),
                    **base_override,
                )

            case QualTypeKind.TypeExpr:
                return self.model_copy()

    def withoutSpace(self, name: str) -> "QualType":
        "Return the type excluding all the spaces with the provided `name`"
        flat = self.flatten()
        return flat.copy_update(Spaces=[S for S in flat.Spaces if S.Name != name])

    def withoutAllScopeQualifiers(self) -> "QualType":
        "Return the type with no parent spaces"
        return self.copy_update(Spaces=[])

    def withChangedSpace(self, name: Union["QualType", str]) -> "QualType":
        """Change the namespace of the qualified type from the current list to the [name]
        Resulting type will have only [name] as the space"""
        added: QualType = QualType(Name=name) if isinstance(name, str) else name
        assert isinstance(added, QualType), type(added)
        return self.flatten().copy_update(Spaces=[added])

    def isArray(self) -> bool:
        return self.Kind == QualTypeKind.Array

    def isFunction(self) -> bool:
        return self.Kind == QualTypeKind.FunctionPtr

    def isPrimitive(self) -> bool:
        return self.IsBuiltin or self.Name in [
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

            for P in T.Params:
                aux(P)

            if with_modifiers:
                result.append((
                    T.Name,
                    T.IsConst,
                    T.PtrCount,
                    T.RefKind,
                ))

            else:
                result.append((T.Name,))  # type: ignore[arg-type]

        aux(self)
        return tuple(result)

    def get_recursive_uses(self) -> List["QualType"]:
        result: List[QualType] = []
        match self.Kind:
            case QualTypeKind.RegularType:
                result.append(self)
                for p in self.Params:
                    result.extend(p.get_recursive_uses())

            case QualTypeKind.FunctionPtr:
                assert self.Func
                for arg in self.Func.Args:
                    result.extend(arg.get_recursive_uses())

            case QualTypeKind.Array:
                for p in self.Params:
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
                    const=" const" if Typ.IsConst else "",
                    ptr=("*" * Typ.PtrCount),
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
                    assert Typ.Func
                    result = "{result}({args})(*)".format(
                        result=aux(Typ.Func.ReturnType or QualType.ForName("void"),
                                   depth=depth + 1),
                        args=", ".join([aux(T, depth=depth + 1) for T in Typ.Func.Args]),
                    )

                case QualTypeKind.Array:
                    result = "{first}[{expr}]{cvref}".format(
                        first=aux(Typ.Params[0], depth=depth + 1),
                        expr=aux(Typ.Params[1], depth=depth +
                                 1) if 1 < len(Typ.Params) else "",
                        cvref=cvref,
                    )

                case QualTypeKind.RegularType:
                    if max_params:
                        params_list = Typ.Params[:min(len(Typ.Params), max_params)]

                    else:
                        params_list = Typ.Params

                    params_format = [aux(T, depth=depth + 1) for T in params_list]
                    if max_param_size:
                        params_format = [
                            p[:min(len(p), max_param_size)] for p in params_format
                        ]

                    result = "{spaces}{name}{args}{cvref}".format(
                        name=Typ.Name or "?",
                        args="<{}>".format(", ".join(params_format))
                        if params_format else "",
                        cvref=cvref,
                        spaces=spaces,
                    )

                case QualTypeKind.TypeExpr:
                    result = f"{Typ.Expr}"

                case _:
                    assert False, Typ.Kind

            return result

        # return self.model_dump_json() + "  --- " + aux(self)
        return aux(self, depth=0)
        # return str(self.flat_repr_flatten())

    def format(self, dbgOrigin: bool = DEBUG_TYPE_ORIGIN) -> str:

        def aux(Typ: QualType) -> str:
            cvref = "{const}{ptr}{ref}".format(
                const=" const" if Typ.IsConst else "",
                ptr=("*" * Typ.PtrCount),
                ref={
                    ReferenceKind.LValue: "&",
                    ReferenceKind.RValue: "&&",
                    ReferenceKind.NotRef: ""
                }[Typ.RefKind],
            )

            origin = f" FROM:{Typ.DbgOrigin}" if (dbgOrigin and Typ.DbgOrigin) else ""

            spaces = "".join([f"{aux(S)}::" for S in Typ.Spaces])
            # if spaces:
            #     spaces = f"{spaces}"

            match Typ.Kind:
                case QualTypeKind.FunctionPtr:
                    assert Typ.Func
                    assert Typ.Func.ReturnType, "Missing return type for function pointer"
                    result = "{spaces}FUNC:{origin}({args})".format(
                        spaces=spaces,
                        origin=aux(Typ.Func.ReturnType),
                        args=", ".join([aux(T) for T in Typ.Func.Args]),
                    )

                case QualTypeKind.Array:
                    result = "{spaces}ARR:{first}[{expr}]{cvref}{origin}".format(
                        first=aux(Typ.Params[0]),
                        expr=aux(Typ.Params[1]) if 1 < len(Typ.Params) else "",
                        cvref=cvref,
                        origin=origin,
                        spaces=spaces,
                    )

                case QualTypeKind.RegularType:
                    result = "{spaces}REC:({name}{args}{cvref}{origin})".format(
                        name=Typ.Name or "?",
                        args="<{}>".format(", ".join([aux(T) for T in Typ.Params]))
                        if Typ.Params else "",
                        cvref=cvref,
                        origin=origin,
                        spaces=spaces,
                        # namespace=("NSP" if Typ.isNamespace else ""),
                    )

                case QualTypeKind.TypeExpr:
                    result = f"[E:{Typ.Expr}]"

                case _:
                    assert False, Typ.Kind

            return "{" + result + "}"

        # return self.model_dump_json() + "  --- " + aux(self)
        return aux(self)
        # return str(self.flat_repr_flatten())

    def asNamespace(self, is_namespace: bool = True) -> "QualType":
        self.IsNamespace = is_namespace
        return self

    def withVerticalParams(self, params: bool = True) -> "QualType":
        self.VerticalParamList = params
        return self

    @classmethod
    def from_name(cls, name: str) -> "QualType":
        return cls(Name=name)

    @classmethod
    def from_name_and_parameters(cls, name: str,
                                 parameters: List['QualType']) -> "QualType":
        return cls(Name=name, Params=parameters)

    @classmethod
    def from_spaces_and_name(cls, spaces: List[str], name: str) -> "QualType":
        return cls(Name=name, Spaces=[cls.from_name(space) for space in spaces])


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
                Params=[GenTuTemplateTypename(Name=p.Name) for p in Params])
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
    Type: QualType
    Name: str
    Value: Optional[Union[BlockId, str]] = None
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
    Name: QualType
    Base: QualType
    Original: Optional[Path] = None
    OriginName: Optional[str] = None
    ReflectionParams: GenTuReflParams = field(default_factory=lambda: GenTuReflParams())
    ExposeHeaderDeclaration: bool = True
    "When generating header source files, the structure would be exposed for public API"


@beartype
@dataclass
class GenTuEnumField:
    Name: str
    Doc: GenTuDoc
    Value: Optional[int] = None
    OriginName: Optional[str] = None


@beartype
@dataclass
class GenTuEnum:
    "IR for enum"
    Name: QualType
    Doc: GenTuDoc
    Fields: List[GenTuEnumField]
    Base: Optional[str] = "short int"
    IsForwardDecl: bool = False
    OriginalPath: Optional[Path] = None
    ReflectionParams: GenTuReflParams = field(default_factory=GenTuReflParams)
    OriginName: Optional[str] = None
    IsDescribedEnum: bool = False

    ExposeHeaderDeclaration: bool = True
    "When generating header source files, the enum would be exposed for public API"

    def __str__(self) -> str:
        return f"GenTuEnum({self.Name.format()})"

    def format(self, dbgOrigin: bool = False) -> str:
        return "enum " + self.Name.format(dbgOrigin=dbgOrigin)


@beartype
@dataclass
class GenTuAnnotation():
    "Any extra annotation on the entry"

    @beartype
    @dataclass
    class Freeform:
        "Fully free-form prefix for the annotation"
        Body: str | BlockId

    @beartype
    @dataclass
    class StandardAttribute:
        "Standard-compliant attribute syntax with `[[xyz]]`"
        Name: QualType
        "Qualified name of the attribute like `clang::abc`"
        Args: List[str | BlockId] = field(default_factory=list)

    @beartype
    @dataclass
    class CompilerSpecificAttribute:
        "Compiler-specific attribute annotation"
        DeclStart: str | BlockId
        "Start of the custom attribute syntax, `__attribute__((` -- without closing part"
        DeclEnd: str | BlockId
        "Closing part of the attribute syntax, `))` -- complementing the start"
        DeclName: str
        "First entry in the attribute syntax"
        Args: List[str | BlockId] = field(default_factory=list)
        "Optional list of additional attribute argument"

    Attribute: Freeform | StandardAttribute | CompilerSpecificAttribute


@beartype
@dataclass
class GenTuFunction:
    """
    Intermediate representation for the callable entry: function, lambda or method in the C++ code.
    Whether specific function entry is considered either of those depends on the parent context --
    if it is placed in class it is a method, if it is a toplevel it is a function etc.
    """
    Name: str = ""
    "Non-demangled function name as seen in the source file"
    ReturnType: QualType = field(default_factory=lambda: QualType(Name="void"))
    "Return type of the function. `None` means void, although `void` might be used explicitly"
    Doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))
    "Documentation comment above the function"
    Params: Optional[GenTuTemplateParams] = field(default=None)
    "Function template parameters"
    Args: List[GenTuIdent] = field(default_factory=list)
    "Runtime function arguments"
    Body: Optional[Union[str, BlockId]] = None
    """
    Implementation body for the function -- might be set up for the codegen,
    is not set up by the reflection tool.
    """
    IsVirtual: bool = False
    "Whether method is marked as virtual in this specific declaration"
    IsConst: bool = False
    "Is method virtual"
    IsStatic: bool = False
    "Is class method static"
    IsPureVirtual: bool = False
    "Is class method pure virtual"
    IsOverride: bool = False
    "Does method override parent implementation"
    ParentClass: Optional['GenTuStruct'] = None
    """
    Optional specification for the parent struct -- might be set up by the codegen, is
    not set up by the reflection tool.
    """
    OriginalPath: Optional[Path] = None
    "Path to the file where function was declared"
    Spaces: List[QualType] = field(default_factory=list)
    "Fully qualified namespace for the function declaration"
    IsExposedForWrap: bool = True
    "Whether function is exposed for the public wrap interface"
    OriginName: Optional[str] = None

    IsConstructor: bool = False
    "Is function a constructor"
    InitList: List[BlockId] = field(default_factory=list)
    "Init list for the constructor definition"
    Linkage: Optional[str] = None
    "Linkage annotation for the parsed/generated function"
    Annotations: List[GenTuAnnotation] = field(default_factory=list)
    "Additional annotation, attributes or prefixes for the function declaration"

    ReflectionParams: GenTuReflParams = field(default_factory=GenTuReflParams)
    "Additional reflection parameters for the function wrapping"

    ExposeHeaderDeclaration: bool = True
    """
    When generating header source files, the function would be exposed for public API.
    For methods the behavior is inherited from the parent structure
    """

    def get_full_qualified_name(self) -> QualType:
        "Get a single type with the fully qualified spaces and function name"
        return QualType(Name=self.Name, Spaces=self.Spaces)

    def get_function_type(self, Class: Optional[QualType] = None) -> QualType:
        "Get a qualified type for the function signature"
        return QualType(
            Func=QualType.Function(
                ReturnType=self.ReturnType,
                Args=[A.Type for A in self.Args],
                Class=Class,
                IsConst=self.IsConst,
            ),
            Kind=QualTypeKind.FunctionPtr,
        )

    def format(self) -> str:
        "Format function representation as a string"
        assert self.ReturnType, "Missing function return type"
        return "function %s %s(%s)" % (self.ReturnType.format(), self.Name, ", ".join(
            [Arg.Name + " " + Arg.Type.format() for Arg in self.Args]))


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
    Type: Optional[QualType]
    "Type field, if specified"
    Name: str
    "Field name as seen in the source code"
    Doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))
    Decl: Optional[Union['GenTuStruct', 'GenTuEnum']] = None
    Value: Optional[Union[str, BlockId]] = None
    IsConst: bool = False
    IsStatic: bool = False
    IsTypeDecl: bool = False
    IsExposedForWrap: bool = True
    IsExposedForDescribe: bool = True
    "Whether to include the field in the auto-generated BOOST_DESCRIBE_CLASS"
    ReflectionParams: GenTuReflParams = field(default_factory=GenTuReflParams)
    OriginName: Optional[str] = None


@beartype
@dataclass
class GenTuStruct():
    """
    Intermediate representation of the C++ record
    """
    Name: QualType
    Doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))
    Fields: List[GenTuField] = field(default_factory=list)
    "Field directly in the structure"
    Methods: List[GenTuFunction] = field(default_factory=list)
    Bases: List[QualType] = field(default_factory=list)
    Nested: List[Union[
        GenTuEnum,
        "GenTuStruct",
        "GenTuTypeGroup",
        GenTuTypedef,
        GenTuPass,
    ]] = field(default_factory=list)
    "All extra elements in the class "
    IsForwardDecl: bool = False
    IsAbstract: bool = False
    HasName: bool = True
    OriginalPath: Optional[Path] = field(default=None)
    GenDescribeMethods: bool = False
    "Include boost describe for the class methods"
    GenDescribeFields: bool = True
    "Include boost describe for the class fields"
    ReflectionParams: GenTuReflParams = field(default_factory=GenTuReflParams)
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
        return f"GenTuStruct({self.Name.format()})"

    def declarationQualName(self) -> QualType:
        return self.Name.copy_update(Params=self.ExplicitTemplateParams)

    def format(self, dbgOrigin: bool = False) -> str:
        return "record " + self.Name.format(dbgOrigin=dbgOrigin)

    def getGetitemMethods(self) -> List[GenTuFunction]:
        return [
            m for m in self.Methods if m.ReflectionParams.function_api and
            m.ReflectionParams.function_api.is_get_item
        ]

    def getBeginEndPair(self) -> Optional[Tuple[GenTuFunction, GenTuFunction]]:
        begin_func: Optional[GenTuFunction] = None
        end_func: Optional[GenTuFunction] = None

        for m in self.Methods:
            if m.Name == "begin":
                begin_func = m

            elif m.Name == "end":
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
            return decl.Base

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
        return struct and struct.ReflectionParams.wrapper_name  # type: ignore

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

            case GenTuEnum():
                qual_name = typ.Name.model_copy()

            case GenTuTypedef():
                qual_name = typ.Name.model_copy()

            case _:
                raise ValueError(f"{type(typ)} is not a type definition")

        qual_hash = qual_name.qual_hash()
        new_index = len(self.entries)
        if qual_hash in self.qual_hash_to_index:
            return
            # raise ValueError(f"Qual type {qual_name} is already mapped to {self.qual_hash_to_index[qual_hash]}")

        self.qual_hash_to_index[qual_hash].append(new_index)
        self.name_to_index[qual_name.Name].append(new_index)

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

                case GenTuEnum():
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
    return QualType(Name="hstd", IsNamespace=True)


@beartype
def n_hstd_ext() -> QualType:
    return QualType(Name="ext", IsNamespace=True, Spaces=[n_hstd()])


@beartype
def n_org() -> QualType:
    return QualType(Name="org", IsNamespace=True)


def n_org_algo() -> QualType:
    return QualType(
        Name="algo",
        IsNamespace=True,
        Meta=dict(isSemNamespace=True),
        Spaces=[n_org()],
    )


@beartype
def t_opt(arg: QualType) -> QualType:
    return QualType(Name="Opt", Params=[arg], Spaces=[n_hstd()])


@beartype
def t_vec(arg: QualType) -> QualType:
    return QualType(Name="Vec", Params=[arg], Spaces=[n_hstd()])


@beartype
def n_sem() -> QualType:
    return QualType(
        Name="sem",
        IsNamespace=True,
        Meta=dict(isSemNamespace=True),
        Spaces=[n_org()],
    )


@beartype
def n_imm() -> QualType:
    return QualType(
        Name="imm",
        IsNamespace=True,
        Meta=dict(isSemNamespace=True),
        Spaces=[n_org()],
    )


@beartype
def t_org(name: str) -> QualType:
    return QualType(
        Name=name,
        Meta=dict(isOrgType=True),
        # dbg_origin="t_org",
    )


@beartype
def t(name: str | QualType,
      namespaces: List[QualType] = [],
      isOrgType: bool = False,
      DbgOrigin: str = "") -> QualType:
    if isinstance(name, QualType):
        return name.copy_update(Spaces=namespaces,
                                DbgOrigin=name.DbgOrigin + " " + DbgOrigin)

    else:
        return QualType(Name=name, Spaces=namespaces, DbgOrigin=DbgOrigin)


@beartype
def t_namespace(name: str | QualType) -> QualType:
    return t(name).asNamespace()


@beartype
def t_space(name: str | QualType, Spaces: List[QualType]) -> QualType:
    if isinstance(name, QualType):
        return name.copy_update(Spaces=Spaces)
    else:
        return QualType(Name=name, Spaces=Spaces)


@beartype
def t_nest(name: Union[str, QualType], Spaces: List[QualType] = []) -> QualType:
    return t_space(name, [n_sem()] + Spaces)


@beartype
def t_id(target: Optional[Union[QualType, str]] = None) -> QualType:
    org_t = target if target else t_nest(t_org("Org"))
    org_t = org_t if isinstance(org_t, QualType) else t_nest(t_org(org_t))

    return (QualType(Name="SemId", Params=[org_t], Spaces=[n_sem()]))


@beartype
def get_type_map(expanded: Sequence[GenTuUnion]) -> GenTypeMap:
    return GenTypeMap.FromTypes(expanded)


@beartype
def filter_walk_scope(iterate_context: List[Any]) -> List[QualType]:
    scope: List[QualType] = []

    for s in iterate_context:
        match s:
            case GenTuStruct():
                scope.append(s.Name)

            case GenTuNamespace():
                scope.append(QualType.ForName(s.Name.Name))

    return scope


@beartype
def get_type_base_fields(
    value: GenTuStruct,
    type_map: GenTypeMap,
) -> List[GenTuField]:
    fields = []
    for base_sym in value.Bases:
        base: Optional[GenTuStruct] = type_map.get_one_type_for_name(
            base_sym.Name)  # type: ignore
        if base:
            fields.extend(base.Fields)
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
            typ.Name)  # type: ignore
        if base:
            for it in base.Bases:
                result.extend(aux(it))

        return result

    for base_sym in value.Bases:
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
