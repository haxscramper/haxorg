import functools
import json
import os
import traceback
from pathlib import Path

import rich_click as click
import toml
import yaml
from beartype import beartype
from beartype.typing import (Any, Dict, List, Optional, Type, TypeVar, get_args,
                             get_origin)
from py_scriptutils.files import get_haxorg_repo_root_path
from py_scriptutils.script_logging import log
from pydantic import BaseModel
from pydantic_core import PydanticUndefined

CAT = __name__


class DefaultWrapper(click.ParamType):
    name = "DefaultWrapper"

    def __init__(self, base_type: Any) -> None:
        self.base_type = base_type

    def convert(self, value: Any, param: Any, ctx: Any) -> Any:
        if isinstance(value, DefaultWrapperValue):
            return value

        else:
            return DefaultWrapperValue(value=self.base_type.convert(value, param, ctx),
                                       is_provided=True)


class DefaultWrapperValue:
    # Your custom type logic here
    def __init__(self, value: Any, is_provided: bool = True) -> None:
        self.value = value
        self.is_provided = is_provided

    def __repr__(self) -> str:
        return f"DefaultWrapperValue({self.value}, {self.is_provided})"


def merge_cli_model(
    ctx: click.Context,
    file_config: Dict,
    on_cli_args: Dict,
    ModelT: type,
) -> Any:
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
    return ModelT.model_validate(final_data)  # type: ignore[attr-defined]


T = TypeVar("T")


@beartype
def get_cli_model(ctx: click.Context, ModelType: Type[T], kwargs: dict) -> T:
    """
    Convert the provided CLI parameters into the object of type `T` for
    more typesafe usage
    """
    initial_cli = ModelType.model_validate(kwargs)  # type: ignore
    if hasattr(initial_cli, "config"):
        config = initial_cli.config
        config_base = run_config_provider(
            ([str(Path(config).resolve())] if config else []), True)

    conf = merge_cli_model(ctx, config_base, kwargs, ModelType)
    return conf


def py_type_to_click(T: Any) -> Any:
    if T is str:
        return click.STRING

    elif T is Path:
        return click.Path

    elif get_origin(T) is list:
        return py_type_to_click(get_args(T)[0])

    else:
        return click.STRING


def options_from_model(model: BaseModel) -> List[Any]:
    result: List[Any] = []
    for name, field in model.model_fields.items():
        has_default = field.default is not None and field.default != PydanticUndefined
        is_multiple = get_origin(field.annotation) is list
        opt_name = field.alias if field.alias else name
        result.append(
            click.option(
                "--" + opt_name,
                type=DefaultWrapper(py_type_to_click(field.annotation)),
                help=field.description,
                expose_value=True,
                **({  # type: ignore
                    "default": [DefaultWrapperValue(it, False) for it in field.default] if
                               is_multiple else DefaultWrapperValue(field.default, False)
                } if has_default else {}),
                multiple=is_multiple,
            ))

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


def apply_options(f: Any, options: Any) -> Any:
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
def find_config_files(with_trace: bool, potential_paths: List[str]) -> List[str]:
    """Search for the config file in a list of default locations."""
    # Check each path, return the first that exists.
    result: List[str] = []
    for path in potential_paths:
        if os.path.exists(path):
            if with_trace:
                # TODO replace 'with trace' by a nested logger name
                log("org.cli").debug(f"Trying {path} for config -- file exists, using it")
            result.append(path)

        elif with_trace:
            log("org.cli").debug(
                f"Trying {path} for config -- file does not exist, skipping")

    return result


class SafeDict(dict):

    def __missing__(self, key: str) -> str:
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
                return d.format_map(substitution)

            case list():
                return [rec_rewrite(it) for it in d]

            case dict():
                return {k: rec_rewrite(v) for k, v in d.items()}

            case _:
                return d

    return rec_rewrite(base)


@beartype
def run_config_provider(
    search_paths: List[str],
    with_trace: bool,
    content_value_substitution: Dict[str, str] = {},
) -> dict:
    """
    Search for the existing paths in the `search_paths`, pase the toml files and
    return merged dictionary.
    """
    try:
        file_paths = find_config_files(
            with_trace=with_trace,
            potential_paths=search_paths,
        )

        if (not file_paths):
            return {}

        configs: List[Dict] = []
        for path in file_paths:
            if not Path(path).exists():
                continue

            if path.endswith("toml"):
                config_dict = toml.load(path)

            elif path.endswith("json"):
                config_dict = json.loads(Path(path).read_text())

            elif path.endswith("yaml"):
                with open(path, "r") as file:
                    config_dict = yaml.load(file, Loader=yaml.SafeLoader)

            else:
                raise ValueError(
                    f"Unexpected config file format: expected `.toml`, `.json` or `.yaml`, got {path}"
                )

            config_value = interpolate_dictionary(
                config_dict,
                merge_dicts([
                    content_value_substitution,
                    dict(config_path=path,
                         config_dir=os.path.dirname(path),
                         haxorg_root=str(get_haxorg_repo_root_path()))
                ]))

            configs.append(config_value)

        return merge_dicts(configs)

    except Exception as e:
        traceback.print_exc()
        raise e


@beartype
def make_config_provider(config_file_name: str, with_trace: bool = False) -> Any:

    def implementation(file_path: str, cmd_name: str) -> Dict:
        D = run_config_provider([file_path], with_trace=with_trace)
        return D

    return implementation


def pack_context(ctx: click.Context, TDef: type[T], cli_kwargs: dict) -> T:
    ctx.ensure_object(dict)
    return get_cli_model(ctx, TDef, cli_kwargs)


@beartype
def get_context(ctx: click.Context, T: type, cli_kwargs: dict) -> Any:
    pack_context(ctx, T, cli_kwargs=cli_kwargs)
    return ctx.obj["tmp"]


@beartype
def get_user_provided_params(ctx: click.Context) -> Dict[str, Any]:
    """
    Get parameters that were explicitly provided by the user.
    """
    contexts = []
    current_ctx = ctx
    while current_ctx is not None:
        contexts.append(current_ctx)
        current_ctx = current_ctx.parent  # type: ignore

    contexts.reverse()

    def get_fields(context: click.Context) -> Dict[str, Any]:
        result: Dict[str, Any] = {}
        for param_name, value in context.params.items():
            if isinstance(value, DefaultWrapperValue) and value.is_provided:
                result[param_name] = value.value

        return result

    def aux(idx: int, parent: Dict):
        if idx < len(contexts):
            c = contexts[idx]
            parent[c.info_name] = get_fields(c)
            aux(idx + 1, parent[c.info_name])

    result: Dict[str, Any] = get_fields(contexts[0])
    if 1 < len(contexts):
        result[contexts[1].info_name] = dict()
        aux(1, result)

    return result
