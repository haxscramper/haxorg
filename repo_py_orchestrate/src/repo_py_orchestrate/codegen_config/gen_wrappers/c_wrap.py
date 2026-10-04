from pathlib import Path

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from beartype import beartype
from beartype.typing import List, Optional, cast
from hstd_py_codegen.gen_cpp import codegen_ir
from hstd_py_codegen.gen_cpp.codegen_algo import (
    SpecializationMatchResult,
    TypedefExpansionMatcher,
    collect_type_specializations,
    instantiate_template,
    match_specializations_for_struct,
    rewrite_any_typedefs,
)
from hstd_py_codegen.gen_cpp.codegen_ir import QualType, n_sem
from hstd_py_codegen.lang_build.astbuilder_c_config import (
    CAstbuilderConfig,
)
from hstd_py_codegen.lang_convert.conv_c import (
    StructGenResult,
    _gen_func,
    gen_enum,
    gen_haxorg_vtable_template_instantiation,
    gen_struct_direct,
    gen_typedef,
)
from hstd_py_lib.script_logging import pprint_to_file_json
from loguru import logger
from repo_py_orchestrate.codegen_config.codegen_type_groups import (
    topological_sort_entries,
)


@beartype
def _get_entries_for_wrapping(
    to_wrap: list[codegen_ir.GenTuUnion], conf: CAstbuilderConfig
) -> list[codegen_ir.GenTuUnion]:
    typedefs_to_expand = list()
    entries_to_rewrite = list()

    for entry in to_wrap:
        if (
            conf.isAcceptedByBackend(entry)
            and isinstance(entry, codegen_ir.GenTuTypedef)
            and entry.ReflectionParams.expand_typedef
        ):
            logger.info(f"Typedef entry {entry}")
            typedefs_to_expand.append(entry)

        else:
            entries_to_rewrite.append(entry)

    expansion_matcher = TypedefExpansionMatcher(typedefs_to_expand)

    return cast(
        list[codegen_ir.GenTuUnion],
        [rewrite_any_typedefs(e, matcher=expansion_matcher) for e in entries_to_rewrite],
    )


@beartype
def gen_haxorg_c_wrappers(
    to_wrap: list[codegen_ir.GenTuUnion],
    ast: cpp.ASTBuilder,
    type_map: codegen_ir.GenTypeMap,
    root: Path,
) -> codegen_ir.GenFiles:
    "Generate C wrappers"
    conf = CAstbuilderConfig(type_map=type_map)

    standalone_funcs: List[codegen_ir.GenTuFunction] = list()
    wrapped_structs: List[codegen_ir.GenTuEntry] = list()
    header_only: list[codegen_ir.GenTuEntry] = list()
    vtables: list[codegen_ir.GenTuEntry] = list()

    def _add_struct_result(structs: StructGenResult):
        wrapped_structs.extend(structs.wrappers)
        header_only.extend(structs.forward_decls)
        vtables.extend(structs.vtables)

    def _add_struct(entry: codegen_ir.GenTuStruct):
        structs = gen_struct_direct(entry, ast, conf)
        _add_struct_result(structs)

    expanded_entries = _get_entries_for_wrapping(to_wrap, conf)

    pprint_to_file_json(expanded_entries, "/tmp/expanded_entries.json")

    reflection_template_types: List[codegen_ir.GenTuStruct] = list()
    for entry in expanded_entries:
        if (
            isinstance(entry, codegen_ir.GenTuStruct)
            and entry.IsTemplateRecord
            and not entry.IsExplicitInstantiation
        ):
            match entry.declarationQualName().flatQualNameWithParams():
                case ["org", "sem", "SemId", _]:
                    # TODO: This edge case can be replaced by the reflection
                    # parameters in the type annotations.
                    _add_struct(
                        cast(
                            codegen_ir.GenTuStruct,
                            instantiate_template(
                                entry,
                                substitution_map={
                                    "O": QualType(Name="Org", Spaces=[n_sem()])
                                },
                                type_map=conf.type_map,
                            ),
                        )
                    )

                case _:
                    reflection_template_types.append(entry)

    specializations = collect_type_specializations(
        expanded_entries,
        conf,
    )

    void_handle_instantiations = list()
    for template_type in reflection_template_types:
        assert template_type.TemplateParams
        template_usage_types = match_specializations_for_struct(
            specializations=[spec.used_type for spec in specializations],
            template=template_type,
        )

        for target_type in [
            # "hstd::Opt",
        ]:
            for s in specializations:
                if target_type in str(s.used_type) and target_type in str(template_type):
                    logger.debug(f"{s.used_type}")
                    debug = list()
                    match_result = match_specializations_for_struct(
                        [s.used_type],
                        template_type,
                        debug=True,
                        debug_sink=debug,
                    )

                    if not match_result:
                        logger.warning("\n" + "\n".join(debug))

        if (
            template_type.ReflectionParams.backend.c.instantiation_mode
            == "each-specialization"
        ):
            logger.info(f"Found template type with each-specialization {template_type}")
            for match in template_usage_types:
                _add_struct(
                    cast(
                        codegen_ir.GenTuStruct,
                        instantiate_template(
                            template_type,
                            substitution_map=match.substitution_map,
                            type_map=conf.type_map,
                        ),
                    )
                )

        elif template_type.ReflectionParams.backend.c.instantiation_mode == "void-handle":
            logger.info(f"Found void-handle type {template_type}")
            assert template_type.ReflectionParams.backend.c.value_template_parameters, (
                "void-handle must provide names for the template type parameters"
            )

            for inst in template_usage_types:
                void_handle_instantiations.append(
                    cast(
                        codegen_ir.GenTuStruct,
                        instantiate_template(
                            template_type,
                            substitution_map=inst.substitution_map,
                            type_map=conf.type_map,
                        ),
                    )
                )

            _add_struct_result(
                gen_haxorg_vtable_template_instantiation(
                    struct=template_type,
                    specializations=template_usage_types,
                    conf=conf,
                    ast=ast,
                )
            )

    void_handle_specializations = collect_type_specializations(
        void_handle_instantiations, conf
    )

    if False:
        for template_type in reflection_template_types:
            if (
                template_type.ReflectionParams.backend.c.instantiation_mode
                == "each-specialization"
            ):
                matches: list[
                    tuple[SpecializationMatchResult, Optional[codegen_ir.GenTuEntry]]
                ] = list()
                for spec in void_handle_specializations:
                    match1 = match_specializations_for_struct(
                        specializations=[spec.used_type],
                        template=template_type,
                    )

                    if match1:
                        matches.append((match1[0], spec.used_in))

                if 1 < len(matches):
                    raise RuntimeError(
                        """
{template_name} was used with multiple different type parameters when substituting the public API for void-handle types: API for void-handle needs to the type with distinct instances.

{template_usages}

The type cannot be used in each-instantiation mode as there are void-handle API that need to return the instantiations as void handle.

!! TO RESOLVE THIS ISSUE, MARK {template_name} AS `void-handle` !!
                    """.format(
                            template_name=str(template_type.Name),
                            template_usages="\n".join(
                                "- {} (used in {})".format(
                                    m[0].instantiated_name.format(native=True),
                                    m[1],
                                )
                                for m in matches
                            ),
                        )
                    )

    for entry in expanded_entries:
        if conf.isAcceptedByBackend(entry):
            match entry:
                case codegen_ir.GenTuFunction():
                    standalone_funcs.append(_gen_func(entry, ast, conf))

                case codegen_ir.GenTuStruct():
                    if entry.IsTemplateRecord and not entry.IsExplicitInstantiation:
                        continue

                    match entry.declarationQualName().flatQualNameWithParams():
                        case ["org", "imm", "ImmIdT", _]:
                            # Ignore explicit specializations for immutable ID
                            # in the C backend.
                            continue

                        case _:
                            _add_struct(entry)

                case codegen_ir.GenTuEnum():
                    header_only.append(gen_enum(entry, ast, conf))

                case codegen_ir.GenTuTypedef():
                    tdef = gen_typedef(entry, ast, conf)
                    wrapped_structs.append(tdef)

                case _:
                    raise TypeError(type(entry))

    def is_forward_declared(Type: QualType) -> bool:
        return False

    wrapped_structs = topological_sort_entries(
        wrapped_structs,  # type: ignore
        use_api=True,
        is_forward_declared=is_forward_declared,
    )

    return codegen_ir.GenFiles(
        [
            codegen_ir.GenUnit(
                header=codegen_ir.GenTu(
                    root / "src/haxorg_cpp_c_wrap/haxorg_c.h",
                    [
                        codegen_ir.GenTuPass(ast.string("#pragma once")),
                        codegen_ir.GenTuInclude("haxorg_cpp_c_wrap/haxorg_c_api.h", True),
                    ]
                    + header_only
                    + wrapped_structs
                    + standalone_funcs,
                ),
                source=codegen_ir.GenTu(
                    root / "src/haxorg_cpp_c_wrap/haxorg_c.cpp",
                    [
                        codegen_ir.GenTuInclude("haxorg_cpp_c_wrap/haxorg_c.h", True),
                        codegen_ir.GenTuInclude(
                            "haxorg_cpp_c_wrap/haxorg_c_vtables.hpp", True
                        ),
                        codegen_ir.GenTuInclude(
                            "haxorg_cpp_c_wrap/haxorg_c_vtables_manual.hpp", True
                        ),
                        codegen_ir.GenTuInclude(
                            "haxorg_cpp_c_wrap/haxorg_c_utils.hpp", True
                        ),
                    ]
                    + wrapped_structs
                    + standalone_funcs,
                ),
            ),
            codegen_ir.GenUnit(
                header=codegen_ir.GenTu(
                    root / "src/haxorg_cpp_c_wrap/haxorg_c_vtables.hpp",
                    [
                        codegen_ir.GenTuPass(ast.string("#pragma once")),
                        codegen_ir.GenTuInclude("haxorg_cpp_c_wrap/haxorg_c.h", True),
                        codegen_ir.GenTuInclude(
                            "haxorg_cpp_c_wrap/haxorg_c_utils.hpp", True
                        ),
                        codegen_ir.GenTuInclude(
                            "haxorg_cpp_c_wrap/haxorg_c_vtables_manual.hpp", True
                        ),
                    ]
                    + vtables,
                ),
                source=codegen_ir.GenTu(
                    root / "src/haxorg_cpp_c_wrap/haxorg_c_vtables.cpp",
                    [
                        codegen_ir.GenTuInclude("haxorg_cpp_c_wrap/haxorg_c.h", True),
                        codegen_ir.GenTuInclude(
                            "haxorg_cpp_c_wrap/haxorg_c_utils.hpp", True
                        ),
                        codegen_ir.GenTuInclude(
                            "haxorg_cpp_c_wrap/haxorg_c_vtables.hpp", True
                        ),
                        codegen_ir.GenTuInclude(
                            "haxorg_cpp_c_wrap/haxorg_c_vtables_manual.hpp", True
                        ),
                    ]
                    + vtables,
                ),
            ),
        ]
    )
