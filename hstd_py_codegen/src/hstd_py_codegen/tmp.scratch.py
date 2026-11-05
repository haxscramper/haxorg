@pytest.mark.test_release
def test_coverall_nim(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver

    value = (
        refl_test_driver.run_reflection_tool_provider(
            {str(INPUT): INPUT.read_text()},
            code_dir=INPUT.parent,
            output_dir=stable_test_dir,
        )
        .wraps[0]
        .tu
    )

    for _enum in value.enums:
        refl_test_driver.get_nim_code(_enum)

    for _function in value.functions:
        refl_test_driver.get_nim_code(_function)

    for _record in value.structs:
        refl_test_driver.get_nim_code(_record)

    for _typedef in value.typedefs:
        refl_test_driver.get_nim_code(_typedef)


from pathlib import Path
from pprint import pprint

import pytest
from more_itertools import first_true


@pytest.mark.test_release
def test_enum_field_extract(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver

    enum = refl_test_driver.get_enum(
        "enum CEnum { Member1, Member2 };",
        stable_test_dir=stable_test_dir,
    )
    assert enum.Name.Name == "CEnum"
    assert len(enum.Fields) == 2
    assert enum.Fields[0].Name == "Member1"
    assert enum.Fields[1].Name == "Member2"


@pytest.mark.test_release
def test_namespaced_enum_extract(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver

    enum = refl_test_driver.get_enum(
        "namespace Space { enum Enum { member1 }; }",
        stable_test_dir=stable_test_dir,
    )
    assert enum.Name.Name == "Enum"
    assert len(enum.Name.Spaces) == 1
    assert enum.Name.Spaces[0].Name == "Space"


@pytest.mark.test_release
def test_nim_enum_conversion(stable_test_dir: Path) -> None:
    import repo_py_orchestrate.codegen_config.wrapper_gen_nim as gen_nim
    import tests.python.refl.refl_test_driver as refl_test_driver

    con = refl_test_driver.get_nim_code(
        refl_test_driver.get_enum(
            "enum En { Field1, Field2 };",
            stable_test_dir=stable_test_dir,
        )
    )

    with open("/tmp/a.py", "w") as file:
        pprint(con, stream=file)

    raw_wrap = first_true(con.types, default=None, pred=lambda it: it.Name == "c_En")
    assert raw_wrap
    assert len(raw_wrap.Fields) == 2
    assert raw_wrap.Fields[0].Name == "c_Field1"
    assert raw_wrap.Fields[1].Name == "c_Field2"

    nim_wrap = first_true(con.types, default=None, pred=lambda it: it.Name == "En")
    assert nim_wrap
    assert len(nim_wrap.Fields) == 2
    assert nim_wrap.Fields[0].Name == "Field1"
    assert nim_wrap.Fields[1].Name == "Field2"

    # Convert set of nim enums to C-style set with bitor components
    nim_set_to_cint = first_true(
        con.procs,
        default=None,
        pred=lambda it: it.Name == "toCInt" and it.Arguments[0].Type.Name == "set",
    )

    assert nim_set_to_cint
    assert len(nim_set_to_cint.Arguments) == 1
    assert nim_set_to_cint.ReturnType.Name == "cint"
    assert nim_set_to_cint.Arguments[0].Type.Parameters[0].Name == "En"
    assert nim_set_to_cint.Kind == gen_nim.nim.FunctionKind.CONVERTER

    # Convert C enum to cint value
    c_en_to_cint = first_true(
        con.procs,
        default=None,
        pred=lambda it: it.Name == "toCInt" and it.Arguments[0].Type.Name == "c_En",
    )

    assert c_en_to_cint
    assert len(c_en_to_cint.Arguments) == 1
    assert c_en_to_cint.ReturnType.Name == "cint"
    assert nim_set_to_cint.Kind == gen_nim.nim.FunctionKind.CONVERTER

    # Convert nim enum to cint value
    en_to_cint = first_true(
        con.procs,
        default=None,
        pred=lambda it: it.Name == "toCInt" and it.Arguments[0].Type.Name == "En",
    )

    assert en_to_cint
    assert len(en_to_cint.Arguments) == 1
    assert en_to_cint.ReturnType.Name == "cint"
    assert nim_set_to_cint.Kind == gen_nim.nim.FunctionKind.CONVERTER

    nim_to_c = first_true(con.procs, default=None, pred=lambda it: it.Name == "to_c_En")
    assert nim_to_c
    assert len(nim_to_c.Arguments) == 1
    assert nim_to_c.Arguments[0].Type.Name == "En"
    assert nim_to_c.ReturnType.Name == "c_En"

    c_to_nim = first_true(con.procs, default=None, pred=lambda it: it.Name == "to_En")
    assert c_to_nim
    assert len(c_to_nim.Arguments) == 1
    assert c_to_nim.Arguments[0].Type.Name == "c_En"
    assert c_to_nim.ReturnType.Name == "En"


@haxorg_task()
def generate_binary_size_report(ctx: TaskContext) -> None:
    from py_repository.code_analysis import gen_symbol_size_report as gsrs

    if ctx.config.binary_size_conf.update_db:
        build_targets(ctx=ctx, targets=["reflection_tool"])
        gsrs.generate_binary_size_db(ctx)
    gsrs.generate_symbol_size_report(ctx)


@haxorg_task(dependencies=[generate_python_protobuf_files])
def generate_include_graph(ctx: TaskContext) -> None:
    compile_commands = get_script_root(ctx, "build/haxorg/compile_commands.json")
    header_commands = get_script_root(
        ctx, "build/haxorg/compile_commands_with_headers.json"
    )
    # re-configure the whole project to generate new compilation database.
    configure_cmake_haxorg(ctx=ctx)
    build_targets(ctx=ctx, targets=["reflection_tool"])

    from py_repository.code_analysis.gen_include_graph import gen_include_graph

    gen_include_graph(
        ctx,
        compile_commands=compile_commands,
        header_commands=header_commands,
    )


@haxorg_task(dependencies=[generate_python_protobuf_files])
def generate_import_graph(ctx: TaskContext) -> None:
    """
    Generate import graph for all sub-projects and modules.
    """
    from py_repository.code_analysis import gen_import_graph

    import_graph = gen_import_graph.gen_import_graph(ctx)
    tmp = get_tmpdir("haxorg_import")
    ensure_existing_dir(ctx, tmp)
    tmp.joinpath("result.json").write_text(import_graph.model_dump_json(indent=2))
    ig_graph = gen_import_graph.import_graph_to_igraph(import_graph)
    gv_graph = gen_import_graph.import_igraph_to_graphviz(ig_graph)
    gv_graph.render(tmp.joinpath("result"), format="png", engine="dot")
    ig_graph.write_graphml(str(tmp.joinpath("result.graphml")))


@haxorg_task(
    dependencies=[generate_python_protobuf_files, build_and_setup_text_layout_lib]
)
def generate_reflection_snapshot(ctx: TaskContext) -> None:
    """Generate new source code reflection file for the python source code wrapper"""
    compile_commands = get_script_root(ctx, "build/haxorg/compile_commands.json")
    build_targets(
        ctx=ctx,
        targets=["reflection_tool"]
        + [
            # trigger protobuf file generation to allow for clang semantic
            # analysis to properly resolve all headers
            f"{it}_generate_files"
            for it in [
                "haxorg_sem_protobuf",
                "haxorg_imm_graph_protobuf",
                "hstd_proto_base_graph",
                "hstd_proto_graphviz_graph",
            ]
        ],
    )

    from py_codegen.refl_read import open_proto_file

    task = "pyhaxorg"
    out_file = get_build_root(ctx, f"{task}.pb")
    src_file = get_script_root(ctx, "src/py_libs/pyhaxorg/pyhaxorg_manual_refl.cpp")

    run_command_with_json_args(
        ctx,
        str(get_build_root(ctx, "haxorg/reflection_tool")),
        args=cov.ReflectionCLI(
            output=str(out_file),
            input=[str(src_file)],
            log_path=str(get_workflow_out(ctx, f"{task}_reflection_run.log")),
            mode=cov.Mode.AllAnotatedSymbols,
            verbose_log=ctx.config.log_level == HaxorgLogLevel.VERBOSE,
            reflection=cov.ReflectionConfig(
                compilation_database=str(compile_commands),
            ),
        ).model_dump(),
    )

    reflection_debug = get_tmpdir().joinpath(f"reflection_{task}.json")
    reflection_debug.write_text(open_proto_file(out_file).to_json(2))

    logger.info(f"Updated reflection, wrote debug JSON to {reflection_debug}")


# TODO Make compiled reflection generation build optional
@haxorg_task(dependencies=[generate_reflection_snapshot])
def generate_haxorg_sources(ctx: TaskContext) -> None:
    """Update auto-generated source files"""
    assert not ctx.config.emscripten.build, "Codegen is not supported for the EMCC build"
    ctx.run(build_and_setup_text_layout_lib)
    from py_codegen.codegen import run_codegen_task

    task = "pyhaxorg"
    run_codegen_task(
        reflection_path=get_build_root(ctx).joinpath(f"{task}.pb"),
        is_tmp_codegen=ctx.config.generate_sources_conf.tmp,
        manual_tu_path=get_script_root(
            ctx, "scripts/py_codegen/py_codegen/codegen_extra_types.json"
        ),
    )

    logger.info("Updated code definitions")
