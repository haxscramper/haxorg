#include <QtTest/QtTest>
#include <QSignalSpy>
#include <memory>
#include <src/model/QtOrgAstModel.hpp>
#include <src/utils/common.hpp>


class OrgDiagramNodeTest : public QObject {
    Q_OBJECT

  private slots:
};

HAXORG_QT_TEST_MAIN(OrgDiagramNodeTest)
#include "tOrgDiagramNodeTest.moc"
