#include <src/model/DiaNodeTreeModel.hpp>
#include <QTest>
#include <src/model/HistoryManager.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>
#include <QTimer>
#include <QSignalSpy>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"

using namespace test;

class DebugTarget : public QObject {
  public slots:
    void run_thing() {
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

        QApplication::quit();
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    DebugTarget  dt;
    QTimer::singleShot(0, &dt, &DebugTarget::run_thing);
    return app.exec();
}
