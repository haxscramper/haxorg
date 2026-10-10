import faulthandler
import importlib
import sys
from pathlib import Path

faulthandler.enable()

directory = Path(sys.argv[1]).resolve()
sys.path.insert(0, str(directory))

extension = importlib.import_module("hstd_py_lldb_fixture_extension")

match sys.argv[2]:
    case "run":
        assert extension.run() == 112
    case "abort":
        extension.abort_process()
    case mode:
        raise ValueError(f"Unknown fixture execution mode {mode!r}")
