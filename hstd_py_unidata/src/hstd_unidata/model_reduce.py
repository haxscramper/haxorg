from __future__ import annotations

import math
from dataclasses import dataclass

from beartype import beartype
from beartype.typing import Callable, Dict, Iterator, List, Tuple
from loguru import logger

from hstd_unidata.model_eval import errors_only, validate
from hstd_unidata.model_index import ModelIndex
from hstd_unidata.model_ir import (
    INTEGER_RANGES,
    ListT,
    MapT,
    NamedT,
    OpId,
    TypeRef,
    type_text,
)
from hstd_unidata.model_ops import Operator
from hstd_unidata.model_value import (
    EnumValue,
    ListValue,
    MapValue,
    OptValue,
    Position,
    RecordValue,
    ScalarValue,
    Value,
    VariantValue,
    default_value,
    positions,
    record_default,
    replace_at,
    value_key,
    value_size,
)

Predicate = Callable[[Value], bool]


@beartype
@dataclass(frozen=True)
class ReduceConfig:
    max_predicate_calls: int = 10000


@beartype
@dataclass(frozen=True)
class ReductionResult:
    value: Value
    size_before: Tuple[int, int]
    size_after: Tuple[int, int]
    steps: int
    """Accepted candidates, each strictly smaller than the previous value."""
    predicate_calls: int
    rejected_invalid: int
    """Smaller candidates skipped because they violate an error-level check of the model."""
    exhausted: bool
    """The predicate call budget ran out before a local minimum was reached."""


@beartype
class ReductionInputError(Exception):
    """The value to reduce is invalid for the model or does not satisfy the predicate."""


@beartype
def chunk_removals(items: Tuple[Value, ...]) -> Iterator[Tuple[Value, ...]]:
    """Delta-debugging style removal: large contiguous chunks first, then single elements."""
    n = len(items)
    chunk = n
    while 0 < chunk:
        for start in range(0, n, chunk):
            yield items[:start] + items[start + chunk :]
        chunk //= 2


@beartype
def shrink_scalar(value: ScalarValue) -> List[ScalarValue]:
    result: List[ScalarValue] = []
    match value.value:
        case bool():
            if value.value:
                result.append(ScalarValue(prim=value.prim, value=False))
        case int():
            v = value.value
            lo, _ = INTEGER_RANGES[value.prim]
            for c in (0, v // 2 if 0 < v else -((-v) // 2), v - 1 if 0 < v else v + 1):
                if abs(c) < abs(v) and lo <= c:
                    result.append(ScalarValue(prim=value.prim, value=c))
        case float():
            v = value.value
            candidates = (
                [0.0, float(math.trunc(v)), v / 2] if math.isfinite(v) else [0.0]
            )
            for c in candidates:
                if abs(c) < abs(v) or not math.isfinite(v):
                    result.append(ScalarValue(prim=value.prim, value=c))
        case str():
            s = value.value
            options = ["", s[: len(s) // 2]] + [
                s[:i] + s[i + 1 :] for i in range(min(len(s), 16))
            ]
            for c in options:
                if len(c) < len(s):
                    result.append(ScalarValue(prim=value.prim, value=c))
        case None:
            pass
    return result


@beartype
class Reducer:
    """Greedy shrinking that keeps every intermediate value valid and accepted by the predicate."""

    def __init__(
        self,
        index: ModelIndex,
        table: Dict[OpId, Operator],
        root: TypeRef,
        predicate: Predicate,
        config: ReduceConfig,
    ) -> None:
        self.index = index
        self.table = table
        self.root = root
        self.predicate = predicate
        self.config = config
        self.predicate_calls = 0
        self.rejected_invalid = 0

    def invalid_reasons(self, value: Value) -> List[str]:
        return [
            f.render()
            for f in errors_only(
                validate(
                    self.index, self.table, self.root, value, crash_as_failure=True
                )
            )
        ]

    def place(self, root: Value, pos: Position, new: Value) -> Value:
        return replace_at(root, pos.path, pos.rebuild(new))

    def candidates(self, root: Value) -> Iterator[Value]:
        found = list(positions(self.index, self.root, root))
        for pos in found:
            match pos.value, pos.type:
                case ListValue(), ListT():
                    for items in chunk_removals(pos.value.items):
                        yield self.place(root, pos, ListValue(items=items))
                case MapValue(), MapT():
                    for entries in chunk_removals_entries(pos.value.entries):
                        yield self.place(root, pos, MapValue(entries=entries))
                case _:
                    pass
        for pos in found:
            if isinstance(pos.value, OptValue) and pos.value.value is not None:
                yield self.place(root, pos, OptValue(value=None))
        for pos in found:
            if pos.is_case_record:
                continue
            try:
                trivial = default_value(self.index, pos.type)
            except TypeError:
                continue
            if value_key(self.index, trivial) != value_key(self.index, pos.value):
                yield self.place(root, pos, trivial)
        for pos in found:
            yield from self.hoist(root, pos, found)
        for pos in found:
            yield from self.switch_kind(root, pos)
        for pos in found:
            match pos.value:
                case ScalarValue():
                    for c in shrink_scalar(pos.value):
                        yield self.place(root, pos, c)
                case EnumValue():
                    names = [ev.name for ev in self.index.enum_values(pos.value.enum)]
                    for name in names[: names.index(pos.value.name)]:
                        yield self.place(
                            root, pos, EnumValue(enum=pos.value.enum, name=name)
                        )
                case _:
                    pass

    def hoist(
        self, root: Value, pos: Position, found: List[Position]
    ) -> Iterator[Value]:
        """Replaces a record or list by a nested value that fits the same slot."""
        if pos.is_case_record:
            return
        for inner in found:
            if inner.path == pos.path or not pos.path.is_prefix_of(inner.path):
                continue
            match pos.type, inner.value:
                case NamedT(), RecordValue() if not self.index.is_enum(
                    pos.type.qname
                ) and self.index.derived_from(inner.value.qname, pos.type.qname):
                    yield self.place(root, pos, inner.value)
                case ListT(), ListValue() if inner.type == pos.type:
                    yield self.place(root, pos, inner.value)
                case _:
                    pass

    def switch_kind(self, root: Value, pos: Position) -> Iterator[Value]:
        """Earlier variant cases with trivial data, and base records keeping the shared field values."""
        match pos.value:
            case VariantValue():
                vdef = self.index.variant(pos.value.variant)
                tags = [c.tag for c in vdef.cases]
                for c in vdef.cases[: tags.index(pos.value.tag)]:
                    yield self.place(
                        root,
                        pos,
                        VariantValue(
                            variant=pos.value.variant,
                            tag=c.tag,
                            case=record_default(self.index, c.case),
                        ),
                    )
            case RecordValue() if (
                isinstance(pos.type, NamedT)
                and not pos.is_case_record
                and pos.value.qname != pos.type.qname
            ):
                for anc in self.index.ancestors(pos.value.qname)[1:]:
                    if not self.index.derived_from(anc, pos.type.qname):
                        continue
                    shared = {
                        f.name: pos.value.fields[f.name]
                        for f in self.index.effective_fields(anc)
                    }
                    yield self.place(root, pos, RecordValue(qname=anc, fields=shared))
            case _:
                pass

    def reduce(self, value: Value) -> ReductionResult:
        reasons = self.invalid_reasons(value)
        if reasons:
            raise ReductionInputError(
                f"The value to reduce violates {len(reasons)} error-level check(s) of '{type_text(self.root)}', reduction only works on valid values:\n  "
                + "\n  ".join(reasons)
            )
        if not self.predicate(value):
            raise ReductionInputError(
                "The predicate rejects the initial value, so there is no property to preserve while reducing"
            )
        self.predicate_calls = 1
        current = value
        size_before = value_size(self.index, value)
        size = size_before
        steps = 0
        exhausted = False
        progress = True
        while progress and not exhausted:
            progress = False
            for cand in self.candidates(current):
                cand_size = value_size(self.index, cand)
                if not cand_size < size:
                    continue
                if self.invalid_reasons(cand):
                    self.rejected_invalid += 1
                    continue
                if self.config.max_predicate_calls <= self.predicate_calls:
                    exhausted = True
                    break
                self.predicate_calls += 1
                if self.predicate(cand):
                    current = cand
                    size = cand_size
                    steps += 1
                    progress = True
                    break
        logger.debug(
            f"Reduced '{type_text(self.root)}' from {size_before} to {size} (nodes, magnitude) in {steps} step(s) "
            f"with {self.predicate_calls} predicate call(s) and {self.rejected_invalid} invalid candidate(s)"
        )
        return ReductionResult(
            value=current,
            size_before=size_before,
            size_after=size,
            steps=steps,
            predicate_calls=self.predicate_calls,
            rejected_invalid=self.rejected_invalid,
            exhausted=exhausted,
        )


@beartype
def chunk_removals_entries(
    entries: Tuple[Tuple[Value, Value], ...],
) -> Iterator[Tuple[Tuple[Value, Value], ...]]:
    n = len(entries)
    chunk = n
    while 0 < chunk:
        for start in range(0, n, chunk):
            yield entries[:start] + entries[start + chunk :]
        chunk //= 2


@beartype
def reduce_value(
    index: ModelIndex,
    table: Dict[OpId, Operator],
    root: TypeRef,
    value: Value,
    predicate: Predicate,
    config: ReduceConfig,
) -> ReductionResult:
    return Reducer(index, table, root, predicate, config).reduce(value)
