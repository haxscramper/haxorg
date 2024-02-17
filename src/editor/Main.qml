import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: window
    width: 1500
    height: 1000
    visible: true

    RowLayout {
        anchors.fill: parent
        ColumnLayout {
            width: 200
            Layout.fillHeight: true
            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                TreeView {
                    model: sortedSubtree
                    id: subtreeView
                    delegate: Item {
                        implicitHeight: 20
                        Text {
                            text: Array(model.data.level + 1).join("*") + " " + model.data.title.getRichText()
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
}
