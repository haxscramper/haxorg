#!/usr/bin/env python

import pandas as pd
from py_cli.haxorg_cli import *
from beartype import beartype
from beartype.typing import List, Tuple, Set, Dict, Any, Optional
from py_haxorg.pyhaxorg_utils import getFlatTags
from py_scriptutils.script_logging import log
import py_haxorg.pyhaxorg_wrap as org
from dataclasses import dataclass, field
from py_scriptutils.pandas_utils import dataframe_to_rich_table
from py_scriptutils.rich_utils import render_rich
from pydantic import Field
from collections import defaultdict
from rich.tree import Tree
from rich.console import Console
from difflib import SequenceMatcher
from rich.panel import Panel
from rich.table import Table

CAT = __name__


class TagSortingOptions(BaseModel):
    target_path: Path = Field(description="Input file or directory to analyze files in")
    tag_glossary_file: Path = Field(
        description=
        "org-mode file describing the tags. The structure of the file is not important, just that it uses tags in some way"
    )

    output_dir: Optional[Path] = Field(default=None, description="Directory for all output files")
    autocomplete_file: Optional[Path] = Field(default=None, description="Optional file with one tag per line for autocomplete purposes")

    cachedir: Optional[Path] = None


@beartype
@dataclass(frozen=True)
class OrgTagDesc():
    tag: tuple[str, ...]


def analysis_options(f: Any) -> Any:
    return apply_options(f, options_from_model(TagSortingOptions))


@beartype
def find_duplicate_tags(target_count: Dict[OrgTagDesc, int],
                        duplicates_output: Path) -> None:
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
                duplicates.append(("part_overlap", tag1, tag2))

            tag1_str = "##".join(tag1.tag)
            tag2_str = "##".join(tag2.tag)
            similarity = SequenceMatcher(None, tag1_str, tag2_str).ratio()
            if similarity >= 0.9 and len(tag1_parts) == len(tag2_parts):
                duplicates.append(("similar", tag1, tag2))

            for k, part1 in enumerate(tag1.tag):
                for l, part2 in enumerate(tag2.tag):
                    if k == l:
                        part_similarity = SequenceMatcher(None, part1, part2).ratio()
                        if part_similarity >= 0.8 and part1 != part2:
                            if k == 0:
                                break
                            duplicates.append(("part_similar", tag1, tag2))
                            break

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
        for dup_type, tag1, tag2 in duplicates:
            key = tuple(sorted(["##".join(tag1.tag), "##".join(tag2.tag)]))
            if key not in seen:
                seen.add(key)
                table.add_row(dup_type, "##".join(tag1.tag), "##".join(tag2.tag),
                              str(target_count[tag1]), str(target_count[tag2]))

        console.print(table)

    console.file.close()


@beartype
def build_tag_tree(target_count: Dict[OrgTagDesc, int]) -> Tree:
    tree_data: Dict[str, Any] = defaultdict(lambda: {"count": 0, "children": defaultdict(dict)})

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
def generate_tag_files(target_count: Dict[OrgTagDesc, int],
                       glossary_usage: Set[OrgTagDesc], opts: TagSortingOptions) -> None:
    assert opts.output_dir, "Missing output directory configuration in tag sorting options"
    opts.output_dir.mkdir(parents=True, exist_ok=True)

    stats_output = opts.output_dir / "tag_statistics.csv"
    unknown_output = opts.output_dir / "tag_unknown.csv"
    unused_output = opts.output_dir / "tag_unused.csv"
    tree_output = opts.output_dir / "tag_tree.txt"
    duplicates_output = opts.output_dir / "tag_duplicates.txt"

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
    stats_df.to_csv(stats_output, index=False)
    log(CAT).info(f"Wrote tag statistics to {stats_output}")

    unknown_data = ["##".join(tag_desc.tag) for tag_desc in unknown_tags]
    unknown_df = pd.DataFrame({"tag": sorted(unknown_data)})
    unknown_df.to_csv(unknown_output, index=False)
    log(CAT).info(f"Wrote unknown tags to {unknown_output}")

    unused_data = ["##".join(tag_desc.tag) for tag_desc in unused_tags]
    unused_df = pd.DataFrame({"tag": sorted(unused_data)})
    unused_df.to_csv(unused_output, index=False)
    log(CAT).info(f"Wrote unused tags to {unused_output}")

    tree = build_tag_tree(target_count)
    console = Console(file=open(tree_output, "w"), width=120)
    console.print(tree)
    console.file.close()
    tree_content = tree_output.read_text().replace("│   ", "    ").replace("├── ", "    ").replace("└── ", "    ")
    tree_output.write_text(tree_content)
    log(CAT).info(f"Wrote tag tree to {tree_output}")

    find_duplicate_tags(target_count, duplicates_output=duplicates_output)
    log(CAT).info(f"Wrote duplicate analysis to {duplicates_output}")

    if opts.autocomplete_file and opts.autocomplete_file.exists():
        autocomplete_output = opts.output_dir / "autocomplete.patch"
        
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
        
        with open(autocomplete_output, "w") as f:
            f.write("--- autocomplete_old\n")
            f.write("+++ autocomplete_new\n")
            f.write("@@ -1,1 +1,1 @@\n")
            
            for tag in sorted(tags_to_remove, key=lambda x: "##".join(x.tag)):
                f.write(f"-#{'##'.join(tag.tag)}\n")
            
            for tag in sorted(tags_to_add, key=lambda x: "##".join(x.tag)):
                f.write(f"+#{'##'.join(tag.tag)}\n")
        
        log(CAT).info(f"Wrote autocomplete patch to {autocomplete_output}")

@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@analysis_options
@click.pass_context
def cli(ctx: click.Context, config: Optional[str], **kwargs: Any) -> None:
    pack_context(ctx, "root", TagSortingOptions, config=config, kwargs=kwargs)
    opts: TagSortingOptions = ctx.obj["root"]
    parse_opts = org.OrgParseParameters()

    dir_opts = org.OrgDirectoryParseParameters()

    def parse_node_impl(path: str) -> org.Org:
        try:
            log(CAT).info(f"Parsing file {path}")
            result = parseCachedFile(Path(path), opts.cachedir)
            log(CAT).debug("OK")
            return result

        except Exception as e:
            log(CAT).error(f"Failed parsing {path}", exc_info=e)
            return org.Empty()

    org.setGetParsedNode(dir_opts, parse_node_impl)

    log(CAT).info("Parsing input directory")
    target = org.parseDirectoryOpts(str(opts.target_path), dir_opts)
    log(CAT).info("Directory parse complete")

    target_count: Dict[OrgTagDesc, int] = defaultdict(lambda: 0)

    def visit_target(node: org.Org) -> None:
        if isinstance(node, org.HashTag):
            for tag in getFlatTags(node):
                target_count[OrgTagDesc(tuple(tag))] += 1

    org.eachSubnodeRec(target, visit_target)

    glossary = parseCachedFile(Path(opts.tag_glossary_file), opts.cachedir)

    glossary_usage = set()

    def visit_glossary(node: org.Org) -> None:
        if isinstance(node, org.HashTag):
            for tag in getFlatTags(node):
                glossary_usage.add(OrgTagDesc(tuple(tag)))

    org.eachSubnodeRec(glossary, visit_glossary)

    generate_tag_files(target_count=target_count,
                       glossary_usage=glossary_usage,
                       opts=opts)


if __name__ == "__main__":
    cli()
