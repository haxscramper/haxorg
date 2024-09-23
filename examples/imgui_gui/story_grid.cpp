#include "story_grid.hpp"

#include <haxorg/sem/ImmOrgEdit.hpp>

void story_grid_loop(GLFWwindow* window, sem::SemId<sem::Org> node) {

}


GridRow buildRow(
    org::ImmAdapterT<org::ImmSubtree> tree,
    const GridConfig&                 conf) {
    GridRow result;
    result.title = buildCell(tree.getTitle(), conf.widths.title);
    for (auto const& sub : tree.subAs<org::ImmList>()) {
        if (sub.isDescriptionList()) {
            for (auto const& item : sub.subAs<org::ImmListItem>()) {
                auto flat = flatWords(item.getHeader().value());
                for (auto const& word : flat) {
                    if (word == "story_event") {
                        result.columns.event = buildCell(
                            item.at(0), conf.widths.event);
                    } else if (word == "story_location") {
                        result.columns.location = buildCell(
                            item.at(0), conf.widths.event);
                    } else {
                        throw logic_unreachable_error::init(
                            fmt("Unexpected story grid keyword {}", word));
                    }
                }
            }
        }
    }

    for (auto const& sub : tree.subAs<org::ImmSubtree>()) {
        result.nested.push_back(buildRow(sub, conf));
    }

    return result;
}

Vec<GridRow> buildRows(org::ImmAdapter root, const GridConfig& conf) {
    Vec<GridRow> result;
    for (auto const& tree : root.subAs<org::ImmSubtree>()) {
        result.push_back(buildRow(tree, conf));
    }

    return result;
}

GridCell buildCell(org::ImmAdapter adapter, int width) {
    GridCell result;
    result.value  = join(" ", flatWords(adapter));
    result.origin = adapter;
    return result;
}
