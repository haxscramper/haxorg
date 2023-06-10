#include "exportersimplesexpr.hpp"
#include <hstd/stdlib/strutils.hpp>

void ExporterSimpleSExpr::visit(Res& res, In<sem::Org> org) {

    switch (org->getKind()) {
#define __case(__Kind) case OrgSemKind::__Kind:
        EACH_SEM_ORG_LEAF_KIND(__case) {
            res = string(escape_for_write(org.as<sem::Leaf>()->text));
            break;
        }
#undef __case
        default: {
            Res inner = SemSet{OrgSemKind::Subtree, OrgSemKind::ListItem}
                                .contains(org->getKind())
                          ? b::stack()
                          : b::line();

            if (SemSet{
                    OrgSemKind::Paragraph,
                    OrgSemKind::MarkQuote,
                    OrgSemKind::Bold,
                    OrgSemKind::Par,
                }
                    .contains(org->getKind())) {
                res = b::line({string(to_string(org->getKind()))});

                for (const auto& it : org->subnodes) {
                    res->add(string(" "));
                    res->add(visit(it));
                }
            } else {
                visitDispatch(inner, org);
                res = b::line({
                    string(
                        to_string(org->getKind())
                        + (inner->isStack() ? " " : "")),
                    inner,
                });
            }
        }
    }
}
