#pragma once

#include "hstd/stdlib/TraceBase.hpp"
#include "hstd/stdlib/algorithms.hpp"
#include <boost/preprocessor/facilities/expand.hpp>
#include <haxorg/sem/ImmOrgBase.hpp>
#include <haxorg/sem/ImmOrgTypes.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <immer/map_transient.hpp>
#include <hstd/wrappers/hstd_extra/graphviz.hpp>
#include <boost/preprocessor.hpp>
#include <hstd/stdlib/reflection_visitor.hpp>


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


struct ImmPathStep {
    /// \brief path from the root of the immer node to the next ImmId
    /// element.
    ReflPath path;
    DESC_FIELDS(ImmPathStep, (path));
    bool operator==(ImmPathStep const& other) const {
        return path == other.path;
    }
};

struct ImmPath {
    ImmId            root;
    Vec<ImmPathStep> path;
    DESC_FIELDS(ImmPath, (root, path));

    bool empty() const { return path.empty(); }

    ImmPath() : root{ImmId::Nil()} {}
    ImmPath(ImmId root) : root{root} {};
    ImmPath(ImmId root, Vec<ImmPathStep> const& path)
        : root{root}, path{path} {}
    ImmPath(ImmId root, Span<ImmPathStep> const& span)
        : root{root}, path{span.begin(), span.end()} {}

    generator<Span<ImmPathStep>> pathSpans(bool leafStart = true) const {
        if (leafStart) {
            for (int i = path.high(); 0 <= i; --i) {
                co_yield path.at(slice(0, i));
            }
        } else {
            for (int i = 0; i < path.size(); ++i) {
                co_yield path.at(slice(0, i));
            }
        }
    }

    ImmPath pop() const {
        auto res = *this;
        res.path.pop_back();
        return res;
    }

    ImmPath add(ImmPathStep const& it) const {
        auto res = *this;
        res.path.push_back(it);
        return res;
    }

    bool operator==(ImmPath const& other) const {
        return root == other.root && path == other.path;
    }

    bool operator<(ImmPath const& other) const {
        logic_todo_impl();
        return root < other.root;
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

    bool operator==(ImmUniqId const& it) const {
        return id == it.id && path == it.path;
    }

    bool operator<(ImmUniqId const& it) const {
        return id < it.id && path < it.path;
    }
};

} // namespace org


template <>
struct std::hash<org::ImmUniqId> {
    std::size_t operator()(org::ImmUniqId const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.id);
        hax_hash_combine(result, it.path);
        return result;
    }
};


namespace org {

struct ImmAstTrackingMapTransient {
    ImmMap<Str, ImmId>::transient_type footnotes;
    ImmMap<Str, ImmId>::transient_type subtrees;
    ImmMap<Str, ImmId>::transient_type radioTargets;
    ImmMap<Str, ImmId>::transient_type anchorTargets;

    ImmAstTrackingMap persistent();
    DESC_FIELDS(
        ImmAstTrackingMapTransient,
        (footnotes, subtrees, radioTargets, anchorTargets));
};

struct ImmAstTrackingMap {
    ImmMap<Str, ImmId> footnotes;
    ImmMap<Str, ImmId> subtrees;
    ImmMap<Str, ImmId> radioTargets;
    ImmMap<Str, ImmId> anchorTargets;

    DESC_FIELDS(
        ImmAstTrackingMap,
        (footnotes, subtrees, radioTargets, anchorTargets));
    ImmAstTrackingMapTransient transient() {
        return {
            .footnotes     = footnotes.transient(),
            .subtrees      = subtrees.transient(),
            .radioTargets  = radioTargets.transient(),
            .anchorTargets = anchorTargets.transient(),
        };
    }
};

struct ImmAstStore;

struct ImmAstEditContext {
    ImmAstTrackingMapTransient track;
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
    if (ctx.ctx->debug->TraceState) { ctx.message(__VA_ARGS__); }

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
    Opt<org::ImmUniqId> original;
    org::ImmUniqId      replaced;

    DESC_FIELDS(ImmAstReplace, (original, replaced));
};

struct ImmAstReplaceGroup {
    UnorderedMap<ImmUniqId, ImmUniqId> map;
    UnorderedMap<ImmId, ImmId>         nodeReplaceMap;
    DESC_FIELDS(ImmAstReplaceGroup, (map, nodeReplaceMap));

    ImmAstReplaceGroup() {}
    ImmAstReplaceGroup(ImmAstReplace const& replace) { incl(replace); }

    void set(ImmAstReplace const& replace);

    void incl(ImmAstReplace const& replace);

    void incl(ImmAstReplaceGroup const& replace) {
        for (auto const& it : replace.allReplacements()) { incl(it); }
    }

    /// \brief Update list of subnodes to a new replaced coutnerparts. Use
    /// during recursive node updates to construct the final node value in
    /// a single go -- this reduces the number of intermediate nodes in the
    /// cascading update. See `demoteSubtreeRecursive` for use example.
    ImmVec<ImmId> newSubnodes(ImmVec<ImmId> oldSubnodes) const;
    Vec<ImmId>    newSubnodes(Vec<ImmId> oldSubnodes) const;

    generator<ImmAstReplace> allReplacements() const {
        for (auto const& key : sorted(this->map.keys())) {
            co_yield ImmAstReplace{
                .original = key,
                .replaced = this->map.at(key),
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
    ImmAstReplace setNode(
        ImmAdapter const&  target,
        T const&           value,
        ImmAstEditContext& ctx);

    template <org::IsImmOrgValueType T, typename Func>
    ImmAstReplace updateNode(
        ImmAdapter         id,
        ImmAstEditContext& ctx,
        Func               cb);


    /// \brief Generate new set of parent nodes for the node update.
    ImmAstReplaceEpoch cascadeUpdate(
        const ImmAdapter& root,
        const ImmAstReplaceGroup&,
        ImmAstEditContext& ctx);

    template <org::IsImmOrgValueType T>
    ImmId add(T const& value, ImmAstEditContext& ctx) {
        return getStore<T>()->add(value, ctx);
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
        ImmAdapter const&                                            root,
        Func<ImmAstReplaceGroup(ImmAstContext&, ImmAstEditContext&)> cb);

    ImmAstEditContext getEditContext() {
        return ImmAstEditContext{
            .track = parents.transient(),
            .ctx   = this,
            .debug = OperationsScope{
                .TraceState  = &debug->TraceState,
                .activeLevel = 0,
            }};
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


    ImmId at(ImmId node, const ImmPathStep& item) const;
    ImmId at(ImmPath const& item) const;

    void format(ColStream& os, std::string const& prefix = "") const;

    ImmAdapter adapt(ImmUniqId const& id);


    ImmAstContext()
        : store{std::make_shared<ImmAstStore>()}
        , debug{std::make_shared<OperationsTracer>()} //
    {}
};


struct ImmRootAddResult {
    ImmAstContext context;
    org::ImmId    root;
    DESC_FIELDS(ImmRootAddResult, (context, root));
};

/// \brief Specific version of the document.
struct ImmAstVersion {
    ImmAstContext      context;
    ImmAstReplaceEpoch epoch;
    DESC_FIELDS(ImmAstVersion, (context, epoch));

    ImmId      getRoot() const { return epoch.getRoot(); }
    ImmAdapter getRootAdapter();

    ImmAstVersion getEditVersion(
        Func<ImmAstReplaceGroup(ImmAstContext& ast, ImmAstEditContext&)>
            cb);
};

struct ImmAstGraphvizConf {
    SemSet skippedKinds;
    bool   withEpochClusters = true;
    bool   withAuxNodes      = false;
    bool   withEditHistory   = false;

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
    bool     isRoot() const { return selfPath.empty(); }
    ReflPath reflPath() const {
        ReflPath result;
        for (auto const& it : selfPath.path) { result.add(it.path); }
        return result;
    }

    ReflPathItem const& lastPath() const {
        return selfPath.path.back().path.last();
    }

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
    Vec<ImmAdapter> getAllSubnodes() const;

    Vec<ImmAdapter> getParentChain(bool withSelf = true) const {
        Vec<ImmAdapter> result;
        for (auto const& span : selfPath.pathSpans()) {
            result.push_back(ImmAdapter{
                ImmPath{selfPath.root, span},
                ctx,
            });
        }
        result.push_back(ImmAdapter{ImmPath{selfPath.root}, ctx});
        return result;
    }

    bool operator==(ImmAdapter const& id) const {
        return this->id == id.id;
    }

    ImmOrg const* get() const { return ctx->at(id); }
    ImmOrg const* operator->() const { return get(); }

    ImmAdapter at(ImmId id, ImmPathStep idx) const {
        return ImmAdapter{id, ctx, selfPath.add(idx)};
    }

    ImmAdapter at(Str const& field) const {
        return at(
            ctx->at(id, ImmPathStep{{ReflPathItem::FromFieldName(field)}}),
            field);
    }

    ImmAdapter at(ImmId id, Str field) const {
        return ImmAdapter{
            id,
            ctx,
            selfPath.add(
                ImmPathStep{{ReflPathItem::FromFieldName(field)}})};
    }

    ImmAdapter at(ImmId id, int idx) const {
        return ImmAdapter{
            id,
            ctx,
            selfPath.add(ImmPathStep{{ReflPathItem::FromIndex(idx)}})};
    }


    ImmAdapter at(int idx) const {
        return at(ctx->at(id)->subnodes.at(idx), idx);
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
    T const& value() const {
        return *as<T>().get();
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

        return ImmAdapterT<T>{id, ctx, selfPath};
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

template <org::IsImmOrgValueType T, typename Func>
ImmAstReplace ImmAstStore::updateNode(
    ImmAdapter         id,
    ImmAstEditContext& ctx,
    Func               cb) {
    auto const&   start_value  = id.value<T>();
    auto const&   update_value = cb(start_value);
    ImmAstReplace update       = setNode(id, update_value, ctx);
    return update;
}

ImmAstReplace setSubnodes(
    ImmAdapter         target,
    ImmVec<org::ImmId> subnodes,
    ImmAstEditContext& ctx);


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
struct std::formatter<org::ImmPath> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::ImmPath& p, FormatContext& ctx) const {
        return fmt_ctx(fmt("{}//{}", p.root, p.path), ctx);
    }
};

template <>
struct std::formatter<org::ImmUniqId> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::ImmUniqId& p, FormatContext& ctx) const {
        return fmt_ctx(fmt("{}->{}", p.path, p.id), ctx);
    }
};


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
        return fmt_ctx(fmt("{}->{}", p.selfPath, p.id), ctx);
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

template <>
struct std::formatter<org::ImmPathStep> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::ImmPathStep& p, FormatContext& ctx) const {
        Vec<Str>          result;
        AnyFormatter<Str> anyFmt;
        for (ReflPathItem const& step : p.path.path) {
            if (step.isAnyKey()) {
                result.push_back(anyFmt(step.getAnyKey().key));
            } else {
                std::visit(
                    [&](auto const& it) { result.push_back(fmt1(it)); },
                    step.data);
            }
        }

        return fmt_ctx(join(">>", result), ctx);
    }
};

template <>
struct std::hash<org::ImmPathStep> {
    std::size_t operator()(org::ImmPathStep const& step) const noexcept {
        AnyHasher<Str> hasher;
        std::size_t    result = 0;
        for (int i = 0; i < step.path.path.size(); ++i) {
            ReflPathItem const& it = step.path.path.at(i);
            hax_hash_combine(result, i);
            if (it.isAnyKey()) {
                hax_hash_combine(result, hasher(it.getAnyKey().key));
            } else {
                hax_hash_combine(result, it);
            }
        }
        return result;
    }
};

template <>
struct std::hash<org::ImmPath> {
    std::size_t operator()(org::ImmPath const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.root);
        hax_hash_combine(result, it.path);
        return result;
    }
};
