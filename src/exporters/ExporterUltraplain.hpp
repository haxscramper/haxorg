#include <exporters/Exporter.hpp>

struct ExporterUltraplain : public Exporter<ExporterUltraplain, QString> {
#define __ExporterBase Exporter<ExporterUltraplain, QString>
    EXPORTER_USING()
#undef __ExporterBase

    static QString toStr(sem::SemId node);

    void visitLink(QString& res, In<sem::Link> link);

    template <sem::NotOrg T>
    void visit(QString& res, CR<T> value) {}

    template <typename T>
    void visit(QString& res, CVec<T> values) {
        for (const auto& value : values) {
            visit(res, value);
        }
    }

    template <typename T>
    void visit(QString& res, CR<Opt<T>> opt) {
        if (opt) {
            visit(res, *opt);
        }
    }

    template <typename T>
    void visitField(QString& res, const char* name, CR<T> field) {
        visit(res, field);
    }

#define __visit(__Kind)                                                   \
    void visit##__Kind(QString& res, In<sem::__Kind> leaf) {              \
        res += leaf->text;                                                \
    }

    __visit(Word);
    __visit(Space);
    __visit(Punctuation);
    __visit(BigIdent);
    __visit(Placeholder);
    __visit(RawText);
    __visit(Newline);


#undef __visit
};
