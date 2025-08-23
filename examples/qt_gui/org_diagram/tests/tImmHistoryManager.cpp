#include <QTest>
#include <src/model/HistoryManager.hpp>
#include <src/utils/common.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"


class ImmHistoryManager : public QObject {
    Q_OBJECT


  private slots:
    void fromRegularText() {
        HistoryManager manager;
        manager.setDocument("*bold*");
        manager.setDocument("/italic/");
    }

    void getSimpleDifference() {
        HistoryManager manager;
        manager.setDocument("word");
        manager.setDocument("word second");

    }
};

HAXORG_QT_TEST_MAIN(ImmHistoryManager)
#include "tImmHistoryManager.moc"
