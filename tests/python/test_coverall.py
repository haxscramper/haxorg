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
def add_if_ok(target: Tree, other: Optional[Tree]):
    if other is not None:
        target.add(other)


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
    value_check: Optional[ValueCheckResult]
    field_predicate_id: Optional[str]
    sub_failed: List["FieldCheckResult"] = field(default_factory=list)

    def is_matching(self) -> bool:
        return bool(self.value_check and self.value_check.is_ok)

    def format(self, format_if_ok: bool) -> Tree:
        if self.is_matching():
            if format_if_ok:
                return Tree(f"Field '[green]{self.field}[/green]' OK")

            else:
                return None

        else:
            res = Tree(f"Field '[red]{self.field}[/red]' fail")
            if self.value_check.on_fail:
                res.add(self.value_check.on_fail)

            elif self.sub_failed:
                sub_fail = Tree("Field alternatives failed")
                for alt in self.sub_failed:
                    add_if_ok(sub_fail, alt.format(format_if_ok))

                res.add(sub_fail)

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

    def visit_field(self, field: str, value: Any) -> FieldCheckResult:
        failed: List[FieldCheckResult] = []
        final_res: Optional[FieldCheckResult] = None
        visisted_alternatives: Set[str] = set()
        for alt in self.items:
            assert (
                alt.field_predicate_id not in visisted_alternatives,
                f"Field '{field}' already has value alternative with ID '{alt.field_predicate_id}'",
            )

            visisted_alternatives.add(alt.field_predicate_id)

            res = alt.visit_field(field, value)
            if res.is_matching():
                final_res = res

            else:
                failed.append(res)

        if final_res:
            return final_res

        else:
            return FieldCheckResult(
                field=field,
                sub_failed=failed,
                field_predicate_id=None,
                value_check=None,
            )


@beartype
@dataclass
class NodeCheckResult():
    is_ok: bool
    on_fail: Optional[Tree] = None

    def format(self, format_if_ok) -> Optional[Tree]:
        if self.is_ok:
            if format_if_ok:
                return None

            else:
                return Tree("Node check ok")

        else:
            return self.on_fail


@beartype
@dataclass
class ClassCheckResult():
    class_predicate_id: Optional[str]
    class_name: org.OrgSemKind
    fields: List[FieldCheckResult] = field(default_factory=list)
    error: Optional[Tree] = None
    unknown_fields: List[str] = field(default_factory=list)
    match_failure: List["ClassCheckResult"] = field(default_factory=list)
    node_check_result: Optional[NodeCheckResult] = None

    def is_matching(self):
        return all(f.is_matching() for f in self.fields) and not self.error and (
            self.node_check_result is None or self.node_check_result.is_ok)

    def format(self, format_if_ok: bool) -> Optional[Tree]:
        if self.is_matching():
            if format_if_ok:
                return Tree(
                    f"Class [green]{self.class_name}[/green] ok with ID [green]{self.class_predicate_id}[/green]"
                )

            else:
                return None

        else:
            res = Tree(
                f"Class [red]{self.class_name}[/red] failed with ID [red]{self.class_predicate_id}[/red]"
            )
            if self.error:
                res.add(self.error)

            if self.node_check_result is not None:
                add_if_ok(res, self.node_check_result.format(format_if_ok))

            if any(not f.is_matching() for f in self.fields):
                sub_fails = Tree("Failed to match fields")
                for field in self.fields:
                    add_if_ok(sub_fails, field.format(format_if_ok))

                res.add(sub_fails)

            if self.match_failure:
                sub_matches = Tree("Failed to match alternatives")
                for fail in self.match_failure:
                    add_if_ok(sub_matches, fail.format(format_if_ok))

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
    class_predicate_id: str
    fields: Mapping[str, FieldAlternatives] = field(default_factory=dict)
    node_predicate: Optional[Callable[[org.Org], NodeCheckResult]] = None

    def visit_type(self, value: org.Org) -> ClassCheckResult:
        res = ClassCheckResult(
            class_name=value.getKind(),
            class_predicate_id=self.class_predicate_id,
        )

        if self.node_predicate:
            res.node_check_result = self.node_predicate(value)

        for field_name, field_value in value.__dict__.items():
            if field_name in self.fields:
                visit_res = self.fields[field_name].visit_field(field_name, field_value)
                res.fields.append(visit_res)

            else:
                res.unknown_fields.append(field_name)

        return res


@beartype
@dataclass
class ClassAlternatives():
    items: List[ClassPrediate] = field(default_factory=list)

    def get_for_id(self, name: str) -> Optional[ClassPrediate]:
        for it in self.items:
            if it.class_predicate_id == name:
                return it

    def visit_type(self, value: org.Org) -> ClassCheckResult:
        failed: List[ClassCheckResult] = []
        final_res: Optional[ClassCheckResult] = None
        for item in self.items:
            res = item.visit_type(value)

            if res.is_matching():
                final_res = res

            else:
                failed.append(res)

        if any(it.class_predicate_id == "subtree_closed_pre_1970" for it in self.items):
            log(CAT).info(
                f"Final res {final_res.class_predicate_id} {final_res.class_name}")

        if final_res:
            return final_res

        else:
            return ClassCheckResult(
                match_failure=failed,
                class_name=value.getKind(),
                class_predicate_id=None,
            )


@beartype
@dataclass
class OrgSpecification:
    alternatives: Mapping[org.OrgSemKind, ClassAlternatives] = field(default_factory=dict)

    def visit(self, node: org.Org) -> Optional[ClassCheckResult]:
        kind = node.getKind()
        if kind in self.alternatives:
            return self.alternatives[kind].visit_type(node)

    def visit_all(self, node: org.Org) -> List[ClassCheckResult]:
        result: List[ClassCheckResult] = []
        visited_kinds: Set[org.OrgSemKind] = set()

        def impl(node: org.Org):
            res = self.visit(node)
            if res is not None:
                result.append(res)

            visited_kinds.add(node.getKind())

        org.eachSubnodeRec(node, impl)

        for kind in org.OrgSemKind(0):
            if kind not in visited_kinds:
                result.append(
                    ClassCheckResult(
                        error=Tree(f"Missing coverage for node kind {kind}"),
                        class_predicate_id=None,
                        class_name=kind,
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
                on_fail=Tree(f"Value '{value}' did not match regex '{regex}'"))

    return FieldPredicate(
        name=field,
        check=ValuePredicate(
            func=functools.partial(regex_check_impl, copy.deepcopy(regex))),
        field_predicate_id=predicate_id,
    )


@beartype
def altN(*args: FieldPredicate) -> FieldAlternatives:
    return FieldAlternatives(items=[*args])


@beartype
def altCls(*args: ClassPrediate) -> ClassAlternatives:
    return ClassAlternatives(items=list(args))


@beartype
def fnBoolOrText(
        func: Callable[[Any], Union[Tree, bool]]) -> Callable[[Any], ValueCheckResult]:

    def impl(func, value):
        res = func(value)
        if isinstance(res, bool) and res == True:
            return ValueCheckResult(is_ok=True)

        else:
            assert isinstance(res, Tree)
            return ValueCheckResult(is_ok=False, on_fail=res)

    return functools.partial(impl, func)


@beartype
def get_regex_field_alternatives(
        field: str, regex_with_id: List[Tuple[str, str]]) -> FieldAlternatives:
    return altN(*(get_regex_field_check(field, rx, id) for rx, id in regex_with_id))


@beartype
def make_check_node_has_subnode_of_kind(kind: org.OrgSemKind):

    def impl(kind: org.OrgSemKind, node: org.Org):
        if any(sub.getKind() == kind for sub in node):
            return NodeCheckResult(is_ok=True)

        else:
            return NodeCheckResult(is_ok=False,
                                   on_fail=Tree(f"No subnode of kind [red]{kind}[/red]"))

    return functools.partial(impl, kind)


@beartype
def altFieldsCheck1(
        name: str, check: Callable[[Any],
                                   ValueCheckResult]) -> Mapping[str, FieldAlternatives]:
    return {
        name:
            altN(
                FieldPredicate(
                    name=name,
                    check=ValuePredicate(func=check),
                    field_predicate_id=name,
                ))
    }


@beartype
def altFieldsCheckN(
    name: str, checks: List[Tuple[str, Callable[[Any], ValueCheckResult]]]
) -> Mapping[str, FieldAlternatives]:
    return {
        name:
            altN(*(FieldPredicate(
                name=name,
                check=ValuePredicate(func=check),
                field_predicate_id=f"{name}_{idx}",
            ) for idx, check in checks))
    }


@beartype
def clsField1Check(predicate_name: str, field_name: str, mapping) -> ClassPrediate:
    if isinstance(mapping, dict):
        return ClassPrediate(
            class_predicate_id=predicate_name,
            fields=mapping,
        )

    elif isinstance(mapping, list):
        return ClassPrediate(
            class_predicate_id=predicate_name,
            fields=altFieldsCheckN(name=field_name, checks=mapping),
        )

    else:
        return ClassPrediate(
            class_predicate_id=predicate_name,
            fields=altFieldsCheck1(name=field_name, check=mapping),
        )


@beartype
def get_subtree_property_spec() -> ClassPrediate:

    def impl(kind: org.NamedPropertyKind,
             properties: List[org.NamedProperty]) -> ValueCheckResult:
        for prop in properties:
            if prop.getKind() == kind:
                return ValueCheckResult(is_ok=True)

        return ValueCheckResult(
            is_ok=False,
            on_fail=Tree(f"No subtree with property {kind}"),
        )

    return ClassPrediate(
        class_predicate_id=f"subtree_with_all_properties",
        fields=altFieldsCheckN(
            "properties",
            checks=list((str(property_kind), functools.partial(impl, property_kind))
                        for property_kind in org.NamedPropertyKind(0)),
        ),
    )


@beartype
def get_subtree_logbook_head_spec() -> List[ClassPrediate]:

    @beartype
    def impl(kind: org.SubtreeLogHeadKind, head: org.SubtreeLogHead) -> ValueCheckResult:
        if head.getLogKind() == kind:
            return ValueCheckResult(is_ok=True)

        else:
            return ValueCheckResult(
                is_ok=False,
                on_fail=Tree(f"No subtree with property {kind}"),
            )

    return list(
        ClassPrediate(
            class_predicate_id=f"subtree_log_with_all_heads",
            fields=altFieldsCheck1(
                "head",
                functools.partial(impl, property_kind),
            ),
        ) for property_kind in org.SubtreeLogHeadKind(0))


@beartype
def get_spec() -> OrgSpecification:
    osk = org.OrgSemKind
    res = OrgSpecification()

    res.alternatives[org.OrgSemKind.Word] = altCls(
        ClassPrediate(
            fields=dict(text=altN(get_regex_field_check("text", ".*", "any_value"))),
            class_predicate_id="text_field",
        ),)

    markup_node_kind = [osk.Bold, osk.Italic, osk.Underline]
    for kind in markup_node_kind:

        def has_different_nested_markup_kind(kind: org.OrgSemKind, node: org.Org):
            if any(sub.getKind() in markup_node_kind for sub in node):
                return NodeCheckResult(is_ok=True)

            else:
                return NodeCheckResult(
                    is_ok=False, on_fail=Tree(f"No subnode of kind [red]{kind}[/red]"))

        res.alternatives[kind] = altCls(
            ClassPrediate(
                class_predicate_id=f"{kind}_with_space",
                node_predicate=make_check_node_has_subnode_of_kind(org.OrgSemKind.Space),
            ),
            ClassPrediate(
                class_predicate_id=f"{kind}_with_different_markup_nested",
                node_predicate=functools.partial(has_different_nested_markup_kind, kind),
            ),
        )

    def check_closed_value(it: org.UserTime):
        if isinstance(it, org.UserTime) and it.getBreakdown().year < 1960:
            return True

        else:
            return Tree("no subtree with year prior to 1960")

    res.alternatives[osk.Subtree] = altCls(
        get_subtree_property_spec(),
        clsField1Check("subtree_closed", "closed", [
            ("closed",
             fnBoolOrText(lambda it: bool(it) or Tree("no subtree with missing 'closed'"))
            ),
            ("closed",
             fnBoolOrText(
                 lambda it: not bool(it) or Tree("no subtree with provided 'closed'"))),
        ]),
        clsField1Check(
            "subtree_closed_pre_1970",
            "closed",
            fnBoolOrText(check_closed_value),
        ),
    )

    res.alternatives[osk.SubtreeLog] = altCls(*get_subtree_logbook_head_spec(),)

    res.alternatives[org.OrgSemKind.BigIdent] = altCls(
        ClassPrediate(
            fields=dict(text=get_regex_field_alternatives("text", [
                ("[A-Z]+", "single_ident"),
                ("[A-Z]+_[A-Z]+", "underscore_ident"),
            ])),
            class_predicate_id="big_ident_text",
        ),)

    return res


def test_run():
    org_corpus_dir = get_haxorg_repo_root_path().joinpath("tests/org/corpus/org")
    file = org_corpus_dir.joinpath("py_validated_all.org")
    node = org.parseFile(str(file), org.OrgParseParameters())
    spec = get_spec()
    coverage = spec.visit_all(node)

    final_mapping: Mapping[org.OrgSemKind, List[Tree]] = dict()
    class_cover_tree: Mapping[org.OrgSemKind, Mapping[str,
                                                      List[ClassCheckResult]]] = dict()

    @beartype
    def add_final_to_type(kind: org.OrgSemKind, node: Optional[Tree]):
        if node is not None:
            if kind not in final_mapping:
                final_mapping[kind] = []

            final_mapping[kind].append(node)

    def add_class_item(item: ClassCheckResult):

        # add_final_to_type(item.class_name, item.format(format_if_ok=False))
        if item.class_name not in class_cover_tree:
            class_cover_tree[item.class_name] = dict()

        if item.class_predicate_id not in class_cover_tree[item.class_name]:
            class_cover_tree[item.class_name][item.class_predicate_id] = []

        if item.class_predicate_id is None:
            for sub_fail in item.match_failure:
                add_class_item(sub_fail)

        else:
            class_cover_tree[item.class_name][item.class_predicate_id].append(item)

    for item in coverage:
        add_class_item(item)

    for class_kind, alternatives in spec.alternatives.items():
        for alt in alternatives.items:
            if class_kind not in class_cover_tree:
                add_final_to_type(
                    class_kind,
                    Tree(f"Document does not have coverage for class kind {class_kind}"),
                )

            elif alt.class_predicate_id not in class_cover_tree[class_kind]:
                add_final_to_type(
                    class_kind,
                    Tree(
                        f"Document does not cover ID {class_kind}.{alt.class_predicate_id}"
                    ))

    for class_kind, class_preciate_map in class_cover_tree.items():
        for class_predicate_id, cover in class_preciate_map.items():
            unknown_fields: Set[str] = set()
            for cov in cover:
                for field in cov.unknown_fields:
                    unknown_fields.add(field)

            for cov in cover:
                for field_check in cov.fields:
                    if field_check.field in unknown_fields:
                        unknown_fields.remove(field_check.field)

            if 0 < len(unknown_fields):
                missing_fields = Tree("No checks defined for fields")
                for f in sorted(unknown_fields):
                    missing_fields.add(Tree(f"{f}"))

                add_final_to_type(class_kind, missing_fields)

            if any(cov.is_matching() for cov in cover):
                field_cover_tree: Mapping[Tuple[str, str],
                                          List[FieldCheckResult]] = dict()
                for cov in cover:
                    for field_check in cov.fields:
                        key = (field_check.field, field_check.field_predicate_id)
                        if key not in field_cover_tree:
                            field_cover_tree[key] = []

                        field_cover_tree[key].append(field_check)

                if class_predicate_id is not None:
                    for field_name, field_predicate in spec.alternatives[
                            class_kind].get_for_id(class_predicate_id).fields.items():
                        for wanted_check in field_predicate.items:
                            key = (field_name, wanted_check.field_predicate_id)
                            if key not in field_cover_tree:
                                field_cover_tree[key] = []

                field_coverage = Tree(
                    f"Field coverage for {class_kind}.{class_predicate_id}")

                for key in sorted(field_cover_tree):
                    check_result = field_cover_tree[key]
                    if 0 < len(check_result):
                        if any(f.is_matching() for f in check_result):
                            pass

                        else:
                            field_coverage.add(
                                Tree(f"No node ever matched {key[0]}.{key[1]}"))

                    else:
                        field_coverage.add(
                            Tree(f"No node ever checked {key[0]}.{key[1]}"))

                if 0 < len(field_coverage.children):
                    add_final_to_type(class_kind, field_coverage)

            else:
                none_covered = Tree(
                    f"No nodes in the input document successfully checked {class_kind}.{class_predicate_id}"
                )

                for cov in cover:
                    add_if_ok(none_covered, cov.format(format_if_ok=False))

                add_final_to_type(class_kind, none_covered)

    final = Tree("Coverage report")

    for kind in sorted(final_mapping, key=lambda it: int(it)):
        kind_tree = Tree(f"{kind}")
        for item in final_mapping[kind]:
            kind_tree.add(item)

        final.add(kind_tree)

    Path("/tmp/report.txt").write_text(render_rich(final, False))
    Path("/tmp/report.ansi").write_text(render_rich(final, True))
