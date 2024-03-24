from pathlib import Path
import rich_click as click
import json

from py_cli.haxorg_cli import (
    apply_options,
    options_from_model,
    BaseModel,
    pack_context,
    Field,
)

from beartype.typing import List, Union, Optional, Dict, Callable, Any, Iterable
from beartype import beartype
from dataclasses import dataclass, field
import igraph as ig

import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.script_logging import log, to_debug_json
from py_haxorg.pyhaxorg_utils import formatOrgWithoutTime
import graphviz as gv

CAT = "mind_map"


@beartype
@dataclass
class NodeEntry():
    entry: "DocEntry"


@beartype
@dataclass
class NodeSubtree():
    subtree: "DocSubtree"


@beartype
@dataclass
class Node():

    data: Union[NodeEntry, NodeSubtree]

    def isEntry(self) -> bool:
        return isinstance(self.data, NodeEntry)

    def isSubtree(self) -> bool:
        return isinstance(self.data, NodeSubtree)


@beartype
@dataclass
class DocLink():
    resolved: Optional[Node] = None
    description: Optional[org.Org] = None
    location: Optional[org.Org] = None
    parent: Optional["DocSubtree"] = None

    def isEntry(self) -> bool:
        return self.resolved.isEntry()

    def isSubtree(self) -> bool:
        return self.resolved.isSubtree()


@beartype
@dataclass
class DocEntry():
    content: org.Org
    outgoing: List[DocLink] = field(default_factory=list)
    parent: Optional["DocSubtree"] = None


@beartype
@dataclass
class DocSubtree():
    original: org.Org
    parent: Optional["DocSubtree"] = None
    subtrees: List["DocSubtree"] = field(default_factory=list)
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
            cb(it, tree)

        for it in tree.unordered:
            cb(it, tree)

    eachSubtree(root, aux)


@beartype
@dataclass
class MindMapCollector():
    stack: List[DocSubtree] = field(default_factory=list)
    root: List[DocSubtree] = field(default_factory=list)
    entriesOut: Dict[org.Org, DocEntry] = field(default_factory=dict)
    subtreesOut: Dict[org.Org, DocSubtree] = field(default_factory=dict)
    resolveContext: Optional[org.OrgDocumentContext] = None

    def eachRootEntry(self, cb: Callable[[DocEntry, DocSubtree], None]):
        for item in self.root:
            eachEntry(item, cb)

    def eachRootSubtree(self, cb: Callable[[DocSubtree], None]):
        for item in self.root:
            eachSubtree(item, cb)

    def popStack(self):
        top = self.stack.pop()
        if self.stack:
            self.stack[-1].subtrees.append(top)

        else:
            self.root.append(top)

    def visitSubtree(self, tree: org.Subtree):
        top: Optional[DocSubtree] = None
        if self.stack:
            top = self.stack[-1]

        res = DocSubtree(original=tree)
        self.stack.append(res)
        res.parent = top

        for sub in tree:
            match sub:
                case org.Subtree():
                    self.visitSubtree(sub)

                case org.Newline() | org.Space():
                    pass

                case org.List() if sub.at(0).isDescriptionItem():
                    for it in sub:
                        # Push temporary outgoing doc link -- all links
                        # will be resolved in the `visitEnd` once the
                        # whole document is mapped out.
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

        self.popStack()

    def visitDocument(self, doc: org.Document):
        self.stack.append(DocSubtree(original=doc))

        for item in doc:
            if isinstance(item, org.Subtree):
                self.visitSubtree(item)

        self.popStack()

    def getResolved(self, node: org.Org, parent: DocSubtree) -> Optional[DocLink]:
        if isinstance(node, org.Link):
            target: List[org.Org] = self.resolveContext.getLinkTarget(node)
            if not target:
                return None

            first = target[0]

            entry: Optional[DocEntry] = self.entriesOut.get(first, None)
            subtree: Optional[DocSubtree] = self.subtreesOut.get(first, None)

            if entry:
                return DocLink(
                    parent=parent,
                    resolved=Node(data=NodeEntry(entry=entry)),
                    location=node,
                )

            elif subtree:
                return DocLink(
                    parent=parent,
                    resolved=Node(data=NodeSubtree(subtree=subtree)),
                    location=node,
                )

    def visitFiles(self, nodes: List[org.Org]):
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

        self.eachRootEntry(register_out_entires)

        def register_subtrees_out(tree: DocSubtree):
            assert tree.original not in self.subtreesOut
            self.subtreesOut[tree.original] = tree

        self.eachRootSubtree(register_subtrees_out)

        @beartype
        def register_outgoing_entry_links(entry: DocEntry, tree: DocSubtree):

            @beartype
            def aux(node: org.Org):
                resolved = self.getResolved(node, tree)
                if resolved:
                    entry.outgoing.append(resolved)

            org.eachSubnodeRec(entry.content, aux)

        self.eachRootEntry(register_outgoing_entry_links)

        # def register_outgoging_subtree_links(tree: DocSubtree):


class JsonGraphNodeSubtreeMeta(BaseModel, extra="forbid"):
    kind: str = "Subtree"
    title: Optional[str] = None
    level: Optional[int] = None
    parent: Optional[str] = None
    ordered: List[str] = Field(default_factory=list)
    unordered: List[str] = Field(default_factory=list)
    subtrees: List[str] = Field(default_factory=list)


class JsonGraphNodeOutgoingMeta(BaseModel, extra="forbid"):
    out_index: int
    target: str
    source: str


class JsonGraphNodeEntryMeta(BaseModel, extra="forbid"):
    kind: str = "Entry"
    parent: Optional[str] = None
    content: Any = Field(default_factory=dict)
    order: Optional[int] = None
    outgoing: List[JsonGraphNodeOutgoingMeta] = Field(default_factory=list)


class JsonGraphNode(BaseModel, extra="forbid"):
    metadata: Union[JsonGraphNodeSubtreeMeta, JsonGraphNodeEntryMeta] = Field(
        default_factory=lambda: JsonGraphNodeEntryMeta())

    id: str


class JsonGraphEdge(BaseModel, extra="forbid"):
    metadata: Dict = Field(default_factory=dict)
    source: str
    target: str


class JsonGraph(BaseModel, extra="forbid"):
    type: str = "Haxorg MindMap export"
    metadata: Dict = Field(default_factory=dict)
    edges: List[JsonGraphEdge] = Field(default_factory=list)
    nodes: Dict[str, JsonGraphNode] = Field(default_factory=dict)


@beartype
@dataclass
class MindMapNodeEntry():
    entry: DocEntry
    idx: Optional[int] = None


@beartype
@dataclass
class MindMapNodeSubtree():
    subtree: DocSubtree


@beartype
@dataclass
class MindMapNode():
    data: Union[MindMapNodeEntry, MindMapNodeSubtree]


@beartype
@dataclass
class MindMapEdge():

    class PlacedIn():
        pass

    class NestedIn():
        pass

    @dataclass
    class RefersTo():
        target: DocLink

    class InternallyRefers():
        pass

    data: Union[PlacedIn, NestedIn, RefersTo, InternallyRefers]
    location: Optional[org.Org] = None


@beartype
def getStrId(value: Union[
    org.Org,
    DocSubtree,
    DocEntry,
    DocLink,
    MindMapNode,
]) -> str:
    match value:
        case org.Org():
            return str(id(value))

        case DocSubtree():
            return getStrId(value.original)

        case DocEntry():
            return getStrId(value.content)

        case DocLink():
            return getStrId(value.resolved.data)

        case MindMapNode(data=MindMapNodeSubtree()):
            return getStrId(value.data.subtree)

        case MindMapNode(data=MindMapNodeEntry()):
            return getStrId(value.data.entry)


@beartype
@dataclass
class MindMapGraph():
    graph: ig.Graph = field(default_factory=lambda: ig.Graph(directed=True))

    def addVertex(self, value: MindMapNode) -> int:
        idx = len(self.graph.vs)
        self.graph.add_vertex()
        self.graph.vs[idx]["node"] = value
        return idx

    def addEdge(self, from_: int, to: int, value: MindMapEdge) -> int:
        idx = len(self.graph.es)
        self.graph.add_edge(from_, to)
        self.graph.es[idx]["edge"] = value
        return idx

    def getNodeObj(self, node: int) -> MindMapNode:
        return self.graph.vs[node]["node"]

    def getEdgeObj(self, edge: int) -> MindMapEdge:
        return self.graph.es[edge]["edge"]

    def getSource(self, idx: int) -> int:
        return self.graph.es[idx].source

    def getTarget(self, idx: int) -> int:
        return self.graph.es[idx].target

    def getVertices(self) -> Iterable[int]:
        return range(0, len(self.graph.vs))

    def getEdges(self) -> Iterable[int]:
        return range(0, len(self.graph.es))

    def getIdxId(self, idx: int) -> str:
        return getStrId(self.getNodeObj(idx))

    def toJsonGraphNode(self, idx: int) -> JsonGraphNode:
        res = JsonGraphNode(id=getStrId(self.getNodeObj(idx)))
        node = self.getNodeObj(idx)
        if isinstance(node.data, MindMapNodeEntry):
            entry: MindMapNodeEntry = node.data
            res.metadata = JsonGraphNodeEntryMeta()

            res.metadata.parent = getStrId(entry.entry.parent)

        else:
            tree: MindMapNodeSubtree = node.data
            res.metadata = JsonGraphNodeSubtreeMeta()

            if isinstance(tree.subtree.original, org.Subtree):
                res.metadata.title = formatOrgWithoutTime(tree.subtree.original.title)
                res.metadata.level = tree.subtree.original.level

            if tree.subtree.parent:
                res.metadata.parent = getStrId(tree.subtree.parent)

            res.metadata.ordered = [getStrId(it) for it in tree.subtree.ordered]
            res.metadata.unordered = [getStrId(it) for it in tree.subtree.unordered]
            res.metadata.subtrees = [getStrId(it) for it in tree.subtree.subtrees]

        return res

    def toJsonGraphEdge(self, idx: int) -> JsonGraphEdge:
        res = JsonGraphEdge(
            source=getStrId(self.getNodeObj(self.getSource(idx))),
            target=getStrId(self.getNodeObj(self.getTarget(idx))),
        )

        return res

    def toJsonGraph(self) -> JsonGraph:
        result = JsonGraph()

        for idx in self.getVertices():
            result.nodes[getStrId(self.getNodeObj(idx))] = self.toJsonGraphNode(idx)

        for idx in self.getEdges():
            result.edges.append(self.toJsonGraphEdge(idx))

        return result

    def toGraphvizGraph(self) -> gv.Digraph:
        dot: gv.Digraph = gv.Digraph("map")
        dot.attr("graph", rankdir="LR", overlap="false", concentrate="true")
        dot.attr("node", shape="rect", font="Iosevka")
        dot.format = "png"
        dot.engine = "neato"

        for idx in self.getVertices():
            node_attrs = {}
            obj = self.getNodeObj(idx)
            if isinstance(obj.data, MindMapNodeSubtree) and isinstance(
                    obj.data.subtree.original, org.Subtree):
                node_attrs["title"] = formatOrgWithoutTime(
                    obj.data.subtree.original.title)

            dot.node(self.getIdxId(idx), **node_attrs)

        for idx in self.getEdges():
            dot.edge(
                self.getIdxId(self.getSource(idx)),
                self.getIdxId(self.getTarget(idx)),
            )

        return dot


class MindMapOpts(BaseModel, extra="forbid"):
    infile: List[Path]
    outfile: Path


@beartype
def getGraph(nodes: List[org.Org]) -> MindMapGraph:
    collector = MindMapCollector()
    collector.visitFiles(nodes)

    Path("/tmp/debug.json").write_text(json.dumps(to_debug_json(collector), indent=2))

    result = MindMapGraph()

    entryNodes: Dict[org.Org, int] = {}
    subtreeNodes: Dict[org.Org, int] = {}

    @beartype
    def auxEntry(entry: DocEntry, idx: Optional[int]) -> int:
        return result.addVertex(MindMapNode(data=MindMapNodeEntry(entry=entry, idx=idx)))

    @beartype
    def getVertex(link: Union[DocLink, org.Org]) -> Optional[int]:
        if isinstance(link, org.Org):
            if link in entryNodes:
                return entryNodes[link]

            elif link in subtreeNodes:
                return subtreeNodes[link]

            else:
                return None

        elif isinstance(link, DocLink):
            if link.isEntry():
                return entryNodes[link.resolved.data.entry.content]

            else:
                return subtreeNodes[link.resolved.data.subtree.original]

        else:
            assert False

    @beartype
    def auxSubtree(tree: DocSubtree) -> int:
        desc = result.addVertex(MindMapNode(data=MindMapNodeSubtree(subtree=tree)))

        for sub in tree.subtrees:
            sub_desc = auxSubtree(sub)
            result.addEdge(
                from_=desc,
                to=sub_desc,
                value=MindMapEdge(data=MindMapEdge.NestedIn()),
            )

        for idx, sub in enumerate(tree.ordered):
            entry = auxEntry(sub, idx)
            result.addEdge(from_=desc,
                           to=entry,
                           value=MindMapEdge(data=MindMapEdge.PlacedIn()))

        for sub in tree.unordered:
            entry = auxEntry(sub, None)
            result.addEdge(from_=desc,
                           to=entry,
                           value=MindMapEdge(data=MindMapEdge.PlacedIn()))

        return desc

    for item in collector.root:
        auxSubtree(item)

    for idx in range(0, len(result.graph.vs)):
        prop = result.getNodeObj(idx)
        if isinstance(prop.data, MindMapNodeEntry):
            entryNodes[prop.data.entry.content] = idx

        else:
            subtreeNodes[prop.data.subtree.original] = idx

    def addLink(desc: int, link: DocLink):
        if link.resolved:
            result.addEdge(
                desc, getVertex(link),
                MindMapEdge(location=link.location,
                            data=MindMapEdge.RefersTo(target=link)))

    def register_outgoing_links(entry: DocEntry, parent: DocSubtree):
        for item in entry.outgoing:
            addLink(entryNodes[entry.content], item)

    collector.eachRootEntry(register_outgoing_links)

    def register_subtree_links(subtree: DocSubtree):
        idx = subtreeNodes[subtree.original]
        for out in subtree.outgoing:
            addLink(idx, out)

        for ord in subtree.ordered:
            for link in ord.outgoing:
                if link.isSubtree():
                    result.addEdge(
                        idx, getVertex(link),
                        MindMapEdge(
                            data=MindMapEdge.InternallyRefers(),
                            location=link.location,
                        ))

        for unord in subtree.unordered:
            for link in unord.outgoing:
                if link.isSubtree():
                    result.addEdge(
                        idx, getVertex(link),
                        MindMapEdge(
                            data=MindMapEdge.InternallyRefers(),
                            location=link.location,
                        ))

    collector.eachRootSubtree(register_subtree_links)

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
