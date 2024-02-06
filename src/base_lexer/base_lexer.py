#!/usr/bin/env python

import yaml
from yaml.loader import SafeLoader
from pydantic import BaseModel, Field
from beartype.typing import List, Optional, Literal, Dict
from beartype import beartype
from collections import OrderedDict
import os
from copy import copy


class Action(BaseModel):
    # When token is matched, what to do
    do: Literal["push", "pop", "set", "raw", "token"]
    to: Optional[str] = None
    from_: Optional[str] = Field(alias="from", default=None)
    raw: Optional[str] = None


class Rule(BaseModel):
    re: Optional[str] = None
    lit: Optional[str] = None
    token: Optional[str] = None
    sub: Optional[str] = None
    states: Optional[List[str]] = None
    actions: Optional[List[Action]] = None
    line: Optional[int] = None
    keepLead: bool = False


class State(BaseModel):
    name: str
    kind: Literal["xstate", "state"]
    line: Optional[int] = None


class RxMacro(BaseModel):
    # Substitute `{name}` in the regex pattern with a common string replacement
    name: str
    value: str
    line: Optional[int] = None


class TokenDesc(BaseModel):
    name: str


def sub_state_name(name: str) -> str:
    return f"sub_state_{name}"


def sub_run_name(name: str) -> str:
    return f"lex_sub_{name}"


class Configuration(BaseModel):
    states: List[State]  # List of states that lexer can transition between
    rules: List[Rule]  # Regex/literal matching rules
    # Explicitly specified list of tokens to be added to whatever was detected in the 'rules'
    tokens: List[TokenDesc] = Field(default_factory=list)
    # Regular expression macros to save on re-typing the same thing
    rx_macros: List[RxMacro] = Field(default_factory=list)
    sub_lexers: OrderedDict[str, List[Rule]] = Field(default_factory=dict)

    def get_states(self) -> List[State]:
        result = copy(self.states)

        for name in self.sub_lexers.keys():
            result.append(State(name=sub_state_name(name), kind="xstate"))

        return result

    @beartype
    def get_all_rules(self) -> List[Rule]:
        result: List[Rule] = []
        for name, sub_rules in self.sub_lexers.items():
            for rule in sub_rules:
                result.append(rule.model_copy(update=dict(states=[sub_state_name(name)])))

            if not any(rule.re == "<<EOF>>" for rule in sub_rules):
                result.append(
                    Rule(
                        re="<<EOF>>",
                        states=[sub_state_name(name)],
                        actions=[
                            Action(do="raw", raw="return 0;"),
                        ],
                        keepLead=True,
                    ))

        result += [r for r in self.rules]

        return result


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

    if "sub_lexers" in data:
        del data["sub_lexers"]["__line__"]
        for _, rules in data["sub_lexers"].items():
            for rule in rules:
                rule["line"] = rule.pop("__line__", None)

    return Configuration(**data)


MATCH_WIDTH = 40
ENUM_NAME = "OrgTokenKind"


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

    if not rule.keepLead:
        actions.append(f"maybe_pop_expect(LEAD, INITIAL, {rule.line or -1});")

    if rule.actions:
        for action in rule.actions:
            match action.do:
                case "push":
                    actions.append(
                        f"push_expect({action.from_ or '-1'}, {action.to}, {rule.line});")

                case "pop":
                    actions.append(
                        f"pop_expect({action.from_ or '-1'}, {action.to}, {rule.line});")

                case "set":
                    actions.append(f"start({action.to});")

                case "raw":
                    actions.append(action.raw)

                case "token":
                    actions.append(f"impl.add({ENUM_NAME}::{action.to});")

                case _:
                    raise ValueError(f"Unexpected action 'do' value: {action.do}")

    if rule.token:
        actions.insert(0, f"impl.add({ENUM_NAME}::{rule.token});")

    elif rule.sub:
        actions = [f"{sub_run_name(rule.sub)}(str());"] + actions

    actions_code = " ".join(actions)

    before_param = f"{ENUM_NAME}::{rule.token}" if rule.token else "std::nullopt"
    content = " ".join([
        f"impl.before({rule.line or -1}, {before_param}, R\"raw({rule.re or rule.lit})raw\");",
        actions_code,
        f"impl.after({rule.line or -1});",
    ])
    return f"{state_prefix} {{ /*{rule.line or 1:<4}*/ {content} }}"


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
                       [rule.token for rule in config.get_all_rules() if rule.token]))))


@beartype
def generate_state(config: Configuration) -> str:
    tokens = sorted(
        set([rule.token for rule in config.get_all_rules() if rule.token] +
            [tok.name for tok in config.tokens]))
    return """
std::string OrgLexerImpl::state_name(int state) {{
    switch(state) {{
        case 0: return "INITIAL";
{mappings}
        default: return std::to_string(state);
    }}
}}

std::string enum_serde<OrgTokenKind>::to_string(const OrgTokenKind &value) {{
    switch(value) {{
{values}
    }}
}}

Opt<OrgTokenKind> enum_serde<OrgTokenKind>::from_string(std::string const& value) {{
{from_string}
}}

""".format(
        mappings="\n".join([
            f"        case {idx + 1}: return \"{state.name}\";"
            for idx, state in enumerate(config.get_states())
        ]),
        values="\n".join([
            f"        case OrgTokenKind::{name}: return \"{name}\";" for name in tokens
        ]),
        from_string="\n".join([
            f"  if (value == \"{name}\") {{ return OrgTokenKind::{name}; }} else"
            for name in tokens
        ] + ["  { return std::nullopt; }"]),
    )


@beartype
def generate_reflex_code(config: Configuration) -> str:
    macros = {m.name: m.value for m in config.rx_macros}

    rules = "\n".join(
        [rule_to_reflex_code(rule, macros) for rule in config.get_all_rules()])
    errtok = ENUM_NAME + "::Unknown"

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

#define pop_expect(current, next, line) impl.pop_expect_impl(current, next, line)
#define maybe_pop_expect(current, next, line) impl.maybe_pop_expect_impl(current, next, line)
#define push_expect(current, next, line) impl.push_expect_impl(current, next, line)
%}}

%option fast freespace unicode

{states}

%class{{
  public:
    OrgLexerImpl impl;

  {sub_lexer_declarations}
}}

%%

{rules}  

(.|\\n) {{ impl.before(__LINE__, {errtok}, ".|\\n"); impl.unknown(); impl.after(__LINE__); }}
{unknowns}

%%

{sub_lexer_definitions}

TokenGroup<OrgTokenKind, OrgFill> tokenize(const char* input, int size, LexerParams const& p) {{
    base_lexer::Lexer lex(input);
    OrgTokenGroup result;
    lex.impl.tokens = &result;
    lex.impl.impl = &lex;
    lex.impl.p = p;
    lex.impl.tokens->tokens.reserve(size / 3);
    lex.lex();
    return result;
}}

    """.format(
        rules=rules,
        unknowns="\n".join([
            f"<{state.name}>(.|\\n) {{ impl.before(__LINE__, {errtok}, \".|\\n\"); impl.unknown(); impl.after(__LINE__); }}"
            for state in config.get_states()
            if (state.kind == "xstate" and state.name not in ["BODY_SRC"])
        ]),
        errtok=errtok,
        states="\n".join(
            [f"%{state.kind} {state.name}".format() for state in config.get_states()]),
        sub_lexer_declarations="\n".join([
            f"void {sub_run_name(name)}(std::string const& values);"
            for name in config.sub_lexers.keys()
        ]),
        sub_lexer_definitions="\n".join([
            f"""
void base_lexer::Lexer::{sub_run_name(name)}(std::string const& values) {{
    base_lexer::Lexer lex(values.c_str());
    lex.start({sub_state_name(name)});
    lex.impl.tokens = this->impl.tokens;
    lex.impl.impl = &lex;
    lex.impl.p = this->impl.p;
    lex.impl.p.sub_locations.push_back({{static_cast<int>(impl.impl->lineno()), static_cast<int>(impl.impl->columno())}});
    ++lex.impl.p.indentation;
    lex.lex();
}}                              
                               """ for name in config.sub_lexers.keys()
        ]),
    )


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
