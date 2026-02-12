import ast
import importlib.util
from pathlib import Path

from beartype import beartype
from beartype.typing import Optional
from graphviz import Digraph
import grimp
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
def import_graph_to_graphviz(graph: ImportGraph) -> Digraph:
    """
    Convert ImportGraph to a Graphviz Digraph with package-based clustering.

    Each package is rendered as a cluster containing its modules. Import edges
    point from the importing module to the imported module. External dependencies
    (imports from outside the analyzed packages) are shown as dashed ellipses.
    """
    dot = Digraph(name="import_graph", engine="dot")
    dot.attr(rankdir="LR", compound="true", fontsize="12")

    # Collect valid analyses and all known modules
    analyses: dict[str, PackageAnalysis] = {}
    internal_modules: set[str] = set()

    for pkg_name, pkg_data in graph.packages.items():
        if isinstance(pkg_data, PackageAnalysis):
            analyses[pkg_name] = pkg_data
            internal_modules.update(pkg_data.modules)

    # Create clusters for each package
    for pkg_name, analysis in analyses.items():
        # Sanitize name for Graphviz ID (cluster names must be valid identifiers)
        cluster_id = f"cluster_{pkg_name.replace('.', '_').replace('-', '_')}"

        with dot.subgraph(name=cluster_id) as cluster:
            cluster.attr(label=pkg_name,
                         style="rounded,filled",
                         fillcolor="lightgrey",
                         color="black",
                         fontname="Helvetica")

            for module in analysis.modules:
                cluster.node(module,
                             module,
                             shape="box",
                             style="filled",
                             fillcolor="white")

    # Draw edges for all import relationships
    for analysis in analyses.values():
        for module_name, deps in analysis.dependencies.items():
            for imported in deps.internal + deps.workspace:
                # Handle external dependencies (not in any analyzed package)
                if imported.get_name() not in internal_modules:
                    dot.node(imported.get_name(),
                             imported.get_name(),
                             shape="ellipse",
                             style="dashed,filled",
                             fillcolor="lightyellow",
                             fontsize="10")

                dot.edge(module_name, imported.get_name(), arrowsize="0.7")

    return dot
