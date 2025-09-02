#include <QtTest/QtTest>
#include <QSignalSpy>
#include <haxorg/sem/SemBaseApi.hpp>
#include <src/model/QtOrgAstModel.hpp>
#include <src/utils/common.hpp>
#include <src/model/nodes/DiagramTreeNodeLayer.hpp>
#include <src/model/nodes/DiagramTreeNodeCanvas.hpp>
#include <src/model/nodes/DiagramTreeNodeItem.hpp>


class OrgDiagramNodeTest : public QObject {
    Q_OBJECT

  public:
    struct Scope {
        org::imm::ImmAstContext::Ptr context;
        Scope() : context{org::imm::ImmAstContext::init_start_context()} {}

        org::imm::ImmAstVersion getAdapter(std::string const& text) {
            auto parsed = org::parseString(text);
            return context->addRoot(parsed);
        }
    };


  private slots:
    void testTreeConstruction() {
        Scope s;
        auto  v1           = s.getAdapter("* document level");
        auto  tree_context = DiagramTreeNode::Context::shared();
        auto  tree         = DiagramTreeNode::FromDocument(
            tree_context, v1.getRootAdapter().as<org::imm::ImmDocument>());
    }

    void testTreeEditRemove() {
        auto  __scope      = trackTestExecution(this);
        auto  tree_context = DiagramTreeNode::Context::shared();
        Scope s;
        auto  v1   = s.getAdapter(R"(
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
        auto  conf = org::imm::ImmAdapter::TreeReprConf::getDefault();
        conf.with_field(&org::imm::ImmSubtree::properties);
        HSLOG_INFO(
            "test", v1.getRootAdapter().treeRepr(conf).toString(false));
        auto canvas = DiagramTreeNode::FromDocument(
            tree_context, v1.getRootAdapter().as<org::imm::ImmDocument>());
        QVERIFY(canvas->as<DiagramTreeNodeCanvas>() != nullptr);
        QCOMPARE_EQ2(canvas->uniq().id.getKind(), OrgSemKind::Document);
        auto layer = canvas->subnodes.at(0);
        QCOMPARE_EQ2(layer->uniq().id.getKind(), OrgSemKind::Subtree);
        QCOMPARE_EQ2(
            layer->id.as<org::imm::ImmSubtree>().getCleanTitle(),
            "diagram layer"_ss);
        auto item1 = layer->subnodes.at(0);
        QCOMPARE_EQ2(
            item1->id.as<org::imm::ImmSubtree>().getCleanTitle(),
            "layer item 1"_ss);
        auto item2 = layer->subnodes.at(1);
        QCOMPARE_EQ2(
            item2->id.as<org::imm::ImmSubtree>().getCleanTitle(),
            "layer item 2"_ss);

        auto item1_node = item1->as<DiagramTreeNodeItem>();
        QVERIFY(item1_node != nullptr);
        auto item2_node = item2->as<DiagramTreeNodeItem>();
        QVERIFY(item2_node != nullptr);

        QCOMPARE_EQ2(item1_node->getPos().x, 12);
        QCOMPARE_EQ2(item1_node->getPos().y, 30);
        QCOMPARE_EQ(item2_node->getPos().x, 12);
        QCOMPARE_EQ(item2_node->getPos().y, 90);
    }
};

HAXORG_QT_TEST_MAIN(OrgDiagramNodeTest)
#include "tOrgDiagramNodeTest.moc"
