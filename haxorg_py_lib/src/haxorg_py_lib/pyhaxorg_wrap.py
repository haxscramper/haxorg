from typing import TYPE_CHECKING

from beartype import beartype

if TYPE_CHECKING:
    from haxorg_py_lib.pyhaxorg import *
else:
    import os as _os

    _debug_import = "HAXORG_PY_LIB_VERBOSE_IMPORT_DEBUG" in _os.environ

    if _debug_import:
        import sys as _sys
        from importlib.machinery import EXTENSION_SUFFIXES as _extension_suffixes
        from pprint import pprint as _pprint

        _pprint(
            {
                "import_target": "haxorg_cpp_py_wrap",
                "importing_module": __name__,
                "importing_file": globals().get("__file__"),
                "cwd": _os.getcwd(),
                "executable": _sys.executable,
                "python_version": _sys.version,
                "implementation": _sys.implementation,
                "platform": _sys.platform,
                "argv": _sys.argv,
                "flags": _sys.flags,
                "prefix": _sys.prefix,
                "base_prefix": _sys.base_prefix,
                "exec_prefix": _sys.exec_prefix,
                "base_exec_prefix": _sys.base_exec_prefix,
                "sys.path": list(_sys.path),
                "sys.meta_path": list(_sys.meta_path),
                "sys.path_hooks": list(_sys.path_hooks),
                "sys.path_importer_cache": dict(_sys.path_importer_cache),
                "extension_suffixes": _extension_suffixes,
                "environment": {
                    name: value
                    for name, value in sorted(_os.environ.items())
                    if name.startswith(("PYTHON", "HAXORG"))
                    or name
                    in {
                        "PATH",
                        "LD_LIBRARY_PATH",
                        "LD_PRELOAD",
                        "VIRTUAL_ENV",
                        "CONDA_PREFIX",
                    }
                },
                "already_loaded_haxorg_modules": {
                    name: {
                        "file": getattr(module, "__file__", None),
                        "spec": getattr(module, "__spec__", None),
                    }
                    for name, module in sorted(_sys.modules.copy().items())
                    if "haxorg" in name
                },
            },
            stream=_sys.stderr,
            sort_dicts=False,
        )
        _sys.stderr.flush()

    import haxorg_cpp_py_wrap as _runtime_package
    from haxorg_cpp_py_wrap import *

    if _debug_import:
        _symbols = sorted(dir(_runtime_package))
        _exports = getattr(_runtime_package, "__all__", None)
        if _exports is None:
            _exports = [
                name for name in vars(_runtime_package) if not name.startswith("_")
            ]

        _spec = getattr(_runtime_package, "__spec__", None)

        _pprint(
            {
                "module": _runtime_package.__name__,
                "package": _runtime_package.__package__,
                "file": getattr(_runtime_package, "__file__", None),
                "package_paths": getattr(_runtime_package, "__path__", None),
                "version": getattr(_runtime_package, "__version__", None),
                "cached": getattr(_runtime_package, "__cached__", None),
                "spec": _spec,
                "spec_origin": getattr(_spec, "origin", None),
                "spec_has_location": getattr(_spec, "has_location", None),
                "spec_search_locations": getattr(
                    _spec, "submodule_search_locations", None
                ),
                "loader": getattr(_runtime_package, "__loader__", None),
                "all_symbols": _symbols,
                "wildcard_imported_symbols": sorted(_exports),
                "loaded_haxorg_modules": {
                    name: {
                        "file": getattr(module, "__file__", None),
                        "spec": getattr(module, "__spec__", None),
                    }
                    for name, module in sorted(_sys.modules.copy().items())
                    if "haxorg" in name
                },
                "sys.path_after_import": list(_sys.path),
            },
            stream=_sys.stderr,
            sort_dicts=False,
        )
        _sys.stderr.flush()

SemSet = set[OrgSemKind]


@beartype
def org_ident_normalize(input_str: str) -> str:
    result = ""
    for c in input_str:
        if c not in {"_", "-"}:
            if c.islower() or c.isdigit():
                result += c
            elif c.isupper():
                result += c.lower()

    return result


@beartype
def treeRepr(node: Org, colored: bool = True, maxDepth: int = 50) -> str:
    return exportToTreeString(  # type: ignore
        node,
        OrgTreeExportOpts(  # type: ignore
            withColor=colored,
            maxDepth=maxDepth,
        ),
    )
