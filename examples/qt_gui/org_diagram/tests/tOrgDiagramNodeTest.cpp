#include <QtTest/QtTest>
#include <QSignalSpy>
#include <haxorg/sem/SemBaseApi.hpp>
#include <src/model/QtOrgAstModel.hpp>
#include <src/utils/common.hpp>


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
        auto  v1   = s.getAdapter("* document level");
        auto  tree = DiagramTreeNode::FromDocument(
            v1.getRootAdapter().as<org::imm::ImmDocument>());
    }

    void testTreeEditRemove() {
        auto  __scope = trackTestExecution(this);
        Scope s;
        auto  v1 = s.getAdapter(R"(
* diagram layer
** layer item 1
    :properties:
    :haxorg_diagram_position: {"x": 12, "y": 30}
    :haxorg_diagram_node: :some-value t
    :end:
** layer item 2
    :properties:
    :haxorg_diagram_position: {"x": 12, "y": 90}
    :haxorg_diagram_node: :some-value t
    :end:
)");
        HSLOG_INFO("test", v1.getRootAdapter().treeRepr().toString(false));
        auto tree = DiagramTreeNode::FromDocument(
            v1.getRootAdapter().as<org::imm::ImmDocument>());
    }
};

HAXORG_QT_TEST_MAIN(OrgDiagramNodeTest)
#include "tOrgDiagramNodeTest.moc"
