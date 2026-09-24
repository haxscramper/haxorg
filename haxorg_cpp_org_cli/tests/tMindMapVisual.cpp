#include <hstd_cpp_lib/ext/graph/visual/visual_factory.hpp>

class TestFactory : public hstd::ext::graph::VisualFactory {
    using hstd::ext::graph::VisualFactory::VisualFactory;

    hstd::SPtr<hstd::ext::graph::IVertex> newVertex(
        hstd::ext::graph::proto::IVertex const* in) override {
        if (in->payload().Is<org::graph::proto::MapNodePayload>()) {
            return std::make_shared<org::graph::MapNode>();
        } else {
            return VisualFactory::newVertex(in);
        }
    }

    hstd::SPtr<hstd::ext::graph::IPortCollection> newPortCollection(
        hstd::ext::graph::proto::IPortCollection const* in) {
        if (in->payload().Is<org::graph::proto::MapNodePayload>()) {
            logic_todo_impl();
        } else {
            return VisualFactory::newPortCollection(in);
        }
    }

    hstd::SPtr<hstd::ext::graph::IEdgeCollection> newEdgeCollection(
        hstd::ext::graph::proto::IEdgeCollection const* in) {
        if (in->payload().Is<org::graph::proto::MapEdgeCollectionPayload>()) {
            return std::make_shared<org::graph::MapEdgeCollection>();
        } else {
            return VisualFactory::newEdgeCollection(in);
        }
    }

    hstd::SPtr<IPort> newPort(hstd::ext::graph::proto::IPort const* port) {
        if (port->payload().Is<org::graph::proto::MapNodePayload>()) {
            logic_todo_impl();
        } else {
            return VisualFactory::newPort(port);
        }
    }
};


std::unique_ptr<hstd::ext::graph::proto::IGraph> get_layout_structure(
    std::unique_ptr<hstd::ext::graph::proto::IGraph> const& in) {
    auto out = std::make_unique<proto::IGraph>();

    auto        out_hierarchy = out->add_hierarchies();
    std::string rg_id{"root-vertex"};


    auto out_vertex = out->add_vertices();
    out_vertex->set_stable_id(rg_id);
    out_vertex->mutable_payload()->PackFrom(
        hstd::ext::graph::proto::TrivialVertexPayload{});
    gv::proto::GroupAttributePayload attr_payload;
    auto                             out_attr = out_vertex->add_attributes();
    out_attr->mutable_payload()->PackFrom(attr_payload);

    out_hierarchy->mutable_nested_in_map()->insert(
        {rg_id, hstd::ext::graph::proto::VertexIDVec{}});
    out_hierarchy->mutable_payload()->PackFrom(
        hstd::ext::graph::proto::TrivialVertexHierarchyPayload{});

    for (auto const& vertex : in->vertices()) {
        auto out_vertex = out->add_vertices();
        out_vertex->set_stable_id(vertex.stable_id());
        gv::proto::NodeAttributePayload attr_payload;
        attr_payload.set_width(2);
        attr_payload.set_height(2);
        attr_payload.set_label(out_vertex->stable_id());
        attr_payload.set_parent_stable_id(rg_id);
        auto out_attr = out_vertex->add_attributes();
        out_attr->mutable_payload()->PackFrom(attr_payload);
        out_vertex->mutable_payload()->PackFrom(
            hstd::ext::graph::proto::TrivialVertexPayload{});
        out_hierarchy->mutable_nested_in_map()->at(rg_id).add_vertices(
            vertex.stable_id());
    }

    auto edges = out->add_collections();
    edges->mutable_payload()->PackFrom(
        hstd::ext::graph::proto::TrivialEdgeCollectionPayload{});
    for (auto const& edge : in->collections().at(0).edges()) {
        auto out_edge = edges->add_edges();
        out_edge->set_source_vertex_id(edge.source_vertex_id());
        out_edge->set_target_vertex_id(edge.target_vertex_id());
        out_edge->set_stable_id(
            hstd::fmt("{}-{}", edge.source_vertex_id(), edge.target_vertex_id()));

        gv::proto::EdgeAttributePayload attr_payload;
        auto                            out_attr = out_edge->add_attributes();
        attr_payload.set_parent_stable_id(rg_id);
        out_attr->mutable_payload()->PackFrom(attr_payload);
        out_edge->mutable_payload()->PackFrom(
            hstd::ext::graph::proto::TrivialEdgePayload{});
    }

    return out;
}


std::unique_ptr<proto::IGraph> run_layout(
    std::unique_ptr<hstd::ext::graph::proto::IGraph> const& proto) {
    auto        graph = std::make_shared<TrivialGraphBase>();
    TestFactory factory{graph};
    factory.setTraceFile(getDebugFile("graph_serial_read.log"));

    auto proto_layout = get_layout_structure(proto);
    writeFile(
        getDebugFile("proto_laoyout_initial.json"),
        hstd::serde::getJString(*proto_layout));

    graph->readSerial(proto_layout.get(), &factory);
    graph
        ->getVertex(
            graph->getRootVertices(graph->getHierarchies().at(0)->getCollectionID())
                .items()
                .at(0))
        ->getUniqueAttribute<gv::GraphGroup>()
        ->render(getDebugFile("render.png"));

    factory.run->setTraceFile(getDebugFile("serial_read_layout.log"));
    factory.run->runFullLayout();
    auto result = std::make_unique<hstd::ext::graph::proto::IGraph>();
    graph->writeSerial(result.get());
    writeFile(
        getDebugFile("serial_layout_result.json"), hstd::serde::getJString(*result));
    return result;
}

class TestClass {
    void runExternalizedLayoutPipeline() {
        auto serial = state->graph->get_serial();
#if HAXORG_CPP_BUILD_WITH_PROTOBUF
        auto completed_layout = run_layout(serial);
#endif
    }


    // TODO: re-enable
#warning TODO re-enable
#if false
    auto getGraphviz() {
        graph::MapGraph::GvConfig gvc{};
        gvc.run->setTraceFile(getDebugFile("layout_run.log"));
        auto gv = gvc.toGraphviz(versions.back().context, getGraph());
        return gv;
    }
#endif


    void writeGraphviz(fs::path const& name) {
        auto gv = getGraphviz();
        gv->render(name);
    }
};
