from datetime import datetime
from pathlib import Path

from beartype import beartype
from beartype.typing import Any
from beartype.typing import Dict
from beartype.typing import List
from beartype.typing import Optional
from beartype.typing import Union
import py_scriptutils.json_utils as ju
from rich.console import Console
from rich.table import Table
from sqlalchemy import Boolean
from sqlalchemy import Column
from sqlalchemy import create_engine
from sqlalchemy import DateTime
from sqlalchemy import Engine
from sqlalchemy import ForeignKey
from sqlalchemy import inspect
from sqlalchemy import Integer
from sqlalchemy import MetaData
from sqlalchemy import String
from sqlalchemy import Table as SATable
from sqlalchemy.orm import Session
from sqlalchemy.orm import sessionmaker
from sqlalchemy.sql import Executable
from sqlalchemy.sql import select
from sqlalchemy.types import TypeDecorator


def IdColumn() -> Column:
    return Column(Integer, primary_key=True, autoincrement=True)


def ForeignId(name: str, nullable: bool = False) -> Column:
    return Column(Integer, ForeignKey(name), nullable=nullable)


def IntColumn(nullable: bool = False) -> Column:
    return Column(Integer, nullable=nullable)


def BoolColumn(nullable: bool = False) -> Column:
    return Column(Boolean, nullable=nullable)


def StrColumn(nullable: bool = False) -> Column:
    return Column(String, nullable=nullable)


def DateTimeColumn(**kwargs: Any) -> Column:
    return Column(DateTime, **kwargs)


class MillisecondsUnixTimestamp(TypeDecorator):
    """Converts between Unix timestamp in milliseconds and Python datetime objects."""
    impl = Integer

    def process_bind_param(self, value: Any, dialect: Any) -> Any:
        """Convert Python datetime to Unix timestamp in milliseconds."""
        if value is not None:
            return int(value.timestamp() * 1000)
        return value

    def process_result_value(self, value: Any, dialect: Any) -> Any:
        """Convert Unix timestamp in milliseconds to Python datetime."""
        if value is not None:
            return datetime.fromtimestamp(value / 1000.0)
        return value


class NumericEnum(TypeDecorator):
    """
    Enables passing in a Python enum and storing the enum's *value* in the db.
    The default would have stored the enum's *name* (ie the string).
    """

    impl = Integer

    def __init__(self, enumtype: Any, *args: Any, **kwargs: Any) -> None:
        super(NumericEnum, self).__init__(*args, **kwargs)
        self._enumtype = enumtype

    def process_bind_param(self, value: Any, dialect: Any) -> Any:
        if isinstance(value, int):
            return value

        return value.value

    def process_result_value(self, value: Any, dialect: Any) -> Any:
        return self._enumtype(value)


@beartype
def format_rich_table(
    engine: Engine,
    table_name: str,
    excluded_columns: List[str] = [],
    style: bool = True,
) -> Table:
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

    rich_table = Table(
        show_header=True,
        header_style="bold blue" if style else None,
    )

    for column in columns_to_fetch:
        rich_table.add_column(str(column.name),
                              no_wrap=True,
                              overflow="ignore",
                              width=None,
                              min_width=None,
                              max_width=None)

    for row in result:

        def get_cell(it: Any) -> str:
            text = str(it)
            if text.strip() == str(it):
                return text
            else:
                return f"\"{text}\""

        rich_table.add_row(*[get_cell(it) for it in row])

    return rich_table


@beartype
def _map_engine_or_session(engine_or_session: Engine | Session) -> Engine:
    if isinstance(engine_or_session, Session):
        return engine_or_session.get_bind()  # type: ignore

    else:
        return engine_or_session


@beartype
def format_rich_query(
    engine_or_session: Union[Engine, Session],
    query: Executable,
    column_labels: List[str] = [],
) -> Table:

    engine = _map_engine_or_session(engine_or_session)

    rich_table = Table(show_header=True, header_style="bold blue")
    with engine.connect() as connection:
        result = connection.execute(query)
        if not column_labels:
            column_labels = result.keys()  # type: ignore
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
    engine_or_session: Union[Engine, Session],
    excluded_tables: List[str] = [],
    ignored_columns: dict[str, List[str]] = {},
    style: bool = True,
) -> str:

    engine = _map_engine_or_session(engine_or_session)

    def st(text: str, wrap: str) -> str:
        if style:
            return f"[{wrap}]{text}[/{wrap}]"

        else:
            return text

    ignored_columns = ignored_columns or {}
    console = Console(
        no_color=not style,
        force_terminal=style,
        width=999999999,
    )
    with console.capture() as capture:
        tables = get_table_names(engine, excluded_tables)
        for table_name in tables:

            table_content = format_rich_table(
                engine,
                table_name,
                ignored_columns.get(table_name, []),
                style=style,
            )

            if table_content.row_count == 0:
                console.print(
                    "Table: {table_name} {size}{empty}".format(
                        table_name=st(str(table_name), "bold magenta"),
                        size=st("Size:", "white"),
                        empty=st("empty", "red"),
                    ),
                    style="bold underline" if style else None,
                )

            else:
                console.print(
                    "Table: {table_name} {size}{count}".format(
                        table_name=st(str(table_name), "bold magenta"),
                        size=st("Size:", "white"),
                        count=table_content.row_count,
                    ),
                    style="bold underline" if style else None,
                )

                console.print(table_content)

    return capture.get()


@beartype
def dump_flat_table(
    engine_or_session: Union[Engine, Session],
    table_name: str,
    excluded_columns: List[str] = [],
    dict_primary_key: Optional[str] = None,
) -> ju.Json:
    metadata = MetaData()
    engine = _map_engine_or_session(engine_or_session)

    table = SATable(table_name, metadata, autoload_with=engine)
    columns_to_fetch = [c for c in table.columns if c.name not in excluded_columns]

    with engine.connect() as connection:
        if dict_primary_key is None:
            table_list: List[Dict] = []
            selection = connection.execute(select(*columns_to_fetch))
            for row in selection:
                table_list.append({c.name: r for c, r in zip(columns_to_fetch, row)})

            return table_list

        else:
            table_dict: Dict[Any, Dict] = {}
            selection = connection.execute(select(*columns_to_fetch))
            for row in selection:
                row_dict = {}
                for c, r in zip(columns_to_fetch, row):
                    if c.name != dict_primary_key:
                        row_dict[c.name] = r

                key_value = [
                    r for c, r in zip(columns_to_fetch, row) if c.name == dict_primary_key
                ]

                assert len(key_value) == 1

                table_dict[key_value[0]] = row_dict

            return table_dict


@beartype
def dump_db_all(
    engine_or_session: Union[Engine, Session],
    excluded_tables: List[str] = [],
    excluded_columns: Dict[str, List[str]] = {},
) -> ju.Json:
    engine = _map_engine_or_session(engine_or_session)

    result = dict()
    for table_name in get_table_names(engine, excluded_tables):
        result[table_name] = dump_flat_table(engine, table_name,
                                             excluded_columns.get(table_name, []))

    return result


@beartype
def open_sqlite(file: Path, base: Any = None) -> Engine:
    engine = create_engine("sqlite:///" + str(file))
    if base:
        base.metadata.create_all(engine)

    return engine


@beartype
def open_sqlite_session(file: Union[Path, Engine], base: Any = None) -> Session:
    if isinstance(file, Engine):
        return sessionmaker()(bind=file)

    else:
        engine = open_sqlite(file, base)
        return sessionmaker()(bind=engine)
