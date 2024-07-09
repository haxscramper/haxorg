#include <sem/SemOrg.hpp>
#include <boost/mp11.hpp>
#include <concepts>
#include <format>
#include <exporters/exportertree.hpp>

#define _define_static(__Kind)                                            \
    const OrgSemKind sem::__Kind::staticKind = OrgSemKind::__Kind;

EACH_SEM_ORG_KIND(_define_static)

#undef _define_static


using boost::mp11::mp_for_each;
using namespace boost::describe;

using namespace sem;
using osk      = OrgSemKind;
using Property = Subtree::Property;

template <>
struct value_domain<sem::Subtree::Period::Kind>
    : value_domain_ungapped<
          sem::Subtree::Period::Kind,
          sem::Subtree::Period::Kind::Clocked,
          sem::Subtree::Period::Kind::Repeated> {};

namespace sem {
sem::OrgIdVariant asVariant(SemId<Org> in) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: return in.as<__Kind>();

    switch (in->getKind()) { EACH_SEM_ORG_KIND(__case) }

#undef __case
}

sem::OrgPtrVariant asVariant(Org* in) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: return dynamic_cast<__Kind*>(in);
    switch (in->getKind()) { EACH_SEM_ORG_KIND(__case) }
#undef __case
}

} // namespace sem

Org::Org() : subnodes({}) {}
Org::Org(OrgAdapter original) : original(original), subnodes({}) {}
Org::Org(CVec<SemId<Org>> subnodes) : subnodes(subnodes) {}


Opt<SemId<CmdArgumentList>> CmdArguments::getArguments(
    CR<Opt<Str>> param) const {
    if (param) {
        auto norm = normalize(*param);
        if (named.contains(norm)) {
            return named.at(norm);
        } else {
            return std::nullopt;
        }
    } else {
        auto result = SemId<CmdArgumentList>::New();
        for (auto const& it : positional->args) {
            result->args.push_back(it);
        }

        for (auto const& it : named.keys()) {
            for (auto const& val : named.at(it)->args) {
                result->args.push_back(val);
            }
        }

        return result;
    }
}

Opt<SemId<CmdArgumentList>> Command::getArguments(
    CR<Opt<Str>> param) const {
    Opt<SemId<CmdArgumentList>> paramArguments;
    if (parameters) {
        paramArguments = (*parameters)->getArguments(param);
    }

    auto stmtArguments = Stmt::getArguments(param);

    auto res = SemId<CmdArgumentList>::New();
    if (paramArguments) { res->args.append((**paramArguments).args); }
    if (stmtArguments) { res->args.append((**stmtArguments).args); }

    if (res->args.empty()) {
        return std::nullopt;
    } else {
        return res;
    }
}

Vec<Subtree::Period> Subtree::getTimePeriods(
    IntSet<Period::Kind> kinds) const {
    Vec<Period> res;
    for (const auto& it : title->subnodes) {
        if (it->getKind() == osk::Time) {
            Period period{};
            period.from = it.as<Time>();
            period.kind = Period::Kind::Titled;
            res.push_back(period);
        } else if (it->getKind() == osk::TimeRange) {
            Period period{};
            period.from = it.as<TimeRange>()->from;
            period.to   = it.as<TimeRange>()->to;
            period.kind = Period::Kind::Titled;
            res.push_back(period);
        }
    }

    if (kinds.contains(Period::Kind::Deadline) && this->deadline) {
        Period period{};
        period.from = this->deadline.value();
        period.kind = Period::Kind::Deadline;
        res.push_back(period);
    }

    if (kinds.contains(Period::Kind::Scheduled) && this->scheduled) {
        Period period{};
        period.from = this->scheduled.value();
        period.kind = Period::Kind::Scheduled;
        res.push_back(period);
    }

    if (kinds.contains(Period::Kind::Closed) && this->closed) {
        Period period{};
        period.from = this->closed.value();
        period.kind = Period::Kind::Closed;
        res.push_back(period);
    }

    if (kinds.contains(Period::Kind::Clocked)) {
        for (auto const& log : this->logbook) {
            if (log->getLogKind() == SubtreeLog::Kind::Clock) {
                Period period{};
                period.from = log->getClock().from;
                period.to   = log->getClock().to;
                period.kind = Period::Kind::Clocked;
                res.push_back(period);
            }
        }
    }

    for (const auto& prop : properties) {
        std::visit(
            overloaded{
                [&](Property::Created const& cr) {
                    Period period{};
                    period.from = cr.time;
                    period.kind = Period::Kind::Created;
                    res.push_back(period);
                },
                [](auto const&) {}},
            prop.data);
    }


    return res;
}

Vec<Property> Subtree::getProperties(Str const& kind, CR<Opt<Str>> subkind)
    const {
    Vec<Property> result;
    for (const auto& prop : properties) {
        if (prop.isMatching(kind, subkind)) { result.push_back(prop); }
    }
    return result;
}


bool HashTag::prefixMatch(CR<Vec<Str>> prefix) const {
    if (prefix.empty() || (prefix.size() == 1 && prefix[0] == head)) {
        return true;
    } else if (prefix[0] != head) {
        return false;
    } else {
        Vec<Str> tmp;
        for (const auto& it : prefix[slice(1, 1_B)]) { tmp.push_back(it); }

        for (const auto& sub : subtags) {
            if (sub->prefixMatch(tmp)) { return true; }
        }
        return false;
    }
}

void Subtree::setPropertyStrValue(
    Str const&   value,
    Str const&   kind,
    CR<Opt<Str>> subkind) {
    if (normalize(kind) == "id") {
        this->treeId = value;
    } else {
        removeProperty(kind, subkind);
        Property::Unknown prop;
        prop.name  = kind;
        auto text  = SemId<RawText>::New();
        text->text = value;
        prop.value = text;
        properties.push_back(Property{prop});
    }
}

void Subtree::setProperty(Property const& value) {
    removeProperty(value.getName(), value.getSubKind());
    properties.push_back(value);
}

Opt<Property> Subtree::getProperty(Str const& kind, CR<Opt<Str>> subkind)
    const {
    auto props = getProperties(kind, subkind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        return props[0];
    }
}

void Subtree::removeProperty(const Str& kind, const Opt<Str>& subkind) {
    for (int i = properties.high(); 0 <= i; --i) {
        if (properties.at(i).getName() == kind
            && properties.at(i).getSubKind() == subkind) {
            properties.erase(properties.begin() + i);
        }
    }
}

Str Subtree::Property::getName() const {
    if (getKind() == Kind::Unknown) {
        return getUnknown().name;
    } else {
        return fmt1(getKind());
    }
}

Opt<Str> Subtree::Property::getSubKind() const {
    if (getKind() == Kind::ExportOptions) {
        return getExportOptions().backend;
    } else {
        return std::nullopt;
    }
}

bool Subtree::Property::isMatching(Str const& kind, CR<Opt<Str>> subkind)
    const {
    if (getKind() == Property::Kind::Unknown) {
        return normalize(getUnknown().name) == normalize(kind);
    } else if (normalize(fmt1(getKind())) == normalize(kind)) {
        return true;
    } else if (
        getKind() == Property::Kind::ExportOptions && subkind
        && normalize(getExportOptions().backend) == normalize(*subkind)) {
        return true;
    } else {
        return false;
    }
}

Vec<Subtree::Property> DocumentOptions::getProperties(
    Str const&   kind,
    CR<Opt<Str>> subkind) const {
    Vec<Subtree::Property> result;
    for (const auto& prop : properties) {
        if (prop.isMatching(kind, subkind)) { result.push_back(prop); }
    }
    return result;
}

Opt<Subtree::Property> DocumentOptions::getProperty(
    CR<Str>      kind,
    CR<Opt<Str>> subkind) const {
    auto props = getProperties(kind, subkind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        return props[0];
    }
}

Vec<Subtree::Property> Document::getProperties(
    CR<Str>      kind,
    CR<Opt<Str>> subkind) const {
    if (options.isNil()) {
        return {};
    } else {
        return options->getProperties(kind, subkind);
    }
}

Opt<Subtree::Property> Document::getProperty(
    CR<Str>      kind,
    CR<Opt<Str>> subkind) const {
    if (options.isNil()) {
        return std::nullopt;
    } else {
        return options->getProperty(kind, subkind);
    }
}

bool List::isDescriptionList() const {
    for (const auto& sub : subnodes) {
        if (sub->is(osk::ListItem)) {
            if (sub.as<ListItem>()->isDescriptionItem()) { return true; }
        }
    }
    return false;
}

Vec<sem::SemId<sem::Org>> Stmt::getAttached(CR<Opt<Str>> kind) const {
    Vec<SemId<Org>> result;
    for (const auto& sub : attached) {
        if (kind) {
            auto k = *kind;
            if (auto attr = sub.getAs<sem::CmdAttr>()) {
                if (normalize("attr_" + attr->target) == k) {
                    result.push_back(sub);
                }
            } else if (auto cap = sub.getAs<sem::Caption>();
                       cap && normalize(k) == "caption") {
                result.push_back(sub);
            }
        } else {
            result.push_back(sub);
        }
    }

    return result;
}

Opt<sem::SemId<CmdArgumentList>> Stmt::getArguments(
    const Opt<Str>& kind) const {
    auto result      = SemId<CmdArgumentList>::New();
    auto expect_kind = [&](CR<Str> key) -> bool {
        return !kind || normalize(*kind) == key;
    };

    for (auto const& sub : attached) {
        if (auto cap = sub.getAs<Caption>(); expect_kind("caption")) {
            // pass
        } else if (auto attr = sub.getAs<sem::CmdAttr>()) {
            if (auto arguments = (**attr->parameters).getArguments(kind)) {
                for (auto const& arg : (**arguments).args) {
                    result->args.push_back(arg);
                }
            }
        }
    }

    if (result->args.empty()) {
        return std::nullopt;
    } else {
        return result;
    }
}

void Org::push_back(SemId<Org> sub) {
    auto dat = subnodes.data();
    subnodes.push_back(sub);
}


Str CmdArgument::getString() const { return value; }

Opt<bool> CmdArgument::getBool() const {
    if (value == "yes" || value == "true" || value == "on"
        || value == "t") {
        return true;
    } else if (
        value == "no" || value == "false" || value == "nil"
        || value == "off") {
        return false;
    } else {
        return std::nullopt;
    }
}

Opt<int> CmdArgument::getInt() const {
    bool isOk   = false;
    int  result = value.toInt();
    if (isOk) {
        return result;
    } else {
        return std::nullopt;
    }
}
