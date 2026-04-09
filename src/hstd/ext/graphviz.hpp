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
#    include <hstd/ext/hstd_graph.hpp>

#    define _attr_aligned(Method, key, Type)                              \
        void set##Method(                                                 \
            Type const& value, TextAlign direction = TextAlign::Left) {   \
            setAttr(#key, value, direction);                              \
        }                                                                 \
                                                                          \
        Opt<Type> get##Method() const {                                   \
            Opt<Type> value;                                              \
            getAttr(#key, value);                                         \
            return value;                                                 \
        }

#    define _attr(Method, key, Type)                                      \
        void set##Method(Type const& value) { setAttr(#key, value); }     \
                                                                          \
        Opt<Type> get##Method() const {                                   \
            Opt<Type> value;                                              \
            getAttr(#key, value);                                         \
            return value;                                                 \
        }

#    define _attrx(Method, key, Type) void set##Method(Type const& value);


#    define _eattr(Name, key, ...)                                        \
        DECL_DESCRIBED_ENUM(Name, __VA_ARGS__);                           \
        void set##Name(Name value) {                                      \
            setAttr(#key, enum_serde<Name>::to_string(value));            \
        }

namespace hstd::ext::graph::gv {

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
    Dot,   /// Hierarchical layout
    Neato, /// Spring model layout
    Fdp,   /// Force-directed layout
    Sfdp,  /// Multiscale version of Fdp for large graphs
    Twopi, /// Radial layout
    Circo  /// Circular layout
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
        if (tmp) { value = tmp->toInt(); }
    }

    void getAttr(Str const& key, Opt<hstd::u64>& value) const {
        Opt<Str> tmp;
        getAttr(key, tmp);
        if (tmp) { value = tmp->toU64(); }
    }

    void getAttr(Str const& key, Opt<double>& value) const {
        Opt<Str> tmp;
        getAttr(key, tmp);
        if (tmp) { value = tmp->toDouble(); }
    }

    void getAttr(Str const& key, Opt<bool>& value) const {
        Opt<Str> tmp;
        getAttr(key, tmp);
        if (tmp) { value = *tmp == "true"; }
    }


    void getAttr(Str const& key, Opt<Point>& value) const {
        Opt<Str> tmp;
        getAttr(key, tmp);
        if (tmp) {
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

    _eattr(
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

    _eattr(ArrowSize, arrowsize, tiny, small, normal, large, huge);
    _eattr(Dir, dir, forward, back, both, none);
    _eattr(
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


    /// \brief Color of the node's border
    _attr(Color, color, Str);
    /// \brief Fill color of the node
    _attr(FillColor, fillcolor, Str);
    /// \brief Font color of the node's label
    _attr(FontColor, fontcolor, Str);
    /// \brief Font name of the node's label
    _attr(FontName, fontname, Str);
    /// \brief Font size of the node's label
    _attr(FontSize, fontsize, double);
    /// \brief Height of the node
    _attr(Height, height, double);
    /// \brief Label (text) of the node
    _attr_aligned(Label, label, Str);
    /// \brief Position of the node's center
    _attr(Position, pos, Point);
    /// \brief Shape of the node
    _attr(Shape, shape, Str);
    /// \brief URL associated with the node
    _attr(URL, URL, Str);
    /// \brief Width of the node
    _attr(Width, width, double);
    /// \brief External label (text) of the node
    _attr_aligned(XLabel, xlabel, Str);
    /// \brief Position of the node's external label
    _attr(XLabelPosition, xlabelpos, Point);

    Agnodeinfo_t*       info() { return (Agnodeinfo_t*)AGDATA(node); }
    Agnodeinfo_t const* info() const {
        return (Agnodeinfo_t*)AGDATA(node);
    }

    void setFixedWH(double w, double h);

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

    NodeAttribute head() { return NodeAttribute(graph, AGHEAD(edge_)); }
    NodeAttribute tail() { return NodeAttribute(graph, AGTAIL(edge_)); }

    _attr(Constraint, constraint, bool);
    /// \brief Color of the edge
    _attr(Color, color, Str /*Str*/);
    /// \brief Font color of the edge's label
    _attr(FontColor, fontcolor, Str /*Str*/);
    /// \brief Font name of the edge's label
    _attr(FontName, fontname, Str);
    /// \brief Font size of the edge's label
    _attr(FontSize, fontsize, double);
    /// \brief Label (text) of the edge
    _attr_aligned(Label, label, Str);
    /// \brief Position of the edge's label
    _attr(LabelPosition, lp, Point);
    /// \brief Width of the edge's line
    _attr(PenWidth, penwidth, double);
    /// \brief Style of the edge's line
    _attr(Style, style, Str);
    /// \brief URL associated with the edge
    _attr(URL, URL, Str);
    _attr(LHead, lhead, Str);
    _attr(LTail, ltail, Str);

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


class GraphGroup
    : public GraphvizObjBase<GraphGroup>
    , public layout::IGroup {
    void initDefaultSetters();

  public:
    static const int graphvizKind = AGRAPH;


    GraphGroup(
        hstd::SPtr<layout::LayoutRun> run,
        Str const&                    name,
        Agdesc_t                      desc = Agdirected);
    GraphGroup(hstd::SPtr<layout::LayoutRun> run, fs::path const& file);
    GraphGroup(hstd::SPtr<layout::LayoutRun> run, Agraph_t* graph)
        : layout::IGroup{run}
        , graph(graph)
        , defaultEdge(graph, nullptr)
        , defaultNode(graph, nullptr) {
        initDefaultSetters();
    }

    Agraph_t*       get() { return graph; }
    Agraph_t const* get() const { return graph; }

    enum class Splines
    {
        Ortho,
        Polyline,
        Curved
    };


    hstd::SPtr<GraphGroup> newSubgraph(Str const& name) {
        return std::make_shared<GraphGroup>(
            run, agsubg(graph, strdup("cluster_" + name), 1));
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
    _eattr(RankDirection, rankdir, LR, TB, BT, RL);
    /// \brief Placement of nodes withing the graph.
    ///
    /// 'none' is the default value (not in the same/source/sink list
    /// that is explicitly recognized by GV), 'same' causes nodes to be
    /// placd on the same level, `source` is closer to the source
    /// nodes, `sink` is closer to the target
    _eattr(Rank, rank, none, same, source, sink);

    /// \brief Damping factor for force-directed layout
    _attr(Damping, Damping, double);
    /// \brief Spring constant factor for force-directed layout
    _attr(K, K, double);
    /// \brief URL associated with the graph
    _attr(URL, URL, Str);
    /// \brief Desired aspect ratio of the drawing
    _attr(AspectRatio, aspect, double);
    /// \brief Background color of the graph
    _attr(BackgroundColor, bgcolor, Str);
    /// \brief Default edge length
    _attr(DefaultDistance, defaultdist, double);
    /// \brief Default node color
    _attr(DefaultNodeColor, defaultNodeColor, Str);
    /// \brief Default edge color
    _attr(DefaultEdgeColor, defaultEdgeColor, Str);
    /// \brief Font color
    _attr(FontColor, fontcolor, Str);
    /// \brief Font name
    _attr(FontName, fontname, Str);
    /// \brief Font size
    _attr(FontSize, fontsize, double);
    /// \brief Label (title) of the graph
    _attr_aligned(Label, label, Str);
    /// \brief URL associated with the graph label
    _attr_aligned(LabelURL, labelURL, Str);
    /// \brief Horizontal placement of the graph label
    _attr(LabelJustification, labeljust, Str);
    /// \brief Vertical placement of the graph label
    _attr(LabelLocator, labelloc, Str);
    /// \brief Layer separator character
    _attr(LayerListSeparator, layersep, Str);
    /// \brief List of layers in the graph
    _attr(Layers, layers, Str);
    /// \brief Margin around the drawing
    _attr(Margin, margin, Point);
    /// \brief Minimum separation between nodes
    _attr(NodeSeparation, nodesep, double);
    /// \brief Order in which nodes and edges are drawn
    _attr(OutputOrder, outputorder, Str);
    /// \brief Direction of page layout
    _attr(PageDirection, pagedir, Str);
    /// \brief Height of output pages
    _attr(PageHeight, pageheight, double);
    /// \brief Width of output pages
    _attr(PageWidth, pagewidth, double);
    /// \brief Cluster quantum scale factor
    _attr(Quantum, quantum, double);
    /// \brief Minimum separation between ranks
    _attr(RankSeparation, ranksep, double);
    /// \brief Resolution (dpi) of the output image
    _attr(Resolution, resolution, double);
    /// \brief Size of the layout search space
    _attr(SearchSize, searchsize, int);
    /// \brief Maximum size of the drawing
    _attr(Size, size, Point);
    /// \brief Type of edges (splines, lines, etc.)
    _attr(Spline, splines, Str);
    /// \brief Style sheet used for the output
    _attr(StyleSheet, stylesheet, Str);
    /// \brief Whether to use truecolor in the output
    _attr(TrueColor, truecolor, bool);
    /// \brief Viewport size and position
    _attr(ViewPort, viewport, Point);
    _attr(Compound, compound, bool);
    _attr(Concentrate, concentrate, bool);

  public:
    Agraph_t*     graph;
    EdgeAttribute defaultNode;
    EdgeAttribute defaultEdge;

    hstd::UnorderedMap<VertexID, hstd::SPtr<NodeAttribute>> nodeAttributes;
    hstd::UnorderedMap<EdgeID, hstd::SPtr<EdgeAttribute>>   edgeAttributes;
    hstd::UnorderedMap<layout::GroupID, hstd::SPtr<GraphGroup>> subgroups;

    void delVertex(VertexID const& id) {
        agdelnode(get(), nodeAttributes.at(id)->get());
        nodeAttributes.erase(id);
    }

    void delEdge(EdgeID const& id) {
        agdeledge(get(), edgeAttributes.at(id)->get());
        edgeAttributes.erase(id);
    }

    void delSubgraph(layout::GroupID const& id) {
        agdelsubg(get(), subgroups.at(id)->get());
        subgroups.erase(id);
    }

    hstd::SPtr<layout::IVertexVisualAttribute> addVertex(
        VertexID const& id) override;
    hstd::SPtr<layout::IEdgeVisualAttribute> addEdge(
        EdgeID const& id) override;
    layout::GroupID addNewSubgroup() override;
    void addExistingSubgroup(layout::GroupID const& id) override;

    virtual hstd::Vec<VertexID> getVertices() const override {
        return nodeAttributes.keys();
    }

    virtual hstd::Vec<EdgeID> getEdges() const override {
        return edgeAttributes.keys();
    }
};

class Graphviz;
class Layout : public layout::IPlacementAlgorithm {
  public:
    Layout(Graphviz* gvc, hstd::SPtr<layout::LayoutRun> run)
        : layout::IPlacementAlgorithm{run}, gvc{gvc} {}
    LayoutType layout = LayoutType::Dot;

    /// \brief Which DPI to use when converting to and from graphviz sizes.
    /// Backend-specific, 72 is the default used by graphviz.
    [[refl]] int graphviz_size_scaling = 72;

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

    Graphviz* gvc;

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

    hstd::SPtr<hstd::SPtr<layout::IPortLayoutAttribute>> getPorts()
        const override {
        return {};
    }
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
};


class Graphviz {
  public:
    hstd::SPtr<layout::LayoutRun> run;
    Graphviz(hstd::SPtr<layout::LayoutRun> run) : run{run} {
        LOGIC_ASSERTION_CHECK(run != nullptr, "");
        gvc = SPtr<GVC_t>(gvContext(), gvFreeContext);
        if (!gvc) {
            throw std::runtime_error("Failed to create Graphviz context");
        }
    }

    layout::GroupID getNewGraph();

    GVC_t* get() { return gvc.get(); }

  private:
    SPtr<GVC_t> gvc;
};

} // namespace hstd::ext::graph::gv
#endif
