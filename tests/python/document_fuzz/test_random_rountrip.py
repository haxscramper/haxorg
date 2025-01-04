from hypothesis import strategies as st
from hypothesis import given, settings, seed, HealthCheck
import py_haxorg.pyhaxorg_wrap as org
from dataclasses import dataclass, replace, field
from beartype import beartype
from beartype.typing import List, Optional, Union, Iterable
import itertools
from py_scriptutils.script_logging import log
import pytest

from py_exporters import export_ultraplain
from py_exporters import export_tex
from py_exporters import export_html
from tempfile import TemporaryDirectory
from pathlib import Path
import shutil

FILE = None


@beartype
@dataclass
class OrgGenOptions():
    minSubnodeCount: int = 1
    maxSubnodeCount: int = 8
    minAttachedCount: int = 0
    maxAttachedCount: int = 0
    maxRecursionDepth: Optional[int] = 8
    enableTrace: bool = False
    parentSubtree: int = 0


@beartype
@dataclass
class OrgGenPath:
    kind: org.OrgSemKind


osk = org.OrgSemKind

SET_MARKUP_KINDS = org.SemSet([
    osk.Bold,
    osk.Italic,
    osk.Verbatim,
    osk.Monospace,
    osk.Underline,
    osk.Strike,
])

SET_PARAGRAPH_KINDS = org.SemSet([
    osk.AtMention,
    osk.HashTag,
    osk.BigIdent,
    osk.Word,
    osk.Time,
    osk.TimeRange,
    osk.Link,
    osk.Macro,
    osk.Symbol,
    osk.Latex,
    osk.Escaped,
    osk.Placeholder,
    osk.Punctuation,
])

SET_COMMAND_KINDS = org.SemSet([
    osk.BlockCode,
    osk.BlockExport,
    osk.BlockCenter,
    osk.BlockExample,
    osk.BlockQuote,
    osk.CmdCaption,
    osk.BlockVerse,
])

SET_STMT_TOPLEVEL = org.SemSet([
    osk.Subtree,
    osk.Paragraph,
]).union(SET_COMMAND_KINDS)


@beartype
@dataclass
class OrgGenCtx():
    opts: OrgGenOptions = field(default_factory=lambda: OrgGenOptions())
    steps: List[OrgGenPath] = field(default_factory=list)

    def depth(self) -> int:
        return len(self.steps)

    def back(self) -> OrgGenPath:
        return self.steps[-1]

    def count(self, kind: org.OrgSemKind) -> int:
        return len(list(filter(lambda it: it.kind == kind, self.steps)))

    def isAtRecursionLimit(self) -> bool:
        return self.opts.maxRecursionDepth <= self.depth()

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

    def rec_update(self, **kwargs) -> 'OrgGenCtx':
        return replace(self, opts=replace(self.opts, **kwargs))

    def withRelativeRecursionLimit(self, max: int) -> 'OrgGenCtx':
        limit = self.depth() + max
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

        def order(it: Iterable[org.OrgSemKind]):
            return sorted(it, key=lambda it: it.value)

        if self.depth() == 0:
            return [osk.Document]

        elif self.back().kind == osk.Paragraph:
            return order(SET_PARAGRAPH_KINDS)

        elif self.back().kind == osk.Document:
            return order(SET_STMT_TOPLEVEL)

        elif 0 < self.count(osk.Paragraph):
            result = SET_PARAGRAPH_KINDS

            markupLayerCount = 0
            for step in self.steps:
                if step.kind in SET_MARKUP_KINDS:
                    markupLayerCount += 1

            if markupLayerCount <= 2:
                result += SET_MARKUP_KINDS

            return order(result)

        elif self.back().kind in [osk.Document, osk.ListItem, osk.Subtree]:
            return order(SET_STMT_TOPLEVEL)

        result = set(it for it in org.OrgSemKind.Document.__iter__())

        result = result - set([
            osk.FileTarget,
            osk.DocumentOptions,
            osk.Empty,
            osk.SubtreeLog,
            osk.Par,
            osk.Row,
            osk.Cell,
            osk.MarkQuote,
            osk.ListItem,
            osk.DocumentGroup,
            osk.BlockAdmonition,
            osk.Include,
            osk.CmdTblfm,
            osk.Call,
            osk.CmdResults,
            osk.Table,
            osk.StmtList,
        ]) - SET_COMMAND_KINDS

        if 3 <= self.count(osk.List):
            result.remove(osk.List)

        if self.isAtRecursionLimit():
            result = result - set(
                osk.InlineFootnote,
                osk.Link,
                osk.Symbol,
                osk.TimeRange,
                osk.HashTag,
            )

        for step in self.steps:
            if step.kind in result:
                result.remove(step.kind)

            match step.kind:
                case osk.Paragraph:
                    result = SET_PARAGRAPH_KINDS

        return order(result)

    def getSubnodeStrategy(self) -> st.SearchStrategy:
        kinds = self.getSubnodeSet()
        return st.sampled_from(kinds)


@st.composite
def build_subnodes(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(
        st.lists(
            node_strategy(ctx=ctx),
            min_size=ctx.getMinSubnodeCount(),
            max_size=ctx.getMaxSubnodeCount(),
        ))


def build_alnum_ident(**kwargs) -> st.SearchStrategy:
    return st.text(
        alphabet=st.one_of(st.characters(min_codepoint=65, max_codepoint=90),
                           st.characters(min_codepoint=97, max_codepoint=122)),
        min_size=1,
        **kwargs,
    )


def build_ascii_strategy(excluded_chars: str = "", **kwargs):
    allowed_chars = [chr(i) for i in range(32, 128) if chr(i) not in excluded_chars]
    text_strategy = st.text(alphabet=allowed_chars, **kwargs)
    return text_strategy


def interleave_strategy(
    odd_item: st.SearchStrategy,
    even_item: st.SearchStrategy,
    n_strategy: st.SearchStrategy,
):

    @st.composite
    def interleave(draw):
        n = draw(n_strategy)
        odd_items = draw(st.lists(odd_item, min_size=n + 1, max_size=n + 1))
        even_items = draw(st.lists(even_item, min_size=n, max_size=n))
        result = [None] * (2 * n + 1)
        result[::2] = odd_items
        result[1::2] = even_items
        return result

    return interleave()


def interleave_with_newlines(
    ctx,
    item: st.SearchStrategy,
    n_strategy: Optional[st.SearchStrategy] = None,
    newline_count: int = 2,
):
    return interleave_strategy(
        odd_item=item,
        even_item=build_Newline(ctx=ctx, count=st.just(newline_count)),
        n_strategy=st.integers(1, ctx.getMaxSubnodeCount())
        if n_strategy is None else n_strategy,
    )


@st.composite
def build_Document(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(
        st.builds(
            org.Document,
            subnodes=interleave_strategy(
                odd_item=node_strategy(ctx=ctx.rec(osk.Document)),
                even_item=st.builds(org.Newline, text=st.just("\n\n")),
                n_strategy=st.integers(min_value=2, max_value=5),
            ),
        ))


@st.composite
def build_StmtList(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.StmtList, subnodes=draw(build_subnodes(ctx=ctx))))


@st.composite
def build_HashTagText(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(
        st.builds(org.HashTagText,
                  head=build_alnum_ident(),
                  subtags=st.lists(build_HashTagText(ctx))))


@st.composite
def build_HashTag(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.HashTag, text=build_HashTagText(ctx)))


@st.composite
def build_InlineFootnote(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(
        st.builds(org.InlineFootnote,
                  head=st.from_regex("[a-zA-Z]+", fullmatch=True),
                  definition=st.one_of(None,
                                       build_Paragraph(ctx.rec(osk.InlineFootnote)))))


@st.composite
def build_Paragraph(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(
        st.builds(org.Paragraph,
                  subnodes=interleave_strategy(
                      odd_item=node_strategy(ctx.rec(osk.Paragraph)),
                      even_item=build_Space(ctx),
                      n_strategy=st.integers(1, ctx.getMaxSubnodeCount()),
                  )))


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
def build_BlockCenter(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.BlockCenter))


@st.composite
def build_CmdCaption(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.CmdCaption, text=build_Paragraph(ctx.rec(osk.CmdCaption))))


@st.composite
def build_CmdName(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.CmdName))


@st.composite
def build_CmdResults(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.CmdResults))


@st.composite
def build_CmdTblfm(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.CmdTblfm))


@st.composite
def build_BlockQuote(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(
        st.builds(
            org.BlockQuote,
            subnodes=interleave_with_newlines(ctx, build_Paragraph(ctx)),
        ))


@st.composite
def build_BlockVerse(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(
        st.builds(
            org.BlockVerse,
            subnodes=interleave_with_newlines(ctx, build_Paragraph(ctx)),
        ))


@st.composite
def build_CmdAttr(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.CmdAttr, target=build_alnum_ident()))


def build_raw_text_block(ctx: OrgGenCtx):
    return interleave_with_newlines(
        ctx,
        st.builds(org.RawText,
                  text=build_ascii_strategy(excluded_chars="\n", min_size=1,
                                            max_size=20)),
        newline_count=1,
        n_strategy=st.integers(min_value=0, max_value=2),
    )


@st.composite
def build_BlockExport(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.BlockExport, subnodes=build_raw_text_block(ctx)))


@st.composite
def build_BlockExample(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.BlockExample, subnodes=build_raw_text_block(ctx)))


@st.composite
def build_Code(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.BlockCode, subnodes=build_raw_text_block(ctx)))


@st.composite
def build_AdmonitionBlock(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.BlockAdmonition))


@st.composite
def build_Call(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Call))


@st.composite
def build_Time(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Time))


@st.composite
def build_TimeRange(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(
        st.builds(org.TimeRange, **{
            "from": build_Time(ctx=ctx),
            "to": build_Time(ctx=ctx)
        }))


@st.composite
def build_Macro(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Macro))


@st.composite
def build_Symbol(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Symbol))


@st.composite
def build_SubtreeLog(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.SubtreeLog,))


@st.composite
def build_Subtree(draw: st.DrawFn, ctx: OrgGenCtx):
    min_level = ctx.opts.parentSubtree + 1
    level = draw(st.integers(min_value=min_level, max_value=min_level + 10))
    return draw(
        st.builds(
            org.Subtree,
            level=st.just(level),
            title=build_Paragraph(ctx.rec(osk.Subtree)),
            subnodes=build_subnodes(ctx.rec(osk.Subtree).rec_update(parentSubtree=level)),
        ))


@st.composite
def build_InlineMath(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Latex))


@st.composite
def build_Escaped(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Escaped, text=build_alnum_ident(max_size=1)))


@st.composite
def build_Newline(draw: st.DrawFn, ctx: OrgGenCtx, count: st.SearchStrategy = st.just(1)):
    size = draw(count)
    return draw(st.builds(org.Newline, text=st.text("\n", min_size=size, max_size=size)))


@st.composite
def build_Space(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Space, text=st.just(" ")))


@st.composite
def build_Word(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Word, text=build_alnum_ident()))


@st.composite
def build_AtMention(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.AtMention, text=build_alnum_ident()))


@st.composite
def build_RawText(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.RawText))


@st.composite
def build_Punctuation(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Punctuation))


@st.composite
def build_Placeholder(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Placeholder, text=build_alnum_ident()))


@st.composite
def build_BigIdent(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.BigIdent))


@st.composite
def build_Bold(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Bold, subnodes=build_subnodes(ctx.rec(osk.Bold))))


@st.composite
def build_Underline(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Underline, subnodes=build_subnodes(ctx.rec(osk.Underline))))


@st.composite
def build_Monospace(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Monospace))


@st.composite
def build_MarkQuote(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.MarkQuote))


@st.composite
def build_Verbatim(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Verbatim, subnodes=build_subnodes(ctx.rec(osk.Verbatim))))


@st.composite
def build_Italic(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Italic, subnodes=build_subnodes(ctx.rec(osk.Italic))))


@st.composite
def build_Strike(draw: st.DrawFn, ctx: OrgGenCtx):
    return draw(st.builds(org.Strike, subnodes=build_subnodes(ctx.rec(osk.Strike))))


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
        case osk.InlineFootnote:
            return draw(build_InlineFootnote(ctx=ctx))
        case osk.Paragraph:
            return draw(build_Paragraph(ctx=ctx))
        case osk.BlockCenter:
            return draw(build_BlockCenter(ctx=ctx))
        case osk.CmdCaption:
            return draw(build_CmdCaption(ctx=ctx))
        case osk.CmdName:
            return draw(build_CmdName(ctx=ctx))
        case osk.CmdResults:
            return draw(build_CmdResults(ctx=ctx))
        case osk.CmdTblfm:
            return draw(build_CmdTblfm(ctx=ctx))
        case osk.BlockQuote:
            return draw(build_BlockQuote(ctx=ctx))
        case osk.BlockVerse:
            return draw(build_BlockVerse(ctx=ctx))
        case osk.BlockExample:
            return draw(build_BlockExample(ctx=ctx))
        case osk.CmdAttr:
            return draw(build_CmdAttr(ctx=ctx))
        case osk.BlockExport:
            return draw(build_BlockExport(ctx=ctx))
        case osk.BlockAdmonition:
            return draw(build_AdmonitionBlock(ctx=ctx))
        case osk.Call:
            return draw(build_Call(ctx=ctx))
        case osk.BlockCode:
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
        case osk.Latex:
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


ignore_this_fucking_vomit_shit = [
    HealthCheck.data_too_large,
    HealthCheck.too_slow,
    HealthCheck.filter_too_much,
]

gen_settings = dict(
    max_examples=30,
    suppress_health_check=ignore_this_fucking_vomit_shit,
)


@pytest.mark.unstable
@settings(**gen_settings)
@given(node_strategy(OrgGenCtx()))
def test_ultraplain_export(doc: org.Document):
    exp = export_ultraplain.ExporterUltraplain()
    exp.exp.evalTop(doc)


@pytest.mark.unstable
@settings(**gen_settings)
@given(node_strategy(OrgGenCtx()))
def test_tex_export(doc: org.Document):
    exp = export_tex.ExporterLatex()
    exp.exp.evalTop(doc)


@pytest.mark.unstable
@settings(**gen_settings)
@given(node_strategy(OrgGenCtx()))
def test_html_export(doc: org.Document):
    exp = export_html.ExporterHtml()
    exp.exp.evalTop(doc)


counter = 0


@pytest.mark.unstable
@settings(**gen_settings)
@given(node_strategy(OrgGenCtx()))
def test_render(doc: org.Document):
    global counter
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        dir = Path("/tmp/test_render")
        dir.mkdir(parents=True, exist_ok=True)

        with open(dir.joinpath(f"debug_{counter}.txt"), "w") as file:
            file.write("================================================\n\n")
            file.write(org.treeRepr(doc, colored=False))
            file.write("\n\n\n")
            file.write(org.formatToString(doc))
            file.write("\n\n")

        counter += 1


# if __name__ == "__main__":
#     test_render()
