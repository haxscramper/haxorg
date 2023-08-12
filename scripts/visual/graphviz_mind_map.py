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


@dataclass_json
@dataclass
class OrgNode:
    kind: str = ""
    subnodes: List["OrgNode"] = field(default_factory=list)
    text: str = ""
    extra: Dict[str, any] = field(default_factory=dict)


def to_org_node(d: Dict[str, any]) -> OrgNode:
    res: OrgNode = OrgNode()
    if "subnodes" in d:
        for node in d["subnodes"]:
            res.subnodes.append(to_org_node(node))

    if "text" in d:
        res.text = d["text"]

    for key, val in d.items():
        if key not in ["subnodes", "text", "val"]:
            res.extra[key] = val

    res.kind = d["kind"]

    return res


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
        default=None, metadata=config(decoder=to_org_node)
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

    def rec_node(res: gv.Digraph, node: Node):
        if 0 == len(node.metadata.nested):
            res.node(
                node.metadata.nodeId,
                node.metadata.title,
            )

        else:
            with res.subgraph(
                name="cluster_" + node.metadata.nodeId
            ) as cluster:
                for nested in node.metadata.nested:
                    rec_node(cluster, graph.nodes[nested])

    dot = gv.Digraph("map")
    dot.attr("graph", rankdir="LR")
    dot.attr("node", shape="rect", font="Iosevka")
    dot.format = "png"

    for key, node in graph.nodes.items():
        rec_node(dot, node)

    for edge in graph.edges:
        if edge.metadata.kind not in ["NestedIn", "InternallyRefers"]:
            dot.edge(edge.source, edge.target)

    dot.render(directory="/tmp")


if __name__ == "__main__":
    cmd = click.CommandCollection(sources=[dot])
    cmd()
