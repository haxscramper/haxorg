from dataclasses import dataclass, field
import enum
import importlib
import inspect
from pathlib import Path

from beartype import beartype
from beartype.typing import Any, cast, Dict, Iterator, List, Mapping, Optional, Tuple
from docutils import nodes
from pydantic import BaseModel, Field
from sphinx import addnodes
from sphinx.builders import Builder
from sphinx.domains.python import ModuleEntry, PythonDomain
from sphinx.util import logging

logger = logging.getLogger(__name__)


class DomainObject(BaseModel, extra="forbid"):
    """Base exported domain object with Sphinx location metadata."""
    name: str  # nodoc
    full_name: str  # nodoc
    display_name: str  # nodoc
    docname: str  # nodoc
    anchor: str  # nodoc
    priority: int  # nodoc
    doc_rendered: Optional[str] = None  # nodoc
    doc_line: Optional[int] = None  # nodoc
    doc_file: Optional[str] = None  # nodoc
    entry_source: Optional[str] = None  # nodoc
    doc_string: Optional[str] = None
    "Original text for the docstring"


class FunctionObject(DomainObject, extra="forbid"):
    """Module-level or class-level callable (function/method)."""
    pass


class AttributeObject(DomainObject, extra="forbid"):
    """Module-level or class-level attribute/data."""
    pass


class ClassObject(DomainObject, extra="forbid"):
    """Class-like object with nested members."""
    methods: List[FunctionObject] = Field(default_factory=list)  # nodoc
    attributes: List[AttributeObject] = Field(default_factory=list)  # nodoc


class ModuleMeta(BaseModel, extra="forbid"):
    """Sphinx module entry metadata from the Python domain."""
    full_name: str  # nodoc
    docname: str  # nodoc
    anchor: str  # nodoc
    synopsis: str  # nodoc
    platform: str  # nodoc
    deprecated: bool  # nodoc


class ModuleNode(BaseModel, extra="forbid"):
    """Module/package tree node with nested content."""
    name: str  # nodoc
    full_name: str  # nodoc
    meta: Optional[ModuleMeta] = None  # nodoc

    submodules: List["ModuleNode"] = Field(default_factory=list)  # nodoc

    functions: List[FunctionObject] = Field(default_factory=list)  # nodoc
    classes: List[ClassObject] = Field(default_factory=list)  # nodoc
    exceptions: List[ClassObject] = Field(default_factory=list)  # nodoc
    data: List[AttributeObject] = Field(default_factory=list)  # nodoc


class StructJSONPayload(BaseModel, extra="forbid"):
    """Top-level structured API export."""
    project: str  # nodoc
    version: str  # nodoc
    release: str  # nodoc
    root: ModuleNode  # nodoc


@dataclass
class _ModuleAcc:
    "Mutable module accessor"
    name: str
    "Unqualified name for the module"
    full_name: str
    "Fully qualified name for the module"
    meta: ModuleMeta | None = None
    "Optional extra information for the module"
    children: Dict[str, "_ModuleAcc"] = field(default_factory=dict)
    "Nested sub-modules"

    functions: Dict[str, FunctionObject] = field(default_factory=dict)
    "Functions defined at the toplevel of the module"
    classes: Dict[str, ClassObject] = field(default_factory=dict)
    "Classes at the module toplevel"
    exceptions: Dict[str, ClassObject] = field(default_factory=dict)
    "Exceptions the module defines"
    data: Dict[str, AttributeObject] = field(default_factory=dict)
    "Extra module data"


@beartype
def _ensure_module(root: _ModuleAcc, full_name: str,
                   index: Dict[str, _ModuleAcc]) -> _ModuleAcc:
    "Find or create a new module accessor for fully qualified name"
    parts: List[str] = full_name.split(".") if full_name else []
    node = root
    cur = ""
    for part in parts:
        cur = part if not cur else f"{cur}.{part}"
        child = node.children.get(part)
        if child is None:
            child = _ModuleAcc(name=part, full_name=cur)
            node.children[part] = child
            index[cur] = child
        node = child
    return node


@beartype
def _find_module_prefix(
        name: str,
        module_index: Mapping[str, _ModuleAcc]) -> Tuple[_ModuleAcc | None, List[str]]:
    "Get the module accessor and split qualified name"
    parts: List[str] = name.split(".")
    for i in range(len(parts), 0, -1):
        prefix = ".".join(parts[:i])
        mod = module_index.get(prefix)
        if mod is not None:
            return mod, parts[i:]
    return None, parts


@beartype
def _freeze(node: _ModuleAcc) -> ModuleNode:
    "Create fixed pydantic object from the module accessor"
    submodules = [
        _freeze(ch) for ch in sorted(node.children.values(), key=lambda x: x.name)
    ]
    return ModuleNode(
        name=node.name,
        full_name=node.full_name,
        meta=node.meta,
        submodules=submodules,
        functions=sorted(node.functions.values(), key=lambda x: x.name),
        classes=sorted(node.classes.values(), key=lambda x: x.name),
        exceptions=sorted(node.exceptions.values(), key=lambda x: x.name),
        data=sorted(node.data.values(), key=lambda x: x.name),
    )


class _SphinxObjType(str, enum.Enum):
    "Types of entires parsed by the sphinx python domain"
    _function = "function"  # nodoc
    _class = "class"  # nodoc
    _exception = "exception"  # nodoc
    _method = "method"  # nodoc
    _attribute = "attribute"  # nodoc
    _data = "data"  # nodoc
    _module = "module"  # nodoc


@beartype
@dataclass
class _SphinxPyDomainObject():
    "Typed representation of the sphinx python domain object"
    full_name: str
    "Fully qualified name."
    dispname: str
    "Name to display when searching/linking."
    objtype: _SphinxObjType
    "Object type, a key in self.object_types."
    docname: str
    "The document where it is to be found."
    anchor: str
    "The anchor name for the object."
    priority: int
    """
    How "important" the object is (determines placement in search results). One of:

    - `1` Default priority (placed before full-text matches).
    - `0` Object is important (placed before default-priority objects).
    - `2` Object is unimportant (placed after full-text matches).
    - `-1` Object should not show up in search at all.
    """


@dataclass
class _SphinxDescribedPyObject:
    "Typed representation of the documented python object"
    domain: str  # nodoc
    objtype: _SphinxObjType  # nodoc
    fullname: str  # often a fully-qualified name
    display_name: str  # nodoc
    doc_rendered: str  # nodoc
    "rendered doc text (from docstring/autodoc, etc.)"
    entry_source: Optional[str]
    "Source code of the documentable entry"
    doc_string: Optional[str]
    "Original text for the docstring"
    doc_line: Optional[int]
    "line number in rst (or None)"
    doc_file: Optional[str] = None  # nodoc


@beartype
def _resolve_fqn(fqn: str) -> Any:
    """
    Resolve 'pkg.mod.Class.method' -> python object.

    This is simplistic; you may need to handle properties, overloads, etc.
    """
    parts = fqn.split(".")
    if not parts:
        raise ValueError(f"Empty fqn: {fqn}")

    # Find the longest importable module prefix
    for i in range(len(parts), 0, -1):
        modname = ".".join(parts[:i])
        try:
            mod = importlib.import_module(modname)
        except Exception:
            continue

        obj: Any = mod
        for attr in parts[i:]:
            obj = getattr(obj, attr)
        return obj

    raise ImportError(f"Could not import any module from fqn: {fqn}")


@beartype
def _get_py_location(obj: Any) -> tuple[Optional[str], Optional[int]]:
    "Attempt to infer the source code location from the imported python item"
    try:
        src_file = inspect.getsourcefile(obj) or inspect.getfile(obj)
    except Exception:
        src_file = None

    try:
        _, start_line = inspect.getsourcelines(obj)
    except Exception:
        start_line = None

    return src_file, start_line


@beartype
def _iter_py_descriptions(doctree: nodes.document) -> Iterator[_SphinxDescribedPyObject]:
    "Iterate over a flat list of described python objects"
    for desc in doctree.findall(addnodes.desc):
        if desc.get("domain") != "py":
            continue

        objtype = desc.get("objtype", "")

        # One desc node can contain multiple signatures; usually one.
        sig = next(desc.findall(addnodes.desc_signature), None)
        if sig is None:
            continue

        # Sphinx commonly provides these attrs on the signature:
        # - 'fullname' (most useful when present)
        # - 'module'
        fullname = sig.get("fullname")
        module = sig.get("module")

        if not fullname:
            # Fallbacks vary by Sphinx version/themes/extensions
            names = sig.get("names") or []
            fullname = names[0] if names else sig.astext()

        # Try to build an FQN if Sphinx split module/fullname
        fqn = fullname
        if module and fullname and not fullname.startswith(module + "."):
            fqn = f"{module}.{fullname}"

        content = next(desc.findall(addnodes.desc_content), None)
        doc_rendered = content.astext().strip() if content is not None else ""

        try:
            obj = _resolve_fqn(fqn)

        except Exception:
            py_file, py_line = None, None
            obj = None

        else:
            py_file, py_line = _get_py_location(obj)

        result = _SphinxDescribedPyObject(
            domain="py",
            objtype=_SphinxObjType(objtype),
            fullname=fqn,
            display_name=sig.astext(),
            doc_rendered=doc_rendered,
            doc_string=getattr(obj, "__doc__", None),
            entry_source=getattr(desc, "source", None) or doctree.get("source"),
            doc_line=py_line or getattr(desc, "line", None),
            doc_file=py_file,
        )

        yield result


@beartype
def _mk_function(name: str, full: str, obj: _SphinxPyDomainObject) -> FunctionObject:
    "Create documented python function object"
    return FunctionObject(
        name=name,
        full_name=full,
        display_name=obj.dispname,
        docname=obj.docname,
        anchor=obj.anchor,
        priority=obj.priority,
    )


@beartype
def _mk_attr(name: str, full: str, obj: _SphinxPyDomainObject) -> AttributeObject:
    "Create documented python attribute object"
    return AttributeObject(
        name=name,
        full_name=full,
        display_name=obj.dispname,
        docname=obj.docname,
        anchor=obj.anchor,
        priority=obj.priority,
    )


@beartype
def _get_or_create_class(class_full: str, class_short: str, obj: _SphinxPyDomainObject,
                         mod_node: _ModuleAcc) -> ClassObject:
    "Create documented new documented class entry or return existing"
    existing = mod_node.classes.get(class_full)
    if existing is not None:
        return existing
    cls = ClassObject(
        name=class_short,
        full_name=class_full,
        display_name=obj.dispname,
        docname=obj.docname,
        anchor=obj.anchor,
        priority=obj.priority,
        methods=[],
        attributes=[],
    )
    mod_node.classes[class_full] = cls
    return cls


@beartype
def _get_or_create_exception(
    exc_full: str,
    exc_short: str,
    obj: _SphinxPyDomainObject,
    mod_node: _ModuleAcc,
) -> ClassObject:
    "Create documented exception object or return existing"
    existing = mod_node.exceptions.get(exc_full)
    if existing is not None:
        return existing
    exc = ClassObject(
        name=exc_short,
        full_name=exc_full,
        display_name=obj.dispname,
        docname=obj.docname,
        anchor=obj.anchor,
        priority=obj.priority,
        methods=[],
        attributes=[],
    )
    mod_node.exceptions[exc_full] = exc
    return exc


@beartype
def _iterate_py_objects(py: PythonDomain) -> Iterator[_SphinxPyDomainObject]:
    "Iterate over flat list of the python domain entires"
    return (_SphinxPyDomainObject(
        full_name,
        dispname,
        _SphinxObjType(objtype),
        docname,
        anchor,
        priority,
    ) for full_name, dispname, objtype, docname, anchor, priority in py.get_objects())


class StructJSONBuilder(Builder):
    """Structured JSON backend builder for Sphinx."""
    name = "structjson"  # nodoc
    format = "json"  # nodoc
    epilog = "Wrote api.json"  # nodoc

    def init(self) -> None:
        "Initialize builder state and resolve the output directory path."
        self._outdir = Path(self.outdir)
        self.collected: Dict[str, _SphinxDescribedPyObject] = dict()

    def get_outdated_docs(self):
        "Force a full rebuild so the single JSON payload always reflects current state."
        return "all"

    def get_target_uri(self, docname: str, typ: str | None = None) -> str:
        "Return an empty URI since this builder does not emit per-document pages."
        return ""

    def prepare_writing(self, docnames) -> None:
        "No-op: this builder only emits a single JSON file in `finish()`."
        pass

    def write_doc(self, docname: str, doctree: nodes.document) -> None:
        "Collect individual doctree entries into common list"
        # rst_path = self.env.doc2path(docname)
        for d in _iter_py_descriptions(doctree):
            self.collected[d.fullname] = d

    def finish(self) -> None:
        "Finalize structured JSON generation"
        py_domain = self.env.domains.get("py")
        if py_domain is None:
            raise RuntimeError("Python domain is not available")
        py = cast(PythonDomain, py_domain)

        # 1) Build module/package tree from module entries.
        root = _ModuleAcc(name="", full_name="")
        module_index: Dict[str, _ModuleAcc] = {}

        modules_data: Mapping[str, ModuleEntry] = cast(
            Mapping[str, ModuleEntry],
            py.data.get("modules", {}),
        )

        for modname, modinfo in modules_data.items():
            node = _ensure_module(root, modname, module_index)
            node.meta = ModuleMeta(
                full_name=modname,
                docname=modinfo.docname,
                anchor=modinfo.node_id,
                synopsis=modinfo.synopsis,
                platform=modinfo.platform,
                deprecated=bool(modinfo.deprecated),
            )

        # 2) Attach objects under the right module/class based on fully-qualified name.
        for obj in _iterate_py_objects(py):
            if obj.objtype == _SphinxObjType._module:
                # module tree already comes from py.data["modules"]
                continue

            mod_node, remainder = _find_module_prefix(obj.full_name, module_index)
            if mod_node is None:
                # Object not associated with any known module entry; skip.
                continue

            def update_docs(it: DomainObject):
                "nodoc"
                if it.full_name in self.collected:
                    sph = self.collected[it.full_name]
                    it.doc_rendered = sph.doc_rendered
                    it.doc_line = sph.doc_line
                    it.entry_source = sph.entry_source
                    it.doc_file = sph.doc_file
                    if sph.doc_string:
                        it.doc_string = sph.doc_string.strip()

            match obj.objtype:
                case _SphinxObjType._function if len(remainder) == 1:
                    # Functions: pkg.mod.func
                    short = remainder[0]
                    _function = _mk_function(short, obj.full_name, obj)
                    update_docs(_function)
                    mod_node.functions[obj.full_name] = _function

                case _SphinxObjType._class if 1 <= len(remainder):
                    # Classes/exceptions: pkg.mod.Class
                    class_short = remainder[-1]
                    _class = _get_or_create_class(obj.full_name, class_short, obj,
                                                  mod_node)
                    update_docs(_class)

                case _SphinxObjType._exception if 1 <= len(remainder):
                    exc_short = remainder[-1]
                    _exc = _get_or_create_exception(obj.full_name, exc_short, obj,
                                                    mod_node)
                    update_docs(_exc)

                case _SphinxObjType._method if 2 <= len(remainder):
                    # Methods: pkg.mod.Class.method (or deeper: pkg.mod.Outer.Inner.method)
                    class_parts = remainder[:-1]
                    method_short = remainder[-1]
                    class_full = f"{mod_node.full_name}." + ".".join(class_parts)
                    cls = _get_or_create_class(class_full, class_parts[-1], obj, mod_node)
                    update_docs(cls)
                    cls.methods.append(_mk_function(method_short, obj.full_name, obj))

                case _SphinxObjType._attribute | _SphinxObjType._data if 1 <= len(
                    remainder):
                    # Attributes/data: module-level or class-level
                    attr_short = remainder[-1]
                    if len(remainder) == 1:
                        _attr = _mk_attr(attr_short, obj.full_name, obj)
                        update_docs(_attr)
                        mod_node.data[obj.full_name] = _attr
                    else:
                        class_parts = remainder[:-1]
                        class_full = f"{mod_node.full_name}." + ".".join(class_parts)
                        cls = _get_or_create_class(class_full, class_parts[-1], obj,
                                                   mod_node)
                        _attr = _mk_attr(attr_short, obj.full_name, obj)
                        update_docs(_attr)
                        cls.attributes.append(_attr)

            # Other object kinds can be added later as needed (e.g. property, descriptor, etc.).

        payload = StructJSONPayload(
            project=self.config.project,
            version=self.config.version,
            release=self.config.release,
            root=_freeze(root),
        )

        self._outdir.mkdir(parents=True, exist_ok=True)
        out = self._outdir / "api.json"
        out.write_text(payload.model_dump_json(indent=2) + "\n", encoding="utf-8")
        logger.info("wrote %s", out)


def setup(app):
    "entry point for the sphinx extension"
    app.add_builder(StructJSONBuilder)
    return {"version": "0.1", "parallel_read_safe": True, "parallel_write_safe": True}
