import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Coverage Table Display"

    TableView {
        anchors.fill: parent
        model: tableModel

        TableViewColumn {
            title: "Line Text"
            role: "lineText"
            width: 300
        }

        TableViewColumn {
            title: "Test Names"
            role: "testNames"
            width: 300
        }

        TableViewColumn {
            title: "Counts"
            role: "counts"
            width: 200
        }
    }
}
