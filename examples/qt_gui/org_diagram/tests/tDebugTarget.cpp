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
                ditem(3, "item 2-nested"),
                ditem(3, "item 3-nested"),
            }));


        {
            auto root = scope.getRoot();
            QCOMPARE_EQ2(root.size(), 1);
            QCOMPARE_EQ2(root.at(0, true).size(), 1);
            QCOMPARE_EQ2(root.at(0, true).at(0, true).size(), 2);
        }

        QSignalSpy updateSpy{
            scope.version_store.get(), &DiaVersionStore::diaRootChanged};

        DiaAdapter target = res.dia.at(0, true).at(1, true);
        org::sem::SemId<org::sem::Subtree>
            item2Subtree = org::imm::sem_from_immer(
                               target.getImmAdapter().id,
                               *scope.imm_context)
                               .as<org::sem::Subtree>();

        org::sem::SemId<org::sem::Org> tmpDocument = org::parseString(
            "item updated");
        HSLOG_INFO(
            _cat,
            org::algo::ExporterTree::treeRepr(tmpDocument)
                .toString(false));
        org::sem::SemId<org::sem::Paragraph>
            tmpTitle = tmpDocument.at(0).as<org::sem::Paragraph>();

        item2Subtree->title = tmpTitle;

        LOGIC_ASSERTION_CHECK(target.getKind() == DiaNodeKind::Item, "");

        scope.version_store->applyDiaEdits(
            S::EditGroup::UpdateExisting(target.uniq(), item2Subtree));

        QCOMPARE_EQ(updateSpy.count(), 1);

        {
            auto root = scope.getRoot();
            _dbg(root.atPath({}, true).size());
            _dbg(root.atPath({0}, true).size());
            _dbg(root.atPath({0, 0}, true).size());
            _dbg(root.atPath({0, 1}, true).size());
            _dbg(root.atPath({0, 1, 0}, true).size());
            _dbg(root.atPath({0, 1, 1}, true).size());
            _dbg(root.atPath({0, 1}, true)
                     .getImmAdapter()
                     .as<org::imm::ImmSubtree>()
                     .getCleanTitle());
        }


        HSLOG_INFO(_cat, "done");
        QApplication::quit();
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    DebugTarget  dt;
    QTimer::singleShot(0, &dt, &DebugTarget::run_thing);
    return app.exec();
}
