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
  buf generate --path hstd_cpp_diagram/graph_diagram.proto
  buf generate --path hstd_cpp_diagram/graph_diagram_validate.proto


repo_prepare_git_hooks:
  install -Dm755 repo_py_validate/prepare_commit_message.py .git/hooks/prepare-commit-msg



HAXORG_ROOT := source_directory()
# custom profile is mandatory for full builds, otherwise onetbb fails
# to configure hwloc, see profile text for more details.
CONAN_PROFILE := HAXORG_ROOT / "repo_tool_configs/conan/conanprofile.txt"
SUPPRESSION_FILE := HAXORG_ROOT / "repo_tool_configs/clang_suppressions.supp"

conan_info_package_path package:
  conan graph info {{package}} --format=html > /tmp/graph.html
  echo /tmp/graph.html

conan_reset_external_dep target:
  conan remove "{{target}}/*" -c
  conan export "repo_conan_wraps/{{target}}"

conan_reset_local_dep target:
  conan remove "{{target}}/*" -c
  conan export "{{target}}"

conan_remove_external_deps:
  conan remove "protovalidate-cc/*" -c
  conan remove "graphviz/*" -c
  conan remove "kiwi/*" -c
  conan remove "adaptagrams/*" -c

conan_export_external_deps:
  conan export "repo_conan_wraps/protovalidate-cc"
  conan export "repo_conan_wraps/graphviz"
  conan export "repo_conan_wraps/kiwi"
  conan export "repo_conan_wraps/adaptagrams"

conan_remove_local_deps:
  conan remove "hstd_cpp_lib/*" --confirm
  conan remove "hstd_cpp_text_layout/*" --confirm
  conan remove "haxorg_cpp_org_lib/*" --confirm
  conan remove "hstd_cpp_diagram_lib/*" --confirm
  conan remove "haxdex_read_code_cpp/*" --confirm

conan_export_local_deps:
  conan export "hstd_cpp_lib"
  conan export "hstd_cpp_text_layout"
  conan export "haxorg_cpp_org_lib"
  conan export "hstd_cpp_diagram_lib"
  conan export "haxdex_read_code_cpp"

[working-directory("/tmp")]
conan_validate_deps dep_name:
  conan remove "{{dep_name}}/*" -c
  conan create {{HAXORG_ROOT}}/repo_conan_wraps/{{dep_name}} \
    --profile:all={{CONAN_PROFILE}} \
    -s build_type=Release \
    --build=missing

# -c 'user.hstd:ninja_args=["-k","0","--verbose"]' \

[working-directory("/tmp")]
conan_validate target:
  conan remove "{{target}}/*" --confirm
  conan create {{HAXORG_ROOT}}/{{target}} \
    --profile:all={{CONAN_PROFILE}} \
    -s build_type=Release \
    -c 'user.hstd:warning_suppressions={{SUPPRESSION_FILE}}' \
    -c 'user.hstd:ninja_args=["-k","0","--verbose"]' \
    --build=missing \
     -vstatus

conan_update_local_deps: conan_remove_local_deps conan_export_local_deps
conan_update_external_deps: conan_remove_external_deps conan_export_external_deps

# remove and export all dependencies in project
conan_update_all_deps: conan_update_external_deps conan_update_local_deps

# remove all dependencies (local+external), then validate target from scratch
conan_clean_total_validate target: conan_update_local_deps conan_update_external_deps
  just conan_validate {{target}}

conan_clean_local_validate target: conan_update_local_deps
  just conan_validate {{target}}

# Conan currently has no `conan workspace source` command.
# Enumerate the workspace members from `conanws.yml` and invoke `conan source` for each:
conan_workspace_source:
    #!/usr/bin/env bash
    set -euo pipefail

    yq -r '.packages[].path' conanws.yml |
        while IFS= read -r package; do
            conan source "$package"
        done


# Conan workspace monolithic install
conan_workspace_install_monorepo:
  conan workspace super-install \
    --output-folder=build/conan_super \
    -s build_type=Debug \
    --build=missing \
    --profile:all={{CONAN_PROFILE}}

# Conan workspace install for individual projects
conan_workspace_install_per_project:
  mkdir -p build
  conan workspace install \
    -s build_type=Debug \
    --build=missing \
    --profile:all={{CONAN_PROFILE}}

  conan workspace build --build=missing --profile:all={{CONAN_PROFILE}}

# !! completely reset the conan state -- WILL CLEAN EVERYTHING
conan_clean_all:
  conan cache clean
  conan remove "*" -c

py_validate target *args:
  {{HAXORG_ROOT}}/repo_ci_config/py_ci/test_uv_install.py \
    {{HAXORG_ROOT}}/{{target}} \
    --conan-profile={{CONAN_PROFILE}} \
    {{args}}

run_to_output target *ARGS:
  -just {{target}} {{ARGS}} > build/target_result.log 2>&1
# ./repo_py_orchestrate/remap_conan_error_paths.py build/target_result.log
