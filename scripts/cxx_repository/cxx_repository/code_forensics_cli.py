from pathlib import Path

from beartype.typing import Any
from cxx_repository import burndown, orm_model
from cxx_repository.code_forensics import run_forensics
from py_scriptutils.script_logging import log
from py_scriptutils.sqlalchemy_utils import open_sqlite
from py_scriptutils.toml_config_profiler import (
    get_user_provided_params,
    get_wrap_options,
    pack_context,
)
from pydantic import BaseModel
import rich_click as click


class CodeForensicsCLI(BaseModel, extra="forbid"):
    input: str
    out: str
    skip_if_exists: bool = False


@click.command()
@get_wrap_options(CodeForensicsCLI)
@click.pass_context
def main(ctx: click.Context, **kwargs: Any):
    cli: CodeForensicsCLI = pack_context(ctx,
                                         CodeForensicsCLI,
                                         cli_kwargs=get_user_provided_params(ctx))

    Path(cli.out).parent.mkdir(parents=True, exist_ok=True)
    if not Path(cli.out).exists() or not cli.skip_if_exists:
        run_forensics(Path(cli.input), db=cli.out)

    log().info(f"cli.out = {Path(cli.out).resolve()}")
    engine = open_sqlite(Path(cli.out), orm_model.Base)

    burndown.run_for(engine)


if __name__ == "__main__":
    main()
