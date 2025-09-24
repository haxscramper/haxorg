#include <src/model/DiaNodeTreeModel.hpp>
#include <QTest>
#include <src/model/DiaContextStore.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>
#include <QTimer>
#include <QSignalSpy>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"

using namespace test;

using S  = DiaContextStore;
using EC = S::EditCmd;

class DebugTarget : public QObject {
  public slots:
    void run_thing() {
        auto __scope = trackTestExecution(this);

        ScopeDiaContextEdits scope;

        auto res = scope.setText(makeLayerText(
            DiaNodeLayerParams{},
            hstd::Vec{
                ditem(2, "item 1"),
                ditem(2, "item 2"),
            }));

        DiaAdapter target = res.dia.at(0, true).at(0, true);
        QVERIFY(target.getKind() == DiaNodeKind::Item);

        scope.manager->applyDiaEdits(S::EditGroup{
            .edits = {EC{EC::RemoveDiaNode{
                .target = S::EditTarget{
                    S::EditTarget::Existing{.target = target.id}}}}}});


        QApplication::quit();
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    DebugTarget  dt;
    QTimer::singleShot(0, &dt, &DebugTarget::run_thing);
    return app.exec();
}
