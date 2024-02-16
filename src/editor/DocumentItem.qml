import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: treeItem

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
            text: `${treeItem.height} ${itemRow.height} ${model.index}`
        }

        Rectangle {
            height: 10
            width: 10 * model.index
        }

        Rectangle {
            height: nodeSelect.height
            width: 10
            border.color: "red"
            border.width: 2
        }

        Loader {
            id: nodeSelect

            // Binding {
            //     target: treeItem
            //     property: "height"
            //     value: nodeSelect.sourceComponent.height
            //     when: nodeSelect.status == Loader.Ready
            // }

            onStatusChanged: {
                if (nodeSelect.status === Loader.Ready) {
                    console.log(`treeItem.height = ${treeItem.height} nodeSelect.item.height = ${nodeSelect.item.height}`)
                    treeItem.height = nodeSelect.item.height;
                    treeItem.heightChanged()
                }
            }

            sourceComponent: {
                if (model.kind === "Paragraph") {
                    return edit;
                } else if (model.kind === "Subtree") {
                    return label;
                } else {
                    return unknown;
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

                Text {
                    text: model.data.level ? Array(model.data.level + 1).join("*") : "?"
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
    }
}
