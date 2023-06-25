#include "exporterlatex.hpp"

void ExporterLatex::visitDocument(Res& res, In<sem::Document> value) {
    __visit_specific_kind(res, value);
    res = b::stack();
    for (const auto& it : value->subnodes) {
        res->add(visit(it));
    }
}
