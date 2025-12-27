from pathlib import Path
from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Tuple, Type
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import get_build_root, get_script_root
from py_repository.repo_tasks.workflow_utils import TaskContext

from sqlalchemy import create_engine, Column, select, Select
from sqlalchemy.schema import CreateTable
from sqlalchemy.orm import declarative_base, Session
from py_scriptutils.sqlalchemy_utils import IdColumn, ForeignId, IntColumn, StrColumn, BoolColumn, open_sqlite_session
from sqlalchemy.types import JSON
import json
from py_scriptutils.script_logging import log

CAT = __name__

Base: Type = declarative_base()


class BinarySection(Base):
    __tablename__ = "BinarySection"

    Id = IdColumn()
    Name = StrColumn()


class DemangledHead(Base):
    __tablename__ = "DemangledHead"

    Id = IdColumn()
    Kind = IntColumn()
    Fields = Column(JSON)


class DemangledNested(Base):
    __tablename__ = "DemangledNested"

    ComponentIndex = IntColumn()
    Parent = ForeignId("DemangledHead.Id")
    Self = ForeignId("DemangledHead.Id", nullable=True)

    __mapper_args__ = {"primary_key": [ComponentIndex, Parent]}


class BinarySymbol(Base):
    __tablename__ = "BinarySymbol"

    Id = IdColumn()
    Name = StrColumn()
    Demangled = StrColumn()
    DemangledHeadId = ForeignId("DemangledHead.Id")
    Size = IntColumn()
    Address = IntColumn()
    Section = ForeignId("BinarySection.Id")
    File = StrColumn(nullable=True)
    Line = IntColumn(nullable=True)
    Column = IntColumn(nullable=True)
    function = StrColumn(nullable=True)


@beartype
def generate_binary_size_db(ctx: TaskContext) -> None:
    assert ctx.config.binary_size_conf.binary_path, "Missing input binary path for the binary size report"
    assert ctx.config.binary_size_conf.output_db, "Missing output DB for binary size conf"

    args = [
        "--run-mode",
        "BinarySymbols",
        "--out",
        ctx.config.binary_size_conf.output_db,
        "--target-files",
        str(ctx.config.binary_size_conf.binary_path),
    ]

    if ctx.config.binary_size_conf.perf_out:
        args.append("--perf")
        args.append(ctx.config.binary_size_conf.perf_out)

    args.append("--")
    args.append(
        str(get_script_root(ctx,
                            "cxx_codegen/reflection_tool/clang_reflection_tool.cpp")))

    env = dict()

    if ctx.config.binary_size_conf.min_symbol_index:
        env["REFLECTION_TOOL_SYM_MIN"] = str(ctx.config.binary_size_conf.min_symbol_index)

    if ctx.config.binary_size_conf.max_symbol_index:
        env["REFLECTION_TOOL_SYM_MAX"] = str(ctx.config.binary_size_conf.max_symbol_index)

    run_command(
        ctx,
        get_build_root(ctx, "haxorg/scripts/cxx_codegen/reflection_tool/reflection_tool"),
        args,
        env=env,
    )


@beartype
def _generate_symbol_report_impl(
    ctx: TaskContext,
    group_by: str,
    session: Session,
) -> None:
    assert ctx.config.binary_size_conf.report_path, "Missing report path for binary symbol size"
    assert group_by in ["head_id",
                        "file_line"], "group_by must be 'head_id' or 'file_line'"

    query = (session.query(BinarySymbol, DemangledHead).join(
        DemangledHead, BinarySymbol.DemangledHeadId == DemangledHead.Id).order_by(
            DemangledHead.Id, BinarySymbol.Size.desc()))

    # Group symbols based on the specified criteria
    grouped_symbols: dict[Any, List[tuple[BinarySymbol, DemangledHead]]] = {}
    for symbol, head in query:
        if group_by == "head_id":
            key = head.Id
        else:  # file_line
            key = (symbol.File or "", symbol.Line or 0)

        if key not in grouped_symbols:
            grouped_symbols[key] = []
        grouped_symbols[key].append((symbol, head))

    # Sort groups by total size
    sorted_groups = sorted(grouped_symbols.items(),
                           key=lambda item: sum(symbol.Size for symbol, _ in item[1]),
                           reverse=True)

    rep_path = Path(ctx.config.binary_size_conf.report_path)
    rep_path = rep_path.with_stem(f"{rep_path.stem}_{group_by}")
    with open(rep_path, "w") as f:
        for key, symbols_and_heads in sorted_groups:
            symbols = [s for s, _ in symbols_and_heads]
            total_size = sum(symbol.Size for symbol in symbols)
            average_size = total_size / len(symbols)

            # Write group header
            if group_by == "head_id":
                head = symbols_and_heads[0][1]
                f.write(f"ID:{key} KIND:{head.Kind}\n")
                for line in json.dumps(head.Fields, indent=2).split("\n"):
                    f.write(f"  {line}\n")
            else:  # file_line
                file, line = key
                f.write(f"FILE:\"{file}\":{line}\n")

            # Write summary stats
            f.write(f"  total_size = {total_size}\n")
            f.write(f"  average_size = {average_size}\n")

            # Write individual symbols
            for symbol, head in symbols_and_heads:
                f.write(f"  {symbol.Size}")

                if group_by == "head_id":
                    if symbol.File and symbol.Line:
                        f.write(f" \"{symbol.File}\":{symbol.Line}")
                    f.write(f" {symbol.Demangled}\n")
                else:  # file_line
                    f.write(f" ID:{head.Id} KIND:{head.Kind} {symbol.Demangled}\n")

    log(CAT).info(f"Wrote symbol report to {rep_path}")


@beartype
def generate_symbol_size_report(ctx: TaskContext) -> None:
    assert ctx.config.binary_size_conf.output_db
    session = open_sqlite_session(Path(ctx.config.binary_size_conf.output_db), Base)
    _generate_symbol_report_impl(ctx, "head_id", session)
    _generate_symbol_report_impl(ctx, "file_line", session)
