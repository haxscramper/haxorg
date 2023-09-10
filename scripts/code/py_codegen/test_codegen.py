#!/usr/bin/env python

import os
import sys

# Get the absolute path of the directory containing the Python script
script_dir = os.path.dirname(os.path.abspath(__file__))

# Construct the absolute path to the 'lib' directory
lib_dir = os.path.abspath(os.path.join(script_dir, '..', '..', '..', 'lib'))

# Add this directory to sys.path
sys.path.append(lib_dir)

print(lib_dir)
import ctypes
ctypes.CDLL(lib_dir + '/libpy_textlayout.so')

# Now you should be able to import your C++ library
from py_textlayout import TextLayout, TextOptions


b = TextLayout()

_id = b.text("Test")
print(b.toString(_id, TextOptions()))
