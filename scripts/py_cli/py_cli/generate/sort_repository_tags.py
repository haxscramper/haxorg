#!/usr/bin/env python

from collections import defaultdict
from dataclasses import dataclass
from difflib import SequenceMatcher
import enum
from pathlib import Path

from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Set
import pandas as pd
from py_cli import haxorg_cli, haxorg_opts
from py_haxorg.pyhaxorg_utils import getFlatTags
import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import get_user_provided_params
from rich.console import Console
from rich.panel import Panel
from rich.table import Table
from rich.tree import Tree
import rich_click as click

CAT = __name__


@beartype
@dataclass(frozen=True)
class OrgTagDesc():
    tag: tuple[str, ...]


class DuplicateType(enum.Enum):
    PART_OVERLAP = "part_overlap"
    SIMILAR = "similar"
    PART_SIMILAR = "part_similar"


@dataclass
class TagDuplicate:
    type: DuplicateType
    tag1: OrgTagDesc
    tag2: OrgTagDesc
    count1: int
    count2: int


class TagCollectionArtifacts():
    stats_output: Path
    unknown_output: Path
    unused_output: Path
    tree_output: Path
    duplicates_output: Path
    autocomplete_output: Path
    tag_tree: Tree
    duplicate_tag_list: List[TagDuplicate]


@beartype
def _find_duplicate_tags_data(target_count: Dict[OrgTagDesc, int]) -> List[TagDuplicate]:
    tags = list(target_count.keys())
    duplicates = []

    for i, tag1 in enumerate(tags):
        for j, tag2 in enumerate(tags[i + 1:], i + 1):
            tag1_parts = tag1.tag
            tag2_parts = tag2.tag

            is_overlap = False

            if set(tag1_parts).issubset(set(tag2_parts)):
                if not (len(tag1_parts) <= len(tag2_parts) and
                        tag2_parts[:len(tag1_parts)] == tag1_parts):
                    is_overlap = True
            elif set(tag2_parts).issubset(set(tag1_parts)):
                if not (len(tag2_parts) <= len(tag1_parts) and
                        tag1_parts[:len(tag2_parts)] == tag2_parts):
                    is_overlap = True
            elif any(tag1_parts[k:k + len(tag2_parts)] == tag2_parts
                     for k in range(1,
                                    len(tag1_parts) - len(tag2_parts) + 1)):
                is_overlap = True
            elif any(tag2_parts[k:k + len(tag1_parts)] == tag1_parts
                     for k in range(1,
                                    len(tag2_parts) - len(tag1_parts) + 1)):
                is_overlap = True

            if is_overlap:
                duplicates.append(
                    TagDuplicate(type=DuplicateType.PART_OVERLAP,
                                 tag1=tag1,
                                 tag2=tag2,
                                 count1=target_count[tag1],
                                 count2=target_count[tag2]))

            tag1_str = "##".join(tag1.tag)
            tag2_str = "##".join(tag2.tag)
            similarity = SequenceMatcher(None, tag1_str, tag2_str).ratio()
            if similarity >= 0.9 and len(tag1_parts) == len(tag2_parts):
                duplicates.append(
                    TagDuplicate(type=DuplicateType.SIMILAR,
                                 tag1=tag1,
                                 tag2=tag2,
                                 count1=target_count[tag1],
                                 count2=target_count[tag2]))

            for k, part1 in enumerate(tag1.tag):
                for l, part2 in enumerate(tag2.tag):
                    if k == l:
                        part_similarity = SequenceMatcher(None, part1, part2).ratio()
                        if part_similarity >= 0.8 and part1 != part2:
                            if k == 0:
                                break
                            duplicates.append(
                                TagDuplicate(type=DuplicateType.PART_SIMILAR,
                                             tag1=tag1,
                                             tag2=tag2,
                                             count1=target_count[tag1],
                                             count2=target_count[tag2]))
                            break

    return duplicates


@beartype
def _format_duplicate_tags_table(duplicates: List[TagDuplicate],
                                 duplicates_output: Path) -> None:
    console = Console(file=open(duplicates_output, "w"), width=120)

    console.print(Panel.fit("Tag Duplicate Analysis", style="bold blue"))

    if not duplicates:
        console.print("No potential duplicates found.", style="green")
    else:
        table = Table(title="Potential Duplicates")
        table.add_column("Type", style="cyan")
        table.add_column("Tag 1", style="magenta")
        table.add_column("Tag 2", style="magenta")
        table.add_column("Count 1", style="yellow")
        table.add_column("Count 2", style="yellow")

        seen = set()
        for duplicate in duplicates:
            key = tuple(
                sorted(["##".join(duplicate.tag1.tag), "##".join(duplicate.tag2.tag)]))
            if key not in seen:
                seen.add(key)
                table.add_row(duplicate.type.value, "##".join(duplicate.tag1.tag),
                              "##".join(duplicate.tag2.tag), str(duplicate.count1),
                              str(duplicate.count2))

        console.print(table)

    console.file.close()


@beartype
def _build_tag_tree(target_count: Dict[OrgTagDesc, int]) -> Tree:
    tree_data: Dict[str, Any] = defaultdict(lambda: {
        "count": 0,
        "children": defaultdict(dict)
    })

    for tag_desc, count in target_count.items():
        current = tree_data
        for i, part in enumerate(tag_desc.tag):
            if part not in current:
                current[part] = {"count": 0, "children": defaultdict(dict)}
            current[part]["count"] = current[part]["count"] + count
            current = current[part]["children"]

    def create_tree_node(data: dict, name: str = "Tags") -> Tree:
        root = Tree(name)

        sorted_items = sorted(data.items(), key=lambda x: x[1]["count"], reverse=True)

        for tag_name, tag_info in sorted_items:
            node_label = f"{tag_name} ({tag_info['count']})"
            if tag_info["children"]:
                subtree = create_tree_node(tag_info["children"], node_label)
                root.add(subtree)
            else:
                root.add(node_label)

        return root

    return create_tree_node(tree_data)


@beartype
def _generate_tag_files(
    target_count: Dict[OrgTagDesc, int],
    glossary_usage: Set[OrgTagDesc],
    opts: haxorg_opts.TagSortingOptions,
    result: TagCollectionArtifacts,
) -> None:
    assert opts.output_dir, "Missing output directory configuration in tag sorting options"
    opts.output_dir.mkdir(parents=True, exist_ok=True)

    result.stats_output = opts.output_dir / "tag_statistics.csv"
    result.unknown_output = opts.output_dir / "tag_unknown.csv"
    result.unused_output = opts.output_dir / "tag_unused.csv"
    result.tree_output = opts.output_dir / "tag_tree.txt"
    result.duplicates_output = opts.output_dir / "tag_duplicates.txt"

    target_tags = set(target_count.keys())
    unknown_tags = target_tags - glossary_usage
    unused_tags = glossary_usage - target_tags

    stats_data = []
    for tag_desc, count in target_count.items():
        tag_str = "##".join(tag_desc.tag)
        in_glossary = tag_desc in glossary_usage
        stats_data.append({"tag": tag_str, "count": count, "in_glossary": in_glossary})

    stats_df = pd.DataFrame(stats_data)
    stats_df = stats_df.sort_values("tag")
    stats_df.to_csv(result.stats_output, index=False)

    unknown_data = ["##".join(tag_desc.tag) for tag_desc in unknown_tags]
    unknown_df = pd.DataFrame({"tag": sorted(unknown_data)})
    unknown_df.to_csv(result.unknown_output, index=False)

    unused_data = ["##".join(tag_desc.tag) for tag_desc in unused_tags]
    unused_df = pd.DataFrame({"tag": sorted(unused_data)})
    unused_df.to_csv(result.unused_output, index=False)

    result.tag_tree = _build_tag_tree(target_count)
    console = Console(file=open(result.tree_output, "w"), width=120)
    console.print(result.tag_tree)
    console.file.close()
    tree_content = result.tree_output.read_text().replace("│   ", "    ").replace(
        "├── ", "    ").replace("└── ", "    ")
    result.tree_output.write_text(tree_content)

    result.duplicate_tag_list = _find_duplicate_tags_data(target_count)
    _format_duplicate_tags_table(duplicates=result.duplicate_tag_list,
                                 duplicates_output=result.duplicates_output)

    if opts.autocomplete_file and opts.autocomplete_file.exists():
        result.autocomplete_output = opts.output_dir / "autocomplete.patch"

        with open(opts.autocomplete_file, "r") as f:
            autocomplete_tags = set()
            for line in f:
                line = line.strip()
                if line:
                    tag_parts = tuple(line.lstrip("#").split("##"))
                    autocomplete_tags.add(OrgTagDesc(tag=tag_parts))

        all_referenced_tags = target_tags | glossary_usage

        tags_to_add = all_referenced_tags - autocomplete_tags
        tags_to_remove = autocomplete_tags - all_referenced_tags

        with open(result.autocomplete_output, "w") as f:
            f.write("--- autocomplete_old\n")
            f.write("+++ autocomplete_new\n")
            f.write("@@ -1,1 +1,1 @@\n")

            for tag in sorted(tags_to_remove, key=lambda x: "##".join(x.tag)):
                f.write(f"-#{'##'.join(tag.tag)}\n")

            for tag in sorted(tags_to_add, key=lambda x: "##".join(x.tag)):
                f.write(f"+#{'##'.join(tag.tag)}\n")


@beartype
def sort_reposutory_tags(ctx: haxorg_cli.CliRunContext) -> TagCollectionArtifacts:
    opts = ctx.opts
    assert opts.generate
    assert opts.generate.sort_tags
    dir_opts = org.OrgDirectoryParseParameters()
    result = TagCollectionArtifacts()
    target = haxorg_cli.parseDirectory(ctx, opts.generate.sort_tags.input_dir)
    target_count: Dict[OrgTagDesc, int] = defaultdict(lambda: 0)

    def visit_target(node: org.Org) -> None:
        if isinstance(node, org.HashTag):
            for tag in getFlatTags(node):
                target_count[OrgTagDesc(tuple(tag))] += 1

    org.eachSubnodeRec(target, visit_target)

    glossary = haxorg_cli.parseCachedFile(ctx,
                                          Path(opts.generate.sort_tags.tag_glossary_file))

    glossary_usage = set()

    def visit_glossary(node: org.Org) -> None:
        if isinstance(node, org.HashTag):
            for tag in getFlatTags(node):
                glossary_usage.add(OrgTagDesc(tuple(tag)))

    org.eachSubnodeRec(glossary, visit_glossary)

    _generate_tag_files(
        target_count=target_count,
        glossary_usage=glossary_usage,
        opts=opts.generate.sort_tags,
        result=result,
    )

    return result


@click.command("sort_tags")
@haxorg_cli.get_wrap_options(haxorg_opts.TagSortingOptions)
@click.pass_context
def sort_repository_tags_cli(ctx: click.Context, **kwargs: Any) -> None:
    """
    Collect all the hashtags and subtree tags in the repository and summarize
    usage frequency, nesting structure etc. into the single report file.
    """
    sort_reposutory_tags(haxorg_cli.get_opts(ctx))
