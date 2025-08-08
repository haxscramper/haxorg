#!/usr/bin/env bash
# -*- coding: utf-8 -*-
set -o nounset
set -o errexit

TOOL="/haxorg/toolchain"
ln -sf /docker_toolchain $TOOL
ls -al $TOOL

export PATH="/haxorg/build/utils:$TOOL/cmake/bin:$TOOL/llvm/bin:$PATH"
export HAXORG_SKIP_PY_HAXORG_BUILD=ON

git config --global --add safe.directory /haxorg
git config --global user.email "you@example.com"
git config --global user.name "Your Name"

poetry install --no-root
poetry run $@
 