#ifndef EXPORTERDOT_HPP
#define EXPORTERDOT_HPP

#include <exporters/Exporter.hpp>
#include <hstd/wrappers/graphviz.hpp>

class ExporterDot : public Exporter<ExporterDot, Graphviz::Node> {
    using Node   = Graphviz::Node;
    using Record = Node::Record;
    using Graph  = Graphviz::Graph;

  public:
#define __ExporterBase Exporter<ExporterDot, Graphviz::Node>
    EXPORTER_USING()
#undef __ExporterBase


    SPtr<Graphviz::Graph> graph;
    struct NodeCtx {
        Graphviz::Node last;
    };

    Vec<NodeCtx> nodes;
    int          counter = 0;

    ExporterDot(QString const& name) {
        graph = std::make_shared<Graphviz::Graph>(name);
        graph->setRankDirection(Graphviz::Graph::RankDirection::LR);
        graph->setFontName("Iosevka");
    }


    void visitField(
        Graphviz::Node& record,
        char const*     name,
        sem::SemId      value) {
        Graphviz::Node target = newRes(value);
    }

    template <typename T>
    void visitField(Node& node, char const* name, CR<Opt<T>> value) {
        if (value) {
            visitField(node, name, *value);
        } else {
            node.getNodeRecord()->set(
                name, Record("<none>" + demangle(typeid(T).name())));
        }
    }

    template <typename T>
    void visitField(
        Graphviz::Node& record,
        char const*     name,
        CR<T>           value) {
        if constexpr (std::is_same_v<T, int>) {
            record.getNodeRecord()->set(
                name, Graphviz::Node::Record(QString::number(value)));
        }
    }

    template <typename T>
    Graphviz::Node newRes(CR<T> value) {
        Graphviz::Node node = graph->node(QString::number(++counter));
        node.startRecord();
        return node;
    }

    void pushVisit(Graphviz::Node& node, sem::SemId org) {
        node.getNodeRecord()->set(
            "kind", Graphviz::Node::Record(to_string(org->getKind())));

        if (!nodes.empty()) {
            graph->edge(node, nodes.back().last);
        }

        nodes.push_back({.last = node});
    }

    void popVisit(Graphviz::Node& record, sem::SemId org) {
        if (!nodes.empty()) {
            nodes.pop_back();
        }
    }

    void visitEnd(sem::SemId org) {
        graph->eachNode([](Graphviz::Node node) { node.finishRecord(); });
    }
};


#endif // EXPORTERDOT_HPP
