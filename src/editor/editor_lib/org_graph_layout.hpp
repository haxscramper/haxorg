#pragma once

#include <libcola/cola.h>
#include <libcola/output_svg.h>
#include <hstd/wrappers/graphviz.hpp>
#include <QRect>
#include <QPolygonF>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <editor/editor_lib/app_utils.hpp>
#include <QPainterPath>

struct GraphConstraint {
    struct Align {
        struct Spec {
            int         node;
            Opt<double> fixPos = std::nullopt;
            double      offset = 0.0;
        };

        Vec<Spec> nodes;
        vpsc::Dim dimension;
        DESC_FIELDS(Align, (nodes, dimension));

        SPtr<cola::CompoundConstraint> toCola() const {
            auto result = std::make_shared<cola::AlignmentConstraint>(
                dimension);

            for (auto const& spec : nodes) {
                result->addShape(spec.node, spec.offset);
                if (spec.fixPos) { result->fixPos(*spec.fixPos); }
            }

            return result;
        }
    };

    SPtr<cola::CompoundConstraint> toCola() const {
        return std::visit(
            [](auto const& spec) { return spec.toCola(); }, data);
    }

    SUB_VARIANTS(Kind, Data, data, getKind, Align);
    Data data;

    GraphConstraint(CR<Data> data) : data(data) {};
};


struct GraphLayoutIR {
    using IrEdge = Pair<int, int>;

    struct Subgraph {
        Str           graphName;
        Vec<int>      nodes;
        Vec<Subgraph> subgraphs;
    };

    Vec<QRect>           rectangles;
    Vec<IrEdge>          edges;
    Vec<GraphConstraint> constraints;
    Vec<Subgraph>        subgraphs;
    double               width     = 100;
    double               height    = 100;
    Str                  graphName = "G";

    int graphviz_size_scaling = 72;

    void validate() {
        for (auto const& e : enumerator(edges)) {
            for (auto const& it :
                 Vec<int>{e.value().first, e.value().second}) {
                Q_ASSERT_X(
                    it < rectangles.size(),
                    "validate",
                    fmt("Edge {} point is out of range for rectangles: "
                        "[{}] out of {} rects",
                        e.index(),
                        it,
                        rectangles.size()));
            }
        }
    }

    struct Result {
        struct Subgraph {
            QRect         bbox;
            Vec<Subgraph> subgraphs;

            Subgraph const& getSubgraph(Span<int> path) const {
                switch (path.size()) {
                    case 0: return *this;
                    case 1: return subgraphs.at(path.front());
                    default:
                             return subgraphs.at(path.front())
                            .getSubgraph(path.at(slice(1, 1_B)));
                }
            }
        };

        Vec<QRect>                         fixed;
        UnorderedMap<IrEdge, QPainterPath> lines;
        QRect                              bbox;
        Vec<Subgraph>                      subgraphs;
        Vec<Vec<int>>                      subgraphPaths;

        Subgraph const& getSubgraph(CVec<int> path) {
            switch (path.size()) {
                case 0:
                    throw std::invalid_argument(
                        "Expected at least 1 element in the subgraph "
                        "path, got 0");
                case 1: return subgraphs.at(path.front());
                default:
                    return subgraphs.at(path.front())
                        .getSubgraph(path.at(slice(1, 1_B)));
            }
        }
    };

    struct GraphvizResult {
        Graphviz::Graph graph;
        Graphviz        gvc;
        int             graphviz_size_scaling;

        void writeSvg(CR<Str> path) const {
            gvc.writeFile(path, graph, Graphviz::RenderFormat::SVG);
        }

        void writeXDot(CR<Str> path) const {
            gvc.writeFile(path, graph, Graphviz::RenderFormat::XDOT);
        }

        Result convert();
    };

    GraphvizResult doGraphvizLayout(
        Graphviz             gvc,
        Graphviz::LayoutType layout = Graphviz::LayoutType::Dot);

    /// Intermediate layout representation storage
    struct ColaResult {
        Vec<vpsc::Rectangle>          baseRectangles;
        Vec<vpsc::Rectangle*>         rectPointers;
        Vec<Pair<unsigned, unsigned>> edges;

        Result convert();

        void writeSvg(CR<Str> path) {
            OutputFile output(rectPointers, edges, nullptr, path);
            output.rects = true;
            output.generate();
        }
    };

    ColaResult doColaLayout();
};
