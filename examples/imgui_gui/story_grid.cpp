#include "story_grid.hpp"

#include <haxorg/sem/ImmOrgEdit.hpp>
#include "imgui_utils.hpp"

Vec<GridAction> render_story_grid(
    GridDocument const& doc,
    GridConfig const&   conf) {
    Vec<GridAction> result;

    return result;
}

void story_grid_loop(GLFWwindow* window, sem::SemId<sem::Org> node) {
    GridModel          model;
    org::ImmAstContext start;
    model.history.push_back(GridState{
        .ast = start.init(node),
    });

    while (!glfwWindowShouldClose(window)) {
        frame_start();
        Vec<GridAction> updates = render_story_grid(
            model.document, model.conf);
        frame_end(window);
        if (!updates.empty()) {
            for (auto const& update : updates) { model.apply(update); }
            model.updateDocument();
        }
    }
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

void GridModel::updateDocument() {
    document.rows = buildRows(
        getCurrentState().ast.getRootAdapter(), conf);
}

void GridModel::apply(const GridAction& act) {
    switch (act.getKind()) {
        case GridAction::Kind::EditCell: {
            auto edit = act.getEditCell();
            org::ImmAstVersion vNext = getCurrentState().ast.getEditVersion(
                [&](org::ImmAstContext& ast, org::ImmAstEditContext& ctx)
                    -> org::ImmAstReplaceGroup {
                    org::ImmAstReplaceGroup result;
                    result.incl(org::replaceNode(
                        edit.cell.origin,
                        ast.add(
                            sem::asOneNode(
                                sem::parseString(edit.cell.value)),
                            ctx),
                        ctx));
                    return result;
                });
            history.push_back(GridState{
                .ast = vNext,
            });
            break;
        }
    }
}
