#ifndef EXPORTERMINDMAP_HPP
#define EXPORTERMINDMAP_HPP

#include "hstd/system/aux_utils.hpp"
#include <exporters/Exporter.hpp>
#include <hstd/wrappers/graphviz.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Json.hpp>
#include <boost/graph/adjacency_list.hpp>

struct ExporterMindMap : public Exporter<ExporterMindMap, std::monostate> {
    using Base = Exporter<ExporterMindMap, std::monostate>;

#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase


    struct DocEntry;
    struct DocSubtree;

    /// List of known documents that were encountered during processing
    Vec<sem::SemIdT<sem::Document>> documents;

    /// Outgoing documentation link that targets some documentable entry.
    struct DocLink {
        struct Entry {
            SPtr<DocEntry> entry;
        };

        struct Subtree {
            SPtr<DocSubtree> subtree;
        };

        Opt<SPtr<DocSubtree>> parent;
        SUB_VARIANTS(Kind, Resolved, resolved, getKind, Entry, Subtree);
        Resolved resolved;
        /// Description of the link -- taken from description lists that
        /// have links in the tags. Description in the link node itself is
        /// ignored
        Opt<sem::SemId> description;
    };

    /// Single mappable entry in the document that represents
    /// either paragraph of text or some other entry to be
    /// rendered into the mind map graph
    struct DocEntry : SharedPtrApi<DocEntry> {
        /// Text block for documentable entry
        sem::SemId content = sem::SemId::Nil();
        /// Resolved outgoing links from the documentable entry
        Vec<DocLink>          outgoing;
        Opt<SPtr<DocSubtree>> parent = std::nullopt;
        int                   id;
        static int            counter;
        DocEntry() : id(++counter) {}
    };

    /// Simplified tree structure of the document(s) that
    /// contains only doc entry nodes and wrapping clusters.
    ///
    /// Each subtree is turned into a cluster that might contain any number
    /// of nested clusters, ordered and unordered documentable entries.
    struct DocSubtree : SharedPtrApi<DocSubtree> {
        /// Subtrees that were physically nested inside of
        /// the original subtree, or, for top-level document group, a list
        /// of nested documents
        Vec<DocSubtree::Ptr> subtrees;
        Opt<DocSubtree::Ptr> parent;

        /// Original subtree node that content was mapped from -- subtree
        /// or document
        sem::SemId original = sem::SemId::Nil();

        /// Ordered list of documentable entries that were generated from
        /// top-level paragraphs in the tree
        Vec<DocEntry::Ptr> ordered;
        /// Unordered entries -- comments, footnotes, that were attached to
        /// some items in the subtree.
        Vec<DocEntry::Ptr> unordered;

        /// Outgoing links attached to the subtree. Defined using
        /// description lists or drawer annotations.
        Vec<DocLink> outgoing;

        int        id;
        static int counter;
        DocSubtree() : id(++counter) {}
    };

    void eachSubtree(
        DocSubtree::Ptr             startRoot,
        Func<void(DocSubtree::Ptr)> cb);
    void eachEntry(
        DocSubtree::Ptr                                   startRoot,
        Func<void(DocEntry::Ptr, DocSubtree::Ptr const&)> cb);


    // Catch-all implementation for the field visitor. We only need to
    // iterate over subnodes for this exporter, offshoot branches with
    // different extra data bits are not relevant.
    template <sem::NotOrg T>
    void visitField(std::monostate& s, char const*, CR<T> field) {}

    template <typename T>
    void visitField(std::monostate& s, char const* n, CR<Opt<T>> opt) {
        if (opt) {
            visitField(s, n, *opt);
        }
    }

    template <typename T>
    void visitField(std::monostate& s, char const* n, CVec<T> vec) {
        for (const auto& it : vec) {
            visitField(s, n, it);
        }
    }


    DocSubtree::Ptr      root;
    Vec<DocSubtree::Ptr> stack;

    void visitSubtree(std::monostate& s, sem::SemIdT<sem::Subtree> ptr);
    void visitDocument(std::monostate& s, sem::SemIdT<sem::Document> doc);

    void visitEnd(sem::SemId doc);


    UnorderedMap<sem::SemId, DocEntry::Ptr>   entriesOut;
    UnorderedMap<sem::SemId, DocSubtree::Ptr> subtreesOut;

    Opt<DocLink> getResolved(
        sem::SemId                  node,
        Opt<DocSubtree::Ptr> const& parent);


    struct VertexProp {
        struct Subtree {
            DocSubtree::Ptr subtree;
        };

        struct Entry {
            DocEntry::Ptr entry;
            Opt<int>      order;
        };

        SUB_VARIANTS(Kind, Data, data, getKind, Subtree, Entry);
        Data data;
    };

    struct EdgeProp {
        /// Mind map entry that is nested inside of the subtree
        struct PlacedIn {};
        /// Nested subtree structure
        struct NestedIn {};
        /// Mind map entry that refers to some other element
        struct RefersTo {
            DocLink target;
        };

        /// \brief Some part of the subtree content internally refers to
        /// another target node
        struct InternallyRefers {};

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            NestedIn,
            InternallyRefers,
            RefersTo,
            PlacedIn);
        Data data;
    };

    struct GraphProp {};

    using Graph = boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::bidirectionalS,
        VertexProp,
        EdgeProp,
        GraphProp>;

    using GraphTraits     = boost::graph_traits<Graph>;
    using VertDesc        = typename GraphTraits::vertex_descriptor;
    using EdgeDesc        = typename GraphTraits::edge_descriptor;
    using VertBundledType = typename boost::vertex_bundle_type<
        Graph>::type;
    using EdgeBundledType = typename boost::edge_bundle_type<Graph>::type;

    Graph   toGraph();
    QString toGraphML(CR<Graph>);
    QString toGraphviz(CR<Graph>);

    /// \brief export mind map in a tree-like structure that closely maps
    /// to the original data structure
    json toJsonTree();
    json toJsonGraph();
    json toJsonGraph(CR<Graph> g);
    json toJsonGraphNode(CR<Graph> g, CR<VertDesc> n);
    json toJsonGraphEdge(CR<Graph> g, CR<EdgeDesc> e);

    QString getId(VertexProp const& prop);
    QString getId(sem::SemId id);
    QString getId(DocEntry::Ptr const& entry);
    QString getId(DocSubtree::Ptr const& subtree);
};

extern template class Exporter<ExporterMindMap, std::monostate>;

#endif // EXPORTERMINDMAP_HPP
