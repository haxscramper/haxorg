#!/usr/bin/env python

import py_repository.repo_tasks.airflow_utils as airflow_utils
from py_repository.repo_tasks import (
    haxorg_base,
    haxorg_build,
    haxorg_codegen,
    haxorg_coverage,
    haxorg_docker,
    haxorg_docs,
    haxorg_tests,
    examples_build,
)

main_pipeline = airflow_utils.create_dag_from_tasks(airflow_utils.get_haxorg_tasks(),
                                                    "haxorg_main_pipeline",
                                                    "Main haxorg build pipeline")

for dag in airflow_utils.create_individual_dags(airflow_utils.get_haxorg_tasks()):
    globals()[f"airflow_dag_id_{dag.dag_id}"] = dag
