#include "exporter_qtextdocument.hpp"

#include <exporters/Exporter.cpp>
template class Exporter<ExporterQTextDocument>;

void ExporterQTextDocument::visitSubtree(
    export_type&     r,
    In<sem::Subtree> tree) {
    Func<bool(sem::SemId<sem::Org>)> hasNonTreeSub;


    visit(SB{}.bold().size(18 - tree->level), tree->title);
    if (tree->subnodes.empty()
        || tree->subnodes.at(0)->getKind() == OrgSemKind::Subtree) {
        write("\n");
    }

    eachSub(tree);
}
