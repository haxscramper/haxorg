#!/usr/bin/env python

from dataclasses import dataclass, field
from typing import *

@dataclass
class Entry:
    kind: str = ""

@dataclass 
class GenTu:
    path: str = ""
    entries: List[Entry] = field(default_factory=list)

@dataclass
class GenUnit:
    header: GenTu = field(default_factory=lambda: GenTu())
    source: GenTu = field(default_factory=lambda: GenTu())

@dataclass
class GenFiles:
    files: List[GenUnit] = field(default_factory=list)

def gen_value():
    return GenFiles()
