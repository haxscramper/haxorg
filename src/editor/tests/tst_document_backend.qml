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
        var startCount = spy.count
        backend.parseDocumentFile("/home/haxscramper/tmp/doc1.org")
        compare(backend.hasDocument, true, "has document")
        compare(spy.count, startCount + 1, "has documents loaded at the start")
    }

    function test_document_from_string() {
        backend.parseDocumentString("*bold*")
        var doc = backend.getDocument()
        compare(doc.getKind(), "Document")
        compare(doc.size(), 1)
        compare(doc.at(0).getKind(), "Paragraph")
        compare(doc.at(0).size(), 1)
        var j = doc.getJson()
        compare(j.kind, "Document")
        comapre(j.subnodes.size(), 1)
    }
}
