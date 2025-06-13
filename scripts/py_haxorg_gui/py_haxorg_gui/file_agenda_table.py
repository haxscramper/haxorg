#!/usr/bin/env python

import logging
import sys
from datetime import datetime
from beartype import beartype
from beartype.typing import Any, List, Optional, Iterator, Tuple
import functools
from fractions import Fraction
from enum import Enum
import math

from PyQt6.QtCore import QAbstractItemModel, QModelIndex, Qt, pyqtSignal, QMargins, QSortFilterProxyModel
from PyQt6.QtGui import QStandardItemModel, QColor
from PyQt6.QtGui import QFont

from PyQt6.QtWidgets import (
    QApplication,
    QHeaderView,
    QLineEdit,
    QTreeView,
    QVBoxLayout,
    QWidget,
    QCheckBox,
    QFormLayout,
    QPushButton,
)

from fuzzywuzzy import fuzz
import rich_click as click
import py_haxorg.pyhaxorg_wrap as org
from py_haxorg.pyhaxorg_utils import evalDateTime, getFlatTags
from pathlib import Path
from py_scriptutils.script_logging import log, pprint_to_file, to_debug_json

CAT = __name__

COMPLETED_TASK_SET = set(["DONE", "FAILED", "COMPLETED", "CANCELED"])


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

    @functools.cache
    def get_priority(self) -> str:
        if isinstance(self.data, org.Subtree):
            return self.data.priority or ""

        else:
            return ""

    @functools.cache
    def get_clocked_seconds(self) -> int:
        result = 0

        def aux(node: TreeNode):
            nonlocal result
            if isinstance(node.data, org.Subtree):
                time: org.SubtreePeriod
                for time in node.data.getTimePeriods(
                        org.IntSetOfSubtreePeriodKind([org.SubtreePeriodKind.Clocked])):
                    if time.to and time.from_:
                        from_ = evalDateTime(time.from_)
                        to = evalDateTime(time.to)
                        result += (to - from_).seconds

            for sub in node.children:
                aux(sub)

        aux(self)

        return result

    @functools.cache
    def get_recursive_completion(self) -> Tuple[int, int]:
        nom = 0
        denom = 0

        def aux(node: TreeNode):
            nonlocal nom
            nonlocal denom
            if node.get_todo() != "":
                if node.get_todo() in COMPLETED_TASK_SET:
                    nom += 1
                    denom += 1

                else:
                    denom += 1

            for sub in node.children:
                aux(sub)

        aux(self)

        return (nom, denom)

    @functools.cache
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

    @functools.cache
    def get_tags(self) -> List[str]:
        if isinstance(self.data, org.Subtree):
            result = []
            for tag in self.data.tags:
                for flat in getFlatTags(tag):
                    result.append("##".join(flat))

            return result

        else:
            return []

    @functools.cache
    def get_age_seconds(self) -> int:
        if isinstance(self.data, org.Subtree):
            created: List[org.SubtreePeriod] = self.data.getTimePeriods(
                org.IntSetOfSubtreePeriodKind([org.SubtreePeriodKind.Created]))
            if created:
                return int(
                    (datetime.now() - evalDateTime(created[0].from_)).total_seconds())

        return 0

    @functools.cache
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

    @functools.cache
    def get_title(self) -> str:
        if isinstance(self.data, org.Subtree):
            return self.data.getCleanTitle()

        else:
            return ""

    @functools.cache
    def get_todo(self) -> str:
        if isinstance(self.data, org.Subtree):
            return self.data.todo or ""

        else:
            return ""

    @functools.cache
    def get_level(self) -> int:
        try:
            if hasattr(self.data, "getLevel"):
                return self.data.getLevel()
            return 0
        except (AttributeError, TypeError):
            return 0

    @functools.cache
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


class TableColumns(Enum):
    TITLE = 0
    COMPLETION = 1
    PRIORITY_INDEX = 2
    TODO_INDEX = 3
    CREATION_DATE = 4
    CLOCKED = 5
    TASK_AGE = 6
    TAGS = 7

    def getName(self) -> str:
        return {
            TableColumns.TITLE: "title",
            TableColumns.COMPLETION: "[/]",
            TableColumns.PRIORITY_INDEX: "[#]",
            TableColumns.TODO_INDEX: "todo",
            TableColumns.CREATION_DATE: "created",
            TableColumns.CLOCKED: "clocked",
            TableColumns.TAGS: "tags",
            TableColumns.TASK_AGE: "age",
        }[self]


class OrgTreeModel(QAbstractItemModel):

    def __init__(self, root_node: TreeNode):
        super().__init__()
        self.focused = None
        self.root_node = root_node
        self.sort_column = 0
        self.sort_order = Qt.SortOrder.AscendingOrder
        self.flat_nodes: List[TreeNode] = []
        self.set_flat_list_from(self.root_node)

    def getRoot(self) -> TreeNode:
        if self.focused:
            return self.focused

        else:
            return self.root_node

    def setFocused(self, node: Optional[TreeNode]):
        self.beginResetModel()
        self.focused = node
        self.set_flat_list_from(self.getRoot())
        self.endResetModel()
        log(CAT).info("Set focused row done")

    def set_flat_list_from(self, node: TreeNode) -> None:
        self.flat_nodes = []

        def collect_all_nodes(node: TreeNode) -> None:
            if node != self.getRoot():
                self.flat_nodes.append(node)
            for child in node.children:
                collect_all_nodes(child)

        collect_all_nodes(node)

    def is_flat_sorting(self) -> bool:
        return self.sort_column != TableColumns.TITLE.value

    def index(self, row: int, column: int,
              parent: QModelIndex = QModelIndex()) -> QModelIndex:
        if not self.hasIndex(row, column, parent):
            return QModelIndex()

        if self.is_flat_sorting():
            if not parent.isValid() and row < len(self.flat_nodes):
                return self.createIndex(row, column, self.flat_nodes[row])
            return QModelIndex()
        else:
            if not parent.isValid():
                if row < len(self.getRoot().children):
                    return self.createIndex(row, column, self.getRoot().children[row])
            else:
                parent_node = parent.internalPointer()
                if row < len(parent_node.children):
                    child_node = parent_node.children[row]
                    return self.createIndex(row, column, child_node)

        return QModelIndex()

    def parent(self, index: QModelIndex) -> QModelIndex:
        if not index.isValid() or self.is_flat_sorting():
            return QModelIndex()

        node: TreeNode = index.internalPointer()
        parent_node = node.parent

        if parent_node is None or parent_node == self.getRoot():
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
        if self.is_flat_sorting():
            if not parent.isValid():
                return len(self.flat_nodes)
            return 0
        else:
            if not parent.isValid():
                return len(self.getRoot().children)
            node: TreeNode = parent.internalPointer()
            return len(node.children)

    def columnCount(self, parent: QModelIndex = QModelIndex()) -> int:
        return len(TableColumns)

    def data(self, index: QModelIndex, role: int = Qt.ItemDataRole.DisplayRole) -> Any:
        if not index.isValid():
            return None

        node: TreeNode = index.internalPointer()
        column = index.column()

        if role == Qt.ItemDataRole.DisplayRole:
            if column == TableColumns.TITLE.value:
                return node.get_title()
            elif column == TableColumns.PRIORITY_INDEX.value:
                return node.get_priority()
            elif column == TableColumns.TODO_INDEX.value:
                return node.get_todo()
            elif column == TableColumns.CREATION_DATE.value:
                return node.get_creation_date()
            elif column == TableColumns.TASK_AGE.value:
                return node.get_age_display()
            elif column == TableColumns.TAGS.value:
                return ", ".join(node.get_tags())
            elif column == TableColumns.COMPLETION.value:
                a, b = node.get_recursive_completion()
                return f"{a}/{b}"

            elif column == TableColumns.CLOCKED.value:
                sec = node.get_clocked_seconds()
                hours = math.floor(sec / (60 * 60))
                minutes = math.floor((sec / 60) % 60)
                return f"{hours}:{minutes}"

        elif role == Qt.ItemDataRole.BackgroundRole and column == TableColumns.PRIORITY_INDEX.value:
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

        elif role == Qt.ItemDataRole.FontRole and column == TableColumns.PRIORITY_INDEX.value:
            priority = node.get_priority()
            font = QFont()
            if priority == "A":
                font.setBold(True)
                font.setUnderline(True)
            elif priority in ["E", "F"]:
                font.setWeight(QFont.Weight.Light)
            return font if priority in ["A", "E", "F"] else None

        elif role == Qt.ItemDataRole.BackgroundRole and column == TableColumns.TODO_INDEX.value:
            todo = node.get_todo().lower()
            if todo in ["done", "completed"]:
                return QColor(144, 238, 144)
            elif todo in ["wip", "next"]:
                return QColor(255, 165, 0)
            elif todo == "todo":
                return QColor(255, 182, 193)

        elif role == Qt.ItemDataRole.BackgroundRole and column == TableColumns.TASK_AGE.value:
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

    def headerData(
        self,
        section: int,
        orientation: Qt.Orientation,
        role: int = Qt.ItemDataRole.DisplayRole,
    ) -> Any:
        if orientation == Qt.Orientation.Horizontal and role == Qt.ItemDataRole.DisplayRole:
            headers = [h.getName() for h in TableColumns]
            if section < len(headers):
                return headers[section]

        elif orientation == Qt.Orientation.Vertical and role == Qt.ItemDataRole.DisplayRole:
            if self.is_flat_mode():
                return str(section)
            else:
                return str(section)

        return None


class OrgTreeProxyModel(QSortFilterProxyModel):

    def __init__(self, parent, model: OrgTreeModel):
        super().__init__(parent)
        self.model = model
        self.setSortRole(Qt.ItemDataRole.DisplayRole)
        self.hide_tasks_without_todo_on_flat = False
        self.hide_completed_tasks = False
        self.hide_nested = False

        if model:
            model.modelReset.connect(self.invalidateFilter)

    def sort(self, column: int, order):
        self.model.sort_column = column
        self.model.sort_order = order

        self.invalidate()
        if column != TableColumns.TITLE.value:
            super().sort(column, order)

        self.invalidateFilter()

    def filterAcceptsRow(self, source_row: int, source_parent: QModelIndex) -> bool:
        if self.model.is_flat_sorting():
            node = self.model.flat_nodes[source_row]
            if self.hide_completed_tasks and node.get_todo() in COMPLETED_TASK_SET:
                return False

            if self.hide_tasks_without_todo_on_flat and node.get_todo() == "":
                return False

            return True

        else:

            # Get the node at this row
            if source_parent.isValid():
                parent_node: TreeNode = source_parent.internalPointer()
                if source_row < len(parent_node.children):
                    node = parent_node.children[source_row]
                else:
                    return True
            else:
                if source_row < len(self.model.getRoot().children):
                    node = self.model.getRoot().children[source_row]
                else:
                    return True

            if self.hide_completed_tasks and node.get_todo() in COMPLETED_TASK_SET and (
                    self.hide_nested or len(node.children) == 0):
                return False

            if self.hide_tasks_without_todo_on_flat and node.get_todo() == "" and (
                    self.hide_nested or len(node.children) == 0):
                return False

            return True  # TODO Later this logic will have filters for tree repr as well

    def lessThan(self, left: QModelIndex, right: QModelIndex) -> bool:
        column = left.column()
        is_ascending = self.model.sort_order == Qt.SortOrder.AscendingOrder
        if self.model.is_flat_sorting():
            left_node: TreeNode = left.internalPointer()
            right_node: TreeNode = right.internalPointer()

            def early_empty_result(left_empty: bool, right_empty: bool) -> Optional[bool]:
                # Both have zero age - maintain stable order
                if left_empty and right_empty:
                    return False

                # Left has zero age - put at bottom (return False for ascending, True for descending)
                if left_empty:
                    return not is_ascending  # Left is "greater" so goes to bottom

                # Right has zero age - put at bottom (return True for ascending, False for descending)
                if right_empty:
                    return is_ascending  # Right is "greater" so goes to bottom

            def compare_with_empty_handling(left_value, right_value, empty_value):
                early = early_empty_result(left_value == empty_value,
                                           right_value == empty_value)
                if early is not None:
                    return early
                return left_value < right_value

            if column == TableColumns.PRIORITY_INDEX.value:
                return compare_with_empty_handling(left_node.get_priority_order(),
                                                   right_node.get_priority_order(), -1)

            elif column == TableColumns.TAGS.value:
                return compare_with_empty_handling(left_node.get_tags(),
                                                   right_node.get_tags(), 0)

            elif column == TableColumns.TODO_INDEX.value:
                return compare_with_empty_handling(left_node.get_todo(),
                                                   right_node.get_todo(), "")

            elif column == TableColumns.CLOCKED.value:
                return compare_with_empty_handling(left_node.get_clocked_seconds(),
                                                   right_node.get_clocked_seconds(), 0)

            elif column == TableColumns.CREATION_DATE.value:
                return compare_with_empty_handling(left_node.get_creation_date(),
                                                   right_node.get_creation_date(), "")

            elif column == TableColumns.TASK_AGE.value:
                return compare_with_empty_handling(left_node.get_age_seconds(),
                                                   right_node.get_age_seconds(), 0)

            else:
                return super().lessThan(left, right)

        else:
            return super().lessThan(left, right)


class AgendaWidget(QWidget):

    def __init__(self, root_node: TreeNode):
        super().__init__()
        self.model = OrgTreeModel(root_node)
        self.setup_ui()

    def on_model_reset(self) -> None:
        if not self.model.is_flat_sorting():
            self.tree_view.expandAll()

    def on_focus_lifted(self) -> None:
        self.model.setFocused(None)

    def on_row_focused(self, index: QModelIndex) -> None:
        if not index.isValid():
            return

        if index.model() == self.sort_model:
            source_index = self.sort_model.mapToSource(index)
            node = source_index.internalPointer()

        else:
            node = source_index.internalPointer()

        log(CAT).info("Focusing on node")
        self.model.setFocused(node)

    def setup_ui(self) -> None:
        layout = QVBoxLayout()

        self.tree_view = QTreeView()
        self.sort_model = OrgTreeProxyModel(self, self.model)
        self.sort_model.setSourceModel(self.model)
        self.tree_view.setModel(self.sort_model)
        self.tree_view.setAlternatingRowColors(True)
        self.tree_view.setSortingEnabled(True)
        self.tree_view.model().modelReset.connect(self.on_model_reset)

        self.tree_view.doubleClicked.connect(self.on_row_focused)

        header = self.tree_view.header()
        for h in TableColumns:
            header.setSectionResizeMode(h.value, QHeaderView.ResizeMode.ResizeToContents)

        configuration_layout = QFormLayout()
        configuration_layout.setContentsMargins(0, 0, 0, 0)
        configuration_widget = QWidget()
        configuration_widget.setContentsMargins(0, 0, 0, 0)
        configuration_widget.setLayout(configuration_layout)

        hide_tasks_without_todo_on_flat = QCheckBox()
        hide_tasks_without_todo_on_flat.setText("Hide tasks without todo")
        hide_tasks_without_todo_on_flat.toggled.connect(
            self.on_hide_tasks_without_todo_on_flat_changed)
        hide_tasks_without_todo_on_flat.setToolTip(
            "If enabled, flat sorting operations (priority, todo, creation date, task age etc.) "
            "will not show the rows that have no creation date.")
        configuration_layout.addWidget(hide_tasks_without_todo_on_flat)

        hide_completed_task = QCheckBox()
        hide_completed_task.setText("Hide completed tasks")
        hide_completed_task.toggled.connect(self.on_hide_completed_tasks)
        configuration_layout.addWidget(hide_completed_task)

        hide_nested = QCheckBox()
        hide_nested.setText("Hide nested")
        hide_nested.toggled.connect(self.on_hide_nested)
        configuration_layout.addWidget(hide_nested)

        unfocus = QPushButton()
        unfocus.setText("Unfocus")
        unfocus.clicked.connect(self.on_focus_lifted)
        configuration_layout.addWidget(unfocus)

        layout.addWidget(self.tree_view)
        layout.addWidget(configuration_widget)
        self.setLayout(layout)

        self.setWindowTitle("Org Agenda")
        # self.showMaximized()
        self.resize(1400, 600)
        self.tree_view.expandAll()

    def on_hide_completed_tasks(self, state: bool) -> None:
        self.sort_model.hide_completed_tasks = state
        self.sort_model.invalidate()

    def on_hide_tasks_without_todo_on_flat_changed(self, state: bool) -> None:
        self.sort_model.hide_tasks_without_todo_on_flat = state
        self.sort_model.invalidate()

    def on_hide_nested(self, state: bool) -> None:
        self.sort_model.hide_nested = state
        self.sort_model.invalidate()
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
