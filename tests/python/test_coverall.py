import py_haxorg.pyhaxorg_wrap as org
from dataclasses import dataclass, replace, field
from beartype import beartype
from beartype.typing import List, Optional, Union, Iterable, Callable, Any, Tuple, Mapping, Set
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.script_logging import log
from rich.tree import Tree
from py_scriptutils.rich_utils import render_rich
from pathlib import Path
import re
import functools
import copy

CAT = __name__


@beartype
@dataclass
class ValueCheckResult():
    is_ok: bool = False
    on_fail: Optional[Tree] = None


@beartype
@dataclass
class ValuePredicate():
    func: Callable[[Any], ValueCheckResult]


@beartype
@dataclass
class FieldCheckResult():
    field: str
    value_check: ValueCheckResult
    field_predicate_id: str

    def is_matching(self) -> bool:
        return self.value_check.is_ok

    def format(self) -> Tree:
        if self.is_matching():
            res = Tree(f"Field '[green]{self.field}[/green]' OK")

        else:
            res = Tree(f"Field '[red]{self.field}[/red]' fail")
            res.add(self.value_check.on_fail)

        return res


@beartype
@dataclass
class FieldPredicate():
    name: str
    check: ValuePredicate
    field_predicate_id: str

    def visit_field(self, name: str, value: Any) -> FieldCheckResult:
        return FieldCheckResult(
            field=name,
            value_check=self.check.func(value),
            field_predicate_id=self.field_predicate_id,
        )


@beartype
@dataclass
class FieldAlternatives():
    items: List[FieldPredicate] = field(default_factory=list)

    def visit_field(self, field: str, value: Any):
        pass


@beartype
@dataclass
class ClassCheckResult():
    class_predicate_id: Optional[str]
    class_name: str
    fields: List[FieldCheckResult] = field(default_factory=list)
    error: Optional[Tree] = None
    unknown_fields: List[str] = field(default_factory=list)
    match_failure: List["ClassCheckResult"] = field(default_factory=list)

    def is_matching(self):
        return all(f.is_matching() for f in self.fields) and len(
            self.unknown_fields) == 0 and not self.error

    def format(self) -> Tree:
        if self.is_matching():
            return Tree(
                f"Class [green]{self.class_name}[/green] ok with ID [green]{self.class_predicate_id}[/green]"
            )

        else:
            res = Tree(
                f"Class [red]{self.class_name}[/red] failed with ID [red]{self.class_predicate_id}[/red]"
            )
            if self.error:
                res.add(self.error)

            if any(not f.is_matching() for f in self.fields):
                sub_fails = Tree("Failed to match fields")
                for field in self.fields:
                    sub_fails.add(field.format())

                res.add(sub_fails)

            if self.match_failure:
                sub_matches = Tree("Failed to match alternatives")
                for fail in self.match_failure:
                    sub_matches.add(fail.format())

                res.add(sub_matches)

            if self.unknown_fields:
                sub_fields = Tree("Unknown fields")
                for field in self.unknown_fields:
                    sub_fields.add(Tree(f"[red]{field}[/red]"))

                res.add(sub_fields)

            return res


@beartype
@dataclass
class ClassPrediate():
    fields: Mapping[str, FieldAlternatives]
    class_predicate_id: str
    allow_unknown_fields: bool = True

    def visit_type(self, value: Any) -> ClassCheckResult:
        res = ClassCheckResult(
            class_name=str(type(value)),
            class_predicate_id=self.class_predicate_id,
        )

        for field_name, field_value in value.__dict__.items():
            if field_name in self.fields:
                res.fields.append(self.fields[field_name].visit_field(
                    field_name, field_value))

            elif not self.allow_unknown_fields:
                res.unknown_fields.append(field_name)

        return res


@beartype
@dataclass
class ClassAlternatives():
    items: List[ClassPrediate] = field(default_factory=list)

    def visit_type(self, value: org.Org) -> ClassCheckResult:
        failed: List[ClassCheckResult] = []
        for item in self.items:
            res = item.visit_type(value)

            if res.is_matching():
                return res
            else:
                failed.append(res)

        return ClassCheckResult(
            match_failure=failed,
            class_name=str(value.getKind),
            class_predicate_id=None,
        )


@beartype
@dataclass
class OrgSpecification:
    alternatives: Mapping[org.OrgSemKind, ClassAlternatives] = field(default_factory=dict)

    def visit(self, node: org.Org) -> ClassCheckResult:
        kind = node.getKind()
        if kind in self.alternatives:
            return self.alternatives[kind].visit_type(node)

        else:
            return ClassCheckResult(
                error=Tree(f"No type description for {kind}"),
                class_predicate_id=None,
                class_name=str(kind),
            )

    def visit_all(self, node: org.Org) -> List[ClassCheckResult]:
        result: List[ClassCheckResult] = []
        visited_kinds: Set[org.OrgSemKind] = set()

        def impl(node: org.Org):
            result.append(self.visit(node))
            visited_kinds.add(node.getKind())

        org.eachSubnodeRec(node, impl)

        for kind in org.OrgSemKind(0):
            if kind not in visited_kinds:
                result.append(
                    ClassCheckResult(
                        error=Tree(f"Missing coverage for node kind {kind}"),
                        class_predicate_id=None,
                        class_name=str(kind),
                    ))

        return result


@beartype
def get_regex_field_check(field: str, regex: str, predicate_id: str) -> FieldPredicate:

    def regex_check_impl(regex, value):
        if re.match(regex, value):
            return ValueCheckResult(is_ok=True)

        else:
            return ValueCheckResult(
                is_ok=False,
                on_fail=True (f"Value '{value}' did not match regex '{regex}'"))

    return FieldPredicate(
        name=field,
        check=ValuePredicate(
            func=functools.partial(regex_check_impl, copy.deepcopy(regex))),
        field_predicate_id=predicate_id,
    )


@beartype
def get_spec() -> OrgSpecification:
    res = OrgSpecification()

    res.alternatives[org.OrgSemKind.Word] = ClassAlternatives(items=[
        ClassPrediate(
            fields=dict(text=get_regex_field_check("text", ".*", "any_value")),
            class_predicate_id="text_field",
        )
    ])

    return res


def test_run():
    org_corpus_dir = get_haxorg_repo_root_path().joinpath("tests/org/corpus/org")
    file = org_corpus_dir.joinpath("py_validated_all.org")
    node = org.parseFile(str(file), org.OrgParseParameters())
    spec = get_spec()
    coverage = spec.visit_all(node)

    final = Tree("Coverage report")
    for item in coverage:
        final.add(item.format())

    Path("/tmp/report.txt").write_text(render_rich(final, False))
