import logging
import shlex
from dataclasses import dataclass, field, replace
from typing import Callable

import lldb

from hstd_py_lib.debug_utils.config import Settings
from hstd_py_lib.debug_utils.extract import (
    ExtractionContext,
    ExtractorRegistry,
)
from hstd_py_lib.debug_utils.model import ReportReason, ValueNode
from hstd_py_lib.debug_utils.output import create_logger, emit_report


@dataclass
class Runtime:
    target: lldb.SBTarget
    settings: Settings
    context: ExtractionContext
    logger: logging.Logger
    configured: bool = False
    fatal_processes: set[int] = field(default_factory=set)


registry = ExtractorRegistry()
runtimes: dict[int, Runtime] = {}


def register_extractor(
    pattern: str,
    extract: Callable[
        [lldb.SBValue, ExtractionContext, int],
        ValueNode,
    ],
) -> None:
    registry.register(pattern, extract)


def execute_command(
    debugger: lldb.SBDebugger,
    command: str,
) -> str:
    result = lldb.SBCommandReturnObject()
    debugger.GetCommandInterpreter().HandleCommand(
        command,
        result,
    )

    if not result.Succeeded():
        raise RuntimeError(
            f"LLDB command {command!r} failed: {result.GetError() or result.GetOutput()}"
        )

    return result.GetOutput() or ""


def get_runtime(
    debugger: lldb.SBDebugger,
) -> Runtime:
    target = debugger.GetSelectedTarget()

    if not target.IsValid():
        raise RuntimeError("rich-backtrace requires a selected LLDB target")

    identifier = debugger.GetID()
    current = runtimes.get(identifier)

    if current is not None and current.target == target:
        return current

    settings = Settings.from_environment()
    runtime = Runtime(
        target=target,
        settings=settings,
        context=ExtractionContext(settings, registry),
        logger=create_logger(
            f"hstd_py_lib.debug_utils.{identifier}",
            settings,
        ),
    )
    runtimes[identifier] = runtime
    return runtime


def configure(
    debugger: lldb.SBDebugger,
) -> None:
    runtime = get_runtime(debugger)

    if runtime.configured:
        raise RuntimeError(
            "rich-backtrace-configure has already configured the selected target"
        )

    for name in runtime.settings.breakpoint_functions:
        breakpoint = runtime.target.BreakpointCreateByName(name)

        if not breakpoint.IsValid():
            raise RuntimeError(f"LLDB could not create breakpoint for {name!r}")

        breakpoint.SetScriptCallbackFunction(f"{__name__}.breakpoint_callback")

    for name in runtime.settings.fatal_signals:
        execute_command(
            debugger,
            f"process handle {shlex.quote(name)} -s true -n false -p true",
        )

    if runtime.settings.fatal_signals:
        execute_command(
            debugger,
            f"target stop-hook add -P {__name__}.FatalSignalStopHook",
        )

    runtime.configured = True


def trace_command(
    debugger: lldb.SBDebugger,
    command: str,
    result: lldb.SBCommandReturnObject,
    internal_dict: dict,
) -> None:
    try:
        match shlex.split(command):
            case []:
                all_threads = False
            case ["--all"]:
                all_threads = True
            case arguments:
                raise ValueError(
                    f"Unexpected rich-backtrace arguments "
                    f"{arguments!r}; expected no arguments or --all"
                )

        runtime = get_runtime(debugger)
        process = runtime.target.GetProcess()

        if not process.IsValid():
            raise RuntimeError("rich-backtrace requires a launched process")

        if process.GetState() not in (
            lldb.eStateStopped,
            lldb.eStateCrashed,
            lldb.eStateSuspended,
        ):
            raise RuntimeError(
                "rich-backtrace requires a stopped process; "
                f"current LLDB state is {process.GetState()}"
            )

        if all_threads:
            threads = list(process)
        else:
            thread = process.GetSelectedThread()

            if not thread.IsValid():
                raise RuntimeError("rich-backtrace requires a selected thread")

            threads = [thread]

        report = runtime.context.extract_report(
            process,
            threads,
            ReportReason.MANUAL,
        )
        emit_report(
            runtime.logger,
            runtime.settings,
            report,
        )
    except Exception as error:
        result.SetError(f"rich-backtrace failed: {type(error).__name__}: {error}")


def configure_command(
    debugger: lldb.SBDebugger,
    command: str,
    result: lldb.SBCommandReturnObject,
    internal_dict: dict,
) -> None:
    try:
        if command.strip():
            raise ValueError(
                "rich-backtrace-configure does not accept "
                f"arguments, received {command!r}"
            )

        configure(debugger)
    except Exception as error:
        result.SetError(
            f"rich-backtrace-configure failed: {type(error).__name__}: {error}"
        )


def breakpoint_callback(
    frame: lldb.SBFrame,
    location: lldb.SBBreakpointLocation,
    internal_dict: dict,
) -> bool:
    process = frame.GetThread().GetProcess()
    debugger = process.GetTarget().GetDebugger()
    runtime = get_runtime(debugger)

    report = runtime.context.extract_report(
        process,
        [frame.GetThread()],
        ReportReason.BREAKPOINT,
    )

    report_directory = runtime.settings.pytest_backtrace_dir
    report_logger = runtime.logger

    if report_directory is not None:
        report_path = report_directory / f"{process.GetProcessID()}.log"
        report_logger = create_logger(
            f"{runtime.logger.name}.pytest",
            replace(runtime.settings, log_file=report_path),
        )

    try:
        emit_report(
            report_logger,
            runtime.settings,
            report,
        )
    finally:
        if report_logger is not runtime.logger:
            for handler in list(report_logger.handlers):
                report_logger.removeHandler(handler)
                handler.close()

    return not runtime.settings.auto_continue


class FatalSignalStopHook:
    def __init__(
        self,
        target: lldb.SBTarget,
        extra_args: lldb.SBStructuredData,
        internal_dict: dict,
    ) -> None:
        self.debugger = target.GetDebugger()

    def handle_stop(
        self,
        execution: lldb.SBExecutionContext,
        stream: lldb.SBStream,
    ) -> bool:
        runtime = get_runtime(self.debugger)
        process = execution.GetProcess()
        signals = process.GetUnixSignals()
        crashing: list[lldb.SBThread] = []

        for thread in process:
            if thread.GetStopReason() != lldb.eStopReasonSignal:
                continue

            number = thread.GetStopReasonDataAtIndex(0)
            name = signals.GetSignalAsCString(number)

            if name in runtime.settings.fatal_signals:
                crashing.append(thread)

        if not crashing:
            return True

        identifier = process.GetUniqueID()

        if identifier not in runtime.fatal_processes:
            report = runtime.context.extract_report(
                process,
                crashing,
                ReportReason.SIGNAL,
            )
            emit_report(
                runtime.logger,
                runtime.settings,
                report,
            )
            runtime.fatal_processes.add(identifier)

        return not runtime.settings.auto_continue


def install(debugger: lldb.SBDebugger) -> None:
    execute_command(
        debugger,
        f"command script add -f {__name__}.trace_command rich-backtrace",
    )
    execute_command(
        debugger,
        f"command script add -f {__name__}.configure_command rich-backtrace-configure",
    )
