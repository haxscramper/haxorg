#!/usr/bin/env python
from sqlalchemy.testing import eq_clause_element

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
            return 'recursive - {}'.format(type(obj).__name__)

        seen.add(obj_id)

        if isinstance(obj, dict):
            return {k: aux(v, seen) for k, v in obj.items()}

        elif isinstance(obj, list):
            return [aux(i, seen) for i in obj]

        elif hasattr(obj, '__dict__'):
            return aux(obj.__dict__, seen)

        elif hasattr(obj, '__iter__') and not isinstance(obj, str):
            return [aux(i, seen) for i in obj]

        else:
            return 'Type({}) - {}'.format(type(obj).__name__, str(obj))

    seen: set[Any] = set()
    return aux(obj, seen)


NB_INCLUDE_LIST = [
    GenTuInclude("nanobind/nanobind.h", True),
    GenTuInclude("nanobind/stl/string.h", True),
    GenTuInclude("nanobind/stl/vector.h", True),
    GenTuInclude("nanobind/stl/map.h", True),
    GenTuInclude("nanobind/stl/array.h", True),
    GenTuInclude("nanobind/stl/filesystem.h", True),
    GenTuInclude("nanobind/stl/function.h", True),
    GenTuInclude("nanobind/stl/map.h", True),
    GenTuInclude("nanobind/stl/optional.h", True),
    GenTuInclude("nanobind/stl/set.h", True),
    GenTuInclude("nanobind/stl/shared_ptr.h", True),
    GenTuInclude("nanobind/stl/string_view.h", True),
    GenTuInclude("nanobind/stl/tuple.h", True),
    GenTuInclude("nanobind/stl/unique_ptr.h", True),
    GenTuInclude("nanobind/stl/unordered_map.h", True),
    GenTuInclude("nanobind/stl/variant.h", True),
    GenTuInclude("nanobind/operators.h", True),
    GenTuInclude("nanobind/make_iterator.h", True),
    GenTuInclude("nanobind/ndarray.h", True),
]


@beartype
def gen_adaptagrams_wrappers(
    ast: cpp.ASTBuilder,
    pyast: pya.ASTBuilder,
    reflection_path: Path,
) -> GenFiles:
    "Generate wrappers for adaptagrams library"
    tu: refl_read.ConvTu = refl_read.conv_proto_file(reflection_path)

    reflection_debug = Path("/tmp/haxorg/adaptagrams_reflection.json")
    reflection_debug.write_text(refl_read.open_proto_file(reflection_path).to_json(2))
    log(CAT).debug(f"Debug reflection data to '{reflection_debug}'")

    with ExceptionContextNote(f"reflection_debug:{reflection_debug}"):
        type_map = get_type_map(tu.enums + tu.structs + tu.typedefs)  # type: ignore
        conf = NanobindAstbuilderConfig(type_map)
        res = NbModule("py_adaptagrams", conf)
        res.add_all(tu.get_all(), ast=ast)
        specializations = collect_type_specializations(tu.get_all(), conf)
        res.add_type_specializations(
            ast=ast,
            specializations=specializations,
        )

        return GenFiles([
            GenUnit(header=GenTu(
                "{root}/scripts/py_wrappers/py_wrappers/py_adaptagrams.pyi",
                [GenTuPass(res.build_typedef(pyast))],
                clangFormatGuard=False,
            )),
            GenUnit(header=GenTu(
                "{root}/src/py_libs/py_adaptagrams/adaptagrams_py_wrap.cpp",
                [
                    GenTuPass("#undef slots"),
                    GenTuInclude("adaptagrams/adaptagrams_ir.hpp", True),
                    GenTuInclude("py_libs/nanobind_utils.hpp", True),
                    *NB_INCLUDE_LIST,
                    GenTuPass(res.build_bind(ast)),
                ],
            )),
        ])


class HaxorgNanobindWrapper(NanobindAstbuilderConfig):
    "Override some nanobind generation options for haxorg-specific types"

    def isRegisteredForBacked(self, Type: codegen_cpp.QualType) -> bool:
        "nodoc"
        match Type.flatQualNameWithParams():
            case ["org", "sem", "SemId", _]:
                return True

            case ["org", "imm", "ImmAdapterTBase", _]:
                return False

            case ["org", "imm", *rest]:
                return True

            case n if n in [
                ["org", "imm", "ImmId", "NodeIdxT"],
                ["org", "bind", "python", "ExporterPython", "PyFunc"],
                ["org", "bind", "python", "ExporterPython", "Res"],
            ]:
                return True

            case _:
                return super().isRegisteredForBacked(Type)


@beartype
def gen_pyhaxorg_python_wrappers(
    groups: PyhaxorgTypeGroups,
    ast: cpp.ASTBuilder,
    pyast: pya.ASTBuilder,
) -> GenFiles:
    "Generate haxorg python wrappers"
    conf = HaxorgNanobindWrapper(groups.type_map)
    res = NbModule("pyhaxorg", conf)

    for decl in groups.get_entries_for_wrapping():
        if decl.ReflectionParams.isAcceptedBackend("python"):
            res.add_decl(decl, ast=ast)

    specializations = collect_type_specializations(
        groups.get_entries_for_wrapping(),
        conf,
    )

    verify_type_usage(groups.get_entries_for_wrapping(), conf, specializations)

    res.add_type_specializations(ast, specializations=specializations)

    res.Decls.append(ast.Include("pyhaxorg_manual_wrap.hpp"))

    return GenFiles([
        GenUnit(header=GenTu(
            "{root}/scripts/py_haxorg/py_haxorg/pyhaxorg.pyi",
            [GenTuPass(res.build_typedef(pyast))],
            clangFormatGuard=False,
        )),
        GenUnit(header=GenTu(
            "{root}/src/py_libs/pyhaxorg/pyhaxorg.cpp",
            [
                GenTuPass("#undef slots"),
                *NB_INCLUDE_LIST,
                GenTuInclude("haxorg/imm/ImmOrgAdapter.hpp", True),
                GenTuInclude("haxorg/sem/SemOrg.hpp", True),
                GenTuInclude("pyhaxorg_manual_impl.hpp", False),
                GenTuPass(res.build_bind(ast)),
            ],
        )),
    ])


@beartype
def gen_pyhaxorg_napi_wrappers(
    groups: PyhaxorgTypeGroups,
    ast: cpp.ASTBuilder,
    type_map: GenTypeMap,
) -> GenFiles:
    "Generate embind wrappers"

    cpp_builder = cpp.ASTBuilder(ast.b)

    conf = EmbindAstbuilderConfig(type_map)
    res = napi.WasmModule("haxorg_wasm", conf)

    res.add_specializations(
        b=ast,
        specializations=collect_type_specializations(groups.get_entries_for_wrapping(),
                                                     conf),
    )

    for decl in groups.get_entries_for_wrapping():
        if decl.ReflectionParams.isAcceptedBackend("wasm"):
            res.add_decl(decl)

    res.Header.append(napi.WasmBindPass(ast.Include("node_utils.hpp")))
    res.Header.append(napi.WasmBindPass(ast.Include("node_org_include.hpp")))
    res.Header.append(napi.WasmBindPass(ast.Include("haxorg_wasm_manual.hpp")))
    res.Header.append(napi.WasmBindPass(ast.string("using namespace org::bind::js;")))

    res.add_decl(napi.WasmBindPass(ast.string("haxorg_wasm_manual_register();")))

    return GenFiles([
        GenUnit(header=GenTu("{root}/src/wrappers/js/haxorg_wasm.cpp", [
            GenTuPass(res.build_bind(ast=ast, b=cpp_builder)),
        ])),
        GenUnit(header=GenTu("{root}/src/wrappers/js/haxorg_wasm_types.d.ts", [
            GenTuPass(res.build_typedef(ast=ast)),
        ])),
    ])


@beartype
def gen_haxorg_c_wrappers(groups: PyhaxorgTypeGroups, ast: cpp.ASTBuilder) -> GenFiles:
    conf = CAstbuilderConfig(type_map=groups.type_map)

    standalone_funcs: List[codegen_ir.GenTuFunction] = list()

    for func in groups.get_entries_for_wrapping():
        if isinstance(func, codegen_ir.GenTuFunction):
            impl_call = ast.XCall(
                "convert_cpp_execution",
                args=[
                    ast.Addr(ast.Type(func.get_full_qualified_name())),
                    ast.string("org_context"),
                ] + [ast.string(a.Name) for a in func.Args],
                Params=[conf.getBackendType(func.ReturnType)] +
                [conf.getBackendType(arg.Type) for arg in func.Args],
            )

            if func.ReturnType != "void":
                impl_call = ast.Return(impl_call)

            standalone_funcs.append(
                codegen_ir.GenTuFunction(
                    ReturnType=conf.getBackendType(func.ReturnType),
                    Name=func.Name,
                    Args=[
                        codegen_ir.GenTuIdent(
                            Type=conf.getBackendType(arg.Type),
                            Name=arg.Name,
                        ) for arg in func.Args
                    ] + [
                        codegen_ir.GenTuIdent(
                            Type=QualType(Name="OrgContext", PtrCount=1),
                            Name="org_context",
                        )
                    ],
                    Body=ast.stack([impl_call]),
                    Annotations=[
                        codegen_ir.GenTuAnnotation(
                            Attribute=codegen_ir.GenTuAnnotation.Freeform(
                                Body="HAXORG_C_API_LINKAGE"))
                    ]))

    return GenFiles([
        GenUnit(
            header=GenTu("{root}/src/wrappers/c/haxorg_c.h", [
                GenTuInclude("wrappers/c/haxorg_c_api.h", True),
            ] + standalone_funcs),
            source=GenTu("{root}/src/wrappers/c/haxorg_c.cpp", [
                GenTuInclude("wrappers/c/haxorg_c.h", True),
                GenTuInclude("wrappers/c/haxorg_c_utils.hpp", True),
            ] + standalone_funcs),
        )
    ])


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
    )

    groups_dump_yaml = get_tmpdir().joinpath("pyhaxorg_groups.yaml")
    with groups_dump_yaml.open("w") as file:
        yaml.safe_dump(to_base_types(groups.conv_tu), stream=file)
        log(CAT).info(f"Wrote debug for type groups to {groups_dump_yaml}")

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
def run_codegen_task(task: Literal["adaptagrams", "pyhaxorg"], reflection_path: Path,
                     is_tmp_codegen: bool) -> None:
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
                )


@click.command()
@codegen_options
@click.pass_context
def impl(ctx: click.Context, config: Optional[str] = None, **kwargs: Any) -> None:
    opts: CodegenOptions = get_context(ctx, CodegenOptions, config=config, kwargs=kwargs)
    run_codegen_task(
        is_tmp_codegen=opts.tmp,
        reflection_path=Path(opts.reflection_path),
        task=opts.codegen_task,
    )


if __name__ == "__main__":
    impl()
