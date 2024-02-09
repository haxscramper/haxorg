#pragma once

#include <hstd/system/basic_typedefs.hpp>
#include <sem/SemOrgEnums.hpp>

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Opt.hpp>

#include <hstd/system/Formatter.hpp>
#include <parse/OrgTypes.hpp>
#include <format>
#include <hstd/system/reflection.hpp>

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
struct SemId;

#define COMMA ,
#define SKIP_FIRST_ARG_AUX(op, ...) __VA_ARGS__
#define SKIP_FIRST_ARG(op, ...) SKIP_FIRST_ARG_AUX(op)

#define EACH_SEM_ORG_KIND_CSV(__CMD)                                      \
    SKIP_FIRST_ARG(EACH_SEM_ORG_KIND(__CMD))


#define __id(I) , SemId<I>
/// \brief Global variant of all sem node derivations
using OrgVariant = std::variant<EACH_SEM_ORG_KIND_CSV(__id)>;
#undef __id

struct SemValue {
    int         getInt() const;
    std::string getString() const;
    bool        getBool() const;
    std::string value;
};

struct Org;

template <typename O>
struct SemId {
    SPtr<O> value;

    bool isNil() const { return value.get() == nullptr; }
    bool operator==(SemId const& other) const {
        return value == other.value;
    }


    template <typename... Args>
    static SemId<O> New(Args&&... args) {
        return std::make_shared<O>(std::forward(args)...);
    }

    static SemId Nil() { return SemId(nullptr); }

    SemId() { value = nullptr; }
    SemId(SPtr<O> const& value) : value(value) {}
    SemId(O* value) : value(value) {}

    operator SemId<Org>() {
        return SemId<Org>{std::shared_ptr<Org>(value)};
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
    O*              get();
    O const*        get() const;
    O*              operator->() { return get(); }
    O const*        operator->() const { return get(); }
    SemId<sem::Org> asOrg() const { return as<sem::Org>(); }

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
    SemId<T> as() const {
        if constexpr (!std::is_abstract_v<T>) {
            CHECK(value->getKind() == T::staticKind);
        }
        return SemId<T>{std::dynamic_pointer_cast<T>(value)};
    }

    /// \brief Get parent node ID for the node pointed to by this ID
    SemId      getParent() const;
    Vec<SemId> getParentChain(bool withSelf = false) const;

    /// \brief non-nil nodes are converter to `true`
    operator bool() const { return !isNil(); }


    using SubnodeVisitor = Func<void(SemId)>;
    /// \brief Recursively visit each subnode in the tree and apply the
    /// provided callback
    void eachSubnodeRec(SubnodeVisitor cb);
};


template <typename T>
struct remove_sem_org {
    using type = remove_smart_pointer<T>;
};

template <typename T>
struct remove_sem_org<SemId<T>> {
    using type = remove_smart_pointer<T>;
};

sem::OrgVariant asVariant(SemId<Org> in);

/// \brief Base class for all org nodes. Provides essential baseline API
/// and information.
struct Org {
    /// \brief Adapter to the original parsed node.
    ///
    /// Set by the conversion functions from linearized representation,
    /// will be missing for all generated node kinds.
    OrgAdapter original;

    Org(CVec<SemId<Org>> subnodes);
    Org();
    Org(OrgAdapter original);

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
    Vec<SemId<Org>> subnodes;

    void push_back(SemId<Org> sub);

    /// \brief Get subnode at specified index
    inline SemId<Org> at(int idx) const { return subnodes[idx]; }

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
struct std::formatter<sem::SemId<sem::Org>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const sem::SemId<sem::Org>& p,
        FormatContext&              ctx) const {
        return fmt_ctx(p->getKind(), ctx);
    }
};

template <typename T>
struct std::formatter<sem::SemId<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const sem::SemId<sem::Org>& p,
        FormatContext&              ctx) const {
        return fmt_ctx(p->getKind(), ctx);
    }
};
