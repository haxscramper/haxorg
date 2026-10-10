import lldb

from hstd_py_lib.debug_utils.extract import ExtractionContext
from hstd_py_lib.debug_utils.model import ValueNode


def extract_std_string(
    value: lldb.SBValue,
    context: ExtractionContext,
    depth: int,
) -> ValueNode:
    source = value.GetDynamicValue(lldb.eDynamicDontRunTarget)
    if not source.IsValid():
        source = value

    source.SetPreferSyntheticValue(True)
    error = source.GetError()

    return ValueNode(
        name=value.GetName() or "",
        type_name="std::string",
        value=source.GetValue(),
        summary=source.GetSummary(),
        error=error.GetCString() if error.Fail() else None,
    )
