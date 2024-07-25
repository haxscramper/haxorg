#pragma once

#include <exporters/Exporter.hpp>

template <typename T>
struct TypeName {
    static Str get() {
        return Str(demangle(typeid(T).name())).replaceAll("sem::", "");
    }
};


template <typename T>
struct TypeName<Opt<T>> {
    static Str get() {
        return Str("Opt<") + TypeName<T>::get() + Str(">");
    }
};

template <typename K, typename V>
struct TypeName<UnorderedMap<K, V>> {
    static Str get() {
        return "UnorderedMap<"_ss + TypeName<K>::get() + ", "_ss
             + TypeName<V>::get() + ">"_ss;
    }
};

template <typename... Args>
struct TypeName<Variant<Args...>> {
    static Str get() {
        return "Variant<"_ss
             + Str(join(", ", Vec<Str>{TypeName<Args>::get()...}))
             + ">"_ss;
    }
};

/// \brief Trigger field visitation for value object
#define __obj_field(res, obj, name)                                       \
    visitFieldRedirect(res, #name, obj.name);

#define __org_field(res, obj, name)                                       \
    visitFieldRedirect(res, #name, obj->name);

template <typename V, typename R>
void Exporter<V, R>::visitField(
    R&                   arg,
    const char*          name,
    sem::SemId<sem::Org> org) {
    auto __scope = __visit_field_scope(name);
    _this()->visit(arg, org);
}

template <typename V, typename R>
void Exporter<V, R>::visitSubnode(R& tmp, int, sem::SemId<sem::Org> val) {
    _this()->visit(tmp, val);
}

template <typename V, typename R>
void Exporter<V, R>::visitDispatch(R& res, sem::SemId<sem::Org> arg) {
    __visit_scope(VisitReport::Kind::VisitDispatch, arg);

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
R Exporter<V, R>::evalTop(sem::SemId<sem::Org> org) {
    auto __scope = __visit_scope(VisitReport::Kind::VisitTop, org);
    _this()->visitStart(org);
    R tmp = _this()->newRes(org);
    _this()->visit(tmp, org);
    _this()->visitEnd(org);
    return tmp;
}
