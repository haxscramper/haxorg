#include <sem/SemOrg.hpp>
#include <boost/mp11.hpp>
#include <concepts>

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

sem::OrgVariant SemId::asVariant() {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: return this->as<__Kind>();

    switch (this->getKind()) { EACH_SEM_ORG_KIND(__case) }

#undef __case
}

SemId SemId::getParent() const { return (*this)->getParent(); }

Org::Org(SemId parent) : parent(parent), subnodes({}) {}

Org::Org(SemId parent, OrgAdapter original)
    : parent(parent), original(original), subnodes({}) {}

Org::Org(SemId parent, CVec<SemId> subnodes)
    : parent(parent), subnodes(subnodes) {}

Vec<SemId> SemId::getParentChain(bool withSelf) const {
    Vec<SemId> result;
    if (withSelf) {
        result.push_back(*this);
    }
    result.append(get()->getParentChain());

    return result;
}

Vec<SemId> Org::getParentChain() const {
    Vec<SemId> result;

    SemId now = parent;

    while (now) {
        result.push_back(now);
        now = now.getParent();
    }

    return result;
}


Opt<SemId> Link::resolve(Document const& doc) const {
    // TODO add target lookup that will create a full list
    // of all possible targets and genrate warning message.
    //
    // IDEA another feature that can be implemented using
    // document walker is autocompletion logic of some
    // sort.
    switch (getLinkKind()) {
        case Link::Kind::Id: {
            Opt<SemId> target = doc.idTable.get(getId().text);
            if (target) {
                return target.value();
            }
            break;
        }

        case Link::Kind::Footnote: {
            auto target = doc.footnoteTable.get(getFootnote().target);
            if (target) {
                return target.value();
            }
            break;
        }
    }

    return std::nullopt;
}

Opt<SemId> Link::resolve() const {
    if (auto doc = getDocument(); doc) {
        return resolve(*doc.value().get());
    } else {
        return std::nullopt;
    }
}


namespace {
void eachSubnodeRecImpl(
    CR<SemId::SubnodeVisitor> visitor,
    SemId                     org,
    bool                      originalBase);

template <sem::NotOrg T>
void visitField(CR<SemId::SubnodeVisitor>, CR<T>) {}


void visitField(CR<SemId::SubnodeVisitor> visitor, SemId node) {
    eachSubnodeRecImpl(visitor, node, true);
}

template <typename T>
void visitField(CR<SemId::SubnodeVisitor> visitor, CVec<T> value) {
    for (const auto& it : value) {
        visitField(visitor, it);
    }
}


template <typename T>
void visitField(CR<SemId::SubnodeVisitor> visitor, CR<Opt<T>> value) {
    if (value) {
        visitField(visitor, *value);
    }
}

template <typename T>
void recVisitOrgNodesImpl(
    CR<SemId::SubnodeVisitor> visitor,
    sem::SemIdT<T>            tree,
    bool                      originalBase) {
    if (originalBase) {
        visitor(tree);
    }
    using Bd = describe_bases<T, mod_any_access>;
    using Md = describe_members<T, mod_any_access>;
    mp_for_each<Bd>([&](auto Base) {
        recVisitOrgNodesImpl<typename decltype(Base)::type>(
            visitor, tree, false);
    });

    mp_for_each<Md>([&](auto const& field) {
        visitField(
            visitor, (*static_cast<T const*>(tree.get())).*field.pointer);
    });
}

void eachSubnodeRecImpl(
    CR<SemId::SubnodeVisitor> visitor,
    SemId                     org,
    bool                      originalBase) {
    std::visit(
        [&](const auto& node) {
            recVisitOrgNodesImpl(visitor, node, originalBase);
        },
        org.asVariant());
}
} // namespace

void SemId::eachSubnodeRec(SubnodeVisitor cb) {
    eachSubnodeRecImpl(cb, *this, true);
}

Opt<SemIdT<Subtree>> Org::getParentSubtree() const {
    for (const auto& item : getParentChain()) {
        if (item->getKind() == OrgSemKind::Subtree) {
            return item.as<Subtree>();
        }
    }
    return std::nullopt;
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

Vec<Property> Subtree::getProperties(Property::Kind kind, CR<Str> subkind)
    const {
    Vec<Property> result;
    for (const auto& prop : properties) {
        if (prop.matches(kind, subkind)) {
            result.push_back(prop);
        }
    }
    return result;
}

Vec<Property> Subtree::getContextualProperties(
    Property::Kind kind,
    CR<Str>        subkind) const {
    Vec<Property> result;
    result.append(getProperties(kind));

    for (SemId parent : getParent().getParentChain(true)) {
        if (parent->is(osk::Subtree)) {
            result.append(parent.as<Subtree>()->getProperties(kind));
        }
    }

    std::reverse(result.begin(), result.end());

    Vec<Property> rulesApplied;
    for (int i = 0; i < result.size(); ++i) {
        const auto& prop = result[i];
        if (prop.inheritanceMode
            == Property::InheritanceMode::ThisAndSub) {
            rulesApplied.push_back(prop);
        } else if (
            prop.inheritanceMode == Property::InheritanceMode::OnlyThis
            && i == result.size() - 1) {
            // 'this' is the target node
            rulesApplied.push_back(prop);
        } else if (
            prop.inheritanceMode == Property::InheritanceMode::OnlySub
            && i != result.size() - 1) {
            rulesApplied.push_back(prop);
        }
    }

    return rulesApplied;
}

bool HashTag::prefixMatch(CR<Vec<Str>> prefix) const {
    if (prefix.empty() || (prefix.size() == 1 && prefix[0] == head)) {
        return true;
    } else if (prefix[0] != head) {
        return false;
    } else {
        Vec<Str> tmp;
        for (const auto& it : prefix[slice(1, 1_B)]) {
            tmp.push_back(it);
        }

        for (const auto& sub : subtags) {
            if (sub->prefixMatch(tmp)) {
                return true;
            }
        }
        return false;
    }
}

Opt<Property> Subtree::getContextualProperty(
    Property::Kind kind,
    CR<Str>        subkind) const {
    Vec<Property> props = getContextualProperties(kind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        switch (props[0].getKind()) {
            case Property::Kind::Nonblocking:
            case Property::Kind::Unnumbered:
            case Property::Kind::Ordered:
            case Property::Kind::Created: return props[0];
            case Property::Kind::ExportOptions: {
                Property::ExportOptions res;
                for (const auto& it : props) {
                    Property::ExportOptions const& tmp = it.getExportOptions();
                    for (auto const& [k, v] : tmp.values) {
                        if (!res.values.contains(k)) {
                            res.values[k] = v;
                        }
                    }
                }
                return Property(res);
            }
        }
    }
}

Opt<Property> Subtree::getProperty(Property::Kind kind, CR<Str> subkind)
    const {
    auto props = getProperties(kind, subkind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        return props[0];
    }
}

bool Subtree::Property::matches(Kind kind, CR<QString> subkind) const {
    if (getKind() == kind) {
        return true;
    } else if (
        getKind() == Property::Kind::ExportOptions
        && normalize(getExportOptions().backend) == normalize(subkind)) {
        return true;
    } else {
        return false;
    }
}

Vec<Subtree::Property> DocumentOptions::getProperties(
    Subtree::Property::Kind kind,
    CR<Str>                 subkind) const {
    Vec<Subtree::Property> result;
    for (const auto& prop : properties) {
        if (prop.matches(kind, subkind)) {
            result.push_back(prop);
        }
    }
    return result;
}

Opt<Subtree::Property> DocumentOptions::getProperty(
    Subtree::Property::Kind kind,
    CR<Str>                 subkind) const {
    auto props = getProperties(kind, subkind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        return props[0];
    }
}

Vec<Subtree::Property> Document::getProperties(
    Subtree::Property::Kind kind,
    CR<Str>                 subkind) const {
    if (options.isNil()) {
        return {};
    } else {
        return options->getProperties(kind, subkind);
    }
}

Opt<Subtree::Property> Document::getProperty(
    Subtree::Property::Kind kind,
    CR<Str>                 subkind) const {
    if (options.isNil()) {
        return std::nullopt;
    } else {
        return options->getProperty(kind, subkind);
    }
}

Opt<SemIdT<Subtree>> Document::getSubtree(CR<Str> id) const {
    return idTable.get(id);
}

Opt<SemId> Document::resolve(CR<SemId> node) const {
    Q_CHECK_PTR(node);
    Q_CHECK_PTR(this);
    switch (node->getKind()) {
        case osk::Link: return node.as<Link>()->resolve(*this);
        default: return std::nullopt;
    }
}

bool List::isDescriptionList() const {
    for (const auto& sub : subnodes) {
        if (sub->is(osk::ListItem)) {
            if (sub.as<ListItem>()->isDescriptionItem()) {
                return true;
            }
        }
    }
    return false;
}

Opt<SemId> Stmt::getAttached(OrgSemKind kind) {
    for (const auto& sub : attached) {
        if (sub->getKind() == kind) {
            return sub;
        }
    }

    return std::nullopt;
}


Opt<SemIdT<Document>> Org::getDocument() const {
    for (const auto& item : getParentChain()) {
        if (item->getKind() == OrgSemKind::Document) {
            auto result = item.as<Document>();
            return result;
        }
    }
    Q_ASSERT(false);
    return std::nullopt;
}

void Org::push_back(SemId sub) {
    auto dat = subnodes.data();
    subnodes.push_back(sub);
}

bool SemId::is(OrgSemKind kind) const {
    return !isNil() && get()->is(kind);
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
    int  result = value.toInt(&isOk);
    if (isOk) {
        return result;
    } else {
        return std::nullopt;
    }
}

Opt<SemIdT<CmdArgument>> CmdArguments::popArg(Str key) {
    if (named.contains(key)) {
        auto result = named.at(key);
        named.erase(key);
        return result;
    } else {
        return std::nullopt;
    }
}

namespace sem {
QTextStream& operator<<(QTextStream& os, SemId const& value) {
    return os << value.getStoreIndex() << ":" << to_string(value.getKind())
              << ":" << value.getNodeIndex();
}
} // namespace sem
