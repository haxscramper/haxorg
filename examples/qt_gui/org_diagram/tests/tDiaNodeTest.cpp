#include <QtTest/QtTest>
#include <QSignalSpy>
#include <haxorg/sem/SemBaseApi.hpp>
#include <src/model/DiaNodeTreeModel.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>

using namespace test;

class DiaNodeTest : public QObject {
    Q_OBJECT

  private slots:
    void testTreeConstruction() {
        ScopeDiagramTree scope;
        auto             v1   = scope.getAdapter("* document level");
        auto             tree = FromDocument(
            scope.tree_context,
            v1.getRootAdapter().as<org::imm::ImmDocument>());
    }

    void testTreeEditRemove() {
        auto             __scope = trackTestExecution(this);
        ScopeDiagramTree scope;
        auto             v1 = scope.getAdapter(R"(
* diagram layer
** layer item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 12, "y": 30}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
** layer item 2
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 12, "y": 90}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
)");
        auto conf = org::imm::ImmAdapter::TreeReprConf::getDefault();
        conf.with_field(&org::imm::ImmSubtree::properties);
        HSLOG_INFO(
            "test", v1.getRootAdapter().treeRepr(conf).toString(false));
        auto canvas = FromDocument(
            scope.tree_context,
            v1.getRootAdapter().as<org::imm::ImmDocument>());
        QVERIFY(canvas.as<DiaNodeCanvas>() != nullptr);
        QCOMPARE_EQ2(canvas.get()->id.getKind(), OrgSemKind::Document);
        auto layer = canvas.at(0, true);
        QCOMPARE_EQ2(layer.get()->id.getKind(), OrgSemKind::Subtree);
        QCOMPARE_EQ2(
            layer.get()->id.as<org::imm::ImmSubtree>().getCleanTitle(),
            "diagram layer"_ss);
        auto item1 = layer.at(0, true);
        QCOMPARE_EQ2(
            item1.get()->id.as<org::imm::ImmSubtree>().getCleanTitle(),
            "layer item 1"_ss);
        auto item2 = layer.at(1, true);
        QCOMPARE_EQ2(
            item2.get()->id.as<org::imm::ImmSubtree>().getCleanTitle(),
            "layer item 2"_ss);

        auto item1_node = item1.get()->as<DiaNodeItem>();
        QVERIFY(item1_node != nullptr);
        auto item2_node = item2.get()->as<DiaNodeItem>();
        QVERIFY(item2_node != nullptr);

        QCOMPARE_EQ2(item1_node->getPos().x, 12);
        QCOMPARE_EQ2(item1_node->getPos().y, 30);
        QCOMPARE_EQ(item2_node->getPos().x, 12);
        QCOMPARE_EQ(item2_node->getPos().y, 90);
    }
};

HAXORG_QT_TEST_MAIN(DiaNodeTest)
#include "tDiaNodeTest.moc"
