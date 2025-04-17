from dataclasses import dataclass, field
from typing import List
from pathlib import Path
from py_ci.util_scripting import cmake_opt


@dataclass
class CmakeOptConfig():
    name: str
    value: str | Path | bool

    def __str__(self) -> str:
        return cmake_opt(self.name, self.value)


@dataclass
class ExternalDep():
    build_name: str
    deps_name: str
    cmake_dirs: List[tuple[str, str]]
    configure_args: List[CmakeOptConfig] = field(default_factory=list)
    install_prefixes: List[str] = field(default_factory=list)
    is_emcc_ready: bool = field(default=False)

    def get_install_prefix(self, install_dir: Path) -> str:
        return ";".join([str(install_dir.joinpath(it)) for it in self.install_prefixes])

    def get_configure_args(self) -> List[str]:
        return [str(it) for it in self.configure_args]


def get_emscripten_cmake_flags() -> List[CmakeOptConfig]:
    return [
        CmakeOptConfig(
            name="CMAKE_CXX_FLAGS",
            value=" ".join([
                "-fexceptions",
                # "-sUSE_BOOST_HEADERS=1",
            ]),
        ),
        CmakeOptConfig(name="HAVE_NEON", value=False),
        CmakeOptConfig(name="HAVE_AVX", value=False),
        CmakeOptConfig(name="HAVE_SSE", value=False),
        CmakeOptConfig(name="CMAKE_CXX_FLAGS", value="-m32"),
        CmakeOptConfig(name="CMAKE_C_FLAGS", value="-m32"),
    ]


def get_external_deps_list(install_dir: Path, is_emcc: bool) -> List[ExternalDep]:
    result: List[ExternalDep] = []

    def opt(name: str, value: any) -> CmakeOptConfig:
        return CmakeOptConfig(name=name, value=value)

    def dep(
            build_name: str,
            deps_name: str,
            cmake_dirs: List[tuple[str, str]],
            configure_args: List[str] = list(),
            install_prefixes: List[str] = list(),
            is_emcc_ready: bool = False,
    ):
        ext = ExternalDep(
            build_name=build_name,
            deps_name=deps_name,
            configure_args=configure_args,
            install_prefixes=install_prefixes,
            cmake_dirs=cmake_dirs,
        )

        if is_emcc:
            if is_emcc_ready:
                ext.configure_args.extend(get_emscripten_cmake_flags())
                result.append(ext)

        else:
            result.append(ext)

        return ext

    # NOTE! Order of dependencies is important here. Assuming the build is happening on the
    # system with all system-wide library packages missing, the build of the third-party
    # dependenices should happen in exact order as specified, this is especially important
    # for the google packages (gtest, protobuf, absl), as they depend on each other being
    # present.
    dep(
        build_name="cpptrace",
        deps_name="cpptrace",
        is_emcc_ready=False,
        cmake_dirs=[
            ("cpptrace", "cpptrace/lib/cmake/cpptrace"),
            ("libdwarf", "cpptrace/lib/cmake/libdwarf"),
        ],
        install_prefixes=[
            "cpptrace/lib/cmake/cpptrace",
            "cpptrace/lib64/cmake/cpptrace",
            "cpptrace/lib/cmake/libdwarf",
            "cpptrace/lib64/cmake/libdwarf",
        ],
    )

    # dep(build_name="scintilla", deps_name="scintilla/")
    dep(
        build_name="describe",
        is_emcc_ready=True,
        deps_name="cmake_wrap/describe",
        cmake_dirs=[
            ("BoostDescribe", "describe/lib/cmake/BoostDescribe"),
        ],
        install_prefixes=[
            "describe/lib/cmake/BoostDescribe",
            "describe/lib64/cmake/BoostDescribe",
        ],
    )

    dep(
        build_name="preprocessor",
        is_emcc_ready=True,
        deps_name="cmake_wrap/boost_preprocessor",
        cmake_dirs=[
            ("BoostPreprocessor", "preprocessor/lib/cmake/BoostPreprocessor"),
        ],
        install_prefixes=[
            "preprocessor/lib/cmake/BoostPreprocessor",
            "preprocessor/lib64/cmake/BoostPreprocessor",
        ],
    )

    dep(
        build_name="adaptagrams",
        deps_name="cmake_wrap/adaptagrams",
        configure_args=[
            opt("CMAKE_POSITION_INDEPENDENT_CODE", "TRUE"),
        ],
        cmake_dirs=[
            ("Adaptagrams", "adaptagrams/lib/cmake/Adaptagrams"),
        ],
        install_prefixes=[
            "adaptagrams/lib/cmake/Adaptagrams",
            "adaptagrams/lib64/cmake/Adaptagrams",
        ],
    )
    dep(
        build_name="perfetto",
        deps_name="cmake_wrap/perfetto",
        configure_args=[
            opt("CMAKE_POSITION_INDEPENDENT_CODE", "TRUE"),
        ],
        cmake_dirs=[
            ("perfetto", "perfetto/lib/cmake/Perfetto"),
        ],
        install_prefixes=[
            "perfetto/lib/cmake/Perfetto",
            "perfetto/lib64/cmake/Perfetto",
        ],
    )

    dep(
        build_name="immer",
        deps_name="immer",
        is_emcc_ready=True,
        cmake_dirs=[
            ("Immer", "immer/lib/cmake/Immer"),
        ],
        configure_args=[
            opt("immer_BUILD_TESTS", False),
            opt("immer_BUILD_EXAMPLES", False),
            opt("immer_BUILD_DOCS", False),
            opt("immer_BUILD_EXTRAS", False),
        ],
        install_prefixes=[
            "immer/lib/cmake/Immer",
            "immer/lib64/cmake/Immer",
        ],
    )

    dep(
        build_name="lager",
        deps_name="lager",
        is_emcc_ready=True,
        cmake_dirs=[
            ("Lager", "lager/lib/cmake/Lager"),
        ],
        configure_args=[
            opt("lager_BUILD_EXAMPLES", False),
            opt("lager_BUILD_TESTS", False),
            opt("lager_BUILD_FAILURE_TESTS", False),
            opt("lager_BUILD_DEBUGGER_EXAMPLES", False),
            opt("lager_BUILD_DOCS", False),
        ],
        install_prefixes=[
            "lager/lib/cmake/Lager",
            "lager/lib64/cmake/Lager",
        ],
    )

    absl = dep(
        build_name="abseil",
        deps_name="abseil-cpp",
        is_emcc_ready=True,
        configure_args=[
            opt("ABSL_CC_LIB_COPTS", "-fPIC"),
            opt("CMAKE_POSITION_INDEPENDENT_CODE", "TRUE"),
        ],
        cmake_dirs=[
            ("absl", "abseil/lib/cmake/absl"),
        ],
        install_prefixes=[
            "abseil/lib/cmake/absl",
            "abseil/lib64/cmake/absl",
        ],
    )

    dep(
        build_name="SQLiteCpp",
        deps_name="SQLiteCpp",
        configure_args=[opt("SQLITECPP_RUN_CPPLINT", False)],
        cmake_dirs=[
            ("SQLiteCpp", "SQLiteCpp/lib/cmake/SQLiteCpp"),
        ],
        install_prefixes=[
            "SQLiteCpp/lib/cmake/SQLiteCpp",
            "SQLiteCpp/lib64/cmake/SQLiteCpp",
        ],
    )

    dep(
        build_name="libgit2",
        deps_name="libgit2",
        install_prefixes=[],
        cmake_dirs=[],
        configure_args=[
            opt("BUILD_TESTS", False),
        ],
    )

    dep(
        build_name="mp11",
        deps_name="mp11",
        cmake_dirs=[
            ("boost_mp11", "mp11/lib/cmake/boost_mp11-1.85.0"),
        ],
        is_emcc_ready=True,
        install_prefixes=[
            "mp11/lib/cmake/boost_mp11-1.85.0",
            "mp11/lib64/cmake/boost_mp11-1.85.0",
        ],
    )

    dep(
        build_name="json",
        deps_name="json",
        is_emcc_ready=True,
        cmake_dirs=[
            ("nlohmann_json", "json/share/cmake/nlohmann_json"),
        ],
        configure_args=[
            opt("JSON_BuildTests", False),
        ],
        install_prefixes=[
            "json/share/cmake/nlohmann_json",
        ],
    )

    dep(
        build_name="yaml",
        deps_name="yaml-cpp",
        is_emcc_ready=True,
        cmake_dirs=[
            ("yaml-cpp",
             "yaml/lib/cmake/yaml-cpp" if is_emcc else "yaml/share/cmake/yaml-cpp"),
        ],
        configure_args=[
            opt("YAML_CPP_BUILD_TESTS", False),
            opt("CMAKE_POSITION_INDEPENDENT_CODE", "TRUE"),
        ],
        install_prefixes=[
            "yaml/share/cmake/yaml-cpp",
        ],
    )

    dep(
        build_name="range-v3",
        deps_name="range-v3",
        is_emcc_ready=True,
        cmake_dirs=[
            ("range-v3", "range-v3/lib/cmake/range-v3"),
        ],
        configure_args=[
            opt("RANGE_V3_TESTS", False),
            opt("RANGE_V3_EXAMPLES", False),
            opt("RANGE_V3_PERF", False),
        ],
        install_prefixes=[
            "range-v3/lib/cmake/range-v3",
            "range-v3/lib64/cmake/range-v3",
        ],
    )

    dep(
        build_name="pybind11",
        deps_name="pybind11",
        cmake_dirs=[
            ("pybind11", "pybind11/share/cmake/pybind11"),
        ],
        configure_args=[opt("PYBIND11_TEST", False)],
        install_prefixes=[
            "pybind11/share/cmake/pybind11",
        ],
    )

    utf8 = dep(
        build_name="utf8_range",
        deps_name="protobuf/third_party/utf8_range",
        configure_args=[
            opt("CMAKE_PREFIX_PATH", absl.get_install_prefix(install_dir=install_dir)),
            opt("utf8_range_ENABLE_TESTS", False),
        ],
        cmake_dirs=[
            ("utf8_range", "utf8_range/lib/cmake/utf8_range"),
        ],
        install_prefixes=[
            "utf8_range/lib/cmake/utf8_range",
            "utf8_range/lib64/cmake/utf8_range",
        ],
    )

    dep(
        build_name="protobuf",
        deps_name="protobuf",
        cmake_dirs=[
            ("protobuf", "protobuf/lib/cmake/protobuf"),
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
        ],
        install_prefixes=[
            "protobuf/lib/cmake/protobuf",
            "protobuf/lib64/cmake/protobuf",
        ],
    )

    dep(
        build_name="googletest",
        deps_name="googletest",
        cmake_dirs=[
            ("googletest", "googletest/lib/cmake/GTest"),
        ],
        install_prefixes=[
            "googletest/lib/cmake/GTest",
            "googletest/lib64/cmake/GTest",
        ],
    )

    dep(
        build_name="reflex",
        deps_name="RE-flex",
        is_emcc_ready=True,
        configure_args=[
            opt("CMAKE_POSITION_INDEPENDENT_CODE", "TRUE"),
        ],
        cmake_dirs=[
            ("Reflex", "reflex/lib/cmake/reflex"),
        ],
        install_prefixes=[
            "reflex/lib/cmake/reflex",
            "reflex/lib64/cmake/reflex",
        ],
    )

    dep(
        build_name="lexy",
        deps_name="lexy",
        is_emcc_ready=True,
        cmake_dirs=[
            ("lexy", "lexy/lib/cmake/lexy"),
        ],
        configure_args=[
            opt("LEXY_BUILD_EXAMPLES", False),
            opt("LEXY_BUILD_TESTS", False),
        ],
        install_prefixes=[
            "lexy/lib/cmake/lexy",
            "lexy/lib64/cmake/lexy",
        ],
    )

    return result


def get_published_build_opts() -> List[CmakeOptConfig]:
    return [
        CmakeOptConfig("ORG_DEPS_USE_PROTOBUF", False),
        CmakeOptConfig("ORG_BUILD_TESTS", True),
        CmakeOptConfig("CMAKE_BUILD_TYPE", "Debug"),
        CmakeOptConfig("ORG_BUILD_IS_DEVELOP", False),
        CmakeOptConfig("ORG_BUILD_ASSUME_CLANG", True),
        CmakeOptConfig("CMAKE_CXX_COMPILER", "clang++"),
        CmakeOptConfig("CMAKE_C_COMPILER", "clang "),
        CmakeOptConfig("ORG_USE_SANITIZER", False),
        CmakeOptConfig("ORG_DEPS_USE_ADAPTAGRAMS", False),
        CmakeOptConfig("ORG_DEPS_USE_PACKAGED_BOOST", False),
    ]
