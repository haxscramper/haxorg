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
                console.log("Component on complte");
                function expandAll(index) {
                    if (!index.isValid()) return;

                    const rowCount = treeView.model.rowCount(index);
                    for (let i = 0; i < rowCount; ++i) {
                        const childIndex = treeView.model.index(i, 0, index);
                        treeView.expand(childIndex);
                        expandAll(childIndex); // Recursively expand children
                    }
                }

                // Start the recursive expansion with the root index
                expandAll(treeView.rootIndex);
            }

            delegate: Item {
                id: tree_item
                implicitHeight: 20

                readonly property real indent: 20
                readonly property real padding: 5

                // Assigned to by TreeView:
                required property TreeView treeView
                required property bool isTreeNode
                required property bool expanded
                required property int hasChildren
                required property int depth

                RowLayout {
                    x: padding + (tree_item.isTreeNode ? (tree_item.depth + 1) * tree_item.indent : 0)
                    height: 20

                    Text {
                        id: indicator
                        visible: tree_item.isTreeNode && tree_item.hasChildren
                        anchors.verticalCenter: label.verticalCenter
                        text: "▸"
                        rotation: tree_item.expanded ? 90 : 0
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
                            width: tree_item.width - tree_item.padding - x
                            clip: true
                            text: model.kind
                            textFormat: Text.RichText
                        }
                    }

                    Component {
                        id: edit
                        TextEdit {
                            id: text_edit
                            width: tree_item.width - tree_item.padding - x
                            clip: true
                            text: model.rich.text
                            textFormat: TextEdit.RichText
                            onEditingFinished: {
                                model.rich.text = text_edit.text
                            }
                        }
                    }
                }
            }
        }
    }
}
