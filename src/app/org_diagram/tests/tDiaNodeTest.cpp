#include <QtTest/QtTest>
#include <QSignalSpy>
#include <haxorg/api/SemBaseApi.hpp>
#include <org_diagram/src/model/DiaNodeTreeModel.hpp>
#include <org_diagram/src/utils/common.hpp>
#include <org_diagram/src/utils/test_utils.hpp>
#include <org_diagram/src/model/nodes/DiagramTreeNode.hpp>

#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>

using namespace test;

class DiaNodeTest : public QObject {
    Q_OBJECT

  private slots:
    void testTreeConstruction() {
        ScopeDiagramTree scope;
        auto             v1   = scope.getAdapter("* document level");
        auto             tree = FromDocument(
            scope.dia_context,
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
            scope.dia_context,
            v1.getRootAdapter().as<org::imm::ImmDocument>());
        QVERIFY(canvas->dyn_cast<DiaNodeCanvas>() != nullptr);
        QCOMPARE_EQ2(canvas->id.getKind(), OrgSemKind::Document);
        auto layer = canvas.at(0, true);
        QCOMPARE_EQ2(layer->id.getKind(), OrgSemKind::Subtree);
        QCOMPARE_EQ2(
            layer->id.as<org::imm::ImmSubtree>().getCleanTitle(),
            "diagram layer"_ss);
        auto item1 = layer.at(0, true);
        QCOMPARE_EQ2(
            item1->id.as<org::imm::ImmSubtree>().getCleanTitle(),
            "layer item 1"_ss);
        auto item2 = layer.at(1, true);
        QCOMPARE_EQ2(
            item2->id.as<org::imm::ImmSubtree>().getCleanTitle(),
            "layer item 2"_ss);

        auto item1_node = item1->dyn_cast<DiaNodeItem>();
        QVERIFY(item1_node != nullptr);
        auto item2_node = item2->dyn_cast<DiaNodeItem>();
        QVERIFY(item2_node != nullptr);

        QCOMPARE_EQ2(item1_node->getPos().value().x(), 12);
        QCOMPARE_EQ2(item1_node->getPos().value().y(), 30);
        QCOMPARE_EQ(item2_node->getPos().value().x(), 12);
        QCOMPARE_EQ(item2_node->getPos().value().y(), 90);
    }
};

HAXORG_QT_TEST_MAIN(DiaNodeTest)
#include "tDiaNodeTest.moc"
