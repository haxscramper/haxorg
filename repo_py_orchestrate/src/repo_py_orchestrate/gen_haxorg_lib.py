import sys
from pathlib import Path

import click
import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from hstd_py_codegen.gen_cpp.codegen_write import gen_description_files
from hstd_py_lib.script_logging import get_custom_traceback_handler
from hstd_py_text_layout.base.wrap import TextLayout

from repo_py_orchestrate.codegen_config.codegen import (
    gen_haxorg_base_sources1,
)
from repo_py_orchestrate.codegen_config.org_codegen_data import COMMON_CONTEXT_TU
from repo_py_orchestrate.codegen_config.type_models.model_to_gentu import (
    get_pyhaxorg_type_groups_via_dsl,
)


@click.command()
@click.argument("root_dir", type=Path)
def main(root_dir: Path):
    t = TextLayout()
    builder = cpp.ASTBuilder(t)
    model = get_pyhaxorg_type_groups_via_dsl(builder)
    _, sources = gen_haxorg_base_sources1(
        root_dir,
        t=t,
        builder=builder,
        groups=model,
        context_tu=COMMON_CONTEXT_TU,
    )
    gen_description_files(sources, builder, t)


if __name__ == "__main__":
    sys.excepthook = get_custom_traceback_handler(
        show_args=False,
    )
    main()
