#pragma once

#include "elk_jni_wrapper.hpp"
#include <memory>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/JsonUse.hpp>
#include <hstd/ext/graph/graph_base.hpp>


namespace hstd::ext::graph::elk {

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
    hstd::Vec<Node>             children;
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
    hstd::Vec<Node>             children;
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

} // namespace hstd::ext::graph::elk


#define SPECIALIZE_WO_NULL_FIELDS(__name)                                 \
    template <>                                                           \
    struct hstd::JsonSerde<hstd::ext::graph::elk::__name>                 \
        : hstd::JsonSerdeDescribedRecordBaseEx<                           \
              hstd::ext::graph::elk::__name,                              \
              false> {};

SPECIALIZE_WO_NULL_FIELDS(Graph);
SPECIALIZE_WO_NULL_FIELDS(PortProperties);
SPECIALIZE_WO_NULL_FIELDS(NodeProperties);
SPECIALIZE_WO_NULL_FIELDS(Point);
SPECIALIZE_WO_NULL_FIELDS(Port);
SPECIALIZE_WO_NULL_FIELDS(EdgeSection);
SPECIALIZE_WO_NULL_FIELDS(Edge);
SPECIALIZE_WO_NULL_FIELDS(Node);


namespace hstd::ext::graph::elk {

class ElkLayoutManager {
  private:
    std::unique_ptr<elk_jni::ElkLayoutEngine> elkEngine;
    std::string                               classPath;

  public:
    ElkLayoutManager(std::string const& classPath = JNI_ELK_LIB_JAR_PATH)
        : elkEngine(std::make_unique<elk_jni::ElkLayoutEngine>())
        , classPath{classPath} {
        LOGIC_ASSERTION_CHECK(
            elkEngine->initialize(classPath),
            "Failed to initialize ELK layout engine");
    }

    ~ElkLayoutManager() {
        if (elkEngine) { // elkEngine->shutdown();
        }
    }

    std::string layoutDiagram(std::string const& graphJson);
    elk::Graph  layoutDiagram(elk::Graph const& graph);
};

} // namespace hstd::ext::graph::elk
