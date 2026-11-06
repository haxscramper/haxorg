import sqlite3
from contextlib import contextmanager
from datetime import datetime
from pathlib import Path

import hstd_py_lib.json_utils as ju
import pandas as pd
from beartype import beartype
from beartype.typing import Any, Dict, Iterator, List, Mapping, Optional, Union
from hstd_py_lib.external_packages.rich_utils import (
    dict_of_tables_to_group,
    render_rich,
    use_colored_repr,
)
from rich.table import Table
from sqlalchemy import (
    URL,
    Boolean,
    Column,
    DateTime,
    Engine,
    ForeignKey,
    Integer,
    MetaData,
    String,
    create_engine,
    inspect,
    text,
)
from sqlalchemy import (
    Table as SATable,
)
from sqlalchemy.orm import Session, sessionmaker
from sqlalchemy.sql import Executable, select
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

        return value.Value

    def process_result_value(self, value: Any, dialect: Any) -> Any:
        return self._enumtype(value)


@beartype
def format_rich_table(
    engine: Engine,
    table_name: str,
    excluded_columns: List[str] = [],
    style: bool = use_colored_repr(),
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
        rich_table.add_column(
            str(column.name),
            no_wrap=True,
            overflow="ignore",
            width=None,
            min_width=None,
            max_width=None,
        )

    for row in result:

        def get_cell(it: Any) -> str:
            text = str(it)
            if text.strip() == str(it):
                return text
            else:
                return f'"{text}"'

        rich_table.add_row(*[get_cell(it) for it in row])

    return rich_table


@beartype
def _map_engine_or_session(engine_or_session: Engine | Session | Path) -> Engine:
    match engine_or_session:
        case Session():
            return engine_or_session.get_bind()  # type: ignore

        case Engine():
            return engine_or_session

        case Path():
            return create_engine(
                URL.create(
                    drivername="sqlite",
                    database=str(engine_or_session.resolve()),
                )
            )


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
        table
        for table in inspect(engine).get_table_names()
        if table not in excluded_tables
    ]
    return tables


@beartype
def format_db_all(
    engine_or_session: Union[Engine, Session, Path],
    excluded_tables: List[str] = [],
    ignored_columns: dict[str, List[str]] = {},
    style: bool = use_colored_repr(),
) -> str:

    engine = _map_engine_or_session(engine_or_session)
    ignored_columns = ignored_columns or {}
    tables = get_table_names(engine, excluded_tables)

    return render_rich(
        dict_of_tables_to_group(
            {
                name: format_rich_table(
                    engine,
                    name,
                    ignored_columns.get(name, []),
                    style=style,
                )
                for name in tables
            }
        )
    )


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
                table_list.append({c.Name: r for c, r in zip(columns_to_fetch, row)})

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
        result[table_name] = dump_flat_table(
            engine, table_name, excluded_columns.get(table_name, [])
        )

    return result


@beartype
def open_sqlite(file: Path, base: Any = None) -> Engine:
    engine = create_engine("sqlite:///" + str(file))
    if base:
        base.metadata.create_all(engine)

    return engine


@contextmanager
@beartype
def database_engine_scope(
    database_path: str | Path,
    read_only: bool = False,
) -> Iterator[Engine]:
    path = Path(database_path).resolve()

    if read_only:
        uri = path.as_uri() + "?mode=ro"
        engine = create_engine(
            "sqlite+pysqlite://",
            creator=lambda: sqlite3.connect(uri, uri=True),
        )
    else:
        engine = create_engine(URL.create("sqlite+pysqlite", database=str(path)))

    try:
        yield engine
    finally:
        engine.dispose()


@beartype
def open_sqlite_session(file: Union[Path, Engine], base: Any = None) -> Session:
    if isinstance(file, Engine):
        return sessionmaker()(bind=file)

    else:
        engine = open_sqlite(file, base)
        return sessionmaker()(bind=engine)


@beartype
def load_database_as_dataframe_structure(
    database_path: str | Path,
    schema: MetaData,
    *,
    ignored_tables: set[str] = set(),  # noqa
    decode_mapped_types: bool = True,
) -> Mapping[str, pd.DataFrame]:
    """Read typed selections so dataframe cells contain decoded ADT values."""

    import pandas as pd

    with database_engine_scope(database_path, read_only=True) as engine:
        with engine.connect() as connection:
            dataframes = {
                str(table.name): pd.read_sql_query(
                    (
                        select(table)
                        if decode_mapped_types
                        else text(str(select(table).compile(dialect=engine.dialect)))
                    ),
                    connection,
                    coerce_float=False,
                )
                for table in schema.sorted_tables
                if str(table.name) not in ignored_tables
            }

    return dict(**dataframes)
