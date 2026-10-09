from pathlib import Path

import click
import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from hstd_py_codegen.gen_cpp.codegen_write import gen_description_files
from hstd_py_text_layout.base.wrap import TextLayout

from repo_py_orchestrate.codegen_config.codegen import gen_haxorg_base_sources


@click.command()
@click.argument("root_dir", type=Path)
def main(root_dir: Path):
    t = TextLayout()
    builder = cpp.ASTBuilder(t)
    _, sources = gen_haxorg_base_sources(root_dir, t=t)
    gen_description_files(sources, builder, t)


if __name__ == "__main__":
    main()
