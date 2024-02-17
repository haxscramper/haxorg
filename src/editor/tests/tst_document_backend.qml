import org_editor_lib 1.0
import QtQuick 2.0
import QtTest 1.2
import OrgQml

TestCase {
    name: "Org backend loader"
    OrgBackend {
        id: backend
    }

    SignalSpy {
        id: spy
        target: backend
        signalName: "hasDocumentChanged"
    }

    function test_document_load() {
        compare(spy.count, 0, "no document loaded at the start")
        backend.loadDocument("/home/haxscramper/tmp/doc1.org")
        compare(backend.hasDocument, true, "has document")
        compare(spy.count, 1, "has documents loaded at the start")
    }
}
