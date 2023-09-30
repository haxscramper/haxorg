import os
import sys

script_dir = os.path.dirname(os.path.abspath(__file__))
lib_dir = os.path.abspath(os.path.join(script_dir, '..', '..', 'build/haxorg/lib'))

if lib_dir not in sys.path:
    # Add this directory to sys.path
    sys.path.append(lib_dir)