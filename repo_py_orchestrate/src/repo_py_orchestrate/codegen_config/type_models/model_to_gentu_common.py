from dataclasses import dataclass
from typing import Sequence

from beartype import beartype
from beartype.typing import List, Optional
from hstd_py_codegen.gen_cpp.codegen_ir import (
    GenTuFunction,
    QualType,
)
from hstd_py_text_layout.base.wrap import BlockId

CPP_SPACE_T = QualType(
    Name="unidata",
    IsNamespace=True,
    Spaces=[
        QualType(Name="hstd", IsNamespace=True),
        QualType(Name="ext", IsNamespace=True),
    ],
)

CPP_RESULT_T = QualType(Name="VerifyResult", Spaces=[CPP_SPACE_T])
CPP_CONTEXT_T = QualType(Name="VerifyContext", Spaces=[CPP_SPACE_T])
CPP_CB_T = QualType(Name="VerifyCb", Spaces=[CPP_SPACE_T])
CPP_CB_LIST_T = QualType(Name="VerifyCbList", Spaces=[CPP_SPACE_T])
CPP_KEY_T = QualType(Name="VerifyKey", Spaces=[CPP_SPACE_T])
CPP_VERIFY_COLLECTION_T = QualType(Name="VerifyCheckCollection", Spaces=[CPP_SPACE_T])


@beartype
@dataclass
class ExpressionEvaluation:
    statements: List[BlockId]
    value: BlockId


@beartype
@dataclass
class CheckFunction:
    class_type_name: str
    "Class type ID (fully qualified name as a string) for the check"
    impl: List[GenTuFunction]
    "Static method for the class to perform the check"
    class_field: Optional[str] = None
    "Which field this check applies to -- if empty, apply check to class"


# TODO: Move this logic into the QualType and simplify the
# Type usages for the qualified types in the code, it should
# be possible to use some sort of DSL/`[]` operation
# to make it easier to create `QualType`
def qualified_type(
    parts: Sequence[str],
    *,
    namespace_count: int = 0,
    params: Sequence[QualType] = (),
) -> QualType:
    if not parts:
        raise ValueError("A C++ type name cannot be empty")

    return QualType(
        Name=parts[-1],
        Spaces=[
            QualType(Name=part, IsNamespace=index < namespace_count)
            for index, part in enumerate(parts[:-1])
        ],
        Params=list(params),
    )


# TODO: See above
def named_cpp_type(
    name: str,
    params: Sequence[QualType] = (),
) -> QualType:
    parts = name.split("::")
    return qualified_type(
        parts,
        namespace_count=len(parts) - 1,
        params=params,
    )
