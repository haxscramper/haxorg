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


COLOR_GRID_LINE = QColor(200, 200, 200)
COLOR_HEADERS = QColor(0, 0, 0)
COLOR_SCHEDULED_EVENT_FILL = QColor(100, 150, 255, 100)
COLOR_SCHEDULED_EVENT_FRAME = QColor(0, 100, 200)

class CalendarEvent:

    def __init__(self,
                 node: OrgAgendaNode,
                 occurrence_date: Optional[datetime] = None) -> None:
        self.node = node
        self.scheduled = occurrence_date or node.get_scheduled_time()
        self.deadline = node.get_deadline_time()
        self.duration = node.get_duration()
        self.clock_periods = node.get_clock_periods()
        self.title = node.get_title()
        self.created = node.get_created_time()
        self.is_event = node.is_event()
        self.level = node.get_level()
        self.repeat = node.get_scheduled_repeat()
        self.parent_event = None
        self.child_events: List["CalendarEvent"] = []

    def get_start_time(self) -> Optional[datetime]:
        return self.scheduled

    def get_end_time(self) -> Optional[datetime]:
        if self.deadline:
            return self.deadline
        if self.scheduled and self.duration:
            return self.scheduled + self.duration
        return None

    def has_duration(self) -> bool:
        return self.duration is not None or (self.scheduled is not None and
                                             self.deadline is not None)

    def spans_multiple_days(self) -> bool:
        start = self.get_start_time()
        end = self.get_end_time()
        if not start or not end:
            return False
        return start.date() != end.date()

    def get_display_time(self) -> Optional[datetime]:
        if self.is_event:
            return self.get_start_time()
        return self.created

    def add_child(self, child: "CalendarEvent") -> None:
        child.parent_event = self
        self.child_events.append(child)


class RepeatCalculator:

    @staticmethod
    def get_occurrences_in_range(event: CalendarEvent, start_date: date,
                                 end_date: date) -> List[datetime]:
        if not event.repeat or not event.scheduled:
            return [event.scheduled
                   ] if event.scheduled and start_date <= event.scheduled.date(
                   ) <= end_date else []

        occurrences = []
        current = event.scheduled

        while current.date() <= end_date:
            if current.date() >= start_date:
                occurrences.append(current)

            current = RepeatCalculator._get_next_occurrence(current, event.repeat)
            if len(occurrences) > 100:
                break

        return occurrences

    @staticmethod
    def _get_next_occurrence(current: datetime, repeat: org.TimeRepeat) -> datetime:
        if repeat.period == org.TimeRepeatPeriod.Day:
            return current + timedelta(days=repeat.count)
        elif repeat.period == org.TimeRepeatPeriod.Week:
            return current + timedelta(weeks=repeat.count)
        elif repeat.period == org.TimeRepeatPeriod.Month:
            month = current.month + repeat.count
            year = current.year + (month - 1) // 12
            month = ((month - 1) % 12) + 1
            try:
                return current.replace(year=year, month=month)
            except ValueError:
                return current.replace(year=year, month=month, day=1) + timedelta(days=30)
        elif repeat.period == org.TimeRepeatPeriod.Year:
            try:
                return current.replace(year=current.year + repeat.count)
            except ValueError:
                return current.replace(year=current.year + repeat.count, month=2, day=28)
        elif repeat.period == org.TimeRepeatPeriod.Hour:
            return current + timedelta(hours=repeat.count)
        elif repeat.period == org.TimeRepeatPeriod.Minute:
            return current + timedelta(minutes=repeat.count)
        return current


class EventLayoutCalculator:

    @staticmethod
    def calculate_layout(events: List[CalendarEvent],
                         day_width: int) -> Dict[CalendarEvent, Tuple[int, int, int]]:
        layout = {}

        EventLayoutCalculator._build_hierarchy(events)

        root_events = [e for e in events if e.parent_event is None]
        overlapping_groups = EventLayoutCalculator._find_overlapping_groups(root_events)

        for group in overlapping_groups:
            EventLayoutCalculator._layout_group(group, day_width, layout, 0)

        return layout

    @staticmethod
    def _build_hierarchy(events: List[CalendarEvent]) -> None:
        for event in events:
            event.parent_event = None
            event.child_events = []

        events_by_level = {}
        for event in events:
            level = event.level
            if level not in events_by_level:
                events_by_level[level] = []
            events_by_level[level].append(event)

        sorted_levels = sorted(events_by_level.keys())

        for i in range(len(sorted_levels) - 1):
            parent_level = sorted_levels[i]
            child_level = sorted_levels[i + 1]

            for parent in events_by_level[parent_level]:
                for child in events_by_level[child_level]:
                    if EventLayoutCalculator._is_time_contained(child, parent):
                        parent.add_child(child)

    @staticmethod
    def _is_time_contained(child: CalendarEvent, parent: CalendarEvent) -> bool:
        child_start = child.get_display_time()
        parent_start = parent.get_display_time()
        parent_end = parent.get_end_time()

        if not child_start or not parent_start:
            return False

        if parent_end:
            return parent_start <= child_start <= parent_end
        else:
            return abs((child_start - parent_start).total_seconds()) < 3600

    @staticmethod
    def _find_overlapping_groups(
            events: List[CalendarEvent]) -> List[List[CalendarEvent]]:
        groups = []
        used = set()

        for event in events:
            if event in used:
                continue

            group = [event]
            used.add(event)

            for other in events:
                if other in used:
                    continue

                if EventLayoutCalculator._events_overlap(event, other):
                    group.append(other)
                    used.add(other)

            groups.append(group)

        return groups

    @staticmethod
    def _events_overlap(event1: CalendarEvent, event2: CalendarEvent) -> bool:
        start1 = event1.get_display_time()
        end1 = event1.get_end_time()
        start2 = event2.get_display_time()
        end2 = event2.get_end_time()

        if not start1 or not start2:
            return False

        if not end1:
            end1 = start1 + timedelta(minutes=30)
        if not end2:
            end2 = start2 + timedelta(minutes=30)

        return not (end1 <= start2 or end2 <= start1)

    @staticmethod
    def _layout_group(events: List[CalendarEvent], day_width: int,
                      layout: Dict[CalendarEvent, Tuple[int, int,
                                                        int]], x_offset: int) -> None:
        if not events:
            return

        event_width = day_width // len(events)

        for i, event in enumerate(events):
            x = x_offset + i * event_width
            width = event_width - 2
            depth = event.level

            layout[event] = (x, width, depth)

            if event.child_events:
                child_x_offset = x + 10
                child_width = width - 20
                EventLayoutCalculator._layout_group(event.child_events, child_width,
                                                    layout, child_x_offset)


class WeekView(QWidget):

    def sizeHint(self):
        return self.minimumSize()

    def resizeEvent(self, event) -> None:
        super().resizeEvent(event)
        if self.parent():
            available_width = self.parent().width() - self.time_column_width - 20
            self.day_width = max(100, available_width // 7)
            self._update_size()


    def __init__(self, parent: Optional[QWidget] = None) -> None:
        assert parent is not None
        log(CAT).info(parent.objectName())
        super().__init__(parent)
        self.current_week_start = self._get_week_start(datetime.now())
        self.events: List[CalendarEvent] = []
        self.base_hour_height = 60
        self.hour_height = 60
        self.day_width = 160
        self.header_height = 60
        self.time_column_width = 80
        self.zoom_factor = 0.3
        self.setMinimumSize(800, 24 * self.hour_height + self.header_height)

    def _get_week_start(self, dt: datetime) -> date:
        days_since_monday = dt.weekday()
        return (dt - timedelta(days=days_since_monday)).date()

    def set_agenda_data(self, root_node: OrgAgendaNode) -> None:
        self.events = []
        self._collect_events(root_node)
        self.update()

    def _collect_events(self, node: OrgAgendaNode) -> None:
        week_start = self.current_week_start
        week_end = week_start + timedelta(days=7)

        if node.is_event():
            scheduled = node.get_scheduled_time()
            if scheduled:
                repeat = node.get_scheduled_repeat()
                if repeat:
                    occurrences = RepeatCalculator.get_occurrences_in_range(
                        CalendarEvent(node), week_start, week_end)
                    for occurrence in occurrences:
                        self.events.append(CalendarEvent(node, occurrence))
                else:
                    if week_start <= scheduled.date() <= week_end:
                        self.events.append(CalendarEvent(node))
        elif node.get_created_time():
            created = node.get_created_time()
            if created and week_start <= created.date() <= week_end:
                self.events.append(CalendarEvent(node))

        for child in node:
            self._collect_events(child)

    def next_week(self) -> None:
        self.current_week_start += timedelta(days=7)
        self.update()

    def prev_week(self) -> None:
        self.current_week_start -= timedelta(days=7)
        self.update()

    def zoom_in(self) -> None:
        self.zoom_factor = min(3.0, self.zoom_factor * 1.2)
        self.hour_height = int(self.base_hour_height * self.zoom_factor)
        self._update_size()
        self.update()

    def zoom_out(self) -> None:
        self.zoom_factor = max(0.3, self.zoom_factor / 1.2)
        self.hour_height = int(self.base_hour_height * self.zoom_factor)
        self._update_size()
        self.update()

    def _update_size(self) -> None:
        total_height = 24 * self.hour_height + self.header_height
        total_width = self.time_column_width + 7 * self.day_width
        self.setMinimumSize(total_width, total_height)

    def _get_week_events(self) -> List[CalendarEvent]:
        week_end = self.current_week_start + timedelta(days=7)
        week_events = []

        for event in self.events:
            display_time = event.get_display_time()
            end_time = event.get_end_time()

            if display_time and self.current_week_start <= display_time.date(
            ) <= week_end:
                week_events.append(event)
            elif end_time and self.current_week_start <= end_time.date() <= week_end:
                week_events.append(event)

        return week_events

    def _get_day_events(self, day_date: date) -> List[CalendarEvent]:
        day_events = []
        for event in self._get_week_events():
            display_time = event.get_display_time()
            end_time = event.get_end_time()

            if display_time and display_time.date() == day_date:
                day_events.append(event)
            elif end_time and end_time.date() == day_date and not display_time:
                day_events.append(event)

        return day_events

    def wheelEvent(self, event) -> None:
        if event.modifiers() & Qt.KeyboardModifier.ControlModifier:
            if event.angleDelta().y() > 0:
                self.zoom_in()
            else:
                self.zoom_out()
        else:
            super().wheelEvent(event)

    def paintEvent(self, event) -> None:
        painter = QPainter(self)
        painter.fillRect(self.rect(), QColor(255, 255, 255))

        self._draw_grid(painter)
        self._draw_headers(painter)
        self._draw_events(painter)

    def _draw_grid(self, painter: QPainter) -> None:
        painter.setPen(QPen(COLOR_GRID_LINE, 1))

        for hour in range(24):
            y = self.header_height + hour * self.hour_height
            painter.drawLine(0, y, self.width(), y)

        for day in range(8):
            x = self.time_column_width + day * self.day_width
            painter.drawLine(x, 0, x, self.height())

    def _draw_headers(self, painter: QPainter) -> None:
        painter.setPen(QPen(COLOR_HEADERS, 1))
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

            if not day_events:
                continue

            layout = EventLayoutCalculator.calculate_layout(day_events, self.day_width)

            for event in day_events:
                if event in layout:
                    x_offset, width, depth = layout[event]
                    self._draw_event(painter, event, day, x_offset, width, depth)

    def _draw_event(self, painter: QPainter, event: CalendarEvent, day_index: int,
                    x_offset: int, width: int, depth: int) -> None:
        display_time = event.get_display_time()
        end_time = event.get_end_time()

        if not display_time:
            return

        day_x = self.time_column_width + day_index * self.day_width
        event_x = day_x + x_offset

        start_y = self.header_height + display_time.hour * self.hour_height + (
            display_time.minute * self.hour_height // 60)

        if event.is_event:
            self._draw_event_rectangle(painter, event, event_x, start_y, width, end_time,
                                       depth)
        else:
            self._draw_creation_marker(painter, event, event_x, start_y, width)

        self._draw_clock_periods(painter, event, event_x, width, start_y)

    def _draw_event_rectangle(self, painter: QPainter, event: CalendarEvent, x: int,
                              y: int, width: int, end_time: Optional[datetime],
                              depth: int) -> None:
        if event.has_duration() and end_time:
            if event.spans_multiple_days():
                self._draw_multi_day_event(painter, event, x, width, y)
            else:
                end_y = self.header_height + end_time.hour * self.hour_height + (
                    end_time.minute * self.hour_height // 60)
                height = max(20, end_y - y)

                if event.scheduled and event.deadline:
                    painter.setBrush(QBrush(COLOR_SCHEDULED_EVENT_FILL))
                    painter.setPen(QPen(COLOR_SCHEDULED_EVENT_FRAME, 3))
                    painter.drawRect(x, y, width, height)
                    painter.setPen(QPen(COLOR_SCHEDULED_EVENT_FRAME, 3))
                    painter.drawLine(x, y, x + width, y)
                    painter.drawLine(x, y + height, x + width, y + height)
                else:
                    color_intensity = max(100, 255 - depth * 30)
                    painter.setBrush(QBrush(QColor(100, 150, color_intensity)))
                    painter.setPen(QPen(COLOR_SCHEDULED_EVENT_FRAME, 1))
                    painter.drawRect(x, y, width, height)
        else:
            painter.setPen(QPen(QColor(200, 100, 100), 3))
            painter.drawLine(x, y, x + width, y)
            painter.drawLine(x, y + 3, x + width, y + 3)

        painter.setPen(QPen(QColor(0, 0, 0), 1))
        font_size = max(6, min(10, width // 10))
        painter.setFont(QFont("Arial", font_size))

        text = event.title
        if len(text) * font_size > width:
            max_chars = max(1, width // font_size)
            text = text[:max_chars] + "..."

        painter.drawText(x + 2, y + 12, text)

    def _draw_creation_marker(self, painter: QPainter, event: CalendarEvent, x: int,
                              y: int, width: int) -> None:
        painter.setBrush(QBrush(QColor(150, 150, 150, 150)))
        painter.setPen(QPen(QColor(100, 100, 100), 1))
        painter.drawEllipse(x, y, min(width, 20), 10)

        painter.setPen(QPen(QColor(0, 0, 0), 1))
        painter.setFont(QFont("Arial", 8))
        painter.drawText(x + 25, y + 8, f"Created: {event.title[:10]}")

    def _draw_multi_day_event(self, painter: QPainter, event: CalendarEvent, x: int,
                              width: int, y: int) -> None:
        start_time = event.get_start_time()
        end_time = event.get_end_time()

        if not start_time or not end_time:
            return

        current_day = self.current_week_start + timedelta(
            days=(x - self.time_column_width) // self.day_width)

        painter.setBrush(QBrush(QColor(100, 150, 255)))
        painter.setPen(QPen(QColor(0, 100, 200), 1))

        if start_time.date() == current_day:
            height = self.hour_height
            rect = QRect(x, y, width, height)
            painter.drawRect(rect)

            painter.setPen(QPen(QColor(0, 0, 0), 1))
            for i in range(0, width, 10):
                painter.drawLine(x + width - i, y, x + width - i, y + height)

        elif end_time.date() == current_day:
            end_y = self.header_height + end_time.hour * self.hour_height + (
                end_time.minute * self.hour_height // 60)
            rect = QRect(x, self.header_height, width, end_y - self.header_height)
            painter.drawRect(rect)

            painter.setPen(QPen(QColor(0, 0, 0), 1))
            for i in range(0, width, 10):
                painter.drawLine(x + i, self.header_height, x + i, end_y)

    def _draw_clock_periods(self, painter: QPainter, event: CalendarEvent, x: int,
                            width: int, y: int) -> None:
        if not event.clock_periods:
            return

        painter.setBrush(QBrush(QColor(255, 200, 100)))
        painter.setPen(QPen(QColor(200, 150, 50), 1))

        for i, (start, end) in enumerate(event.clock_periods[:3]):
            clock_x = x + width + 2 + i * 15
            clock_y = y
            clock_height = min(30, int((end - start).total_seconds() // 60))
            painter.drawRect(clock_x, clock_y, 12, clock_height)



class OrgCalendarView(QWidget):
    def resizeEvent(self, event) -> None:
        # log(CAT).info("Calendar view resize event")
        super().resizeEvent(event)

    def __init__(self, parent: QWidget) -> None:
        assert parent is not None
        super().__init__(parent)

        layout = QVBoxLayout()

        nav_layout = QHBoxLayout()
        self.prev_button = QPushButton("← Previous Week")
        self.next_button = QPushButton("Next Week →")
        self.zoom_in_button = QPushButton("Zoom In")
        self.zoom_out_button = QPushButton("Zoom Out")
        self.week_label = QLabel()

        nav_layout.addWidget(self.prev_button)
        nav_layout.addWidget(self.next_button)
        nav_layout.addWidget(self.zoom_in_button)
        nav_layout.addWidget(self.zoom_out_button)
        nav_layout.addStretch()
        nav_layout.addWidget(self.week_label)

        scroll_area = QScrollArea(self)
        self.week_view = WeekView(scroll_area)
        scroll_area.setWidget(self.week_view)
        scroll_area.setWidgetResizable(True)
        scroll_area.setVerticalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOn)
        scroll_area.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAsNeeded)

        layout.addLayout(nav_layout)
        layout.addWidget(scroll_area)

        self.setLayout(layout)

        self.prev_button.clicked.connect(self._prev_week)
        self.next_button.clicked.connect(self._next_week)
        self.zoom_in_button.clicked.connect(self.week_view.zoom_in)
        self.zoom_out_button.clicked.connect(self.week_view.zoom_out)

        self._update_week_label()

    def _prev_week(self) -> None:
        self.week_view.prev_week()
        self._update_week_label()

    def _next_week(self) -> None:
        self.week_view.next_week()
        self._update_week_label()

    def _update_week_label(self) -> None:
        start = self.week_view.current_week_start
        end = start + timedelta(days=6)
        self.week_label.setText(
            f"Week of {start.strftime('%B %d, %Y')} - {end.strftime('%B %d, %Y')}")

    def set_agenda_data(self, root_node: OrgAgendaNode) -> None:
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

        tab_widget = QTabWidget(self)
        assert tab_widget is not None
        calendar_view = OrgCalendarView(tab_widget)
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
    widget.resize(1600, 800)
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
        use_cache=False,
    )
    log(CAT).info("File parsing done")
    show_calendar(node)


if __name__ == "__main__":
    main()
