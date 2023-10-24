#!/usr/bin/env python

import yaml
from yaml.loader import SafeLoader
from pydantic import BaseModel, validator
from typing import List, Optional, Union
import os

class Action(BaseModel):
    do: str
    to: Optional[str]
    from_: Optional[str] = None

    # Convert "from" from the YAML to "from_" in our model
    @validator("from_", pre=True, always=True)
    def from_field(cls, v, values):
        return values.get('from')

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

# Convert rule data to re/flex code pattern
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
    return f"{state_prefix} {{ /*{rule.line:<4}*/ add(BaseTokenKind::{rule.token}); {actions_code} }}"

def generate_reflex_code(config: Configuration) -> str:
    return "\n".join([rule_to_reflex_code(rule) for rule in config.rules])

# Example usage:
config = parse_yaml_to_pydantic(os.path.join(os.path.dirname(os.path.abspath(__file__)), "base_lexer.yaml"))
for rule in config.rules:
    print(rule_to_reflex_code(rule))
