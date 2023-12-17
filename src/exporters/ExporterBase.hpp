#pragma once

import org.exporters.Exporter;

/// \brief Trigger field visitation for value object
#define __obj_field(res, obj, name)                                       \
    visitFieldRedirect(res, #name, obj.name);

#define __org_field(res, obj, name)                                       \
    visitFieldRedirect(res, #name, obj->name);

template <typename V, typename R>
void Exporter<V, R>::visitField(R& arg, const char* name, sem::SemId org) {
    __visit_scope(
        VisitEvent::Kind::VisitEnd,
        .visitedNode  = org,
        .field        = name,
        .visitedValue = &arg);

    _this()->visit(arg, org);
}

template <typename V, typename R>
void Exporter<V, R>::visitSubnode(R& tmp, int, sem::SemId val) {
    _this()->visit(tmp, val);
}

template <typename V, typename R>
void Exporter<V, R>::visitDispatch(R& res, sem::SemId arg) {
    __visit_scope(
        VisitEvent::Kind::VisitDispatch,
        .visitedValue = &res,
        .visitedNode  = arg);

    if (arg.isNil()) {
        return;
    }

    auto kind = arg->getKind();
    switch (kind) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        In<sem::__Kind> tmp = arg.as<sem::__Kind>();                      \
        _this()->pushVisit(res, tmp);                                     \
        _this()->visitDispatchHook(res, arg);                             \
        _this()->visit##__Kind(res, tmp);                                 \
        _this()->popVisit(res, tmp);                                      \
        break;                                                            \
    }


        EACH_SEM_ORG_KIND(__case)

#undef __case
    }
}

template <typename V, typename R>
R Exporter<V, R>::evalTop(sem::SemId org) {
    __visit_scope(VisitEvent::Kind::VisitTop, .visitedNode = org);

    _this()->visitStart(org);
    R tmp = _this()->newRes(org);
    _this()->visit(tmp, org);
    _this()->visitEnd(org);
    return tmp;
}
