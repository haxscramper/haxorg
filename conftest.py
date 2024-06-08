import pytest

def pytest_addoption(parser: pytest.Parser) -> None:
    parser.addoption("--markfilter", action="store", help="Filter tests by custom mark expressions")
