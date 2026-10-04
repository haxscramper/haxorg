import os

from hstd_py_lib.script_logging import ExceptionContextNote
from hstd_py_text_layout.base.wrap import TextLayout, TextOptions
from repo_py_orchestrate.codegen_config.org_codegen_data import *

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from hstd_py_codegen.gen_cpp import codegen_cpp


@beartype
def gen_tu(
    define: GenTu,
    builder: cpp.ASTBuilder,
    t: TextLayout,
    isHeader: bool,
    isSplitHeaderSource: bool,
):
    """
    Generate code for source/header of the translation unit component
    """
    with ExceptionContextNote(f"Path: {define.path}"):
        result = builder.TranslationUnit(
            [
                codegen_cpp.GenConverter(
                    builder, isHeader=isHeader, isSplitHeaderSource=isSplitHeaderSource
                ).convertTu(define)
            ]
        )

    directory = os.path.dirname(define.path)
    if not os.path.exists(directory):
        os.makedirs(directory)
        logger.info(f"Created dir for {define.path}")

    opts = TextOptions()
    opts.rightMargin = 160
    newCode = t.toString(result, opts)

    if os.path.exists(define.path):
        oldCode = define.path.read_text()

        if oldCode != newCode:
            define.path.write_text(newCode)
            logger.info(f"Updated code in {define.path}")
        else:
            logger.info(f"No changes on {define.path}")
    else:
        define.path.write_text(newCode)
        logger.info(f"Wrote to {define.path}")


@beartype
def gen_file(tu: GenUnit, builder: cpp.ASTBuilder, t: TextLayout) -> None:
    if tu.source:
        gen_tu(
            tu.source,
            builder,
            t,
            isHeader=False,
            isSplitHeaderSource=bool(tu.source and tu.header),
        )

    gen_tu(
        tu.header,
        builder,
        t,
        isHeader=True,
        isSplitHeaderSource=bool(tu.source and tu.header),
    )


@beartype
def gen_description_files(
    description: GenFiles, builder: cpp.ASTBuilder, t: TextLayout
) -> None:
    "Generate all translation unit files"
    for tu in description.files:
        gen_file(tu, builder=builder, t=t)
