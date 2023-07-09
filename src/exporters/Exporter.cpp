#pragma once

#include <exporters/Exporter.hpp>

/// \brief Trigger field visitation for value object
#define __obj_field(res, obj, name)                                       \
    visitFieldRedirect(res, #name, obj.name);

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
R Exporter<V, R>::visitTop(sem::SemId org) {
    __visit_scope(VisitEvent::Kind::VisitTop, .visitedNode = org);

    _this()->visitStart(org);
    R tmp = _this()->newRes(org);
    _this()->visit(tmp, org);
    _this()->visitEnd(org);
    return tmp;
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                               res,
    CR<sem::Code::Switch::LineStart> start) {
    __obj_field(res, start, start);
    __obj_field(res, start, extendLast);
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                   res,
    CR<sem::Code::Switch::CalloutFormat> start) {
    __obj_field(res, start, format);
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                   res,
    CR<sem::Code::Switch::RemoveCallout> start) {
    __obj_field(res, start, remove);
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                   res,
    CR<sem::Code::Switch::EmphasizeLine> start) {
    __obj_field(res, start, line);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Code::Switch::Dedent> start) {
    __obj_field(res, start, value);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Code::Switch::Data> data) {
    visitVariants(res, sem::Code::Switch::getKind(data), data);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Code::Switch> sw) {
    visit(res, sw.data);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Time::Repeat> repeat) {
    __obj_field(res, repeat, period);
    __obj_field(res, repeat, count);
    __obj_field(res, repeat, mode);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<UserTime> time) {
    visitVariants(res, time.getKind(), time.time);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Time::Static> time) {
    __obj_field(res, time, time);
    __obj_field(res, time, repeat);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Time::Dynamic> time) {
    __obj_field(res, time, expr);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Time::TimeVariant> time) {
    visitVariants(res, sem::Time::getTimeKind(time), time);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Link::Id> id) {
    __obj_field(res, id, text);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Link::Footnote> id) {
    __obj_field(res, id, target);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Link::Raw> raw) {
    __obj_field(res, raw, text);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Link::File> raw) {
    __obj_field(res, raw, file);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Link::Person> raw) {
    __obj_field(res, raw, name);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Link::Data> data) {
    visitVariants(res, sem::Link::getLinkKind(data), data);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::SubtreeLog::State> state) {
    __obj_field(res, state, from);
    __obj_field(res, state, to);
    __obj_field(res, state, on);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::SubtreeLog::Clock> state) {
    swl::visit(
        [&, this](const auto& it) {
            _this()->visitField(res, "range", it);
        },
        state.range);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::SubtreeLog::Tag> state) {
    __obj_field(res, state, tag);
    __obj_field(res, state, added);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::SubtreeLog::Refile> state) {
    __obj_field(res, state, on);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::SubtreeLog::Note> state) {
    __obj_field(res, state, on);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::SubtreeLog::LogEntry> entry) {
    visitVariants(res, sem::SubtreeLog::getLogKind(entry), entry);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Include::Example> p) {}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Include::Export> p) {}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Include::Src> p) {}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Include::OrgDocument> p) {}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Include::Data> prop) {
    visitVariants(res, sem::Include::getIncludeKind(prop), prop);
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                  res,
    CR<sem::DocumentOptions::TocExport> prop) {
    visitVariants(res, static_cast<int>(prop.index()), prop);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Symbol::Param> param) {
    __obj_field(res, param, key);
    __obj_field(res, param, value);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Subtree::Property::Ordered> p) {
    __obj_field(res, p, isOrdered);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Subtree::Property::Origin> p) {
    __obj_field(res, p, text);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Subtree::Property::Effort> p) {
    __obj_field(res, p, hours);
    __obj_field(res, p, minutes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                     res,
    CR<sem::Subtree::Property::Visibility> p) {
    __obj_field(res, p, level);
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                        res,
    CR<sem::Subtree::Property::ExportOptions> p) {
    __obj_field(res, p, backend);
    __obj_field(res, p, values);
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                           res,
    CR<sem::Subtree::Property::ExportLatexClass> p) {
    __obj_field(res, p, latexClass);
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                            res,
    CR<sem::Subtree::Property::ExportLatexHeader> p) {
    __obj_field(res, p, header);
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                              res,
    CR<sem::Subtree::Property::ExportLatexCompiler> p) {
    __obj_field(res, p, compiler);
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                      res,
    CR<sem::Subtree::Property::Nonblocking> o) {
    __obj_field(res, o, isBlocking);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Subtree::Property::Blocker> o) {
    __obj_field(res, o, blockers);
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                  res,
    CR<sem::Subtree::Property::Trigger> trigger) {}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                     res,
    CR<sem::Subtree::Property::Unnumbered> trigger) {}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                  res,
    CR<sem::Subtree::Property::Created> created) {
    __obj_field(res, created, time);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Subtree::Property> prop) {
    __obj_field(res, prop, data);
    __obj_field(res, prop, mainSetRule);
    __obj_field(res, prop, subSetRule);
    __obj_field(res, prop, inheritanceMode);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::Subtree::Property::Data> prop) {
    visitVariants(res, sem::Subtree::Property::getKind(prop), prop);
}

template <typename V, typename R>
template <sem::NotOrg T>
void Exporter<V, R>::visitDescribedOrgFields(R& res, CR<T> value) {}

template <typename V, typename R>
template <sem::IsOrg T>
void Exporter<V, R>::visitDescribedOrgFields(R& res, In<T> tree) {
    using Bd = describe_bases<T, mod_any_access>;
    using Md = describe_members<T, mod_any_access>;
    mp_for_each<Md>([&](auto const& field) {
        _this()->visitField(
            res,
            field.name,
            (*static_cast<T const*>(tree.get())).*field.pointer);
    });

    mp_for_each<Bd>([&](auto Base) {
        visitDescribedOrgFields<typename decltype(Base)::type>(res, tree);
    });
}

template <typename V, typename R>
template <typename T, typename Kind>
void Exporter<V, R>::visitVariants(R& res, Kind kind, CR<T> var) {
    QString fieldName = to_string(kind);
    _this()->visitField(res, "kind", kind);
    swl::visit(
        [&, this](const auto& it) {
            _this()->visitField(res, fieldName.toLatin1(), it);
        },
        var);
}
