#include "test_utils.hpp"
#include <hstd/stdlib/Ranges.hpp>

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
