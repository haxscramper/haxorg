import QtQuick

Item {
    height: rect.height + 5
    id: wrap

    property var modelData: null
    signal geometryChanged()
    property int textWidth: 500

    Rectangle {
        id: rect
        border.width: 1
        border.color: "gray"
        anchors.top: wrap.top
        height: textEdit.contentHeight + 2 * textEdit.padding
        width: textEdit.width
        radius: textEdit.padding


        TextEdit {
            padding: 5
            id: textEdit
            text: modelData.getRichText()
            width: textWidth
            font.pixelSize: 16
            textFormat: TextEdit.RichText
            wrapMode: TextEdit.WordWrap

            property int prevHeight: 0
            property bool completed: false

            onEditingFinished: {
                modelData.setRichText(textEdit.text)
            }

            Component.onCompleted: {
                textEdit.completed = true;
            }

            onContentHeightChanged: {
                if (prevHeight !== height) {
                    if(textEdit.completed) {
                        if(prevHeight !== 0) {
                            geometryChanged()
                            console.log(`Changed height from ${prevHeight} to ${height} textEdit.completed=${textEdit.completed}`)
                        }

                        prevHeight = height;
                    }
                }
            }
        }
    }

}

