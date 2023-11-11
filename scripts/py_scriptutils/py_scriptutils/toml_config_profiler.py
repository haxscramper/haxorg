from beartype import beartype
import os
from beartype.typing import List, Dict, Any, get_origin, get_args
# trunk-ignore(mypy/import)
import toml
import traceback
import rich_click as click
import functools
from pydantic import BaseModel

from py_scriptutils.script_logging import log

def merge_cli_model(ctx: click.Context, base: Dict, ModelT: type) -> Any:
    store = {}
    for param, value in ctx.params.items():
        store[param] = value

    final_data = merge_dicts([base, store])

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
        result.append(
            click.option("--" + (field.alias if field.alias else name),
                         type=py_type_to_click(field.annotation),
                         help=field.description,
                         multiple=get_origin(field.annotation) is list))

    return result

@beartype
def merge_dicts(dicts: List[Dict]) -> Dict:
    def recursive_merge(base: Dict, new: Dict) -> None:
        for key, value in new.items():
            if (isinstance(value, dict) and key in base 
                and isinstance(base[key], dict)):
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


@beartype
def run_config_provider(search_paths: List[str], withTrace: bool) -> dict:
    try:
        file_paths = find_config_files(withTrace=withTrace, potential_paths=search_paths)

        if (not file_paths):
            return {}

        configs = [toml.load(path) for path in file_paths if os.path.exists(path)]
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
