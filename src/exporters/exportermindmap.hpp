#ifndef EXPORTERMINDMAP_HPP
#define EXPORTERMINDMAP_HPP

#include <exporters/Exporter.hpp>
#include <hstd/wrappers/graphviz.hpp>
#include <hstd/stdlib/Map.hpp>

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
        Variant<SPtr<DocEntry>, SPtr<DocSubtree>> resolved;
        /// Description of the link -- taken from description lists that
        /// have links in the tags. Description in the link node itself is
        /// ignored
        Opt<sem::Paragraph::Ptr> description;
    };

    /// Single mappable entry in the document that represents
    /// either paragraph of text or some other entry to be
    /// rendered into the mind map graph
    struct DocEntry : SharedPtrApi<DocEntry> {
        /// Text block for documentable entry
        sem::Org::Ptr content;
        /// Resolved outgoing links from the documentable entry
        Vec<DocLink> outgoing;

        int        id = 0;
        static int counter;

        inline DocEntry() : id(++counter) {}
    };

    Vec<DocEntry::Ptr> entryList;

    DocEntry::Ptr newEntry() {
        entryList.push_back(DocEntry::shared());
        return entryList.back();
    }

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
    };


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

    Graphviz::Graph toGraph();
};

#endif // EXPORTERMINDMAP_HPP
