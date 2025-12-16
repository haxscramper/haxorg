#!/usr/bin/env python

import json
from pathlib import Path
from py_repository.repo_tasks.common import get_build_root
from py_repository.repo_tasks.config import HaxorgConfig, HaxorgLogLevel
import py_repository.repo_tasks.workflow_utils as workflow_utils
from py_repository.repo_tasks import (
    haxorg_base,
    haxorg_build,
    haxorg_codegen,
    haxorg_coverage,
    haxorg_docker,
    haxorg_docs,
    haxorg_tests,
    examples_build,
)

from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.toml_config_profiler import apply_options, merge_dicts, options_from_model, pack_context
from pydantic import BaseModel, Field
from beartype.typing import Optional, Any
import rich_click as click
from py_scriptutils.script_logging import log, setup_multi_file_logging
import logging

CAT = __name__

logging.getLogger("plumbum.local").setLevel(logging.WARNING)


class WorkflowOptions(BaseModel):
    task: Optional[str] = Field(default=None)
    workflow_log_dir: str = "/tmp/haxorg/workflow_log"
    stamp_root: str = str(get_haxorg_repo_root_path().joinpath("build").joinpath("workflow_stamps"))
    config_override: Optional[Path] = None
    verbose: bool = False


def workflow_options(f: Any) -> Any:
    return apply_options(f, options_from_model(WorkflowOptions))


@click.command()
@click.argument("cmd")
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@workflow_options
@click.pass_context
def cli(ctx: click.Context, cmd: str, config: str, **kwargs: Any) -> None:
    pack_context(ctx, "root", WorkflowOptions, config=config, kwargs=kwargs)
    opts: WorkflowOptions = ctx.obj["root"]
    setup_multi_file_logging(Path(opts.workflow_log_dir))

    graph = workflow_utils.create_dag_from_tasks(workflow_utils.get_haxorg_tasks())
    config_json = HaxorgConfig().model_dump()

    if opts.config_override:
        config_json = merge_dicts(
            [config_json, json.loads(opts.config_override.read_text())])

    config_obj = HaxorgConfig(**config_json)
    if opts.verbose:
        config_obj.log_level = HaxorgLogLevel.VERBOSE

    context = workflow_utils.TaskContext(
        graph=graph,
        stamp_root=Path(opts.stamp_root),
        config=config_obj,
    )

    log(CAT).info(f"{context.config.model_dump_json(indent=2)}")
    log(CAT).info(opts.config_override)

    match cmd:
        case "run":
            assert opts.task is not None
            context.run(opts.task, ctx=context)
            log(CAT).info("Done")

        case "list_tasks":
            for t in graph.get_tasks():
                print(t)

        case _:
            raise ValueError(f"Unknown command {cmd}")


if __name__ == "__main__":
    cli()

# main_pipeline = workflow_utils.create_dag_from_tasks(workflow_utils.get_haxorg_tasks(),
#                                                     "haxorg_main_pipeline",
#                                                     "Main haxorg build pipeline")

# for dag in workflow_utils.create_individual_dags(workflow_utils.get_haxorg_tasks()):
#     globals()[f"airflow_dag_id_{dag.dag_id}"] = dag
