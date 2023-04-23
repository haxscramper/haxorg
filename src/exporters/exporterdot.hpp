#ifndef EXPORTERDOT_HPP
#define EXPORTERDOT_HPP

#include <exporters/Exporter.hpp>
#include <hstd/wrappers/graphviz.hpp>

class ExporterDot : public Exporter<ExporterDot, int> {

  public:
    SPtr<Graphviz::Graph> graph;
    struct NodeCtx {
        Graphviz::Node last;
    };

    Vec<NodeCtx> nodes;
    int          counter = 0;

    ExporterDot(QString const& name) {
        graph = std::make_shared<Graphviz::Graph>(name);
    }

    void pushVisit(sem::Wrap<sem::Org> org) {
        Graphviz::Node node = graph->node(QString::number(++counter));
        node.setLabel(to_string(org->getKind()));
        if (!nodes.empty()) {
            graph->edge(node, nodes.back().last);
        }
        nodes.push_back({.last = node});
    }

    void popVisit(sem::Wrap<sem::Org> org) {
        if (!nodes.empty()) {
            nodes.pop_back();
        }
    }
};

#endif // EXPORTERDOT_HPP
