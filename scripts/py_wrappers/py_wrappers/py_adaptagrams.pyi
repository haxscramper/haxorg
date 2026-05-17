from typing import *
from enum import Enum
from datetime import datetime, date, time

T = TypeVar("T")

class ImmBox[T]():
    def get(self) -> T: ...

class ImmFlexVec[T]():
    def at(self, idx: int) -> T: ...
    def __len__(self) -> int: ...

class ImmVec[T]():
    def at(self, idx: int) -> T: ...
    def __len__(self) -> int: ...

class IntSet[T]():
    def __len__(self) -> int: ...

class ImmAdapterTBase[T](ImmAdapter):
    pass
