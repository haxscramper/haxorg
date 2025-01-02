#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"

#include <hstd/system/basic_typedefs.hpp>
#include <haxorg/sem/SemOrgEnums.hpp>

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Opt.hpp>

#include <hstd/system/Formatter.hpp>
#include <haxorg/parse/OrgTypes.hpp>
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
using OrgIdVariant = std::variant<EACH_SEM_ORG_KIND_CSV(__id)>;
#undef __id

#define __ptr(I) , I*
/// \brief Global variant of all sem node derivations
using OrgPtrVariant = std::variant<EACH_SEM_ORG_KIND_CSV(__ptr)>;
#undef __ptr

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
        return std::make_shared<O>(std::forward<Args>(args)...);
    }

    static SemId Nil() { return SemId(SPtr<O>{}); }

    SemId() { value = nullptr; }
    SemId(SPtr<O> const& value) : value(value) {}
    SemId(O* value) : value(value) {}

    operator SemId<Org>() { return asOrg(); }

    /// \name Get pointer to the associated sem org node from ID
    ///
    /// {@
    O*              get() { return value.get(); }
    O const*        get() const { return value.get(); }
    O*              operator->() { return get(); }
    O const*        operator->() const { return get(); }
    O&              operator*() { return *value; }
    O const&        operator*() const { return *value; }
    SemId<sem::Org> asOrg() const { return as<sem::Org>(); }

    SemId<sem::Org> at(int idx) { return value->at(idx); }
    SemId<sem::Org> at(BackwardsIndex idx) { return value->at(idx); }

    SemId<sem::Org> get(int idx) { return value->get(idx); }
    SemId<sem::Org> get(BackwardsIndex idx) { return value->get(idx); }

    using SubnodeVec = Vec<SemId<sem::Org>>;

    SubnodeVec::iterator       begin() { return value->subnodes.begin(); }
    SubnodeVec::iterator       end() { return value->subnodes.end(); }
    SubnodeVec::const_iterator begin() const {
        return value->subnodes.begin();
    }
    SubnodeVec::const_iterator end() const {
        return value->subnodes.end();
    }

    int size() const { return value->subnodes.size(); }

    template <typename T>
    SemId<T> asOpt() const {
        if constexpr (std::is_abstract_v<T>) {
            auto dyna = getAs<T>();
            if (dyna == nullptr) {
                return SemId<T>::Nil();
            } else {
                return as<T>();
            }

        } else {

            if (isNil() || value->getKind() != T::staticKind) {
                return SemId<T>::Nil();
            } else {
                return as<T>();
            }
        }
    }

    template <typename T>
    T* getAs() {
        return dynamic_cast<T*>(get());
    }

    template <typename T>
    T const* getAs() const {
        return dynamic_cast<T const*>(get());
    }
    /// @}

    /// \brief Convert this node to one with specified kind
    template <typename T>
    SemId<T> as() const {
        if constexpr (!std::is_abstract_v<T>) {
            CHECK(value->getKind() == T::staticKind);
        }
        return SemId<T>{std::dynamic_pointer_cast<T>(value)};
    }

    template <typename T>
    Vec<SemId<T>> subAs() const {
        return value->template subAs<T>();
    }

    /// \brief non-nil nodes are converter to `true`
    operator bool() const { return !isNil(); }
};

using OrgArg = sem::SemId<sem::Org> const&;

template <typename T>
struct remove_sem_org {
    using type = remove_smart_pointer<T>::type;
};

template <typename T>
struct remove_sem_org<SemId<T>> {
    using type = remove_smart_pointer<T>::type;
};

sem::OrgIdVariant  asVariant(SemId<Org> in);
sem::OrgPtrVariant asVariant(Org* in);

/// \brief Base class for all org nodes. Provides essential baseline API
/// and information.
struct [[refl]] Org {
    /// \brief Adapter to the original parsed node.
    ///
    /// Set by the conversion functions from linearized representation,
    /// will be missing for all generated node kinds.
    OrgAdapter original;

    Org(CVec<SemId<Org>> subnodes);
    Org();
    Org(OrgAdapter original);
    virtual ~Org() = default;

    /// \brief Get get kind of the original node.
    OrgNodeKind getOriginalKind() const { return original.getKind(); }
    /// \brief Get kind of this sem node
    [[refl]] virtual OrgSemKind getKind() const = 0;
    /// \brief Whether original node adapter is missing
    [[refl]] bool isGenerated() const { return original.isNil(); }
    /// \brief Location of the node in the original source file
    [[refl]] Opt<LineCol> loc = std::nullopt;
    /// \brief Application specific ID of the original document
    [[refl]] Opt<int> documentId = std::nullopt;
    /// \brief List of subnodes.
    ///
    /// Some of the derived nodes don't make the use of subnode list
    /// (word, punctuation etc), but it was left on the top level of the
    /// hierarchy for conveinience purposes. It is not expected that 'any'
    /// node can have subnodes.
    [[refl]] Vec<SemId<Org>> subnodes;

    [[refl]] void push_back(SemId<Org> sub);

    using SubnodeVec = Vec<SemId<Org>>;

    SubnodeVec::iterator       begin() { return subnodes.begin(); }
    SubnodeVec::iterator       end() { return subnodes.end(); }
    SubnodeVec::const_iterator begin() const { return subnodes.begin(); }
    SubnodeVec::const_iterator end() const { return subnodes.end(); }

    [[refl]] void insert(int pos, SemId<Org> node) {
        subnodes.insert(begin() + pos, node);
    }

    template <typename T>
    T* dyn_cast() {
        return dynamic_cast<T*>(this);
    }

    template <typename T>
    T const* dyn_cast() const {
        return dynamic_cast<T const*>(this);
    }

    /// \brief Get subnode at specified index
    [[refl]] inline SemId<Org> at(int idx) const {
        return subnodes.at(idx);
    }

    SemId<Org> as_unref_shared() const;

    SemId<Org> at(BackwardsIndex idx) const { return subnodes.at(idx); }
    Opt<SemId<Org>> get(int idx) const { return subnodes.get(idx); }
    Opt<SemId<Org>> get(BackwardsIndex idx) const {
        return subnodes.get(idx);
    }

    template <typename Func>
    void visit(Func const& cb) {
        switch (getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        cb(dyn_cast<sem::__Kind>());                                      \
        break;                                                            \
    }

            EACH_SEM_ORG_KIND(_case)
#undef _case
        }
    }

    template <typename Func>
    void visit(Func const& cb) const {
        switch (getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        cb(dyn_cast<sem::__Kind>());                                      \
        break;                                                            \
    }

            EACH_SEM_ORG_KIND(_case)
#undef _case
        }
    }

    [[refl]] bool is(OrgSemKind kind) const { return getKind() == kind; }
    bool          is(CR<IntSet<OrgSemKind>> kinds) const {
        return kinds.contains(getKind());
    }

    Vec<SemId<Org>> getAllSubnodes() const;

    template <typename T>
    Vec<SemId<T>> subAs() const {
        Vec<SemId<T>> result;
        for (auto const& sub : subnodes) {
            if (sub->getKind() == T::staticKind) {
                result.push_back(sub.template as<T>());
            }
        }
        return result;
    }

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
        const sem::SemId<T>& p,
        FormatContext&       ctx) const {
        if (p.isNil()) {
            return fmt_ctx("<nil>", ctx);
        } else {
            return fmt_ctx(p->getKind(), ctx);
        }
    }
};
