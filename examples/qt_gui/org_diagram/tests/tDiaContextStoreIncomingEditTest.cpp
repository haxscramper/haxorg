#include <QTest>
#include <haxorg/sem/SemBaseApi.hpp>
#include <qsignalspy.h>
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

        QSignalSpy updateSpy{
            scope.version_store.get(), &DiaVersionStore::diaRootChanged};

        scope.version_store->applyDiaEdits(
            S::EditGroup::Remove1ExistingNode(target.id));

        QCOMPARE_EQ(updateSpy.count(), 1);

        {
            auto root = scope.getRoot();
            QCOMPARE_EQ2(root.size(), 1);
            QCOMPARE_EQ2(root.at(0, true).size(), 1);
            QCOMPARE_EQ2(root.at(0, true).at(0, true).size(), 1);
        }
    }

    void testDiagramTreeInsert() {
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

        QSignalSpy updateSpy{
            scope.version_store.get(), &DiaVersionStore::diaRootChanged};

        DiaAdapter target = res.dia.at(0, true);
        QVERIFY(target.getKind() == DiaNodeKind::Layer);

        scope.version_store->applyDiaEdits(
            S::EditGroup::Append1NewNode(target.uniq()));

        QCOMPARE_EQ(updateSpy.count(), 1);

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
