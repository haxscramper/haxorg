#!/usr/bin/env python

import logging
import sys
from datetime import datetime
from beartype import beartype
from beartype.typing import Any, List, Optional, Iterator

from PyQt6.QtCore import QAbstractItemModel, QModelIndex, Qt, pyqtSignal
from PyQt6.QtGui import QStandardItemModel, QColor
from PyQt6.QtGui import QFont
from PyQt6.QtWidgets import (QApplication, QHeaderView, QLineEdit, QTreeView, QVBoxLayout,
                             QWidget)
from fuzzywuzzy import fuzz
import rich_click as click
import py_haxorg.pyhaxorg_wrap as org
from py_haxorg.pyhaxorg_utils import evalDateTime, getFlatTags
from pathlib import Path
from py_scriptutils.script_logging import log, pprint_to_file, to_debug_json

CAT = __name__


@beartype
class TreeNode:

    def __init__(self,
                 data: org.Org,
                 parent: Optional["TreeNode"] = None,
                 children: List["TreeNode"] = []):
        assert data.getKind() in [org.OrgSemKind.Subtree, org.OrgSemKind.Document]
        self.data = data
        self.parent = parent
        if not children:
            children = list()

        self.children: List["TreeNode"] = children

    def get_priority(self) -> str:
        if isinstance(self.data, org.Subtree):
            return self.data.priority or ""

        else:
            return ""

    def get_priority_order(self) -> int:
        priority = self.get_priority()
        priority_order = {
            "X": 0,
            "S": 1,
            "A": 2,
            "B": 3,
            "C": 4,
            "D": 5,
            "E": 6,
            "F": 7,
        }
        return priority_order.get(priority, -1)

    def get_tags(self) -> List[str]:
        if isinstance(self.data, org.Subtree):
            result = []
            for tag in self.data.tags:
                for flat in getFlatTags(tag):
                    result.append("##".join(flat))

            return result

        else:
            return []

    def get_age_seconds(self) -> int:
        if isinstance(self.data, org.Subtree):
            created: List[org.SubtreePeriod] = self.data.getTimePeriods(
                org.IntSetOfSubtreePeriodKind([org.SubtreePeriodKind.Created]))
            if created:
                return int(
                    (datetime.now() - evalDateTime(created[0].from_)).total_seconds())

        return 0

    def get_age_display(self) -> str:
        seconds = self.get_age_seconds()

        if seconds == 0:
            return ""

        units = [
            ("y", 365 * 24 * 3600),
            ("mo", 30 * 24 * 3600),
            ("w", 7 * 24 * 3600),
            ("d", 24 * 3600),
            ("h", 3600),
            ("m", 60),
            ("s", 1),
        ]

        parts = []
        for unit_name, unit_seconds in units:
            if seconds >= unit_seconds:
                count = seconds // unit_seconds
                parts.append(f"{count}{unit_name}")
                seconds %= unit_seconds
                if len(parts) == 2:
                    break

        return "".join(parts) if parts else "0s"

    def push_back(self, other: "TreeNode"):
        assert other.data.getKind() in [org.OrgSemKind.Subtree, org.OrgSemKind.Document]
        self.children.append(other)

    def __iter__(self) -> Iterator["TreeNode"]:
        return self.children.__iter__()

    def __getitem__(self, idx: int) -> "TreeNode":
        return self.children[idx]

    def __len__(self) -> int:
        return len(self.children)

    def get_title(self) -> str:
        if isinstance(self.data, org.Subtree):
            return self.data.getCleanTitle()

        else:
            return ""

    def get_todo(self) -> str:
        if isinstance(self.data, org.Subtree):
            return self.data.todo or ""

        else:
            return ""

    def get_level(self) -> int:
        try:
            if hasattr(self.data, "getLevel"):
                return self.data.getLevel()
            return 0
        except (AttributeError, TypeError):
            return 0

    def get_creation_date(self) -> str:
        if isinstance(self.data, org.Subtree):
            created: List[org.SubtreePeriod] = self.data.getTimePeriods(
                org.IntSetOfSubtreePeriodKind([org.SubtreePeriodKind.Created]))
            if created:
                return evalDateTime(created[0].from_).strftime("%Y-%m-%d %H:%M")

        return ""

    def is_closed(self) -> bool:
        try:
            if hasattr(self.data, "isClosed"):
                return self.data.isClosed()
            return False
        except (AttributeError, TypeError):
            return False

    def get_kind(self) -> org.OrgSemKind:
        return self.data.getKind()


def build_node(node: org.Org, parent: Optional[TreeNode]) -> TreeNode:
    result = TreeNode(data=node, parent=parent)
    for sub in node:
        if sub.getKind() in [org.OrgSemKind.Subtree, org.OrgSemKind.Document]:
            result.push_back(build_node(sub, result))

    return result


COLUMN_TITLE = 0
COLUMN_PRIORITY_INDEX = 1
COLUMN_TODO_INDEX = 2
COLUMN_CREATION_DATE = 3
COLUMN_TASK_AGE = 4
COLUMN_TAGS = 5


class OrgTreeModel(QAbstractItemModel):

    def __init__(self, root_node: TreeNode):
        super().__init__()
        self.root_node = root_node
        self.sort_column = -1
        self.sort_order = Qt.SortOrder.AscendingOrder
        self.flat_nodes: List[TreeNode] = []
        self._build_flat_list()

    def _build_flat_list(self) -> None:
        self.flat_nodes = []

        def collect_all_nodes(node: TreeNode) -> None:
            if node != self.root_node:
                self.flat_nodes.append(node)
            for child in node.children:
                collect_all_nodes(child)

        collect_all_nodes(self.root_node)

    def _is_flat_mode(self) -> bool:
        return self.sort_column != COLUMN_TITLE

    def sort(self, column: int, order: Qt.SortOrder) -> None:
        self.beginResetModel()
        self.sort_column = column
        self.sort_order = order

        is_ascending = order == Qt.SortOrder.AscendingOrder

        if self._is_flat_mode():
            key_func = None
            if column == COLUMN_PRIORITY_INDEX:

                def key_func(node: TreeNode) -> int:
                    priority_ord = node.get_priority_order()
                    if priority_ord == -1:
                        if is_ascending:
                            return 10E10

                        else:
                            return -1

                    else:
                        if is_ascending:
                            return priority_ord

                        else:
                            return -priority_ord

                self.flat_nodes.sort(key=key_func)

            elif column == COLUMN_TAGS:
                key_func = lambda node: node.get_tags()
                self.flat_nodes.sort(key=key_func, reverse=not is_ascending)

            elif column == COLUMN_TODO_INDEX:
                key_func = lambda node: node.get_todo().lower()
                self.flat_nodes.sort(key=key_func, reverse=not is_ascending)
            elif column == COLUMN_CREATION_DATE:
                key_func = lambda node: (node.get_creation_date() == "",
                                         node.get_creation_date())
                self.flat_nodes.sort(key=key_func, reverse=not is_ascending)

            elif column == COLUMN_TASK_AGE:

                def key_func_3(node: TreeNode) -> tuple:
                    age = node.get_age_seconds()
                    if age == 0:
                        if is_ascending:
                            return 10E10

                        else:
                            return -1

                    else:
                        if is_ascending:
                            return age
                        else:
                            return -age

                self.flat_nodes.sort(key=key_func_3)

        self.endResetModel()

    def index(self, row: int, column: int,
              parent: QModelIndex = QModelIndex()) -> QModelIndex:
        if not self.hasIndex(row, column, parent):
            return QModelIndex()

        if self._is_flat_mode():
            if not parent.isValid() and row < len(self.flat_nodes):
                return self.createIndex(row, column, self.flat_nodes[row])
            return QModelIndex()
        else:
            if not parent.isValid():
                if row < len(self.root_node.children):
                    return self.createIndex(row, column, self.root_node.children[row])
            else:
                parent_node = parent.internalPointer()
                if row < len(parent_node.children):
                    child_node = parent_node.children[row]
                    return self.createIndex(row, column, child_node)

        return QModelIndex()

    def parent(self, index: QModelIndex) -> QModelIndex:
        if not index.isValid() or self._is_flat_mode():
            return QModelIndex()

        node: TreeNode = index.internalPointer()
        parent_node = node.parent

        if parent_node is None or parent_node == self.root_node:
            return QModelIndex()

        grandparent = parent_node.parent
        if grandparent:
            try:
                row = grandparent.children.index(parent_node)
                return self.createIndex(row, 0, parent_node)
            except ValueError:
                return QModelIndex()

        return QModelIndex()

    def rowCount(self, parent: QModelIndex = QModelIndex()) -> int:
        if self._is_flat_mode():
            if not parent.isValid():
                return len(self.flat_nodes)
            return 0
        else:
            if not parent.isValid():
                return len(self.root_node.children)
            node: TreeNode = parent.internalPointer()
            return len(node.children)

    def columnCount(self, parent: QModelIndex = QModelIndex()) -> int:
        return 6

    def data(self, index: QModelIndex, role: int = Qt.ItemDataRole.DisplayRole) -> Any:
        if not index.isValid():
            return None

        node: TreeNode = index.internalPointer()
        column = index.column()

        if role == Qt.ItemDataRole.DisplayRole:
            if column == COLUMN_TITLE:
                return node.get_title()
            elif column == COLUMN_PRIORITY_INDEX:
                return node.get_priority()
            elif column == COLUMN_TODO_INDEX:
                return node.get_todo()
            elif column == COLUMN_CREATION_DATE:
                return node.get_creation_date()
            elif column == COLUMN_TASK_AGE:
                return node.get_age_display()
            elif column == COLUMN_TAGS:
                return ", ".join(node.get_tags())

        elif role == Qt.ItemDataRole.BackgroundRole and column == COLUMN_PRIORITY_INDEX:
            priority = node.get_priority()
            colors = {
                "X": QColor(255, 0, 0),
                "S": QColor(253, 95, 240),
                "A": QColor(240, 223, 175),
                "B": QColor(253, 151, 31),
                "C": QColor(102, 217, 239),
                "D": QColor(161, 239, 228),
                "E": QColor(166, 226, 46),
                "F": QColor(174, 129, 255)
            }
            return colors.get(priority)

        elif role == Qt.ItemDataRole.FontRole and column == COLUMN_PRIORITY_INDEX:
            priority = node.get_priority()
            font = QFont()
            if priority == "A":
                font.setBold(True)
                font.setUnderline(True)
            elif priority in ["E", "F"]:
                font.setWeight(QFont.Weight.Light)
            return font if priority in ["A", "E", "F"] else None

        elif role == Qt.ItemDataRole.BackgroundRole and column == COLUMN_TODO_INDEX:
            todo = node.get_todo().lower()
            if todo in ["done", "completed"]:
                return QColor(144, 238, 144)
            elif todo in ["wip", "next"]:
                return QColor(255, 165, 0)
            elif todo == "todo":
                return QColor(255, 182, 193)

        elif role == Qt.ItemDataRole.BackgroundRole and column == COLUMN_TASK_AGE:
            age_seconds = node.get_age_seconds()
            if age_seconds == 0:
                return None
            elif age_seconds <= 24 * 3600:  # <=1 day
                return QColor(200, 255, 200)
            elif age_seconds <= 7 * 24 * 3600:  # <=1 week
                return QColor(255, 255, 200)
            elif age_seconds <= 30 * 24 * 3600:  # <=1 month
                return QColor(255, 220, 200)
            else:  # 1 month+
                return QColor(255, 200, 200)

        return None

    def headerData(self,
                   section: int,
                   orientation: Qt.Orientation,
                   role: int = Qt.ItemDataRole.DisplayRole) -> Any:
        if orientation == Qt.Orientation.Horizontal and role == Qt.ItemDataRole.DisplayRole:
            headers = ["Title", "Priority", "Todo", "Creation Date", "Task age", "Tags"]
            if section < len(headers):
                return headers[section]
        return None


class AgendaWidget(QWidget):

    def __init__(self, root_node: TreeNode):
        super().__init__()
        self.model = OrgTreeModel(root_node)
        self.setup_ui()

    def setup_ui(self) -> None:
        layout = QVBoxLayout()

        self.tree_view = QTreeView()
        self.tree_view.setModel(self.model)
        self.tree_view.setAlternatingRowColors(True)
        self.tree_view.setSortingEnabled(True)
        self.tree_view.model().modelReset.connect(self.on_model_reset)

        header = self.tree_view.header()
        header.setSectionResizeMode(0, QHeaderView.ResizeMode.ResizeToContents)
        header.setSectionResizeMode(1, QHeaderView.ResizeMode.ResizeToContents)
        header.setSectionResizeMode(2, QHeaderView.ResizeMode.ResizeToContents)
        header.setSectionResizeMode(3, QHeaderView.ResizeMode.ResizeToContents)

        layout.addWidget(self.tree_view)
        self.setLayout(layout)

        self.setWindowTitle("Org Agenda")
        # self.showMaximized()
        self.resize(1400, 600)
        self.tree_view.expandAll()

    def on_model_reset(self) -> None:
        if not self.model._is_flat_mode():
            self.tree_view.expandAll()


def show_agenda_table(node: org.Org) -> None:
    app = QApplication.instance()
    if app is None:
        app = QApplication(sys.argv)

    root_tree_node = build_node(node, None)

    def override_node(n: Any):
        if isinstance(n, org.Org):
            return str(n.getKind())

    pprint_to_file(
        to_debug_json(
            root_tree_node,
            override_callback=override_node,
        ),
        "/tmp/debug_tree.py",
    )

    widget = AgendaWidget(root_tree_node)
    widget.show()

    if app:
        app.exec()


@click.command()
@click.option("--infile",
              type=click.Path(exists=True, path_type=Path),
              required=True,
              help="Path to input .org file")
def main(infile: Path) -> None:
    node = org.parseFile(str(infile), org.OrgParseParameters())
    log(CAT).info("File parsing done")
    show_agenda_table(node)


if __name__ == "__main__":
    main()
