import lldb
from hstd_py_lib.debug_utils.extract import ExtractionContext
from hstd_py_lib.debug_utils.integration import register_extractor
from hstd_py_lib.debug_utils.model import ValueNode


def extract_point(
    value: lldb.SBValue,
    context: ExtractionContext,
    depth: int,
) -> ValueNode:
    raw = value.GetNonSyntheticValue()
    x = raw.GetChildMemberWithName("x").GetValueAsSigned()
    y = raw.GetChildMemberWithName("y").GetValueAsSigned()

    node = context.extract_default(value, depth)
    node.summary = f"point({x}, {y})"
    return node


def __lldb_init_module(
    debugger: lldb.SBDebugger,
    internal_dict: dict,
) -> None:
    register_extractor(
        r"^trace_fixture::Point$",
        extract_point,
    )
