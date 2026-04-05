from dataclasses import dataclass, replace
import functools
import inspect
import itertools
from pathlib import Path

from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Set, Tuple
from py_codegen import codegen_ir
from py_codegen.astbuilder_base_config import AstbulderConfig
from py_codegen.codegen_ir import (
    GenTuTemplateParams,
    GenTuTemplateTypename,
    QualType,
    QualTypeKind,
    ReferenceKind,
    TemplateParamKind,
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
                return subst.copy_update(
                    OriginalSubstitutedTemplate=Type.model_copy(deep=True),)

            elif subst.isFunction():
                assert subst.Func
                return Type.copy_update(
                    Func=aux_type(subst.Func),
                    Kind=subst.Kind,
                    OriginalSubstitutedTemplate=Type.model_copy(deep=True),
                )

            else:
                return Type.copy_update(
                    Name=subst.Name,
                    Params=list(map(aux, subst.Params)),
                    Spaces=list(map(aux, subst.Spaces)),
                    Kind=subst.Kind,
                    IsTemplateTypeParam=subst.IsTemplateTypeParam,
                    IsTemplateInjectedType=subst.IsTemplateInjectedType,
                    OriginalSubstitutedTemplate=Type.model_copy(deep=True),
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
@dataclass
class SpecializationMatchResult:
    instantiated_name: QualType
    substitution_map: Dict[str, QualType]


@beartype
@dataclass
class TemplateMatchCandidate:
    template_index: int
    substitution_map: Dict[str, QualType]


@beartype
class TemplateUnificationMatcher:
    """
    Stateful matcher for unifying instantiated qualified types against template
    declarations represented as `GenTuTemplateParams`.

    The matcher owns:
    - debug configuration
    - indentation depth for hierarchical logs
    - all recursive unification entry points

    Public module-level helper functions can create a fresh instance of this
    matcher and delegate all work to it.
    """

    def __init__(
        self,
        *,
        debug: bool = False,
        debug_sink: Optional[List[str]] = None,
    ) -> None:
        self.debug = debug
        self.debug_sink = debug_sink if debug_sink is not None else []
        self._indent = 0

    def _log(self, message: str) -> None:
        """
        Record a debug message with current indentation if debug is enabled.
        """
        if self.debug:
            current = inspect.currentframe()
            assert current
            frame = current.f_back

            while frame is not None:
                code = frame.f_code
                name = code.co_name
                filename = code.co_filename

                if (name != "_log" and name != "wrapper" and name != "wrapped" and
                        "@beartype" not in filename and "beartype" not in filename):
                    break

                frame = frame.f_back

            if frame is None:
                raise RuntimeError("Could not determine caller frame")

            location = f"{frame.f_lineno:<3}"
            self.debug_sink.append(f'[{location}] {"  " * self._indent}{message} ')

    def get_debug(self) -> str:
        return "unification matcher log:\n" + "\n".join(self.debug_sink)

    @dataclass
    class _IndentScope:
        matcher: "TemplateUnificationMatcher"

        def __enter__(self) -> None:
            self.matcher._indent += 1

        def __exit__(self, exc_type: Any, exc: Any, tb: Any) -> None:
            self.matcher._indent -= 1

    def _indented(self) -> "_IndentScope":
        return self._IndentScope(self)

    def _copy_subst(self, subst: Dict[str, QualType]) -> Dict[str, QualType]:
        """
        Return a shallow copy of a substitution map.

        Recursive matching uses defensive copies so failed branches do not mutate
        successful sibling branches.
        """
        return dict(subst)

    def _flatten_template_params(
        self,
        template_params: GenTuTemplateParams,
    ) -> List[GenTuTemplateTypename]:
        """
        Flatten stacked parameter groups into a single ordered list.

        This preserves the historic behavior of `getTemplateParams()` which also
        iterated stacks in-order and appended all entries into one sequence.
        """
        result: List[GenTuTemplateTypename] = []
        for stack in template_params.Stacks:
            result.extend(stack.Params)
        return result

    def _strip_qualifiers(
        self,
        specialization: QualType,
        template: QualType,
    ) -> Optional[QualType]:
        """
        Strip qualifiers demanded by a template type parameter wrapper.

        When a template parameter is written with wrappers such as `T const&`
        the specialization must provide at least these wrappers. The returned
        value is the bound payload that should be assigned to `T`.

        Examples:
        - template `T`, specialization `int const&` => bind `T = int const&`
        - template `T const&`, specialization `int const&` => bind `T = int`
        - template `T**`, specialization `int***` => bind `T = int*`
        """
        self._log(
            f"strip qualifiers specialization={specialization!r} template={template!r}")

        if template.RefKind != ReferenceKind.NotRef:
            if specialization.RefKind != template.RefKind:
                self._log("reference kind mismatch while stripping")
                return None
        elif specialization.RefKind != ReferenceKind.NotRef:
            self._log("template does not require reference, keep specialization as-is")
            return specialization

        if template.PtrCount > specialization.PtrCount:
            self._log("pointer count mismatch while stripping")
            return None

        if template.IsConst and not specialization.IsConst:
            self._log("const qualifier missing while stripping")
            return None

        stripped = specialization.copy_update(
            RefKind=specialization.RefKind,
            PtrCount=specialization.PtrCount - template.PtrCount,
            IsConst=specialization.IsConst and not template.IsConst,
        )

        if template.RefKind != ReferenceKind.NotRef:
            stripped = stripped.copy_update(RefKind=ReferenceKind.NotRef)

        self._log(f"stripped specialization -> {stripped!r}")
        return stripped

    def _bind_named_param(
        self,
        name: str,
        value: QualType,
        substitution: Dict[str, QualType],
    ) -> Optional[Dict[str, QualType]]:
        """
        Bind a substitution name to a qualified type.

        If the name was already bound, the value must match exactly.
        """
        self._log(f"bind {name} -> {value!r}")
        if name in substitution:
            if substitution[name] == value:
                self._log(f"binding {name} already present with same value")
                return substitution
            self._log(
                f"binding conflict for {name}: existing={substitution[name]!r} new={value!r}"
            )
            return None

        updated = self._copy_subst(substitution)
        updated[name] = value
        return updated

    def _param_decl_name(self, param: GenTuTemplateTypename) -> Optional[str]:
        """
        Return declared parameter name if present.
        """
        return param.TypeExpr.Name if param.TypeExpr.Name else None

    def _substitute_qualtype(
        self,
        value: QualType,
        substitution: Dict[str, QualType],
    ) -> QualType:
        """
        Instantiate a `QualType` using the current substitution map.

        This is used for default template arguments so omitted parameters can be
        materialized after earlier parameters were already deduced.
        """
        if value.IsTemplateTypeParam and value.Name in substitution:
            bound = substitution[value.Name]
            return bound.copy_update(OriginalSubstitutedTemplate=value)

        new_spaces = [
            self._substitute_qualtype(space, substitution) for space in value.Spaces
        ]
        new_params = [
            self._substitute_qualtype(param, substitution) for param in value.Params
        ]

        new_func = value.Func
        if value.Func is not None:
            new_func = QualType.Function(
                ReturnType=self._substitute_qualtype(value.Func.ReturnType, substitution),
                Args=[
                    self._substitute_qualtype(arg, substitution)
                    for arg in value.Func.Args
                ],
                Class=None if value.Func.Class is None else self._substitute_qualtype(
                    value.Func.Class, substitution),
                IsConst=value.Func.IsConst,
            )

        return value.copy_update(
            Spaces=new_spaces,
            Params=new_params,
            Func=new_func,
        )

    def _qualtype_to_template_param(
        self,
        template: QualType,
    ) -> GenTuTemplateTypename:
        """
        Wrap a legacy `QualType` template description into a type-parameter node.

        This preserves the old public API shape where callers pass a `QualType`
        as the template side.
        """
        return GenTuTemplateTypename(
            Kind=TemplateParamKind.Type,
            TypeExpr=template,
        )

    def _unify_template_template_argument(
        self,
        specialization: QualType,
        template_param: GenTuTemplateTypename,
        substitution: Dict[str, QualType],
    ) -> Optional[Dict[str, QualType]]:
        """
        Match a template-template argument.

        The specialization side is represented by a `QualType` naming the passed
        template entity, while its `Params` list encodes the template parameter
        pattern of that entity.

        Inner parameter names belong to the passed template's own declaration and
        must not leak into the caller-visible substitution map for the outer
        unification. Only the outer template-template parameter itself is bound.
        """
        self._log(
            f"unify template-template specialization={specialization!r} template_param={template_param!r}"
        )
        assert template_param.TemplateParams is not None

        expected_params = self._flatten_template_params(template_param.TemplateParams)
        actual_params = specialization.Params

        with self._indented():
            inner_subst = self._unify_template_param_list_against_qualtype_params(
                actual_params=actual_params,
                expected_params=expected_params,
                substitution={},
            )
            if inner_subst is None:
                self._log("template-template parameter list mismatch")
                return None

            name = self._param_decl_name(template_param)
            if name is not None:
                return self._bind_named_param(name, specialization, substitution)

            return substitution

    def _qualtype_non_type_category_matches(
        self,
        specialization: QualType,
        template_expr: QualType,
    ) -> bool:
        """
        Match the category of a non-type template parameter.

        A non-type template parameter declaration can constrain the category by:
        - concrete type like `int`
        - deduced `auto`

        For template-template parameter shape matching, the passed template
        entity is represented by placeholder `QualType` entries in
        `specialization.Params`. Those placeholders should be accepted as long as
        they structurally represent a parameter slot of the required category.
        """
        if template_expr.Name == "auto":
            return True

        if specialization.IsTemplateTypeParam:
            return True

        return self._qualtype_structural_equal(specialization, template_expr)

    def _qualtype_structural_equal(
        self,
        lhs: QualType,
        rhs: QualType,
    ) -> bool:
        """
        Structural equality helper used for fixed non-deduced comparisons.
        """
        return lhs == rhs

    def _unify_param_decl_with_argument(
        self,
        specialization: QualType,
        template_param: GenTuTemplateTypename,
        substitution: Dict[str, QualType],
    ) -> Optional[Dict[str, QualType]]:
        """
        Unify one template parameter declaration against one actual template
        argument from a specialization.
        """
        self._log(
            f"unify decl param kind={template_param.Kind} specialization={specialization!r}"
        )

        if template_param.Kind == TemplateParamKind.Type:
            return self.unify_template_params(
                specialization=specialization,
                template_param=template_param,
                substitution=substitution,
            )

        if template_param.Kind == TemplateParamKind.NonType:
            if not self._qualtype_non_type_category_matches(
                    specialization,
                    template_param.TypeExpr,
            ):
                self._log("non-type template parameter category mismatch")
                return None

            name = self._param_decl_name(template_param)
            if name is None:
                return substitution
            return self._bind_named_param(name, specialization, substitution)

        if template_param.Kind == TemplateParamKind.Template:
            return self._unify_template_template_argument(
                specialization=specialization,
                template_param=template_param,
                substitution=substitution,
            )

        raise ValueError(f"Unsupported template parameter kind: {template_param.Kind}")

    def _unify_template_param_list_against_qualtype_params(
        self,
        actual_params: List[QualType],
        expected_params: List[GenTuTemplateTypename],
        substitution: Dict[str, QualType],
    ) -> Optional[Dict[str, QualType]]:
        """
        Unify a sequence of actual specialization arguments against a sequence
        of template parameter declarations.

        Supports:
        - omitted trailing parameters with defaults
        - variadic final parameters
        """
        self._log(
            f"unify parameter list actual_count={len(actual_params)} expected_count={len(expected_params)}"
        )

        fixed_expected = expected_params
        variadic_param: Optional[GenTuTemplateTypename] = None
        if fixed_expected and fixed_expected[-1].Variadic:
            variadic_param = fixed_expected[-1]
            fixed_expected = fixed_expected[:-1]

        min_required = sum(1 for param in fixed_expected if param.Default is None)
        if len(actual_params) < min_required:
            self._log("too few actual template arguments")
            return None

        if variadic_param is None and len(actual_params) > len(expected_params):
            self._log("too many actual template arguments")
            return None

        current = self._copy_subst(substitution)

        with self._indented():
            fixed_actual_count = min(len(actual_params), len(fixed_expected))
            for idx in range(fixed_actual_count):
                current = self._unify_param_decl_with_argument(
                    specialization=actual_params[idx],
                    template_param=fixed_expected[idx],
                    substitution=current,
                )
                if current is None:
                    self._log(f"failed to unify fixed parameter at index {idx}")
                    return None

            if len(actual_params) < len(fixed_expected):
                for idx in range(len(actual_params), len(fixed_expected)):
                    default_expr = fixed_expected[idx].Default
                    if default_expr is None:
                        self._log(f"missing non-defaulted parameter at index {idx}")
                        return None

                    instantiated_default = self._substitute_qualtype(
                        default_expr, current)
                    self._log(
                        f"use default for parameter index {idx}: {instantiated_default!r}"
                    )

                    name = self._param_decl_name(fixed_expected[idx])
                    if name is not None:
                        current = self._bind_named_param(
                            name,
                            instantiated_default,
                            current,
                        )
                        if current is None:
                            return None

            if variadic_param is not None:
                variadic_name = self._param_decl_name(variadic_param)

                for idx in range(len(fixed_expected), len(actual_params)):
                    if variadic_param.Kind == TemplateParamKind.Type:
                        template_expr = variadic_param.TypeExpr

                        if template_expr.IsTemplateTypeParam and variadic_name is not None:
                            # Variadic template parameter packs are represented in the
                            # external substitution map by binding the pack name to the
                            # whole matched template entity elsewhere, not by forcing all
                            # pack elements to unify to the same single QualType.
                            #
                            # For parameter-list shape matching we only need each element
                            # to be a valid argument for this declaration slot.
                            continue

                    current = self._unify_param_decl_with_argument(
                        specialization=actual_params[idx],
                        template_param=variadic_param,
                        substitution=current,
                    )
                    if current is None:
                        self._log(f"failed to unify variadic parameter at index {idx}")
                        return None

            elif len(actual_params) > len(fixed_expected):
                extra_start = len(fixed_expected)
                current_expected = expected_params[extra_start:]
                for offset, param_decl in enumerate(current_expected):
                    actual_idx = extra_start + offset
                    current = self._unify_param_decl_with_argument(
                        specialization=actual_params[actual_idx],
                        template_param=param_decl,
                        substitution=current,
                    )
                    if current is None:
                        self._log(
                            f"failed to unify trailing parameter at index {actual_idx}")
                        return None

        return current

    def unify_template_params(
        self,
        specialization: QualType,
        template_param: GenTuTemplateTypename,
        substitution: Optional[Dict[str, QualType]] = None,
    ) -> Optional[Dict[str, QualType]]:
        """
        Unify a specialization `QualType` against one template parameter
        declaration.

        For type parameters this generalizes the historic `unify_qualtype`
        behavior while also supporting richer template parameter declarations.

        Returns:
            A substitution map if successful, otherwise `None`.
        """
        if substitution is None:
            substitution = {}

        self._log(
            f"unify_template_params specialization={specialization!r} template_param={template_param!r}"
        )

        if template_param.Kind != TemplateParamKind.Type:
            return self._unify_param_decl_with_argument(
                specialization=specialization,
                template_param=template_param,
                substitution=substitution,
            )

        template = template_param.TypeExpr

        if template.IsTemplateTypeParam:
            has_qualifiers = (template.IsConst or template.PtrCount > 0 or
                              template.RefKind != ReferenceKind.NotRef)

            if has_qualifiers:
                stripped = self._strip_qualifiers(specialization, template)
                if stripped is None:
                    self._log("failed to strip qualifiers for template type param")
                    return None
                bound_value = stripped
            else:
                bound_value = specialization

            param_name = template.Name
            if param_name:
                return self._bind_named_param(param_name, bound_value, substitution)
            return substitution

        if template.Kind != specialization.Kind:
            self._log(
                f"type kind mismatch template={template.Kind} specialization={specialization.Kind}"
            )
            return None

        if template.Kind == QualTypeKind.TypeExpr:
            if template.Expr != specialization.Expr:
                self._log("type expression mismatch")
                return None
            return substitution

        if template.Kind == QualTypeKind.FunctionPtr:
            if template.Func is None or specialization.Func is None:
                self._log("function pointer payload missing")
                return None

            if template.IsConst != specialization.IsConst:
                self._log("function pointer const mismatch")
                return None
            if template.PtrCount != specialization.PtrCount:
                self._log("function pointer ptrcount mismatch")
                return None
            if template.RefKind != specialization.RefKind:
                self._log("function pointer refkind mismatch")
                return None

            current = self._copy_subst(substitution)
            with self._indented():
                current = self.unify_qualtype(
                    specialization=specialization.Func.ReturnType,
                    template=template.Func.ReturnType,
                    substitution=current,
                )
                if current is None:
                    self._log("function return type mismatch")
                    return None

                if len(template.Func.Args) != len(specialization.Func.Args):
                    self._log("function arg count mismatch")
                    return None

                for t_arg, s_arg in zip(template.Func.Args, specialization.Func.Args):
                    current = self.unify_qualtype(
                        specialization=s_arg,
                        template=t_arg,
                        substitution=current,
                    )
                    if current is None:
                        self._log("function arg mismatch")
                        return None

                if (template.Func.Class is None) != (specialization.Func.Class is None):
                    self._log("function class qualifier presence mismatch")
                    return None

                if template.Func.Class is not None:
                    current = self.unify_qualtype(
                        specialization=specialization.Func.Class,
                        template=template.Func.Class,
                        substitution=current,
                    )
                    if current is None:
                        self._log("member function class mismatch")
                        return None

                if template.Func.IsConst != specialization.Func.IsConst:
                    self._log("member function const mismatch")
                    return None

            return current

        if template.Name != specialization.Name:
            self._log(
                f"type name mismatch template={template.Name!r} specialization={specialization.Name!r}"
            )
            return None

        if template.IsConst != specialization.IsConst:
            self._log("const qualifier mismatch")
            return None
        if template.PtrCount != specialization.PtrCount:
            self._log("pointer count mismatch")
            return None
        if template.RefKind != specialization.RefKind:
            self._log("reference kind mismatch")
            return None

        if len(template.Spaces) != len(specialization.Spaces):
            self._log("namespace nesting mismatch")
            return None

        current = self._copy_subst(substitution)
        with self._indented():
            for t_space, s_space in zip(template.Spaces, specialization.Spaces):
                current = self.unify_qualtype(
                    specialization=s_space,
                    template=t_space,
                    substitution=current,
                )
                if current is None:
                    self._log("namespace component mismatch")
                    return None

            if template.Params and template.Params[-1].IsPackExpansion:
                non_pack = template.Params[:-1]
                pack_param = template.Params[-1]

                if len(specialization.Params) < len(non_pack):
                    self._log("not enough params for pack expansion")
                    return None

                for t_param, s_param in zip(non_pack,
                                            specialization.Params[:len(non_pack)]):
                    current = self.unify_qualtype(
                        specialization=s_param,
                        template=t_param,
                        substitution=current,
                    )
                    if current is None:
                        self._log("non-pack template param mismatch")
                        return None

                pack_pattern = pack_param.copy_update(IsPackExpansion=False)
                for s_param in specialization.Params[len(non_pack):]:
                    current = self.unify_qualtype(
                        specialization=s_param,
                        template=pack_pattern,
                        substitution=current,
                    )
                    if current is None:
                        self._log("pack element mismatch")
                        return None
            else:
                if len(template.Params) != len(specialization.Params):
                    self._log("template parameter count mismatch")
                    return None

                for t_param, s_param in zip(template.Params, specialization.Params):
                    current = self.unify_qualtype(
                        specialization=s_param,
                        template=t_param,
                        substitution=current,
                    )
                    if current is None:
                        self._log("template argument mismatch")
                        return None

        return current

    def unify_qualtype(
        self,
        specialization: QualType,
        template: QualType,
        substitution: Optional[Dict[str, QualType]] = None,
    ) -> Optional[Dict[str, QualType]]:
        """
        Compatibility wrapper over template-parameter unification.

        The provided `template` qualtype is wrapped into a synthetic
        `GenTuTemplateTypename` and then unified through the richer
        template-parameter matching path.
        """
        template_param = self._qualtype_to_template_param(template)
        return self.unify_template_params(
            specialization=specialization,
            template_param=template_param,
            substitution=substitution,
        )

    def find_matching_template(
        self,
        specialization: QualType,
        templates: List[QualType],
    ) -> Optional[Tuple[int, Dict[str, QualType]]]:
        """
        Find the first matching legacy `QualType` template for a specialization.

        This preserves the old helper behavior and is mainly intended for the
        compatibility free function API.
        """
        for i, template in enumerate(templates):
            result = self.unify_qualtype(specialization, template)
            if result is not None:
                return (i, result)
        return None

    def match_specializations(
        self,
        specializations: List[QualType],
        template: QualType,
    ) -> List[SpecializationMatchResult]:
        """
        Match a list of instantiated specializations against a single legacy
        `QualType` template.
        """
        results: List[SpecializationMatchResult] = []
        for spec in specializations:
            subst = self.unify_qualtype(spec, template)
            if subst is not None:
                results.append(
                    SpecializationMatchResult(
                        instantiated_name=spec,
                        substitution_map=subst,
                    ))
        return results

    def match_specializations_for_template_params(
        self,
        specializations: List[QualType],
        template_name: QualType,
        template_params: GenTuTemplateParams,
    ) -> List[SpecializationMatchResult]:
        """
        Match instantiated specializations against a template declaration defined
        by a type name plus `GenTuTemplateParams`.

        This is the primary new API for matching real template declarations.
        """
        declared_params = self._flatten_template_params(template_params)
        results: List[SpecializationMatchResult] = []

        for spec in specializations:
            self._log(f"match specialization against template declaration: {spec!r}")
            if spec.Kind != template_name.Kind:
                continue
            if spec.Name != template_name.Name:
                continue
            if len(spec.Spaces) != len(template_name.Spaces):
                continue
            if spec.IsConst != template_name.IsConst:
                continue
            if spec.PtrCount != template_name.PtrCount:
                continue
            if spec.RefKind != template_name.RefKind:
                continue

            current: Dict[str, QualType] = {}

            ok = True
            for t_space, s_space in zip(template_name.Spaces, spec.Spaces):
                current = self.unify_qualtype(
                    specialization=s_space,
                    template=t_space,
                    substitution=current,
                ) or {}
                if current is None:
                    ok = False
                    break

            if not ok:
                continue

            subst = self._unify_template_param_list_against_qualtype_params(
                actual_params=spec.Params,
                expected_params=declared_params,
                substitution=current,
            )
            if subst is not None:
                results.append(
                    SpecializationMatchResult(
                        instantiated_name=spec,
                        substitution_map=subst,
                    ))

        return results

    def group_by_template_qualtypes(
        self,
        templates: List[QualType],
        specializations: List[QualType],
    ) -> Dict[int, List[SpecializationMatchResult]]:
        """
        Group specializations by legacy `QualType` templates.

        If a specialization matches more than one template, raises `ValueError`
        with diagnostics instead of silently taking the first match.
        """
        groups: Dict[int, List[SpecializationMatchResult]] = {}

        for spec in specializations:
            matches: List[TemplateMatchCandidate] = []
            for idx, template in enumerate(templates):
                subst = self.unify_qualtype(spec, template)
                if subst is not None:
                    matches.append(
                        TemplateMatchCandidate(
                            template_index=idx,
                            substitution_map=subst,
                        ))

            if len(matches) > 1:
                raise ValueError(
                    f"Ambiguous specialization match for {spec!r}: "
                    f"matched templates {[m.template_index for m in matches]}")

            if len(matches) == 1:
                match = matches[0]
                groups.setdefault(match.template_index, []).append(
                    SpecializationMatchResult(
                        instantiated_name=spec,
                        substitution_map=match.substitution_map,
                    ))

        return groups

    def group_by_template_declarations(
        self,
        templates: List[Tuple[QualType, GenTuTemplateParams]],
        specializations: List[QualType],
    ) -> Dict[int, List[SpecializationMatchResult]]:
        """
        Group specializations by full template declarations.

        Each declaration is provided as:
            (template_name_without_instantiated_args, template_params)

        If a specialization matches more than one declaration, raises `ValueError`
        with diagnostics to force the caller to resolve ambiguity explicitly.
        """
        groups: Dict[int, List[SpecializationMatchResult]] = {}

        for spec in specializations:
            matches: List[TemplateMatchCandidate] = []

            for idx, (template_name, template_params) in enumerate(templates):
                result = self.match_specializations_for_template_params(
                    specializations=[spec],
                    template_name=template_name,
                    template_params=template_params,
                )
                if result:
                    matches.append(
                        TemplateMatchCandidate(
                            template_index=idx,
                            substitution_map=result[0].substitution_map,
                        ))

            if len(matches) > 1:
                details = ", ".join(
                    f"template#{m.template_index} subst={m.substitution_map!r}"
                    for m in matches)
                raise ValueError(
                    f"Ambiguous specialization match for {spec!r}: {details}")

            if len(matches) == 1:
                match = matches[0]
                groups.setdefault(match.template_index, []).append(
                    SpecializationMatchResult(
                        instantiated_name=spec,
                        substitution_map=match.substitution_map,
                    ))

        return groups


@beartype
def unify_template_params(
    specialization: QualType,
    template_param: GenTuTemplateTypename,
    substitution: Dict[str, QualType] | None = None,
    *,
    debug: bool = False,
    debug_sink: Optional[List[str]] = None,
) -> Optional[Dict[str, QualType]]:
    """
    Public compatibility helper for unifying a specialization against a rich
    template parameter declaration.
    """
    matcher = TemplateUnificationMatcher(debug=debug, debug_sink=debug_sink)
    return matcher.unify_template_params(
        specialization=specialization,
        template_param=template_param,
        substitution=substitution,
    )


@beartype
def unify_qualtype(
    specialization: QualType,
    template: QualType,
    substitution: Dict[str, QualType] | None = None,
    *,
    debug: bool = False,
    debug_sink: Optional[List[str]] = None,
) -> Optional[Dict[str, QualType]]:
    """
    Public compatibility helper for the historic `QualType`-vs-`QualType`
    unification API.

    Internally the template is wrapped into a synthetic
    `GenTuTemplateTypename` and unified via `unify_template_params`.
    """
    matcher = TemplateUnificationMatcher(debug=debug, debug_sink=debug_sink)
    return matcher.unify_qualtype(
        specialization=specialization,
        template=template,
        substitution=substitution,
    )


@beartype
def find_matching_template(
    specialization: QualType,
    templates: List[QualType],
    *,
    debug: bool = False,
    debug_sink: Optional[List[str]] = None,
) -> Optional[Tuple[int, Dict[str, QualType]]]:
    """
    Given a specialization and a list of legacy `QualType` templates, find the
    first template that the specialization unifies with.
    """
    matcher = TemplateUnificationMatcher(debug=debug, debug_sink=debug_sink)
    return matcher.find_matching_template(specialization, templates)


@beartype
def match_specializations(
    specializations: List[QualType],
    template: QualType,
    *,
    debug: bool = False,
    debug_sink: Optional[List[str]] = None,
) -> List[SpecializationMatchResult]:
    """
    Match legacy `QualType` specializations against one legacy `QualType`
    template.
    """
    matcher = TemplateUnificationMatcher(debug=debug, debug_sink=debug_sink)
    return matcher.match_specializations(specializations, template)


@beartype
def group_by_template(
    templates: List[QualType],
    specializations: List[QualType],
    *,
    debug: bool = False,
    debug_sink: Optional[List[str]] = None,
) -> Dict[int, List[SpecializationMatchResult]]:
    """
    Group specializations by legacy `QualType` templates.

    Raises:
        ValueError: if a specialization ambiguously matches multiple templates.
    """
    matcher = TemplateUnificationMatcher(debug=debug, debug_sink=debug_sink)
    return matcher.group_by_template_qualtypes(templates, specializations)
