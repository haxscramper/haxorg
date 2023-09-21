#!/usr/bin/env python

from dataclasses import field, dataclass
from typing import *
from enum import Enum

import setup_imports

import ctypes

ctypes.CDLL(setup_imports.lib_dir + '/pyhaxorg.so')
