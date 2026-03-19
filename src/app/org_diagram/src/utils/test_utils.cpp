#include "test_utils.hpp"
#include <hstd/stdlib/Ranges.hpp>
#include "common.hpp"
#include <haxorg/imm/ImmOrg.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>

std::string test::makeItemText(DiaNodeItemParams const& conf) {
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
    DiaNodeLayerParams const&           layer,
    hstd::Vec<DiaNodeItemParams> const& items) {
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
    ScopeV12DiagramDiff const& scope) {
    auto gv = getEditMappingGraphviz(
        scope.srcAdapter, scope.dstAdapter, scope.edits);
    gv.render(getDebugFile(obj, "edits.png"));
    gv.render(
        getDebugFile(obj, "edits.dot"),
        hstd::ext::Graphviz::LayoutType::Dot,
        hstd::ext::Graphviz::RenderFormat::DOT);
}

test::ScopeV12DiagramDiff::ScopeV12DiagramDiff(
    std::string const& src,
    std::string const& dst) {
    HSLOG_INFO("src:\n{}", src);
    HSLOG_INFO("dst:\n{}", dst);

    version_store->addDocument(src);
    version_store->addDocument(dst);

    org::imm::ImmAdapter::TreeReprConf conf;
    conf.with_field(&org::imm::ImmSubtree::properties);

    HSLOG_INFO(
        "srcRoot:\n{}",
        hstd::indent(getRootV1().treeRepr(conf).toString(false), 2));

    HSLOG_INFO(
        "dstRoot:\n{}",
        hstd::indent(getRootV2().treeRepr(conf).toString(false), 2));

    srcAdapter = FromDocument(dia_context, getRootV1());
    dstAdapter = FromDocument(dia_context, getRootV2());
    edits      = getEdits(srcAdapter, dstAdapter, DiaEditConf{});

    HSLOG_INFO(
        "srcAdapter:\n{}",
        hstd::indent(srcAdapter.format().toString(false), 2));

    HSLOG_INFO(
        "dstAdapter:\n{}",
        hstd::indent(dstAdapter.format().toString(false), 2));

    hstd::log::log_sequential_collection(edits).as_trace().end();
}

test::ScopeDiaContextEdits::TextSetResult test::ScopeDiaContextEdits::
    setText(std::string const& text) {
    HSLOG_INFO("text:\n{}", text);
    TextSetResult res;

    res.rootIndex = version_store->addDocument(text);

    org::imm::ImmAdapter::TreeReprConf conf;
    conf.with_field(&org::imm::ImmSubtree::properties);

    HSLOG_INFO(
        "srcRoot:\n{}",
        hstd::indent(
            version_store->getImmRoot(res.rootIndex)
                .treeRepr(conf)
                .toString(false),
            2));

    res.imm = version_store->getImmRoot(res.rootIndex);
    res.dia = version_store->buildTree(res.imm);


    HSLOG_INFO(
        "srcAdapter:\n{}",
        hstd::indent(res.dia.format().toString(false), 2));

    return res;
}
