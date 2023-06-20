#ifndef EXPORTERQTEXTDOCUMENT_HPP
#define EXPORTERQTEXTDOCUMENT_HPP

#include <exporters/Exporter.hpp>
#include <QTextDocument>
#include <QTextCursor>

struct ExporterQTextDocument
    : public Exporter<ExporterQTextDocument, int> {
    using Base = Exporter<ExporterQTextDocument, int>;
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
    void visit##__Kind(int&, In<sem::__Kind> word) { write(word->text); }

    EACH_SEM_ORG_LEAF_KIND(__leaf)

#undef __leaf


    void eachSub(In<sem::Subtree> tree) {
        int r = 0;
        for (const auto& it : tree->subnodes) {
            visit(r, it);
        }
    }

    void visit(QTextCharFormat const& format, sem::SemId tree) {
        int r = 0;
        mergeFmt(format);
        visit(r, tree);
        popFmt();
    }

    void visitTime(int& r, In<sem::Time> time) {
        if (time->isStatic()) {
            write(time->getStatic().time.toString(Qt::ISODate));
        }
    }

    void visitTimeRange(int& r, In<sem::TimeRange> range) {
        visit(r, range->from);
        write("--");
        visit(r, range->to);
    }

    void visitSubtree(int& r, In<sem::Subtree> tree);

    template <sem::IsOrg T>
    void visitField(int& r, char const*, CVec<T> sub) {
        for (const auto& s : sub) {
            visit(r, s);
        }
    }

    template <sem::IsOrg T>
    void visitField(int& r, char const*, CR<Opt<T>> sub) {
        if (sub) {
            visit(r, *sub);
        }
    }

    template <sem::NotOrg T>
    void visitField(int&, char const* name, CR<T> t) {
        write(name + (": " + demangle(typeid(t).name())));
    }
};

#endif // EXPORTERQTEXTDOCUMENT_HPP
