#!/usr/bin/env python

import yaml
from yaml.loader import SafeLoader
from pydantic import BaseModel, Field
from beartype.typing import List, Optional, Set
from beartype import beartype
import os


class Action(BaseModel):
    do: str
    to: str
    from_: str = Field(alias="from")




class Rule(BaseModel):
    re: Optional[str] = None
    lit: Optional[str] = None
    token: str
    states: Optional[List[str]] = None
    actions: Optional[List[Action]] = None
    line: Optional[int] = None


class State(BaseModel):
    name: str
    kind: str
    line: Optional[int]


class Configuration(BaseModel):
    states: List[State]
    rules: List[Rule]


class SafeLineLoader(SafeLoader):

    def construct_mapping(self, node, deep=False):
        mapping = super(SafeLineLoader, self).construct_mapping(node, deep=deep)
        mapping['__line__'] = node.start_mark.line + 1
        return mapping


@beartype
def parse_yaml_to_pydantic(file_path: str) -> Configuration:
    with open(file_path, 'r') as f:
        data = yaml.load(f, Loader=SafeLineLoader)

    # Process line information for sub-lists
    for state in data["states"]:
        state["line"] = state.pop("__line__", None)

    for rule in data["rules"]:
        rule["line"] = rule.pop("__line__", None)

    return Configuration(**data)


MATCH_WIDTH = 40
ENUM_NAME = "BaseTokenKind"


# Convert rule data to re/flex code pattern
@beartype
def rule_to_reflex_code(rule: Rule) -> str:
    state_prefix = ""
    if rule.states:
        state_prefix = "<{}>".format(",".join(rule.states))

    if rule.re:
        state_prefix = (state_prefix + rule.re).ljust(MATCH_WIDTH)

    else:
        state_prefix = f"{state_prefix}\"{rule.lit}\"".ljust(MATCH_WIDTH)

    actions = []

    if rule.actions:
        for action in rule.actions:
            if action.do == "push":
                actions.append(f"push_state({action.to});")
            elif action.do == "pop":
                actions.append(f"pop_expect({action.from_}, {action.to});")

    actions_code = " ".join(actions)
    return f"{state_prefix} {{ /*{rule.line:<4}*/ add({ENUM_NAME}::{rule.token}); {actions_code} }}"


@beartype
def generate_enum(config: Configuration) -> str:
    return """
enum class {enum} : unsigned short int {{
  {tokens},
}};
    
""".format(enum=ENUM_NAME,
           tokens=",\n  ".join(sorted(set([rule.token for rule in config.rules]))))


@beartype
def generate_state(config: Configuration) -> str:
    tokens = sorted(set([rule.token for rule in config.rules]))
    return """
std::string BaseLexerImpl::state_name(int state) {{
    switch(state) {{
{mappings}
        default: return std::to_string(state);
    }}
}}

std::string enum_serde<BaseTokenKind>::to_string(const BaseTokenKind &value) {{
    switch(value) {{
{values}
    }}
}}

""".format(mappings="\n".join([
        f"        case {idx}: return \"{state.name}\";"
        for idx, state in enumerate(config.states)
    ]),
           values="\n".join([
               f"        case BaseTokenKind::{name}: return \"{name}\";" for name in tokens
           ]))


@beartype
def generate_reflex_code(config: Configuration) -> str:
    rules = "\n".join([rule_to_reflex_code(rule) for rule in config.rules])

    return """

%top{{
#include <string_view>
#include <vector>
#include <locale>
#include <codecvt>
#include <iostream>
#include <format>
#include <absl/log/check.h>
#include "base_token.hpp"

#define pop_expect(current, next) pop_expect_impl(current, next, __LINE__)
%}}

%option fast freespace unicode

{states}

%class{{
  public:
    BaseLexerImpl impl;
    void add(BaseTokenKind token) {{ impl.add(token); }}
    void pop_expect_impl(int current, int next, int line) {{
        impl.pop_expect_impl(current, next, line);
    }}
}}

%%



{rules}  

%%

std::vector<BaseToken> tokenize(const char* input, int size) {{
    base_lexer::Lexer lex(input);
    lex.impl.impl = &lex;
    lex.impl.tokens.reserve(size / 3);
    lex.lex();
    return lex.impl.tokens;
}}

    """.format(rules=rules,
               states="\n".join(
                   [f"%{state.kind} {state.name}".format() for state in config.states]))


# Example usage:
DIR = os.path.dirname(os.path.abspath(__file__))
config = parse_yaml_to_pydantic(os.path.join(DIR, "base_lexer.yaml"))

def write_if_new(path: str, content: str):
    if not os.path.exists(path) or open(path).read() != content:
        with open(path, "w") as file:
            file.write(content)

write_if_new(os.path.join(DIR, "base_token_kind.hpp"), generate_enum(config))
write_if_new(os.path.join(DIR, "base_token_state.tcc"), generate_state(config)) 
write_if_new(os.path.join(DIR, "base_lexer.l"), generate_reflex_code(config)) 
