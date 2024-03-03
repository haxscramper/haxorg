from hypothesis import strategies as st
from hypothesis import given
import py_haxorg.pyhaxorg_wrap as org
from dataclasses import dataclass, replace, field
from beartype import beartype
from beartype.typing import List, Optional, Union
import itertools
from py_scriptutils.script_logging import log


@beartype
@dataclass
class OrgGenOptions():
    minSubnodeCount: int = 1
    maxSubnodeCount: Optional[int] = None
    minAttachedCount: int = 0
    maxAttachedCount: int = 0
    maxRecursionDepth: Optional[int] = 16
    enableTrace: bool = False


@beartype
@dataclass
class OrgGenPath:
    kind: org.OrgSemKind


osk = org.OrgSemKind


@beartype
@dataclass
class OrgGenCtx():
    opts: OrgGenOptions = field(default_factory=lambda: OrgGenOptions())
    steps: List[OrgGenPath] = field(default_factory=list)

    def count(self, kind: org.OrgSemKind) -> int:
        return len(list(filter(lambda it: it.kind == kind, self.steps)))

    def isAtRecursionLimit(self) -> bool:
        return self.opts.maxRecursionDepth <= len(self.steps)

    def getMaxSubnodeCount(self) -> int:
        return 0 if self.isAtRecursionLimit() else self.opts.maxSubnodeCount

    def getMinSubnodeCount(self) -> int:
        return 0 if self.isAtRecursionLimit() else self.opts.minSubnodeCount

    def rec(self, arg: Union[org.OrgSemKind, OrgGenOptions, OrgGenPath]) -> 'OrgGenCtx':
        match arg:
            case org.OrgSemKind():
                return replace(self, steps=self.steps + [OrgGenPath(kind=arg)])

            case OrgGenPath():
                return replace(self, steps=self.steps + [arg])

            case OrgGenOptions():
                return replace(self, opts=arg)

    def withRelativeRecursionLimit(self, max: int) -> 'OrgGenCtx':
        limit = len(self.steps) + max
        if self.opts.maxRecursionDepth and self.opts.maxRecursionDepth < limit:
            limit = self.opts.maxRecursionDepth

        return self.rec(replace(self.opts, maxRecursionDepth=limit))

    def withSubnodes(self, min: int, max: int) -> 'OrgGenCtx':
        return self.rec(replace(
            self.opts,
            maxSubnodeCount=max,
            minSubnodeCount=min,
        ))

    def withoutAttached(self) -> 'OrgGenCtx':
        return self.rec(replace(
            self.opts,
            minAttachedCount=0,
            maxAtachedCount=0,
        ))

    def getSubnodeSet(self) -> list[org.OrgSemKind]:
        if len(self.steps) == 0:
            return [osk.Document]

        result = set(it for it in org.OrgSemKind.Document.__iter__())
        markupLayerCount = 0
        markupKinds = org.SemSet([
            osk.Bold,
            osk.Italic,
            osk.Verbatim,
            osk.Monospace,
            osk.Underline,
            osk.Strike,
        ])

        result = result - set([
            osk.FileTarget,
            osk.CmdArgument,
            osk.CmdArguments,
            osk.ParseError,
            osk.DocumentOptions,
            osk.Empty,
            osk.SubtreeLog,
            osk.Par,
            osk.Row,
            osk.Cell,
            osk.MarkQuote,
            osk.ListItem,
            osk.DocumentGroup,
        ])

        for step in self.steps:
            if step.kind in markupKinds:
                markupLayerCount += 1

        if 2 <= markupLayerCount:
            result = result - markupKinds

        if self.count(osk.List):
            result.remove(osk.List)

        if self.isAtRecursionLimit():
            result = result - set(
                osk.Footnote,
                osk.Link,
                osk.Symbol,
                osk.TimeRange,
                osk.HashTag,
            )

        for step in self.steps:
            result.remove(step.kind)
            match step.kind:
                case osk.Paragraph:
                    result = result - set(
                        osk.Example,
                        osk.Center,
                        osk.Subtree,
                        osk.Code,
                        osk.CommandGroup,
                        osk.Quote,
                        osk.AdmonitionBlock,
                        osk.Table,
                        osk.TextSeparator,
                        osk.Export,
                        osk.List,
                        osk.Caption,
                        osk.Include,
                        osk.StmtList,
                        # Paragraph can contain newlines, but they are not
                        # arbitrarily generated.
                        osk.Newline,
                    )

        return sorted(result, key=lambda it: it.value)

    def getSubnodeStrategy(self) -> st.SearchStrategy:
        return st.sampled_from(self.getSubnodeSet())


@st.composite
def build_subnodes(draw: st.DrawFn, ctx: OrgGenCtx):
    return st.lists(
        node_strategy(ctx=ctx),
        min_size=ctx.getMinSubnodeCount(),
        max_size=ctx.getMaxSubnodeCount(),
    )


@st.composite
def build_Document(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(
        st.builds(
            org.Document,
            subnodes=draw(build_subnodes(ctx=ctx.rec(osk.Document).withSubnodes(3, 10))),
        ))


@st.composite
def build_StmtList(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.StmtList, subnodes=draw(build_subnodes(ctx=ctx))))


@st.composite
def build_Table(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Table))


@st.composite
def build_HashTag(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.HashTag))


@st.composite
def build_Footnote(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Footnote))


@st.composite
def build_Completion(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Completion))


@st.composite
def build_Paragraph(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Paragraph))


@st.composite
def build_Center(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Center))


@st.composite
def build_Caption(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Caption))


@st.composite
def build_StmtList(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.StmtList))


@st.composite
def build_Empty(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Empty))


@st.composite
def build_Cell(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Cell))


@st.composite
def build_Row(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Row))


@st.composite
def build_Table(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Table))


@st.composite
def build_HashTag(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.HashTag))


@st.composite
def build_Footnote(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Footnote))


@st.composite
def build_Completion(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Completion))


@st.composite
def build_Paragraph(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Paragraph))


@st.composite
def build_Center(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Center))


@st.composite
def build_Caption(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Caption))


@st.composite
def build_CmdName(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.CmdName))


@st.composite
def build_CmdResults(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.CmdResults))


@st.composite
def build_CommandGroup(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.CommandGroup))


@st.composite
def build_Tblfm(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Tblfm))


@st.composite
def build_Quote(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Quote))


@st.composite
def build_Verse(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Verse))


@st.composite
def build_Example(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Example))


@st.composite
def build_CmdArguments(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.CmdArguments))


@st.composite
def build_CmdAttr(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.CmdAttr))


@st.composite
def build_CmdArgument(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.CmdArgument))


@st.composite
def build_Export(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Export))


@st.composite
def build_AdmonitionBlock(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.AdmonitionBlock))


@st.composite
def build_Call(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Call))


@st.composite
def build_Code(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Code))


@st.composite
def build_Time(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Time))


@st.composite
def build_TimeRange(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.TimeRange))


@st.composite
def build_Macro(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Macro))


@st.composite
def build_Symbol(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Symbol))


@st.composite
def build_SubtreeLog(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.SubtreeLog))


@st.composite
def build_Subtree(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Subtree))


@st.composite
def build_InlineMath(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.InlineMath))


@st.composite
def build_Escaped(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Escaped))


@st.composite
def build_Newline(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Newline))


@st.composite
def build_Space(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Space))


@st.composite
def build_Word(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Word))


@st.composite
def build_AtMention(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.AtMention))


@st.composite
def build_RawText(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.RawText))


@st.composite
def build_Punctuation(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Punctuation))


@st.composite
def build_Placeholder(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Placeholder))


@st.composite
def build_BigIdent(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.BigIdent))


@st.composite
def build_Bold(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Bold))


@st.composite
def build_Underline(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Underline))


@st.composite
def build_Monospace(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Monospace))


@st.composite
def build_MarkQuote(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.MarkQuote))


@st.composite
def build_Verbatim(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Verbatim))


@st.composite
def build_Italic(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Italic))


@st.composite
def build_Strike(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Strike))


@st.composite
def build_Par(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Par))


@st.composite
def build_List(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.List))


@st.composite
def build_ListItem(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.ListItem))


@st.composite
def build_Link(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Link))


@st.composite
def build_DocumentOptions(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.DocumentOptions))


@st.composite
def build_ParseError(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.ParseError))


@st.composite
def build_FileTarget(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.FileTarget))


@st.composite
def build_TextSeparator(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.TextSeparator))


@st.composite
def build_Include(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Include))


@st.composite
def build_DocumentGroup(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.DocumentGroup))


@st.composite
def node_strategy(draw, ctx: OrgGenCtx):
    item = draw(ctx.getSubnodeStrategy())
    match item:
        case osk.StmtList:
            return draw(build_StmtList(ctx=ctx))
        case osk.Empty:
            return draw(build_Empty(ctx=ctx))
        case osk.Cell:
            return draw(build_Cell(ctx=ctx))
        case osk.Row:
            return draw(build_Row(ctx=ctx))
        case osk.Table:
            return draw(build_Table(ctx=ctx))
        case osk.HashTag:
            return draw(build_HashTag(ctx=ctx))
        case osk.Footnote:
            return draw(build_Footnote(ctx=ctx))
        case osk.Completion:
            return draw(build_Completion(ctx=ctx))
        case osk.Paragraph:
            return draw(build_Paragraph(ctx=ctx))
        case osk.Center:
            return draw(build_Center(ctx=ctx))
        case osk.Caption:
            return draw(build_Caption(ctx=ctx))
        case osk.CmdName:
            return draw(build_CmdName(ctx=ctx))
        case osk.CmdResults:
            return draw(build_CmdResults(ctx=ctx))
        case osk.CommandGroup:
            return draw(build_CommandGroup(ctx=ctx))
        case osk.Tblfm:
            return draw(build_Tblfm(ctx=ctx))
        case osk.Quote:
            return draw(build_Quote(ctx=ctx))
        case osk.Verse:
            return draw(build_Verse(ctx=ctx))
        case osk.Example:
            return draw(build_Example(ctx=ctx))
        case osk.CmdArguments:
            return draw(build_CmdArguments(ctx=ctx))
        case osk.CmdAttr:
            return draw(build_CmdAttr(ctx=ctx))
        case osk.CmdArgument:
            return draw(build_CmdArgument(ctx=ctx))
        case osk.Export:
            return draw(build_Export(ctx=ctx))
        case osk.AdmonitionBlock:
            return draw(build_AdmonitionBlock(ctx=ctx))
        case osk.Call:
            return draw(build_Call(ctx=ctx))
        case osk.Code:
            return draw(build_Code(ctx=ctx))
        case osk.Time:
            return draw(build_Time(ctx=ctx))
        case osk.TimeRange:
            return draw(build_TimeRange(ctx=ctx))
        case osk.Macro:
            return draw(build_Macro(ctx=ctx))
        case osk.Symbol:
            return draw(build_Symbol(ctx=ctx))
        case osk.SubtreeLog:
            return draw(build_SubtreeLog(ctx=ctx))
        case osk.Subtree:
            return draw(build_Subtree(ctx=ctx))
        case osk.InlineMath:
            return draw(build_InlineMath(ctx=ctx))
        case osk.Escaped:
            return draw(build_Escaped(ctx=ctx))
        case osk.Newline:
            return draw(build_Newline(ctx=ctx))
        case osk.Space:
            return draw(build_Space(ctx=ctx))
        case osk.Word:
            return draw(build_Word(ctx=ctx))
        case osk.AtMention:
            return draw(build_AtMention(ctx=ctx))
        case osk.RawText:
            return draw(build_RawText(ctx=ctx))
        case osk.Punctuation:
            return draw(build_Punctuation(ctx=ctx))
        case osk.Placeholder:
            return draw(build_Placeholder(ctx=ctx))
        case osk.BigIdent:
            return draw(build_BigIdent(ctx=ctx))
        case osk.Bold:
            return draw(build_Bold(ctx=ctx))
        case osk.Underline:
            return draw(build_Underline(ctx=ctx))
        case osk.Monospace:
            return draw(build_Monospace(ctx=ctx))
        case osk.MarkQuote:
            return draw(build_MarkQuote(ctx=ctx))
        case osk.Verbatim:
            return draw(build_Verbatim(ctx=ctx))
        case osk.Italic:
            return draw(build_Italic(ctx=ctx))
        case osk.Strike:
            return draw(build_Strike(ctx=ctx))
        case osk.Par:
            return draw(build_Par(ctx=ctx))
        case osk.List:
            return draw(build_List(ctx=ctx))
        case osk.ListItem:
            return draw(build_ListItem(ctx=ctx))
        case osk.Link:
            return draw(build_Link(ctx=ctx))
        case osk.DocumentOptions:
            return draw(build_DocumentOptions(ctx=ctx))
        case osk.Document:
            return draw(build_Document(ctx=ctx))
        case osk.ParseError:
            return draw(build_ParseError(ctx=ctx))
        case osk.FileTarget:
            return draw(build_FileTarget(ctx=ctx))
        case osk.TextSeparator:
            return draw(build_TextSeparator(ctx=ctx))
        case osk.Include:
            return draw(build_Include(ctx=ctx))
        case osk.DocumentGroup:
            return draw(build_DocumentGroup(ctx=ctx))
        case _:
            assert False, item


@given(node_strategy(OrgGenCtx()))
def test_render(doc: org.Document):
    ctx = org.OrgContext()
    tree = org.OrgExporterTree()
    log("t").info("---------------------")
    log("t").info(tree.toString(doc, org.ExporterTreeOpts()))
    log("t").info("---------------------")

    result = ctx.formatToString(doc)


if __name__ == "__main__":
    test_render()
