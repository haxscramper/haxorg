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
    Res newRes(CR<sem::SemId<sem::Org>> id) { return Res::Nil(); }
    Res string(Str const& str) { return b.text(store.str(str)); }

    void visit(Res& res, sem::SemId<sem::Org> org) {
        visitDispatch(res, org);

        if (res.isNil()) {
            res = string(
                "TODO in convert visit [" + fmt1(org->getKind()) + "]");
        }
    }

    Res eval(sem::SemId<sem::Org> org) {
        Res tmp = Res::Nil();
        visit(tmp, org);
        return tmp;
    }

    template <typename T>
    Res eval(CR<T> it) {
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


    Res multiString(Str const& str) {
        Res res = b.stack();
        for (const auto& line : str.split("\n")) {
            b.add_at(res, string(line));
        }

        return res;
    }

    template <typename T>
    void visitField(Res& res, char const* name, CR<T> it) {}

    Res stackSubnodes(sem::SemId<sem::Org> doc) {
        Res res = b.stack();
        for (const auto& it : doc->subnodes) { b.add_at(res, eval(it)); }
        return res;
    }

    Res lineSubnodes(sem::SemId<sem::Org> doc) {
        Res res = b.line();
        for (const auto& it : doc->subnodes) { b.add_at(res, eval(it)); }
        return res;
    }

    Res directionWrap(bool isStack, Str tag, CVec<Res> items) {
        Res res = isStack ? b.stack() : b.line();
        b.add_at(res, string("<" + tag + ">"_ss));
        b.add_at(res, items);
        b.add_at(res, string("</" + tag + ">"_ss));
        return res;
    }

    Res stackWrap(Str const& tag, CVec<Res> items) {
        return directionWrap(true, tag, items);
    }

    Res lineWrap(Str const& tag, CVec<Res> items) {
        return directionWrap(false, tag, items);
    }

    void visitParagraph(Res& res, In<sem::Paragraph> tree) {
        res = lineSubnodes(tree);
        //        res = lineWrap("p", {lineSubnodes(tree)});
    }


    Res createTocList(sem::SemId<sem::Org> node);

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
        res = b.line({eval(range->from), string("--"), eval(range->to)});
    }

    void visitLink(Res& res, In<sem::Link> link) {
        if (link->description) {
            res = eval(link->description.value());
        } else {
            res = string("");
        }
    }

    void visitTime(Res& res, In<sem::Time> time) {
        if (time->isStatic()) {
            res = string(fmt("[{}]", time->getStatic().time.format()));
        } else {
            res = string(time->getDynamic().expr);
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
