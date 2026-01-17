#include <QTest>
#include <haxorg/sem/SemBaseApi.hpp>
#include <qsignalspy.h>
#include <org_diagram/src/model/DiaVersionStore.hpp>
#include <org_diagram/src/utils/common.hpp>
#include <org_diagram/src/utils/test_utils.hpp>
#include <org_diagram/src/model/nodes/DiagramTreeNode.hpp>

#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"

using namespace test;

using S  = DiaVersionStore;
using EC = S::EditCmd;

class DiaContextStoreIncomingEditTest : public QObject {
    Q_OBJECT
  private slots:
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

    void testDiagramTreeUpdate() {
        auto                 __scope = trackTestExecution(this);
        ScopeDiaContextEdits scope;


        auto res = scope.setText(makeLayerText(
            DiaNodeLayerParams{},
            hstd::Vec{
                ditem(2, "item 1"),
                ditem(2, "item 2"),
                ditem(3, "item 2-nested"),
                ditem(3, "item 3-nested"),
            }));


        QCOMPARE_EQ2(scope.getActiveTitleAt({0, 1}), "item 2"_ss);
        QCOMPARE_EQ2(scope.getRootAtPath({0, 1}).size(), 2);
        QCOMPARE_EQ2(
            scope.getActiveTitleAt({0, 1, 0}), "item 2-nested"_ss);
        QCOMPARE_EQ2(
            scope.getActiveTitleAt({0, 1, 1}), "item 3-nested"_ss);

        QSignalSpy updateSpy{
            scope.version_store.get(), &DiaVersionStore::diaRootChanged};

        DiaAdapter target = res.dia.at(0, true).at(1, true);
        org::sem::SemId<org::sem::Subtree>
            item2Subtree = org::imm::sem_from_immer(
                               target.getImmAdapter().id,
                               *scope.imm_context)
                               .as<org::sem::Subtree>();

        org::sem::SemId<org::sem::Org> tmpDocument = org::parseString(
            "item updated", "<test>");

        org::sem::SemId<org::sem::Paragraph>
            tmpTitle = tmpDocument.at(0).as<org::sem::Paragraph>();

        item2Subtree->title = tmpTitle;

        QCOMPARE_EQ2(target.getKind(), DiaNodeKind::Item);

        scope.version_store->applyDiaEdits(
            S::EditGroup::UpdateExisting(target.uniq(), item2Subtree));

        QCOMPARE_EQ(updateSpy.count(), 1);

        QCOMPARE_EQ2(scope.getActiveTitleAt({0, 1}), "item updated"_ss);
        QCOMPARE_EQ2(scope.getRootAtPath({0, 1}).size(), 2);
        QCOMPARE_EQ2(
            scope.getActiveTitleAt({0, 1, 0}), "item 2-nested"_ss);
        QCOMPARE_EQ2(
            scope.getActiveTitleAt({0, 1, 1}), "item 3-nested"_ss);
    }

    void testDiagramTreeMove() {
        auto __scope = trackTestExecution(this);

        ScopeDiaContextEdits scope;

        scope.imm_context->debug->setTraceFile(
            getDebugFile(this, "imm_context_trace.log"));

        auto res = scope.setText(makeLayerText(
            DiaNodeLayerParams{},
            hstd::Vec{
                ditem(2, "item 1"),
                ditem(2, "item 2"),
                ditem(3, "item 3-0"),
                ditem(3, "item 3-1"),
            }));


        {
            auto root = scope.getRoot();
            QCOMPARE_EQ2(root.size(), 1);
            QCOMPARE_EQ2(root.at(0, true).size(), 1);
            QCOMPARE_EQ2(root.at(0, true).at(0, true).size(), 2);
        }

        QSignalSpy updateSpy{
            scope.version_store.get(), &DiaVersionStore::diaRootChanged};

        DiaAdapter target = res.dia.atPath({0, 0}, true);
        LOGIC_ASSERTION_CHECK(target.getKind() == DiaNodeKind::Item, "");

        scope.version_store->applyDiaEdits(
            S::EditGroup::MoveNodesUnderExisting(
                target.uniq(),
                hstd::Vec<DiaUniqId>{
                    res.dia.atPath({0, 1, 0}, true).uniq(),
                    res.dia.atPath({0, 1, 1}, true).uniq(),
                },
                0));

        QCOMPARE_EQ(updateSpy.count(), 1);

        {
            auto root = scope.getRoot();
            QCOMPARE_EQ2(root.size(), 1);
            QCOMPARE_EQ2(root.at(0, true).size(), 2);
            QCOMPARE_EQ2(root.at(0, true).at(0, true).size(), 2);
            QCOMPARE_EQ2(root.at(0, true).at(1, true).size(), 0);
        }
    }
};


HAXORG_QT_TEST_MAIN(DiaContextStoreIncomingEditTest)
#include "tDiaContextStoreIncomingEditTest.moc"
