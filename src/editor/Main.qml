import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 1000
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
                        Text {
                            id: labelText
                            width: 400
                            clip: true
                            text: model.data.title
                            textFormat: Text.RichText
                            wrapMode: TextEdit.WordWrap
                        }
                    }

                    Component {
                        id: edit
                        Rectangle {
                            id: editRect
                            border.width: 2
                            border.color: "black"
                            height: textEdit.contentHeight + 2 * textEdit.padding
                            width: textEdit.width
                            TextEdit {
                                padding: 5
                                id: textEdit
                                text: model.rich.text
                                width: 500
                                font.pixelSize: 12
                                textFormat: TextEdit.RichText
                                wrapMode: TextEdit.WordWrap
                                property bool completed: false
                                onEditingFinished: {
                                    model.rich.text = textEdit.text
                                }

                                Component.onCompleted: {
                                    textEdit.completed = true;
                                }

                                onTextChanged: {
                                    if(textEdit.completed) {
                                        treeView.forceLayout();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
