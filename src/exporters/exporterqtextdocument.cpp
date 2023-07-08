#include "exporterqtextdocument.hpp"

#include <exporters/Exporter.cpp>
template class Exporter<ExporterQTextDocument, int>;

void ExporterQTextDocument::visitSubtree(int& r, In<sem::Subtree> tree) {
    Func<bool(sem::SemId)> hasNonTreeSub;


    visit(SB{}.bold().size(18 - tree->level), tree->title);
    if (tree->subnodes.empty()
        || tree->subnodes.at(0)->getKind() == OrgSemKind::Subtree) {
        write("\n");
    }

    eachSub(tree);
}
