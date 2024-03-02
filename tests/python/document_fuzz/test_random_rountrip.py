from hypothesis import strategies as st
from hypothesis import given
import py_haxorg.pyhaxorg_wrap as org
from dataclasses import dataclass, replace, field
from beartype import beartype
from beartype.typing import List, Optional, Union
import itertools


@beartype
@dataclass
class OrgGenOptions():
    minSubnodeCount: int = 1
    maxSubnodeCount: Optional[int] = None
    minAttachedCount: int = 0
    maxAttachedCount: int = 0
    maxRecursionDepth: Optional[int] = None
    enableTrace: bool = False


@beartype
@dataclass
class OrgGenPath:
    kind: org.OrgSemKind


osk = org.OrgSemKind


@beartype
@dataclass
class OrgGenCtx():
    opts: OrgGenOptions = field(default_factory=list)
    steps: List[OrgGenPath] = field(default_factory=list)

    def count(self, kind: org.OrgSemKind) -> int:
        return len(filter(lambda it: it.kind == kind, self.steps))

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

    def withMaxSubnodes(self, max: int) -> 'OrgGenCtx':
        return self.rec(replace(self.opts, maxSubnodeCount=max))

    def withoutSubnodes(self) -> 'OrgGenCtx':
        return self.rec(replace(
            self.opts,
            maxSubnodeCount=0,
            minSubnodeCount=0,
        ))

    def withoutAttached(self) -> 'OrgGenCtx':
        return self.rec(replace(
            self.opts,
            minAttachedCount=0,
            maxAtachedCount=0,
        ))

    def getSubnodeSet(self) -> org.SemSet:
        result = set(it for it in org.OrgSemKind)
        markupLayerCount = 0
        markupKinds = org.SemSet(
            osk.Bold,
            osk.Italic,
            osk.Verbatim,
            osk.Monospace,
            osk.Underline,
            osk.Strike,
        )

        result = result - set(
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
        )

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
            

        return result
            




@st.composite
def build_subnodes(draw: st.DrawFn, ctx: OrgGenCtx):
    return st.lists(node_strategy(draw, ctx))


def build_Document(draw: st.DrawFn, ctx: OrgGenCtx):
    return st.builds(org.Document,)

@st.composite
def node_strategy(draw, ctx: OrgGenCtx):
    item = draw(ctx.getSubnodeSet())
    return globals().get("build_" + str(item))(draw, ctx)


@given(node_strategy(OrgGenCtx()))
def test_render(doc: org.Document):
    ctx = org.OrgContext()
    # ctx.
