#include "src/model/QtOrgAstModel.hpp"
#include <QTest>
#include <src/model/HistoryManager.hpp>
#include <src/utils/common.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"


class DebugTarget : public QObject {
  public:
    org::imm::ImmUniqId getId(int i) const {
        return org::imm::ImmUniqId{org::imm::ImmId(OrgSemKind::Space, 0)};
    }

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

    void run_thing() {
        auto            root = createTestTree();
        OrgDiagramModel model{root};

        QModelIndex invalidIndex = model.index(0, 1);
        QVERIFY(!invalidIndex.isValid());
    }
};

int main() {
    DebugTarget dt;
    dt.run_thing();
}
