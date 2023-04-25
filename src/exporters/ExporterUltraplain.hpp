#include <exporters/Exporter.hpp>

struct ExporterUltraplain : public Exporter<ExporterUltraplain, QString> {
#define __ExporterBase Exporter<ExporterUltraplain, QString>
    EXPORTER_USING()
#undef __ExporterBase

    void visitSubnode(QString& res, int idx, In<sem::Org> const& org) {
        visit(res, org);
    }

    void visitLink(QString& res, In<sem::Link> link);

#define __visit(__Kind)                                                   \
    void visit##__Kind(QString& res, In<sem::__Kind> const& leaf) {       \
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
