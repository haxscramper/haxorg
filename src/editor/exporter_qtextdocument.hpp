#ifndef EXPORTERQTEXTDOCUMENT_HPP
#define EXPORTERQTEXTDOCUMENT_HPP

#include <exporters/Exporter.hpp>
#include <QTextDocument>
#include <QTextCursor>

struct ExporterQTextDocument : public Exporter<ExporterQTextDocument> {
    using Base = Exporter<ExporterQTextDocument>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    SPtr<QTextDocument>  document;
    QTextCursor          cursor;
    Vec<QTextCharFormat> styles;
    void write(QString const& str) { cursor.insertText(str); }
    void mergeFmt(QTextCharFormat const& format) {
        styles.push_back(cursor.charFormat());
        cursor.mergeCharFormat(format);
    }

    void popFmt() { cursor.setCharFormat(styles.pop_back_v()); }


    struct SB {
        QTextCharFormat newFormat;

        SB& italic(bool set = true) {
            newFormat.setFontItalic(set);
            return *this;
        }

        SB& bold() {
            newFormat.setFontWeight(QFont::Bold);
            return *this;
        }

        SB& weight(int weight) {
            newFormat.setFontWeight(weight);
            return *this;
        }

        SB& size(qreal s) {
            newFormat.setFontPointSize(s);
            return *this;
        }

        operator QTextCharFormat() { return newFormat; }
    };

    ExporterQTextDocument()
        : document(new QTextDocument()), cursor(document.get()) {}

#define __leaf(__Kind)                                                    \
    void visit##__Kind(export_type&, In<sem::__Kind> word) {              \
        write(QString::fromStdString(word->text));                        \
    }

    EACH_SEM_ORG_LEAF_KIND(__leaf)

#undef __leaf


    void eachSub(In<sem::Subtree> tree) {
        export_type r;
        for (const auto& it : tree->subnodes) { visit(r, it); }
    }

    void visit(QTextCharFormat const& format, sem::SemId<sem::Org> tree) {
        export_type r;
        mergeFmt(format);
        visit(r, tree);
        popFmt();
    }

    void visitTime(export_type& r, In<sem::Time> time) {}

    void visitTimeRange(export_type& r, In<sem::TimeRange> range) {
        visitTime(r, range->from);
        write("--");
        visitTime(r, range->to);
    }

    void visitSubtree(export_type& r, In<sem::Subtree> tree);

    template <sem::IsOrg T>
    void visitField(export_type& r, char const*, CVec<T> sub) {
        for (const auto& s : sub) { visit(r, s); }
    }

    template <sem::IsOrg T>
    void visitField(export_type& r, char const*, CR<Opt<T>> sub) {
        if (sub) { visit(r, *sub); }
    }

    template <sem::NotOrg T>
    void visitField(export_type&, char const* name, CR<T> t) {}

    template <typename T>
    void visit(export_type& res, sem::SemId<T> const& arg) {
        visitDispatch(res, arg.asOrg());
    }
};

extern template class Exporter<ExporterQTextDocument>;

#endif // EXPORTERQTEXTDOCUMENT_HPP
