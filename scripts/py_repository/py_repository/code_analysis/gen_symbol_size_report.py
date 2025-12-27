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


@dataclass
class TreemapItem:
    label: str
    size: int


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


@beartype
def _generate_treemap_data(tree: dict[str, TreeNode]) -> list[TreemapItem]:
    treemap_data: list[TreemapItem] = []

    def traverse(nodes: dict[str, TreeNode], path: str = "") -> None:
        for key, node in nodes.items():
            current_path = f"{path}/{key}" if path else key
            if key.startswith("line_"):
                last_path = path.split("/")[-1]
                current_label = f"{last_path}/{key[5:]}"

            else:
                current_label = key

            if node.is_leaf:
                treemap_data.append(TreemapItem(label=current_label, size=node.size))
            elif node.nested:
                traverse(node.nested, current_path)
            else:
                treemap_data.append(TreemapItem(label=current_label, size=node.size))

    traverse(tree)
    return treemap_data


@beartype
def _create_treemap_png(treemap_data: list[TreemapItem], output_path: Path) -> None:
    import matplotlib.pyplot as plt
    import matplotlib.patches as patches
    import squarify
    import numpy as np

    if not treemap_data:
        return

    total_size = sum(item.size for item in treemap_data)
    if total_size == 0:
        return

    plt.ioff()
    fig, ax = plt.subplots(figsize=(24, 16), dpi=150)

    sizes = [item.size for item in treemap_data]
    labels = [item.label for item in treemap_data]

    colors = plt.cm.Set3(np.linspace(0, 1, len(treemap_data)))

    squarify.plot(
        sizes=sizes,
        label=labels,
        color=colors,
        alpha=0.7,
        ax=ax,
        pad=True,
    )

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
