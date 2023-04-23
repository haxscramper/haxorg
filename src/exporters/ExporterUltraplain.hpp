#include <exporters/Exporter.hpp>

struct ExporterUltraplain : public Exporter<ExporterUltraplain, QString> {
#define __ExporterBase Exporter<ExporterUltraplain, QString>
    EXPORTER_USING()
#undef __ExporterBase

    void visitSubnode(QString& res, int idx, In<sem::Org> const& org) {
        visit(res, org);
    }

#define __visit(__Kind)                                                   \
    void visit(QString& res, In<sem::__Kind> const& leaf) {               \
        res += leaf->text;                                                \
    }

    __visit(Word);
    __visit(Space);


#undef __visit
};
