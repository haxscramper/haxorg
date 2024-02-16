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

        TreeView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: documentModel
            id: treeView

            Component.onCompleted: {
                treeView.expandRecursively(-1, -1)
            }

            delegate: Item {
                id: treeItem
                implicitHeight: itemRow.height
                implicitWidth: itemRow.width

                readonly property real indent: 20
                readonly property real padding: 5

                // Assigned to by TreeView:
                required property TreeView treeView
                required property bool isTreeNode
                required property bool expanded
                required property int hasChildren
                required property int depth

                RowLayout {
                    id: itemRow
                    x: padding

                    Text {
                        id: indicator
                        visible: treeItem.isTreeNode && treeItem.hasChildren
                        anchors.verticalCenter: label.verticalCenter
                        text: "▸"
                        rotation: treeItem.expanded ? 90 : 0
                        TapHandler {
                            onTapped: treeView.toggleExpanded(row)
                        }
                    }

                    Loader {
                        id: nodeEdit
                        sourceComponent: model.kind === "Paragraph" ? edit : label;
                    }

                    Component {
                        id: label
                        RowLayout {
                            Text {
                                text: Array(model.data.level + 1).join("*")
                            }
                            Text {
                                width: 400
                                clip: true
                                text: model.data.title.getRichText()
                                textFormat: Text.RichText
                                wrapMode: TextEdit.WordWrap
                            }
                        }
                    }

                    Component {
                        id: edit
                        ParagraphEditor {
                            textWidth: window.width - 50
                            modelData: model.data
                            onGeometryChanged: {
                                treeView.forceLayout()
                            }
                        }
                    }
                }
            }
        }
    }
}
