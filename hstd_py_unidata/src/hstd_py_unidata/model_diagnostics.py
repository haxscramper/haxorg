from __future__ import annotations

import enum
import linecache
from dataclasses import dataclass, field
from textwrap import indent

import rich.tree
from beartype import beartype
from beartype.typing import Dict, List, Sequence, Set, Tuple
from hstd_py_lib.external_packages.rich_utils import render_rich

from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    NamedT,
    OpId,
    QName,
    SourceLoc,
    VariantT,
    expr_tree_repr,
    type_text,
)
from hstd_py_unidata.model_ops import Operator, render_expr
from hstd_py_unidata.model_souffle import DiagRow, Occurrence, TypeCheckOutput


class DiagCode(enum.StrEnum):
    """Diagnostic classification shared with the `diag` relation of the Souffle rules."""

    UNKNOWN_FIELD = "unknown-field"
    FIELD_ON_NON_RECORD = "field-on-non-record"
    AMBIGUOUS_CASE_FIELD = "ambiguous-case-field"
    INVALID_CASE_TAG = "invalid-case-tag"
    NOT_A_VARIANT = "not-a-variant"
    INVALID_ENUM_VALUE = "invalid-enum-value"
    NOT_AN_ENUM = "not-an-enum"
    TUPLE_INDEX = "tuple-index"
    NOT_A_TUPLE = "not-a-tuple"
    NOT_A_RECORD = "not-a-record"
    ARG_CLASS = "arg-class"
    INCOMPATIBLE_OPERANDS = "incompatible-operands"
    BRANCH_MISMATCH = "branch-mismatch"
    ROOT_TYPE = "root-type"
    UNREACHABLE_TYPE_CASE = "unreachable-type-case"
    INCOMPATIBLE_TYPE_CASE = "incompatible-type-case"
    NOT_DERIVABLE = "not-derivable"
    UNTYPED = "untyped"


@beartype
@dataclass
class Diagnostic:
    """Primary type error with its expression context; dependent failures are folded into notes."""

    code: DiagCode
    message: str
    loc: SourceLoc
    record: QName
    check_id: str
    part: str
    check_loc: SourceLoc
    expr_text: str
    position: str
    expr_tree: rich.tree.Tree
    notes: List[str] = field(default_factory=list)

    def render(self) -> str:
        lines = [
            f"{self.loc.render()}: error[{self.code.value}]: {self.message}",
            f"    in the {self.part} of check '{self.check_id}' on '{self.record.to_id()}' declared at {self.check_loc.render()}",
            f"    expression: {self.expr_text}",
            "    typed:",
            *indent(render_rich(self.expr_tree, color=False), "      ").split("\n"),
        ]

        if self.position:
            lines.append(f"    position: {self.position}")
        source = linecache.getline(self.loc.file, self.loc.line).rstrip()
        if source:
            lines.append(f"    {self.loc.line:>5} | {source}")
        lines.extend(f"    note: {n}" for n in self.notes)
        return "\n".join(lines)


@beartype
class DslTypeError(Exception):
    """Check expressions of the model are ill-typed; one diagnostic per root cause."""

    def __init__(self, package: str, diagnostics: Sequence[Diagnostic]) -> None:
        body = "\n\n".join(d.render() for d in diagnostics)
        super().__init__(
            f"Model '{package}' has {len(diagnostics)} type error(s) in check expressions:\n\n{body}"
        )
        self.diagnostics = list(diagnostics)


@beartype
class DiagnosticBuilder:
    def __init__(
        self, index: ModelIndex, table: Dict[OpId, Operator], output: TypeCheckOutput
    ) -> None:
        self.index = index
        self.table = table
        self.output = output
        self.occ: Dict[int, Occurrence] = output.program.occurrences
        self.nested: Dict[int, List[int]] = {}
        for o in self.occ.values():
            if o.parent is not None:
                self.nested.setdefault(o.parent, []).append(o.id)
        for ids in self.nested.values():
            ids.sort(key=lambda i: self.occ[i].arg_index)

    def build(self) -> List[Diagnostic]:
        grouped: Dict[Tuple[int, str, int], List[DiagRow]] = {}
        for row in self.output.diags:
            grouped.setdefault((row.expr, row.code, row.arg), []).append(row)
        with_specific: Set[int] = {row.expr for row in self.output.diags}
        result: List[Diagnostic] = []
        for (expr, code, _), rows in sorted(grouped.items()):
            result.append(
                self.make(expr, DiagCode(code), self.describe(DiagCode(code), rows))
            )
        for expr in sorted(self.output.untyped):
            if expr in with_specific or self.occ[expr].node.op == OpId.VAR:
                continue
            if any(n in self.output.untyped for n in self.nested.get(expr, [])):
                continue
            result.append(self.make(expr, DiagCode.UNTYPED, self.describe_untyped(expr)))
        return result

    def make(self, expr: int, code: DiagCode, message: str) -> Diagnostic:
        o = self.occ[expr]
        notes: List[str] = []
        cascade: List[str] = []
        cur = o.parent
        while cur is not None and cur in self.output.untyped:
            cascade.append(self.occ[cur].node.op.value)
            cur = self.occ[cur].parent
        if cascade:
            notes.append(
                f"{len(cascade)} enclosing expression(s) could not be typed as a consequence: {', '.join(cascade)}"
            )
        return Diagnostic(
            code=code,
            message=message,
            loc=o.node.loc,
            record=o.root.record,
            check_id=o.root.check.id,
            part=o.root.part.value,
            check_loc=o.root.check.loc,
            expr_text=render_expr(self.table, o.node),
            position=self.position(expr),
            expr_tree=expr_tree_repr(self.occ[expr].node),
            notes=notes,
        )

    def position(self, expr: int) -> str:
        steps: List[str] = []
        cur = self.occ[expr]
        while cur.parent is not None:
            parent = self.occ[cur.parent]
            steps.append(
                f"{parent.node.op.value}.{self.table[parent.node.op].role(cur.arg_index)}"
            )
            cur = parent
        steps.reverse()
        steps.append(self.occ[expr].node.op.value)
        return " > ".join(steps)

    def operand_types(self, expr: int) -> List[str]:
        return [
            self.output.typed_as.get(n, "<untyped>") for n in self.nested.get(expr, [])
        ]

    def record_fields(self, subject: str) -> str:
        if "#" in subject:
            owner, vfield = subject.split("#", 1)
            vdef = self.index.variant(
                VariantT(owner=self.index.by_id[owner], field=vfield)
            )
            per_case = [
                f"{c.tag}: {', '.join(f.name for f in self.index.effective_fields(c.case)) or '(none)'}"
                for c in vdef.cases
            ]
            return "fields per case: " + "; ".join(per_case)
        rec = self.index.record_by_id(subject)
        names = [f.name for f in self.index.effective_fields(rec.qname)]
        return f"available fields: {', '.join(names) or '(none)'}"

    def variant_tags(self, subject: str) -> str:
        owner, vfield = subject.split("#", 1)
        vdef = self.index.variant(VariantT(owner=self.index.by_id[owner], field=vfield))
        return ", ".join(c.tag for c in vdef.cases)

    def describe(self, code: DiagCode, rows: List[DiagRow]) -> str:
        row = rows[0]
        o = self.occ[row.expr]
        op = o.node.op.value
        match code:
            case DiagCode.UNKNOWN_FIELD:
                return f"field '{row.detail}' does not exist on '{row.actual}'; {self.record_fields(row.subject)}"
            case DiagCode.FIELD_ON_NON_RECORD:
                return f"field access '{row.detail}' requires a record or variant operand, but the operand has type '{row.actual}'"
            case DiagCode.AMBIGUOUS_CASE_FIELD:
                return f"field '{row.detail}' is declared with different types in several cases of '{row.actual}'; {self.record_fields(row.subject)}"
            case DiagCode.INVALID_CASE_TAG:
                return f"'{row.detail}' is not a case of '{row.actual}'; expected one of: {self.variant_tags(row.subject)}"
            case DiagCode.NOT_A_VARIANT:
                return f"'{op}' requires a variant operand (a field created by __variant__), but the operand has type '{row.actual}'"
            case DiagCode.INVALID_ENUM_VALUE:
                names = ", ".join(
                    ev.name
                    for ev in self.index.enum_values(self.index.by_id[row.subject])
                )

                return f"'{row.detail}' is not a value of enum '{row.actual}'; expected one of: {names}"
            case DiagCode.NOT_AN_ENUM:
                return f"'{op}' requires an enum operand, but the operand has type '{row.actual}'"
            case DiagCode.TUPLE_INDEX:
                return f"tuple index {row.detail} is out of range for '{row.actual}'"
            case DiagCode.NOT_A_TUPLE:
                return f"'{op}' requires a tuple operand, but the operand has type '{row.actual}'"
            case DiagCode.NOT_A_RECORD:
                return f"'{op}' requires a record operand, but the operand has type '{row.actual}'"
            case DiagCode.ARG_CLASS:
                expected = " or ".join(sorted({r.detail for r in rows}))
                return f"argument '{self.table[o.node.op].role(row.arg)}' of '{op}' must be {expected}, but has type '{row.actual}'"
            case DiagCode.INCOMPATIBLE_OPERANDS:
                return f"operands of '{op}' have incompatible types '{row.detail}' and '{row.actual}' because {self.operand_type_rule(o.node.op)}"
            case DiagCode.BRANCH_MISMATCH:
                match o.node.op:
                    case OpId.FOLD:
                        return f"fold body must produce the accumulator type '{row.detail}' given by the initial value, but produces '{row.actual}'"
                    case OpId.TYPE_COND:
                        return f"all type_case branches must have the same result type; the first branch has '{row.detail}', branch {row.arg - 1} has '{row.actual}'"
                    case _:
                        return f"both branches of op_cond must have the same type, the 'then' branch has '{row.detail}' and the 'else' branch has '{row.actual}'"
            case DiagCode.ROOT_TYPE:
                return f"the check {o.root.part.value} must have type '{row.detail}', but has type '{row.actual}'"
            case DiagCode.UNREACHABLE_TYPE_CASE:
                reachable = (
                    ", ".join(
                        q.to_id()
                        for q in self.index.reachable_records(
                            NamedT(qname=self.index.by_id[row.subject])
                        )
                    )
                    if row.subject
                    else "(unknown)"
                )
                return f"type_case pattern '{row.detail}' can never match because no value of that type or of its subtypes is reachable from '{row.actual}'; reachable declarations: {reachable}"
            case DiagCode.INCOMPATIBLE_TYPE_CASE:
                return f"type_case pattern '{row.detail}' is unrelated to the subject type '{row.actual}'; the pattern must be the subject type, one of its subtypes or one of its bases"
            case DiagCode.NOT_DERIVABLE:
                return f"'{row.actual}' and '{row.detail}' are unrelated by inheritance, so the derivation test is always false"
            case DiagCode.UNTYPED:
                return self.describe_untyped(row.expr)

    def operand_type_rule(self, op: OpId) -> str:
        match op:
            case OpId.EQ | OpId.NE:
                return "equality requires equal types or two numeric types"
            case OpId.LT | OpId.LE:
                return "ordering requires two numeric operands or two strings"
            case OpId.ADD:
                return "addition requires two numeric operands or two strings"
            case OpId.SUB | OpId.MUL | OpId.DIV:
                return "arithmetic requires two numeric operands"
            case OpId.LIST_CONTAINS:
                return "the searched item must have the list element type"
            case OpId.LIST_CONCAT:
                return "both lists must have the same element type"
            case OpId.MAP_CONTAINS | OpId.MAP_GET | OpId.MAP_INSERT:
                return "the key must have the map key type and an inserted value must have the map value type"
            case _:
                return "the operator requires compatible operand types"

    def describe_untyped(self, expr: int) -> str:
        o = self.occ[expr]
        types = ", ".join(self.operand_types(expr)) or "no operands"
        hint = ""
        if o.node.type_val is not None:
            hint = f" with type argument '{type_text(o.node.type_val)}'"
        return f"operator '{o.node.op.value}'{hint} cannot be applied to operand types ({types})"


@beartype
def build_diagnostics(
    index: ModelIndex, table: Dict[OpId, Operator], output: TypeCheckOutput
) -> List[Diagnostic]:
    return DiagnosticBuilder(index, table, output).build()
