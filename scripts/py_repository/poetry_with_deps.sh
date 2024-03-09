#!/usr/bin/env bash
# -*- coding: utf-8 -*-
set -o nounset
set -o errexit

poetry install --no-root
poetry run $@
