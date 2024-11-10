/// \file Implementation of methods shared for both sem AST and immutable
/// AST

#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/Ranges.hpp>

namespace {
template <sem::IsOrg T>
T* getMutHandle(T* ptr) {
    return ptr;
}

template <sem::IsOrg T>
T* getMutHandle(sem::SemId<sem::Org> ptr) {
    return ptr.get();
}


template <org::IsImmOrgValueType T>
T* getMutHandle(org::ImmAdapterT<T> ptr) {
    return ptr.get();
}

template <sem::IsOrg T>
T const* getConstHandle(T* ptr) {
    return ptr;
}

template <sem::IsOrg T>
T const* getConstHandle(sem::SemId<T> ptr) {
    return ptr.get();
}


template <org::IsImmOrgValueType T>
T const* getConstHandle(org::ImmAdapterT<T> ptr) {
    return ptr.get();
}

} // namespace


namespace {
template <typename Handle>
Vec<sem::NamedProperty> subtreeGetPropertiesImpl(
    Handle       handle,
    Str const&   kind,
    CR<Opt<Str>> subkind) {
    Vec<sem::NamedProperty> result;
    for (const auto& prop : getConstHandle(handle)->properties) {
        if (prop.isMatching(kind, subkind)) { result.push_back(prop); }
    }
    return result;
}

template <typename Handle>
Opt<sem::NamedProperty> subtreeGetPropertyImpl(
    Handle       handle,
    Str const&   kind,
    CR<Opt<Str>> subkind) {
    auto props = subtreeGetPropertiesImpl(handle, kind, subkind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        return props[0];
    }
}


// clang-format off
Vec<org::ImmAdapter> getSubnodes(org::ImmAdapter const& t, bool withPath) { return t.sub(withPath); }
template <typename T>
Vec<org::ImmAdapter> getSubnodes(org::ImmAdapterT<T> const& t, bool withPath) { return t.sub(withPath); }
template <sem::IsOrg T>
Vec<sem::SemId<sem::Org>> getSubnodes(sem::SemId<T> const& t, bool withPath) { return t->subnodes; }
template <sem::IsOrg T>
Vec<sem::SemId<sem::Org>> getSubnodes(T const* t, bool withPath) { return t->subnodes; }
// clang-format on

bool is_kind(org::ImmAdapter const& ad, OrgSemKind kind) {
    return ad.getKind() == kind;
}

template <sem::IsOrg T>
bool is_kind(sem::SemId<T> const& ad, OrgSemKind kind) {
    return ad->getKind() == kind;
}

/// \brief Cast sem ID type to target
template <sem::IsOrg Out, sem::IsOrg In>
sem::SemId<Out> org_cast(sem::SemId<In> arg) {
    return arg.template as<Out>();
}

/// \brief Cast imm ID type to target.
///
/// The target is specified as sem ID, but return type is mapped to imm ID.
/// This is made for uniform API and more streamlined use on the callsite.
template <sem::IsOrg Out, org::IsImmOrgValueType In>
org::ImmAdapterT<typename org::sem_to_imm_map<Out>::imm_type> org_cast(
    org::ImmAdapterT<In> arg) {
    return arg.template as<typename org::sem_to_imm_map<Out>::imm_type>();
}

template <sem::IsOrg Out>
org::ImmAdapterT<typename org::sem_to_imm_map<Out>::imm_type> org_cast(
    org::ImmAdapter arg) {
    return arg.template as<typename org::sem_to_imm_map<Out>::imm_type>();
}

/// brief Helper function to check if value is 'empty' -- used to
/// streamline `Box<Opt<Imm>>` vs `Opt<Sem>` type handling.
template <typename T>
bool isBoolFalse(T const& t) {
    return value_metadata<T>::isEmpty(t);
}

/// \brief Convert immer ID to the imm adapter.
template <org::IsImmOrgValueType T, typename Handle>
org::ImmAdapterT<T> toHandle(org::ImmIdT<T> id, Handle const& handle) {
    return org::ImmAdapterT<T>{id, handle.ctx, {}};
}

/// \brief Convert sem ID to the sem ID -- identity function.
template <sem::IsOrg T, typename Handle>
sem::SemId<T> toHandle(sem::SemId<T> id, Handle const& handle) {
    return id;
}

/// \brief Convert optional imm ID to optional adapter
template <org::IsImmOrgValueType T, typename Handle>
Opt<org::ImmAdapterT<T>> toHandle(
    Opt<org::ImmIdT<T>> id,
    Handle const&       handle) {
    if (id) {
        return toHandle(id.value(), handle);
    } else {
        return std::nullopt;
    }
}

template <org::IsImmOrgValueType T, typename Handle>
org::ImmAdapterT<T> toHandle(
    org::ImmAdapterT<T> id,
    Handle const&       handle) {
    return id;
}

template <typename Handle>
org::ImmAdapter toHandle(org::ImmAdapter id, Handle const& handle) {
    return id;
}

/// \brief Convert boxed optional imm ID to optional adapter
template <org::IsImmOrgValueType T, typename Handle>
Opt<org::ImmAdapterT<T>> toHandle(
    ImmBox<Opt<org::ImmIdT<T>>> id,
    Handle const&               handle) {
    return toHandle(id.get(), handle);
}

template <sem::IsOrg T, typename Handle>
Opt<sem::SemId<T>> toHandle(Opt<sem::SemId<T>> id, Handle const& handle) {
    return id;
}

/// \brief return object that supports `.apiCall()` for org-mode API
template <sem::IsOrg T>
T const& to_api(sem::SemId<T> it) {
    return *it.get();
}

template <sem::IsOrg T>
T const& to_api(T const* it) {
    return *it;
}

template <org::IsImmOrgValueType T>
org::ImmAdapterT<T> to_api(org::ImmAdapterT<T> it) {
    return it;
}

template <sem::IsOrg T>
T const& to_value(sem::SemId<T> const& it) {
    return *it.get();
}

template <sem::IsOrg T>
T const& to_value(T const* it) {
    return *it;
}

template <org::IsImmOrgValueType T>
T const& to_value(org::ImmAdapterT<T> it) {
    return *it.template dyn_cast<T>();
}

/// \brief Unwrap type `T` and get underlying sem/imm type, define nested
/// `ast_type` for result.
template <typename T>
struct get_ast_type {};

template <typename T>
struct get_ast_type<org::ImmAdapterT<T>> {
    using ast_type = T;
};

template <>
struct get_ast_type<org::ImmAdapter> {
    using ast_type = org::ImmOrg;
};


template <typename T>
struct get_ast_type<sem::SemId<T>> {
    using ast_type = T;
};

template <typename T>
struct get_ast_type<T*> {
    using ast_type = T;
};

/// \brief Select between sem org type and imm org type based on the
/// leading typename `T`
///
/// If `T` is a sem type, define nested `result = SemType`, otherwise
/// define `result = ImmType`.
template <typename T, typename SemType, typename ImmType>
    requires sem::IsOrg<T> || org::IsImmOrgValueType<T>
struct SemOrImmType {};

/// \brief Org type selector specialization to select sem type
template <sem::IsOrg T, typename SemType, typename ImmType>
struct SemOrImmType<T, SemType, ImmType> {
    using result = SemType;
};

/// \brief Org type selector specialization to select immer type
template <org::IsImmOrgValueType T, typename SemType, typename ImmType>
struct SemOrImmType<T, SemType, ImmType> {
    using result = ImmType;
};

template <typename T>
using SemIdOrImmId = SemOrImmType<
    typename get_ast_type<T>::ast_type,
    sem::SemId<sem::Org>,
    org::ImmAdapter>::result;

template <typename Handle>
concept IsSemOrgInstance = sem::IsOrg<
    typename get_ast_type<Handle>::ast_type>;

template <typename Handle>
concept IsImmOrgInstance = org::IsImmOrgValueType<
    typename get_ast_type<Handle>::ast_type>;

/// \brief Generic implementation of the subtree period collection --
/// subtree period type is a shared data type, so in this function only
/// parametrizing on the handle parameter.
template <typename Handle>
Vec<sem::SubtreePeriod> Subtree_getTimePeriodsImpl(
    Handle                           handle,
    IntSet<sem::SubtreePeriod::Kind> kinds,
    bool                             withPath) {
    Vec<sem::SubtreePeriod> res;
    // Get final handle version that can access fields down the line
    auto h = getConstHandle(handle);
    // `sem::T` or `sem::ImmT` type for later compile-time selection
    using HandleBase = get_ast_type<Handle>::ast_type;
    using sem::SubtreePeriod;

    // From now on, frequent usage of `toHandle` is needed to convert immer
    // ID nodes to adapters that can be property accessed -- immer AST
    // types do not store /full/ context necessary for accessing the final
    // value, instead they only store ID elements. And `toHandle` is needed
    // in order to take an ID and parent adapter (which has necessary
    // context pointers), and return an new adapter.
    //
    // For sem IDs this is an identity function that returns the ID
    // directly.

    for (const auto& it :
         getSubnodes(toHandle(h->title, handle), withPath)) {
        if (it->getKind() == OrgSemKind::Time) {
            SubtreePeriod period{};
            // Specifying `sem::Time` in the cast, but returned type also
            // depends on the type of the adapter -- if this is an immer
            // adapter, the final cast would be to `org::ImmTime`,
            period.from = org_cast<sem::Time>(it)->getStatic().time;
            period.kind = SubtreePeriod::Kind::Titled;
            res.push_back(period);
        } else if (it->getKind() == OrgSemKind::TimeRange) {
            SubtreePeriod period{};
            period.from = toHandle(
                              org_cast<sem::TimeRange>(it)->from, handle)
                              ->getStatic()
                              .time;
            period.to = toHandle(org_cast<sem::TimeRange>(it)->to, handle)
                            ->getStatic()
                            .time;
            period.kind = SubtreePeriod::Kind::Titled;
            res.push_back(period);
        }
    }

    if (kinds.contains(SubtreePeriod::Kind::Deadline)
        && !isBoolFalse(h->deadline)) {
        SubtreePeriod period{};
        period.from = toHandle(h->deadline, handle)
                          .value()
                          ->getStatic()
                          .time;
        period.kind = SubtreePeriod::Kind::Deadline;
        res.push_back(period);
    }

    if (kinds.contains(SubtreePeriod::Kind::Scheduled)
        && !isBoolFalse(h->scheduled)) {
        SubtreePeriod period{};
        period.from = toHandle(h->scheduled, handle)
                          .value()
                          ->getStatic()
                          .time;
        period.kind = SubtreePeriod::Kind::Scheduled;
        res.push_back(period);
    }

    if (kinds.contains(SubtreePeriod::Kind::Closed)
        && !isBoolFalse(h->closed)) {
        SubtreePeriod period{};
        period.from = toHandle(h->closed, handle)
                          .value()
                          ->getStatic()
                          .time;
        period.kind = SubtreePeriod::Kind::Closed;
        res.push_back(period);
    }

    if (kinds.contains(SubtreePeriod::Kind::Clocked)) {
        // Subtree log is an AST type which has nested enum definitions,
        // which are identical in structure, but from the compiler
        // perspective `org::ImmSubtreeLog::Kind` and
        // `sem::SubtreeLog::Kind` are two different classes. That's why I
        // need to use the type selector here and define the target log
        // type.
        using LogType = SemOrImmType<
            HandleBase,
            sem::SubtreeLog,
            org::ImmSubtreeLog>::result;

        for (auto const& logIt : h->logbook) {
            auto const log = toHandle(logIt, handle);
            if (log->getLogKind() == LogType::Kind::Clock) {
                SubtreePeriod period{};
                period.from = toHandle(log->getClock().from, handle)
                                  ->getStatic()
                                  .time;
                if (!isBoolFalse(log->getClock().to)) {
                    period.to = //
                        toHandle(log->getClock().to, handle)
                            .value()
                            ->getStatic()
                            .time;
                }
                period.kind = SubtreePeriod::Kind::Clocked;
                res.push_back(period);
            }
        }
    }

    for (const auto& prop : h->properties) {
        std::visit(
            overloaded{
                [&](sem::NamedProperty::Created const& cr) {
                    SubtreePeriod period{};
                    period.from = cr.time;
                    period.kind = SubtreePeriod::Kind::Created;
                    res.push_back(period);
                },
                [](auto const&) {}},
            prop.data);
    }


    return res;
}

template <typename Handle>
Vec<sem::AttrValue> Attrs_getAttrs(
    Handle const& handle,
    CR<Opt<Str>>  param) {
    auto h           = getConstHandle(handle);
    using HandleBase = get_ast_type<Handle>::ast_type;
    Vec<sem::AttrValue> res;
    if (param) {
        auto norm = normalize(*param);
        if (h->named.contains(norm)) {
            for (auto const& it :
                 toHandle(h->named.at(norm), handle)->args) {
                res.push_back(toHandle(it, handle)->arg);
            }
        }
    } else {
        for (auto const& it : toHandle(h->positional, handle)->args) {
            res.push_back(toHandle(it, handle)->arg);
        }

        for (auto const& [it, _1] : h->named) {
            for (auto const& val :
                 toHandle(h->named.at(it), handle)->args) {
                res.push_back(toHandle(val, handle)->arg);
            }
        }
    }

    return res;
}

template <typename Handle>
Vec<sem::AttrValue> Stmt_getAttrs(Handle handle, const Opt<Str>& kind) {
    auto h           = getConstHandle(handle);
    using HandleBase = get_ast_type<Handle>::ast_type;

    Vec<sem::AttrValue> result;

    for (auto const& sub : h->attached) {
        if (toHandle(sub, handle)->getKind() == OrgSemKind::CmdAttr) {
            result.append( //
                Attrs_getAttrs(
                    toHandle(
                        org_cast<sem::CmdAttr>(toHandle(sub, handle))
                            ->attrs,
                        handle)
                        .value(),
                    kind));
        }
    }

    return result;
}

template <typename Handle>
Vec<Vec<Str>> HashTag_getFlatHashes(Handle handle, bool withIntermediate) {
    using Res = Vec<Vec<Str>>;
    Func<Res(Vec<Str> const& parents, Handle const& tag)> aux;
    UnorderedSet<Vec<Str>>                                visited;
    aux = [&](Vec<Str> const& parents, Handle const& tag) -> Res {
        auto const& t = to_value(tag);
        Res         result;
        if (withIntermediate && !parents.empty()
            && !visited.contains(parents)) {
            result.push_back(parents);
            visited.incl(parents);
        }
        if (t.subtags.empty()) {
            result.push_back(parents);
            result.back().push_back(t.head);
        } else {
            for (auto const& subtag : t.subtags) {
                if constexpr (IsSemOrgInstance<Handle>) {
                    result.append(
                        aux(parents + Vec<Str>{t.head}, subtag.get()));
                } else {
                    result.append(
                        aux(parents + Vec<Str>{t.head},
                            toHandle(subtag, handle)));
                }
            }
        }
        return result;
    };

    return aux({}, handle);
}

Vec<org::ImmAdapter> Org_getLeadNodes(
    org::ImmAdapter const& it,
    OrgSemKind             kind,
    SemSet const&          skip) {
    Vec<org::ImmAdapter> result;
    for (auto const& sub : it.sub()) {
        if (sub->getKind() == kind) {
            result.push_back(sub);
        } else if (skip.contains(sub->getKind())) {
            continue;
        } else {
            break;
        }
    }

    return result;
}

Vec<sem::SemId<sem::Org>> Org_getLeadNodes(
    sem::Org const* it,
    OrgSemKind      kind,
    SemSet const&   skip) {
    Vec<sem::SemId<sem::Org>> result;
    for (auto const& sub : *it) {
        if (sub->getKind() == kind) {
            result.push_back(sub);
        } else if (skip.contains(sub->getKind())) {
            continue;
        } else {
            break;
        }
    }

    return result;
}

template <typename Handle, typename Select = SemIdOrImmId<Handle>>
Vec<Select> Paragraph_dropAdmonitionNodes(Handle handle, bool withPath) {
    Vec<Select> result;
    bool        lead     = true;
    auto        subnodes = getSubnodes(handle, withPath);
    for (int i = 0; i < subnodes.size(); ++i) {
        auto const& sub = subnodes.at(i);
        if (lead) {
            if (sub->getKind() == OrgSemKind::BigIdent) {
                if (auto next = subnodes.get(i + 1); next) {
                    SemIdOrImmId<Handle> colon = next.value().get();
                    if (sub->getKind() == OrgSemKind::BigIdent
                        && colon->getKind() == OrgSemKind::Punctuation
                        && to_api(toHandle(
                                      org_cast<sem::Punctuation>(colon),
                                      handle))
                                   .getText()
                               == ":") {
                        ++i;
                    }
                }
            } else if (sub->getKind() == OrgSemKind::Link) {
                bool isFootnote = false;
                if constexpr (IsSemOrgInstance<Handle>) {
                    isFootnote = sub.template as<sem::Link>()
                                     ->target.isFootnote();
                } else {
                    isFootnote = sub.template as<org::ImmLink>()
                                     ->target.isFootnote();
                }

                if (!isFootnote) { lead = false; }

            } else if (!SemSet{
                           OrgSemKind::HashTag,
                           OrgSemKind::BigIdent,
                           OrgSemKind::Time,
                           OrgSemKind::RadioTarget,
                           OrgSemKind::Space,
                       }
                            .contains(sub->getKind())) {
                lead = false;
                result.push_back(sub);
            }
        } else {
            result.push_back(sub);
        }
    }
    return result;
}

template <typename T>
Vec<org::ImmAdapterT<T>> mapNodes(Vec<org::ImmAdapter> const& nodes) {
    return nodes | rv::transform([](org::ImmAdapter const& id) {
               return id.as<T>();
           })
         | rs::to<Vec>();
}

template <typename T>
Vec<sem::SemId<T>> mapNodes(Vec<sem::SemId<sem::Org>> const& nodes) {
    return nodes | rv::transform([](sem::SemId<sem::Org> const& id) {
               return id.as<T>();
           })
         | rs::to<Vec>();
}

template <typename Handle>
Vec<sem::AttrValue> Cmd_getAttrs(
    Handle const& handle,
    CR<Opt<Str>>  param) {
    auto                h = getConstHandle(handle);
    Vec<sem::AttrValue> res;
    if (!isBoolFalse(h->attrs)) {
        res = Attrs_getAttrs(toHandle(h->attrs, handle).value(), param);
    }
    res.append(Stmt_getAttrs(handle, param));
    return res;
}

template <typename Handle>
Opt<sem::AttrValue> Stmt_getFirstAttr(Handle handle, CR<Str> kind) {
    auto h   = getConstHandle(handle);
    auto res = Stmt_getAttrs(handle, kind);

    if (res.empty()) {
        return std::nullopt;
    } else {
        return res.front();
    }
}

template <typename Handle>
Opt<sem::AttrValue> Cmd_getFirstAttr(Handle handle, Str const& kind) {
    auto h = getConstHandle(handle);
    if (!isBoolFalse(h->attrs)) {
        auto res = Attrs_getAttrs(
            toHandle(h->attrs, handle).value(), kind);
        if (res.empty()) {
            return std::nullopt;
        } else {
            return res.front();
        }
    } else {
        return Stmt_getFirstAttr(handle, kind);
    }
}

template <typename Handle>
auto Stmt_getAttached(Handle handle, CR<Opt<Str>> kind) {
    using Select = SemOrImmType<
        typename get_ast_type<Handle>::ast_type,
        sem::SemId<sem::Org>,
        org::ImmAdapter>;

    Vec<typename Select::result> result;
    auto                         h = getConstHandle(handle);
    for (const auto& sub : h->attached) {
        auto sub_h = toHandle(sub, handle);
        if (kind) {
            auto k = normalize(*kind);
            if (is_kind(sub_h, OrgSemKind::CmdAttr)) {
                auto attr = org_cast<sem::CmdAttr>(sub_h);
                if ((k.starts_with("attr") && normalize(attr->target) == k)
                    || (normalize("attr_" + attr->target) == k)) {
                    result.push_back(sub_h);
                }
            } else if (
                is_kind(sub_h, OrgSemKind::CmdCaption)
                && normalize(k) == "caption") {

                result.push_back(sub_h);
            } else if (
                is_kind(sub_h, OrgSemKind::CmdName)
                && normalize(k) == "name") {
                result.push_back(sub_h);
            }
        } else {
            result.push_back(sub_h);
        }
    }

    return result;
}

template <typename Handle>
auto Stmt_getCaption(Handle handle) {
    using Select = SemIdOrImmId<Handle>;
    Vec<Select> result;
    for (auto const& it : Stmt_getAttached(handle, "caption")) {
        auto cap = org_cast<sem::CmdCaption>(toHandle(it, handle));
        if constexpr (IsSemOrgInstance<Handle>) {
            result.push_back(toHandle(to_api(cap).text, handle));
        } else {
            result.push_back(toHandle(to_api(cap).getText(), handle));
        }
    }

    return result;
}

template <typename Handle>
Vec<Str> Stmt_getName(Handle handle) {
    Vec<Str> result;
    for (auto const& it : Stmt_getAttached(handle, "name")) {
        auto cap = org_cast<sem::CmdName>(toHandle(it, handle));
        if constexpr (IsSemOrgInstance<Handle>) {
            result.push_back(to_api(cap).name);
        } else {
            result.push_back(to_api(cap)->name);
        }
    }

    return result;
}

template <typename Handle>
Vec<sem::AttrValue> List_getListAttrs(Handle handle, CR<Str> kind) {
    Vec<sem::AttrValue> result;
    auto                attached = Stmt_getAttached(handle, "attr_list");
    for (auto const& it : attached) {
        auto const& attrs = to_api(org_cast<sem::CmdAttr>(it));
        result.append(attrs.getAttrs(kind));
    }

    return result;
}

template <typename Handle>
Vec<sem::NamedProperty> DocumentOptions_getProperties(
    Handle       handle,
    Str const&   kind,
    CR<Opt<Str>> subkind) {
    auto                    h = getConstHandle(handle);
    Vec<sem::NamedProperty> result;
    for (const auto& prop : h->properties) {
        if (prop.isMatching(kind, subkind)) { result.push_back(prop); }
    }
    return result;
}

template <typename Handle>
Opt<sem::NamedProperty> DocumentOptions_getProperty(
    Handle       handle,
    CR<Str>      kind,
    CR<Opt<Str>> subkind) {
    auto h     = getConstHandle(handle);
    auto props = DocumentOptions_getProperties(handle, kind, subkind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        return props[0];
    }
}

template <typename Handle>
Vec<sem::NamedProperty> Document_getProperties(
    Handle       handle,
    CR<Str>      kind,
    CR<Opt<Str>> subkind) {
    auto h = getConstHandle(handle);
    if (h->options.isNil()) {
        return {};
    } else {
        return DocumentOptions_getProperties(
            toHandle(h->options, handle), kind, subkind);
    }
}

template <typename Handle>
Opt<sem::NamedProperty> Document_getProperty(
    Handle       handle,
    CR<Str>      kind,
    CR<Opt<Str>> subkind) {
    auto h = getConstHandle(handle);
    if (h->options.isNil()) {
        return std::nullopt;
    } else {
        return DocumentOptions_getProperty(
            toHandle(h->options, handle), kind, subkind);
    }
}

template <typename Handle>
bool ListItem_isDescriptionItem(Handle handle) {
    return toHandle(getConstHandle(handle)->header, handle).has_value();
}

template <typename Handle>
bool List_isDescriptionList(Handle handle) {
    auto h = getConstHandle(handle);
    for (const auto& sub : getSubnodes(handle, false)) {
        if (is_kind(sub, OrgSemKind::ListItem)) {
            if (ListItem_isDescriptionItem(org_cast<sem::ListItem>(sub))) {
                return true;
            }
        }
    }
    return false;
}

template <typename Handle>
bool List_isNumberedList(Handle handle) {
    auto h = getConstHandle(handle);
    for (const auto& sub : getSubnodes(handle, false)) {
        if (is_kind(sub, OrgSemKind::ListItem)) {
            auto sub_as = org_cast<sem::ListItem>(sub);
            if constexpr (IsSemOrgInstance<Handle>) {
                if (sub_as->bullet.has_value()) { return true; }
            } else {
                if (sub_as->bullet.get().has_value()) { return true; }
            }
        }
    }

    return false;
}


} // namespace

/// \brief Invoke callback `func` on the concrete type of the input
/// adapter. Adapter cannot correctly hold an ID that refers to the
/// abstract base class, so every adapter object must use a concrete type
/// of the node.
template <
    typename CastType,
    typename ThisType,
    typename Func,
    typename... Args>
void CallDynamicOrgMethod(ThisType thisType, Func func, Args&&... args) {
    thisType->visitNodeAdapter(overloaded{
        [&]<typename Kind>(org::ImmAdapterT<Kind> const& cast)
            requires std::derived_from<Kind, CastType>
        {
            auto dyn = cast.template dyn_cast<CastType>();
            LOGIC_ASSERTION_CHECK(
                dyn != nullptr,
                "Statement adapter must hold an ID for the value type "
                "derived from `{}`, but got {}",
                demangle(typeid(CastType).name()),
                *thisType);
            std::invoke(func, cast, std::forward<Args>(args)...);
        },
        [&]<typename Kind>(org::ImmAdapterT<Kind> const& cast) {
            LOGIC_ASSERTION_CHECK(
                false,
                "Statement adapter must hold an ID for the value type "
                "derived from `{}`, but got {}",
                demangle(typeid(CastType).name()),
                *thisType);
        },
    });
}


// clang-format off

Vec<org::ImmAdapter> org::ImmAdapterStmtAPI::getCaption() const {
    Vec<org::ImmAdapter> result;
    CallDynamicOrgMethod<org::ImmStmt>(getThis(), [&](auto const &a1) { result = Stmt_getCaption(a1); });
    return result;
}

Vec<Str> org::ImmAdapterStmtAPI::getName() const {
    Vec<Str> result;
    CallDynamicOrgMethod<org::ImmStmt>(getThis(), [&](auto const &a1) { result = Stmt_getName(a1); });
    return result;
}

Vec<org::ImmAdapter> org::ImmAdapterStmtAPI::getAttached(Opt<Str> const& kind) const {
    Vec<org::ImmAdapter> result;
    CallDynamicOrgMethod<org::ImmStmt>(getThis(), [&](auto const &a1, auto const &a2) { result = Stmt_getAttached(a1, a2); }, kind);
    return result;
}

Str const& org::ImmAdapterLeafAPI::getText() const {
    Str const* result;
    CallDynamicOrgMethod<org::ImmLeaf>(getThis(), [&](auto const &a1) { result = &a1->text.get(); });
    return *result;
}

Opt<sem::AttrValue> org::ImmAdapterStmtAPI::getFirstAttr(Str const& param) const {
  Opt<sem::AttrValue> result;
  CallDynamicOrgMethod<org::ImmStmt>(getThis(), [&](auto const &a1, auto const &a2) { result = Stmt_getFirstAttr(a1, a2); }, param);
  return result;
}

Vec<sem::AttrValue> org::ImmAdapterStmtAPI::getAttrs(CR<Opt<Str>> param) const {
  Vec<sem::AttrValue> result;
  CallDynamicOrgMethod<org::ImmStmt>(getThis(), [&](auto const &a1, auto const &a2) { result = Stmt_getAttrs(a1, a2); }, param);
  return result;
}

Vec<sem::AttrValue> org::ImmAdapterCmdAPI::getAttrs(CR<Opt<Str>> param) const {
  Vec<sem::AttrValue> result;
  CallDynamicOrgMethod<org::ImmCmd>(getThis(), [&](auto const &a1, auto const &a2) { result = Cmd_getAttrs(a1, a2); }, param);
  return result;
}

Opt<sem::AttrValue> org::ImmAdapterCmdAPI::getFirstAttr(Str const& param) const {
  Opt<sem::AttrValue> result;
  CallDynamicOrgMethod<org::ImmCmd>(getThis(), [&](auto const &a1, auto const &a2) { result = Cmd_getFirstAttr(a1, a2); }, param);
  return result;
}

Vec<Vec<Str>> org::ImmAdapterHashTagAPI::getFlatHashes(bool withIntermediate) const { return HashTag_getFlatHashes(getThis()->as<org::ImmHashTag>(), withIntermediate); }

Opt<sem::NamedProperty> org::ImmAdapterSubtreeAPI::getProperty(Str const &kind, CR<Opt<Str>> subkind) const { return subtreeGetPropertyImpl(getThis()->as<org::ImmSubtree>(), kind, subkind); }
Vec<sem::NamedProperty> org::ImmAdapterSubtreeAPI::getProperties(const Str &kind, const Opt<Str> &subkind) const { return subtreeGetPropertiesImpl(getThis()->as<org::ImmSubtree>(), kind, subkind); }
Vec<sem::SubtreePeriod> org::ImmAdapterSubtreeAPI::getTimePeriods(IntSet<sem::SubtreePeriod::Kind> kinds, bool withPath) const { return Subtree_getTimePeriodsImpl(getThis()->as<org::ImmSubtree>(), kinds, withPath); }

Vec<sem::NamedProperty> org::ImmAdapterDocumentOptionsAPI::getProperties(Str const &kind, CR<Opt<Str>> subkind) const { return DocumentOptions_getProperties(getThis()->as<org::ImmDocumentOptions>(), kind, subkind); }
Opt<sem::NamedProperty> org::ImmAdapterDocumentOptionsAPI::getProperty(CR<Str> kind, CR<Opt<Str>> subkind) const { return DocumentOptions_getProperty(getThis()->as<org::ImmDocumentOptions>(), kind, subkind); }
Vec<sem::NamedProperty> org::ImmAdapterDocumentAPI::getProperties(CR<Str> kind, CR<Opt<Str>> subkind) const { return Document_getProperties(getThis()->as<org::ImmDocument>(), kind, subkind); }
Opt<sem::NamedProperty> org::ImmAdapterDocumentAPI::getProperty(CR<Str> kind, CR<Opt<Str>> subkind) const { return Document_getProperty(getThis()->as<org::ImmDocument>(), kind, subkind); }

bool org::ImmAdapterListAPI::isDescriptionList() const { return List_isDescriptionList(getThis()->as<org::ImmList>()); }
bool org::ImmAdapterListAPI::isNumberedList() const { return List_isNumberedList(getThis()->as<org::ImmList>()); }
Vec<sem::AttrValue> org::ImmAdapterListAPI::getListAttrs(CR<Str> param) const { return List_getListAttrs(getThis()->as<org::ImmList>(), param); }
bool org::ImmAdapterListItemAPI::isDescriptionItem() const { return ListItem_isDescriptionItem(getThis()->as<org::ImmListItem>()); }

SemSet LeadParagraphNodes{
    OrgSemKind::HashTag,
    OrgSemKind::BigIdent,
    OrgSemKind::Time,
    OrgSemKind::RadioTarget,
};


bool org::ImmAdapterParagraphAPI::isFootnoteDefinition() const { return getFootnoteName().has_value(); }
bool org::ImmAdapterParagraphAPI::hasAdmonition() const { return !getAdmonitionNodes().empty(); }
Vec<Str> org::ImmAdapterParagraphAPI::getAdmonitions() const { return own_view(getAdmonitionNodes()) | rv::transform([](org::ImmAdapterT<org::ImmBigIdent> const &id) { return id->text.get(); }) | rs::to<Vec>(); }
Vec<org::ImmAdapterT<org::ImmBigIdent>> org::ImmAdapterParagraphAPI::getAdmonitionNodes() const { return mapNodes<org::ImmBigIdent>(Org_getLeadNodes(*getThis(), OrgSemKind::BigIdent, LeadParagraphNodes)); }
bool org::ImmAdapterParagraphAPI::hasTimestamp() const { return !getTimestampNodes().empty(); }
Vec<UserTime> org::ImmAdapterParagraphAPI::getTimestamps() const { return own_view(getTimestampNodes()) | rv::transform([](org::ImmAdapterT<org::ImmTime> const &id) { return id->getStatic().time; }) | rs::to<Vec>(); }
Vec<org::ImmAdapterT<org::ImmTime>> org::ImmAdapterParagraphAPI::getTimestampNodes() const { return mapNodes<org::ImmTime>(Org_getLeadNodes(*getThis(), OrgSemKind::Time, LeadParagraphNodes)); }
bool org::ImmAdapterParagraphAPI::hasLeadHashtags() const { return !getLeadHashtags().empty(); }
Vec<org::ImmAdapterT<org::ImmHashTag>> org::ImmAdapterParagraphAPI::getLeadHashtags() const { return mapNodes<org::ImmHashTag>(Org_getLeadNodes(*getThis(), OrgSemKind::HashTag, LeadParagraphNodes)); }
Vec<org::ImmAdapter> org::ImmAdapterParagraphAPI::getBody(bool withPath) const { return Paragraph_dropAdmonitionNodes(*getThis(), withPath); }

// sem type API implementation

Vec<Vec<Str>> sem::HashTag::getFlatHashes(bool withIntermediate) const { return HashTag_getFlatHashes(this, withIntermediate); }

UserTime sem::Time::getStaticTime() const  { return getStatic().time; }
Opt<int> sem::Time::getYear() const { return getStaticTime().getBreakdown().year; }
Opt<int> sem::Time::getMonth() const { return getStaticTime().getBreakdown().month; }
Opt<int> sem::Time::getDay() const { return getStaticTime().getBreakdown().day; }
Opt<int> sem::Time::getSecond() const { return getStaticTime().getBreakdown().second; }
Opt<int> sem::Time::getHour() const { return getStaticTime().getBreakdown().hour; }
Opt<int> sem::Time::getMinute() const { return getStaticTime().getBreakdown().minute; }

Opt<sem::NamedProperty> sem::Subtree::getProperty(Str const &kind, CR<Opt<Str>> subkind) const { return subtreeGetPropertyImpl(this, kind, subkind); }
Vec<sem::NamedProperty> sem::Subtree::getProperties(Str const &kind, CR<Opt<Str>> subkind) const { return subtreeGetPropertiesImpl(this, kind, subkind); }
Vec<sem::SubtreePeriod> sem::Subtree::getTimePeriods(IntSet<sem::SubtreePeriod::Kind> kinds) const { return Subtree_getTimePeriodsImpl(this, kinds, false); }
Str sem::Attr::getValue() const { return arg.value; }
Str sem::Attr::getName() const { return arg.name.value(); }
Str sem::Attr::getVarname() const { return arg.varname.value(); }

Vec<sem::AttrValue> sem::Stmt::getAttrs(const Opt<Str>& kind) const { return Stmt_getAttrs(this, kind); }
Opt<sem::AttrValue> sem::Stmt::getFirstAttr(const Str& kind) const { return Stmt_getFirstAttr(this, kind); }
Vec<sem::SemId<sem::Org>> sem::Stmt::getAttached(Opt<Str> const& kind) const { return Stmt_getAttached(this, kind); }
Vec<sem::SemId<sem::Org>> sem::Stmt::getCaption() const { return Stmt_getCaption(this); }
Vec<Str> sem::Stmt::getName() const { return Stmt_getName(this); }

Opt<sem::AttrValue> sem::Cmd::getFirstAttr(CR<Str> kind) const { return Cmd_getFirstAttr(this, kind); }
Vec<sem::AttrValue> sem::Attrs::getAttrs(CR<Opt<Str>> param) const { return Attrs_getAttrs(this, param); }
Vec<sem::AttrValue> sem::Cmd::getAttrs(CR<Opt<Str>> param) const { return Cmd_getAttrs(this, param); }


Vec<sem::NamedProperty> sem::DocumentOptions::getProperties(Str const &kind, CR<Opt<Str>> subkind) const { return DocumentOptions_getProperties(this, kind, subkind); }
Opt<sem::NamedProperty> sem::DocumentOptions::getProperty(CR<Str> kind, CR<Opt<Str>> subkind) const { return DocumentOptions_getProperty(this, kind, subkind); }
Vec<sem::NamedProperty> sem::Document::getProperties(CR<Str> kind, CR<Opt<Str>> subkind) const { return Document_getProperties(this, kind, subkind); }
Opt<sem::NamedProperty> sem::Document::getProperty(CR<Str> kind, CR<Opt<Str>> subkind) const { return Document_getProperty(this, kind, subkind); }

bool sem::List::isDescriptionList() const { return List_isDescriptionList(this); }
bool sem::List::isNumberedList() const { return List_isNumberedList(this); }
Vec<sem::AttrValue> sem::List::getListAttrs(CR<Str> param) const { return List_getListAttrs(this, param); }
bool sem::ListItem::isDescriptionItem() const { return ListItem_isDescriptionItem(this); }

bool sem::Paragraph::isFootnoteDefinition() const { return getFootnoteName().has_value(); }
bool sem::Paragraph::hasAdmonition() const { return !getAdmonitionNodes().empty(); }
Vec<Str> sem::Paragraph::getAdmonitions() const { return own_view(getAdmonitionNodes()) | rv::transform([](sem::SemId<sem::BigIdent> const &id) { return id->text; }) | rs::to<Vec>(); }
Vec<sem::SemId<sem::BigIdent>> sem::Paragraph::getAdmonitionNodes() const { return mapNodes<sem::BigIdent>(Org_getLeadNodes(this, OrgSemKind::BigIdent, LeadParagraphNodes)); }
bool sem::Paragraph::hasTimestamp() const { return !getTimestampNodes().empty(); }
Vec<UserTime> sem::Paragraph::getTimestamps() const { return own_view(getTimestampNodes()) | rv::transform([](sem::SemId<sem::Time> const &id) { return id->getStatic().time; }) | rs::to<Vec>(); }
Vec<sem::SemId<sem::Time>> sem::Paragraph::getTimestampNodes() const { return mapNodes<sem::Time>(Org_getLeadNodes(this, OrgSemKind::Time, LeadParagraphNodes)); }
bool sem::Paragraph::hasLeadHashtags() const { return !getLeadHashtags().empty(); }
Vec<sem::SemId<sem::HashTag>> sem::Paragraph::getLeadHashtags() const { return mapNodes<sem::HashTag>(Org_getLeadNodes(this, OrgSemKind::HashTag, LeadParagraphNodes)); }
Vec<sem::SemId<sem::Org>> sem::Paragraph::getBody() const { return Paragraph_dropAdmonitionNodes(this, false); }


// Opt<org::ImmAdapterT<org::ImmAttrList>> org::ImmAdapterT<org::ImmCell>::getAttrs(CR<Opt<Str>> param) const { return cmdgetAttrsImpl(*this, param); }


// clang-format on

org::ImmAdapterT<org::ImmParagraph> org::ImmAdapterSubtreeAPI::getTitle()
    const {
    return pass(
        getThisT<org::ImmSubtree>()->title,
        ImmPathStep::Field(
            org::ImmReflFieldId::FromTypeField(&org::ImmSubtree::title)));
}
org::ImmAdapterT<org::ImmParagraph> org::ImmAdapterCmdCaptionAPI::getText()
    const {
    return pass(
        getThisT<org::ImmCmdCaption>()->text,
        ImmPathStep::Field(org::ImmReflFieldId::FromTypeField(
            &org::ImmCmdCaption::text)));
}


Opt<org::ImmAdapter> org::ImmAdapterListItemAPI::getHeader() const {
    auto it = getThisT<org::ImmListItem>();
    if (isBoolFalse(it->header)) {
        return std::nullopt;
    } else {
        return pass(
            it->header->value(),
            ImmPathStep::FieldDeref(org::ImmReflFieldId::FromTypeField(
                &org::ImmListItem::header)));
    }
}

Opt<Str> sem::Paragraph::getFootnoteName() const {
    if (!subnodes.has(0)) { return std::nullopt; }
    if (auto link = at(0).asOpt<sem::Link>();
        link && link->target.isFootnote()) {
        return link->target.getFootnote().target;
    } else {
        return std::nullopt;
    }
}

Opt<Str> org::ImmAdapterParagraphAPI::getFootnoteName() const {
    if (getThis()->get()->subnodes.empty()) { return std::nullopt; }
    if (auto link = getThis()->at(0, false).asOpt<org::ImmLink>();
        link && link.value()->target.isFootnote()) {
        return link.value()->target.getFootnote().target;
    } else {
        return std::nullopt;
    }
}
