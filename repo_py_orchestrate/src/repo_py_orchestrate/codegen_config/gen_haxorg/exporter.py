from hstd_py_codegen.gen_cpp import codegen_ir
from hstd_py_lib.algorithm import cond
from repo_py_orchestrate.codegen_config.codegen_type_groups import PyhaxorgTypeGroups

from repo_py_orchestrate.src.repo_py_orchestrate.codegen_config.org_codegen_data import *


@beartype
def _get_exporter_methods(
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
                field
                for field in (value.Fields + get_type_base_fields(value, type_map))
                if field.IsExposedForWrap
            ]

            scoped_target = t_cr(
                QualType.ForName(
                    name,
                    Spaces=[QualType.ForName("sem")]
                    + [QualType.ForName(t) for t in scope_names],
                )
            )
            decl_scope = "" if forward else "Exporter<V, R>::"
            t_params = (
                None
                if forward
                else codegen_ir.GenTuTemplateParams.FromTypeNameList(["V", "R"])
            )

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
                                    "res",
                                ),
                                GenTuIdent(
                                    t_cr(field.Type)
                                    if field.Type
                                    else QualType.ForName("void"),
                                    "object",
                                ),
                            ],
                            Body=None
                            if forward
                            else f"visitVariants(res, sem::{'::'.join(full_scoped_name)}::{kindGetter}(object), object);",
                        )
                    )

            if value.Name.isOrgType() and len(scope_full) == 0:
                method = GenTuFunction(
                    ReturnType=QualType.ForName("void"),
                    Name=f"{decl_scope}visit{name}",
                    Params=t_params,
                    Args=[
                        GenTuIdent(
                            QualType.ForName("R", RefKind=ReferenceKind.LValue), "res"
                        ),
                        GenTuIdent(
                            QualType.ForName(
                                "In", Params=[QualType.ForName(f"sem::{name}")]
                            ),
                            "object",
                        ),
                    ],
                    Body=cond(
                        forward,
                        None,
                        "auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));\n{}".format(
                            "\n".join(
                                [f"__org_field(res, object, {a.Name});" for a in fields]
                            ),
                        ),
                    ),
                )
            else:
                method = GenTuFunction(
                    ReturnType=QualType.ForName("void"),
                    Name=f"{decl_scope}visit",
                    Params=t_params,
                    Args=[
                        GenTuIdent(
                            QualType.ForName("R", RefKind=ReferenceKind.LValue), "res"
                        ),
                        GenTuIdent(scoped_target, "object"),
                    ],
                    Body=None
                    if forward
                    else "\n".join(
                        [f"__obj_field(res, object, {a.Name});" for a in fields]
                    ),
                )

            methods += variant_methods + [method]

    iterate_object_tree(expanded, iterate_tree_context, pre_visit=callback)
    return methods


def gen_exporter_template(groups: PyhaxorgTypeGroups, out_file: Path) -> GenUnit:
    return GenUnit(
        header=GenTu(
            out_file,
            [
                *_get_exporter_methods(
                    False, groups.shared_types, type_map=groups.type_map
                ),
                *_get_exporter_methods(False, groups.expanded, type_map=groups.type_map),
            ],
        ),
    )


def gen_exporter_methods(groups: PyhaxorgTypeGroups, out_file: Path) -> GenUnit:
    return GenUnit(
        header=GenTu(
            out_file,
            [
                *_get_exporter_methods(
                    True, groups.shared_types, type_map=groups.type_map
                ),
                *_get_exporter_methods(True, groups.expanded, type_map=groups.type_map),
            ],
        )
    )
