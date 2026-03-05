import itertools

from beartype.typing import List, Any, Set, Optional
from beartype import beartype
from py_codegen import codegen_ir
from py_codegen.codegen_ir import QualType, TypeSpecialization
from py_codegen.astbuilder_base_config import AstbulderConfig
from py_scriptutils.algorithm import iterate_object_tree
from py_scriptutils.script_logging import log

CAT = __name__


@beartype
def collect_type_specializations(
        entries: List[codegen_ir.GenTuUnion],
        conf: AstbulderConfig) -> List[codegen_ir.TypeSpecialization]:
    res = []
    seen_types: Set[int] = set()

    def visit_type(T: QualType):
        if conf.isUnwrappedTemplateInstantiation(T):
            T = T.withoutCVRefRec()
            if hash(T) in seen_types:
                return

            seen_types.add(hash(T))
            res.append(TypeSpecialization(
                used_type=T,
                bind_name=conf.getBindName(T),
            ))

    def visit_type_rec(value: Optional[QualType]) -> None:
        if value is None:
            return

        T = conf.getResolvedType(value)
        visit_type(T)

        for spec in conf.getBaseClassSpecializations(T):
            visit_type(spec)

        for P in T.Params:
            visit_type_rec(P)

    def visit_entry(entry: codegen_ir.GenTuUnion | codegen_ir.GenTuField):
        match entry:
            case codegen_ir.GenTuField():
                if entry.IsExposedForWrap:
                    visit_type_rec(entry.Type)

            case codegen_ir.GenTuFunction():
                if entry.IsExposedForWrap:
                    visit_type_rec(entry.ReturnType)
                    list(map(lambda it: visit_type_rec(it.Type), entry.Args))

            case codegen_ir.GenTuStruct():
                list(map(visit_entry, entry.Methods))
                list(map(visit_entry, entry.Fields))
                list(map(visit_entry, entry.Nested))
                list(map(visit_entry, entry.Bases))

            case codegen_ir.GenTuTypedef():
                visit_entry(entry.Base)

            case codegen_ir.GenTuEnum() | codegen_ir.GenTuPass():
                pass

            case codegen_ir.QualType():
                visit_type_rec(entry)

            case _:
                raise TypeError(f"todo {type(entry)}")

    for e in entries:
        visit_entry(e)

    return res
