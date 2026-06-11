#include "../t_graph_tests_common.hpp"

struct GraphVisualGraphviz_Test : public GraphUtils_Test {};

TEST_F(GraphVisualGraphviz_Test, GraphvizSimpleConstruction) {
    // Create initial graph structure
    auto v1 = addVertex("v1");
    auto v2 = addVertex("v2");
    auto v3 = addVertex("v3");
    auto v4 = addVertex("v4");

    ASSERT_NE(v1, v2);
    ASSERT_NE(v2, v3);
    ASSERT_NE(v3, v4);

    auto e12 = addEdge(v1, v2);
    auto e23 = addEdge(v2, v3);
    auto e31 = addEdge(v3, v1);

    auto rg_id = getGraph()->addVertex();

    // creates a graphviz root graph
    auto root = gv::GraphGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);

    // add vertext, the graph group will internally create a visual
    // attribute and graphviz node object
    root->addVertex(addNesting(rg_id, v1));
    root->addVertex(addNesting(rg_id, v2));
    root->addVertex(addNesting(rg_id, v3));
    root->addVertex(addNesting(rg_id, v4));

    ASSERT_EQ(run->getDirectVertices(rg_id).size(), 4);

    // configure visual parameters for graphviz nodes. The methods are
    // specific to the graphviz layout nodes, and use cgraph API
    // internally.
    auto shape = gv::NodeShape::rect;
    getGv(v1)->setFixedPointWH(120, 120)->setNodeShape(shape);
    getGv(v2)->setFixedPointWH(120, 120)->setNodeShape(shape);
    getGv(v3)->setFixedPointWH(240, 240)->setNodeShape(shape);
    getGv(v4)->setFixedPointWH(240, 240)->setNodeShape(shape);

    // Add edges to the graphviz graph. This links already existing
    // semantic vertices to the visual representation in the layout.
    root->addEdge(e12);
    root->addEdge(e23);
    root->addEdge(e31);

    ASSERT_EQ(run->getDirectlyNestedEdges(rg_id).size(), 3);

    // For the graphviz backend, adding vertices and edges is enough to
    // gnerate a PNG file with cgraph API. It does not populate the layout
    // attributes for the overall algorithm, but can be used for debugging.
    root->render("/tmp/result.png");

    // Running for layout will populate all maps and fields of the layout
    // run with placement information.
    ASSERT_TRUE(run != nullptr);
    run->runFullLayout();

    // 4 vertices + 1 root group
    EXPECT_EQ(run->result.vertices.size(), 5);

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

TEST_F(GraphVisualGraphviz_Test, GraphvizSameLayoutClusters) {
    hstd::Vec<VertexID> vs;
    hstd::Vec<EdgeID>   es;

    for (int i = 0; i < 11; ++i) {
        vs.push_back(addVertex(hstd::fmt("id_{}", i)));
    }

    auto     rg_id  = addVertex("rg_id");
    VertexID sg_id1 = addVertex("sg_id1");
    VertexID sg_id2 = addVertex("sg_id2");

    auto edge = [&](int source, int target) {
        es.push_back(addEdge(vs.at(source), vs.at(target)));
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


    auto root = gv::GraphGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);
    auto ctx = root->context();

    EXPECT_EQ(run->getRootGroups().size(), 1);
    EXPECT_EQ(run->getSubGroups(rg_id).size(), 0);

    auto sg_1 = root->addNewNativeSubgroup(addNesting(rg_id, sg_id1));
    auto sg_2 = root->addNewNativeSubgroup(addNesting(rg_id, sg_id2));

    auto shape = gv::NodeShape::rect;

    EXPECT_EQ(run->getSubGroups(rg_id).size(), 2);

    as<gv::NodeAttribute>(sg_1->addVertex(addNesting(sg_id1, vs.at(3))))
        ->setFixedPointWH(120, 60)
        ->setNodeShape(shape)
        ->setLabel("VERT-3");
    as<gv::NodeAttribute>(sg_1->addVertex(addNesting(sg_id1, vs.at(4))))
        ->setFixedPointWH(180, 120)
        ->setNodeShape(shape)
        ->setLabel("VERT-4");
    as<gv::NodeAttribute>(sg_1->addVertex(addNesting(sg_id1, vs.at(6))))
        ->setFixedPointWH(240, 60)
        ->setNodeShape(shape)
        ->setLabel("VERT-6");

    root->render(getDebugFile("result-1.png"));

    hstd::ext::graph::proto::IGraphProto ig;
    run->getGraph()->writeSerial(&ig);
    writeFile(getDebugFile("result.json"), getJString(ig));

    EXPECT_EQ(run->getDirectlyNestedEdges(rg_id).size(), 0);
    EXPECT_EQ(run->getDirectVertices(sg_id1).size(), 3);

    as<gv::NodeAttribute>(sg_2->addVertex(addNesting(sg_id2, vs.at(5))))
        ->setFixedPointWH(120, 60)
        ->setNodeShape(shape)
        ->setLabel("VERT-5");
    as<gv::NodeAttribute>(sg_2->addVertex(addNesting(sg_id2, vs.at(9))))
        ->setFixedPointWH(120, 60)
        ->setNodeShape(shape)
        ->setLabel("VERT-9");
    as<gv::NodeAttribute>(sg_2->addVertex(addNesting(sg_id2, vs.at(7))))
        ->setFixedPointWH(120, 60)
        ->setNodeShape(shape)
        ->setLabel("VERT-7");
    as<gv::NodeAttribute>(sg_2->addVertex(addNesting(sg_id2, vs.at(10))))
        ->setFixedPointWH(120, 60)
        ->setNodeShape(shape)
        ->setLabel("VERT-10");


    EXPECT_EQ(run->getDirectVertices(rg_id).size(), 0);
    EXPECT_EQ(run->getDirectVertices(sg_id1).size(), 3);
    EXPECT_EQ(run->getDirectVertices(sg_id2).size(), 4);

    as<gv::EdgeAttribute>(sg_1->addEdge(es.at(4)));
    as<gv::EdgeAttribute>(sg_1->addEdge(es.at(5)));

    as<gv::EdgeAttribute>(sg_2->addEdge(es.at(8)));
    as<gv::EdgeAttribute>(sg_2->addEdge(es.at(9)));
    as<gv::EdgeAttribute>(sg_2->addEdge(es.at(10)));

    root->render(getDebugFile("result.png"));

    EXPECT_EQ(run->getDirectVertices(rg_id).size(), 0);
    EXPECT_EQ(run->getDirectVertices(sg_id1).size(), 3);
    EXPECT_EQ(run->getDirectVertices(sg_id2).size(), 4);

    run->runFullLayout();

    auto const& res = run->result;

    EXPECT_EQ(res.vertices.size(), 10);
    EXPECT_EQ(res.edges.size(), 5);

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}

TEST_F(GraphVisualGraphviz_Test, GraphvizDifferentLayoutClusters) {
    hstd::Vec<VertexID> vs;
    hstd::Vec<EdgeID>   es;
    for (int i = 0; i < 6; ++i) {
        vs.push_back(addVertex(hstd::fmt("id_{}", i)));
    }

    auto edge = [&](int source, int target) {
        es.push_back(getGraph()->addEdge(vs.at(source), vs.at(target)));
    };

    edge(0, 1); // 0
    edge(1, 2); // 1
    edge(2, 0); // 2
    edge(3, 4); // 3
    edge(4, 5); // 4
    edge(5, 3); // 5

    auto     rg_id  = addVertex("rg_id");
    VertexID sg_id1 = addVertex("sg_id1");
    VertexID sg_id2 = addVertex("sg_id2");

    auto root = gv::GraphGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);
    auto ctx = root->context();

    auto sg2 = root->addNewNativeSubgroup(
        addNesting(rg_id, sg_id2), /*with_algorithm=*/true);
    sg2->getAlgorithm<gv::Layout>()->layout = gv::LayoutType::Dot;

    auto sg1 = root->addNewNativeSubgroup(
        addNesting(rg_id, sg_id1), /*with_algorithm=*/true);
    sg1->getAlgorithm<gv::Layout>()->layout = gv::LayoutType::Circo;

    as<gv::NodeAttribute>(sg1->addVertex(addNesting(sg_id1, vs.at(0))))
        ->setFixedPointWH(60, 60)
        ->setLabel(getGraph()->getVertex(vs.at(0))->getStableId());
    as<gv::NodeAttribute>(sg1->addVertex(addNesting(sg_id1, vs.at(1))))
        ->setFixedPointWH(60, 60)
        ->setLabel(getGraph()->getVertex(vs.at(1))->getStableId());
    as<gv::NodeAttribute>(sg1->addVertex(addNesting(sg_id1, vs.at(2))))
        ->setFixedPointWH(60, 60)
        ->setLabel(getGraph()->getVertex(vs.at(2))->getStableId());

    as<gv::NodeAttribute>(sg2->addVertex(addNesting(sg_id2, vs.at(3))))
        ->setFixedPointWH(60, 60)
        ->setLabel(getGraph()->getVertex(vs.at(3))->getStableId());
    as<gv::NodeAttribute>(sg2->addVertex(addNesting(sg_id2, vs.at(4))))
        ->setFixedPointWH(60, 60)
        ->setLabel(getGraph()->getVertex(vs.at(4))->getStableId());
    as<gv::NodeAttribute>(sg2->addVertex(addNesting(sg_id2, vs.at(5))))
        ->setFixedPointWH(60, 60)
        ->setLabel(getGraph()->getVertex(vs.at(5))->getStableId());


    as<gv::EdgeAttribute>(sg1->addEdge(es.at(0)));
    as<gv::EdgeAttribute>(sg1->addEdge(es.at(1)));
    as<gv::EdgeAttribute>(sg1->addEdge(es.at(2)));

    as<gv::EdgeAttribute>(sg2->addEdge(es.at(3)));
    as<gv::EdgeAttribute>(sg2->addEdge(es.at(4)));
    as<gv::EdgeAttribute>(sg2->addEdge(es.at(5)));


    run->runFullLayout();

    auto const& res = run->result;

    EXPECT_EQ(res.vertices.size(), 9);
    EXPECT_EQ(res.edges.size(), 6);

    auto visual = run->getVisual();

    EXPECT_EQ(visual.size(), 2);
    EXPECT_EQ(visual.at(0).subgroups.size(), 2);

    auto const vsg  = visual.at(0);
    auto const vsg1 = visual.at(0).subgroups.at(0);
    auto const vsg2 = visual.at(0).subgroups.at(1);
    EXPECT_EQ(vsg1.subgroups.size(), 6);
    EXPECT_EQ(vsg2.subgroups.size(), 6);

    EXPECT_EQ(vsg1.elements.size(), 2);
    EXPECT_EQ(vsg2.elements.size(), 2);

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

    EXPECT_OUTCOME_OK(checkLeftOf(/*stationary=*/run->getVisual(sg_id2),
                                  /*relative=*/run->getVisual(sg_id1)));

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
    for (VertexID const& gid : hstd::as_vec(sg_id1, sg_id2)) {
        auto const& group = run->getGroup(gid);
        for (VertexID vert : run->getDirectVertices(gid)) {
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

TEST_F(GraphVisualGraphviz_Test, GraphvizIrClusters) {
    hstd::Vec<VertexID> vs;
    for (int i = 0; i < 6; ++i) { vs.push_back(getGraph()->addVertex()); }

    auto e01 = getGraph()->addEdge(vs.at(0), vs.at(1));
    auto e12 = getGraph()->addEdge(vs.at(1), vs.at(2));
    auto e20 = getGraph()->addEdge(vs.at(2), vs.at(0));

    auto e34 = getGraph()->addEdge(vs.at(3), vs.at(4));
    auto e45 = getGraph()->addEdge(vs.at(4), vs.at(5));
    auto e53 = getGraph()->addEdge(vs.at(5), vs.at(3));

    auto     rg_id  = getGraph()->addVertex();
    VertexID sg_id1 = getGraph()->addVertex();
    VertexID sg_id2 = getGraph()->addVertex();

    auto root = gv::GraphGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);

    auto sg_1 = root->addNewNativeSubgroup(addNesting(rg_id, sg_id1));
    auto sg_2 = root->addNewNativeSubgroup(addNesting(rg_id, sg_id2));

    auto shape = gv::NodeShape::rect;

    as<gv::NodeAttribute>(sg_1->addVertex(addNesting(sg_id1, vs.at(0))))
        ->setFixedPointWH(60, 40)
        ->setNodeShape(shape)
        ->setLabel("A0");
    as<gv::NodeAttribute>(sg_1->addVertex(addNesting(sg_id1, vs.at(1))))
        ->setFixedPointWH(60, 40)
        ->setNodeShape(shape)
        ->setLabel("A1");
    as<gv::NodeAttribute>(sg_1->addVertex(addNesting(sg_id1, vs.at(2))))
        ->setFixedPointWH(60, 40)
        ->setNodeShape(shape)
        ->setLabel("A2");

    as<gv::NodeAttribute>(sg_2->addVertex(addNesting(sg_id2, vs.at(3))))
        ->setFixedPointWH(60, 40)
        ->setNodeShape(shape)
        ->setLabel("B0");
    as<gv::NodeAttribute>(sg_2->addVertex(addNesting(sg_id2, vs.at(4))))
        ->setFixedPointWH(60, 40)
        ->setNodeShape(shape)
        ->setLabel("B1");
    as<gv::NodeAttribute>(sg_2->addVertex(addNesting(sg_id2, vs.at(5))))
        ->setFixedPointWH(60, 40)
        ->setNodeShape(shape)
        ->setLabel("B2");

    as<gv::EdgeAttribute>(sg_1->addEdge(e01));
    as<gv::EdgeAttribute>(sg_1->addEdge(e12));
    as<gv::EdgeAttribute>(sg_1->addEdge(e20));

    as<gv::EdgeAttribute>(sg_2->addEdge(e34));
    as<gv::EdgeAttribute>(sg_2->addEdge(e45));
    as<gv::EdgeAttribute>(sg_2->addEdge(e53));

    run->runFullLayout();

    auto const& res = run->result;
    EXPECT_EQ(res.vertices.size(), 9);
    EXPECT_EQ(res.edges.size(), 6);

    auto visual = run->getVisual();
    EXPECT_EQ(visual.size(), 2);
    EXPECT_EQ(visual.at(0).subgroups.size(), 2);

    hstd::writeFile(
        getDebugFile("graphviz_ir_clusters.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}
