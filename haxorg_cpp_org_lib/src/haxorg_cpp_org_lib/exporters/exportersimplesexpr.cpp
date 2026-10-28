#include "exportersimplesexpr.hpp"
#include <hstd_cpp_lib/stdlib/algorithms/strutils.hpp>

#include <haxorg_cpp_org_lib/exporters/Exporter.cpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/OptFormatter.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/VariantFormatter.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/VecFormatter.hpp>

template class org::algo::Exporter<ExporterSimpleSExpr, layout::BlockId>;


void org::algo::ExporterSimpleSExpr::visit(Res& res, sem::SemId<sem::Org> org) {
    if (org.isNil()) {
        res = string("<nil>");
    } else {
        switch (org->getKind()) {
#define __case(__Kind) case org::sem::OrgSemKind::__Kind:
            EACH_SEM_ORG_LEAF_KIND(__case) {
                res = string(escape_for_write(org.getAs<sem::Leaf>()->text));
                break;
            }
#undef __case
            default: {
                Res inner = SemSet{org::sem::OrgSemKind::Subtree, org::sem::OrgSemKind::ListItem}
                                    .contains(org->getKind())
                              ? b.stack()
                              : b.line();

                if (SemSet{
                        org::sem::OrgSemKind::Paragraph,
                        org::sem::OrgSemKind::MarkQuote,
                        org::sem::OrgSemKind::Bold,
                        org::sem::OrgSemKind::Par,
                    }
                        .contains(org->getKind())) {
                    res = b.line({string(fmt::format("{}", org->getKind()))});

                    for (const auto& it : org->subnodes) {
                        b.add_at(res, string(" "));
                        b.add_at(res, eval(it));
                    }
                } else {
                    visitDispatch(inner, org);
                    res = b.line({
                        string(
                            fmt::format("{}", org->getKind())
                            + (b.at(inner).isStack() ? " " : "")),
                        inner,
                    });
                }
            }
        }
    }
}
