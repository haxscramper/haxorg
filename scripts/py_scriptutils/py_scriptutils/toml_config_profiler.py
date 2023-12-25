from beartype import beartype
import os
from beartype.typing import List, Dict, Any, get_origin, get_args
import toml
import traceback
from dataclasses import dataclass
import rich_click as click
import functools
from pydantic import BaseModel
from pydantic_core import PydanticUndefined
from pprint import pprint
from copy import deepcopy
from pathlib import Path

from py_scriptutils.script_logging import log


class DefaultWrapper(click.ParamType):
    name = "DefaultWrapper"

    def __init__(self, base_type):
        self.base_type = base_type

    def convert(self, value, param, ctx):
        if isinstance(value, DefaultWrapperValue):
            return value

        else:
            return DefaultWrapperValue(value=self.base_type.convert(value, param, ctx),
                                       is_provided=True)


class DefaultWrapperValue:
    # Your custom type logic here
    def __init__(self, value, is_provided: bool = True):
        self.value = value
        self.is_provided = is_provided

    def __repr__(self):
        return f"DefaultWrapperValue({self.value}, {self.is_provided})"


def merge_cli_model(ctx: click.Context, file_config: Dict, on_cli_args: Dict,
                    ModelT: type) -> Any:
    on_cli = {}
    on_default = {}
    ctx.ensure_object(dict)
    for param, value in ctx.params.items():
        if isinstance(value, DefaultWrapperValue):
            if value.is_provided:
                on_cli[param] = value.value

            else:
                on_default[param] = value.value

        elif isinstance(value, list) or isinstance(value, tuple) and 0 < len(value) and (
                isinstance(value[0], DefaultWrapperValue)):
            if value[0].is_provided:
                on_cli[param] = [it.value for it in value]

            else:
                on_default[param] = [it.value for it in value]

    for d in [on_default, file_config, on_cli]:
        for k, v in d.items():
            assert not isinstance(v, DefaultWrapper)

    final_data = merge_dicts([on_default, file_config, on_cli])
    # trunk-ignore(mypy/attr-defined)
    return ModelT.model_validate(final_data)


def py_type_to_click(T):
    if T is str:
        return click.STRING

    elif get_origin(T) is list:
        return py_type_to_click(get_args(T)[0])

    else:
        return click.STRING


def options_from_model(model: BaseModel) -> List[click.option]:
    result: List[click.option] = []
    for name, field in model.model_fields.items():
        has_default = field.default is not None and field.default != PydanticUndefined
        is_multiple = get_origin(field.annotation) is list
        result.append(
            click.option(
                "--" + (field.alias if field.alias else name),
                type=DefaultWrapper(py_type_to_click(field.annotation)),
                help=field.description,
                expose_value=True,
                **({
                    "default": [DefaultWrapperValue(it, False) for it in field.default] if
                               is_multiple else DefaultWrapperValue(field.default, False)
                } if has_default else {}),
                multiple=is_multiple))

    return result


@beartype
def merge_dicts(dicts: List[Dict]) -> Dict:

    def recursive_merge(base: Dict, new: Dict) -> None:
        for key, value in new.items():
            if (isinstance(value, dict) and key in base and isinstance(base[key], dict)):
                recursive_merge(base[key], value)
            else:
                base[key] = value

    result: Dict = {}
    for d in dicts:
        recursive_merge(result, d)

    return result


def apply_options(f, options):
    return functools.reduce(lambda x, opt: opt(x), options, f)


@beartype
def get_parent_directories(path: str) -> List[str]:
    path = os.path.abspath(path)  # Ensure path is absolute
    directories = []

    while True:
        directories.append(path)
        new_path = os.path.dirname(path)

        # Check if we've reached the root directory
        if new_path == path:
            break

        path = new_path

    return directories


@beartype
def find_default_search_locations(config_file_name: str) -> List[str]:
    # Start with the current directory.
    potential_paths = [os.path.join(os.getcwd(), config_file_name)]

    # Add $XDG_CONFIG_HOME/haxorg/config.toml
    xdg_config_home = os.environ.get("XDG_CONFIG_HOME",
                                     os.path.join(os.path.expanduser("~"), ".config"))
    potential_paths.append(os.path.join(xdg_config_home, "haxorg", config_file_name))
    return potential_paths


@beartype
def find_config_files(withTrace: bool, potential_paths: List[str]) -> List[str]:
    """Search for the config file in a list of default locations."""
    # Check each path, return the first that exists.
    result: List[str] = []
    for path in potential_paths:
        if os.path.exists(path):
            if withTrace:
                log.debug(f"Trying {path} for config -- file exists, using it")
            result.append(path)

        elif withTrace:
            log.debug(f"Trying {path} for config -- file does not exist, skipping")

    return result


class SafeDict(dict):

    def __missing__(self, key):
        return '{' + key + '}'


@beartype
def interpolate_dictionary(base: Dict, substitution: Dict[str, str]) -> Dict:
    """
    Recursively replace string values from dictionary 'base' with strings interpolated using
    substitution values. 

    {"base": "ZZ{replace}XX"} + {"replace": "---"} --> {"base": "ZZ---XX"}

    This is used to interpolate configuration values in the toml files. 
    """

    def rec_rewrite(d: Any) -> Any:
        match d:
            case int():
                return d

            case float():
                return d

            case str():
                return d.format_map(SafeDict(**substitution))

            case list():
                return [rec_rewrite(it) for it in d]

            case dict():
                return {k: rec_rewrite(v) for k, v in d.items()}

            case _:
                return d

    return rec_rewrite(base)


def get_haxorg_repo_root_path() -> Path:
    result = Path(__file__).parent.parent.parent.parent
    assert result.exists(), result
    assert result.is_dir(), result
    assert result.joinpath("tasks.py").exists(), result
    return result


@beartype
def run_config_provider(search_paths: List[str],
                        withTrace: bool,
                        content_value_substitution: Dict[str, str] = {}) -> dict:
    try:
        file_paths = find_config_files(withTrace=withTrace, potential_paths=search_paths)

        if (not file_paths):
            return {}

        configs: List[Dict] = []
        for path in file_paths:
            if os.path.exists(path):
                configs.append(
                    interpolate_dictionary(
                        toml.load(path), content_value_substitution +
                        dict(config_path=path,
                             config_dir=os.path.dirname(path),
                             haxorg_root=get_haxorg_repo_root_path())))

        return merge_dicts(configs)

    except Exception as e:
        traceback.print_exc()
        raise e


@beartype
def make_config_provider(config_file_name: str):

    def implementation(file_path: str, cmd_name: str):
        D = run_config_provider(file_path, cmd_name, False, config_file_name)
        return D

    return implementation
