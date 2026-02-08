"""
Custom PEP 517 build backend that conditionally uses scikit-build-core or setuptools.

This module is the build backend specified in pyproject.toml. It delegates to either
scikit-build-core (for full C++ builds) or setuptools (for Python-only installs).
"""
import os

import scikit_build_core.build
import setuptools.build_meta


def _skip_cxx_build() -> bool:
    return os.environ.get("SKIP_CXX_BUILD", "0") == "1"


def get_requires_for_build_wheel(config_settings=None):
    return ["setuptools>=45", "wheel"] + ["scikit-build-core>=0.5", "pybind11", "conan"]


def get_requires_for_build_sdist(config_settings=None):
    return ["setuptools>=45", "wheel"] + ["scikit-build-core>=0.5", "pybind11", "conan"]


def get_requires_for_build_editable(config_settings=None):
    return get_requires_for_build_wheel(config_settings)


def build_wheel(wheel_directory, config_settings=None, metadata_directory=None):
    if _skip_cxx_build():
        return setuptools.build_meta.build_wheel(wheel_directory, config_settings,
                                                 metadata_directory)
    else:
        return scikit_build_core.build.build_wheel(wheel_directory, config_settings,
                                                   metadata_directory)


def build_sdist(sdist_directory, config_settings=None):
    if _skip_cxx_build():
        return setuptools.build_meta.build_sdist(sdist_directory, config_settings)
    else:
        return scikit_build_core.build.build_sdist(sdist_directory, config_settings)


def build_editable(wheel_directory, config_settings=None, metadata_directory=None):
    if _skip_cxx_build():
        return setuptools.build_meta.build_editable(wheel_directory, config_settings,
                                                    metadata_directory)
    else:
        return scikit_build_core.build.build_editable(wheel_directory, config_settings,
                                                      metadata_directory)


def prepare_metadata_for_build_wheel(metadata_directory, config_settings=None):
    if _skip_cxx_build():
        return setuptools.build_meta.prepare_metadata_for_build_wheel(
            metadata_directory, config_settings)
    else:
        return scikit_build_core.build.prepare(metadata_directory, config_settings)


def prepare_metadata_for_build_editable(metadata_directory, config_settings=None):
    if _skip_cxx_build():
        return setuptools.build_meta.prepare_metadata_for_build_editable(
            metadata_directory, config_settings)
    else:
        return scikit_build_core.build.prepare(metadata_directory, config_settings)
