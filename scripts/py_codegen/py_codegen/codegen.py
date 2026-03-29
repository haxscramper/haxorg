#!/usr/bin/env python
from py_codegen.codegen_wrapper_c import gen_haxorg_c_wrappers
from py_codegen.codegen_wrapper_embind import gen_pyhaxorg_napi_wrappers
from py_codegen.codegen_wrapper_nanobind import gen_adaptagrams_wrappers, gen_pyhaxorg_python_wrappers

from py_codegen import codegen_cpp, refl_read, codegen_ir
import py_codegen.astbuilder_cpp as cpp
import os
import py_codegen.astbuilder_embind as napi
from py_codegen.astbuilder_embind_config import EmbindAstbuilderConfig
from py_codegen.astbuilder_nanobind import NbModule
import py_codegen.astbuilder_proto as pb
import py_codegen.astbuilder_py as pya
import py_codegen.codegen_immutable as gen_imm
from py_codegen.astbuilder_nanobind_config import NanobindAstbuilderConfig
from py_codegen.astbuilder_c_config import CAstbuilderConfig
from py_codegen.codegen_algo import collect_type_specializations
from py_codegen.codegen_iteration_macros import (
    gen_pyhaxorg_field_iteration_macros,
    gen_pyhaxorg_iteration_macros,
    gen_pyhaxorg_shared_iteration_macros,
)
from py_codegen.codegen_type_groups import get_pyhaxorg_type_groups, PyhaxorgTypeGroups, verify_type_usage
from py_codegen.org_codegen_data import *
from py_haxorg.layout.wrap import TextLayout, TextOptions
from py_repository.repo_tasks.config import get_tmpdir
from py_scriptutils.algorithm import cond
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.script_logging import ExceptionContextNote, log
import yaml
from py_scriptutils.toml_config_profiler import (
    apply_options,
    get_context,
    options_from_model,
)
import rich_click as click

CAT = "codegen"


def with_enum_reflection_api(body: List[Any]) -> List[Any]:
    return [
        GenTuPass("#pragma once"),
        GenTuPass("#include <hstd/system/basic_templates.hpp>"),
        GenTuPass("#include <hstd/system/reflection.hpp>"),
        GenTuPass("#include <hstd/stdlib/Opt.hpp>"),
    ] + body


@beartype
def get_exporter_methods(
    forward: bool,
    expanded: List[GenTuStruct],
    type_map: GenTypeMap,
) -> List[GenTuFunction]:
    methods: List[GenTuFunction] = []
    iterate_tree_context: List[Any] = []

    def callback(value: Any) -> None:
        nonlocal methods
        nonlocal type_map
        nonlocal iterate_tree_context
        if isinstance(value, GenTuStruct):
            scope_full: List[GenTuStruct] = [
                scope for scope in iterate_tree_context if isinstance(scope, GenTuStruct)
            ]
            scope_names: List[str] = [scope.Name.Name for scope in scope_full]
            name: str = value.Name.Name
            full_scoped_name: List[str] = scope_names + [name]
            fields: List[GenTuField] = [
                field for field in (value.Fields + get_type_base_fields(value, type_map))
                if field.IsExposedForWrap
            ]

            scoped_target = t_cr(
                QualType.ForName(name,
                                 Spaces=[QualType.ForName("sem")] +
                                 [QualType.ForName(t) for t in scope_names]))
            decl_scope = "" if forward else "Exporter<V, R>::"
            t_params = None if forward else codegen_ir.GenTuTemplateParams.FromTypeNameList(
                ["V", "R"])

            variant_methods: List[GenTuFunction] = []
            for field in fields:
                if hasattr(field, "isVariantField"):
                    kindGetter = getattr(field, "variantGetter")
                    variant_methods.append(
                        GenTuFunction(
                            ReturnType=QualType.ForName("void"),
                            Name=f"{decl_scope}visit",
                            Params=t_params,
                            Args=[
                                GenTuIdent(
                                    QualType.ForName("R", RefKind=ReferenceKind.LValue),
                                    "res"),
                                GenTuIdent(
                                    t_cr(field.Type)
                                    if field.Type else QualType.ForName("void"),
                                    "object",
                                ),
                            ],
                            Body=None if forward else
                            f"visitVariants(res, sem::{'::'.join(full_scoped_name)}::{kindGetter}(object), object);",
                        ))

            if value.Name.isOrgType() and len(scope_full) == 0:
                method = GenTuFunction(
                    ReturnType=QualType.ForName("void"),
                    Name=f"{decl_scope}visit{name}",
                    Params=t_params,
                    Args=[
                        GenTuIdent(QualType.ForName("R", RefKind=ReferenceKind.LValue),
                                   "res"),
                        GenTuIdent(
                            QualType.ForName("In",
                                             Params=[QualType.ForName(f"sem::{name}")]),
                            "object"),
                    ],
                    Body=cond(
                        forward,
                        None,
                        "auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));\n{}"
                        .format(
                            "\n".join([
                                f"__org_field(res, object, {a.Name});" for a in fields
                            ]),),
                    ),
                )
            else:
                method = GenTuFunction(
                    ReturnType=QualType.ForName("void"),
                    Name=f"{decl_scope}visit",
                    Params=t_params,
                    Args=[
                        GenTuIdent(QualType.ForName("R", RefKind=ReferenceKind.LValue),
                                   "res"),
                        GenTuIdent(scoped_target, "object"),
                    ],
                    Body=None if forward else "\n".join(
                        [f"__obj_field(res, object, {a.Name});" for a in fields]),
                )

            methods += variant_methods + [method]

    iterate_object_tree(expanded, iterate_tree_context, pre_visit=callback)
    return methods


def to_base_types(obj: Any) -> Any:

    def aux(obj: Any, seen: Any) -> Any:
        if isinstance(obj, Enum):
            return obj.name

        elif isinstance(obj, (str, int, float, bool)) or obj is None:
            return obj

        obj_id = id(obj)
        if obj_id in seen:
            return "recursive - {}".format(type(obj).__name__)

        seen.add(obj_id)

        if isinstance(obj, dict):
            return {k: aux(v, seen) for k, v in obj.items()}

        elif isinstance(obj, list):
            return [aux(i, seen) for i in obj]

        elif hasattr(obj, "__dict__"):
            return aux(obj.__dict__, seen)

        elif hasattr(obj, "__iter__") and not isinstance(obj, str):
            return [aux(i, seen) for i in obj]

        else:
            return "Type({}) - {}".format(type(obj).__name__, str(obj))

    seen: set[Any] = set()
    return aux(obj, seen)


@beartype
def gen_pyhaxorg_source(ast: cpp.ASTBuilder, groups: PyhaxorgTypeGroups) -> GenFiles:
    """
    Generate source files compiled as a part of the haxorg library: sem and imm AST definitions.
    """
    proto = pb.ProtoBuilder(
        wrapped=groups.full_enums + groups.shared_types + groups.expanded,  # type: ignore
        ast=ast,
        type_map=groups.type_map,
    )
    t = ast.b

    protobuf = proto.build_protobuf()
    protobuf_writer_declarations, protobuf_writer_implementation = proto.build_protobuf_writer(
    )

    return GenFiles([
        GenUnit(header=GenTu("{base}/serde/SemOrgProto.proto", [
            GenTuPass('syntax = "proto3";'),
            GenTuPass("package orgproto;"),
            GenTuPass('import "SemOrgProtoManual.proto";'),
            GenTuPass(protobuf),
        ])),
        GenUnit(
            header=GenTu(
                "{base}/serde/SemOrgSerdeDeclarations.hpp",
                [
                    GenTuPass("#if ORG_BUILD_WITH_PROTOBUF && !ORG_BUILD_EMCC"),
                    GenTuPass("#pragma once"),
                    GenTuPass("#include <haxorg/serde/SemOrgSerde.hpp>"),
                    GenTuPass(ast.Macro(proto.get_any_node_field_mapping())),
                ] + [
                    GenTuPass(t.stack([ast.Any(rec), t.text("")]))
                    for rec in protobuf_writer_declarations
                ] + [
                    GenTuPass("#endif"),
                ],
            ),
            source=GenTu(
                "{base}/serde/SemOrgSerdeDefinitions.cpp",
                [
                    GenTuPass("#if ORG_BUILD_WITH_PROTOBUF && !ORG_BUILD_EMCC"),
                    GenTuPass("#include <haxorg/serde/SemOrgSerde.hpp>"),
                    GenTuPass("#include <haxorg/serde/SemOrgSerdeDeclarations.hpp>"),
                ] + [
                    GenTuPass(t.stack([ast.Any(rec), t.text("")]))
                    for rec in protobuf_writer_implementation
                ] + [
                    GenTuPass("#endif"),
                ],
            ),
        ),
        GenUnit(header=GenTu(
            "{base}/exporters/Exporter.tcc",
            get_exporter_methods(False, groups.shared_types, type_map=groups.type_map) +
            get_exporter_methods(False, groups.expanded, type_map=groups.type_map),
        ),),
        GenUnit(header=GenTu(
            "{base}/imm/ImmOrgSerde.tcc",
            gen_imm.get_imm_serde(types=groups.expanded,
                                  ast=ast,
                                  type_map=groups.type_map),
        ),),
        GenUnit(header=GenTu(
            "{base}/exporters/ExporterMethods.tcc",
            get_exporter_methods(True, groups.shared_types, type_map=groups.type_map) +
            get_exporter_methods(True, groups.expanded, type_map=groups.type_map))),
        GenUnit(
            header=GenTu(
                "{base}/sem/SemOrgEnums.hpp",
                with_enum_reflection_api(
                    gen_pyhaxorg_shared_iteration_macros(groups.shared_types) +
                    gen_pyhaxorg_iteration_macros(types=groups.expanded)) +
                gen_pyhaxorg_field_iteration_macros(
                    types=groups.expanded,
                    type_map=groups.type_map,
                    ast=ast,
                    macro_namespace="SEM",
                ) + gen_pyhaxorg_field_iteration_macros(
                    types=groups.immutable,
                    type_map=groups.type_map,
                    ast=ast,
                    macro_namespace="IMM",
                ) + groups.full_enums,
            ),
            source=GenTu(
                "{base}/sem/SemOrgEnums.cpp",
                [GenTuPass('#include "SemOrgEnums.hpp"')] +
                groups.full_enums,  # type: ignore
            ),
        ),
        GenUnit(header=GenTu(
            "{base}/sem/SemOrgSharedTypes.hpp",
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
        )),
        GenUnit(header=GenTu(
            "{base}/sem/SemOrgTypes.hpp",
            [
                GenTuPass("#pragma once"),
                GenTuInclude("haxorg/sem/SemOrgEnums.hpp", True),
                GenTuInclude("hstd/stdlib/Vec.hpp", True),
                GenTuInclude("hstd/stdlib/Variant.hpp", True),
                GenTuInclude("hstd/stdlib/Time.hpp", True),
                GenTuInclude("hstd/stdlib/Opt.hpp", True),
                GenTuInclude("hstd/stdlib/Str.hpp", True),
                GenTuInclude("haxorg/parse/OrgTypes.hpp", True),
                GenTuInclude("boost/describe.hpp", True),
                GenTuInclude("hstd/system/macros.hpp", True),
                GenTuInclude("haxorg/sem/SemOrgBase.hpp", True),
                GenTuInclude("haxorg/sem/SemOrgEnums.hpp", True),
                GenTuInclude("haxorg/sem/SemOrgSharedTypes.hpp", True),
                GenTuNamespace(n_sem(), groups.expanded),
            ],
        )),
        GenUnit(header=GenTu(
            "{base}/imm/ImmOrgTypes.hpp",
            [
                GenTuPass("#pragma once"),
                GenTuInclude("haxorg/imm/ImmOrgBase.hpp", True),
                GenTuNamespace(n_imm(), groups.immutable),
            ],
        )),
        GenUnit(
            header=GenTu(
                "{base}/imm/ImmOrgAdapterGenerated.hpp",
                [
                    GenTuPass("#pragma once"),
                    GenTuPass("#define HAXORG_IMM_ORG_ADAPTER_GENERATED_INCLUDED"),
                    GenTuPass(
                        "#pragma clang diagnostic ignored \"-Wextra-qualification\""),
                    GenTuInclude("haxorg/imm/ImmOrg.hpp", True),
                    GenTuNamespace(n_imm(), groups.adapter_specializations),
                ],
            ),
            source=GenTu(
                "{base}/imm/ImmOrgAdapterGenerated.cpp",
                [
                    GenTuInclude("haxorg/imm/ImmOrg.hpp", True),
                    GenTuInclude("haxorg/imm/ImmOrgAdapterGenerated.hpp", True),
                ] + groups.adapter_specializations,
            ),
        ),
    ])


@beartype
def gen_unit(
    define: GenTu,
    builder: cpp.ASTBuilder,
    t: TextLayout,
    tmp: bool,
    isHeader: bool,
    isSplitHeaderSource: bool,
):
    """
    Generate code for source/header of the translation unit component
    """
    out_root = Path("/tmp") if tmp else get_haxorg_repo_root_path()

    path = define.path.format(base=out_root.joinpath("src/haxorg"), root=out_root)

    with ExceptionContextNote(f"Path: {define.path}"):
        result = builder.TranslationUnit([
            codegen_cpp.GenConverter(
                builder, isHeader=isHeader,
                isSplitHeaderSource=isSplitHeaderSource).convertTu(define)
        ])

    directory = os.path.dirname(path)
    if not os.path.exists(directory):
        os.makedirs(directory)
        log(CAT).info(f"Created dir for {path}")

    opts = TextOptions()
    opts.rightMargin = 160
    newCode = t.toString(result, opts)

    if os.path.exists(path):
        with open(path, "r") as f:
            oldCode = f.read()

        if oldCode != newCode:
            with open(path, "w") as out:
                out.write(newCode)
            log(CAT).info(f"[red]Updated code[/red] in {define.path}")
        else:
            log(CAT).info(f"[green]No changes[/green] on {define.path}")
    else:
        with open(path, "w") as out:
            out.write(newCode)
        log(CAT).info(f"[red]Wrote[/red] to {define.path}")


def gen_description_files(
    description: GenFiles,
    builder: cpp.ASTBuilder,
    t: TextLayout,
    tmp: bool,
) -> None:
    "Generate all translation unit files"
    for tu in description.files:
        if tu.source:
            gen_unit(tu.source,
                     builder,
                     t,
                     tmp,
                     isHeader=False,
                     isSplitHeaderSource=bool(tu.source and tu.header))

        gen_unit(tu.header,
                 builder,
                 t,
                 tmp,
                 isHeader=True,
                 isSplitHeaderSource=bool(tu.source and tu.header))


class CodegenOptions(BaseModel):
    reflection_path: str
    codegen_task: Literal["pyhaxorg", "adaptagrams"]
    tmp: bool = False


def codegen_options(f: Any) -> Any:
    return apply_options(f, options_from_model(CodegenOptions))


def _write_files_group(
    impl: GenFiles,
    builder: cpp.ASTBuilder,
    is_tmp_codegen: bool,
    t: TextLayout,
) -> None:
    gen_description_files(
        description=impl,
        builder=builder,
        t=t,
        tmp=is_tmp_codegen,
    )


@beartype
def run_codegen_adaptagrams(
    is_tmp_codegen: bool,
    builder: cpp.ASTBuilder,
    pyast: pya.ASTBuilder,
    reflection_path: Path,
    t: TextLayout,
) -> None:
    _write_files_group(
        gen_adaptagrams_wrappers(
            builder,
            pyast,
            reflection_path=Path(reflection_path),
        ),
        is_tmp_codegen=is_tmp_codegen,
        builder=builder,
        t=t,
    )


@beartype
def run_codegen_pyhaxorg(
    is_tmp_codegen: bool,
    builder: cpp.ASTBuilder,
    pyast: pya.ASTBuilder,
    reflection_path: Path,
    t: TextLayout,
    manual_tu_path: Path,
) -> None:
    """
    Generate sources for the haxorg library
    :param is_tmp_codegen: If set, put newly genrated sources in the
      temporary directory instead of overwriting existing ones. Useful
      for development.
    :param reflection_path: Input protobuf file with reflection information.
    """
    groups: PyhaxorgTypeGroups = get_pyhaxorg_type_groups(
        ast=builder,
        reflection_path=Path(reflection_path),
        manual_tu_path=manual_tu_path,
    )

    groups_dump_yaml = get_tmpdir().joinpath("pyhaxorg_groups.yaml")
    with groups_dump_yaml.open("w") as file:
        yaml.safe_dump(to_base_types(groups.conv_tu), stream=file)
        log(CAT).info(f"Wrote debug for type groups to {groups_dump_yaml}")

    groups_dump_yaml = get_tmpdir().joinpath("pyhaxorg_manual_groups.yaml")
    with groups_dump_yaml.open("w") as file:
        yaml.safe_dump(to_base_types(groups.manual_tu), stream=file)
        log(CAT).info(f"Wrote debug for manual type groups to {groups_dump_yaml}")

    _write_files_group(
        gen_haxorg_c_wrappers(
            groups=groups,
            ast=builder,
        ),
        is_tmp_codegen=is_tmp_codegen,
        builder=builder,
        t=t,
    )

    _write_files_group(
        gen_pyhaxorg_napi_wrappers(
            groups=groups,
            ast=builder,
            type_map=groups.type_map,
        ),
        is_tmp_codegen=is_tmp_codegen,
        builder=builder,
        t=t,
    )

    _write_files_group(
        gen_pyhaxorg_python_wrappers(
            groups=groups,
            ast=builder,
            pyast=pyast,
        ),
        is_tmp_codegen=is_tmp_codegen,
        builder=builder,
        t=t,
    )

    _write_files_group(
        gen_pyhaxorg_source(
            ast=builder,
            groups=groups,
        ),
        is_tmp_codegen=is_tmp_codegen,
        builder=builder,
        t=t,
    )


@beartype
def run_codegen_task(
    task: Literal["adaptagrams", "pyhaxorg"],
    reflection_path: Path,
    is_tmp_codegen: bool,
    manual_tu_path: Path,
) -> None:
    t = TextLayout()
    pyast = pya.ASTBuilder(t)
    builder = cpp.ASTBuilder(t)

    with ExceptionContextNote(f"reflection_path:{reflection_path}, task: {task}"):
        match task:
            case "adaptagrams":
                run_codegen_adaptagrams(
                    is_tmp_codegen=is_tmp_codegen,
                    reflection_path=reflection_path,
                    builder=builder,
                    pyast=pyast,
                    t=t,
                )

            case "pyhaxorg":
                run_codegen_pyhaxorg(
                    is_tmp_codegen=is_tmp_codegen,
                    reflection_path=reflection_path,
                    builder=builder,
                    pyast=pyast,
                    t=t,
                    manual_tu_path=manual_tu_path,
                )
