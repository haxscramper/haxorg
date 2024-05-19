#pragma once

#include <sem/SemOrg.hpp>
#include <hstd/stdlib/Map.hpp>
#include <QMimeData>
#include <QIODevice>
#include <sem/SemBaseApi.hpp>
#include <immer/box.hpp>
#include <hstd/stdlib/Filesystem.hpp>

struct OrgBox {
    immer::box<sem::SemId<sem::Org>> boxed;
    OrgBox(sem::SemId<sem::Org> node) : boxed(node) {}

    sem::Org const&      operator*() { return *boxed.get().get(); }
    sem::Org const*      operator->() { return boxed.get().get(); }
    sem::SemId<sem::Org> node() const { return boxed.get(); }
    OrgBox() : boxed(sem::SemId<sem::Org>::Nil()) {}
};

struct OrgBoxId {
    int      value = 0;
    OrgBoxId next() const { return OrgBoxId{value + 1}; }
    OrgBoxId(int value = 0) : value(value) {};

    bool operator==(OrgBoxId const& other) const {
        return this->value == other.value;
    }

    DESC_FIELDS(OrgBoxId, (value));
};

template <>
struct std::formatter<OrgBoxId> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const OrgBoxId& p, FormatContext& ctx) const {
        fmt_ctx("{", ctx);
        fmt_ctx(p.value, ctx);
        return fmt_ctx("}", ctx);
    }
};


inline QDataStream& operator<<(QDataStream& out, const OrgBoxId& myObj) {
    return out << myObj.value;
}

inline QDataStream& operator>>(QDataStream& in, OrgBoxId& myObj) {
    return in >> myObj.value;
}

Q_DECLARE_METATYPE(OrgBoxId);

template <>
struct std::hash<OrgBoxId> {
    std::size_t operator()(OrgBoxId const& it) const noexcept {
        std::size_t result = 0;
        boost::hash_combine(result, it.value);
        return result;
    }
};


sem::SemId<sem::Org> copy(sem::OrgArg node);

static const SemSet NestedNodes{
    OrgSemKind::Subtree,
    OrgSemKind::Document,
    OrgSemKind::List,
    OrgSemKind::ListItem,
    OrgSemKind::StmtList,
};

struct OrgStore;

struct OrgTreeNode {
    OrgBoxId               boxId{};
    Vec<UPtr<OrgTreeNode>> subnodes;
    OrgTreeNode*           parent;
    OrgStore*              store;

    OrgTreeNode(
        OrgBoxId     id,
        OrgStore*    store,
        OrgTreeNode* pParent = nullptr)
        : boxId(id), parent(pParent), store(store) {}

    Vec<OrgTreeNode*> getParentChain(bool withSelf = true) {
        OrgTreeNode*      tmp = this;
        Vec<OrgTreeNode*> result;
        while (tmp->parent != nullptr) {
            if (withSelf || tmp != this) { result.push_back(tmp); }
            tmp = tmp->parent;
        }
        return result;
    }

    OrgTreeNode* root() {
        OrgTreeNode* result = this;
        while (result->parent != nullptr) { result = result->parent; }
        return result;
    }

    sem::SemId<sem::Org> getBoxedNode() const;

    OrgTreeNode* at(int idx) { return subnodes.at(idx).get(); }

    OrgTreeNode* at(CVec<int> path) {
        auto result = this;
        for (auto const& idx : path) { result = result->at(idx); }
        return result;
    }

    OrgBoxId id(int inx) { return at(inx)->boxId; }
    OrgBoxId id(CVec<int> idx) { return at(idx)->boxId; }

    sem::SemId<sem::Org> toNode() const;
    void                 buildTree(OrgTreeNode* parentNode);

    Opt<int> selfRow() const;
    Vec<int> selfPath() const;
};

struct OrgStore : public QObject {
  private:
    Q_OBJECT

  public:
    OrgBoxId                             lastId{0};
    UnorderedMap<OrgBoxId, OrgBox>       data{};
    UnorderedMap<OrgBoxId, OrgTreeNode*> nodeLookup;
    Vec<UPtr<OrgTreeNode>>               roots;

    /// \brief Create new org tree node for the ID and register it in the
    /// node lookup.
    UPtr<OrgTreeNode> addTree(OrgBoxId id, OrgTreeNode* parent) {
        auto result    = std::make_unique<OrgTreeNode>(id, this, parent);
        nodeLookup[id] = result.get();
        emit boxAdded(id);
        return result;
    }

    OrgBoxId add(sem::OrgArg node) {
        auto id  = lastId.next();
        data[id] = OrgBox{node};
        lastId   = id;
        return id;
    }

    int rootCount() const { return roots.size(); }

    /// \brief Get box from the root 0. Mainly for testing purposes.
    OrgBoxId getBox0(CVec<int> path) {
        return getRoot(0)->at(path)->boxId;
    }

    OrgTreeNode* getRoot(int idx) { return roots.at(idx).get(); }

    OrgTreeNode* addRoot(sem::OrgArg node) {
        auto box  = add(node);
        auto root = addTree(box, nullptr);
        root->buildTree(root.get());
        this->roots.push_back(std::move(root));
        return roots.back().get();
    }

    OrgTreeNode* addRoot(
        CR<fs::path>                path,
        CR<sem::OrgParseParameters> opts = sem::OrgParseParameters{}) {
        return addRoot(sem::parseFile(path, opts));
    }

    OrgTreeNode* addRoot(
        CR<Str>                     text,
        CR<sem::OrgParseParameters> opts = sem::OrgParseParameters{}) {
        return addRoot(sem::parseStringOpts(text, opts));
    }

    OrgTreeNode* getOrgTree(CR<OrgBoxId> id) const {
        return nodeLookup.at(id);
    }

    Opt<OrgBoxId> parent(CR<OrgBoxId> id) const {
        if (getOrgTree(id)->parent) {
            return getOrgTree(id)->parent->boxId;
        } else {
            return std::nullopt;
        }
    }

    sem::SemId<sem::Org> node(CR<OrgBoxId> id) const {
        return data.at(id).node();
    }

    sem::SemId<sem::Org> nodeWithoutNested(CR<OrgBoxId> id) const;
    sem::SemId<sem::Org> nodeWithoutNested(
        CR<sem::SemId<sem::Org>> id) const;


    generator<OrgBoxId> boxes() {
        for (auto const& id : data.keys()) { co_yield id; }
    }

    OrgStore() {}

    /// Create a shallow copy of the sem org tree from the `prev` boxed
    /// value and apply the replacement callback to the object. Then add a
    /// new updated node to the store as well.
    template <typename T>
    OrgBoxId update(OrgBoxId prev, Func<void(T&)> replace) {
        sem::SemId<sem::Org> node = copy(this->node(prev));
        replace(*node.getAs<T>());
        auto result = add(node);
        auto tree   = nodeLookup.at(prev);
        nodeLookup.erase(prev);
        nodeLookup[result] = tree;
        emit boxReplaced(prev, result);
        return result;
    }

  signals:
    void boxReplaced(OrgBoxId prev, OrgBoxId replace);
    void boxDeleted(OrgBoxId box);
    void boxAdded(OrgBoxId box);
};
