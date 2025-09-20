#include <src/gui/DiaScene.hpp>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <src/gui/DiaSceneItemModel.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>

using namespace test;

class DiaSceneItemModelTest : public QObject {
    Q_OBJECT

  private slots:
    void testTrivialSwitch() {
        auto              __scope = trackTestExecution(this);
        ScopeV12ItemModel scope{
            makeLayerText(
                DiaNodeLayerParams{}, hstd::Vec{ditem(2, "item 1")}),
            makeLayerText(
                DiaNodeLayerParams{}, hstd::Vec{ditem(2, "item 1")}),
        };
        visualizeTestDiff(this, scope);
        HSLOG_INFO(_cat, printModelTree(&scope.model).toString(false));

        hstd::log::SignalDebugger signalCatcher{
            get_tracker(), &scope.model};

        scope.scene.setRootAdapter(scope.srcAdapter);
        scope.scene.resetRootAdapter(scope.edits);
    }


    void testOneItemDelete() {
        auto __scope = trackTestExecution(this);

        ScopeV12UpdateTest s{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                    ditem(2, "item 2"),
                }),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                }),
        };

        visualizeTestDiff(this, s);
        s.setV1();

        QCOMPARE_EQ2(s.model.rowCount(), 1);
        QCOMPARE_EQ2(s.model.rowCount(s.indexAt({0})), 2);
        QCOMPARE_EQ2(
            s.itemViaIndexAt({0, 0})->name.toStdString(), "item 1"_ss);
        QCOMPARE_EQ2(
            s.itemViaIndexAt({0, 1})->name.toStdString(), "item 2"_ss);

        QPersistentModelIndex rootIndex;

        QSignalSpy deleteSpy{&s.model, &QAbstractItemModel::rowsRemoved};
        QSignalSpy updateSpy{&s.model, &QAbstractItemModel::dataChanged};

        s.setV2();

        QCOMPARE_EQ2(s.model.rowCount(), 1);
        QCOMPARE_EQ2(s.model.rowCount(s.indexAt({0})), 1);
        QCOMPARE_EQ2(
            s.itemViaIndexAt({0, 0})->name.toStdString(), "item 1"_ss);

        QCOMPARE_EQ2(deleteSpy.count(), 1);
        QCOMPARE_EQ2(updateSpy.count(), 2);

        // Test delete triggered on item2Index
        QList<QVariant> deleteArgs = deleteSpy.takeFirst();
        QModelIndex deleteParent   = deleteArgs.at(0).value<QModelIndex>();
        int         deleteFirst    = deleteArgs.at(1).toInt();
        int         deleteLast     = deleteArgs.at(2).toInt();
        QCOMPARE(deleteFirst, 1);
        QCOMPARE(deleteLast, 1);

        // Test first update triggered on s.indexAt({0})
        QList<QVariant> update1Args    = updateSpy.at(0);
        QModelIndex     update1TopLeft = update1Args.at(0)
                                         .value<QModelIndex>();
        QModelIndex update1BottomRight = update1Args.at(1)
                                             .value<QModelIndex>();
        QCOMPARE(update1TopLeft, s.indexAt({0}));
        QCOMPARE(update1BottomRight, s.indexAt({0}));

        // Test second update triggered on rootIndex
        QList<QVariant> update2Args    = updateSpy.at(1);
        QModelIndex     update2TopLeft = update2Args.at(0)
                                         .value<QModelIndex>();
        QModelIndex update2BottomRight = update2Args.at(1)
                                             .value<QModelIndex>();
        QCOMPARE(update2TopLeft, rootIndex);
        QCOMPARE(update2BottomRight, rootIndex);
    }

    void testOneItemInsert() {
        auto __scope = trackTestExecution(this);

        ScopeV12UpdateTest scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                }),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                    ditem(2, "item 2"),
                }),
        };

        visualizeTestDiff(this, scope);
        scope.setV1();

        QCOMPARE_EQ2(scope.model.rowCount(), 1);
        QCOMPARE_EQ2(scope.model.rowCount(scope.indexAt({0})), 1);
        QCOMPARE_EQ2(
            scope.itemViaIndexAt({0, 0})->name.toStdString(), "item 1"_ss);

        QSignalSpy insertSpy{
            &scope.model, &QAbstractItemModel::rowsInserted};
        QSignalSpy updateSpy{
            &scope.model, &QAbstractItemModel::dataChanged};

        scope.setV2();

        QCOMPARE_EQ2(scope.model.rowCount(), 1);
        QCOMPARE_EQ2(scope.model.rowCount(scope.indexAt({0})), 2);
        QCOMPARE_EQ2(
            scope.itemViaIndexAt({0, 0})->name.toStdString(), "item 1"_ss);
        QCOMPARE_EQ2(
            scope.itemViaIndexAt({0, 1})->name.toStdString(), "item 2"_ss);

        QCOMPARE_EQ2(insertSpy.count(), 1);
        QCOMPARE_EQ2(updateSpy.count(), 2);

        // Test insert triggered at position 1 in layer
        QList<QVariant> insertArgs  = insertSpy.takeFirst();
        int             insertFirst = insertArgs.at(1).toInt();
        int             insertLast  = insertArgs.at(2).toInt();
        QCOMPARE(insertFirst, 1);
        QCOMPARE(insertLast, 1);

        // Test first update triggered on layer
        QList<QVariant> update1Args    = updateSpy.at(0);
        QModelIndex     update1TopLeft = update1Args.at(0)
                                         .value<QModelIndex>();
        QModelIndex update1BottomRight = update1Args.at(1)
                                             .value<QModelIndex>();
        QCOMPARE(update1TopLeft, scope.indexAt({0}));
        QCOMPARE(update1BottomRight, scope.indexAt({0}));

        // Test second update triggered on root
        QList<QVariant> update2Args    = updateSpy.at(1);
        QModelIndex     update2TopLeft = update2Args.at(0)
                                         .value<QModelIndex>();
        QModelIndex update2BottomRight = update2Args.at(1)
                                             .value<QModelIndex>();
        QCOMPARE(update2TopLeft, QModelIndex{});
        QCOMPARE(update2BottomRight, QModelIndex{});
    }

    void testOneItemSwap() {
        auto __scope = trackTestExecution(this);

        ScopeV12UpdateTest scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                    ditem(2, "item 2"),
                }),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 2"),
                    ditem(2, "item 1"),
                }),
        };

        visualizeTestDiff(this, scope);
        scope.setV1();
        scope.setV2();
    }

    void testOneItemUpdate() {
        auto __scope = trackTestExecution(this);

        ScopeV12UpdateTest scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                    ditem(2, "item 2"),
                }),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                    ditem(2, "item 2-updated"),
                }),
        };

        visualizeTestDiff(this, scope);
        scope.setV1();
        scope.setV2();
    }

    void testStepByStepUpdates() {
        auto __scope = trackTestExecution(this);

        ScopeV12UpdateTest scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "leaf A1", {11, 11}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "leaf A3", {13, 13}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "leaf B1", {21, 11}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "leaf C1", {31, 11}),
                    ditem(4, "leaf C2", {32, 12}),
                    ditem(4, "leaf C3", {33, 13})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "leaf A1", {11, 11}),
                    ditem(4, "leaf B1", {21, 11}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "leaf C1", {31, 11}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "leaf A3", {13, 13}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(4, "leaf C2", {32, 12})}),
        };

        visualizeTestDiff(this, scope);
        scope.setV1();
        scope.setV2();
    }
};

HAXORG_QT_TEST_MAIN(DiaSceneItemModelTest)
#include "tDiaSceneItemModelTest.moc"
