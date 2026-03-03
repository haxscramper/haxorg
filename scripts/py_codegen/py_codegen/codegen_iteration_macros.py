from dataclasses import dataclass, field

from beartype import beartype
from beartype.typing import List, Tuple
import py_codegen.astbuilder_cpp as cpp
from py_codegen.codegen_ir import QualType
import py_codegen.codegen_ir as tu
from py_codegen.codegen_type_groups import get_concrete_types
from py_haxorg.astbuilder.astbuilder_utils import pascal_case
from py_scriptutils.algorithm import iterate_object_tree


@beartype
@dataclass
class PyhaxorgTypenameGroups:
    nested_records: List[Tuple[str, str, str]] = field(default_factory=list)
    nested_enums: List[Tuple[str, str, str]] = field(default_factory=list)
    all_records: List[Tuple[str, str]] = field(default_factory=list)


@beartype
@dataclass
class PyhaxorgTypeDesc:
    fields: List[tu.GenTuField]
    parent_fields: List[tu.GenTuField]
    bases: List[QualType]
    name: str
    typ: QualType


@beartype
@dataclass
class PyhaxorgTypeFieldGroup:
    types: List[PyhaxorgTypeDesc] = field(default_factory=list)


@beartype
def collect_type_field_groups(types: List[tu.GenTuStruct],
                              type_map: tu.GenTypeMap) -> PyhaxorgTypeFieldGroup:

    def aux(t: tu.GenTuStruct) -> List[tu.GenTuField]:
        result: List[tu.GenTuField] = []
        for base in t.bases:
            base_type = type_map.get_one_type_for_name(base.name)
            if base_type:
                assert isinstance(base_type, tu.GenTuStruct)
                result += aux(base_type)

        return result

    def filter_fields(f: List[tu.GenTuField]) -> List[tu.GenTuField]:
        return [it for it in f if not it.isStatic]

    result = PyhaxorgTypeFieldGroup()

    for t in types:
        group = PyhaxorgTypeDesc(
            fields=filter_fields(t.fields),
            parent_fields=filter_fields(aux(t)),
            bases=list(t.bases),
            name=t.name.name,
            typ=t.name,
        )

        result.types.append(group)

    return result


@beartype
def collect_pyhaxorg_typename_groups(
        types: List[tu.GenTuStruct]) -> PyhaxorgTypenameGroups:
    res = PyhaxorgTypenameGroups()

    def aux(it: tu.GenTuStruct | tu.GenTuEnum | tu.GenTuTypedef | tu.GenTuFunction
           ) -> None:
        match it:
            case tu.GenTuStruct() | tu.GenTuEnum():
                flat = it.name.flatQualScope() + [it.name.withoutAllScopeQualifiers()]
                without_namespaces = [
                    i for i in range(len(flat)) if not flat[i].isNamespace
                ]
                # log(CAT).info(f"{it.name} {flat} {name_start} {without_namespaces}")
                name_start = without_namespaces[0]
                if 1 < len(without_namespaces):
                    parent = flat[name_start]
                    nested = flat[without_namespaces[1]:]
                    value = (
                        parent.name,
                        "::".join(it.name for it in nested),
                        "({})".format(", ".join(it.name for it in nested)),
                    )
                    if isinstance(it, tu.GenTuStruct):
                        res.nested_records.append(value)

                    else:
                        res.nested_enums.append(value)

                if isinstance(it, tu.GenTuStruct):
                    res.all_records.append((
                        "::".join(it.name for it in flat[name_start:]),
                        "({})".format(", ".join(it.name for it in flat[name_start:])),
                    ))

    iterate_object_tree(types, [], pre_visit=aux)

    return res


@beartype
def gen_iteration_macros(res: PyhaxorgTypenameGroups,
                         macro_group: str) -> List[tu.GenTuPass]:
    result: List[tu.GenTuPass] = []

    result.append(
        tu.GenTuPass(
            f"#define EACH_{macro_group}_ORG_RECORD_NESTED(__IMPL) \\\n" + (" \\\n".join(
                ["    __IMPL({}, {}, {})".format(*it) for it in res.nested_records]))))

    result.append(
        tu.GenTuPass(
            f"#define EACH_{macro_group}_ORG_ENUM_NESTED(__IMPL) \\\n" + (" \\\n".join(
                ["    __IMPL({}, {}, {})".format(*it) for it in res.nested_enums]))))

    result.append(
        tu.GenTuPass(f"#define EACH_{macro_group}_ORG_RECORD(__IMPL) \\\n" + (
            " \\\n".join(["    __IMPL({}, {})".format(*it) for it in res.all_records]))))

    return result


@beartype
def gen_pyhaxorg_shared_iteration_macros(
        types: List[tu.GenTuStruct]) -> List[tu.GenTuPass]:
    return gen_iteration_macros(collect_pyhaxorg_typename_groups(types), "SHARED")


@beartype
def gen_pyhaxorg_field_iteration_macros(
    types: List[tu.GenTuStruct],
    type_map: tu.GenTypeMap,
    ast: cpp.ASTBuilder,
    macro_namespace: str,
) -> List[tu.GenTuPass]:
    """
    Generate collection of macros to iterate over fixed set of haxorg entires at
    compile-time: fields, types, node kinds etc.
    """

    result: List[tu.GenTuPass] = []

    field_groups = collect_type_field_groups(types, type_map=type_map)

    for group in field_groups.types:
        for with_base_fields in [True, False]:
            def_stack = ast.b.stack([])

            if with_base_fields:
                ast.b.add_at(
                    def_stack,
                    ast.string(
                        f"#define EACH_{macro_namespace}_ORG_{group.name}_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \\"
                    ))

            else:
                ast.b.add_at(
                    def_stack,
                    ast.string(
                        f"#define EACH_{macro_namespace}_ORG_{group.name}_FIELD_WITH_BASES(__IMPL_BASE) \\"
                    ))

            def impl_field(field: tu.GenTuField) -> None:
                "nodoc"
                ast.b.add_at(
                    def_stack,
                    ast.b.line([
                        ast.string("    "),
                        ast.XCall(
                            "__IMPL_FIELD",
                            [
                                # Type of the field
                                ast.pars(ast.Type(field.type)) if field.type else
                                ast.string("void"),  # type: ignore[arg-type]
                                # field name without changes
                                ast.string(field.name),
                                # field name for `getField` etc.
                                ast.string(pascal_case(field.name)),
                                # Parent type for field, in case you need to define methods for
                                # each field outside of the class body.
                                ast.pars(ast.Type(group.typ)),
                                ast.string(group.name.replace("Imm", "")),
                            ]),
                        ast.string(" \\"),
                    ]))

            if with_base_fields:
                for field in group.parent_fields:
                    impl_field(field)

            else:
                for base in group.bases:
                    ast.b.add_at(
                        def_stack,
                        ast.b.line([
                            ast.string("    "),
                            ast.XCall("__IMPL_BASE", [
                                ast.pars(ast.Type(base)),
                            ]),
                            ast.string(" \\"),
                        ]))

            for field in group.fields:
                impl_field(field)

            ast.b.add_at(def_stack, ast.string(""))

            result.append(tu.GenTuPass(def_stack))

    return result


@beartype
def gen_pyhaxorg_iteration_macros(types: List[tu.GenTuStruct]) -> List[tu.GenTuPass]:
    res = collect_pyhaxorg_typename_groups(types)

    result: List[tu.GenTuPass] = gen_iteration_macros(res, "SEM")
    result.append(
        tu.GenTuPass("#define EACH_SEM_ORG_KIND(__IMPL) \\\n" + (" \\\n".join(
            [f"    __IMPL({struct.name.name})"
             for struct in get_concrete_types(types)]))))

    result.append(
        tu.GenTuPass("#define EACH_SEM_ORG_FINAL_TYPE_BASE(__IMPL) \\\n" + (" \\\n".join([
            f"    __IMPL({struct.name.name}, {struct.bases[0].name})"
            for struct in get_concrete_types(types)
        ]))))

    result.append(
        tu.GenTuPass("#define EACH_SEM_ORG_TYPE_BASE(__IMPL) \\\n" + (" \\\n".join([
            f"    __IMPL({struct.name.name}, {struct.bases[0].name})" for struct in types
        ]))))

    return result
