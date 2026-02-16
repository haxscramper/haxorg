from py_haxorg.exporters import (
    export_html,
    export_pandoc,
    export_sqlite,
    export_typst,
    export_ultraplain,
    export_utils,
)
import py_haxorg.pyhaxorg_wrap as org

ctx = org.ParseContext()
node = ctx.parseString("*bold*", "<input>")
assert node.getKind() == org.OrgSemKind.Document
assert node[0].getKind() == org.OrgSemKind.Paragraph
