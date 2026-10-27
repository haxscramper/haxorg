from __future__ import annotations

from dataclasses import dataclass

from beartype import beartype
from beartype.typing import Dict, List, NoReturn, Optional
from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    CheckContext,
    CheckDef,
    ExprNode,
    ItemPath,
    NamedT,
    OpId,
    PrimT,
    QName,
    Severity,
    SourceLoc,
    TypeRef,
)
from hstd_py_unidata.model_ops import (
    Env,
    EvalError,
    EvalHost,
    Operator,
    expect_bool,
    expect_str,
)
from hstd_py_unidata.model_value import (
    EnumValue,
    RecordValue,
    ScalarValue,
    Value,
    locate,
    positions,
)


@beartype
@dataclass(frozen=True)
class CheckFailure:
    """Failed check on one record or field occurrence of an instance."""

    check_id: str
    level: Severity
    owner: QName
    """Record declaring the check, which can be a base of the instance record."""
    path: ItemPath
    message: str
    loc: SourceLoc

    def render(self) -> str:
        return f"{self.loc.render()}: {self.level.value}[{self.check_id}] at {self.path.render()} ({self.owner.to_id()}): {self.message}"


@beartype
class Evaluator(EvalHost):
    """Reference interpreter of the expression IR over typed instance values."""

    def __init__(self, index: ModelIndex, table: Dict[OpId, Operator]) -> None:
        self.index = index
        self.table = table

    def eval(self, node: ExprNode, env: Env) -> Value:
        return self.table[node.op].evaluate(self, node, env)

    def fail(
        self, node: ExprNode, message: str, value: Optional[Value] = None
    ) -> NoReturn:
        path = (
            value.path.render()
            if value is not None and value.path is not None
            else None
        )
        raise EvalError(node, message, path)

    def matches_type(self, value: Value, t: TypeRef) -> bool:
        match value, t:
            case RecordValue(), NamedT():
                return self.index.derived_from(value.qname, t.qname)
            case EnumValue(), NamedT():
                return value.enum == t.qname
            case ScalarValue(), PrimT():
                return value.prim == t.prim
            case _:
                return False

    def run_check(
        self, owner: QName, check: CheckDef, this: Value, path: ItemPath
    ) -> Optional[CheckFailure]:
        env = Env(this=this)
        if expect_bool(self, check.cond, self.eval(check.cond, env)):
            return None
        message = expect_str(self, check.message, self.eval(check.message, env))
        return CheckFailure(
            check_id=check.id,
            level=check.level,
            owner=owner,
            path=path,
            message=message,
            loc=check.loc,
        )


@beartype
def validate(
    index: ModelIndex,
    table: Dict[OpId, Operator],
    root_type: TypeRef,
    value: Value,
    crash_as_failure: bool = False,
) -> List[CheckFailure]:
    """Runs every applicable check on every record occurrence.

    Invalid operations raise `EvalError`, or become error-level failures of the check with `crash_as_failure`."""
    evaluator = Evaluator(index, table)
    located = locate(value)
    failures: List[CheckFailure] = []
    for pos in positions(index, root_type, located):
        if not isinstance(pos.value, RecordValue):
            continue
        for owner, check in index.checks_for(pos.value.qname):
            match check.context:
                case CheckContext.RECORD:
                    this = pos.value
                    path = pos.path
                case CheckContext.FIELD:
                    assert check.field is not None
                    this = pos.value.fields[check.field]
                    path = pos.path.field(check.field)
            try:
                failure = evaluator.run_check(owner, check, this, path)
            except EvalError as err:
                if not crash_as_failure:
                    raise
                failure = CheckFailure(
                    check_id=check.id,
                    level=Severity.ERROR,
                    owner=owner,
                    path=path,
                    message=f"evaluation of the check failed: {err}",
                    loc=check.loc,
                )
            if failure is not None:
                failures.append(failure)
    return failures


@beartype
def errors_only(failures: List[CheckFailure]) -> List[CheckFailure]:
    return [f for f in failures if f.level == Severity.ERROR]
