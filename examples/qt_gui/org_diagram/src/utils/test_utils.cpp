#include "test_utils.hpp"
#include <hstd/stdlib/Ranges.hpp>
#include "common.hpp"
#include <haxorg/sem/ImmOrg.hpp>

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

test::ScopeV12DiagramDiff::ScopeV12DiagramDiff(
    const std::string& src,
    const std::string& dst) {
    HSLOG_INFO("test", "src:\n", src);
    HSLOG_INFO("test", "dst:\n", dst);

    manager.addDocument(src);
    manager.addDocument(dst);

    org::imm::ImmAdapter::TreeReprConf conf;
    conf.with_field(&org::imm::ImmSubtree::properties);

    HSLOG_INFO(
        "test",
        "srcRoot:\n",
        hstd::indent(getRootV1().treeRepr(conf).toString(false), 2));

    HSLOG_INFO(
        "test",
        "dstRoot:\n",
        hstd::indent(getRootV2().treeRepr(conf).toString(false), 2));

    srcAdapter = FromDocument(dia_context, getRootV1());
    dstAdapter = FromDocument(dia_context, getRootV2());
    edits      = getEdits(srcAdapter, dstAdapter, DiaEditConf{});

    HSLOG_INFO(
        "test",
        "srcAdapter:\n",
        hstd::indent(srcAdapter.format().toString(false), 2));

    HSLOG_INFO(
        "test",
        "dstAdapter:\n",
        hstd::indent(dstAdapter.format().toString(false), 2));

    log_collection("test", hstd::log::severity_level::trace, edits).end();
}
