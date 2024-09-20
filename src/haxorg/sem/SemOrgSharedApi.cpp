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

#define WRAP_FIELD(InType, CapsField, LowField, ResType)                  \
    sem::SemId<sem::ResType> get##InType##CapsField(                      \
        sem::SemId<sem::InType> const& t) {                               \
        return t->LowField;                                               \
    }                                                                     \
    sem::SemId<sem::ResType> get##InType##CapsField(                      \
        sem::InType const* t) {                                           \
        return t->LowField;                                               \
    }                                                                     \
    org::ImmAdapterT<org::Imm##ResType> get##InType##CapsField(           \
        org::ImmAdapterT<org::Imm##InType> const& t) {                    \
        return t.getField(&org::Imm##InType::LowField);                   \
    }

WRAP_FIELD(Subtree, Title, title, Paragraph)
WRAP_FIELD(TimeRange, From, from, Time)
WRAP_FIELD(TimeRange, To, to, Time)

// clang-format off
Vec<org::ImmAdapter> getSubnodes(org::ImmAdapter const& t) { return t.sub(); }
template <typename T>
Vec<org::ImmAdapter> getSubnodes(org::ImmAdapterT<T> const& t) { return t.sub(); }
template <sem::IsOrg T>
Vec<sem::SemId<sem::Org>> getSubnodes(sem::SemId<T> const& t) { return t->subnodes; }
template <sem::IsOrg T>
Vec<sem::SemId<sem::Org>> getSubnodes(T const* t) { return t->subnodes; }
// clang-format on

template <sem::IsOrg Out, sem::IsOrg In>
sem::SemId<Out> org_cast(sem::SemId<In> arg) {
    return arg.template as<Out>();
}

template <sem::IsOrg Out, org::IsImmOrgValueType In>
org::ImmAdapterT<Out> org_cast(org::ImmAdapterT<In> arg) {
    return arg.template as<typename org::sem_to_imm_map<Out>::imm_type>();
}

template <sem::IsOrg Out>
org::ImmAdapterT<typename org::sem_to_imm_map<Out>::imm_type> org_cast(
    org::ImmAdapter arg) {
    return arg.template as<typename org::sem_to_imm_map<Out>::imm_type>();
}

template <typename Handle>
Vec<sem::SubtreePeriod> subtreeGetTimePeriodsImpl(
    Handle                           handle,
    IntSet<sem::SubtreePeriod::Kind> kinds) {
    Vec<sem::SubtreePeriod> res;
    auto                    h = getConstHandle(handle);
    using sem::SubtreePeriod;
    for (const auto& it : getSubnodes(getSubtreeTitle(handle))) {
        if (it->getKind() == OrgSemKind::Time) {
            SubtreePeriod period{};
            period.from = org_cast<sem::Time>(it)->getStatic().time;
            period.kind = SubtreePeriod::Kind::Titled;
            res.push_back(period);
        } else if (it->getKind() == OrgSemKind::TimeRange) {
            SubtreePeriod period{};
            period.from = getTimeRangeFrom(org_cast<sem::TimeRange>(it))
                              ->getStatic()
                              .time;
            period.to = org_cast<sem::TimeRange>(it)->to->getStatic().time;
            period.kind = SubtreePeriod::Kind::Titled;
            res.push_back(period);
        }
    }

    if (kinds.contains(SubtreePeriod::Kind::Deadline) && h->deadline) {
        SubtreePeriod period{};
        period.from = h->deadline.value()->getStatic().time;
        period.kind = SubtreePeriod::Kind::Deadline;
        res.push_back(period);
    }

    if (kinds.contains(SubtreePeriod::Kind::Scheduled) && h->scheduled) {
        SubtreePeriod period{};
        period.from = h->scheduled.value()->getStatic().time;
        period.kind = SubtreePeriod::Kind::Scheduled;
        res.push_back(period);
    }

    if (kinds.contains(SubtreePeriod::Kind::Closed) && h->closed) {
        SubtreePeriod period{};
        period.from = h->closed.value()->getStatic().time;
        period.kind = SubtreePeriod::Kind::Closed;
        res.push_back(period);
    }

    if (kinds.contains(SubtreePeriod::Kind::Clocked)) {
        for (auto const& log : h->logbook) {
            if (log->getLogKind() == SubtreeLog::Kind::Clock) {
                SubtreePeriod period{};
                period.from = log->getClock().from->getStatic().time;
                if (log->getClock().to) {
                    period.to = //
                        log->getClock().to.value()->getStatic().time;
                }
                period.kind = SubtreePeriod::Kind::Clocked;
                res.push_back(period);
            }
        }
    }

    for (const auto& prop : properties) {
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


} // namespace

// clang-format off
Opt<sem::NamedProperty> sem::Subtree::getProperty(Str const &kind, CR<Opt<Str>> subkind) const { return subtreeGetPropertyImpl(this, kind, subkind); }
Opt<sem::NamedProperty> org::ImmAdapterT<org::ImmSubtree>::getProperty(Str const &kind, CR<Opt<Str>> subkind) const { return subtreeGetPropertyImpl(*this, kind, subkind); }
Vec<sem::NamedProperty> sem::Subtree::getProperties(Str const &kind, CR<Opt<Str>> subkind) const { return subtreeGetPropertiesImpl(this, kind, subkind); }
Vec<sem::NamedProperty> org::ImmAdapterT<org::ImmSubtree>::getProperties(const Str &kind, const Opt<Str> &subkind) const { return subtreeGetPropertiesImpl(*this, kind, subkind); }
Vec<sem::SubtreePeriod> sem::Subtree::getTimePeriods(IntSet<sem::SubtreePeriod::Kind> kinds) const { return subtreeGetTimePeriodsImpl(this, kinds); }
Vec<sem::SubtreePeriod> org::ImmAdapterT<org::ImmSubtree>::getTimePeriods(IntSet<sem::SubtreePeriod::Kind> kinds) const { return subtreeGetTimePeriodsImpl(*this, kinds); }
// clang-format on
