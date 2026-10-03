import itertools
import json
from dataclasses import dataclass, field
from pathlib import Path

from beartype import beartype
from beartype.typing import Any, Dict, Union
from hstd_py_codegen.gen_cpp.codegen_ir import (
    GenTypeMap,
)
from hstd_py_codegen.langs import (
    astbuilder_cpp,
    astbuilder_embind,
    astbuilder_nim,
)
from hstd_py_codegen.langs.astbuilder_embind_config import (
    EmbindAstbuilderConfig,
)
from hstd_py_codegen.langs.astbuilder_nanobind import (
    NbModule,
    Py11Entry,
    Py11Field,
)
from hstd_py_codegen.langs.astbuilder_nanobind_config import (
    NanobindAstbuilderConfig,
)
from hstd_py_codegen.langs.astbuilder_nim_config import (
    NimAstbuilderConfig,
    NimAstbuilderStaticConfig,
)
from hstd_py_codegen.read_cpp.refl_wrapper_graph import (
    GenGraph,
)
from hstd_py_lib.script_logging import pprint_to_file, to_debug_json
from hstd_py_text_layout.base.wrap import TextLayout
from plumbum import CommandNotFound, local

import repo_py_orchestrate.src.repo_py_orchestrate.codegen_config.wrapper_gen_nim as gen_nim


@beartype
def get_nim_code(content: gen_nim.GenTuUnion) -> gen_nim.ConvRes:
    t = gen_nim.nim.TextLayout()
    builder = gen_nim.nim.ASTBuilder(t, conf=NimAstbuilderConfig(type_map=GenTypeMap()))
    return gen_nim.conv_res_to_nim(builder, content)


@beartype
def format_nim_code(
    refl: ReflProviderRunResult,
    is_cpp_wrap: bool = True,
    with_header_imports: bool = True,
) -> Dict[str, gen_nim.GenNimResult]:
    graph: gen_nim.GenGraph = gen_nim.GenGraph()
    for wrap in refl.wraps:
        graph.add_unit(wrap)

    graph.connect_usages()
    graph.group_connected_files()

    def get_out_path(path: Path) -> Path:
        return path.with_suffix(".nim")

    mapped: Dict[str, gen_nim.GenNimResult] = {}
    for sub in graph.subgraphs:
        code = gen_nim.to_nim(
            graph=graph,
            sub=sub,
            conf=NimAstbuilderConfig(
                type_map=GenTypeMap(),
                opts=NimAstbuilderStaticConfig(
                    with_header_imports=with_header_imports,
                    is_cpp_wrap=is_cpp_wrap,
                ),
            ),
            output_directory=refl.code_dir,
            get_out_path=get_out_path,
        )

        assert code
        mapped[str(get_out_path(sub.original).relative_to(refl.code_dir))] = code

    return mapped


@beartype
def has_nim_installed() -> bool:
    try:
        local["nim"]
        return True

    except CommandNotFound:
        return False


@beartype
def compile_nim_path(file: Path, binary: Path) -> None:
    cmd = local["nim"]
    cmd.run(["cpp", f"-o={binary}", str(file)])


@beartype
def compile_nim_code(code_dir: Path, files: Dict[str, str]) -> None:
    for file, content in files.items():
        code_dir.joinpath(file).write_text(content)

    for file in files.keys():
        compile_nim_path(
            code_dir.joinpath(file), code_dir.joinpath(file).with_suffix(".bin")
        )


@beartype
def verify_nim_code(
    code_dir: Path, formatted: Dict[str, gen_nim.GenNimResult], test_text: str
) -> tuple[int, str, str]:
    compile_nim_code(
        code_dir=code_dir, files={file: res.content for file, res in formatted.items()}
    )

    compile_nim_code(code_dir, files={"main.nim": test_text})

    binary = local[str(code_dir.joinpath("main.bin"))]
    retcode, stdout, stderr = binary.run()
    return (retcode, stdout, stderr)


@beartype
@dataclass
class AllCodeWrappers:
    nim: list[gen_nim.GenNimResult] = field(default_factory=list)
    python: list[NbModule] = field(default_factory=list)
    embind: list[astbuilder_embind.WasmModule] = field(default_factory=list)

    def getNimEntries(
        self, name: str
    ) -> list[astbuilder_nim.NimEntryParams | astbuilder_nim.IdentParams]:
        return list(itertools.chain(*[gen.getEntryForName(name) for gen in self.nim]))

    def getPythonEntries(self, name: str) -> list[Py11Entry | Py11Field]:
        return list(itertools.chain(*[gen.getEntryForName(name) for gen in self.python]))

    def getWasmEntries(self, name: str) -> list[astbuilder_embind.WasmUnion]:
        return list(itertools.chain(*[gen.getEntryForName(name) for gen in self.embind]))


@beartype
def get_all_code(
    text: Union[str, Dict[str, str]], *, stable_test_dir: Path, **kwargs: Any
) -> AllCodeWrappers:
    wraps = run_reflection_tool_provider(
        text,
        Path(stable_test_dir),
        output_dir=stable_test_dir,
        only_annotated=True,
        **kwargs,
    )

    result = AllCodeWrappers()
    type_map = GenTypeMap()

    gen_graph = GenGraph()
    for sub in wraps.wraps:
        gen_graph.add_unit(sub)

        for entry in sub.tu.structs + sub.tu.enums:
            type_map.add_type(entry)

    t = TextLayout()
    cpp_ast = astbuilder_cpp.ASTBuilder(t)

    for sub in gen_graph.subgraphs:

        def get_out_path(in_path: Path) -> Path:
            return stable_test_dir.joinpath(in_path.stem)

        nim_conf = NimAstbuilderConfig(type_map=type_map)

        result.nim.append(
            gen_nim.to_nim(
                gen_graph,
                sub,
                get_out_path=get_out_path,
                conf=nim_conf,
                output_directory=stable_test_dir.joinpath("nim"),
            )
        )

        py_conf = NanobindAstbuilderConfig(type_map=type_map)
        nb_module = NbModule(sub.original.name, py_conf)

        for e in gen_graph.get_entries(sub):
            nb_module.add_decl(e, cpp_ast)

        result.python.append(nb_module)

        em_conf = EmbindAstbuilderConfig(type_map=type_map)
        embind_module = astbuilder_embind.WasmModule(sub.original.name, em_conf)

        for e in gen_graph.get_entries(sub):
            embind_module.add_decl(e)

        result.embind.append(embind_module)

    pprint_to_file(result, stable_test_dir.joinpath("result.py"), width=120)
    stable_test_dir.joinpath("result.json").write_text(
        json.dumps(to_debug_json(result), indent=2)
    )

    return result
