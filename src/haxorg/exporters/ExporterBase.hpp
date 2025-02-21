#pragma once

#include <haxorg/exporters/Exporter.hpp>

/// \brief Trigger field visitation for value object
#define __obj_field(res, obj, name)                                       \
    visitFieldRedirect(res, #name, obj.name);

#define __org_field(res, obj, name)                                       \
    visitFieldRedirect(res, #name, obj->name);

template <typename V, typename R>
void org::algo::Exporter<V, R>::visitField(
    R&                   arg,
    const char*          name,
    sem::SemId<sem::Org> org) {
    auto __scope = trace_scope(trace(VisitReport::Kind::VisitField)
                                   .with_field(name)
                                   .with_node(org));
    _this()->visit(arg, org);
}

template <typename V, typename R>
void org::algo::Exporter<V, R>::visitSubnode(
    R& tmp,
    int,
    sem::SemId<sem::Org> val) {
    _this()->visit(tmp, val);
}

template <typename V, typename R>
void org::algo::Exporter<V, R>::visitDispatch(
    R&                   res,
    sem::SemId<sem::Org> arg) {
    auto __scope = trace(VisitReport::Kind::VisitDispatch).with_node(arg);

    if (arg.isNil()) { return; }

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
R org::algo::Exporter<V, R>::evalTop(sem::SemId<sem::Org> org) {
    auto __scope = trace_scope(
        trace(VisitReport::Kind::VisitTop).with_node(org));
    _this()->visitStart(org);
    R tmp = _this()->newRes(org);
    _this()->visit(tmp, org);
    _this()->visitEnd(org);
    return tmp;
}
