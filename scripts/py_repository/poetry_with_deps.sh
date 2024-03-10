#!/usr/bin/env bash
# -*- coding: utf-8 -*-
set -o nounset
set -o errexit

TOOL="/haxorg/toolchain"
ln -sf /docker_toolchain $TOOL
ls -al $TOOL

export PATH="/haxorg/build/utils:$TOOL/cmake/bin:$TOOL/llvm/bin:$PATH"

git config --global --add safe.directory /haxorg
poetry install --no-root
poetry run $@
 