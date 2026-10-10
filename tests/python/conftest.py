#!/usr/bin/env python

import logging
import warnings

import pytest
from beartype.typing import Any
from hstd_py_lib.tracer import TraceCollector

CAT = "conftest"

trace_collector: TraceCollector = None


def pytest_configure(config: Any) -> None:
    "nodoc"
    for logger_name in [
        "plumbum.local",
        "matplotlib.font_manager",
        "graphviz._tools",
        "matplotlib",
        "asyncio",
        "git.cmd",
        "git.util",
    ]:
        logger = logging.getLogger(logger_name)
        logger.disabled = True

    warnings.filterwarnings(
        "ignore",
        category=DeprecationWarning,
        module="pydantic._internal._config",
    )
    warnings.filterwarnings(
        "ignore",
        category=UserWarning,
        module="pydantic._internal._config",
    )
    warnings.filterwarnings(
        "ignore",
        category=pytest.PytestRemovedIn9Warning,
        module="tests.python.conftest",
    )
    warnings.filterwarnings(
        "ignore",
        category=DeprecationWarning,
        module="dominate.dom_tag",
    )
