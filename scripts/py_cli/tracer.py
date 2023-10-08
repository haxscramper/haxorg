from dataclasses import field, dataclass, replace
from beartype.typing import *
from beartype import beartype
from time import time


@beartype
@dataclass(frozen=True)
class PayloadId:
    id: int


@beartype
@dataclass(frozen=True)
class EventPayload:
    kind: str
    nk: str = field(
        default=None
    )  # Placeholder, you'd replace this with a more specific type if available
    loc: str = field(default=None)  # Placeholder
    sym: str = field(default=None)  # Placeholder
    str_: str = field(default=None)


@beartype
@dataclass(frozen=True)
class TraceEvent:
    begin: bool
    payload: PayloadId
    timeStamp: float


@beartype
@dataclass(frozen=True)
class Tracer:
    start: float = field(default_factory=time.time)
    events: list[TraceEvent] = field(default_factory=list)
    payloads: list[EventPayload] = field(default_factory=list)

    def startTracer(self):
        self.start = time.time()
        self.payloads.append(EventPayload(kind="root"))
        self.events.append(
            TraceEvent(begin=True,
                       payload=PayloadId(len(self.payloads) - 1),
                       timeStamp=self.start))

    def finish(self):
        t = time.time()
        self.events.append(TraceEvent(begin=False, payload=PayloadId(0), timeStamp=t))

    def addPayload(self, payload: EventPayload) -> PayloadId:
        self.payloads.append(payload)
        return PayloadId(len(self.payloads) - 1)

    def record(self, begin: bool, payload: PayloadId):
        self.events.append(TraceEvent(begin=begin, payload=payload,
                                      timeStamp=time.time()))


