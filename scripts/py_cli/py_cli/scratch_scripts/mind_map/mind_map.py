from pathlib import Path
import rich_click as click
import json
from copy import copy

from py_cli.haxorg_cli import (
    apply_options,
    options_from_model,
    BaseModel,
    pack_context,
    Field,
)

from beartype.typing import List, Union, Optional, Dict, Callable, Any, Iterable, Set
from beartype import beartype
from dataclasses import dataclass, field, replace
import igraph as ig

import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.script_logging import log, to_debug_json
from py_haxorg.pyhaxorg_utils import formatOrgWithoutTime, NodeIdProvider
import graphviz as gv
from py_exporters.export_html import ExporterHtml

CAT = "mind_map"


@beartype
@dataclass
class DocLink():
    resolved: Optional[Union["DocSubtree", "DocEntry"]] = None
    description: Optional[org.Org] = None
    location: Optional[org.Org] = None
    parent: Optional["DocSubtree"] = None

    def isEntry(self) -> bool:
        return isinstance(self.resolved, DocEntry)

    def isSubtree(self) -> bool:
        return isinstance(self.resolved, DocSubtree)


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
                    it: org.ListItem
                    for it in sub:
                        if isinstance(it.header[0], org.Link):
                            # Push temporary outgoing doc link -- all links
                            # will be resolved in the `visitEnd` once the
                            # whole document is mapped out.
                            description = org.StmtList(subnodes=[n for n in it])
                            res.outgoing.append(
                                DocLink(
                                    description=description,
                                    parent=top,
                                    location=it.header[0],
                                ))

                case _:
                    entry = DocEntry(
                        parent=res,
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

    def getResolved(
        self,
        node: Union[org.Org, DocLink],
        parent: Optional[DocSubtree] = None,
    ) -> Optional[DocLink]:

        def getTargets(node: org.Org):
            target: List[org.Org] = self.resolveContext.getLinkTarget(node)
            if not target:
                return None, None

            first = target[0]

            entry: Optional[DocEntry] = self.entriesOut.get(first, None)
            subtree: Optional[DocSubtree] = self.subtreesOut.get(first, None)

            return entry, subtree

        if isinstance(node, org.Link):
            entry, subtree = getTargets(node)

            if entry:
                return DocLink(
                    parent=parent,
                    resolved=entry,
                    location=node,
                    description=node.description,
                )

            elif subtree:
                return DocLink(
                    parent=parent,
                    resolved=subtree,
                    location=node,
                    description=node.description,
                )

        elif isinstance(node, DocLink):
            if node.resolved:
                return node

            else:
                entry, subtree = getTargets(node.location)
                if entry:
                    return replace(node, resolved=entry)

                elif subtree:
                    return replace(node, resolved=subtree)

                else:
                    log(CAT).warning("Could not get resolution for the link " +
                                     org.formatToString(node.location))

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


class JsonGraphNodeSubtreeMeta(BaseModel, extra="forbid"):
    kind: str = "Subtree"
    title: Optional[str] = None
    level: Optional[int] = None
    parent: Optional[str] = None
    ordered: List[str] = Field(default_factory=list)
    unordered: List[str] = Field(default_factory=list)
    subtrees: List[str] = Field(default_factory=list)
    id: Optional[str] = None


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
    id: Optional[str] = None


class JsonGraphNode(BaseModel, extra="forbid"):
    metadata: Union[JsonGraphNodeSubtreeMeta, JsonGraphNodeEntryMeta] = Field(
        default_factory=lambda: JsonGraphNodeEntryMeta())


class JsonGraphEdgeMeta(BaseModel, extra="forbid"):
    kind: str
    out_index: Optional[int] = None
    description: Optional[str] = None


class JsonGraphEdge(BaseModel, extra="forbid"):
    metadata: JsonGraphEdgeMeta
    source: str
    target: str


class JsonGraphMeta(BaseModel, extra="forbid"):
    nested: Dict[str, Set[str]] = Field(default_factory=dict)


class JsonGraph(BaseModel, extra="forbid"):
    type: str = "Haxorg MindMap export"
    metadata: JsonGraphMeta = Field(default_factory=lambda: JsonGraphMeta())
    edges: List[JsonGraphEdge] = Field(default_factory=list)
    nodes: Dict[str, JsonGraphNode] = Field(default_factory=dict)


class GvRecordLabel(BaseModel):
    kind: str = "record"
    port: Optional[str] = None
    content: Union[str, List["GvRecordLabel"]] = ""
    changeDirection: bool = Field(
        default=True,
        description="Change the record content layout direction with {} wrapping")

    def toString(self) -> str:
        if isinstance(self.content, str):
            if self.port:
                return f"<{self.port}> {self.content}"

            else:
                return self.content

        else:
            return "{" + "|".join([it.toString() for it in self.content]) + "}"


class GvHtmlLabel(BaseModel, extra="forbid"):
    kind: str = "html"
    text: str


class GvGraphNode(BaseModel):
    id: str
    label: Optional[Union[str, GvRecordLabel, GvHtmlLabel]] = None
    attrs: dict = {}

    def getAttrs(self) -> dict:
        result = copy(self.attrs)

        match self.label:
            case str():
                result["label"] = self.label

            case GvRecordLabel():
                result["label"] = self.label.toString()
                result["shape"] = "record"

            case GvHtmlLabel():
                result["label"] = "<" + self.label.text + ">"
                # result["shape"] = "plaintext"

        return result


class GvGraphEdge(BaseModel):
    source: str
    target: str
    attrs: dict = {}


class GvGraph(BaseModel, extra="forbid"):
    id: Optional[str] = None
    directed: bool = True
    nodes: List[GvGraphNode] = []
    edges: List[GvGraphEdge] = []
    engine: str = "dot"
    format: str = "png"
    graph_attrs: dict = Field(default_factory=dict)
    node_attrs: dict = Field(default_factory=dict)
    edge_attrs: dict = Field(default_factory=dict)
    subgraphs: List["GvGraph"] = Field(default_factory=list)

    def to_graphviz(self) -> Union[gv.Digraph, gv.Graph]:
        graph_class = gv.Digraph if self.directed else gv.Graph
        graph = graph_class(name=self.id)
        graph.attr(**self.graph_attrs)
        if self.node_attrs:
            graph.attr("node", **self.node_attrs)

        if self.edge_attrs:
            graph.attr("edge", **self.edge_attrs)

        graph.engine = self.engine
        graph.format = self.format

        for node in self.nodes:
            graph.node(node.id, **node.getAttrs())

        for edge in self.edges:
            graph.edge(edge.source, edge.target, **edge.attrs)

        return graph


@beartype
@dataclass
class MindMapNodeEntry():
    entry: DocEntry
    idx: Optional[int] = None


@beartype
@dataclass
class MindMapNodeSubtree():
    subtree: DocSubtree

    def isDocument(self) -> bool:
        return isinstance(self.subtree.original, org.Document)


@beartype
@dataclass
class MindMapNode():
    data: Union[MindMapNodeEntry, MindMapNodeSubtree]

    def isDocument(self) -> bool:
        return isinstance(self.data, MindMapNodeSubtree) and self.data.isDocument()


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
@dataclass
class MindMapGraph():
    idProvider: NodeIdProvider
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

    def getNodeIdIndex(self, value: org.Org) -> str:
        return self.idProvider.getNodeId(value)

    @beartype
    def getStrId(
            self, value: Union[
                org.Org,
                int,
                DocSubtree,
                DocEntry,
                DocLink,
                MindMapNode,
            ]) -> str:
        match value:
            case int():
                return str(value)

            case org.Org():
                return str(self.getNodeIdIndex(value))

            case DocSubtree():
                return self.getStrId(value.original)

            case DocEntry():
                return self.getStrId(value.content)

            case DocLink():
                return self.getStrId(value.resolved)

            case MindMapNode(data=MindMapNodeSubtree()):
                return self.getStrId(value.data.subtree)

            case MindMapNode(data=MindMapNodeEntry()):
                return self.getStrId(value.data.entry)

    def getIdxId(self, idx: int) -> str:
        return self.getStrId(self.getNodeObj(idx))

    def toJsonGraphNode(self, idx: int) -> JsonGraphNode:
        res = JsonGraphNode()
        node = self.getNodeObj(idx)
        if isinstance(node.data, MindMapNodeEntry):
            entry: MindMapNodeEntry = node.data
            res.metadata = JsonGraphNodeEntryMeta()

            res.metadata.id = self.getStrId(self.getNodeObj(idx))
            res.metadata.parent = self.getStrId(entry.entry.parent)

        else:
            tree: MindMapNodeSubtree = node.data
            res.metadata = JsonGraphNodeSubtreeMeta()

            if isinstance(tree.subtree.original, org.Subtree):
                res.metadata.title = formatOrgWithoutTime(tree.subtree.original.title)
                res.metadata.level = tree.subtree.original.level

            if tree.subtree.parent:
                res.metadata.parent = self.getStrId(tree.subtree.parent)

            res.metadata.id = self.getStrId(self.getNodeObj(idx))
            res.metadata.ordered = [self.getStrId(it) for it in tree.subtree.ordered]
            res.metadata.unordered = [self.getStrId(it) for it in tree.subtree.unordered]
            res.metadata.subtrees = [self.getStrId(it) for it in tree.subtree.subtrees]

        return res

    def toJsonGraphEdge(self, idx: int) -> JsonGraphEdge:
        edge = self.getEdgeObj(idx)
        description: Optional[str] = None
        if isinstance(edge.data, MindMapEdge.RefersTo):
            description = org.formatToString(edge.data.target.description)

        res = JsonGraphEdge(
            metadata=JsonGraphEdgeMeta(kind=type(edge.data).__name__,
                                       description=description),
            source=self.getStrId(self.getNodeObj(self.getSource(idx))),
            target=self.getStrId(self.getNodeObj(self.getTarget(idx))),
        )

        return res

    def toJsonGraph(self) -> JsonGraph:
        result = JsonGraph()

        for idx in self.getVertices():
            result.nodes[self.getStrId(self.getNodeObj(idx))] = self.toJsonGraphNode(idx)

        for idx in self.getEdges():
            result.edges.append(self.toJsonGraphEdge(idx))

        return result

    def toGraphvizGraph(
        self,
        withDocument: bool = False,
        withNesting: bool = False,
    ) -> GvGraph:
        dot = GvGraph()
        dot.graph_attrs = dict(rankdir="LR", overlap="false", concentrate="true")
        dot.node_attrs = dict(shape="rect", font="Iosevka")

        for idx in self.getVertices():
            obj = self.getNodeObj(idx)
            if obj.isDocument() and not withDocument:
                continue

            node = GvGraphNode(id=self.getIdxId(idx))

            def formatOrg(node: org.Org) -> str:
                exp = ExporterHtml(graphviz_break="left")
                return exp.getHtmlString(node) + "<br align=\"left\"/>"

            match obj.data:
                case MindMapNodeSubtree():
                    if isinstance(obj.data.subtree.original, org.Subtree):
                        node.label = GvHtmlLabel(
                            text=formatOrg(obj.data.subtree.original.title))

                        node.attrs["kind"] = "Subtree"

                    else:
                        node.attrs["kind"] = "Document"

                case MindMapNodeEntry():
                    node.attrs["kind"] = "Entry"
                    exp = ExporterHtml(graphviz_break="left")
                    node.label = GvHtmlLabel(text=formatOrg(obj.data.entry.content))

            dot.nodes.append(node)

        for idx in self.getEdges():
            source = self.getSource(idx)
            target = self.getTarget(idx)
            edge = self.getEdgeObj(idx)
            if not withDocument and (self.getNodeObj(source).isDocument() or
                                     self.getNodeObj(target).isDocument()):
                continue

            elif not withNesting and isinstance(edge.data, MindMapEdge.NestedIn):
                continue

            else:
                dot.edges.append(
                    GvGraphEdge(
                        source=self.getIdxId(source),
                        target=self.getIdxId(target),
                    ))

        return dot

    @staticmethod
    def FromCollector(idProvider: NodeIdProvider,
                      collector: MindMapCollector) -> "MindMapGraph":
        result = MindMapGraph(idProvider=idProvider)

        entryNodes: Dict[org.Org, int] = {}
        subtreeNodes: Dict[org.Org, int] = {}

        @beartype
        def auxEntry(entry: DocEntry, idx: Optional[int]) -> int:
            return result.addVertex(
                MindMapNode(data=MindMapNodeEntry(entry=entry, idx=idx)))

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
                if isinstance(link.resolved, DocEntry):
                    return entryNodes[link.resolved.content]

                else:
                    return subtreeNodes[link.resolved.original]

            else:
                assert False

        @beartype
        def auxNested(parent: int, nested: int):
            pass  # TODO implement subtree nested store structure

        @beartype
        def auxSubtree(tree: DocSubtree) -> int:
            desc = result.addVertex(MindMapNode(data=MindMapNodeSubtree(subtree=tree)))

            for sub in tree.subtrees:
                sub_desc = auxSubtree(sub)
                auxNested(parent=desc, nested=sub_desc)

            for idx, sub in enumerate(tree.ordered):
                entry = auxEntry(sub, idx)
                auxNested(parent=desc, nested=entry)

            for sub in tree.unordered:
                entry = auxEntry(sub, None)
                auxNested(parent=desc, nested=entry)

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
            upd_link = collector.getResolved(link)
            if upd_link.resolved:
                result.addEdge(
                    desc, getVertex(upd_link),
                    MindMapEdge(location=upd_link.location,
                                data=MindMapEdge.RefersTo(target=upd_link)))

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


class MindMapOpts(BaseModel, extra="forbid"):
    infile: List[Path]
    outfile: Path


@beartype
def getGraph(idProvider: NodeIdProvider, nodes: List[org.Org]) -> MindMapGraph:
    collector = MindMapCollector()
    collector.visitFiles(nodes)

    Path("/tmp/debug.json").write_text(json.dumps(to_debug_json(collector), indent=2))

    return MindMapGraph.FromCollector(
        idProvider=idProvider,
        collector=collector,
    )


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
