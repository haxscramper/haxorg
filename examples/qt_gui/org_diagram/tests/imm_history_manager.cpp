#include <QTest>

class ImmHistoryManager : public QObject {
    Q_OBJECT
  private slots:
    void toUpper() {
        QString str = "Hello";
        QCOMPARE(str.toUpper(), QString("HELLO"));
    }
};

QTEST_MAIN(ImmHistoryManager)
#include "imm_history_manager.moc"
