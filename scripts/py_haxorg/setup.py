#!/usr/bin/env python
# -*- coding: utf-8 -*-
## @file   setup.py
## @brief  Setuptools for installable python package

import os
from pathlib import Path
import sys

from setuptools import find_packages
from setuptools import setup

# Import and run the build script
sys.path.insert(0, str(Path(__file__).parent))
from build import build

packages = ['py_haxorg']

package_data = {
    'py_haxorg': ['*.so', '**/*.so'],  # Include shared library files
    '': ['*']
}

setup_kwargs = {
    'name': 'py-haxorg',
    'version': '0.1.0',
    'description': 'Python bindings for haxorg',
    'long_description': '',
    'author': 'haxscramper',
    'author_email': 'haxscramper@gmail.com',
    'maintainer': 'None',
    'maintainer_email': 'None',
    'url': 'None',
    'packages': packages,
    'package_data': package_data,
    'include_package_data': True,
    'python_requires': '>=3.9.0,<3.14',
    'install_requires': ['beartype>=0.20.0',],
    'zip_safe': False,  # Important for shared libraries
}

if not os.getenv("HAXORG_SKIP_PY_HAXORG_BUILD"):
    # Run custom build script before setup
    print("Running custom build script...")
    build(setup_kwargs)
    print("Custom build script completed.")

setup(**setup_kwargs)
