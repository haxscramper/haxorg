#pragma once

#include <exporters/Exporter.hpp>
#include <hstd/stdlib/Json.hpp>

struct PandocRes {
    Vec<json> unpacked;
    json      toJson() const {
        json res = json::array();
        for (auto const& it : unpacked) {
            res.push_back(it);
        }
        return res;
    }
    PandocRes() {}
    PandocRes(json value) : unpacked({value}) {}
};

struct ExporterPandoc : public Exporter<ExporterPandoc, PandocRes> {
    using Base = Exporter<ExporterPandoc, PandocRes>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    template <typename T>
    PandocRes newRes(CVec<T>) {
        return json::array();
    }

    template <typename T>
    PandocRes newRes(CR<T>) {
        return json::object();
    }

    template <typename T>
    void visitField(PandocRes& res, const char* name, CR<T> field) {
        res = json();
    }

    template <typename T>
    PandocRes visit(CR<T> arg) {
        PandocRes res = newRes(arg);
        visit(res, arg);
        return res;
    }

    PandocRes newRes(sem::SemId org);

    template <typename T>
    PandocRes newRes(sem::SemIdT<T> org) {
        return newRes(org.toId());
    }

    json content(sem::SemId id, SemSet const& skip = SemSet{});

    void visitDocument(PandocRes& res, In<sem::Document> doc);
    void visitNewline(PandocRes& res, In<sem::Newline> item);
    void visitSpace(PandocRes& res, In<sem::Space> item);
    void visitWord(PandocRes& res, In<sem::Word> item);
    void visitRawText(PandocRes& res, In<sem::RawText> item);
    void visitPunctuation(PandocRes& res, In<sem::Punctuation> item);
    void visitPlaceholder(PandocRes& res, In<sem::Placeholder> item);
    void visitMonospace(PandocRes& res, In<sem::Monospace> monospace);
    void visitBigIdent(PandocRes& res, In<sem::BigIdent> item);
    void visitFootnote(PandocRes& res, In<sem::Footnote> footnote);
    void visitSubtree(PandocRes& res, In<sem::Subtree> tree);
    void visitParagraph(PandocRes& res, In<sem::Paragraph> par);
    void visitTime(PandocRes& res, In<sem::Time> time);
    void visitTimeRange(PandocRes& res, In<sem::TimeRange> range);
    void visitBold(PandocRes& res, In<sem::Bold> bold);
    void visitItalic(PandocRes& res, In<sem::Italic> italic);
    void visitVerbatim(PandocRes& res, In<sem::Verbatim> verb);
    void visitQuote(PandocRes& res, In<sem::Quote> quote);
    void visitLink(PandocRes& res, In<sem::Link> link);
    void visitList(PandocRes& res, In<sem::List> list);
    void visitListItem(PandocRes& res, In<sem::ListItem> item);
    void visitTextSeparator(PandocRes& res, In<sem::TextSeparator> sep);
    void visitHashTag(PandocRes& res, In<sem::HashTag> tag);
    void visitEscaped(PandocRes& res, In<sem::Escaped> escaped);
    void visitUnderline(PandocRes& res, In<sem::Underline> under);
    void visitSymbol(PandocRes& res, In<sem::Symbol> sym);
    void visitCenter(PandocRes& res, In<sem::Center> center);
    void visitExport(PandocRes& res, In<sem::Export> exp);
    void visitEmpty(PandocRes& res, In<sem::Empty> empty);
};
