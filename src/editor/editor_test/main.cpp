#include <QtTest>


class GuiTest : public QObject {
    Q_OBJECT

  private slots:
    void testButtonClick() {}
};


QTEST_MAIN(GuiTest)
#include "main.moc"
