#include <exporters/ExporterUltraplain.hpp>
#include <hstd/stdlib/strutils.hpp>

#include <exporters/Exporter.cpp>

template class Exporter<ExporterUltraplain, std::string>;


std::string ExporterUltraplain::toStr(sem::SemId<sem::Org> node) {
    return strip(
        ExporterUltraplain{}.evalTop(node), CharSet{' '}, CharSet{' '});
}

void ExporterUltraplain::visitLink(std::string& res, In<sem::Link> link) {
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
                break;
            }
            default: {
            }
        }
    }
}

void ExporterUltraplain::visitSubtree(
    std::string&     res,
    In<sem::Subtree> tree) {

    res += Str("*").repeated(tree->level);
    res += " ";
    visit(res, tree->title);
    if (!tree->subnodes.empty()) {
        res += "\n";
        for (auto const& sub : tree->subnodes) { visit(res, sub); }
    }
}

void ExporterUltraplain::visitTime(std::string& res, In<sem::Time> time) {
    if (time->isStatic()) {
        res += (time->getTimeKind() == sem::Time::TimeKind::Dynamic ? "<" : "[");
        res += time->getStatic().time.format(UserTime::Format::OrgFormat);
        res += (time->getTimeKind() == sem::Time::TimeKind::Dynamic ? ">" : "]");
    }
}
