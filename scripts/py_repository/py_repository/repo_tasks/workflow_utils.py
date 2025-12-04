from collections import defaultdict
from graphlib import TopologicalSorter
from pathlib import Path
from beartype import beartype
from beartype.typing import List, Callable, get_type_hints, Dict, Any, Optional
from functools import wraps
import inspect
from datetime import timedelta
from py_scriptutils.script_logging import log
from dataclasses import dataclass, field
import igraph as ig

CAT = __name__


@beartype
@dataclass
class TaskMetadata():
    dependencies: List[Callable]
    task_id: str
    signature: inspect.Signature
    type_hints: dict
    as_dag: bool
    branching: bool


@beartype
def get_task_metadata(func: Callable) -> TaskMetadata:
    return getattr(func, "_haxorg_metadata")


__airflow_task_list = []


@beartype
def get_haxorg_tasks() -> List[Callable]:
    return __airflow_task_list


@beartype
def get_task_id(func: Callable) -> str:
    return func.__name__.replace("_task", "")


@beartype
def haxorg_task(
    dependencies: List[Callable] = None,
    as_dag: bool = True,
    branching: bool = False,
):

    def decorator(func: Callable) -> Callable:
        # Validate dependencies are also haxorg_task decorated
        if dependencies:
            for dep in dependencies:
                if not hasattr(dep, "_haxorg_metadata"):
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
                if param_name == "ctx":
                    kwargs[param_name] = context["ctx"]
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

                kwargs[param_name] = value

            return func(**kwargs)

        wrapper._haxorg_metadata = TaskMetadata(
            dependencies=[dep for dep in (dependencies or [])],
            task_id=get_task_id(func),
            signature=inspect.signature(func),
            type_hints=get_type_hints(func),
            as_dag=as_dag,
            branching=branching,
        )

        __airflow_task_list.append(wrapper)
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
@dataclass
class PythonOperator():
    task_id: str
    python_callable: Callable
    params: Optional[Dict[Any, Any]] = field(default_factory=dict)

    def get_metadata(self) -> TaskMetadata:
        return get_task_metadata(self.python_callable)


@beartype
@dataclass
class TaskGraph:
    tasks: Dict[str, PythonOperator] = field(default_factory=dict)
    graph: ig.Graph = field(default_factory=lambda: ig.Graph(directed=True))

    @beartype
    def create_python_operator(
        self,
        python_callable: Any,
        params: Optional[Dict[str, Any]] = None,
    ) -> PythonOperator:
        metadata = get_task_metadata(python_callable)
        task_id = metadata.task_id

        return PythonOperator(
            task_id=task_id,
            python_callable=python_callable,
            params=params or {},
        )

    @beartype
    def get_create_python_operator(self, func: Callable) -> PythonOperator:
        metadata = get_task_metadata(func)
        task_id = metadata.task_id

        if task_id not in self.tasks:
            self.tasks[task_id] = self.create_python_operator(func)
            self.graph.add_vertex(name=task_id)

        return self.tasks[task_id]

    def add_edge(self, source: PythonOperator, target: PythonOperator):
        self.graph.add_edge(source.task_id, target.task_id)

    def get_tasks(self) -> List[str]:
        return [self.graph.vs[n]["name"] for n in self.graph.topological_sorting()]


@beartype
@dataclass
class TaskContext():
    graph: TaskGraph
    current_task: Optional[PythonOperator] = None

    def get_task_debug_suffix(self, cmd: str = "") -> str:
        result = ""

        if self.current_task:
            result += self.current_task.get_metadata().task_id

        if cmd:
            result += "_" + cmd

        if not result:
            result = "default"

        return result

    def get_task_debug_streams(self, cmd: str, args) -> tuple[Path, Path]:
        import hashlib
        digest = hashlib.md5(f"{cmd} {args}".encode()).hexdigest()[:8]
        result = (
            Path(f"/tmp/{self.get_task_debug_suffix(cmd)}_{digest}_stderr.log"),
            Path(f"/tmp/{self.get_task_debug_suffix(cmd)}_{digest}_stdout.log"),
        )

        header = f"""
cmd:  {cmd}
args: {args}
        """

        result[0].write_text(header)
        result[1].write_text(header)

        return result

    def run(self, target_name: str | Callable):
        target_name = target_name if isinstance(target_name,
                                                str) else target_name.__name__
        target_id = self.graph.graph.vs.find(name=target_name).index

        dependent_indices = self.graph.graph.subcomponent(target_id, mode="in")
        sub_graph = self.graph.graph.induced_subgraph(dependent_indices)

        sorted_indices = sub_graph.topological_sorting()
        execution_order = sub_graph.vs[sorted_indices]["name"]

        for task_id in execution_order:
            self.current_task = self.graph.tasks[task_id]
            self.graph.tasks[task_id].python_callable(ctx=self)
            self.current_task = None


@beartype
def create_dag_from_tasks(task_functions: List[Callable]) -> TaskGraph:
    dag = TaskGraph()
    for func in task_functions:
        metadata = get_task_metadata(func)
        current_op = dag.get_create_python_operator(func)

        for dep in metadata.dependencies:
            dep_op = dag.get_create_python_operator(dep)
            dag.add_edge(source=dep_op, target=current_op)

    return dag


# @beartype
# def create_individual_dags(task_functions: List[Callable]) -> List[DAG]:
#     individual_dags = []

#     for func in task_functions:
#         metadata = get_task_metadata(func)
#         if metadata.as_dag:
#             task_id = metadata.task_id
#             dag = create_dag(f"{task_id}_dag", f"Individual task: {task_id}")
#             operators = {}
#             get_create_python_operator(func, operators, dag)
#             individual_dags.append(dag)

#             def dfs_deps(func: Callable):
#                 metadata = get_task_metadata(func)
#                 for dep in metadata.dependencies:
#                     current_task = get_create_python_operator(func, operators, dag)
#                     get_create_python_operator(dep, operators, dag) >> current_task

#                     dfs_deps(dep)

#             dfs_deps(func)

#     return individual_dags
