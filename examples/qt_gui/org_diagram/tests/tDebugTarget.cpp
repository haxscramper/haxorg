#include <src/model/DiaNodeTreeModel.hpp>
#include <QTest>
#include <src/model/HistoryManager.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>
#include <QTimer>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"

using namespace test;

class DebugTarget : public QObject {
  public slots:
    void run_thing() {
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

        QApplication::quit();
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    DebugTarget  dt;
    QTimer::singleShot(0, &dt, &DebugTarget::run_thing);
    return app.exec();
}
