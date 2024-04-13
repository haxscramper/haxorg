from sqlalchemy import Column, Integer, String, ForeignKey, DateTime, Boolean
from sqlalchemy import create_engine, MetaData, Table as SATable, Engine, inspect
from sqlalchemy.orm import Session, sessionmaker
from sqlalchemy.sql import select, Executable
from sqlalchemy.types import TypeDecorator
from rich.table import Table
from rich.console import Console
from beartype.typing import Optional, List
from beartype import beartype
from pathlib import Path
from datetime import datetime


def IdColumn():
    return Column(Integer, primary_key=True, autoincrement=True)


def ForeignId(name: str, nullable: bool = False):
    return Column(Integer, ForeignKey(name), nullable=nullable)


def IntColumn(nullable: bool = False):
    return Column(Integer, nullable=nullable)

def BoolColumn(nullable: bool = False):
    return Column(Boolean, nullable=nullable)


def StrColumn(nullable: bool = False):
    return Column(String, nullable=nullable)


def DateTimeColumn(**kwargs):
    return Column(DateTime, **kwargs)

class MillisecondsUnixTimestamp(TypeDecorator):
    """Converts between Unix timestamp in milliseconds and Python datetime objects."""
    impl = Integer

    def process_bind_param(self, value, dialect):
        """Convert Python datetime to Unix timestamp in milliseconds."""
        if value is not None:
            return int(value.timestamp() * 1000)
        return value

    def process_result_value(self, value, dialect):
        """Convert Unix timestamp in milliseconds to Python datetime."""
        if value is not None:
            return datetime.fromtimestamp(value / 1000.0)
        return value


@beartype
def format_rich_table(engine: Engine,
                      table_name: str,
                      excluded_columns: List[str] = []) -> Table:
    """
    Fetches a table from the database and returns a rich Table object.

    :param engine: SQLAlchemy engine connected to the database.
    :param table_name: Name of the table to fetch.
    :param excluded_columns: Optional list of column names to ignore.
    :return: A rich Table object.
    """

    metadata = MetaData()
    table = SATable(table_name, metadata, autoload_with=engine)

    columns_to_fetch = [c for c in table.columns if c.name not in excluded_columns]

    with engine.connect() as connection:
        result = connection.execute(select(*columns_to_fetch))

    rich_table = Table(show_header=True, header_style="bold blue")

    for column in columns_to_fetch:
        rich_table.add_column(str(column.name))

    for row in result:
        rich_table.add_row(*[str(it) for it in row])

    return rich_table


@beartype
def format_rich_query(
    engine: Engine,
    query: Executable,
    column_labels: List[str] = [],
) -> Table:
    
    rich_table = Table(show_header=True, header_style="bold blue")
    with engine.connect() as connection:
        result = connection.execute(query)
        if not column_labels:
            column_labels = result.keys()
        for label in column_labels:
            rich_table.add_column(label)
        for row in result:
            rich_table.add_row(*[str(item) for item in row])
    return rich_table


@beartype
def get_table_names(engine: Engine, excluded_tables: List[str] = []) -> List[str]:
    """
    Retrieves all table names from the database connected to the given engine,
    with an option to exclude specific tables.
    """
    excluded_tables = excluded_tables or []
    tables = [
        table for table in inspect(engine).get_table_names()
        if table not in excluded_tables
    ]
    return tables


@beartype
def format_db_all(
    engine: Engine,
    excluded_tables: List[str] = [],
    ignored_columns: dict[str, List[str]] = {},
    style: bool = True,
) -> str:

    ignored_columns = ignored_columns or {}
    console = Console(no_color=not style)
    with console.capture() as capture:
        tables = get_table_names(engine, excluded_tables)
        for table_name in tables:

            table_content = format_rich_table(engine, table_name,
                                              ignored_columns.get(table_name, []))

            if table_content.row_count == 0:
                console.print(
                    f"Table: [bold magenta]{table_name}[/bold magenta] [white]Size:[/white][red]empty[/red]",
                    style="bold underline" if style else None,
                )

            else:
                console.print(
                    f"Table: [bold magenta]{table_name}[/bold magenta] [white]Size:[/white]{table_content.row_count}",
                    style="bold underline" if style else None,
                )

                console.print(table_content)

    return capture.get()


@beartype
def open_sqlite(file: Path, base = None) -> Engine:
    engine = create_engine("sqlite:///" + str(file))
    if base:
        base.metadata.create_all(engine)

    return engine

@beartype
def open_sqlite_session(file: Path, base = None) -> Session:
    engine = open_sqlite(file, base)
    return sessionmaker()(bind=engine)
