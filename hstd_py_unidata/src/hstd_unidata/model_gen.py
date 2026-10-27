from __future__ import annotations

import random
import string
from collections import Counter
from dataclasses import dataclass, field

from beartype import beartype
from beartype.typing import Any, Callable, Dict, List, Optional, Tuple
from loguru import logger

from hstd_unidata.model_eval import CheckFailure, errors_only, validate
from hstd_unidata.model_index import ModelIndex
from hstd_unidata.model_ir import (
    FLOAT_PRIMS,
    INTEGER_RANGES,
    ArrayT,
    ExprNode,
    ExternalT,
    ItemPath,
    ListT,
    MapT,
    NamedT,
    OpId,
    OptT,
    PrimKind,
    PrimT,
    QName,
    TupleT,
    TypeRef,
    VariantT,
    type_text,
)
from hstd_unidata.model_ops import Operator
from hstd_unidata.model_value import (
    AnyValue,
    EnumValue,
    ListValue,
    OptValue,
    Position,
    RecordValue,
    ScalarValue,
    TupleValue,
    Value,
    VariantValue,
    decode_json,
    default_value,
    make_map,
    positions,
    replace_at,
)


@beartype
@dataclass(frozen=True)
class GenConfig:
    seed: int = 0
    size: int = 6
    """Scale of scalar magnitudes and string lengths."""
    max_depth: int = 6
    """Nesting depth after which collections are empty, optionals absent and records trivial."""
    max_collection: int = 4
    repair_attempts: int = 200
    restarts: int = 20


@beartype
class GenerationError(Exception):
    """No value satisfying every error-level check was found within the configured attempts."""


@beartype
class GenContext:
    """Generation state passed to user generators of external types and overridden fields."""

    def __init__(self, generator: ValueGenerator, depth: int) -> None:
        self.generator = generator
        self.depth = depth

    @property
    def rng(self) -> random.Random:
        return self.generator.rng

    @property
    def index(self) -> ModelIndex:
        return self.generator.index

    def generate(self, t: TypeRef) -> Value:
        """Generates a nested value with the regular strategy, including user overrides."""
        return self.generator.gen(t, self.depth + 1)

    def generate_record(self, qname: QName, fixed: Dict[str, Value]) -> RecordValue:
        """Record of exactly this type with the given field values, the remaining fields are generated."""
        return self.generator.gen_record(qname, self.depth, fixed)

    def fresh_name(self, prefix: str) -> str:
        """Name that is unique within one generation run."""
        return self.generator.fresh_name(prefix)

    def decode(self, t: TypeRef, data: Any) -> Value:
        return decode_json(self.index, t, data)

    def default(self, t: TypeRef) -> Value:
        return default_value(self.index, t)


GeneratorFunc = Callable[[GenContext], Value]


@beartype
@dataclass
class GenOverrides:
    """User generators: by type for any slot of that type, by (record, field) for one field of a record and its subtypes."""

    types: Dict[TypeRef, GeneratorFunc] = field(default_factory=dict)
    fields: Dict[Tuple[QName, str], GeneratorFunc] = field(default_factory=dict)


@beartype
@dataclass
class ConstantPool:
    """Literals of check conditions, used to hit the boundaries the checks test."""

    ints: List[int] = field(default_factory=list)
    floats: List[float] = field(default_factory=list)
    strings: List[str] = field(default_factory=list)

    def collect(self, node: ExprNode) -> None:
        match node.op:
            case OpId.CONST_INT:
                assert node.int_val is not None
                self.ints.extend([node.int_val - 1, node.int_val, node.int_val + 1])
            case OpId.CONST_FLOAT:
                assert node.float_val is not None
                self.floats.append(node.float_val)
            case OpId.CONST_STR:
                assert node.str_val is not None
                self.strings.append(node.str_val)
            case _:
                pass
        for arg in node.args:
            self.collect(arg)


@beartype
def external_types(index: ModelIndex, root: TypeRef) -> List[ExternalT]:
    return [t for t in index.reachable_types(root) if isinstance(t, ExternalT)]


@beartype
class ValueGenerator:
    """Seeded random generator of model values that are valid with respect to every error-level check."""

    def __init__(
        self,
        index: ModelIndex,
        table: Dict[OpId, Operator],
        config: GenConfig,
        overrides: GenOverrides,
    ) -> None:
        self.index = index
        self.table = table
        self.config = config
        self.overrides = overrides
        self.rng = random.Random(config.seed)
        self.name_counter = 0
        self.pool = ConstantPool()
        for rec in index.model.records:
            for check in rec.checks:
                self.pool.collect(check.cond)

    def fresh_name(self, prefix: str) -> str:
        self.name_counter += 1
        return f"{prefix}{self.name_counter}"

    def check_generators(self, root: TypeRef) -> None:
        missing = [
            t for t in external_types(self.index, root) if t not in self.overrides.types
        ]
        if missing:
            names = ", ".join(type_text(t) for t in missing)
            raise GenerationError(
                f"Values of '{type_text(root)}' contain external types without a user generator: {names}; "
                "pass a generator for each of them in the type overrides"
            )

    def collection_size(self, depth: int) -> int:
        if self.config.max_depth <= depth:
            return 0
        return self.rng.randint(0, self.config.max_collection)

    def gen(self, t: TypeRef, depth: int) -> Value:
        if t in self.overrides.types:
            return self.overrides.types[t](GenContext(self, depth))
        if self.config.max_depth + 2 <= depth and not isinstance(t, NamedT):
            return default_value(self.index, t)
        match t:
            case PrimT():
                return self.gen_prim(t.prim)
            case ListT():
                return ListValue(
                    items=tuple(
                        self.gen(t.elem, depth + 1)
                        for _ in range(self.collection_size(depth))
                    )
                )
            case ArrayT():
                return ListValue(
                    items=tuple(self.gen(t.elem, depth + 1) for _ in range(t.size))
                )
            case MapT():
                entries = [
                    (self.gen(t.key, depth + 1), self.gen(t.value, depth + 1))
                    for _ in range(self.collection_size(depth))
                ]
                return make_map(self.index, entries)
            case OptT():
                if self.config.max_depth <= depth or self.rng.random() < 0.3:
                    return OptValue(value=None)
                return OptValue(value=self.gen(t.elem, depth + 1))
            case TupleT():
                return TupleValue(items=tuple(self.gen(e, depth + 1) for e in t.elems))
            case NamedT() if self.index.is_enum(t.qname):
                return EnumValue(
                    enum=t.qname,
                    name=self.rng.choice(self.index.enum_values(t.qname)).name,
                )
            case NamedT():
                options = self.index.descendants(t.qname)
                concrete = (
                    options[0]
                    if self.config.max_depth <= depth
                    else self.rng.choice(options)
                )
                return self.gen_record(concrete, depth, {})
            case VariantT():
                case_def = self.rng.choice(self.index.variant(t).cases)
                return VariantValue(
                    variant=t,
                    tag=case_def.tag,
                    case=self.gen_record(case_def.case, depth, {}),
                )
            case ExternalT():
                raise GenerationError(
                    f"External type '{type_text(t)}' has no user generator in the type overrides"
                )
            case _:
                raise GenerationError(
                    f"Type '{type_text(t)}' cannot hold instance data and cannot be generated"
                )

    def gen_record(
        self, qname: QName, depth: int, fixed: Dict[str, Value]
    ) -> RecordValue:
        if self.config.max_depth + 2 <= depth:
            base = default_value(self.index, NamedT(qname=qname))
            assert isinstance(base, RecordValue)
            fields = dict(base.fields)
            fields.update(fixed)
            for f in self.index.effective_fields(qname):
                override = self.field_override(qname, f.name)
                if override is not None and f.name not in fixed:
                    fields[f.name] = override(GenContext(self, depth + 1))
            return RecordValue(qname=qname, fields=fields)
        fields = {}
        for f in self.index.effective_fields(qname):
            override = self.field_override(qname, f.name)
            if f.name in fixed:
                fields[f.name] = fixed[f.name]
            elif override is not None:
                fields[f.name] = override(GenContext(self, depth + 1))
            else:
                fields[f.name] = self.gen(f.type, depth + 1)
        return RecordValue(qname=qname, fields=fields)

    def field_override(self, qname: QName, name: str) -> Optional[GeneratorFunc]:
        for anc in self.index.ancestors(qname):
            found = self.overrides.fields.get((anc, name))
            if found is not None:
                return found
        return None

    def gen_prim(self, prim: PrimKind) -> Value:
        size = self.config.size
        if prim in INTEGER_RANGES:
            lo, hi = INTEGER_RANGES[prim]
            pool = [v for v in self.pool.ints if lo <= v <= hi]
            if pool and self.rng.random() < 0.3:
                return ScalarValue(prim=prim, value=self.rng.choice(pool))
            return ScalarValue(
                prim=prim, value=self.rng.randint(max(lo, -4 * size), min(hi, 4 * size))
            )
        if prim in FLOAT_PRIMS:
            if self.pool.floats and self.rng.random() < 0.3:
                return ScalarValue(prim=prim, value=self.rng.choice(self.pool.floats))
            return ScalarValue(prim=prim, value=round(self.rng.uniform(-size, size), 3))
        match prim:
            case PrimKind.STRING:
                if self.pool.strings and self.rng.random() < 0.2:
                    return ScalarValue(
                        prim=prim, value=self.rng.choice(self.pool.strings)
                    )
                length = self.rng.randint(0, size)
                return ScalarValue(
                    prim=prim,
                    value="".join(
                        self.rng.choice(string.ascii_lowercase) for _ in range(length)
                    ),
                )
            case PrimKind.BOOL:
                return ScalarValue(prim=prim, value=self.rng.random() < 0.5)
            case PrimKind.ANY:
                return AnyValue(payload=None)
            case _:
                raise GenerationError(
                    f"Primitive type '{prim.value}' cannot be stored in instance data and cannot be generated"
                )

    def failures(self, root: TypeRef, value: Value) -> List[CheckFailure]:
        return errors_only(
            validate(self.index, self.table, root, value, crash_as_failure=True)
        )

    def repair_target(
        self, failure: CheckFailure, attempt: int, by_path: Dict[ItemPath, Position]
    ) -> ItemPath:
        """A position nested in the failing one, or the failing position and progressively farther ancestors."""
        nested = [
            p for p in by_path if failure.path.is_prefix_of(p) and p != failure.path
        ]
        if nested and self.rng.random() < 0.5:
            return self.rng.choice(nested)
        segments = failure.path.segments
        prefixes = [
            ItemPath(segments=segments[:i]) for i in range(len(segments), -1, -1)
        ]
        prefixes = [p for p in prefixes if p in by_path]
        escalation = min(len(prefixes) - 1, attempt // 10)
        return prefixes[self.rng.randint(0, escalation)]

    def generate(self, root: TypeRef) -> Value:
        self.check_generators(root)
        last: List[CheckFailure] = []
        for restart in range(self.config.restarts):
            value = self.gen(root, 0)
            for attempt in range(self.config.repair_attempts):
                last = self.failures(root, value)
                if not last:
                    if restart or attempt:
                        logger.debug(
                            f"Generated a valid '{type_text(root)}' after {restart} restart(s) and {attempt} repair(s)"
                        )
                    return value
                by_path: Dict[ItemPath, Position] = {}
                for pos in positions(self.index, root, value):
                    by_path.setdefault(pos.path, pos)
                target = self.repair_target(self.rng.choice(last), attempt, by_path)
                pos = by_path[target]
                value = replace_at(
                    value, target, self.gen(pos.type, len(target.segments))
                )
        counts = Counter(f.check_id for f in last)
        examples: Dict[str, CheckFailure] = {}
        for f in last:
            examples.setdefault(f.check_id, f)
        summary = "; ".join(
            f"'{cid}' failed {n} time(s), e.g. at {examples[cid].path.render()}: {examples[cid].message}"
            for cid, n in counts.most_common()
        )
        raise GenerationError(
            f"Could not generate a valid '{type_text(root)}' with seed {self.config.seed} after {self.config.restarts} restart(s) "
            f"of {self.config.repair_attempts} repair attempt(s); remaining check failures: {summary}. "
            "Provide field or type overrides that construct values satisfying these checks"
        )


@beartype
def generate_value(
    index: ModelIndex,
    table: Dict[OpId, Operator],
    root: TypeRef,
    config: GenConfig,
    overrides: GenOverrides,
) -> Value:
    return ValueGenerator(index, table, config, overrides).generate(root)
