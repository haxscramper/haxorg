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

    void visitDocument(Res& res, In<sem::Document> value);
    void visitSubtree(Res& res, In<sem::Subtree> tree);
    void visitParagraph(Res& res, In<sem::Paragraph> par);
    void visitTime(Res& res, In<sem::Time> time);

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

    Res command(QString const& name, Vec<QString> const& args);
    Res command(QString const& name, Vec<Res> const& args);
    Res command(
        QString const&      name,
        Vec<QString> const& opts,
        Vec<QString> const& args);
    Res command(
        QString const&  name,
        Vec<Res> const& opts,
        Vec<Res> const& args);

    Res stackSubnodes(sem::SemId doc) {
        Res res = b::stack();
        for (const auto& it : doc->subnodes) {
            res->add(visit(it));
        }
        return res;
    }

    Res lineSubnodes(sem::SemId doc) {
        Res res = b::line();
        for (const auto& it : doc->subnodes) {
            res->add(visit(it));
        }
        return res;
    }

#define __leaf(__Kind)                                                    \
    void visit##__Kind(Res& res, In<sem::__Kind> word) {                  \
        __visit_specific_kind(res, word);                                 \
        res = string(escape(word->text));                                 \
    }

    EACH_SEM_ORG_LEAF_KIND(__leaf)

#undef __leaf
};
