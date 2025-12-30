from py_scriptutils import configure_asan
import linecache
import sys

def trace_lines(frame, event, arg) -> None:
    if event == 'call' and frame.f_code.co_name == '__import__':
        lineno = frame.f_lineno
        filename = frame.f_globals.get("__file__", "<none>")
        if filename.endswith((".pyc", ".pyo")):
            filename = filename[:-1]
        line = linecache.getline(filename, lineno)
        print(f"{event} {filename}:{lineno}: {line.rstrip()}")

    return trace_lines



import pytest

sys.settrace(trace_lines)

if __name__ == "__main__":
    pytest.main(['--collect-only', '-vv'])
