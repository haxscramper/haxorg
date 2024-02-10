#!/usr/bin/env python

from PySide6.QtWidgets import QApplication
from PySide6.QtQml import QQmlApplicationEngine
from PySide6.QtCore import QUrl
import sys
import os
import py_haxorg.pyhaxorg as org

app = QApplication(sys.argv)

engine = QQmlApplicationEngine()

ctx = org.OrgContext()
node = ctx.parseFile("/home/haxscramper/tmp/doc1.org")
print(node)
exp = org.OrgExporterTree()
opts = org.ExporterTreeOpts()
opts.withColor = False
text = exp.toString(node, opts)
engine.rootContext().setContextProperty("initialText", text.replace("\n", "<br/>"))


qml_file_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'org_editor.qml')
engine.load(QUrl.fromLocalFile(qml_file_path))

if not engine.rootObjects():
    sys.exit(-1)


sys.exit(app.exec())
