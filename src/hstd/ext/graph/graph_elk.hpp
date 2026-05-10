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

class Options {
  public:
    json data;
    // TODO: add options to insert add/remove values for the fields storing
    // list of identifiers.

    void init() {
        if (data.is_null()) { data = json::object(); }
    }

    void set(hstd::Str const& key, hstd::Str const& value) {
        init();
        data[key] = value;
    }

    void set(hstd::Str const& key, double const& value) {
        init();
        data[key] = value;
    }

    void set(hstd::Str const& key, int const& value) {
        init();
        data[key] = value;
    }

#if false
#    include <algorithm>
#    include <stdexcept>
#    include <string>
#    include <string_view>
#    include <vector>

#    include <lexy/action/parse.hpp>
#    include <lexy/callback.hpp>
#    include <lexy/dsl.hpp>
#    include <lexy/input/string_input.hpp>

class IdentifierList {
public:
    static void add(std::string& value, std::string const& ident) {
        auto items = parse(value);
        if (!containsIn(items, ident)) {
            items.push_back(ident);
            value = format(items);
        }
    }

    static void remove(std::string& value, std::string const& ident) {
        auto items = parse(value);
        auto it = std::find(items.begin(), items.end(), ident);
        if (it == items.end()) {
            throw std::out_of_range("Identifier not present: " + ident);
        }
        items.erase(it);
        value = format(items);
    }

    static bool contains(std::string const& value, std::string const& ident) {
        return containsIn(parse(value), ident);
    }

private:
    struct ident_p {
        static constexpr auto rule = lexy::dsl::capture(lexy::dsl::while_one(lexy::dsl::ascii::word));
        static constexpr auto value = lexy::as_string<std::string>;
    };

    struct value_p {
        static constexpr auto whitespace = lexy::dsl::ascii::space;

        static constexpr auto bracketed =
            lexy::dsl::lit_c<'['>
            + lexy::dsl::opt(lexy::dsl::list(lexy::dsl::p<ident_p>, lexy::dsl::sep(lexy::dsl::comma)))
            + lexy::dsl::lit_c<']'>;

        static constexpr auto single = lexy::dsl::p<ident_p>;

        static constexpr auto rule = (bracketed | single) + lexy::dsl::eof;

        static constexpr auto value = lexy::callback<std::vector<std::string>>(
            [](std::optional<std::vector<std::string>> items) {
                if (items) {
                    return std::move(*items);
                }
                return std::vector<std::string>{};
            },
            [](std::string item) {
                return std::vector<std::string>{std::move(item)};
            });
    };

    static std::vector<std::string> parse(std::string_view text) {
        auto input = lexy::string_input<lexy::utf8_encoding>(text.data(), text.size());
        auto result = lexy::parse<value_p>(input, lexy::noop);
        if (!result) {
            throw std::invalid_argument("Malformed identifier list");
        }
        return result.value();
    }

    static std::string format(std::vector<std::string> const& items) {
        if (items.empty()) {
            return "[]";
        }
        if (items.size() == 1) {
            return items[0];
        }

        std::string out = "[";
        for (std::size_t i = 0; i < items.size(); ++i) {
            if (i != 0) {
                out += ", ";
            }
            out += items[i];
        }
        out += "]";
        return out;
    }

    static bool containsIn(std::vector<std::string> const& items, std::string const& ident) {
        return std::find(items.begin(), items.end(), ident) != items.end();
    }
};
#endif
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
    Options                     opts;

    BOOST_DESCRIBE_CLASS(
        Label,
        (),
        (id, x, y, width, height, text, labels, opts),
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
    Options                     opts;

    BOOST_DESCRIBE_CLASS(
        Port,
        (),
        (id, x, y, width, height, labels, properties, opts),
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

class EdgeElkLayoutData {
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
    Options                           opts;

    BOOST_DESCRIBE_CLASS(
        EdgeElkLayoutData,
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
         opts),
        (),
        ());
};

class EdgeVisual
    : public layout::IEdgeVisualAttribute
    , public EdgeElkLayoutData {};

class NodeElkLayoutData {
  public:
    hstd::Str                    id;
    hstd::Opt<double>            x;
    hstd::Opt<double>            y;
    hstd::Opt<double>            width;
    hstd::Opt<double>            height;
    hstd::Opt<hstd::Str>         type;
    hstd::Vec<Port>              ports;
    hstd::Vec<Label>             labels;
    hstd::Vec<NodeElkLayoutData> children;
    hstd::Vec<EdgeElkLayoutData> edges;
    hstd::Opt<NodeProperties>    properties;
    Options                      opts;

    NodeElkLayoutData* setSize(double width, double height) {
        this->width  = width;
        this->height = height;
        opts.set("nodeLabels.placement", "[H_CENTER, V_TOP, OUTSIDE]");
        opts.set("portLabels.placement", "NEXT_TO_PORT_OF_POSSIBLE");
        opts.set("edgeLabels.placement", "CENTER");
        opts.set("elk.nodeSize.constraints", "MINIMUM_SIZE");
        opts.set(
            "elk.nodeSize.minimum", hstd::fmt("({}, {})", width, height));
        opts.set("elk.margins", 0);
        return this;
    }

    BOOST_DESCRIBE_CLASS(
        NodeElkLayoutData,
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
         opts),
        (),
        ());
};

class NodeVisual
    : public layout::IVertexVisualAttribute
    , public NodeElkLayoutData {};

class GroupVisual
    : public layout::IGroupVisualAttribute
    , public NodeElkLayoutData {
  public:
    void setOuterPadding(geometry::Padding const& pad) override {
        logic_todo_impl();
    }

    hstd::Opt<geometry::Padding> getOuterPadding() const override {
        logic_todo_impl();
    }

    std::string getStableId() const override { return local.name; }

    struct SharedCtx {
        hstd::SPtr<layout::LayoutRun> run;
    };

    struct LocalCtx {
        hstd::Str name;
    };

    hstd::SPtr<SharedCtx> shared;
    LocalCtx              local;

    GroupVisual(hstd::SPtr<SharedCtx> const& ctx, hstd::Str const& name)
        : layout::IGroupVisualAttribute{ctx->run}, shared{ctx} {}


    auto&       get_run() { return shared->run; }
    auto const& get_run() const { return shared->run; }

    static hstd::SPtr<GroupVisual> newRootGraph(
        hstd::SPtr<layout::LayoutRun> run,
        hstd::Str const&              name = "");

    hstd::SPtr<GroupVisual> addNewNativeSubgroup(
        VertexID const& parent,
        VertexID const& id) {
        auto res = std::make_shared<GroupVisual>(
            shared, hstd::fmt("cola_{}", id));
        std::ignore = run->addNestedGroup(parent, id, res);
        return res;
    }


    hstd::SPtr<NodeVisual> addVertex(
        VertexID const& parent,
        VertexID const& id) {
        auto vattr  = std::make_shared<NodeVisual>();
        std::ignore = get_run()->addNestedVertex(parent, id, vattr);
        return vattr;
    }

    hstd::SPtr<EdgeVisual> addEdge(EdgeID const& id) {
        auto res = std::make_shared<EdgeVisual>();
        get_run()->addEdge(id, res);
        return res;
    }
};

class NodeLayout
    : public layout::IVertexLayoutAttribute
    , public NodeElkLayoutData {};

class GroupLayout
    : public layout::IVertexLayoutAttribute
    , public NodeElkLayoutData {};


class GraphElkLayoutData {
  public:
    hstd::Str                               id;
    hstd::Opt<double>                       x;
    hstd::Opt<double>                       y;
    hstd::Opt<double>                       width;
    hstd::Opt<double>                       height;
    hstd::Opt<json>                         opts;
    hstd::Vec<NodeElkLayoutData>            children;
    hstd::Opt<hstd::Vec<EdgeElkLayoutData>> edges;
    hstd::Opt<hstd::Vec<Port>>              ports;
    hstd::Opt<hstd::Vec<Label>>             labels;

    BOOST_DESCRIBE_CLASS(
        GraphElkLayoutData,
        (),
        (id, x, y, width, height, opts, children, edges, ports, labels),
        (),
        ());
};

void validate(GraphElkLayoutData const& graph);

class ElkLayoutAlgorithm : public layout::IPlacementAlgorithm {
  public:
    class Manager {
      private:
        std::unique_ptr<elk_jni::ElkLayoutEngine> elkEngine;
        std::string                               classPath;

      public:
        Manager(std::string const& classPath = JNI_ELK_LIB_JAR_PATH)
            : elkEngine(std::make_unique<elk_jni::ElkLayoutEngine>())
            , classPath{classPath} {
            LOGIC_ASSERTION_CHECK(
                elkEngine->initialize(classPath),
                "Failed to initialize ELK layout engine");
        }

        ~Manager() {
            if (elkEngine) { // elkEngine->shutdown();
            }
        }

        std::string layoutDiagram(std::string const& graphJson);
        elk::GraphElkLayoutData layoutDiagram(
            elk::GraphElkLayoutData const& graph);
    };

    hstd::SPtr<Manager> manager;

    ElkLayoutAlgorithm(
        hstd::SPtr<layout::LayoutRun> const& run,
        hstd::SPtr<Manager> const&           manager)
        : layout::IPlacementAlgorithm{run} {}

  public:
    Result runSingleLayout(VertexID const& group) override;

    hstd::Opt<double> x;
    hstd::Opt<double> y;
    hstd::Opt<double> width;
    hstd::Opt<double> height;
    hstd::Opt<json>   opts;
};


} // namespace hstd::ext::graph::elk


#define SPECIALIZE_WO_NULL_FIELDS(__name)                                 \
    template <>                                                           \
    struct hstd::JsonSerde<hstd::ext::graph::elk::__name>                 \
        : hstd::JsonSerdeDescribedRecordBaseEx<                           \
              hstd::ext::graph::elk::__name,                              \
              false> {};

SPECIALIZE_WO_NULL_FIELDS(GraphElkLayoutData);
SPECIALIZE_WO_NULL_FIELDS(PortProperties);
SPECIALIZE_WO_NULL_FIELDS(NodeProperties);
SPECIALIZE_WO_NULL_FIELDS(Point);
SPECIALIZE_WO_NULL_FIELDS(Port);
SPECIALIZE_WO_NULL_FIELDS(EdgeSection);
SPECIALIZE_WO_NULL_FIELDS(EdgeElkLayoutData);
SPECIALIZE_WO_NULL_FIELDS(NodeElkLayoutData);

template <>
struct hstd::JsonSerde<hstd::ext::graph::elk::Options> {
    static json to_json(hstd::ext::graph::elk::Options const& it) {
        return it.data;
    }
    static hstd::ext::graph::elk::Options from_json(json const& j) {
        return {j};
    }
};
