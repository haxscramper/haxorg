#ifndef GRAPHVIZ_HPP
#define GRAPHVIZ_HPP


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


#define _attr(Method, key, Type)                                          \
    void set##Method(Type const& value) { set(#key, value); }

#define _attrx(Method, key, Type) void set##Method(Type const& value);

#define _e_enum(Name, ...)                                                \
    enum class Name                                                       \
    {                                                                     \
        __VA_ARGS__                                                       \
    };                                                                    \
    BOOST_DESCRIBE_NESTED_ENUM(Name, __VA_ARGS__);

#define _eattr(Name, key, ...)                                            \
    _e_enum(Name, __VA_ARGS__);                                           \
    void set##Name(Name value) { set(#key, enum_to_string(value)); }

class Graphviz {
  public:
    class Node {
      public:
        Node(Agraph_t* graph, const QString& name) {
            auto node_ = agnode(
                graph, const_cast<char*>(name.toStdString().c_str()), 1);
            if (!node_) {
                throw std::runtime_error("Failed to create node");
            } else {
                node = std::shared_ptr<Agnode_t>(node_);
            }
        }

        Agnode_t*       get() { return node.get(); }
        Agnode_t const* get() const { return node.get(); }

        void set(const QString& attribute, const QString& value) {
            agsafeset(
                node.get(),
                const_cast<char*>(attribute.toStdString().c_str()),
                const_cast<char*>(value.toStdString().c_str()),
                const_cast<char*>(""));
        }

        void set(QString const& key, int value) {
            set(key, QString::number(value));
        }

        void set(QString const& key, QPointF value) {
            set(key, QString("%1,%2").arg(value.x(), value.y()));
        }

        void set(QString const& key, double value) {
            set(key, QString::number(value));
        }

        _eattr(
            Shape,
            shape,
            //
            box,
            circle,
            diamond,
            ellipse,
            hexagon,
            octagon,
            parallelogram,
            triangle);

        _e_enum(
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
        SPtr<Agnode_t> node;
        friend class Graph;
    };

    class Edge {
      public:
        Edge(Agraph_t* graph, CR<Node> head, CR<Node> tail)
            : graph(graph) {
            Q_CHECK_PTR(graph);
            Agedge_t* edge = agedge(
                graph,
                const_cast<Agnode_t*>(tail.get()),
                const_cast<Agnode_t*>(head.get()),
                nullptr,
                1);

            if (!edge) {
                throw std::runtime_error("Failed to create edge");
            }
        }

        void set(const QString& attribute, const QString& value) {
            agsafeset(
                edge_.get(),
                const_cast<char*>(attribute.toStdString().c_str()),
                const_cast<char*>(value.toStdString().c_str()),
                const_cast<char*>(""));
        }

        void set(QString const& key, int value) {
            set(key, QString::number(value));
        }

        void set(QString const& key, double value) {
            set(key, QString::number(value));
        }

        void set(QString const& key, QPointF value) {
            set(key, QString("%1,%2").arg(value.x(), value.y()));
        }

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
        Agraph_t*      graph;
        SPtr<Agedge_t> edge_;
    };

    class Graph {
      public:
        Graph(const QString& name, Agdesc_t desc = Agdirected) {
            Agraph_t* graph_ = agopen(
                const_cast<char*>(name.toStdString().c_str()),
                desc,
                nullptr);
            if (!graph_) {
                throw std::runtime_error("Failed to create graph");
            } else {
                graph = std::shared_ptr<Agraph_t>(graph_);
            }
        }


        void set(const QString& attribute, const QString& value) {
            agsafeset(
                graph.get(),
                const_cast<char*>(attribute.toStdString().c_str()),
                const_cast<char*>(value.toStdString().c_str()),
                const_cast<char*>(""));
        }

        void set(QString const& key, int value) {
            set(key, QString::number(value));
        }

        void set(QString const& key, double value) {
            set(key, QString::number(value));
        }

        void set(QString const& key, QPointF value) {
            set(key, QString("%1,%2").arg(value.x(), value.y()));
        }


        enum class Splines
        {
            Ortho,
            Polyline,
            Curved
        };

        void setSplines(Splines splines);

        Node node(QString const& name) {
            Q_CHECK_PTR(graph.get());
            return Node(graph.get(), name);
        }

        Edge edge(CR<Node> head, CR<Node> tail) {
            Q_CHECK_PTR(graph.get());
            return Edge(graph.get(), head, tail);
        }

        Agraph_t*       get() { return graph.get(); }
        Agraph_t const* get() const { return graph.get(); }

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
        /// \brief Direction of layout ranks
        _attr(RankDirection, rankdir, QString);
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
        SPtr<Agraph_t> graph;
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
        XDOT  /// Extended dot format
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

    void renderToFile(
        CR<Graph>      graph,
        LayoutType     layout,
        RenderFormat   format,
        const QString& fileName) {
        Q_CHECK_PTR(graph.get());
        Q_CHECK_PTR(gvc);
        gvLayout(
            gvc,
            const_cast<Agraph_t*>(graph.get()),
            strdup(layoutTypeToString(layout)));

        gvRenderFilename(
            gvc,
            const_cast<Agraph_t*>(graph.get()),
            strdup(renderFormatToString(format)),
            strdup(fileName));

        gvFreeLayout(gvc, const_cast<Agraph_t*>(graph.get()));
    }

  private:
    GVC_t* gvc;
};


#endif // GRAPHVIZ_HPP
