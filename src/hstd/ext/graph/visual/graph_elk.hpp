#pragma once

#if ORG_BUILD_WITH_ELK

#    include "elk_jni_wrapper.hpp"
#    include <memory>
#    include <hstd/stdlib/Exception.hpp>
#    include <hstd/stdlib/Vec.hpp>
#    include <hstd/stdlib/Json.hpp>
#    include <hstd/stdlib/Str.hpp>
#    include <hstd/system/reflection.hpp>
#    include <hstd/stdlib/Opt.hpp>
#    include <hstd/stdlib/JsonSerde.hpp>
#    include <hstd/stdlib/JsonUse.hpp>
#    include <hstd/ext/graph/base/graph_base.hpp>
#    include <hstd/ext/graph/visual/graph_visual.hpp>
#    include <hstd/stdlib/Debug.hpp>


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

#    if false
#        include <algorithm>
#        include <stdexcept>
#        include <string>
#        include <string_view>
#        include <vector>

#        include <lexy/action/parse.hpp>
#        include <lexy/callback.hpp>
#        include <lexy/dsl.hpp>
#        include <lexy/input/string_input.hpp>

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
#    endif
};

class Label {
  public:
    hstd::Opt<hstd::Str> id;
    hstd::Opt<double>    x;
    hstd::Opt<double>    y;
    hstd::Opt<double>    width;
    hstd::Opt<double>    height;
    hstd::Opt<hstd::Str> text;
    hstd::Vec<Label>     labels;
    Options              layoutOptions;

    BOOST_DESCRIBE_CLASS(
        Label,
        (),
        (id, x, y, width, height, text, labels, layoutOptions),
        (),
        ());
};

class ElkPortData {
  public:
    hstd::Str                 id;
    hstd::Opt<double>         x;
    hstd::Opt<double>         y;
    hstd::Opt<double>         width;
    hstd::Opt<double>         height;
    hstd::Vec<Label>          labels;
    hstd::Opt<PortProperties> properties;
    Options                   layoutOptions;

    ElkPortData* setWidth(double arg) {
        width = arg;
        return this;
    }

    ElkPortData* setHeight(double arg) {
        height = arg;
        return this;
    }

    ElkPortData* setSize(geometry::Size size) {
        width  = size.width();
        height = size.height();
        return this;
    }

    BOOST_DESCRIBE_CLASS(
        ElkPortData,
        (),
        (id, x, y, width, height, labels, properties, layoutOptions),
        (),
        ());
};

class ElkPortVisualAttribute
    : public ElkPortData
    , public layout::IPortVisualAttribute {


  public:
    void writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {}

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }
};

class ElkPortLayoutAttribute
    : public ElkPortData
    , public layout::IPortLayoutAttribute {
  public:
    void writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {}

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }

    Rect getBBox() const override {
        // port placement may omit some values if they are zeroed out, and
        // potr does not have to have a width/height either.
        return geometry::Rect{
            x.value_or(0),
            y.value_or(0),
            width.value_or(0),
            height.value_or(0),
        };
    }
};

class EdgeSection {
  public:
    hstd::Opt<hstd::Str> id;
    Point                startPoint;
    Point                endPoint;
    hstd::Vec<Point>     bendPoints;
    hstd::Opt<hstd::Str> incomingShape;
    hstd::Opt<hstd::Str> outgoingShape;
    hstd::Vec<hstd::Str> incomingSections;
    hstd::Vec<hstd::Str> outgoingSections;

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

class ElkEdgeData {
  public:
    hstd::Str              id;
    hstd::Opt<hstd::Str>   source;
    hstd::Opt<hstd::Str>   sourcePort;
    hstd::Opt<hstd::Str>   target;
    hstd::Opt<hstd::Str>   targetPort;
    hstd::Vec<hstd::Str>   sources;
    hstd::Vec<hstd::Str>   targets;
    hstd::Vec<EdgeSection> sections;
    hstd::Vec<Label>       labels;
    hstd::Vec<Point>       junctionPoints;
    Options                layoutOptions;

    void validate() {}

    BOOST_DESCRIBE_CLASS(
        ElkEdgeData,
        (),
        (id,
         source,
         sourcePort,
         target,
         targetPort,
         sources,
         targets,
         sections,
         labels,
         junctionPoints,
         layoutOptions),
        (),
        ());
};

class ElkEdgeVisualAttribute
    : public layout::IEdgeVisualAttribute
    , public ElkEdgeData {
  public:
    void writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {}

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }
};

class ElkEdgeLayoutAttribute
    : public layout::IEdgeLayoutAttribute
    , public ElkEdgeData {
  public:
    Path getPath() const override {
        Path res;
        for (auto const& sec : sections) {
            res.moveTo(sec.startPoint);
            for (auto const& point : sec.bendPoints) { res.lineTo(point); }
            res.lineTo(sec.endPoint);
        }

        return res;
    }

    void writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {}

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }
};

class NodeElkLayoutData {
  public:
    hstd::Str                    id;
    hstd::Opt<double>            x;
    hstd::Opt<double>            y;
    hstd::Opt<double>            width;
    hstd::Opt<double>            height;
    hstd::Opt<hstd::Str>         type;
    hstd::Vec<ElkPortData>       ports;
    hstd::Vec<Label>             labels;
    hstd::Vec<NodeElkLayoutData> children;
    hstd::Vec<ElkEdgeData>       edges;
    hstd::Opt<NodeProperties>    properties;
    Options                      layoutOptions;

    void validate() {
        LOGIC_ASSERTION_CHECK_FMT(
            x.has_value() && x.has_value() && x.has_value()
                && x.has_value(),
            "node layout data incomplete ID {}: x={} y={} width={} "
            "height={}",
            id,
            x,
            y,
            width,
            height);
    }

    NodeElkLayoutData* setSize(geometry::Size const& size) {
        return setSize(size.width(), size.height());
    }

    NodeElkLayoutData* setSize(double _width, double _height) {
        this->width  = _width;
        this->height = _height;
        layoutOptions.set(
            "nodeLabels.placement", "[H_CENTER, V_TOP, OUTSIDE]");
        layoutOptions.set(
            "portLabels.placement", "NEXT_TO_PORT_OF_POSSIBLE");
        layoutOptions.set("edgeLabels.placement", "CENTER");
        layoutOptions.set("elk.nodeSize.constraints", "MINIMUM_SIZE");
        layoutOptions.set(
            "elk.nodeSize.minimum",
            hstd::fmt("({}, {})", _width, _height));
        layoutOptions.set("elk.margins", 0);
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
         layoutOptions),
        (),
        ());
};

class ElkNodeVisualAttribute
    : public layout::IVertexVisualAttribute
    , public NodeElkLayoutData {
  public:
    void writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {}

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }
};

class ElkGroupVisualAttribute
    : public layout::IGroupVisualAttribute
    , public NodeElkLayoutData {
  public:
    void writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {}

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }

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

    ElkGroupVisualAttribute(
        hstd::SPtr<SharedCtx> const& ctx,
        hstd::Str const&             name)
        : layout::IGroupVisualAttribute{ctx->run}, shared{ctx} {}


    auto&       get_run() { return shared->run; }
    auto const& get_run() const { return shared->run; }

    static hstd::SPtr<ElkGroupVisualAttribute> newRootGraph(
        hstd::SPtr<layout::LayoutRun> run,
        hstd::Str const&              name = "");

    hstd::SPtr<ElkGroupVisualAttribute> addNewNativeSubgroup(
        EdgeID const& edge) {
        auto id  = run->getNestedVertex(edge);
        auto res = std::make_shared<ElkGroupVisualAttribute>(
            shared, hstd::fmt("cola_{}", id));
        run->setNestedGroupAttribute(edge, res);
        return res;
    }

    hstd::SPtr<ElkNodeVisualAttribute> addVertex(EdgeID const& edge) {
        auto vattr = std::make_shared<ElkNodeVisualAttribute>();
        get_run()->setNestedVertexAttribute(edge, vattr);
        return vattr;
    }

    hstd::SPtr<ElkEdgeVisualAttribute> addEdge(EdgeID const& id) {
        auto res = std::make_shared<ElkEdgeVisualAttribute>();
        get_run()->setEdgeAttribute(id, res);
        LOGIC_ASSERTION_CHECK(
            get_run()->getEdges()->hasEdge(id), get_run()->getDebug(id));
        return res;
    }

    hstd::SPtr<ElkPortVisualAttribute> addPort(PortID const& pid) {
        auto res = std::make_shared<ElkPortVisualAttribute>();
        get_run()->getMPort(pid)->addUniqueAttribute(res);
        return res;
    }
};

class ElkNodeLayoutAttribute
    : public layout::IVertexLayoutAttribute
    , public NodeElkLayoutData {
  public:
    void writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {}

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }

    hstd::SPtr<layout::LayoutRun> run;


    ElkNodeLayoutAttribute(hstd::SPtr<layout::LayoutRun> const& run)
        : run{run} {}

    Rect getBBox() const override {
        return geometry::Rect{
            x.value(),
            y.value(),
            width.value(),
            height.value(),
        };
    }

    visual::VisGroup getVisual(VertexID const& selfId) const override {
        visual::VisGroup res;
        auto             bb = getBBox();
        res.offset          = bb.upper_left();
        res.elements.push_back(
            visual::VisElement{visual::VisElement::RectShape{
                geometry::Rect::FromSize(bb.size())}});

        res.elements.push_back(
            visual::VisElement::FromText(
                run->getGraph()->getVertex(selfId)->getStableId()));

        res.custom.setAttr(
            "inkscape:label",
            hstd::fmt("ELK VERTEX:{}", run->getDebug(selfId)));
        return res;
    }
};

class ElkGroupLayoutAttribute
    : public layout::IGroupLayoutAttribute
    , public NodeElkLayoutData {
  public:
    void writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {}

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }

    geometry::Rect bbox;

    void setBBox(geometry::Rect const& bbox) override {
        this->bbox = bbox;
    }

    Rect getBBox() const override { return bbox; }


    visual::VisGroup getVisual(VertexID const& id) const override;
};


class GraphElkLayoutData {
  public:
    hstd::Str                    id;
    hstd::Opt<double>            x;
    hstd::Opt<double>            y;
    hstd::Opt<double>            width;
    hstd::Opt<double>            height;
    Options                      layoutOptions;
    hstd::Vec<NodeElkLayoutData> children;
    hstd::Vec<ElkEdgeData>       edges;
    hstd::Vec<ElkPortData>       ports;
    hstd::Vec<Label>             labels;

    BOOST_DESCRIBE_CLASS(
        GraphElkLayoutData,
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
            elk::GraphElkLayoutData const&       graph,
            hstd::SPtr<layout::LayoutRun> const& run);
    };

    hstd::SPtr<Manager> manager;

    ElkLayoutAlgorithm(
        hstd::SPtr<layout::LayoutRun> const& run,
        hstd::SPtr<Manager> const&           manager)
        : layout::IPlacementAlgorithm{run}, manager{manager} {
        hstd::logic_assertion_check_not_nil(manager);
    }

  public:
    Result runSingleLayout(VertexID const& group) override;

    hstd::Opt<double> x;
    hstd::Opt<double> y;
    hstd::Opt<double> width;
    hstd::Opt<double> height;
    Options           layoutOptions;
};


} // namespace hstd::ext::graph::elk

template <>
struct hstd::value_metadata<hstd::ext::graph::elk::Options> {
    static bool isNil(hstd::ext::graph::elk::Options const& opts) {
        return opts.data.is_null();
    }

    static bool isEmpty(hstd::ext::graph::elk::Options const& opts) {
        return isNil(opts)
            || ((opts.data.is_array() || opts.data.is_object())
                && opts.data.size() == 0)
            || (opts.data.is_string()
                && opts.data.get_ref<const std::string&>().size() == 0);
    }
};

#    define SPECIALIZE_WO_NULL_FIELDS(__name)                             \
        template <>                                                       \
        struct hstd::JsonSerde<hstd::ext::graph::elk::__name>             \
            : hstd::JsonSerdeDescribedRecordBaseEx<                       \
                  hstd::ext::graph::elk::__name> {};

SPECIALIZE_WO_NULL_FIELDS(GraphElkLayoutData);
SPECIALIZE_WO_NULL_FIELDS(PortProperties);
SPECIALIZE_WO_NULL_FIELDS(NodeProperties);
SPECIALIZE_WO_NULL_FIELDS(ElkPortData);
SPECIALIZE_WO_NULL_FIELDS(EdgeSection);
SPECIALIZE_WO_NULL_FIELDS(ElkEdgeData);
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

template <>
struct std::formatter<hstd::ext::graph::elk::Options> {
    template <typename FormatContext>
    auto format(
        hstd::ext::graph::elk::Options const& p,
        FormatContext&                        ctx) const {
        return hstd::fmt_ctx(p.data, ctx);
    }
};
#endif
