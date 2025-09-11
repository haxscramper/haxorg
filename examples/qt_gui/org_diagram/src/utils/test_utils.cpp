#include "test_utils.hpp"
#include <hstd/stdlib/Ranges.hpp>
#include "common.hpp"

std::string test::makeItemText(const DiaNodeItemParams& conf) {
    return hstd::fmt(
        R"(
{} {}
    :properties:
    :prop_json:haxorg_diagram_position: {}
    :prop_args:haxorg_diagram_node:
    :end:
)",
        hstd::Str{"*"}.repeated(conf.level),
        conf.itemName,
        hstd::to_json_eval(conf.pos).dump());
}

std::string test::makeLayerText(
    const DiaNodeLayerParams&           layer,
    const hstd::Vec<DiaNodeItemParams>& items) {
    return hstd::fmt(
        R"(
* {}
{}
)",
        layer.layerName,
        items
            | hstd::rv::transform(
                [](DiaNodeItemParams const& it) -> std::string {
                    return makeItemText(it);
                })
            | hstd::rv_intersperse_newline_join);
}

void test::visualizeTestDiff(
    QObject*                   obj,
    const ScopeV12DiagramDiff& scope) {
    auto gv = getEditMappingGraphviz(
        scope.srcAdapter, scope.dstAdapter, scope.edits);
    gv.render(getDebugFile(obj, "edits.png"));
    gv.render(
        getDebugFile(obj, "edits.dot"),
        hstd::ext::Graphviz::LayoutType::Dot,
        hstd::ext::Graphviz::RenderFormat::DOT);
}
