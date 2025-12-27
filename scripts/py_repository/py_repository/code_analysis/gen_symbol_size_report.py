from pathlib import Path
from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Tuple, Type
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import ensure_existing_dir, get_build_root, get_script_root
from py_repository.repo_tasks.workflow_utils import TaskContext

from sqlalchemy import create_engine, Column, select, Select
from sqlalchemy.schema import CreateTable
from sqlalchemy.orm import declarative_base, Session
from py_scriptutils.sqlalchemy_utils import IdColumn, ForeignId, IntColumn, StrColumn, BoolColumn, open_sqlite_session
from sqlalchemy.types import JSON
import json
from py_scriptutils.script_logging import log
from dataclasses import dataclass, field

CAT = __name__

Base: Type = declarative_base()


class BinarySection(Base):
    __tablename__ = "BinarySection"

    Id = IdColumn()
    Name = StrColumn()


class DemangledHead(Base):
    __tablename__ = "DemangledHead"

    Id = IdColumn()
    Kind = IntColumn()
    Fields = Column(JSON)


class DemangledNested(Base):
    __tablename__ = "DemangledNested"

    ComponentIndex = IntColumn()
    Parent = ForeignId("DemangledHead.Id")
    Self = ForeignId("DemangledHead.Id", nullable=True)

    __mapper_args__ = {"primary_key": [ComponentIndex, Parent]}


class BinarySymbol(Base):
    __tablename__ = "BinarySymbol"

    Id = IdColumn()
    Name = StrColumn()
    Demangled = StrColumn()
    DemangledHeadId = ForeignId("DemangledHead.Id")
    Size = IntColumn()
    Address = IntColumn()
    Section = ForeignId("BinarySection.Id")
    File = StrColumn(nullable=True)
    Line = IntColumn(nullable=True)
    Column = IntColumn(nullable=True)
    function = StrColumn(nullable=True)


@beartype
def generate_binary_size_db(ctx: TaskContext) -> None:
    assert ctx.config.binary_size_conf.binary_path, "Missing input binary path for the binary size report"
    assert ctx.config.binary_size_conf.output_db, "Missing output DB for binary size conf"

    args = [
        "--run-mode",
        "BinarySymbols",
        "--out",
        ctx.config.binary_size_conf.output_db,
        "--target-files",
        str(ctx.config.binary_size_conf.binary_path),
    ]

    if ctx.config.binary_size_conf.perf_out:
        args.append("--perf")
        args.append(ctx.config.binary_size_conf.perf_out)

    args.append("--")
    args.append(
        str(get_script_root(ctx,
                            "cxx_codegen/reflection_tool/clang_reflection_tool.cpp")))

    env = dict()

    if ctx.config.binary_size_conf.min_symbol_index:
        env["REFLECTION_TOOL_SYM_MIN"] = str(ctx.config.binary_size_conf.min_symbol_index)

    if ctx.config.binary_size_conf.max_symbol_index:
        env["REFLECTION_TOOL_SYM_MAX"] = str(ctx.config.binary_size_conf.max_symbol_index)

    run_command(
        ctx,
        get_build_root(ctx, "haxorg/scripts/cxx_codegen/reflection_tool/reflection_tool"),
        args,
        env=env,
    )


@beartype
def _get_grouped_symbols(
        session: Session,
        by_head: bool) -> list[tuple[Any, list[tuple[BinarySymbol, DemangledHead]]]]:
    query = (session.query(BinarySymbol, DemangledHead).join(
        DemangledHead, BinarySymbol.DemangledHeadId == DemangledHead.Id).order_by(
            DemangledHead.Id, BinarySymbol.Size.desc()))

    # Group symbols based on the specified criteria
    grouped_symbols: dict[Any, List[tuple[BinarySymbol, DemangledHead]]] = {}
    for symbol, head in query:
        if by_head:
            key = head.Id
        else:  # file_line
            key = (symbol.File or "", symbol.Line or 0)

        if key not in grouped_symbols:
            grouped_symbols[key] = []
        grouped_symbols[key].append((symbol, head))

    # Sort groups by total size
    sorted_groups = sorted(grouped_symbols.items(),
                           key=lambda item: sum(symbol.Size for symbol, _ in item[1]),
                           reverse=True)

    return sorted_groups


@beartype
def _write_groups(
    rep_path: Path,
    sorted_groups: list[tuple[Any, list[tuple[BinarySymbol, DemangledHead]]]],
    by_head: bool,
) -> None:
    with open(rep_path, "w") as f:
        for key, symbols_and_heads in sorted_groups:
            symbols = [s for s, _ in symbols_and_heads]
            total_size = sum(symbol.Size for symbol in symbols)
            average_size = total_size / len(symbols)

            # Write group header
            if by_head:
                head = symbols_and_heads[0][1]
                f.write(f"ID:{key} KIND:{head.Kind}\n")
                for line in json.dumps(head.Fields, indent=2).split("\n"):
                    f.write(f"  {line}\n")
            else:  # file_line
                file, line = key
                f.write(f"FILE:\"{file}\":{line}\n")

            # Write summary stats
            f.write(f"  total_size = {total_size}\n")
            f.write(f"  average_size = {average_size}\n")

            # Write individual symbols
            for symbol, head in symbols_and_heads:
                f.write(f"  {symbol.Size}")

                if by_head:
                    if symbol.File and symbol.Line:
                        f.write(f" \"{symbol.File}\":{symbol.Line}")
                    f.write(f" {symbol.Demangled}\n")
                else:  # file_line
                    f.write(f" ID:{head.Id} KIND:{head.Kind} {symbol.Demangled}\n")

    log(CAT).info(f"Wrote symbol report to {rep_path}")


@dataclass
class TreeNode:
    size: int
    nested: dict[str, "TreeNode"] = field(default_factory=dict)
    is_leaf: bool = False


@beartype
def _normalize_and_collapse_path(path: str) -> list[str]:
    if not path:
        return ["<empty>"]

    normalized = Path(path).as_posix()
    parts = [part for part in normalized.split("/") if part]

    if not parts:
        return ["<empty>"]

    return parts


@beartype
def _build_tree_structure(
    grouped_symbols: list[tuple[Any, list[tuple[BinarySymbol, DemangledHead]]]]
) -> dict[str, TreeNode]:
    tree: dict[str, TreeNode] = {}

    for key, symbols in grouped_symbols:
        if isinstance(key, tuple):
            file_path, line = key
            total_size = sum(symbol.Size for symbol, _ in symbols)

            path_parts = _normalize_and_collapse_path(file_path)

            current = tree
            for part in path_parts[:-1]:
                if part not in current:
                    current[part] = TreeNode(size=0)
                current = current[part].nested

            final_part = path_parts[-1]
            if final_part not in current:
                current[final_part] = TreeNode(size=0)

            line_key = f"line_{line}" if line > 0 else "line_unknown"
            current[final_part].nested[line_key] = TreeNode(size=total_size, is_leaf=True)

            node_dict = tree
            for part in path_parts:
                if part in node_dict:
                    node_dict[part].size += total_size
                node_dict = node_dict[part].nested

    return tree


@beartype
def _collapse_single_child_nodes(tree: dict[str, TreeNode]) -> dict[str, TreeNode]:
    collapsed: dict[str, TreeNode] = {}

    for key, node in tree.items():
        if len(node.nested) == 1 and not node.is_leaf:
            child_key, child_node = next(iter(node.nested.items()))
            if not child_node.is_leaf:
                collapsed_child = _collapse_single_child_nodes({child_key: child_node})
                for collapsed_key, collapsed_node in collapsed_child.items():
                    new_key = f"{key}/{collapsed_key}"
                    collapsed[new_key] = collapsed_node
            else:
                collapsed[key] = TreeNode(
                    size=node.size,
                    nested=node.nested,
                    is_leaf=node.is_leaf,
                )
        else:
            collapsed[key] = TreeNode(
                size=node.size,
                nested=_collapse_single_child_nodes(node.nested),
                is_leaf=node.is_leaf,
            )

    return collapsed


@dataclass
class TreemapRect:
    label: str
    size: int
    depth: int
    x: float
    y: float
    width: float
    height: float
    is_leaf: bool
    has_children: bool


@beartype
def _generate_treemap_data(tree: dict[str, TreeNode]) -> list[TreemapRect]:
    treemap_rects: list[TreemapRect] = []

    def compute_rects(nodes: dict[str, TreeNode],
                      x: float,
                      y: float,
                      width: float,
                      height: float,
                      depth: int,
                      path: str = "") -> None:
        import squarify

        if not nodes:
            return

        sizes = [node.size for node in nodes.values()]
        total_size = sum(sizes)
        if total_size == 0:
            return

        normalized_sizes = [s / total_size * width * height for s in sizes]
        rects = squarify.squarify(normalized_sizes, x, y, width, height)

        for (key, node), rect in zip(nodes.items(), rects):
            current_path = f"{path}/{key}" if path else key
            if key.startswith("line_"):
                last_path = path.split("/")[-1]
                current_label = f"{last_path}/{key[5:]}"
            else:
                current_label = key

            treemap_rects.append(
                TreemapRect(label=current_label,
                            size=node.size,
                            depth=depth,
                            x=rect["x"],
                            y=rect["y"],
                            width=rect["dx"],
                            height=rect["dy"],
                            is_leaf=node.is_leaf,
                            has_children=bool(node.nested)))

            if node.nested:
                padding = 0.02 * min(rect["dx"], rect["dy"])
                inner_x = rect["x"] + padding
                inner_y = rect["y"] + padding
                inner_width = rect["dx"] - 2 * padding
                inner_height = rect["dy"] - 2 * padding

                if 0 < inner_width and 0 < inner_height:
                    compute_rects(node.nested, inner_x, inner_y, inner_width,
                                  inner_height, depth + 1, current_path)

    compute_rects(nodes=tree, x=0, y=0, width=100, height=100, depth=0)
    return treemap_rects


@beartype
def _create_treemap_png(treemap_data: list[TreemapRect], output_path: Path) -> None:
    import matplotlib.pyplot as plt
    import matplotlib.patches as patches
    import numpy as np

    if not treemap_data:
        return

    plt.ioff()
    fig, ax = plt.subplots(figsize=(24, 16), dpi=150)

    max_depth = max(item.depth for item in treemap_data)
    colormaps = [plt.cm.Set3, plt.cm.Pastel1, plt.cm.Pastel2, plt.cm.Set2, plt.cm.Accent]

    depth_items: dict[int, list[TreemapRect]] = {}
    for item in treemap_data:
        if item.depth not in depth_items:
            depth_items[item.depth] = []
        depth_items[item.depth].append(item)

    sorted_rects = sorted(treemap_data, key=lambda r: r.depth)

    for item in sorted_rects:
        cmap = colormaps[item.depth % len(colormaps)]
        items_at_depth = depth_items[item.depth]
        idx = items_at_depth.index(item)
        color = cmap(idx /
                     max(1,
                         len(items_at_depth) - 1) if 1 < len(items_at_depth) else 0.5)

        alpha = 0.9 - (item.depth * 0.1)
        alpha = max(0.3, alpha)

        rect = patches.Rectangle((item.x, item.y),
                                 item.width,
                                 item.height,
                                 linewidth=max(0.5, 2 - item.depth * 0.3),
                                 edgecolor="black",
                                 facecolor=color,
                                 alpha=alpha)
        ax.add_patch(rect)

        min_dimension = min(item.width, item.height)
        if 3 < min_dimension:
            fontsize = max(4, min(10, min_dimension * 0.8))
            label_text = item.label
            if 8 < len(label_text) and min_dimension < 10:
                label_text = label_text[:7] + "..."

            text_y = item.y + item.height - fontsize * 0.15 if item.has_children else item.y + item.height / 2

            ax.text(item.x + item.width / 2,
                    text_y,
                    label_text,
                    ha="center",
                    va="top" if item.has_children else "center",
                    fontsize=fontsize,
                    wrap=True)

    ax.set_xlim(0, 100)
    ax.set_ylim(0, 100)
    ax.set_title("Symbol Size Treemap", fontsize=14, pad=15)
    ax.axis("off")

    plt.tight_layout()
    plt.savefig(output_path, dpi=150, format="png")
    plt.close(fig)
    plt.ion()


@beartype
def _create_tree_report(tree: dict[str, TreeNode], output_path: Path) -> None:
    from rich.tree import Tree
    from rich.console import Console

    console = Console(record=True,
                      width=120,
                      file=open(output_path, "w", encoding="utf-8"))
    root = Tree("Symbol Tree Report")

    def add_to_tree(nodes: dict[str, TreeNode], tree_node: Tree, path: str = "") -> None:
        for key, node in sorted(nodes.items(), key=lambda x: x[1].size, reverse=True):
            current_path = f"{path}/{key}" if path else key

            if node.is_leaf:
                label = f"{key} (size: {node.size})"
                tree_node.add(label)
            elif node.nested:
                label = f"{key} (total: {node.size})"
                child_tree = tree_node.add(label)
                add_to_tree(node.nested, child_tree, current_path)
            else:
                label = f"{key} (size: {node.size})"
                tree_node.add(label)

    add_to_tree(tree, root)
    console.print(root)
    console.file.close()
    tree_content = output_path.read_text().replace("│   ", "    ").replace(
        "├── ", "    ").replace("└── ", "    ")
    output_path.write_text(tree_content)


@beartype
def generate_symbol_size_report(ctx: TaskContext) -> None:
    assert ctx.config.binary_size_conf.output_db
    ensure_existing_dir(ctx, ctx.config.workflow_out_dir)
    session = open_sqlite_session(Path(ctx.config.binary_size_conf.output_db), Base)

    group_by_head = _get_grouped_symbols(session, by_head=True)
    _write_groups(ctx.config.workflow_out_dir.joinpath("symbol_report_by_head.txt"),
                  group_by_head, True)

    group_by_file = _get_grouped_symbols(session, by_head=False)
    _write_groups(ctx.config.workflow_out_dir.joinpath("symbol_report_by_file.txt"),
                  group_by_file, False)

    tree_structure = _build_tree_structure(group_by_file)
    collapsed_tree = _collapse_single_child_nodes(tree_structure)
    treemap_data = _generate_treemap_data(collapsed_tree)

    report_path = ctx.config.workflow_out_dir / "symbol_tree_report.txt"
    _create_tree_report(collapsed_tree, report_path)
    log(CAT).info(f"Generated tree report: {report_path}")

    treemap_path = ctx.config.workflow_out_dir / "symbol_treemap.png"
    _create_treemap_png(treemap_data, treemap_path)
    log(CAT).info(f"Generated treemap: {treemap_path}")
