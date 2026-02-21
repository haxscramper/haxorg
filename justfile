uv_run := "uv run --verbose --all-groups -C HAXORG_PY_SOURCE_DISTRIBUTION=1"

run_develop_ci:
  {{uv_run}} --env-file=build/haxorg/dev_env \
    ./scripts/py_repository/py_repository/repo_tasks/workflow.py run \
    --task run_develop_ci \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf_develop_ci.json

build_haxorg:
  {{uv_run}} ./scripts/py_repository/py_repository/repo_tasks/workflow.py run \
    --task build_haxorg \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf_no_emcc.json

run_py_tests:
  {{uv_run}} ./scripts/py_repository/py_repository/repo_tasks/workflow.py run \
    --task run_py_tests \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf_no_emcc.json

run_docker_release_ci:
  {{uv_run}} ./scripts/py_repository/py_repository/repo_tasks/workflow.py run \
    --task run_docker_release_test \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf_develop_docker_ci.json

# RE-generate haxorg sources without running any dependent tasks
run_haxorg_only_source_generation:
  {{uv_run}} ./scripts/py_repository/py_repository/repo_tasks/workflow.py run \
    --task generate_haxorg_sources \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_only_source_generate.json

run_haxorg_reflection_snapshot_generation:
  {{uv_run}} ./scripts/py_repository/py_repository/repo_tasks/workflow.py run \
    --task generate_reflection_snapshot \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_only_source_generate.json


run_github_ci:
  act push  --container-options "--cpus 24"
