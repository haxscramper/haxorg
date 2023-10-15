import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Coverage Table Display"

    TableView {
        anchors.fill: parent
        model: tableModel
        delegate: Rectangle {
            implicitHeight: 20
            Text {
                text: display
            }
        }
    }
}
