import copy
from dataclasses import dataclass, field, replace
from graphlib import CycleError, TopologicalSorter
from pathlib import Path

from beartype import beartype
from beartype.typing import Dict, List, Sequence
from py_codegen import codegen_ir, refl_read
import py_codegen.astbuilder_cpp as cpp
import py_codegen.codegen_immutable as gen_imm
from py_codegen.codegen_algo import collect_type_specializations
from py_codegen.codegen_ir import QualType
import py_codegen.org_codegen_data as org_data
from py_codegen.refl_read import ConvTu
from py_scriptutils.script_logging import log

CAT = __name__


@beartype
def topological_sort_entries(
        entries: List[codegen_ir.GenTuUnion]) -> List[codegen_ir.GenTuUnion]:
    entry_by_hash: Dict[int, codegen_ir.GenTuUnion] = {}
    cant_have_dependants: List[codegen_ir.GenTuUnion] = []

    for it in entries:
        match it:
            case codegen_ir.GenTuStruct():
                qual_hash = it.declarationQualName().qual_hash()
                assert qual_hash not in entry_by_hash, f"Duplicate hash for {it.declarationQualName()}, already mapped to {it}"
                entry_by_hash[qual_hash] = it

            case codegen_ir.GenTuTypedef():
                entry_by_hash[it.name.qual_hash()] = it

            case _:
                cant_have_dependants.append(it)

    assert (len(entry_by_hash) + len(cant_have_dependants)) == len(
        entries
    ), f"Sorting order mismatch len(hash): {len(entry_by_hash)} + len(no-deps): {len(cant_have_dependants)} len(entries): {len(entries)}"

    graph = {}
    for entry in entries:
        match entry:
            case codegen_ir.GenTuStruct():
                entry_hash = entry.declarationQualName().qual_hash()
                graph[entry_hash] = {
                    base.qual_hash()
                    for base in entry.bases
                    if base.qual_hash() in entry_by_hash
                }

            case codegen_ir.GenTuTypedef():
                entry_hash = entry.name.qual_hash()
                if entry.base.qual_hash() in entry_by_hash:
                    graph[entry_hash] = {entry.base.qual_hash()}

    ts = TopologicalSorter(graph)
    try:
        sorted_hashes = list(ts.static_order())
        result = [entry_by_hash[h] for h in sorted_hashes] + cant_have_dependants

        # assert len(result) == len(
        #     entries
        # ), f"Sorting order mismatch len(in): {len(entries)} len(out): {len(result)} len(no-deps): {len(cant_have_dependants)} len(hash): {len(entry_by_hash)}"

        return result
    except CycleError:
        raise ValueError("Cyclic inheritance detected")


@beartype
def get_concrete_types(
        expanded: List[codegen_ir.GenTuStruct]) -> Sequence[codegen_ir.GenTuStruct]:
    return [struct for struct in expanded if not struct.IsAbstract]


@beartype
def get_osk_enum(expanded: List[codegen_ir.GenTuStruct]) -> codegen_ir.GenTuEnum:
    return codegen_ir.GenTuEnum(
        QualType.ForName(org_data.t_osk().name),
        codegen_ir.GenTuDoc(""),
        fields=[
            codegen_ir.GenTuEnumField(struct.name.name, codegen_ir.GenTuDoc(""))
            for struct in get_concrete_types(expanded)
        ],
    )


@beartype
def rec_expand_type(ast: cpp.ASTBuilder,
                    typ: codegen_ir.GenTuStruct) -> codegen_ir.GenTuStruct:
    """
    Recursively expand all the type groups in the input structure.
    """
    converted: List[codegen_ir.GenTuEntry] = []
    methods: List[codegen_ir.GenTuFunction] = []
    fields: List[codegen_ir.GenTuField] = []
    for item in typ.nested:
        match item:
            case codegen_ir.GenTuStruct():
                converted.append(rec_expand_type(ast, item))

            case codegen_ir.GenTuTypeGroup():
                for res in rec_expand_group(ast, item):
                    if isinstance(res, codegen_ir.GenTuField):
                        fields.append(res)

                    elif isinstance(res, codegen_ir.GenTuFunction):
                        methods.append(res)

                    else:
                        converted.append(res)

            case codegen_ir.GenTuEnum():
                converted.append(replace(item, name=item.name))

            case codegen_ir.GenTuPass():
                converted.append(item)

            case _:
                assert False, type(item)

    result = replace(
        typ,
        # name=typ.name.model_copy(update=dict(Spaces=context)),
        nested=converted,
        methods=typ.methods + methods,
        fields=typ.fields + fields,
    )

    if hasattr(typ, "isOrgType"):
        setattr(result, "isOrgType", getattr(typ, "isOrgType"))

    return result


@beartype
def rec_expand_group(
    ast: cpp.ASTBuilder, record: codegen_ir.GenTuTypeGroup
) -> List[codegen_ir.GenTuEntry | codegen_ir.GenTuField]:
    """
    Recursively expand all the types in the type group, generating a new
    list of entries that should be added to the parent structure for the
    type group.
    """
    result: List[codegen_ir.GenTuEntry | codegen_ir.GenTuField] = []
    typeNames: List[QualType] = []

    for item in record.types:
        expanded = rec_expand_type(ast, item)
        result.append(expanded)
        if not item.IsAbstract:
            typeNames.append(expanded.name)

    if record.iteratorMacroName:
        iteratorMacro = cpp.MacroParams(
            name=record.iteratorMacroName,
            params=[cpp.MacroParams.Param("__IMPL")],
            doc=cpp.DocParams(""),
        )

        for typeItem in typeNames:
            iteratorMacro.definition.append(f"__IMPL({typeItem.name})")

        result.append(codegen_ir.GenTuPass(ast.Macro(iteratorMacro)))

    if record.variantName and record.enumName:
        enum_type = record.enumName
        variant_type = record.variantName
        result.append(
            codegen_ir.GenTuTypedef(
                name=variant_type,
                base=QualType(
                    name="variant",
                    Spaces=[QualType.ForName("std")],
                    Parameters=typeNames,
                ),
            ))

        result.append(
            codegen_ir.GenTuEnum(
                name=enum_type,
                doc=codegen_ir.GenTuDoc(""),
                fields=[
                    codegen_ir.GenTuEnumField(N.name, codegen_ir.GenTuDoc(""))
                    for N in typeNames
                ],
            ))

        for idx, T in enumerate(typeNames):
            kindName = T.name[0].upper() + T.name[1:]
            result.append(
                codegen_ir.GenTuFunction(
                    doc=codegen_ir.GenTuDoc(""),
                    name="is" + kindName,
                    result=QualType.ForName("bool"),
                    isConst=True,
                    impl=ast.Return(
                        ast.XCall("==", [
                            ast.XCall(record.kindGetter, []),
                            ast.string(f"{enum_type.name}::{kindName}"),
                        ])),
                ))

            for isConst in [True, False]:
                result.append(
                    codegen_ir.GenTuFunction(
                        doc=codegen_ir.GenTuDoc(""),
                        name="get" + kindName,
                        result=T.model_copy(update=dict(
                            RefKind=codegen_ir.ReferenceKind.LValue,
                            isConst=isConst,
                        )),
                        reflectionParams=codegen_ir.GenTuReflParams(
                            unique_name="get" + kindName +
                            ("Const" if isConst else "Mut")),
                        isConst=isConst,
                        impl=ast.Return(
                            ast.XCall(
                                "hstd::variant_get",
                                [ast.string(record.variantField)],
                                Params=[QualType.ForName(str(idx))],
                            )),
                    ))

        result.append(
            codegen_ir.GenTuFunction(
                isStatic=True,
                doc=codegen_ir.GenTuDoc(""),
                name=record.kindGetter,
                reflectionParams=codegen_ir.GenTuReflParams(
                    unique_name=record.kindGetter + "Static"),
                result=enum_type,
                arguments=[codegen_ir.GenTuIdent(variant_type.asConstRef(), "__input")],
                impl=ast.Return(
                    ast.XCall(
                        "static_cast",
                        args=[ast.XCallRef(ast.string("__input"), "index")],
                        Params=[enum_type],
                    )),
            ))

        result.append(
            codegen_ir.GenTuFunction(
                name=record.kindGetter,
                result=enum_type,
                impl=ast.Return(
                    ast.XCall(record.kindGetter, [ast.string(record.variantField)])),
                doc=codegen_ir.GenTuDoc(""),
                isConst=True,
            ))

        result.append(
            codegen_ir.GenTuFunction(
                name="sub_variant_get_name",
                result=QualType(name="char", ptrCount=1, isConst=True),
                impl=ast.Return(ast.StringLiteral(record.variantField)),
                doc=codegen_ir.GenTuDoc(""),
                isConst=True,
            ))

        result.append(
            codegen_ir.GenTuFunction(
                name="sub_variant_get_data",
                result=record.variantName.asConstRef(),
                impl=ast.Return(ast.string(record.variantField)),
                doc=codegen_ir.GenTuDoc(""),
                isConst=True,
            ))

        result.append(
            codegen_ir.GenTuFunction(
                name="sub_variant_get_kind",
                result=record.enumName,
                impl=ast.Return(ast.XCall(record.kindGetter)),
                doc=codegen_ir.GenTuDoc(""),
                isConst=True,
            ))

        result.append(
            codegen_ir.GenTuPass(
                ast.Using(cpp.UsingParams(newName="variant_enum_type",
                                          baseType=enum_type))))

        result.append(
            codegen_ir.GenTuPass(
                ast.Using(
                    cpp.UsingParams(newName="variant_data_type", baseType=variant_type))))

        variant_field = codegen_ir.GenTuField(
            type=copy.deepcopy(variant_type),
            name=record.variantField,
            doc=codegen_ir.GenTuDoc(""),
            value=ast.string(record.variantValue) if record.variantValue else None,
        )

        setattr(variant_field, "isVariantField", True)
        setattr(variant_field, "variantGetter", record.kindGetter)

        result.append(variant_field)

    return result


@beartype
def expand_type_groups(
    ast: cpp.ASTBuilder, types: Sequence[codegen_ir.GenTuStruct]
) -> List[codegen_ir.GenTuEntry | codegen_ir.GenTuField]:
    return [rec_expand_type(ast, T) for T in types]


@beartype
@dataclass
class PyhaxorgTypeGroups():
    "Type groups for wrapping and codegen"
    shared_types: List[codegen_ir.GenTuStruct] = field(default_factory=list)
    expanded: List[codegen_ir.GenTuStruct] = field(default_factory=list)
    immutable: List[codegen_ir.GenTuStruct] = field(default_factory=list)
    reader_accessors: List[codegen_ir.GenTuStruct] = field(default_factory=list)
    "Proxy objects wrapping around pointer to the immutable AST node value."
    adapter_specializations: List[codegen_ir.GenTuStruct] = field(default_factory=list)
    conv_tu: ConvTu = field(default_factory=lambda: ConvTu())
    base_map: codegen_ir.GenTypeMap = field(
        default_factory=lambda: codegen_ir.GenTypeMap())  # type: ignore[assignment]
    full_enums: List[codegen_ir.GenTuEnum] = field(default_factory=list)
    imm_id_specializations: List[codegen_ir.GenTuStruct] = field(default_factory=list)
    only_wrap_entries: List[codegen_ir.GenTuEntry] = field(default_factory=list)
    "Types not exposed for codegen, but only for entry wrapping"

    # specializations: List[codegen_ir.TypeSpecialization] = field(default_factory=list)

    def get_entries_for_wrapping(self) -> List[codegen_ir.GenTuUnion]:
        "Get full list of entries to be wrapped for public API"

        def aux(e: codegen_ir.GenTuEntry, ind: int) -> None:
            match e:
                case codegen_ir.GenTuStruct():
                    log(CAT).info(
                        f"{'  ' * ind}{e.name.name} {e.name} wrapper:{e.reflectionParams.wrapper_name} py:{py_type(e.name, self.base_map)}"
                    )
                    for sub in e.nested:
                        aux(sub, ind + 1)

        result = self.full_enums + \
            self.conv_tu.enums + \
            self.conv_tu.structs + \
            self.conv_tu.typedefs + \
            self.shared_types + \
            self.expanded + \
            self.conv_tu.functions + \
            self.immutable + \
            self.imm_id_specializations + \
            self.adapter_specializations + \
            self.only_wrap_entries

        return topological_sort_entries(result)


@beartype
def get_pyhaxorg_type_groups(ast: cpp.ASTBuilder,
                             reflection_path: Path) -> PyhaxorgTypeGroups:
    """
    Get type groups and method implementations for the haxorg library
    source file generation and wrappers.
    """
    res = PyhaxorgTypeGroups()
    res.shared_types = expand_type_groups(ast, org_data.get_shared_sem_types())
    res.expanded = expand_type_groups(ast, org_data.get_types())
    (adapters, readers) = gen_imm.generate_adapter_specializations(ast, res.expanded)
    res.adapter_specializations = adapters
    res.reader_accessors = readers
    res.immutable = expand_type_groups(ast,
                                       gen_imm.rewrite_to_immutable(org_data.get_types()))

    res.conv_tu = refl_read.conv_proto_file(reflection_path)
    res.base_map = codegen_ir.get_base_map(
        res.expanded + res.shared_types + res.immutable + res.conv_tu.enums +
        res.conv_tu.structs + res.conv_tu.typedefs,)

    res.full_enums = org_data.get_shared_sem_enums() + org_data.get_enums() + [
        get_osk_enum(res.expanded)
    ]

    # res.specializations = collect_type_specializations(
    #     res.get_entries_for_wrapping(),
    #     base_map=res,
    # )

    imm_space = [QualType.ForName("org"), QualType.ForName("imm")]
    for sem_base in res.expanded:
        derived_base: str = sem_base.name.name
        Derived = QualType(name=f"Imm{derived_base}", Spaces=imm_space)
        Base = QualType(name="ImmAdapterTBase", Spaces=imm_space, Parameters=[Derived])
        res.only_wrap_entries.append(
            codegen_ir.GenTuStruct(
                name=Base,
                IsTemplateRecord=True,
                ExplicitTemplateParams=[Derived],
                reflectionParams=codegen_ir.GenTuReflParams(
                    backend=codegen_ir.GenTuBackendParams(target_backends=["python"]),
                    wrapper_has_params=False,
                    wrapper_name=f"ImmAdapter{derived_base}Base",
                ),
            ))

    for org_type in org_data.get_types():
        res.imm_id_specializations.append(
            codegen_ir.GenTuStruct(
                OriginName="imm ID explicit",
                name=QualType.ForName("ImmIdT", Spaces=imm_space),
                IsExplicitInstantiation=True,
                ExplicitTemplateParams=[gen_imm.rewrite_type_to_immutable(org_type.name)],
                reflectionParams=codegen_ir.GenTuReflParams(wrapper_name="ImmIdT" +
                                                            org_type.name.name),
                IsDescribedRecord=False,
                bases=[QualType.ForName("ImmId", Spaces=imm_space)],
            ))

    return res
