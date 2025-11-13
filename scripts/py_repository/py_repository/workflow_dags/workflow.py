#!/usr/bin/env python

from functools import wraps
from typing import List, Callable, Any, Dict, get_type_hints, Optional
from beartype import beartype
import inspect
import logging
from airflow import DAG
from airflow.providers.standard.operators.python import PythonOperator
from datetime import timedelta

default_args = {
    "owner": "haxorg",
    "depends_on_past": False,
    "email_on_failure": False,
    "email_on_retry": False,
    "retries": 1,
    "retry_delay": timedelta(minutes=5)
}


@beartype
def create_python_operator(task_id: str,
                           python_callable: Any,
                           dag: DAG,
                           params: Optional[Dict[str, Any]] = None) -> PythonOperator:
    return PythonOperator(task_id=task_id,
                          python_callable=python_callable,
                          dag=dag,
                          params=params or {})


@beartype
def create_dag(dag_id: str, description: str) -> DAG:
    return DAG(
        dag_id,
        default_args=default_args,
        description=description,
        catchup=False,
        tags=["haxorg"],
    )


from functools import wraps
from typing import List, Callable, Any, Dict, get_type_hints
from beartype import beartype
import inspect


@beartype
def haxorg_task(dependencies: List[Callable] = None, as_dag: bool = True):

    def decorator(func: Callable) -> Callable:
        # Validate dependencies are also haxorg_task decorated
        if dependencies:
            for dep in dependencies:
                if not hasattr(dep, "_haxorg_task_id"):
                    raise ValueError(
                        f"Dependency {dep.__name__} must be decorated with @haxorg_task")

        @wraps(func)
        def wrapper(**context):
            # Get function signature and type hints
            sig = inspect.signature(func)
            type_hints = get_type_hints(func)

            # Extract parameters from context based on function signature
            kwargs = {}

            for param_name, param in sig.parameters.items():
                if param_name == "context":
                    kwargs[param_name] = context
                    continue

                # Get value from context params or use default
                if param_name in context.get("params", {}):
                    value = context["params"][param_name]
                elif param.default != inspect.Parameter.empty:
                    value = param.default
                else:
                    raise ValueError(
                        f"Required parameter '{param_name}' not found in context for task {func.__name__}"
                    )

                # Type conversion if type hint is available
                if param_name in type_hints:
                    expected_type = type_hints[param_name]
                    # Handle Optional types and basic type conversion
                    if hasattr(expected_type, "__origin__"):
                        if expected_type.__origin__ is list and isinstance(value, str):
                            value = [value] if value else []
                    elif expected_type == bool and isinstance(value, str):
                        value = value.lower() in ("true", "1", "yes", "on")
                    elif expected_type == int and isinstance(value, str):
                        value = int(value)
                    elif expected_type == float and isinstance(value, str):
                        value = float(value)

                kwargs[param_name] = value

            return func(**kwargs)

        wrapper._haxorg_dependencies = [
            dep.__name__.replace("_task", "") for dep in (dependencies or [])
        ]
        wrapper._haxorg_task_id = func.__name__.replace("_task", "")
        wrapper._haxorg_signature = inspect.signature(func)
        wrapper._haxorg_type_hints = get_type_hints(func)
        wrapper._haxorg_as_dag = as_dag

        return wrapper

    return decorator


@beartype
def get_task_metadata(func: Callable) -> Dict[str, Any]:
    return {
        "dependencies": getattr(func, "_haxorg_dependencies", []),
        "task_id": getattr(func, "_haxorg_task_id", func.__name__),
        "signature": getattr(func, "_haxorg_signature", None),
        "type_hints": getattr(func, "_haxorg_type_hints", {}),
        "as_dag": getattr(func, "_haxorg_as_dag", True)
    }


@beartype
def create_dag_from_tasks(task_functions: List[Callable], dag_id: str,
                          description: str) -> DAG:
    dag = create_dag(dag_id, description)
    operators = {}

    for func in task_functions:
        metadata = get_task_metadata(func)
        task_id = metadata["task_id"]
        operators[task_id] = create_python_operator(task_id, func, dag)

    for func in task_functions:
        metadata = get_task_metadata(func)
        task_id = metadata["task_id"]
        current_op = operators[task_id]

        for dep in metadata["dependencies"]:
            if dep in operators:
                operators[dep] >> current_op

    return dag


@beartype
def create_individual_dags(task_functions: List[Callable]) -> List[DAG]:
    individual_dags = []

    for func in task_functions:
        metadata = get_task_metadata(func)
        if metadata["as_dag"]:
            task_id = metadata["task_id"]
            logging.info(f"haxorg_{task_id}, {func}, {metadata}")
            dag = create_dag(f"haxorg_{task_id}", f"Individual task: {task_id}")
            create_python_operator(task_id, func, dag)
            individual_dags.append(dag)

    return individual_dags


@haxorg_task()
def git_init_submodules_task(context: Dict[str, Any]):
    logging.info("Initializing git submodules")


@haxorg_task()
def download_llvm_task(context: Dict[str, Any]):
    logging.info("Downloading LLVM")


@haxorg_task(dependencies=[git_init_submodules_task, download_llvm_task])
def base_environment_task(context: Dict[str, Any]):
    logging.info("Setting up base environment")


@haxorg_task(as_dag=False)
def generate_develop_deps_install_paths_task(context: Dict[str, Any]):
    logging.info("Generating develop deps install paths")


@haxorg_task(
    dependencies=[base_environment_task, generate_develop_deps_install_paths_task])
def configure_cmake_haxorg_task(context: Dict[str, Any], force: bool = False):
    logging.info(f"Configuring cmake haxorg (force: {force})")


@haxorg_task(dependencies=[configure_cmake_haxorg_task])
def build_haxorg_task(context: Dict[str, Any],
                      target: List[str] = None,
                      force: bool = False):
    if target is None:
        target = ["all"]
    logging.info(f"Building haxorg (target: {target}, force: {force})")


@haxorg_task(dependencies=[build_haxorg_task], as_dag=False)
def install_haxorg_develop_task(context: Dict[str, Any], perfetto: bool = False):
    logging.info(f"Installing haxorg develop (perfetto: {perfetto})")


@haxorg_task(dependencies=[build_haxorg_task])
def run_py_tests_task(context: Dict[str, Any], arg: List[str] = None):
    if arg is None:
        arg = []
    logging.info(f"Running py tests (args: {arg})")


@haxorg_task(dependencies=[run_py_tests_task])
def run_py_tests_ci_task(context: Dict[str, Any]):
    logging.info("Running py tests ci")


all_tasks = [
    git_init_submodules_task,
    download_llvm_task,
    base_environment_task,
    generate_develop_deps_install_paths_task,
    configure_cmake_haxorg_task,
    build_haxorg_task,
    install_haxorg_develop_task,
    run_py_tests_task,
    run_py_tests_ci_task,
]

main_pipeline = create_dag_from_tasks(all_tasks, "haxorg_main_pipeline",
                                      "Main haxorg build pipeline")


for dag in create_individual_dags(all_tasks):
    globals()[f"airflow_dag_id_{dag.dag_id}"] = dag
