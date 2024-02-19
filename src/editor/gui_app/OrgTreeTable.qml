import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import org_editor_lib
import OrgQml

Window {
    id: window
    visible: true
    visibility: "FullScreen"
    width: 640
    height: 480

    OrgBackend {
        id: mainDocument
        Component.onCompleted: {
            mainDocument.parseDocumentFile("/home/haxscramper/workspace/repos/fic/ordered.org");
            loader.forceActiveFocus()
        }
    }

    Loader {
        id: loader
        anchors.fill: parent
        sourceComponent: mainDocument.hasDocument ? view : empty
    }

    Component {
        id: empty
        Text {
            text: "loadi asdfas fas dfng ..."
        }
    }

    Component {
        id: view
        ScrollView {
            clip: true
            Layout.leftMargin: 5
            Layout.fillWidth: true
            Layout.fillHeight: true

            TreeView {
                model: mainDocument.getOutlineModel()
                id: treeView
                rowSpacing: 1

                Component.onCompleted: {
                    treeView.expandRecursively(-1, -1)
                    treeView.forceLayout()
                }

                delegate: RowLayout {
                    id: treeItem
                    required property TreeView treeView
                    required property bool isTreeNode
                    required property bool expanded
                    required property int hasChildren
                    required property int depth


                    Rectangle {
                        width: 20
                        Text {
                            id: indicator
                            visible: treeItem.isTreeNode && treeItem.hasChildren
                            text: "▸"
                            font.pixelSize: 16
                            rotation: treeItem.expanded ? 90 : 0
                            TapHandler {
                                onTapped: treeView.toggleExpanded(row)
                            }
                        }
                    }



                    Rectangle {
                        width: 60
                        Text {
                            font.pixelSize: 16
                            text: Array(model.data.level + 1).join("*")
                        }
                    }

                    Rectangle {
                        width: 400
                        height: 20
                        clip: true
                        Text {
                            wrapMode: Text.WrapAnywhere
                            text: model.data.title.getRichText()
                        }
                    }
                }
            }
        }
    }
}
