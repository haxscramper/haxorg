#include "ImmOrgGraphBoost.hpp"

#include <boost/graph/graphml.hpp>
#include <boost/graph/graphviz.hpp>

boost::dynamic_properties org::graph::toGraphvizDynamicProperties(
    const MapGraph& g) {
    boost::dynamic_properties dp;

    dp //
        .property(
            "node_id",
            make_transform_value_property_map<std::string>(
                [&](org::graph::MapNode const& prop) -> std::string {
                    return fmt1(prop.id);
                },
                boost::make_map_vertex_identity_map()))
        .property(
            "splines",
            boost::make_constant_property<org::graph::MapGraph>(
                std::string("polyline")))
        .property(
            "shape",
            boost::make_constant_property<org::graph::MapNode>(
                std::string("rect")))
        .property(
            "color",
            make_transform_value_property_map<std::string>(
                [&](org::graph::MapNodeProp const& prop) -> std::string {
                    return prop.unresolved.empty() ? "green" : "yellow";
                },
                boost::get(boost::vertex_bundle, g)))
        .property(
            "label",
            make_transform_value_property_map<std::string>(
                [&](org::graph::MapNodeProp const& prop) -> std::string {
                    return fmt("{}", prop.id);
                },
                boost::get(boost::vertex_bundle, g)));

    return dp;
}

void org::graph::bfs_visit(
    const MapGraph&                           g,
    const MapNode&                            start,
    const boost_lambda_bfs_visitor<MapGraph>& visitor,
    const boost_color_map&                    map) {
    boost::breadth_first_search(
        g, start, boost::visitor(visitor).color_map(map.map));
}
