#include <QTest>
#include <haxorg/sem/SemBaseApi.hpp>
#include <src/model/DiaVersionStore.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"

using namespace test;

using S  = DiaVersionStore;
using EC = S::EditCmd;

class DiaContextStoreIncomingEditTest : public QObject {
    Q_OBJECT
  public:
  public slots:
    void testDiagramTreeRemove() {
        auto                 __scope = trackTestExecution(this);
        ScopeDiaContextEdits scope;

        auto res = scope.setText(makeLayerText(
            DiaNodeLayerParams{},
            hstd::Vec{
                ditem(2, "item 1"),
                ditem(2, "item 2"),
            }));

        {
            auto root = scope.getRoot();
            QCOMPARE_EQ2(root.size(), 1);
            QCOMPARE_EQ2(root.at(0, true).size(), 1);
            QCOMPARE_EQ2(root.at(0, true).at(0, true).size(), 2);
        }

        DiaAdapter target = res.dia.at(0, true).at(0, true);
        QVERIFY(target.getKind() == DiaNodeKind::Item);
        scope.version_store->applyDiaEdits(S::EditGroup{
            .edits = {EC{EC::RemoveDiaNode{
                .target = S::EditTarget{
                    S::EditTarget::Existing{.target = target.id}}}}}});

        {
            auto root = scope.getRoot();
            QCOMPARE_EQ2(root.size(), 1);
            QCOMPARE_EQ2(root.at(0, true).size(), 1);
            QCOMPARE_EQ2(root.at(0, true).at(0, true).size(), 1);
        }
    }
};


HAXORG_QT_TEST_MAIN(DiaContextStoreIncomingEditTest)
#include "tDiaContextStoreIncomingEditTest.moc"
