#include <QtTest/QtTest>
#include <QSignalSpy>
#include <memory>
#include <src/model/QtOrgAstModel.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>

using namespace test;

class QtOrgAstModelTest_Standalone : public QObject {
    Q_OBJECT

  public:
    org::imm::ImmAstContext::Ptr context;
    QtOrgAstModelTest_Standalone()
        : context{org::imm::ImmAstContext::init_start_context()} {}

  private:
    std::shared_ptr<DiagramTreeNode> createTestTree(
        ScopeDiagramTree& scope) {
        auto root = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(1));
        auto child1 = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(2));
        auto child2 = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(3));
        auto grandchild1 = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(4));

        root->addSubnode(child1);
        root->addSubnode(child2);
        child1->addSubnode(grandchild1);

        return root;
    }

    org::imm::ImmAdapter getId(int i) const {
        return context->adapt(
            org::imm::ImmUniqId{org::imm::ImmId(OrgSemKind::Space, i)});
    }

  private slots:
    void testOrgDiagramNodeCreation() {
        ScopeDiagramTree scope;
        auto             node = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(1));
        QVERIFY(!node->id.id.isNil());
        QVERIFY(node->subnodes.empty());
        QVERIFY(node->parent.expired());
    }

    void testOrgDiagramNodeAddSubnode() {
        ScopeDiagramTree scope;
        auto             parent = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(1));
        auto child = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(2));

        QSignalSpy spy{parent.get(), &DiagramTreeNode::subnodeAdded};

        parent->addSubnode(child);

        QCOMPARE(parent->subnodes.size(), 1);
        QCOMPARE(parent->subnodes.at(0), child);
        QCOMPARE(child->parent.lock(), parent);
        QCOMPARE(spy.count(), 1);
        QCOMPARE(spy.at(0).at(0).toInt(), 0);
    }

    void testOrgDiagramNodeRemoveSubnode() {
        ScopeDiagramTree scope;
        auto             parent = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(1));
        auto child = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(2));

        parent->addSubnode(child);

        QSignalSpy aboutToRemoveSpy{
            parent.get(), &DiagramTreeNode::subnodeAboutToBeRemoved};
        QSignalSpy removedSpy{
            parent.get(), &DiagramTreeNode::subnodeRemoved};

        parent->removeSubnode(0);

        QVERIFY(parent->subnodes.empty());
        QVERIFY(child->parent.expired());
        QCOMPARE(aboutToRemoveSpy.count(), 1);
        QCOMPARE(aboutToRemoveSpy.at(0).at(0).toInt(), 0);
        QCOMPARE(removedSpy.count(), 1);
    }

    void testOrgDiagramNodeUpdateData() {
        auto             __scope = trackTestExecution(this);
        ScopeDiagramTree scope;
        auto             node = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(1));
        QSignalSpy spy{node.get(), &DiagramTreeNode::dataChanged};

        node->updateData();

        QCOMPARE(spy.count(), 1);
    }

    void testModelCreation() {
        ScopeDiagramTree scope;
        auto             root = createTestTree(scope);
        OrgDiagramModel  model{root, scope.tree_context};

        QCOMPARE(model.rowCount(), 2);
        QCOMPARE(model.columnCount(), 1);
    }

    void testModelIndex() {
        ScopeDiagramTree scope;
        auto             root = createTestTree(scope);
        OrgDiagramModel  model{root, scope.tree_context};

        QModelIndex child1Index = model.index(0, 0);
        QModelIndex child2Index = model.index(1, 0);

        QVERIFY(child1Index.isValid());
        QVERIFY(child2Index.isValid());
        QCOMPARE(child1Index.row(), 0);
        QCOMPARE(child2Index.row(), 1);
    }

    void testModelParent() {
        ScopeDiagramTree scope;
        auto             root = createTestTree(scope);
        OrgDiagramModel  model{root, scope.tree_context};

        QModelIndex child1Index      = model.index(0, 0);
        QModelIndex grandchild1Index = model.index(0, 0, child1Index);

        QVERIFY(grandchild1Index.isValid());
        QCOMPARE(model.parent(grandchild1Index), child1Index);
        QCOMPARE(model.parent(child1Index), QModelIndex{});
    }

    void testModelRowCount() {
        ScopeDiagramTree scope;
        auto             root = createTestTree(scope);
        OrgDiagramModel  model{root, scope.tree_context};

        QModelIndex child1Index = model.index(0, 0);
        QModelIndex child2Index = model.index(1, 0);

        QCOMPARE(model.rowCount(), 2);
        QCOMPARE(model.rowCount(child1Index), 1);
        QCOMPARE(model.rowCount(child2Index), 0);
    }

    void testModelData() {
        ScopeDiagramTree scope;
        auto             root = createTestTree(scope);
        OrgDiagramModel  model{root, scope.tree_context};

        QModelIndex child1Index = model.index(0, 0);
        QVariant    data        = model.data(child1Index, Qt::DisplayRole);

        QVERIFY(!data.toString().isEmpty());
        QVERIFY(data.toString().contains("Node"));
    }

    void testModelInsertRows() {
        ScopeDiagramTree scope;
        auto             root = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(1));
        OrgDiagramModel model{root, scope.tree_context};

        QSignalSpy spy{&model, &QAbstractItemModel::rowsInserted};

        bool result = model.insertRows(0, 2);

        QVERIFY(result);
        QCOMPARE(model.rowCount(), 2);
        QCOMPARE(root->subnodes.size(), 2);
        QCOMPARE(spy.count(), 1);
    }

    void testModelRemoveRows() {
        ScopeDiagramTree scope;
        auto             root = createTestTree(scope);
        OrgDiagramModel  model{root, scope.tree_context};

        QSignalSpy spy{&model, &QAbstractItemModel::rowsRemoved};

        bool result = model.removeRows(0, 1);

        QVERIFY(result);
        QCOMPARE(model.rowCount(), 1);
        QCOMPARE(root->subnodes.size(), 1);
        QCOMPARE(spy.count(), 1);
    }

    void testModelAddNodeToParent() {
        auto             __scope = trackTestExecution(this);
        ScopeDiagramTree scope;
        auto             root = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(1));
        TRACKED_OBJECT(root);
        OrgDiagramModel model{root, scope.tree_context};
        auto            newNode = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(2));
        TRACKED_OBJECT(newNode);

        hstd::log::SignalDebugger debugger{get_tracker(), &model};
        QSignalSpy spy{&model, &QAbstractItemModel::rowsInserted};

        QCOMPARE(model.rowCount(), 0);
        model.addNodeToParent(newNode, QModelIndex{});


        QCOMPARE(model.rowCount(), 1);
        QCOMPARE(root->subnodes.size(), 1);
        QCOMPARE(root->subnodes.at(0), newNode);
        QCOMPARE(spy.count(), 1);
    }

    void testModelGetIndexForId() {
        ScopeDiagramTree scope;
        auto             root = createTestTree(scope);
        OrgDiagramModel  model{root, scope.tree_context};

        auto        childId = root->subnodes.at(0)->id;
        QModelIndex index   = model.getIndexForId(childId.uniq());

        QVERIFY(index.isValid());
        QCOMPARE(index.row(), 0);
        QCOMPARE(index.column(), 0);
    }

    void testBidirectionalSync() {
        ScopeDiagramTree scope;
        auto             root = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(1));
        OrgDiagramModel model{root, scope.tree_context};

        QSignalSpy modelSpy{&model, &QAbstractItemModel::rowsInserted};

        auto newNode = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(2));
        root->addSubnode(newNode);

        QCOMPARE(model.rowCount(), 1);
        QCOMPARE(modelSpy.count(), 1);
    }

    void testDataChangedSync() {
        auto             __scope = trackTestExecution(this);
        ScopeDiagramTree scope;
        auto             root = createTestTree(scope);
        OrgDiagramModel  model{root, scope.tree_context};

        TRACKED_OBJECT(root->subnodes.at(0).get());

        QSignalSpy spyModelDataChanged{
            &model, &QAbstractItemModel::dataChanged};
        QSignalSpy spyNodeDataChanged{
            root->subnodes.at(0).get(), &DiagramTreeNode::dataChanged};

        root->subnodes.at(0)->updateData();

        QCOMPARE(spyNodeDataChanged.count(), 1);
        QCOMPARE(spyModelDataChanged.count(), 1);
    }

    void testRemoveInvalidIndex() {
        ScopeDiagramTree scope;
        auto             root = std::make_shared<DiagramTreeNode>(
            scope.tree_context, getId(2));
        OrgDiagramModel model{root, scope.tree_context};

        bool result = model.removeRows(0, 1);

        QVERIFY(!result);
    }

    void testInsertAtSpecificPosition() {
        ScopeDiagramTree scope;
        auto             root = createTestTree(scope);
        OrgDiagramModel  model{root, scope.tree_context};

        QModelIndex child1Index = model.index(0, 0);
        bool        result      = model.insertRows(0, 1, child1Index);

        QVERIFY(result);
        QCOMPARE(model.rowCount(child1Index), 2);
        QCOMPARE(root->subnodes.at(0)->subnodes.size(), 2);
    }

    void testNodeMapConsistency() {
        auto             __scope = trackTestExecution(this);
        ScopeDiagramTree scope;
        auto             root = createTestTree(scope);
        OrgDiagramModel  model{root, scope.tree_context};

        auto rootId       = root->id;
        auto child1Id     = root->subnodes.at(0)->id;
        auto grandchildId = root->subnodes.at(0)->subnodes.at(0)->id;


        HSLOG_INFO(
            "test", "root diagram tree\n", root->format().toString(false));
        HSLOG_INFO(
            "test",
            "model diagram tree\n",
            model.format().toString(false));
        QVERIFY(model.getIndexForId(rootId.uniq()) == QModelIndex{});
        QVERIFY(model.getIndexForId(child1Id.uniq()).isValid());
        QVERIFY(model.getIndexForId(grandchildId.uniq()).isValid());

        model.removeRows(0, 1);

        QVERIFY(!model.getIndexForId(child1Id.uniq()).isValid());
        QVERIFY(!model.getIndexForId(grandchildId.uniq()).isValid());
    }

    void testMultipleDataChanges() {
        auto             __scope = trackTestExecution(this);
        ScopeDiagramTree scope;
        auto             root = createTestTree(scope);
        OrgDiagramModel  model{root, scope.tree_context};

        QSignalSpy spy{&model, &QAbstractItemModel::dataChanged};

        root->subnodes.at(0)->updateData();
        root->subnodes.at(1)->updateData();
        root->subnodes.at(0)->subnodes.at(0)->updateData();

        QCOMPARE(spy.count(), 3);
    }

    void testInvalidColumnAccess() {
        auto             __scope = trackTestExecution(this);
        ScopeDiagramTree scope;
        auto             root = createTestTree(scope);
        OrgDiagramModel  model{root, scope.tree_context};

        QModelIndex invalidIndex = model.index(0, 1);
        QVERIFY(!invalidIndex.isValid());
    }
};

HAXORG_QT_TEST_MAIN(QtOrgAstModelTest_Standalone)
#include "tQtOrgAstModelTest_Standalone.moc"
