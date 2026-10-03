import itertools
import json
from dataclasses import dataclass, field
from pathlib import Path

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from beartype import beartype
from beartype.typing import Dict, List, Sequence
from hstd_py_codegen.gen_cpp import codegen_ir
from hstd_py_codegen.gen_cpp.codegen_ir import QualType
from hstd_py_codegen.lang_build.astbuilder_base_config import (
    AstbulderConfig,
)
from hstd_py_codegen.read_cpp import refl_read
from hstd_py_codegen.read_cpp.refl_read import ConvTu
from hstd_py_lib.script_logging import (
    ExceptionContextNote,
    pprint_to_file_json,
    to_debug_json,
)

import repo_py_orchestrate.src.repo_py_orchestrate.codegen_config.codegen_immutable as gen_imm
import repo_py_orchestrate.src.repo_py_orchestrate.codegen_config.org_codegen_data as org_data


@beartype
def get_concrete_types(
    expanded: List[codegen_ir.GenTuStruct],
) -> Sequence[codegen_ir.GenTuStruct]:
    return [struct for struct in expanded if not struct.IsAbstract]


@beartype
def get_osk_enum(expanded: List[codegen_ir.GenTuStruct]) -> codegen_ir.GenTuEnum:
    return codegen_ir.GenTuEnum(
        QualType.ForName(org_data.t_osk().Name),
        codegen_ir.GenTuDoc(""),
        Fields=[
            codegen_ir.GenTuEnumField(struct.Name.Name, codegen_ir.GenTuDoc(""))
            for struct in get_concrete_types(expanded)
        ],
    )


@beartype
@dataclass
class PyhaxorgTypeGroups:
    "Type groups for wrapping and codegen"

    shared_types: List[codegen_ir.GenTuStruct] = field(default_factory=list)
    expanded: List[codegen_ir.GenTuStruct] = field(default_factory=list)
    immutable: List[codegen_ir.GenTuStruct] = field(default_factory=list)
    adapter_specializations: List[codegen_ir.GenTuStruct] = field(default_factory=list)
    conv_tu: ConvTu = field(default_factory=lambda: ConvTu())
    manual_tu: ConvTu = field(default_factory=lambda: ConvTu())
    type_map: codegen_ir.GenTypeMap = field(
        default_factory=lambda: codegen_ir.GenTypeMap()
    )  # type: ignore[assignment]
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
                    logger.info(
                        f"{'  ' * ind}{e.Name.Name} {e.Name} wrapper:{e.ReflectionParams.wrapper_name} py:{py_type(e.Name, self.type_map)}"
                    )
                    for sub in e.Nested:
                        aux(sub, ind + 1)

        return topological_sort_entries(
            list(
                itertools.chain(
                    self.full_enums,
                    self.conv_tu.enums,
                    self.conv_tu.structs,
                    self.conv_tu.typedefs,
                    self.manual_tu.enums,
                    self.manual_tu.structs,
                    self.manual_tu.typedefs,
                    self.shared_types,
                    self.expanded,
                    self.conv_tu.functions,
                    self.manual_tu.functions,
                    self.immutable,
                    self.imm_id_specializations,
                    self.adapter_specializations,
                    self.only_wrap_entries,
                )
            )
        )


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


@beartype
def get_pyhaxorg_type_groups(
    ast: cpp.ASTBuilder,
    reflection_path: Path,
    manual_tu_path: Path,
) -> PyhaxorgTypeGroups:
    """
    Get type groups and method implementations for the haxorg library
    source file generation and wrappers.
    """
    res = PyhaxorgTypeGroups()
    res.shared_types = expand_type_groups(ast, org_data.get_shared_sem_types())
    res.expanded = expand_type_groups(ast, org_data.get_types())
    adapters = gen_imm.generate_adapter_specializations(ast, res.expanded)
    res.adapter_specializations = adapters
    res.immutable = expand_type_groups(
        ast, gen_imm.rewrite_to_immutable(org_data.get_types())
    )

    res.conv_tu = refl_read.conv_proto_file(reflection_path)
    res.manual_tu = refl_read.conv_proto_file(manual_tu_path)

    pprint_to_file_json(res.manual_tu, Path("/tmp/manual_tu_haxorg.json"))

    res.full_enums = (
        org_data.get_shared_sem_enums()
        + org_data.get_enums()
        + [get_osk_enum(res.expanded)]
    )

    import itertools

    res.type_map = codegen_ir.get_type_map(
        list(
            itertools.chain(
                res.expanded,
                res.shared_types,
                res.immutable,
                res.conv_tu.enums,
                res.conv_tu.structs,
                res.conv_tu.typedefs,
                res.manual_tu.enums,
                res.manual_tu.structs,
                res.manual_tu.typedefs,
                res.full_enums,
            )
        )
    )

    imm_space = [QualType.ForName("org"), QualType.ForName("imm")]
    for sem_base in res.expanded:
        derived_base: str = sem_base.Name.Name
        Derived = QualType(Name=f"Imm{derived_base}", Spaces=imm_space)
        Base = QualType(Name="ImmAdapterTBase", Spaces=imm_space, Params=[Derived])
        res.only_wrap_entries.append(
            codegen_ir.GenTuStruct(
                Name=Base,
                IsTemplateRecord=True,
                IsExplicitInstantiation=True,
                ExplicitTemplateParams=[Derived],
                ReflectionParams=codegen_ir.GenTuReflParams(
                    backend=codegen_ir.GenTuBackendParams(target_backends=["python"]),
                    wrapper_has_params=False,
                    wrapper_name=f"ImmAdapter{derived_base}Base",
                ),
            )
        )

    for org_type in org_data.get_types():
        res.imm_id_specializations.append(
            codegen_ir.GenTuStruct(
                OriginName="imm ID explicit",
                Name=QualType.ForName("ImmIdT", Spaces=imm_space),
                IsExplicitInstantiation=True,
                IsTemplateRecord=True,
                ExplicitTemplateParams=[gen_imm.rewrite_type_to_immutable(org_type.Name)],
                ReflectionParams=codegen_ir.GenTuReflParams(
                    wrapper_name="ImmIdT" + org_type.Name.Name
                ),
                IsDescribedRecord=False,
                Bases=[QualType.ForName("ImmId", Spaces=imm_space)],
            )
        )

    return res
