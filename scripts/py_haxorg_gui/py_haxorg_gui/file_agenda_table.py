#!/usr/bin/env python

import logging
import sys
from datetime import datetime
from beartype import beartype
from beartype.typing import Any, List, Optional, Iterator, Tuple, Dict
import functools
from fractions import Fraction
from enum import Enum
import math
import difflib
import json

from PyQt6.QtCore import QAbstractItemModel, QModelIndex, Qt, pyqtSignal, QMargins, QSortFilterProxyModel
from PyQt6.QtGui import QStandardItemModel, QColor
from PyQt6.QtGui import QFont, QShortcut, QKeySequence

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
    QListWidgetItem,
    QDialog,
    QListWidget,
)

from fuzzywuzzy import fuzz
import rich_click as click
import py_haxorg.pyhaxorg_wrap as org
from py_haxorg.pyhaxorg_utils import evalDateTime, getFlatTags
from pathlib import Path
from py_scriptutils.script_logging import log, pprint_to_file, to_debug_json

CAT = __name__

COMPLETED_TASK_SET = set(["DONE", "FAILED", "COMPLETED", "CANCELED"])
AGENDA_NODE_TYPES = [
    org.OrgSemKind.Subtree,
    org.OrgSemKind.Document,
    org.OrgSemKind.Directory,
    org.OrgSemKind.File,
    org.OrgSemKind.Symlink,
]


@beartype
class TreeNode:

    def __init__(self,
                 data: org.Org,
                 parent: Optional["TreeNode"] = None,
                 children: List["TreeNode"] = []):
        assert data.getKind() in AGENDA_NODE_TYPES
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
        assert other.data.getKind() in AGENDA_NODE_TYPES
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

        elif isinstance(self.data, org.File):
            return self.data.relPath

        elif isinstance(self.data, org.Directory):
            return self.data.relPath

        else:
            return str(self.data.getKind())

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
        if sub.getKind() in AGENDA_NODE_TYPES:
            added = build_node(sub, result)
            completion = added.get_recursive_completion()
            if completion[1] != 0:
                result.push_back(added)

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

            completion = node.get_recursive_completion()
            if self.hide_completed_tasks and node.get_todo() in COMPLETED_TASK_SET and (
                    self.hide_nested or len(node.children) == 0) or (completion[0]
                                                                     == completion[1]):
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


class CommandPaletteItem:

    def __init__(self, title: str, full_path: str, model_index: QModelIndex):
        self.title = title
        self.full_path = full_path
        self.model_index = model_index
        self.score = 0.0


class CommandPalette(QDialog):
    item_selected = pyqtSignal(QModelIndex)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.items: List[CommandPaletteItem] = []
        self.filtered_items: List[CommandPaletteItem] = []
        self.setup_ui()
        self.setWindowFlags(Qt.WindowType.FramelessWindowHint | Qt.WindowType.Popup)

    def setup_ui(self):
        self.setWindowTitle("Go to Item")
        self.setModal(True)
        self.resize(600, 400)

        layout = QVBoxLayout(self)
        layout.setContentsMargins(10, 10, 10, 10)

        # Search input
        self.search_input = QLineEdit()
        self.search_input.setPlaceholderText("Type to search items...")
        self.search_input.textChanged.connect(self.on_search_changed)
        layout.addWidget(self.search_input)

        # Results list
        self.results_list = QListWidget()
        self.results_list.itemActivated.connect(self.on_item_activated)
        self.results_list.setVerticalScrollBarPolicy(
            Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.results_list.setHorizontalScrollBarPolicy(
            Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        layout.addWidget(self.results_list)

        # Set focus to search input
        self.search_input.setFocus()

    def position_over_parent(self):
        if self.parent():
            parent_rect = self.parent().geometry()
            palette_width = int(parent_rect.width() * 0.6)
            x = parent_rect.x() + (parent_rect.width() - palette_width) // 2
            y = parent_rect.y() + 50  # 50px from top
            self.setGeometry(x, y, palette_width, 400)

    def keyPressEvent(self, event):
        key = event.key()

        if key == Qt.Key.Key_Escape:
            self.reject()
        elif key == Qt.Key.Key_Return or key == Qt.Key.Key_Enter:
            self.select_current_item()
        elif key == Qt.Key.Key_Down:
            self.move_selection(1)
        elif key == Qt.Key.Key_Up:
            self.move_selection(-1)
        else:
            # Pass other keys to search input
            if not self.search_input.hasFocus():
                self.search_input.setFocus()
            super().keyPressEvent(event)

    def move_selection(self, direction: int):
        current_row = self.results_list.currentRow()
        new_row = current_row + direction

        if 0 <= new_row < self.results_list.count():
            self.results_list.setCurrentRow(new_row)

    def select_current_item(self):
        current_item = self.results_list.currentItem()
        if current_item:
            self.on_item_activated(current_item)

    def on_item_activated(self, item: QListWidgetItem):
        item_data = item.data(Qt.ItemDataRole.UserRole)
        if item_data:
            self.item_selected.emit(item_data.model_index)
            self.accept()

    def populate_items(self, model, proxy_model=None):
        """Extract all items from the tree model"""
        self.items.clear()
        self._extract_items_recursive(model, QModelIndex(), [], proxy_model)
        self.filtered_items = self.items.copy()
        self.update_results_list()

    def _extract_items_recursive(self,
                                 model,
                                 parent_index: QModelIndex,
                                 path: List[str],
                                 proxy_model=None):
        """Recursively extract all items from the model"""
        row_count = model.rowCount(parent_index)

        for row in range(row_count):
            index = model.index(row, 0, parent_index)
            if not index.isValid():
                continue

            # Get the title
            title = model.data(index, Qt.ItemDataRole.DisplayRole) or ""
            current_path = path + [title]
            full_path = " > ".join(current_path)

            # Map to proxy model index if needed
            display_index = index
            if proxy_model:
                display_index = proxy_model.mapFromSource(index)

            # Add item
            item = CommandPaletteItem(title, full_path, display_index)
            self.items.append(item)

            # Recurse into children
            self._extract_items_recursive(model, index, current_path, proxy_model)

    def on_search_changed(self, text: str):
        """Filter and sort items based on search text"""
        if not text.strip():
            self.filtered_items = self.items.copy()
        else:
            self.filtered_items = self._filter_and_score_items(text.lower())

        self.update_results_list()

    def _filter_and_score_items(self, search_text: str) -> List[CommandPaletteItem]:
        """Filter items and calculate similarity scores"""
        scored_items = []

        for item in self.items:
            score = self._calculate_score(item, search_text)
            if score > 0:
                item.score = score
                scored_items.append(item)

        # Sort by score (descending) and then by path length (ascending)
        scored_items.sort(key=lambda x: (-x.score, len(x.full_path)))
        return scored_items

    def _calculate_score(self, item: CommandPaletteItem, search_text: str) -> float:
        """Calculate similarity score for an item"""
        title_lower = item.title.lower()
        path_lower = item.full_path.lower()

        # Exact match gets highest score
        if search_text == title_lower:
            return 100.0

        # Title starts with search text
        if title_lower.startswith(search_text):
            return 90.0

        # Title contains search text
        if search_text in title_lower:
            return 80.0

        # Full path contains search text
        if search_text in path_lower:
            return 70.0

        # Fuzzy matching using difflib
        title_ratio = difflib.SequenceMatcher(None, search_text, title_lower).ratio()
        path_ratio = difflib.SequenceMatcher(None, search_text, path_lower).ratio()

        # Use the better of title or path ratio
        fuzzy_score = max(title_ratio, path_ratio) * 60.0

        # Only include items with decent fuzzy match
        return fuzzy_score if fuzzy_score > 20.0 else 0.0

    def update_results_list(self):
        """Update the results list widget"""
        self.results_list.clear()

        for item in self.filtered_items:
            list_item = QListWidgetItem()

            # Set main text (full path)
            list_item.setText(item.full_path)

            # Store the item data
            list_item.setData(Qt.ItemDataRole.UserRole, item)

            # Highlight exact matches
            if hasattr(self, 'search_input') and self.search_input.text().strip():
                search_text = self.search_input.text().lower()
                if search_text in item.title.lower():
                    font = list_item.font()
                    font.setBold(True)
                    list_item.setFont(font)

            self.results_list.addItem(list_item)

        # Select first item if available
        if self.results_list.count() > 0:
            self.results_list.setCurrentRow(0)


class TreeViewWithCommandPalette:

    def __init__(self, tree_view, model, proxy_model=None):
        self.tree_view = tree_view
        self.model = model
        self.proxy_model = proxy_model
        self.command_palette = None

        # Setup Ctrl+P shortcut
        self.shortcut = QShortcut(QKeySequence("Ctrl+P"), tree_view)
        self.shortcut.activated.connect(self.show_command_palette)

    def show_command_palette(self):
        """Show the command palette dialog"""
        if self.command_palette is None:
            self.command_palette = CommandPalette(self.tree_view)
            self.command_palette.item_selected.connect(self.on_item_selected)

        # Populate with current model data
        source_model = self.proxy_model.sourceModel() if self.proxy_model else self.model
        self.command_palette.populate_items(source_model, self.proxy_model)

        # Show dialog
        self.command_palette.position_over_parent()
        self.command_palette.exec()
        self.command_palette.raise_()
        self.command_palette.activateWindow()

    def on_item_selected(self, model_index: QModelIndex):
        """Handle item selection from command palette"""
        if model_index.isValid():
            # Scroll to and select the item
            self.tree_view.scrollTo(model_index)
            self.tree_view.setCurrentIndex(model_index)

            # Expand parent items if necessary
            parent = model_index.parent()
            while parent.isValid():
                self.tree_view.expand(parent)
                parent = parent.parent()

            # Ensure the item is visible and selected
            self.tree_view.scrollTo(model_index)
            self.tree_view.setFocus()


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

        self.command_palette_handler = TreeViewWithCommandPalette(
            self.tree_view, self.model, self.sort_model)

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


import traceback


def get_org_file_times(infile: Path) -> Dict[str, float]:
    current_times: Dict[str, float] = {}
    for org_file in infile.glob("*.org"):
        current_times[str(org_file)] = org_file.stat().st_mtime
    return current_times

def check_org_files_changed(infile: Path, cache_file: Path) -> bool:
    current_times = get_org_file_times(infile)

    if not cache_file.exists():
        return True

    with open(cache_file, "r") as f:
        cached_times: Dict[str, float] = json.load(f)

    return current_times != cached_times

def write_org_file_cache(infile: Path, cache_file: Path) -> None:
    current_times = get_org_file_times(infile)
    
    with open(cache_file, "w") as f:
        json.dump(current_times, f)

@click.command()
@click.option("--infile",
              type=click.Path(exists=True, path_type=Path),
              required=True,
              help="Path to input .org file")
def main(infile: Path) -> None:
    dir_opts = org.OrgDirectoryParseParameters()
    parse_opts = org.OrgParseParameters()
    stack_file = open("/tmp/stack_dumps.txt", "w")

    graph_path = Path("/tmp/immutable_graph_dump.bin")
    context_path = Path("/tmp/immutable_ast_dump.bin")
    epoch_path = Path("/tmp/immutable_epoch_dump.bin")
    cache_file = Path("/tmp/file_agenda_cache.org_files_cache.json")

    if check_org_files_changed(infile, cache_file):
        def parse_node_impl(path: str):
            try:
                return org.parseStringOpts(Path(path).read_text(), parse_opts)

            except Exception as e:
                print(f"Parsing {path}", file=stack_file)
                traceback.print_exc(file=stack_file)
                # log(CAT).info(f"Failed parsing {path}", exc_info=e, stack_info=True, )
                return org.Empty()

        org.setGetParsedNode(dir_opts, parse_node_impl)

        node = org.parseDirectoryOpts(str(infile), dir_opts)
        initial_context = org.initImmutableAstContext()
        log(CAT).info("Adding immutable AST root")
        version = initial_context.addRoot(node)

        graph_state: org.graphMapGraphState = org.graphMapGraphState.FromAstContextStatic(
            version.getContext())

        conf = org.graphMapConfig()
        root = version.getRootAdapter()

        log(CAT).info("Recursively adding graph state node")
        graph_state.addNodeRec(version.getContext(), root, conf)

        log(CAT).info("Serialize graph state to binary")
        graph_path.write_bytes(org.serializeMapGraphToText(graph_state.graph))
        log(CAT).info("Serialize context to binary")
        context_path.write_bytes(org.serializeAstContextToText(version.getContext()))
        epoch_path.write_bytes(org.serializeAstReplaceEpochToText(version.getEpoch()))
        write_org_file_cache(infile, cache_file)

    else:
        initial_context: org.ImmAstContext = org.initImmutableAstContext()
        org.serializeAstContextFromText(context_path.read_bytes(), initial_context)
        version: org.ImmAstVersion = initial_context.getEmptyVersion()
        org.serializeAstReplaceEpochFromText(epoch_path.read_bytes(), version.getEpoch())
        node = initial_context.get(version.getRoot())

        graph_state: org.graphMapGraphState = org.graphMapGraphState.FromAstContextStatic(
            version.getContext())

        org.serializeMapGraphFromText(graph_path.read_bytes(), graph_state.graph)

    log(CAT).info("File parsing done")
    show_agenda_table(node)


if __name__ == "__main__":
    main()
