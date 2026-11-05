"""Diagram model illustrating graph constraints expressed with the core DSL operations only.

Clusters cannot contain themselves because instance data is a tree, so that constraint is structural."""

import json
from pathlib import Path

from beartype.typing import Annotated, Dict, List, Optional, cast
from hstd_py_unidata.model_dsl import (
    EnFieldAnnotation,
    Float64,
    GenConfig,
    Severity,
    __check__,
    __variant__,
    get_dsl_model,
    op_all,
    op_concat,
    op_cond,
    op_filter,
    op_filter_map,
    op_format,
    op_group_by,
    op_let,
    op_map,
    op_or,
    op_path_of,
    op_walk,
    type_case,
    type_cond,
)
from hstd_py_unidata.model_expr import Expr
from hstd_py_unidata.model_gen import GenContext
from hstd_py_unidata.model_ir import NamedT
from hstd_py_unidata.model_value import (
    ListValue,
    OptValue,
    RecordValue,
    Value,
    VariantValue,
    walk_values,
)
from loguru import logger

M = get_dsl_model("dia.model")


def elements_of(root: Expr, type_name: str, binder: str) -> Expr:
    """Every value of the named record type contained in the root, the root included."""
    return op_filter_map(
        op_walk(root),
        f"{binder}_any",
        type_cond(
            M.Iter(f"{binder}_any"),
            type_case(M._T[type_name], binder, M.Iter(binder)),
            unhandled_ignore=True,
        ),
    )


def ids_of(root: Expr, type_name: str, binder: str) -> Expr:
    return op_map(
        elements_of(root, type_name, binder),
        f"{binder}_id",
        M.Iter(f"{binder}_id")["id"],
    )


def endpoints_in(ids: Expr, edge: Expr) -> Expr:
    return ids._List.contains(edge["source"]) & ids._List.contains(edge["target"])


class GraphvizEngine(M.Enum):
    Dot: Annotated[int, EnFieldAnnotation(doc="Hierarchical layout")] = 0
    Neato: Annotated[int, EnFieldAnnotation(doc="Spring model layout")] = 1
    Circo: Annotated[
        int, EnFieldAnnotation(doc="Circular layout, edge weights have no effect")
    ] = 2


class DiaElement(M.Class):
    class NoAlgo(M.Case):
        pass

    class Graphviz(M.Case):
        engine: GraphvizEngine

    class Kiwi(M.Case):
        strength: Float64

    id: str = M.Field(
        doc="Identifier, unique in the whole diagram",
        check=0 < M.This._Str.size(),
        message="element ids must not be empty",
    )
    __variant__(NoAlgo, Graphviz, Kiwi, field="algo", kind="AlgoKind")


class DiaNode(DiaElement, M.Class):
    label: str


class DiaEdge(DiaElement, M.Class):
    source: str
    target: str
    weight: Optional[Float64] = None

    __check__(
        id="no-self-loop",
        cond=M.This["source"] != M.This["target"],
        message=op_format(
            "edge {} connects node {} to itself", M.This["id"], M.This["source"]
        ),
    )


class DiaCluster(DiaElement, M.Class):
    nodes: List[DiaNode]
    edges: List[DiaEdge]
    clusters: List["DiaCluster"]

    __check__(
        id="edge-enclosed",
        cond=op_let(
            "local_ids",
            ids_of(M.This, "DiaNode", "local"),
            op_all(
                M.This["edges"],
                "edge",
                endpoints_in(M.Iter("local_ids"), M.Iter("edge")),
            ),
        ),
        message=op_format(
            "edges of cluster {} must connect nodes nested in the cluster", M.This["id"]
        ),
    )

    __check__(
        id="algorithm-consistency",
        cond=op_or(
            ~M.This["algo"]._Case.is_case("Kiwi"),
            op_all(
                op_concat(
                    op_map(
                        M.This["nodes"],
                        "node",
                        M.Iter("node")["algo"]._Case.which_case(),
                    ),
                    op_map(
                        M.This["edges"],
                        "edge",
                        M.Iter("edge")["algo"]._Case.which_case(),
                    ),
                ),
                "kind",
                ~M.Iter("kind")._Enum.is_val("Graphviz"),
            ),
        ),
        message=op_cond(
            (
                M.This["nodes"]._List.size() == 0,
                op_format("edges of kiwi cluster {} use graphviz", M.This["id"]),
            ),
            default=op_format("elements of kiwi cluster {} use graphviz", M.This["id"]),
        ),
    )

    __check__(
        id="ignored-edge-weight",
        level=Severity.WARNING,
        cond=op_or(
            ~M.This["algo"]._Case.is_case("Graphviz"),
            ~M.This["algo"]["engine"]._Enum.is_val("Circo"),
            op_all(M.This["edges"], "edge", ~M.Iter("edge")["weight"]._Opt.has_value()),
        ),
        message=op_format(
            "edge weights in cluster {} are ignored by the circo engine", M.This["id"]
        ),
    )


class Diagram(M.Class):
    root: DiaCluster

    __check__(
        id="no-dangling-edges",
        cond=op_let(
            "node_ids",
            ids_of(M.This["root"], "DiaNode", "node"),
            op_all(
                elements_of(M.This["root"], "DiaEdge", "edge"),
                "edge_ok",
                endpoints_in(M.Iter("node_ids"), M.Iter("edge_ok")),
            ),
        ),
        message=op_let(
            "node_ids",
            ids_of(M.This["root"], "DiaNode", "node"),
            op_format(
                "edges with unknown endpoints at {}",
                op_map(
                    op_filter(
                        elements_of(M.This["root"], "DiaEdge", "edge"),
                        "bad",
                        ~endpoints_in(M.Iter("node_ids"), M.Iter("bad")),
                    ),
                    "bad_edge",
                    op_path_of(M.Iter("bad_edge")),
                ),
            ),
        ),
    )

    __check__(
        id="unique-ids",
        cond=op_all(
            op_group_by(
                elements_of(M.This["root"], "DiaElement", "el"),
                "same_id",
                M.Iter("same_id")["id"],
            )._Map.values(),
            "group",
            M.Iter("group")._List.size() <= 1,
        ),
        message=op_format(
            "element ids are reused at {}",
            op_map(
                op_filter(
                    op_group_by(
                        elements_of(M.This["root"], "DiaElement", "el"),
                        "same_id",
                        M.Iter("same_id")["id"],
                    )._Map.values(),
                    "dup",
                    1 < M.Iter("dup")._List.size(),
                ),
                "dup_group",
                op_map(M.Iter("dup_group"), "dup_item", op_path_of(M.Iter("dup_item"))),
            ),
        ),
    )


def string_value(ctx: GenContext, text: str) -> Value:
    return ctx.decode(M.type_of(str), text)


def fresh_id(ctx: GenContext) -> Value:
    return string_value(ctx, ctx.fresh_name("el"))


def generate_cluster(ctx: GenContext) -> Value:
    """Edges connect distinct nodes of the same cluster, kiwi clusters keep their elements off graphviz."""
    algo_type = M.index.field(cast(NamedT, M.type_of(DiaElement)).qname, "algo").type
    algo = ctx.generate(algo_type)
    node_fixed: Dict[str, Value] = {}
    if isinstance(algo, VariantValue) and algo.tag == "Kiwi":
        node_fixed["algo"] = ctx.decode(algo_type, {"kind": "NoAlgo"})
    node_qname = cast(NamedT, M.type_of(DiaNode)).qname
    nodes = [
        ctx.generate_record(node_qname, dict(node_fixed))
        for _ in range(ctx.rng.randint(0, 4) if ctx.depth < 4 else 0)
    ]
    ids = [n.fields["id"] for n in nodes]
    edges: List[Value] = []
    for _ in range(ctx.rng.randint(0, 3) if 2 <= len(ids) else 0):
        source, target = ctx.rng.sample(ids, 2)
        edges.append(
            ctx.generate_record(
                cast(NamedT, M.type_of(DiaEdge)).qname,
                dict(node_fixed, source=source, target=target),
            )
        )
    clusters = (
        ctx.generate(M.type_of(List[DiaCluster]))
        if ctx.depth < 3
        else ListValue(items=())
    )
    return ctx.generate_record(
        cast(NamedT, M.type_of(DiaCluster)).qname,
        {
            "algo": algo,
            "nodes": ListValue(items=tuple(nodes)),
            "edges": ListValue(items=tuple(edges)),
            "clusters": clusters,
        },
    )


def generate_diagram(seed: int) -> Value:
    return M.generate(
        Diagram,
        GenConfig(seed=seed, max_collection=3),
        type_overrides={DiaCluster: generate_cluster},
        field_overrides={(DiaElement, "id"): fresh_id},
    )


def has_weighted_edge(value: Value) -> bool:
    """Sample property of an external consumer: the diagram exercises weighted edges."""
    for v in walk_values(value):
        if isinstance(v, RecordValue) and v.qname.name == "DiaEdge":
            weight = v.fields["weight"]
            if isinstance(weight, OptValue) and weight.value is not None:
                return True
    return False


def test_example_dia_main(stable_test_dir: Path):
    M.type_check()
    logger.info("Souffle type check passed")
    for seed in range(100):
        diagram = generate_diagram(seed)
        if has_weighted_edge(diagram):
            break
    else:
        raise RuntimeError(
            "None of the seeds 0..99 generated a diagram with a weighted edge"
        )
    for warning in M.validate(Diagram, diagram):
        logger.warning(warning.render())
    logger.info(
        f"Generated diagram with seed {seed}: {json.dumps(M.encode(Diagram, diagram))}"
    )
    result = M.reduce(Diagram, diagram, has_weighted_edge)
    logger.info(
        f"Reduced from {result.size_before} to {result.size_after} (nodes, magnitude) in {result.steps} step(s), "
        f"{result.predicate_calls} predicate call(s), {result.rejected_invalid} invalid candidate(s) skipped"
    )
    logger.info(f"Reduced diagram: {json.dumps(M.encode(Diagram, result.value))}")
