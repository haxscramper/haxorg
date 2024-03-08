#include <sem/SemOrg.hpp>
#include <boost/mp11.hpp>
#include <concepts>
#include <format>

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
sem::OrgVariant asVariant(SemId<Org> in) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: return in.as<__Kind>();

    switch (in->getKind()) { EACH_SEM_ORG_KIND(__case) }

#undef __case
}
} // namespace sem

Org::Org() : subnodes({}) {}

Org::Org(OrgAdapter original) : original(original), subnodes({}) {}

Org::Org(CVec<SemId<Org>> subnodes) : subnodes(subnodes) {}

namespace {
void eachSubnodeRecImpl(
    CR<SemId<Org>::SubnodeVisitor> visitor,
    SemId<Org>                     org,
    bool                           originalBase);

template <sem::NotOrg T>
void visitField(CR<SemId<Org>::SubnodeVisitor>, CR<T>) {}


void visitField(CR<SemId<Org>::SubnodeVisitor> visitor, SemId<Org> node) {
    if (!node.isNil()) { eachSubnodeRecImpl(visitor, node, true); }
}

template <typename T>
void visitField(CR<SemId<Org>::SubnodeVisitor> visitor, CVec<T> value) {
    for (const auto& it : value) { visitField(visitor, it); }
}


template <typename T>
void visitField(CR<SemId<Org>::SubnodeVisitor> visitor, CR<Opt<T>> value) {
    if (value) { visitField(visitor, *value); }
}

template <typename T>
void recVisitOrgNodesImpl(
    CR<SemId<Org>::SubnodeVisitor> visitor,
    sem::SemId<T>                  tree,
    bool                           originalBase) {
    if (originalBase) { visitor(tree); }
    using Bd = describe_bases<T, mod_any_access>;
    using Md = describe_members<T, mod_any_access>;
    mp_for_each<Bd>([&](auto Base) {
        using BaseType = typename decltype(Base)::type;
        recVisitOrgNodesImpl<BaseType>(
            visitor, tree.template as<BaseType>(), false);
    });

    mp_for_each<Md>([&](auto const& field) {
        visitField(
            visitor, (*static_cast<T const*>(tree.get())).*field.pointer);
    });
}

void eachSubnodeRecImpl(
    CR<SemId<Org>::SubnodeVisitor> visitor,
    SemId<Org>                     org,
    bool                           originalBase) {
    std::visit(
        [&](const auto& node) {
            recVisitOrgNodesImpl(visitor, node, originalBase);
        },
        asVariant(org));
}
} // namespace

template <>
void SemId<Org>::eachSubnodeRec(SubnodeVisitor cb) {
    eachSubnodeRecImpl(cb, *this, true);
}

Opt<SemId<CmdArgument>> CmdArguments::getParameter(CR<Str> param) const {
    return named.get(normalize(param));
}

Opt<SemId<CmdArgument>> Block::getParameter(CR<Str> param) const {
    if (parameters) {
        return (*parameters)->getParameter(param);
    } else {
        return std::nullopt;
    }
}

Vec<Subtree::Period> Subtree::getTimePeriods(
    IntSet<Period::Kind> kinds) const {
    Vec<Period> res;
    for (const auto& it : title->subnodes) {
        if (it->getKind() == osk::Time) {
            res.push_back(Period(it.as<Time>(), Period::Kind::Titled));
        } else if (it->getKind() == osk::TimeRange) {
            res.push_back(
                Period(it.as<TimeRange>(), Period::Kind::Titled));
        }
    }

    for (const auto& prop : properties) {
        std::visit(
            overloaded{
                [&](Property::Created const& cr) {
                    res.push_back(Period(cr.time, Period::Kind::Created));
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

Opt<Property> Subtree::getProperty(Str const& kind, CR<Opt<Str>> subkind)
    const {
    auto props = getProperties(kind, subkind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        return props[0];
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
    if (normalize(fmt1(getKind())) == normalize(kind)) {
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

Opt<SemId<Org>> Stmt::getAttached(OrgSemKind kind) {
    for (const auto& sub : attached) {
        if (sub->getKind() == kind) { return sub; }
    }

    return std::nullopt;
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
