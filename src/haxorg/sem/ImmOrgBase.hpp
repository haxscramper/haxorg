#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"

#include <hstd/stdlib/dod_base.hpp>
#include <haxorg/sem/SemOrgBase.hpp>
#include <hstd/stdlib/Time.hpp>

#include <immer/vector.hpp>
#include <immer/box.hpp>
#include <immer/map.hpp>

template <typename T>
using ImmVec = immer::vector<T>;

template <typename T>
using ImmBox = immer::box<T>;

template <typename K, typename V>
using ImmMap = immer::map<K, V>;

template <typename T>
struct std::formatter<ImmBox<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ImmBox<T>& p, FormatContext& ctx) const {
        fmt_ctx("Box{", ctx);
        fmt_ctx(p.get(), ctx);
        return fmt_ctx("}", ctx);
    }
};

template <>
struct std::formatter<ImmBox<std::string>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ImmBox<std::string>& p, FormatContext& ctx) const {
        fmt_ctx("Box{", ctx);
        fmt_ctx(escape_literal(p.get()), ctx);
        return fmt_ctx("}", ctx);
    }
};

template <>
struct std::formatter<ImmBox<Str>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ImmBox<Str>& p, FormatContext& ctx) const {
        fmt_ctx("Box{", ctx);
        fmt_ctx(escape_literal(p.get()), ctx);
        return fmt_ctx("}", ctx);
    }
};


template <typename T>
struct std::formatter<ImmVec<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(ImmVec<T> const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        fmt.format("[", ctx);
        fmt.format(join(", ", p), ctx);
        return fmt.format("]", ctx);
    }
};

template <typename K, typename V>
struct std::formatter<ImmMap<K, V>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        ImmMap<K, V> const& p,
        FormatContext&      ctx) const {
        std::formatter<std::string> fmt;
        fmt.format("{", ctx);
        bool first = true;
        for (const auto& [key, value] : p) {
            if (!first) { fmt.format(", ", ctx); }
            first = false;
            fmt_ctx(key, ctx);
            fmt.format(": ", ctx);
            fmt_ctx(value, ctx);
        }
        return fmt.format("}", ctx);
    }
};


namespace org {

#define forward_declare(__Kind) struct Imm##__Kind;
EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare

struct ContextStore;
struct ImmOrg;

template <typename T>
struct ImmIdT;

static const u64 ImmIdMaskSize   = 4 * 6;
static const u64 ImmIdMaskOffset = 8 * 8 - ImmIdMaskSize;
using ImmIdBase                  = dod::
    Id<u64, u64, std::integral_constant<u64, ImmIdMaskSize>>;

struct ImmId : ImmIdBase {
    using IdType    = u64;
    using NodeIdxT  = u32;
    using StoreIdxT = u32;

    static const u64 NodeIdxMask;
    static const u64 NodeIdxOffset;
    static const u64 NodeKindMask;
    static const u64 NodeKindOffset;
    static const u64 StoreIdxMask;
    static const u64 StoreIdxOffset;

    // clang-format off
    static StoreIdxT  getStoreIndex(IdType id) { return StoreIdxT((id & StoreIdxMask) >> StoreIdxOffset); }
    static NodeIdxT   getNodeIdx(IdType id)    { return NodeIdxT((id & NodeIdxMask) >> NodeIdxOffset); }
    static OrgSemKind getKind(IdType id)       { return OrgSemKind((id & NodeKindMask) >> NodeKindOffset); }
    // clang-format on

    static IdType combineMask(StoreIdxT store, OrgSemKind kind);

    static IdType combineFullValue(
        StoreIdxT  store,
        OrgSemKind kind,
        NodeIdxT   node);

    static ImmId Nil() {
        auto res = ImmId(0, OrgSemKind(0), 0);
        return res;
    }

    ImmId() : ImmIdBase{0} {};
    ImmId(ImmIdBase const& base) : ImmIdBase{base} {};

    ImmId(StoreIdxT storeIndex, OrgSemKind kind, NodeIdxT nodeIndex)
        : ImmIdBase{combineFullValue(storeIndex, kind, nodeIndex)} {}

    OrgSemKind getKind() const { return ImmId::getKind(value); }
    bool       is(OrgSemKind kind) const;

    /// \brief Get index of the node in associated kind store. NOTE: The
    /// node must not be nil
    NodeIdxT getNodeIndex() const { return ImmId::getNodeIdx(value); }

    /// \brief Get index of an associated local store
    StoreIdxT getStoreIndex() const { return ImmId::getStoreIndex(value); }

    /// \brief Convert this node to one with specified kind
    template <typename T>
    ImmIdT<T> as() const {
        if constexpr (!std::is_abstract_v<T>) {
            if (T::staticKind != getKind()) {
                throw std::logic_error(
                    fmt("Kind for type T '{}' != ID kind '{}'",
                        T::staticKind,
                        getKind()));
            }
        }

        return ImmIdT<T>{*this};
    }

    /// \brief non-nil nodes are converter to `true`
    operator bool() const { return !isNil(); }

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
    ImmIdT() : ImmId(ImmId::Nil()) {}

    static ImmIdT<T> Nil() { return ImmIdT<T>(ImmId::Nil()); }
};


struct ImmOrg {
    ImmVec<ImmId>      subnodes;
    virtual OrgSemKind getKind() const = 0;

    auto begin() const { return subnodes.begin(); }
    auto end() const { return subnodes.end(); }

    bool is(OrgSemKind kind) const { return getKind() == kind; }

    template <typename T>
    T const* dyn_cast() const {
        return dynamic_cast<T const*>(this);
    }

    template <typename T>
    T const* as() const {
        auto res = dyn_cast<T>();
        if (res == nullptr) {
            if constexpr (std::is_abstract_v<T>) {
                throw std::logic_error(
                    fmt("Cannot cast node of kind {}", this->getKind()));
            } else {
                throw std::logic_error(
                    fmt("Cannot cast node of kind {} to kind {}",
                        this->getKind(),
                        T::staticKind));
            }
        }
        return res;
    }

    DESC_FIELDS(ImmOrg, (subnodes));
};

} // namespace org

template <>
struct std::formatter<org::ImmId> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::ImmId& p, FormatContext& ctx) const {
        return fmt_ctx(p.getReadableId(), ctx);
    }
};
