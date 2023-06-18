#include "exportersubtreestructure.hpp"

#include <exporters/ExporterUltraplain.hpp>
#include <exporters/ExporterJson.hpp>
#include <boost/mp11.hpp>


json ExporterSubtreeStructure::newRes(In<sem::Subtree> tree) {
    json result = ExporterJson().newRes(tree);

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
    j["isSubtree"] = true;

    using Md = describe_members<sem::Subtree, mod_any_access>;
    mp_for_each<Md>([&](auto const& field) {
        if (field.name != "subnodes" && field.name != "title") {
            ExporterJson().visitField(
                j,
                field.name,
                (*static_cast<sem::Subtree const*>(tree.get()))
                    .*field.pointer);
        }
    });
}

void ExporterSubtreeStructure::visitDocument(
    json&             j,
    In<sem::Document> doc) {
    j              = newRes(doc);
    j["name"]      = "<document>";
    j["isSubtree"] = false;
    visitStructuralCommon(j, doc);
}
