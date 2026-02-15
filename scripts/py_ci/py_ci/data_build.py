from dataclasses import dataclass, field
from pathlib import Path
import shlex
from typing import Any, Callable, List, Optional

from py_ci.util_scripting import cmake_opt


@dataclass
class CmakeOptConfig():
    name: str
    value: str | Path | bool

    def __str__(self) -> str:
        return cmake_opt(self.name, self.value)

    def get_cli(self) -> List[str]:
        return [str(self)]

    @property
    def isBuild(self) -> bool:
        return False


@dataclass
class CmakeFlagConfig():
    name: str
    value: Optional[str] = None
    isBuild: bool = False

    def __str__(self) -> str:
        assert self.name.startswith("-"), self.name
        if self.value:
            return f"{self.name} {shlex.quote(self.value)}"

        else:
            return f"{self.name}"

    def get_cli(self) -> List[str]:
        if self.value:
            return [self.name, self.value]

        else:
            return [self.name]


CmakeCLIConfig = CmakeOptConfig | CmakeFlagConfig


@dataclass
class ExternalDep():
    build_name: str
    deps_name: str
    cmake_dirs: List[tuple[str, List[str]]]
    configure_args: List[CmakeCLIConfig] = field(default_factory=list)
    is_emcc_ready: bool = field(default=False)
    is_binary: bool = field(default=False)

    def get_install_prefix(self, install_dir: Path) -> str:
        dirs: List[str] = []
        for (name, dirs) in self.cmake_dirs:
            dirs.extend(dirs)

        return ";".join([str(install_dir.joinpath(it)) for it in dirs])

    def get_configure_args(self) -> List[str]:
        return [str(it) for it in self.configure_args if not it.isBuild]

    def get_build_args(self) -> List[str]:
        return [str(it) for it in self.configure_args if it.isBuild]


def get_emscripten_cmake_flags() -> List[CmakeCLIConfig]:
    return [
        CmakeOptConfig(
            name="CMAKE_CXX_FLAGS",
            value=" ".join([
                "-fexceptions",
                # "-sUSE_BOOST_HEADERS=1",
            ]),
        ),
        # CmakeOptConfig(name="HAVE_NEON", value=False),
        # CmakeOptConfig(name="HAVE_AVX", value=False),
        # CmakeOptConfig(name="HAVE_SSE", value=False),
        CmakeOptConfig(name="CMAKE_CXX_FLAGS", value="-m32"),
        CmakeOptConfig(name="CMAKE_C_FLAGS", value="-m32"),
    ]


def get_external_deps_list(
    install_dir: Path,
    is_emcc: bool,
) -> List[ExternalDep]:
    result: List[ExternalDep] = []

    def opt(name: str, value: Any) -> CmakeOptConfig:
        return CmakeOptConfig(name=name, value=value)

    def flag(name: str,
             value: Optional[str] = None,
             isBuild: bool = False) -> CmakeFlagConfig:
        return CmakeFlagConfig(name=name, value=value, isBuild=isBuild)

    def ninja_build() -> List[CmakeFlagConfig]:
        return [
            flag("-G", "Ninja"),
            flag("-d", "explain", isBuild=True),
        ]

    def dep(
        build_name: str,
        deps_name: str,
        cmake_dirs: List[tuple[str, List[str]]],
        configure_args: List[CmakeCLIConfig] = list(),
        is_emcc_ready: bool = False,
        **kwargs: Any,
    ) -> ExternalDep:
        ext = ExternalDep(
            build_name=build_name,
            deps_name=deps_name,
            configure_args=configure_args,
            cmake_dirs=cmake_dirs,
            **kwargs,
        )

        if is_emcc:
            if is_emcc_ready:
                ext.configure_args.extend(get_emscripten_cmake_flags())
                result.append(ext)

        else:
            result.append(ext)

        return ext

    def make_lib(path: str) -> List[str]:
        return [
            path.format("lib64"),
            path.format("lib"),
        ]

    # NOTE! Order of dependencies is important here. Assuming the build is happening on the
    # system with all system-wide library packages missing, the build of the third-party
    # dependenices should happen in exact order as specified, this is especially important
    # for the google packages (gtest, protobuf, absl), as they depend on each other being
    # present.

    dep(
        build_name="benchmark",
        deps_name="benchmark",
        is_emcc_ready=False,
        cmake_dirs=[("benchmark", make_lib("benchmark/{}/cmake/benchmark"))],
        configure_args=[
            opt("BENCHMARK_ENABLE_TESTING", False),
            opt("BENCHMARK_ENABLE_GTEST_TESTS", False),
        ],
    )

    dep(
        build_name="Tracy",
        deps_name="tracy",
        is_emcc_ready=False,
        cmake_dirs=[
            ("Tracy", make_lib("Tracy/{}/cmake/Tracy")),
        ],
        configure_args=[
            opt("BUILD_SHARED_LIBS", True),
            opt("TRACY_STATIC", False),
            opt("TRACY_LTO", False),
            opt("CCACHE", "OFF"),
            # opt("CMAKE_CXX_FLAGS", "-fPIC"),
        ])

    dep(
        build_name="tracy_profiler",
        deps_name="tracy/profiler",
        is_emcc_ready=False,
        cmake_dirs=[],
        configure_args=[
            opt("LEGACY", True),
            opt("TRACY_LTO", False),
        ],
        is_binary=True,
    )

    dep(
        build_name="msgpack",
        deps_name="msgpack-c",
        is_emcc_ready=True,
        cmake_dirs=[
            ("msgpack-cxx",
             ["msgpack/lib/cmake/msgpack-cxx"] + make_lib("msgpack/{}/cmake/msgpack-cxx"))
        ],
        configure_args=[
            opt("MSGPACK_USE_BOOST", False),
            opt("MSGPACK_BUILD_TESTS", False),
        ],
    )

    dep(
        build_name="cpptrace",
        deps_name="cpptrace",
        is_emcc_ready=False,
        cmake_dirs=[
            ("cpptrace", make_lib("cpptrace/{}/cmake/cpptrace")),
            ("libdwarf", make_lib("cpptrace/{}/cmake/libdwarf")),
        ],
        configure_args=[],
    )

    dep(
        build_name="describe",
        is_emcc_ready=True,
        deps_name="cmake_wrap/describe",
        cmake_dirs=[
            ("BoostDescribe", make_lib("describe/{}/cmake/BoostDescribe")),
        ],
    )

    dep(build_name="cctz",
        is_emcc_ready=True,
        deps_name="cctz",
        configure_args=[
            opt("CMAKE_POSITION_INDEPENDENT_CODE", "TRUE"),
            opt("BUILD_TESTING", False),
            opt("BUILD_TOOLS", False),
            opt("BUILD_EXAMPLES", False),
            opt("BUILD_BENCHMARK", False),
        ],
        cmake_dirs=[
            ("cctz", make_lib("cctz/{}/cmake/cctz")),
        ])

    dep(
        build_name="preprocessor",
        is_emcc_ready=True,
        deps_name="cmake_wrap/boost_preprocessor",
        cmake_dirs=[
            ("BoostPreprocessor", make_lib("preprocessor/{}/cmake/BoostPreprocessor")),
        ],
    )

    dep(
        build_name="adaptagrams",
        deps_name="cmake_wrap/adaptagrams",
        configure_args=[
            opt("CMAKE_POSITION_INDEPENDENT_CODE", "TRUE"),
        ],
        cmake_dirs=[
            ("Adaptagrams", make_lib("adaptagrams/{}/cmake/Adaptagrams")),
        ],
    )
    dep(
        build_name="perfetto",
        deps_name="cmake_wrap/perfetto",
        is_emcc_ready=True,
        configure_args=[
            opt("CMAKE_POSITION_INDEPENDENT_CODE", "TRUE"),
        ],
        cmake_dirs=[
            ("Perfetto", make_lib("perfetto/{}/cmake/Perfetto")),
        ],
    )

    dep(
        build_name="immer",
        deps_name="immer",
        is_emcc_ready=True,
        cmake_dirs=[
            ("Immer", make_lib("immer/{}/cmake/Immer")),
        ],
        configure_args=[
            opt("immer_BUILD_TESTS", False),
            opt("immer_BUILD_EXAMPLES", False),
            opt("immer_BUILD_DOCS", False),
            opt("immer_BUILD_EXTRAS", False),
        ],
    )

    dep(
        build_name="lager",
        deps_name="lager",
        is_emcc_ready=True,
        cmake_dirs=[
            ("Lager", make_lib("lager/{}/cmake/Lager")),
        ],
        configure_args=[
            opt("lager_BUILD_EXAMPLES", False),
            opt("lager_BUILD_TESTS", False),
            opt("lager_BUILD_FAILURE_TESTS", False),
            opt("lager_BUILD_DEBUGGER_EXAMPLES", False),
            opt("lager_BUILD_DOCS", False),
        ],
    )

    absl = dep(
        build_name="abseil",
        deps_name="abseil-cpp",
        is_emcc_ready=True,
        configure_args=[
            opt("ABSL_CC_LIB_COPTS", "-fPIC"),
            opt("CMAKE_POSITION_INDEPENDENT_CODE", "TRUE"),
            *ninja_build(),
        ],
        cmake_dirs=[
            ("absl", make_lib("abseil/{}/cmake/absl")),
        ],
    )

    dep(
        build_name="SQLiteCpp",
        deps_name="SQLiteCpp",
        configure_args=[opt("SQLITECPP_RUN_CPPLINT", False)],
        cmake_dirs=[
            ("SQLiteCpp", make_lib("SQLiteCpp/{}/cmake/SQLiteCpp")),
        ],
    )

    dep(
        build_name="libgit2",
        deps_name="libgit2",
        cmake_dirs=[],
        configure_args=[
            opt("BUILD_TESTS", False),
        ],
    )

    dep(
        build_name="mp11",
        deps_name="mp11",
        cmake_dirs=[
            ("boost_mp11", make_lib("mp11/{}/cmake/boost_mp11-1.85.0")),
        ],
        is_emcc_ready=True,
    )

    dep(
        build_name="json",
        deps_name="json",
        is_emcc_ready=True,
        cmake_dirs=[
            ("nlohmann_json", ["json/share/cmake/nlohmann_json"]),
        ],
        configure_args=[
            opt("JSON_BuildTests", False),
        ],
    )

    dep(
        build_name="yaml",
        deps_name="yaml-cpp",
        is_emcc_ready=True,
        cmake_dirs=[
            ("yaml-cpp",
             make_lib("yaml/{}/cmake/yaml-cpp") + ["yaml/share/cmake/yaml-cpp"]),
        ],
        configure_args=[
            opt("YAML_CPP_BUILD_TESTS", False),
            opt("CMAKE_POSITION_INDEPENDENT_CODE", "TRUE"),
        ],
    )

    dep(
        build_name="range-v3",
        deps_name="range-v3",
        is_emcc_ready=True,
        cmake_dirs=[
            ("range-v3", make_lib("range-v3/{}/cmake/range-v3")),
        ],
        configure_args=[
            opt("RANGE_V3_TESTS", False),
            opt("RANGE_V3_EXAMPLES", False),
            opt("RANGE_V3_PERF", False),
        ],
    )

    dep(
        build_name="pybind11",
        deps_name="pybind11",
        cmake_dirs=[
            ("pybind11", ["pybind11/share/cmake/pybind11"]),
        ],
        configure_args=[opt("PYBIND11_TEST", False)],
    )

    utf8 = dep(
        build_name="utf8_range",
        deps_name="protobuf/third_party/utf8_range",
        configure_args=[
            opt("CMAKE_PREFIX_PATH", absl.get_install_prefix(install_dir=install_dir)),
            opt("utf8_range_ENABLE_TESTS", False),
            opt("protobuf_VERSION", "6.31.1"),
            *ninja_build(),
        ],
        cmake_dirs=[
            ("utf8_range", make_lib("utf8_range/{}/cmake/utf8_range")),
        ],
    )

    dep(
        build_name="protobuf",
        deps_name="protobuf",
        cmake_dirs=[
            ("protobuf", make_lib("protobuf/{}/cmake/protobuf")),
        ],
        configure_args=[
            opt("protobuf_BUILD_TESTS", False),
            opt("protobuf_BUILD_SHARED_LIBS", False),
            opt("utf8_range_ENABLE_TESTS", False),
            opt("utf8_range_ENABLE_INSTALL", True),
            opt("protobuf_ABSL_PROVIDER", "package"),
            opt(
                "CMAKE_PREFIX_PATH", ";".join([
                    absl.get_install_prefix(install_dir=install_dir),
                    utf8.get_install_prefix(install_dir=install_dir),
                ])),
            opt("ABSL_CC_LIB_COPTS", "-fPIC"),
            opt("CMAKE_POSITION_INDEPENDENT_CODE", "TRUE"),
            *ninja_build(),
        ],
    )

    dep(
        build_name="googletest",
        deps_name="googletest",
        cmake_dirs=[
            ("GTest", make_lib("googletest/{}/cmake/GTest")),
        ],
    )

    dep(
        build_name="lexy",
        deps_name="lexy",
        is_emcc_ready=True,
        cmake_dirs=[
            ("lexy", make_lib("lexy/{}/cmake/lexy")),
        ],
        configure_args=[
            opt("LEXY_BUILD_EXAMPLES", False),
            opt("LEXY_BUILD_TESTS", False),
        ],
    )

    return result


def get_deps_install_config(
    deps: List[ExternalDep],
    install_dir: Path,
    exists_check: Callable,
) -> str:
    cmake_paths = []
    for item in deps:
        if item.is_binary:
            continue

        for dir in item.cmake_dirs:
            path = None
            tried_paths = []
            for possible_install in dir[1]:
                possible_path = install_dir.joinpath(possible_install)
                tried_paths.append(possible_path)
                if exists_check(possible_path):
                    assert possible_path != Path(
                        "/"
                    ), f"install_dir = {install_dir}, possible_install = {possible_install}"
                    path = possible_path
                    break

            if not path:
                raise ValueError(
                    f"{dir[0]} is not insalled: could not find cmake installation dir in {install_dir}, tried {tried_paths} relative paths"
                )

            cmake_paths.append(f"set({dir[0]}_DIR \"{path}\")")

    return "\n".join(cmake_paths)


def get_published_build_opts() -> List[CmakeOptConfig]:
    return [
        CmakeOptConfig("ORG_BUILD_WITH_PROTOBUF", False),
        CmakeOptConfig("ORG_BUILD_TESTS", True),
        CmakeOptConfig("CMAKE_BUILD_TYPE", "Debug"),
        CmakeOptConfig("ORG_BUILD_INTERNAL_TOOLS", False),
        CmakeOptConfig("ORG_BUILD_ASSUME_CLANG", True),
        CmakeOptConfig("CMAKE_CXX_COMPILER", "clang++"),
        CmakeOptConfig("CMAKE_C_COMPILER", "clang "),
        CmakeOptConfig("ORG_USE_SANITIZER", False),
        CmakeOptConfig("ORG_BUILD_WITH_ADAPTAGRAMS", False),
        CmakeOptConfig("ORG_DEPS_USE_PACKAGED_BOOST", False),
    ]
