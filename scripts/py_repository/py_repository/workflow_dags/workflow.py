#!/usr/bin/env python

import py_repository.repo_tasks.airflow_utils as airflow_utils
from py_repository.repo_tasks.haxorg_build import build_haxorg


all_tasks = [
    build_haxorg,
]

main_pipeline = airflow_utils.create_dag_from_tasks(all_tasks, "haxorg_main_pipeline",
                                      "Main haxorg build pipeline")


for dag in airflow_utils.create_individual_dags(all_tasks):
    globals()[f"airflow_dag_id_{dag.dag_id}"] = dag
