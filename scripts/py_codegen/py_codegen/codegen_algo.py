from dataclasses import dataclass, replace
import itertools

from beartype.typing import List, Any, Set, Optional
from beartype import beartype
from py_codegen import codegen_ir
from py_codegen.codegen_ir import QualType, TypeSpecialization
from py_codegen.astbuilder_base_config import AstbulderConfig
from py_scriptutils.algorithm import iterate_object_tree
from py_scriptutils.script_logging import log
import functools

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
                bind_name=conf.getTypeBindName(T),
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


@beartype
def _get_template_parameters(Type: QualType) -> List[QualType]:
    found = list()

    def aux(Type: QualType):
        nonlocal found
        if Type.IsTemplateTypeParam:
            found.append(Type)

    Type.visit_recursive(aux)

    return found


@beartype
@dataclass
class _InstantiateCtx():
    substitution_map: dict[str, QualType]
    type_map: codegen_ir.GenTypeMap


@beartype
def _map_template_type(Type: QualType | None, ctx: _InstantiateCtx) -> QualType | None:

    def aux(Type: QualType | None) -> QualType | None:
        if not Type:
            return Type

        if Type.Name in ctx.substitution_map:
            return ctx.substitution_map[Type.Name]

        match Type.Kind:
            case codegen_ir.QualTypeKind.RegularType | codegen_ir.QualTypeKind.Array:
                return Type.copy_update(
                    Params=map(aux, Type.Params),
                    Spaces=map(aux, Type.Spaces),
                )

            case codegen_ir.QualTypeKind.FunctionPtr:
                assert Type.Func
                return Type.copy_update(Func=Type.Func.model_copy(update=dict(
                    ReturnType=aux(Type.Func.ReturnType),
                    Args=map(aux, Type.Func.Args),
                    Class=aux(Type.Func.Class),
                )))

            case _:
                return Type

    return aux(Type)


@beartype
def _map_template_struct(ctx: _InstantiateCtx,
                         base: codegen_ir.GenTuStruct) -> codegen_ir.GenTuStruct:
    if not base.TemplateParams:
        return base

    updated_stack = codegen_ir.GenTuTemplateParams()

    explicit_params = list()

    for _stack in base.TemplateParams.Stacks:
        updated_group = codegen_ir.GenTuTemplateGroup()
        for _param in _stack.Params:
            if _param.Name in ctx.substitution_map:
                substituted = ctx.substitution_map[_param.Name]
                for _nested in _get_template_parameters(substituted):
                    updated_group.Params.append(
                        codegen_ir.GenTuTemplateTypename(Name=_nested.Name))

                explicit_params.append(substituted)

            else:
                updated_group.Params.append(_param)

        updated_stack.Stacks.append(updated_group)

    _map = functools.partial(_instantiate_template, ctx)

    return replace(
        base,
        IsTemplateRecord=True,
        IsExplicitInstantiation=True,
        TemplateParams=updated_stack,
        Nested=list(map(_map, base.Nested)),
        Methods=list(map(_map, base.Methods)),
        Fields=list(map(_map, base.Fields)),
        ExplicitTemplateParams=base.ExplicitTemplateParams + explicit_params,
    )


@beartype
def _map_template_function(ctx: _InstantiateCtx,
                           func: codegen_ir.GenTuFunction) -> codegen_ir.GenTuFunction:
    result = replace(
        func,
        Args=[replace(Arg, Type=_map_template_type(Arg.Type, ctx)) for Arg in func.Args],
        ParentClass=_map_template_type(func.ParentClass, ctx),
        ReturnType=_map_template_type(func.ReturnType, ctx),
    )

    return result


@beartype
def _instantiate_template(_ctx: _InstantiateCtx,
                          Base: codegen_ir.GenTuEntry) -> codegen_ir.GenTuEntry:
    match Base:
        case codegen_ir.GenTuStruct():
            return _map_template_struct(_ctx, Base)

        case codegen_ir.GenTuPass():
            return Base

        case codegen_ir.GenTuFunction():
            return _map_template_function(_ctx, Base)

        case codegen_ir.GenTuField():
            return replace(Base, Type=_map_template_type(Base.Type, _ctx))

        case _:
            raise TypeError(type(Base))


@beartype
def instantiate_template(
    Base: codegen_ir.GenTuDeclaration,
    substitution_map: dict[str, QualType],
    type_map: codegen_ir.GenTypeMap,
) -> codegen_ir.GenTuDeclaration:
    return _instantiate_template(  # type: ignore
        _InstantiateCtx(substitution_map=substitution_map, type_map=type_map),
        Base,
    )
