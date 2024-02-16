import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
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
            font.pixelSize: 16
            rotation: treeItem.expanded ? 90 : 0
            TapHandler {
                onTapped: treeView.toggleExpanded(row)
            }
        }

        Loader {
            id: nodeSelect

            function getSourceComponent() {
                if (model.kind === "Paragraph") {
                    return edit;
                } else if (model.kind === "Subtree") {
                    return label;
                } else {
                    return unknown;
                }
            }

            height: sourceComponent.height
            sourceComponent: getSourceComponent()
        }

        Component {
            id: unknown
            RowLayout {
                Text {
                    width: 400
                    clip: true
                    font.pixelSize: 16
                    text: model.kind
                    textFormat: Text.RichText
                    wrapMode: TextEdit.WordWrap
                }
            }
        }

        Component {
            id: label
            RowLayout {
                Text {
                    text: Array(model.data.level + 1).join("*")
                    font.pixelSize: 16
                }
                Text {
                    width: 400
                    clip: true
                    font.pixelSize: 16
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
