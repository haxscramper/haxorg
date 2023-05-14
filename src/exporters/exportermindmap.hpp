#ifndef EXPORTERMINDMAP_HPP
#define EXPORTERMINDMAP_HPP

#include "hstd/system/aux_utils.hpp"
#include <boost/graph/graphviz.hpp>
#include <exporters/Exporter.hpp>
#include <hstd/wrappers/graphviz.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Json.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/subgraph.hpp>

struct ExporterMindMap : public Exporter<ExporterMindMap, std::monostate> {
    using Base = Exporter<ExporterMindMap, std::monostate>;

#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase


    struct DocEntry;
    struct DocSubtree;

    /// List of known documents that were encountered during processing
    Vec<sem::Document::Ptr> documents;

    /// Outgoing documentation link that targets some documentable entry.
    struct DocLink {
        struct Entry {
            SPtr<DocEntry> entry;
        };

        struct Subtree {
            SPtr<DocSubtree> subtree;
        };

        SUB_VARIANTS(Kind, Resolved, resolved, getKind, Entry, Subtree);
        Resolved resolved;
        /// Description of the link -- taken from description lists that
        /// have links in the tags. Description in the link node itself is
        /// ignored
        Opt<sem::Org::Ptr> description;
    };

    /// Single mappable entry in the document that represents
    /// either paragraph of text or some other entry to be
    /// rendered into the mind map graph
    struct DocEntry : SharedPtrApi<DocEntry> {
        /// Text block for documentable entry
        sem::Org::Ptr content;
        /// Resolved outgoing links from the documentable entry
        Vec<DocLink> outgoing;
        int          id;
        static int   counter;
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

        /// Original subtree node that content was mapped from -- subtree
        /// or document
        sem::Org::Ptr original;

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
        DocSubtree::Ptr           startRoot,
        Func<void(DocEntry::Ptr)> cb);


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
    void visitSubtree(std::monostate& s, CR<sem::Subtree::Ptr> ptr);
    void visitDocument(std::monostate& s, CR<sem::Document::Ptr> doc);

    void visitEnd(In<sem::Org> doc);


    SortedMap<int, DocEntry::Ptr>   entriesOut;
    SortedMap<int, DocSubtree::Ptr> subtreesOut;
    Opt<DocLink>                    getResolved(sem::Org::Ptr node);

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
        struct PlacedIn {};
        struct NestedIn {};
        struct RefersTo {
            DocLink target;
        };

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            NestedIn,
            RefersTo,
            PlacedIn);
        Data data;
    };

    struct GraphProp {};

    using BaseVertexProp = boost::
        property<boost::vertex_attribute_t, VertexProp>;

    using BaseEdgeProp = boost::property<
        boost::edge_index_t,
        int,
        boost::property<boost::edge_attribute_t, EdgeProp>>;

    using BaseGraphProp = boost::property<
        boost::graph_name_t,
        std::string,
        boost::property<
            boost::graph_graph_attribute_t,
            GraphProp,
            boost::property<
                boost::graph_vertex_attribute_t,
                GraphProp,
                boost::
                    property<boost::graph_edge_attribute_t, GraphProp>>>>;

    using BaseGraph = boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::directedS,
        BaseVertexProp,
        BaseEdgeProp,
        BaseGraphProp>;

    using Graph = boost::subgraph<BaseGraph>;

    using GraphTraits     = boost::graph_traits<Graph>;
    using VertDesc        = typename GraphTraits::vertex_descriptor;
    using VertBundledType = typename boost::vertex_bundle_type<
        Graph>::type;
    using EdgeBundledType = typename boost::edge_bundle_type<Graph>::type;

    Graph   toGraph();
    QString toGraphML(CR<Graph>);
    QString toGraphviz(CR<Graph>);

    Graphviz::Graph toCGraph();
    json            toJson();
};

#endif // EXPORTERMINDMAP_HPP
