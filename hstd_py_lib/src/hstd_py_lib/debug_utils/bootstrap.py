import sys
from pathlib import Path


def __lldb_init_module(debugger: object, internal_dict: dict) -> None:
    source = str(Path(__file__).resolve().parents[2])

    if source in sys.path:
        sys.path.remove(source)

    sys.path.insert(0, source)

    from hstd_py_lib.debug_utils import integration

    internal_dict["hstd_py_lib"] = sys.modules["hstd_py_lib"]
    integration.install(debugger)
