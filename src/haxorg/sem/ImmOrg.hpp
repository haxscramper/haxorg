#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"

#include "hstd/stdlib/TraceBase.hpp"
#include "hstd/stdlib/algorithms.hpp"
#include <boost/preprocessor/facilities/expand.hpp>
#include <haxorg/sem/ImmOrgBase.hpp>
#include <haxorg/sem/ImmOrgTypes.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <immer/map_transient.hpp>
#include <hstd/ext/graphviz.hpp>
#include <boost/preprocessor.hpp>
#include <hstd/stdlib/reflection_visitor.hpp>
#include <immer/flex_vector_transient.hpp>
#include <immer/vector_transient.hpp>


#define _declare_hash(__kind)                                             \
    template <>                                                           \
    struct std::hash<org::imm::Imm##__kind> {                             \
        std::size_t operator()(                                           \
            org::imm::Imm##__kind const& it) const noexcept;              \
    };

EACH_SEM_ORG_KIND(_declare_hash)
#undef _declare_hash


#define _declare_hash(__parent, __qual, _)                                \
    template <>                                                           \
    struct std::hash<org::imm::Imm##__parent::__qual> {                   \
        std::size_t operator()(                                           \
            org::imm::Imm##__parent::__qual const& it) const noexcept;    \
    };

EACH_SEM_ORG_RECORD_NESTED(_declare_hash)
#undef _declare_hash

#define _declare_hash(__qual, _)                                          \
    template <>                                                           \
    struct std::hash<org::sem::__qual> {                                  \
        std::size_t operator()(                                           \
            org::sem::__qual const& it) const noexcept;                   \
    };

EACH_SHARED_ORG_RECORD(_declare_hash)
#undef _declare_hash


template <typename Func>
void switch_node_nullptr(OrgSemKind kind, Func const& cb) {
    switch (kind) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        cb((org::imm::Imm##__Kind*)nullptr);                              \
        break;                                                            \
    }

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}


namespace org::imm {

template <typename T>
concept IsImmOrgValueType = std::derived_from<T, ImmOrg>;

using ImmAstParentMapType = hstd::ext::
    ImmMap<org::imm::ImmId, org::imm::ImmId>;

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
struct [[refl]] ImmPathStep {
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
            other.path,
            hstd::ReflPathComparator<org::imm::ImmReflPathTag>{});
    }
};

/// \brief Full path from the root of the document to a specific node.
struct [[refl]] ImmPath {
    using Store = immer::flex_vector<ImmPathStep>;
    /// \brief Root ID node
    [[refl]] ImmId root;
    /// \brief Sequence of jumps from the root of the document down to the
    /// specified target node. For the path iteration structure see \see
    /// ImmPathStep documentation.
    [[refl]] Store path;


    DESC_FIELDS(ImmPath, (root, path));

    /// \brief Empty path refers to the root of the document
    [[refl]] bool empty() const { return path.empty(); }

    /// \brief Construct default path that refers to a `Nil` root
    ImmPath() : root{ImmId::Nil()} {}
    /// \brief Path referring to the root directly
    ImmPath(ImmId root) : root{root} {};
    /// \brief Path referring to a direct sub-element of the root (one jump
    /// from the root node)
    ImmPath(ImmId root, org::imm::ImmReflPathBase const& step0)
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
    ImmPath(ImmId root, hstd::Span<ImmPathStep> const& span)
        : root{root}, path{span.begin(), span.end()} {}

    /// \brief Generate sequence of spans for each jump step, starting from
    /// the leaf up, or from root down.
    ///
    /// \note Spans will not include the empty span (targeting the root
    /// node itself)
    hstd::generator<immer::flex_vector<ImmPathStep>> pathSpans(
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
            && hstd::itemwise_less_than(
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
struct [[refl]] ImmUniqId {
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

} // namespace org::imm


template <>
struct std::hash<org::imm::ImmUniqId> {
    std::size_t operator()(org::imm::ImmUniqId const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.id);
        hstd::hax_hash_combine(result, it.path);
        return result;
    }
};


namespace org::imm {

struct ImmAdapter;
using ImmStrIdMap      = hstd::ext::ImmMap<hstd::Str, ImmId>;
using ImmHashTagIdMap  = hstd::ext::ImmMap<sem::HashTagFlat, ImmId>;
using ImmParentPathVec = hstd::SmallVec<ImmPathStep, 4>;
using ImmParentIdVec   = hstd::SmallVec<ImmId, 4>;
using ParentPathMap    = hstd::UnorderedMap<ImmId, ImmParentPathVec>;
using RadioTargetMap   = hstd::ext::ImmMap<hstd::Str, hstd::Vec<ImmId>>;
using ImmParentMap     = hstd::ext::ImmMap<ImmId, ImmParentIdVec>;
using ImmPanentTrackFilter = hstd::Func<bool(ImmAdapter const&)>;


struct ImmAstTrackingMapTransient {
    ImmAstContext*                  oldCtx;
    ImmStrIdMap::transient_type     footnotes;
    ImmStrIdMap::transient_type     subtrees;
    RadioTargetMap::transient_type  radioTargets;
    ImmStrIdMap::transient_type     anchorTargets;
    ImmStrIdMap::transient_type     names;
    ImmHashTagIdMap::transient_type hashtagDefinitions;
    ImmParentMap::transient_type    parents;
    ImmPanentTrackFilter const&     isTrackingParentImpl;

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
    ImmStrIdMap     footnotes;
    ImmStrIdMap     subtrees;
    ImmStrIdMap     anchorTargets;
    ImmStrIdMap     names;
    ImmParentMap    parents;
    ImmHashTagIdMap hashtagDefinitions;
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

    hstd::ColText toString() const;

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
    hstd::Vec<ImmUniqId> getPathsFor(
        ImmId const&         it,
        ImmAstContext const* ctx) const;

    ImmAstTrackingMapTransient transient(ImmAstContext* oldCtx) {
        return {
            .oldCtx               = oldCtx,
            .names                = names.transient(),
            .footnotes            = footnotes.transient(),
            .subtrees             = subtrees.transient(),
            .radioTargets         = radioTargets.transient(),
            .anchorTargets        = anchorTargets.transient(),
            .parents              = parents.transient(),
            .hashtagDefinitions   = hashtagDefinitions.transient(),
            .isTrackingParentImpl = isTrackingParent,
        };
    }
};

struct ImmAstStore;

struct ImmAstEditContext {
    ImmAstTrackingMapTransient transientTrack;
    hstd::WPtr<ImmAstContext>  ctx;
    hstd::SPtr<ImmAstContext>  finish();
    ImmAstStore&               store();

    /// \brief Add or remove tracking data associated with the value for
    /// the node
    void updateTracking(org::imm::ImmId const& node, bool add);

    hstd::SPtr<hstd::OperationsTracer> debug();

    void message(
        std::string const& value,
        char const*        function = __builtin_FUNCTION(),
        int                line     = __builtin_LINE(),
        char const*        file     = __builtin_FILE());

    ImmAstContext* operator->() { return ctx.lock().get(); }
};

template <org::imm::IsImmOrgValueType T>
struct ImmAstKindStore {
    using NodeType = T;
    hstd::dod::InternStore<org::imm::ImmId, T> values;

    int size() const { return values.size(); }

    ImmAstKindStore() {}
    void format(hstd::ColStream& os, std::string const& linePrefix = "")
        const;

    bool     empty() const { return values.empty(); }
    T const* at(org::imm::ImmId id) const { return &values.at(id); }
    ImmId    add(T const& value, ImmAstEditContext& ctx);
    ImmId    add(sem::SemId<sem::Org> data, ImmAstEditContext& ctx);

    sem::SemId<sem::Org> get(org::imm::ImmId id, ImmAstContext const& ctx);
};

struct ImmAstReplace {
    hstd::Opt<org::imm::ImmUniqId> original;
    org::imm::ImmUniqId            replaced;

    DESC_FIELDS(ImmAstReplace, (original, replaced));
};

struct ImmAstReplaceGroup {
    hstd::UnorderedMap<ImmUniqId, ImmUniqId> map;
    hstd::UnorderedMap<ImmId, ImmId>         nodeReplaceMap;
    DESC_FIELDS(ImmAstReplaceGroup, (map, nodeReplaceMap));

    ImmAstReplaceGroup() {}
    ImmAstReplaceGroup(ImmAstReplace const& replace) { incl(replace); }
    ImmAstReplaceGroup(hstd::Opt<ImmAstReplace> const& replace) {
        if (replace) { incl(replace.value()); }
    }

    void set(ImmAstReplace const& replace);

    void incl(ImmAstReplace const& replace);

    void incl(ImmAstReplaceGroup const& replace) {
        for (auto const& it : replace.allReplacements()) { incl(it); }
    }

    /// \brief Update list of subnodes to a new replaced coutnerparts. Use
    /// during recursive node updates to construct the final node value in
    /// a single go -- this reduces the number of intermediate nodes in the
    /// cascading update. See `demoteSubtreeRecursive` for use example.
    hstd::ext::ImmVec<ImmId> newSubnodes(
        hstd::ext::ImmVec<ImmId> oldSubnodes) const;
    hstd::Vec<ImmId> newSubnodes(hstd::Vec<ImmId> oldSubnodes) const;

    hstd::generator<ImmAstReplace> allReplacements() const {
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
    template <org::imm::IsImmOrgValueType T>
    ImmAstKindStore<T> const* getStoreImpl() const;

    template <org::imm::IsImmOrgValueType T>
    ImmAstKindStore<T> const* getStore() const {
        return getStoreImpl<T>();
    }

    template <org::imm::IsImmOrgValueType T>
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

    void format(hstd::ColStream& os, std::string const& prefix = "") const;

    hstd::generator<org::imm::ImmId> all_ids() const {
        for (auto const& kind : hstd::sliceT<OrgSemKind>()) {
            int size = 0;
            switch_node_nullptr(kind, [&]<typename N>(N*) {
                size = getStore<N>()->size();
            });

            for (int i = 0; i < size; ++i) {
                co_yield org::imm::ImmId{
                    kind, static_cast<ImmId::NodeIdxT>(i)};
            }
        }
    }


    ImmOrg const* at(ImmId index) const;

    template <org::imm::IsImmOrgValueType T>
    hstd::Opt<ImmAstReplace> setNode(
        ImmAdapter const&  target,
        T const&           value,
        ImmAstEditContext& ctx);

    template <org::imm::IsImmOrgValueType T, typename Func>
    hstd::Opt<ImmAstReplace> updateNode(
        ImmAdapter         id,
        ImmAstEditContext& ctx,
        Func               cb);

    /// \brief Generate new set of parent nodes for the node update.
    ImmAstReplaceEpoch cascadeUpdate(
        const ImmAdapter& root,
        const ImmAstReplaceGroup&,
        ImmAstEditContext& ctx);

    template <org::imm::IsImmOrgValueType T>
    ImmId add(T const& value, ImmAstEditContext& ctx) {
        return getStore<T>()->add(value, ctx);
    }

    ImmId add(sem::SemId<sem::Org> data, ImmAstEditContext& ctx);

    sem::SemId<sem::Org> get(org::imm::ImmId id, ImmAstContext const& ctx);
};

struct ImmAstVersion;
struct ImmAdapter;

#define __DECLARE_VALUE_READ_FIELD(                                       \
    __FIELD_TYPE,                                                         \
    __FIELD_NAME,                                                         \
    __FIELD_UPPERCASE,                                                    \
    __PARENT_TYPE,                                                        \
    __PARENT_KIND)                                                        \
    [[refl]] BOOST_PP_REMOVE_PARENS(__FIELD_TYPE)                         \
        const& get##__FIELD_UPPERCASE() const;

#define __DECLARE_VALUE_WRITE_FIELD(                                      \
    __FIELD_TYPE,                                                         \
    __FIELD_NAME,                                                         \
    __FIELD_UPPERCASE,                                                    \
    __PARENT_TYPE,                                                        \
    __PARENT_KIND)                                                        \
    [[refl]]                                                              \
    void set##__FIELD_UPPERCASE(BOOST_PP_REMOVE_PARENS(__FIELD_TYPE)      \
                                    const& value);


#define __DECLARE_VALUE_READ_TYPE(__KIND)                                 \
    struct [[refl(                                                        \
        R"({"default-constructor": false})")]] Imm##__KIND##ValueRead {   \
        org::imm::Imm##__KIND* ptr;                                       \
        Imm##__KIND##ValueRead(org::imm::Imm##__KIND const* ptr)          \
            : ptr{const_cast<org::imm::Imm##__KIND*>(ptr)} {}             \
        EACH_IMM_ORG_Imm##__KIND##_FIELD_WITH_BASE_FIELDS(                \
            __DECLARE_VALUE_READ_FIELD);                                  \
        DESC_FIELDS(Imm##__KIND##ValueRead, ());                          \
    };                                                                    \
                                                                          \
    struct [[refl(                                                        \
        R"({"default-constructor": false})")]] Imm##__KIND##Value         \
        : public org::imm::Imm##__KIND##ValueRead {                       \
        using org::imm::Imm##__KIND##ValueRead::Imm##__KIND##ValueRead;   \
        EACH_IMM_ORG_Imm##__KIND##_FIELD_WITH_BASE_FIELDS(                \
            __DECLARE_VALUE_WRITE_FIELD);                                 \
        DESC_FIELDS(Imm##__KIND##Value, ());                              \
    };


EACH_SEM_ORG_KIND(__DECLARE_VALUE_READ_TYPE)

#undef __DECLARE_VALUE_READ_TYPE
#undef __DECLARE_VALUE_READ_FIELD
#undef __DECLARE_VALUE_WRITE_FIELD

/// \brief Store additional lookup and debug contexts for a particular
/// version of the AST tree.
struct
    [[nodiscard,
      refl(
          R"({"default-constructor": false, "backend": {"python": {"holder-type": "shared"}}})")]] ImmAstContext
    : hstd::SharedPtrApi<ImmAstContext> {
    /// \brief Shared operation tracer for the debug operations.
    hstd::SPtr<hstd::OperationsTracer> debug;
    /// \brief Shared AST store, the underlying store data is shared
    /// between all contexts and can only be added to, store data is never
    /// removed so older contexts are always valid.
    hstd::SPtr<ImmAstStore> store;
    /// \brief Current version of the AST tracking map stored in the
    /// context
    hstd::SPtr<ImmAstTrackingMap> currentTrack;

    DESC_FIELDS(ImmAstContext, (store, currentTrack));

    ImmParentIdVec const& getParentIds(ImmId const& it) const {
        return currentTrack->getParentIds(it);
    }

    ParentPathMap getParentsFor(ImmId const& it) const {
        return currentTrack->getParentsFor(it, this);
    }

    hstd::Vec<ImmUniqId> getPathsFor(ImmId const& it) const {
        return currentTrack->getPathsFor(it, this);
    }

    hstd::Vec<ImmAdapter> getAdaptersFor(ImmId const& it) const;
    hstd::Vec<ImmAdapter> getParentPathsFor(ImmId const& id) const;

    ImmAstVersion getEditVersion(
        ImmAdapter const& root,
        hstd::Func<
            ImmAstReplaceGroup(ImmAstContext::Ptr, ImmAstEditContext&)>
            cb);

    ImmAstEditContext getEditContext();

    ImmAstContext::Ptr finishEdit(ImmAstEditContext& ctx);

    ImmAstVersion finishEdit(
        ImmAstEditContext&        ctx,
        ImmAstReplaceEpoch const& epoch);

    /// \brief Create new sem node of the specified kind in the local store
    /// with `index`
    ImmId add(sem::SemId<sem::Org> data, ImmAstEditContext& ctx);

    [[refl]] ImmAstVersion        addRoot(sem::SemId<sem::Org> data);
    ImmAstVersion                 init(sem::SemId<sem::Org> root);
    [[refl]] sem::SemId<sem::Org> get(org::imm::ImmId id);

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

    void format(hstd::ColStream& os, std::string const& prefix = "") const;

    ImmAdapter adapt(ImmUniqId const& id) const;
    ImmAdapter adaptUnrooted(ImmId const& id) const;

    static ImmAstContext::Ptr init_start_context() {
        return std::make_shared<ImmAstContext>(
            std::make_shared<ImmAstStore>(),
            std::make_shared<ImmAstTrackingMap>(),
            std::make_shared<hstd::OperationsTracer>() //
        );
    }

    ImmAstContext(
        hstd::SPtr<ImmAstStore> const&            sharedStore,
        hstd::SPtr<ImmAstTrackingMap> const&      startTracking,
        hstd::SPtr<hstd::OperationsTracer> const& sharedTracer)
        : store{sharedStore}
        , currentTrack{startTracking}
        , debug{sharedTracer} //
    {}
};

/// \brief Specific version of the document.
struct [[refl]] ImmAstVersion {
    ImmAstContext::Ptr context;
    ImmAstReplaceEpoch epoch;
    DESC_FIELDS(ImmAstVersion, (context, epoch));

    [[refl]] ImmId      getRoot() const { return epoch.getRoot(); }
    [[refl]] ImmAdapter getRootAdapter() const;

    [[refl]] std::shared_ptr<ImmAstContext> getContext() const {
        return context;
    }

    ImmAstVersion getEditVersion(hstd::Func<ImmAstReplaceGroup(
                                     ImmAstContext::Ptr,
                                     ImmAstEditContext&)> cb);
};

struct ImmAstGraphvizConf {
    SemSet skippedKinds;
    bool   withEpochClusters = true;
    bool   withAuxNodes      = false;
    bool   withEditHistory   = false;

    hstd::UnorderedMap<hstd::Str, hstd::Vec<hstd::Str>> skippedFields = {
        {"DocumentOptions", {"exportConfig"}},
        {"Subtree", {"title"}},
    };

    hstd::Vec<hstd::Str> epochColors = {
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

template <org::imm::IsImmOrgValueType T>
hstd::Vec<ImmId> allSubnodes(
    T const&                            value,
    org::imm::ImmAstContext::Ptr const& ctx);

hstd::Vec<ImmId> allSubnodes(
    ImmId const&                        value,
    org::imm::ImmAstContext::Ptr const& ctx);


template <typename Func>
void switch_node_kind(org::imm::ImmId id, Func const& cb) {
    LOGIC_ASSERTION_CHECK(id.getKind() != OrgSemKind::None, "");
    switch (id.getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        cb(id.as<org::imm::Imm##__Kind>());                               \
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
    org::imm::ImmId           id,
    ImmAstContext::Ptr const& ctx,
    Func const&               cb) {
    LOGIC_ASSERTION_CHECK(id.getKind() != OrgSemKind::None, "");
    switch_node_kind(id, [&]<typename K>(org::imm::ImmIdT<K> id) {
        cb(ctx->value<K>(id));
    });
}

template <typename Func>
void switch_node_fields(
    org::imm::ImmId           id,
    ImmAstContext::Ptr const& ctx,
    Func const&               cb) {
    LOGIC_ASSERTION_CHECK(id.getKind() != OrgSemKind::None, "");
    switch_node_value(id, ctx, [&]<typename T>(T const& node) {
        hstd::for_each_field_value_with_bases(node, cb);
    });
}


hstd::ext::Graphviz::Graph toGraphviz(
    hstd::Vec<ImmAstVersion> const& history,
    ImmAstGraphvizConf const&       conf = ImmAstGraphvizConf{});

template <typename T>
struct ImmAdapterT;

struct [[refl(R"({"default-constructor": false})")]] ImmAdapter {
    ImmId               id;
    ImmAstContext::WPtr ctx;
    ImmPath             path;

    DESC_FIELDS(ImmAdapter, (id, ctx, path));

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

    [[refl]] int size() const {
        return ctx.lock()->at(id)->subnodes.size();
    }
    iterator      begin() const { return iterator(this); }
    iterator      end() const { return iterator(this, size()); }
    [[refl]] bool isNil() const { return id.isNil(); }
    [[refl]] bool isRoot() const { return path.empty(); }
    org::imm::ImmReflPathBase flatPath() const {
        org::imm::ImmReflPathBase result;
        auto                      tmp = result.path.transient();
        for (auto const& it : path.path) {
            for (auto const& item : it.path.path) { tmp.push_back(item); }
        }
        result.path = tmp.persistent();
        return result;
    }

    /// \brief Return code to get from the document root to the specified
    /// adapter. Mainly used for writint tests -- print the 'self select'
    /// for the node and then use the expression in the test itself.
    hstd::Str selfSelect() const;

    [[refl]] OrgSemKind getKind() const { return id.getKind(); }

    org::imm::ImmReflPathItemBase const& lastPath() const {
        return path.path.back().path.last();
    }

    ImmPathStep const& lastStep() const { return path.path.back(); }

    org::imm::ImmReflPathItemBase const& firstPath() const {
        return path.path.front().path.first();
    }

    ImmAdapter(ImmPath const& path, ImmAstContext::WPtr ctx)
        : id{ctx.lock()->at(path)}, ctx{ctx}, path{path} {}

    ImmAdapter(ImmUniqId id, ImmAstContext::WPtr ctx)
        : id{id.id}, ctx{ctx}, path{id.path} {}

    ImmAdapter(ImmId id, ImmAstContext::WPtr ctx, ImmPath const& path)
        : id{id}, ctx{ctx}, path{path} {}

    ImmAdapter(org::imm::ImmAdapter const& other)
        : id{other.id}, ctx{other.ctx}, path{other.path} {}

    ImmAdapter() : id{ImmId::Nil()}, ctx{}, path{ImmId::Nil()} {}

    ImmAdapter pass(ImmId id, ImmPath const& path) const {
        return ImmAdapter(id, ctx, path);
    }

    [[refl]] ImmUniqId uniq() const {
        return ImmUniqId{.id = id, .path = path};
    }

    struct [[refl]] TreeReprConf {
        [[refl]] int  maxDepth       = 40;
        [[refl]] bool withAuxFields  = false;
        [[refl]] bool withReflFields = false;

        DESC_FIELDS(
            TreeReprConf,
            (maxDepth, withAuxFields, withReflFields));

        static TreeReprConf getDefault() { return TreeReprConf{}; }
    };

    void treeRepr(hstd::ColStream& os, TreeReprConf const& conf) const;
    hstd::ColText treeRepr(
        TreeReprConf const& conf = TreeReprConf::getDefault()) const {
        hstd::ColStream os;
        treeRepr(os, conf);
        return os.getBuffer();
    }

    [[refl]] std::string treeReprString() const {
        return treeRepr().toString(false);
    }

    [[refl]] std::string treeReprStringOpts(
        TreeReprConf const& conf) const {
        return treeRepr(conf).toString(false);
    }


    template <typename T>
    ImmAdapter pass(ImmIdT<T> id) const {
        return ImmAdapter(id, ctx);
    }

    [[refl]] bool isDirectParentOf(ImmAdapter const& other) const;

    [[refl]] bool isIndirectParentOf(ImmAdapter const& other) const;

    [[refl]] bool isSubnodeOf(ImmAdapter const& other) const {
        return other->indexOf(this->id) != -1;
    }

    [[refl]] hstd::Opt<ImmAdapter> getParent() const {
        if (path.empty()) {
            return std::nullopt;
        } else {
            auto newPath = path.pop();
            return ImmAdapter{ctx.lock()->at(newPath), ctx, newPath};
        }
    }

    [[refl]] int getSelfIndex() const {
        auto parent = getParent();
        if (parent) {
            return parent.value()->indexOf(this->id);
        } else {
            return -1;
        }
    }

    hstd::Opt<ImmAdapter> getAdjacentNode(int offset) const;
    hstd::Opt<ImmAdapter> getFirstMatchingParent(
        hstd::Func<bool(const ImmAdapter&)> pred) const;
    hstd::Opt<ImmAdapter> getParentSubtree() const;
    hstd::Vec<ImmAdapter> getAllSubnodes(
        const hstd::Opt<ImmPath>& rootPath,
        bool                      withPath = true) const;
    hstd::Vec<ImmAdapter> getAllSubnodesDFS(
        const hstd::Opt<ImmPath>&                      rootPath,
        bool                                           withPath     = true,
        const hstd::Opt<hstd::Func<bool(ImmAdapter)>>& acceptFilter = std::
            nullopt) const;

    hstd::Vec<ImmPathStep> getRelativeSubnodePaths(
        ImmId const& subnode) const;

    hstd::Vec<ImmAdapter> getParentChain(bool withSelf = true) const;

    bool operator==(ImmAdapter const& id) const {
        return this->id == id.id;
    }

    ImmOrg const* get() const { return ctx.lock()->at(id); }
    ImmOrg const* operator->() const { return get(); }

    template <typename T>
    T const* dyn_cast() const {
        return dynamic_cast<T const*>(get());
    }

    [[refl]] ImmAdapter at(ImmId id, ImmPathStep idx) const {
        return ImmAdapter{id, ctx, path.add(idx)};
    }

    [[refl]] ImmAdapter at(ImmReflFieldId const& field) const {
        return at(
            ctx.lock()->at(
                id,
                ImmPathStep{{org::imm::ImmReflPathItemBase::FromFieldName(
                    field)}}),
            ImmPathStep::Field(field));
    }

    [[refl]] ImmAdapter at(int idx, bool withPath = true) const;

    [[refl]] ImmAdapter at(
        hstd::Vec<int> const& path,
        bool                  withPath = true) const {
        auto res = *this;
        for (int idx : path) { res = res.at(idx); }
        return res;
    }

    [[refl]] bool is(OrgSemKind kind) const { return get()->is(kind); }

    [[refl]] hstd::Vec<ImmAdapter> sub(bool withPath = true) const;

    template <typename T>
    hstd::Vec<ImmAdapterT<T>> subAs(bool withPath = true) const {
        hstd::Vec<ImmAdapterT<T>> result;
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
    hstd::Opt<ImmAdapterT<T>> asOpt() const {
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
            id, [&]<typename Kind>(org::imm::ImmIdT<Kind> const& id) {
                cb(this->as<Kind>());
            });
    }

    template <typename Func>
    void visitNodeValue(Func const& cb) const {
        ::org::imm::switch_node_value(id, ctx.lock(), cb);
    }

    template <typename Func>
    void visitNodeFields(Func const& cb) const {
        ::org::imm::switch_node_fields(id, ctx, cb);
    }
};

template <org::imm::IsImmOrgValueType T, typename Func>
hstd::Opt<ImmAstReplace> ImmAstStore::updateNode(
    ImmAdapter         id,
    ImmAstEditContext& ctx,
    Func               cb) {
    auto const&              start_value  = id.value<T>();
    auto const&              update_value = cb(start_value);
    hstd::Opt<ImmAstReplace> update       = setNode(id, update_value, ctx);
    return update;
}

ImmAstReplace setSubnodes(
    ImmAdapter                         target,
    hstd::ext::ImmVec<org::imm::ImmId> subnodes,
    ImmAstEditContext&                 ctx);


/// \brief Group sequence of subnodes under some criteria depending on the
/// AST context. Used to implement contextually aware elements that are not
/// represented by the actual document syntax, like radio link targets.
struct ImmSubnodeGroup {
    struct RadioTarget {
        hstd::Vec<ImmAdapter> nodes;
        ImmId                 target;
        DESC_FIELDS(RadioTarget, (nodes, target));
    };

    struct Single {
        ImmAdapter node;
        DESC_FIELDS(Single, (node));
    };

    struct TrackedHashtag {
        ImmAdapter                                  tag;
        hstd::UnorderedMap<sem::HashTagFlat, ImmId> targets;
        DESC_FIELDS(TrackedHashtag, (tag, targets));
    };

    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getKind,
        RadioTarget,
        Single,
        TrackedHashtag);
    Data data;
    DESC_FIELDS(ImmSubnodeGroup, (data));
};

hstd::Vec<ImmSubnodeGroup> getSubnodeGroups(
    org::imm::ImmAdapter const& node,
    bool                        withPath = true);

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
    ImmAdapterT<F> getField(ImmIdT<F> T::*fieldPtr) const;

    template <typename F>
    ImmAdapterT<F> getField(
        ImmIdT<F> T::*     fieldPtr,
        ImmPathStep const& step) const;

    ImmAdapterTBase(ImmPath const& path, ImmAstContext::WPtr ctx)
        : ImmAdapter{path, ctx} {}

    ImmAdapterTBase(ImmUniqId id, ImmAstContext::WPtr ctx)
        : ImmAdapter{id, ctx} {}

    ImmAdapterTBase(ImmId id, ImmAstContext::WPtr ctx, ImmPath const& path)
        : ImmAdapter{id, ctx, path} {}

    ImmAdapterTBase(org::imm::ImmAdapter const& other)
        : ImmAdapter{other} {}

    ImmAdapterTBase() : org::imm::ImmAdapter{} {}
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
    struct ImmAdapterT<org::imm::Imm##Derived>;

EACH_SEM_ORG_FINAL_TYPE_BASE(__declare_adapter)
#undef __declare_adapter

/// \brief Base interface for accessing the final adapter specialization
struct [[refl]] ImmAdapterVirtualBase {
    virtual ImmAdapter const* getThis() const = 0;
    virtual ImmAdapter*       getThis()       = 0;

    virtual ~ImmAdapterVirtualBase() {}

    template <typename T>
    ImmAdapterT<T> getThisT() const {
        return getThis()->as<T>();
    }

    template <typename T>
    ImmAdapterT<T> pass(ImmIdT<T> const& id, ImmPathStep const& step)
        const {
        return ImmAdapterT<T>{
            id, getThis()->ctx, getThis()->path.add(step)};
    }
};

/// \brief Root for the full org API specialization hierarchy, mirros the
/// `sem::Org` API implementation.
struct [[refl]] ImmAdapterOrgAPI : ImmAdapterVirtualBase {};

struct [[refl]] ImmAdapterStmtAPI : ImmAdapterOrgAPI {
    virtual hstd::Vec<org::sem::AttrValue> getAttrs(
        hstd::Opt<hstd::Str> const& param) const;
    virtual hstd::Opt<org::sem::AttrValue> getFirstAttr(
        hstd::Str const& kind) const;

    hstd::Vec<ImmAdapter> getCaption() const;
    hstd::Vec<hstd::Str>  getName() const;
    hstd::Vec<ImmAdapter> getAttached(
        hstd::Opt<hstd::Str> const& kind = std::nullopt) const;
};

struct [[refl]] ImmAdapterCmdAPI : ImmAdapterStmtAPI {
    virtual hstd::Vec<org::sem::AttrValue> getAttrs(
        hstd::Opt<hstd::Str> const& param) const override;
    virtual hstd::Opt<org::sem::AttrValue> getFirstAttr(
        hstd::Str const& kind) const override;
};

struct [[refl]] ImmAdapterSubtreeAPI : ImmAdapterOrgAPI {
    hstd::Vec<org::sem::SubtreePeriod> getTimePeriods(
        hstd::IntSet<org::sem::SubtreePeriod::Kind> kinds,
        bool                                        withPath = true) const;
    hstd::Vec<org::sem::NamedProperty> getProperties(
        hstd::Str const&            kind,
        hstd::Opt<hstd::Str> const& subkind = std::nullopt) const;
    hstd::Opt<org::sem::NamedProperty> getProperty(
        hstd::Str const&            kind,
        hstd::Opt<hstd::Str> const& subkind = std::nullopt) const;

    org::imm::ImmAdapterT<org::imm::ImmParagraph> getTitle() const;

    hstd::Str getCleanTitle() const;
};

struct [[refl]] ImmAdapterNoneAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterAttrAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterAttrListAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterAttrsAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterErrorItemAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterErrorGroupAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterStmtListAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterEmptyAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterLineCommandAPI : ImmAdapterCmdAPI {};
struct [[refl]] ImmAdapterAttachedAPI : ImmAdapterLineCommandAPI {};
struct [[refl]] ImmAdapterCmdCaptionAPI : ImmAdapterAttachedAPI {
    org::imm::ImmAdapterT<org::imm::ImmParagraph> getText() const;
};
struct [[refl]] ImmAdapterCmdColumnsAPI : ImmAdapterAttachedAPI {};
struct [[refl]] ImmAdapterCmdNameAPI : ImmAdapterAttachedAPI {};
struct [[refl]] ImmAdapterCmdCallAPI : ImmAdapterAttachedAPI {};
struct [[refl]] ImmAdapterCmdCustomArgsAPI : ImmAdapterCmdAPI {};
struct [[refl]] ImmAdapterCmdCustomRawAPI : ImmAdapterStmtAPI {};
struct [[refl]] ImmAdapterCmdCustomTextAPI : ImmAdapterStmtAPI {};
struct [[refl]] ImmAdapterCmdResultsAPI : ImmAdapterAttachedAPI {};
struct [[refl]] ImmAdapterCmdTblfmAPI : ImmAdapterCmdAPI {};
struct [[refl]] ImmAdapterInlineAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterHashTagAPI : ImmAdapterInlineAPI {};
struct [[refl]] ImmAdapterInlineFootnoteAPI : ImmAdapterInlineAPI {};
struct [[refl]] ImmAdapterTimeAPI : ImmAdapterOrgAPI {
    hstd::UserTime getStaticTime() const;
    hstd::Opt<int> getYear() const;
    hstd::Opt<int> getMonth() const;
    hstd::Opt<int> getDay() const;
    hstd::Opt<int> getHour() const;
    hstd::Opt<int> getMinute() const;
    hstd::Opt<int> getSecond() const;
};
struct [[refl]] ImmAdapterTimeRangeAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterMacroAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterSymbolAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterLeafAPI : ImmAdapterOrgAPI {
    hstd::Str const& getText() const;
};
struct [[refl]] ImmAdapterEscapedAPI : ImmAdapterLeafAPI {};
struct [[refl]] ImmAdapterNewlineAPI : ImmAdapterLeafAPI {};
struct [[refl]] ImmAdapterSpaceAPI : ImmAdapterLeafAPI {};
struct [[refl]] ImmAdapterWordAPI : ImmAdapterLeafAPI {};
struct [[refl]] ImmAdapterAtMentionAPI : ImmAdapterLeafAPI {};
struct [[refl]] ImmAdapterRawTextAPI : ImmAdapterLeafAPI {};
struct [[refl]] ImmAdapterPunctuationAPI : ImmAdapterLeafAPI {};
struct [[refl]] ImmAdapterPlaceholderAPI : ImmAdapterLeafAPI {};
struct [[refl]] ImmAdapterBigIdentAPI : ImmAdapterLeafAPI {};
struct [[refl]] ImmAdapterTextTargetAPI : ImmAdapterLeafAPI {};
struct [[refl]] ImmAdapterMarkupAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterBoldAPI : ImmAdapterMarkupAPI {};
struct [[refl]] ImmAdapterUnderlineAPI : ImmAdapterMarkupAPI {};
struct [[refl]] ImmAdapterMonospaceAPI : ImmAdapterMarkupAPI {};
struct [[refl]] ImmAdapterMarkQuoteAPI : ImmAdapterMarkupAPI {};
struct [[refl]] ImmAdapterRadioTargetAPI : ImmAdapterMarkupAPI {};
struct [[refl]] ImmAdapterVerbatimAPI : ImmAdapterMarkupAPI {};
struct [[refl]] ImmAdapterItalicAPI : ImmAdapterMarkupAPI {};
struct [[refl]] ImmAdapterStrikeAPI : ImmAdapterMarkupAPI {};
struct [[refl]] ImmAdapterParAPI : ImmAdapterMarkupAPI {};
struct [[refl]] ImmAdapterLatexAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterLinkAPI : ImmAdapterStmtAPI {};
struct [[refl]] ImmAdapterBlockAPI : ImmAdapterCmdAPI {};
struct [[refl]] ImmAdapterBlockCenterAPI : ImmAdapterBlockAPI {};
struct [[refl]] ImmAdapterBlockQuoteAPI : ImmAdapterBlockAPI {};
struct [[refl]] ImmAdapterBlockCommentAPI : ImmAdapterStmtAPI {};
struct [[refl]] ImmAdapterBlockVerseAPI : ImmAdapterBlockAPI {};
struct [[refl]] ImmAdapterBlockExampleAPI : ImmAdapterBlockAPI {};
struct [[refl]] ImmAdapterInlineExportAPI : ImmAdapterBlockAPI {};
struct [[refl]] ImmAdapterCmdExportAPI : ImmAdapterBlockAPI {};
struct [[refl]] ImmAdapterBlockExportAPI : ImmAdapterBlockAPI {
    hstd::Opt<hstd::Str> getPlacement() const;
};
struct [[refl]] ImmAdapterBlockDynamicFallbackAPI : ImmAdapterBlockAPI {};
struct [[refl]] ImmAdapterBlockAdmonitionAPI : ImmAdapterBlockAPI {};
struct [[refl]] ImmAdapterBlockCodeEvalResultAPI : ImmAdapterBlockAPI {};
struct [[refl]] ImmAdapterBlockCodeAPI : ImmAdapterBlockAPI {};
struct [[refl]] ImmAdapterSubtreeLogAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterSubtreeCompletionAPI : ImmAdapterInlineAPI {};
struct [[refl]] ImmAdapterCellAPI : ImmAdapterCmdAPI {};
struct [[refl]] ImmAdapterRowAPI : ImmAdapterCmdAPI {};
struct [[refl]] ImmAdapterTableAPI : ImmAdapterBlockAPI {};
struct [[refl]] ImmAdapterParagraphAPI : ImmAdapterStmtAPI {
    bool                      isFootnoteDefinition() const;
    hstd::Opt<hstd::Str>      getFootnoteName() const;
    bool                      hasAdmonition() const;
    hstd::Vec<hstd::Str>      getAdmonitions() const;
    bool                      hasTimestamp() const;
    hstd::Vec<hstd::UserTime> getTimestamps() const;
    bool                      hasLeadHashtags() const;

    hstd::Vec<ImmAdapterT<ImmBigIdent>> getAdmonitionNodes() const;
    hstd::Vec<ImmAdapterT<ImmTime>>     getTimestampNodes() const;
    hstd::Vec<ImmAdapterT<ImmHashTag>>  getLeadHashtags() const;
    hstd::Vec<ImmAdapter> getBody(bool withPath = true) const;
};
struct [[refl]] ImmAdapterColonExampleAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterCmdAttrAPI : ImmAdapterAttachedAPI {};
struct [[refl]] ImmAdapterCallAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterFileAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterDirectoryAPI : ImmAdapterOrgAPI {
    [[refl]] hstd::Opt<org::imm::ImmAdapter> getFsSubnode(
        hstd::Str const& name,
        bool             withPath = true) const;
};
struct [[refl]] ImmAdapterSymlinkAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterDocumentFragmentAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterCriticMarkupAPI : ImmAdapterOrgAPI {};

struct [[refl]] ImmAdapterListAPI : ImmAdapterStmtAPI {
    bool                           isDescriptionList() const;
    bool                           isNumberedList() const;
    hstd::Vec<org::sem::AttrValue> getListAttrs(
        hstd::Str const& kind) const;
};

struct [[refl]] ImmAdapterListItemAPI : ImmAdapterOrgAPI {
    bool isDescriptionItem() const;

    hstd::Opt<ImmAdapter> getHeader() const;
    hstd::Opt<hstd::Str>  getCleanHeader() const;
};

struct [[refl]] ImmAdapterDocumentOptionsAPI : ImmAdapterOrgAPI {
    hstd::Vec<sem::NamedProperty> getProperties(
        hstd::Str const&            kind,
        hstd::Opt<hstd::Str> const& subkind = std::nullopt) const;
    hstd::Opt<sem::NamedProperty> getProperty(
        hstd::Str const&            kind,
        hstd::Opt<hstd::Str> const& subkind = std::nullopt) const;
};

struct [[refl]] ImmAdapterDocumentAPI : ImmAdapterOrgAPI {
    hstd::Vec<sem::NamedProperty> getProperties(
        hstd::Str const&            kind,
        hstd::Opt<hstd::Str> const& subkind = std::nullopt) const;
    hstd::Opt<sem::NamedProperty> getProperty(
        hstd::Str const&            kind,
        hstd::Opt<hstd::Str> const& subkind = std::nullopt) const;
};

struct [[refl]] ImmAdapterFileTargetAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterTextSeparatorAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterCmdIncludeAPI : ImmAdapterOrgAPI {};
struct [[refl]] ImmAdapterDocumentGroupAPI : ImmAdapterOrgAPI {};

// Define specializations for all final (non-abstract) org-mode types.
#define __define_adapter(Derived, Base)                                   \
    template <>                                                           \
    struct [[refl(                                                        \
        "{\"default-constructor\": false, \"wrapper-name\": "             \
        "\"Imm" #Derived                                                  \
        "Adapter\", \"wrapper-has-params\": "                             \
        "false}")]] ImmAdapterT<org::imm::Imm##Derived>                   \
        : ImmAdapterTBase<Imm##Derived>                                   \
        , ImmAdapter##Derived##API {                                      \
        using api_type = ImmAdapter##Derived##API;                        \
        USE_IMM_ADAPTER_BASE(org::imm::Imm##Derived);                     \
        [[refl]] ImmAdapterT(org::imm::ImmAdapter const& other)           \
            : ImmAdapterTBase<Imm##Derived>{other} {                      \
            LOGIC_ASSERTION_CHECK(                                        \
                other.getKind() == OrgSemKind::Derived,                   \
                "Adapter type mismatch, creating {} from generic "        \
                "adapter of type {}",                                     \
                #Derived,                                                 \
                other.getKind());                                         \
        }                                                                 \
        [[refl]] org::imm::Imm##Derived##ValueRead getValue() const {     \
            return org::imm::Imm##Derived##ValueRead{&this->value()};     \
        };                                                                \
    };

EACH_SEM_ORG_FINAL_TYPE_BASE(__define_adapter)
#undef __define_adapter


template <typename T>
template <typename F>
inline ImmAdapterT<F> ImmAdapterTBase<T>::getField(
    org::imm::ImmIdT<F> T::*fieldPtr) const {
    return ImmAdapterT<F>{(get()->*fieldPtr).asOrg(), ctx, {}};
}

template <typename T>
template <typename F>
ImmAdapterT<F> ImmAdapterTBase<T>::getField(
    org::imm::ImmIdT<F> T::*fieldPtr,
    ImmPathStep const&      step) const {
    return ImmAdapterT<F>{(get()->*fieldPtr).asOrg(), ctx, path.add(step)};
}

template <typename T>
struct remove_sem_org {
    using type = hstd::remove_smart_pointer<T>::type;
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
    using type = hstd::remove_smart_pointer<T>::type;
};

template <typename T>
struct remove_sem_org<ImmAdapterT<T>> {
    using type = hstd::remove_smart_pointer<T>::type;
};


template <typename T>
concept IsImmOrg = std::
    derived_from<typename remove_sem_org<T>::type, ImmOrg>;


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
    struct imm_to_sem_map<org::imm::Imm##__Kind> {                        \
        using sem_type = org::sem::__Kind;                                \
    };                                                                    \
    template <>                                                           \
    struct sem_to_imm_map<org::sem::__Kind> {                             \
        using imm_type = org::imm::Imm##__Kind;                           \
    };
EACH_SEM_ORG_KIND(_gen_map)
#undef _gen_map

sem::SemId<sem::Org> sem_from_immer(
    org::imm::ImmId const& id,
    ImmAstContext const&   ctx);

org::imm::ImmId immer_from_sem(
    org::sem::SemId<org::sem::Org> const& id,
    ImmAstEditContext&                    ctx);

} // namespace org::imm


template <>
struct std::formatter<org::imm::ImmAstStore*>
    : hstd::std_format_ptr_as_hex<org::imm::ImmAstStore> {};

template <>
struct std::formatter<org::imm::ImmAstContext*>
    : hstd::std_format_ptr_as_hex<org::imm::ImmAstContext> {};

template <>
struct std::formatter<org::imm::ParentPathMap*>
    : hstd::std_format_ptr_as_hex_and_value<org::imm::ParentPathMap> {};

template <>
struct std::formatter<org::imm::ImmPath> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::imm::ImmPath& p, FormatContext& ctx) const {
        return hstd::fmt_ctx(hstd::fmt("{}//{}", p.root, p.path), ctx);
    }
};

template <>
struct std::formatter<org::imm::ImmUniqId> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::imm::ImmUniqId& p, FormatContext& ctx) const {
        return hstd::fmt_ctx(hstd::fmt("{}->{}", p.path, p.id), ctx);
    }
};


template <>
struct std::formatter<org::imm::ImmAstStore>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::imm::ImmAstStore& p, FormatContext& ctx) const {
        return hstd::fmt_ctx("ImmAstStore{}", ctx);
    }
};


template <>
struct std::formatter<org::imm::ImmAdapter> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::imm::ImmAdapter& p, FormatContext& ctx) const {
        return hstd::fmt_ctx(hstd::fmt("{}->{}", p.path, p.id), ctx);
    }
};


template <typename T>
struct std::formatter<org::imm::ImmAdapterT<T>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::imm::ImmAdapterT<T>& p, FormatContext& ctx)
        const {
        return hstd::fmt_ctx(p.id, ctx);
    }
};


template <>
struct hstd::JsonSerde<org::imm::ImmAdapter> {
    static json to_json(org::imm::ImmAdapter const& it) {
        return json(it.id.getReadableId());
    }
    static org::imm::ImmAdapter from_json(json const& j) {
        throw logic_assertion_error::init(
            "org::ImmAdapter does not support deserialization.");
    }
};

template <typename T>
struct hstd::JsonSerde<org::imm::ImmAdapterT<T>> {
    static json to_json(org::imm::ImmAdapterT<T> const& it) {
        return json(it.id.getReadableId());
    }
    static org::imm::ImmAdapterT<T> from_json(json const& j) {
        throw logic_assertion_error::init(
            "org::ImmAdapterT<T> does not support deserialization.");
    }
};

template <>
struct std::formatter<org::imm::ImmPathStep>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::imm::ImmPathStep& p, FormatContext& ctx) const {
        return hstd::ReflPathFormatter<org::imm::ImmReflPathTag>{}.format(
            p.path, ctx);
    }
};

template <>
struct std::hash<org::imm::ImmPathStep> {
    std::size_t operator()(
        org::imm::ImmPathStep const& step) const noexcept {
        hstd::AnyHasher<hstd::Str> hasher;
        std::size_t                result = 0;
        for (int i = 0; i < step.path.path.size(); ++i) {
            org::imm::ImmReflPathItemBase const& it = step.path.path.at(i);
            hstd::hax_hash_combine(result, i);
            if (it.isAnyKey()) {
                hstd::hax_hash_combine(result, hasher(it.getAnyKey().key));
            } else {
                hstd::hax_hash_combine(result, it);
            }
        }
        return result;
    }
};

template <>
struct std::hash<org::imm::ImmPath> {
    std::size_t operator()(org::imm::ImmPath const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.root);
        hstd::hax_hash_combine(result, it.path);
        return result;
    }
};


namespace org::details {
inline org::imm::ImmAstContext* ___get_context(
    org::imm::ImmAstContext::Ptr p) {
    return p.get();
}
inline org::imm::ImmAstEditContext* ___get_context(
    org::imm::ImmAstEditContext& p) {
    return &p;
}

inline bool ___is_debug(org::imm::ImmAstEditContext& p) {
    return p.ctx.lock()->debug->TraceState;
}
inline bool ___is_debug(org::imm::ImmAstContext::Ptr p) {
    return p->debug->TraceState;
}
} // namespace org::details

#define AST_EDIT_TRACE() ::org::details::___is_debug(ctx)

#define AST_EDIT_MSG(...)                                                 \
    if (AST_EDIT_TRACE()) {                                               \
        ::org::details::___get_context(ctx)->message(__VA_ARGS__);        \
    }
