from beartype import beartype
from py_repository.repo_tasks.common import (
    get_build_root,)
from py_repository.repo_tasks.deps_build import build_develop_deps
from py_repository.repo_tasks.examples_build import (
    build_examples,
    run_examples,
    run_js_test_example,
)
from py_repository.repo_tasks.haxorg_build import build_haxorg, install_haxorg_develop
from py_repository.repo_tasks.haxorg_codegen import (
    generate_binary_size_report,
    generate_haxorg_sources,
    generate_include_graph,
    generate_python_protobuf_files,
)
from py_repository.repo_tasks.haxorg_coverage import run_cxx_coverage_merge
from py_repository.repo_tasks.haxorg_docs import build_custom_docs
from py_repository.repo_tasks.haxorg_tests import run_py_tests
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_scriptutils.script_logging import log

CAT = __name__


@haxorg_task()
@beartype
def run_develop_ci(ctx: TaskContext) -> None:
    "Execute all CI tasks"
    conf = ctx.config

    if conf.develop_ci_conf.coverage:
        for file in get_build_root(ctx).rglob("*.gcda"):
            file.unlink()

    log(CAT).info("Running binary task set")
    if conf.develop_ci_conf.deps:
        ctx.run(build_develop_deps, ctx=ctx)

    if conf.develop_ci_conf.install:
        ctx.run(install_haxorg_develop, ctx=ctx)

    if conf.develop_ci_conf.build:
        ctx.run(build_haxorg, ctx=ctx)

    if conf.develop_ci_conf.example_build:
        ctx.run(build_examples, ctx=ctx)

    if conf.develop_ci_conf.reflection:
        ctx.run(generate_haxorg_sources, ctx=ctx)

    if conf.develop_ci_conf.test:
        ctx.run(generate_python_protobuf_files, ctx=ctx)
        ctx.run(run_py_tests, ctx=ctx)

    if conf.develop_ci_conf.example_run:
        ctx.run(run_examples, ctx=ctx)

    if conf.develop_ci_conf.coverage:
        assert conf.instrument.coverage, "Coverage was enabled in the workflow develop CI configuration, but not in the build"
        ctx.run(run_cxx_coverage_merge, ctx=ctx)

    if conf.develop_ci_conf.docs:
        ctx.run(build_custom_docs, ctx=ctx)

    if conf.develop_ci_conf.include_graph:
        ctx.run(generate_include_graph, ctx=ctx)

    if conf.develop_ci_conf.symbol_size:
        ctx.run(generate_binary_size_report, ctx=ctx)

    log(CAT).info("Running EMCC task set")
    emcc_conf = conf.model_copy()
    emcc_conf.emscripten.build = True
    emcc_conf.instrument.coverage = False
    emcc_conf.use.qt = False
    emcc_context = ctx.with_temp_config(emcc_conf)

    if conf.develop_ci_conf.emscripten_deps:
        emcc_context.run(build_develop_deps, ctx=emcc_context)

    if conf.develop_ci_conf.emscripten_build:
        emcc_context.run(build_haxorg, ctx=emcc_context)

    if conf.develop_ci_conf.emscripten_test:
        emcc_context.run(run_js_test_example, ctx=emcc_context)
