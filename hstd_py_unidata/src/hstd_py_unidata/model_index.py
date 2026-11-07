from __future__ import annotations

from beartype import beartype
from beartype.typing import Dict, List, Optional, Set, Tuple

from hstd_py_unidata.model_ir import (
    ArrayT,
    CheckDef,
    ClassConfig,
    DynT,
    EnumDef,
    EnumValueDef,
    ExternalT,
    FieldDef,
    ListT,
    MapT,
    ModelDef,
    NamedT,
    OptT,
    PrimT,
    QName,
    RecordDef,
    RecordKind,
    TupleT,
    TypeParamT,
    TypeRef,
    UnresolvedT,
    VariantCaseDef,
    VariantDef,
    VariantT,
)


@beartype
class ModelIndex:
    """Derived lookup tables over a finalized model: ancestry, effective fields, variants, checks."""

    def __init__(self, model: ModelDef) -> None:
        self.model = model
        self.records: Dict[QName, RecordDef] = {r.qname: r for r in model.records}
        self.enums: Dict[QName, EnumDef] = {e.qname: e for e in model.enums}
        declarations = model.records + model.enums
        self.by_id: Dict[str, QName] = {
            declaration.qname.to_id(): declaration.qname for declaration in declarations
        }
        self.order: Dict[QName, int] = {
            declaration.qname: i for i, declaration in enumerate(declarations)
        }
        self.field_cache: Dict[QName, Tuple[FieldDef, ...]] = {}
        self.ancestor_cache: Dict[QName, Tuple[QName, ...]] = {}

    def has_record(self, qname: QName) -> bool:
        return qname in self.records

    def record(self, qname: QName) -> RecordDef:
        if qname not in self.records:
            known = ", ".join(sorted(self.by_id)[:30])
            raise KeyError(
                f"Record '{qname.to_id()}' is not declared in model '{self.model.package}'; known records: {known}"
            )
        return self.records[qname]

    def record_by_id(self, text: str) -> RecordDef:
        qname = self.by_id.get(text)
        if qname is None or qname not in self.records:
            known = ", ".join(sorted(q.to_id() for q in self.records)[:30])
            raise KeyError(
                f"Record id '{text}' is not a record in model '{self.model.package}'; known records: {known}"
            )
        return self.records[qname]

    def enum_by_id(self, text: str) -> EnumDef:
        qname = self.by_id.get(text)
        if qname is None or qname not in self.enums:
            known = ", ".join(sorted(q.to_id() for q in self.enums)[:30])
            raise KeyError(
                f"Enum id '{text}' is not a enum in model '{self.model.package}'; known enums: {known}"
            )
        return self.enums[qname]

    def is_enum(self, qname: QName) -> bool:
        return qname in self.enums

    def is_root_class(self, qname: QName) -> bool:
        return len(self.record(qname).bases) == 0

    def ancestors(self, qname: QName) -> Tuple[QName, ...]:
        """The record itself followed by all transitive bases, each listed once."""
        if qname not in self.ancestor_cache:
            result: List[QName] = []
            pending = [qname]
            while pending:
                cur = pending.pop(0)
                if cur in result:
                    continue
                result.append(cur)
                pending.extend(self.record(cur).bases)
            self.ancestor_cache[qname] = tuple(result)
        return self.ancestor_cache[qname]

    def class_config_chain(self, qname: QName) -> Tuple[ClassConfig, ...]:
        """Tuple of class configs starting from the current one and up"""

        res = list()
        for base in self.ancestors(qname):
            res.append(self.record(base).class_config)

        return tuple(res)

    def derived_from(self, sub: QName, sup: QName) -> bool:
        return sup in self.ancestors(sub)

    def descendants(self, qname: QName) -> List[QName]:
        """Every non-enum record deriving from the given one, including itself, in declaration order."""
        return [
            r.qname
            for r in self.model.records
            if r.kind != RecordKind.ENUM and self.derived_from(r.qname, qname)
        ]

    def effective_fields(self, qname: QName) -> Tuple[FieldDef, ...]:
        """Fields of all bases first, followed by the own fields of the record."""
        if qname not in self.field_cache:
            result: List[FieldDef] = []
            seen: Set[str] = set()
            for anc in reversed(self.ancestors(qname)):
                for f in self.record(anc).fields:
                    if f.name not in seen:
                        seen.add(f.name)
                        result.append(f)
            self.field_cache[qname] = tuple(result)
        return self.field_cache[qname]

    def field(self, qname: QName, name: str) -> Optional[FieldDef]:
        for f in self.effective_fields(qname):
            if f.name == name:
                return f
        return None

    def variant(self, vt: VariantT) -> VariantDef:
        for v in self.record(vt.owner).variants:
            if v.field == vt.field:
                return v
        declared = ", ".join(v.field for v in self.record(vt.owner).variants) or "(none)"
        raise KeyError(
            f"Record '{vt.owner.to_id()}' has no variant stored in field '{vt.field}'; declared variant fields: {declared}"
        )

    def variant_case(self, vt: VariantT, tag: str) -> VariantCaseDef:
        vdef = self.variant(vt)
        for c in vdef.cases:
            if c.tag == tag:
                return c
        tags = ", ".join(c.tag for c in vdef.cases)
        raise KeyError(
            f"Variant '{vt.owner.to_id()}.{vt.field}' has no case '{tag}'; expected one of: {tags}"
        )

    def enum_values(self, qname: QName) -> Tuple[EnumValueDef, ...]:
        if qname not in self.enums:
            known = ", ".join(sorted(q.to_id() for q in self.enums)[:30])
            raise KeyError(
                f"Enum '{qname.to_id()}' is not declared in model '{self.model.package}'; known enums: {known}"
            )
        return self.enums[qname].enum_values

    def checks_for(self, qname: QName) -> List[Tuple[QName, CheckDef]]:
        """Checks that apply to an instance of the record, inherited checks first."""
        result: List[Tuple[QName, CheckDef]] = []
        for anc in reversed(self.ancestors(qname)):
            for chk in self.record(anc).checks:
                result.append((anc, chk))
        return result

    def key_fields(self, qname: QName) -> Optional[Tuple[str, ...]]:
        """Fields participating in structural equality and hashing, `None` means all fields."""
        for anc in self.ancestors(qname):
            rec = self.record(anc)
            if rec.eq_fields is not None:
                return rec.eq_fields
            if rec.hash_fields is not None:
                return rec.hash_fields
        return None

    def reachable_types(self, root: TypeRef) -> List[TypeRef]:
        """All types a value of the root type can contain, following subclasses under the closed world."""
        result: List[TypeRef] = []
        pending: List[TypeRef] = [root]
        while pending:
            cur = pending.pop()
            if cur in result:
                continue
            result.append(cur)
            match cur:
                case ListT() | ArrayT() | OptT():
                    pending.append(cur.elem)
                case MapT():
                    pending.extend([cur.key, cur.value])
                case TupleT():
                    pending.extend(cur.elems)
                case DynT():
                    pending.append(cur.root)
                case VariantT():
                    pending.extend(NamedT(qname=c.case) for c in self.variant(cur).cases)
                case NamedT() if not self.is_enum(cur.qname):
                    for desc in self.descendants(cur.qname):
                        pending.append(NamedT(qname=desc))
                        pending.extend(f.type for f in self.effective_fields(desc))
                case NamedT() | PrimT() | ExternalT() | TypeParamT() | UnresolvedT():
                    pass
        return result

    def reachable_records(self, root: TypeRef) -> List[QName]:
        return sorted(
            (t.qname for t in self.reachable_types(root) if isinstance(t, NamedT)),
            key=lambda q: self.order.get(q, 0),
        )
