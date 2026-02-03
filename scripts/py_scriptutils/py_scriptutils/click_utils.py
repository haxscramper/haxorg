from beartype import beartype
from beartype.typing import Any
from beartype.typing import List
from click.testing import CliRunner
from click.testing import Result


def check_cli(result: Result) -> None:
    if result.exception:
        raise result.exception

    assert result.exit_code == 0, result.output


@beartype
def click_run_test(cmd: Any, args: List[str]) -> None:
    runner = CliRunner()
    result = runner.invoke(cmd, args)
    check_cli(result)
