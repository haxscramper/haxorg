#include <gtest/gtest.h>
#include <adaptagrams/adaptagrams_ir.hpp>
#include <hstd/ext/hstd_graph.hpp>
#include <hstd/ext/graphviz.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/VariantSerde.hpp>
#include <hstd/ext/hstd_geometry_test.hpp>
#include "../common.hpp"

template <typename A, typename T>
hstd::SPtr<A> as(hstd::SPtr<T> const& value) {
    auto result = std::dynamic_pointer_cast<A>(value);
    hstd::logic_assertion_check_not_nil(result);
    return result;
}

using namespace hstd::ext::graph;
using namespace hstd::ext;

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
    auto root = gv::GraphGroup::newRootGraph(run);

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
    getGv(v1)->setFixedWH(2, 2)->setShape(shape);
    getGv(v2)->setFixedWH(2, 2)->setShape(shape);
    getGv(v3)->setFixedWH(4, 4)->setShape(shape);
    getGv(v4)->setFixedWH(4, 4)->setShape(shape);

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

    EXPECT_EQ(run->getLayout(v1)->getBBox().width(), 2);
    EXPECT_EQ(run->getLayout(v1)->getBBox().height(), 2);

    EXPECT_EQ(run->getLayout(v2)->getBBox().width(), 2);
    EXPECT_EQ(run->getLayout(v2)->getBBox().height(), 2);

    EXPECT_EQ(run->getLayout(v3)->getBBox().width(), 4);
    EXPECT_EQ(run->getLayout(v3)->getBBox().height(), 4);

    EXPECT_EQ(run->getLayout(v4)->getBBox().width(), 4);
    EXPECT_EQ(run->getLayout(v4)->getBBox().height(), 4);

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
        hstd::ext::visual::toSvg(visual, false).to_string());
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
        ->setFixedWH(2, 1)
        ->setShape(shape)
        ->setLabel("VERT-3");
    as<gv::NodeAttribute>(sub_group1->addVertex(vs.at(4)))
        ->setFixedWH(3, 2)
        ->setShape(shape)
        ->setLabel("VERT-4");
    as<gv::NodeAttribute>(sub_group1->addVertex(vs.at(6)))
        ->setFixedWH(4, 1)
        ->setShape(shape)
        ->setLabel("VERT-6");

    EXPECT_EQ(ctx->nodeAttributes.size(), 3);
    EXPECT_EQ(group->directVertices.size(), 0);
    EXPECT_EQ(group->directEdges.size(), 0);
    EXPECT_EQ(sub_group1->directEdges.size(), 0);
    EXPECT_EQ(sub_group1->directVertices.size(), 3);

    as<gv::NodeAttribute>(sub_group2->addVertex(vs.at(5)))
        ->setFixedWH(2, 1)
        ->setShape(shape)
        ->setLabel("VERT-5");
    as<gv::NodeAttribute>(sub_group2->addVertex(vs.at(9)))
        ->setFixedWH(2, 1)
        ->setShape(shape)
        ->setLabel("VERT-9");
    as<gv::NodeAttribute>(sub_group2->addVertex(vs.at(7)))
        ->setFixedWH(2, 1)
        ->setShape(shape)
        ->setLabel("VERT-7");
    as<gv::NodeAttribute>(sub_group2->addVertex(vs.at(10)))
        ->setFixedWH(2, 1)
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
        hstd::ext::visual::toSvg(visual, false).to_string());
}

TEST_F(GraphUtils_Test, GraphvizDifferentLayoutClusters) {
    auto __log_scoped = HSLOG_SINK_FACTORY_SCOPED([]() {
        return ::hstd::log::init_file_sink(
            getDebugFile("hslog_trace.log"));
    });

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
        ->setFixedWH(1, 1)
        ->setLabel("VERT-0");
    as<gv::NodeAttribute>(sg1->addVertex(vs.at(1)))
        ->setFixedWH(1, 1)
        ->setLabel("VERT-1");
    as<gv::NodeAttribute>(sg1->addVertex(vs.at(2)))
        ->setFixedWH(1, 1)
        ->setLabel("VERT-2");

    as<gv::NodeAttribute>(sg2->addVertex(vs.at(3)))
        ->setFixedWH(1, 1)
        ->setLabel("VERT-3");
    as<gv::NodeAttribute>(sg2->addVertex(vs.at(4)))
        ->setFixedWH(1, 1)
        ->setLabel("VERT-4");
    as<gv::NodeAttribute>(sg2->addVertex(vs.at(5)))
        ->setFixedWH(1, 1)
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
        hstd::ext::visual::toSvg(visual, true).to_string());

    hstd::writeFile(
        getDebugFile("result.json"), hstd::to_json_eval(visual).dump(2));

    hstd::writeFile(
        getDebugFile("result.txt"),
        visual::VisGroup{.subgroups = visual}.treeRepr().toString());

    // VSG1 is a left layout group
    // VSG2 is a right one
    EXPECT_OUTCOME_OK(checkLeftOf(vsg1.offset, vsg2.offset));

    EXPECT_OUTCOME_OK(
        checkFullyCovers(vsg.computeBounds(), vsg1.computeBounds()));

    EXPECT_OUTCOME_OK(
        checkFullyCovers(vsg.computeBounds(), vsg2.computeBounds()));

    using VE = hstd::ext::visual::VisElement;

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
            {
                auto __log_scoped = HSLOG_SINK_FACTORY_SCOPED([&]() {
                    return ::hstd::log::init_file_sink(getDebugFile(
                        hstd::fmt("trace-{}-{}.log", gid, vert)));
                });
                group_visual.computeBoundsNoSelfOffset();
                HSLOG_TRACE("Item visual group");
                computeBounds(item_visual);
            }
            EXPECT_OUTCOME_OK(
                checkFullyCovers(
                    group_visual.computeBoundsNoSelfOffset(),
                    computeBounds(item_visual)),
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
                    visual::VisGroup{.subgroups = item_visual}
                        .treeRepr()
                        .toString()));
        }
    }
}


#if ORG_BUILD_WITH_ADAPTAGRAMS
#    include <libcola/output_svg.h>


using namespace hstd::ext;
using namespace hstd;

TEST(GraphUtils, LibcolaApi) {
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

TEST(GraphUtils, LibcolaRaw1) {
    using namespace Avoid;
    Router  router_it{PolyLineRouting | OrthogonalRouting};
    Router* router = &router_it;
    router->setRoutingPenalty((PenaltyType)0, 50);
    router->setRoutingPenalty((PenaltyType)1, 0);
    router->setRoutingPenalty((PenaltyType)2, 400);
    router->setRoutingPenalty((PenaltyType)3, 4000);
    router->setRoutingPenalty((PenaltyType)4, 110);
    router->setRoutingParameter(idealNudgingDistance, 25);

    Polygon poly143407352(4);
    poly143407352.ps[0] = Point(5810, 4340);
    poly143407352.ps[1] = Point(5810, 5035);
    poly143407352.ps[2] = Point(5450, 5035);
    poly143407352.ps[3] = Point(5450, 4340);
    new ShapeRef(router, poly143407352, 143407352);

    Polygon poly124950386(4);
    poly124950386.ps[0] = Point(4900, 4090);
    poly124950386.ps[1] = Point(4900, 4785);
    poly124950386.ps[2] = Point(4540, 4785);
    poly124950386.ps[3] = Point(4540, 4090);
    new ShapeRef(router, poly124950386, 124950386);

    ConnRef* connRef373967044 = new ConnRef(router, 373967044);
    ConnEnd  srcPt373967044(Point(4890, 4250), 8);
    connRef373967044->setSourceEndpoint(srcPt373967044);
    ConnEnd dstPt373967044(Point(5460, 4500), 4);
    connRef373967044->setDestEndpoint(dstPt373967044);
    connRef373967044->setRoutingType((ConnType)2);

    ConnRef* connRef681881486 = new ConnRef(router, 681881486);
    ConnEnd  srcPt681881486(Point(4890, 4325), 8);
    connRef681881486->setSourceEndpoint(srcPt681881486);
    ConnEnd dstPt681881486(Point(5460, 4575), 4);
    connRef681881486->setDestEndpoint(dstPt681881486);
    connRef681881486->setRoutingType((ConnType)2);

    ConnRef* connRef829752 = new ConnRef(router, 829752);
    ConnEnd  srcPt829752(Point(4890, 4400), 8);
    connRef829752->setSourceEndpoint(srcPt829752);
    ConnEnd dstPt829752(Point(5460, 4650), 4);
    connRef829752->setDestEndpoint(dstPt829752);
    connRef829752->setRoutingType((ConnType)2);

    router->processTransaction();
    router->outputDiagramText("/tmp/orthordering-01");
    router->outputInstanceToSVG("/tmp/orthordering-01");
}


TEST(GraphUtils, LibcolaRaw2) {
    using namespace Avoid;
    Router  router_it{Avoid::OrthogonalRouting};
    Router* router = &router_it;

    ShapeRef* shapeRef0;
    ShapeRef* shapeRef1;
    ShapeRef* shapeRef2;

    auto pin_for_shape = [](ShapeRef* shape, int pinClass) {
        new ShapeConnectionPin(
            shape,
            pinClass,
            Avoid::ATTACH_POS_CENTRE,
            Avoid::ATTACH_POS_CENTRE,
            true,
            0,
            Avoid::ConnDirNone);
    };

    { // Edge routing works with already positioned elements
        {
            auto polygon  = Polygon(4);
            polygon.ps[0] = Point(-10.3237, -3.46733);
            polygon.ps[1] = Point(-5.32374, -3.46733);
            polygon.ps[2] = Point(-5.32374, -8.46733);
            polygon.ps[3] = Point(-10.3237, -8.46733);

            shapeRef1 = new ShapeRef(router, polygon, 1);
        }

        {
            auto polygon  = Polygon(4);
            polygon.ps[0] = Point(-56.6515, 15.3407);
            polygon.ps[1] = Point(-51.6515, 15.3407);
            polygon.ps[2] = Point(-51.6515, 10.3407);
            polygon.ps[3] = Point(-56.6515, 10.3407);

            shapeRef0 = new ShapeRef(router, polygon, 1);
        }

        {
            auto polygon  = Polygon(4);
            polygon.ps[0] = Point(-17.1994, 46.0577);
            polygon.ps[1] = Point(-12.1994, 46.0577);
            polygon.ps[2] = Point(-12.1994, 41.0577);
            polygon.ps[3] = Point(-17.1994, 41.0577);

            shapeRef2 = new ShapeRef(router, polygon, 2);
        }
    }

    // each shape can have a number of pins. Pins connected by the same
    // edge must share the same class ID.
    {
        // Shape 0 has two pins, connecting for edge 0 and edge 1.
        pin_for_shape(shapeRef0, 1);
        pin_for_shape(shapeRef0, 2);

        pin_for_shape(shapeRef1, 2);
        pin_for_shape(shapeRef1, 3);

        pin_for_shape(shapeRef2, 3);
        pin_for_shape(shapeRef2, 1);
    }

    {
        { // Edge 0, connecting first pin of shape 0 to the pin of shape 1
            ConnEnd source{shapeRef0, 2};
            ConnEnd target{shapeRef1, 2};
            auto    conn = new ConnRef(router, source, target);
            conn->setRoutingType(ConnType::ConnType_Orthogonal);
        }
        {
            ConnEnd source{shapeRef1, 3};
            ConnEnd target{shapeRef2, 3};
            auto    conn = new ConnRef(router, source, target);
            conn->setRoutingType(ConnType::ConnType_Orthogonal);
        }

        {
            ConnEnd source{shapeRef2, 1};
            ConnEnd target{shapeRef0, 1};
            auto    conn = new ConnRef(router, source, target);
            conn->setRoutingType(ConnType::ConnType_Orthogonal);
        }
    }

    router->processTransaction();
    router->outputInstanceToSVG("/tmp/testLibcolaRaw2");
}

TEST(GraphUtils, LibavoidRaw1) {
    using namespace Avoid;
    Router* router = new Router(PolyLineRouting | OrthogonalRouting);
    router->setRoutingParameter((RoutingParameter)0, 50);
    router->setRoutingParameter((RoutingParameter)1, 0);
    router->setRoutingParameter((RoutingParameter)2, 0);
    router->setRoutingParameter((RoutingParameter)3, 4000);
    router->setRoutingParameter((RoutingParameter)4, 0);
    router->setRoutingParameter((RoutingParameter)5, 100);
    router->setRoutingParameter((RoutingParameter)6, 0);
    router->setRoutingParameter((RoutingParameter)7, 4);
    router->setRoutingOption((RoutingOption)0, true);
    router->setRoutingOption((RoutingOption)1, true);
    router->setRoutingOption((RoutingOption)2, false);
    router->setRoutingOption((RoutingOption)3, false);

    double rectMaxX       = -264;
    double rectMinX       = -296;
    double rectConnectorX = rectMaxX - 1;
    double rectSize       = 20;

    std::vector<Checkpoint> checkpoints{
        Checkpoint{
            Point{-242, 782},
            ConnDirFlag::ConnDirAll,
            ConnDirFlag::ConnDirAll,
        },
        Checkpoint{
            Point{500, 500},
            ConnDirFlag::ConnDirAll,
            ConnDirFlag::ConnDirAll,
        },
        Checkpoint{
            Point{400, 400},
            ConnDirFlag::ConnDirAll,
            ConnDirFlag::ConnDirAll,
        },
        Checkpoint{
            Point{400, 240},
            ConnDirFlag::ConnDirAll,
            ConnDirFlag::ConnDirAll,
        },
    };


    ConnEnd dstPt(Point(160, 240), ConnDirFlag::ConnDirRight);

    auto add_left_box = [&](double rectY, int connId, uint shapeRefId) {
        Polygon poly(4);
        poly.ps[0] = Point{rectMaxX, rectY};
        poly.ps[1] = Point{rectMaxX, rectY + rectSize};
        poly.ps[2] = Point{rectMinX, rectY + rectSize};
        poly.ps[3] = Point{rectMinX, rectY};
        new ShapeRef{router, poly, shapeRefId};
        ConnRef* conn = new ConnRef(router, connId);
        ConnEnd  srcPt(Point(rectConnectorX, rectY + rectSize / 2), 8);
        conn->setSourceEndpoint(srcPt);
        conn->setDestEndpoint(dstPt);
        conn->setRoutingType(ConnType::ConnType_Orthogonal);
        conn->setRoutingCheckpoints(checkpoints);
    };

    int id = 0;
    add_left_box(376, id + 1, id + 2);
    id += 2;
    add_left_box(526, id + 1, id + 2);
    id += 2;
    add_left_box(601, id + 1, id + 2);
    id += 2;
    add_left_box(676, id + 1, id + 2);
    id += 2;
    add_left_box(900, id + 1, id + 2);

    {
        Polygon dest(4);
        dest.ps[0] = Point(180, 200);
        dest.ps[1] = Point(180, 280);
        dest.ps[2] = Point(120, 280);
        dest.ps[3] = Point(120, 200);
        new ShapeRef(router, dest, 42);
    }

    {
        Polygon obstacle(4);
        obstacle.ps[0] = Point(-120, 690);
        obstacle.ps[1] = Point(-120, 830);
        obstacle.ps[2] = Point(-180, 830);
        obstacle.ps[3] = Point(-180, 690);
        new ShapeRef(router, obstacle, 59);
    }

    {
        Polygon obstacle(4);
        obstacle.ps[0] = Point(-120, 100);
        obstacle.ps[1] = Point(-120, 250);
        obstacle.ps[2] = Point(-180, 250);
        obstacle.ps[3] = Point(-180, 100);
        new ShapeRef(router, obstacle, 60);
    }


    router->processTransaction();
    router->outputInstanceToSVG("/tmp/nudgingSkipsCheckpoint02");

    delete router;
}

TEST(GraphUtils, LibcolaRaw3) {
    using namespace Avoid;
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
    alg2.run();

    Router* router = new Router(OrthogonalRouting);
    router->setRoutingPenalty((PenaltyType)0, 50);
    router->setRoutingOption(
        nudgeOrthogonalSegmentsConnectedToShapes, true);
    router->setRoutingOption(
        nudgeOrthogonalTouchingColinearSegments, true);

    auto r = [&](int idx) -> vpsc::Rectangle& {
        return *rectangles.at(idx);
    };

    Rectangle shapeRect1(
        Point(r(0).getMinX(), r(0).getMinY()),
        Point(r(0).getMaxX(), r(0).getMaxY()));

    ShapeRef* shapeRef1 = new ShapeRef{router, shapeRect1, 1};

    Rectangle shapeRect2(
        Point(r(1).getMinX(), r(1).getMinY()),
        Point(r(1).getMaxX(), r(1).getMaxY()));
    ShapeRef* shapeRef2 = new ShapeRef{router, shapeRect2, 2};

    Rectangle shapeRect3(
        Point(r(2).getMinX(), r(2).getMinY()),
        Point(r(2).getMaxX(), r(2).getMaxY()));

    ShapeRef* shapeRef3 = new ShapeRef{router, shapeRect3, 3};

    Rectangle shapeRect4(
        Point(r(3).getMinX(), r(3).getMinY()),
        Point(r(3).getMaxX(), r(3).getMaxY()));

    ShapeRef* shapeRef4 = new ShapeRef{router, shapeRect4, 4};

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
    new ShapeConnectionPin{
        shapeRef3, ID_3_1, dMin, dMid + 0.02, true, 0, ConnDirLeft};

    // 2 -> 3 target pin
    new ShapeConnectionPin{
        shapeRef3, ID_3_2, dMin, dMid, true, 0, ConnDirLeft};

    // 3 -> 4 source pin
    new ShapeConnectionPin{
        shapeRef3, ID_3_3, dMax, dMid, true, 0, ConnDirRight};

    // 1 -> 3 source pin
    new ShapeConnectionPin{
        shapeRef1, ID_1_1, dMid, dMax, true, 0.0, ConnDirDown};

    // 2 -> 3 source pin
    new ShapeConnectionPin{
        shapeRef2, ID_2_1, dMid, dMax, true, 0.0, ConnDirDown};

    // 3 -> 4 target pin
    new ShapeConnectionPin{
        shapeRef4, ID_4_1, dMin, dMid, true, 0.0, ConnDirLeft};

    new ConnRef{
        router,
        ConnEnd{shapeRef2, ID_2_1},
        ConnEnd{shapeRef3, ID_3_2},
    };

    new ConnRef{
        router,
        ConnEnd{shapeRef1, ID_1_1},
        ConnEnd{shapeRef3, ID_3_1},
    };

    new ConnRef{
        router,
        ConnEnd{shapeRef3, ID_3_3},
        ConnEnd{shapeRef4, ID_4_1},
    };


    router->processTransaction();
    router->outputInstanceToSVG("/tmp/LibcolaRaw3");
}


GraphLayoutIR init_graph(
    CVec<GraphEdge> edges,
    GraphSize       size = GraphSize(5, 5)) {
    int           max_node = 0;
    GraphLayoutIR ir;
    ir.edges = edges;
    for (auto const& e : edges) {
        max_node = std::max(max_node, std::max(e.source, e.target));
    }

    for (int i = 0; i <= max_node; ++i) { ir.rectangles.push_back(size); }

    return ir;
}

using C = GraphNodeConstraint;

TEST(GraphUtils, LibcolaIr1) {
    GraphLayoutIR ir;
    ir.edges.push_back({0, 1});
    ir.edges.push_back({1, 2});
    ir.edges.push_back({2, 3});

    ir.rectangles.push_back(GraphSize(5, 5));
    ir.rectangles.push_back(GraphSize(5, 5));
    ir.rectangles.push_back(GraphSize(5, 5));
    ir.rectangles.push_back(GraphSize(5, 5));


    ir.nodeConstraints.push_back(
        C{C::Align{
            .nodes
            = {GraphNodeConstraint::Align::Spec{.node = 0},
               GraphNodeConstraint::Align::Spec{.node = 1}},
            .dimension = GraphDimension::XDIM,
        }});

    ir.nodeConstraints.push_back(
        C{C::Align{
            .nodes
            = {GraphNodeConstraint::Align::Spec{.node = 1},
               GraphNodeConstraint::Align::Spec{.node = 3}},
            .dimension = GraphDimension::YDIM,
        }});

    auto lyt = ir.doColaLayout();
    lyt.writeSvg("/tmp/testLibcolaIr1.svg");
    lyt.convert();
}

TEST(GraphUtils, LibcolaIr2) {
    auto ir = init_graph(
        {
            {0, 1},
            {1, 2},
            {2, 0},
            {3, 0},
            {4, 0},
            {2, 3},
            {3, 4},
            {4, 5},
        },
        GraphSize(60, 60));

    ir.width  = 400;
    ir.height = 400;

    auto lyt = ir.doColaLayout();
    lyt.writeSvg("/tmp/testLibcolaIr2.svg");
    auto conv = lyt.convert();

    lyt.router->outputInstanceToSVG("/tmp/testLibcolaIr2_router");
    lyt.router->outputDiagramText("/tmp/testLibcolaIr2_router");
    EXPECT_TRUE(!conv.lines.at({0, 1}).paths.at(0).points.empty());
}

TEST(GraphUtils, LibcolaIr3) {
    GraphLayoutIR ir;

    ir.edges = {
        GraphEdge{.source = 0, .target = 3},
        GraphEdge{.source = 1, .target = 4},
        GraphEdge{.source = 1, .target = 5},
        GraphEdge{.source = 1, .target = 6},
        GraphEdge{.source = 2, .target = 7},
        GraphEdge{.source = 3, .target = 8},
        GraphEdge{.source = 4, .target = 8},
        GraphEdge{.source = 4, .target = 9},
        GraphEdge{.source = 5, .target = 9},
        GraphEdge{.source = 6, .target = 9},
        GraphEdge{.source = 6, .target = 10},
        GraphEdge{.source = 7, .target = 9},
        GraphEdge{.source = 7, .target = 11},
    };

    auto& ec = ir.edgeConstraints;
    using P  = GraphEdgeConstraint::Port;
    // ec[GraphEdge{.source = }]

    ec[{.source = 7, .target = 9}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 6, .target = 10}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 6, .target = 9}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 4, .target = 9}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 1, .target = 6}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 3, .target = 8}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 1, .target = 5}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 7, .target = 11}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 4, .target = 8}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 2, .target = 7}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 1, .target = 4}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 5, .target = 9}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 0, .target = 3}] = GraphEdgeConstraint{
        .sourcePort       = P::East,
        .targetPort       = P::West,
        .targetCheckpoint = 20,
    };


    using C   = GraphNodeConstraint;
    auto ydim = GraphDimension::YDIM;
    auto xdim = GraphDimension::XDIM;

    ir.nodeConstraints = {
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 0}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 1}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 1}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 2}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 3}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 4}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 4}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 5}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 5}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 6}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 6}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 7}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 8}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 9}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left              = C::
                Align{.dimension = ydim, .nodes = {C::Align::Spec{.node = 9}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 10}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 10}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 11}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = xdim,
            .isExactSeparation = true,
            .left
            = {.dimension = xdim,
               .nodes
               = {C::Align::Spec{.node = 0},
                  C::Align::
                      Spec{.node = 1},
                  C::Align::
                      Spec{.node = 2}}},
            .right
            = {.dimension = xdim,
               .nodes
               = {C::Align::Spec{.node = 3},
                  C::Align::
                      Spec{.node = 4},
                  C::Align::
                      Spec{.node = 5},
                  C::Align::
                      Spec{.node = 6},
                  C::Align::
                      Spec{.node = 7}}},
            .separationDistance = 125.0}},
        C{C::Separate{
            .dimension         = xdim,
            .isExactSeparation = true,
            .left
            = {.dimension = xdim,
               .nodes
               = {C::Align::Spec{.node = 3},
                  C::Align::
                      Spec{.node = 4},
                  C::Align::
                      Spec{.node = 5},
                  C::Align::
                      Spec{.node = 6},
                  C::Align::
                      Spec{.node = 7}}},
            .right
            = {.dimension = xdim,
               .nodes
               = {C::Align::Spec{.node = 8},
                  C::Align::
                      Spec{.node = 9},
                  C::Align::
                      Spec{.node = 10},
                  C::Align::
                      Spec{.node = 11}}},
            .separationDistance = 125.0}}};

    ir.rectangles = {
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
    };

    ir.height = 10000;
    ir.width  = 10000;

    auto lyt = ir.doColaLayout();
    lyt.writeSvg("/tmp/testLibcolaIr3.svg");
    auto conv = lyt.convert();

    lyt.router->outputInstanceToSVG("/tmp/testLibcolaIr3_router");
    lyt.router->outputDiagramText("/tmp/testLibcolaIr3_router");
}

TEST(GraphUtils, LibcolaIrMultiEdge) {
    GraphLayoutIR ir;

    ir.edges = {
        GraphEdge{.source = 0, .target = 1, .bundle = 0},
        GraphEdge{.source = 0, .target = 1, .bundle = 1},
        GraphEdge{.source = 0, .target = 1, .bundle = 2},
        GraphEdge{.source = 0, .target = 1, .bundle = 3},
    };

    auto& ec    = ir.edgeConstraints;
    using P     = GraphEdgeConstraint::Port;
    float shift = 0.2f;
    // ec[GraphEdge{.source = }]


    ec[GraphEdge{
        .source = 0,
        .target = 1,
        .bundle = 0,
    }] = GraphEdgeConstraint{
        .sourcePort       = P::East,
        .targetPort       = P::West,
        .sourceOffset     = 0.1f + shift * 0,
        .targetOffset     = 0.9f - shift * 0,
        .sourceCheckpoint = 30,
        .targetCheckpoint = 30,
    };

    ec[GraphEdge{
        .source = 0,
        .target = 1,
        .bundle = 1,
    }] = GraphEdgeConstraint{
        .sourcePort   = P::East,
        .targetPort   = P::West,
        .sourceOffset = 0.1f + shift * 1,
        .targetOffset = 0.9f - shift * 1,
    };

    ec[GraphEdge{
        .source = 0,
        .target = 1,
        .bundle = 2,
    }] = GraphEdgeConstraint{
        .sourcePort   = P::East,
        .targetPort   = P::West,
        .sourceOffset = 0.1f + shift * 2,
        .targetOffset = 0.9f - shift * 2,
    };

    ec[GraphEdge{
        .source = 0,
        .target = 1,
        .bundle = 3,
    }] = GraphEdgeConstraint{
        .sourcePort   = P::East,
        .targetPort   = P::West,
        .sourceOffset = 0.1f + shift * 3,
        .targetOffset = 0.9f - shift * 3,
    };


    using C   = GraphNodeConstraint;
    auto ydim = GraphDimension::YDIM;
    auto xdim = GraphDimension::XDIM;

    ir.nodeConstraints = {
        C{C::Separate{
            .dimension         = xdim,
            .isExactSeparation = true,
            .left = {.dimension = xdim, .nodes = {C::Align::Spec{.node = 0}}},
            .right = {.dimension = xdim, .nodes = {C::Align::Spec{.node = 1}}},
            .separationDistance = 200.0}},
    };

    ir.rectangles = {
        GraphSize{.h = 100.0, .w = 25.0},
        GraphSize{.h = 100.0, .w = 25.0},
    };

    ir.height = 10000;
    ir.width  = 10000;

    auto lyt = ir.doColaLayout();
    lyt.writeSvg("/tmp/LibcolaIrMultiEdge.svg");
    auto conv = lyt.convert();

    lyt.router->outputInstanceToSVG("/tmp/LibcolaIrMultiEdge_router");
    lyt.router->outputDiagramText("/tmp/LibcolaIrMultiEdge_router");
}

TEST(GraphUtils, tHolaIr1) {
    auto ir = init_graph(
        {
            {0, 1},
            {1, 2},
            {2, 0},
            {3, 0},
            {4, 0},
            {2, 3},
            {3, 4},
            {4, 5},
        },
        GraphSize(60, 60));

    auto lyt = ir.doHolaLayout();
    writeFile("/tmp/testHolaIr1.svg", lyt.graph->writeSvg());
    auto conv = lyt.convert();
    EXPECT_TRUE(!conv.lines.at({0, 1}).paths.at(0).points.empty());
}

TEST(GraphUtils, GraphvizIrClusters) {
    auto lyt = ir.doGraphvizLayout(gvc);
    lyt.writeSvg("/tmp/testGraphvizIrClusters.svg");
    lyt.writeXDot("/tmp/testGraphvizIrClusters.xdot");
    auto c = lyt.convert();

    EXPECT_EQ(c.subgraphPaths.size(), 3);
    EXPECT_EQ(c.subgraphs.size(), 1);
    EXPECT_EQ(c.subgraphs.at(0).subgraphs.size(), 2);
    EXPECT_EQ(c.getSubgraph({0}).subgraphs.size(), 2);
    EXPECT_EQ(c.getSubgraph({0, 0}).subgraphs.size(), 0);
    EXPECT_EQ(c.getSubgraph({0, 1}).subgraphs.size(), 0);
    EXPECT_EQ(c.subgraphPaths.at(0), Vec<int>{0});
    EXPECT_EQ(c.subgraphPaths.at(1), (Vec<int>{0, 0}));
    EXPECT_EQ(c.subgraphPaths.at(2), (Vec<int>{0, 1}));
    // QEXPECT_TRUE(toQRect(c.getSubgraph({0}).bbox)
    //                  .contains(toQRect(c.getSubgraph({0, 0}).bbox)));
    // QEXPECT_TRUE(toQRect(c.getSubgraph({0}).bbox)
    //                  .contains(toQRect(c.getSubgraph({0, 1}).bbox)));
}
#endif
