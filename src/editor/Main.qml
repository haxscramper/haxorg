import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: window
    width: 1500
    height: 1000
    visible: true

    ColumnLayout {
        anchors.fill: parent
        Button {
            property int save_count: 0

            id: save_button
            Layout.preferredWidth: 200
            Layout.preferredHeight: 50
            text: "Save " + save_count
            onClicked: {
                ++save_count;
                backend.saveDocument();
            }
        }

        ScrollView {
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true

            TreeView {
                model: documentModel
                id: treeView

                Component.onCompleted: {
                    treeView.expandRecursively(-1, -1)
                    treeView.forceLayout()
                }

                delegate: DocumentItem {

                }
            }
        }
    }
}
