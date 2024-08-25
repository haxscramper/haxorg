#ifndef EXPORTERHTML_HPP
#define EXPORTERHTML_HPP

#include <haxorg/exporters/Exporter.hpp>
#include <hstd/wrappers/hstd_extra/textlayouter.hpp>
#include <concepts>


struct ExporterHtml : public Exporter<ExporterHtml, layout::BlockId> {
    using Base = Exporter<ExporterHtml, layout::BlockId>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    bool newlineToSpace = false;

    using Res    = layout::BlockId;
    using LytStr = layout::LytStr;

    layout::SimpleStringStore store;
    layout::BlockStore        b;

    ExporterHtml() : store{&b} {}
    Res newRes(CR<sem::SemId<sem::Org>> id) { return Res::Nil(); }
    Res string(Str const& str) { return b.text(store.str(str)); }

    template <sem::IsOrg T>
    void visit(Res& res, sem::SemId<T> org) {
        visitDispatch(res, org);
        if (res.isNil()) {
            res = string(
                "TODO in convert visit [" + fmt1(org->getKind()) + "]");
        }
    }

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
    }

    void visitAnnotatedParagraph(
        Res&                        res,
        In<sem::AnnotatedParagraph> tree) {
        res = lineSubnodes(tree);
    }

    void visitSubtree(Res& res, In<sem::Subtree> tree);

    void visitStmtList(Res& res, In<sem::StmtList> doc) {
        res = stackSubnodes(doc);
    }

    void visitVerbatim(Res& res, In<sem::Verbatim> verb) {
        res = lineSubnodes(verb);
    }

    void visitFootnote(Res& res, In<sem::Footnote> note) {
        res = lineWrap("sup", {string("["_ss + note->tag + "]"_ss)});
    }

    void visitBold(Res& res, In<sem::Bold> bold) {
        res = lineWrap("b", {lineSubnodes(bold)});
    }

    void visitMonospace(Res& res, In<sem::Monospace> bold) {
        res = lineWrap("tt", {lineSubnodes(bold)});
    }

    void visitItalic(Res& res, In<sem::Italic> bold) {
        res = lineWrap("i", {lineSubnodes(bold)});
    }

    void visitMarkQuote(Res& res, In<sem::MarkQuote> mark) {
        res = b.line({string("\""), lineSubnodes(mark), string("\"")});
    }

    void visitTimeRange(Res& res, In<sem::TimeRange> range) {
        res = b.line({eval(range->from), string("--"), eval(range->to)});
    }

    void visitLink(Res& res, In<sem::Link> link);

    void visitTime(Res& res, In<sem::Time> time) {
        if (time->isStatic()) {
            res = string(fmt("[{}]", time->getStatic().time.format()));
        } else {
            res = string(time->getDynamic().expr);
        }
    }

    void visitDocument(Res& res, In<sem::Document> doc);

    void visitNewline(Res& res, In<sem::Newline> doc) {
        if (newlineToSpace) {
            res = string(Str(" "));
        } else {
            res = string(doc->text);
        }
    }


#define __leaf(__Kind)                                                    \
    void visit##__Kind(Res& res, In<sem::__Kind> word) {                  \
        res = string(word->text);                                         \
    }


    __leaf(Space);
    __leaf(Word);
    __leaf(RawText);
    __leaf(Punctuation);
    __leaf(Placeholder);
    __leaf(BigIdent);

#undef __leaf
};

extern template class Exporter<ExporterHtml, layout::BlockId>;

#endif // EXPORTERHTML_HPP
