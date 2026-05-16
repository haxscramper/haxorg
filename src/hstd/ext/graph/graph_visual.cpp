#include "graph_visual.hpp"

#include <hstd/stdlib/algorithms.hpp>

using namespace hstd::ext::graph;

hstd::Vec<hstd::ext::visual::VisGroup> layout::LayoutRun::getVisual()
    const {
    hstd::Vec<hstd::ext::visual::VisGroup> res;


    EdgeIteration iter{this};
    auto          aux = [&](this auto&& self,
                            VertexID    id) -> hstd::ext::visual::VisGroup {
        auto                        group  = getGroup(id);
        auto                        attr   = getLayout(id);
        hstd::ext::visual::VisGroup result = getLayout(id)->getVisual(id);

        for (auto const& sub : hstd::sorted(getSubGroups(id).items())) {
            auto visual          = self(sub);
            visual.original_id   = sub.getValue();
            visual.original_type = (int)ILayoutAttribute::Kind::Group;
            result.subgroups.push_back(visual);
        }

        for (auto const& it :
             hstd::sorted(getDirectVertices(id).items())) {
            auto const& attr   = getLayout(it);
            auto        visual = attr->getVisual(it);
            LOGIC_ASSERTION_CHECK_FMT(
                visual.offset == attr->getBBox().upper_left(),
                "Vertex visualization group must use the group offset for "
                "the element placement. The visual group offset is {}, "
                "bounding box offset {}",
                visual.offset,
                attr->getBBox().upper_left());

            visual.original_id   = it.getValue();
            visual.original_type = (int)ILayoutAttribute::Kind::Vertex;
            visual.custom.title  = graph->getDebugVertexFormat(it);

            for (auto const& port :
                 hstd::sorted(ports->getPortsForVertex(it).items())) {
                auto const& attr        = getLayout(port);
                auto        port_visual = attr->getVisual(port);
                visual.subgroups.push_back(port_visual);

                LOGIC_ASSERTION_CHECK_FMT(
                    port_visual.offset == attr->getBBox().upper_left(),
                    "Vertex port_visualization group must use the group "
                    "offset for the element placement. The port_visual "
                    "group offset is {}, bounding box offset {}",
                    visual.offset,
                    attr->getBBox().upper_left());
            }

            result.subgroups.push_back(visual);
        }

        for (auto const& it :
             hstd::sorted(iter.getEdgesForGroup(id).items())) {
            auto const& attr     = getLayout(it);
            auto        visual   = attr->getVisual(it);
            visual.original_id   = it.getValue();
            visual.original_type = (int)ILayoutAttribute::Kind::Edge;
            visual.custom.title  = graph->getDebugEdgeFormat(it);
            result.subgroups.push_back(visual);
        }

        return result;
    };

    for (auto const& rg : groups->getRootVertices()) {
        res.push_back(aux(rg));
    }

    iter.validateLeftoverEdges();

    hstd::ext::visual::VisGroup unbound_edge_overlay;

    for (auto const& it : this->getAllUnboundEdges()) {
        auto const& attr     = getLayout(it);
        auto        visual   = attr->getVisual(it);
        visual.original_id   = it.getValue();
        visual.original_type = (int)ILayoutAttribute::Kind::Edge;
        visual.custom.title  = graph->getDebugEdgeFormat(it);
        unbound_edge_overlay.subgroups.push_back(visual);
    }

    res.push_back(unbound_edge_overlay);

    return res;
}


void hstd::ext::graph::layout::LayoutRun::treeRepr(
    hstd::ColStream&    os,
    TreeReprConf const& conf) const {
    auto g = getGraph();

    EdgeIteration iter{this};

    auto aux_edge = [&](EdgeID const& id, int depth) {
        auto visual = getEdgeVisualAttribute(id);
        os.indent(depth * 2);
        os << hstd::fmt("EDGE {}", g->getDebugEdgeFormat(id));
    };


    auto aux =
        [&](this auto&& self, VertexID const& id, int depth) -> void {
        if (isGroupVertex(id)) {
            auto visual = getGroup(id);
            os.indent(depth * 2);
            os << hstd::fmt("GROUP {}", g->getDebugVertexFormat(id));
            if (visual->hasAlgorithm()) { os << " algo"; }

            if (hasLayout(id)) {
                auto layout = getLayout<IGroupLayoutAttribute>(id);
                os << hstd::fmt(" layout {}", layout->getBBox());
            }

            for (auto const& sub :
                 hstd::sorted(getDirectVertices(id).items())) {
                os.newline();
                self(sub, depth + 1);
            }


            for (auto const& sub :
                 hstd::sorted(iter.getEdgesForGroup(id).items())) {
                os.newline();
                aux_edge(sub, depth + 1);
            }


            for (auto const& sub :
                 hstd::sorted(getSubGroups(id).items())) {
                os.newline();
                self(sub, depth + 1);
            }

        } else {
            auto visual = getVertexVisualAttribute(id);
            os.indent(depth * 2);
            os << hstd::fmt("VERTEX {}", g->getDebugVertexFormat(id));

            if (hasLayout(id)) {
                auto layout = getLayout<IVertexLayoutAttribute>(id);
                os << hstd::fmt(" layout {}", layout->getBBox());
            }
        }
    };

    for (auto const& g : hstd::sorted(groups->getRootVertices().items())) {
        aux(g, 0);
    }

    for (auto const& e : hstd::sorted(iter.getLeftoverEdges().items())) {
        os.newline();
        aux_edge(e, 0);
        os << " leftover";
    }

    for (auto const& e : hstd::sorted(getAllUnboundEdges().items())) {
        os.newline();
        aux_edge(e, 0);
        os << " unbound";
    }
}

hstd::SPtr<IGraph> hstd::ext::graph::layout::IGroupVisualAttribute::
    getGraph() const {
    return run->graph;
}
