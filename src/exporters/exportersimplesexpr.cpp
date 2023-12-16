#include "exportersimplesexpr.hpp"
import std.stdlib.strutils;

#include <exporters/Exporter.cpp>

template class Exporter<ExporterSimpleSExpr, layout::BlockId>;


void ExporterSimpleSExpr::visit(Res& res, sem::SemId org) {

    switch (org->getKind()) {
#define __case(__Kind) case OrgSemKind::__Kind:
        EACH_SEM_ORG_LEAF_KIND(__case) {
            res = string(escape_for_write(org.getAs<sem::Leaf>()->text));
            break;
        }
#undef __case
        default: {
            Res inner = SemSet{OrgSemKind::Subtree, OrgSemKind::ListItem}
                                .contains(org->getKind())
                          ? b.stack()
                          : b.line();

            if (SemSet{
                    OrgSemKind::Paragraph,
                    OrgSemKind::MarkQuote,
                    OrgSemKind::Bold,
                    OrgSemKind::Par,
                }
                    .contains(org->getKind())) {
                res = b.line({string(std::format("{}", org->getKind()))});

                for (const auto& it : org->subnodes) {
                    b.add_at(res, string(" "));
                    b.add_at(res, eval(it));
                }
            } else {
                visitDispatch(inner, org);
                res = b.line({
                    string(
                        std::format("{}", org->getKind())
                        + (b.at(inner).isStack() ? " " : "")),
                    inner,
                });
            }
        }
    }
}
