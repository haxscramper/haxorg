import os
import sys

# Get the absolute path of the directory containing the Python script
script_dir = os.path.dirname(os.path.abspath(__file__))

# Construct the absolute path to the 'lib' directory
lib_dir = os.path.abspath(os.path.join(script_dir, '..', '..', '..', 'lib'))

if lib_dir not in sys.path:
    # Add this directory to sys.path
    sys.path.append(lib_dir)

