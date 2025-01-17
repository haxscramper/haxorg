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
    field_predicate_id: str
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
            if self.value_check and self.value_check.on_fail:
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

    def visit_field(self, field: str, value: Any) -> Optional[FieldCheckResult]:
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
    unknown_fields: List[str] = field(default_factory=list)
    node_check_result: Optional[NodeCheckResult] = None

    def is_matching(self):
        return all(
            f.is_matching() for f in self.fields) and (self.node_check_result is None or
                                                       self.node_check_result.is_ok)

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

            if self.node_check_result is not None:
                add_if_ok(res, self.node_check_result.format(format_if_ok))

            if any(not f.is_matching() for f in self.fields):
                sub_fails = Tree("Failed to match fields")
                for field in self.fields:
                    add_if_ok(sub_fails, field.format(format_if_ok))

                res.add(sub_fails)

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
                if visit_res is not None:
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

    def visit_type(self, value: org.Org) -> List[ClassCheckResult]:
        res_list: List[ClassCheckResult] = []
        visited: Set[str] = set()
        for item in self.items:
            assert item.class_predicate_id not in visited, f"Duplicate class alternative for ID {item.class_predicate_id}"
            visited.add(item.class_predicate_id)
            res_list.append(item.visit_type(value))

        return res_list


@beartype
@dataclass
class OrgSpecification:
    alternatives: Mapping[org.OrgSemKind, ClassAlternatives] = field(default_factory=dict)

    def visit(self, node: org.Org) -> List[ClassCheckResult]:
        kind = node.getKind()
        if kind in self.alternatives:
            return self.alternatives[kind].visit_type(node)

        else:
            return []

    def visit_all(self, node: org.Org) -> List[ClassCheckResult]:
        result: List[ClassCheckResult] = []
        visited_kinds: Set[org.OrgSemKind] = set()

        def impl(node: org.Org):
            nonlocal result
            res = self.visit(node)
            if res is not None:
                result += res

            visited_kinds.add(node.getKind())

        org.eachSubnodeRec(node, impl)

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
def valueFnBoolOrText(
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
def boolableField(field_name: str,
                  expected: bool) -> Tuple[str, Callable[[Any], ValueCheckResult]]:

    def impl(val: bool, it):
        if bool(it) == val:
            return ValueCheckResult(is_ok=True)

        else:
            return ValueCheckResult(is_ok=False,
                                    on_fail=Tree(f"Expected bool({field_name}) == {val}"))

    return (field_name, functools.partial(impl, expected))


@beartype
def boolableField2(
        field_name: str) -> List[Tuple[str, Callable[[Any], ValueCheckResult]]]:
    return [
        boolableField(field_name, True),
        boolableField(field_name, False),
    ]


@beartype
def nodeFnBoolOrText(
        func: Callable[[org.Org], Union[Tree,
                                        bool]]) -> Callable[[org.Org], NodeCheckResult]:

    def impl(func, value):
        res = func(value)
        if isinstance(res, bool) and res == True:
            return NodeCheckResult(is_ok=True)

        else:
            assert isinstance(res, Tree)
            return NodeCheckResult(is_ok=False, on_fail=res)

    return functools.partial(impl, func)


@beartype
def nodeCls(class_predicate_id: str, func: Callable[[org.Org],
                                                    NodeCheckResult]) -> ClassPrediate:
    return ClassPrediate(class_predicate_id=class_predicate_id, node_predicate=func)


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
            return NodeCheckResult(
                is_ok=False,
                on_fail=Tree(
                    f"No subnode of kind [red]{kind}[/red] in"
                    # f"No subnode of kind [red]{kind}[/red] in {org.treeRepr(node, colored=False)}"
                ))

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
def get_subtree_property_spec() -> List[ClassPrediate]:

    def impl(kind: org.NamedPropertyKind,
             properties: List[org.NamedProperty]) -> ValueCheckResult:
        for prop in properties:
            if prop.getKind() == kind:
                return ValueCheckResult(is_ok=True)

        return ValueCheckResult(
            is_ok=False,
            on_fail=Tree(f"No subtree with property {kind}"),
        )

    return list(
        ClassPrediate(
            class_predicate_id=f"subtree_with_all_{property_kind}_property",
            fields=altFieldsCheck1(
                "properties",
                functools.partial(impl, property_kind),
            ),
        ) for property_kind in org.NamedPropertyKind(0))


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
            class_predicate_id=f"subtree_log_with_{property_kind}",
            fields=altFieldsCheck1(
                "head",
                functools.partial(impl, property_kind),
            ),
        ) for property_kind in org.SubtreeLogHeadKind(0))


@beartype
def get_block_spec(kind: org.OrgSemKind) -> List[ClassPrediate]:
    Block_alternatives: List[ClassPrediate] = []

    def impl_expect(kind: org.OrgSemKind, attached: List[org.Org]):
        if any(at.getKind() == kind for at in attached):
            return ValueCheckResult(is_ok=True)

        else:
            return ValueCheckResult(is_ok=False, on_fail=Tree(f"Not {kind} in attached"))

    for attached_kind in [org.OrgSemKind.CmdCaption, org.OrgSemKind.CmdName]:
        Block_alternatives.append(
            clsField1Check(
                f"with_{attached_kind}_attached",
                "attached",
                [(f"{attached_kind}", functools.partial(impl_expect, attached_kind))],
            ))

    def impl_not_expect(attached: List[org.Org]):
        if len(attached) == 0:
            return ValueCheckResult(is_ok=True)

        else:
            return ValueCheckResult(is_ok=False, on_fail=Tree(f"Not empty in attached"))

    Block_alternatives.append(
        clsField1Check(
            f"with_no_attached",
            "attached",
            [(f"{attached_kind}", impl_not_expect)],
        ))

    return Block_alternatives


@beartype
def get_spec() -> OrgSpecification:
    osk = org.OrgSemKind
    res = OrgSpecification()

    res.alternatives[org.OrgSemKind.Word] = altCls(
        ClassPrediate(
            fields=dict(text=altN(get_regex_field_check("text", ".*", "any_value"))),
            class_predicate_id="text_field",
        ),)

    markup_node_kind = [osk.Bold, osk.Italic, osk.Underline, osk.Strike]
    for kind in markup_node_kind:

        def has_different_nested_markup_kind(kind: org.OrgSemKind, node: org.Org):
            if any(sub.getKind() in markup_node_kind for sub in node):
                return NodeCheckResult(is_ok=True)

            else:
                return NodeCheckResult(
                    is_ok=False,
                    on_fail=Tree(
                        f"No subnode of kind [red]{kind}[/red]"
                        # f"No subnode of kind [red]{kind}[/red] in {org.treeRepr(node, colored=False)}"
                    ))

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
        if isinstance(it, org.UserTime) and it.getBreakdown().year < 1970:
            return True

        else:
            return Tree("no subtree with year prior to 1960")

    res.alternatives[osk.Subtree] = altCls(
        *get_subtree_property_spec(),
        clsField1Check("subtree_closed", "closed", boolableField2("closed")),
        clsField1Check("subtree_archiving", "isArchived", boolableField2("isArchived")),
        clsField1Check("subtree_comment", "isComment", boolableField2("isComment")),
        clsField1Check(
            "subtree_closed_pre_1970",
            "closed",
            valueFnBoolOrText(check_closed_value),
        ),
    )

    res.alternatives[osk.Paragraph] = altCls(
        nodeCls(
            "footnote_definition_paragraph",
            nodeFnBoolOrText(lambda node:
                             (isinstance(node, org.Paragraph) and node.
                              isFootnoteDefinition()) or Tree("No footnote definition")),
        ),
        nodeCls(
            "paragraph_with_admonition",
            nodeFnBoolOrText(lambda node:
                             (isinstance(node, org.Paragraph) and node.hasAdmonition()
                             ) or Tree("No paragraph with admonition")),
        ),
        nodeCls(
            "paragraph_with_lead_hashtag",
            nodeFnBoolOrText(lambda node:
                             (isinstance(node, org.Paragraph) and node.hasLeadHashtags()
                             ) or Tree("No paragraph with lead hashtag")),
        ),
        nodeCls(
            "paragraph_with_lead_timestamp",
            nodeFnBoolOrText(lambda node:
                             (isinstance(node, org.Paragraph) and node.hasTimestamp()
                             ) or Tree("No paragraph with lead timestamp")),
        ),
    )

    Time_alternatives: List[ClassPrediate] = []

    def breakdown_cutoff(field_list: List[str], node: org.Time):
        for field_name, value in node.getStaticTime().getBreakdown().__dict__.items():
            if field_name in field_list:
                if not isinstance(value, int) or value == 0:
                    return NodeCheckResult(
                        is_ok=False,
                        on_fail=Tree(
                            f"Expected field {field_name} to be listed in breakdown"))

            else:
                if isinstance(value, int) and value != 0:
                    return NodeCheckResult(
                        is_ok=False,
                        on_fail=Tree(
                            f"Expected field {field_name} to be absent from breakdown"))

        return NodeCheckResult(is_ok=True)

    for field_names in [
        ["year", "month", "day"],
        ["year", "month", "day", "hour", "minute"],
        ["year", "month", "day", "hour", "minute", "second"],
    ]:
        Time_alternatives.append(
            nodeCls(
                f"breakdown_for_{field_names}",
                functools.partial(breakdown_cutoff, field_names),
            ))

    Time_alternatives.append(
        clsField1Check("time_isActive", "isActive", [
            boolableField("isActive", True),
            boolableField("isActive", False),
        ]))

    res.alternatives[osk.Time] = altCls(*Time_alternatives)

    Link_alternatives: List[ClassPrediate] = []
    for kind in org.LinkTargetKind(0):

        def impl(kind: org.LinkTargetKind, target: org.LinkTarget):
            if target.getKind() == kind:
                log(CAT).info(f"Got target with kind {kind}")
                return ValueCheckResult(is_ok=True)

            else:
                return ValueCheckResult(is_ok=False, on_fail=Tree(f"Expected {kind}"))

        Link_alternatives.append(
            clsField1Check(
                f"link_with_{kind}_target",
                "target",
                [(f"{kind}", functools.partial(impl, kind))],
            ))

    res.alternatives[osk.Link] = altCls(*Link_alternatives)

    res.alternatives[osk.SubtreeLog] = altCls(*get_subtree_logbook_head_spec(),)

    res.alternatives[org.OrgSemKind.BigIdent] = altCls(
        ClassPrediate(
            fields=dict(text=get_regex_field_alternatives("text", [
                ("[A-Z]+", "single_ident"),
                ("[A-Z]+_[A-Z]+", "underscore_ident"),
            ])),
            class_predicate_id="big_ident_text",
        ),)

    block_kinds = [
        osk.BlockQuote,
        osk.BlockCenter,
        osk.BlockComment,
        osk.BlockCode,
        osk.BlockVerse,
        osk.BlockExample,
        osk.BlockExport,
    ]

    for kind in block_kinds:
        res.alternatives[kind] = altCls(*get_block_spec(kind))

    for kind in org.OrgSemKind(0):
        if kind not in res.alternatives:
            res.alternatives[kind] = altCls(ClassPrediate("placeholder"))

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
        if item.class_name not in class_cover_tree:
            class_cover_tree[item.class_name] = dict()

        if item.class_predicate_id is None:
            for sub_fail in item.grouped:
                add_class_item(sub_fail)

        else:
            if item.class_predicate_id not in class_cover_tree[item.class_name]:
                class_cover_tree[item.class_name][item.class_predicate_id] = []

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

    for kind in org.OrgSemKind(0):
        if kind not in class_cover_tree:
            add_final_to_type(kind, Tree(f"Missing coverage for node kind {kind}"))

    for class_kind, class_preciate_map in class_cover_tree.items():
        unknown_fields: Set[str] = set()
        for class_predicate_id, cover in class_preciate_map.items():
            for cov in cover:
                for field in cov.unknown_fields:
                    unknown_fields.add(field)

            for cov in cover:
                for field_check in cov.fields:
                    if field_check.field in unknown_fields:
                        unknown_fields.remove(field_check.field)

        if "subnodes" in unknown_fields:
            unknown_fields.remove("subnodes")

        if 0 < len(unknown_fields):
            missing_fields = Tree("No checks defined for fields")
            for f in sorted(unknown_fields):
                missing_fields.add(Tree(f"{f}"))

            add_final_to_type(class_kind, missing_fields)

        for class_predicate_id, cover in class_preciate_map.items():
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
