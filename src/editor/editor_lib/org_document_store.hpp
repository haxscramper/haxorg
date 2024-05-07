#pragma once

#include <sem/SemOrg.hpp>
#include <hstd/stdlib/Map.hpp>
#include <QMimeData>
#include <QIODevice>
#include <immer/box.hpp>

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

struct OrgStore;

struct OrgTreeNode {
    OrgBoxId               boxId{};
    Vec<UPtr<OrgTreeNode>> subnodes;
    OrgTreeNode*           parent;

    OrgTreeNode(OrgBoxId id, OrgTreeNode* pParent = nullptr)
        : boxId(id), parent(pParent) {}

    OrgTreeNode* at(int idx) { return subnodes.at(idx).get(); }

    sem::SemId<sem::Org> toNode(OrgStore* store) const;
    void buildTree(OrgTreeNode* parentNode, OrgStore* store);
};

struct OrgStore : public QObject {
  private:
    Q_OBJECT

  public:
    OrgBoxId                       lastId{0};
    UnorderedMap<OrgBoxId, OrgBox> data{};
    Vec<UPtr<OrgTreeNode>>         roots;

    OrgBoxId add(sem::OrgArg node) {
        auto id  = lastId.next();
        data[id] = OrgBox{node};
        lastId   = id;
        return id;
    }

    OrgTreeNode* addRoot(sem::OrgArg node) {
        auto root = std::make_unique<OrgTreeNode>(add(node), nullptr);
        root->buildTree(root.get(), this);
        this->roots.push_back(std::move(root));
        return roots.back().get();
    }

    sem::SemId<sem::Org> node(CR<OrgBoxId> id) const {
        return data.at(id).node();
    }


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
        emit boxReplaced(prev, result);
        return result;
    }

  signals:
    void boxReplaced(OrgBoxId prev, OrgBoxId replace);
};
