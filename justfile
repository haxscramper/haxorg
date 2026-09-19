workflow_run := "uv run --verbose --all-groups -C HAXORG_PY_SOURCE_DISTRIBUTION=1 ./scripts/py_repository/py_repository/repo_tasks/workflow.py run"

uv_run := "uv run --verbose --all-groups -C HAXORG_PY_SOURCE_DISTRIBUTION=1"

run_code_forensics:
  {{uv_run}} scripts/cxx_repository/cxx_repository/code_forensics_cli.py \
    --input . \
    --out build/code_forensics_run/db.sqlite \
    --result_dir build/code_forensics_run \
    --skip_if_exists True

run_develop_ci:
  {{workflow_run}} --task run_develop_ci \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf_develop_ci.json

run_develop_ci_emcc:
  {{workflow_run}} --task run_develop_ci \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf_emcc_only.json

build_haxorg:
  {{workflow_run}} --task build_haxorg \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf.json

build_develop_deps:
  {{workflow_run}} --task build_develop_deps \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf.json

build_develop_deps_and_haxorg: build_develop_deps build_haxorg

run_py_tests:
  {{workflow_run}} --task run_py_tests \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf.json

run_coverage_merge:
  {{workflow_run}} --task run_cxx_coverage_merge \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf.json

run_custom_docs_gen:
  {{workflow_run}} --task build_custom_docs \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf.json

# RE-generate haxorg sources without running any dependent tasks
run_haxorg_only_source_generation:
  {{workflow_run}} --task generate_haxorg_sources \
    --workflow_log_dir /tmp/haxorg/workflow_source_generation_log \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_only_source_generate.json

run_haxorg_reflection_snapshot_generation:
  {{workflow_run}} --task generate_reflection_snapshot \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_only_source_generate.json

run_conan_create_test:
  conan create . --test-folder=tests/vendor/conan_test_package --build=missing

run_uv_install_test:
  uv run ./scripts/py_ci/py_ci/test_uv_install.py scripts/py_haxorg --test-package tests/vendor/haxorg_py_test_package

run_github_ci:
  act push --container-options "--cpus 24" --reuse

run_github_ci_1:
  act push --container-options "--cpus 24" --reuse -W .github/workflows/readme_run_lib.yaml

run_haxorg_codegen_and_tests: run_haxorg_only_source_generation run_py_tests

run_haxorg_codegen_and_build: run_haxorg_only_source_generation build_haxorg

run_haxorg_builder_codegen_and_tests: build_haxorg run_haxorg_reflection_snapshot_generation run_haxorg_only_source_generation run_py_tests

run_haxorg_builder_and_tests: build_haxorg run_haxorg_only_source_generation run_py_tests

run_pytest_and_coverage_docs: run_py_tests run_coverage_merge run_custom_docs_gen

run_doxygen_docs_build:
  {{workflow_run}} --task docs_doxygen \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf.json

run_include_graph_generation:
  {{workflow_run}} --task generate_include_graph \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf.json

run_codechecker:
  {{workflow_run}} --task docs_doxygen \
    run_codechecker_analysis

dump_cli_stack:
  lldb -p $(pgrep -f haxorg_cpp_org_cli) -o "thread backtrace all" -o "detach" -o "quit" > /tmp/trace.log

debug_py_test TEST:
    #!/usr/bin/env bash
    export PYTHONPATH="${PYTHONPATH}:$(pwd)/build/haxorg"
    lldb \
        -o 'breakpoint set -E c++' \
        -o run \
        -- "$(uv run --no-sync which python)" -m pytest -vv -s {{TEST}}

profile_perf_cli bin opts_path freq='3000':
    perf record --freq={{freq}} --call-graph dwarf -- {{bin}} {{opts_path}}

profile_heaptrack_cli bin opts_path:
    heaptrack {{bin}} {{opts_path}}

profile_valgrind tool bin opts_path:
    valgrind --tool={{tool}}  --{{tool}}-out-file=build/{{tool}}.out.haxorg_cli {{bin}} {{opts_path}}


# by default, kcachegrind is incapable of properly reading the specified path verbatim -- it tries
# to read everything around it, some things like `build/callgrind.out.haxorg_cli-2026-08-29T19:09:31+04:00`
# or whatnot -- and the actual specified path is given lowest priority, so to make justfile actually
# work as expected, I need to do this hack.
profile_valgrind_view path:
    #!/usr/bin/env bash
    set -euo pipefail
    tmpdir=$(mktemp -d)
    trap 'rm -rf "$tmpdir"' EXIT
    cp "{{path}}" "$tmpdir/profile"
    kcachegrind "$tmpdir/profile"

profile_callgrind_annotate out_file *files:
  callgrind_annotate --auto=no {{out_file}} {{files}} > build/haxorg_callgrind_annotate.txt

profile_perf_view:
  hotspot perf.data

generate_diagram_schema:
  rm -rf build/jsonschema
  buf generate --path src/hstd/ext/graph/visual/graph_diagram.proto
  buf generate --path src/hstd/ext/graph/visual/graph_diagram_validate.proto


repo_prepare_git_hooks:
  install -Dm755 repo_py_validate/prepare_commit_message.py .git/hooks/prepare-commit-msg



HAXORG_ROOT := source_directory()
CONAN_PROFILE := HAXORG_ROOT / "repo_tool_configs/conan/conanprofile.txt"

conan_info_package_path package:
  conan graph info {{package}} --format=html > /tmp/graph.html
  echo /tmp/graph.html

conan_remove_deps:
  conan remove "protovalidate-cc/*" -c

# Export local dependencies so subsequent build 
conan_export_deps: 
  conan export "repo_conan_wraps/protovalidate-cc"

[working-directory("/tmp")]
conan_validate_deps_protovalidate_cc: conan_remove_deps
  conan create {{HAXORG_ROOT}}/repo_conan_wraps/protovalidate-cc \
    --profile:all={{CONAN_PROFILE}} \
    -s build_type=Release \
    --build=missing

[working-directory("/tmp")]
conan_validate_hstd_cpp: 
  conan create {{HAXORG_ROOT}}/hstd_cpp/hstd_lib \
    --profile:all={{CONAN_PROFILE}} \
    -s build_type=Release \
    --build=missing

conan_clean_validate_hstd_cpp: conan_remove_deps conan_export_deps conan_validate_hstd_cpp
