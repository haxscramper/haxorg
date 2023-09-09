#ifndef EXPORTERHTML_HPP
#define EXPORTERHTML_HPP

#include <exporters/Exporter.hpp>
#include <hstd/wrappers/textlayouter.hpp>
#include <concepts>


struct ExporterHtml : public Exporter<ExporterHtml, layout::BlockId> {
    using Base = Exporter<ExporterHtml, layout::BlockId>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase


    using Res    = layout::BlockId;
    using LytStr = layout::LytStr;

    layout::SimpleStringStore store;
    layout::BlockStore        b;

    ExporterHtml() : store{&b} {}
    Res newRes(CR<sem::SemId> id) { return Res::Nil(); }
    Res string(QString const& str) { return b.text(store.str(str)); }

    void visit(Res& res, sem::SemId org) {
        visitDispatch(res, org);

        if (res.isNil()) {
            res = string(
                "TODO in convert visit [" + to_string(org->getKind())
                + "]");
        }
    }

    Res visit(sem::SemId org) {
        Res tmp = Res::Nil();
        visit(tmp, org);
        return tmp;
    }

    template <typename T>
    Res visit(CR<T> it) {
        Res tmp = Res::Nil();
        visit(tmp, it);

        if (tmp.isNil()) {
            tmp = string("TODO " + demangle(typeid(it).name()));
        }

        return tmp;
    }

    template <sem::NotOrg T>
    void visit(Res& res, CR<T> it) {
        res = string(
            demangle(typeid(it).name())
            + " visit of not derived from org");
    }


    Res multiString(QString const& str) {
        Res res = b.stack();
        for (const auto& line : str.split("\n")) {
            b.add_at(res, string(line));
        }

        return res;
    }

    template <typename T>
    void visitField(Res& res, char const* name, CR<T> it) {}

    Res stackSubnodes(sem::SemId doc) {
        Res res = b.stack();
        for (const auto& it : doc->subnodes) {
            b.add_at(res, visit(it));
        }
        return res;
    }

    Res lineSubnodes(sem::SemId doc) {
        Res res = b.line();
        for (const auto& it : doc->subnodes) {
            b.add_at(res, visit(it));
        }
        return res;
    }

    Res directionWrap(bool isStack, QString tag, CVec<Res> items) {
        Res res = isStack ? b.stack() : b.line();
        b.add_at(res, string("<" + tag + ">"));
        b.add_at(res, items);
        b.add_at(res, string("</" + tag + ">"));
        return res;
    }

    Res stackWrap(QString tag, CVec<Res> items) {
        return directionWrap(true, tag, items);
    }

    Res lineWrap(QString tag, CVec<Res> items) {
        return directionWrap(false, tag, items);
    }

    void visitParagraph(Res& res, In<sem::Paragraph> tree) {
        res = lineSubnodes(tree);
        //        res = lineWrap("p", {lineSubnodes(tree)});
    }

    void visitTime(Res& res, In<sem::Time> time);

    Res createTocList(sem::SemId node);

    void visitSubtree(Res& res, In<sem::Subtree> tree);

    void visitStmtList(Res& res, In<sem::StmtList> doc) {
        res = stackSubnodes(doc);
    }

    void visitVerbatim(Res& res, In<sem::Verbatim> verb) {
        res = lineSubnodes(verb);
    }

    void visitMarkQuote(Res& res, In<sem::MarkQuote> mark) {
        res = b.line({string("\""), lineSubnodes(mark), string("\"")});
    }

    void visitTimeRange(Res& res, In<sem::TimeRange> range) {
        res = b.line({visit(range->from), string("--"), visit(range->to)});
    }

    void visitLink(Res& res, In<sem::Link> link) {
        if (link->description) {
            res = visit(link->description.value());
        } else {
            res = string("");
        }
    }

    void visitDocument(Res& res, In<sem::Document> doc);

#define __leaf(__Kind)                                                    \
    void visit##__Kind(Res& res, In<sem::__Kind> word) {                  \
        res = string(word->text);                                         \
    }

    EACH_SEM_ORG_LEAF_KIND(__leaf)

#undef __leaf
};

extern template class Exporter<ExporterHtml, layout::BlockId>;

#endif // EXPORTERHTML_HPP
