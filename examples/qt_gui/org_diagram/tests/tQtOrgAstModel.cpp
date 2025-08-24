#include <QtTest/QtTest>
#include <QSignalSpy>
#include <memory>
#include <src/model/QtOrgAstModel.hpp>
#include <src/utils/common.hpp>


class QtOrgAstModelTest : public QObject {
    Q_OBJECT

  private:
    std::shared_ptr<OrgDiagramNode> createTestTree() {
        auto root        = std::make_shared<OrgDiagramNode>(getId(1));
        auto child1      = std::make_shared<OrgDiagramNode>(getId(2));
        auto child2      = std::make_shared<OrgDiagramNode>(getId(3));
        auto grandchild1 = std::make_shared<OrgDiagramNode>(getId(4));

        root->addSubnode(child1);
        root->addSubnode(child2);
        child1->addSubnode(grandchild1);

        return root;
    }

    org::imm::ImmUniqId getId(int i) const {
        return org::imm::ImmUniqId{org::imm::ImmId::FromValue(i)};
    }

  private slots:
    void testOrgDiagramNodeCreation() {
        auto node = std::make_shared<OrgDiagramNode>(getId(1));
        QVERIFY(!node->id.id.isNil());
        QVERIFY(node->subnodes.empty());
        QVERIFY(node->parent.expired());
    }

    void testOrgDiagramNodeAddSubnode() {
        auto parent = std::make_shared<OrgDiagramNode>(getId(1));
        auto child  = std::make_shared<OrgDiagramNode>(getId(2));

        QSignalSpy spy{parent.get(), &OrgDiagramNode::subnodeAdded};

        parent->addSubnode(child);

        QCOMPARE(parent->subnodes.size(), 1);
        QCOMPARE(parent->subnodes.at(0), child);
        QCOMPARE(child->parent.lock(), parent);
        QCOMPARE(spy.count(), 1);
        QCOMPARE(spy.at(0).at(0).toInt(), 0);
    }

    void testOrgDiagramNodeRemoveSubnode() {
        auto parent = std::make_shared<OrgDiagramNode>(getId(1));
        auto child  = std::make_shared<OrgDiagramNode>(getId(2));

        parent->addSubnode(child);

        QSignalSpy aboutToRemoveSpy{
            parent.get(), &OrgDiagramNode::subnodeAboutToBeRemoved};
        QSignalSpy removedSpy{
            parent.get(), &OrgDiagramNode::subnodeRemoved};

        parent->removeSubnode(0);

        QVERIFY(parent->subnodes.empty());
        QVERIFY(child->parent.expired());
        QCOMPARE(aboutToRemoveSpy.count(), 1);
        QCOMPARE(aboutToRemoveSpy.at(0).at(0).toInt(), 0);
        QCOMPARE(removedSpy.count(), 1);
    }

    void testOrgDiagramNodeUpdateData() {
        auto       __scope = trackTestExecution(this);
        auto       node    = std::make_shared<OrgDiagramNode>(getId(1));
        QSignalSpy spy{node.get(), &OrgDiagramNode::dataChanged};

        node->updateData();

        QCOMPARE(spy.count(), 1);
    }

    void testModelCreation() {
        auto            root = createTestTree();
        OrgDiagramModel model{root};

        QCOMPARE(model.rowCount(), 2);
        QCOMPARE(model.columnCount(), 1);
    }

    void testModelIndex() {
        auto            root = createTestTree();
        OrgDiagramModel model{root};

        QModelIndex child1Index = model.index(0, 0);
        QModelIndex child2Index = model.index(1, 0);

        QVERIFY(child1Index.isValid());
        QVERIFY(child2Index.isValid());
        QCOMPARE(child1Index.row(), 0);
        QCOMPARE(child2Index.row(), 1);
    }

    void testModelParent() {
        auto            root = createTestTree();
        OrgDiagramModel model{root};

        QModelIndex child1Index      = model.index(0, 0);
        QModelIndex grandchild1Index = model.index(0, 0, child1Index);

        QVERIFY(grandchild1Index.isValid());
        QCOMPARE(model.parent(grandchild1Index), child1Index);
        QCOMPARE(model.parent(child1Index), QModelIndex{});
    }

    void testModelRowCount() {
        auto            root = createTestTree();
        OrgDiagramModel model{root};

        QModelIndex child1Index = model.index(0, 0);
        QModelIndex child2Index = model.index(1, 0);

        QCOMPARE(model.rowCount(), 2);
        QCOMPARE(model.rowCount(child1Index), 1);
        QCOMPARE(model.rowCount(child2Index), 0);
    }

    void testModelData() {
        auto            root = createTestTree();
        OrgDiagramModel model{root};

        QModelIndex child1Index = model.index(0, 0);
        QVariant    data        = model.data(child1Index, Qt::DisplayRole);

        QVERIFY(!data.toString().isEmpty());
        QVERIFY(data.toString().contains("Node"));
    }

    void testModelInsertRows() {
        auto            root = std::make_shared<OrgDiagramNode>(getId(1));
        OrgDiagramModel model{root};

        QSignalSpy spy{&model, &QAbstractItemModel::rowsInserted};

        bool result = model.insertRows(0, 2);

        QVERIFY(result);
        QCOMPARE(model.rowCount(), 2);
        QCOMPARE(root->subnodes.size(), 2);
        QCOMPARE(spy.count(), 1);
    }

    void testModelRemoveRows() {
        auto            root = createTestTree();
        OrgDiagramModel model{root};

        QSignalSpy spy{&model, &QAbstractItemModel::rowsRemoved};

        bool result = model.removeRows(0, 1);

        QVERIFY(result);
        QCOMPARE(model.rowCount(), 1);
        QCOMPARE(root->subnodes.size(), 1);
        QCOMPARE(spy.count(), 1);
    }

    void testModelAddNodeToParent() {
        auto __scope = trackTestExecution(this);
        auto root    = std::make_shared<OrgDiagramNode>(getId(1));
        TRACKED_OBJECT(root);
        OrgDiagramModel model{root};
        auto newNode = std::make_shared<OrgDiagramNode>(getId(2));
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
        auto            root = createTestTree();
        OrgDiagramModel model{root};

        org::imm::ImmUniqId childId = root->subnodes.at(0)->id;
        QModelIndex         index   = model.getIndexForId(childId);

        QVERIFY(index.isValid());
        QCOMPARE(index.row(), 0);
        QCOMPARE(index.column(), 0);
    }

    void testBidirectionalSync() {
        auto            root = std::make_shared<OrgDiagramNode>(getId(1));
        OrgDiagramModel model{root};

        QSignalSpy modelSpy{&model, &QAbstractItemModel::rowsInserted};

        auto newNode = std::make_shared<OrgDiagramNode>(getId(2));
        root->addSubnode(newNode);

        QCOMPARE(model.rowCount(), 1);
        QCOMPARE(modelSpy.count(), 1);
    }

    void testDataChangedSync() {
        auto            __scope = trackTestExecution(this);
        auto            root    = createTestTree();
        OrgDiagramModel model{root};

        QSignalSpy spyModelDataChanged{
            &model, &QAbstractItemModel::dataChanged};
        QSignalSpy spyNodeDataChanged{
            root->subnodes.at(0).get(), &OrgDiagramNode::dataChanged};

        root->subnodes.at(0)->updateData();

        QCOMPARE(spyNodeDataChanged.count(), 1);
        QCOMPARE(spyModelDataChanged.count(), 1);
    }

    void testRemoveInvalidIndex() {
        auto            root = std::make_shared<OrgDiagramNode>(getId(2));
        OrgDiagramModel model{root};

        bool result = model.removeRows(0, 1);

        QVERIFY(!result);
    }

    void testInsertAtSpecificPosition() {
        auto            root = createTestTree();
        OrgDiagramModel model{root};

        QModelIndex child1Index = model.index(0, 0);
        bool        result      = model.insertRows(0, 1, child1Index);

        QVERIFY(result);
        QCOMPARE(model.rowCount(child1Index), 2);
        QCOMPARE(root->subnodes.at(0)->subnodes.size(), 2);
    }

    void testNodeMapConsistency() {
        auto            root = createTestTree();
        OrgDiagramModel model{root};

        org::imm::ImmUniqId rootId       = root->id;
        org::imm::ImmUniqId child1Id     = root->subnodes.at(0)->id;
        org::imm::ImmUniqId grandchildId = root->subnodes.at(0)
                                               ->subnodes.at(0)
                                               ->id;

        QVERIFY(model.getIndexForId(rootId) == QModelIndex{});
        QVERIFY(model.getIndexForId(child1Id).isValid());
        QVERIFY(model.getIndexForId(grandchildId).isValid());

        model.removeRows(0, 1);

        QVERIFY(!model.getIndexForId(child1Id).isValid());
        QVERIFY(!model.getIndexForId(grandchildId).isValid());
    }

    void testMultipleDataChanges() {
        auto            __scope = trackTestExecution(this);
        auto            root    = createTestTree();
        OrgDiagramModel model{root};

        QSignalSpy spy{&model, &QAbstractItemModel::dataChanged};

        root->subnodes.at(0)->updateData();
        root->subnodes.at(1)->updateData();
        root->subnodes.at(0)->subnodes.at(0)->updateData();

        QCOMPARE(spy.count(), 3);
    }

    void testInvalidColumnAccess() {
        auto            __scope = trackTestExecution(this);
        auto            root    = createTestTree();
        OrgDiagramModel model{root};

        QModelIndex invalidIndex = model.index(0, 1);
        QVERIFY(!invalidIndex.isValid());

        QCOMPARE(model.rowCount(model.index(0, 1)), 0);
    }
};

HAXORG_QT_TEST_MAIN(QtOrgAstModelTest)
#include "tQtOrgAstModel.moc"
