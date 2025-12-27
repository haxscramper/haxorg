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
def generate_symbol_size_report(ctx: TaskContext) -> None:
    assert ctx.config.binary_size_conf.report_path, "Missing report path for binary symbol size"
    assert ctx.config.binary_size_conf.output_db
    session = open_sqlite_session(Path(ctx.config.binary_size_conf.output_db), Base)

    query = (session.query(BinarySymbol, DemangledHead).join(
        DemangledHead, BinarySymbol.DemangledHeadId == DemangledHead.Id).order_by(
            DemangledHead.Id, BinarySymbol.Size.desc()))

    grouped_symbols: dict[int, list[tuple[BinarySymbol, DemangledHead]]] = {}
    for symbol, head in query:
        if head.Id not in grouped_symbols:
            grouped_symbols[head.Id] = []
        grouped_symbols[head.Id].append((symbol, head))

    sorted_groups = sorted(grouped_symbols.items(),
                           key=lambda item: sum(symbol.Size for symbol, _ in item[1]),
                           reverse=True)

    with open(ctx.config.binary_size_conf.report_path, "w") as f:
        for head_id, symbols_and_heads in sorted_groups:
            head = symbols_and_heads[0][1]
            symbols = [s for s, _ in symbols_and_heads]

            total_size = sum(symbol.Size for symbol in symbols)
            average_size = total_size / len(symbols)

            f.write(f"ID:{head_id} KIND:{head.Kind}\n")
            for line in json.dumps(head.Fields, indent=2).split("\n"):
                f.write(f"  {line}\n")
            f.write(f"  total_size = {total_size}\n")
            f.write(f"  average_size = {average_size}\n")

            for symbol in symbols:
                f.write(f"  {symbol.Size}")
                if symbol.File and symbol.Line:
                    f.write(f" \"{symbol.File}\":{symbol.Line}")

                f.write(f" {symbol.Demangled}\n")
                    
