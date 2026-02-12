import ast
import importlib.util
from pathlib import Path

from beartype import beartype
from beartype.typing import Optional
from graphviz import Digraph
import grimp
import igraph
from py_repository.repo_tasks.common import get_script_root
from py_repository.repo_tasks.workflow_utils import TaskContext
from py_scriptutils.script_logging import log
from pydantic import BaseModel, Field

CAT = __name__


class ImportStmt(BaseModel, frozen=True):
    """
    Full description of the import statement as found in the source
    code of the module.
    """
    qual_name: tuple[str, ...] = Field(default_factory=tuple,
                                       description="Fully qualified import name")
    imported_names: tuple[str, ...] = Field(
        default_factory=tuple,
        description="Name of the classes and functions imported from module")
    toplevel: bool = Field(
        default=False,
        description=
        "Is the import statement on the top of the file, or it is conditionally executed")

    def get_name(self) -> str:
        """Get fully qualified name as a string"""
        return ".".join(self.qual_name)


class ModuleDependencies(BaseModel):
    """Import relationships for a single module."""
    internal: list[ImportStmt] = Field(default_factory=list,
                                       description="Modules within the same package")
    workspace: list[ImportStmt] = Field(
        default_factory=list, description="Modules from other workspace packages")
    external: list[ImportStmt] = Field(default_factory=list,
                                       description="Modules from external packages")


class PackageAnalysis(BaseModel):
    """Analysis result for a single Python package."""
    modules: list[str] = Field(description="All modules discovered in this package")
    dependencies: dict[str, ModuleDependencies] = Field(
        default_factory=dict,
        description=
        "Per-module dependency information, keyed by fully qualified module name",
    )


class PackageError(BaseModel):
    """Error encountered while analyzing a package."""
    error: str = Field(description="Error message describing what went wrong")


class ImportGraph(BaseModel):
    """Complete import graph for a workspace."""
    packages: dict[str, PackageAnalysis | PackageError] = Field(
        default_factory=dict,
        description="Analysis results keyed by 'package_name/module_name'")


@beartype
def _module_source_path(module_name: str) -> Path:
    """
    Get absolute path to the module source
    """
    spec = importlib.util.find_spec(module_name)
    if spec is None or spec.origin is None:
        raise ModuleNotFoundError(module_name)
    return Path(spec.origin)


@beartype
def _resolve_from_import(current_module: str, level: int,
                         imported_module: str | None) -> str:
    """
    Resolve module import name to absolute one
    """
    base = imported_module or ""
    if level == 0:
        return base
    rel = "." * level + base
    return importlib.util.resolve_name(rel, current_module)


@beartype
def _find_fully_qualified_imports(module_name: str) -> set[ImportStmt]:
    """
    Recursively collect all import statement from the module source.
    """
    src_path = _module_source_path(module_name)
    code = src_path.read_text(encoding="utf-8")
    tree = ast.parse(code, filename=str(src_path))

    out: set[ImportStmt] = set()

    for node in ast.walk(tree):
        # Determine if this is a top-level import
        toplevel = getattr(node, 'col_offset', 0) == 0

        if isinstance(node, ast.Import):
            for alias in node.names:
                qual_name = tuple(alias.name.split("."))
                imported_names = (alias.asname,) if alias.asname else ()
                out.add(
                    ImportStmt(qual_name=qual_name,
                               imported_names=imported_names,
                               toplevel=toplevel))

        elif isinstance(node, ast.ImportFrom):
            if node.level == 0 and node.module is None:
                continue
            resolved = _resolve_from_import(module_name, node.level, node.module)
            qual_name = tuple(resolved.split("."))
            imported_names = tuple(alias.name for alias in node.names)
            out.add(
                ImportStmt(qual_name=qual_name,
                           imported_names=imported_names,
                           toplevel=toplevel))

    return out


@beartype
def _find_module_dependencies(
    graph: grimp.ImportGraph,
    module: str,
    module_name: str,
    workspace_packages: set[str],
) -> Optional[ModuleDependencies]:
    """
    Find all imports by the input module.
    """
    imported = _find_fully_qualified_imports(module)

    internal: list[ImportStmt] = []
    workspace_imports: list[ImportStmt] = []
    external: list[ImportStmt] = []

    for imp in imported:
        imp_pkg = imp.qual_name[0] if imp.qual_name else ""

        if imp_pkg == module_name:
            internal.append(imp)
        elif imp_pkg in workspace_packages:
            workspace_imports.append(imp)
        else:
            external.append(imp)

    if internal or workspace_imports or external:
        return ModuleDependencies(
            internal=internal,
            workspace=workspace_imports,
            external=external,
        )


@beartype
def gen_import_graph(ctx: TaskContext) -> ImportGraph:
    """Analyze imports across all packages in a uv workspace."""
    result = ImportGraph()

    packages = []
    for pyproject in get_script_root(ctx).rglob("pyproject.toml"):
        pkg_dir = pyproject.parent
        for src_candidate in [pkg_dir / "src", pkg_dir]:
            if src_candidate.exists() and (any(src_candidate.glob("*.py")) or any(
                    d.is_dir() and (d / "__init__.py").exists()
                    for d in src_candidate.iterdir()
                    if d.is_dir())):
                packages.append((pkg_dir.name, src_candidate))
                break

    workspace_packages = {pkg_name for pkg_name, _ in packages}
    log(CAT).info(f"Workspace packages {workspace_packages}")

    for pkg_name, src_path in packages:
        pkg_modules = [
            d.name
            for d in src_path.iterdir()
            if d.is_dir() and (d / "__init__.py").exists()
        ]

        for module_name in pkg_modules:
            key = f"{pkg_name}/{module_name}"
            try:
                graph = grimp.build_graph(module_name, include_external_packages=True)
            except Exception as e:
                result.packages[key] = PackageError(error=str(e))
                continue

            module_deps: dict[str, ModuleDependencies] = {}
            own_modules = [
                m for m in graph.modules
                if m == module_name or m.startswith(f"{module_name}.")
            ]

            for module in own_modules:
                deps = _find_module_dependencies(
                    graph,
                    module,
                    module_name=module_name,
                    workspace_packages=workspace_packages,
                )
                if deps:
                    module_deps[module] = deps

            result.packages[key] = PackageAnalysis(
                modules=own_modules,
                dependencies=module_deps,
            )

    return result


@beartype
def import_graph_to_igraph(graph: ImportGraph) -> igraph.Graph:
    """
    Convert ImportGraph to an igraph Graph with vertex attributes for
    module name, package membership, and external status.
    """
    g = igraph.Graph(directed=True)

    # module_name -> package_name (None for external modules)
    module_packages: dict[str, str | None] = {}

    # First pass: collect internal modules with their package assignments
    for pkg_name, pkg_data in graph.packages.items():
        if isinstance(pkg_data, PackageAnalysis):
            for module in pkg_data.modules:
                module_packages[module] = pkg_name

    # Second pass: collect import edges and identify external dependencies
    edges: list[tuple[str, str]] = []

    for pkg_name, pkg_data in graph.packages.items():
        if isinstance(pkg_data, PackageAnalysis):
            for module_name, deps in pkg_data.dependencies.items():
                for imported in deps.internal + deps.workspace:
                    target = imported.get_name()
                    edges.append((module_name, target))

                    # External modules are those not in any analyzed package
                    if target not in module_packages:
                        module_packages[target] = None

    if not module_packages:
        return g

    # Create vertices with attributes
    module_names = list(module_packages.keys())
    g.add_vertices(len(module_names))
    g.vs["name"] = module_names
    g.vs["package"] = [module_packages[m] for m in module_names]
    g.vs["is_external"] = [module_packages[m] is None for m in module_names]

    # Map names to indices for edge creation
    name_to_idx = {name: idx for idx, name in enumerate(module_names)}

    # Add edges as vertex indices
    edge_indices = [(name_to_idx[src], name_to_idx[dst])
                    for src, dst in edges
                    if src in name_to_idx and dst in name_to_idx]

    if edge_indices:
        g.add_edges(edge_indices)

    return g


@beartype
def import_igraph_to_graphviz(g: igraph.Graph) -> Digraph:
    """
    Convert igraph Graph to Graphviz Digraph with package-based clustering.

    Analyzes edge directions between packages. If imports between two packages
    predominantly flow in one direction, edges going the opposite direction
    (back edges) are colored red.
    """
    dot = Digraph(name="import_graph", engine="dot")
    dot.attr(rankdir="LR", compound="true", fontsize="12")

    # Group vertices: by package for internals, separate list for externals
    packages: dict[str, list[int]] = {}
    external_indices: list[int] = []

    for v in g.vs:
        if v["is_external"]:
            external_indices.append(v.index)
        else:
            pkg = v["package"]
            packages.setdefault(pkg, []).append(v.index)

    # Create clusters for each package
    for pkg_name, indices in packages.items():
        cluster_id = f"cluster_{pkg_name.replace('.', '_').replace('-', '_')}"

        with dot.subgraph(name=cluster_id) as cluster:
            cluster.attr(label=pkg_name,
                         style="rounded,filled",
                         fillcolor="lightgrey",
                         color="black",
                         fontname="Helvetica")

            for idx in indices:
                v = g.vs[idx]
                cluster.node(v["name"],
                             v["name"],
                             shape="box",
                             style="filled",
                             fillcolor="white")

    # Add external dependencies as dashed ellipses outside clusters
    for idx in external_indices:
        v = g.vs[idx]
        dot.node(v["name"],
                 v["name"],
                 shape="ellipse",
                 style="dashed,filled",
                 fillcolor="lightyellow",
                 fontsize="10")

    # Analyze edge directions between distinct internal packages
    edge_counts: dict[tuple[str, str], list[int]] = {}

    for e in g.es:
        src_pkg = g.vs[e.source]["package"]
        dst_pkg = g.vs[e.target]["package"]

        # Only consider inter-package edges between internal packages
        if src_pkg is None or dst_pkg is None or src_pkg == dst_pkg:
            continue

        key = (src_pkg, dst_pkg)
        edge_counts.setdefault(key, []).append(e.index)

    # Identify back edges (minority direction between package pairs)
    back_edges: set[int] = set()
    processed_pairs: set[frozenset[str]] = set()

    for (src_pkg, dst_pkg), indices in edge_counts.items():
        pair = frozenset([src_pkg, dst_pkg])
        if pair in processed_pairs:
            continue
        processed_pairs.add(pair)

        reverse_indices = edge_counts.get((dst_pkg, src_pkg), [])
        if not reverse_indices:
            continue

        forward_count = len(indices)
        backward_count = len(reverse_indices)

        if forward_count > backward_count:
            back_edges.update(reverse_indices)
        elif backward_count > forward_count:
            back_edges.update(indices)

    # Draw all edges, coloring back edges red
    for e in g.es:
        source = g.vs[e.source]["name"]
        target = g.vs[e.target]["name"]

        if e.index in back_edges:
            dot.edge(source, target, arrowsize="0.7", color="red", penwidth="2")
        else:
            dot.edge(source, target, arrowsize="0.7")

    return dot
