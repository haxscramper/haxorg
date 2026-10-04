import copy
import json
from dataclasses import replace
from graphlib import CycleError, TopologicalSorter

from beartype import beartype
from beartype.typing import Callable, Dict, List, Sequence
from hstd_py_lib.script_logging import ExceptionContextNote, to_debug_json

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from hstd_py_codegen.gen_cpp import codegen_ir
from hstd_py_codegen.gen_cpp.codegen_ir import QualType
from hstd_py_codegen.lang_build.astbuilder_base_config import AstbulderConfig


@beartype
def topological_sort_entries(
    entries: Sequence[codegen_ir.GenTuEntry],
    use_bases: bool = True,
    use_api: bool = False,
    is_forward_declared: Callable[[QualType], bool] = lambda it: False,
) -> List[codegen_ir.GenTuUnion]:
    entry_by_hash: Dict[int, codegen_ir.GenTuUnion] = {}
    put_last: List[codegen_ir.GenTuUnion] = []
    put_first: List[codegen_ir.GenTuUnion] = []

    for it in entries:
        match it:
            case codegen_ir.GenTuStruct():
                qual_hash = it.declarationQualName().qual_hash()
                if qual_hash in entry_by_hash:
                    existing_entry = entry_by_hash[qual_hash]
                    from pprint import pformat

                    from deepdiff import DeepDiff

                    diff = DeepDiff(
                        to_debug_json(existing_entry), to_debug_json(it), verbose_level=1
                    )
                    formatted_diff = pformat(diff)

                else:
                    formatted_diff = ""

                assert qual_hash not in entry_by_hash, (
                    f"Duplicate hash for {it.declarationQualName()}, already mapped "
                    f"IsExplicitInstantiation={it.IsExplicitInstantiation} IsTemplateRecord={it.IsTemplateRecord}"
                    f"\n{formatted_diff}"
                )
                entry_by_hash[qual_hash] = it

            case codegen_ir.GenTuTypedef():
                entry_by_hash[it.Name.qual_hash()] = it

            case codegen_ir.GenTuEnum():
                put_first.append(it)

            case _:
                # Other entries cannot have dependants -- functions, passes etc.
                put_last.append(it)

    if (len(entry_by_hash) + len(put_last) + len(put_first)) != len(entries):
        raise RuntimeError(
            "Sorting order mismatch {}".format(
                {
                    "len(hash)": len(entry_by_hash),
                    "len(no-dependants)": len(put_last),
                    "len(no-deps)": len(put_first),
                    "len(entries)": len(entries),
                }
            )
        )

    graph: dict[int, set[int]] = {}
    for entry in entries:
        match entry:
            case codegen_ir.GenTuStruct():
                entry_hash = entry.declarationQualName().qual_hash()
                graph[entry_hash] = set()

                def use_type(Type: QualType):
                    match Type.Kind:
                        case codegen_ir.QualTypeKind.RegularType:
                            if (
                                Type.qual_hash() in entry_by_hash
                                and not is_forward_declared(Type)
                            ):
                                graph[entry_hash].add(Type.qual_hash())

                        case codegen_ir.QualTypeKind.FunctionPtr:
                            assert Type.Func
                            if Type.Func.Class:
                                use_type(Type.Func.Class)

                            if Type.Func.ReturnType:
                                use_type(Type.Func.ReturnType)

                            list(map(use_type, Type.Func.Args))

                        case codegen_ir.QualTypeKind.Array:
                            list(map(use_type, Type.Params))

                if use_bases:
                    for base in entry.Bases:
                        use_type(base)

                if use_api:

                    def aux(nest: codegen_ir.GenTuEntry):
                        match nest:
                            case codegen_ir.GenTuStruct():
                                list(map(aux, nest.Methods))
                                list(map(aux, nest.Fields))
                                list(map(aux, nest.Nested))

                            case codegen_ir.GenTuField():
                                if nest.Type:
                                    use_type(nest.Type)

                            case codegen_ir.GenTuFunction():
                                use_type(nest.ReturnType)
                                list(map(lambda arg: use_type(arg.Type), nest.Args))

                            case codegen_ir.GenTuTypeGroup():
                                list(map(aux, nest.types))

                            case _:
                                raise TypeError(type(nest))

                    aux(entry)

            case codegen_ir.GenTuTypedef():
                entry_hash = entry.Name.qual_hash()
                if entry.Base.qual_hash() in entry_by_hash:
                    graph[entry_hash] = {entry.Base.qual_hash()}

                else:
                    # typedef might refer to the specialization of the
                    # standard type
                    graph[entry_hash] = set()

    ts = TopologicalSorter(graph)
    try:
        sorted_hashes = list(ts.static_order())
        result = put_first + [entry_by_hash[h] for h in sorted_hashes] + put_last

        return result
    except CycleError as e:
        cycle_nodes = [entry_by_hash[n].Name for n in e.args[1]]
        raise ValueError(f"Cyclic inheritance detected for nodes {cycle_nodes}")


@beartype
def rec_expand_type(
    ast: cpp.ASTBuilder, typ: codegen_ir.GenTuStruct
) -> codegen_ir.GenTuStruct:
    """
    Recursively expand all the type groups in the input structure.
    """
    converted: List[codegen_ir.GenTuEntry] = []
    methods: List[codegen_ir.GenTuFunction] = []
    fields: List[codegen_ir.GenTuField] = []
    for item in typ.Nested:
        match item:
            case codegen_ir.GenTuStruct():
                converted.append(rec_expand_type(ast, item))

            case codegen_ir.GenTuTypeGroup():
                for res in rec_expand_group(ast, item, typ.declarationQualName()):
                    if isinstance(res, codegen_ir.GenTuField):
                        fields.append(res)

                    elif isinstance(res, codegen_ir.GenTuFunction):
                        methods.append(res)

                    else:
                        converted.append(res)

            case codegen_ir.GenTuEnum():
                converted.append(replace(item, Name=item.Name))

            case codegen_ir.GenTuPass() | codegen_ir.GenTuTypedef():
                converted.append(item)

            case _:
                assert False, type(item)

    result = replace(
        typ,
        # name=typ.name.copy_update(Spaces=context),
        Nested=converted,
        Methods=typ.Methods + methods,
        Fields=typ.Fields + fields,
    )

    if hasattr(typ, "isOrgType"):  # TODO: Remove the haxorg-specific handling
        setattr(result, "isOrgType", getattr(typ, "isOrgType"))

    return result


@beartype
def rec_expand_group(
    ast: cpp.ASTBuilder,
    record: codegen_ir.GenTuTypeGroup,
    parent_class: QualType,
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
            typeNames.append(expanded.Name)

    if record.iteratorMacroName:
        iteratorMacro = cpp.MacroParams(
            name=record.iteratorMacroName,
            params=[cpp.MacroParams.Param("__IMPL")],
            doc=cpp.DocParams(""),
        )

        for typeItem in typeNames:
            iteratorMacro.definition.append(f"__IMPL({typeItem.Name})")

        result.append(codegen_ir.GenTuPass(ast.Macro(iteratorMacro)))

    if record.variantName and record.enumName:
        enum_type = record.enumName
        variant_type = record.variantName
        result.append(
            codegen_ir.GenTuTypedef(
                Name=variant_type,
                Base=QualType(
                    Name="variant",
                    Spaces=[QualType.ForName("std")],
                    Params=typeNames,
                ),
                IsExposedForWrap=False,
            )
        )

        result.append(
            codegen_ir.GenTuEnum(
                Name=enum_type,
                Doc=codegen_ir.GenTuDoc(""),
                Fields=[
                    codegen_ir.GenTuEnumField(N.Name, codegen_ir.GenTuDoc(""))
                    for N in typeNames
                ],
            )
        )

        for idx, T in enumerate(typeNames):
            kindName = T.Name[0].upper() + T.Name[1:]
            result.append(
                codegen_ir.GenTuFunction(
                    Doc=codegen_ir.GenTuDoc(""),
                    Name="is" + kindName,
                    ReturnType=QualType.ForName("bool"),
                    IsConst=True,
                    ParentClass=parent_class,
                    Body=ast.Return(
                        ast.XCall(
                            "==",
                            [
                                ast.XCall(record.kindGetter, []),
                                ast.string(f"{enum_type.Name}::{kindName}"),
                            ],
                        )
                    ),
                )
            )

            for IsConst in [True, False]:
                result.append(
                    codegen_ir.GenTuFunction(
                        Doc=codegen_ir.GenTuDoc(""),
                        Name="get" + kindName,
                        ParentClass=parent_class,
                        ReturnType=T.copy_update(
                            RefKind=codegen_ir.ReferenceKind.LValue,
                            IsConst=IsConst,
                        ),
                        ReflectionParams=codegen_ir.GenTuReflParams(
                            unique_name="get" + kindName + ("Const" if IsConst else "Mut")
                        ),
                        IsConst=IsConst,
                        Body=ast.Return(
                            ast.XCall(
                                "hstd::variant_get",
                                [ast.string(record.variantField)],
                                Params=[QualType.ForName(str(idx))],
                            )
                        ),
                    )
                )

        result.append(
            codegen_ir.GenTuFunction(
                IsStatic=True,
                Doc=codegen_ir.GenTuDoc(""),
                Name=record.kindGetter,
                IsExposedForWrap=False,
                ParentClass=parent_class,
                ReflectionParams=codegen_ir.GenTuReflParams(
                    unique_name=record.kindGetter + "Static"
                ),
                ReturnType=enum_type,
                Args=[codegen_ir.GenTuIdent(variant_type.asConstRef(), "__input")],
                Body=ast.Return(
                    ast.XCall(
                        "static_cast",
                        args=[ast.XCallRef(ast.string("__input"), "index")],
                        Params=[enum_type],
                    )
                ),
            )
        )

        result.append(
            codegen_ir.GenTuFunction(
                Name=record.kindGetter,
                ReturnType=enum_type,
                ParentClass=parent_class,
                Body=ast.Return(
                    ast.XCall(record.kindGetter, [ast.string(record.variantField)])
                ),
                Doc=codegen_ir.GenTuDoc(""),
                IsConst=True,
            )
        )

        result.append(
            codegen_ir.GenTuFunction(
                Name="sub_variant_get_name",
                ParentClass=parent_class,
                ReturnType=QualType(Name="char", PtrCount=1, IsConst=True),
                Body=ast.Return(ast.StringLiteral(record.variantField)),
                Doc=codegen_ir.GenTuDoc(""),
                IsConst=True,
                IsExposedForWrap=False,
            )
        )

        result.append(
            codegen_ir.GenTuFunction(
                Name="sub_variant_get_data",
                ParentClass=parent_class,
                ReturnType=record.variantName.asConstRef(),
                Body=ast.Return(ast.string(record.variantField)),
                Doc=codegen_ir.GenTuDoc(""),
                IsConst=True,
                IsExposedForWrap=False,
            )
        )

        result.append(
            codegen_ir.GenTuFunction(
                Name="sub_variant_get_kind",
                ParentClass=parent_class,
                ReturnType=record.enumName,
                Body=ast.Return(ast.XCall(record.kindGetter)),
                Doc=codegen_ir.GenTuDoc(""),
                IsConst=True,
                IsExposedForWrap=False,
            )
        )

        result.append(
            codegen_ir.GenTuPass(
                ast.Using(
                    cpp.UsingParams(newName="variant_enum_type", baseType=enum_type)
                )
            )
        )

        result.append(
            codegen_ir.GenTuPass(
                ast.Using(
                    cpp.UsingParams(newName="variant_data_type", baseType=variant_type)
                )
            )
        )

        variant_field = codegen_ir.GenTuField(
            Type=copy.deepcopy(variant_type),
            Name=record.variantField,
            Doc=codegen_ir.GenTuDoc(""),
            Value=ast.string(record.variantValue) if record.variantValue else None,
            IsExposedForWrap=False,
        )

        setattr(variant_field, "isVariantField", True)
        setattr(variant_field, "variantGetter", record.kindGetter)

        result.append(variant_field)

    return result


@beartype
def expand_type_groups(
    ast: cpp.ASTBuilder, types: Sequence[codegen_ir.GenTuStruct]
) -> List[codegen_ir.GenTuStruct]:
    return [rec_expand_type(ast, T) for T in types]


@beartype
def verify_type_usage(
    entries: Sequence[codegen_ir.GenTuEntry],
    conf: AstbulderConfig,
    specializations: Sequence[codegen_ir.TypeSpecialization],
):
    specialization_map: Dict[int, codegen_ir.TypeSpecialization] = dict()

    for spec in specializations:
        specialization_map[spec.used_type.qual_hash()] = spec

    def aux(
        entry: codegen_ir.GenTuEntry
        | codegen_ir.GenTuField
        | codegen_ir.QualType
        | codegen_ir.GenTuIdent
        | None,
    ):

        if isinstance(
            entry,
            (
                codegen_ir.GenTuStruct,
                codegen_ir.GenTuField,
                codegen_ir.GenTuFunction,
            ),
        ) and not conf.isAcceptedByBackend(entry):
            return

        match entry:
            case None:
                pass

            case codegen_ir.GenTuIdent():
                aux(entry.Type)

            case codegen_ir.QualType():
                # Type with unresolved template parameters should not be a part of the API
                assert len(entry.getTemplateParameters()) == 0, (
                    f"Found type {entry} with unresolved template parameters"
                )

                if all(
                    [
                        not conf.isRegisteredForBacked(entry),
                        #
                        entry.qual_hash() not in specialization_map,
                    ]
                ):
                    raise ValueError(
                        f"Type {entry} is not registered in the the API map or the list of specializations. "
                        f"List match is {entry.flatQualNameWithParams()}."
                    )

            case codegen_ir.GenTuField():
                if entry.Type:
                    with ExceptionContextNote(f"Field {entry.Name}"):
                        aux(entry.Type)

            case codegen_ir.GenTuStruct():
                if conf.isAcceptedByBackend(entry):
                    with ExceptionContextNote(f"Struct {entry.Name}"):
                        with ExceptionContextNote("Nested elements"):
                            list(map(aux, entry.Nested))

                        with ExceptionContextNote("Methods"):
                            list(map(aux, entry.Methods))

                    # Note: bases are not verified as they are not mandatory
                    # for wrapping on the backends -- the final type can be
                    # treated as an opaque structure without knowing all of
                    # its base classes.

            case codegen_ir.GenTuFunction():
                if conf.isAcceptedByBackend(entry):
                    with ExceptionContextNote(f"Function '{entry.Name}'"):
                        for arg in entry.Args:
                            with ExceptionContextNote(f"Argument {arg.Name}"):
                                aux(arg)

                        with ExceptionContextNote("Return type"):
                            aux(entry.ReturnType)

            case codegen_ir.GenTuTypedef():
                if conf.isAcceptedByBackend(entry):
                    with ExceptionContextNote(
                        f"Typedef {json.dumps(to_debug_json(entry))}"
                    ):
                        aux(entry.Base)

            case codegen_ir.GenTuEnum():
                if conf.isAcceptedByBackend(entry):
                    with ExceptionContextNote(f"Enum {entry.Name}"):
                        aux(entry.Name)

            case codegen_ir.GenTuPass():
                pass

            case _:
                raise TypeError(f"Unexpected entry type {type(entry)}")

    list(map(aux, entries))
