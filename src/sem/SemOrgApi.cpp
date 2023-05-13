#include <sem/SemOrg.hpp>
#include <boost/mp11.hpp>
#include <concepts>

using boost::mp11::mp_for_each;
using namespace boost::describe;

using namespace sem;
using osk      = OrgSemKind;
using Property = Subtree::Property;

template <>
sem::Subtree::Period::Kind low() {
    return sem::Subtree::Period::Kind::Clocked;
}

template <>
sem::Subtree::Period::Kind high() {
    return sem::Subtree::Period::Kind::Repeated;
}

sem::OrgVariant Org::asVariant() {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: return this->as<__Kind>();

    switch (this->getKind()) { EACH_SEM_ORG_KIND(__case) }

#undef __case
}

OrgVariant Org::fromKind(OrgSemKind kind) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: return std::make_shared<__Kind>();

    switch (kind) { EACH_SEM_ORG_KIND(__case) }

#undef __case
}


Vec<Org*> Org::getParentChain(bool withSelf) const {
    Vec<Org*> result;

    Org const* now = withSelf ? this : getParent();

    while (now != nullptr) {
        result.push_back(const_cast<Org*>(now));
        now = now->getParent();
    }

    return result;
}


Opt<Wrap<Document>> Org::getDocument() const {
    for (const auto& item : getParentChain()) {
        if (item->getKind() == OrgSemKind::Document) {
            return item->as<Document>();
        }
    }
    return std::nullopt;
}


namespace {
void assignIdsImpl(
    CR<Org::SubnodeVisitor> visitor,
    sem::Wrap<sem::Org>     org);

template <sem::NotOrg T>
void visitField(CR<Org::SubnodeVisitor>, CR<T>) {}


void visitField(
    CR<Org::SubnodeVisitor> visitor,
    sem::Wrap<sem::Org>     node) {
    assignIdsImpl(visitor, node);
}

template <typename T>
void visitField(CR<Org::SubnodeVisitor> visitor, CVec<T> value) {
    for (const auto& it : value) {
        visitField(visitor, it);
    }
}


template <typename T>
void visitField(CR<Org::SubnodeVisitor> visitor, CR<Opt<T>> value) {
    if (value) {
        visitField(visitor, *value);
    }
}

template <typename T>
void recVisitOrgNodesImpl(
    CR<Org::SubnodeVisitor> visitor,
    sem::Wrap<T>            tree) {
    visitor(tree);
    using Bd = describe_bases<T, mod_any_access>;
    using Md = describe_members<T, mod_any_access>;
    mp_for_each<Bd>([&](auto Base) {
        recVisitOrgNodesImpl<typename decltype(Base)::type>(visitor, tree);
    });

    mp_for_each<Md>([&](auto const& field) {
        visitField(visitor, (*tree).*field.pointer);
    });
}

void assignIdsImpl(
    CR<Org::SubnodeVisitor> visitor,
    sem::Wrap<sem::Org>     org) {
    std::visit(
        [&](const auto& node) { recVisitOrgNodesImpl(visitor, node); },
        org->asVariant());
}
} // namespace

void Org::eachSubnodeRec(SubnodeVisitor cb) {
    assignIdsImpl(cb, shared_from_this());
}

void Org::assignIds() {
    int count = 0;
    eachSubnodeRec([&](Wrap<Org> org) {
        org->id = count;
        ++count;
    });
}

Opt<Wrap<Subtree>> Org::getParentSubtree() const {
    for (const auto& item : getParentChain()) {
        if (item->getKind() == OrgSemKind::Subtree) {
            return item->as<Subtree>();
        }
    }
    return std::nullopt;
}

Vec<Subtree::Period> Subtree::getTimePeriods(IntSet<Period::Kind> kinds) {
    Vec<Period> res;
    for (const auto& it : title->subnodes) {
        if (it->getKind() == osk::Time) {
            res.push_back(Period(it->as<Time>(), Period::Kind::Titled));
        } else if (it->getKind() == osk::TimeRange) {
            res.push_back(
                Period(it->as<TimeRange>(), Period::Kind::Titled));
        }
    }

    for (const auto& prop : properties) {
        std::visit(
            overloaded{
                [&](Property::Created const& cr) {
                    res.push_back(Period(
                        std::make_shared<Time>(cr.time),
                        Period::Kind::Created));
                },
                [](auto const&) {}},
            prop.data);
    }


    return res;
}

Vec<Property> Subtree::getProperties(
    Property::Kind kind,
    CR<QString>    subkind) const {
    Vec<Property> result;
    for (const auto& prop : properties) {
        if (prop.getKind() == kind) {
            result.push_back(prop);
        } else if (
            prop.getKind() == Property::Kind::ExportOptions
            && normalize(prop.getExportOptions().backend)
                   == normalize(subkind)) {
            result.push_back(prop);
        }
    }
    return result;
}

Vec<Property> Subtree::getContextualProperties(
    Property::Kind kind,
    CR<QString>    subkind) const {
    Subtree const* now = this;
    Vec<Property>  result;
    while (now != nullptr) {
        result.append(now->getProperties(kind));
        if (auto sup = now->getParentSubtree()) {
            now = sup.value().get();
        } else {
            now = nullptr;
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
    CR<QString>    subkind) const {
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

Opt<Property> Subtree::getProperty(
    Property::Kind kind,
    CR<QString>    subkind) const {
    auto props = getProperties(kind, subkind);
    if (props.empty()) {
        return std::nullopt;
    } else {
        return props[0];
    }
}

Opt<Wrap<Subtree>> Document::getSubtree(CR<Str> id) {
    auto iid = idTable.get(id);
    if (!iid) {
        return std::nullopt;
    }
    auto tree = getTree(iid.value());
    if (!tree) {
        return std::nullopt;
    }
    return (**tree).as<Subtree>();
}

Opt<Wrap<Org>> Document::resolve(CR<Wrap<Org>> node) {
    Q_CHECK_PTR(node);
    Q_CHECK_PTR(this);
    switch (node->getKind()) {
        case osk::Link: {
            auto link = node->as<Link>();
            switch (link->getLinkKind()) {
                case Link::Kind::Id: {
                    Opt<int> target = idTable.get(link->getId().text);


                    if (target) {
                        return getTree(target.value());
                    }
                    // TODO add target lookup that will create a full list
                    // of all possible targets and genrate warning message.
                    //
                    // IDEA another feature that can be implemented using
                    // document walker is autocompletion logic of some
                    // sort.
                    qWarning() << "Failed resolving link with ID"
                               << link->getId().text << "to" << target;


                    break;
                }
                case Link::Kind::Footnote: {
                    auto target = footnoteTable.get(
                        link->getFootnote().target);

                    if (target) {
                        return getTree(target.value());
                    }

                    qWarning()
                        << "Failed resolving footnote with ID"
                        << link->getFootnote().target << "to" << target;

                    break;
                }
            }
            break;
        }
    }

    return std::nullopt;
}

bool List::isDescriptionList() const {
    for (const auto& sub : subnodes) {
        if (sub->as<ListItem>()->isDescriptionItem()) {
            return true;
        }
    }
    return false;
}
