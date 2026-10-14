#!/usr/bin/env python

import importlib.util
import subprocess
import sys
from importlib.machinery import SourceFileLoader
from pathlib import Path

path = Path(__file__).resolve().parent / "commit-msg"

assert path.exists(), path

spec = importlib.util.spec_from_file_location(
    "other",
    path,
    loader=SourceFileLoader("other", str(path)),
)
module = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = module
spec.loader.exec_module(module)

SCOPES: dict[str, str] = module.SCOPES
TYPES: dict[str, str] = module.TYPES

if 2 < len(sys.argv) and sys.argv[2] == "commit":
    sys.exit(0)

msg_path = Path(sys.argv[1])
content = msg_path.read_text() if msg_path.exists() else ""

# Check if our help block is already present in the message
marker = "# <type>(<scope>): <subject>"
if 2 < len(sys.argv) and sys.argv[2] in {"message", "commit"}:
    sys.exit(0)


lines = ["", ""]

stat = subprocess.run(
    ["git", "diff", "--staged", "--stat"],
    check=True,
    capture_output=True,
)

lines.extend(f"# {it.decode()}" for it in stat.stdout.splitlines())
lines.extend(["#", marker, "#", "# Available types:"])
for name, desc in TYPES.items():
    lines.append(f"#   {name:<10} {desc}")
lines.extend(["#", "# Available scopes:"])
for name, desc in SCOPES.items():
    lines.append(f"#   {name:<10} {desc}")
lines.extend(["#", ""])

msg_path.write_text("\n".join(lines) + content)
