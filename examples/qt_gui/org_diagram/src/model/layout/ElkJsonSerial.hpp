#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Opt.hpp>


namespace hstd {
template <DescribedRecord T, bool WithNullFields>
struct JsonSerdeDescribedRecordBaseEx {
    static json to_json(T const& obj) {
        json result = json::object();

        hstd::for_each_field_value_with_bases(
            obj, [&]<typename F>(char const* name, F const& value) {
                if (WithNullFields
                    || !hstd::value_metadata<F>::isNil(value)) {
                    result[name] = JsonSerde<
                        std::remove_cvref_t<F>>::to_json(value);
                }
            });

        return result;
    }

    static T from_json(json const& j) {
        T result = SerdeDefaultProvider<T>::get();
        for_each_field_with_bases<T>([&](auto const& field) {
            if (j.contains(field.name)) {
                result.*field.pointer = JsonSerde<
                    std::remove_cvref_t<decltype(result.*field.pointer)>>::
                    from_json(j[field.name]);
            }
        });

        return result;
    }
};
} // namespace hstd

namespace dia::layout::elk {


using json = nlohmann::json;

class PortProperties {
  public:
    hstd::Opt<json>      port;
    hstd::Opt<hstd::Str> portConstraints;
    hstd::Opt<hstd::Str> portAlignment;
    hstd::Opt<bool>      allowNonFlowPortsToSwitchSides;

    BOOST_DESCRIBE_CLASS(
        PortProperties,
        (),
        (port,
         portConstraints,
         portAlignment,
         allowNonFlowPortsToSwitchSides),
        (),
        ());
};

class NodeProperties {
  public:
    hstd::Opt<hstd::Str> portConstraints;
    hstd::Opt<hstd::Str> portAlignment;

    BOOST_DESCRIBE_CLASS(
        NodeProperties,
        (),
        (portConstraints, portAlignment),
        (),
        ());
};

class Point {
  public:
    double x;
    double y;

    BOOST_DESCRIBE_CLASS(Point, (), (x, y), (), ());
};

class Label {
  public:
    hstd::Opt<hstd::Str>        id;
    hstd::Opt<double>           x;
    hstd::Opt<double>           y;
    hstd::Opt<double>           width;
    hstd::Opt<double>           height;
    hstd::Opt<hstd::Str>        text;
    hstd::Opt<hstd::Vec<Label>> labels;
    hstd::Opt<json>             layoutOptions;

    BOOST_DESCRIBE_CLASS(
        Label,
        (),
        (id, x, y, width, height, text, labels, layoutOptions),
        (),
        ());
};

class Port {
  public:
    hstd::Str                   id;
    hstd::Opt<double>           x;
    hstd::Opt<double>           y;
    hstd::Opt<double>           width;
    hstd::Opt<double>           height;
    hstd::Opt<hstd::Vec<Label>> labels;
    hstd::Opt<PortProperties>   properties;
    hstd::Opt<json>             layoutOptions;

    BOOST_DESCRIBE_CLASS(
        Port,
        (),
        (id, x, y, width, height, labels, properties, layoutOptions),
        (),
        ());
};

class EdgeSection {
  public:
    hstd::Opt<hstd::Str>            id;
    Point                           startPoint;
    Point                           endPoint;
    hstd::Opt<hstd::Vec<Point>>     bendPoints;
    hstd::Opt<hstd::Str>            incomingShape;
    hstd::Opt<hstd::Str>            outgoingShape;
    hstd::Opt<hstd::Vec<hstd::Str>> incomingSections;
    hstd::Opt<hstd::Vec<hstd::Str>> outgoingSections;

    BOOST_DESCRIBE_CLASS(
        EdgeSection,
        (),
        (id,
         startPoint,
         endPoint,
         bendPoints,
         incomingShape,
         outgoingShape,
         incomingSections,
         outgoingSections),
        (),
        ());
};

class Edge {
  public:
    hstd::Str                         id;
    hstd::Opt<hstd::Str>              source;
    hstd::Opt<hstd::Str>              sourcePort;
    hstd::Opt<hstd::Str>              target;
    hstd::Opt<hstd::Str>              targetPort;
    hstd::Opt<hstd::Vec<hstd::Str>>   sources;
    hstd::Opt<hstd::Vec<hstd::Str>>   targets;
    hstd::Opt<Point>                  sourcePoint;
    hstd::Opt<Point>                  targetPoint;
    hstd::Opt<hstd::Vec<Point>>       bendPoints;
    hstd::Opt<hstd::Vec<EdgeSection>> sections;
    hstd::Opt<hstd::Vec<Label>>       labels;
    hstd::Opt<hstd::Vec<Point>>       junctionPoints;
    hstd::Opt<json>                   layoutOptions;

    BOOST_DESCRIBE_CLASS(
        Edge,
        (),
        (id,
         source,
         sourcePort,
         target,
         targetPort,
         sources,
         targets,
         sourcePoint,
         targetPoint,
         bendPoints,
         sections,
         labels,
         junctionPoints,
         layoutOptions),
        (),
        ());
};

class Node {
  public:
    hstd::Str                   id;
    hstd::Opt<double>           x;
    hstd::Opt<double>           y;
    hstd::Opt<double>           width;
    hstd::Opt<double>           height;
    hstd::Opt<hstd::Str>        type;
    hstd::Opt<hstd::Vec<Port>>  ports;
    hstd::Opt<hstd::Vec<Label>> labels;
    hstd::Opt<hstd::Vec<Node>>  children;
    hstd::Opt<hstd::Vec<Edge>>  edges;
    hstd::Opt<NodeProperties>   properties;
    hstd::Opt<json>             layoutOptions;

    BOOST_DESCRIBE_CLASS(
        Node,
        (),
        (id,
         x,
         y,
         width,
         height,
         type,
         ports,
         labels,
         children,
         edges,
         properties,
         layoutOptions),
        (),
        ());
};

class Graph {
  public:
    hstd::Str                   id;
    hstd::Opt<double>           x;
    hstd::Opt<double>           y;
    hstd::Opt<double>           width;
    hstd::Opt<double>           height;
    hstd::Opt<json>             layoutOptions;
    hstd::Opt<hstd::Vec<Node>>  children;
    hstd::Opt<hstd::Vec<Edge>>  edges;
    hstd::Opt<hstd::Vec<Port>>  ports;
    hstd::Opt<hstd::Vec<Label>> labels;

    BOOST_DESCRIBE_CLASS(
        Graph,
        (),
        (id,
         x,
         y,
         width,
         height,
         layoutOptions,
         children,
         edges,
         ports,
         labels),
        (),
        ());
};

void validate(Graph const& graph);

} // namespace dia::layout::elk


#define SPECIALIZE_WO_NULL_FIELDS(__name)                                 \
    template <>                                                           \
    struct hstd::JsonSerde<dia::layout::elk::__name>                      \
        : hstd::JsonSerdeDescribedRecordBaseEx<                           \
              dia::layout::elk::__name,                                   \
              false> {};

SPECIALIZE_WO_NULL_FIELDS(Graph);
SPECIALIZE_WO_NULL_FIELDS(PortProperties);
SPECIALIZE_WO_NULL_FIELDS(NodeProperties);
SPECIALIZE_WO_NULL_FIELDS(Point);
SPECIALIZE_WO_NULL_FIELDS(Port);
SPECIALIZE_WO_NULL_FIELDS(EdgeSection);
SPECIALIZE_WO_NULL_FIELDS(Edge);
SPECIALIZE_WO_NULL_FIELDS(Node);
