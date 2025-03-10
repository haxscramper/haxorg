# -*- coding: utf-8 -*-
from setuptools import setup

packages = \
['py_haxorg']

package_data = \
{'': ['*']}

setup_kwargs = {
    'name': 'py-haxorg',
    'version': '0.1.0',
    'description': '',
    'long_description': '',
    'author': 'haxscramper',
    'author_email': 'haxscramper@gmail.com',
    'maintainer': 'None',
    'maintainer_email': 'None',
    'url': 'None',
    'packages': packages,
    'package_data': package_data,
    'python_requires': '>=3.9.0,<3.14',
}
from build import *
build(setup_kwargs)

setup(**setup_kwargs)
