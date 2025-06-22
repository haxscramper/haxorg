#!/usr/bin/env python

from beartype import beartype
from beartype.typing import Any, List, Optional, Iterator, Tuple, Dict
import rich_click as click
import py_haxorg.pyhaxorg_wrap as org
from pathlib import Path
from py_haxorg_gui.shared_org_logic import load_cached_imm_node, OrgAgendaNode, build_genda_tree
from py_scriptutils.script_logging import log
import sys
from datetime import datetime, timedelta, date

from PyQt6.QtCore import Qt, QRect, QTimer
from PyQt6.QtGui import QPainter, QColor, QPen, QBrush, QFont
from PyQt6.QtWidgets import (
    QApplication,
    QVBoxLayout,
    QWidget,
    QTabWidget,
    QLabel,
    QHBoxLayout,
    QPushButton,
    QScrollArea,
)


CAT = __name__

class CalendarEvent:
    def __init__(self, node: "OrgAgendaNode") -> None:
        self.node = node
        self.scheduled = node.get_scheduled_time()
        self.deadline = node.get_deadline_time()
        self.duration = node.get_duration()
        self.clock_periods = node.get_clock_periods()
        self.title = node.get_title()
        
    def get_start_time(self) -> Optional[datetime]:
        return self.scheduled
        
    def get_end_time(self) -> Optional[datetime]:
        if self.deadline:
            return self.deadline
        if self.scheduled and self.duration:
            return self.scheduled + self.duration
        return None
        
    def has_duration(self) -> bool:
        return self.duration is not None or (self.scheduled is not None and self.deadline is not None)
        
    def spans_multiple_days(self) -> bool:
        start = self.get_start_time()
        end = self.get_end_time()
        if not start or not end:
            return False
        return start.date() != end.date()

class WeekView(QWidget):
    def __init__(self, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.current_week_start = self._get_week_start(datetime.now())
        self.events: List[CalendarEvent] = []
        self.hour_height = 60
        self.day_width = 120
        self.header_height = 60
        self.time_column_width = 80
        
    def _get_week_start(self, dt: datetime) -> date:
        days_since_monday = dt.weekday()
        return (dt - timedelta(days=days_since_monday)).date()
        
    def set_agenda_data(self, root_node: "OrgAgendaNode") -> None:
        self.events = []
        self._collect_events(root_node)
        self.update()
        
    def _collect_events(self, node: "OrgAgendaNode") -> None:
        if node.is_event():
            event = CalendarEvent(node)
            if event.get_start_time() or event.get_end_time():
                self.events.append(event)
        
        for child in node:
            self._collect_events(child)
            
    def next_week(self) -> None:
        self.current_week_start += timedelta(days=7)
        self.update()
        
    def prev_week(self) -> None:
        self.current_week_start -= timedelta(days=7)
        self.update()
        
    def _get_week_events(self) -> List[CalendarEvent]:
        week_end = self.current_week_start + timedelta(days=7)
        week_events = []
        
        for event in self.events:
            start_time = event.get_start_time()
            end_time = event.get_end_time()
            
            if start_time and start_time.date() <= week_end and start_time.date() >= self.current_week_start:
                week_events.append(event)
            elif end_time and end_time.date() <= week_end and end_time.date() >= self.current_week_start:
                week_events.append(event)
                
        return week_events
        
    def _get_day_events(self, day_date: date) -> List[CalendarEvent]:
        day_events = []
        for event in self._get_week_events():
            start_time = event.get_start_time()
            end_time = event.get_end_time()
            
            if start_time and start_time.date() == day_date:
                day_events.append(event)
            elif end_time and end_time.date() == day_date and not start_time:
                day_events.append(event)
                
        return day_events
        
    def _calculate_overlaps(self, events: List[CalendarEvent]) -> Dict[CalendarEvent, Tuple[int, int]]:
        overlaps = {}
        
        for i, event in enumerate(events):
            overlapping = []
            event_start = event.get_start_time()
            event_end = event.get_end_time()
            
            if not event_start:
                continue
                
            for j, other in enumerate(events):
                if i == j:
                    continue
                    
                other_start = other.get_start_time()
                other_end = other.get_end_time()
                
                if not other_start:
                    continue
                    
                if event_end and other_end:
                    if not (event_end <= other_start or other_end <= event_start):
                        overlapping.append(other)
                elif event_end:
                    if event_start <= other_start <= event_end:
                        overlapping.append(other)
                elif other_end:
                    if other_start <= event_start <= other_end:
                        overlapping.append(other)
                        
            overlaps[event] = (len(overlapping) + 1, i % (len(overlapping) + 1))
            
        return overlaps
        
    def paintEvent(self, event) -> None:
        painter = QPainter(self)
        painter.fillRect(self.rect(), QColor(255, 255, 255))
        
        self._draw_grid(painter)
        self._draw_headers(painter)
        self._draw_events(painter)
        
    def _draw_grid(self, painter: QPainter) -> None:
        painter.setPen(QPen(QColor(200, 200, 200), 1))
        
        for hour in range(24):
            y = self.header_height + hour * self.hour_height
            painter.drawLine(0, y, self.width(), y)
            
        for day in range(8):
            x = self.time_column_width + day * self.day_width
            painter.drawLine(x, 0, x, self.height())
            
    def _draw_headers(self, painter: QPainter) -> None:
        painter.setPen(QPen(QColor(0, 0, 0), 1))
        painter.setFont(QFont("Arial", 10))
        
        for hour in range(24):
            y = self.header_height + hour * self.hour_height + 15
            painter.drawText(10, y, f"{hour:02d}:00")
            
        days = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]
        for i, day_name in enumerate(days):
            x = self.time_column_width + i * self.day_width + 10
            current_date = self.current_week_start + timedelta(days=i)
            painter.drawText(x, 20, f"{day_name} {current_date.day}")
            
    def _draw_events(self, painter: QPainter) -> None:
        for day in range(7):
            day_date = self.current_week_start + timedelta(days=day)
            day_events = self._get_day_events(day_date)
            overlaps = self._calculate_overlaps(day_events)
            
            for event in day_events:
                self._draw_event(painter, event, day, overlaps.get(event, (1, 0)))
                
    def _draw_event(self, painter: QPainter, event: CalendarEvent, day_index: int, overlap_info: Tuple[int, int]) -> None:
        start_time = event.get_start_time()
        end_time = event.get_end_time()
        
        if not start_time:
            return
            
        day_x = self.time_column_width + day_index * self.day_width
        overlap_count, overlap_index = overlap_info
        event_width = self.day_width // overlap_count
        event_x = day_x + overlap_index * event_width
        
        start_y = self.header_height + start_time.hour * self.hour_height + (start_time.minute * self.hour_height // 60)
        
        if event.has_duration() and end_time:
            if event.spans_multiple_days():
                self._draw_multi_day_event(painter, event, event_x, event_width, start_y, day_index)
            else:
                end_y = self.header_height + end_time.hour * self.hour_height + (end_time.minute * self.hour_height // 60)
                height = end_y - start_y
                
                if event.scheduled and event.deadline:
                    painter.setBrush(QBrush(QColor(100, 150, 255, 100)))
                    painter.setPen(QPen(QColor(0, 100, 200), 3))
                else:
                    painter.setBrush(QBrush(QColor(100, 150, 255)))
                    painter.setPen(QPen(QColor(0, 100, 200), 1))
                    
                painter.drawRect(event_x, start_y, event_width - 2, height)
        else:
            painter.setPen(QPen(QColor(200, 100, 100), 3))
            painter.drawLine(event_x, start_y, event_x + event_width - 2, start_y)
            
        painter.setPen(QPen(QColor(0, 0, 0), 1))
        painter.setFont(QFont("Arial", 8))
        painter.drawText(event_x + 2, start_y + 12, event.title[:15] + ("..." if len(event.title) > 15 else ""))
        
        self._draw_clock_periods(painter, event, event_x, event_width, start_y)
        
    def _draw_multi_day_event(self, painter: QPainter, event: CalendarEvent, x: int, width: int, y: int, day_index: int) -> None:
        start_time = event.get_start_time()
        end_time = event.get_end_time()
        
        if not start_time or not end_time:
            return
            
        current_day = self.current_week_start + timedelta(days=day_index)
        
        painter.setBrush(QBrush(QColor(100, 150, 255)))
        painter.setPen(QPen(QColor(0, 100, 200), 1))
        
        if start_time.date() == current_day:
            height = self.hour_height
            rect = QRect(x, y, width - 2, height)
            painter.drawRect(rect)
            
            painter.setPen(QPen(QColor(0, 0, 0), 1))
            for i in range(0, width - 2, 10):
                painter.drawLine(x + width - 2 - i, y, x + width - 2 - i, y + height)
                
        elif end_time.date() == current_day:
            end_y = self.header_height + end_time.hour * self.hour_height + (end_time.minute * self.hour_height // 60)
            rect = QRect(x, self.header_height, width - 2, end_y - self.header_height)
            painter.drawRect(rect)
            
            painter.setPen(QPen(QColor(0, 0, 0), 1))
            for i in range(0, width - 2, 10):
                painter.drawLine(x + i, self.header_height, x + i, end_y)
                
    def _draw_clock_periods(self, painter: QPainter, event: CalendarEvent, x: int, width: int, y: int) -> None:
        if not event.clock_periods:
            return
            
        painter.setBrush(QBrush(QColor(255, 200, 100)))
        painter.setPen(QPen(QColor(200, 150, 50), 1))
        
        for i, (start, end) in enumerate(event.clock_periods[:3]):
            clock_x = x + width + 2 + i * 15
            clock_y = y
            clock_height = min(30, (end - start).total_seconds() // 60)
            painter.drawRect(clock_x, clock_y, 12, clock_height)
            
    def sizeHint(self):
        return self.size()
        
    def resizeEvent(self, event) -> None:
        super().resizeEvent(event)
        available_width = self.width() - self.time_column_width
        self.day_width = max(100, available_width // 7)

class OrgCalendarView(QWidget):
    def __init__(self, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        
        layout = QVBoxLayout()
        
        nav_layout = QHBoxLayout()
        self.prev_button = QPushButton("← Previous Week")
        self.next_button = QPushButton("Next Week →")
        self.week_label = QLabel()
        
        nav_layout.addWidget(self.prev_button)
        nav_layout.addWidget(self.week_label)
        nav_layout.addWidget(self.next_button)
        
        self.week_view = WeekView()
        
        scroll_area = QScrollArea()
        scroll_area.setWidget(self.week_view)
        scroll_area.setWidgetResizable(True)
        scroll_area.setVerticalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAsNeeded)
        scroll_area.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAsNeeded)
        
        layout.addLayout(nav_layout)
        layout.addWidget(scroll_area)
        
        self.setLayout(layout)
        
        self.prev_button.clicked.connect(self.week_view.prev_week)
        self.next_button.clicked.connect(self.week_view.next_week)
        self.week_view.update = self._on_week_updated
        
        self._update_week_label()
        
    def _on_week_updated(self) -> None:
        QWidget.update(self.week_view)
        self._update_week_label()
        
    def _update_week_label(self) -> None:
        start = self.week_view.current_week_start
        end = start + timedelta(days=6)
        self.week_label.setText(f"Week of {start.strftime('%B %d, %Y')} - {end.strftime('%B %d, %Y')}")
        
    def set_agenda_data(self, root_node: "OrgAgendaNode") -> None:
        self.week_view.set_agenda_data(root_node)
    

class OrgGanttView(QWidget):
    def __init__(self, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        layout = QVBoxLayout()
        layout.addWidget(QLabel("Gantt View Placeholder"))
        self.setLayout(layout)

class OrgFeedView(QWidget):
    def __init__(self, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        layout = QVBoxLayout()
        layout.addWidget(QLabel("Feed View Placeholder"))
        self.setLayout(layout)


class OrgTabWidget(QWidget):
    def __init__(self, node: OrgAgendaNode, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        layout = QVBoxLayout()
        
        tab_widget = QTabWidget()
        
        calendar_view = OrgCalendarView()
        calendar_view.set_agenda_data(node)
        gantt_view = OrgGanttView()
        feed_view = OrgFeedView()
        
        tab_widget.addTab(calendar_view, "Calendar")
        tab_widget.addTab(gantt_view, "Gantt")
        tab_widget.addTab(feed_view, "Feed")
        
        layout.addWidget(tab_widget)
        self.setLayout(layout)


def show_calendar(node: org.Org) -> None:
    app = QApplication.instance()
    if app is None:
        app = QApplication(sys.argv)

    root_tree_node = build_genda_tree(node, None)
    widget = OrgTabWidget(root_tree_node)
    widget.show()
    widget.resize(1200, 600)
    widget.setWindowTitle("Org calendar")

    if app:
        app.exec()

@click.command()
@click.option("--infile",
              type=click.Path(exists=True, path_type=Path),
              required=True,
              help="Path to input .org file")
def main(infile: Path) -> None:
    node = load_cached_imm_node(
        infile=infile,
        graph_path=Path("/tmp/immutable_graph_dump.bin"),
        context_path=Path("/tmp/immutable_ast_dump.bin"),
        epoch_path=Path("/tmp/immutable_epoch_dump.bin"),
        cache_file=Path("/tmp/file_agenda_cache.org_files_cache.json"),
    )
    log(CAT).info("File parsing done")
    show_calendar(node)


if __name__ == "__main__":
    main()
