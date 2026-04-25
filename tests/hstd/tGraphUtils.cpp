#include <gtest/gtest.h>
#include <adaptagrams/adaptagrams_ir.hpp>

#include <hstd/ext/graph/graph_base.hpp>
#include <hstd/ext/graph/graph_graphviz.hpp>
#include <hstd/ext/graph/graph_cola.hpp>
#include <hstd/ext/graph/adaptagrams_common.hpp>

#include <libdialect/hola.h>
#include <libdialect/opts.h>

#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/VariantSerde.hpp>
#include <hstd/ext/geometry/hstd_geometry_test.hpp>
#include "../common.hpp"
#include <libcola/output_svg.h>
#include <utility>

template <typename A, typename T>
hstd::SPtr<A> as(hstd::SPtr<T> const& value) {
    auto result = std::dynamic_pointer_cast<A>(value);
    hstd::logic_assertion_check_not_nil(result);
    return result;
}

using namespace hstd::ext::graph;
using namespace hstd::ext;
using namespace hstd;

struct TestVertex : public IVertex {
    VertexID selfId;
    TestVertex(VertexID selfId) : selfId{selfId} {}

    std::size_t getHash() const override {
        hstd::logic_assertion_check_not_nil(this);
        return std::hash<VertexID>{}(selfId);
    }

    bool isEqual(IGraphObjectBase const* other) const override {
        return this->selfId
            == dynamic_cast<TestVertex const*>(other)->selfId;
    }

    std::string getRepr() const override {
        return hstd::fmt("IVertex({})", selfId);
    }

    json getSerialNonRecursive(IGraph const* graph, VertexID const& id)
        const override {
        return json{};
    }

    hstd::Vec<hstd::SPtr<IAttribute>> attrs;

    hstd::Vec<hstd::SPtr<IAttribute>> getAttributes() const override {
        return attrs;
    }

    void addAttribute(hstd::SPtr<IAttribute> const& attr) override {
        attrs.push_back(attr);
    }

    std::string getStableId() const override {
        return hstd::fmt("test-vertex-{}", selfId);
    }
};


struct TestEdge : public IEdge {
    using IEdge::IEdge;

    hstd::Vec<hstd::SPtr<IAttribute>> attrs;

    hstd::Vec<hstd::SPtr<IAttribute>> getAttributes() const override {
        return attrs;
    }

    void addAttribute(hstd::SPtr<IAttribute> const& attr) override {
        attrs.push_back(attr);
    }
};

struct TestEdgeCollection : public IEdgeCollection {
  public:
    hstd::UnorderedIncrementalStore<EdgeID, TestEdge> edgeStore;

    EdgeCollectionID getCategory() const override {
        return getCollectionIdImpl(this);
    }

    const IEdge* getEdge(EdgeID const& id) const override {
        return &edgeStore.at(id);
    }

    hstd::Vec<EdgeID> addAllOutgoing(VertexID const& id) override {
        return {};
    }
};

struct TestGraph : public IGraph {
    hstd::UnorderedIncrementalStore<VertexID, TestVertex> vertexStore;
    hstd::SPtr<TestEdgeCollection>                        edges;

    TestGraph() : edges{std::make_shared<TestEdgeCollection>()} {
        addCollection(edges);
    }

    VertexID addVertex() {
        auto result = vertexStore.add(TestVertex{vertexStore.getNextId()});
        trackVertex(result);
        return result;
    }

    const IVertex* getVertex(VertexID const& id) const override {
        return &vertexStore.at(id);
    }

    EdgeID addEdge(VertexID const& source, VertexID const& target) {
        auto result = edges->edgeStore.add(
            TestEdge{source, target}, edges->getCategory());
        edges->trackEdge(result);
        return result;
    }
};


class GraphUtils_Test : public ::testing::Test {
  protected:
    void SetUp() override {
        graph = std::make_shared<TestGraph>();
        run   = std::make_shared<layout::LayoutRun>(graph);
        run->setTraceFile(getDebugFile("layout_trace.log"));
    }

    hstd::SPtr<TestGraph>         graph;
    hstd::SPtr<layout::LayoutRun> run;

    hstd::SPtr<gv::GraphGroup> getGv(layout::GroupID const& id) {
        auto result = std::dynamic_pointer_cast<gv::GraphGroup>(
            run->at(id));
        LOGIC_ASSERTION_CHECK(result != nullptr, "");
        return result;
    }

    hstd::SPtr<gv::NodeAttribute> getGv(VertexID const& id) {
        return graph->getVertex(id)
            ->getUniqueAttribute<gv::NodeAttribute>();
    }

    hstd::SPtr<gv::EdgeAttribute> getGv(EdgeID const& id) {
        return graph->getEdge(id)->getUniqueAttribute<gv::EdgeAttribute>();
    }

    hstd::SPtr<cst::ColaGroup> getCola(layout::GroupID const& id) {
        auto result = std::dynamic_pointer_cast<cst::ColaGroup>(
            run->at(id));
        LOGIC_ASSERTION_CHECK(result != nullptr, "");
        return result;
    }

    hstd::SPtr<cst::ColaVertexAttribute> getCola(VertexID const& id) {
        return graph->getVertex(id)
            ->getUniqueAttribute<cst::ColaVertexAttribute>();
    }

    hstd::SPtr<cst::ColaEdgeAttribute> getCola(EdgeID const& id) {
        return graph->getEdge(id)
            ->getUniqueAttribute<cst::ColaEdgeAttribute>();
    }
};


TEST_F(GraphUtils_Test, GraphvizSimpleConstruction) {
    // Create initial graph structure
    auto v1 = graph->addVertex();
    auto v2 = graph->addVertex();
    auto v3 = graph->addVertex();
    auto v4 = graph->addVertex();

    auto e12 = graph->addEdge(v1, v2);
    auto e23 = graph->addEdge(v2, v3);
    auto e31 = graph->addEdge(v3, v1);

    // creates a graphviz root graph
    auto                       root  = gv::GraphGroup::newRootGraph(run);
    hstd::SPtr<gv::GraphGroup> group = getGv(root);

    // add vertext, the graph group will internally create a visual
    // attribute and graphviz node object
    group->addVertex(v1);
    group->addVertex(v2);
    group->addVertex(v3);
    group->addVertex(v4);

    // configure visual parameters for graphviz nodes. The methods are
    // specific to the graphviz layout nodes, and use cgraph API
    // internally.
    auto shape = gv::NodeAttribute::Shape::rect;
    getGv(v1)->setFixedPointWH(120, 120)->setShape(shape);
    getGv(v2)->setFixedPointWH(120, 120)->setShape(shape);
    getGv(v3)->setFixedPointWH(240, 240)->setShape(shape);
    getGv(v4)->setFixedPointWH(240, 240)->setShape(shape);

    // Add edges to the graphviz graph. This links already existing
    // semantic vertices to the visual representation in the layout.
    group->addEdge(e12);
    group->addEdge(e23);
    group->addEdge(e31);

    // For the graphviz backend, adding vertices and edges is enough to
    // gnerate a PNG file with cgraph API. It does not populate the layout
    // attributes for the overall algorithm, but can be used for debugging.
    group->render("/tmp/result.png");

    // Running for layout will populate all maps and fields of the layout
    // run with placement information.
    ASSERT_TRUE(run != nullptr);
    run->runFullLayout();

    EXPECT_EQ(run->result.vertices.size(), 4);

    auto const& res = run->result;

    // verify the structure and geometry of the vertices. Running full
    // layout should have created an additional collection of objects
    // derived from `IVisualAttribute` that can provide bounding boxes for
    // the entries.
    ASSERT_TRUE(res.vertices.contains(v1));
    ASSERT_TRUE(res.vertices.contains(v2));
    ASSERT_TRUE(res.vertices.contains(v3));
    ASSERT_TRUE(res.vertices.contains(v4));

    EXPECT_NEAR(run->getLayout(v1)->getBBox().width(), 120, 0.005);
    EXPECT_NEAR(run->getLayout(v1)->getBBox().height(), 120, 0.005);

    EXPECT_NEAR(run->getLayout(v2)->getBBox().width(), 120, 0.005);
    EXPECT_NEAR(run->getLayout(v2)->getBBox().height(), 120, 0.005);

    EXPECT_NEAR(run->getLayout(v3)->getBBox().width(), 240, 0.005);
    EXPECT_NEAR(run->getLayout(v3)->getBBox().height(), 240, 0.005);

    EXPECT_NEAR(run->getLayout(v4)->getBBox().width(), 240, 0.005);
    EXPECT_NEAR(run->getLayout(v4)->getBBox().height(), 240, 0.005);

    EXPECT_EQ(run->result.edges.size(), 3);

    EXPECT_TRUE(res.edges.contains(e12));
    EXPECT_TRUE(res.edges.contains(e23));
    EXPECT_TRUE(res.edges.contains(e31));

    EXPECT_TRUE(!res.edges.at(e12)->getPath().commands.empty());
    EXPECT_TRUE(!res.edges.at(e23)->getPath().commands.empty());
    EXPECT_TRUE(!res.edges.at(e31)->getPath().commands.empty());

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}

TEST_F(GraphUtils_Test, GraphvizSameLayoutClusters) {
    hstd::Vec<VertexID> vs;
    hstd::Vec<EdgeID>   es;
    for (int i = 0; i < 11; ++i) { vs.push_back(graph->addVertex()); }

    auto edge = [&](int source, int target) {
        es.push_back(graph->addEdge(vs.at(source), vs.at(target)));
    };


    edge(0, 2);  // 0
    edge(2, 1);  // 1
    edge(1, 8);  // 2
    edge(8, 3);  // 3
    edge(3, 4);  // 4
    edge(4, 6);  // 5
    edge(3, 6);  // 6
    edge(8, 5);  // 7
    edge(5, 9);  // 8
    edge(9, 10); // 9
    edge(10, 7); // 10
    edge(7, 5);  // 11

    auto                       root  = gv::GraphGroup::newRootGraph(run);
    hstd::SPtr<gv::GraphGroup> group = getGv(root);
    auto                       ctx   = group->context();

    EXPECT_EQ(ctx->groups.size(), 1);
    EXPECT_EQ(group->subGroups.size(), 0);

    layout::GroupID sub_group_id1         = group->addNewNativeSubgroup();
    hstd::SPtr<gv::GraphGroup> sub_group1 = as<gv::GraphGroup>(
        run->getGroup(sub_group_id1));

    layout::GroupID sub_group_id2         = group->addNewNativeSubgroup();
    hstd::SPtr<gv::GraphGroup> sub_group2 = as<gv::GraphGroup>(
        run->getGroup(sub_group_id2));

    auto shape = gv::NodeAttribute::Shape::rect;


    EXPECT_EQ(group->subGroups.size(), 2);
    EXPECT_EQ(ctx->groups.size(), 3);
    EXPECT_EQ(ctx->nodeAttributes.size(), 0);
    EXPECT_EQ(ctx->edgeAttributes.size(), 0);

    as<gv::NodeAttribute>(sub_group1->addVertex(vs.at(3)))
        ->setFixedPointWH(120, 60)
        ->setShape(shape)
        ->setLabel("VERT-3");
    as<gv::NodeAttribute>(sub_group1->addVertex(vs.at(4)))
        ->setFixedPointWH(180, 120)
        ->setShape(shape)
        ->setLabel("VERT-4");
    as<gv::NodeAttribute>(sub_group1->addVertex(vs.at(6)))
        ->setFixedPointWH(240, 60)
        ->setShape(shape)
        ->setLabel("VERT-6");

    EXPECT_EQ(ctx->nodeAttributes.size(), 3);
    EXPECT_EQ(group->directVertices.size(), 0);
    EXPECT_EQ(group->directEdges.size(), 0);
    EXPECT_EQ(sub_group1->directEdges.size(), 0);
    EXPECT_EQ(sub_group1->directVertices.size(), 3);

    as<gv::NodeAttribute>(sub_group2->addVertex(vs.at(5)))
        ->setFixedPointWH(120, 60)
        ->setShape(shape)
        ->setLabel("VERT-5");
    as<gv::NodeAttribute>(sub_group2->addVertex(vs.at(9)))
        ->setFixedPointWH(120, 60)
        ->setShape(shape)
        ->setLabel("VERT-9");
    as<gv::NodeAttribute>(sub_group2->addVertex(vs.at(7)))
        ->setFixedPointWH(120, 60)
        ->setShape(shape)
        ->setLabel("VERT-7");
    as<gv::NodeAttribute>(sub_group2->addVertex(vs.at(10)))
        ->setFixedPointWH(120, 60)
        ->setShape(shape)
        ->setLabel("VERT-10");

    EXPECT_EQ(group->directVertices.size(), 0);
    EXPECT_EQ(group->directEdges.size(), 0);
    EXPECT_EQ(sub_group2->directEdges.size(), 0);
    EXPECT_EQ(sub_group2->directVertices.size(), 4);

    EXPECT_EQ(group->getVertices().size(), 0);
    EXPECT_EQ(sub_group1->getVertices().size(), 3);
    EXPECT_EQ(sub_group2->getVertices().size(), 4);

    EXPECT_EQ(ctx->nodeAttributes.size(), 7);

    as<gv::EdgeAttribute>(sub_group1->addEdge(es.at(4)));
    as<gv::EdgeAttribute>(sub_group1->addEdge(es.at(5)));

    as<gv::EdgeAttribute>(sub_group2->addEdge(es.at(8)));
    as<gv::EdgeAttribute>(sub_group2->addEdge(es.at(9)));
    as<gv::EdgeAttribute>(sub_group2->addEdge(es.at(10)));

    EXPECT_EQ(sub_group1->directEdges.size(), 2);
    EXPECT_EQ(sub_group2->directEdges.size(), 3);

    group->render(getDebugFile("result.png"));

    EXPECT_EQ(group->getVertices().size(), 0);
    EXPECT_EQ(sub_group1->getVertices().size(), 3);
    EXPECT_EQ(sub_group2->getVertices().size(), 4);

    run->runFullLayout();

    auto const& res = run->result;

    EXPECT_EQ(res.vertices.size(), 7);
    EXPECT_EQ(res.edges.size(), 5);
    EXPECT_EQ(res.groups.size(), 3);

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}

TEST_F(GraphUtils_Test, GraphvizDifferentLayoutClusters) {
    hstd::Vec<VertexID> vs;
    hstd::Vec<EdgeID>   es;
    for (int i = 0; i < 6; ++i) { vs.push_back(graph->addVertex()); }

    auto edge = [&](int source, int target) {
        es.push_back(graph->addEdge(vs.at(source), vs.at(target)));
    };


    edge(0, 1); // 0
    edge(1, 2); // 1
    edge(2, 0); // 2
    edge(3, 4); // 3
    edge(4, 5); // 4
    edge(5, 3); // 5

    auto                       root  = gv::GraphGroup::newRootGraph(run);
    hstd::SPtr<gv::GraphGroup> group = getGv(root);
    auto                       ctx   = group->context();

    layout::GroupID            sg1_id = group->newSubLayoutGraph();
    hstd::SPtr<gv::GraphGroup> sg1    = as<gv::GraphGroup>(
        run->getGroup(sg1_id));
    sg1->getAlgorithm<gv::Layout>()->layout = gv::LayoutType::Circo;

    layout::GroupID            sg2_id = group->newSubLayoutGraph();
    hstd::SPtr<gv::GraphGroup> sg2    = as<gv::GraphGroup>(
        run->getGroup(sg2_id));
    sg2->getAlgorithm<gv::Layout>()->layout = gv::LayoutType::Dot;

    as<gv::NodeAttribute>(sg1->addVertex(vs.at(0)))
        ->setFixedPointWH(60, 60)
        ->setLabel("VERT-0");
    as<gv::NodeAttribute>(sg1->addVertex(vs.at(1)))
        ->setFixedPointWH(60, 60)
        ->setLabel("VERT-1");
    as<gv::NodeAttribute>(sg1->addVertex(vs.at(2)))
        ->setFixedPointWH(60, 60)
        ->setLabel("VERT-2");

    as<gv::NodeAttribute>(sg2->addVertex(vs.at(3)))
        ->setFixedPointWH(60, 60)
        ->setLabel("VERT-3");
    as<gv::NodeAttribute>(sg2->addVertex(vs.at(4)))
        ->setFixedPointWH(60, 60)
        ->setLabel("VERT-4");
    as<gv::NodeAttribute>(sg2->addVertex(vs.at(5)))
        ->setFixedPointWH(60, 60)
        ->setLabel("VERT-5");


    as<gv::EdgeAttribute>(sg1->addEdge(es.at(0)));
    as<gv::EdgeAttribute>(sg1->addEdge(es.at(1)));
    as<gv::EdgeAttribute>(sg1->addEdge(es.at(2)));

    as<gv::EdgeAttribute>(sg2->addEdge(es.at(3)));
    as<gv::EdgeAttribute>(sg2->addEdge(es.at(4)));
    as<gv::EdgeAttribute>(sg2->addEdge(es.at(5)));


    run->runFullLayout();

    auto const& res = run->result;

    EXPECT_EQ(res.vertices.size(), 6);
    EXPECT_EQ(res.edges.size(), 6);
    EXPECT_EQ(res.groups.size(), 3);

    HSLOG_TRACE("{}", res.groups.keys());

    auto visual = run->getVisual();

    EXPECT_EQ(visual.size(), 1);
    EXPECT_EQ(visual.at(0).subgroups.size(), 2);

    auto const vsg  = visual.at(0);
    auto const vsg1 = visual.at(0).subgroups.at(0);
    auto const vsg2 = visual.at(0).subgroups.at(1);
    EXPECT_EQ(vsg1.subgroups.size(), 6);
    EXPECT_EQ(vsg2.subgroups.size(), 6);

    EXPECT_EQ(vsg1.elements.size(), 1);
    EXPECT_EQ(vsg2.elements.size(), 1);

    // ...............................................
    // :                  :                          :
    // :   +---------+    : +---------+..............:
    // :   |  VERT-3 |<-\ : |  VERT-1 |              :
    // :   +---------+  | : +---------+              :
    // :        |       | :      ^     \             :
    // :        v       | :      |      \            :
    // :   +---------+  | :      |       v           :
    // :   |  VERT-4 |  | :      |    +---------+    :
    // :   +---------+  | :      |    |  VERT-2 |    :
    // :        |       | :      |    +---------+    :
    // :        v       | :      |       /           :
    // :   +---------+  | :      |      /            :
    // :   |  VERT-5 |--/ : +---------+<             :
    // :   +---------+    : |  VERT-0 |              :
    // :                  : +---------+..............:
    // :                  :                          :
    // ...............................................

    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());

    hstd::writeFile(
        getDebugFile("result.json"), hstd::to_json_eval(visual).dump(2));

    hstd::writeFile(
        getDebugFile("result.txt"),
        visual::VisGroup{.subgroups = visual}.treeRepr().toString());

    // VSG1 is a left layout group
    // VSG2 is a right one
    EXPECT_OUTCOME_OK(
        checkLeftOf(/*stationary=*/vsg2.offset, /*relative=*/vsg1.offset));

    EXPECT_OUTCOME_OK(checkFullyCovers(/*main=*/vsg.computeBounds(),
                                       /*nested=*/vsg1.computeBounds()));

    EXPECT_OUTCOME_OK(checkFullyCovers(/*main=*/vsg.computeBounds(),
                                       /*nested=*/vsg2.computeBounds()));

    using VE = hstd::ext::visual::VisElement;

    EXPECT_OUTCOME_OK(checkLeftOf(/*stationary=*/run->getVisual(sg1_id),
                                  /*relative=*/run->getVisual(sg2_id)));

    EXPECT_OUTCOME_OK(checkLeftOf(/*stationary=*/run->getVisual(vs.at(2)),
                                  /*relative=*/run->getVisual(vs.at(0))));

    EXPECT_OUTCOME_OK(checkLeftOf(/*stationary=*/run->getVisual(vs.at(2)),
                                  /*relative=*/run->getVisual(vs.at(1))));

    EXPECT_OUTCOME_OK(checkAbove(/*stationary=*/run->getVisual(vs.at(0)),
                                 /*relative=*/run->getVisual(vs.at(1))));

    EXPECT_OUTCOME_OK(checkBelow(/*stationary=*/run->getVisual(vs.at(3)),
                                 /*relative=*/run->getVisual(vs.at(4))));

    EXPECT_OUTCOME_OK(checkBelow(/*stationary=*/run->getVisual(vs.at(4)),
                                 /*relative=*/run->getVisual(vs.at(5))));

    // group 0
    for (auto const& [group_idx, group] :
         hstd::enumerate(hstd::as_vec(&vsg1, &vsg2))) {
        for (int i : hstd::as_vec(0, 1, 2)) {
            EXPECT_OUTCOME_OK(
                checkFullyCovers(
                    group->computeBoundsNoSelfOffset(),
                    group->getElements<VE::RectShape>().at(i).geometry),
                hstd::fmt("\ngroup {} element {}", group_idx, i));
        }
    }

    // re-checking the same element placement, but now via the visual
    // attribute API access
    for (layout::GroupID const& gid : hstd::as_vec(sg1_id, sg2_id)) {
        auto const& group = run->getGroup(gid);
        for (VertexID vert : group->getVertices()) {
            auto const& group_visual = run->getVisual(gid);
            auto const& item_visual  = run->getVisual(vert);
            EXPECT_OUTCOME_OK(
                checkFullyCovers(
                    group_visual.computeBoundsNoSelfOffset(),
                    item_visual.computeBounds(),
                    // precision loss around 1% for checking the
                    // boundaries.
                    /*rtol=*/1e-2),
                hstd::fmt(
                    R"(
group: {}
item:  {}
irepr: {}
arepr: {}
group_visual:
{}
item_visual:
{}
)",
                    gid,
                    vert,
                    run->getVertex(vert)->getRepr(),
                    run->getLayout(vert)->getRepr(),
                    group_visual.treeRepr().toString(),
                    item_visual.treeRepr().toString()));
        }
    }
}


TEST_F(GraphUtils_Test, LibcolaApi) {
    std::vector<std::pair<unsigned, unsigned>> edges{
        {0, 1},
        {1, 2},
        {2, 3},
    };

    double                        width  = 100;
    double                        height = 100;
    std::vector<vpsc::Rectangle*> rectangles;

    for (unsigned i = 0; i < edges.size() + 1; i++) {
        double x = i * 10;
        double y = i * 10;
        rectangles.push_back(new vpsc::Rectangle(x, x + 5, y, y + 5));
    }

    cola::CompoundConstraints ccs;

    cola::AlignmentConstraint align_on_x{vpsc::XDIM};
    ccs.push_back(&align_on_x);
    align_on_x.addShape(0, 0);
    align_on_x.addShape(1, 0);

    cola::AlignmentConstraint align_on_y{vpsc::YDIM};
    ccs.push_back(&align_on_y);
    align_on_y.addShape(1, 0);
    align_on_y.addShape(3, 0);

    cola::ConstrainedFDLayout alg2(rectangles, edges, width / 2);
    alg2.setConstraints(ccs);
    alg2.run();

    OutputFile output(
        rectangles, edges, nullptr, "/tmp/testLibcolaApi1.svg");
    output.rects = true;
    output.generate();

    for (auto r : rectangles) { delete r; }
}

TEST_F(GraphUtils_Test, LibcolaRaw1) {
    // Expected shape for the visualization
    //     rect_width
    //    ├───────────┤
    // 0,0┌───────────┐
    //    │           │
    //    │           ├──────────┐
    //    │           │          │
    //    │           │          │
    //    │           ├───────┐  │
    //    │           │       │  │
    //    │           │       │  │
    //    │           ├────┐  │  │
    //    │           │    │  │  │
    //    │           │    │  │  │    650,350┌────────────┐
    //    └───────────┘    │  │  │           │            │
    //                     │  │  └───────────┤            │
    //                     │  │              │            │
    //                     │  │              │            │
    //                     │  └──────────────┤            │
    //                     │                 │            │
    //                     │                 │            │
    //                     └─────────────────┤            │
    //                                       │            │
    //                                       └────────────┘


    Avoid::Router router_it{
        Avoid::PolyLineRouting | Avoid::OrthogonalRouting};
    Avoid::Router* router = &router_it;
    router->setRoutingPenalty(Avoid::RoutingParameter::segmentPenalty, 50);
    router->setRoutingPenalty(Avoid::RoutingParameter::anglePenalty, 0);
    router->setRoutingPenalty(
        Avoid::RoutingParameter::crossingPenalty, 400);
    router->setRoutingPenalty(
        Avoid::RoutingParameter::clusterCrossingPenalty, 4000);
    router->setRoutingPenalty(
        Avoid::RoutingParameter::fixedSharedPathPenalty, 110);
    router->setRoutingParameter(Avoid::idealNudgingDistance, 25);

    double right_rect_x = 650;
    double right_rect_y = 350;
    // Use non-zero inset to move the connection edges slightly inside of
    // the shape so libavoid does not consider them free-floating (if this
    // happens the start/end segment of edge can run perfectly flush along
    // the rectangle boundary).
    //
    // Alternative solutions to enforce edges orthogonal to the rect side
    // - Boundary Inflation: Use
    //   `router->setRoutingParameter(Avoid::shapeBufferDistance, 5);`
    //   This globally inflates the routing obstacles so points on the
    //   visual edge are treated as being inside the routing boundary,
    //   enforcing the direction flags.
    // - Shape Connection Pins: Instead of using absolute free-floating
    //   coordinates, attach the connections using
    //   `Avoid::ShapeConnectionPin`. This natively
    //   forces perpendicular exits from the shape's edges without relying
    //   on coordinate math.
    double inset = 0.001;
    // with inset 0 the shape will be
    // ┌──────────────┐
    // │              │
    // │              │
    // │              │
    // │              │
    // │              ├──────────────────────────┐
    // │              ├──────────────────────────┤
    // │              │                          │
    // │              ├──────────────────────────┤
    // └──────────────┘                          │
    //                                           │
    //                                           ├──────────────┐
    //                                           │              │
    //                                           │              │
    //                                           │              │
    //                                           │              │
    //                                           │              │
    //                                           └──────────────┘

    double rect_width     = 300;
    double rect_height    = 700;
    double connector_step = 60;
    // right rectangle
    Avoid::Polygon poly4(4);
    poly4.ps[0] = Avoid::Point(right_rect_x + rect_width, right_rect_y);
    poly4.ps[1] = Avoid::Point(
        right_rect_x + rect_width, right_rect_y + rect_height);
    poly4.ps[2] = Avoid::Point(right_rect_x, right_rect_y + rect_height);
    poly4.ps[3] = Avoid::Point(right_rect_x, right_rect_y);
    new Avoid::ShapeRef(router, poly4, /*id=*/4);

    // left rectangle
    Avoid::Polygon poly5(4);
    poly5.ps[0] = Avoid::Point(rect_width, 0);
    poly5.ps[1] = Avoid::Point(rect_width, rect_height);
    poly5.ps[2] = Avoid::Point(0, rect_height);
    poly5.ps[3] = Avoid::Point(0, 0);
    new Avoid::ShapeRef(router, poly5, /*id=*/5);

    // first edge
    Avoid::ConnRef* connRef1 = new Avoid::ConnRef(router, /*id=*/1);
    Avoid::ConnEnd  srcPt1(
        Avoid::Point(rect_width - inset, connector_step * 2),
        Avoid::ConnDirRight);
    connRef1->setSourceEndpoint(srcPt1);
    Avoid::ConnEnd dstPt1(
        Avoid::Point(
            right_rect_x + inset, right_rect_y + connector_step * 2),
        Avoid::ConnDirLeft);
    connRef1->setDestEndpoint(dstPt1);
    connRef1->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

    // second edge
    Avoid::ConnRef* connRef2 = new Avoid::ConnRef(router, /*id=*/2);
    Avoid::ConnEnd  srcPt2(
        Avoid::Point(rect_width - inset, connector_step * 3),
        Avoid::ConnDirRight);
    connRef2->setSourceEndpoint(srcPt2);
    Avoid::ConnEnd dstPt2(
        Avoid::Point(
            right_rect_x + inset, right_rect_y + connector_step * 3),
        Avoid::ConnDirLeft);
    connRef2->setDestEndpoint(dstPt2);
    connRef2->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

    // third edge
    Avoid::ConnRef* connRef3 = new Avoid::ConnRef(router, /*id=*/3);
    Avoid::ConnEnd  srcPt3(
        Avoid::Point(rect_width - inset, connector_step * 4),
        Avoid::ConnDirRight);
    connRef3->setSourceEndpoint(srcPt3);
    Avoid::ConnEnd dstPt3(
        Avoid::Point(
            right_rect_x + inset, right_rect_y + connector_step * 4),
        Avoid::ConnDirLeft);
    connRef3->setDestEndpoint(dstPt3);
    connRef3->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

    router->processTransaction();

    auto path1 = adapt::to_hstd_path(connRef1->displayRoute());
    auto path2 = adapt::to_hstd_path(connRef2->displayRoute());
    auto path3 = adapt::to_hstd_path(connRef3->displayRoute());

    using namespace visual;

    VisGroup result;
    for (auto const& group : hstd::as_vec(path1, path2, path3)) {
        result.elements.push_back(
            VisElement{VisElement::PathShape{group}});
    }

    auto rect_right = adapt::to_hstd_rect(poly4);
    auto rect_left  = adapt::to_hstd_rect(poly5);

    result.elements.push_back(
        VisElement{VisElement::RectShape{rect_right}});
    result.elements.push_back(
        VisElement{VisElement::RectShape{rect_left}});

    hstd::writeFile(
        getDebugFile("result.svg"),
        toSvg({result}, /*debug=*/false).to_string());

    EXPECT_OUTCOME_OK(
        checkLeftOf(/*stationary=*/rect_right, /*relative=*/rect_left));

    EXPECT_OUTCOME_OK(checkPartiallyAbove(
        /*stationary=*/rect_right, /*relative=*/rect_left, 70));
}


TEST_F(GraphUtils_Test, LibcolaRaw2) {
    //                             ┌────────────┐
    //                             │            │
    //                         ┌───┤            │
    // ┌───────────────────┐   │   │            │
    // │ ┌────────────┐    │   │   │            │
    // │ │            │    └───┼───┤            │
    // └─┤            │        │   └────────────┘
    //   │            │        │
    // ┌─┤            │        │
    // │ │            │        │
    // │ └────────────┘        │   ┌────────────┐
    // │                       │   │            │
    // └───────────────────────┼───┤            │
    //                         │   │            │
    //                         └───┤            │
    //                             │            │
    //                             └────────────┘
    Avoid::Router  router_it{Avoid::OrthogonalRouting};
    Avoid::Router* router = &router_it;
    router->setRoutingParameter(Avoid::idealNudgingDistance, 4);
    router->setRoutingOption(
        Avoid::nudgeOrthogonalSegmentsConnectedToShapes, true);
    router->setRoutingOption(
        Avoid::improveHyperedgeRoutesMovingJunctions, true);
    router->setRoutingOption(
        Avoid::penaliseOrthogonalSharedPathsAtConnEnds, true);
    // buffer distance is mandatory for sane routing, otherwise most of the
    // edges will run perfectly flush against the rectangles.
    router->setRoutingParameter(Avoid::shapeBufferDistance, 10);

    auto pin_for_shape =
        // Y position is mandatory, if connection points overlap with each
        // other the whole edge automatically collapses to the straight
        // line between the start and end shape centers. Setting nudge
        // distance does not affect it in any way.
        [](Avoid::ShapeRef* shape, int pinClass, double yPos) {
            new Avoid::ShapeConnectionPin(
                shape,
                pinClass,
                Avoid::ATTACH_POS_LEFT,
                yPos,
                /*proportional=*/true,
                /*insideOffset=*/0,
                /*visDirs=*/Avoid::ConnDirLeft);
        };

    auto add_rect =
        [&](double x,
            double y) -> std::pair<Avoid::ShapeRef*, Avoid::Rectangle> {
        double w = 100;
        double h = 100;

        auto polygon = Avoid::Rectangle(
            Avoid::Point(x, y), Avoid::Point(x + w, y + h));

        auto ref = new Avoid::ShapeRef(router, polygon);

        return {ref, polygon};
    };

    // Edge routing works with already positioned elements
    auto [shapeRef0, polygon0] = add_rect(-100, 100);
    auto [shapeRef1, polygon1] = add_rect(-500, 150);
    auto [shapeRef2, polygon2] = add_rect(-170, 460);

    // each shape can have a number of pins. Pins connected by the same
    // edge must share the same class ID.
    // Shape 0 has two pins, connecting for edge 0 and edge 1.
    pin_for_shape(shapeRef0, 1, 0.25);
    pin_for_shape(shapeRef0, 2, 0.75);

    pin_for_shape(shapeRef1, 2, 0.25);
    pin_for_shape(shapeRef1, 3, 0.75);

    pin_for_shape(shapeRef2, 3, 0.25);
    pin_for_shape(shapeRef2, 1, 0.75);

    // Edge 0, connecting first pin of shape 0 to the pin of shape 1
    auto conn01 = new Avoid::ConnRef(
        router,
        Avoid::ConnEnd{shapeRef0, 2},
        Avoid::ConnEnd{shapeRef1, 2});
    conn01->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

    auto conn12 = new Avoid::ConnRef(
        router,
        Avoid::ConnEnd{shapeRef1, 3},
        Avoid::ConnEnd{shapeRef2, 3});
    conn12->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

    auto conn20 = new Avoid::ConnRef(
        router,
        Avoid::ConnEnd{shapeRef2, 1},
        Avoid::ConnEnd{shapeRef0, 1});
    conn20->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

    router->processTransaction();

    visual::VisGroup result;
    adapt::add_rect(result, polygon0);
    adapt::add_rect(result, polygon1);
    adapt::add_rect(result, polygon2);

    adapt::add_path(result, conn01->displayRoute());
    adapt::add_path(result, conn12->displayRoute());
    adapt::add_path(result, conn20->displayRoute());

    hstd::writeFile(
        getDebugFile("result.svg"),
        visual::toSvg({result}, /*debug=*/false).to_string());

    router->outputInstanceToSVG("/tmp/testLibcolaRaw2");
}

TEST_F(GraphUtils_Test, LibavoidRaw1) {
    auto router = std::make_shared<Avoid::Router>(
        Avoid::PolyLineRouting | Avoid::OrthogonalRouting);
    router->setRoutingParameter(
        Avoid::RoutingParameter::segmentPenalty, 50);
    router->setRoutingParameter(Avoid::RoutingParameter::anglePenalty, 0);
    router->setRoutingParameter(
        Avoid::RoutingParameter::crossingPenalty, 0);
    router->setRoutingParameter(
        Avoid::RoutingParameter::clusterCrossingPenalty, 4000);
    router->setRoutingParameter(
        Avoid::RoutingParameter::fixedSharedPathPenalty, 0);
    router->setRoutingParameter(
        Avoid::RoutingParameter::portDirectionPenalty, 100);
    router->setRoutingParameter(
        Avoid::RoutingParameter::shapeBufferDistance, 0);
    router->setRoutingParameter(
        Avoid::RoutingParameter::idealNudgingDistance, 4);
    router->setRoutingOption(
        Avoid::RoutingOption::nudgeOrthogonalSegmentsConnectedToShapes,
        true);
    router->setRoutingOption(
        Avoid::RoutingOption::improveHyperedgeRoutesMovingJunctions, true);
    router->setRoutingOption(
        Avoid::RoutingOption::penaliseOrthogonalSharedPathsAtConnEnds,
        false);
    router->setRoutingOption(
        Avoid::RoutingOption::nudgeOrthogonalTouchingColinearSegments,
        false);

    double rectMaxX       = -250;
    double rectMinX       = -300;
    double rectConnectorX = rectMaxX - 1;
    double rectSize       = 20;

    std::vector<Avoid::Checkpoint> checkpoints{
        Avoid::Checkpoint{
            Avoid::Point{-250, 785},
            Avoid::ConnDirFlag::ConnDirAll,
            Avoid::ConnDirFlag::ConnDirAll,
        },
        Avoid::Checkpoint{
            Avoid::Point{500, 500},
            Avoid::ConnDirFlag::ConnDirAll,
            Avoid::ConnDirFlag::ConnDirAll,
        },
        Avoid::Checkpoint{
            Avoid::Point{400, 400},
            Avoid::ConnDirFlag::ConnDirAll,
            Avoid::ConnDirFlag::ConnDirAll,
        },
        Avoid::Checkpoint{
            Avoid::Point{400, 240},
            Avoid::ConnDirFlag::ConnDirAll,
            Avoid::ConnDirFlag::ConnDirAll,
        },
    };


    Avoid::ConnEnd dstPt(
        Avoid::Point(160, 240), Avoid::ConnDirFlag::ConnDirRight);


    auto add_rect = [&](double x, double y, double w, double h)
        -> std::pair<Avoid::ShapeRef*, Avoid::Rectangle> {
        auto polygon = Avoid::Rectangle(
            Avoid::Point(x, y), Avoid::Point(x + w, y + h));

        auto ref = new Avoid::ShapeRef(router.get(), polygon);

        return {ref, polygon};
    };

    auto add_left_box = [&](double rectY, int connId, uint shapeRefId)
        -> std::pair<Avoid::ConnRef*, Avoid::ShapeRef*> {
        Avoid::Polygon poly(4);
        poly.ps[0] = Avoid::Point{rectMaxX, rectY};
        poly.ps[1] = Avoid::Point{rectMaxX, rectY + rectSize};
        poly.ps[2] = Avoid::Point{rectMinX, rectY + rectSize};
        poly.ps[3] = Avoid::Point{rectMinX, rectY};
        auto shape = new Avoid::ShapeRef{router.get(), poly, shapeRefId};
        Avoid::ConnRef* conn = new Avoid::ConnRef(router.get(), connId);
        Avoid::ConnEnd  srcPt(
            Avoid::Point(rectConnectorX, rectY + rectSize / 2), 8);
        conn->setSourceEndpoint(srcPt);
        conn->setDestEndpoint(dstPt);
        conn->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);
        conn->setRoutingCheckpoints(checkpoints);
        return {conn, shape};
    };

    int id                    = 0;
    auto [conn1, left_shape1] = add_left_box(380, id + 1, id + 2);
    id += 2;
    auto [conn2, left_shape2] = add_left_box(530, id + 1, id + 2);
    id += 2;
    auto [conn3, left_shape3] = add_left_box(600, id + 1, id + 2);
    id += 2;
    auto [conn4, left_shape4] = add_left_box(670, id + 1, id + 2);
    id += 2;
    auto [conn5, left_shape5] = add_left_box(900, id + 1, id + 2);

    auto [_1, dest]      = add_rect(120, 200, 60, 80);
    auto [_2, obstacle1] = add_rect(-120, 450, 60, 220);
    auto [_3, obstacle2] = add_rect(-120, 100, 60, 50);

    router->processTransaction();

    visual::VisGroup result;

    adapt::add_rect(result, dest);
    adapt::add_rect(result, obstacle1);
    adapt::add_rect(result, obstacle2);
    adapt::add_path(result, conn1->displayRoute());
    adapt::add_path(result, conn2->displayRoute());
    adapt::add_path(result, conn3->displayRoute());
    adapt::add_path(result, conn4->displayRoute());
    adapt::add_path(result, conn5->displayRoute());
    adapt::add_rect(result, left_shape1->routingPolygon());
    adapt::add_rect(result, left_shape2->routingPolygon());
    adapt::add_rect(result, left_shape3->routingPolygon());
    adapt::add_rect(result, left_shape4->routingPolygon());
    adapt::add_rect(result, left_shape5->routingPolygon());
    adapt::add_checkpoint(result, checkpoints.at(0));
    adapt::add_checkpoint(result, checkpoints.at(1));
    adapt::add_checkpoint(result, checkpoints.at(2));
    adapt::add_checkpoint(result, checkpoints.at(3));

    hstd::writeFile(
        getDebugFile("result.svg"),
        visual::toSvg({result}, /*debug=*/false).to_string());
}

TEST_F(GraphUtils_Test, LibcolaRaw3) {
    std::vector<std::pair<unsigned, unsigned>> edges{
        {0, 1},
        {1, 2},
        {2, 3},
    };

    double mult  = 10;
    double width = 100 * mult;

    std::vector<vpsc::Rectangle*> rectangles;

    for (unsigned i = 0; i < 4; i++) {
        double x = i * 10 * mult;
        double y = i * 10 * mult;
        rectangles.push_back(
            new vpsc::Rectangle(x, x + 10 * mult, y, y + 10 * mult));
    }

    cola::CompoundConstraints ccs;

    cola::AlignmentConstraint align_on_x1{vpsc::XDIM};
    ccs.push_back(&align_on_x1);
    align_on_x1.addShape(0, 0);
    align_on_x1.addShape(1, 0);

    cola::AlignmentConstraint align_on_x2{vpsc::XDIM};
    ccs.push_back(&align_on_x2);
    align_on_x2.addShape(2, 0);

    cola::AlignmentConstraint align_on_x3{vpsc::XDIM};
    ccs.push_back(&align_on_x3);
    align_on_x3.addShape(3, 0);

    cola::MultiSeparationConstraint separate{vpsc::XDIM};
    ccs.push_back(&separate);
    separate.setSeparation(50 * mult);
    separate.addAlignmentPair(&align_on_x1, &align_on_x2);
    separate.addAlignmentPair(&align_on_x2, &align_on_x3);


    cola::ConstrainedFDLayout alg2(rectangles, edges, width / 2);
    alg2.setConstraints(ccs);

    cola::UnsatisfiableConstraintInfos unsatX;
    cola::UnsatisfiableConstraintInfos unsatY;
    alg2.setUnsatisfiableConstraintInfo(&unsatX, &unsatY);

    alg2.run();

    EXPECT_TRUE(unsatX.empty());
    EXPECT_TRUE(unsatY.empty());

    Avoid::Router* router = new Avoid::Router(Avoid::OrthogonalRouting);
    router->setRoutingPenalty((Avoid::PenaltyType)0, 50);
    router->setRoutingOption(
        Avoid::nudgeOrthogonalSegmentsConnectedToShapes, true);
    router->setRoutingOption(
        Avoid::nudgeOrthogonalTouchingColinearSegments, true);

    auto r = [&](int idx) -> vpsc::Rectangle& {
        return *rectangles.at(idx);
    };

    Avoid::Rectangle shapeRect1(
        Avoid::Point(r(0).getMinX(), r(0).getMinY()),
        Avoid::Point(r(0).getMaxX(), r(0).getMaxY()));

    Avoid::ShapeRef* shapeRef1 = new Avoid::ShapeRef{
        router, shapeRect1, 1};

    Avoid::Rectangle shapeRect2(
        Avoid::Point(r(1).getMinX(), r(1).getMinY()),
        Avoid::Point(r(1).getMaxX(), r(1).getMaxY()));
    Avoid::ShapeRef* shapeRef2 = new Avoid::ShapeRef{
        router, shapeRect2, 2};

    Avoid::Rectangle shapeRect3(
        Avoid::Point(r(2).getMinX(), r(2).getMinY()),
        Avoid::Point(r(2).getMaxX(), r(2).getMaxY()));

    Avoid::ShapeRef* shapeRef3 = new Avoid::ShapeRef{
        router, shapeRect3, 3};

    Avoid::Rectangle shapeRect4(
        Avoid::Point(r(3).getMinX(), r(3).getMinY()),
        Avoid::Point(r(3).getMaxX(), r(3).getMaxY()));

    Avoid::ShapeRef* shapeRef4 = new Avoid::ShapeRef{
        router, shapeRect4, 4};

    uint ID_1_1 = 1;
    uint ID_2_1 = 2;
    uint ID_4_1 = 4;
    uint ID_3_1 = 5;
    uint ID_3_2 = 6;
    uint ID_3_3 = 7;

    uint ID_common = 8;

    double dMin = 0.0;
    double dMid = 0.5;
    double dMax = 1.0;

    // 1 -> 3 target pin
    new Avoid::ShapeConnectionPin{
        shapeRef3, ID_3_1, dMin, dMid + 0.02, true, 0, Avoid::ConnDirLeft};

    // 2 -> 3 target pin
    new Avoid::ShapeConnectionPin{
        shapeRef3, ID_3_2, dMin, dMid, true, 0, Avoid::ConnDirLeft};

    // 3 -> 4 source pin
    new Avoid::ShapeConnectionPin{
        shapeRef3, ID_3_3, dMax, dMid, true, 0, Avoid::ConnDirRight};

    // 1 -> 3 source pin
    new Avoid::ShapeConnectionPin{
        shapeRef1, ID_1_1, dMid, dMax, true, 0.0, Avoid::ConnDirDown};

    // 2 -> 3 source pin
    new Avoid::ShapeConnectionPin{
        shapeRef2, ID_2_1, dMid, dMax, true, 0.0, Avoid::ConnDirDown};

    // 3 -> 4 target pin
    new Avoid::ShapeConnectionPin{
        shapeRef4, ID_4_1, dMin, dMid, true, 0.0, Avoid::ConnDirLeft};

    auto conn1 = new Avoid::ConnRef{
        router,
        Avoid::ConnEnd{shapeRef2, ID_2_1},
        Avoid::ConnEnd{shapeRef3, ID_3_2},
    };

    auto conn2 = new Avoid::ConnRef{
        router,
        Avoid::ConnEnd{shapeRef1, ID_1_1},
        Avoid::ConnEnd{shapeRef3, ID_3_1},
    };

    auto conn3 = new Avoid::ConnRef{
        router,
        Avoid::ConnEnd{shapeRef3, ID_3_3},
        Avoid::ConnEnd{shapeRef4, ID_4_1},
    };


    router->processTransaction();

    visual::VisGroup result;

    adapt::add_path(result, conn1->displayRoute());
    adapt::add_path(result, conn2->displayRoute());
    adapt::add_path(result, conn3->displayRoute());
    adapt::add_rect(result, shapeRef1->routingPolygon());
    adapt::add_rect(result, shapeRef2->routingPolygon());
    adapt::add_rect(result, shapeRef3->routingPolygon());
    adapt::add_rect(result, shapeRef4->routingPolygon());

    hstd::writeFile(
        getDebugFile("result.svg"),
        visual::toSvg({result}, /*debug=*/false).to_string());
}

namespace {
void addPinsForShape(Avoid::ShapeRef* shape, int pinsPerSide) {
    for (int i = 0; i < pinsPerSide; ++i) {
        double t = static_cast<double>(i + 1)
                 / static_cast<double>(pinsPerSide + 1);

        new Avoid::ShapeConnectionPin(
            shape, 1, t, 0.0, true, 0.0, Avoid::ConnDirUp);
        new Avoid::ShapeConnectionPin(
            shape, 1, 1.0, t, true, 0.0, Avoid::ConnDirRight);
        new Avoid::ShapeConnectionPin(
            shape, 1, t, 1.0, true, 0.0, Avoid::ConnDirDown);
        new Avoid::ShapeConnectionPin(
            shape, 1, 0.0, t, true, 0.0, Avoid::ConnDirLeft);
    }
}

Avoid::Polygon rectToPolygon(vpsc::Rectangle const* rect) {
    Avoid::Polygon poly(4);
    poly.ps[0] = Avoid::Point(rect->getMinX(), rect->getMinY());
    poly.ps[1] = Avoid::Point(rect->getMaxX(), rect->getMinY());
    poly.ps[2] = Avoid::Point(rect->getMaxX(), rect->getMaxY());
    poly.ps[3] = Avoid::Point(rect->getMinX(), rect->getMaxY());
    return poly;
}
} // namespace

TEST_F(GraphUtils_Test, BuildsAndRendersFinalizedGraphWithPins) {
    using namespace cola;

    std::vector<vpsc::Rectangle*> rectangles;
    rectangles.push_back(new vpsc::Rectangle(0.0, 110.0, 0.0, 50.0));
    rectangles.push_back(new vpsc::Rectangle(0.0, 70.0, 0.0, 140.0));
    rectangles.push_back(new vpsc::Rectangle(0.0, 160.0, 0.0, 60.0));
    rectangles.push_back(new vpsc::Rectangle(0.0, 90.0, 0.0, 100.0));
    rectangles.push_back(new vpsc::Rectangle(0.0, 130.0, 0.0, 45.0));
    rectangles.push_back(new vpsc::Rectangle(0.0, 75.0, 0.0, 120.0));

    // Expand rectangles to force libcola to leave a gap between nodes
    double layoutMargin = 15.0;
    for (auto* rect : rectangles) {
        rect->setXBorder(layoutMargin);
        rect->setYBorder(layoutMargin);
    }


    std::vector<Edge> edges;
    edges.emplace_back(0, 1);
    edges.emplace_back(0, 2);
    edges.emplace_back(0, 3);
    edges.emplace_back(0, 4);
    edges.emplace_back(0, 5);
    edges.emplace_back(1, 5);
    edges.emplace_back(2, 5);

    ConstrainedFDLayout layout(rectangles, edges, 80.0);
    layout.setAvoidNodeOverlaps(true);
    layout.run();

    // The rectangle borders must be reset after the initial layout to
    // make SVG visualization work as expected.
    for (auto* rect : rectangles) {
        rect->setXBorder(0);
        rect->setYBorder(0);
    }

    Avoid::Router router(Avoid::OrthogonalRouting);
    router.setRoutingParameter(Avoid::segmentPenalty, 10.0);
    router.setRoutingParameter(Avoid::crossingPenalty, 50.0);
    router.setRoutingParameter(Avoid::anglePenalty, 1.0);
    // FIXME: The shape buffer distance does not work here, the SVG
    // visualization still shows edges that are perfectly flush against the
    // rectangles.
    router.setRoutingParameter(Avoid::shapeBufferDistance, 5.0);

    std::vector<Avoid::ShapeRef*> shapes;
    shapes.reserve(rectangles.size());

    for (std::size_t i = 0; i < rectangles.size(); ++i) {
        Avoid::Polygon poly  = rectToPolygon(rectangles[i]);
        auto*          shape = new Avoid::ShapeRef(
            &router, poly, static_cast<unsigned>(i));

        if (i == 0) {
            addPinsForShape(shape, 3);
        } else {
            addPinsForShape(shape, 2);
        }

        shapes.push_back(shape);
    }

    std::vector<Avoid::ConnRef*> conns;
    conns.reserve(edges.size());

    for (std::size_t i = 0; i < edges.size(); ++i) {
        Edge const& edge = edges[i];

        auto* conn = new Avoid::ConnRef(&router, static_cast<unsigned>(i));
        conn->setSourceEndpoint(Avoid::ConnEnd(shapes[edge.first], 1));
        conn->setDestEndpoint(Avoid::ConnEnd(shapes[edge.second], 1));
        conns.push_back(conn);
    }

    router.processTransaction();
    router.outputInstanceToSVG("/tmp/libcola_libavoid_layout");

    for (auto* conn : conns) { router.deleteConnector(conn); }
    for (auto* shape : shapes) { router.deleteShape(shape); }
    for (auto* rect : rectangles) { delete rect; }
}

TEST_F(GraphUtils_Test, HolaLayoutRaw1) {
    dialect::Graph g;

    Vec<SPtr<dialect::Node>> nodes;

    using IP = std::pair<int, int>;
    for (auto const& [w, h] : hstd::Vec<IP>({
             {110, 50},
             {70, 140},
             {160, 60},
             {90, 100},
             {130, 45},
             {75, 120},
         })) {
        dialect::Node_SP node = g.addNode(w, h);
        g.addNode(node);
        nodes.push_back(node);
    }

    hstd::UnorderedMap<IP, dialect::Edge_SP> edges;

    for (auto const& pair : hstd::Vec<IP>({
             {0, 1},
             {0, 2},
             {0, 3},
             {0, 4},
             {0, 5},
             {1, 5},
             {2, 5},
         })) {
        dialect::Edge_SP edge = g.addEdge(
            nodes.at(pair.first), nodes.at(pair.second));
        edges[pair] = edge;
    }

    dialect::HolaOpts opts;
    opts.routingScalar_crossingPenalty = 20;
    dialect::doHOLA(g, opts);

    hstd::writeFile(getDebugFile("hola_result.svg"), g.writeSvg());
}


TEST_F(GraphUtils_Test, LibcolaIr1) {
    VertexID v1 = graph->addVertex();
    VertexID v2 = graph->addVertex();

    EdgeID e12 = graph->addEdge(v1, v2);

    auto                       root  = cst::ColaGroup::newRootGraph(run);
    hstd::SPtr<cst::ColaGroup> group = getCola(root);

    group->addVertex(v1, Size(5, 5));
    group->addVertex(v2, Size(6, 6));
    group->addEdge(e12);

    run->runFullLayout();

    auto const& res = run->result;

    ASSERT_TRUE(res.vertices.contains(v1));
    ASSERT_TRUE(res.vertices.contains(v2));

    EXPECT_NEAR(run->getLayout(v1)->getBBox().width(), 5, 0.005);
    EXPECT_NEAR(run->getLayout(v1)->getBBox().height(), 5, 0.005);

    EXPECT_NEAR(run->getLayout(v2)->getBBox().width(), 6, 0.005);
    EXPECT_NEAR(run->getLayout(v2)->getBBox().height(), 6, 0.005);

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}

TEST_F(GraphUtils_Test, LibcolaIr2) {
    VertexID v1 = graph->addVertex();
    VertexID v2 = graph->addVertex();
    VertexID v3 = graph->addVertex();
    VertexID v4 = graph->addVertex();

    auto                       root  = cst::ColaGroup::newRootGraph(run);
    hstd::SPtr<cst::ColaGroup> group = getCola(root);

    group->addVertex(v1, Size(50, 50));
    group->addVertex(v2, Size(60, 60));
    group->addVertex(v3, Size(70, 70));
    group->addVertex(v4, Size(80, 80));

    group->addConstraint<cst::AlignConstraint>(group)
        ->useX()
        ->addAlignVertex(v1)
        ->addAlignVertex(v2);

    group->addConstraint<cst::AlignConstraint>(group)
        ->useY()
        ->addAlignVertex(v1)
        ->addAlignVertex(v4);

    run->runFullLayout();

    auto const& res = run->result;

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());

    EXPECT_OUTCOME_OK(
        checkAlignedHorizontally(run->getVisual(v1), run->getVisual(v4)));

    EXPECT_OUTCOME_OK(
        checkAlignedVertically(run->getVisual(v1), run->getVisual(v2)));
}

TEST_F(GraphUtils_Test, LibcolaIr3) {
    hstd::Vec<VertexID> vs;
    hstd::Vec<EdgeID>   es;

    for (int i = 0; i < 12; ++i) { vs.push_back(graph->addVertex()); }

    auto add_edge = [&](int source, int target) {
        es.push_back(graph->addEdge(vs.at(source), vs.at(target)));
    };

    add_edge(0, 3);
    add_edge(1, 4);
    add_edge(1, 5);
    add_edge(1, 6);
    add_edge(2, 7);
    add_edge(3, 8);
    add_edge(4, 8);
    add_edge(4, 9);
    add_edge(5, 9);
    add_edge(6, 9);
    add_edge(6, 10);
    add_edge(7, 9);
    add_edge(7, 11);

    auto                       root  = cst::ColaGroup::newRootGraph(run);
    hstd::SPtr<cst::ColaGroup> group = getCola(root);
    group->getAlgorithm<cst::ColaLayoutAlgorithm>()
        ->router->shapeBufferDistance = 25;

    for (VertexID v : vs) { group->addVertex(v, Size(75, 25)); }
    for (EdgeID e : es) { group->addEdge(e); }

    group->addConstraint<cst::AlignConstraint>(group)
        ->useX()
        ->addAlignVertex(vs.at(0))
        ->addAlignVertex(vs.at(1))
        ->addAlignVertex(vs.at(2));

    group->addConstraint<cst::AlignConstraint>(group)
        ->useX()
        ->addAlignVertex(vs.at(3))
        ->addAlignVertex(vs.at(4))
        ->addAlignVertex(vs.at(5))
        ->addAlignVertex(vs.at(6))
        ->addAlignVertex(vs.at(7));

    group->addConstraint<cst::AlignConstraint>(group)
        ->useX()
        ->addAlignVertex(vs.at(8))
        ->addAlignVertex(vs.at(9))
        ->addAlignVertex(vs.at(10))
        ->addAlignVertex(vs.at(11));

    run->runFullLayout();

    auto const& res = run->result;
    EXPECT_EQ(res.vertices.size(), 12);
    EXPECT_EQ(res.edges.size(), 13);

    for (EdgeID e : es) {
        ASSERT_TRUE(res.edges.contains(e));
        EXPECT_TRUE(!res.edges.at(e)->getPath().commands.empty());
    }

    hstd::writeFile(
        getDebugFile("libcola_ir3.svg"),
        hstd::ext::visual::toSvg(run->getVisual(), /*debug=*/false)
            .to_string());
}

TEST_F(GraphUtils_Test, LibcolaIrMultiSeparate) {
    hstd::Vec<VertexID> vs;
    hstd::Vec<EdgeID>   es;

    for (int i = 0; i < 12; ++i) { vs.push_back(graph->addVertex()); }

    auto                       root  = cst::ColaGroup::newRootGraph(run);
    hstd::SPtr<cst::ColaGroup> group = getCola(root);
    group->getAlgorithm<cst::ColaLayoutAlgorithm>()
        ->router->shapeBufferDistance = 25;

    for (VertexID v : vs) { group->addVertex(v, Size(75, 25)); }

    group->addConstraint<cst::MultiSeparateConstraint>(group)
        ->separateHorizontally()
        ->addFullLane({vs.at(0), vs.at(1), vs.at(2)})
        ->addFullLane({vs.at(3), vs.at(4), vs.at(5), vs.at(6), vs.at(7)})
        ->addFullLane({vs.at(8), vs.at(9), vs.at(10), vs.at(11)})
        ->setSeparationDistance(120);

    run->runFullLayout();

    auto const& res = run->result;
    EXPECT_EQ(res.vertices.size(), 12);

    hstd::writeFile(
        getDebugFile("libcola_ir_multi_separate.svg"),
        hstd::ext::visual::toSvg(run->getVisual(), /*debug=*/false)
            .to_string());
}

TEST_F(GraphUtils_Test, LibcolaIrMultiEdge) {
    VertexID v0 = graph->addVertex();
    VertexID v1 = graph->addVertex();

    hstd::Vec<EdgeID> es;
    es.push_back(graph->addEdge(v0, v1));
    es.push_back(graph->addEdge(v0, v1));
    es.push_back(graph->addEdge(v0, v1));
    es.push_back(graph->addEdge(v0, v1));

    auto                       root  = cst::ColaGroup::newRootGraph(run);
    hstd::SPtr<cst::ColaGroup> group = getCola(root);

    group->addVertex(v0, Size(25, 100));
    group->addVertex(v1, Size(25, 100));

    group->addConstraint<cst::AlignConstraint>(group)
        ->useY()
        ->addAlignVertex(v0)
        ->addAlignVertex(v1);

    for (EdgeID e : es) { group->addEdge(e); }

    run->runFullLayout();

    auto const& res = run->result;
    EXPECT_EQ(res.vertices.size(), 2);
    EXPECT_EQ(res.edges.size(), 4);

    for (EdgeID e : es) {
        ASSERT_TRUE(res.edges.contains(e));
        EXPECT_TRUE(!res.edges.at(e)->getPath().commands.empty());
    }

    hstd::writeFile(
        getDebugFile("libcola_ir_multi_edge.svg"),
        hstd::ext::visual::toSvg(run->getVisual(), /*debug=*/false)
            .to_string());
}

TEST_F(GraphUtils_Test, tHolaIr1) {
    dialect::Graph g;

    hstd::Vec<dialect::Node_SP> nodes;
    for (int i = 0; i < 6; ++i) {
        auto node = g.addNode(60, 60);
        g.addNode(node);
        nodes.push_back(node);
    }

    auto add_edge = [&](int source, int target) {
        g.addEdge(nodes.at(source), nodes.at(target));
    };

    add_edge(0, 1);
    add_edge(1, 2);
    add_edge(2, 0);
    add_edge(3, 0);
    add_edge(4, 0);
    add_edge(2, 3);
    add_edge(3, 4);
    add_edge(4, 5);

    dialect::HolaOpts opts;
    opts.routingScalar_crossingPenalty = 20;
    dialect::doHOLA(g, opts);

    auto svg = g.writeSvg();
    EXPECT_TRUE(!svg.empty());

    hstd::writeFile(getDebugFile("hola_ir1.svg"), svg);
}

TEST_F(GraphUtils_Test, GraphvizIrClusters) {
    hstd::Vec<VertexID> vs;
    for (int i = 0; i < 6; ++i) { vs.push_back(graph->addVertex()); }

    auto e01 = graph->addEdge(vs.at(0), vs.at(1));
    auto e12 = graph->addEdge(vs.at(1), vs.at(2));
    auto e20 = graph->addEdge(vs.at(2), vs.at(0));

    auto e34 = graph->addEdge(vs.at(3), vs.at(4));
    auto e45 = graph->addEdge(vs.at(4), vs.at(5));
    auto e53 = graph->addEdge(vs.at(5), vs.at(3));

    auto                       root  = gv::GraphGroup::newRootGraph(run);
    hstd::SPtr<gv::GraphGroup> group = getGv(root);

    auto sg1_id = group->addNewNativeSubgroup();
    auto sg2_id = group->addNewNativeSubgroup();

    auto sg1 = as<gv::GraphGroup>(run->getGroup(sg1_id));
    auto sg2 = as<gv::GraphGroup>(run->getGroup(sg2_id));

    auto shape = gv::NodeAttribute::Shape::rect;

    as<gv::NodeAttribute>(sg1->addVertex(vs.at(0)))
        ->setFixedPointWH(60, 40)
        ->setShape(shape)
        ->setLabel("A0");
    as<gv::NodeAttribute>(sg1->addVertex(vs.at(1)))
        ->setFixedPointWH(60, 40)
        ->setShape(shape)
        ->setLabel("A1");
    as<gv::NodeAttribute>(sg1->addVertex(vs.at(2)))
        ->setFixedPointWH(60, 40)
        ->setShape(shape)
        ->setLabel("A2");

    as<gv::NodeAttribute>(sg2->addVertex(vs.at(3)))
        ->setFixedPointWH(60, 40)
        ->setShape(shape)
        ->setLabel("B0");
    as<gv::NodeAttribute>(sg2->addVertex(vs.at(4)))
        ->setFixedPointWH(60, 40)
        ->setShape(shape)
        ->setLabel("B1");
    as<gv::NodeAttribute>(sg2->addVertex(vs.at(5)))
        ->setFixedPointWH(60, 40)
        ->setShape(shape)
        ->setLabel("B2");

    as<gv::EdgeAttribute>(sg1->addEdge(e01));
    as<gv::EdgeAttribute>(sg1->addEdge(e12));
    as<gv::EdgeAttribute>(sg1->addEdge(e20));

    as<gv::EdgeAttribute>(sg2->addEdge(e34));
    as<gv::EdgeAttribute>(sg2->addEdge(e45));
    as<gv::EdgeAttribute>(sg2->addEdge(e53));

    run->runFullLayout();

    auto const& res = run->result;
    EXPECT_EQ(res.groups.size(), 3);
    EXPECT_EQ(res.vertices.size(), 6);
    EXPECT_EQ(res.edges.size(), 6);

    auto visual = run->getVisual();
    EXPECT_EQ(visual.size(), 1);
    EXPECT_EQ(visual.at(0).subgroups.size(), 2);

    hstd::writeFile(
        getDebugFile("graphviz_ir_clusters.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}
