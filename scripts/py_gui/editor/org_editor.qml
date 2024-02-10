import QtQuick

Window {
    width: 600
    height: 400
    visible: true

    TextEdit {
        width: 240
        textFormat: TextEdit.RichText
        text: initialText
        font.family: "Helvetica"
        font.pointSize: 20
        focus: true
        id: test_text_edit
    }
}
