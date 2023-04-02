#!/usr/bin/env bash
# -*- coding: utf-8 -*-
set -o nounset
set -o errexit

lim=9000000

ulimit -v $lim
ulimit -m $lim

export LLDB_CUSTOM_TERM_WIDTH=$(tput cols)

lldb \
    --batch \
    -o "command script import $IN_PWD/lldb_script.py" \
    -o run \
    --source-on-crash $IN_PWD/lldb-script.txt \
    -- \
    $IN \
    $ARGS |
    rg -v "(is a Catch2|Run with -\? for options|Catch will terminate|\(lldb\)|frame-format|  0x|libc\.so|Process \d{2,}|Executing commands in|Terminate called without|\.{10,}|-{10,}|~{10,}|Test failure requires aborting|terminate called without)" |
    tee /tmp/haxorg_run.txt
