#include <exporters/ExporterUltraplain.hpp>
#include <hstd/stdlib/strutils.hpp>


QString ExporterUltraplain::toStr(sem::Org::Ptr node) {
    return strip(
        ExporterUltraplain{}.visitTop(node),
        CharSet{QChar(' ')},
        CharSet{QChar(' ')});
}

void ExporterUltraplain::visitLink(QString& res, In<sem::Link> link) {
    if (link->description) {
        visitDispatch(res, *link->description);
    } else {
        switch (link->getLinkKind()) {
            case sem::Link::Kind::Id: {
                res += link->getId().text;
                break;
            }
            case sem::Link::Kind::Footnote: {
                res += link->getFootnote().target;
                break;
            }
            case sem::Link::Kind::Raw: {
                res += link->getRaw().text;
            }
        }
    }
}
