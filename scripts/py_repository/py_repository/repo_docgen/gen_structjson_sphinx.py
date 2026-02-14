from dataclasses import dataclass, field
import enum
from pathlib import Path

from beartype import beartype
from beartype.typing import cast, Dict, Iterator, List, Mapping, Optional, Tuple
from pydantic import BaseModel, Field
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
class _SphinxPyObject():
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


@beartype
def _mk_function(name: str, full: str, obj: _SphinxPyObject) -> FunctionObject:
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
def _mk_attr(name: str, full: str, obj: _SphinxPyObject) -> AttributeObject:
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
def _get_or_create_class(class_full: str, class_short: str, obj: _SphinxPyObject,
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
    obj: _SphinxPyObject,
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
def _iterate_py_objects(py: PythonDomain) -> Iterator[_SphinxPyObject]:
    "Iterate over flat list of the python domain entires"
    return (_SphinxPyObject(
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

    def get_outdated_docs(self):
        "Force a full rebuild so the single JSON payload always reflects current state."
        return "all"

    def get_target_uri(self, docname: str, typ: str | None = None) -> str:
        "Return an empty URI since this builder does not emit per-document pages."
        return ""

    def prepare_writing(self, docnames) -> None:
        "No-op: this builder only emits a single JSON file in `finish()`."
        pass

    def write_doc(self, docname: str, doctree) -> None:
        "No-op: per-document output is not generated by this builder."
        pass

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

            match obj.objtype:
                case _SphinxObjType._function if len(remainder) == 1:
                    # Functions: pkg.mod.func
                    short = remainder[0]
                    mod_node.functions[obj.full_name] = _mk_function(
                        short, obj.full_name, obj)

                case _SphinxObjType._class if 1 <= len(remainder):
                    # Classes/exceptions: pkg.mod.Class
                    class_short = remainder[-1]
                    _get_or_create_class(obj.full_name, class_short, obj, mod_node)

                case _SphinxObjType._exception if 1 <= len(remainder):
                    exc_short = remainder[-1]
                    _get_or_create_exception(obj.full_name, exc_short, obj, mod_node)

                case _SphinxObjType._method if 2 <= len(remainder):
                    # Methods: pkg.mod.Class.method (or deeper: pkg.mod.Outer.Inner.method)
                    class_parts = remainder[:-1]
                    method_short = remainder[-1]
                    class_full = f"{mod_node.full_name}." + ".".join(class_parts)
                    cls = _get_or_create_class(class_full, class_parts[-1], obj, mod_node)
                    cls.methods.append(_mk_function(method_short, obj.full_name, obj))

                case _SphinxObjType._attribute | _SphinxObjType._data if 1 <= len(
                    remainder):
                    # Attributes/data: module-level or class-level
                    attr_short = remainder[-1]
                    if len(remainder) == 1:
                        mod_node.data[obj.full_name] = _mk_attr(
                            attr_short, obj.full_name, obj)
                    else:
                        class_parts = remainder[:-1]
                        class_full = f"{mod_node.full_name}." + ".".join(class_parts)
                        cls = _get_or_create_class(class_full, class_parts[-1], obj,
                                                   mod_node)
                        cls.attributes.append(_mk_attr(attr_short, obj.full_name, obj))

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
