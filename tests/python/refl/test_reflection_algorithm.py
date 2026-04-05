from py_codegen.codegen_algo import (
    group_by_template,
    match_specializations,
    SpecializationMatchResult,
    TemplateUnificationMatcher,
    unify_qualtype,
    unify_template_params,
)
from py_codegen.codegen_ir import (
    GenTuTemplateGroup,
    GenTuTemplateParams,
    GenTuTemplateTypename,
    QualType,
    ReferenceKind,
    TemplateParamKind,
)
import pytest


def test_unify_qualtype_simple_template_param() -> None:
    specialization = QualType(Name="int", IsBuiltin=True)
    template = QualType(Name="T", IsTemplateTypeParam=True)

    result = unify_qualtype(specialization, template)

    assert result == {"T": specialization}


def test_unify_qualtype_template_param_with_qualifier_stripping() -> None:
    specialization = QualType(
        Name="int",
        IsBuiltin=True,
        IsConst=True,
        RefKind=ReferenceKind.LValue,
    )
    template = QualType(
        Name="T",
        IsTemplateTypeParam=True,
        IsConst=True,
        RefKind=ReferenceKind.LValue,
    )

    result = unify_qualtype(specialization, template)

    assert result == {"T": QualType(Name="int", IsBuiltin=True)}


def test_unify_qualtype_repeated_param_consistency() -> None:
    specialization = QualType(
        Name="pair",
        Params=[
            QualType(Name="int", IsBuiltin=True),
            QualType(Name="int", IsBuiltin=True),
        ],
    )
    template = QualType(
        Name="pair",
        Params=[
            QualType(Name="T", IsTemplateTypeParam=True),
            QualType(Name="T", IsTemplateTypeParam=True),
        ],
    )

    result = unify_qualtype(specialization, template)

    assert result == {"T": QualType(Name="int", IsBuiltin=True)}


def test_unify_qualtype_repeated_param_conflict() -> None:
    specialization = QualType(
        Name="pair",
        Params=[
            QualType(Name="int", IsBuiltin=True),
            QualType(Name="float", IsBuiltin=True),
        ],
    )
    template = QualType(
        Name="pair",
        Params=[
            QualType(Name="T", IsTemplateTypeParam=True),
            QualType(Name="T", IsTemplateTypeParam=True),
        ],
    )

    result = unify_qualtype(specialization, template)

    assert result is None


def test_unify_qualtype_pack_expansion() -> None:
    specialization = QualType(
        Name="tuple",
        Params=[
            QualType(Name="int", IsBuiltin=True),
            QualType(Name="float", IsBuiltin=True),
            QualType(Name="bool", IsBuiltin=True),
        ],
    )
    template = QualType(
        Name="tuple",
        Params=[
            QualType(Name="Ts", IsTemplateTypeParam=True, IsPackExpansion=True),
        ],
    )

    result = unify_qualtype(specialization, template)

    assert result is None


def test_unify_qualtype_pack_expansion_repeated_same_type() -> None:
    specialization = QualType(
        Name="tuple",
        Params=[
            QualType(Name="int", IsBuiltin=True),
            QualType(Name="int", IsBuiltin=True),
        ],
    )
    template = QualType(
        Name="tuple",
        Params=[
            QualType(Name="Ts", IsTemplateTypeParam=True, IsPackExpansion=True),
        ],
    )

    result = unify_qualtype(specialization, template)

    assert result == {"Ts": QualType(Name="int", IsBuiltin=True)}


def test_unify_template_params_type_param_direct() -> None:
    template_param = GenTuTemplateTypename(
        Kind=TemplateParamKind.Type,
        TypeExpr=QualType(Name="T", IsTemplateTypeParam=True),
    )
    specialization = QualType(Name="int", IsBuiltin=True)

    result = unify_template_params(specialization, template_param)

    assert result == {"T": QualType(Name="int", IsBuiltin=True)}


def test_get_name_raises_for_unnamed_param() -> None:
    param = GenTuTemplateTypename(
        Kind=TemplateParamKind.Type,
        TypeExpr=QualType(IsTemplateTypeParam=True),
    )

    with pytest.raises(ValueError, match="does not have a declared name"):
        param.getName()


def test_template_declaration_matching_with_default_type_argument() -> None:
    matcher = TemplateUnificationMatcher(debug=True)

    template_name = QualType(Name="X")
    template_params = GenTuTemplateParams(Stacks=[
        GenTuTemplateGroup(Params=[
            GenTuTemplateTypename(
                Kind=TemplateParamKind.Type,
                TypeExpr=QualType(Name="T", IsTemplateTypeParam=True),
            ),
            GenTuTemplateTypename(
                Kind=TemplateParamKind.Type,
                TypeExpr=QualType(Name="U", IsTemplateTypeParam=True),
                Default=QualType(Name="int", IsBuiltin=True),
            ),
        ])
    ])

    specialization = QualType(
        Name="X",
        Params=[QualType(Name="float", IsBuiltin=True)],
    )

    result = matcher.match_specializations_for_template_params(
        specializations=[specialization],
        template_name=template_name,
        template_params=template_params,
    )

    assert result == [
        SpecializationMatchResult(
            instantiated_name=specialization,
            substitution_map={
                "T": QualType(Name="float", IsBuiltin=True),
                "U": QualType(Name="int", IsBuiltin=True),
            },
        )
    ], matcher.get_debug()


def test_template_declaration_matching_with_instantiated_default_argument() -> None:
    matcher = TemplateUnificationMatcher(debug=True)

    template_name = QualType(Name="X")
    template_params = GenTuTemplateParams(Stacks=[
        GenTuTemplateGroup(Params=[
            GenTuTemplateTypename(
                Kind=TemplateParamKind.Type,
                TypeExpr=QualType(Name="T", IsTemplateTypeParam=True),
            ),
            GenTuTemplateTypename(
                Kind=TemplateParamKind.Type,
                TypeExpr=QualType(Name="U", IsTemplateTypeParam=True),
                Default=QualType(
                    Name="hash",
                    Spaces=[QualType(Name="std", IsNamespace=True)],
                    Params=[QualType(Name="T", IsTemplateTypeParam=True)],
                ),
            ),
        ])
    ])

    specialization = QualType(
        Name="X",
        Params=[QualType(Name="float", IsBuiltin=True)],
    )

    result = matcher.match_specializations_for_template_params(
        specializations=[specialization],
        template_name=template_name,
        template_params=template_params,
    )

    assert result == [
        SpecializationMatchResult(
            instantiated_name=specialization,
            substitution_map={
                "T":
                    QualType(Name="float", IsBuiltin=True),
                "U":
                    QualType(
                        Name="hash",
                        Spaces=[QualType(Name="std", IsNamespace=True)],
                        Params=[
                            QualType(
                                Name="float",
                                IsBuiltin=True,
                                OriginalSubstitutedTemplate=QualType(
                                    Name="T",
                                    IsTemplateTypeParam=True,
                                ),
                            )
                        ],
                    ),
            },
        )
    ], matcher.get_debug()


def test_template_template_parameter_matches_single_type_param_template() -> None:
    matcher = TemplateUnificationMatcher(debug=True)

    template_param = GenTuTemplateTypename(
        Kind=TemplateParamKind.Template,
        TypeExpr=QualType(Name="TT"),
        TemplateParams=GenTuTemplateParams(Stacks=[
            GenTuTemplateGroup(Params=[
                GenTuTemplateTypename(
                    Kind=TemplateParamKind.Type,
                    TypeExpr=QualType(Name="T", IsTemplateTypeParam=True),
                )
            ])
        ]),
    )

    specialization = QualType(
        Name="vector",
        Spaces=[QualType(Name="std", IsNamespace=True)],
        Params=[QualType(Name="X", IsTemplateTypeParam=True)],
    )

    result = matcher.unify_template_params(specialization, template_param)

    assert result == {
        "TT": specialization,
        "X": QualType(Name="X", IsTemplateTypeParam=True),
    } or result == {
        "TT": specialization
    }, matcher.get_debug()


def test_template_template_parameter_mismatch_on_arity() -> None:
    matcher = TemplateUnificationMatcher(debug=True)

    template_param = GenTuTemplateTypename(
        Kind=TemplateParamKind.Template,
        TypeExpr=QualType(Name="TT"),
        TemplateParams=GenTuTemplateParams(Stacks=[
            GenTuTemplateGroup(Params=[
                GenTuTemplateTypename(
                    Kind=TemplateParamKind.Type,
                    TypeExpr=QualType(Name="T", IsTemplateTypeParam=True),
                )
            ])
        ]),
    )

    specialization = QualType(
        Name="map",
        Spaces=[QualType(Name="std", IsNamespace=True)],
        Params=[
            QualType(Name="K", IsTemplateTypeParam=True),
            QualType(Name="V", IsTemplateTypeParam=True),
        ],
    )

    result = matcher.unify_template_params(specialization, template_param)

    assert result is None, matcher.get_debug()


def test_template_template_parameter_matches_non_type_inner_param() -> None:
    matcher = TemplateUnificationMatcher(debug=True)

    template_param = GenTuTemplateTypename(
        Kind=TemplateParamKind.Template,
        TypeExpr=QualType(Name="TT"),
        TemplateParams=GenTuTemplateParams(Stacks=[
            GenTuTemplateGroup(Params=[
                GenTuTemplateTypename(
                    Kind=TemplateParamKind.NonType,
                    TypeExpr=QualType(Name="N"),
                )
            ])
        ]),
    )

    specialization = QualType(
        Name="arr",
        Params=[QualType(Name="N", IsTemplateTypeParam=True)],
    )

    result = matcher.unify_template_params(specialization, template_param)

    assert result == {"TT": specialization}, matcher.get_debug()


def test_template_template_parameter_matches_auto_inner_param() -> None:
    matcher = TemplateUnificationMatcher(debug=True)

    template_param = GenTuTemplateTypename(
        Kind=TemplateParamKind.Template,
        TypeExpr=QualType(Name="TT"),
        TemplateParams=GenTuTemplateParams(Stacks=[
            GenTuTemplateGroup(Params=[
                GenTuTemplateTypename(
                    Kind=TemplateParamKind.NonType,
                    TypeExpr=QualType(Name="auto"),
                )
            ])
        ]),
    )

    specialization = QualType(
        Name="holder",
        Params=[QualType(Name="int", IsBuiltin=True)],
    )

    result = matcher.unify_template_params(specialization, template_param)

    assert result == {"TT": specialization}, matcher.get_debug()


def test_template_template_parameter_matches_nested_template_template_param() -> None:
    matcher = TemplateUnificationMatcher(debug=True)

    nested_inner = GenTuTemplateTypename(
        Kind=TemplateParamKind.Template,
        TypeExpr=QualType(Name="Inner"),
        TemplateParams=GenTuTemplateParams(Stacks=[
            GenTuTemplateGroup(Params=[
                GenTuTemplateTypename(
                    Kind=TemplateParamKind.Type,
                    TypeExpr=QualType(Name="T", IsTemplateTypeParam=True),
                )
            ])
        ]),
    )

    outer_param = GenTuTemplateTypename(
        Kind=TemplateParamKind.Template,
        TypeExpr=QualType(Name="TT"),
        TemplateParams=GenTuTemplateParams(
            Stacks=[GenTuTemplateGroup(Params=[nested_inner])]),
    )

    specialization = QualType(
        Name="outer_template",
        Params=[
            QualType(
                Name="InnerTemplate",
                Params=[QualType(Name="X", IsTemplateTypeParam=True)],
            )
        ],
    )

    result = matcher.unify_template_params(specialization, outer_param)

    assert result == {"TT": specialization}, matcher.get_debug()


def test_template_template_parameter_variadic_inner_param() -> None:
    matcher = TemplateUnificationMatcher(debug=True)

    template_param = GenTuTemplateTypename(
        Kind=TemplateParamKind.Template,
        TypeExpr=QualType(Name="TT"),
        TemplateParams=GenTuTemplateParams(Stacks=[
            GenTuTemplateGroup(Params=[
                GenTuTemplateTypename(
                    Kind=TemplateParamKind.Type,
                    TypeExpr=QualType(Name="T", IsTemplateTypeParam=True),
                    Variadic=True,
                )
            ])
        ]),
    )

    specialization = QualType(
        Name="tuple_like",
        Params=[
            QualType(Name="A", IsTemplateTypeParam=True),
            QualType(Name="B", IsTemplateTypeParam=True),
            QualType(Name="C", IsTemplateTypeParam=True),
        ],
    )

    result = matcher.unify_template_params(specialization, template_param)

    assert result == {"TT": specialization}, matcher.get_debug()


def test_match_specializations_legacy_api() -> None:
    specializations = [
        QualType(Name="Box", Params=[QualType(Name="int", IsBuiltin=True)]),
        QualType(Name="Box", Params=[QualType(Name="float", IsBuiltin=True)]),
        QualType(Name="Other", Params=[QualType(Name="int", IsBuiltin=True)]),
    ]
    template = QualType(
        Name="Box",
        Params=[QualType(Name="T", IsTemplateTypeParam=True)],
    )

    result = match_specializations(specializations, template)

    assert result == [
        SpecializationMatchResult(
            instantiated_name=specializations[0],
            substitution_map={"T": QualType(Name="int", IsBuiltin=True)},
        ),
        SpecializationMatchResult(
            instantiated_name=specializations[1],
            substitution_map={"T": QualType(Name="float", IsBuiltin=True)},
        ),
    ]


def test_group_by_template_raises_on_ambiguity() -> None:
    templates = [
        QualType(Name="Box", Params=[QualType(Name="T", IsTemplateTypeParam=True)]),
        QualType(Name="Box", Params=[QualType(Name="U", IsTemplateTypeParam=True)]),
    ]
    specializations = [
        QualType(Name="Box", Params=[QualType(Name="int", IsBuiltin=True)]),
    ]

    with pytest.raises(ValueError, match="Ambiguous specialization match"):
        group_by_template(templates, specializations)


def test_debug_logging_collects_messages() -> None:
    logs: list[str] = []

    result = unify_qualtype(
        specialization=QualType(Name="int", IsBuiltin=True),
        template=QualType(Name="T", IsTemplateTypeParam=True),
        debug=True,
        debug_sink=logs,
    )

    assert result == {"T": QualType(Name="int", IsBuiltin=True)}
    assert logs
