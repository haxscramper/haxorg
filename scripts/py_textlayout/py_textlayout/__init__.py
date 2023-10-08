import os
import sys

script_dir = os.path.dirname(os.path.abspath(__file__))

# Construct the absolute path to the 'lib' directory
lib_dir = os.path.abspath(os.path.join(script_dir, '..', '..', '..', 'lib'))
print(lib_dir)

if lib_dir not in sys.path:
    # Add this directory to sys.path
    sys.path.append(lib_dir)
