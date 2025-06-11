#!/usr/bin/env python

import logging
import sys
from datetime import datetime
from typing import Any, List, Optional

from PyQt6.QtCore import QAbstractItemModel, QModelIndex, Qt, pyqtSignal
from PyQt6.QtGui import QStandardItemModel
from PyQt6.QtWidgets import (QApplication, QHeaderView, QLineEdit, QTreeView, QVBoxLayout,
                             QWidget)
from fuzzywuzzy import fuzz

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class TreeNode:

    def __init__(self, data: Any, parent: Optional["TreeNode"] = None):
        self.data = data
        self.parent = parent
        self.children: List["TreeNode"] = []
        self._build_children()

    def _build_children(self) -> None:
        try:
            for sub in self.data:
                kind = sub.getKind()
                if hasattr(kind, "name") and kind.name in ["Document", "Subtree"]:
                    child_node = TreeNode(sub, self)
                    self.children.append(child_node)
        except (TypeError, AttributeError):
            pass

    def get_title(self) -> str:
        try:
            if hasattr(self.data, "getTitle"):
                return self.data.getTitle() or "Untitled"
            return "Root"
        except (AttributeError, TypeError):
            return "Unknown"

    def get_todo(self) -> str:
        try:
            if hasattr(self.data, "getTodo"):
                todo = self.data.getTodo()
                return todo if todo else ""
            return ""
        except (AttributeError, TypeError):
            return ""

    def get_level(self) -> int:
        try:
            if hasattr(self.data, "getLevel"):
                return self.data.getLevel()
            return 0
        except (AttributeError, TypeError):
            return 0

    def get_creation_date(self) -> str:
        try:
            if hasattr(self.data, "getCreationDate"):
                date = self.data.getCreationDate()
                return date.strftime("%Y-%m-%d %H:%M") if date else ""
            return ""
        except (AttributeError, TypeError):
            return ""

    def is_closed(self) -> bool:
        try:
            if hasattr(self.data, "isClosed"):
                return self.data.isClosed()
            return False
        except (AttributeError, TypeError):
            return False

    def get_kind(self) -> str:
        try:
            kind = self.data.getKind()
            return kind.name if hasattr(kind, "name") else str(kind)
        except (AttributeError, TypeError):
            return "Unknown"


class OrgTreeModel(QAbstractItemModel):

    def __init__(self, root_node: TreeNode):
        super().__init__()
        self.root_node = root_node
        self.filtered_nodes: List[TreeNode] = []
        self.filter_text = ""
        self._build_filtered_list()

    def _build_filtered_list(self) -> None:
        self.filtered_nodes = []
        self._collect_nodes(self.root_node)

    def _collect_nodes(self, node: TreeNode) -> None:
        if node != self.root_node:
            if not self.filter_text or self._matches_filter(node):
                self.filtered_nodes.append(node)

        for child in node.children:
            self._collect_nodes(child)

    def _matches_filter(self, node: TreeNode) -> bool:
        if not self.filter_text:
            return True
        title = node.get_title().lower()
        filter_lower = self.filter_text.lower()
        return fuzz.partial_ratio(filter_lower, title) >= 60

    def set_filter(self, text: str) -> None:
        self.beginResetModel()
        self.filter_text = text
        self._build_filtered_list()
        self.endResetModel()

    def index(self, row: int, column: int,
              parent: QModelIndex = QModelIndex()) -> QModelIndex:
        if not self.hasIndex(row, column, parent):
            return QModelIndex()

        if not parent.isValid():
            if row < len(self.filtered_nodes):
                return self.createIndex(row, column, self.filtered_nodes[row])
        else:
            parent_node = parent.internalPointer()
            if row < len(parent_node.children):
                child_node = parent_node.children[row]
                if not self.filter_text or self._matches_filter(child_node):
                    return self.createIndex(row, column, child_node)

        return QModelIndex()

    def parent(self, index: QModelIndex) -> QModelIndex:
        if not index.isValid():
            return QModelIndex()

        node = index.internalPointer()
        parent_node = node.parent

        if parent_node is None or parent_node == self.root_node:
            return QModelIndex()

        if parent_node.parent == self.root_node:
            try:
                row = self.filtered_nodes.index(parent_node)
                return self.createIndex(row, 0, parent_node)
            except ValueError:
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
        if not parent.isValid():
            return len(self.filtered_nodes)

        node = parent.internalPointer()
        visible_children = [
            child for child in node.children
            if not self.filter_text or self._matches_filter(child)
        ]
        return len(visible_children)

    def columnCount(self, parent: QModelIndex = QModelIndex()) -> int:
        return 5

    def data(self, index: QModelIndex, role: int = Qt.ItemDataRole.DisplayRole) -> Any:
        if not index.isValid():
            return None

        node = index.internalPointer()
        column = index.column()

        if role == Qt.ItemDataRole.DisplayRole:
            if column == 0:
                return node.get_title()
            elif column == 1:
                return node.get_kind()
            elif column == 2:
                return node.get_todo()
            elif column == 3:
                return node.get_creation_date()
            elif column == 4:
                return "Closed" if node.is_closed() else "Open"

        return None

    def headerData(self,
                   section: int,
                   orientation: Qt.Orientation,
                   role: int = Qt.ItemDataRole.DisplayRole) -> Any:
        if orientation == Qt.Orientation.Horizontal and role == Qt.ItemDataRole.DisplayRole:
            headers = ["Title", "Kind", "Todo", "Creation Date", "Status"]
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

        self.search_box = QLineEdit()
        self.search_box.setPlaceholderText("Search subtree titles...")
        self.search_box.textChanged.connect(self.on_search_changed)
        layout.addWidget(self.search_box)

        self.tree_view = QTreeView()
        self.tree_view.setModel(self.model)
        self.tree_view.setAlternatingRowColors(True)
        self.tree_view.setSortingEnabled(True)

        header = self.tree_view.header()
        header.setSectionResizeMode(0, QHeaderView.ResizeMode.ResizeToContents)
        header.setSectionResizeMode(1, QHeaderView.ResizeMode.ResizeToContents)
        header.setSectionResizeMode(2, QHeaderView.ResizeMode.ResizeToContents)
        header.setSectionResizeMode(3, QHeaderView.ResizeMode.ResizeToContents)
        header.setSectionResizeMode(4, QHeaderView.ResizeMode.ResizeToContents)

        layout.addWidget(self.tree_view)
        self.setLayout(layout)

        self.setWindowTitle("Org Agenda")
        self.resize(800, 600)

    def on_search_changed(self, text: str) -> None:
        self.model.set_filter(text)
        if text:
            self.tree_view.expandAll()


def show_agenda_table(node: Any) -> None:
    app = QApplication.instance()
    if app is None:
        app = QApplication(sys.argv)

    root_tree_node = TreeNode(node)
    widget = AgendaWidget(root_tree_node)
    widget.show()

    if app:
        app.exec()
