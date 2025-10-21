#include <QtTest/QtTest>
#include <QSignalSpy>
#include <src/model/layout/ElkLayoutManager.hpp>
#include <src/utils/common.hpp>


class DiaNodeLayout : public QObject {
    Q_OBJECT

  private slots:
    void testLayoutMultipleRuns() {}
};

HAXORG_QT_TEST_MAIN(DiaNodeLayout)
#include "tDiaNodeLayout.moc"
