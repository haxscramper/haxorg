import pandas as pd
from rich.table import Table
from beartype.typing import List, Dict, Union, Any
import rich.box
from beartype import beartype
import py_scriptutils.json_utils as ju
from py_scriptutils.rich_utils import render_rich
from py_scriptutils.script_logging import to_debug_json


@beartype
def dataframe_to_rich_table(
    df: pd.DataFrame,
    exclude_columns: List[str] = [],
    show_lines: bool = False,
) -> Table:
    table = Table(
        show_header=True,
        header_style="bold magenta",
        show_lines=show_lines,
    )
    add_index = "index" not in exclude_columns
    if add_index:
        table.add_column("index")

    for column in df.columns:
        if column not in exclude_columns:
            table.add_column(column)

    for index, row in df.iterrows():
        row_content = []
        if add_index:
            row_content.append(str(index))

        for col in df.columns:
            if col not in exclude_columns:
                row_content.append(str(row[col]))

        table.add_row(*row_content)

    return table


def dataframe_from_dict_list(
    column_names: Union[List[str], pd.DataFrame],
    data_dicts: List[Dict[str, Any]],
) -> pd.DataFrame:
    if isinstance(column_names, pd.DataFrame):
        column_names = column_names.columns.tolist()

    data_prepared = [{col: d.get(col, None) for col in column_names} for d in data_dicts]
    df = pd.DataFrame(data_prepared, columns=column_names)
    return df


@beartype
def assert_frame(df: pd.DataFrame, subset: ju.Json) -> None:
    given_dataframe = dataframe_to_rich_table(df)
    given_dataframe.box = rich.box.ASCII
    df2 = dataframe_from_dict_list(df, subset)
    expected_dataframe = dataframe_to_rich_table(df2)
    expected_dataframe.box = rich.box.ASCII
    ju.assert_subset(
        to_debug_json(df.to_dict("records")),
        subset,
        message="\nGiven dataframe:\n{}\nExpected dataframe:\n{}".format(
            render_rich(given_dataframe, color=False),
            render_rich(expected_dataframe, color=False),
        ),
    )
