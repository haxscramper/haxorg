import yaml
from pydantic import BaseModel, Field
from beartype.typing import List, Optional
from invoke.context import Context
from py_ci.util_scripting import parse_haxorg_env
from py_scriptutils.script_logging import log, to_debug_json
from py_scriptutils.toml_config_profiler import merge_dicts
import json

CAT = __name__ 

class HaxorgInstrumentConfig(BaseModel, extra="forbid"):
    coverage: bool = Field(default=False)
    xray: bool = Field(default=False)
    asan: bool = Field(default=False)
    perfetto: bool = Field(default=False)

class HaxorgUseConfig(BaseModel, extra="forbid"): 
    qt: bool = Field(default=False)


class HaxorgTasksConfig(BaseModel, extra="forbid"):
    skip_python_refl: bool = Field(default=False)

    # invoke config fields
    search_root: Optional[str] = None
    dedupe: bool = True
    collection_name: Optional[str] = None
    ignore_unknown_help: bool = False
    executor_class: Optional[str] = None
    auto_dash_names: bool = True


class HaxorgCoverageCookiePattern(BaseModel, extra="forbid"):
    binary_pattern: Optional[str] = None
    class_pattern: Optional[str] = None
    name_pattern: Optional[str] = None


class HaxorgCoverageAggregateFilter(BaseModel, extra="forbid"):
    whitelist_patterns: List[HaxorgCoverageCookiePattern] = []
    blacklist_patterns: List[HaxorgCoverageCookiePattern] = []


class HaxorgEmscriptenConfig(BaseModel, extra="forbid"):
    build: bool = False
    toolchain: str = "/usr/lib/emscripten/cmake/Modules/Platform/Emscripten.cmake"


class HaxorgConfig(BaseModel, extra="forbid"):
    quiet: bool = Field(default=False)
    debug: bool = Field(default=False)
    use: HaxorgUseConfig = Field(default_factory=lambda: HaxorgUseConfig())
    emscripten: HaxorgEmscriptenConfig = Field(
        default_factory=lambda: HaxorgEmscriptenConfig())
    instrument: HaxorgInstrumentConfig = Field(
        default_factory=lambda: HaxorgInstrumentConfig())
    tasks: HaxorgTasksConfig = Field(default_factory=lambda: HaxorgTasksConfig())
    force_task: List[str] = Field(
        default_factory=list,
        description="Always execute task",
    )

    forceall: bool = Field(default=False)
    ci: bool = Field(default=False)
    dryrun: bool = Field(default=False)

    python_version: Optional[str] = None
    aggregate_filters: Optional[HaxorgCoverageAggregateFilter] = None
    profdata_file_whitelist: List[str] = Field(default_factory=lambda: [".*"])
    profdata_file_blacklist: List[str] = Field(
        default_factory=lambda: ["base_lexer_gen.cpp", "thirdparty"])

    # field for unparsing invoke config
    sudo: dict = Field(default_factory=dict)
    runners: dict = Field(default_factory=dict)
    timeouts: dict = Field(default_factory=dict)
    run: dict = Field(default_factory=dict)



CONFIG_CACHE: Optional[HaxorgConfig] = None


def get_config(ctx: Context) -> HaxorgConfig:
    global CONFIG_CACHE
    if CONFIG_CACHE:
        return CONFIG_CACHE

    else:
        res_dict = dict()

        def aux(it):
            match it:
                case bool() | None | str() | type():
                    return it

                case list():
                    return [aux(i) for i in it]

                case _:
                    out = dict()
                    for key in it:
                        out[key] = aux(it[key])

                    return out

        ctx_dict = aux(ctx.config)

        env_dict = parse_haxorg_env()
        log(CAT).info(f"Parsed haxorg env variables")
        print(json.dumps(to_debug_json(env_dict), indent=2))
        res_dict = merge_dicts([ctx_dict, env_dict])
        log(CAT).info(f"Final parsed dictionary")
        print(json.dumps(to_debug_json(res_dict), indent=2))

        CONFIG_CACHE = HaxorgConfig(**res_dict)

        return CONFIG_CACHE
