#include <QtTest/QtTest>
#include <QSignalSpy>
#include <org_diagram/src/model/layout/ElkLayoutManager.hpp>
#include <org_diagram/src/utils/common.hpp>

#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>


class DiaNodeLayout : public QObject {
    Q_OBJECT

  private slots:
    void testLayoutMultipleRuns() {}
};

HAXORG_QT_TEST_MAIN(DiaNodeLayout)
#include "tDiaNodeLayout.moc"
