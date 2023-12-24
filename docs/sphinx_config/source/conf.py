project = "haxorg"
copyright = "2023, haxscramper"
author = "haxscramper"

extensions = [
    "sphinx.ext.todo", "sphinx.ext.viewcode", "sphinx.ext.autodoc",
    "sphinx.ext.coverage",
]

templates_path = ["_templates"]
exclude_patterns = []
coverage_show_missing_items = True

html_theme = "alabaster"
html_static_path = ["_static"]

import sys
from pathlib import Path

full_path = Path(__file__).parent / "../api_source"
sys.path.insert(0, str(full_path.resolve()))

import sphinx_autoconf

