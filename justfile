workflow_run := "uv run --verbose --all-groups -C HAXORG_PY_SOURCE_DISTRIBUTION=1 ./scripts/py_repository/py_repository/repo_tasks/workflow.py run"


run_develop_ci:
  {{workflow_run}} --task run_develop_ci \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf_develop_ci.json

build_haxorg:
  {{workflow_run}} --task build_haxorg \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf_no_emcc.json

build_develop_deps:
  {{workflow_run}} --task build_develop_deps \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf_no_emcc.json

build_develop_deps_and_haxorg: build_develop_deps build_haxorg

run_py_tests:
  {{workflow_run}} --task run_py_tests \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf_no_emcc.json

run_docker_release_ci:
  {{workflow_run}} --task run_docker_release_test \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf_develop_docker_ci.json

# RE-generate haxorg sources without running any dependent tasks
run_haxorg_only_source_generation:
  {{workflow_run}} --task generate_haxorg_sources \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_only_source_generate.json

run_haxorg_reflection_snapshot_generation:
  {{workflow_run}} --task generate_reflection_snapshot \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_only_source_generate.json

run_conan_create_test:
  conan create . --test-folder=tests/vendor/conan_test_package

run_uv_install_test:
  uv run ./scripts/py_ci/py_ci/test_uv_install.py scripts/py_haxorg --test-package tests/vendor/haxorg_py_test_package

run_github_ci:
  act push  --container-options "--cpus 24"

run_haxorg_codegen_and_tests: run_haxorg_only_source_generation run_py_tests
