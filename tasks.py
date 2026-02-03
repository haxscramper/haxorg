# mypy: ignore-errors

graphviz_logger = logging.getLogger("graphviz._tools")
graphviz_logger.setLevel(logging.WARNING)
import graphviz


def custom_traceback_handler(exc_type, exc_value, exc_traceback) -> None:
    """
    Custom traceback handler that filters and prints stack traces
    only for frames that originate from 'tasks.py'.
    """
    log(CAT).error("tasks traceback ----------------------")
    for frame in traceback.extract_tb(exc_traceback):
        log(CAT).error("File \"{}\", line {}, in {}  {}".format(
            frame.filename,
            frame.lineno,
            frame.name,
            frame.line,
        ))

    log(CAT).error(f"{exc_type}, {exc_value}")


# Register the custom traceback handler
sys.excepthook = custom_traceback_handler


def get_py_env(ctx: Context) -> Dict[str, str]:
    if get_config(ctx).instrument.asan:
        asan_lib = get_llvm_root(
            f"lib/clang/{LLVM_MAJOR}/lib/x86_64-unknown-linux-gnu/libclang_rt.asan.so")

        assert asan_lib.exists(), asan_lib

        return {
            "LD_PRELOAD": str(asan_lib),
            "ASAN_OPTIONS": "detect_leaks=0",
        }

    else:
        return {}


@beartype
def create_graph(call_map: Dict[Callable, List[Callable]]) -> graphviz.Digraph:
    dot = graphviz.Digraph(comment='Function Call Graph')
    dot.attr(rankdir="LR")

    for func, callees in call_map.items():
        func_name = func.__name__
        task_name = func_name.replace("_", "-")
        if func.__doc__:
            doc_text = "<BR/>".join(textwrap.wrap(func.__doc__, width=50))
            func_label = f"<<B>{task_name}</B><BR/><FONT POINT-SIZE='10'>{doc_text}</FONT>>"

        else:
            func_label = task_name

        dot.node(func_name, label=func_label, shape='rectangle', fontname='Iosevka')

        for callee in callees:
            callee_name = callee.__name__
            dot.node(callee_name, shape='rectangle', fontname='Iosevka')
            dot.edge(callee_name, func_name)

    return dot


@haxorg_task()
def generate_org_task_graph(ctx: Context, dot_file: str = "/tmp/graph.dot") -> None:
    """Generate graphviz for task graph"""
    graph = create_graph(TASK_DEPS)
    file = Path(dot_file)
    file.write_text(graph.source)
    log(CAT).info(f"Wrote graph to {dot_file}")
    run_command(ctx, "dot", [
        "-Tpng",
        file,
        "-o",
        file.with_suffix(".png"),
    ])


def get_poetry_lldb(test: str) -> list[str]:
    return [
        "run",
        "lldb",  # NOTE using system-provided LLDB instead of the get_llvm_root("bin/lldb"),
        # because the latter one is not guaranteed to be compiled with the python
        # installed on the system. For example, 17.0.6 required python 3.10, but the
        # arch linux already moved to 3.11 here.
        "--batch",
        *get_lldb_py_import(),
        "-o",
        f"run {test}",
        *get_lldb_source_on_crash(),
        "--",
        "python",
    ]


@haxorg_task(iterable=["arg"])
def run_py_debug_script(ctx: Context, arg) -> None:
    run_command(
        ctx,
        "poetry",
        get_poetry_lldb(" ".join(arg)),
        allow_fail=True,
        env=get_py_env(ctx),
    )


@haxorg_task(dependencies=[build_haxorg, generate_python_protobuf_files])
def run_py_test_debug(ctx: Context, test: str) -> None:
    log(CAT).info(get_py_env(ctx))
    test: Path = Path(test)
    if not test.is_absolute():
        test = get_script_root(test)

    retcode, _, _ = run_command(
        ctx,
        "poetry",
        get_poetry_lldb(test),
        allow_fail=True,
        env=get_py_env(ctx),
    )

    if retcode != 0:
        exit(1)


def get_poetry_import_paths(ctx: Context) -> List[Path]:
    return [
        Path(it) for it in run_command(
            ctx,
            "poetry",
            ['run', 'python', '-c', 'import sys; print("\\n".join(sys.path))'],
            capture=True,
        )[1].split("\n") if 0 < len(it.strip())
    ]
