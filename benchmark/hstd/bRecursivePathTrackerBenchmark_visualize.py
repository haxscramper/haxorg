#!/usr/bin/env python

import json
import logging
from pathlib import Path
from dataclasses import dataclass
from beartype.typing import List, Dict, Any, Optional, Union
import matplotlib.pyplot as plt
import matplotlib.axes as plt_axes
import rich_click as click
from beartype import beartype
import seaborn as sns
import pandas as pd
import numpy as np

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


@beartype
@dataclass
class BenchmarkResult:
    name: str
    family_index: int
    per_family_instance_index: int
    run_name: str
    run_type: str
    repetitions: int
    repetition_index: Optional[int]
    threads: int
    iterations: Optional[int]
    real_time: Optional[float | int]
    cpu_time: Optional[float | int]
    time_unit: Optional[str]
    label: Optional[str] = None
    error_occurred: bool = False
    error_message: Optional[str] = None
    aggregate_name: Optional[str] = None
    aggregate_unit: Optional[str] = None


@beartype
@dataclass
class BenchmarkContext:
    date: str
    host_name: str
    executable: str
    num_cpus: int
    mhz_per_cpu: float | int
    cpu_scaling_enabled: bool
    caches: List[Dict[str, Any]]
    load_avg: List[float | int]


@beartype
@dataclass
class BenchmarkData:
    context: BenchmarkContext
    benchmarks: List[BenchmarkResult]


class BenchmarkParser:

    def parse_json_output(self, json_path: Path) -> BenchmarkData:
        with open(json_path, "r") as f:
            data = json.load(f)

        context = self._parse_context(data["context"])
        benchmarks = [self._parse_benchmark(b) for b in data["benchmarks"]]

        return BenchmarkData(context, benchmarks)

    def _parse_context(self, context_data: Dict[str, Any]) -> BenchmarkContext:
        return BenchmarkContext(
            date=context_data["date"],
            host_name=context_data["host_name"],
            executable=context_data["executable"],
            num_cpus=context_data["num_cpus"],
            mhz_per_cpu=context_data["mhz_per_cpu"],
            cpu_scaling_enabled=context_data["cpu_scaling_enabled"],
            caches=context_data.get("caches", []),
            load_avg=context_data.get("load_avg", []),
        )

    def _parse_benchmark(self, benchmark_data: Dict[str, Any]) -> BenchmarkResult:
        return BenchmarkResult(
            name=benchmark_data["name"],
            family_index=benchmark_data["family_index"],
            per_family_instance_index=benchmark_data["per_family_instance_index"],
            run_name=benchmark_data["run_name"],
            run_type=benchmark_data["run_type"],
            repetitions=benchmark_data["repetitions"],
            repetition_index=benchmark_data.get("repetition_index", None),
            threads=benchmark_data["threads"],
            iterations=benchmark_data.get("iterations", None),
            real_time=benchmark_data.get("real_time", None),
            cpu_time=benchmark_data.get("cpu_time", None),
            time_unit=benchmark_data.get("time_unit", None),
            label=benchmark_data.get("label"),
            error_occurred=benchmark_data.get("error_occurred", False),
            error_message=benchmark_data.get("error_message"),
            aggregate_unit=benchmark_data.get("aggregate_unit", None),
            aggregate_name=benchmark_data.get("aggregate_name", None),
        )


class BenchmarkVisualizer:

    def __init__(self) -> None:
        plt.style.use("seaborn-v0_8")
        sns.set_palette("husl")

    def create_performance_comparison(self, data: BenchmarkData,
                                      output_path: Path) -> None:
        df = self._benchmarks_to_dataframe(data.benchmarks)
        df = df[df["run_type"] == "iteration"]

        operations = df["operation"].unique()
        fig, axes = plt.subplots(len(operations), 1, figsize=(15, 6 * len(operations)))
        if len(operations) == 1:
            axes = [axes]

        for idx, operation in enumerate(operations):
            op_data = df[df["operation"] == operation]
            self._plot_operation_comparison(axes[idx], operation, op_data)

        plt.tight_layout()
        plt.savefig(output_path, dpi=300, bbox_inches="tight")
        plt.close()

    def create_scaling_analysis(self, data: BenchmarkData, output_path: Path) -> None:
        df = self._benchmarks_to_dataframe(data.benchmarks)
        df = df[df["run_type"] == "iteration"]

        operations = df["operation"].unique()
        fig, axes = plt.subplots(len(operations), 1, figsize=(15, 6 * len(operations)))
        if len(operations) == 1:
            axes = [axes]

        for idx, operation in enumerate(operations):
            op_data = df[df["operation"] == operation]
            self._plot_scaling_behavior(axes[idx], operation, op_data)

        plt.tight_layout()
        plt.savefig(output_path, dpi=300, bbox_inches="tight")
        plt.close()

    def create_heatmap(self, data: BenchmarkData, output_path: Path) -> None:
        df = self._benchmarks_to_dataframe(data.benchmarks)
        df = df[df["run_type"] == "iteration"]

        if df.empty or "param1" not in df.columns or "param2" not in df.columns:
            logger.warning("Insufficient data for heatmap")
            return

        pivot_data = df.pivot_table(values="real_time_ms",
                                    index="implementation",
                                    columns=["operation", "param1", "param2"],
                                    aggfunc="mean")

        plt.figure(figsize=(20, 8))
        sns.heatmap(pivot_data, annot=True, fmt=".2f", cmap="YlOrRd")
        plt.title("Performance Heatmap (ms)")
        plt.tight_layout()
        plt.savefig(output_path, dpi=300, bbox_inches="tight")
        plt.close()

    def create_complexity_analysis(self, data: BenchmarkData, output_path: Path) -> None:
        df = self._benchmarks_to_dataframe(data.benchmarks)
        complexity_data = df[df["run_type"].isin(["aggregate"])]

        if complexity_data.empty:
            logger.warning("No complexity data found")
            return

        big_o_data = complexity_data[complexity_data["aggregate_name"] == "BigO"]

        plt.figure(figsize=(12, 8))

        for impl in big_o_data["implementation"].unique():
            impl_data = big_o_data[big_o_data["implementation"] == impl]
            operations = impl_data["operation"].unique()

            for op in operations:
                op_data = impl_data[impl_data["operation"] == op]
                if not op_data.empty:
                    complexity = op_data["real_time"].iloc[0]
                    plt.bar(f"{impl}_{op}", complexity, label=f"{impl} - {op}")

        plt.xlabel("Implementation - Operation")
        plt.ylabel("Complexity Coefficient")
        plt.title("Big-O Complexity Analysis")
        plt.xticks(rotation=45)
        plt.legend()
        plt.tight_layout()
        plt.savefig(output_path, dpi=300, bbox_inches="tight")
        plt.close()

    def _benchmarks_to_dataframe(self, benchmarks: List[BenchmarkResult]) -> pd.DataFrame:
        data = []
        for benchmark in benchmarks:
            operation, implementation, param1, param2 = self._parse_benchmark_name(
                benchmark.name)

            real_time_ms = self._convert_to_ms(benchmark.real_time, benchmark.time_unit)
            cpu_time_ms = self._convert_to_ms(benchmark.cpu_time, benchmark.time_unit)

            data.append({
                "name": benchmark.name,
                "operation": operation,
                "implementation": implementation,
                "param1": param1,
                "param2": param2,
                "run_type": benchmark.run_type,
                "real_time": benchmark.real_time,
                "cpu_time": benchmark.cpu_time,
                "real_time_ms": real_time_ms,
                "cpu_time_ms": cpu_time_ms,
                "time_unit": benchmark.time_unit,
                "iterations": benchmark.iterations,
                "threads": benchmark.threads,
                "aggregate_name": benchmark.aggregate_name,
                "aggregate_unit": benchmark.aggregate_unit,
            })

        return pd.DataFrame(data)

    def _parse_benchmark_name(self,
                              name: str) -> tuple[str, str, Optional[int], Optional[int]]:
        parts = name.split("_")

        if name.endswith("_BigO") or name.endswith("_RMS"):
            parts = parts[:-1]

        operation = parts[1] if len(parts) > 1 else "Unknown"
        implementation = parts[2] if len(parts) > 2 else "Unknown"

        param_parts = name.split("/")
        param1 = int(param_parts[1]) if 1 < len(param_parts) else None
        param2 = int(param_parts[2]) if 2 < len(param_parts) else None
        if 0 < len(param_parts):
            implementation = param_parts[0]

        # logger.info(f"{(operation, implementation, param1, param2)}")
        return operation, implementation, param1, param2

    def _convert_to_ms(self, time_value: float, time_unit: str) -> float:
        if time_value is None:
            return 0
        elif time_unit == "ns":
            return time_value / 1_000_000
        elif time_unit == "us":
            return time_value / 1_000
        elif time_unit == "ms":
            return time_value
        elif time_unit == "s":
            return time_value * 1_000
        else:
            return time_value

    def _plot_operation_comparison(self, ax: plt_axes.Axes, operation: str, df: pd.DataFrame) -> None:
        grouped = df.groupby("implementation")["real_time_ms"].mean().sort_values()

        bars = ax.bar(range(len(grouped)), grouped.values)
        ax.set_xlabel("Implementation")
        ax.set_ylabel("Time (ms)")
        ax.set_title(f"{operation} Performance Comparison")
        ax.set_xticks(range(len(grouped)))
        ax.set_xticklabels(grouped.index, rotation=45)
        ax.set_yscale("log")

        for i, (impl, time) in enumerate(grouped.items()):
            ax.text(i, time, f"{time:.2f}ms", ha="center", va="bottom")

    def _plot_scaling_behavior(self, ax: plt_axes.Axes, operation: str, df: pd.DataFrame) -> None:
        for impl in df["implementation"].unique():
            impl_data = df[df["implementation"] == impl]

            if impl_data["param1"].notna().any() and impl_data["param2"].notna().any():
                x_data = impl_data["param1"] * impl_data["param2"]
                y_data = impl_data["real_time_ms"]
                sorted_data = sorted(zip(x_data, y_data))
                x_sorted, y_sorted = zip(*sorted_data)
                ax.plot(x_sorted, y_sorted, label=impl, alpha=0.7, marker='o')

        ax.set_xlabel("Problem Size (param1 * param2)")
        ax.set_ylabel("Time (ms)")
        ax.set_title(f"{operation} Scaling Behavior")
        ax.set_xscale("log")
        ax.set_yscale("log")
        ax.legend()
        ax.grid(True, alpha=0.3)


@click.command()
@click.option("--input",
              "-i",
              "input_file",
              type=click.Path(exists=True, path_type=Path),
              default="benchmark_results.json",
              help="Input JSON benchmark file")
@click.option("--output",
              "-o",
              "output_dir",
              type=click.Path(path_type=Path),
              default="benchmark_plots",
              help="Output directory for plots")
def main(input_file: Path, output_dir: Path) -> None:
    output_dir.mkdir(exist_ok=True)

    if not input_file.exists():
        logger.error(f"Benchmark JSON file not found: {input_file}")
        return

    parser = BenchmarkParser()

    data = parser.parse_json_output(input_file)

    logger.info(f"Parsed {len(data.benchmarks)} benchmark results")

    visualizer = BenchmarkVisualizer()

    perf_path = output_dir / "performance_comparison.png"
    visualizer.create_performance_comparison(data, perf_path)
    logger.info(f"Created performance comparison plot in '{perf_path}'")

    scaling_analysis = output_dir / "scaling_analysis.png"
    visualizer.create_scaling_analysis(data, scaling_analysis)
    logger.info(f"Created scaling analysis plot in '{scaling_analysis}'")

    perf_heatmap_path =  output_dir / "performance_heatmap.png"
    visualizer.create_heatmap(data, perf_heatmap_path)
    logger.info(f"Created performance heatmap in '{perf_heatmap_path}")

    complexity_analysis_path = output_dir / "complexity_analysis.png"
    visualizer.create_complexity_analysis(data, complexity_analysis_path)
    logger.info(f"Created complexity analysis plot ino '{complexity_analysis_path}'")


if __name__ == "__main__":
    main()
