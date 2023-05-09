#ifndef EXPORTERMINDMAP_HPP
#define EXPORTERMINDMAP_HPP

#include <exporters/Exporter.hpp>
#include <hstd/wrappers/graphviz.hpp>

struct ExporterMindMap : public Exporter<ExporterMindMap, std::monostate> {
    using Base = Exporter<ExporterMindMap, std::monostate>;

#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase


    struct DocEntry;

    /// List of known documents that were encountered during processing
    Vec<sem::Document::Ptr> documents;

    /// Outgoing documentation link that targets some documentable entry.
    struct DocLink {
        sem::Link::Ptr target;
        SPtr<DocEntry> resolved;
        /// Description of the link -- taken from description lists that
        /// have links in the tags. Description in the link node itself is
        /// ignored
        Opt<sem::Paragraph::Ptr> description;
    };

    /// Resolve `Link` or any other node to some doc link. If resolution
    /// fails then empty option is returned.
    Opt<DocLink> resolve(CR<sem::Org::Ptr> node);

    /// Single mappable entry in the document that represents
    /// either paragraph of text or some other entry to be
    /// rendered into the mind map graph
    struct DocEntry : SharedPtrApi<DocEntry> {
        /// Content of the document entry. Either top-level subtree (in
        /// this cases nested elements ought to be ignored for exporting)
        /// or a list of paragraphs/lines/tables etc.
        Vec<sem::Org::Ptr> content;

        int        id = 0;
        static int counter;

        inline DocEntry() : id(++counter) {}
    };

    /// Simplified tree structure of the document(s) that
    /// contains only doc entry nodes and links between the
    /// different parts of the subtree
    struct DocSubtree : SharedPtrApi<DocSubtree> {
        /// Subtrees that were physically nested inside of
        /// the original subtree, or, for top-level document group, a list
        /// of nested documents
        Vec<DocSubtree::Ptr> subtrees;

        /// Original subtree node that content was mapped from -- subtree
        /// or document
        sem::Org::Ptr original;

        /// Document entry associated with the particular subtree. For
        /// leaf-level nodes (or ones that were marked as such for the mind
        /// map) it is filled with the documentable entry from this tree.
        Opt<DocEntry::Ptr> entry;
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

    Graphviz::Graph toGraph();
};

#endif // EXPORTERMINDMAP_HPP
