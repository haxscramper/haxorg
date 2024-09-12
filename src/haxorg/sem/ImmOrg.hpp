#pragma once

#include "hstd/stdlib/TraceBase.hpp"
#include <boost/preprocessor/facilities/expand.hpp>
#include <haxorg/sem/ImmOrgBase.hpp>
#include <haxorg/sem/ImmOrgTypes.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <immer/map_transient.hpp>
#include <hstd/wrappers/hstd_extra/graphviz.hpp>
#include <boost/preprocessor.hpp>


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

template <typename Func>
void switch_node_nullptr(OrgSemKind kind, Func const& cb) {
    switch (kind) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        cb((org::Imm##__Kind*)nullptr);                                   \
        break;                                                            \
    }

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}


namespace org {


template <typename T>
concept IsImmOrgValueType = std::derived_from<T, ImmOrg>;

using ImmAstParentMapType = ImmMap<org::ImmId, org::ImmId>;

struct ImmAstTrackingMap;

#define IMM_PATH_NAMES title

BOOST_PP_EXPAND(
    DECL_DESCRIBED_ENUM_STANDALONE(ImmPathField, IMM_PATH_NAMES))

struct ImmPathItem {
    Variant<int, ImmPathField> step;
    DESC_FIELDS(ImmPathItem, (step));

    ImmPathField getField() const { return std::get<ImmPathField>(step); }
    int          getIndex() const { return std::get<int>(step); }
    bool         isIndex() const { return step.index() == 0; }
    bool         isField() const { return step.index() == 1; }
};

struct ImmPath {
    ImmId            root;
    Vec<ImmPathItem> steps;
    DESC_FIELDS(ImmPath, (root, steps));

    bool empty() const { return steps.empty(); }

    ImmPath() : root{ImmId::Nil()} {}
    ImmPath(ImmId root) : root{root} {};
    ImmPath(ImmId root, Vec<ImmPathItem> const& path)
        : root{root}, steps{path} {}
    ImmPath(ImmId root, Span<ImmPathItem> const& path)
        : root{root}, steps{path.begin(), path.end()} {}

    generator<Span<ImmPathItem>> pathSpans(bool leafStart = true) const {
        if (leafStart) {
            for (int i = steps.high(); 0 <= i; --i) {
                co_yield steps.at(slice(0, i));
            }
        } else {
            for (int i = 0; i < steps.size(); ++i) {
                co_yield steps.at(slice(0, i));
            }
        }
    }


    ImmPath add(int idx) const {
        auto res = *this;
        res.steps.push_back(ImmPathItem{idx});
        return res;
    }

    ImmPath pop() const {
        auto res = *this;
        res.steps.pop_back();
        return res;
    }
};

struct ImmUniqId {
    ImmId   id;
    ImmPath path;
    DESC_FIELDS(ImmUniqId, (id, path));

    ImmUniqId update(ImmId id) const {
        auto res = *this;
        res.id   = id;
        return res;
    }
};

struct ImmAstTrackingMapTransient {
    ImmAstTrackingMap persistent();
    DESC_FIELDS(ImmAstTrackingMapTransient, ());
};

struct ImmAstTrackingMap {
    DESC_FIELDS(ImmAstTrackingMap, ());
    ImmAstTrackingMapTransient transient() { return {}; }
};

struct ImmAstStore;

struct ImmAstEditContext {
    ImmAstTrackingMapTransient parents;
    ImmAstContext*             ctx;
    ImmAstContext              finish();
    ImmAstStore&               store();
    OperationsScope            debug;

    void message(
        std::string const& value,
        char const*        function = __builtin_FUNCTION(),
        int                line     = __builtin_LINE(),
        char const*        file     = __builtin_FILE());

    ImmAstContext* operator->() { return ctx; }
};

#define AST_EDIT_MSG(...)                                                 \
    if (ctx.debug.TraceState) { ctx.message(__VA_ARGS__); }

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
    org::ImmUniqId original;
    org::ImmUniqId replaced;

    DESC_FIELDS(ImmAstReplace, (original, replaced));
};

struct ImmIdFullCompare {
    bool operator()(ImmId first, ImmId other) const {
        return first.getValue() < other.getValue();
    }
};

struct ImmAstReplaceGroup {
    SortedMap<ImmUniqId, ImmUniqId, ImmIdFullCompare> map;

    ImmAstReplaceGroup() {}
    ImmAstReplaceGroup(ImmAstReplace const& replace) { incl(replace); }

    void set(ImmAstReplace const& replace) {
        map.insert_or_assign(replace.original, replace.replaced);
    }

    void incl(ImmAstReplace const& replace) {
        LOGIC_ASSERTION_CHECK(
            !map.contains(replace.original),
            "replacement group cannot contain duplicate nodes. {0} -> {1} "
            "is already added, {0} -> {2} cannot be included",
            /*0*/ replace.original,
            /*1*/ map.at(replace.original),
            /*2*/ replace.replaced);
        set(replace);
    }

    void incl(ImmAstReplaceGroup const& replace) {
        for (auto const& it : replace.allReplacements()) { incl(it); }
    }

    /// \brief Update list of subnodes to a new replaced coutnerparts. Use
    /// during recursive node updates to construct the final node value in
    /// a single go -- this reduces the number of intermediate nodes in the
    /// cascading update. See `demoteSubtreeRecursive` for use example.
    ImmVec<ImmId> newSubnodes(ImmVec<ImmId> oldSubnodes) const;

    generator<ImmAstReplace> allReplacements() const {
        for (auto const& [original, replaced] : this->map) {
            co_yield ImmAstReplace{
                .original = original,
                .replaced = replaced,
            };
        }
    }
};

struct ImmAstReplaceEpoch {
    ImmAstReplaceGroup replaced;
    ImmId              root;

    ImmId getRoot() const { return root; }

    DESC_FIELDS(ImmAstReplaceEpoch, (root, replaced));
};

struct ImmAdapter;

struct ImmAstStore {
    UnorderedMap<org::ImmId, org::ImmId> parents;

    template <org::IsImmOrgValueType T>
    ImmAstKindStore<T> const* getStoreImpl() const;

    template <org::IsImmOrgValueType T>
    ImmAstKindStore<T> const* getStore() const {
        return getStoreImpl<T>();
    }

    template <org::IsImmOrgValueType T>
    ImmAstKindStore<T>* getStore() {
        return const_cast<ImmAstKindStore<T>*>(getStoreImpl<T>());
    }

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

    generator<ImmId> all_ids() const {
        for (auto const& kind : sliceT<OrgSemKind>()) {
            int size = 0;
            switch_node_nullptr(kind, [&]<typename N>(N*) {
                size = getStore<N>()->size();
            });

            for (int i = 0; i < size; ++i) {
                co_yield org::ImmId{kind, static_cast<ImmId::NodeIdxT>(i)};
            }
        }
    }


    ImmOrg const* at(ImmId index) const;

    template <org::IsImmOrgValueType T>
    ImmAstReplace setNode(ImmAdapter const& target, T const& value);

    template <org::IsImmOrgValueType T, typename Func>
    ImmAstReplace updateNode(
        org::ImmId         id,
        ImmAstEditContext& ctx,
        Func               cb);


    /// \brief Generate new set of parent nodes for the node update.
    ImmAstReplaceEpoch cascadeUpdate(
        const ImmAstReplaceGroup&,
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
struct ImmAdapter;

struct [[nodiscard]] ImmAstContext {
    SPtr<OperationsTracer> debug;
    SPtr<ImmAstStore>      store;
    ImmAstTrackingMap      parents;

    void message(
        std::string const& value,
        int                level    = 0,
        char const*        function = __builtin_FUNCTION(),
        int                line     = __builtin_LINE(),
        char const*        file     = __builtin_FILE()) {
        if (debug) { debug->message(value, level, line, function, file); }
    }

    DESC_FIELDS(ImmAstContext, (store, parents));

    ImmAstVersion getEditVersion(
        Func<ImmAstReplaceGroup(ImmAstContext&, ImmAstEditContext&)> cb);

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

    ImmRootAddResult     addRoot(sem::SemId<sem::Org> data);
    ImmAstVersion        init(sem::SemId<sem::Org> root);
    sem::SemId<sem::Org> get(org::ImmId id);

    template <typename T>
    T const& value(ImmId id) const {
        LOGIC_ASSERTION_CHECK(!id.isNil(), "cannot get value for nil ID");
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


    ImmId at(ImmId node, const ImmPathItem& item) const;
    ImmId at(ImmPath const& item) const;

    void format(ColStream& os, std::string const& prefix = "") const;

    ImmAdapter adapt(ImmUniqId const& id);


    ImmAstContext()
        : store{std::make_shared<ImmAstStore>()}
        , debug{std::make_shared<OperationsTracer>()} //
    {}
};

template <org::IsImmOrgValueType T, typename Func>
ImmAstReplace ImmAstStore::updateNode(
    ImmId              id,
    ImmAstEditContext& ctx,
    Func               cb) {
    auto const&   start_value  = ctx.ctx->value<T>(id);
    auto const&   update_value = cb(start_value);
    ImmAstReplace update       = setNode(id, update_value, ctx);
    return update;
}

struct ImmRootAddResult {
    ImmAstContext context;
    org::ImmId    root;
    DESC_FIELDS(ImmRootAddResult, (context, root));
};

struct ImmAstVersion {
    ImmAstContext      context;
    ImmAstReplaceEpoch epoch;
    DESC_FIELDS(ImmAstVersion, (context, epoch));

    ImmId      getRoot() const { return epoch.getRoot(); }
    ImmAdapter getRootAdapter();
};

struct ImmAstGraphvizConf {
    SemSet skippedKinds;
    bool   withEpochClusters = true;
    bool   withAuxNodes      = false;
    bool   withEditHistory   = false;
    bool   withNodePath      = false;

    UnorderedMap<Str, Vec<Str>> skippedFields = {
        {"DocumentOptions", {"exportConfig"}},
        {"Subtree", {"title"}},
    };

    Vec<Str> epochColors = {
        "black",
        "red",
        "blue",
        "goldenrod",
        "deepskyblue3",
        "orange",
        "darkgreen",
        "purple",
        "darkslateblue",
        "firebrick",
        "darkturquoise",
        "sienna",
        "orchid",
        "darkviolet",
        "teal",
        "darkolivegreen",
    };
};

template <org::IsImmOrgValueType T>
Vec<ImmId> allSubnodes(T const& value, org::ImmAstContext const& ctx);

Vec<ImmId> allSubnodes(ImmId const& value, org::ImmAstContext const& ctx);


template <typename Func>
void switch_node_kind(org::ImmId id, Func const& cb) {
    LOGIC_ASSERTION_CHECK(id.getKind() != OrgSemKind::None, "");
    switch (id.getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        cb(id.as<org::Imm##__Kind>());                                    \
        break;                                                            \
    }

        EACH_SEM_ORG_KIND(_case)
#undef _case
        default: {
            id.assertValid();
        }
    }
}

template <typename Func>
void switch_node_value(
    org::ImmId           id,
    ImmAstContext const& ctx,
    Func const&          cb) {
    LOGIC_ASSERTION_CHECK(id.getKind() != OrgSemKind::None, "");
    switch_node_kind(
        id, [&]<typename K>(org::ImmIdT<K> id) { cb(ctx.value<K>(id)); });
}

template <typename T, typename Func>
void for_each_field_value_with_bases(T const& value, Func const& cb) {
    for_each_field_with_bases<T>(
        [&](auto const& field) { cb(field.name, value.*field.pointer); });
}

template <typename Func>
void switch_node_fields(
    org::ImmId           id,
    ImmAstContext const& ctx,
    Func const&          cb) {
    LOGIC_ASSERTION_CHECK(id.getKind() != OrgSemKind::None, "");
    switch_node_value(id, ctx, [&]<typename T>(T const& node) {
        for_each_field_value_with_bases(node, cb);
    });
}


Graphviz::Graph toGraphviz(
    Vec<ImmAstVersion> const& history,
    ImmAstGraphvizConf const& conf = ImmAstGraphvizConf{});

template <typename T>
struct ImmAdapterT;

struct ImmAdapter {
    ImmId          id;
    ImmAstContext* ctx;
    ImmPath        selfPath;

    class iterator {
      public:
        ImmAdapter const* it;
        int               idx = 0;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef ImmAdapter                value_type;
        typedef std::ptrdiff_t            difference_type;

        iterator(ImmAdapter const* it, int idx = 0) : it{it}, idx{idx} {}

        ImmAdapter operator*() const {
            check();
            return it->at(idx);
        }

        void check() const {
            LOGIC_ASSERTION_CHECK(
                idx < it->size(),
                "Check node id iterator {} < {}",
                idx,
                it->size());
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
    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(this, size()); }
    bool     isNil() const { return id.isNil(); }

    ImmAdapter(ImmPath const& path, ImmAstContext* ctx)
        : id{ctx->at(path)}, ctx{ctx}, selfPath{path} {}

    ImmAdapter(ImmUniqId id, ImmAstContext* ctx)
        : id{id.id}, ctx{ctx}, selfPath{id.path} {}

    ImmAdapter(ImmId id, ImmAstContext* ctx, ImmPath const& path)
        : id{id}, ctx{ctx}, selfPath{path} {}

    ImmAdapter()
        : id{ImmId::Nil()}, ctx{nullptr}, selfPath{ImmId::Nil()} {}

    ImmAdapter pass(ImmId id, ImmPath const& path) const {
        return ImmAdapter(id, ctx, path);
    }

    ImmUniqId uniq() const {
        return ImmUniqId{.id = id, .path = selfPath};
    }

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

    bool isDirectParentOf(ImmAdapter const& other) const {
        if (auto parent = other.getParent(); parent) {
            return parent->id == this->id;
        } else {
            return false;
        }
    }

    bool isIndirectParentOf(ImmAdapter const& other) const {
        for (auto const& parent : other.getParentChain(false)) {
            if (parent.id == this->id) { return true; }
        }

        return false;
    }

    bool isSubnodeOf(ImmAdapter const& other) const {
        return other->indexOf(this->id) != -1;
    }

    Opt<ImmAdapter> getParent() const {
        if (selfPath.empty()) {
            return std::nullopt;
        } else {
            auto newPath = selfPath.pop();
            return ImmAdapter{ctx->at(newPath), ctx, newPath};
        }
    }

    int getSelfIndex() const {
        auto parent = getParent();
        if (parent) {
            return parent.value()->indexOf(this->id);
        } else {
            return -1;
        }
    }

    Opt<ImmAdapter> getAdjacentNode(int offset) const;
    Opt<ImmAdapter> getParentSubtree() const;

    Vec<ImmAdapter> getParentChain(bool withSelf = true) const {
        Vec<ImmAdapter> result;
        for (auto const& span : selfPath.pathSpans()) {
            result.push_back(ImmAdapter{
                ImmPath{selfPath.root, span},
                ctx,
            });
        }
        return result;
    }

    bool operator==(ImmAdapter const& id) const {
        return this->id == id.id;
    }

    ImmOrg const* get() const { return ctx->at(id); }
    ImmOrg const* operator->() const { return get(); }
    ImmAdapter    at(int idx) const {
        return ImmAdapter{
            ctx->at(id)->subnodes.at(idx), ctx, selfPath.add(idx)};
    }

    ImmAdapter at(Vec<int> const& path) const {
        auto res = *this;
        for (int idx : path) { res = res.at(idx); }
        return res;
    }

    bool is(OrgSemKind kind) const { return get()->is(kind); }

    Vec<ImmAdapter> sub() const {
        Vec<ImmAdapter> result;
        for (int i = 0; i < size(); ++i) { result.push_back(at(i)); }
        return result;
    }

    template <typename T>
    Vec<ImmAdapterT<T>> subAs() const {
        Vec<ImmAdapterT<T>> result;
        for (auto const& it : sub()) {
            if (it.is(T::staticKind)) { result.push_back(it.as<T>()); }
        }
        return result;
    }

    template <typename T>
    ImmAdapterT<T> as() const {
        if constexpr (!std::is_abstract_v<T>) {
            LOGIC_ASSERTION_CHECK(
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

ImmAstReplace setSubnodes(ImmAdapter target, ImmVec<org::ImmId> subnodes);


template <typename T>
struct ImmAdapterT : ImmAdapter {
    using ImmAdapter::at;
    using ImmAdapter::ImmAdapter;
    using ImmAdapter::pass;
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
