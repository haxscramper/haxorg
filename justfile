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

run_docker_release_ci:
  {{uv_run}} ./scripts/py_repository/py_repository/repo_tasks/workflow.py run \
    --task run_docker_release_test \
    --config_override scripts/py_repository/py_repository/repo_tasks/haxorg_conf_develop_docker_ci.json

run_github_ci:
  act push  --container-options "--cpus 24"
