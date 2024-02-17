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
            mainDocument.loadDocument("/home/haxscramper/tmp/doc1.org");
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
            text: "loading ..."
        }
    }

    Component {
        id: view
        DocumentView {
            backend: mainDocument
        }
    }
}
