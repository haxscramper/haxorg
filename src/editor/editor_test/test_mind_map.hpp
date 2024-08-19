#pragma once
#include "test_utils.hpp"

class TestMindMap
    : public QObject
    , public TestBase {
    Q_OBJECT
  private slots:
    void initTestCase() { init_test_base(); }
    void cleanupTestCase() { cleanup_test_base(); }

    void testGraphConstruction();
    void testGraphConstructionSubtreeId1();
    void testGraphConstructionFootnoteId();
    void testGraphConstructionMultipleLinks_footnote1();
    void testGraphConstructionMultipleLinks_footnote2();
    void testGraphConstructionSubtree_description_lists();
    void testGraphConstructionLoose_end_origin();
    void testFullMindMapGraph();
    void testLargeSubtreeGraph();
    void testNestedFootnotesGraph();
    void testQtGraphModel1();
    void testQtGraphScene1();
    void testQtGraphSceneFullMindMap();
    void testMindMapNodeAdd1();
    void testMindMapNodeAddRemoveAdd();
    void testMindMapSignals1();
    void testRowModelSignals();
    void testGraphLayoutRowConsistency();
    void testGraphLayoutFilterSignals();
    void testGraphLayoutUpdateSignals();
    void testGraphvizLayoutAlgorithms();
    void testMultiRootGraphConstruction();
    void testMultiViewGraphConstruction();

    void testTreeEditingApiReaction();
};
