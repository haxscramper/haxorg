#!/usr/bin/env python

import rich_click as click
import json
from dataclasses import dataclass, field
from dataclasses_json import dataclass_json, config, Undefined
import graphviz as gv
import logging
from rich.logging import RichHandler
from typing import *
from pprint import pprint
from bs4 import BeautifulSoup

logging.basicConfig(
    level="NOTSET",
    format="%(message)s",
    datefmt="[%X]",
    handlers=[
        RichHandler(
            rich_tracebacks=True,
            markup=True,
            enable_link_path=False,
            show_time=False,
        )
    ],
)

for name in logging.root.manager.loggerDict:
    logger = logging.getLogger(name)
    logger.setLevel(logging.WARNING)

log = logging.getLogger("rich")
log.setLevel(logging.DEBUG)


@click.group()
def dot():
    pass


@dataclass_json
@dataclass
class EdgeMetadata:
    kind: str
    out_index: int


@dataclass_json
@dataclass
class Edge:
    source: str
    target: str
    metadata: EdgeMetadata


@dataclass
class OrgNode:
    kind: str = ""
    subnodes: List["OrgNode"] = field(default_factory=list)
    text: str = ""
    extra: Dict[str, any] = field(default_factory=dict)

    @staticmethod
    def from_dict(d: Dict[str, any]) -> "OrgNode":
        res: "OrgNode" = OrgNode()
        if "subnodes" in d:
            for node in d["subnodes"]:
                res.subnodes.append(OrgNode.from_dict(node))

        if "text" in d:
            res.text = d["text"]

        for key, val in d.items():
            if key not in ["subnodes", "text", "val"]:
                res.extra[key] = val

        res.kind = d["kind"]

        return res

    def is_leaf(self) -> bool:
        return (
            0 < len(self.text) and isinstance(self.text, str)
        ) or self.kind in ["Link"]

    def get_link_description(self) -> Optional["OrgNode"]:
        return (
            OrgNode.from_dict(self.extra["description"])
            if "description" in self.extra
            else None
        )

    def flat_text(self) -> str:
        match self.kind:
            case "Link":
                desc = self.get_link_description()
                if desc:
                    return desc.flat_text()

                else:
                    return "LINK"

            case _:
                return "".join([node.text for node in self.flatten()])

    def width(self) -> int:
        if 0 < len(self.flat_text()):
            return len(self.flat_text())

        else:
            result: int = 0
            for sub in self.subnodes:
                result += sub.width()

            return result

    def flatten(self) -> List["OrgNode"]:
        result: List["OrgNode"] = []
        if self.is_leaf():
            result.append(self)

        elif self.kind == "Caption":
            result = OrgNode.from_dict(self.text).flatten()

        else:
            for sub in self.subnodes:
                result += sub.flatten()

        return result

    def flat_wrap(self, max_width: int = 80) -> List[List["OrgNode"]]:
        lines: List[List["OrgNode"]] = [[]]

        current: int = 0
        for node in self.flatten():
            if node.kind == "Newline":
                node = OrgNode(kind="Space", text=" ")

            width = node.width()
            if not (current + width < max_width):
                lines.append([])
                current = 0

            lines[-1].append(node)
            current += width

        return lines


@dataclass_json
@dataclass
class NodeMetadata:
    nodeId: str = field(default="", metadata=config(field_name="id"))
    kind: str = ""
    level: Optional[int] = None
    parent: Optional[str] = None
    title: str = ""
    outgoing: List[str] = field(default_factory=list)
    nested: List[str] = field(default_factory=list)
    content: Optional[OrgNode] = field(
        default=None, metadata=config(decoder=OrgNode.from_dict)
    )


@dataclass_json
@dataclass
class Node:
    metadata: NodeMetadata


@dataclass_json
@dataclass
class Graph:
    metadata: Dict[str, any]
    edges: List[Edge]
    nodes: Dict[str, Node]


def format_node(
    dot: gv.Digraph, node: Node, entry_links: Set[Tuple[str, int, str]]
) -> str:
    soup = BeautifulSoup("<table></table>", "html.parser")
    # soup.table["BORDER"] = 0
    soup.table["CELLBORDER"] = 0
    soup.table["CELLSPACING"] = 0
    soup.table["CELLPADDING"] = 0

    meta: NodeMetadata = node.metadata
    lines: List[str] = []
    line: List[OrgNode]

    ROW_LINKS = True

    def wrap(node, tag):
        result = soup.new_tag(tag)
        result.append(node)
        return result

    def sub(node, tag):
        result = soup.new_tag(tag)
        node.append(result)
        return result

    MAX_ROWS = 30

    for idx, line in enumerate(meta.content.flat_wrap(80)):
        if MAX_ROWS < idx:
            break

        tokens = []
        for wordIdx, node in enumerate(line):
            if ROW_LINKS:
                tokens.append(node.flat_text())

            if node.kind == "Link":
                port = f"p{idx}" if ROW_LINKS else f"p{idx}_{wordIdx}"

                if not ROW_LINKS:
                    font = soup.new_tag("font")
                    font["COLOR"] = "blue"
                    font.string = node.flat_text()
                    td = wrap(font, "td")
                    td["PORT"] = port
                    tokens.append(td)

                if "map" in node.extra:
                    lmap = node.extra["map"]
                    entry_links.add(
                        (
                            lmap["source"],
                            lmap["out_index"],
                            lmap["target"],
                        )
                    )

                    dot.edge(
                        lmap["source"]
                        + ":"
                        + port
                        + (":e" if ROW_LINKS else ""),
                        lmap["target"],
                        **(
                            {"arrowtail": "box", "dir": "both"}
                            if ROW_LINKS
                            else {}
                        ),
                    )

            else:
                if not ROW_LINKS:
                    td = soup.new_tag("td")
                    td.string = node.flat_text()
                    tokens.append(td)

        if 0 == len(tokens):
            return ""

        if ROW_LINKS:
            tr = soup.new_tag("tr")
            td = soup.new_tag("td")
            td["PORT"] = f"p{idx}"
            tr.append(td)
            td.string = "".join(tokens)
            soup.table.append(tr)

        else:
            GRID_TEXT = False

            if GRID_TEXT:
                tr = soup.new_tag("tr")
                for td in tokens:
                    tr.append(td)

                soup.table.append(tr)

            else:
                nested_row = soup.new_tag("tr")

                for word in tokens:
                    nested_row.append(word)

                row_table = soup.new_tag("table")
                row_table["WIDTH"] = 120
                row_table["BORDER"] = 0
                row_table["CELLSPACING"] = 0
                row_table["CELLPADDING"] = 0
                # row_table["CELLBORDER"] = 0
                row_table.append(nested_row)
                td = soup.new_tag("td")
                td.append(row_table)
                tr = soup.new_tag("tr")
                tr.append(td)

                soup.table.append(tr)

    return "<\n" + str(soup) + ">"


@dot.command("dot")
@click.argument("file", type=click.Path())
def export_dot(file: str):
    log.info(f"Reading input file {file}")
    with open(file) as f:
        data = json.load(f)

    if not data:
        log.error("Could not read the input file into JSON object")
        return

    graph: Graph = Graph.from_dict(data)

    entry_links: Set[Tuple[str, int, str]] = set()

    dot = gv.Digraph("map")
    dot.attr("graph", rankdir="LR")
    dot.attr("node", shape="rect", font="Iosevka")
    dot.format = "png"
    dot.engine = "neato"
    dot.attr("graph", overlap="false", concentrate="true")

    def rec_node(res: gv.Digraph, node: Node):
        meta: NodeMetadata = node.metadata
        if 0 == len(meta.nested):
            if meta.kind == "Subtree":
                res.node(meta.nodeId, meta.title)

            else:
                res.node(
                    meta.nodeId,
                    format_node(dot, node, entry_links),
                    shape="plaintext",
                )

        else:
            with res.subgraph(name="cluster_" + meta.nodeId) as cluster:
                cluster.attr("graph", label=meta.title)
                for nested in meta.nested:
                    rec_node(cluster, graph.nodes[nested])

    nested: Set[str] = set()
    for _, node in graph.nodes.items():
        if node.metadata.kind == "Subtree":
            for item in node.metadata.nested:
                nested.add(item)

    for key, node in graph.nodes.items():
        if key not in nested:
            rec_node(dot, node)

    for edge in graph.edges:
        if edge.metadata.kind not in ["NestedIn", "InternallyRefers"]:
            if (
                edge.source,
                edge.metadata.out_index,
                edge.target,
            ) not in entry_links:
                dot.edge(edge.source, edge.target)

    dot.render(directory="/tmp")

    log.info("Export done")


if __name__ == "__main__":
    cmd = click.CommandCollection(sources=[dot])
    cmd()
