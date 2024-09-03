#pragma once

#include <haxorg/sem/ImmOrgBase.hpp>
#include <haxorg/sem/ImmOrgTypes.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <immer/map_transient.hpp>
#include <hstd/wrappers/hstd_extra/graphviz.hpp>


#define _declare_hash(__kind)                                             \
    template <>                                                           \
    struct std::hash<org::Imm##__kind> {                                  \
        std::size_t operator()(                                           \
            org::Imm##__kind const& it) const noexcept;                   \
    };

EACH_SEM_ORG_KIND(_declare_hash)
#undef _declare_hash


#define _declare_hash(__parent, __qual, _)                                \
    template <>                                                           \
    struct std::hash<org::Imm##__parent::__qual> {                        \
        std::size_t operator()(                                           \
            org::Imm##__parent::__qual const& it) const noexcept;         \
    };

EACH_SEM_ORG_RECORD_NESTED(_declare_hash)
#undef _declare_hash


namespace org {


template <typename T>
concept IsImmOrgValueType = std::derived_from<T, ImmOrg>;

using ImmAstParentMapType = ImmMap<org::ImmId, org::ImmId>;

struct ImmAstParentMap;

struct ImmAstParentMapTransient {
    ImmAstParentMapType::transient_type parents;

    void setParent(org::ImmId node, org::ImmId parent) {
        parents.insert({node, parent});
    }

    void removeParent(org::ImmId node) { parents.erase(node); }

    ImmAstParentMap persistent();
};

struct ImmAstParentMap {
    ImmAstParentMapType parents;
    DESC_FIELDS(ImmAstParentMap, (parents));

    Opt<ImmId> getParent(ImmId id) const { return parents.get(id); }
    Vec<int>   getPath(ImmId id, ImmAstContext const& ctx) const;
    Vec<ImmId> getParentChain(ImmId id, bool withSelf = true) const;
    bool       hasParent(org::ImmId node) const {
        return parents.contains(node);
    }

    ImmAstParentMapTransient transient() {
        return {.parents = parents.transient()};
    }
};


struct ImmAstEditContext {
    ImmAstParentMapTransient parents;
    ImmAstContext*           ctx;
    ImmAstContext            finish();
};

template <org::IsImmOrgValueType T>
struct ImmAstKindStore {
    using NodeType = T;
    dod::InternStore<org::ImmId, T> values;

    int size() const { return values.size(); }

    ImmAstKindStore() {}
    void format(
        ColStream&                                  os,
        UnorderedMap<org::ImmId, org::ImmId> const& parents,
        std::string const&                          linePrefix = "") const;

    bool     empty() const { return values.empty(); }
    T const* at(org::ImmId id) const { return &values.at(id); }
    ImmId    add(T const& value, ImmAstEditContext& ctx);
    ImmId    add(sem::SemId<sem::Org> data, ImmAstEditContext& ctx);

    sem::SemId<sem::Org> get(org::ImmId id, ImmAstContext const& ctx);
};

struct ImmAstReplace {
    org::ImmId original;
    org::ImmId replaced;

    DESC_FIELDS(ImmAstReplace, (original, replaced));
};

struct ImmAstReplaceCascade {
    Vec<ImmAstReplace> chain;

    DESC_FIELDS(ImmAstReplaceCascade, (chain));
};

struct ImmAstReplaceEpoch {
    Vec<ImmAstReplaceCascade> replaced;

    ImmId getRoot() const {
        return replaced.front().chain.back().replaced;
    }

    DESC_FIELDS(ImmAstReplaceEpoch, (replaced));
};

struct ImmAstStore {
    UnorderedMap<org::ImmId, org::ImmId> parents;

    template <typename T>
    ImmAstKindStore<T>* getStore();

#define _kind(__Kind) ImmAstKindStore<Imm##__Kind> store##__Kind;
    EACH_SEM_ORG_KIND(_kind)
#undef _kind


    ImmAstStore()
        :
#define _kind(__Kind) , store##__Kind()
        EACH_SEM_ORG_KIND_CSV(_kind)
#undef _kind
    {
    }

    void format(ColStream& os, std::string const& prefix = "") const;


    ImmOrg const* at(ImmId index) const;

    template <org::IsImmOrgValueType T>
    ImmAstReplace setNode(
        org::ImmId         target,
        T const&           value,
        ImmAstEditContext& ctx);

    ImmAstReplace setSubnodes(
        org::ImmId         target,
        ImmVec<org::ImmId> subnodes,
        ImmAstEditContext& ctx);

    ImmAstReplaceEpoch setSubnode(
        org::ImmId         target,
        org::ImmId         newSubnode,
        int                position,
        ImmAstEditContext& ctx);

    /// \brief Generate new set of parent nodes for the node update.
    ImmAstReplaceEpoch cascadeUpdate(
        Vec<ImmAstReplace> const&,
        ImmAstEditContext& ctx);

    template <org::IsImmOrgValueType T>
    ImmId add(T const& value, ImmAstEditContext& ctx) {
        return getStore<T>().add(value, ctx);
    }

    ImmId add(sem::SemId<sem::Org> data, ImmAstEditContext& ctx);

    sem::SemId<sem::Org> get(org::ImmId id, ImmAstContext const& ctx);
};

struct ImmRootAddResult;
struct ImmAstVersion;

struct [[nodiscard]] ImmAstContext {
    SPtr<ImmAstStore> store;
    ImmAstParentMap   parents;

    DESC_FIELDS(ImmAstContext, (store, parents));

    bool       hasParent(ImmId id) const { return parents.hasParent(id); }
    Opt<ImmId> getParent(ImmId id) const { return parents.getParent(id); }
    Vec<int> getPath(ImmId id) const { return parents.getPath(id, *this); }
    Vec<ImmId> getParentChain(ImmId id, bool withSelf = true) const {
        return parents.getParentChain(id, withSelf);
    }

    ImmAstEditContext getEditContext() {
        return ImmAstEditContext{
            .parents = parents.transient(),
            .ctx     = this,
        };
    }

    ImmAstContext finishEdit(ImmAstEditContext& ctx);

    ImmAstVersion finishEdit(
        ImmAstEditContext&        ctx,
        ImmAstReplaceEpoch const& epoch);

    /// \brief Create new sem node of the specified kind in the local store
    /// with `index`
    ImmId add(sem::SemId<sem::Org> data, ImmAstEditContext& ctx);
    ImmRootAddResult addRoot(sem::SemId<sem::Org> data);
    ImmAstVersion    init(sem::SemId<sem::Org> root);

    sem::SemId<sem::Org> get(org::ImmId id);

    template <typename T>
    T const& value(ImmId id) const {
        logic_assertion_check(!id.isNil(), "cannot get value for nil ID");
        return *at_t<T>(id);
    }

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


    ImmAstContext() : store{std::make_shared<ImmAstStore>()} {}
};

struct ImmRootAddResult {
    ImmAstContext context;
    org::ImmId    root;
    DESC_FIELDS(ImmRootAddResult, (context, root));
};

struct ImmAstVersion {
    ImmAstContext      context;
    ImmAstReplaceEpoch epoch;
    DESC_FIELDS(ImmAstVersion, (context, epoch));
};

struct ImmAstGraphvizConf {
    SemSet skippedKinds;

    UnorderedMap<Str, Vec<Str>> skippedFields = {
        {"DocumentOptions", {"exportConfig"}},
    };

    Vec<Str> epochColors = {
        "gray",
        "red",
        "blue",
        "yellow",
        "cyan",
        "orange",
    };
};

template <org::IsImmOrgValueType T>
Vec<ImmId> allSubnodes(T const& value, org::ImmAstContext const& ctx);

Vec<ImmId> allSubnodes(ImmId const& value, org::ImmAstContext const& ctx);

Graphviz::Graph toGraphviz(
    Vec<ImmAstVersion> const& history,
    ImmAstGraphvizConf const& conf = ImmAstGraphvizConf{});

template <typename T>
struct ImmAdapterT;

struct ImmAdapter {
    ImmId          id;
    ImmAstContext* ctx;

    class iterator {
      public:
        ImmId          id;
        ImmAstContext* ctx;
        int            idx = 0;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef ImmAdapter                value_type;
        typedef std::ptrdiff_t            difference_type;

        iterator(ImmId id, ImmAstContext* ctx, int idx = 0)
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

    ImmAdapter(ImmId id, ImmAstContext* ctx) : id{id}, ctx{ctx} {}
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


template <typename T>
struct remove_sem_org {
    using type = remove_smart_pointer<T>::type;
};

template <>
struct remove_sem_org<ImmId> {
    using type = ImmOrg;
};

template <>
struct remove_sem_org<ImmAdapter> {
    using type = ImmOrg;
};

template <typename T>
struct remove_sem_org<ImmIdT<T>> {
    using type = remove_smart_pointer<T>::type;
};

template <typename T>
struct remove_sem_org<ImmAdapterT<T>> {
    using type = remove_smart_pointer<T>::type;
};


template <typename T>
concept IsImmOrg = std::
    derived_from<typename remove_sem_org<T>::type, ImmOrg>;


using SubnodeVisitor = Func<void(ImmAdapter)>;
void eachSubnodeRec(org::ImmAdapter id, SubnodeVisitor cb);

} // namespace org

template <>
struct std::formatter<org::ImmAstStore*>
    : std_format_ptr_as_hex<org::ImmAstStore> {};

template <>
struct std::formatter<org::ImmAstContext*>
    : std_format_ptr_as_hex<org::ImmAstContext> {};

template <>
struct std::formatter<org::ImmAstStore> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::ImmAstStore& p, FormatContext& ctx) const {
        return fmt_ctx("ImmAstStore{}", ctx);
    }
};


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
