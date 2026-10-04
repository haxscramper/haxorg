import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
import hstd_py_codegen.lang_build.astbuilder_proto as pb
import repo_py_orchestrate.codegen_config.gen_haxorg.immutable as gen_imm
from hstd_py_codegen.gen_cpp.iteration_macros import (
    gen_pyhaxorg_field_iteration_macros,
    gen_pyhaxorg_iteration_macros,
    gen_pyhaxorg_shared_iteration_macros,
)
from repo_py_orchestrate.codegen_config.codegen_type_groups import (
    PyhaxorgTypeGroups,
)
from repo_py_orchestrate.codegen_config.gen_haxorg.exporter import (
    gen_exporter_methods,
    gen_exporter_template,
)
from repo_py_orchestrate.codegen_config.org_codegen_data import *


def _gen_sem_org_enums(
    ast: cpp.ASTBuilder, groups: PyhaxorgTypeGroups, header: Path, source: Path
) -> GenUnit:
    return GenUnit(
        header=GenTu(
            header,
            [
                GenTuPass("#pragma once"),
                GenTuPass("#include <hstd_cpp_lib/system/basic_templates.hpp>"),
                GenTuPass("#include <hstd_cpp_lib/system/reflection.hpp>"),
                GenTuPass("#include <hstd_cpp_lib/stdlib/containers/Opt.hpp>"),
                *gen_pyhaxorg_shared_iteration_macros(groups.shared_types),
                *gen_pyhaxorg_iteration_macros(types=groups.expanded),
                *gen_pyhaxorg_field_iteration_macros(
                    types=groups.expanded,
                    type_map=groups.type_map,
                    ast=ast,
                    macro_namespace="SEM",
                ),
                *gen_pyhaxorg_field_iteration_macros(
                    types=groups.immutable,
                    type_map=groups.type_map,
                    ast=ast,
                    macro_namespace="IMM",
                ),
                *groups.full_enums,
            ],
        ),
        source=GenTu(
            source,
            [GenTuPass('#include "SemOrgEnums.hpp"')] + groups.full_enums,  # type: ignore
        ),
    )


def _gen_sem_org_shared_type(
    groups: PyhaxorgTypeGroups,
    header: Path,
) -> GenUnit:
    return GenUnit(
        header=GenTu(
            header,
            [
                GenTuPass("#pragma once"),
                GenTuInclude("haxorg/sem/SemOrgEnums.hpp", True),
                GenTuInclude("hstd/stdlib/Vec.hpp", True),
                GenTuInclude("hstd/stdlib/Variant.hpp", True),
                GenTuInclude("hstd/stdlib/Time.hpp", True),
                GenTuInclude("hstd/stdlib/Opt.hpp", True),
                GenTuInclude("hstd/stdlib/Str.hpp", True),
                GenTuInclude("boost/describe.hpp", True),
                GenTuInclude("hstd/system/macros.hpp", True),
                GenTuInclude("haxorg/sem/SemOrgBaseSharedTypes.hpp", True),
                GenTuInclude("haxorg/sem/SemOrgEnums.hpp", True),
                GenTuNamespace(n_sem(), groups.shared_types),
            ],
        )
    )


def _gen_imm_org_serde(
    ast: cpp.ASTBuilder, groups: PyhaxorgTypeGroups, template_file: Path
) -> GenUnit:
    return GenUnit(
        header=GenTu(
            template_file,
            gen_imm.get_imm_serde(
                types=groups.expanded, ast=ast, type_map=groups.type_map
            ),
        ),
    )


def _gen_imm_org_type(
    ast: cpp.ASTBuilder, groups: PyhaxorgTypeGroups, header: Path
) -> GenUnit:
    return GenUnit(
        header=GenTu(
            header,
            [
                GenTuPass("#pragma once"),
                GenTuInclude("haxorg/imm/ImmOrgBase.hpp", True),
                GenTuNamespace(n_imm(), groups.immutable),
            ],
        )
    )


def _gen_imm_org_adapter(
    groups: PyhaxorgTypeGroups, header: Path, source: Path
) -> GenUnit:
    return GenUnit(
        header=GenTu(
            header,
            [
                GenTuPass("#pragma once"),
                GenTuPass("#define HAXORG_IMM_ORG_ADAPTER_GENERATED_INCLUDED"),
                GenTuPass('#pragma clang diagnostic ignored "-Wextra-qualification"'),
                GenTuInclude("haxorg/imm/ImmOrg.hpp", True),
                GenTuNamespace(n_imm(), groups.adapter_specializations),
            ],
        ),
        source=GenTu(
            source,
            [
                GenTuInclude("haxorg/imm/ImmOrg.hpp", True),
                GenTuInclude("haxorg/imm/ImmOrgAdapterGenerated.hpp", True),
            ]
            + groups.adapter_specializations,
        ),
    )


def _gen_sem_org_serde(
    ast: cpp.ASTBuilder, groups: PyhaxorgTypeGroups, header: Path, source: Path
) -> GenUnit:

    proto = pb.ProtoBuilder(
        wrapped=groups.get_protobuf_target_entires(),
        ast=ast,
        type_map=groups.type_map,
    )

    protobuf_writer_declarations, protobuf_writer_implementation = (
        proto.build_protobuf_writer()
    )

    return GenUnit(
        header=GenTu(
            header,
            [
                GenTuPass("#if ORG_BUILD_WITH_PROTOBUF && !ORG_BUILD_EMCC"),
                GenTuPass("#pragma once"),
                GenTuPass("#include <haxorg_cpp_org_lib/serde/SemOrgSerde.hpp>"),
                GenTuPass(ast.Macro(proto.get_any_node_field_mapping())),
            ]
            + [
                GenTuPass(ast.b.stack([ast.Any(rec), ast.b.text("")]))
                for rec in protobuf_writer_declarations
            ]
            + [
                GenTuPass("#endif"),
            ],
        ),
        source=GenTu(
            source,
            [
                GenTuPass("#if ORG_BUILD_WITH_PROTOBUF && !ORG_BUILD_EMCC"),
                GenTuPass("#include <haxorg_cpp_org_lib/serde/SemOrgSerde.hpp>"),
                GenTuPass(
                    "#include <haxorg_cpp_org_lib/serde/SemOrgSerdeDeclarations.hpp>"
                ),
            ]
            + [
                GenTuPass(ast.b.stack([ast.Any(rec), ast.b.text("")]))
                for rec in protobuf_writer_implementation
            ]
            + [
                GenTuPass("#endif"),
            ],
        ),
    )


def gen_haxorg_source(
    ast: cpp.ASTBuilder, groups: PyhaxorgTypeGroups, root: Path
) -> GenFiles:
    return GenFiles(
        [
            _gen_imm_org_serde(
                ast,
                groups,
                template_file=root / "src/haxorg_cpp_org_lib/imm/ImmOrgSerde.tcc",
            ),
            _gen_imm_org_type(
                ast,
                groups,
                header=root / "src/haxorg_cpp_org_lib/imm/ImmOrgTypes.hpp",
            ),
            _gen_imm_org_adapter(
                groups,
                header=root / "src/haxorg_cpp_org_lib/imm/ImmOrgAdapter.hpp",
                source=root / "src/haxorg_cpp_org_lib/imm/ImmOrgAdapter.cpp",
            ),
            _gen_sem_org_serde(
                ast,
                groups,
                header=root / "src/haxorg_cpp_org_lib/serde/SemOrgSerde.hpp",
                source=root / "src/haxorg_cpp_org_lib/serde/SemOrgSerde.cpp",
            ),
            _gen_sem_org_shared_type(
                groups,
                header=root / "src/haxorg_cpp_org_lib/sem/SemOrgSharedTypes.hpp",
            ),
            _gen_sem_org_enums(
                ast,
                groups,
                header=root / "src/haxorg_cpp_org_lib/sem/SemOrgEnums.hpp",
                source=root / "src/haxorg_cpp_org_lib/sem/SemOrgEnums.cpp",
            ),
            gen_exporter_template(
                groups,
                out_file=root / "src/haxorg_cpp_org_lib/exporters/Exporter.tcc",
            ),
            gen_exporter_methods(
                groups,
                out_file=root / "src/haxorg_cpp_org_lib/exporters/ExporterMethods.tcc",
            ),
        ]
    )
