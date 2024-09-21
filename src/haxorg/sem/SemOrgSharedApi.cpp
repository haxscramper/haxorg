/// \file Implementation of methods shared for both sem AST and immutable
/// AST

#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/SemOrg.hpp>

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
Vec<org::ImmAdapter> getSubnodes(org::ImmAdapter const& t) { return t.sub(); }
template <typename T>
Vec<org::ImmAdapter> getSubnodes(org::ImmAdapterT<T> const& t) { return t.sub(); }
template <sem::IsOrg T>
Vec<sem::SemId<sem::Org>> getSubnodes(sem::SemId<T> const& t) { return t->subnodes; }
template <sem::IsOrg T>
Vec<sem::SemId<sem::Org>> getSubnodes(T const* t) { return t->subnodes; }
// clang-format on

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

/// \brief Unwrap type `T` and get underlying sem/imm type, define nested
/// `ast_type` for result.
template <typename T>
struct get_ast_type {};

template <typename T>
struct get_ast_type<org::ImmAdapterT<T>> {
    using ast_type = T;
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

/// \brief Generic implementation of the subtree period collection --
/// subtree period type is a shared data type, so in this function only
/// parametrizing on the handle parameter.
template <typename Handle>
Vec<sem::SubtreePeriod> subtreeGetTimePeriodsImpl(
    Handle                           handle,
    IntSet<sem::SubtreePeriod::Kind> kinds) {
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

    for (const auto& it : getSubnodes(toHandle(h->title, handle))) {
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
        && isBoolFalse(h->deadline)) {
        SubtreePeriod period{};
        period.from = toHandle(h->deadline, handle)
                          .value()
                          ->getStatic()
                          .time;
        period.kind = SubtreePeriod::Kind::Deadline;
        res.push_back(period);
    }

    if (kinds.contains(SubtreePeriod::Kind::Scheduled)
        && isBoolFalse(h->scheduled)) {
        SubtreePeriod period{};
        period.from = toHandle(h->scheduled, handle)
                          .value()
                          ->getStatic()
                          .time;
        period.kind = SubtreePeriod::Kind::Scheduled;
        res.push_back(period);
    }

    if (kinds.contains(SubtreePeriod::Kind::Closed)
        && isBoolFalse(h->closed)) {
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
                if (isBoolFalse(log->getClock().to)) {
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
Vec<sem::CmdArgumentValue> CmdArguments_getArguments(
    Handle const& handle,
    CR<Opt<Str>>  param) {
    auto h           = getConstHandle(handle);
    using HandleBase = get_ast_type<Handle>::ast_type;
    Vec<sem::CmdArgumentValue> res;
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
Vec<sem::CmdArgumentValue> Stmt_getArguments(
    Handle          handle,
    const Opt<Str>& kind) {
    auto h           = getConstHandle(handle);
    using HandleBase = get_ast_type<Handle>::ast_type;

    Vec<sem::CmdArgumentValue> result;

    for (auto const& sub : h->attached) {
        if (toHandle(sub, handle)->getKind() == OrgSemKind::CmdAttr) {
            result.append( //
                CmdArguments_getArguments(
                    toHandle(
                        org_cast<sem::CmdAttr>(toHandle(sub, handle))
                            ->parameters,
                        handle)
                        .value(),
                    kind));
        }
    }

    return result;
}

template <typename Handle>
Vec<sem::CmdArgumentValue> Cmd_getArguments(
    Handle const& handle,
    CR<Opt<Str>>  param) {
    auto                       h = getConstHandle(handle);
    Vec<sem::CmdArgumentValue> res;
    if (isBoolFalse(h->parameters)) {
        res = CmdArguments_getArguments(
            toHandle(h->parameters, handle).value(), param);
    }
    res.append(Stmt_getArguments(handle, param));
    return res;
}

template <typename Handle>
Opt<sem::CmdArgumentValue> Stmt_getFirstArgument(
    Handle  handle,
    CR<Str> kind) {
    auto h   = getConstHandle(handle);
    auto res = Stmt_getArguments(handle, kind);

    if (res.empty()) {
        return std::nullopt;
    } else {
        return res.front();
    }
}

template <typename Handle>
Opt<sem::CmdArgumentValue> Cmd_getFirstArgument(
    Handle     handle,
    Str const& kind) {
    auto h = getConstHandle(handle);
    if (isBoolFalse(h->parameters)) {
        auto res = CmdArguments_getArguments(
            toHandle(h->parameters, handle).value(), kind);
        if (res.empty()) {
            return std::nullopt;
        } else {
            return res.front();
        }
    } else {
        return Stmt_getFirstArgument(handle, kind);
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
            auto k = *kind;
            if (sub_h->is(OrgSemKind::CmdAttr)) {
                auto attr = org_cast<sem::CmdAttr>(sub_h);
                if (normalize("attr_" + attr->target) == k) {
                    result.push_back(sub_h);
                }
            } else if (
                sub_h->is(OrgSemKind::CmdCaption)
                && normalize(k) == "caption") {
                auto cap = org_cast<sem::CmdCaption>(sub_h);
                result.push_back(sub_h);
            }
        } else {
            result.push_back(sub_h);
        }
    }

    return result;
}


} // namespace


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

Vec<org::ImmAdapter> org::ImmAdapterStmtAPI::getAttached(Opt<Str> const& kind) const {
    Vec<org::ImmAdapter> result;
    CallDynamicOrgMethod<org::ImmStmt>(getThis(), [&](auto const &a1, auto const &a2) { result = Stmt_getAttached(a1, a2); }, kind);
    return result;
}

Vec<sem::CmdArgumentValue> org::ImmAdapterStmtAPI::getArguments(CR<Opt<Str>> param) const {
  Vec<sem::CmdArgumentValue> result;
  CallDynamicOrgMethod<org::ImmStmt>(getThis(), [&](auto const &a1, auto const &a2) { result = Stmt_getArguments(a1, a2); }, param);
  return result;
}

Vec<sem::CmdArgumentValue> org::ImmAdapterCmdAPI::getArguments(CR<Opt<Str>> param) const {
  Vec<sem::CmdArgumentValue> result;
  CallDynamicOrgMethod<org::ImmCmd>(getThis(), [&](auto const &a1, auto const &a2) { result = Cmd_getArguments(a1, a2); }, param);
  return result;
}

Opt<sem::CmdArgumentValue> org::ImmAdapterStmtAPI::getFirstArgument(Str const& param) const {
  Opt<sem::CmdArgumentValue> result;
  CallDynamicOrgMethod<org::ImmStmt>(getThis(), [&](auto const &a1, auto const &a2) { result = Stmt_getFirstArgument(a1, a2); }, param);
  return result;
}

Opt<sem::CmdArgumentValue> org::ImmAdapterCmdAPI::getFirstArgument(Str const& param) const {
  Opt<sem::CmdArgumentValue> result;
  CallDynamicOrgMethod<org::ImmCmd>(getThis(), [&](auto const &a1, auto const &a2) { result = Cmd_getFirstArgument(a1, a2); }, param);
  return result;
}

Opt<sem::NamedProperty> org::ImmAdapterSubtreeAPI::getProperty(Str const &kind, CR<Opt<Str>> subkind) const { return subtreeGetPropertyImpl(getThis()->as<org::ImmSubtree>(), kind, subkind); }
Vec<sem::NamedProperty> org::ImmAdapterSubtreeAPI::getProperties(const Str &kind, const Opt<Str> &subkind) const { return subtreeGetPropertiesImpl(getThis()->as<org::ImmSubtree>(), kind, subkind); }
Vec<sem::SubtreePeriod> org::ImmAdapterSubtreeAPI::getTimePeriods(IntSet<sem::SubtreePeriod::Kind> kinds) const { return subtreeGetTimePeriodsImpl(getThis()->as<org::ImmSubtree>(), kinds); }


Opt<sem::NamedProperty> sem::Subtree::getProperty(Str const &kind, CR<Opt<Str>> subkind) const { return subtreeGetPropertyImpl(this, kind, subkind); }
Vec<sem::NamedProperty> sem::Subtree::getProperties(Str const &kind, CR<Opt<Str>> subkind) const { return subtreeGetPropertiesImpl(this, kind, subkind); }
Vec<sem::SubtreePeriod> sem::Subtree::getTimePeriods(IntSet<sem::SubtreePeriod::Kind> kinds) const { return subtreeGetTimePeriodsImpl(this, kinds); }
Str sem::CmdArgument::getValue() const { return arg.value; }
Str sem::CmdArgument::getName() const { return arg.name.value(); }
Str sem::CmdArgument::getVarname() const { return arg.varname.value(); }

Vec<sem::CmdArgumentValue> sem::Stmt::getArguments(const Opt<Str>& kind) const { return Stmt_getArguments(this, kind); }
Opt<sem::CmdArgumentValue> sem::Stmt::getFirstArgument(const Str& kind) const { return Stmt_getFirstArgument(this, kind); }

Opt<sem::CmdArgumentValue> sem::Cmd::getFirstArgument(CR<Str> kind) const { return Cmd_getFirstArgument(this, kind); }
Vec<sem::CmdArgumentValue> sem::CmdArguments::getArguments(CR<Opt<Str>> param) const { return CmdArguments_getArguments(this, param); }
Vec<sem::CmdArgumentValue> sem::Cmd::getArguments(CR<Opt<Str>> param) const { return Cmd_getArguments(this, param); }



// Opt<org::ImmAdapterT<org::ImmCmdArgumentList>> org::ImmAdapterT<org::ImmCell>::getArguments(CR<Opt<Str>> param) const { return cmdGetArgumentsImpl(*this, param); }


// clang-format on
