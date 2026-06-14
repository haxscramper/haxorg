workflow_run := "uv run --verbose --all-groups -C HAXORG_PY_SOURCE_DISTRIBUTION=1 ./scripts/py_repository/py_repository/repo_tasks/workflow.py run"

uv_run := "uv run --verbose --all-groups -C HAXORG_PY_SOURCE_DISTRIBUTION=1"

run_code_forensics:
  {{uv_run}} scripts/cxx_repository/cxx_repository/code_forensics_cli.py \
    --input . --out build/code_forensics_run/db.sqlite --skip_if_exists True

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
  act push  --container-options "--cpus 24" --reuse

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
