#!/usr/bin/env bash
# -*- coding: utf-8 -*-
set -o nounset
set -o errexit

TOOL="/haxorg/toolchain"
ln -sf /docker_toolchain $TOOL
ls -al $TOOL

export PATH="$TOOL/cmake/bin:$TOOL/llvm/bin:$PATH"

poetry install --no-root
poetry run $@
 