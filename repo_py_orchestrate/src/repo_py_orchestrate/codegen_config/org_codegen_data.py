from dataclasses import replace

from beartype import beartype
from beartype.typing import Any, List, Optional, Union

# Now you should be able to import your C++ library
from hstd_py_codegen.gen_cpp.codegen_ir import *
from hstd_py_codegen.read_cpp import refl_read


@beartype
def org_doc(Text: Union[str, GenTuDoc] = GenTuDoc(""), Full: str = "") -> GenTuDoc:
    return GenTuDoc(Text, Full) if isinstance(Text, str) else Text


AnyDoc = Union[str, GenTuDoc]


@beartype
def efield(
    Name: str, Doc: AnyDoc = GenTuDoc(""), Value: Optional[int] = None
) -> GenTuEnumField:
    return GenTuEnumField(Name=Name, Doc=org_doc(Doc), Value=Value)


# region cxx-types


@beartype
def t_str() -> QualType:
    return t("Str", [n_hstd()])


@beartype
def t_bool() -> QualType:
    return t("bool")


@beartype
def t_int() -> QualType:
    return t("int")


@beartype
def t_user_time() -> QualType:
    return t("UserTime", [n_hstd()])


@beartype
def t_nest_shared(Name: Union[str, QualType], Spaces: List[QualType] = []) -> QualType:
    return t_nest(name=Name, Spaces=Spaces)


@beartype
def k_args(obj: Any, **kwargs: Any) -> Any:
    for key, value in kwargs.items():
        obj.__setattr__(key, value)

    return obj


@beartype
def t_cr(arg: QualType) -> QualType:
    return arg.copy_update(RefKind=ReferenceKind.LValue, IsConst=True)


def t_var(*args: QualType) -> QualType:
    return QualType(Name="Variant", Params=[*args], Spaces=[n_hstd()])


def t_map(key: QualType, val: QualType) -> QualType:
    return QualType(Name="UnorderedMap", Params=[key, val], Spaces=[n_hstd()])


# endregion


@beartype
def org_struct(
    Type: QualType,
    Doc: AnyDoc = GenTuDoc(""),
    Fields: List[GenTuField] = [],
    Nested: List[GenTuEntry] = [],
    Methods: List[GenTuFunction] = [],
    Bases: List[QualType] = [],
    DefaultConstructor: bool = False,
    DefaultEq: bool = False,
) -> GenTuStruct:

    MethodsTmp = [replace(M, ParentClass=Type) for M in Methods]

    return GenTuStruct(
        Name=Type,
        Doc=org_doc(Doc),
        Fields=Fields,
        Nested=Nested,
        Methods=MethodsTmp,
        Bases=Bases,
        IsDescribedRecord=True,
    )


@beartype
def vec_field(Type: QualType, Name: str, Doc: AnyDoc = GenTuDoc("")) -> GenTuField:
    return GenTuField(t_vec(Type), Name, org_doc(Doc), Value="{}")


@beartype
def opt_field(Type: QualType, Name: str, Doc: AnyDoc = GenTuDoc("")) -> GenTuField:
    return GenTuField(
        Type=t_opt(Type),
        Name=Name,
        Doc=org_doc(Doc),
        Value="std::nullopt",
    )


# reflection run of the code generation must wrap the full
# set of functions and fields for the org type, but the
# base code generation only needs some common information
# such as fields and presence of the base class for `Org`
# common context is used to generate C++/protobuf sources
# wrappers are generated using full reflection information
# so the context TU must be supplied separately for the
# code generation.
COMMON_CONTEXT_TU = refl_read.ConvTu(
    structs=[
        org_struct(
            t("Org", [t("org"), t("sem")]),
            Fields=[
                opt_field(t("SourceLoc", [t("org"), t("parse")]), "loc"),
                vec_field(t_id(t("Org", [t("org"), t("sem")])), "subnodes"),
            ],
        )
    ]
)
