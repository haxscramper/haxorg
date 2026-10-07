import itertools
from dataclasses import dataclass, field

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
import repo_py_orchestrate.codegen_config.gen_haxorg.immutable as gen_imm
import repo_py_orchestrate.codegen_config.org_codegen_data as org_data
from beartype import beartype
from beartype.typing import List, Sequence
from hstd_py_codegen.gen_cpp import codegen_ir
from hstd_py_codegen.gen_cpp.codegen_ir import QualType
from hstd_py_codegen.gen_cpp.codegen_type_order import (
    expand_type_groups,
)


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
    full_enums: List[codegen_ir.GenTuEnum] = field(default_factory=list)
    imm_id_specializations: List[codegen_ir.GenTuStruct] = field(default_factory=list)
    only_wrap_entries: List[codegen_ir.GenTuUnion] = field(default_factory=list)
    "Types not exposed for codegen, but only for entry wrapping"

    def get_protobuf_target_entires(self) -> Sequence[codegen_ir.GenTuUnion]:
        return self.full_enums + self.shared_types + self.expanded

    def get_all(self) -> list[codegen_ir.GenTuUnion]:
        return list(
            itertools.chain(
                self.full_enums,
                self.shared_types,
                self.expanded,
                self.immutable,
                self.imm_id_specializations,
                self.adapter_specializations,
                self.only_wrap_entries,
            )
        )


@beartype
def get_pyhaxorg_type_groups(ast: cpp.ASTBuilder) -> PyhaxorgTypeGroups:
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

    res.full_enums = (
        org_data.get_shared_sem_enums()
        + org_data.get_enums()
        + [get_osk_enum(res.expanded)]
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
