import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

RowLayout {
    property var backend: null
    Layout.fillWidth: true
    Layout.fillHeight: true
    ColumnLayout {
        width: 200
        Layout.fillHeight: true
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            TreeView {
                model: backend.getOutlineModel()
                id: subtreeView
                delegate: Item {
                    implicitHeight: 20
                    RowLayout {
                        Text {
                            text: Array(model.data.level + 1).join("*") + " "
                        }

                        Text {
                            text: model.data.title.getRichText()
                            wrapMode: Text.WrapAnywhere
                            width: 180
                        }
                    }
                }

                Component.onCompleted: {
                    subtreeView.expandRecursively(-1, -1)
                    subtreeView.forceLayout()
                }
            }
        }
    }

    ColumnLayout {
        Layout.fillWidth: true
        Layout.fillHeight: true
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
            Layout.leftMargin: 5
            Layout.fillWidth: true
            Layout.fillHeight: true

            TreeView {
                model: backend.getDocumentModel()
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
