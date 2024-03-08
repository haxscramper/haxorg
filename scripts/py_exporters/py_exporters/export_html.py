from beartype import beartype
import dominate
from dominate.util import text
import dominate.tags as tags
from py_exporters.export_base import ExporterBase
import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.script_logging import log
from py_haxorg.pyhaxorg_utils import formatDateTime

CAT = "haxorg.export.html"

def add_html(html, sub):
    if isinstance(sub, list):
        if isinstance(html, list):
            html.append(sub)

        else:
            for item in sub:
                html.add(item)

    else:
        if isinstance(html, list):
            html.append(sub)

        else:
            html.add(sub)

def add_new(html, sub):
    add_html(html, sub)
    return html

class ExporterHtml(ExporterBase):
    def __init__(self):
        super().__init__(self)

    def newOrg(self, node: org.Org) -> text:
        return text("TODO" + str(node.getKind()))
    
    def evalNewline(self, node: org.Newline) -> text:
        return text("\n")
    
    def evalBigIdent(self, node: org.BigIdent) -> text:
        return text(node.text)
    
    def evalPunctuation(self, node: org.Punctuation) -> text:
        return text(node.text)
    
    def evalHashTag(self, node: org.HashTag) -> text:
        def aux(sub: org.HashTag) -> str:
            if len(sub.subtags) == 0:
                return sub.head

            elif len(sub.subtags) == 1:
                return sub.head + "##" + aux(sub.subtags[0])
            
            else: 
                return sub.head + "##" + "[" + ",".join([aux(it) for it in sub.subtags]) + "]"


        return "#" + aux(node)


    
    def evalWord(self, node: org.Word) -> text:
        return text(node.text)
    
    def evalRawText(self, node: org.RawText) -> text:
        return text(node.text)

    def evalSpace(self, node: org.Space) -> text:
        return text(node.text)
    
    def evalTime(self, node: org.Time) -> text:
        return formatDateTime(node.getStatic().time)
    
    def evalBold(self, node: org.Bold) -> tags.b:
        res = tags.b()
        for sub in node:
            add_html(res, self.eval(sub))

        return res
    
    def evalVerbatim(self, node: org.Verbatim) -> tags.b:
        res = tags.b()
        for sub in node:
            add_html(res, self.eval(sub))

        return res

    def evalItalic(self, node: org.Italic) -> tags.i:
        res = tags.i()
        for sub in node:
            add_html(res, self.eval(sub))
            
        return res
    
    def evalParagraph(self, node: org.Paragraph):
        par = []
        for sub in node:
            add_html(par, self.eval(sub))

        return par
    
    def evalSubtree(self, node: org.Subtree):
        tree = None 

        match node.level:
            case 1: tree = tags.h1()
            case 2: tree = tags.h2()
            case 3: tree = tags.h3()
            case 4: tree = tags.h4()
            case 5: tree = tags.h5()
            case 6: tree = tags.h6()
            case _: tree = tags.b()

        tree.add(self.eval(node.title))

        result = [tree]
        for sub in node:
            add_html(result, self.eval(sub))

        return result
    
    def evalDocument(self, node: org.Subtree) -> dominate.document:
        doc = dominate.document()
        if node.title:
            log(CAT).info("Has title")
            doc.title = self.eval(node.title)

        for sub in node:
            add_html(doc, self.eval(sub))

        return doc
