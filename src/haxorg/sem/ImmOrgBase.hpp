#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"

#include <hstd/stdlib/dod_base.hpp>
#include <haxorg/sem/SemOrgBase.hpp>
#include <hstd/stdlib/Time.hpp>

#include <immer/vector.hpp>
#include <immer/box.hpp>
#include <immer/map.hpp>
#include <immer/set.hpp>
#include <immer/flex_vector.hpp>
#include <hstd/stdlib/Json.hpp>

template <typename T>
using ImmVec = immer::flex_vector<T>;

template <typename T>
using ImmBox = immer::box<T>;

template <typename K, typename V>
struct ImmMap : immer::map<K, V> {
    using base = immer::map<K, V>;
    using base::at;
    using base::base;
    using base::find;

    ImmMap(base const& val) : base{val} {}

    Opt<V> get(K const& key) const {
        if (auto val = find(key)) {
            return *val;
        } else {
            return std::nullopt;
        }
    }

    bool contains(K const& key) const { return find(key) != nullptr; }
};

template <typename T>
using ImmSet = immer::set<T>;


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

template <typename T>
struct JsonSerde<ImmVec<T>> {
    static json to_json(ImmVec<T> const& it) {
        auto result = json::array();
        for (auto const& i : it) {
            result.push_back(JsonSerde<T>::to_json(i));
        }

        return result;
    }
    static ImmVec<T> from_json(json const& j) {
        ImmVec<T> result;
        auto      tmp = result.transient();
        for (auto const& i : j) {
            tmp.push_back(JsonSerde<T>::from_json(i));
        }
        return tmp.persistent();
    }
};

template <typename T>
struct JsonSerde<ImmSet<T>> {
    static json to_json(ImmSet<T> const& it) {
        auto result = json::array();
        for (auto const& i : it) {
            result.push_back(JsonSerde<T>::to_json(i));
        }

        return result;
    }
    static ImmSet<T> from_json(json const& j) {
        ImmSet<T> result;
        auto      tmp = result.transient();
        for (auto const& i : j) {
            result.insert(JsonSerde<T>::from_json(i));
        }
        return tmp.persistent();
    }
};

template <typename T>
struct std::formatter<ImmSet<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(ImmSet<T> const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        fmt.format("{", ctx);
        fmt.format(join(", ", p), ctx);
        return fmt.format("}", ctx);
    }
};

template <typename K, typename V>
using ImmMapTransientDefault = immer::map_transient<
    K,
    V,
    /*Hash        =*/std::hash<K>,
    /*Equal       =*/std::equal_to<K>,
    /*MemoryPolicy=*/immer::default_memory_policy,
    /*B           =*/immer::default_bits>;

template <typename K, typename V, typename Type>
struct std_kv_tuple_iterator_formatter : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(Type const& p, FormatContext& ctx)
        const {
        fmt_ctx("{", ctx);
        bool first = true;
        for (const auto& [key, value] : p) {
            if (!first) { fmt_ctx(", ", ctx); }
            first = false;
            fmt_ctx(key, ctx);
            fmt_ctx(": ", ctx);
            fmt_ctx(value, ctx);
        }
        return fmt_ctx("}", ctx);
    }
};


template <typename K, typename V>
struct std::formatter<ImmMapTransientDefault<K, V>>
    : std_kv_tuple_iterator_formatter<K, V, ImmMapTransientDefault<K, V>> {
};

template <typename K, typename V>
struct std::formatter<ImmMap<K, V>>
    : std_kv_tuple_iterator_formatter<K, V, ImmMap<K, V>> {};

template <typename K, typename V>
struct std::formatter<immer::map<K, V>>
    : std_kv_tuple_iterator_formatter<K, V, immer::map<K, V>> {};


template <typename K, typename V>
struct JsonSerde<immer::map<K, V>> {
    static json to_json(immer::map<K, V> const& it) {
        auto result = json::array();
        for (auto const& [key, val] : it) {
            result.push_back(json::object({
                {"key", JsonSerde<K>::to_json(key)},
                {"value", JsonSerde<V>::to_json(val)},
            }));
        }

        return result;
    }
    static immer::map<K, V> from_json(json const& j) {
        immer::map<K, V> result;
        auto             tmp = result.transient();
        for (auto const& i : j) {
            result.insert(
                JsonSerde<K>::from_json(i["key"]),
                JsonSerde<V>::from_json(i["value"]));
        }
        return tmp.persistent();
    }
};

template <typename K, typename V>
struct JsonSerde<ImmMap<K, V>> {
    static json to_json(ImmMap<K, V> const& it) {
        return JsonSerde<immer::map<K, V>>::to_json(it);
    }
    static ImmMap<K, V> from_json(json const& j) {
        return JsonSerde<immer::map<K, V>>::from_json(j);
    }
};


namespace org {

#define forward_declare(__Kind) struct Imm##__Kind;
EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare

struct ImmAstContext;
struct ImmOrg;

template <typename T>
struct ImmIdT;

static const u64 ImmIdMaskSize   = 4 * 6;
static const u64 ImmIdMaskOffset = 8 * 8 - ImmIdMaskSize;
using ImmIdBase                  = dod::
    Id<u64, u64, std::integral_constant<u64, ImmIdMaskSize>>;

struct ImmId : ImmIdBase {
    using IdType   = u64;
    using NodeIdxT = u32;

    static const u64 NodeIdxMask;
    static const u64 NodeIdxOffset;
    static const u64 NodeKindMask;
    static const u64 NodeKindOffset;

    // clang-format off
    static NodeIdxT   getNodeIdx(IdType id)    { return NodeIdxT((id & NodeIdxMask) >> NodeIdxOffset); }
    static OrgSemKind getKind(IdType id)       { return OrgSemKind((id & NodeKindMask) >> NodeKindOffset); }
    // clang-format on

    static IdType combineMask(OrgSemKind kind);

    static IdType combineFullValue(OrgSemKind kind, NodeIdxT node);

    static ImmId Nil() {
        auto res = ImmId::FromValue(0);
        return res;
    }

    ImmId() : ImmIdBase{0} {};
    static ImmId FromValue(u64 value) {
        return ImmId{ImmIdBase::FromValue(value)};
    }
    ImmId(ImmIdBase const& base) : ImmIdBase{base} {};

    ImmId(OrgSemKind kind, NodeIdxT nodeIndex)
        : ImmIdBase{combineFullValue(kind, nodeIndex)} {}

    OrgSemKind getKind() const { return ImmId::getKind(value); }
    bool       is(OrgSemKind kind) const { return getKind() == kind; }

    /// \brief Get index of the node in associated kind store. NOTE: The
    /// node must not be nil
    NodeIdxT getNodeIndex() const { return ImmId::getNodeIdx(value); }

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

    std::string getReadableId() const;

    void assertValid() const;
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

    ImmId at(int pos) const { return subnodes.at(pos); }
    auto  begin() const { return subnodes.begin(); }
    auto  end() const { return subnodes.end(); }
    int   size() const { return subnodes.size(); }
    int   indexOf(org::ImmId subnode) const {
        for (int i = 0; i < subnodes.size(); ++i) {
            if (subnodes.at(i) == subnode) { return i; }
        }
        return -1;
    }

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


template <>
struct JsonSerde<org::ImmId> {
    static json to_json(org::ImmId const& it) {
        return json::object(
            {{"number", it.getValue()}, {"format", it.getReadableId()}});
    }
    static org::ImmId from_json(json const& j) {
        return org::ImmId::FromValue(
            j["number"].get<unsigned long long>());
    }
};
