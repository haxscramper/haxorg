#!/usr/bin/env python

from dataclasses import dataclass, field, fields
from typing import *


@dataclass
class Entry:
    kind: str = ""


@dataclass
class GenTu:
    path: str = ""
    entries: List[Entry] = field(default_factory=list)

@dataclass
class GenTuParam:
    name: str = ""


@dataclass
class GenUnit:
    header: Optional[GenTu] = None
    source: Optional[GenTu] = None


@dataclass
class GenFiles:
    files: List[GenUnit] = field(default_factory=list)


@dataclass
class GenTuDoc:
    brief: str
    full: str = ""


@dataclass
class GenTuInclude:
    what: str
    isSystem: bool
    kind: str = "Include"


@dataclass
class GenTuNamespace:
    name: str
    entries: List[Any]
    kind: str = "Namespace"


@dataclass
class GenTuField:
    type: str
    name: str
    doc: GenTuDoc
    value: Optional[str] = None
    kind: str = "Field"
    isStatic: bool = False
    isConst: bool = False


@dataclass
class GenTuIdent:
    type: str
    name: str
    value: Optional[str] = None


@dataclass
class GenTuFunction:
    result: str
    name: str
    doc: GenTuDoc
    arguments: List[GenTuIdent] = field(default_factory=list)
    isConst: bool = False
    isStatic: bool = False
    impl: Optional[str] = None
    params: List[str] = field(default_factory=list)
    isVirtual: bool = False
    isPureVirtual: bool = False
    kind: str = "Function"


@dataclass
class GenTuPass:
    what: str
    kind: str = "Pass"


@dataclass
class GenTuStruct:
    name: str
    doc: GenTuDoc
    fields: List[GenTuField] = field(default_factory=list)
    nested: List[Any] = field(default_factory=list)
    methods: List[GenTuFunction] = field(default_factory=list)
    bases: List[str] = field(default_factory=list)
    concreteKind: bool = True
    kind: str = "Struct"


@dataclass
class GenTuEnumField:
    name: str
    doc: GenTuDoc
    value: Optional[str] = None


@dataclass
class GenTuEnum:
    name: str
    doc: GenTuDoc
    fields: List[GenTuEnumField] = field(default_factory=list)
    base: Optional[str] = "short int"
    kind: str = "Enum"


@dataclass
class GenTuTypeGroup:
    types: List[Any] = field(default_factory=list)
    enumName: str = "Kind"
    iteratorMacroName: str = ""
    variantName: str = "Data"
    variantField: str = "data"
    variantValue: Optional[str] = None
    kindGetter: str = "getKind"
    kind: str = "TypeGroup"

