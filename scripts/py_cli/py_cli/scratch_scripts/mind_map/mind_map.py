from pathlib import Path
import rich_click as click

from py_cli.haxorg_cli import (
    apply_options,
    options_from_model,
    BaseModel,
    pack_context,
    Field,
)

from beartype.typing import List, Union, Optional, Dict, Callable, Any
from beartype import beartype
from dataclasses import dataclass, field
import igraph as ig

import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.script_logging import log

CAT = "mind_map"


@beartype
@dataclass
class Node():

    @beartype
    @dataclass
    class Entry():
        entry: "DocEntry"

    @beartype
    @dataclass
    class Subtree():
        subtree: "DocSubtree"

    data: Union[Entry, Subtree]


@beartype
@dataclass
class DocLink():
    resolved: Node
    description: Optional[org.Org] = None
    location: Optional[org.Org] = None
    parent: Optional["DocSubtree"] = None


@beartype
@dataclass
class DocEntry():
    content: org.Org
    outgoing: List[DocLink] = field(default_factory=list)
    parent: Optional["DocSubtree"] = None


@beartype
@dataclass
class DocSubtree():
    parent: Optional["DocSubtree"] = None
    subtrees: List["DocSubtree"] = field(default_factory=list)
    original: Optional[org.Org] = None
    ordered: List[DocEntry] = field(default_factory=list)
    unordered: List[DocEntry] = field(default_factory=list)
    outgoing: List[DocLink] = field(default_factory=list)


@beartype
def eachSubtree(root: DocSubtree, cb: Callable[[DocSubtree], None]):

    def aux(tree: DocSubtree):
        cb(tree)
        for sub in tree.subtrees:
            aux(sub)

    aux(root)


@beartype
def eachEntry(root: DocSubtree, cb: Callable[[DocEntry, DocSubtree], None]):

    def aux(tree: DocSubtree):
        for it in tree.ordered:
            cb(it)

        for it in tree.unordered:
            cb(it)

    eachSubtree(root, aux)


class JsonGraphNode(BaseModel):
    meta: Dict = Field(default_factory=dict)


class JsonGraphEdge(BaseModel):
    meta: Dict = Field(default_factory=dict)


class JsonGraph(BaseModel):
    type: str = "Haxorg MindMap export"
    metadata: Dict = Field(default_factory=dict)
    edges: List[JsonGraphEdge] = Field(default_factory=list)
    nodes: List[JsonGraphNode] = Field(default_factory=list)


class MindMapOpts(BaseModel, extra="forbid"):
    infile: List[Path]
    outfile: Path


@beartype
@dataclass
class MindMapCollector():
    stack: List[DocSubtree] = field(default_factory=list)
    root: Optional[DocSubtree] = None
    entriesOut: Dict[org.Org, DocEntry] = field(default_factory=dict)
    subtreesOut: Dict[org.Org, DocSubtree] = field(default_factory=dict)
    resolveContext: Optional[org.OrgDocumentContext] = None

    def visitSubtree(self, tree: org.Subtree):
        top: Optional[DocSubtree] = None
        if self.stack:
            top = self.stack[-1]

        res = DocSubtree()
        self.stack.append(res)
        res.parent = top
        res.original = top

        for sub in tree:
            match sub:
                case org.Subtree():
                    self.visitSubtree(sub)

                case org.Newline() | org.Space():
                    pass

                case org.List() if sub.at(0).isDescriptionItem():
                    for it in sub:
                        res.outgoing.append(
                            DocLink(
                                description=it,
                                parent=top,
                                location=it,
                            ))

                case _:
                    entry = DocEntry(
                        parent=top,
                        content=sub,
                    )

                    if isinstance(sub, org.AnnotatedParagraph) and sub.getAnnotationKind(
                    ) == org.AnnotatedParagraphAnnotationKind.Footnote:
                        res.unordered.append(entry)

                    else:
                        res.ordered.append(entry)

    def visitDocument(self, doc: org.Document):
        self.stack.append(DocSubtree())

        for item in doc:
            if isinstance(item, org.Subtree):
                self.visitSubtree(item)

        self.stack[-1].subtrees.append(self.stack.pop())

    def getResolved(self, node: org.Org, parent: DocSubtree) -> Optional[DocLink]:
        if isinstance(node, org.Link):
            target = self.resolveContext.getLinkTarget(node)
            entry: Optional[DocEntry] = self.entriesOut.get(target, None)
            subtree: Optional[DocSubtree] = self.subtreesOut.get(target, None)

            if entry:
                return DocLink(
                    parent=parent,
                    resolved=Node(data=Node.Entry(entry)),
                    location=node,
                )

            elif subtree:
                return DocLink(
                    parent=parent,
                    resolved=Node(data=Node.Subtree(subtree)),
                    location=node,
                )

    def visitFiles(self, nodes: List[org.Org]):
        self.root = DocSubtree()
        self.stack.append(self.root)
        self.resolveContext = org.OrgDocumentContext()

        for node in nodes:
            self.resolveContext.addNodes(node)

        for node in nodes:
            self.visitDocument(node)

        self.entriesOut = {}
        self.subtreesOut = {}

        def register_out_entires(entry: DocEntry, parent: DocSubtree):
            id = entry.content
            assert id not in self.entriesOut
            self.entriesOut[id] = entry

        eachEntry(self.root, register_out_entires)

        def register_subtrees_out(tree: DocSubtree):
            assert tree.original not in self.subtreesOut
            self.subtreesOut[tree.original] = tree

        eachSubtree(self.root, register_subtrees_out)

        def register_outgoing_entry_links(entry: DocEntry, tree: DocSubtree):

            def aux(node: org.Org):
                resolved = self.getResolved(node, tree)
                if resolved:
                    entry.outgoing.append(resolved)

            org.eachSubnodeRec(entry.content, aux)

        eachEntry(self.root, register_outgoing_entry_links)

        # def register_outgoging_subtree_links(tree: DocSubtree):


@beartype
@dataclass
class MindMapNode():

    @beartype
    @dataclass
    class Entry():
        entry: DocEntry
        idx: Optional[int] = None

    @beartype
    @dataclass
    class Subtree():
        subtree: DocSubtree

    data: Union[Entry, Subtree]


@beartype
@dataclass
class MindMapEdge():
    pass


@beartype
@dataclass
class MindMapGraph():
    graph: ig.Graph = field(default_factory=lambda: ig.Graph(directed=True))

    def addVertex(self, value: MindMapNode) -> int:
        idx = self.graph.add_vertex()
        self.graph.vs[idx]["node"] = value
        return idx

    def addEdge(self, from_: int, to: int, value: MindMapEdge) -> int:
        idx = self.graph.add_edge(from_, to)
        self.graph.es[idx]["edge"] = value
        return idx

    def getNode(self, node: int) -> Any:
        return self.graph.vs[node]["node"]

    def getEdge(self, edge: int) -> Any:
        return self.graph.es[edge]["edge"]


@beartype
def getGraph(nodes: List[org.Org]) -> MindMapGraph:
    collector = MindMapCollector()
    collector.visitFiles(nodes)

    subtreeNodes: Dict[org.Org, int] = {}
    entryNodes: Dict[org.Org, int] = {}

    result = MindMapGraph()

    def auxEntry(entry: DocEntry, idx: Optional[int]) -> int:
        return result.addVertex(MindMapNode(data=MindMapNode.Entry(entry=entry, idx=idx)))
    
    def auxSubtree(tree: DocSubtree) -> int:
        desc = result.addVertex(MindMapNode(data=MindMapNode.Subtree(subtree=tree)))

    return result


def cli_options(f):
    return apply_options(f, options_from_model(MindMapOpts))


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@cli_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    pack_context(ctx, "root", MindMapOpts, config=config, kwargs=kwargs)
    opts: MindMapOpts = ctx.obj["root"]
    node = org.parseFile(str(opts.infile.resolve()), org.OrgParseParameters())


if __name__ == "__main__":
    cli()
