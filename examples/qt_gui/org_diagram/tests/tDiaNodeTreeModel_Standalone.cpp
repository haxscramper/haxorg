#include <QtTest/QtTest>
#include <QSignalSpy>
#include <src/model/DiaNodeTreeModel.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>

using namespace test;

class DiaNodeTreeModelTest_Standalone : public QObject {
    Q_OBJECT

  private:
    struct ScopeV12QtModel : ScopeV12DiagramDiff {
        DiaNodeTreeModel model;
        ScopeV12QtModel(std::string const& src, std::string const& dst)
            : ScopeV12DiagramDiff{src, dst}, model{srcAdapter} {}
    };

  private slots:
    void testTrivialSwitch() {
        auto            __scope = trackTestExecution(this);
        ScopeV12QtModel scope{
            makeLayerText(
                DiaNodeLayerParams{}, hstd::Vec{ditem(2, "item 1")}),
            makeLayerText(
                DiaNodeLayerParams{}, hstd::Vec{ditem(2, "item 1")}),
        };
        visualizeTestDiff(this, scope);
        HSLOG_INFO(_cat, printModelTree(&scope.model).toString(false));
        scope.model.setNewRoot(scope.dstAdapter, scope.edits);
    }
};

HAXORG_QT_TEST_MAIN(DiaNodeTreeModelTest_Standalone)
#include "tDiaNodeTreeModel_Standalone.moc"
