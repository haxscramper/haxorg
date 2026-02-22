"""
Custom PEP 517 build backend that conditionally uses scikit-build-core or setuptools.

This module is the build backend specified in pyproject.toml. It delegates to either
scikit-build-core (for full C++ builds) or setuptools (for Python-only/source installs).
"""

from dataclasses import dataclass
import os
from typing import Any, Mapping, Optional

_CUSTOM_CFG_KEYS = {"HAXORG_PY_SOURCE_DISTRIBUTION"}


def _filter_for_downstream(config_settings: Optional[Mapping[str, Any]]):
    """Remove our private config keys before delegating to other backends."""
    if not config_settings:
        return None
    filtered = {k: v for k, v in config_settings.items() if k not in _CUSTOM_CFG_KEYS}
    return filtered or None


def _cfg_get(config_settings: Optional[Mapping[str, Any]], key: str, default=None):
    if not config_settings:
        return default
    val = config_settings.get(key, default)
    if isinstance(val, (list, tuple)):
        return val[-1] if val else default
    return val


def _as_bool(value: Any, default: bool = False) -> bool:
    if value is None:
        return default
    if isinstance(value, bool):
        return value
    s = str(value).strip().lower()
    if s in {"1", "true", "yes", "on"}:
        return True
    if s in {"0", "false", "no", "off"}:
        return False
    return default


@dataclass(frozen=True)
class HaxorgBuildConfig:
    """
    HAXORG_PY_SOURCE_DISTRIBUTION == True  -> setuptools (no C++ build)
    HAXORG_PY_SOURCE_DISTRIBUTION == False -> scikit-build-core (CMake build)
    """
    HAXORG_PY_SOURCE_DISTRIBUTION: bool = False

    @classmethod
    def from_config_settings(cls, config_settings: Optional[Mapping[str, Any]]):
        return cls(HAXORG_PY_SOURCE_DISTRIBUTION=_as_bool(
            _cfg_get(config_settings, "HAXORG_PY_SOURCE_DISTRIBUTION", None),
            False,
        ))


def _binary_build_requires() -> list[str]:
    # Things you only want present for the CMake/pybind/conan build.
    return [
        "scikit-build-core>=0.5",
        "nanobind",
        "conan",
    ]


# --- PEP 517 dynamic requirements --------------------------------------------


def get_requires_for_build_wheel(config_settings=None):
    cfg = HaxorgBuildConfig.from_config_settings(config_settings)
    if cfg.HAXORG_PY_SOURCE_DISTRIBUTION:
        return []
    return _binary_build_requires()


def get_requires_for_build_editable(config_settings=None):
    return get_requires_for_build_wheel(config_settings)


def get_requires_for_build_sdist(config_settings=None):
    # Usually sdists are fine without the C++ toolchain;
    # if your sdist generation needs it, switch this to mirror wheel.
    return []


# --- Build hooks -------------------------------------------------------------


def build_wheel(wheel_directory, config_settings=None, metadata_directory=None):
    cfg = HaxorgBuildConfig.from_config_settings(config_settings)
    downstream = _filter_for_downstream(config_settings)
    if cfg.HAXORG_PY_SOURCE_DISTRIBUTION:
        import setuptools.build_meta as st
        return st.build_wheel(wheel_directory, downstream, metadata_directory)
    else:
        import scikit_build_core.build as sk
        return sk.build_wheel(wheel_directory, downstream, metadata_directory)


def build_editable(wheel_directory, config_settings=None, metadata_directory=None):
    cfg = HaxorgBuildConfig.from_config_settings(config_settings)
    downstream = _filter_for_downstream(config_settings)
    if cfg.HAXORG_PY_SOURCE_DISTRIBUTION:
        import setuptools.build_meta as st
        return st.build_editable(wheel_directory, downstream, metadata_directory)
    else:
        import scikit_build_core.build as sk
        return sk.build_editable(wheel_directory, downstream, metadata_directory)


def build_sdist(sdist_directory, config_settings=None):
    cfg = HaxorgBuildConfig.from_config_settings(config_settings)
    downstream = _filter_for_downstream(config_settings)
    if cfg.HAXORG_PY_SOURCE_DISTRIBUTION:
        import setuptools.build_meta as st
        return st.build_sdist(sdist_directory, downstream)
    else:
        import scikit_build_core.build as sk
        return sk.build_sdist(sdist_directory, downstream)


def prepare_metadata_for_build_wheel(metadata_directory, config_settings=None):
    cfg = HaxorgBuildConfig.from_config_settings(config_settings)
    downstream = _filter_for_downstream(config_settings)
    if cfg.HAXORG_PY_SOURCE_DISTRIBUTION:
        import setuptools.build_meta as st
        return st.prepare_metadata_for_build_wheel(metadata_directory, downstream)
    else:
        import scikit_build_core.build as sk
        return sk.prepare_metadata_for_build_wheel(metadata_directory, downstream)


def prepare_metadata_for_build_editable(metadata_directory, config_settings=None):
    cfg = HaxorgBuildConfig.from_config_settings(config_settings)
    downstream = _filter_for_downstream(config_settings)
    if cfg.HAXORG_PY_SOURCE_DISTRIBUTION:
        import setuptools.build_meta as st
        return st.prepare_metadata_for_build_editable(metadata_directory, downstream)
    else:
        import scikit_build_core.build as sk

        # If your scikit-build-core version lacks this hook, you may need to
        # fall back to prepare_metadata_for_build_wheel here.
        return sk.prepare_metadata_for_build_editable(metadata_directory, downstream)
