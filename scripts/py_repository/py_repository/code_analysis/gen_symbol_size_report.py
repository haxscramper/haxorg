from pathlib import Path
from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Tuple, Type, Callable
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
    log(CAT).info("Updating database for symbol sizes")
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
        get_build_root(ctx, "haxorg/reflection_tool"),
        args,
        env=env,
    )


@beartype
def _get_grouped_symbols(
    session: Session,
    by_head: bool,
    symbol_filter: Optional[Callable[[BinarySymbol], bool]] = None,
) -> list[tuple[Any, list[tuple[BinarySymbol, DemangledHead]]]]:
    query = (session.query(BinarySymbol, DemangledHead).join(
        DemangledHead, BinarySymbol.DemangledHeadId == DemangledHead.Id).order_by(
            DemangledHead.Id, BinarySymbol.Size.desc()))

    # Group symbols based on the specified criteria
    grouped_symbols: dict[Any, List[tuple[BinarySymbol, DemangledHead]]] = {}
    for symbol, head in query:
        if symbol_filter and not symbol_filter(symbol):
            continue

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
    symbols: List[BinarySymbol]
    nested: dict[str, "TreeNode"] = field(default_factory=dict)
    is_leaf: bool = False
    path: Optional[str] = None
    line: Optional[int] = None


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
                    current[part] = TreeNode(size=0, symbols=[])
                current = current[part].nested

            final_part = path_parts[-1]
            if final_part not in current:
                current[final_part] = TreeNode(size=0, symbols=[])

            line_key = f"line_{line}" if line > 0 else "line_unknown"
            current[final_part].nested[line_key] = TreeNode(
                size=total_size,
                is_leaf=True,
                line=line,
                path=file_path,
                symbols=[it[0] for it in symbols],
            )

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
                    path=node.path,
                    line=node.line,
                    symbols=node.symbols,
                )
        else:
            collapsed[key] = TreeNode(
                size=node.size,
                nested=_collapse_single_child_nodes(node.nested),
                is_leaf=node.is_leaf,
                path=node.path,
                line=node.line,
                symbols=node.symbols,
            )

    return collapsed


@dataclass
class TreemapItem:
    label: str
    parent: str
    size: int
    depth: int

    path: Optional[str]
    line: Optional[int]
    symbols: List[BinarySymbol]

    extra_hover: List[str] = field(default_factory=list)


@beartype
def _generate_treemap_data(tree: dict[str, TreeNode],
                           top_percent: float) -> list[TreemapItem]:
    treemap_data: list[TreemapItem] = []

    def traverse(nodes: dict[str, TreeNode], parent_label: str, path: str,
                 depth: int) -> None:
        # Check if this node has only leaf children
        has_non_leaf = any(node.nested for node in nodes.values())

        if has_non_leaf:
            # Has non-leaf subnodes, proceed without grouping
            for key, node in nodes.items():
                current_path = f"{path}/{key}" if path else key

                treemap_data.append(
                    TreemapItem(
                        label=current_path,
                        parent=parent_label,
                        size=node.size,
                        path=node.path,
                        line=node.line,
                        symbols=node.symbols,
                        depth=depth,
                    ))

                if node.nested:
                    traverse(node.nested, current_path, current_path, depth + 1)
        else:
            # All children are leaf nodes, apply grouping to this specific node
            leaf_items = list(nodes.items())

            if not leaf_items:
                return

            # Calculate how many items to keep (top N percent)
            num_items_to_keep = max(1, int(len(leaf_items) * (top_percent / 100)))

            # Sort by size (descending) and take top N percent
            sorted_items = sorted(leaf_items, key=lambda x: x[1].size, reverse=True)
            top_items = sorted_items[:num_items_to_keep]
            small_items = sorted_items[num_items_to_keep:]

            # Add top items
            for key, node in top_items:
                current_path = f"{path}/{key}" if path else key
                item = TreemapItem(
                    label=current_path,
                    parent=parent_label,
                    size=node.size,
                    path=node.path,
                    line=node.line,
                    symbols=node.symbols,
                    depth=depth,
                )

                item.extra_hover.append(f"Symbols: {len(node.symbols)}")
                for sym in node.symbols[:5]:
                    item.extra_hover.append(f"  {sym.Demangled[:200]}")

                treemap_data.append(item)

            # Group small items if any
            if small_items:
                total_size = sum(node.size for _, node in small_items)
                others_label = f"{parent_label}/Others ({len(small_items)} items)" if parent_label else f"Others ({len(small_items)} items)"
                item = TreemapItem(
                    label=others_label,
                    parent=parent_label,
                    size=total_size,
                    path=None,
                    line=None,
                    symbols=[node.symbols[0] for _, node in small_items if node.symbols],
                    depth=depth,
                )

                item.extra_hover.append(
                    f"Symbols: {sum([len(node[1].symbols) for node in small_items] + [0])}"
                )
                for it in small_items[:20]:
                    item.extra_hover.append(f"line:{it[1].line} size:{it[1].size}")
                    for sym in it[1].symbols[:5]:
                        item.extra_hover.append(f"  {sym.Demangled[:200]}")

                treemap_data.append(item)

    # Add root node
    treemap_data.append(
        TreemapItem(
            label="",
            parent="",
            size=0,
            path=None,
            line=None,
            symbols=[],
            depth=0,
        ))

    # Start traversal
    traverse(tree, "", "", 1)

    return treemap_data


@beartype
def _format_bytes(size: int) -> str:
    units = ["B", "KB", "MB", "GB", "TB", "PB"]
    unit_index = 0
    size_float = float(size)

    while size_float >= 1024 and unit_index < len(units) - 1:
        size_float /= 1024
        unit_index += 1

    if unit_index == 0:
        return f"{int(size_float)} {units[unit_index]}"
    else:
        return f"{size_float:.1f} {units[unit_index]}"


@beartype
def _get_visual_text(item: TreemapItem) -> str:
    """Text displayed on the treemap rectangle."""
    if item.line is not None and item.path is not None:
        # Leaf node with line info - show filename:line
        return f"{Path(item.path).stem}:{item.line}"
    elif item.line is not None:
        return f"{item.line}"
    elif item.label:
        # Show only the last part of the path (the key)
        parts = item.label.split("/")
        res = parts[-1] if parts else item.label
        return f"{res} {_format_bytes(item.size)}"
    else:
        return ""


@beartype
def _get_hover_text(item: TreemapItem) -> str:
    """Full hover text for an item."""
    parts = [f"<b>{item.label}</b>" if item.label else "<b>Root</b>"]
    parts.append(f"Size: {_format_bytes(item.size)}")
    if item.path:
        parts.append(f"File: {item.path}")
    if item.line is not None:
        parts.append(f"Line: {item.line}")

    parts.extend(item.extra_hover)

    return "<br>".join(parts)


def _assign_colors(treemap_data: list[TreemapItem],
                   max_color_depth: int = 3) -> dict[str, str]:
    """Assign colors based on hierarchy depth and parent grouping."""
    import plotly.colors as pc

    colors = {}

    # Available color palettes for different depths
    color_palettes = [
        pc.qualitative.Set1,
        pc.qualitative.Set2,
        pc.qualitative.Set3,
        pc.qualitative.Pastel1,
        pc.qualitative.Pastel2,
        pc.qualitative.Dark2,
    ]

    # Group items by depth
    items_by_depth: Dict[int, List[TreemapItem]] = {}
    for item in treemap_data:
        if item.depth not in items_by_depth:
            items_by_depth[item.depth] = []
        items_by_depth[item.depth].append(item)

    # Assign colors for depths 1 to max_color_depth
    for depth in range(1, max_color_depth + 1):
        if depth not in items_by_depth:
            continue

        # Get color palette for this depth (cycle through available palettes)
        palette_idx = (depth - 1) % len(color_palettes)
        current_palette = color_palettes[palette_idx]

        # Group items by parent at this depth
        items_by_parent: Dict[str, List[TreemapItem]] = {}
        for item in items_by_depth[depth]:
            if item.parent not in items_by_parent:
                items_by_parent[item.parent] = []
            items_by_parent[item.parent].append(item)

        # Assign colors to items at this depth
        color_counter = 0
        for parent, children in items_by_parent.items():
            for child in children:
                color_idx = color_counter % len(current_palette)
                colors[child.label] = current_palette[color_idx]
                color_counter += 1

    # For depths beyond max_color_depth, inherit parent's color
    for depth in sorted(items_by_depth.keys()):
        if depth > max_color_depth:
            for item in items_by_depth[depth]:
                parent_color = colors.get(item.parent)
                if parent_color:
                    colors[item.label] = parent_color

    return colors


@beartype
def _create_treemap_html(treemap_data: list["TreemapItem"], output_path: Path) -> None:
    import plotly.graph_objects as go

    if not treemap_data:
        return

    # IMPORTANT:
    # - Use `ids` / `parents` for hierarchy (keep full paths there).
    # - Use `labels` purely for what you want rendered visually (branches + leaves).

    # full unique hierarchical id (e.g., "a/b/c")
    ids = [item.label for item in treemap_data]
    # parent id (must match an `id`; "" or None for root)
    parents = [item.parent for item in treemap_data]
    values = [item.size for item in treemap_data]

    labels = [_get_visual_text(item) for item in treemap_data]
    hover_texts = [_get_hover_text(item) for item in treemap_data]

    # Assign colors
    color_map = _assign_colors(treemap_data)
    node_colors = [color_map.get(item.label, "lightgrey") for item in treemap_data]

    fig = go.Figure(
        go.Treemap(
            ids=ids,
            parents=parents,
            labels=labels,
            values=values,

            # Hover
            customdata=hover_texts,
            hovertemplate="%{customdata}<extra></extra>",
            branchvalues="total",

            # Text rendering (use label/value everywhere)
            texttemplate="%{label}<br>%{value}",
            textinfo="none",
            marker=dict(
                cornerradius=3,
                colors=node_colors,  # Apply our custom colors
                colorscale=None,  # Disable automatic colorscale
                line=dict(
                    color="gray",  # Border color
                    width=1  # Border width
                ),
            ),
        ))

    fig.update_traces(
        root_color="lightgrey",
        tiling=dict(packing="squarify"),
        pathbar=dict(
            textfont=dict(size=12),
            edgeshape=">",
        ),
    )

    fig.update_layout(
        title="Symbol Size Treemap",
        margin=dict(t=50, l=25, r=25, b=25),
    )

    fig.write_html(output_path)


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
    log(CAT).info("Generating binary symbol reports")
    assert ctx.config.binary_size_conf.output_db
    ensure_existing_dir(ctx, ctx.config.workflow_out_dir)
    session = open_sqlite_session(Path(ctx.config.binary_size_conf.output_db), Base)

    def symbol_filter(sym: BinarySymbol) -> bool:
        return sym.File and ("src/haxorg" in sym.File or
                             "src/hstd" in sym.File) and "build" not in sym.File

    group_by_file = _get_grouped_symbols(
        session,
        by_head=False,
        symbol_filter=symbol_filter,
    )

    _write_groups(
        ctx.config.workflow_out_dir.joinpath("symbol_report_by_file.txt"),
        group_by_file,
        False,
    )

    tree_structure = _build_tree_structure(group_by_file)
    collapsed_tree = _collapse_single_child_nodes(tree_structure)
    treemap_data = _generate_treemap_data(collapsed_tree, 30.0)

    report_path = ctx.config.workflow_out_dir / "symbol_tree_report.txt"
    _create_tree_report(collapsed_tree, report_path)
    log(CAT).info(f"Generated tree report: {report_path}")

    treemap_path = ctx.config.workflow_out_dir / "symbol_treemap.html"
    _create_treemap_html(treemap_data, treemap_path)
    log(CAT).info(f"Generated treemap: {treemap_path}")

    group_by_head = _get_grouped_symbols(session, by_head=True)
    _write_groups(ctx.config.workflow_out_dir.joinpath("symbol_report_by_head.txt"),
                  group_by_head, True)
