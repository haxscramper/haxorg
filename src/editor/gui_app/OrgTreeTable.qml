import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import org_editor_lib
import OrgQml

Window {
    id: window
    width: 1500
    height: 1000
    visible: true

    OrgBackend {
        id: mainDocument
        Component.onCompleted: {
            mainDocument.parseDocumentFile("/home/haxscramper/workspace/repos/fic/ordered.org");
            loader.forceActiveFocus()
        }
    }

    Loader {
        id: loader
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
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            ScrollView {
                clip: true
                Layout.leftMargin: 5
                Layout.fillWidth: true
                Layout.fillHeight: true

                TreeView {
                    model: mainDocument.getOutlineModel()
                    id: treeView

                    Component.onCompleted: {
                        treeView.expandRecursively(-1, -1)
                        treeView.forceLayout()
                    }

                    delegate: Text {
                        text: model.kind
                    }
                }
            }
        }
    }
}
