#include <src/model/DiaNodeTreeModel.hpp>
#include <QTest>
#include <src/model/DiaVersionStore.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>
#include <QTimer>
#include <QSignalSpy>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/exporters/exportertree.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"

using namespace test;

using S  = DiaVersionStore;
using EC = S::EditCmd;

class DebugTarget : public QObject {
  public slots:
    void run_thing() {
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
        QApplication::quit();
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    DebugTarget  dt;
    QTimer::singleShot(0, &dt, &DebugTarget::run_thing);
    return app.exec();
}
