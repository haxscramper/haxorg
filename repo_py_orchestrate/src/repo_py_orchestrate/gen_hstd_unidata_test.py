import sys
from pathlib import Path

import click
import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from hstd_py_codegen.gen_cpp.codegen_ir import (
    GenFiles,
    GenTu,
    GenTuNamespace,
    GenTuPass,
    GenUnit,
    QualType,
)
from hstd_py_codegen.gen_cpp.codegen_write import gen_description_files
from hstd_py_lib.script_logging import get_custom_traceback_handler
from hstd_py_text_layout.base.wrap import TextLayout

from repo_py_orchestrate.codegen_config.type_models.hstd_test_model import M as HstdModel
from repo_py_orchestrate.codegen_config.type_models.model_to_gentu import ModelToGenTu


@click.command()
@click.argument("root_dir", type=Path)
def main(root_dir: Path):
    t = TextLayout()
    builder = cpp.ASTBuilder(t)
    HstdModel.type_check()
    model = HstdModel.finalize()
    converter = ModelToGenTu(model, ast=builder)
    types = converter.convert()

    sources = GenFiles(
        [
            GenUnit(
                header=GenTu(
                    root_dir / "hstd_cpp_lib/tests/tUnidataDSLModel.hpp",
                    [
                        GenTuPass("#pragma once"),
                        GenTuPass("#include <hstd_cpp_lib/system/basic_templates.hpp>"),
                        GenTuPass("#include <hstd_cpp_lib/system/reflection.hpp>"),
                        GenTuPass("#include <hstd_cpp_lib/stdlib/containers/Opt.hpp>"),
                        GenTuPass("#include <hstd_cpp_lib/stdlib/containers/Vec.hpp>"),
                        GenTuPass("#include <hstd_cpp_lib/stdlib/containers/Map.hpp>"),
                        GenTuPass(
                            "#include <hstd_cpp_lib/proto_serde/hstd_unidata_validate.hpp>"
                        ),
                        GenTuNamespace(
                            QualType(Name="hstd::unidata_dsl::test"),
                            types,
                        ),
                    ],
                ),
                source=GenTu(
                    root_dir / "hstd_cpp_lib/tests/tUnidataDSLModel.cpp",
                    [
                        GenTuPass('#include "tUnidataDSLModel.hpp"'),
                        *types,
                    ],
                ),
            )
        ]
    )

    gen_description_files(sources, builder, t)


if __name__ == "__main__":
    sys.excepthook = get_custom_traceback_handler(
        show_args=False,
    )
    main()
