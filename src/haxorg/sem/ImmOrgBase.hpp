#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"

#include <hstd/stdlib/dod_base.hpp>
#include <immer/vector.hpp>
#include <haxorg/sem/SemOrgBase.hpp>

namespace org {


struct ContextStore;
struct ImmOrg;

template <typename T>
struct ImmIdT;

struct ImmId {
    using IdType          = u64;
    using NodeIndexT      = u32;
    using StoreIndexT     = u32;
    ContextStore* context = nullptr;

    IdType id = 0;
    bool   isNil() const { return id == 0; }

    bool operator==(ImmId const& other) const { return id == other.id; }

    static ImmId Nil() {
        auto res = ImmId(0, OrgSemKind(0), 0, nullptr);
        res.id   = 0;
        return res;
    }

    ImmId(
        StoreIndexT   storeIndex,
        OrgSemKind    kind,
        NodeIndexT    nodeIndex,
        ContextStore* _store)
        : context(_store) {
        setStoreIndex(storeIndex);
        setKind(kind);
        setNodeIndex(nodeIndex);
    }

    OrgSemKind getKind() const { return OrgSemKind((id >> 32) & 0xFF); }
    bool       is(OrgSemKind kind) const;

    /// \brief Get index of the node in associated kind store. NOTE: The
    /// node must not be nil
    NodeIndexT getNodeIndex() const {
        assert(!isNil());
        return (id & 0xFFFFFFFF) - 1;
    }

    /// \brief Get index of an associated local store
    StoreIndexT getStoreIndex() const { return id >> 40; }

    /// \brief Set store index for ID.
    ///
    /// Should only be used if two stores are to be merged and nested IDs
    /// updated, in other cases store is considered fixed.
    void setStoreIndex(StoreIndexT storeIndex) {
        id = (id & 0x000000FFFFFFFFFF) | ((IdType)storeIndex << 40);
    }

    void setKind(OrgSemKind kind) {
        id = (id & 0xFFFFFF00FFFFFFFF) | ((IdType)kind << 32);
    }

    void setNodeIndex(NodeIndexT nodeIndex) {
        id = (id & 0xFFFFFFFF00000000) | (nodeIndex + 1);
    }

    /// \name Get pointer to the associated sem org node from ID
    ///
    /// \warning Resulting pointers are *not* stable -- underlying store
    /// content is subject to relocation and as such pointers are bound to
    /// be invalidated if the new nodes are added. The pattern of `ptr =
    /// node.get() ... add nodes ... ptr->something` will lead to subtle
    /// bugs with dangling pointers and should be avoided. Instead
    /// `node->whatever ... add nodes ... node->whatever` must be used. For
    /// the same reason storing pointers in containers is discouraged.
    ///
    /// {@
    ImmOrg const* get() const;
    ImmOrg const* operator->() const { return get(); }

    template <typename T>
    T* getAs() {
        return dynamic_cast<T*>(get());
    }

    template <typename T>
    T const* getAs() const {
        return dynamic_cast<T const*>(get());
    }
    /// @}

    /// \brief Add new subnode
    ///
    /// \note This method *must* be used instead of the
    /// `id->push_back(convert())` and similar because otherwise it might
    /// cause dangling pointers due to the following sequence: (1) `->` is
    /// evaluated, (2) `convert()` is evaluated, (3) `push_back` is called
    /// on the pointer created earlier, which might be invalidated due to
    /// relocation in p2
    void push_back(ImmId sub);

    /// \brief Convert this node to one with specified kind
    template <typename T>
    ImmIdT<T> as() const;

    /// \brief Get parent node ID for the node pointed to by this ID
    ImmId      getParent() const;
    Vec<ImmId> getParentChain(bool withSelf = false) const;

    /// \brief non-nil nodes are converter to `true`
    operator bool() const { return !isNil(); }


    using SubnodeVisitor = Func<void(ImmId)>;
    /// \brief Recursively visit each subnode in the tree and apply the
    /// provided callback
    void eachSubnodeRec(SubnodeVisitor cb);

    std::string getReadableId() const {
        if (isNil()) {
            return "nil";
        } else {
            return std::format(
                "{}_{}_{}", getStoreIndex(), getKind(), getNodeIndex());
        }
    }
};

template <typename T>
struct ImmIdT : public ImmId {
    ImmId toId() const { return *this; }
    ImmIdT(ImmId base) : ImmId(base) {}

    T*       operator->() { return get(); }
    T const* operator->() const { return get(); }
    T*       get() { return static_cast<T*>(ImmId::get()); }
    T const* get() const { return static_cast<T const*>(ImmId::get()); }
    static ImmIdT<T> Nil() { return ImmIdT<T>(ImmId::Nil()); }
};


template <typename T>
struct KindStore {
    ContextStore* context;
    using NodeType = T;
    Vec<T> values;

    int size() const { return values.size(); }

    KindStore(ContextStore* context) : context(context) {}

    T* getForIndex(ImmId::NodeIndexT index) {
        CHECK(0 <= index && index < values.size());
        return &values.at(index);
    }

    ImmId create(
        ImmId::StoreIndexT selfIndex,
        ImmId              parent,
        Opt<OrgAdapter>    original,
        ContextStore*      context);

    using StoreVisitor = Func<
        void(ImmId::StoreIndexT selfIndex, KindStore<T>* store)>;

    using NodeVisitor = Func<void(ImmIdT<T> node)>;

    generator<ImmIdT<T>> nodes(ImmId::StoreIndexT selfIndex) {
        for (ImmId::NodeIndexT node = 0; node < values.size(); ++node) {
            co_yield ImmIdT<T>(
                ImmId(selfIndex, T::staticKind, node, context));
        }
    }

    void eachNode(ImmId::StoreIndexT selfIndex, CR<NodeVisitor> cb) {
        for (const auto& id : nodes(selfIndex)) { cb(id); }
    }
};

#define __id(I) , org::KindStore<org::Imm##I>*
/// \brief Global variant of all sem node derivations
using OrgKindStorePtrVariant = std::variant<EACH_SEM_ORG_KIND_CSV(__id)>;
#undef __id


struct ParseUnitStore {
#define _kind(__Kind) KindStore<Imm##__Kind> store##__Kind;
    EACH_SEM_ORG_KIND(_kind)
#undef _kind


    ParseUnitStore(ContextStore* context)
        :
#define _kind(__Kind) , store##__Kind(context)
        EACH_SEM_ORG_KIND_CSV(_kind)
#undef _kind
    {
    }

    Org*  get(OrgSemKind kind, ImmId::NodeIndexT index);
    ImmId create(
        ImmId::StoreIndexT selfIndex,
        OrgSemKind         kind,
        ImmId              parent,
        ContextStore*      context,
        Opt<OrgAdapter>    original = std::nullopt);

    using StoreVisitor = Func<
        void(ImmId::StoreIndexT selfIndex, OrgKindStorePtrVariant store)>;

    using NodeVisitor = Func<void(OrgVariant node)>;

    void eachStore(ImmId::StoreIndexT selfIndex, StoreVisitor cb);
    void eachNode(ImmId::StoreIndexT selfIndex, NodeVisitor cb);
};

/// \brief Global group of stores that all nodes are written to
struct ContextStore {
    /// \brief Get reference to a local store by index
    ParseUnitStore& getStoreByIndex(ImmId::StoreIndexT index);
    void            ensureStoreForIndex(ImmId::StoreIndexT index);

    /// \brief Create new sem node of the specified kind in the local store
    /// with `index`
    ImmId createIn(
        ImmId::StoreIndexT index,
        OrgSemKind         kind,
        ImmId              parent,
        Opt<OrgAdapter>    original = std::nullopt);


    /// \brief Create new sem node of the specified kind in the same local
    /// store as the `existing` node
    ImmId createInSame(
        ImmId           existing,
        OrgSemKind      kind,
        ImmId           parent,
        Opt<OrgAdapter> original = std::nullopt);


    Vec<ParseUnitStore> stores;

    void eachStore(ParseUnitStore::StoreVisitor cb);
    void eachNode(ParseUnitStore::NodeVisitor cb);

    ContextStore() {}
    ContextStore(const ContextStore&)            = delete;
    ContextStore& operator=(const ContextStore&) = delete;
};


} // namespace org
