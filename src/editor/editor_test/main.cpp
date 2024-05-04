#include "test_editor_model.hpp"


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    editorInitMain();

    TestEditorModel test;
    return QTest::qExec(&test, argc, argv);
}

#include "main.moc"
