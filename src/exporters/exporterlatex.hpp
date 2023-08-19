#pragma once

#include <exporters/Exporter.hpp>
#include <hstd/wrappers/textlayouter.hpp>

struct ExporterLatex : public Exporter<ExporterLatex, layout::Block::Ptr> {
    using Base = Exporter<ExporterLatex, layout::Block::Ptr>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    using Res    = layout::Block::Ptr;
    using b      = layout::Block;
    using LytStr = layout::LytStr;

    layout::SimpleStringStore store;

    DECL_DESCRIBED_ENUM(
        SubtreeCmd,
        part,
        chapter,
        section,
        subsection,
        subsubsection,
        paragraph,
        subparagraph);

    QString getLatexClass(Opt<ExporterLatex::In<sem::Document>> doc);
    Opt<SubtreeCmd> getSubtreeCommand(
        ExporterLatex::In<sem::Subtree> tree);
    QString      getTreeWrapCommand(SubtreeCmd cmd, bool before);
    Opt<QString> getRefKind(sem::SemId id);

    Res string(QString const& str) { return b::text(store.str(str)); }

    Res visit(int value) {
        __visit_eval_scope(value);
        return string(to_string(value));
    }

    Res visit(CR<Str> value) {
        __visit_eval_scope(value);
        return string(escape_for_write(value));
    }

    Res visit(sem::SemId org);

    template <sem::NotOrg T>
    void visit(Res& res, CR<T> value) {
        res = b::line({string(
            demangle(typeid(T).name())
            + escape_for_write(to_string(value)))});
    }

    template <typename T>
    void visitField(Res& res, char const* name, CR<T> value) {
        __visit_field_scope(res, name, value);
    }

    template <typename T>
    void visit(Res& res, CVec<T> value) {
        __visit_value(res, value);
        res = b::stack();
        for (const auto& it : value) {
            res->add(visit(it));
        }
    }


    static QString escape(QString const& value);

    void addWrap(
        Res&           res,
        QString const& open,
        QString const& close,
        QString const& arg);

    void addWrap(
        Res&           res,
        QString const& open,
        QString const& close,
        Res const&     arg);

    Res command(QString const& name, Vec<QString> const& args = {});
    Res command(QString const& name, Vec<Res> const& args);
    Res command(
        QString const&      name,
        Vec<QString> const& opts,
        Vec<QString> const& args);
    Res command(
        QString const&  name,
        Vec<Res> const& opts,
        Vec<Res> const& args);

    Vec<Res> subnodes(sem::SemId nodes) {
        Vec<Res> res;
        for (const auto& it : nodes->subnodes) {
            res.push_back(visit(it));
        }
        return res;
    }


    void visitNewline(Res& res, In<sem::Newline> item);
    void visitSpace(Res& res, In<sem::Space> item);
    void visitWord(Res& res, In<sem::Word> item);
    void visitRawText(Res& res, In<sem::RawText> item);
    void visitPunctuation(Res& res, In<sem::Punctuation> item);
    void visitPlaceholder(Res& res, In<sem::Placeholder> item);
    void visitMonospace(Res& res, In<sem::Monospace> monospace);
    void visitBigIdent(Res& res, In<sem::BigIdent> item);
    void visitFootnote(Res& res, In<sem::Footnote> footnote);
    void visitDocument(Res& res, In<sem::Document> value);
    void visitSubtree(Res& res, In<sem::Subtree> tree);
    void visitParagraph(Res& res, In<sem::Paragraph> par);
    void visitTime(Res& res, In<sem::Time> time);
    void visitTimeRange(Res& res, In<sem::TimeRange> range);
    void visitBold(Res& res, In<sem::Bold> bold);
    void visitItalic(Res& res, In<sem::Italic> italic);
    void visitVerbatim(Res& res, In<sem::Verbatim> verb);
    void visitQuote(Res& res, In<sem::Quote> quote);
    void visitLink(Res& res, In<sem::Link> link);
    void visitList(Res& res, In<sem::List> list);
    void visitListItem(Res& res, In<sem::ListItem> item);
    void visitTextSeparator(Res& res, In<sem::TextSeparator> sep);
    void visitHashTag(Res& res, In<sem::HashTag> tag);
    void visitEscaped(Res& res, In<sem::Escaped> escaped);
    void visitUnderline(Res& res, In<sem::Underline> under);
    void visitSymbol(Res& res, In<sem::Symbol> sym);
    void visitCenter(Res& res, In<sem::Center> center);
    void visitExport(Res& res, In<sem::Export> exp);
    void visitEmpty(Res& res, In<sem::Empty> empty);
};

extern template class Exporter<ExporterLatex, layout::Block::Ptr>;

template <>
struct value_domain<ExporterLatex::SubtreeCmd>
    : value_domain_ungapped<
          ExporterLatex::SubtreeCmd,
          ExporterLatex::SubtreeCmd::part,
          ExporterLatex::SubtreeCmd::subparagraph> {};
