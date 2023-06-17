#include "exportersubtreestructure.hpp"

#include <exporters/ExporterUltraplain.hpp>

json ExporterSubtreeStructure::newRes(In<sem::Subtree> tree) {
    json result = json::object();

    return result;
}

void ExporterSubtreeStructure::visitStructuralCommon(
    json&        j,
    In<sem::Org> node) {
    json subtrees = json::array();
    for (const auto& subnode : node->subnodes) {
        if (subnode->is(OrgSemKind::Subtree)) {
            json sub;
            visit(sub, subnode);
            subtrees.push_back(sub);
        }
    }

    if (!subtrees.empty()) {
        j["subtrees"] = subtrees;
    }
}

void ExporterSubtreeStructure::visitSubtree(
    json&            j,
    In<sem::Subtree> tree) {
    j         = newRes(tree);
    j["name"] = ExporterUltraplain::toStr(tree->title);
    visitStructuralCommon(j, tree);
}

void ExporterSubtreeStructure::visitDocument(
    json&             j,
    In<sem::Document> doc) {
    j = newRes(doc);
    visitStructuralCommon(j, doc);
}
