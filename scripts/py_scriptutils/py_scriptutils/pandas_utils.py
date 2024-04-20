import pandas as pd
from rich.table import Table
from beartype.typing import List
import rich.box
from beartype import beartype
import py_scriptutils.json_utils as ju
from py_scriptutils.rich_utils import render_rich


@beartype
def dataframe_to_rich_table(df: pd.DataFrame, exclude_columns: List[str] = []) -> Table:
    table = Table(show_header=True, header_style="bold magenta")
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


@beartype
def assert_frame(df: pd.DataFrame, subset: ju.Json):
    render = dataframe_to_rich_table(df)
    render.box = rich.box.ASCII
    ju.assert_subset(
        df.to_dict("records"),
        subset,
        message=render_rich(render, color=False),
    )
