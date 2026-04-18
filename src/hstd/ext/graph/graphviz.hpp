#pragma once

#if ORG_BUILD_WITH_CGRAPH
#    include <graphviz/gvc.h>
#    include <graphviz/cgraph.h>
#    include <string>
#    include <stdexcept>
#    include <string>
#    include <hstd/system/all.hpp>
#    include <hstd/stdlib/Ptrs.hpp>
#    include <hstd/stdlib/strutils.hpp>
#    include <hstd/system/reflection.hpp>
#    include <hstd/stdlib/Opt.hpp>
#    include <hstd/stdlib/Variant.hpp>
#    include <hstd/stdlib/Func.hpp>
#    include <hstd/system/generator.hpp>
#    include <hstd/stdlib/Filesystem.hpp>
#    include <hstd/ext/graph/hstd_graph.hpp>

#    define _attr_aligned(__Class, Method, key, Type)                     \
        __Class* set##Method(                                             \
            Type const& value, TextAlign direction = TextAlign::Left) {   \
            setAttr(#key, value, direction);                              \
            return this;                                                  \
        }                                                                 \
                                                                          \
        Opt<Type> get##Method() const {                                   \
            Opt<Type> value;                                              \
            getAttr(#key, value);                                         \
            return value;                                                 \
        }

#    define _attr(__Class, Method, key, Type)                             \
        __Class* set##Method(Type const& value) {                         \
            setAttr(#key, value);                                         \
            return this;                                                  \
        }                                                                 \
                                                                          \
        Opt<Type> get##Method() const {                                   \
            Opt<Type> value;                                              \
            getAttr(#key, value);                                         \
            return value;                                                 \
        }

#    define _attrx(__Class, Method, key, Type)                            \
        __Class* set##Method(Type const& value);


#    define _eattr_use(__Class, Name, key)                                \
        __Class* set##Name(Name value) {                                  \
            setAttr(#key, enum_serde<Name>::to_string(value));            \
            return this;                                                  \
        }                                                                 \
        Opt<Name> get##Name() const {                                     \
            Opt<Str> result;                                              \
            getAttr(#key, result);                                        \
            if (result) {                                                 \
                return enum_serde<Name>::from_string(result.value());     \
            } else {                                                      \
                return std::nullopt;                                      \
            }                                                             \
        }


#    define _eattr(__Class, Name, key, ...)                               \
        DECL_DESCRIBED_ENUM(Name, __VA_ARGS__);                           \
        _eattr_use(__Class, Name, key);


namespace hstd::ext::graph::gv {

static constexpr double scaling = 72.0f;

struct UserDataBase {
    Agrec_t header;
};

enum class TextAlign
{
    Left,
    Center,
    Right
};

enum class LayoutType
{
    Dot,       /// Hierarchical layout
    Neato,     /// Spring model layout
    Fdp,       /// Force-directed layout
    Sfdp,      /// Multiscale version of Fdp for large graphs
    Twopi,     /// Radial layout
    Circo,     /// Circular layout
    Patchwork, /// Patchwork, squarified treemap layout
};

BOOST_DESCRIBE_ENUM(LayoutType, Dot, Neato, Fdp, Sfdp, Twopi, Circo);

enum class RenderFormat
{
    PNG,  /// Portable Network Graphics format
    PDF,  /// Portable Document Format
    SVG,  /// Scalable Vector Graphics format
    PS,   /// PostScript format
    JPEG, /// Joint Photographic Experts Group format
    GIF,  /// Graphics Interchange Format
    TIF,  /// Tagged Image File Format
    BMP,  /// Windows Bitmap format
    XDOT, /// Extended dot format
    DOT,  /// Write original DOT file
};

Str alignText(Str const& text, TextAlign direction);

std::string escapeHtmlForGraphviz(
    std::string const& input,
    TextAlign          direction = TextAlign::Left);

Str escape(Str const& input);

Str escapeHtml(Str const& input);

Str layoutTypeToString(LayoutType layoutType);
Str renderFormatToString(RenderFormat renderFormat);


template <typename T>
struct GraphvizObjBase : CRTP_this_method<T> {
    using CRTP_this_method<T>::_this;

    template <typename Rec, typename... Args>
    Rec* bindRecord(Str const& name, Args&&... args) {
        Rec* result = (Rec*)agbindrec(
            _this()->get(), strdup(name), sizeof(Rec), false);
        if (result != nullptr) {
            result = new (result) Rec(std::forward<Args>(args)...);
            return result;
        } else {
            return nullptr;
        }
    }

    template <typename Rec>
    Rec* getRecord(Str const& name) {
        return (Rec*)aggetrec(_this()->get(), strdup(name), false);
    }

    void delRecord(Str const& name) {
        agdelrec(_this()->get(), strdup(name));
    }

    Func<void(Str const&, Str const&)> setOverride;


    void setAttr(
        Str const& attribute,
        Str const& value,
        TextAlign  direction) {
        setAttr(attribute, alignText(value, direction));
    }

    template <typename AttrType>
    Opt<AttrType> getAttr(Str const& attribute) const {
        Opt<AttrType> res;
        getAttr(attribute, res);
        return res;
    }

    bool hasAttr(Str const& attribute) {
        return agget(_this()->get(), strdup(attribute)) != nullptr;
    }

    void getAttr(Str const& attribute, Opt<Str>& value) const {
        char* found = agget(
            (void*)(_this()->get()), const_cast<char*>(attribute.data()));

        if (found != nullptr) {
            value = found;
        } else {
            value = std::nullopt;
        }
    }

    void getAttr(Str const& key, Opt<int>& value) const {
        Opt<Str> tmp;
        getAttr(key, tmp);
        if (tmp && !tmp->empty()) { value = tmp->toInt(); }
    }

    void getAttr(Str const& key, Opt<hstd::u64>& value) const {
        Opt<Str> tmp;
        getAttr(key, tmp);
        if (tmp && !tmp->empty()) { value = tmp->toU64(); }
    }

    void getAttr(Str const& key, Opt<double>& value) const {
        Opt<Str> tmp;
        getAttr(key, tmp);
        if (tmp && !tmp->empty()) { value = tmp->toDouble(); }
    }

    void getAttr(Str const& key, Opt<bool>& value) const {
        Opt<Str> tmp;
        getAttr(key, tmp);
        if (tmp && !tmp->empty()) { value = *tmp == "true"; }
    }


    void getAttr(Str const& key, Opt<Point>& value) const {
        Opt<Str> tmp;
        getAttr(key, tmp);
        if (tmp && !tmp->empty()) {
            auto split = tmp->split(",");
            value      = Point(split[0].toDouble(), split[1].toDouble());
        }
    }

    void setHtmlAttr(Str attribute, Str const& value) {
        // Define the attribute if not already defined
        Agsym_t* attr = agattr(
            agraphof(_this()->get()),
            T::graphvizKind,
            attribute.data(),
            "");
        if (!attr) {
            throw std::runtime_error(
                "Failed to define attribute: " + attribute);
        }

        // Set the raw value using `agxset` and `agstrdup_html`
        agxset(
            _this()->get(),
            attr,
            agstrdup_html(
                agraphof(_this()->get()),
                const_cast<char*>(value.c_str())));
    }


    void setAttr(Str attribute, Str const& value) {
        if (setOverride) {
            setOverride(attribute, value);
        } else {
            agsafeset(
                _this()->get(),
                attribute.data(),
                const_cast<char*>(value.c_str()),
                "");
        }
    }

    void setAttr(Str const& key, int value) {
        _this()->setAttr(key, std::to_string(value));
    }

    void setAttr(Str const& key, hstd::u64 value) {
        _this()->setAttr(key, std::to_string(value));
    }

    void setAttr(Str const& key, Point value) {
        _this()->setAttr(key, std::format("{},{}", value.x(), value.y()));
    }

    void setAttr(Str const& key, double value) {
        _this()->setAttr(key, std::to_string(value));
    }


    void setAttr(Str const& key, bool value) {
        _this()->setAttr(key, Str(value ? "true" : "false"));
    }

    Agobj_s*       obj() { return (Agobj_s*)(_this()->get()); }
    Agtag_s const& tag() { return obj()->tag; }

    bool isAgraph() const { return tag().objtype == AGRAPH; }
    bool isAgnode() const { return tag().objtype == AGNODE; }
    bool isAgOutEdge() const { return tag().objtype == AGOUTEDGE; }
    bool isAgInEdge() const { return tag().objtype == AGINEDGE; }
};

class NodeAttribute
    : public GraphvizObjBase<NodeAttribute>
    , public layout::IVertexVisualAttribute {
  public:
    static const int graphvizKind = AGNODE;
    struct Record {
        Str toHtml(bool horizontal = true) const;


        Record() {}
        Record(Str const& content, Opt<Str> const& tag = std::nullopt)
            : content(content), tag(tag) {}

        Record(Vec<Record> const& sub) : content(sub) {}

        void push_back(Vec<Str> const& cells) {
            Vec<Record> row;
            for (const auto& it : cells) { row.push_back(it); }
            getNested().push_back(Record(row));
        }

        void push_back(Record const& rec) { getNested().push_back(rec); }

        bool isFinal() const {
            return std::holds_alternative<Str>(content);
        }

        void set(Str const& columnKey, Record const& value);
        void setEscaped(Str const& columnKey, Str const& value) {
            set(columnKey, fromEscapedText(value));
        }

        void setHtml(Str const& columnKey, Str const& value) {
            set(columnKey, fromHtmlText(value));
        }

        bool         isRecord() const { return !isFinal(); }
        Str&         getLabel() { return std::get<Str>(content); }
        Str const&   getLabel() const { return std::get<Str>(content); }
        Vec<Record>& getNested() { return std::get<1>(content); }
        Vec<Record> const& getNested() const {
            return std::get<1>(content);
        }

        Opt<Str>                                     tag;
        Variant<Str, Vec<Record>>                    content;
        std::unordered_map<std::string, std::string> htmlAttrs;


        static Record fromEscapedText(
            Str const& text,
            TextAlign  align = TextAlign::Left);

        static Record fromHtmlText(Str const& text) {
            return Record{text};
        }

        static Record fromRow(Vec<Record> const& recs);

        static Record fromEscapedTextRow(Vec<Str> const& cells);

        void add(Record const& rec) { getNested().push_back(rec); }
        void addHtml(Str const& html) { getLabel().append(html); }
        void addEscaped(
            Str const& text,
            TextAlign  align = TextAlign::Left) {
            getLabel().append(escapeHtmlForGraphviz(text.toBase(), align));
        }

        Record& htmlAttr(
            std::string const& key,
            std::string const& value) {
            htmlAttrs.insert_or_assign(key, value);
            return *this;
        }

        Str toString(bool braceCount = 1) const;
    };

    void startHtmlRecord() {
        setShape(Shape::plaintext);
        bindRecord<Record>("record");
        getNodeRecord()->content = Vec<Record>{};
    }

    void startRecord() {
        setShape(Shape::record);
        bindRecord<Record>("record");
        getNodeRecord()->content = Vec<Record>{};
    }

    Record* getNodeRecord() { return getRecord<Record>("record"); }

    void finishRecord(int braceCount = 1) {
        setLabel(getNodeRecord()->toString(braceCount));
    }

    void finishHtmlRecord(bool horizontal = false) {
        setHtmlAttr("label", getNodeRecord()->toHtml(horizontal));
    }

    NodeAttribute(Agraph_t* graph, Str const& name, Record const& record);

    NodeAttribute(Agraph_t* graph, Agnode_t* node_)
        : node(node_), graph(graph) {}

    NodeAttribute(Agraph_t* graph, Str const& name);

    Agnode_t*       get() { return node; }
    Agnode_t const* get() const { return node; }

    Str name() const { return agnameof(node); }

    std::string getRepr() const override {
        return getPropertiesAsString();
    }

    std::string getPropertiesAsString() const;

    _eattr(
        NodeAttribute,
        Shape,
        shape,
        //
        box,
        polygon,
        ellipse,
        oval,
        circle,
        point,
        egg,
        triangle,
        plaintext,
        plain,
        diamond,
        trapezium,
        parallelogram,
        house,
        pentagon,
        hexagon,
        septagon,
        octagon,
        doublecircle,
        doubleoctagon,
        tripleoctagon,
        invtriangle,
        invtrapezium,
        invhouse,
        Mdiamond,
        Msquare,
        Mcircle,
        rect,
        rectangle,
        square,
        star,
        none,
        underline,
        cylinder,
        note,
        tab,
        folder,
        box3d,
        component,
        promoter,
        cds,
        terminator,
        utr,
        primersite,
        restrictionsite,
        fivepoverhang,
        threepoverhang,
        noverhang,
        assembly,
        signature,
        insulator,
        ribosite,
        record,
        rnastab,
        proteasesite,
        proteinstab,
        rpromoter,
        rarrow,
        larrow,
        lpromoter);

    DECL_DESCRIBED_ENUM(
        ArrowType,
        normal,
        inv,
        dot,
        odot,
        none,
        tee,
        empty,
        invempty,
        diamond,
        odiamond,
        ediamond,
        open,
        halfopen,
        vee,
        invvee,
        box,
        obox,
        crow,
        invcrow,
        curve,
        icurve,
        lace,
        ilace);

    void setArrowHead(ArrowType type) {
        setAttr("arrowhead", enum_serde<ArrowType>::to_string(type));
    };

    void setArrowTail(ArrowType type) {
        setAttr("arrowtail", enum_serde<ArrowType>::to_string(type));
    };

    _eattr(
        NodeAttribute,
        ArrowSize,
        arrowsize,
        tiny,
        small,
        normal,
        large,
        huge);
    _eattr(NodeAttribute, Dir, dir, forward, back, both, none);
    _eattr(
        NodeAttribute,
        Style,
        style,
        solid,
        dashed,
        dotted,
        bold,
        invis,
        tapered,
        filled,
        striped,
        wedged,
        diagonals,
        rounded);

    /// \brief Width of the edge's line
    _attr(NodeAttribute, PenWidth, penwidth, double);
    /// \brief Color of the node's border
    _attr(NodeAttribute, Color, color, Str);
    /// \brief Fill color of the node
    _attr(NodeAttribute, FillColor, fillcolor, Str);
    /// \brief Font color of the node's label
    _attr(NodeAttribute, FontColor, fontcolor, Str);
    /// \brief Font name of the node's label
    _attr(NodeAttribute, FontName, fontname, Str);
    /// \brief Font size of the node's label
    _attr(NodeAttribute, FontSize, fontsize, double);
    /// \brief Height of the node
    _attr(NodeAttribute, Height, height, double);
    /// \brief Label (text) of the node
    _attr_aligned(NodeAttribute, Label, label, Str);
    /// \brief Position of the node's center
    _attr(NodeAttribute, Position, pos, Point);
    /// \brief URL associated with the node
    _attr(NodeAttribute, URL, URL, Str);
    /// \brief Width of the node
    _attr(NodeAttribute, Width, width, double);
    /// \brief External label (text) of the node
    _attr_aligned(NodeAttribute, XLabel, xlabel, Str);
    /// \brief Position of the node's external label
    _attr(NodeAttribute, XLabelPosition, xlabelpos, Point);
    /// \brief Margin around the drawing
    _attr(NodeAttribute, Margin, margin, Point);


    NodeAttribute* setInchWidth(double inches) {
        setAttr("width", inches);
        return this;
    }

    NodeAttribute* setPointWidth(double points) {
        setInchWidth(points / scaling);
        return this;
    }

    double getInchWidth() const {
        hstd::Opt<double> result = 0;
        getAttr("width", result);
        return result.value();
    }

    double getPointWidth() const { return getInchWidth() * scaling; }

    NodeAttribute* setInchHeight(double inches) {
        setAttr("height", inches);
        return this;
    }

    NodeAttribute* setPointHeight(double points) {
        setInchHeight(points / scaling);
        return this;
    }

    double getInchHeight() const {
        hstd::Opt<double> result = 0;
        getAttr("height", result);
        return result.value();
    }

    double getPointHeight() const { return getInchHeight() * scaling; }

    Agnodeinfo_t*       info() { return (Agnodeinfo_t*)AGDATA(node); }
    Agnodeinfo_t const* info() const {
        return (Agnodeinfo_t*)AGDATA(node);
    }

    NodeAttribute* setFixedInchesWH(double w, double h);
    NodeAttribute* setFixedPointWH(double w, double h) {
        return setFixedInchesWH(w / scaling, h / scaling);
    }

  public:
    Agnode_t* node;
    Agraph_t* graph;
};

class EdgeAttribute
    : public GraphvizObjBase<EdgeAttribute>
    , public layout::IEdgeVisualAttribute {
  public:
    static const int graphvizKind = AGEDGE;
    EdgeAttribute(Agraph_t* graph, Agedge_t* edge)
        : edge_(edge), graph(graph) {}

    EdgeAttribute(
        Agraph_t*            graph,
        NodeAttribute const& head,
        NodeAttribute const& tail);

    Agedge_t*       get() { return edge_; }
    Agedge_t const* get() const { return edge_; }

    std::string getPropertiesAsString() const;

    NodeAttribute head() { return NodeAttribute(graph, AGHEAD(edge_)); }
    NodeAttribute tail() { return NodeAttribute(graph, AGTAIL(edge_)); }

    _attr(EdgeAttribute, Constraint, constraint, bool);
    /// \brief Color of the edge
    _attr(EdgeAttribute, Color, color, Str /*Str*/);
    /// \brief Font color of the edge's label
    _attr(EdgeAttribute, FontColor, fontcolor, Str /*Str*/);
    /// \brief Font name of the edge's label
    _attr(EdgeAttribute, FontName, fontname, Str);
    /// \brief Font size of the edge's label
    _attr(EdgeAttribute, FontSize, fontsize, double);
    /// \brief Label (text) of the edge
    _attr_aligned(EdgeAttribute, Label, label, Str);
    /// \brief Position of the edge's label
    _attr(EdgeAttribute, LabelPosition, lp, Point);
    /// \brief Width of the edge's line
    _attr(EdgeAttribute, PenWidth, penwidth, double);
    using Style = gv::NodeAttribute::Style;
    /// \brief Style of the edge's line
    _eattr_use(EdgeAttribute, Style, style);
    /// \brief URL associated with the edge
    _attr(EdgeAttribute, URL, URL, Str);
    _attr(EdgeAttribute, LHead, lhead, Str);
    _attr(EdgeAttribute, LTail, ltail, Str);

    void setLHead(NodeAttribute node) { setLHead(node.name()); }
    void setLTail(NodeAttribute node) { setLTail(node.name()); }

    Agedgeinfo_t*       info() { return (Agedgeinfo_t*)AGDATA(edge_); }
    Agedgeinfo_t const* info() const {
        return (Agedgeinfo_t*)AGDATA(edge_);
    }

  public:
    Agraph_t* graph;
    Agedge_t* edge_;
};

class Layout;
class GraphGroup
    : public GraphvizObjBase<GraphGroup>
    , public layout::IGroup {
    void initDefaultSetters();

  public:
    static const int graphvizKind = AGRAPH;


    struct GVContext : hstd::SharedPtrApi<GVContext> {
        hstd::UnorderedMap<VertexID, hstd::SPtr<NodeAttribute>>
            nodeAttributes;
        hstd::UnorderedMap<EdgeID, hstd::SPtr<EdgeAttribute>>
            edgeAttributes;
        hstd::UnorderedMap<layout::GroupID, hstd::SPtr<GraphGroup>> groups;
    };

    struct GroupContext {
        hstd::SPtr<layout::LayoutRun> run;
        GVContext::Ptr                context;
        SPtr<GVC_t>                   gvc;
    };

    GraphGroup(
        GroupContext ctx,
        Str const&   name,
        Agdesc_t     desc = Agdirected);
    GraphGroup(GroupContext ctx, fs::path const& file);
    GraphGroup(GroupContext ctx, Agraph_t* graph);

    Agraph_t*       get() { return graph; }
    Agraph_t const* get() const { return graph; }

    SPtr<GVC_t> gvc() { return ctx.gvc; }

    std::string getPropertiesAsString() const;

    enum class Splines
    {
        Ortho,
        Polyline,
        Curved
    };


    hstd::SPtr<GraphGroup> newSubgraph(Str const& name) {
        return std::make_shared<GraphGroup>(
            ctx, agsubg(graph, strdup("cluster_" + name), 1));
    }

    layout::GroupID newSubLayoutGraph();

    static layout::GroupID newRootGraph(hstd::SPtr<layout::LayoutRun> run);

    void setSplines(Splines splines);
    void eachNode(Func<void(NodeAttribute)> cb);
    void eachEdge(Func<void(EdgeAttribute)> cb);
    void eachSubgraph(Func<void(GraphGroup)> cb) const;

    int nodeCount() { return agnnodes(graph); }

    void render(
        fs::path const& path,
        LayoutType      layout = LayoutType::Dot,
        RenderFormat    format = RenderFormat::PNG);

    /// Set default attriute value for edge
    void setDefaultEdgeAttr(Str const& key, Str const& value) {}

    NodeAttribute subNode(NodeAttribute const& node) {
        agsubnode(graph, node.node, 1);
        return node;
    }

    Agraphinfo_t*       info() { return (Agraphinfo_t*)AGDATA(graph); }
    Agraphinfo_t const* info() const {
        return (Agraphinfo_t*)AGDATA(graph);
    }

    hstd::SPtr<NodeAttribute> node(Str const& name) {
        LOGIC_ASSERTION_CHECK(graph != nullptr, "");
        auto tmp = std::make_shared<NodeAttribute>(graph, name);
        return tmp;
    }

    hstd::SPtr<EdgeAttribute> edge(
        NodeAttribute const& head,
        NodeAttribute const& tail) {
        LOGIC_ASSERTION_CHECK(graph != nullptr, "");
        return std::make_shared<EdgeAttribute>(graph, head, tail);
    }

    hstd::SPtr<EdgeAttribute> edge(Str const& head, Str const& tail) {
        return edge(
            NodeAttribute(graph, head), NodeAttribute(graph, tail));
    }

    /// \brief Direction of layout ranks
    _eattr(GraphGroup, RankDirection, rankdir, LR, TB, BT, RL);
    /// \brief Placement of nodes withing the graph.
    ///
    /// 'none' is the default value (not in the same/source/sink list
    /// that is explicitly recognized by GV), 'same' causes nodes to be
    /// placd on the same level, `source` is closer to the source
    /// nodes, `sink` is closer to the target
    _eattr(GraphGroup, Rank, rank, none, same, source, sink);

    /// \brief Damping factor for force-directed layout
    _attr(GraphGroup, Damping, Damping, double);
    /// \brief Spring constant factor for force-directed layout
    _attr(GraphGroup, K, K, double);
    /// \brief URL associated with the graph
    _attr(GraphGroup, URL, URL, Str);
    /// \brief Desired aspect ratio of the drawing
    _attr(GraphGroup, AspectRatio, aspect, double);
    /// \brief Background color of the graph
    _attr(GraphGroup, BackgroundColor, bgcolor, Str);
    /// \brief Default edge length
    _attr(GraphGroup, DefaultDistance, defaultdist, double);
    /// \brief Default node color
    _attr(GraphGroup, DefaultNodeColor, defaultNodeColor, Str);
    /// \brief Default edge color
    _attr(GraphGroup, DefaultEdgeColor, defaultEdgeColor, Str);
    /// \brief Font color
    _attr(GraphGroup, FontColor, fontcolor, Str);
    /// \brief border color
    _attr(GraphGroup, Color, color, Str);
    _attr(GraphGroup, PenWidth, penwidth, double);
    _attr(GraphGroup, FillColor, fillcolor, Str);
    using Style = NodeAttribute::Style;
    _eattr_use(GraphGroup, Style, style);
    /// \brief Font name
    _attr(GraphGroup, FontName, fontname, Str);
    /// \brief Font size
    _attr(GraphGroup, FontSize, fontsize, double);
    /// \brief Label (title) of the graph
    _attr_aligned(GraphGroup, Label, label, Str);
    /// \brief URL associated with the graph label
    _attr_aligned(GraphGroup, LabelURL, labelURL, Str);
    /// \brief Horizontal placement of the graph label
    _attr(GraphGroup, LabelJustification, labeljust, Str);
    /// \brief Vertical placement of the graph label
    _attr(GraphGroup, LabelLocator, labelloc, Str);
    /// \brief Layer separator character
    _attr(GraphGroup, LayerListSeparator, layersep, Str);
    /// \brief List of layers in the graph
    _attr(GraphGroup, Layers, layers, Str);
    /// \brief Margin around the drawing
    _attr(GraphGroup, Margin, margin, Point);
    /// \brief Padding inside of the cluster
    _attr(GraphGroup, Pad, pad, Point);
    /// \brief Minimum separation between nodes
    _attr(GraphGroup, NodeSeparation, nodesep, double);
    /// \brief Order in which nodes and edges are drawn
    _attr(GraphGroup, OutputOrder, outputorder, Str);
    /// \brief Direction of page layout
    _attr(GraphGroup, PageDirection, pagedir, Str);
    /// \brief Height of output pages
    _attr(GraphGroup, PageHeight, pageheight, double);
    /// \brief Width of output pages
    _attr(GraphGroup, PageWidth, pagewidth, double);
    /// \brief Cluster quantum scale factor
    _attr(GraphGroup, Quantum, quantum, double);
    /// \brief Minimum separation between ranks
    _attr(GraphGroup, RankSeparation, ranksep, double);
    /// \brief Resolution (dpi) of the output image
    _attr(GraphGroup, Resolution, resolution, double);
    /// \brief Size of the layout search space
    _attr(GraphGroup, SearchSize, searchsize, int);
    /// \brief Maximum size of the drawing
    _attr(GraphGroup, Size, size, Point);
    /// \brief Type of edges (splines, lines, etc.)
    _attr(GraphGroup, Spline, splines, Str);
    /// \brief Style sheet used for the output
    _attr(GraphGroup, StyleSheet, stylesheet, Str);
    /// \brief Whether to use truecolor in the output
    _attr(GraphGroup, TrueColor, truecolor, bool);
    /// \brief Viewport size and position
    _attr(GraphGroup, ViewPort, viewport, Point);
    _attr(GraphGroup, Compound, compound, bool);
    _attr(GraphGroup, Concentrate, concentrate, bool);

  public:
    Agraph_t*     graph;
    EdgeAttribute defaultNode;
    EdgeAttribute defaultEdge;
    GroupContext  ctx;

    Str            name() const { return agnameof(graph); }
    GVContext::Ptr context() { return ctx.context; }

    auto& nodeAttributes() { return ctx.context->nodeAttributes; }
    auto& edgeAttributes() { return ctx.context->edgeAttributes; }
    auto& groups() { return ctx.context->groups; }


    hstd::UnorderedSet<VertexID> directVertices;
    hstd::UnorderedSet<EdgeID>   directEdges;

    void delVertex(VertexID const& id) {
        agdelnode(get(), nodeAttributes().at(id)->get());
        nodeAttributes().erase(id);
        directVertices.erase(id);
    }

    void delEdge(EdgeID const& id) {
        agdeledge(get(), edgeAttributes().at(id)->get());
        edgeAttributes().erase(id);
        directEdges.erase(id);
    }

    void delSubgraph(layout::GroupID const& id) {
        agdelsubg(get(), groups().at(id)->get());
        groups().erase(id);
    }

    hstd::SPtr<layout::IVertexVisualAttribute> addVertex(
        VertexID const& id) override;
    hstd::SPtr<layout::IEdgeVisualAttribute> addEdge(
        EdgeID const& id) override;
    layout::GroupID addNewNativeSubgroup() override;

    void addExistingSubgroup(layout::GroupID const& id) override;

    virtual hstd::Vec<VertexID> getVertices() const override {
        return hstd::Vec<VertexID>{
            directVertices.begin(), directVertices.end()};
    }

    virtual hstd::Vec<EdgeID> getEdges() const override {
        return hstd::Vec<EdgeID>{directEdges.begin(), directEdges.end()};
    }

    virtual std::string getStableId() const override {
        return hstd::fmt("graph-group-{}", name());
    }
};

class Graphviz;
class Layout : public layout::IPlacementAlgorithm {
  public:
    Layout(SPtr<GVC_t> gvc, hstd::SPtr<layout::LayoutRun> run)
        : layout::IPlacementAlgorithm{run}, gvc{gvc} {}
    LayoutType layout = LayoutType::Dot;

    // FIXME: this might not be necessary, using 1 returns the correct
    // results in tests.
    /// \brief Which DPI to use when converting to and from graphviz sizes.
    /// Backend-specific, 72 is the default used by graphviz.
    [[refl]] int graphviz_size_scaling = 1;

    void createLayout(GraphGroup const& graph);

    void freeLayout(GraphGroup graph);

    void writeFile(
        fs::path const&   path,
        GraphGroup const& graph,
        RenderFormat      format = RenderFormat::DOT);

    void renderToFile(
        fs::path const&   path,
        GraphGroup const& graph,
        RenderFormat      format = RenderFormat::PNG);

    SPtr<GVC_t> gvc;

    Result runSingleLayout(layout::GroupID const& group) override;
};

class GraphVertexLayoutAttribute : public layout::IVertexLayoutAttribute {
  public:
    NodeAttribute node;
    GraphGroup    graph;

    GraphVertexLayoutAttribute(
        NodeAttribute const& node,
        GraphGroup const&    graph)
        : node{node}, graph{graph} {}

    Rect getBBox() const override;

    std::string getRepr() const override {
        return node.getPropertiesAsString();
    }

    hstd::SPtr<hstd::SPtr<layout::IPortLayoutAttribute>> getPorts()
        const override {
        return {};
    }

    visual::VisGroup getVisual() const override;
};

class GraphEdgeLayoutAttribute : public layout::IEdgeLayoutAttribute {
  public:
    EdgeAttribute edge;
    GraphGroup    graph;

    GraphEdgeLayoutAttribute(
        EdgeAttribute const& edge,
        GraphGroup const&    graph)
        : edge{edge}, graph{graph} {}

    Path getPath() const override;

    std::string getRepr() const override {
        return edge.getPropertiesAsString();
    }


    visual::VisGroup getVisual() const override;
};

class GraphGroupLayoutAttribute : public layout::IGroupLayoutAttribute {
  public:
    Rect                   graph;
    hstd::SPtr<GraphGroup> group;

    GraphGroupLayoutAttribute(
        Rect const&                   graph,
        hstd::SPtr<GraphGroup> const& group)
        : graph{graph}, group{group} {}

    virtual Rect getPointsBBox() const override;

    std::string getRepr() const override {
        return group->getPropertiesAsString();
    }


    hstd::SPtr<hstd::SPtr<layout::IPortLayoutAttribute>> getPorts()
        const override {
        return {};
    }

    visual::VisGroup getVisual() const override;
};

} // namespace hstd::ext::graph::gv
#endif
