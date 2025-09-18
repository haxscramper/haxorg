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

        void logModel() {
            HSLOG_INFO(_cat, printModelTree(&model).toString(false));
        }
    };

    struct ScopeV12UpdateTest : ScopeV12ItemModel {
        hstd::log::SignalDebugger signalCatcher;
        ScopeV12UpdateTest(std::string const& src, std::string const& dst)
            : ScopeV12ItemModel{src, dst}
            , signalCatcher{get_tracker(), &model} {}

        void setV1() {
            HSLOG_TRACE(_cat, "Scene root before setting the adapter");
            scene.logSceneRoot();
            scene.setRootAdapter(srcAdapter);
            HSLOG_TRACE(_cat, "Scene root after setting the adapter");
            scene.logSceneRoot();
        }
        void setV2() {
            scene.resetRootAdapter(dstAdapter, edits);
            HSLOG_TRACE(_cat, "Scene root after updating the adapter");
            scene.logSceneRoot();
        }
    };

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
        scope.scene.resetRootAdapter(scope.dstAdapter, scope.edits);
    }

    void testOneItemDelete() {
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
                }),
        };

        visualizeTestDiff(this, scope);
        scope.setV1();
        scope.setV2();
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
        scope.setV2();
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
};

HAXORG_QT_TEST_MAIN(DiaSceneItemModelTest)
#include "tDiaSceneItemModelTest.moc"
