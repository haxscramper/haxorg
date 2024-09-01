#pragma once

#include <haxorg/sem/ImmOrgBase.hpp>
#include <haxorg/sem/ImmOrgTypes.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/ColText.hpp>


#define _declare_hash(__kind)                                             \
    template <>                                                           \
    struct std::hash<org::Imm##__kind> {                                  \
        std::size_t operator()(                                           \
            org::Imm##__kind const& it) const noexcept;                   \
    };

EACH_SEM_ORG_KIND(_declare_hash)


namespace org {


template <typename T>
struct KindStore {
    ContextStore* context;
    using NodeType = T;
    dod::InternStore<org::ImmId, T> values;

    int size() const { return values.size(); }

    KindStore(ContextStore* context) : context(context) {}
    void format(
        ColStream&                                  os,
        UnorderedMap<org::ImmId, org::ImmId> const& parents,
        std::string const&                          linePrefix = "") const;

    bool     empty() const { return values.empty(); }
    T const* at(org::ImmId id) const { return &values.at(id); }
    ImmId    add(
           ImmId::StoreIdxT     selfIndex,
           sem::SemId<sem::Org> data,
           ContextStore*        context);
};

#define __id(I) , org::KindStore<org::Imm##I>*
/// \brief Global variant of all sem node derivations
using OrgKindStorePtrVariant = std::variant<EACH_SEM_ORG_KIND_CSV(__id)>;
#undef __id


struct ParseUnitStore {
    UnorderedMap<org::ImmId, org::ImmId> parents;

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

    void       format(ColStream& os, std::string const& prefix = "") const;
    Opt<ImmId> getParent(ImmId id) const { return parents.get(id); }
    Vec<int>   getPath(ImmId id) const;
    Vec<ImmId> getParentChain(ImmId id, bool withSelf = true) const;

    ImmOrg const* at(ImmId index) const;
    ImmId         add(
                ImmId::StoreIdxT     selfIndex,
                sem::SemId<sem::Org> data,
                ContextStore*        context);

    using StoreVisitor = Func<
        void(ImmId::StoreIdxT selfIndex, OrgKindStorePtrVariant store)>;
};

/// \brief Global group of stores that all nodes are written to
struct ContextStore {
    /// \brief Get reference to a local store by index
    ParseUnitStore&       getStoreByIndex(ImmId::StoreIdxT index);
    ParseUnitStore const& getStoreByIndex(ImmId::StoreIdxT index) const;
    ParseUnitStore&       getStoreByIndex(ImmId id) {
        return getStoreByIndex(id.getStoreIndex());
    }

    Opt<ImmId> getParent(ImmId id) const {
        return getStoreByIndex(id.getStoreIndex()).getParent(id);
    }

    ParseUnitStore const& getStoreByIndex(ImmId id) const {
        return getStoreByIndex(id.getStoreIndex());
    }

    Vec<int> getPath(ImmId id) const {
        return getStoreByIndex(id).getPath(id);
    }

    Vec<ImmId> getParentChain(ImmId id, bool withSelf = true) const {
        return getStoreByIndex(id).getParentChain(id, withSelf);
    }

    void ensureStoreForIndex(ImmId::StoreIdxT index);

    /// \brief Create new sem node of the specified kind in the local store
    /// with `index`
    ImmId add(ImmId::StoreIdxT index, sem::SemId<sem::Org> data);

    ImmOrg const* at(ImmId id) const;

    template <typename T>
    T const* at_t(ImmId id) const {
        return at(id)->template as<T>();
    }

    template <typename T>
    T const* at(ImmIdT<T> id) const {
        return at(id.toId())->template as<T>();
    }

    void format(ColStream& os, std::string const& prefix = "") const;

    Vec<ParseUnitStore> stores;

    ContextStore() {}
    ContextStore(const ContextStore&)            = delete;
    ContextStore& operator=(const ContextStore&) = delete;
};

template <typename T>
struct ImmAdapterT;

struct ImmAdapter {
    ImmId         id;
    ContextStore* ctx;

    class iterator {
      public:
        ImmId         id;
        ContextStore* ctx;
        int           idx = 0;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef ImmAdapter                value_type;
        typedef std::ptrdiff_t            difference_type;

        iterator(ImmId id, ContextStore* ctx, int idx = 0)
            : id{id}, ctx{ctx}, idx{idx} {}

        ImmAdapter operator*() const {
            check();
            return ImmAdapter{ctx->at(id)->subnodes.at(idx), ctx};
        }

        void check() const {
            if (!(!id.isNil() && idx < ctx->at(id)->size())) {
                throw logic_assertion_error::init(
                    fmt("Check node id iterator {} < {}",
                        idx,
                        ctx->at(id)->size()));
            }
        }

        iterator& operator++() {
            ++idx;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return this->idx != other.idx;
        }
    };

    int      size() const { return ctx->at(id)->subnodes.size(); }
    iterator begin() const { return iterator(id, ctx); }
    iterator end() const { return iterator(id, ctx, size()); }
    bool     isNil() const { return id.isNil(); }

    ImmAdapter(ImmId id, ContextStore* ctx) : id{id}, ctx{ctx} {}
    ImmAdapter() : id{ImmId::Nil()}, ctx{nullptr} {}

    ImmAdapter pass(ImmId id) const { return ImmAdapter(id, ctx); }

    struct TreeReprConf {
        int  maxDepth      = 40;
        bool withAuxFields = false;

        static TreeReprConf getDefault() { return TreeReprConf{}; }
    };

    void    treeRepr(ColStream& os, TreeReprConf const& conf) const;
    ColText treeRepr(
        TreeReprConf const& conf = TreeReprConf::getDefault()) const {
        ColStream os;
        treeRepr(os, conf);
        return os.getBuffer();
    }

    template <typename T>
    ImmAdapter pass(ImmIdT<T> id) const {
        return ImmAdapter(id, ctx);
    }

    Opt<ImmAdapter> getParent() const {
        if (auto parent = ctx->getParent(id)) {
            return ImmAdapter{parent.value(), ctx};
        } else {
            return std::nullopt;
        }
    }

    Vec<ImmAdapter> getParentChain(bool withSelf = true) const {
        Vec<ImmAdapter> result;
        for (auto const& it : ctx->getParentChain(id, withSelf)) {
            result.push_back(ImmAdapter{it, ctx});
        }
        return result;
    }

    bool operator==(ImmAdapter const& id) const {
        return this->id == id.id;
    }

    ImmOrg const* get() const { return ctx->at(id); }
    ImmOrg const* operator->() const { return get(); }
    ImmAdapter    at(int idx) const {
        return ImmAdapter(ctx->at(id)->subnodes.at(idx), ctx);
    }

    ImmAdapter at(Vec<int> const& path) const {
        auto res = *this;
        for (int idx : path) { res = res.at(idx); }
        return res;
    }

    bool is(OrgSemKind kind) const { return get()->is(kind); }

    Vec<ImmAdapter> sub() const {
        Vec<ImmAdapter> result;
        for (auto const& it : ctx->at(id)->subnodes) {
            result.push_back(pass(it));
        }
        return result;
    }

    template <typename T>
    Vec<ImmAdapterT<T>> subAs() const {
        Vec<ImmAdapterT<T>> result;
        for (auto const& it : ctx->at(id)->subnodes) {
            if (auto sub = pass(it).asOpt<T>()) {
                result.push_back(sub.value());
            }
        }
        return result;
    }

    template <typename T>
    ImmAdapterT<T> as() const {
        if constexpr (!std::is_abstract_v<T>) {
            logic_assertion_check(
                T::staticKind == id.getKind(),
                "static kind:{} id kind:{}",
                T::staticKind,
                id.getKind());
        }

        return ImmAdapterT<T>(id, ctx);
    }

    template <typename T>
    Opt<ImmAdapterT<T>> asOpt() const {
        if (T::staticKind == id.getKind()) {
            return as<T>();
        } else {
            return std::nullopt;
        }
    }
};

template <typename T>
struct ImmAdapterT : ImmAdapter {
    using ImmAdapter::at;
    using ImmAdapter::ImmAdapter;
    T const* get() const { return ctx->at_t<T>(id); }
    T const* operator->() const { return get(); }
};

using SubnodeVisitor = Func<void(ImmAdapter)>;
void eachSubnodeRec(org::ImmAdapter id, SubnodeVisitor cb);

} // namespace org


template <>
struct std::formatter<org::ImmAdapter> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::ImmAdapter& p, FormatContext& ctx) const {
        return fmt_ctx(p.id, ctx);
    }
};


template <typename T>
struct std::formatter<org::ImmAdapterT<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::ImmAdapterT<T>& p, FormatContext& ctx) const {
        return fmt_ctx(p.id, ctx);
    }
};


template <>
struct JsonSerde<org::ImmAdapter> {
    static json to_json(org::ImmAdapter const& it) {
        return json(it.id.getReadableId());
    }
    static org::ImmAdapter from_json(json const& j) {
        throw logic_assertion_error::init(
            "org::ImmAdapter does not support deserialization.");
    }
};

template <typename T>
struct JsonSerde<org::ImmAdapterT<T>> {
    static json to_json(org::ImmAdapterT<T> const& it) {
        return json(it.id.getReadableId());
    }
    static org::ImmAdapterT<T> from_json(json const& j) {
        throw logic_assertion_error::init(
            "org::ImmAdapterT<T> does not support deserialization.");
    }
};
