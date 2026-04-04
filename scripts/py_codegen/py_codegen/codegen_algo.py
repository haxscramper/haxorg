from dataclasses import dataclass, replace
import functools
import itertools

from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Set, Tuple
from py_codegen import codegen_ir
from py_codegen.astbuilder_base_config import AstbulderConfig
from py_codegen.codegen_ir import (
    QualType,
    QualTypeKind,
    ReferenceKind,
    TypeSpecialization,
)
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
                bind_name=conf.getTypeBindName(T),
            ))

    def visit_type_rec(value: Optional[QualType]) -> None:
        if value is None:
            return

        # Not all template parameters were substituted in this instance
        # -- the type is not a full specialization, ignoring.
        if value.getTemplateParameters():
            return

        T = conf.getResolvedType(value)
        visit_type(T)

        for spec in conf.getBaseClassSpecializations(T):
            visit_type(spec)

        for P in T.Params:
            visit_type_rec(P)

    def visit_entry(entry: Any):
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
@dataclass
class _InstantiateCtx():
    substitution_map: dict[str, QualType]
    type_map: codegen_ir.GenTypeMap


@beartype
def _map_template_type(Type: QualType | None, ctx: _InstantiateCtx) -> QualType | None:

    def aux(Type: QualType | None) -> QualType | None:

        def aux_type(Func: QualType.Function) -> QualType.Function:
            return Func.model_copy(update=dict(
                ReturnType=aux(Func.ReturnType),
                Args=list(map(aux, Func.Args)),
                Class=aux(Func.Class),
            ))

        if not Type:
            return Type

        if Type.Name in ctx.substitution_map:
            subst = ctx.substitution_map[Type.Name]
            if subst.Kind == codegen_ir.QualTypeKind.TypeExpr:
                return subst

            elif subst.isFunction():
                assert subst.Func
                return Type.copy_update(
                    Func=aux_type(subst.Func),
                    Kind=subst.Kind,
                )

            else:
                return Type.copy_update(
                    Name=subst.Name,
                    Params=list(map(aux, subst.Params)),
                    Spaces=list(map(aux, subst.Spaces)),
                    Kind=subst.Kind,
                    IsTemplateTypeParam=subst.IsTemplateTypeParam,
                    IsTemplateInjectedType=subst.IsTemplateInjectedType,
                )

        match Type.Kind:
            case codegen_ir.QualTypeKind.RegularType | codegen_ir.QualTypeKind.Array:
                return Type.copy_update(
                    Params=list(map(aux, Type.Params)),
                    Spaces=list(map(aux, Type.Spaces)),
                )

            case codegen_ir.QualTypeKind.FunctionPtr:
                assert Type.Func
                return Type.copy_update(Func=aux_type(Type.Func))

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
                for _nested in substituted.getTemplateParameters():
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


@beartype
def _strip_qualifiers(
    specialization: QualType,
    template: QualType,
) -> Optional[QualType]:
    """
    If the template node is a template type parameter with qualifiers/pointers/refs,
    check that the specialization has at least those qualifiers, and return a
    stripped copy of the specialization with those qualifiers removed.

    For a bare `T` (no qualifiers), returns the specialization as-is.
    For `T const&`, checks the specialization is `const&` and strips those.
    For `T const**`, checks the specialization has const and >=2 pointers, strips them.

    Returns None if the specialization doesn't have the required qualifiers.
    """
    # Check ref kind: template demands a specific ref kind
    if template.RefKind != ReferenceKind.NotRef:
        if specialization.RefKind != template.RefKind:
            return None
    elif specialization.RefKind != ReferenceKind.NotRef:
        # Template doesn't demand a ref, but specialization has one.
        # A bare `T` can match `int const&` — T binds to `int const&`.
        # So we do NOT strip here; return as-is.
        return specialization

    # Check pointer count: template demands at least this many
    if template.PtrCount > specialization.PtrCount:
        return None

    # Check const: if template demands const, specialization must have it
    if template.IsConst and not specialization.IsConst:
        return None

    # Now strip what the template demands
    stripped = specialization.model_copy(
        update={
            "RefKind":
                ReferenceKind.NotRef if template.RefKind !=
                ReferenceKind.NotRef else specialization.RefKind,
            "PtrCount":
                specialization.PtrCount - template.PtrCount,
            "IsConst":
                specialization.IsConst and not template.IsConst,
        })

    # If template demanded a ref, we already checked it matches, now strip it
    if template.RefKind != ReferenceKind.NotRef:
        stripped = stripped.model_copy(update={"RefKind": ReferenceKind.NotRef})

    return stripped


@beartype
def unify_qualtype(
    specialization: QualType,
    template: QualType,
    substitution: Dict[str, QualType] | None = None,
) -> Optional[Dict[str, QualType]]:
    """
    Attempt unification of the template type and its specialization. If unification
    is successful, the function returns a dictionary with all the template type
    parameters in the original template substituted for whatever was matched in the
    specialization.
    """
    if substitution is None:
        substitution = {}

    # If the template node is a template type parameter, handle variable binding
    if template.IsTemplateTypeParam:
        has_qualifiers = (template.IsConst or template.PtrCount > 0 or
                          template.RefKind != ReferenceKind.NotRef)

        if has_qualifiers:
            stripped = _strip_qualifiers(specialization, template)
            if stripped is None:
                return None
            bound_value = stripped
        else:
            bound_value = specialization

        param_name = template.Name
        if param_name in substitution:
            if substitution[param_name] == bound_value:
                return substitution
            else:
                return None
        else:
            substitution[param_name] = bound_value
            return substitution

    # Kind must match
    if template.Kind != specialization.Kind:
        return None

    if template.Kind == QualTypeKind.TypeExpr:
        assert template.Expr is not None
        assert specialization.Expr is not None
        if template.Expr != specialization.Expr:
            return None
        return substitution

    if template.Kind == QualTypeKind.FunctionPtr:
        assert template.Func
        assert template.Func is not None
        assert specialization.Func is not None

        # Qualifiers on the function pointer type itself
        if template.IsConst != specialization.IsConst:
            return None
        if template.PtrCount != specialization.PtrCount:
            return None
        if template.RefKind != specialization.RefKind:
            return None

        # Return type
        substitution = unify_qualtype(specialization.Func.ReturnType,
                                      template.Func.ReturnType, substitution)
        if substitution is None:
            return None

        # Args
        if len(template.Func.Args) != len(specialization.Func.Args):
            return None
        for t_arg, s_arg in zip(template.Func.Args, specialization.Func.Args):
            substitution = unify_qualtype(s_arg, t_arg, substitution)
            if substitution is None:
                return None

        # Class (member function pointer)
        if (template.Func.Class is None) != (specialization.Func.Class is None):
            return None
        if template.Func.Class is not None:
            substitution = unify_qualtype(specialization.Func.Class, template.Func.Class,
                                          substitution)
            if substitution is None:
                return None

        if template.Func.IsConst != specialization.Func.IsConst:
            return None

        return substitution

    # RegularType and Array both use Name + Params + qualifiers

    # Name must match
    if template.Name != specialization.Name:
        return None

    # For concrete types, qualifiers must match exactly
    if template.IsConst != specialization.IsConst:
        return None
    if template.PtrCount != specialization.PtrCount:
        return None
    if template.RefKind != specialization.RefKind:
        return None

    # Namespace spaces must unify
    if len(template.Spaces) != len(specialization.Spaces):
        return None
    for t_space, s_space in zip(template.Spaces, specialization.Spaces):
        substitution = unify_qualtype(s_space, t_space, substitution)
        if substitution is None:
            return None

    # Template parameters / array dimensions — handle pack expansion
    if template.Params and template.Params[-1].IsPackExpansion:
        non_pack = template.Params[:-1]
        pack_param = template.Params[-1]
        if len(specialization.Params) < len(non_pack):
            return None
        for t_param, s_param in zip(non_pack, specialization.Params[:len(non_pack)]):
            substitution = unify_qualtype(s_param, t_param, substitution)
            if substitution is None:
                return None
        pack_pattern = pack_param.copy_update(IsPackExpansion=False)
        for s_param in specialization.Params[len(non_pack):]:
            substitution = unify_qualtype(s_param, pack_pattern, substitution)
            if substitution is None:
                return None
    else:
        if len(template.Params) != len(specialization.Params):
            return None
        for t_param, s_param in zip(template.Params, specialization.Params):
            substitution = unify_qualtype(s_param, t_param, substitution)
            if substitution is None:
                return None

    return substitution


@beartype
def find_matching_template(
    specialization: QualType,
    templates: List[QualType],
) -> Optional[Tuple[int, Dict[str, QualType]]]:
    """
    Given a specialization and a list of template types, find the first template
    that the specialization is an instantiation of.
    Returns (index, substitution_map) or None.
    """
    for i, template in enumerate(templates):
        result = unify_qualtype(specialization, template)
        if result is not None:
            return (i, result)
    return None


@beartype
@dataclass
class SpecializationMatchResult():
    instantiated_name: QualType
    substitution_map: Dict[str, QualType]


@beartype
def match_specializations(
    specializations: List[QualType],
    template: QualType,
) -> List[SpecializationMatchResult]:
    """
    Given a list of specializations and a single template, return a list of
    (specialization, substitution_map) pairs for each specialization that
    successfully unifies with the template.
    """
    results = []
    for spec in specializations:
        subst = unify_qualtype(spec, template)
        if subst is not None:
            results.append(
                SpecializationMatchResult(
                    instantiated_name=spec,
                    substitution_map=subst,
                ))
    return results


@beartype
def group_by_template(
    templates: List[QualType],
    specializations: List[QualType],
) -> Dict[int, List[SpecializationMatchResult]]:
    """
    Given a list of templates and a list of specializations, produce a mapping
    from template index to the list of (specialization, substitution_map) pairs
    that matched it.

    Each specialization is assigned to the first template it matches.
    Specializations that don't match any template are omitted.
    """
    groups: Dict[int, List[SpecializationMatchResult]] = {}
    for spec in specializations:
        result = find_matching_template(spec, templates)
        if result is not None:
            idx, subst = result
            if idx not in groups:
                groups[idx] = []
            groups[idx].append(
                SpecializationMatchResult(
                    instantiated_name=spec,
                    substitution_map=subst,
                ))
    return groups
