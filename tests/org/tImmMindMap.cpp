/// \file Immutable AST mind map tests


#include "tOrgTestCommon.hpp"
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/MapFormatter.hpp>

#include "src/haxorg/imm/ImmOrgGraph.pb.h"

using namespace hstd::ext::graph;


#if ORG_BUILD_WITH_PROTOBUF
class TestFactory : public IGraphSerialReaderFactory {
  public:
    hstd::SPtr<IVertexHierarchy> newVertexHierarchy(
        proto::IVertexHierarchy const* in) override {
        LOGIC_ASSERTION_CHECK_FMT(
            in->has_payload(),
            "De-serialization input does not have payload object {}",
            getJString(*in));
        OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
        if (in->payload().Is<proto::TrivialVertexHierarchyPayload>()) {
            return std::make_shared<TrivialHierarchy>();
        } else {
            throw hstd::logic_unhandled_kind_error::init(in->payload().type_url());
        }
    }

    hstd::SPtr<IEdgeCollection> newEdgeCollection(
        proto::IEdgeCollection const* in) override {
        LOGIC_ASSERTION_CHECK_FMT(
            in->has_payload(),
            "De-serialization input does not have payload object {}",
            getJString(*in));
        OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
        if (in->payload().Is<org::graph::proto::MapEdgeCollectionPayload>()) {
            return std::make_shared<org::graph::MapEdgeCollection>();
        } else if (in->payload().Is<proto::TrivialEdgeCollectionPayload>()) {
            return std::make_shared<TrivialEdgeCollection>(
                EdgeCollectionID{static_cast<hstd::u16>(in->collection_id())});
        } else {
            throw hstd::logic_unhandled_kind_error::init(in->payload().type_url());
        }
    }

    hstd::SPtr<IPortCollection> newPortCollection(
        proto::IPortCollection const* in) override {
        LOGIC_ASSERTION_CHECK_FMT(
            in->has_payload(),
            "De-serialization input does not have payload object {}",
            getJString(*in));
        OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
        if (in->payload().Is<org::graph::proto::MapNodePayload>()) {
        } else {
            throw hstd::logic_unhandled_kind_error::init(in->payload().type_url());
        }
    }


    hstd::SPtr<layout::LayoutRun> run;
    hstd::SPtr<IGraph>            graph;

    hstd::SPtr<IAttribute> newAttribute(
        proto::IAttribute const* in,
        IGraph const*            graph,
        IAttributeObject const*  parent) override {
        LOGIC_ASSERTION_CHECK_FMT(
            in->has_payload(),
            "De-serialization input does not have payload object {}",
            getJString(*in));
        OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());

        if (!run) {
            if (this->graph->getPorts().empty()) {
                this->graph->addPorts(std::make_shared<TrivialPortCollection>());
            }

            run = std::make_shared<layout::LayoutRun>(
                this->graph,
                this->graph->getCollections().at(0)->getCollectionID(),
                this->graph->getPorts().at(0)->getCollectionID(),
                this->graph->getHierarchies().at(0)->getCollectionID());
        }

        if (in->payload().Is<gv::proto::GroupAttributePayload>()) {
            auto vertex = hstd::validated_dynamic_cast<IVertex>(parent);
            gv::proto::GroupAttributePayload pl;
            in->payload().UnpackTo(&pl);

            if (pl.has_parent_stable_id()) {
                return graph
                    ->getVertex(graph->getVertexIDByStableId(pl.parent_stable_id()))
                    ->getUniqueAttribute<gv::GraphGroup>()
                    ->newSubgraph(vertex->getStableId());
            } else {
                return gv::GraphGroup::newRootGraph(run, vertex->getStableId());
            }
        } else if (in->payload().Is<gv::proto::NodeAttributePayload>()) {
            auto vertex = hstd::validated_dynamic_cast<IVertex>(parent);
            gv::proto::NodeAttributePayload pl;
            in->payload().UnpackTo(&pl);
            LOGIC_ASSERTION_CHECK_FMT(
                !pl.parent_stable_id().empty(),
                "Parent stable ID cannot be set to empty, graphviz "
                "attribute for node '{}' must have the parent ID "
                "specified",
                vertex->getStableId());

            return graph->getVertex(graph->getVertexIDByStableId(pl.parent_stable_id()))
                ->getUniqueAttribute<gv::GraphGroup>()
                ->node(vertex->getStableId());
        } else if (in->payload().Is<gv::proto::EdgeAttributePayload>()) {
            auto vertex = hstd::validated_dynamic_cast<IEdge>(parent);
            gv::proto::EdgeAttributePayload pl;
            in->payload().UnpackTo(&pl);
            LOGIC_ASSERTION_CHECK_FMT(
                !pl.parent_stable_id().empty(),
                "Parent stable ID cannot be set to empty, graphviz "
                "attribute for node '{}' must have the parent ID "
                "specified",
                vertex->getStableId());

            auto edge_id = graph->getEdgeIDByStableId(vertex->getStableId());

            return graph->getVertex(graph->getVertexIDByStableId(pl.parent_stable_id()))
                ->getUniqueAttribute<gv::GraphGroup>()
                ->edge(
                    *graph->getVertex(graph->getSource(edge_id))
                         ->getUniqueAttribute<gv::NodeAttribute>(),
                    *graph->getVertex(graph->getTarget(edge_id))
                         ->getUniqueAttribute<gv::NodeAttribute>());
        } else {
            throw hstd::logic_unhandled_kind_error::init(in->payload().type_url());
        }
    }

    hstd::SPtr<IVertex> newVertex(proto::IVertex const* in) override {
        LOGIC_ASSERTION_CHECK_FMT(
            in->has_payload(),
            "De-serialization input does not have payload object {}",
            getJString(*in));
        OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
        hstd::SPtr<IVertex> res;
        if (in->payload().Is<org::graph::proto::MapNodePayload>()) {
            res = std::make_shared<org::graph::MapNode>();
        } else if (in->payload().Is<proto::TrivialVertexPayload>()) {
            res = std::make_shared<TrivialVertex>(in->stable_id());
        } else {
            throw hstd::logic_unhandled_kind_error::init(in->payload().type_url());
        }

        return res;
    }

    hstd::SPtr<layout::IConstraint> newConstraint(proto::IConstraint const* in) override {
        LOGIC_ASSERTION_CHECK_FMT(
            in->has_payload(),
            "De-serialization input does not have payload object {}",
            getJString(*in));
        OP_TRACER_MESSAGE(this, "URL {}", in->payload().type_url());
        hstd::SPtr<layout::IConstraint> res;
        if (false) {
        } else {
            throw hstd::logic_unhandled_kind_error::init(in->payload().type_url());
        }

        return res;
    }


    hstd::SPtr<IEdge> newEdge(proto::IEdge const* edge) override {
        LOGIC_ASSERTION_CHECK_FMT(
            edge->has_payload(),
            "De-serialization input does not have payload object {}",
            getJString(*edge));

        if (edge->payload().Is<proto::TrivialEdgePayload>()) {
            return std::make_shared<TrivialEdge>(edge->stable_id());
        } else {
            throw hstd::logic_unhandled_kind_error::init(edge->payload().type_url());
        }
    }

    hstd::SPtr<IPort> newPort(proto::IPort const* port) override {
        LOGIC_ASSERTION_CHECK_FMT(
            port->has_payload(),
            "De-serialization input does not have payload object {}",
            getJString(*port));

        if (port->payload().Is<org::graph::proto::MapNodePayload>()) {
        } else {
            throw hstd::logic_unhandled_kind_error::init(port->payload().type_url());
        }
    }
};

#endif

std::unique_ptr<proto::IGraphProto> get_layout_structure(
    std::unique_ptr<proto::IGraphProto> const& in) {
    auto out = std::make_unique<proto::IGraphProto>();

    auto        out_hierarchy = out->add_hierarchies();
    std::string rg_id{"root-vertex"};


    auto out_vertex = out->add_vertices();
    out_vertex->set_stable_id(rg_id);
    out_vertex->mutable_payload()->PackFrom(proto::TrivialVertexPayload{});
    gv::proto::GroupAttributePayload attr_payload;
    auto                             out_attr = out_vertex->add_attributes();
    out_attr->mutable_payload()->PackFrom(attr_payload);

    out_hierarchy->mutable_nested_in_map()->insert({rg_id, proto::VertexIDVec{}});
    out_hierarchy->mutable_payload()->PackFrom(proto::TrivialVertexHierarchyPayload{});

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
        out_vertex->mutable_payload()->PackFrom(proto::TrivialVertexPayload{});
        out_hierarchy->mutable_nested_in_map()->at(rg_id).add_vertices(
            vertex.stable_id());
    }

    auto edges = out->add_collections();
    edges->mutable_payload()->PackFrom(proto::TrivialEdgeCollectionPayload{});
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
        out_edge->mutable_payload()->PackFrom(proto::TrivialEdgePayload{});
    }

    return out;
}

#if ORG_BUILD_WITH_PROTOBUF
std::unique_ptr<proto::IGraphProto> run_layout(
    std::unique_ptr<proto::IGraphProto> const& proto) {
    TestFactory factory;
    factory.setTraceFile(getDebugFile("graph_serial_read.log"));

    auto proto_layout = get_layout_structure(proto);
    writeFile(getDebugFile("proto_laoyout_initial.json"), getJString(*proto_layout));

    auto graph    = std::make_shared<TrivialGraphBase>();
    factory.graph = graph;
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
    auto result = std::make_unique<proto::IGraphProto>();
    graph->writeSerial(result.get());
    writeFile(getDebugFile("serial_layout_result.json"), getJString(*result));
    return result;
}
#endif

struct ImmMapApi : ImmOrgApiTestBase {
    org::graph::MapConfig::Ptr     conf;
    org::graph::MapGraphState::Ptr state;
    imm::ImmAstContext::Ptr        store;
    hstd::Vec<imm::ImmAstVersion>  versions;

    ImmMapApi()
        : conf{org::graph::MapConfig::shared()}
        , store{imm::ImmAstContext::init_start_context()} //
    {}

    imm::ImmAstVersion const& getVersion() const { return versions.back(); }

    imm::ImmAdapter getLastRootAdapter() const { return getVersion().getRootAdapter(); }

    hstd::Vec<imm::ImmAdapter> getRootAdapters() const {
        return versions | hstd::rv::transform([](imm::ImmAstVersion const& v) {
                   return v.getRootAdapter();
               })
             | hstd::rs::to<hstd::Vec>();
    }

    org::graph::MapGraph::Ptr getGraph() const {
        hstd::logic_assertion_check_not_nil(state);
        hstd::logic_assertion_check_not_nil(state->graph);
        return state->graph;
    }

    org::graph::MapGraphState::Ptr getState() const { return state; }

    void init_with(Str const& text) {
        auto node = testParseString(text);
        writeTreeRepr(node, getDebugFile("repr.yaml"));
        init_with(node);
        writeTreeRepr(getLastRootAdapter(), getDebugFile("repr.txt"));
        writeTreeRepr(
            getLastRootAdapter(),
            getDebugFile("repr_verbose.txt"),
            imm::ImmAdapter::TreeReprConf{
                .withReflFields = true,
                .withAuxFields  = true,
            });

        writeFile(
            getDebugFile("repr_tracking.txt"),
            getVersion().getContext()->currentTrack->toString().toString(false));
    }

    void init_with(Vec<std::string> const& texts) {
        auto nodes = texts
                   | hstd::rv::transform(std::bind_back(&testParseString, std::nullopt))
                   | hstd::rs::to<Vec>();
        for (auto const& [idx, node] : hstd::enumerate(nodes)) {
            writeTreeRepr(node, getDebugFile(fmt("repr_{}.yaml", idx)));
        }

        init_with(nodes);
        for (auto const& [idx, adapter] : hstd::enumerate(getRootAdapters())) {
            writeTreeRepr(adapter, getDebugFile(fmt("repr_{}.txt", idx)));
            writeTreeRepr(
                adapter,
                getDebugFile(fmt("repr_{}_verbose.txt", idx)),
                imm::ImmAdapter::TreeReprConf{
                    .withReflFields = true,
                    .withAuxFields  = true,
                });

            writeFile(
                getDebugFile(fmt("repr_{}_tracking.txt", idx)),
                getVersion().getContext()->currentTrack->toString().toString(false));
        }
    }

    void init_with(org::sem::SemId<org::sem::Org> const& node) {
        setImmContextTraceFile(getDebugFile("imm.log"));
        versions = {store->addRoot(node)};
        state    = org::graph::MapGraphState::shared(versions.back().context);
        setGraphTraceFile(getDebugFile("graph.log"));
        getGraph()->message("init done");
    }

    void init_with(hstd::Vec<org::sem::SemId<org::sem::Org>> const& nodes) {
        setImmContextTraceFile(getDebugFile("imm.log"));
        versions = {store->addRoot(nodes.front())};
        for (auto const& n : nodes.at(slice(1, 1_B))) {
            versions.push_back(versions.back().context->addRoot(n));
        }
        state = org::graph::MapGraphState::shared(versions.back().context);
        setGraphTraceFile(getDebugFile("graph.log"));
        getGraph()->message("init done");
    }

    void initGraph(std::shared_ptr<org::imm::ImmAstContext> const& ast) {
        state = org::graph::MapGraphState::FromAstContext(ast);
    }

    void addNodeRec(Vec<imm::ImmAdapter> const& nodes) {
        for (auto const& node : nodes) { state->addNodeRec(node.ctx.lock(), node, conf); }
    }

    void addNode(imm::ImmAdapter const& node) {
        state->addNodeRec(node.ctx.lock(), node, conf);
    }

    void addNodeRec(imm::ImmAdapter const& node) {
        state->addNodeRec(node.ctx.lock(), node, conf);
    }

    void writeRepresentation() {
        writeGraphviz(getDebugFile("graph.png"));
        auto serial = state->graph->get_serial();
        writeFile(getDebugFile("serial.json"), getJString(*serial));
    }

    void runExternalizedLayoutPipeline() {
        auto serial = state->graph->get_serial();
#if ORG_BUILD_WITH_PROTOBUF
        auto completed_layout = run_layout(serial);
#endif
    }

    auto getGraphviz() {
        graph::MapGraph::GvConfig gvc{};
        gvc.run->setTraceFile(getDebugFile("layout_run.log"));
        auto gv = gvc.toGraphviz(versions.back().context, getGraph());
        return gv;
    }

    void writeGraphviz(fs::path const& name) {
        auto gv = getGraphviz();
        gv->render(name);
    }

    void setGraphTraceFile(fs::path const& name) { getGraph()->setTraceFile(name); }

    void setImmContextTraceFile(fs::path const& name) {
        store->debug->setTraceFile(name);
    }

    fs::path getTraceFile() { return getGraph()->traceFile.value(); }
};


TEST_F(ImmMapApi, AddNode) {
    init_with("* subtree");
    EXPECT_EQ(getGraph()->getVertexCount(), 0);
    auto v1 = getState()->addNode(getVersion().getRootAdapter(), conf);
    EXPECT_EQ(getGraph()->getVertexCount(), 1);

    writeRepresentation();
    runExternalizedLayoutPipeline();
}

TEST_F(ImmMapApi, AddNodeWithLinks) {
    init_with(R"(
Paragraph [[id:subtree-id]]

* Subtree
  :properties:
  :id: subtree-id
  :end:
)"_ss);

    auto root = getVersion().getRootAdapter();
    EXPECT_EQ(getGraph()->getVertexCount(), 0);
    EXPECT_EQ(getGraph()->getSummedEdgeCount(), 0);
    EXPECT_EQ(getState()->unresolved.size(), 0);

    getGraph()->message("add first node");
    auto v1 = VertexID::Nil();
    {
        auto __scope = getGraph()->begin_scope();
        auto par     = root.at(1);

        auto init_prop = conf->getInitialNodeProp(state.get(), par);
        ASSERT_EQ(init_prop->unresolved.size(), 1);
        ASSERT_TRUE(init_prop->unresolved.at(0).isLink());

        v1 = getState()->addNode(par, conf);

        ASSERT_EQ(
            getGraph()
                ->getVertex(v1)
                ->getUniqueAttribute<org::graph::MapNodeProp>()
                ->unresolved.size(),
            1);

        EXPECT_EQ(par->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(getGraph()->getVertexCount(), 1);
        EXPECT_EQ(getGraph()->getSummedEdgeCount(), 0);
        ASSERT_EQ(getState()->unresolved.size(), 1);
        // EXPECT_EQ(getState()->unresolved.items().at(0), par.uniq());
    }

    getGraph()->message("add second node");
    {
        auto __scope = getGraph()->begin_scope();
        auto v       = getState()->addNode(root.at(3), conf);
        EXPECT_EQ(getGraph()->getVertexCount(), 2);
        ASSERT_EQ(
            getGraph()
                ->getVertex(v1)
                ->getUniqueAttribute<org::graph::MapNodeProp>()
                ->unresolved.size(),
            0);

        EXPECT_EQ(getState()->unresolved.size(), 0);
        EXPECT_EQ(getGraph()->getSummedEdgeCount(), 1);
        EXPECT_EQ(getGraph()->getEdges().size(), 1);
    }

    writeRepresentation();
    runExternalizedLayoutPipeline();
}


TEST_F(ImmMapApi, SubtreeBacklinks) {
    init_with({
        R"(
* Subtree1
  :properties:
  :id: subtree-1
  :end:

#+attr_list: :attached subtree
- [[id:subtree-2]] :: Forward link
)"_ss,
        R"(
* Subtree2
  :properties:
  :id: subtree-2
  :end:

#+attr_list: :attached subtree
- [[id:subtree-1]] :: Backlink
)"_ss,
    });

    addNodeRec(getRootAdapters());

    EXPECT_EQ(getGraph()->getVertexCount(), 2);
    EXPECT_EQ(getGraph()->getSummedEdgeCount(), 2);
    EXPECT_EQ(getState()->unresolved.size(), 0);

    writeRepresentation();
    runExternalizedLayoutPipeline();
}

TEST_F(ImmMapApi, RadioTargetsForward) {
    init_with(R"(
<<<radio>>> target paragraph

radio user paragraph
)"_ss);

    EXPECT_EQ(getGraph()->getVertexCount(), 0);
    EXPECT_EQ(getGraph()->getSummedEdgeCount(), 0);
    EXPECT_EQ(getState()->unresolved.size(), 0);

    {
        auto __scope = getGraph()->begin_scope("add first node");
        auto par     = getLastRootAdapter().at(1);
        auto v       = getState()->addNode(par, conf);
        EXPECT_EQ(par->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(getGraph()->getVertexCount(), 1);
        EXPECT_EQ(getGraph()->getSummedEdgeCount(), 0);
        ASSERT_EQ(getState()->unresolved.size(), 0);
    }

    {
        auto __scope = getGraph()->begin_scope("add second node");
        auto v       = getState()->addNode(getLastRootAdapter().at(3), conf);
        EXPECT_EQ(getGraph()->getVertexCount(), 2);
        EXPECT_EQ(getGraph()->getSummedEdgeCount(), 1);
        EXPECT_EQ(getState()->unresolved.size(), 0);
    }

    writeRepresentation();
    runExternalizedLayoutPipeline();
}

TEST_F(ImmMapApi, RadioTargetsInverse) {
    init_with(R"(
radio user paragraph

<<<radio>>> target paragraph
)"_ss);


    EXPECT_EQ(getGraph()->getVertexCount(), 0);
    EXPECT_EQ(getGraph()->getSummedEdgeCount(), 0);
    EXPECT_EQ(getState()->unresolved.size(), 0);

    {
        auto __scope = getGraph()->begin_scope("add first node");
        auto par     = getLastRootAdapter().at(1);
        auto v       = getState()->addNode(par, conf);
        EXPECT_EQ(par->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(getGraph()->getVertexCount(), 1);
        EXPECT_EQ(getGraph()->getSummedEdgeCount(), 0);
        // radio link tracking is finalized by the time the immutable AST
        // context is constructed, even though the graph node with radio
        // target has not been added to the graph yet, the unresolve link
        // is registered.
        ASSERT_EQ(getState()->unresolved.size(), 1);
    }

    {
        auto __scope = getGraph()->begin_scope("add second node");
        auto v       = getState()->addNode(getLastRootAdapter().at(3), conf);
        EXPECT_EQ(getGraph()->getVertexCount(), 2);
        EXPECT_EQ(getGraph()->getSummedEdgeCount(), 1);
        EXPECT_EQ(getState()->unresolved.size(), 0);
    }

    writeRepresentation();
    runExternalizedLayoutPipeline();
}

TEST_F(ImmMapApi, RadioTargetAliases) {
    init_with(R"(
* Subtree with item description
  :properties:
  :radio_id: alias1
  :radio_id: alias2
  :radio_id: human-readable alias
  :end:

* Other subtree

alias1 is a thing

alias2 is a thing

also known as a human-readable alias
)"_ss);

    auto root = getLastRootAdapter();
    addNodeRec(root);
    writeRepresentation();

    imm::ImmAdapter t1         = root.at(1);
    imm::ImmAdapter t2         = root.at(2);
    imm::ImmAdapter par_alias1 = t2.at(0);
    imm::ImmAdapter par_alias2 = t2.at(2);
    imm::ImmAdapter par_human  = t2.at(4);

    EXPECT_TRUE(getGraph()->hasEdge(par_alias1.uniq(), t1.uniq()));
    EXPECT_TRUE(getGraph()->hasEdge(par_alias2.uniq(), t1.uniq()));
    EXPECT_TRUE(getGraph()->hasEdge(par_human.uniq(), t1.uniq()));

    writeRepresentation();
    runExternalizedLayoutPipeline();
}

Str getFullMindMapText() {
    Vec<Str> text{
        R"(
* Mind map nodes are made from subtrees
)",
        R"(
** Subtrees can be nested for clustering
   :PROPERTIES:
   :ID:       c468e9c7-7422-4b17-8ccb-53575f186fe0
   :END:
)",
        R"(
** More than one subtree can exist in cluster
)",
        R"(
Tree  description, maybe  on multiple  lines.
Can include  [[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][links]] to  other trees.
Links are attached to specific [[id:6d6d6689-d9da-418d-9f91-1c8c4428e5af][rows]] in the text
so it is easier to track which part of the
description refers to the [[id:9879fed7-f0a4-44bd-bf56-983279afc622][other]] tree
)",
        R"(- )",
        R"(when [[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][link]] :: Description lists can be used for annotated links

)",
        R"(  Multiple paragraphs attached to link
)",
        R"(
used in description list it's placed as annotation to the graph node.
Description can take multiple lines[fn:lines-20].
)",
        R"(
[fn:lines-20]  Footnotes  are placed  into  separate  nodes. You  can  have
nested[fn:nested-23]
)",
        R"(
[fn:nested-23] footnotes
)",
        R"(
** Extra entries
   :PROPERTIES:
   :ID:       6d6d6689-d9da-418d-9f91-1c8c4428e5af
   :END:
)",
        R"(
Parent subtrees can contain some things.
)",
        R"(
* Several clusters can exist
)",
        R"(
Nested subtrees
Multiline [[id:6d6d6689-d9da-418d-9f91-1c8c4428e5af][Extra entries]]
)",
        R"(
** With multiple nodes
   :PROPERTIES:
   :ID:       9879fed7-f0a4-44bd-bf56-983279afc622
   :END:
)",
        R"(
** And even nested
)",
        R"(
*** Clusters
)",
        R"(
*** And nodes
)",
        R"(
*** Intercluster links are possible
)",
        R"(
[[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][Annotation for the target subtree]]
[[id:XXSDASD][Unresolved subtree]]
)",
        "- ",
        "Regular list element\n",
        "- ",
        "Two items in a list\n",
    };
    return join("", text);
}

using osk = OrgSemKind;

TEST_F(ImmMapApi, SubtreeFullMap) {
    init_with(getFullMindMapText());
    imm::ImmAdapter file = getLastRootAdapter();

    EXPECT_EQ(file.at(1)->getKind(), osk::Subtree);
    // see debug `repr.txt` for the test for the full collection of paths.
    auto node_s10  = file.at(Vec{1, 0});
    auto node_p110 = file.at({1, 1, 0});
    auto node_s12  = file.at(Vec{1, 2});
    EXPECT_EQ(node_s10->getKind(), osk::Subtree);
    EXPECT_EQ(
        node_s10.as<imm::ImmSubtree>()->treeId->value(),
        "c468e9c7-7422-4b17-8ccb-53575f186fe0");

    EXPECT_EQ(node_s12->getKind(), osk::Subtree);
    EXPECT_EQ(
        node_s12.as<imm::ImmSubtree>()->treeId->value(),
        "6d6d6689-d9da-418d-9f91-1c8c4428e5af");


    auto conf = org::graph::MapConfig ::shared();
    getGraph()->setTraceFile(getDebugFile("conf"));
    addNodeRec(file);

    EXPECT_TRUE(getGraph()->hasEdge(node_p110.uniq(), node_s12.uniq()));
    EXPECT_TRUE(getGraph()->hasEdge(node_p110.uniq(), node_s10.uniq()));

    writeRepresentation();
    runExternalizedLayoutPipeline();

    auto Subtree_1 = file.at({1, 0}).as<org::imm::ImmSubtree>();
    // EXPECT_EQ(getGraph().getEd)
}

Str getSubtreeBlockText() {
    return Str{R"str(
* Subtree 1
  :properties:
  :id: subtree_1
  :end:

#+attr_list: :attached subtree
- [[id:subtree_2]] :: Describe link to subtree 2
- [[internal_1]] :: Describe link to internal

<<internal_1>> Internal paragraph [fn:footnote_1]

#+begin_comment :attach above
Comment for the paragraph content above
#+end_comment

[fn:footnote_1] Definition of the footnote 1

Second paragraph [fn:footnote_2]

[fn:footnote_2] Footnote 2 [fn:recursive_1]

[fn:recursive_1] Recursive footnote 1 [fn:recursive_2]

[fn:recursive_2] Recursive footnote 2

* Subtree 2
  :properties:
  :id: subtree_2
  :end:

- [[id:subtree_2]] :: Standalone description list targeting subtree
- [[id:subtree_1]] :: Targeting subtree one
- [[internal_1]] :: Targeting standalone paragraph 1
- [[named-paragraph-one]] :: Targeting named paragraph

#+name: named-paragraph-one
Paragraph with name annotations
)str"};
}

struct DocItem {
    imm::ImmAdapter id;
    DESC_FIELDS(DocItem, (id));
};

struct DocBlock {
    Vec<DocItem>  items;
    Vec<DocBlock> nested;
    DESC_FIELDS(DocBlock, (items, nested));
};

DocBlock fromAst(imm::ImmAdapter const& id) {
    SemSet Skip{OrgSemKind::Newline};

    DocBlock result;
    switch (id->getKind()) {
        case OrgSemKind::Document: {
            for (auto const& sub : id.sub()) {
                if (!Skip.contains(sub->getKind())) {
                    result.nested.push_back(fromAst(sub));
                }
            }
            break;
        }
        case OrgSemKind::Subtree: {
            result.items.push_back(DocItem{.id = id});
            for (auto const& sub : id.sub()) {
                if (!Skip.contains(sub->getKind())) {
                    result.nested.push_back(fromAst(sub));
                }
            }
            break;
        }

        default: {
            if (!org::imm::isAttachedDescriptionList(id)) {
                result.items.push_back(DocItem{.id = id});
            }

            break;
        }
    }

    return result;
}

void addAll(
    org::graph::MapGraphState::Ptr const& state,
    DocBlock const&                       block,
    org::graph::MapConfig::Ptr            conf) {
    for (auto const& it : block.items) { std::ignore = state->addNode(it.id, conf); }

    for (auto const& it : block.nested) { addAll(state, it, conf); }
}

TEST_F(ImmMapApi, SubtreeBlockMap) {
    init_with(getSubtreeBlockText());
    imm::ImmAdapter root = getLastRootAdapter();
    DocBlock        doc  = fromAst(root);
    addAll(state, doc, conf);

    imm::ImmAdapter comment   = root.at({1, 3});
    imm::ImmAdapter par_above = root.at({1, 1});
    EXPECT_EQ(comment->getKind(), OrgSemKind::BlockComment);
    EXPECT_EQ(par_above->getKind(), OrgSemKind::Paragraph);

    writeRepresentation();

    auto List_1       = root.at(1).at(0);
    auto List_2       = root.at(2).at(0);
    auto Paragraph_10 = root.at(1).at(9);
    EXPECT_EQ((imm::flatWords(Paragraph_10)), (Vec<Str>{"Footnote", "2"}));

    auto Paragraph_11 = root.at(1).at(11);
    EXPECT_EQ((imm::flatWords(Paragraph_11)), (Vec<Str>{"Recursive", "footnote", "1"}));

    auto Paragraph_12 = root.at(1).at(13);
    EXPECT_EQ((imm::flatWords(Paragraph_12)), (Vec<Str>{"Recursive", "footnote", "2"}));


    auto Paragraph_14 = root.at(2).at(0).at(0).at(0);
    auto Paragraph_16 = root.at(2).at(0).at(1).at(0);
    auto Paragraph_17 = root.at(2).at(0).at(2).at(0);
    auto Paragraph_19 = root.at(2).at(0).at(3).at(0);
    auto Paragraph_20 = root.at(2).at(1);
    EXPECT_EQ(
        (imm::flatWords(Paragraph_20)),
        (Vec<Str>{"Paragraph", "with", "name", "annotations"}));

    auto Paragraph_3 = root.at(1).at(0).at(0).at(0);
    auto Paragraph_5 = root.at(1).at(0).at(1).at(0);
    auto Paragraph_6 = root.at(1).at(1);
    EXPECT_EQ((imm::flatWords(Paragraph_6)), (Vec<Str>{"Internal", "paragraph"}));

    auto Paragraph_7 = root.at(1).at(3).at(0);
    auto Paragraph_8 = root.at(1).at(5);
    auto Paragraph_9 = root.at(1).at(7);
    EXPECT_EQ((imm::flatWords(Paragraph_9)), (Vec<Str>{"Second", "paragraph"}));

    auto Subtree_1 = root.at(1);
    EXPECT_EQ(
        (imm::flatWords(Subtree_1.as<imm::ImmSubtree>().getTitle())),
        (Vec<Str>{"Subtree", "1"}));

    auto Subtree_2 = root.at(2);
    EXPECT_EQ(
        (imm::flatWords(Subtree_2.as<imm::ImmSubtree>().getTitle())),
        (Vec<Str>{"Subtree", "2"}));

    auto BlockComment_1 = root.at(1).at(3);

    EXPECT_EQ(List_1->getKind(), OrgSemKind::List);
    EXPECT_EQ(List_2->getKind(), OrgSemKind::List);
    EXPECT_EQ(Paragraph_10->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_11->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_12->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_14->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_16->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_17->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_19->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_20->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_3->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_5->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_6->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_7->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_8->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_9->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Subtree_1->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(Subtree_2->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(BlockComment_1->getKind(), OrgSemKind::BlockComment);

    auto g = getGraph();

    // from description list to surrounding elements
    g->hasEdge(List_2, Paragraph_20);
    g->hasEdge(List_2, Subtree_1);
    g->hasEdge(List_2, Subtree_2);
    g->hasEdge(List_2, Paragraph_6);
    g->hasEdge(Subtree_1, Subtree_2);
    g->hasEdge(Subtree_1, Paragraph_6);
    g->hasEdge(Paragraph_6, BlockComment_1);
    g->hasEdge(Paragraph_9, Paragraph_10);
    g->hasEdge(Paragraph_10, Paragraph_11);
    g->hasEdge(Paragraph_11, Paragraph_12);

    writeRepresentation();
    runExternalizedLayoutPipeline();
}

TEST_F(ImmMapApi, Doc1Graph) {
    __perf_trace("imm", "run test");
    fs::path file = fs::path{std::getenv("HOME")} / std::string{"tmp/doc_graph->org"};

    if (!fs::exists(file)) { return; }
    auto n = testParseString(readFile(file));

    auto               store = imm::ImmAstContext::init_start_context();
    imm::ImmAstVersion v     = store->addRoot(n);
    // return;

    // writeTreeRepr(
    //     v.getRootAdapter(),
    //     "imm.txt",
    //     org::ImmAdapter::TreeReprConf{
    //         .withReflFields = true,
    //         .withAuxFields  = true,
    //     });

    {
        int count = 0;
        __perf_trace("imm", "iterate each sem node");
        org::eachSubnodeRec(n, [&](sem::OrgArg) { ++count; });
    }

    {
        int count = 0;
        __perf_trace("imm", "iterate each node with path");
        org::eachSubnodeRec(
            v.getRootAdapter(), true, [&](imm::ImmAdapter const&) { ++count; });
    }

    {
        int count = 0;
        __perf_trace("imm", "iterate each node without path");
        org::eachSubnodeRec(
            v.getRootAdapter(), false, [&](imm::ImmAdapter const&) { ++count; });
    }

    imm::ImmAdapter root = v.getRootAdapter();

    auto                      conf = org::graph::MapConfig::shared();
    org::graph::MapGraphState state{v.context};
    state.addNodeRec(v.context, root, conf);

    // org::graph::MapGraph::GvConfig gvConf;
    // // gvConf.acceptNode = [&](org::graph::MapNode const& node) {
    // //     return 0 < state.graph->inDegree(node)
    // //         || 0 < state.graph->outDegree(node);
    // // };
    // auto gv = state.graph->toGraphviz(v.context, gvConf);
    // gv->render(getDebugFile("map.dot"));
    // gv->render(
    //     getDebugFile("map.png"),
    //     gv::LayoutType::Sfdp);
    writeRepresentation();
    runExternalizedLayoutPipeline();
}
