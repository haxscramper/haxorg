from beartype import beartype
from beartype.typing import List, Callable, get_type_hints, Dict, Any, Optional
from functools import wraps
import inspect
from datetime import timedelta
from airflow import DAG
from airflow.providers.standard.operators.python import PythonOperator

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
