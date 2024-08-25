#pragma once

#include <QMimeData>
#include <QIODevice>

#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/Map.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
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

    template <typename T>
    sem::SemId<T> getBoxedNodeAs() const {
        return getBoxedNode().as<T>();
    }

    Vec<OrgTreeNode*> filterSubnodes(SemSet kind) {
        Vec<OrgTreeNode*> result;
        for (auto const& sub : subnodes) {
            if (kind.contains(sub->getBoxedNode()->getKind())) {
                result.push_back(sub.get());
            }
        }
        return result;
    }

    OrgTreeNode* at(int idx) { return subnodes.at(idx).get(); }

    OrgTreeNode* at(CVec<int> path) {
        auto result = this;
        for (auto const& idx : path) { result = result->at(idx); }
        return result;
    }

    Opt<OrgBoxId> parentId() const {
        if (parent == nullptr) {
            return std::nullopt;
        } else {
            return parent->id();
        }
    }

    OrgBoxId id() const { return this->boxId; }
    OrgBoxId id(int inx) { return at(inx)->boxId; }
    OrgBoxId id(CVec<int> idx) { return at(idx)->boxId; }

    OrgTreeNode* tree(OrgBoxId id);

    sem::SemId<sem::Org> toNode() const;
    void                 buildTree(OrgTreeNode* parentNode);

    Opt<int> selfRow() const;
    Vec<int> selfPath() const;

    struct MoveParams {
        OrgBoxId sourceParent;
        int      sourceFirst;
        int      sourceLast;
        OrgBoxId destinationParent;
        int      destinationRow;
        DESC_FIELDS(
            MoveParams,
            (sourceParent,
             sourceFirst,
             sourceLast,
             destinationParent,
             destinationRow));
    };

    struct InsertParams {
        OrgBoxId parent;
        int      first;
        int      last;
        DESC_FIELDS(InsertParams, (parent, first, last));
    };

    /// \brief Get parameters to insert a new node directly before the
    /// current tree
    InsertParams getInsertAfter();
    /// \brief Get parameters to insert a new node directly after the
    /// current tree
    InsertParams getInsertBefore();
    /// \brief Get parameters to insert a new node as a first subnode of
    /// the current tree
    InsertParams getInsertFirstUnder();
    /// \brief Get parameters to insert a new node as a last subnode of the
    /// current tree
    InsertParams getInsertLastUnder();

    /// \brief Compute move parameters to put this subtree as a subnode of
    /// a new parent at index. Return nullopt if the move is unnecessary
    /// (already at the position).
    Opt<MoveParams> getMoveParams(OrgTreeNode* parent, int index);

    /// \brief Compute move parameters to shift this subtree into a
    /// position `offset` elements from the current one. `+1` will move the
    /// node down, `-1` will move it up etc.
    Opt<MoveParams> getShiftParams(int offset);

    /// \brief Execute the move of the subtree
    void apply(CR<MoveParams> params);
    void apply(CR<Opt<MoveParams>> params) {
        if (params) { apply(*params); }
    }

    /// \brief Insert a new node in given position and return its new box
    /// ID
    void apply(CR<InsertParams> params, UPtr<OrgTreeNode>&& inserted) {
        Vec<UPtr<OrgTreeNode>> vec;
        vec.push_back(std::move(inserted));
        apply(params, std::move(vec));
    }

    /// \brief Insert multiple new nodes at a given position. Emitted
    /// signals adjust the `last` position based on the `inserted` size.
    void apply(CR<InsertParams> params, Vec<UPtr<OrgTreeNode>>&& inserted);

    ColText treeRepr() const;
};

template <>
struct std::formatter<OrgTreeNode*> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(OrgTreeNode const* p, FormatContext& ctx) const {
        return fmt_ctx(fmt("{:p}", (void*)p), ctx);
    }
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

    UPtr<OrgTreeNode> toRoot(sem::OrgArg node) {
        emit beginBatchAdd();
        auto box  = add(node);
        auto root = addTree(box, nullptr);
        root->buildTree(root.get());
        emit endBatchAdd();
        return root;
    }

    UPtr<OrgTreeNode> toRoot(
        CR<fs::path>                path,
        CR<sem::OrgParseParameters> opts = sem::OrgParseParameters{}) {
        return toRoot(sem::parseFile(path, opts));
    }

    UPtr<OrgTreeNode> toRoot(
        CR<Str>                     text,
        CR<sem::OrgParseParameters> opts = sem::OrgParseParameters{}) {
        return toRoot(sem::parseStringOpts(text, opts));
    }

    OrgTreeNode* addRoot(UPtr<OrgTreeNode>&& root) {
        roots.push_back(std::move(root));
        emit rootAdded(roots.high());
        return roots.back().get();
    }

    OrgTreeNode* addRoot(sem::OrgArg node) {
        roots.push_back(toRoot(node));
        emit rootAdded(roots.high());
        return roots.back().get();
    }

    OrgTreeNode* addRoot(
        CR<fs::path>                path,
        CR<sem::OrgParseParameters> opts = sem::OrgParseParameters{}) {
        return addRoot(toRoot(path, opts));
    }

    OrgTreeNode* addRoot(
        CR<Str>                     text,
        CR<sem::OrgParseParameters> opts = sem::OrgParseParameters{}) {
        return addRoot(toRoot(text, opts));
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

    sem::SemId<sem::Org> getBoxedNode(CR<OrgBoxId> id) const {
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
        sem::SemId<sem::Org> node = copy(this->getBoxedNode(prev));
        replace(*node.getAs<T>());
        auto result = add(node);
        auto tree   = nodeLookup.at(prev);
        nodeLookup.erase(prev);
        nodeLookup[result] = tree;
        tree->boxId        = result;
        emit boxReplaced(prev, result);
        return result;
    }

  signals:
    void boxReplaced(OrgBoxId prev, OrgBoxId replace);
    void boxDeleted(OrgBoxId box);
    void boxAdded(OrgBoxId box);

    void beginBatchAdd();
    void endBatchAdd();

    void rootAdded(int index);

    void beginNodeMove(OrgTreeNode::MoveParams params);
    void endNodeMove(OrgTreeNode::MoveParams params);

    void beginNodeInsert(OrgTreeNode::InsertParams params);
    void endNodeInsert(OrgTreeNode::InsertParams params);
};
