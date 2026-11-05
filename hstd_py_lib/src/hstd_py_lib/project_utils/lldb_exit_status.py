import os
import sys

import lldb


def __lldb_init_module(debugger, internal_dict):
    process = debugger.GetSelectedTarget().GetProcess()

    if process.IsValid() and process.GetState() == lldb.eStateExited:
        exit_status = process.GetExitStatus()
    else:
        exit_status = 1

    sys.stdout.flush()
    sys.stderr.flush()
    os._exit(exit_status)
