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
#include <immer/flex_vector_transient.hpp>
#include <immer/vector_transient.hpp>


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

#define _declare_hash(__qual, _)                                          \
    template <>                                                           \
    struct std::hash<sem::__qual> {                                       \
        std::size_t operator()(sem::__qual const& it) const noexcept;     \
    };

EACH_SHARED_ORG_RECORD(_declare_hash)
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


/// \brief Single jump from one node in the AST to another node.
///
/// The path is targeting only node elements in the structure --
/// regular fields like vectors, key-value maps are not targetable. For
/// example, if the node `Paragraph_1` has 3 subnodes for `Word_1`,
/// `Space_1` and, `Word_2`, the full set of paths for them is going to be
///
/// - `Paragraph_1` -- targeting the root node itself
/// - `Paragraph_1` >> .subnodes.[0] >> `Word_1` -- targeting the first
/// word
/// - `Paragraph_1` >> .subnodes.[1] >> `Space_1` -- targeting space
/// - `Paragraph_1` >> .subnodes.[2] >> `Word_2` -- targeting the second
/// word
///
/// `.subnodes` field of the root paragraph can be targeted with the
/// general reflection visitor, but for the immutable AST this is not
/// necessary, as the path should transition between AST *nodes*.
struct ImmPathStep {
    /// \brief path from the root of the immer node to the next ImmId
    /// element.
    ImmReflPathBase path;
    DESC_FIELDS(ImmPathStep, (path));
    bool operator==(ImmPathStep const& other) const {
        return path == other.path;
    }

    static ImmPathStep FieldIdx(ImmReflFieldId const& field, int idx) {
        return ImmPathStep{ImmReflPathBase{{
            ImmReflPathItemBase::FromFieldName(field),
            ImmReflPathItemBase::FromIndex(idx),
        }}};
    }

    static ImmPathStep Field(ImmReflFieldId const& field) {
        return ImmPathStep{ImmReflPathBase{{
            ImmReflPathItemBase::FromFieldName(field),
        }}};
    }

    static ImmPathStep FieldDeref(ImmReflFieldId const& field) {
        return ImmPathStep{ImmReflPathBase{{
            ImmReflPathItemBase::FromFieldName(field),
            ImmReflPathItemBase::FromDeref(),
        }}};
    }

    bool operator<(ImmPathStep const& other) const {
        return path.lessThan(
            other.path, ReflPathComparator<org::ImmReflPathTag>{});
    }
};

/// \brief Full path from the root of the document to a specific node.
struct ImmPath {
    using Store = immer::flex_vector<ImmPathStep>;
    /// \brief Root ID node
    ImmId root;
    /// \brief Sequence of jumps from the root of the document down to the
    /// specified target node. For the path iteration structure see \see
    /// ImmPathStep documentation.
    Store path;


    DESC_FIELDS(ImmPath, (root, path));

    /// \brief Empty path refers to the root of the document
    bool empty() const { return path.empty(); }

    /// \brief Construct default path that refers to a `Nil` root
    ImmPath() : root{ImmId::Nil()} {}
    /// \brief Path referring to the root directly
    ImmPath(ImmId root) : root{root} {};
    /// \brief Path referring to a direct sub-element of the root (one jump
    /// from the root node)
    ImmPath(ImmId root, org::ImmReflPathBase const& step0)
        : root{root}, path{ImmPathStep{step0}} {}
    /// \brief Path referring to a direct sub-element (one jump from the
    /// root)
    ImmPath(ImmId root, ImmPathStep const& step0)
        : root{root}, path{{step0}} {}
    /// \brief Path referring to some nested element in the tree (any
    /// number of jumps)
    ImmPath(ImmId root, Store const& path) : root{root}, path{path} {}
    /// \brief Path referring to some nested element in the tree (any
    /// number of jumps)
    ImmPath(ImmId root, Span<ImmPathStep> const& span)
        : root{root}, path{span.begin(), span.end()} {}

    /// \brief Generate sequence of spans for each jump step, starting from
    /// the leaf up, or from root down.
    ///
    /// \note Spans will not include the empty span (targeting the root
    /// node itself)
    generator<immer::flex_vector<ImmPathStep>> pathSpans(
        /// \brief Starting from the leaf will generate the largest path
        /// span first, and then will decrease it in steps. Starting from
        /// the root will go from the span of size 1 and increase it until
        /// it reaches the target.
        bool leafStart = true) const {
        if (leafStart) {
            for (int i = path.size() - 1; 0 <= i; --i) {
                co_yield path.take(i);
            }
        } else {
            for (int i = 0; i < path.size(); ++i) {
                co_yield path.take(i);
            }
        }
    }

    /// \brief Remove one jump from the path and return a new version
    ImmPath pop() const {
        return ImmPath{root, path.erase(path.size() - 1)};
    }

    /// \brief Add one jump step from the path and return a new version.
    ImmPath add(ImmPathStep const& it) const {
        return ImmPath{root, path.push_back(it)};
    }

    bool operator==(ImmPath const& other) const {
        return root == other.root && path.operator==(other.path);
    }

    bool operator<(ImmPath const& other) const {
        return root < other.root
            && itemwise_less_than(
                   path, other.path, std::less<ImmPathStep>{});
    }
};

/// \brief ID uniquely identifying specific position in the AST
///
/// `ImmId` refers to an interned value, so the same ID can appear in the
/// AST in hundreds and thousands of different places (e.g. `Space_1` is
/// the most likely ID for the regular one-character space, and it will be
/// all over the document). This deduplication is perfect for the general
/// API operations and is the backbone of the whole data model for
/// immutable AST, but makes it impossible to correctly represent tree edit
/// operations -- if `ImmId` were to be used, replacing `Space_1` in one
/// location with `Space_2` would've changed the entire document.
///
/// Unique ID solves this problem by tracking the origin node (root of the
/// document), and the full path from the document root to the final target
/// node `id`. The type is comparable and hash-able.
struct ImmUniqId {
    ImmId   id;
    ImmPath path;
    DESC_FIELDS(ImmUniqId, (id, path));

    /// \brief Create a new unique ID with different final target.
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

struct ImmAdapter;
using ImmStrIdMap          = ImmMap<Str, ImmId>;
using ImmParentPathVec     = SmallVec<ImmPathStep, 4>;
using ImmParentIdVec       = SmallVec<ImmId, 4>;
using ParentPathMap        = UnorderedMap<ImmId, ImmParentPathVec>;
using RadioTargetMap       = ImmMap<Str, Vec<ImmId>>;
using ImmParentMap         = ImmMap<ImmId, ImmParentIdVec>;
using ImmPanentTrackFilter = Func<bool(ImmAdapter const&)>;


struct ImmAstTrackingMapTransient {
    ImmAstContext*                 oldCtx;
    ImmStrIdMap::transient_type    footnotes;
    ImmStrIdMap::transient_type    subtrees;
    RadioTargetMap::transient_type radioTargets;
    ImmStrIdMap::transient_type    anchorTargets;
    ImmStrIdMap::transient_type    names;
    ImmParentMap::transient_type   parents;
    ImmPanentTrackFilter const&    isTrackingParentImpl;

    void setAsParentOf(ImmId const& parent, ImmId const& target);

    /// \brief Remove all direct subnodes of the adapter.
    void removeAllSubnodesOf(ImmAdapter const& parent);
    /// \brief Insert all direct subnodes of the adapter. The adapter does
    /// not need to have a fully correct context path -- only relative
    /// subnode steps are reused, and they can be computed from the node
    /// value alone.
    void insertAllSubnodesOf(ImmAdapter const& parent);

    /// \brief Check if the target adapter should be tracked as a parent
    /// node in the map. Uses \see `isTrackingParentImpl` callback if it is
    /// provided.
    bool isTrackingParent(ImmAdapter const& it) const {
        return isTrackingParentImpl && isTrackingParentImpl(it);
    }

    ImmAstTrackingMap persistent();
    DESC_FIELDS(
        ImmAstTrackingMapTransient,
        (footnotes, subtrees, radioTargets, anchorTargets, parents));
};

bool isTrackingParentDefault(ImmAdapter const&);

struct ImmAstTrackingMap {
    ImmStrIdMap  footnotes;
    ImmStrIdMap  subtrees;
    ImmStrIdMap  anchorTargets;
    ImmStrIdMap  names;
    ImmParentMap parents;
    /// \brief Map starting ID of the radio target text to the parent radio
    /// target for faster lookup.
    RadioTargetMap radioTargets;

    /// \brief Filter out unnecessary nodes that should not be tracked as
    /// parents -- mostly related to leaf nodes like space, word, big ident
    /// etc., to reduce the size of the parent tracking map
    ImmPanentTrackFilter isTrackingParent = isTrackingParentDefault;

    DESC_FIELDS(
        ImmAstTrackingMap,
        (footnotes, subtrees, radioTargets, anchorTargets, parents));

    bool isParentTracked(ImmId const& item) const {
        return parents.contains(item);
    }

    bool isParentOf(ImmId const& parent, ImmId const& item) const {
        return parents.contains(item) && parents.at(item).contains(parent);
    }

    /// \brief Get a list of all nodes that specified ID is used in. Due to
    /// value interning, each specific ID can be used in multiple places at
    /// once.
    ImmParentIdVec const& getParentIds(ImmId const& it) const;

    /// \brief Get map of parents for the ID
    ParentPathMap getParentsFor(ImmId const& it, const ImmAstContext* ctx)
        const;
    /// \brief Get full list of all paths that can be used to reach the
    /// target node. Resulting paths are not guaranteed to converge to a
    /// single root.
    Vec<ImmUniqId> getPathsFor(ImmId const& it, ImmAstContext const* ctx)
        const;

    ImmAstTrackingMapTransient transient(ImmAstContext* oldCtx) {
        return {
            .oldCtx               = oldCtx,
            .names                = names.transient(),
            .footnotes            = footnotes.transient(),
            .subtrees             = subtrees.transient(),
            .radioTargets         = radioTargets.transient(),
            .anchorTargets        = anchorTargets.transient(),
            .parents              = parents.transient(),
            .isTrackingParentImpl = isTrackingParent,
        };
    }
};

struct ImmAstStore;

struct ImmAstEditContext {
    ImmAstTrackingMapTransient transientTrack;
    WPtr<ImmAstContext>        ctx;
    SPtr<ImmAstContext>        finish();
    ImmAstStore&               store();
    OperationsScope            debug;

    /// \brief Add or remove tracking data associated with the value for
    /// the node
    void updateTracking(org::ImmId const& node, bool add);

    void message(
        std::string const& value,
        char const*        function = __builtin_FUNCTION(),
        int                line     = __builtin_LINE(),
        char const*        file     = __builtin_FILE());

    ImmAstContext* operator->() { return ctx.lock().get(); }

    finally_std collectAbslLogs();
};

template <org::IsImmOrgValueType T>
struct ImmAstKindStore {
    using NodeType = T;
    dod::InternStore<org::ImmId, T> values;

    int size() const { return values.size(); }

    ImmAstKindStore() {}
    void format(ColStream& os, std::string const& linePrefix = "") const;

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

struct ImmAstVersion;
struct ImmAdapter;

/// \brief Store additional lookup and debug contexts for a particular
/// version of the AST tree.
struct [[nodiscard]] ImmAstContext : SharedPtrApi<ImmAstContext> {
    /// \brief Shared operation tracer for the debug operations.
    SPtr<OperationsTracer> debug;
    /// \brief Shared AST store, the underlying store data is shared
    /// between all contexts and can only be added to, store data is never
    /// removed so older contexts are always valid.
    SPtr<ImmAstStore> store;
    /// \brief Current version of the AST tracking map stored in the
    /// context
    SPtr<ImmAstTrackingMap> currentTrack;

    void message(
        std::string const& value,
        int                level    = 0,
        char const*        function = __builtin_FUNCTION(),
        int                line     = __builtin_LINE(),
        char const*        file     = __builtin_FILE()) {
        if (debug) { debug->message(value, level, line, function, file); }
    }

    DESC_FIELDS(ImmAstContext, (store, currentTrack));

    ImmParentIdVec const& getParentIds(ImmId const& it) const {
        return currentTrack->getParentIds(it);
    }

    ParentPathMap getParentsFor(ImmId const& it) const {
        return currentTrack->getParentsFor(it, this);
    }

    Vec<ImmUniqId> getPathsFor(ImmId const& it) const {
        return currentTrack->getPathsFor(it, this);
    }

    Vec<ImmAdapter> getAdaptersFor(ImmId const& it) const;
    Vec<ImmAdapter> getParentPathsFor(CR<ImmId> id) const;

    ImmAstVersion getEditVersion(
        ImmAdapter const& root,
        Func<ImmAstReplaceGroup(ImmAstContext::Ptr, ImmAstEditContext&)>
            cb);

    ImmAstEditContext getEditContext();

    ImmAstContext::Ptr finishEdit(ImmAstEditContext& ctx);

    ImmAstVersion finishEdit(
        ImmAstEditContext&        ctx,
        ImmAstReplaceEpoch const& epoch);

    /// \brief Create new sem node of the specified kind in the local store
    /// with `index`
    ImmId add(sem::SemId<sem::Org> data, ImmAstEditContext& ctx);

    ImmAstVersion        addRoot(sem::SemId<sem::Org> data);
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

    ImmAdapter adapt(ImmUniqId const& id) const;
    ImmAdapter adaptUnrooted(ImmId const& id) const;

    static ImmAstContext::Ptr init_start_context() {
        return std::make_shared<ImmAstContext>(
            std::make_shared<ImmAstStore>(),
            std::make_shared<ImmAstTrackingMap>(),
            std::make_shared<OperationsTracer>() //
        );
    }

    ImmAstContext(
        SPtr<ImmAstStore> const&       sharedStore,
        SPtr<ImmAstTrackingMap> const& startTracking,
        SPtr<OperationsTracer> const&  sharedTracer)
        : store{sharedStore}
        , currentTrack{startTracking}
        , debug{sharedTracer} //
    {}
};

/// \brief Specific version of the document.
struct ImmAstVersion {
    ImmAstContext::Ptr context;
    ImmAstReplaceEpoch epoch;
    DESC_FIELDS(ImmAstVersion, (context, epoch));

    ImmId      getRoot() const { return epoch.getRoot(); }
    ImmAdapter getRootAdapter() const;

    ImmAstVersion getEditVersion(
        Func<ImmAstReplaceGroup(ImmAstContext::Ptr, ImmAstEditContext&)>
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
Vec<ImmId> allSubnodes(T const& value, org::ImmAstContext::Ptr const& ctx);

Vec<ImmId> allSubnodes(
    ImmId const&                   value,
    org::ImmAstContext::Ptr const& ctx);


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
    org::ImmId                id,
    ImmAstContext::Ptr const& ctx,
    Func const&               cb) {
    LOGIC_ASSERTION_CHECK(id.getKind() != OrgSemKind::None, "");
    switch_node_kind(
        id, [&]<typename K>(org::ImmIdT<K> id) { cb(ctx->value<K>(id)); });
}

template <typename Func>
void switch_node_fields(
    org::ImmId                id,
    ImmAstContext::Ptr const& ctx,
    Func const&               cb) {
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
    ImmId               id;
    ImmAstContext::WPtr ctx;
    ImmPath             path;

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

    int      size() const { return ctx.lock()->at(id)->subnodes.size(); }
    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(this, size()); }
    bool     isNil() const { return id.isNil(); }
    bool     isRoot() const { return path.empty(); }
    org::ImmReflPathBase flatPath() const {
        org::ImmReflPathBase result;
        auto                 tmp = result.path.transient();
        for (auto const& it : path.path) {
            for (auto const& item : it.path.path) { tmp.push_back(item); }
        }
        result.path = tmp.persistent();
        return result;
    }

    /// \brief Return code to get from the document root to the specified
    /// adapter. Mainly used for writint tests -- print the 'self select'
    /// for the node and then use the expression in the test itself.
    Str selfSelect() const;

    OrgSemKind getKind() const { return id.getKind(); }

    org::ImmReflPathItemBase const& lastPath() const {
        return path.path.back().path.last();
    }

    ImmPathStep const& lastStep() const { return path.path.back(); }

    org::ImmReflPathItemBase const& firstPath() const {
        return path.path.front().path.first();
    }

    ImmAdapter(ImmPath const& path, ImmAstContext::WPtr ctx)
        : id{ctx.lock()->at(path)}, ctx{ctx}, path{path} {}

    ImmAdapter(ImmUniqId id, ImmAstContext::WPtr ctx)
        : id{id.id}, ctx{ctx}, path{id.path} {}

    ImmAdapter(ImmId id, ImmAstContext::WPtr ctx, ImmPath const& path)
        : id{id}, ctx{ctx}, path{path} {}

    ImmAdapter() : id{ImmId::Nil()}, ctx{}, path{ImmId::Nil()} {}

    ImmAdapter pass(ImmId id, ImmPath const& path) const {
        return ImmAdapter(id, ctx, path);
    }

    ImmUniqId uniq() const { return ImmUniqId{.id = id, .path = path}; }

    struct TreeReprConf {
        int  maxDepth       = 40;
        bool withAuxFields  = false;
        bool withReflFields = false;

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

    bool isDirectParentOf(ImmAdapter const& other) const;

    bool isIndirectParentOf(ImmAdapter const& other) const;

    bool isSubnodeOf(ImmAdapter const& other) const {
        return other->indexOf(this->id) != -1;
    }

    Opt<ImmAdapter> getParent() const {
        if (path.empty()) {
            return std::nullopt;
        } else {
            auto newPath = path.pop();
            return ImmAdapter{ctx.lock()->at(newPath), ctx, newPath};
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
    Vec<ImmAdapter> getAllSubnodes(
        const Opt<ImmPath>& rootPath,
        bool                withPath = true) const;
    Vec<ImmAdapter> getAllSubnodesDFS(
        const Opt<ImmPath>&                     rootPath,
        bool                                    withPath     = true,
        const Opt<Func<bool(org::ImmAdapter)>>& acceptFilter = std::
            nullopt) const;

    Vec<ImmPathStep> getRelativeSubnodePaths(ImmId const& subnode) const;

    Vec<ImmAdapter> getParentChain(bool withSelf = true) const;

    bool operator==(ImmAdapter const& id) const {
        return this->id == id.id;
    }

    ImmOrg const* get() const { return ctx.lock()->at(id); }
    ImmOrg const* operator->() const { return get(); }

    template <typename T>
    T const* dyn_cast() const {
        return dynamic_cast<T const*>(get());
    }

    ImmAdapter at(ImmId id, ImmPathStep idx) const {
        return ImmAdapter{id, ctx, path.add(idx)};
    }

    ImmAdapter at(ImmReflFieldId const& field) const {
        return at(
            ctx.lock()->at(
                id,
                ImmPathStep{
                    {org::ImmReflPathItemBase::FromFieldName(field)}}),
            ImmPathStep::Field(field));
    }

    ImmAdapter at(int idx, bool withPath = true) const;

    ImmAdapter at(Vec<int> const& path, bool withPath = true) const {
        auto res = *this;
        for (int idx : path) { res = res.at(idx); }
        return res;
    }

    bool is(OrgSemKind kind) const { return get()->is(kind); }

    Vec<ImmAdapter> sub(bool withPath = true) const;

    template <typename T>
    Vec<ImmAdapterT<T>> subAs(bool withPath = true) const {
        Vec<ImmAdapterT<T>> result;
        for (auto const& it : sub(withPath)) {
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

        return ImmAdapterT<T>{id, ctx, path};
    }

    template <typename T>
    Opt<ImmAdapterT<T>> asOpt() const {
        if (T::staticKind == id.getKind()) {
            return as<T>();
        } else {
            return std::nullopt;
        }
    }

    template <typename Func>
    void visitNodeKind(Func const& cb) const {
        switch_node_kind(id, cb);
    }

    template <typename Func>
    void visitNodeAdapter(Func const& cb) const {
        switch_node_kind(
            id, [&]<typename Kind>(org::ImmIdT<Kind> const& id) {
                cb(this->as<Kind>());
            });
    }

    template <typename Func>
    void visitNodeValue(Func const& cb) const {
        ::org::switch_node_value(id, ctx, cb);
    }

    template <typename Func>
    void visitNodeFields(Func const& cb) const {
        ::org::switch_node_fields(id, ctx, cb);
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


/// \brief Group sequence of subnodes under some criteria depending on the
/// AST context. Used to implement contextually aware elements that are not
/// represented by the actual document syntax, like radio link targets.
struct ImmSubnodeGroup {
    struct RadioTarget {
        Vec<org::ImmAdapter> nodes;
        ImmId                target;
        DESC_FIELDS(RadioTarget, (nodes, target));
    };

    struct Single {
        org::ImmAdapter node;
        DESC_FIELDS(Single, (node));
    };

    SUB_VARIANTS(Kind, Data, data, getKind, RadioTarget, Single);
    Data data;
    DESC_FIELDS(ImmSubnodeGroup, (data));
};

Vec<ImmSubnodeGroup> getSubnodeGroups(
    CR<org::ImmAdapter> node,
    bool                withPath = true);

/// \brief Common adapter specialization methods to inject in the final
/// specializations.
template <typename T>
struct ImmAdapterTBase : ImmAdapter {
    using ImmAdapter::at;
    /// \brief Pass the constructor implementation unchanged
    using ImmAdapter::ImmAdapter;
    using ImmAdapter::pass;
    using ImmAdapter::subAs;
    T const* get() const { return ctx.lock()->template at_t<T>(id); }
    T const* operator->() const { return get(); }
    T const& value() const { return ImmAdapter::value<T>(); }

    /// \brief Get sub-field value wrapped as adapter.
    ///
    /// \warning resulting path is empty, use this only for regular field
    /// access, not for something that would have to be marked as 'edited'
    /// later on.
    template <typename F>
    ImmAdapterT<F> getField(org::ImmIdT<F> T::*fieldPtr) const;

    template <typename F>
    ImmAdapterT<F> getField(
        org::ImmIdT<F> T::*fieldPtr,
        ImmPathStep const& step) const;
};

/// \brief Implement `getThis()` for final specialization and introduce all
/// the adapter base types into the specialization namespace. `
#define USE_IMM_ADAPTER_BASE(T)                                           \
    using ImmAdapterTBase<T>::at;                                         \
    using ImmAdapterTBase<T>::ImmAdapterTBase;                            \
    using ImmAdapterTBase<T>::pass;                                       \
    using ImmAdapterTBase<T>::get;                                        \
    using ImmAdapterTBase<T>::operator->;                                 \
    using ImmAdapterTBase<T>::subAs;                                      \
    using ImmAdapterTBase<T>::value;                                      \
    ImmAdapter*       getThis() { return this; }                          \
    ImmAdapter const* getThis() const { return this; }


/// \brief Generic adapter implementation, with no direct specialization.
template <typename T>
struct ImmAdapterT : ImmAdapterTBase<T> {
    USE_IMM_ADAPTER_BASE(T);
};

#define __declare_adapter(Derived, Base)                                  \
    template <>                                                           \
    struct ImmAdapterT<org::Imm##Derived>;

EACH_SEM_ORG_FINAL_TYPE_BASE(__declare_adapter)
#undef __declare_adapter

/// \brief Base interface for accessing the final adapter specialization
struct ImmAdapterVirtualBase {
    virtual ImmAdapter const* getThis() const = 0;
    virtual ImmAdapter*       getThis()       = 0;

    template <typename T>
    ImmAdapterT<T> getThisT() const {
        return getThis()->as<T>();
    }

    template <typename T>
    ImmAdapterT<T> pass(org::ImmIdT<T> const& id, ImmPathStep const& step)
        const {
        return ImmAdapterT<T>{
            id, getThis()->ctx, getThis()->path.add(step)};
    }
};

/// \brief Root for the full org API specialization hierarchy, mirros the
/// `sem::Org` API implementation.
struct ImmAdapterOrgAPI : ImmAdapterVirtualBase {};

struct ImmAdapterStmtAPI : ImmAdapterOrgAPI {
    virtual Vec<sem::AttrValue> getAttrs(CR<Opt<Str>> param) const;
    virtual Opt<sem::AttrValue> getFirstAttr(Str const& kind) const;

    Vec<ImmAdapter> getCaption() const;
    Vec<Str>        getName() const;
    Vec<ImmAdapter> getAttached(Opt<Str> const& kind = std::nullopt) const;
};

struct ImmAdapterCmdAPI : ImmAdapterStmtAPI {
    virtual Vec<sem::AttrValue> getAttrs(
        CR<Opt<Str>> param) const override;
    virtual Opt<sem::AttrValue> getFirstAttr(
        Str const& kind) const override;
};

struct ImmAdapterSubtreeAPI : ImmAdapterOrgAPI {
    Vec<sem::SubtreePeriod> getTimePeriods(
        IntSet<sem::SubtreePeriod::Kind> kinds,
        bool                             withPath = true) const;
    Vec<sem::NamedProperty> getProperties(
        Str const&      kind,
        Opt<Str> const& subkind = std::nullopt) const;
    Opt<sem::NamedProperty> getProperty(
        Str const&      kind,
        Opt<Str> const& subkind = std::nullopt) const;

    org::ImmAdapterT<org::ImmParagraph> getTitle() const;

    Str getCleanTitle() const;
};

struct ImmAdapterNoneAPI : ImmAdapterOrgAPI {};
struct ImmAdapterAttrAPI : ImmAdapterOrgAPI {};
struct ImmAdapterAttrListAPI : ImmAdapterOrgAPI {};
struct ImmAdapterAttrsAPI : ImmAdapterOrgAPI {};
struct ImmAdapterErrorItemAPI : ImmAdapterOrgAPI {};
struct ImmAdapterErrorGroupAPI : ImmAdapterOrgAPI {};
struct ImmAdapterStmtListAPI : ImmAdapterOrgAPI {};
struct ImmAdapterEmptyAPI : ImmAdapterOrgAPI {};
struct ImmAdapterLineCommandAPI : ImmAdapterCmdAPI {};
struct ImmAdapterAttachedAPI : ImmAdapterLineCommandAPI {};
struct ImmAdapterCmdCaptionAPI : ImmAdapterAttachedAPI {
    org::ImmAdapterT<org::ImmParagraph> getText() const;
};
struct ImmAdapterCmdColumnsAPI : ImmAdapterAttachedAPI {};
struct ImmAdapterCmdNameAPI : ImmAdapterAttachedAPI {};
struct ImmAdapterCmdCustomArgsAPI : ImmAdapterCmdAPI {};
struct ImmAdapterCmdCustomRawAPI : ImmAdapterStmtAPI {};
struct ImmAdapterCmdCustomTextAPI : ImmAdapterStmtAPI {};
struct ImmAdapterCmdResultsAPI : ImmAdapterAttachedAPI {};
struct ImmAdapterCmdTblfmAPI : ImmAdapterCmdAPI {};
struct ImmAdapterInlineAPI : ImmAdapterOrgAPI {};
struct ImmAdapterHashTagAPI : ImmAdapterInlineAPI {};
struct ImmAdapterInlineFootnoteAPI : ImmAdapterInlineAPI {};
struct ImmAdapterTimeAPI : ImmAdapterOrgAPI {
    UserTime getStaticTime() const;
    Opt<int> getYear() const;
    Opt<int> getMonth() const;
    Opt<int> getDay() const;
    Opt<int> getHour() const;
    Opt<int> getMinute() const;
    Opt<int> getSecond() const;
};
struct ImmAdapterTimeRangeAPI : ImmAdapterOrgAPI {};
struct ImmAdapterMacroAPI : ImmAdapterOrgAPI {};
struct ImmAdapterSymbolAPI : ImmAdapterOrgAPI {};
struct ImmAdapterLeafAPI : ImmAdapterOrgAPI {
    Str const& getText() const;
};
struct ImmAdapterEscapedAPI : ImmAdapterLeafAPI {};
struct ImmAdapterNewlineAPI : ImmAdapterLeafAPI {};
struct ImmAdapterSpaceAPI : ImmAdapterLeafAPI {};
struct ImmAdapterWordAPI : ImmAdapterLeafAPI {};
struct ImmAdapterAtMentionAPI : ImmAdapterLeafAPI {};
struct ImmAdapterRawTextAPI : ImmAdapterLeafAPI {};
struct ImmAdapterPunctuationAPI : ImmAdapterLeafAPI {};
struct ImmAdapterPlaceholderAPI : ImmAdapterLeafAPI {};
struct ImmAdapterBigIdentAPI : ImmAdapterLeafAPI {};
struct ImmAdapterTextTargetAPI : ImmAdapterLeafAPI {};
struct ImmAdapterMarkupAPI : ImmAdapterOrgAPI {};
struct ImmAdapterBoldAPI : ImmAdapterMarkupAPI {};
struct ImmAdapterUnderlineAPI : ImmAdapterMarkupAPI {};
struct ImmAdapterMonospaceAPI : ImmAdapterMarkupAPI {};
struct ImmAdapterMarkQuoteAPI : ImmAdapterMarkupAPI {};
struct ImmAdapterRadioTargetAPI : ImmAdapterMarkupAPI {};
struct ImmAdapterVerbatimAPI : ImmAdapterMarkupAPI {};
struct ImmAdapterItalicAPI : ImmAdapterMarkupAPI {};
struct ImmAdapterStrikeAPI : ImmAdapterMarkupAPI {};
struct ImmAdapterParAPI : ImmAdapterMarkupAPI {};
struct ImmAdapterLatexAPI : ImmAdapterOrgAPI {};
struct ImmAdapterLinkAPI : ImmAdapterStmtAPI {};
struct ImmAdapterBlockAPI : ImmAdapterCmdAPI {};
struct ImmAdapterBlockCenterAPI : ImmAdapterBlockAPI {};
struct ImmAdapterBlockQuoteAPI : ImmAdapterBlockAPI {};
struct ImmAdapterBlockCommentAPI : ImmAdapterStmtAPI {};
struct ImmAdapterBlockVerseAPI : ImmAdapterBlockAPI {};
struct ImmAdapterBlockExampleAPI : ImmAdapterBlockAPI {};
struct ImmAdapterInlineExportAPI : ImmAdapterBlockAPI {};
struct ImmAdapterCmdExportAPI : ImmAdapterBlockAPI {};
struct ImmAdapterBlockExportAPI : ImmAdapterBlockAPI {
    Opt<Str> getPlacement() const;
};
struct ImmAdapterBlockDynamicFallbackAPI : ImmAdapterBlockAPI {};
struct ImmAdapterBlockAdmonitionAPI : ImmAdapterBlockAPI {};
struct ImmAdapterBlockCodeAPI : ImmAdapterBlockAPI {};
struct ImmAdapterSubtreeLogAPI : ImmAdapterOrgAPI {};
struct ImmAdapterSubtreeCompletionAPI : ImmAdapterInlineAPI {};
struct ImmAdapterCellAPI : ImmAdapterCmdAPI {};
struct ImmAdapterRowAPI : ImmAdapterCmdAPI {};
struct ImmAdapterTableAPI : ImmAdapterBlockAPI {};
struct ImmAdapterParagraphAPI : ImmAdapterStmtAPI {
    bool          isFootnoteDefinition() const;
    Opt<Str>      getFootnoteName() const;
    bool          hasAdmonition() const;
    Vec<Str>      getAdmonitions() const;
    bool          hasTimestamp() const;
    Vec<UserTime> getTimestamps() const;
    bool          hasLeadHashtags() const;

    Vec<org::ImmAdapterT<org::ImmBigIdent>> getAdmonitionNodes() const;
    Vec<org::ImmAdapterT<org::ImmTime>>     getTimestampNodes() const;
    Vec<org::ImmAdapterT<org::ImmHashTag>>  getLeadHashtags() const;
    Vec<org::ImmAdapter> getBody(bool withPath = true) const;
};
struct ImmAdapterColonExampleAPI : ImmAdapterOrgAPI {};
struct ImmAdapterCmdAttrAPI : ImmAdapterAttachedAPI {};
struct ImmAdapterCallAPI : ImmAdapterOrgAPI {};

struct ImmAdapterListAPI : ImmAdapterStmtAPI {
    bool                isDescriptionList() const;
    bool                isNumberedList() const;
    Vec<sem::AttrValue> getListAttrs(CR<Str> kind) const;
};

struct ImmAdapterListItemAPI : ImmAdapterOrgAPI {
    bool isDescriptionItem() const;

    Opt<ImmAdapter> getHeader() const;
    Opt<Str>        getCleanHeader() const;
};

struct ImmAdapterDocumentOptionsAPI : ImmAdapterOrgAPI {
    Vec<sem::NamedProperty> getProperties(
        Str const&   kind,
        CR<Opt<Str>> subkind = std::nullopt) const;
    Opt<sem::NamedProperty> getProperty(
        CR<Str>      kind,
        CR<Opt<Str>> subkind = std::nullopt) const;
};

struct ImmAdapterDocumentAPI : ImmAdapterOrgAPI {
    Vec<sem::NamedProperty> getProperties(
        CR<Str>      kind,
        CR<Opt<Str>> subkind = std::nullopt) const;
    Opt<sem::NamedProperty> getProperty(
        CR<Str>      kind,
        CR<Opt<Str>> subkind = std::nullopt) const;
};

struct ImmAdapterFileTargetAPI : ImmAdapterOrgAPI {};
struct ImmAdapterTextSeparatorAPI : ImmAdapterOrgAPI {};
struct ImmAdapterIncludeAPI : ImmAdapterOrgAPI {};
struct ImmAdapterDocumentGroupAPI : ImmAdapterOrgAPI {};

// Define specializations for all final (non-abstract) org-mode types.
#define __define_adapter(Derived, Base)                                   \
    template <>                                                           \
    struct ImmAdapterT<org::Imm##Derived>                                 \
        : ImmAdapterTBase<Imm##Derived>                                   \
        , ImmAdapter##Derived##API {                                      \
        using api_type = ImmAdapter##Derived##API;                        \
        USE_IMM_ADAPTER_BASE(org::Imm##Derived);                          \
    };

EACH_SEM_ORG_FINAL_TYPE_BASE(__define_adapter)
#undef __define_adapter

template <typename T>
Vec<T> getSubtreeProperties(CR<org::ImmSubtree> subtree) {
    Vec<T> result;
    for (auto const& prop : subtree.properties) {
        if (std::holds_alternative<T>(prop.data)) {
            result.push_back(std::get<T>(prop.data));
        }
    }

    return result;
}


template <typename T>
template <typename F>
inline ImmAdapterT<F> ImmAdapterTBase<T>::getField(
    org::ImmIdT<F> T::*fieldPtr) const {
    return ImmAdapterT<F>{(get()->*fieldPtr).asOrg(), ctx, {}};
}

template <typename T>
template <typename F>
ImmAdapterT<F> ImmAdapterTBase<T>::getField(
    org::ImmIdT<F> T::*fieldPtr,
    ImmPathStep const& step) const {
    return ImmAdapterT<F>{(get()->*fieldPtr).asOrg(), ctx, path.add(step)};
}

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
void eachSubnodeRec(org::ImmAdapter id, bool withPath, SubnodeVisitor cb);

/// \brief Map immutable AST type to the sem type, defines inner type
/// `sem_type`
template <typename Imm>
struct imm_to_sem_map {};

/// \brief Map sem AST type to the immer type, defines inner type
/// `imm_type`
template <typename Mut>
struct sem_to_imm_map {};

#define _gen_map(__Kind)                                                  \
    template <>                                                           \
    struct imm_to_sem_map<org::Imm##__Kind> {                             \
        using sem_type = sem::__Kind;                                     \
    };                                                                    \
    template <>                                                           \
    struct sem_to_imm_map<sem::__Kind> {                                  \
        using imm_type = org::Imm##__Kind;                                \
    };
EACH_SEM_ORG_KIND(_gen_map)
#undef _gen_map

sem::SemId<sem::Org> sem_from_immer(
    org::ImmId const&    id,
    ImmAstContext const& ctx);

org::ImmId immer_from_sem(
    sem::SemId<sem::Org> const& id,
    ImmAstEditContext&          ctx);

} // namespace org


template <>
struct std::formatter<org::ImmAstStore*>
    : std_format_ptr_as_hex<org::ImmAstStore> {};

template <>
struct std::formatter<org::ImmAstContext*>
    : std_format_ptr_as_hex<org::ImmAstContext> {};

template <>
struct std::formatter<org::ParentPathMap*>
    : std_format_ptr_as_hex_and_value<org::ParentPathMap> {};

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
        return fmt_ctx(fmt("{}->{}", p.path, p.id), ctx);
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
        return ReflPathFormatter<org::ImmReflPathTag>{}.format(
            p.path, ctx);
    }
};

template <>
struct std::hash<org::ImmPathStep> {
    std::size_t operator()(org::ImmPathStep const& step) const noexcept {
        AnyHasher<Str> hasher;
        std::size_t    result = 0;
        for (int i = 0; i < step.path.path.size(); ++i) {
            org::ImmReflPathItemBase const& it = step.path.path.at(i);
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


namespace org::details {
inline org::ImmAstContext* ___get_context(org::ImmAstContext::Ptr p) {
    return p.get();
}
inline ImmAstEditContext* ___get_context(org::ImmAstEditContext& p) {
    return &p;
}

inline bool ___is_debug(org::ImmAstEditContext& p) {
    return p.debug.TraceState;
}
inline bool ___is_debug(org::ImmAstContext::Ptr p) {
    return p->debug->TraceState;
}
} // namespace org::details

#define AST_EDIT_TRACE() ::org::details::___is_debug(ctx)

#define AST_EDIT_MSG(...)                                                 \
    if (AST_EDIT_TRACE()) {                                               \
        ::org::details::___get_context(ctx)->message(__VA_ARGS__);        \
    }
