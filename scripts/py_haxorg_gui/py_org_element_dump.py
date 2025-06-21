#!/usr/bin/env python

import click
from plumbum import local
import pprint
import sexpdata
import os

from pydantic import BaseModel, Field, Extra
from typing import List, Union, Any, Optional


# Helper function to parse the S-expression into Python data types
def parse_sexpr(data):
    return sexpdata.loads(data)


def sexpr_to_pythonic(data):
    if isinstance(data, list):
        if any(isinstance(x, sexpdata.Symbol) and str(x).startswith(":") for x in data):
            return {
                str(data[i][1:]): sexpr_to_pythonic(data[i + 1])
                for i in range(0, len(data), 2)
                if str(data[i]) != ":parent"
            }
        else:
            result = [sexpr_to_pythonic(x) for x in data]
            if 2 <= len(result) and isinstance(result[0], sexpdata.Symbol) and isinstance(
                    result[1], dict):
                return {
                    "kind": str(result[0]),
                    "content": result[1],
                    "nested": result[2:]
                }
            else:
                return result

    else:
        return data


class OrgContent(BaseModel):
    mode: Optional[str] = None
    begin: int
    end: int
    level: Optional[int] = None
    language: Optional[str] = None
    parameters: Optional[str] = None
    value: Optional[str] = None
    contents_begin: Optional[int] = Field(default=None, alias="contents-begin")
    contents_end: Optional[int] = Field(default=None, alias="contents-end")
    CATEGORY: List = Field(default_factory=list)
    granularity: List = Field(default_factory=list)
    path: List = Field(default_factory=list)
    post_affiliated: Optional[int] = Field(default=None, alias="post-affiliated")
    post_blank: Optional[int] = Field(default=None, alias="post-blank")
    robust_begin: Optional[int] = Field(default=None, alias="robust-begin")
    robust_end: Optional[int] = Field(default=None, alias="robust-end")
    archivedp: List = Field(default_factory=list, alias="archivedp")
    isCommented: List = Field(default_factory=list, alias="commentedp")
    isFootnoteSection: List = Field(default_factory=list, alias="footnote-section-p")
    priority: List = Field(default_factory=list)
    pre_blank: Optional[int] = Field(default=None, alias="pre-blank")
    raw_value: Optional[str] = Field(default=None, alias="raw-value")
    tags: List = Field(default_factory=list)
    title: List[Union[str, Any]] = Field(default_factory=list)
    todo_keyword: List = Field(default_factory=list, alias="todo-keyword")
    todo_type: List = Field(default_factory=list, alias="todo-type")
    label_fmt: List = Field(default_factory=list, alias="label-fmt")
    number_lines: List = Field(default_factory=list, alias="number-lines")
    preserve_indent: List = Field(default_factory=list, alias="preserve-indent")
    retain_labels: Optional[bool] = Field(default=None, alias="retain-labels")
    switches: List = Field(default_factory=list)
    use_labels: Optional[bool] = Field(default=None, alias="use-labels")

    class Config:
        extra = Extra.forbid


class OrgNode(BaseModel):
    kind: str
    content: OrgContent
    nested: List['OrgNode']


OrgContent.update_forward_refs()


class OrgData(BaseModel):
    nested: List[OrgNode]
    kind: str


@click.command()
@click.argument('orgfile', type=click.Path(exists=True, readable=True))
def main(orgfile):
    """Parses an org-mode file into an AST using Emacs and the org-element API."""
    elisp = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                         "py_org_element_dump.el")

    # Emacs command to dump org-mode AST to stdout
    elisp_code = f"""
    (progn
      (load-file "{elisp}")
      (print (dump-org-element "{orgfile}")))
    """

    emacs_cmd = local["emacs"]
    result = emacs_cmd.run(("--batch", "--eval", elisp_code), retcode=None)

    if result[0] != 0:
        with open("/tmp/debug.txt", "w") as file:
            print(result[1], file=file)

    else:
        print(result[1])

    # # Parse the S-expression output into Python data types
    parsed_data = sexpr_to_pythonic(parse_sexpr(result[1]))

    # # Pretty print the result
    with open("/tmp/ast.py", "w") as file:
        pprint.pprint(parsed_data, width=120, stream=file)

    data = OrgData(**parsed_data)
    pprint.pprint(
        data.dict(exclude_none=True,
                  exclude_unset=True,
                  exclude_defaults=True,
                  by_alias=True))


if __name__ == "__main__":
    main()
