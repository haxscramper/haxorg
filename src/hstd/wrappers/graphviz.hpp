#pragma once

#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <string>
#include <stdexcept>
#include <QString>
#include <hstd/system/all.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <QPointF>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <new>
#include <hstd/stdlib/Func.hpp>


#define _attr(Method, key, Type)                                          \
    void set##Method(Type const& value) { set(#key, value); }

#define _attrx(Method, key, Type) void set##Method(Type const& value);


#define _eattr(Name, key, ...)                                            \
    DECL_DESCRIBED_ENUM(Name, __VA_ARGS__);                               \
    void set##Name(Name value) { set(#key, enum_to_string(value)); }

class Graphviz {
  public:
    struct UserDataBase {
        Agrec_t header;
    };

    template <typename T>
    struct GraphvizObjBase : CRTP_this_method<T> {
        using CRTP_this_method<T>::_this;

        template <typename Rec, typename... Args>
        Rec* bindRecord(QString const& name, Args&&... args) {
            Rec* result = (Rec*)agbindrec(
                _this()->get(),
                name.toStdString().c_str(),
                sizeof(Rec),
                false);
            if (result != nullptr) {
                result = new (result) Rec(std::forward<Args>(args)...);
                return result;
            } else {
                return nullptr;
            }
        }

        template <typename Rec>
        Rec* getRecord(QString const& name) {
            return (Rec*)aggetrec(
                _this()->get(), name.toStdString().c_str(), false);
        }

        void delRecord(QString const& name) {
            agdelrec(_this()->get(), name.toStdString().c_str());
        }

        void set(const QString& attribute, const QString& value) {
            agsafeset(
                _this()->get(),
                const_cast<char*>(attribute.toStdString().c_str()),
                const_cast<char*>(value.toStdString().c_str()),
                const_cast<char*>(""));
        }

        void set(QString const& key, int value) {
            _this()->set(key, QString::number(value));
        }

        void set(QString const& key, QPointF value) {
            _this()->set(key, QString("%1,%2").arg(value.x(), value.y()));
        }

        void set(QString const& key, double value) {
            _this()->set(key, QString::number(value));
        }
    };

    class Node : public GraphvizObjBase<Node> {
      public:
        struct Record {
            static QString escape(const QString& input) {
                QString escaped = input;
                escaped.replace("\\", "\\\\");
                escaped.replace("\"", "\\\"");
                escaped.replace("<", "\\<");
                escaped.replace(">", "\\>");
                escaped.replace("|", "\\|");
                escaped.replace("{", "\\{");
                escaped.replace("}", "\\}");
                return escaped;
            }


            Record() {}
            Record(Str const& content, Opt<Str> const& tag = std::nullopt)
                : content(content), tag(tag) {}

            Record(Vec<Record> const& sub) : content(sub) {}

            void push_back(CR<Vec<Str>> cells) {
                Vec<Record> row;
                for (const auto& it : cells) {
                    row.push_back(it);
                }
                getNested().push_back(Record(row));
            }

            void push_back(CR<Record> rec) { getNested().push_back(rec); }

            bool isFinal() const {
                return std::holds_alternative<Str>(content);
            }

            void set(QString const& columnKey, CR<Record> value);

            bool       isRecord() const { return !isFinal(); }
            Str&       getLabel() { return std::get<Str>(content); }
            Str const& getLabel() const { return std::get<Str>(content); }
            Vec<Record>&       getNested() { return std::get<1>(content); }
            Vec<Record> const& getNested() const {
                return std::get<1>(content);
            }

            Opt<Str>                  tag;
            Variant<Str, Vec<Record>> content;

            Str toString(bool braceCount = 1) const;
        };

        void startRecord() {
            setShape(Shape::record);
            bindRecord<Record>("record");
        }

        Record* getNodeRecord() { return getRecord<Record>("record"); }

        void finishRecord() { setLabel(getNodeRecord()->toString()); }

        Node(Agraph_t* graph, QString const& name, Record const& record)
            : Node(graph, name) {
            setShape(Shape::record);
            setLabel(record.toString());
        }

        Node(Agraph_t* graph, Agnode_t* node_)
            : node(node_), graph(graph) {}

        Node(Agraph_t* graph, const QString& name) {
            auto node_ = agnode(
                graph, const_cast<char*>(name.toStdString().c_str()), 1);
            if (!node_) {
                throw std::runtime_error("Failed to create node");
            } else {
                node = node_;
            }
        }

        Agnode_t*       get() { return node; }
        Agnode_t const* get() const { return node; }


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
            set("arrowhead", enum_to_string(type));
        };

        void setArrowTail(ArrowType type) {
            set("arrowtail", enum_to_string(type));
        };

        _eattr(ArrowSize, arrowsize, tiny, small, normal, large, huge);
        _eattr(Dir, dir, forward, back, both, none);
        _eattr(Style, style, solid, dashed, dotted, bold, invis, tapered);


        /// \brief Color of the node's border
        _attr(Color, color, QString /* QColor */);
        /// \brief Fill color of the node
        _attr(FillColor, fillcolor, QString /* QColor */);
        /// \brief Font color of the node's label
        _attr(FontColor, fontcolor, QString /* QColor */);
        /// \brief Font name of the node's label
        _attr(FontName, fontname, QString);
        /// \brief Font size of the node's label
        _attr(FontSize, fontsize, double);
        /// \brief Height of the node
        _attr(Height, height, double);
        /// \brief Label (text) of the node
        _attr(Label, label, QString);
        /// \brief Position of the node's center
        _attr(Position, pos, QPointF);
        /// \brief Shape of the node
        _attr(Shape, shape, QString);
        /// \brief URL associated with the node
        _attr(URL, URL, QString);
        /// \brief Width of the node
        _attr(Width, width, double);
        /// \brief External label (text) of the node
        _attr(XLabel, xlabel, QString);
        /// \brief Position of the node's external label
        _attr(XLabelPosition, xlabelpos, QPointF);

      private:
        Agnode_t* node;
        Agraph_t* graph;
    };

    class Edge : public GraphvizObjBase<Edge> {
      public:
        Edge(Agraph_t* graph, Agedge_t* edge)
            : edge_(edge), graph(graph) {}

        Edge(Agraph_t* graph, CR<Node> head, CR<Node> tail);

        Agedge_t*       get() { return edge_; }
        Agedge_t const* get() const { return edge_; }

        /// \brief Color of the edge
        _attr(Color, color, QString /*QColor*/);
        /// \brief Font color of the edge's label
        _attr(FontColor, fontcolor, QString /*QColor*/);
        /// \brief Font name of the edge's label
        _attr(FontName, fontname, QString);
        /// \brief Font size of the edge's label
        _attr(FontSize, fontsize, double);
        /// \brief Label (text) of the edge
        _attr(Label, label, QString);
        /// \brief Position of the edge's label
        _attr(LabelPosition, lp, QPointF);
        /// \brief Width of the edge's line
        _attr(PenWidth, penwidth, double);
        /// \brief Style of the edge's line
        _attr(Style, style, QString);
        /// \brief URL associated with the edge
        _attr(URL, URL, QString);

      private:
        Agraph_t* graph;
        Agedge_t* edge_;
    };

    class Graph : public GraphvizObjBase<Graph> {
      public:
        Graph(const QString& name, Agdesc_t desc = Agdirected);
        Graph(Agraph_t* graph) : graph(graph) {}

        Agraph_t*       get() { return graph; }
        Agraph_t const* get() const { return graph; }

        enum class Splines
        {
            Ortho,
            Polyline,
            Curved
        };


        Graph newSubgraph(QString const& name) {
            return Graph(agsubg(graph, name.toLatin1().data(), 1));
        }

        void setSplines(Splines splines);
        void eachNode(Func<void(Node)> cb);
        void eachEdge(Func<void(Edge)> cb);

        // TODO Reuse field and type definitions from the graph nodes
        // instead of relying on strings here.

        /// Set default attribute value for graph node
        void setDefaultNodeAttr(QString const& key, QString const& value) {
            agattr(
                graph,
                AGNODE,
                key.toLatin1().data(),
                value.toLatin1().data());
        }

        /// Set default attriute value for edge
        void setDefaultEdgeAttr(QString const& key, QString const& value) {
            agattr(
                graph,
                AGEDGE,
                key.toLatin1().data(),
                value.toLatin1().data());
        }

        Node node(QString const& name) {
            Q_CHECK_PTR(graph);
            auto tmp = Node(graph, name);
            return tmp;
        }

        Edge edge(CR<Node> head, CR<Node> tail) {
            Q_CHECK_PTR(graph);
            auto tmp = Edge(graph, head, tail);
            return tmp;
        }

        /// \brief Direction of layout ranks
        _eattr(RankDirection, rankdir, LR, TB, BT, RL);

        /// \brief Damping factor for force-directed layout
        _attr(Damping, Damping, double);
        /// \brief Spring constant factor for force-directed layout
        _attr(K, K, double);
        /// \brief URL associated with the graph
        _attr(URL, URL, QString);
        /// \brief Desired aspect ratio of the drawing
        _attr(AspectRatio, aspect, double);
        /// \brief Background color of the graph
        _attr(BackgroundColor, bgcolor, QString /* QColor */);
        /// \brief Default edge length
        _attr(DefaultDistance, defaultdist, double);
        /// \brief Default node color
        _attr(DefaultNodeColor, defaultNodeColor, QString /* QColor */);
        /// \brief Default edge color
        _attr(DefaultEdgeColor, defaultEdgeColor, QString /* QColor */);
        /// \brief Font color
        _attr(FontColor, fontcolor, QString /* QColor */);
        /// \brief Font name
        _attr(FontName, fontname, QString);
        /// \brief Font size
        _attr(FontSize, fontsize, double);
        /// \brief Label (title) of the graph
        _attr(Label, label, QString);
        /// \brief URL associated with the graph label
        _attr(LabelURL, labelURL, QString);
        /// \brief Horizontal placement of the graph label
        _attr(LabelJustification, labeljust, QString);
        /// \brief Vertical placement of the graph label
        _attr(LabelLocator, labelloc, QString);
        /// \brief Layer separator character
        _attr(LayerListSeparator, layersep, QString);
        /// \brief List of layers in the graph
        _attr(Layers, layers, QString);
        /// \brief Margin around the drawing
        _attr(Margin, margin, QPointF);
        /// \brief Minimum separation between nodes
        _attr(NodeSeparation, nodesep, double);
        /// \brief Order in which nodes and edges are drawn
        _attr(OutputOrder, outputorder, QString);
        /// \brief Direction of page layout
        _attr(PageDirection, pagedir, QString);
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
        _attr(Size, size, QPointF);
        /// \brief Type of edges (splines, lines, etc.)
        _attr(Spline, splines, QString);
        /// \brief Style sheet used for the output
        _attr(StyleSheet, stylesheet, QString);
        /// \brief Whether to use truecolor in the output
        _attr(TrueColor, truecolor, bool);
        /// \brief Viewport size and position
        _attr(ViewPort, viewport, QPointF);

      private:
        Agraph_t* graph;
    };


    Graphviz() {
        gvc = gvContext();
        if (!gvc) {
            throw std::runtime_error("Failed to create Graphviz context");
        }
    }

    ~Graphviz() { gvFreeContext(gvc); }


    enum class LayoutType
    {
        Dot,   /// Hierarchical layout
        Neato, /// Spring model layout
        Fdp,   /// Force-directed layout
        Sfdp,  /// Multiscale version of Fdp for large graphs
        Twopi, /// Radial layout
        Circo  /// Circular layout
    };

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


    QString layoutTypeToString(LayoutType layoutType) {
        switch (layoutType) {
            case LayoutType::Dot: return "dot";
            case LayoutType::Neato: return "neato";
            case LayoutType::Fdp: return "fdp";
            case LayoutType::Sfdp: return "sfdp";
            case LayoutType::Twopi: return "twopi";
            case LayoutType::Circo: return "circo";
            default: throw std::runtime_error("Invalid layout type.");
        }
    }

    QString renderFormatToString(RenderFormat renderFormat) {
        switch (renderFormat) {
            case RenderFormat::PNG: return "png";
            case RenderFormat::PDF: return "pdf";
            case RenderFormat::SVG: return "svg";
            case RenderFormat::PS: return "ps";
            case RenderFormat::JPEG: return "jpeg";
            case RenderFormat::GIF: return "gif";
            case RenderFormat::TIF: return "tif";
            case RenderFormat::BMP: return "bmp";
            case RenderFormat::XDOT: return "xdot";
            default: throw std::runtime_error("Invalid render format.");
        }
    }

    void createLayout(
        CR<Graph>  graph,
        LayoutType layout = LayoutType::Dot) {
        gvLayout(
            gvc,
            const_cast<Agraph_t*>(graph.get()),
            strdup(layoutTypeToString(layout)));
    }

    void freeLayout(CR<Graph> graph) {
        gvFreeLayout(gvc, const_cast<Agraph_t*>(graph.get()));
    }

    void writeFile(
        QString const& fileName,
        CR<Graph>      graph,
        RenderFormat   format = RenderFormat::DOT);

    void renderToFile(
        const QString& fileName,
        CR<Graph>      graph,
        RenderFormat   format = RenderFormat::PNG,
        LayoutType     layout = LayoutType::Dot);

  private:
    GVC_t* gvc;
};
