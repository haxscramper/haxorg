#!/usr/bin/env bash
# -*- coding: utf-8 -*-
set -o nounset
set -o errexit

lim=3000000

ulimit -v $lim
ulimit -m $lim

lldb \
    --batch \
    -o "command script import $IN_PWD/lldb_script.py" \
    -o run \
    --source-on-crash $IN_PWD/lldb-script.txt \
    -- \
    $IN \
    $ARGS
