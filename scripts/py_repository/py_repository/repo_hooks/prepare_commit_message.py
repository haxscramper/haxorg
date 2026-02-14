#!/usr/bin/env python

from pathlib import Path
import sys

hook_path = Path(__file__).resolve()
module_path = hook_path.parents[
    2] / "scripts" / "py_repository" / "py_repository" / "repo_hooks"
sys.path.insert(0, str(module_path))

from validate_commit_message import SCOPES, TYPES

if len(sys.argv) > 2 and sys.argv[2] == "commit":
    sys.exit(0)

msg_path = Path(sys.argv[1])
content = msg_path.read_text() if msg_path.exists() else ""

lines = ["", "", "# <type>(<scope>): <subject>", "#", "# Available types:"]
for name, desc in TYPES.items():
    lines.append(f"#   {name:<10} {desc}")
lines.extend(["#", "# Available scopes:"])
for name, desc in SCOPES.items():
    lines.append(f"#   {name:<10} {desc}")
lines.extend(["#", ""])

msg_path.write_text("\n".join(lines) + content)
