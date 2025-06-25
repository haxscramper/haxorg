/// \file Implementation of methods shared for both sem AST and immutable
/// AST

#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <hstd/stdlib/strutils.hpp>

using namespace org;
using namespace hstd;

template <class E>
Opt<E> string_to_enum_insensitive(std::string const& name) {
    bool   found = false;
    Opt<E> r     = {};

    boost::mp11::mp_for_each<boost::describe::describe_enumerators<E>>(
        [&](auto D) {
            if (!r && hstd::iequals(D.name, name)) { r = D.value; }
        });

    return r;
}

namespace {
template <sem::IsOrg T>
T* getMutHandle(T* ptr) {
    return ptr;
}

template <sem::IsOrg T>
T* getMutHandle(sem::SemId<sem::Org> ptr) {
    return ptr.get();
}


template <imm::IsImmOrgValueType T>
T* getMutHandle(imm::ImmAdapterT<T> ptr) {
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


template <imm::IsImmOrgValueType T>
T const* getConstHandle(imm::ImmAdapterT<T> ptr) {
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
Vec<imm::ImmAdapter> getSubnodes(imm::ImmAdapter const& t, bool withPath) { return t.sub(withPath); }
template <typename T>
Vec<imm::ImmAdapter> getSubnodes(imm::ImmAdapterT<T> const& t, bool withPath) { return t.sub(withPath); }
template <sem::IsOrg T>
Vec<sem::SemId<sem::Org>> getSubnodes(sem::SemId<T> const& t, bool withPath) { return t->subnodes; }
template <sem::IsOrg T>
Vec<sem::SemId<sem::Org>> getSubnodes(T const* t, bool withPath) { return t->subnodes; }
// clang-format on

bool is_kind(imm::ImmAdapter const& ad, OrgSemKind kind) {
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
template <sem::IsOrg Out, imm::IsImmOrgValueType In>
imm::ImmAdapterT<typename imm::sem_to_imm_map<Out>::imm_type> org_cast(
    imm::ImmAdapterT<In> arg) {
    return arg.template as<typename imm::sem_to_imm_map<Out>::imm_type>();
}

template <sem::IsOrg Out>
imm::ImmAdapterT<typename imm::sem_to_imm_map<Out>::imm_type> org_cast(
    imm::ImmAdapter arg) {
    return arg.template as<typename imm::sem_to_imm_map<Out>::imm_type>();
}

/// brief Helper function to check if value is 'empty' -- used to
/// streamline `Box<Opt<Imm>>` vs `Opt<Sem>` type handling.
template <typename T>
bool isBoolFalse(T const& t) {
    return value_metadata<T>::isEmpty(t);
}

/// \brief Convert immer ID to the imm adapter.
template <imm::IsImmOrgValueType T, typename Handle>
imm::ImmAdapterT<T> toHandle(imm::ImmIdT<T> id, Handle const& handle) {
    return imm::ImmAdapterT<T>{id, handle.ctx, {}};
}

/// \brief Convert sem ID to the sem ID -- identity function.
template <sem::IsOrg T, typename Handle>
sem::SemId<T> toHandle(sem::SemId<T> id, Handle const& handle) {
    return id;
}

/// \brief Convert optional imm ID to optional adapter
template <imm::IsImmOrgValueType T, typename Handle>
Opt<imm::ImmAdapterT<T>> toHandle(
    Opt<imm::ImmIdT<T>> id,
    Handle const&       handle) {
    if (id) {
        return toHandle(id.value(), handle);
    } else {
        return std::nullopt;
    }
}

template <imm::IsImmOrgValueType T, typename Handle>
imm::ImmAdapterT<T> toHandle(
    imm::ImmAdapterT<T> id,
    Handle const&       handle) {
    return id;
}

template <typename Handle>
imm::ImmAdapter toHandle(imm::ImmAdapter id, Handle const& handle) {
    return id;
}

/// \brief Convert boxed optional imm ID to optional adapter
template <imm::IsImmOrgValueType T, typename Handle>
Opt<imm::ImmAdapterT<T>> toHandle(
    hstd::ext::ImmBox<Opt<imm::ImmIdT<T>>> id,
    Handle const&                          handle) {
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

template <imm::IsImmOrgValueType T>
imm::ImmAdapterT<T> to_api(imm::ImmAdapterT<T> it) {
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

template <imm::IsImmOrgValueType T>
T const& to_value(imm::ImmAdapterT<T> it) {
    return *it.template dyn_cast<T>();
}

/// \brief Unwrap type `T` and get underlying sem/imm type, define nested
/// `ast_type` for result.
template <typename T>
struct get_ast_type {};

template <typename T>
struct get_ast_type<imm::ImmAdapterT<T>> {
    using ast_type = T;
};

template <>
struct get_ast_type<imm::ImmAdapter> {
    using ast_type = imm::ImmOrg;
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
    requires sem::IsOrg<T> || imm::IsImmOrgValueType<T>
struct SemOrImmType {};

/// \brief Org type selector specialization to select sem type
template <sem::IsOrg T, typename SemType, typename ImmType>
struct SemOrImmType<T, SemType, ImmType> {
    using result = SemType;
};

/// \brief Org type selector specialization to select immer type
template <imm::IsImmOrgValueType T, typename SemType, typename ImmType>
struct SemOrImmType<T, SemType, ImmType> {
    using result = ImmType;
};

template <typename T>
using SemIdOrImmId = SemOrImmType<
    typename get_ast_type<T>::ast_type,
    sem::SemId<sem::Org>,
    imm::ImmAdapter>::result;

template <typename Handle>
concept IsSemOrgInstance = sem::IsOrg<
    typename get_ast_type<Handle>::ast_type>;

template <typename Handle>
concept IsImmOrgInstance = imm::IsImmOrgValueType<
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
            // adapter, the final cast would be to `imm::ImmTime`,
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
        if constexpr (IsSemOrgInstance<Handle>) {
            period.from = h->deadline.value()->getStaticTime();
        } else {
            period.from = toHandle(h->deadline.get().value(), handle)
                              .getStaticTime();
        }

        period.kind = SubtreePeriod::Kind::Deadline;
        res.push_back(period);
    }

    if (kinds.contains(SubtreePeriod::Kind::Scheduled)
        && !isBoolFalse(h->scheduled)) {
        SubtreePeriod period{};
        if constexpr (IsSemOrgInstance<Handle>) {
            period.from = h->scheduled.value()->getStaticTime();
        } else {
            period.from = toHandle(h->scheduled.get().value(), handle)
                              .getStaticTime();
        }

        period.kind = SubtreePeriod::Kind::Scheduled;
        res.push_back(period);
    }

    if (kinds.contains(SubtreePeriod::Kind::Closed)
        && !isBoolFalse(h->closed)) {
        SubtreePeriod period{};
        if constexpr (IsSemOrgInstance<Handle>) {
            period.from = h->closed.value()->getStaticTime();
        } else {
            period.from = toHandle(h->closed.get().value(), handle)
                              .getStaticTime();
        }

        period.kind = SubtreePeriod::Kind::Closed;
        res.push_back(period);
    }

    if (kinds.contains(SubtreePeriod::Kind::Clocked)) {
        // Subtree log is an AST type which has nested enum definitions,
        // which are identical in structure, but from the compiler
        // perspective `imm::ImmSubtreeLog::Kind` and
        // `sem::SubtreeLog::Kind` are two different classes. That's why I
        // need to use the type selector here and define the target log
        // type.
        using LogType = SemOrImmType<
            HandleBase,
            sem::SubtreeLog,
            imm::ImmSubtreeLog>::result;

        for (auto const& logIt : h->logbook) {
            auto const log = toHandle(logIt, handle);
            if (log->head.isClock()) {
                SubtreePeriod period{};
                period.from = log->head.getClock().from;
                if (!isBoolFalse(log->head.getClock().to)) {
                    period.to = log->head.getClock().to;
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

Vec<sem::AttrValue> Attrs_getAttrs(
    sem::AttrGroup const& attrs,
    CR<Opt<Str>>          param) {
    return attrs.getAttrs(param);
}

Vec<sem::AttrValue> Attrs_getAttrs(
    Opt<sem::AttrGroup> const& attrs,
    CR<Opt<Str>>               param) {
    if (attrs) {
        return Attrs_getAttrs(attrs.value(), param);
    } else {
        return {};
    }
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
                    org_cast<sem::CmdAttr>(toHandle(sub, handle))->attrs,
                    kind));
        }
    }

    return result;
}

template <typename Handle>
Opt<Str> Org_getString(Handle const& id) {
    if (id->getKind() == OrgSemKind::Time) {
        return "["_ss
             + Str{to_api(toHandle(org_cast<sem::Time>(id), id))
                       .getStaticTime()
                       .format(UserTime::Format::OrgFormat)}
             + "]"_ss;
    } else if (
        auto w = id->template dyn_cast<typename SemOrImmType<
                     typename get_ast_type<Handle>::ast_type,
                     sem::Leaf,
                     imm::ImmLeaf>::result>()) {
        return w->text;
    } else {
        return std::nullopt;
    }
}

Vec<imm::ImmAdapter> Org_getLeadNodes(
    imm::ImmAdapter const& it,
    OrgSemKind             kind,
    SemSet const&          skip) {
    Vec<imm::ImmAdapter> result;
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
                    isFootnote = sub.template as<imm::ImmLink>()
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
Vec<imm::ImmAdapterT<T>> mapNodes(Vec<imm::ImmAdapter> const& nodes) {
    return nodes | rv::transform([](imm::ImmAdapter const& id) {
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
    if (!isBoolFalse(h->attrs)) { res = Attrs_getAttrs(h->attrs, param); }
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
        auto res = Attrs_getAttrs(h->attrs, kind);
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
        imm::ImmAdapter>;

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
        [&]<typename Kind>(imm::ImmAdapterT<Kind> const& cast)
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
        [&]<typename Kind>(imm::ImmAdapterT<Kind> const& cast) {
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

Vec<imm::ImmAdapter> imm::ImmAdapterStmtAPI::getCaption() const {
    Vec<imm::ImmAdapter> result;
    CallDynamicOrgMethod<imm::ImmStmt>(getThis(), [&](auto const &a1) { result = Stmt_getCaption(a1); });
    return result;
}

Vec<Str> imm::ImmAdapterStmtAPI::getName() const {
    Vec<Str> result;
    CallDynamicOrgMethod<imm::ImmStmt>(getThis(), [&](auto const &a1) { result = Stmt_getName(a1); });
    return result;
}

Vec<imm::ImmAdapter> imm::ImmAdapterStmtAPI::getAttached(Opt<Str> const& kind) const {
    Vec<imm::ImmAdapter> result;
    CallDynamicOrgMethod<imm::ImmStmt>(getThis(), [&](auto const &a1, auto const &a2) { result = Stmt_getAttached(a1, a2); }, kind);
    return result;
}

Str const& imm::ImmAdapterLeafAPI::getText() const {
    Str const* result;
    CallDynamicOrgMethod<imm::ImmLeaf>(getThis(), [&](auto const &a1) { result = &a1->text.get(); });
    return *result;
}

Opt<sem::AttrValue> imm::ImmAdapterStmtAPI::getFirstAttr(Str const& param) const {
  Opt<sem::AttrValue> result;
  CallDynamicOrgMethod<imm::ImmStmt>(getThis(), [&](auto const &a1, auto const &a2) { result = Stmt_getFirstAttr(a1, a2); }, param);
  return result;
}

Vec<sem::AttrValue> imm::ImmAdapterStmtAPI::getAttrs(CR<Opt<Str>> param) const {
  Vec<sem::AttrValue> result;
  CallDynamicOrgMethod<imm::ImmStmt>(getThis(), [&](auto const &a1, auto const &a2) { result = Stmt_getAttrs(a1, a2); }, param);
  return result;
}

Vec<sem::AttrValue> imm::ImmAdapterCmdAPI::getAttrs(CR<Opt<Str>> param) const {
  Vec<sem::AttrValue> result;
  CallDynamicOrgMethod<imm::ImmCmd>(getThis(), [&](auto const &a1, auto const &a2) { result = Cmd_getAttrs(a1, a2); }, param);
  return result;
}

Opt<sem::AttrValue> imm::ImmAdapterCmdAPI::getFirstAttr(Str const& param) const {
  Opt<sem::AttrValue> result;
  CallDynamicOrgMethod<imm::ImmCmd>(getThis(), [&](auto const &a1, auto const &a2) { result = Cmd_getFirstAttr(a1, a2); }, param);
  return result;
}



UserTime imm::ImmAdapterTimeAPI::getStaticTime() const  { return getThis()->as<imm::ImmTime>()->getStatic().time; }
Opt<int> imm::ImmAdapterTimeAPI::getYear() const { return getStaticTime().getBreakdown().year; }
Opt<int> imm::ImmAdapterTimeAPI::getMonth() const { return getStaticTime().getBreakdown().month; }
Opt<int> imm::ImmAdapterTimeAPI::getDay() const { return getStaticTime().getBreakdown().day; }
Opt<int> imm::ImmAdapterTimeAPI::getSecond() const { return getStaticTime().getBreakdown().second; }
Opt<int> imm::ImmAdapterTimeAPI::getHour() const { return getStaticTime().getBreakdown().hour; }
Opt<int> imm::ImmAdapterTimeAPI::getMinute() const { return getStaticTime().getBreakdown().minute; }

Str imm::ImmAdapterSubtreeAPI::getCleanTitle() const { return org::getCleanText(getThis()->as<imm::ImmSubtree>().getTitle()); }
Opt<sem::NamedProperty> imm::ImmAdapterSubtreeAPI::getProperty(Str const &kind, CR<Opt<Str>> subkind) const { return subtreeGetPropertyImpl(getThis()->as<imm::ImmSubtree>(), kind, subkind); }
Vec<sem::NamedProperty> imm::ImmAdapterSubtreeAPI::getProperties(const Str &kind, const Opt<Str> &subkind) const { return subtreeGetPropertiesImpl(getThis()->as<imm::ImmSubtree>(), kind, subkind); }
Vec<sem::SubtreePeriod> imm::ImmAdapterSubtreeAPI::getTimePeriods(IntSet<sem::SubtreePeriod::Kind> kinds, bool withPath) const { return Subtree_getTimePeriodsImpl(getThis()->as<imm::ImmSubtree>(), kinds, withPath); }

Vec<sem::NamedProperty> imm::ImmAdapterDocumentOptionsAPI::getProperties(Str const &kind, CR<Opt<Str>> subkind) const { return DocumentOptions_getProperties(getThis()->as<imm::ImmDocumentOptions>(), kind, subkind); }
Opt<sem::NamedProperty> imm::ImmAdapterDocumentOptionsAPI::getProperty(CR<Str> kind, CR<Opt<Str>> subkind) const { return DocumentOptions_getProperty(getThis()->as<imm::ImmDocumentOptions>(), kind, subkind); }
Vec<sem::NamedProperty> imm::ImmAdapterDocumentAPI::getProperties(CR<Str> kind, CR<Opt<Str>> subkind) const { return Document_getProperties(getThis()->as<imm::ImmDocument>(), kind, subkind); }
Opt<sem::NamedProperty> imm::ImmAdapterDocumentAPI::getProperty(CR<Str> kind, CR<Opt<Str>> subkind) const { return Document_getProperty(getThis()->as<imm::ImmDocument>(), kind, subkind); }

bool imm::ImmAdapterListAPI::isDescriptionList() const { return List_isDescriptionList(getThis()->as<imm::ImmList>()); }
bool imm::ImmAdapterListAPI::isNumberedList() const { return List_isNumberedList(getThis()->as<imm::ImmList>()); }
Vec<sem::AttrValue> imm::ImmAdapterListAPI::getListAttrs(CR<Str> param) const { return List_getListAttrs(getThis()->as<imm::ImmList>(), param); }

bool imm::ImmAdapterListItemAPI::isDescriptionItem() const { return ListItem_isDescriptionItem(getThis()->as<imm::ImmListItem>()); }
Opt<Str> imm::ImmAdapterListItemAPI::getCleanHeader() const { return isDescriptionItem() ? std::make_optional(org::getCleanText(getHeader().value())) : std::nullopt; }

SemSet LeadParagraphNodes{
    OrgSemKind::HashTag,
    OrgSemKind::BigIdent,
    OrgSemKind::Time,
    OrgSemKind::RadioTarget,
};


bool imm::ImmAdapterParagraphAPI::isFootnoteDefinition() const { return getFootnoteName().has_value(); }
bool imm::ImmAdapterParagraphAPI::hasAdmonition() const { return !getAdmonitionNodes().empty(); }
Vec<Str> imm::ImmAdapterParagraphAPI::getAdmonitions() const { return own_view(getAdmonitionNodes()) | rv::transform([](imm::ImmAdapterT<imm::ImmBigIdent> const &id) { return id->text.get(); }) | rs::to<Vec>(); }
Vec<imm::ImmAdapterT<imm::ImmBigIdent>> imm::ImmAdapterParagraphAPI::getAdmonitionNodes() const { return mapNodes<imm::ImmBigIdent>(Org_getLeadNodes(*getThis(), OrgSemKind::BigIdent, LeadParagraphNodes)); }
bool imm::ImmAdapterParagraphAPI::hasTimestamp() const { return !getTimestampNodes().empty(); }
Vec<UserTime> imm::ImmAdapterParagraphAPI::getTimestamps() const { return own_view(getTimestampNodes()) | rv::transform([](imm::ImmAdapterT<imm::ImmTime> const &id) { return id->getStatic().time; }) | rs::to<Vec>(); }
Vec<imm::ImmAdapterT<imm::ImmTime>> imm::ImmAdapterParagraphAPI::getTimestampNodes() const { return mapNodes<imm::ImmTime>(Org_getLeadNodes(*getThis(), OrgSemKind::Time, LeadParagraphNodes)); }
bool imm::ImmAdapterParagraphAPI::hasLeadHashtags() const { return !getLeadHashtags().empty(); }
Vec<imm::ImmAdapterT<imm::ImmHashTag>> imm::ImmAdapterParagraphAPI::getLeadHashtags() const { return mapNodes<imm::ImmHashTag>(Org_getLeadNodes(*getThis(), OrgSemKind::HashTag, LeadParagraphNodes)); }
Vec<imm::ImmAdapter> imm::ImmAdapterParagraphAPI::getBody(bool withPath) const { return Paragraph_dropAdmonitionNodes(*getThis(), withPath); }

// sem type API implementation

UserTime sem::Time::getStaticTime() const  { return getStatic().time; }
Opt<int> sem::Time::getYear() const { return getStaticTime().getBreakdown().year; }
Opt<int> sem::Time::getMonth() const { return getStaticTime().getBreakdown().month; }
Opt<int> sem::Time::getDay() const { return getStaticTime().getBreakdown().day; }
Opt<int> sem::Time::getSecond() const { return getStaticTime().getBreakdown().second; }
Opt<int> sem::Time::getHour() const { return getStaticTime().getBreakdown().hour; }
Opt<int> sem::Time::getMinute() const { return getStaticTime().getBreakdown().minute; }

Str sem::Subtree::getCleanTitle() const { return org::getCleanText(title.asOrg()); }
Opt<sem::NamedProperty> sem::Subtree::getProperty(Str const &kind, CR<Opt<Str>> subkind) const { return subtreeGetPropertyImpl(this, kind, subkind); }
Vec<sem::NamedProperty> sem::Subtree::getProperties(Str const &kind, CR<Opt<Str>> subkind) const { return subtreeGetPropertiesImpl(this, kind, subkind); }
Vec<sem::SubtreePeriod> sem::Subtree::getTimePeriods(IntSet<sem::SubtreePeriod::Kind> kinds) const { return Subtree_getTimePeriodsImpl(this, kinds, false); }


Vec<sem::AttrValue> sem::Stmt::getAttrs(const Opt<Str>& kind) const { return Stmt_getAttrs(this, kind); }
Opt<sem::AttrValue> sem::Stmt::getFirstAttr(const Str& kind) const { return Stmt_getFirstAttr(this, kind); }
Vec<sem::SemId<sem::Org>> sem::Stmt::getAttached(Opt<Str> const& kind) const { return Stmt_getAttached(this, kind); }
Vec<sem::SemId<sem::Org>> sem::Stmt::getCaption() const { return Stmt_getCaption(this); }
Vec<Str> sem::Stmt::getName() const { return Stmt_getName(this); }

Opt<sem::AttrValue> sem::Cmd::getFirstAttr(CR<Str> kind) const { return Cmd_getFirstAttr(this, kind); }
Vec<sem::AttrValue> sem::Cmd::getAttrs(CR<Opt<Str>> param) const { return Cmd_getAttrs(this, param); }


Vec<sem::NamedProperty> sem::DocumentOptions::getProperties(Str const &kind, CR<Opt<Str>> subkind) const { return DocumentOptions_getProperties(this, kind, subkind); }
Opt<sem::NamedProperty> sem::DocumentOptions::getProperty(CR<Str> kind, CR<Opt<Str>> subkind) const { return DocumentOptions_getProperty(this, kind, subkind); }
Vec<sem::NamedProperty> sem::Document::getProperties(CR<Str> kind, CR<Opt<Str>> subkind) const { return Document_getProperties(this, kind, subkind); }
Opt<sem::NamedProperty> sem::Document::getProperty(CR<Str> kind, CR<Opt<Str>> subkind) const { return Document_getProperty(this, kind, subkind); }

bool sem::List::isDescriptionList() const { return List_isDescriptionList(this); }
bool sem::List::isNumberedList() const { return List_isNumberedList(this); }
Vec<sem::AttrValue> sem::List::getListAttrs(CR<Str> param) const { return List_getListAttrs(this, param); }
bool sem::ListItem::isDescriptionItem() const { return ListItem_isDescriptionItem(this); }
Opt<Str> sem::ListItem::getCleanHeader() const { return isDescriptionItem() ? std::make_optional(org::getCleanText(header.value().asOrg())) : std::nullopt; }

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


// Opt<imm::ImmAdapterT<imm::ImmAttrList>> imm::ImmAdapterT<imm::ImmCell>::getAttrs(CR<Opt<Str>> param) const { return cmdgetAttrsImpl(*this, param); }


// clang-format on

ListFormattingMode sem::List::getListFormattingMode() const {
    auto formatting = getFirstAttr("list-format");
    if (formatting.has_value()) {
        auto mode = string_to_enum_insensitive<ListFormattingMode>(
            formatting.value().getString());
        return mode.value_or(ListFormattingMode::None);
    } else {
        return ListFormattingMode::None;
    }
}

imm::ImmAdapterT<imm::ImmParagraph> imm::ImmAdapterSubtreeAPI::getTitle()
    const {
    return pass(
        getThisT<imm::ImmSubtree>()->title,
        ImmPathStep::Field(
            imm::ImmReflFieldId::FromTypeField(&imm::ImmSubtree::title)));
}
imm::ImmAdapterT<imm::ImmParagraph> imm::ImmAdapterCmdCaptionAPI::getText()
    const {
    return pass(
        getThisT<imm::ImmCmdCaption>()->text,
        ImmPathStep::Field(imm::ImmReflFieldId::FromTypeField(
            &imm::ImmCmdCaption::text)));
}


Opt<imm::ImmAdapter> imm::ImmAdapterListItemAPI::getHeader() const {
    auto it = getThisT<imm::ImmListItem>();
    if (isBoolFalse(it->header)) {
        return std::nullopt;
    } else {
        return pass(
            it->header->value(),
            ImmPathStep::FieldDeref(imm::ImmReflFieldId::FromTypeField(
                &imm::ImmListItem::header)));
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

Opt<Str> imm::ImmAdapterParagraphAPI::getFootnoteName() const {
    if (getThis()->get()->subnodes.empty()) { return std::nullopt; }
    if (auto link = getThis()->at(0, false).asOpt<imm::ImmLink>();
        link && link.value()->target.isFootnote()) {
        return link.value()->target.getFootnote().target;
    } else {
        return std::nullopt;
    }
}

Opt<sem::NamedProperty> Org_combinePropertyStack(
    Vec<sem::NamedProperty> const& stack,
    CR<Str>                        kind,
    CR<Opt<Str>>                   subKind) {
    if (stack.empty()) {
        return std::nullopt;
    } else if (stack.size() == 1) {
        return stack.at(0);
    } else {
        sem::NamedProperty res = stack.at(0);
        using NP               = sem::NamedProperty;
        using K                = NP::Kind;

        for (auto const& prop : stack.at(slice(1, 1_B))) {
            LOGIC_ASSERTION_CHECK(
                res.getKind() == prop.getKind(),
                "Property combine expects items of the same kind, "
                "but got properties with two different kinds {} "
                "!= {}",
                res.getKind(),
                prop.getKind());
            switch (prop.getKind()) {
                case K::CustomArgs: {
                    auto&       res_args = res.getCustomArgs();
                    auto const& in_args  = prop.getCustomArgs();
                    LOGIC_ASSERTION_CHECK(
                        res_args.name == in_args.name,
                        "expected identical property name for custom args "
                        "property, {} != {}",
                        res_args.name,
                        in_args.name);


                    if (!in_args.attrs.positional.items.empty()) {
                        res_args.attrs.setPositionalAttr(
                            in_args.attrs.positional.items);
                    }

                    for (auto const& [key, items] : in_args.attrs.named) {
                        res_args.attrs.setNamedAttr(key, items.items);
                    }

                    break;
                }
                default: {
                    res = prop;
                    break;
                }
            }
        }

        return res;
    }
}

Opt<sem::NamedProperty> getPropertyValue(
    sem::SemId<sem::Org> const& org,
    CR<Str>                     kind,
    CR<Opt<Str>>                sub) {
    if (auto tree = org.asOpt<sem::Subtree>()) {
        return tree->getProperty(kind, sub);
    } else if (auto doc = org.asOpt<sem::Document>()) {
        return doc->getProperty(kind, sub);
    } else {
        return std::nullopt;
    }
}

Opt<sem::NamedProperty> getPropertyValue(
    imm::ImmAdapter const& org,
    CR<Str>                kind,
    CR<Opt<Str>>           sub) {
    if (auto tree = org.asOpt<imm::ImmSubtree>()) {
        return tree->getProperty(kind, sub);
    } else if (auto doc = org.asOpt<imm::ImmDocument>()) {
        return doc->getProperty(kind, sub);
    } else {
        return std::nullopt;
    }
}

template <typename Handle>
Opt<sem::NamedProperty> Org_getFinalProperty(
    Vec<Handle> const& handles,
    CR<Str>            kind,
    CR<Opt<Str>>       subKind) {
    Vec<sem::NamedProperty> propertyStack;

    for (auto const& handle : handles) {
        auto prop = getPropertyValue(handle, kind, subKind);
        if (prop.has_value()) { propertyStack.push_back(prop.value()); }
    }

    return Org_combinePropertyStack(propertyStack, kind, subKind);
}

Opt<sem::NamedProperty> org::getFinalProperty(
    CR<Vec<imm::ImmAdapter>> nodes,
    CR<Str>                  kind,
    CR<Opt<Str>>             subKind) {
    return Org_getFinalProperty(nodes, kind, subKind);
}

Opt<sem::NamedProperty> org::getFinalProperty(
    CR<Vec<sem::SemId<sem::Org>>> nodes,
    CR<Str>                       kind,
    CR<Opt<Str>>                  subKind) {
    return Org_getFinalProperty(nodes, kind, subKind);
}

Vec<Str> org::getDfsLeafText(
    sem::SemId<sem::Org> id,
    const SemSet&        filter) {
    return getDfsFuncEval<Str>(
        id, [&](sem::SemId<sem::Org> const& id) -> Opt<Str> {
            if (!filter.contains(id->getKind())) {
                return std::nullopt;
            } else {
                return Org_getString(id);
            }
        });
}

Vec<Str> org::getDfsLeafText(
    const imm::ImmAdapter& id,
    const SemSet&          filter) {
    return getDfsFuncEval<Str>(
        id, false, [&](imm::ImmAdapter const& id) -> Opt<Str> {
            if (!filter.contains(id->getKind())) {
                return std::nullopt;
            } else {
                return Org_getString(id);
            }
        });
}

Str org::getCleanText(sem::SemId<sem::Org> const& id) {
    return join(
        "",
        org::getDfsFuncEval<Str>(
            id, [](sem::SemId<sem::Org> const& id) -> Opt<Str> {
                if (auto space = id.asOpt<sem::Space>()) {
                    return " ";
                } else {
                    return Org_getString(id);
                }
            }));
}

Str org::getCleanText(imm::ImmAdapter const& id) {
    return join(
        "",
        org::getDfsFuncEval<Str>(
            id, false, [](imm::ImmAdapter const& a) -> Opt<Str> {
                if (auto space = a.dyn_cast<imm::ImmSpace>()) {
                    return " ";
                } else {
                    return Org_getString(a);
                }
            }));
}

Opt<Str> imm::ImmAdapterBlockExportAPI::getPlacement() const {
    auto p = getThis()->as<imm::ImmBlockExport>().getFirstAttr(
        "placement");
    if (p) {
        return p.value().getString();
    } else {
        return std::nullopt;
    }
}

Opt<Str> sem::BlockExport::getPlacement() const {
    if (auto p = getFirstAttr("placement")) {
        return p.value().getString();
    } else {
        return std::nullopt;
    }
}

Opt<sem::AttrValue> sem::BlockCode::getVariable(Str const& var) const {
    for (auto const& attr : getAttrs("var")) {
        if (attr.varname == var) { return attr; }
    }

    return std::nullopt;
}


hstd::Opt<org::imm::ImmAdapter> org::imm::ImmAdapterDirectoryAPI::
    getFsSubnode(const hstd::Str& name, bool withPath) const {

    auto test = [&](hstd::Str const& path) -> bool {
        return fs::path{path.toBase()}.filename().native() == name;
    };

    for (auto const& sub : getThis()->sub(withPath)) {
        if (auto const& dir = sub.asOpt<imm::ImmDirectory>();
            dir.has_value() && test(dir.value()->relPath)) {
            return sub;
        } else if (auto const& d = sub.asOpt<imm::ImmFile>();
                   d.has_value() && test(d.value()->relPath)) {
            return sub;
        }
    }

    return std::nullopt;
}
