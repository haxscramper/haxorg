#pragma once

import hstd.system.basic_typedefs;
import org.sem.SemOrgEnums;

import hstd.stdlib.Str;
import hstd.stdlib.Func;
import hstd.stdlib.IntSet;
import hstd.stdlib.Opt;

import hstd.system.Formatter;
import org.parse.OrgTypes;
import hstd.system.reflection;

import hstd.stdlib.Vec;

using SemSet = IntSet<OrgSemKind>;

namespace sem {

struct TreeId {
    Str id;
};

BOOST_DESCRIBE_STRUCT(TreeId, (), (id));

// Forward-declare all node types so 'asVariant' can be defined directly
// as a part of `Org` API
#define forward_declare(__Kind) struct __Kind;
EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare


struct Org;

template <typename T>
struct SemIdT;

#define COMMA ,
#define SKIP_FIRST_ARG_AUX(op, ...) __VA_ARGS__
#define SKIP_FIRST_ARG(op, ...) SKIP_FIRST_ARG_AUX(op)

#define EACH_SEM_ORG_KIND_CSV(__CMD)                                      \
    SKIP_FIRST_ARG(EACH_SEM_ORG_KIND(__CMD))


#define __id(I) , SemIdT<I>
/// \brief Global variant of all sem node derivations
using OrgVariant = std::variant<EACH_SEM_ORG_KIND_CSV(__id)>;
#undef __id

struct ContextStore;

struct SemValue {
    int         getInt() const;
    std::string getString() const;
    bool        getBool() const;
    std::string value;
};

struct SemId {
    using IdType          = u64;
    using NodeIndexT      = u32;
    using StoreIndexT     = u32;
    ContextStore* context = nullptr;

    IdType id = 0;
    bool   isNil() const { return id == 0; }

    bool operator==(SemId const& other) const { return id == other.id; }

    static SemId Nil() {
        auto res = SemId(0, OrgSemKind(0), 0, nullptr);
        res.id   = 0;
        return res;
    }

    SemId(
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
    Org*       get();
    Org const* get() const;
    Org*       operator->() { return get(); }
    Org const* operator->() const { return get(); }

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
    void push_back(SemId sub);

    /// \brief Convert this node to one with specified kind
    template <typename T>
    SemIdT<T> as() const;

    /// \brief Convert the node to corresponding variant type.
    ///
    /// Intented to be used with custom `std::visit` solutions instead of
    /// relying on the more heavyweight CRTP visitator.
    OrgVariant asVariant();


    /// \brief Get parent node ID for the node pointed to by this ID
    SemId      getParent() const;
    Vec<SemId> getParentChain(bool withSelf = false) const;

    /// \brief non-nil nodes are converter to `true`
    operator bool() const { return !isNil(); }


    using SubnodeVisitor = Func<void(SemId)>;
    /// \brief Recursively visit each subnode in the tree and apply the
    /// provided callback
    void eachSubnodeRec(SubnodeVisitor cb);

    std::string getReadableId() const {
        return std::format(
            "{}_{}_{}", getStoreIndex(), getKind(), getNodeIndex());
    }
};


/// \brief Derived node for more explicit APIs
///
/// This node is supposed to be used as a mechanism for CRTP overloading
/// (each node has its own ID) and for providing more explicit interfaces.
/// Otherwise it is a thin wrapper on top of the baseline sem ID
/// functionality.
template <typename T>
struct SemIdT : public SemId {
    SemId toId() const { return *this; }
    SemIdT(SemId base) : SemId(base) {}

    T*       operator->() { return get(); }
    T const* operator->() const { return get(); }
    T*       get() { return static_cast<T*>(SemId::get()); }
    T const* get() const { return static_cast<T const*>(SemId::get()); }
    static SemIdT<T> Nil() { return SemIdT<T>(SemId::Nil()); }
};

template <typename T>
struct DefaultSemId {
    SemIdT<T> id = SemIdT<T>::Nil();
    DefaultSemId() {}
    DefaultSemId(SemIdT<T> id) : id(id) {}
    operator SemIdT<T>() const { return id; }
};


/// \brief Base class for all org nodes. Provides essential baseline API
/// and information.
struct Org {
    // TODO implement 'deepClone' function using visitator node to
    // completely replicate the tree on a structural level

    /// \brief Check if node has a parent pointer (for converted tree only
    /// top-level document should not have parent)
    inline bool hasParent() const { return !parent.isNil(); }
    /// \brief Get parent pointer (might be null)
    SemId getParent() const { return parent; }
    /// \brief Get the document wrapping the node (if such document node
    /// exists in hierarchy)
    Opt<SemIdT<Document>> getDocument() const;
    /// \brief Get closest parent subtree (if it exists)
    Opt<SemIdT<Subtree>> getParentSubtree() const;
    /// \brief Iteratively get all parent nodes for the subtree
    Vec<SemId> getParentChain() const;


    /// \brief Pointer to the parent node in sem tree, might be null.
    SemId                parent           = SemId::Nil();
    Opt<OrgSemPlacement> placementContext = std::nullopt;
    /// \brief Adapter to the original parsed node.
    ///
    /// Set by the conversion functions from linearized representation,
    /// will be missing for all generated node kinds.
    OrgAdapter original;

    Org() : parent(SemId::Nil()) {}
    Org(SemId parent, CVec<SemId> subnodes);
    Org(SemId parent);
    Org(SemId parent, OrgAdapter original);

    /// \brief Get get kind of the original node.
    OrgNodeKind getOriginalKind() const { return original.getKind(); }
    /// \brief Get kind of this sem node
    virtual OrgSemKind getKind() const = 0;
    /// \brief Whether original node adapter is missing
    bool isGenerated() const { return original.empty(); }
    /// \brief Location of the node in the original source file
    Opt<LineCol> loc = std::nullopt;
    /// \brief List of subnodes.
    ///
    /// Some of the derived nodes don't make the use of subnode list
    /// (word, punctuation etc), but it was left on the top level of the
    /// hierarchy for conveinience purposes. It is not expected that 'any'
    /// node can have subnodes.
    Vec<SemId> subnodes;

    void push_back(SemId sub);

    /// \brief Get subnode at specified index
    inline SemId at(int idx) const { return subnodes[idx]; }

    bool is(OrgSemKind kind) const { return getKind() == kind; }
    bool is(CR<SemSet> kinds) const { return kinds.contains(getKind()); }

    BOOST_DESCRIBE_CLASS(Org, (), (subnodes), (), ());
};


}; // namespace sem

#define EACH_SEM_ORG_LEAF_KIND(__IMPL)                                    \
    __IMPL(Newline)                                                       \
    __IMPL(Space)                                                         \
    __IMPL(Word)                                                          \
    __IMPL(RawText)                                                       \
    __IMPL(Punctuation)                                                   \
    __IMPL(Placeholder)                                                   \
    __IMPL(BigIdent)

template <>
struct std::formatter<sem::SemId> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(const sem::SemId& p, FormatContext& ctx)
        const {
        return fmt_ctx(p.getReadableId(), ctx);
    }
};

template <typename T>
struct std::formatter<sem::SemIdT<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(const sem::SemId& p, FormatContext& ctx)
        const {
        return fmt_ctx(p.getReadableId(), ctx);
    }
};
