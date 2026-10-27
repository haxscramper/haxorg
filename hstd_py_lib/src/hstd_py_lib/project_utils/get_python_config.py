#!/usr/bin/env python

import shlex
import sys
import sysconfig

config = {
    "user.haxorg:python_executable": sys.executable,
    "user.haxorg:python_abi": sysconfig.get_config_var("SOABI"),
}

arguments = []
for key, value in config.items():
    arguments.extend(["-c", f"{key}={value}"])

print(shlex.join(arguments))
