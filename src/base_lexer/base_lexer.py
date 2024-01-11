#!/usr/bin/env python

import yaml
from yaml.loader import SafeLoader
from pydantic import BaseModel, Field
from beartype.typing import List, Optional, Literal
from beartype import beartype
import os


class Action(BaseModel):
    # When token is matched, what to do
    do: Literal["push", "pop", "set", "raw", "token"]
    to: Optional[str] = None
    from_: Optional[str] = Field(alias="from", default=None)
    raw: Optional[str] = None


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


class RxMacro(BaseModel):
    # Substitute `{name}` in the regex pattern with a common string replacement
    name: str
    value: str
    line: Optional[int] = None


class TokenDesc(BaseModel):
    name: str


class Configuration(BaseModel):
    states: List[State] # List of states that lexer can transition between
    rules: List[Rule] # Regex/literal matching rules
    # Explicitly specified list of tokens to be added to whatever was detected in the 'rules'
    tokens: List[TokenDesc] = Field(default_factory=list) 
    # Regular expression macros to save on re-typing the same thing
    rx_macros: List[RxMacro] = Field(default_factory=list)


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
def rule_to_reflex_code(rule: Rule, macros: dict[str, str]) -> str:
    state_prefix = ""
    if rule.states:
        state_prefix = "<{}>".format(",".join(rule.states))

    if rule.re:
        state_prefix = (state_prefix + rule.re.format(**macros)).ljust(MATCH_WIDTH)

    else:
        state_prefix = f"{state_prefix}\"{rule.lit}\"".ljust(MATCH_WIDTH)

    actions = []

    if rule.actions:
        for action in rule.actions:
            match action.do:
                case "push":
                    actions.append(f"push_expect({action.from_}, {action.to});")

                case "pop":
                    actions.append(f"pop_expect({action.from_}, {action.to});")

                case "set":
                    actions.append(f"start({action.to});")

                case "raw":
                    actions.append(action.raw)

                case "token":
                    actions.append(f"impl.add({ENUM_NAME}::{action.to});")

                case _:
                    raise ValueError(f"Unexpected action 'do' value: {action.do}")

                

    actions_code = " ".join(actions)
    content = " ".join([
        f"impl.before({rule.line}, {ENUM_NAME}::{rule.token}, R\"raw({rule.re or rule.lit})raw\");",
        f"impl.add({ENUM_NAME}::{rule.token});",
        actions_code,
        f"impl.after({rule.line});",
    ])
    return f"{state_prefix} {{ /*{rule.line:<4}*/ {content} }}"


@beartype
def generate_enum(config: Configuration) -> str:
    return """
enum class {enum} : unsigned short int {{
  {tokens},
}};
    
""".format(enum=ENUM_NAME,
           tokens=",\n  ".join(
               sorted(
                   set([token.name for token in config.tokens] +
                       [rule.token for rule in config.rules]))))


@beartype
def generate_state(config: Configuration) -> str:
    tokens = sorted(set([rule.token for rule in config.rules] + [tok.name for tok in config.tokens]))
    return """
std::string BaseLexerImpl::state_name(int state) {{
    switch(state) {{
        case 0: return "INITIAL";
{mappings}
        default: return std::to_string(state);
    }}
}}

std::string enum_serde<BaseTokenKind>::to_string(const BaseTokenKind &value) {{
    switch(value) {{
{values}
    }}
}}

Opt<BaseTokenKind> enum_serde<BaseTokenKind>::from_string(std::string const& value) {{
{from_string}
}}

""".format(
        mappings="\n".join([
            f"        case {idx + 1}: return \"{state.name}\";"
            for idx, state in enumerate(config.states)
        ]),
        values="\n".join([
            f"        case BaseTokenKind::{name}: return \"{name}\";" for name in tokens
        ]),
        from_string="\n".join([
            f"  if (value == \"{name}\") {{ return BaseTokenKind::{name}; }} else"
            for name in tokens
        ] + ["  { return std::nullopt; }"]),)


@beartype
def generate_reflex_code(config: Configuration) -> str:
    macros = {m.name: m.value for m in config.rx_macros}
    rules = "\n".join([rule_to_reflex_code(rule, macros) for rule in config.rules])

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

#define pop_expect(current, next) impl.pop_expect_impl(current, next, __LINE__)
#define push_expect(current, next) impl.push_expect_impl(current, next, __LINE__)
%}}

%option fast freespace unicode

{states}

%class{{
  public:
    BaseLexerImpl impl;
}}

%%

{rules}  

(.|\\n) {{ impl.unknown(); }}
{unknowns}

%%

TokenGroup<BaseTokenKind, BaseFill> tokenize(const char* input, int size, std::ostream* traceStream) {{
    base_lexer::Lexer lex(input);
    lex.impl.impl = &lex;
    lex.impl.traceStream = traceStream;
    lex.impl.tokens.tokens.reserve(size / 3);
    lex.lex();
    return lex.impl.tokens;
}}

    """.format(
        rules=rules,
        unknowns="\n".join([
            f"<{state.name}>(.|\\n) {{ impl.unknown(); }}" for state in config.states
            if (state.kind == "xstate" and state.name not in ["BODY_SRC"])
        ]),
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
