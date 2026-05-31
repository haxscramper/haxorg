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
#    include <hstd/ext/graph/base/graph_base.hpp>
#    include <hstd/ext/graph/visual/graph_visual.hpp>
#    include <src/hstd/ext/graph/base/graph_base.pb.h>
#    include <src/hstd/ext/graph/visual/graph_graphviz.pb.h>
#    include <google/protobuf/descriptor.h>
#    include <google/protobuf/message.h>
#    include <hstd/stdlib/Xml.hpp>

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


#    define _eattr_use(__Class, Name, key, Type)                          \
        __Class* set##Name(Type value) {                                  \
            setAttr(#key, enum_serde<Type>::to_string(value));            \
            return this;                                                  \
        }                                                                 \
        Opt<Type> get##Name() const {                                     \
            Opt<Str> result;                                              \
            getAttr(#key, result);                                        \
            if (result) {                                                 \
                return enum_serde<Type>::from_string(result.value());     \
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

DECL_DESCRIBED_ENUM_STANDALONE(TextAlign, Left, Center, Right);

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

DECL_DESCRIBED_ENUM_STANDALONE(
    Style,
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

DECL_DESCRIBED_ENUM_STANDALONE(
    NodeArrowSize,
    tiny,
    small,
    normal,
    large,
    huge);

DECL_DESCRIBED_ENUM_STANDALONE(
    NodeArrowType,
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

DECL_DESCRIBED_ENUM_STANDALONE(NodeDir, forward, back, both, none);
DECL_DESCRIBED_ENUM_STANDALONE(Rank, none, same, source, sink);
DECL_DESCRIBED_ENUM_STANDALONE(RankDirection, LR, TB, BT, RL);
DECL_DESCRIBED_ENUM_STANDALONE(Splines, Ortho, Polyline, Curved);

DECL_DESCRIBED_ENUM_STANDALONE(
    NodeShape,
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


#    define _GV_NODE_ATTRIBUTES(                                          \
        __attr_impl, __eattr_use_impl, __attr_aligned_impl)               \
        __eattr_use_impl(NodeAttribute, NodeShape, shape, gv::NodeShape); \
        __eattr_use_impl(                                                 \
            NodeAttribute, NodeArrowSize, arrowsize, gv::NodeArrowSize);  \
        __eattr_use_impl(NodeAttribute, NodeDir, dir, gv::NodeDir);       \
        __eattr_use_impl(NodeAttribute, Style, style, gv::Style);         \
        __attr_impl(NodeAttribute, PenWidth, penwidth, double);           \
        __attr_impl(NodeAttribute, Color, color, Str);                    \
        __attr_impl(NodeAttribute, FillColor, fillcolor, Str);            \
        __attr_impl(NodeAttribute, FontColor, fontcolor, Str);            \
        __attr_impl(NodeAttribute, FontName, fontname, Str);              \
        __attr_impl(NodeAttribute, FontSize, fontsize, double);           \
        __attr_impl(NodeAttribute, Height, height, double);               \
        __attr_aligned_impl(NodeAttribute, Label, label, Str);            \
        __attr_impl(NodeAttribute, Position, pos, Point);                 \
        __attr_impl(NodeAttribute, URL, URL, Str);                        \
        __attr_impl(NodeAttribute, Width, width, double);                 \
        __attr_aligned_impl(NodeAttribute, XLabel, xlabel, Str);          \
        __attr_impl(NodeAttribute, XLabelPosition, xlabelpos, Point);     \
        __attr_impl(NodeAttribute, Margin, margin, Point);

#    define _GV_EDGE_ATTRIBUTES(                                          \
        __attr_impl, __eattr_use_impl, __attr_aligned_impl)               \
        __attr_impl(EdgeAttribute, Constraint, constraint, bool);         \
        __attr_impl(EdgeAttribute, Color, color, Str /*Str*/);            \
        __attr_impl(EdgeAttribute, FontColor, fontcolor, Str /*Str*/);    \
        __attr_impl(EdgeAttribute, FontName, fontname, Str);              \
        __attr_impl(EdgeAttribute, FontSize, fontsize, double);           \
        __attr_aligned_impl(EdgeAttribute, Label, label, Str);            \
        __attr_impl(EdgeAttribute, LabelPosition, lp, Point);             \
        __attr_impl(EdgeAttribute, PenWidth, penwidth, double);           \
        __eattr_use_impl(EdgeAttribute, Style, style, gv::Style);         \
        __attr_impl(EdgeAttribute, URL, URL, Str);                        \
        __attr_impl(EdgeAttribute, LHead, lhead, Str);                    \
        __attr_impl(EdgeAttribute, LTail, ltail, Str);

#    define _GV_GRAPH_ATTRIBUTES(                                         \
        __attr_impl, __eattr_use_impl, __attr_aligned_impl)               \
        __eattr_use_impl(                                                 \
            GraphGroup, RankDirection, rankdir, gv::RankDirection);       \
        __eattr_use_impl(GraphGroup, Rank, rank, gv::Rank);               \
        __attr_impl(GraphGroup, Damping, Damping, double);                \
        __attr_impl(GraphGroup, K, K, double);                            \
        __attr_impl(GraphGroup, URL, URL, Str);                           \
        __attr_impl(GraphGroup, AspectRatio, aspect, double);             \
        __attr_impl(GraphGroup, BackgroundColor, bgcolor, Str);           \
        __attr_impl(GraphGroup, DefaultDistance, defaultdist, double);    \
        __attr_impl(GraphGroup, DefaultNodeColor, defaultNodeColor, Str); \
        __attr_impl(GraphGroup, DefaultEdgeColor, defaultEdgeColor, Str); \
        __attr_impl(GraphGroup, FontColor, fontcolor, Str);               \
        __attr_impl(GraphGroup, Color, color, Str);                       \
        __attr_impl(GraphGroup, PenWidth, penwidth, double);              \
        __attr_impl(GraphGroup, FillColor, fillcolor, Str);               \
        __eattr_use_impl(GraphGroup, Style, style, gv::Style);            \
        __attr_impl(GraphGroup, FontName, fontname, Str);                 \
        __attr_impl(GraphGroup, FontSize, fontsize, double);              \
        __attr_aligned_impl(GraphGroup, Label, label, Str);               \
        __attr_aligned_impl(GraphGroup, LabelURL, labelURL, Str);         \
        __attr_impl(GraphGroup, LabelJustification, labeljust, Str);      \
        __attr_impl(GraphGroup, LabelLocator, labelloc, Str);             \
        __attr_impl(GraphGroup, LayerListSeparator, layersep, Str);       \
        __attr_impl(GraphGroup, Layers, layers, Str);                     \
        __attr_impl(GraphGroup, Margin, margin, Point);                   \
        __attr_impl(GraphGroup, Pad, pad, Point);                         \
        __attr_impl(GraphGroup, NodeSeparation, nodesep, double);         \
        __attr_impl(GraphGroup, OutputOrder, outputorder, Str);           \
        __attr_impl(GraphGroup, PageDirection, pagedir, Str);             \
        __attr_impl(GraphGroup, PageHeight, pageheight, double);          \
        __attr_impl(GraphGroup, PageWidth, pagewidth, double);            \
        __attr_impl(GraphGroup, Quantum, quantum, double);                \
        __attr_impl(GraphGroup, RankSeparation, ranksep, double);         \
        __attr_impl(GraphGroup, Resolution, resolution, double);          \
        __attr_impl(GraphGroup, SearchSize, searchsize, int);             \
        __attr_impl(GraphGroup, Size, size, Point);                       \
        __attr_impl(GraphGroup, Spline, splines, Str);                    \
        __attr_impl(GraphGroup, StyleSheet, stylesheet, Str);             \
        __attr_impl(GraphGroup, TrueColor, truecolor, bool);              \
        __attr_impl(GraphGroup, ViewPort, viewport, Point);               \
        __attr_impl(GraphGroup, Compound, compound, bool);                \
        __attr_impl(GraphGroup, Concentrate, concentrate, bool);

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

    /// \brief graphviz allows binding arbitrary objects to the graph
    /// elements: this method can be used to store some additional payload
    /// that cannot be serialized to the simple string attributes.
    template <typename Rec, typename... Args>
    Rec* bindPayload(Str const& name, Args&&... args) {
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
    Rec* getPayload(Str const& name) {
        return (Rec*)aggetrec(_this()->get(), strdup(name), false);
    }

    void delPayload(Str const& name) {
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


/// \brief Structured representation of the graphviz 'record' node type.
struct Record {
    Opt<Str>                                     tag;
    Variant<Str, Vec<Record>>                    content;
    std::unordered_map<std::string, std::string> htmlAttrs;

    DESC_FIELDS(Record, (tag, content, htmlAttrs));

    /// \brief Export the record content into a HTML table and attempt to
    /// detect the simple patterns (2d grid of elements) to result in a
    /// better alignment of the content.
    XmlNode toHtml(bool horizontal = true) const;

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

    bool isFinal() const { return std::holds_alternative<Str>(content); }

    /// \brief Treat the record as a key-value table, with the first column
    /// used as a key and the second one used as a value.
    void set(Str const& columnKey, Record const& value);
    void setEscaped(Str const& columnKey, Str const& value) {
        set(columnKey, fromEscapedText(value));
    }

    void setHtml(Str const& columnKey, Str const& value) {
        set(columnKey, fromHtmlText(value));
    }

    bool               isRecord() const { return !isFinal(); }
    Str&               getLabel() { return std::get<Str>(content); }
    Str const&         getLabel() const { return std::get<Str>(content); }
    Vec<Record>&       getNested() { return std::get<1>(content); }
    Vec<Record> const& getNested() const { return std::get<1>(content); }


    static Record fromEscapedText(
        Str const& text,
        TextAlign  align = TextAlign::Left);

    static Record fromHtmlText(Str const& text) { return Record{text}; }

    static Record fromRow(Vec<Record> const& recs);

    static Record fromEscapedTextRow(Vec<Str> const& cells);

    void add(Record const& rec) { getNested().push_back(rec); }
    void addHtml(Str const& html) { getLabel().append(html); }
    void addEscaped(Str const& text, TextAlign align = TextAlign::Left) {
        getLabel().append(escapeHtmlForGraphviz(text.toBase(), align));
    }

    Record& htmlAttr(std::string const& key, std::string const& value) {
        htmlAttrs.insert_or_assign(key, value);
        return *this;
    }

    Str toString(bool braceCount = 1) const;
};

class NodeAttribute
    : public GraphvizObjBase<NodeAttribute>
    , public layout::IVertexVisualAttribute {
  public:
    static const int graphvizKind = AGNODE;


    _GV_NODE_ATTRIBUTES(_attr, _eattr_use, _attr_aligned);

    void setNodeRecord(Record const& rec, int braceCount = 1) {
        setLabel(rec.toString(braceCount));
    }

    void setHtmlNodeRecord(Record const& rec) {
        setHtmlAttr("label", rec.toHtml().to_string());
    }

    Record* getNodeRecord() { return getPayload<Record>("record"); }

    NodeAttribute(Agraph_t* graph, Str const& name, Record const& record);

    NodeAttribute(Agraph_t* graph, Agnode_t* node_)
        : node(node_), graph(graph) {}

    NodeAttribute(Agraph_t* graph, Str const& name);
    NodeAttribute(NodeAttribute const& other) = default;

    Agnode_t*       get() { return node; }
    Agnode_t const* get() const { return node; }

    Str name() const { return agnameof(node); }

    std::string getRepr() const override {
        return getPropertiesAsString();
    }

    std::string getPropertiesAsString() const;


    void setArrowHead(NodeArrowType type) {
        setAttr("arrowhead", enum_serde<NodeArrowType>::to_string(type));
    };

    void setArrowTail(NodeArrowType type) {
        setAttr("arrowtail", enum_serde<NodeArrowType>::to_string(type));
    };

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

    NodeAttribute* setFixedPointWH(geometry::Size const& size) {
        return setFixedInchesWH(
            size.width() / scaling, size.height() / scaling);
    }

  public:
    Agnode_t* node;
    Agraph_t* graph;

    void writeSerial(graph::proto::IAttribute*, IGraph const* graph)
        const override;

    void readSerial(
        graph::proto::IAttribute const* in,
        IGraph const*                   graph,
        IGraphSerialReaderFactory*      factory,
        IAttributeObject const*         vertex) override;
};

class EdgeAttribute
    : public GraphvizObjBase<EdgeAttribute>
    , public layout::IEdgeVisualAttribute {
  public:
    static const int graphvizKind = AGEDGE;
    EdgeAttribute(Agraph_t* graph, Agedge_t* edge)
        : edge_(edge), graph(graph) {}

    std::string getRepr() const override { return "gv::EdgeAttribute"; }

    EdgeAttribute(
        Agraph_t*            graph,
        NodeAttribute const& head,
        NodeAttribute const& tail);

    _GV_EDGE_ATTRIBUTES(_attr, _eattr_use, _attr_aligned);

    Agedge_t*       get() { return edge_; }
    Agedge_t const* get() const { return edge_; }

    std::string getPropertiesAsString() const;

    NodeAttribute head() { return NodeAttribute(graph, AGHEAD(edge_)); }
    NodeAttribute tail() { return NodeAttribute(graph, AGTAIL(edge_)); }


    void setLHead(NodeAttribute node) { setLHead(node.name()); }
    void setLTail(NodeAttribute node) { setLTail(node.name()); }

    Agedgeinfo_t*       info() { return (Agedgeinfo_t*)AGDATA(edge_); }
    Agedgeinfo_t const* info() const {
        return (Agedgeinfo_t*)AGDATA(edge_);
    }

  public:
    Agraph_t* graph;
    Agedge_t* edge_;

    void writeSerial(graph::proto::IAttribute*, IGraph const* graph)
        const override;
    void readSerial(
        graph::proto::IAttribute const* in,
        IGraph const*                   graph,
        IGraphSerialReaderFactory*      factory,
        IAttributeObject const*         vertex) override;
};

class Layout;
class GraphGroup
    : public GraphvizObjBase<GraphGroup>
    , public layout::IGroupVisualAttribute {
    void initDefaultSetters();

  public:
    using Base = layout::IGroupVisualAttribute;

    hstd::Opt<geometry::Padding> outerPadding;
    void setOuterPadding(geometry::Padding const& pad) override {
        outerPadding = pad;
    }

    hstd::Opt<geometry::Padding> getOuterPadding() const override {
        return outerPadding;
    }

    static const int graphvizKind = AGRAPH;

    struct GVContext : hstd::SharedPtrApi<GVContext> {};

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


    hstd::SPtr<GraphGroup> newSubgraph(Str const& name) {
        auto res = std::make_shared<GraphGroup>(
            ctx, agsubg(graph, strdup("cluster_" + name), 1));

        return res;
    }

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

    /// \brief Create a new graphviz graph node and return attribute handle
    /// for it.
    hstd::SPtr<NodeAttribute> node(Str const& name) {
        LOGIC_ASSERTION_CHECK(graph != nullptr, "");
        auto existing_node = agnode(
            graph, const_cast<char*>(name.c_str()), 0);
        if (existing_node != nullptr) {
            throw hstd::ext::graph::layout::layout_error::init(
                hstd::fmt(
                    "Node with name {} already exists in the graph",
                    name));
        }

        auto tmp = std::make_shared<NodeAttribute>(graph, name);
        return tmp;
    }

    /// \brief Create new edge between two existing graph nodes, return
    /// graph edge attribute handle.
    hstd::SPtr<EdgeAttribute> edge(
        NodeAttribute const& head,
        NodeAttribute const& tail) {
        LOGIC_ASSERTION_CHECK(graph != nullptr, "");
        return std::make_shared<EdgeAttribute>(graph, head, tail);
    }

    _GV_GRAPH_ATTRIBUTES(_attr, _eattr_use, _attr_aligned);

    GraphGroup* setDirectionLR() {
        return setRankDirection(RankDirection::LR);
    }

    std::string getRepr() const override { return "gv::GraphGroup"; }

  public:
    Agraph_t*     graph;
    NodeAttribute defaultNode;
    EdgeAttribute defaultEdge;
    GroupContext  ctx;

    Str            name() const { return agnameof(graph); }
    GVContext::Ptr context() { return ctx.context; }

    hstd::SPtr<NodeAttribute> addVertex(EdgeID const& edge);


    hstd::SPtr<EdgeAttribute> addEdge(EdgeID const& id);

    /// \brief Legacy method for constructing graph group without the use
    /// layout run. graphviz API makes it reasonably easy to generate a
    /// quick graph visualization, without setting up the full layout run,
    /// so this method is used as an escape hatch for cases like these.
    static hstd::SPtr<gv::GraphGroup> newStandaloneRootGraph(
        hstd::Str const& name);


    static hstd::SPtr<GraphGroup> newRootGraph(
        hstd::SPtr<layout::LayoutRun> run,
        hstd::Str const&              name = "");

    hstd::SPtr<GraphGroup> addNewNativeSubgroup(
        EdgeID const& edge,
        bool          with_algorithm = false);

    std::string getStableId() const override {
        return hstd::fmt("graph-group-{}", name());
    }

    void writeSerial(graph::proto::IAttribute* out, IGraph const* graph)
        const override;

    void readSerial(
        graph::proto::IAttribute const* in,
        IGraph const*                   graph,
        IGraphSerialReaderFactory*      factory,
        IAttributeObject const*         vertex) override;
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

    Result runSingleLayout(VertexID const& group) override;
};

class GraphVertexLayoutAttribute : public layout::IVertexLayoutAttribute {
  public:
    void writeSerial(graph::proto::IAttribute* out, IGraph const* graph)
        const override {
        logic_todo_impl();
    }

    void readSerial(
        graph::proto::IAttribute const* in,
        IGraph const*                   graph,
        IGraphSerialReaderFactory*      factory,
        IAttributeObject const*         vertex) override {
        logic_todo_impl();
    }

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

    visual::VisGroup getVisual(VertexID const& selfId) const override;
};

class GraphEdgeLayoutAttribute : public layout::IEdgeLayoutAttribute {
  public:
    void writeSerial(graph::proto::IAttribute* out, IGraph const* graph)
        const override {
        logic_todo_impl();
    }

    void readSerial(
        graph::proto::IAttribute const* in,
        IGraph const*                   graph,
        IGraphSerialReaderFactory*      factory,
        IAttributeObject const*         vertex) override {
        logic_todo_impl();
    }

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


    visual::VisGroup getVisual(EdgeID const& selfId) const override;
};

class GraphGroupLayoutAttribute : public layout::IGroupLayoutAttribute {
  public:
    void writeSerial(graph::proto::IAttribute* out, IGraph const* graph)
        const override {
        logic_todo_impl();
    }

    void readSerial(
        graph::proto::IAttribute const* in,
        IGraph const*                   graph,
        IGraphSerialReaderFactory*      factory,
        IAttributeObject const*         vertex) override {
        logic_todo_impl();
    }

    Rect                   graph;
    hstd::SPtr<GraphGroup> group;

    GraphGroupLayoutAttribute(
        Rect const&                   graph,
        hstd::SPtr<GraphGroup> const& group)
        : graph{graph}, group{group} {}

    Rect getBBox() const override { return graph; }
    void setBBox(geometry::Rect const& rect) override { graph = rect; }

    std::string getRepr() const override {
        return group->getPropertiesAsString();
    }

    visual::VisGroup getVisual(VertexID const& selfId) const override;
};

} // namespace hstd::ext::graph::gv
#endif
