#include <src/gui/DiaScene.hpp>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <src/gui/DiaSceneItemModel.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>

using namespace test;

class DiaSceneItemModelTest : public QObject {
    Q_OBJECT

  private:
    struct ScopeV12ItemModel : ScopeV12DiagramDiff {
        DiaSceneItemModel model;
        DiaScene          scene;
        ScopeV12ItemModel(std::string const& src, std::string const& dst)
            : ScopeV12DiagramDiff{src, dst}, scene{&model} {}
    };

  private slots:
    void testTrivialSwitch() {
        auto            __scope = trackTestExecution(this);
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
        scope.scene.resetRootAdapter(scope.dstAdapter, scope.edits);
    }

    void testItemDelete() {
        auto            __scope = trackTestExecution(this);

        ScopeV12ItemModel scope{
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

        visualizeTestDiff(this, scope);
        HSLOG_INFO(_cat, printModelTree(&scope.model).toString(false));

        hstd::log::SignalDebugger signalCatcher{
                                                get_tracker(), &scope.model};

        scope.scene.setRootAdapter(scope.srcAdapter);
        scope.scene.resetRootAdapter(scope.dstAdapter, scope.edits);
    }
};

HAXORG_QT_TEST_MAIN(DiaSceneItemModelTest)
#include "tDiaSceneItemModelTest.moc"
