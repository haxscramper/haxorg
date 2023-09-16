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
class Pass:
    what: str
    kind: str = "Pass"


@dataclass
class Struct:
    name: str
    doc: GenTuDoc
    fields: List[GenTuField] = field(default_factory=list)
    nested: List[Any] = field(default_factory=list)
    methods: List[GenTuFunction] = field(default_factory=list)
    bases: List[str] = field(default_factory=list)
    concreteKind: bool = True
    kind: str = "Struct"


@dataclass
class EField:
    name: str
    doc: GenTuDoc
    value: Optional[str] = None


@dataclass
class Enum:
    name: str
    doc: GenTuDoc
    fields: List[EField] = field(default_factory=list)
    base: Optional[str] = "short int"
    kind: str = "Enum"


@dataclass
class Group:
    types: List[Any] = field(default_factory=list)
    enumName: str = "Kind"
    iteratorMacroName: str = ""
    variantName: str = "Data"
    variantField: str = "data"
    variantValue: Optional[str] = None
    kindGetter: str = "getKind"
    kind: str = "TypeGroup"


def t_str():
    return "Str"


def t_int():
    return "int"


def t_vec(arg):
    return f"Vec<{arg}>"


def t_id(target=None):
    return f"SemIdT<{target}>" if target else "SemId"


def t_opt(arg):
    return f"Opt<{arg}>"


def t_osk():
    return "OrgSemKind"


def t_cr(arg):
    return f"CR<{arg}>"


def t_var(*args):
    return "Variant<%s>" % ", ".join(args)


def t_map(key, val):
    return f"UnorderedMap<{key}, {val}>"


def id_field(id, name, doc):
    return GenTuField(t_id(id), name, doc, value=f"SemIdT<{id}>::Nil()")


def vec_field(typ, name, doc):
    return GenTuField(t_vec(typ), name, doc, value="{}")


def opt_field(typ, name, doc):
    return GenTuField(t_opt(typ), name, doc, value="std::nullopt")


def d_org(*args, **kwargs):
    res = Struct(*args, **kwargs)
    kind = res.name
    base = res.bases[0]
    res.nested = [Pass(f"using {base}::{base};")] + res.nested
    if res.concreteKind:
        res.fields.insert(
            0,
            GenTuField(t_osk(), "staticKind", GenTuDoc("Document"), isConst=True, isStatic=True),
        )

        res.methods.insert(0, GenTuFunction(t_osk(), "getKind", GenTuDoc(""), isConst=True, isVirtual=True, isPureVirtual=False,
        impl=f"return {t_osk()}::{kind};"))

        res.methods.insert(0, GenTuFunction(t_id(kind), "create", GenTuDoc(""), isStatic=True, arguments=[
            GenTuIdent(t_id(), "parent"),
            GenTuIdent(t_opt("OrgAdapter"), "original", value="std::nullopt")
        ]))

    return res


def d_simple_enum(name, doc, *args):
    return Enum(name, doc, fields=[EField(arg, GenTuDoc("")) for arg in args])


def get_types():
    return [
        d_org(
            "Stmt",
            GenTuDoc("Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)"
               ),
            bases=["Org"],
            concreteKind=False,
            fields=[GenTuField(t_vec(t_id()), "attached", GenTuDoc(""))],
            methods=[GenTuFunction(
                t_opt(t_id()),
                "getAttached",
                GenTuDoc(""),
                arguments=[GenTuIdent(t_osk(), "kind")],
            )],
            nested=[
                Pass("Stmt() {}"),
                Pass("Stmt(SemId parent, CVec<SemId> attached, CVec<SemId> subnodes) : Org(parent, subnodes), attached(attached) {}"),
            ],
        ),
        d_org(
            "Inline",
            GenTuDoc("Base class for all inline elements"),
            bases=["Org"],
            concreteKind=False,
        ),
        d_org(
            "StmtList",
            GenTuDoc("Zero or more statement nodes"),
            bases=["Org"],
        ),
        d_org(
            "Empty",
            GenTuDoc("Node without content"),
            bases=["Org"],
        ),
        d_org(
            "Row",
            GenTuDoc("Table row"),
            bases=["Org"],
        ),
        d_org(
            "Table",
            GenTuDoc("Table"),
            bases=["Stmt"],
            fields=[GenTuField(
                t_vec(t_id("Row")),
                "rows",
                GenTuDoc("List of rows for the table"),
                value="{}",
            )],
        ),
        d_org(
            "HashTag",
            GenTuDoc("Single or nested inline hash-tag"),
            bases=["Inline"],
            fields=[
                GenTuField("Str", "head", GenTuDoc("Main part of the tag")),
                GenTuField(
                    t_vec(t_id("HashTag")),
                    "subtags",
                    GenTuDoc("List of nested tags"),
                    value="{}",
                ),
            ],
            methods=[
                GenTuFunction(
                    "bool",
                    "prefixMatch",
                    GenTuDoc("Check if list of tag names is a prefix for either of the nested hash tags in this one"),
                    isConst=True,
                    arguments=[GenTuIdent(t_cr(t_vec(t_str())), "prefix")],
                )
            ],
        ),
        d_org(
            "Footnote",
            GenTuDoc(
                "Inline and regular footnote definition",
                full="\\note in-text link to the footnotes are implemented using `Link` nodes",
            ),
            bases=["Inline"],
            fields=[
                GenTuField("Str", "tag", GenTuDoc("Footnote text target name"), value='""'),
                GenTuField(
                    t_opt(t_id()),
                    "definition",
                    GenTuDoc("Link to possibly resolved definition"),
                    value="std::nullopt",
                ),
            ],
        ),
        d_org(
            "Completion",
            GenTuDoc("Completion status of the subtree list element"),
            bases=["Inline"],
            fields=[
                GenTuField("int", "done", GenTuDoc("Number of completed tasks"), value="0"),
                GenTuField("int", "full", GenTuDoc("Full number of tasks"), value="0"),
                GenTuField(
                    "bool",
                    "isPercent",
                    GenTuDoc("Use fraction or percent to display completion"),
                    value="false",
                ),
            ],
        ),
        d_org(
            "Paragraph",
            GenTuDoc("Top-level or inline paragraph"),
            bases=["Stmt"],
            methods=[
                GenTuFunction(
                    "bool",
                    "isFootnoteDefinition",
                    GenTuDoc("Check if paragraph defines footnote"),
                    isConst=True,
                    impl="return !subnodes.empty() && at(0)->is(OrgSemKind::Footnote);",
                )
            ],
        ),
        d_org(
            "Format",
            GenTuDoc("Base class for branch of formatting node classes"),
            bases=["Org"],
            concreteKind=False,
        ),
        d_org("Center", GenTuDoc("Center nested content in export"), bases=["Format"]),
        d_org(
            "Command",
            GenTuDoc("Base class for block or line commands"),
            bases=["Org"],
            concreteKind=False,
        ),
        d_org(
            "LineCommand",
            GenTuDoc("Line commands"),
            bases=["Command"],
            concreteKind=False,
        ),
        #;; TODO rename to the standalone command
        d_org(
            "Standalone",
            GenTuDoc("Standalone commands that can be placed individuall on the the top level and don't have to be attached to any subsequent elements"
               ),
            bases=["LineCommand"],
            concreteKind=False,
        ),
        d_org(
            "Attached",
            GenTuDoc("Line command that might get attached to some block element"),
            bases=["LineCommand"],
            concreteKind=False,
        ),
        d_org(
            "Caption",
            GenTuDoc("Caption annotation for any subsequent node"),
            bases=["Attached"],
            fields=[id_field("Paragraph", "text", GenTuDoc("Content description"))],
        ),
        d_org(
            "CommandGroup",
            GenTuDoc("Multiple attachable commands will get grouped into this element unless it is possible to attached them to some adjacent block command"
               ),
            bases=["Stmt"],
        ),
        d_org(
            "Block",
            GenTuDoc("Block command type"),
            bases=["Command"],
            concreteKind=False,
        ),
        d_org(
            "Quote",
            GenTuDoc("Quotation block"),
            bases=["Org"],
            fields=[id_field("Paragraph", "text", GenTuDoc("Quote content"))],
        ),
        d_org("Example", GenTuDoc("Example block"), bases=["Block"]),
        d_org(
            "CmdArguments",
            GenTuDoc("Additional arguments for command blocks"),
            bases=["Org"],
            methods=[
                GenTuFunction(
                    t_opt(
                        t_id("CmdArgument")),
                    "popArg",
                    GenTuDoc("Remove argument value from the map and return it if present",
                        full=
                        "Some argument values can be processed directly during convert, others will be mapped in respective exporter backends. This is a convenience method to remove things during convert stage"
                       ),
                    arguments=[GenTuIdent(t_str(), "key")])
            ],
            fields=[
                GenTuField(t_vec(t_id("CmdArgument")), "positional", GenTuDoc("Positional arguments that had no keys")),
                GenTuField(t_map(t_str(), t_id("CmdArgument")), "named", GenTuDoc("Stored key-value mapping"))
            ]),
        d_org("CmdArgument",
              GenTuDoc("Single key-value (or positional)"),
              bases=["Org"],
              fields=[opt_field(t_str(), "key", GenTuDoc("Key")), GenTuField(t_str(), "value", GenTuDoc("Value"))],
              methods=[
                  GenTuFunction(t_opt("int"), "getInt", GenTuDoc("Parse argument as integer value"), isConst=True),
                  GenTuFunction(t_opt("bool"), "getBool", GenTuDoc("Get argument as bool"), isConst=True),
                  GenTuFunction(t_str(), "getString", GenTuDoc("Get original string"), isConst=True)
              ]),
        d_org("Export",
              GenTuDoc("Direct export passthrough"),
              bases=["Block"],
              nested=[
                  Enum("Format", GenTuDoc("Export block format type"), [
                      EField("Inline", GenTuDoc("Export directly in the paragraph")),
                      EField("Line", GenTuDoc("Single line of export")),
                      EField("Block", GenTuDoc("Multiple lines of export"))
                  ])
              ],
              fields=[
                  GenTuField("Format", "format", GenTuDoc("Export block type"), value="Format::Inline"),
                  GenTuField(t_str(), "exporter", GenTuDoc("Exporter backend name")),
                  id_field("CmdArguments", "parameters", GenTuDoc("Additional parameters aside from 'exporter',")),
                  opt_field(t_str(), "placement", GenTuDoc("Customized position of the text in the final exporting document.")),
                  GenTuField(t_str(), "content", GenTuDoc("Raw exporter content string"))
              ]),
        d_org("AdmonitionBlock", GenTuDoc("Block of text with admonition tag: 'note',', 'warning','"), bases=["Block"]),
        d_org(
            "Code",
            GenTuDoc("Base class for all code blocks"),
            bases=["Block"],
            nested=[
                Struct(
                    "Switch",
                    GenTuDoc("Extra configuration switches that can be used to control representation of the rendered code block. This field does not exactly correspond to the `-XX` parameters that can be passed directly in the field, but also works with attached `#+options` from the block"
                       ),
                    nested=[
                        Group([
                            Struct("LineStart",
                                   GenTuDoc("Enumerate code lines starting from `start` value instead of default indexing."),
                                   fields=[
                                       GenTuField("int", "start", GenTuDoc("First line number")),
                                       GenTuField("bool",
                                             "extendLast",
                                             GenTuDoc("Continue numbering from the previous block nstead of starting anew"),
                                             value="false")
                                   ]),
                            Struct("CalloutFormat", GenTuDoc(""), fields=[GenTuField("Str", "format", GenTuDoc(""), value="\"\"")]),
                            Struct("RemoveCallout", GenTuDoc(""), fields=[GenTuField("bool", "remove", GenTuDoc(""), value="true")]),
                            Struct("EmphasizeLine",
                                   GenTuDoc("Emphasize single line -- can be repeated multiple times"),
                                   fields=[GenTuField(t_vec("int"), "line", GenTuDoc(""), value="{}")]),
                            Struct("Dedent", GenTuDoc(""), fields=[GenTuField("int", "value", GenTuDoc(""), value="0")])
                        ])
                    ]),
                Enum("Results", GenTuDoc("What to do with newly evaluated result"),
                     [EField("Replace", GenTuDoc("Remove old result, replace with new value"))]),
                Enum("Exports", GenTuDoc("What part of the code block should be visible in export"), [
                    EField("None", GenTuDoc("Hide both original code and run result")),
                    EField("Both", GenTuDoc("Show output and code")),
                    EField("Code", GenTuDoc("Show only code")),
                    EField("Results", GenTuDoc("Show only evaluation results"))
                ])
            ],
            fields=[
                GenTuField(t_opt(t_str()), "lang", GenTuDoc("Code block language name"), value="std::nullopt"),
                GenTuField(t_vec("Switch"), "switches", GenTuDoc("Switch options for block"), value="{}"),
                GenTuField("Exports", "exports", GenTuDoc("What to export"), value="Exports::Both"),
                id_field("CmdArguments", "parameters", GenTuDoc("Additional parameters that are language-specific")),
                GenTuField("bool", "cache", GenTuDoc("Do cache values?"), value="false"),
                GenTuField("bool", "eval", GenTuDoc("Eval on export?"), value="false"),
                GenTuField("bool", "noweb", GenTuDoc("Web-tangle code on export/run"), value="false"),
                GenTuField("bool", "hlines", GenTuDoc("?"), value="false"),
                GenTuField("bool", "tangle", GenTuDoc("?"), value="false")
            ]),
        d_org(
            "Time",
            GenTuDoc("Single static or dynamic timestamp (active or inactive)"),
            bases=["Org"],
            fields=[GenTuField("bool", "isActive", GenTuDoc("<active> vs [inactive]"), value="false")],
            nested=[
                Pass("bool isStatic() const { return std::holds_alternative<Static>(time); }"),
                Struct(
                    "Repeat",
                    GenTuDoc("Repetition information for static time"),
                    nested=[
                        Enum("Mode", GenTuDoc("Timestamp repetition mode"), [
                            EField("None", GenTuDoc("Do not repeat task on completion")),
                            EField("Exact", GenTuDoc("?")),
                            EField("FirstMatch", GenTuDoc("Repeat on the first matching day in the future")),
                            EField("SameDay", GenTuDoc("Repeat task on the same day next week/month/year"))
                        ]),
                        Enum(
                            "Period",
                            GenTuDoc("Repetition period. Temporary placeholder for now, until I figure out what would be the proper way to represent whatever org can do ... which is to be determined as well"
                               ), [
                                   EField("Year", GenTuDoc("")),
                                   EField("Month", GenTuDoc("")),
                                   EField("Week", GenTuDoc("")),
                                   EField("Day", GenTuDoc("")),
                                   EField("Hour", GenTuDoc("")),
                                   EField("Minute", GenTuDoc(""))
                               ])
                    ],
                    fields=[
                        GenTuField("Mode", "mode", GenTuDoc("mode")),
                        GenTuField("Period", "period", GenTuDoc("period")),
                        GenTuField("int", "count", GenTuDoc("count"))
                    ]),
                Group([
                    Struct("Static", GenTuDoc(""), fields=[GenTuField(t_opt("Repeat"), "repeat", GenTuDoc("")),
                                                        GenTuField("UserTime", "time", GenTuDoc(""))]),
                    Struct("Dynamic", GenTuDoc(""), fields=[GenTuField(t_str(), "expr", GenTuDoc(""))])
                ],
                      kindGetter="getTimeKind",
                      enumName="TimeKind",
                      variantField="time",
                      variantName="TimeVariant")
            ]),
        d_org("TimeRange",
              GenTuDoc("Range of time delimited by two points"),
              bases=["Org"],
              fields=[id_field("Time", "from", GenTuDoc("Starting time")),
                      id_field("Time", "to", GenTuDoc("Finishing time"))]),
        d_org("Macro",
              GenTuDoc("Inline macro invocation"),
              bases=["Org"],
              fields=[
                  GenTuField(t_str(), "name", GenTuDoc("Macro name"), value="\"\""),
                  GenTuField(t_vec(t_str()), "arguments", GenTuDoc("Raw uninterpreted macro arguments"), value="{}")
              ]),
        d_org("Symbol",
              GenTuDoc("Text symbol or symbol command"),
              bases=["Org"],
              nested=[
                  Struct("Param",
                         GenTuDoc("Symbol parameters"),
                         fields=[
                             GenTuField(t_opt(t_str()), "key", GenTuDoc("Key -- for non-positional")),
                             GenTuField(t_str(), "value", GenTuDoc("Uninterpreted value"))
                         ])
              ],
              fields=[
                  GenTuField(t_str(), "name", GenTuDoc("Name of the symbol")),
                  GenTuField(t_vec("Param"), "parameters", GenTuDoc("Optional list of parameters")),
                  GenTuField(t_vec(t_id()), "positional", GenTuDoc("Positional parameters"))
              ]),
        d_org("SubtreeLog",
              GenTuDoc("Single subtree log entry"),
              bases=["Org"],
              methods=[GenTuFunction("void", "setDescription", GenTuDoc(""), arguments=[GenTuIdent(t_id("StmtList"), "desc")])],
              nested=[
                  Struct("DescribedLog",
                         GenTuDoc("Base value for the log variant"),
                         fields=[
                             GenTuField(t_opt(t_id("StmtList")),
                                   "desc",
                                   GenTuDoc("Optional description of the log entry"),
                                   value="SemIdT<StmtList>::Nil()")
                         ]),
                  Group([
                      Struct("Priority",
                             GenTuDoc("Priority added"),
                             bases=["DescribedLog"],
                             nested=[d_simple_enum("Action", GenTuDoc("Priority change action"), "Added", "Removed", "Changed")],
                             fields=[
                                 opt_field("QString", "oldPriority", GenTuDoc("Previous priority for change and removal")),
                                 opt_field("QString", "newPriority", GenTuDoc("New priority for change and addition")),
                                 id_field("Time", "on", GenTuDoc("When priority was changed"))
                             ]),
                      Struct("Note",
                             GenTuDoc("Timestamped note"),
                             bases=["DescribedLog"],
                             fields=[id_field("Time", "on", GenTuDoc("Where log was taken"))]),
                      Struct("Refile",
                             GenTuDoc("Refiling action"),
                             bases=["DescribedLog"],
                             fields=[
                                 id_field("Time", "on", GenTuDoc("When the refiling happened")),
                                 id_field("Link", "from", GenTuDoc("Link to the original subtree"))
                             ]),
                      Struct("Clock",
                             GenTuDoc("Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`"),
                             bases=["DescribedLog"],
                             fields=[
                                 GenTuField(t_var(t_id("Time"), t_id("TimeRange")),
                                       "range",
                                       GenTuDoc("Start-end or only start period"),
                                       value="SemIdT<Time>::Nil()")
                             ]),
                      Struct("State",
                             GenTuDoc("Change of the subtree state -- `- State \"WIP\" from \"TODO\" [2023-04-30 Sun 13:29:04]`"),
                             bases=["DescribedLog"],
                             fields=[
                                 GenTuField("OrgBigIdentKind", "from", GenTuDoc("")),
                                 GenTuField("OrgBigIdentKind", "to", GenTuDoc("")),
                                 id_field("Time", "on", GenTuDoc(""))
                             ]),
                      Struct("Tag",
                             GenTuDoc("Assign tag to the subtree `- Tag \"project##haxorg\" Added on [2023-04-30 Sun 13:29:06]`"),
                             bases=["DescribedLog"],
                             fields=[
                                 id_field("Time", "on", GenTuDoc("When the log was assigned")),
                                 id_field("HashTag", "tag", GenTuDoc("Tag in question")),
                                 GenTuField("bool", "added", GenTuDoc("Added/removed?"), value="false")
                             ])
                  ],
                        kindGetter="getLogKind",
                        variantField="log",
                        variantValue="Note{}",
                        variantName="LogEntry")
              ]),
        d_org(
            "Subtree",
            GenTuDoc("Subtree"),
            bases=["Org"],
            fields=[
                GenTuField("int", "level", GenTuDoc("Subtree level"), value="0"),
                opt_field(t_str(), "treeId", GenTuDoc(":ID: property")),
                opt_field(t_str(), "todo", GenTuDoc("Todo state of the tree")),
                opt_field(t_id("Completion"), "completion", GenTuDoc("Task completion state")),
                opt_field(t_id("Paragraph"), "description", GenTuDoc("")),
                vec_field(t_id("HashTag"), "tags", GenTuDoc("Trailing tags")),
                id_field("Paragraph", "title", GenTuDoc("Main title")),
                vec_field(t_id("SubtreeLog"), "logbook", GenTuDoc("Associated subtree log")),
                vec_field("Property", "properties", GenTuDoc("Immediate properties")),
                opt_field(t_id("Time"), "closed", GenTuDoc("When subtree was marked as closed")),
                opt_field(t_id("Time"), "deadline", GenTuDoc("When is the deadline")),
                opt_field(t_id("Time"), "scheduled", GenTuDoc("When the event is scheduled"))
            ],
            methods=[
                GenTuFunction(t_vec("Period"), "getTimePeriods", GenTuDoc(""), isConst=True, arguments=[GenTuIdent("IntSet<Period::Kind>", "kinds")]),
                GenTuFunction(t_vec("Property"),
                       "getProperties",
                       GenTuDoc(""),
                       isConst=True,
                       arguments=[GenTuIdent("Property::Kind", "kind"),
                                  GenTuIdent(t_cr(t_str()), "subkind", value="\"\"")]),
                GenTuFunction(t_opt("Property"),
                       "getProperty",
                       GenTuDoc(""),
                       isConst=True,
                       arguments=[GenTuIdent("Property::Kind", "kind"),
                                  GenTuIdent(t_cr(t_str()), "subkind", value="\"\"")]),
                GenTuFunction(t_vec("Property"),
                       "getContextualProperties",
                       GenTuDoc(""),
                       isConst=True,
                       arguments=[GenTuIdent("Property::Kind", "kind"),
                                  GenTuIdent(t_cr(t_str()), "subkind", value="\"\"")]),
                GenTuFunction(t_opt("Property"),
                       "getContextualProperty",
                       GenTuDoc(""),
                       isConst=True,
                       arguments=[GenTuIdent("Property::Kind", "kind"),
                                  GenTuIdent(t_cr(t_str()), "subkind", value="\"\"")])
            ],
            nested=[
                Struct(
                    "Period",
                    GenTuDoc("Type of the subtree associated time periods"),
                    fields=[
                        GenTuField("Kind", "kind", GenTuDoc("Time period kind -- not associated with point/range distinction")),
                        GenTuField(t_var(t_id("Time"), t_id("TimeRange")), "period", GenTuDoc("Stored time point/range"))
                    ],
                    methods=[
                        GenTuFunction(t_id("Time"), "getTime", GenTuDoc("Get associated time point"), impl="return std::get<SemIdT<Time>>(period);"),
                        GenTuFunction(t_id("Time"),
                               "getTimeRange",
                               GenTuDoc("Get associated time period"),
                               impl="return std::get<SemIdT<TimeRange>>(period);")
                    ],
                    #  ;; TODO constructors
                    nested=[
                        Enum("Kind", GenTuDoc("Period kind"), [
                            EField("Clocked", GenTuDoc("Time period of the task execution.")),
                            EField(
                                "Scheduled",
                                GenTuDoc("Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned"
                                   )),
                            EField(
                                "Titled",
                                GenTuDoc("Single point or time range used in title. Single point can also be a simple time, such as `12:20`")),
                            EField("Deadline", GenTuDoc("Date of task completion. Must be a single time point")),
                            EField("Created", GenTuDoc("When the subtree was created")),
                            EField("Repeated", GenTuDoc("Last repeat time of the recurring tasks"))
                        ]),
                        Pass("Period(CR<Variant<SemIdT<Time>, SemIdT<TimeRange>>> period, Kind kind) : period(period), kind(kind) {}")
                    ]),
                Struct("Property",
                       GenTuDoc("Single subtree property"),
                       fields=[
                           GenTuField("SetMode", "mainSetRule", GenTuDoc(""), value="SetMode::Override"),
                           GenTuField("SetMode", "subSetRule", GenTuDoc(""), value="SetMode::Override"),
                           GenTuField("InheritanceMode", "inheritanceMode", GenTuDoc(""), value="InheritanceMode::ThisAndSub")
                       ],
                       nested=[
                           d_simple_enum("SetMode", GenTuDoc(""), "Override", "Add", "Subtract"),
                           d_simple_enum("InheritanceMode", GenTuDoc(""), "ThisAndSub", "OnlyThis", "OnlySub"),
                           Group([
                               Struct( "Nonblocking" , GenTuDoc(""), fields=[GenTuField("bool", "isBlocking", GenTuDoc(""))]),
                               Struct( "Trigger" , GenTuDoc("")),
                               Struct( "Origin" , GenTuDoc(""), fields=[GenTuField(t_str(), "text", GenTuDoc(""))]),
                               Struct( "ExportLatexClass" , GenTuDoc(""), fields=[GenTuField(t_str(), "latexClass", GenTuDoc(""))]),
                               Struct( "ExportLatexClassOptions" , GenTuDoc(""), fields=[GenTuField(t_vec(t_str()), "options", GenTuDoc(""))]),
                               Struct( "ExportLatexHeader" , GenTuDoc(""), fields=[GenTuField(t_str(), "header", GenTuDoc(""))]),
                               Struct( "ExportLatexCompiler" , GenTuDoc(""), fields=[GenTuField(t_str(), "compiler", GenTuDoc(""))]),
                               Struct( "Ordered" , GenTuDoc(""), fields=[GenTuField("bool", "isOrdered", GenTuDoc(""))]),
                               Struct( "Effort" ,
                                      GenTuDoc(""),
                                      fields=[GenTuField("int", "hours", GenTuDoc(""), value="0"),
                                              GenTuField("int", "minutes", GenTuDoc(""), value="0")]),
                               Struct( "Visibility" ,
                                      GenTuDoc(""),
                                      nested=[d_simple_enum("Level", GenTuDoc(""), "Folded", "Children", "Content", "All")],
                                      fields=[GenTuField("Level", "level", GenTuDoc(""))]),
                               Struct( "ExportOptions" ,
                                      GenTuDoc(""),
                                      fields=[GenTuField(t_str(), "backend", GenTuDoc("")),
                                              GenTuField("UnorderedMap<Str, Str>", "values", GenTuDoc(""))]),
                               Struct( "Blocker" , GenTuDoc(""), fields=[GenTuField(t_vec(t_str()), "blockers", GenTuDoc(""))]),
                               Struct( "Unnumbered" , GenTuDoc("")),
                               Struct( "Created" , GenTuDoc(""), fields=[id_field("Time", "time", GenTuDoc(""))])
                           ]),
                           Pass("Property(CR<Data> data) : data(data) {}"),
                           Pass("bool matches(Kind kind, CR<QString> subkind = \"\") const;"),
                       ])
            ]),
        d_org("LatexBody", GenTuDoc("Latex code body"), bases=["Org"], concreteKind=False),
        d_org("InlineMath", GenTuDoc("Inline math"), bases=["LatexBody"]),
        d_org("Leaf",
              GenTuDoc("Final node"),
              bases=["Org"],
              concreteKind=False,
              fields=[GenTuField(t_str(), "text", GenTuDoc("Final leaf value"), value="\"\"")]),
        d_org("Escaped", GenTuDoc("Escaped text"), bases=["Leaf"]),
        d_org("Newline", GenTuDoc("\\n newline"), bases=["Leaf"]),
        d_org("Space", GenTuDoc("' \"space\","), bases=["Leaf"]),
        d_org("Word", GenTuDoc("word"), bases=["Leaf"]),
        d_org("AtMention", GenTuDoc("@mention"), bases=["Leaf"]),
        d_org("RawText", GenTuDoc(""), bases=["Leaf"]),
        d_org("Punctuation", GenTuDoc(""), bases=["Leaf"]),
        d_org("Placeholder", GenTuDoc(""), bases=["Leaf"]),
        d_org("BigIdent", GenTuDoc(""), bases=["Leaf"]),
        d_org(
            "Markup",
            GenTuDoc(""),
            bases=["Org"],
            concreteKind=False,
        ),
        d_org("Bold", GenTuDoc(""), bases=["Markup"]),
        d_org("Underline", GenTuDoc(""), bases=["Markup"]),
        d_org("Monospace", GenTuDoc(""), bases=["Markup"]),
        d_org("MarkQuote", GenTuDoc(""), bases=["Markup"]),
        d_org("Verbatim", GenTuDoc(""), bases=["Markup"]),
        d_org("Italic", GenTuDoc(""), bases=["Markup"]),
        d_org("Strike", GenTuDoc(""), bases=["Markup"]),
        d_org("Par", GenTuDoc(""), bases=["Markup"]),
        d_org("List", GenTuDoc(""), bases=["Org"], methods=[GenTuFunction("bool", "isDescriptionList", GenTuDoc(""), isConst=True)]),
        d_org("ListItem",
              GenTuDoc(""),
              bases=["Org"],
              fields=[
                  GenTuField("Checkbox", "checkbox", GenTuDoc(""), value="Checkbox::None"),
                  GenTuField(t_opt(t_id("Paragraph")), "header", GenTuDoc(""), value="std::nullopt")
              ],
              nested=[d_simple_enum("Checkbox", GenTuDoc(""), "None", "Done", "Empty")],
              methods=[GenTuFunction("bool", "isDescriptionItem", GenTuDoc(""), isConst=True, impl="return header.has_value();")])
        #;; TODO
        ,
        d_org("Link",
              GenTuDoc(""),
              bases=["Org"],
              fields=[GenTuField(t_opt(t_id("Paragraph")), "description", GenTuDoc(""), value="std::nullopt")],
              methods=[
                  GenTuFunction(t_opt(t_id()), "resolve", GenTuDoc(""), isConst=True, arguments=[GenTuIdent(t_cr("Document"), "doc")]),
                  GenTuFunction(t_opt(t_id()), "resolve", GenTuDoc(""), isConst=True)
              ],
              nested=[
                  Group([
                      Struct( "Raw" , GenTuDoc(""), fields=[(GenTuField(t_str(), "text", GenTuDoc("")))]),
                      Struct( "Id" , GenTuDoc(""), fields=[(GenTuField(t_str(), "text", GenTuDoc("")))]),
                      Struct( "Person" , GenTuDoc(""), fields=[(GenTuField(t_str(), "name", GenTuDoc("")))]),
                      Struct( "Footnote" , GenTuDoc(""), fields=[(GenTuField(t_str(), "target", GenTuDoc("")))]),
                      Struct( "File" , GenTuDoc(""), fields=[(GenTuField(t_str(), "file", GenTuDoc("")))])
                  ],
                        kindGetter="getLinkKind")
              ]),
        d_org("Document",
              GenTuDoc(""),
              bases=["Org"],
              methods=[
                  GenTuFunction(t_opt(t_id()), "resolve", GenTuDoc(""), isConst=True, arguments=[GenTuIdent(t_cr(t_id()), "node")]),
                  GenTuFunction(t_opt(t_id("Subtree")), "getSubtree", GenTuDoc(""), isConst=True, arguments=[GenTuIdent(t_cr(t_str()), "id")]),
                  GenTuFunction(t_vec("Subtree::Property"),
                         "getProperties",
                         GenTuDoc(""),
                         isConst=True,
                         arguments=[GenTuIdent("Subtree::Property::Kind", "kind"),
                                    GenTuIdent(t_cr(t_str()), "subKind", value="\"\"")]),
                  GenTuFunction(t_opt("Subtree::Property"),
                         "getProperty",
                         GenTuDoc(""),
                         isConst=True,
                         arguments=[GenTuIdent("Subtree::Property::Kind", "kind"),
                                    GenTuIdent(t_cr(t_str()), "subKind", value="\"\"")])
              ],
              fields=[
                  GenTuField(t_map(t_str(), t_id()), "idTable", GenTuDoc("")),
                  GenTuField(t_map(t_str(), t_id()), "nameTable", GenTuDoc("")),
                  GenTuField(t_map(t_str(), t_id()), "footnoteTable", GenTuDoc("")),
                  GenTuField(t_map(t_str(), t_id()), "anchorTable", GenTuDoc("")),
                  opt_field(t_id("Paragraph"), "title", GenTuDoc("")),
                  opt_field(t_id("Paragraph"), "author", GenTuDoc("")),
                  opt_field(t_id("Paragraph"), "creator", GenTuDoc("")),
                  opt_field(t_id("RawText"), "email", GenTuDoc("")),
                  opt_field(t_vec(t_str()), "language", GenTuDoc("")),
                  id_field("DocumentOptions", "options", GenTuDoc("")),
                  opt_field(t_str(), "exportFileName", GenTuDoc(""))
              ]),
        d_org(
            "ParseError",
            GenTuDoc(""),
            bases=["Org"],
        ),
        d_org("FileTarget",
              GenTuDoc(""),
              bases=["Org"],
              fields=[
                  GenTuField(t_str(), "path", GenTuDoc("")),
                  opt_field("int", "line", GenTuDoc("")),
                  opt_field(t_str(), "searchTarget", GenTuDoc("")),
                  GenTuField("bool", "restrictToHeadlines", GenTuDoc(""), value="false"),
                  opt_field(t_str(), "targetId", GenTuDoc("")),
                  opt_field(t_str(), "regexp", GenTuDoc(""))
              ]),
        d_org(
            "TextSeparator",
            GenTuDoc(""),
            bases=["Org"],
        ),
        d_org(
            "Include",
            GenTuDoc(""),
            bases=["Org"],
            nested=[
                Group(
                    [Struct( "Example" , GenTuDoc("")),
                     Struct( "Export" , GenTuDoc("")),
                     Struct( "Src" , GenTuDoc("")),
                     Struct( "OrgDocument" , GenTuDoc(""))],
                    kindGetter="getIncludeKind")
            ]),
        d_org("DocumentOptions",
              GenTuDoc(""),
              bases=["Org"],
              methods=[
                  GenTuFunction(t_vec("Subtree::Property"),
                         "getProperties",
                         GenTuDoc(""),
                         isConst=True,
                         arguments=[GenTuIdent("Subtree::Property::Kind", "kind"),
                                    GenTuIdent(t_cr(t_str()), "subKind", value="\"\"")]),
                  GenTuFunction(t_opt("Subtree::Property"),
                         "getProperty",
                         GenTuDoc(""),
                         isConst=True,
                         arguments=[GenTuIdent("Subtree::Property::Kind", "kind"),
                                    GenTuIdent(t_cr(t_str()), "subKind", value="\"\"")])
              ],
              nested=[
                  Pass("using TocExport = Variant<bool, int>;"),
                  d_simple_enum("BrokenLinks", GenTuDoc(""), "Raise", "Ignore", "Mark"),
                  d_simple_enum("Visibility", GenTuDoc(""), "Overview", "Content", "ShowAll", "Show2Levels", "Show3Levels", "Show4Levels",
                                "Show5Levels", "ShowEverything")
              ],
              fields=[
                  GenTuField("BrokenLinks", "brokenLinks", GenTuDoc(""), value="BrokenLinks::Mark"),
                  GenTuField("Visibility", "initialVisibility", GenTuDoc(""), value="Visibility::ShowEverything"),
                  GenTuField("TocExport", "tocExport", GenTuDoc(""), value="false"),
                  GenTuField(t_vec("Subtree::Property"), "properties", GenTuDoc("")),
                  GenTuField("bool", "smartQuotes", GenTuDoc(""), value="false"),
                  GenTuField("bool", "emphasizedText", GenTuDoc(""), value="false"),
                  GenTuField("bool", "specialStrings", GenTuDoc(""), value="false"),
                  GenTuField("bool", "fixedWidthSections", GenTuDoc(""), value="false"),
                  GenTuField("bool", "includeTimestamps", GenTuDoc(""), value="false"),
                  GenTuField("bool", "preserveLineBreaks", GenTuDoc(""), value="false"),
                  GenTuField("bool", "plaintextSubscripts", GenTuDoc(""), value="false"),
                  GenTuField("bool", "exportArchived", GenTuDoc(""), value="false"),
                  GenTuField("bool", "exportWithAuthor", GenTuDoc(""), value="false"),
                  GenTuField("bool", "exportBrokenLinks", GenTuDoc(""), value="false"),
                  GenTuField("bool", "exportWithClock", GenTuDoc(""), value="false"),
                  GenTuField("bool", "exportWithCreator", GenTuDoc(""), value="false")
              ]),
        d_org(
            "DocumentGroup",
            GenTuDoc(""),
            bases=["Org"],
        )
    ]


def get_enums():
    return [
        Enum("OrgSemPlacement", GenTuDoc("Semantic location of the sem org node in the parent tree"), [
            EField("TreeTitle", GenTuDoc("Subtree title")),
            EField("TreeBody", GenTuDoc("Inner content of the subtree")),
            EField("LinkDescription", GenTuDoc("Description paragraph for the link")),
            EField("ListItemBody", GenTuDoc("Statement list or inner content of the list item body")),
            EField("ListItemDesc", GenTuDoc("Description part of the list item")),
            EField("DocBody", GenTuDoc("Toplevel document"))
        ]),
        Enum("OrgHorizontalDirection", GenTuDoc(""), [
            EField("ohdNone", GenTuDoc("No specific positioning requirements")),
            EField("ohdLeft", GenTuDoc("Align to the left")),
            EField("ohdRight", GenTuDoc("Align to the right")),
            EField("ohdCenter", GenTuDoc("Align to the center"))
        ]),
        Enum("OrgVerticalDirection", GenTuDoc(""), [
            EField("ovdNone", GenTuDoc("No specific positioning")),
            EField("ovdTop", GenTuDoc("Align to the top")),
            EField("ovdCenter", GenTuDoc("Center")),
            EField("ovdBottom", GenTuDoc("Bottom"))
        ]),
        Enum("OrgSpecName", GenTuDoc(""), [
            EField("Unnamed", GenTuDoc("")),
            EField("Result", GenTuDoc("")),
            EField("Year", GenTuDoc("")),
            EField("Day", GenTuDoc("")),
            EField("Clock", GenTuDoc("")),
            EField("Repeater", GenTuDoc("")),
            EField("Link", GenTuDoc("")),
            EField("Tags", GenTuDoc("")),
            EField("Tag", GenTuDoc("")),
            EField("State", GenTuDoc("")),
            EField("Protocol", GenTuDoc("")),
            EField("Desc", GenTuDoc("")),
            EField("Times", GenTuDoc("")),
            EField("Drawer", GenTuDoc("")),
            EField("Args", GenTuDoc("")),
            EField("Name", GenTuDoc("")),
            EField("Definition", GenTuDoc("")),
            EField("Body", GenTuDoc("")),
            EField("HeaderArgs", GenTuDoc("")),
            EField("File", GenTuDoc("")),
            EField("Kind", GenTuDoc("")),
            EField("Lang", GenTuDoc("")),
            EField("Prefix", GenTuDoc("")),
            EField("Text", GenTuDoc("")),
            EField("Todo", GenTuDoc("")),
            EField("Urgency", GenTuDoc("")),
            EField("Title", GenTuDoc("")),
            EField("Completion", GenTuDoc("")),
            EField("Head", GenTuDoc("")),
            EField("Subnodes", GenTuDoc("")),
            EField("Properties", GenTuDoc("")),
            EField("Logbook", GenTuDoc("")),
            EField("Description", GenTuDoc("")),
            EField("Logs", GenTuDoc("")),
            EField("Newstate", GenTuDoc("")),
            EField("Oldstate", GenTuDoc("")),
            EField("Time", GenTuDoc("")),
            EField("From", GenTuDoc("")),
            EField("EndArgs", GenTuDoc("")),
            EField("Flags", GenTuDoc("")),
            EField("Value", GenTuDoc("")),
            EField("Assoc", GenTuDoc("")),
            EField("Main", GenTuDoc("")),
            EField("Hash", GenTuDoc("")),
            EField("Bullet", GenTuDoc("")),
            EField("Counter", GenTuDoc("")),
            EField("Checkbox", GenTuDoc("")),
            EField("Header", GenTuDoc("")),
            EField("To", GenTuDoc("")),
            EField("Diff", GenTuDoc("")),
            EField("Property", GenTuDoc("")),
            EField("Subname", GenTuDoc("")),
            EField("Values", GenTuDoc("")),
            EField("Cells", GenTuDoc("")),
            EField("Rows", GenTuDoc("")),
            EField("Lines", GenTuDoc("")),
            EField("Chunks", GenTuDoc("")),
            EField("InheritanceMode", GenTuDoc("")),
            EField("MainSetRule", GenTuDoc("")),
            EField("SubSetRule", GenTuDoc(""))
        ]),
        Enum("OrgNodeKind", GenTuDoc(""), [
            EField("None", GenTuDoc("Default valye for node - invalid state")),
            EField("Document", GenTuDoc("Toplevel part of the ast, not created by parser, and only used in `semorg` stage")),
            EField("UserNode", GenTuDoc("User-defined node [[code:OrgUserNode]]")),
            EField("Empty", GenTuDoc("Empty node - valid state that does not contain any value")),
            EField(
                "Error",
                GenTuDoc("Failed node parse",
                    full="""
   Failed node parse - technically there are no /wrong/ syntax in the
   org-mode document because everything can be considered a one large
   word or a paragraph with flat `Word` content.

   Error node's extent covers all subnodes that were constructed
   during nested content parsing plus ErrorTerminator node with error
   token (description of the parsing failure). So failure node will be
   structured as `[Error <some content> <ErrorToken>
   <ErrorTermiator>]`. Second-to-last is the invalid token itself,
   error terminator will hold fake token that referes to an error.

   Error node can be produced by any parsing routine, although it is
   mostly used in the low-level text elements, since high-level
   structures are mostly detected based on the correct syntax - for
   example, `*** subtree` (and any title variations) can never be an
   error in itself. Title /text/ might contain an error, but invalid
   it is not possible to write an invalid subtree - it is either `*
   ANYTHING` or not a subtree at all.
   """)),
            EField("ErrorTerminator", GenTuDoc("Terminator node for failure in nested structure parsing")),
            EField("ErrorToken", GenTuDoc("Single invalid token")),
            EField("InlineStmtList", GenTuDoc("")),
            EField(
                "StmtList",
                GenTuDoc("List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together."
                   )),
            EField(
                "AssocStmtList",
                GenTuDoc("Associated list of statements - AST elements like commands and links are grouped together if placed on adjacent lines")
            ),
            EField("Subtree", GenTuDoc("Section subtree")),
            EField("SubtreeTimes", GenTuDoc("Time? associated with subtree entry")),
            EField("SubtreeStars", GenTuDoc("")),
            EField("Completion", GenTuDoc("Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio.")),
            EField("Checkbox", GenTuDoc("Single checkbox item like `[X]` or `[-]`")),
            EField("List", GenTuDoc("")),
            EField("Bullet", GenTuDoc("List item prefix")),
            EField("ListItem", GenTuDoc("")),
            EField("ListTag", GenTuDoc("Auxilliary wrapper for the paragraph placed at the start of the description list.")),
            EField("Counter", GenTuDoc("")),
            EField(
                "Comment",
                GenTuDoc("Inline or trailling comment. Can be used addition to `#+comment:` line or `#+begin-comment` section. Nested comment syntax is allowed (`#[ level1 #[ level2 ]# ]#`), but only outermost one is represented as separate AST node, everything else is a `.text`"
                   )),
            EField(
                "RawText",
                GenTuDoc("Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers "
                   )),
            EField(
                "Unparsed",
                GenTuDoc("Part of the org-mode document that is yet to be parsed. This node should not be created manually, it is only used for handling mutually recursive DSLs such as tables, which might include lists, which in turn might contain more tables in different bullet points."
                   )),
            EField("Command", GenTuDoc("Undefined single-line command -- most likely custom user-provided oe")),
            EField("CommandArguments", GenTuDoc("Arguments for the command block")),
            EField("CommandTitle", GenTuDoc("`#+title:` - full document title")),
            EField("CommandAuthor", GenTuDoc("`#+author:` Document author")),
            EField("CommandCreator", GenTuDoc("`#+creator:` Document creator")),
            EField("CommandInclude",
                   GenTuDoc("`#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk.")),
            EField("CommandLanguage", GenTuDoc("`#+language:`")),
            EField("CommandAttrHtml", GenTuDoc("`#+attr_html:`")),
            EField("CommandName", GenTuDoc("`#+name:` - name of the associated entry")),
            EField("CommandHeader", GenTuDoc("`#+header:` - extended list of parameters passed to associated block")),
            EField("CommandOptions", GenTuDoc("`#+options:` - document-wide formatting options")),
            EField("CommandTblfm", GenTuDoc("")),
            EField("CommandBackendOptions", GenTuDoc("Backend-specific configuration options like `#+latex_header` `#+latex_class` etc.")),
            EField("AttrImg", GenTuDoc("")),
            EField("CommandCaption", GenTuDoc("`#+caption:` command")),
            EField("File", GenTuDoc("")),
            EField("BlockExport", GenTuDoc("")),
            EField("InlineExport", GenTuDoc("")),
            EField(
                "MultilineCommand",
                GenTuDoc("Multiline command such as code block, latex equation, large block of passthrough code. Some built-in org-mode commands do not requires `#+begin` prefix, (such as `#+quote` or `#+example`) are represented by this type of block as well."
                   )),
            EField("Result", GenTuDoc("Command evaluation result")),
            EField(
                "Ident",
                GenTuDoc("regular identifier - `alnum + [-_]` characters for punctuation. Identifiers are compared and parsed in style-insensetive manner, meaning `CODE_BLOCK`, `code-block` and `codeblock` are identical."
                   )),
            EField("BareIdent", GenTuDoc("Bare identifier - any characters are allowed")),
            EField(
                "AdmonitionTag",
                GenTuDoc("Big ident used in conjunction with colon at the start of paragraph is considered an admonition tag: `NOTE: Text`, `WARNING: text` etc."
                   )),
            EField("BigIdent", GenTuDoc("full-uppsercase identifier such as `MUST` or `TODO`")),
            EField(
                "VerbatimMultilineBlock",
                GenTuDoc("Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks."
                   )),
            EField("CodeLine", GenTuDoc("Single line of source code")),
            EField("CodeText", GenTuDoc("Block of source code text")),
            EField("CodeTangle", GenTuDoc("Single tangle target in the code block")),
            EField("CodeCallout", GenTuDoc("`(refs:` callout in the source code")),
            EField("QuoteBlock", GenTuDoc("`#+quote:` block in code")),
            EField("AdmonitionBlock", GenTuDoc("")),
            EField("CenterBlock", GenTuDoc("'")),
            EField("Example", GenTuDoc("Verbatim example text block")),
            EField("SrcCode", GenTuDoc("Block of source code - can be multiline, single-line and")),
            EField(
                "SrcInlineCode",
                GenTuDoc("inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc."
                   )),
            EField("CallCode", GenTuDoc("Call to named source code block. Inline, multiline, or single-line.")),
            EField(
                "PassCode",
                GenTuDoc("Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively"
                   )),
            EField("CmdArguments", GenTuDoc("Command arguments")),
            EField("CmdFlag",
                   GenTuDoc("Flag for source code block. For example `-n`, which is used to to make source code block export with lines")),
            EField("CmdKey", GenTuDoc("")),
            EField("CmdValue", GenTuDoc("")),
            EField("CmdNamedValue", GenTuDoc("Key-value pair for source code block call.")),
            EField(
                "UrgencyStatus",
                GenTuDoc("Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`."
                   )),
            EField("TextSeparator", GenTuDoc("Long horizontal line `----`")),
            EField(
                "Paragraph",
                GenTuDoc("Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph"
                   )),
            EField(
                "AnnotatedParagraph",
                GenTuDoc("Annotated paragraph -- a wrapper around a regular paragraph kind with added admonition, footnote, list tag prefix and similar types. `[fn:ID] Some Text` is an annotated paragraph, just like `NOTE: Text` or `- Prefix :: Body` (in this case list header is an annotated paragraph)"
                   )),
            EField(
                "Bold",
                GenTuDoc("""Region of text with formatting, which contains standalone words -
     can itself contain subnodes, which allows to represent nested
     formatting regions, such as `*bold /italic/*` text. Particular type
     of identifier is stored in string form in `str` field for `OrgNode`
     -- bold is represented as `\"*\"`, italic as `/` and so on. In case
     of explicit open/close pairs only opening one is stored.

     NOTE: when structured sentences are enabled, regular punctuation
     elements like `some text (notes)` are also represented as `Word,
     Word, Markup(str: \"(\", [Word])` - e.g. structure is not fully flat.""")),
            EField("Italic", GenTuDoc("")),
            EField("Verbatim", GenTuDoc("")),
            EField("Backtick", GenTuDoc("")),
            EField("Underline", GenTuDoc("")),
            EField("Strike", GenTuDoc("")),
            EField("Quote", GenTuDoc("")),
            EField("Angle", GenTuDoc("")),
            EField("Monospace", GenTuDoc("")),
            EField("Par", GenTuDoc("")),
            EField(
                "InlineMath",
                GenTuDoc("Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\\(paren-wrapped\\)` inline text.")),
            EField("DisplayMath", GenTuDoc("Inline display latex math from `$$double-dollar$$` or `\\[bracket-wrapped\\]` code.")),
            EField("Space", GenTuDoc("Space or tab character in regular text")),
            EField("Punctuation", GenTuDoc("")),
            EField("Colon", GenTuDoc("")),
            EField(
                "Word",
                GenTuDoc("Regular word - technically not different from `orgIdent`, but defined separately to disiguish between places where special syntax is required and free-form text."
                   )),
            EField("Escaped", GenTuDoc("Escaped formatting character in the text")),
            EField("Newline", GenTuDoc("")),
            EField("SkipNewline", GenTuDoc("")),
            EField("SkipSpace", GenTuDoc("")),
            EField("SkipAny", GenTuDoc("")),
            EField("RawLink", GenTuDoc("Raw unwrapped link that was pasted in text")),
            EField(
                "Link",
                GenTuDoc("""External or internal link. Consists of one or two elements - target
     (url, file location etc.) and description (`orgParagraph` of text).
     Description might be empty, and represented as empty node in this
     case. For external links particular formatting of the address is
     not handled by parser and instead contains raw string from input
     text.""")),
            EField(
                "Macro",
                GenTuDoc("""Org-mode macro replacement - during export each macro is expanded
     and evaluated according to it's environment. Body of the macro is
     not parsed fully during org-mode evaluation, but is checked for
     correct parenthesis balance (as macro might contain elisp code)""")),
            EField(
                "BackendRaw",
                GenTuDoc("""Raw content to be passed to a particular backend. This is the most
     compact way of quoting export strings, after `#+<backend>:
     <single-backend-line>` and `#+begin-export <backend>`
     `<multiple-lines>`.""")),
            EField(
                "Symbol",
                GenTuDoc("Special symbol that should be exported differently to various backends - greek letters (`\alpha`), mathematical notations and so on."
                   )),
            EField("TimeAssoc", GenTuDoc("Time association pair for the subtree deadlines.")),
            EField("StaticActiveTime", GenTuDoc("")),
            EField("StaticInactiveTime", GenTuDoc("")),
            EField("DynamicActiveTime", GenTuDoc("")),
            EField(
                "DynamicInactiveTime",
                GenTuDoc("Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later"
                   )),
            EField("TimeRange", GenTuDoc("Date and time range format - two `orgDateTime` entries")),
            EField("SimpleTime", GenTuDoc("Result of the time range evaluation or trailing annotation a subtree")),
            EField("Details", GenTuDoc("`#+begin_details`  section")),
            EField("Summary", GenTuDoc("`#+begin_summary` section")),
            EField(
                "Table",
                GenTuDoc("""Org-mode table. Tables can be writtein in different formats, but in
   the end they are all represented using single ast type. NOTE: it is
   not guaranteed that all subnodes for table are exactly
   `orgTableRow` - sometimes additional property metadata might be
   used, making AST like `Table[AssocStmtList[Command[_],
   TableRow[_]]]` possible""")),
            EField("TableRow", GenTuDoc("Horizontal table row")),
            EField("TableCell", GenTuDoc("Single cell in row. Might contain anyting, including other tables, simple text paragraph etc.")),
            EField("InlineFootnote", GenTuDoc("Inline footnote with text placed directly in the node body.")),
            EField(
                "Footnote",
                GenTuDoc("Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node."
                   )),
            EField("Horizontal",
                   GenTuDoc("Horizotal rule. Rule body might contain other subnodes, to represnt `---- some text ----` kind of formatting.")),
            EField("Filetags", GenTuDoc("`#+filetags:` line command")),
            EField(
                "OrgTag",
                GenTuDoc("""Original format of org-mode tags in form of `:tagname:`. Might
   contain one or mode identifgiers, but does not provide support for
   nesting - `:tag1:tag2:`. Can only be placed within restricted set
   of places such as subtree headings and has separate place in AST
   when allowed (`orgSubtree` always has subnode `№4` with either
   `orgEmpty` or `orgOrgTag`)""")),
            EField(
                "HashTag",
                GenTuDoc("""More commonly used `#hashtag` format, with some additional
   extension. Can be placed anywere in the document (including section
   headers), but does not have separate place in AST (e.g. considered
   regular part of the text)""")),
            EField("MetaSymbol", GenTuDoc("`\\sym{}` with explicit arguments")),
            EField("AtMention", GenTuDoc("`@user`")),
            EField(
                "BracTag",
                GenTuDoc("Custom extension to org-mode. Similarly to `BigIdent` used to have something like informal keywords `MUST`, `OPTIONAL`, but instead aimed /specifically/ at commit message headers - `[FEATURE]`, `[FIX]` and so on."
                   )),
            EField("Drawer", GenTuDoc("Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`")),
            EField("LatexClass", GenTuDoc("")),
            EField("LatexHeader", GenTuDoc("")),
            EField("LatexCompiler", GenTuDoc("")),
            EField("LatexClassOptions", GenTuDoc("")),
            EField("HtmlHead", GenTuDoc("")),
            EField("Columns",
                   GenTuDoc("`#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis.")),
            EField("PropertyList", GenTuDoc("")),
            EField("Property", GenTuDoc("Property entry, either in `#+property:` command, or in `:property:` drawer")),
            EField("Placeholder", GenTuDoc("Placeholder entry in text, usually writte like `<text to replace>`")),
            EField("SubtreeDescription", GenTuDoc("`:description:` entry")),
            EField("SubtreeUrgency", GenTuDoc("")),
            EField("Logbook", GenTuDoc("`:logbook:` entry storing note information")),
            EField("LogbookEntry", GenTuDoc("")),
            EField("LogbookStateChange", GenTuDoc("Annotation about change in the subtree todo state")),
            EField("LogbookNote", GenTuDoc("Timestamped log note on the subtree")),
            EField("LogbookClock", GenTuDoc("`CLOCK` entry in the subtree")),
            EField("LogbookRefile", GenTuDoc("`Refile` entry in the subtree logbook drawer")),
            EField("LogbookPriority", GenTuDoc("Change in the subtree priority")),
            EField("LogbookPriorityChangeAction", GenTuDoc("Action to change subtree")),
            EField("LogbookReschedule", GenTuDoc("")),
            EField("LogbookTagChange", GenTuDoc("")),
            EField("LogbookTagChangeAction", GenTuDoc("")),
            EField("RadioTarget", GenTuDoc("`<<<RADIO>>>`")),
            EField("Target", GenTuDoc("`<<TARGET>>`"))
        ]),
        Enum("OrgTextContext", GenTuDoc(""), [
            EField("otcPlain", GenTuDoc("")),
            EField("otcSubtree0", GenTuDoc("")),
            EField("otcSubtree1", GenTuDoc("")),
            EField("otcSubtree2", GenTuDoc("")),
            EField("otcSubtree3", GenTuDoc("")),
            EField("otcSubtree4", GenTuDoc("")),
            EField("otcSubtree5", GenTuDoc("")),
            EField("otcSubtree6", GenTuDoc("")),
            EField("otcSubtree7", GenTuDoc("")),
            EField("otcSubtree8", GenTuDoc("")),
            EField("otcSubtree9", GenTuDoc("")),
            EField("otcSubtree10", GenTuDoc("")),
            EField("otcSubtree11", GenTuDoc("")),
            EField("otcSubtree12", GenTuDoc("")),
            EField("otcSubtreeOther", GenTuDoc("")),
            EField("otcBold", GenTuDoc("")),
            EField("otcItalic", GenTuDoc("")),
            EField("otcStrike", GenTuDoc("")),
            EField("otcUnderline", GenTuDoc("")),
            EField("otcMonospaceInline", GenTuDoc("")),
            EField("otcMonospaceBlock", GenTuDoc(""))
        ]),
        Enum(
            "OrgBigIdentKind",
            GenTuDoc(""),
            [
                EField("None", GenTuDoc("")),
                EField(
                    "Must",
                    GenTuDoc("MUST This word, or the terms \"REQUIRED\" or \"SHALL\", mean that the definition is an absolute requirement of the specification."
                       )),
                EField(
                    "MustNot",
                    GenTuDoc("MUST NOT This phrase, or the phrase \"SHALL NOT\", mean that the definition is an absolute prohibition of the specification."
                       )),
                EField(
                    "Should",
                    GenTuDoc("""SHOULD This word, or the adjective \"RECOMMENDED\", mean that there
   may exist valid reasons in particular circumstances to ignore a
   particular item, but the full implications must be understood and
   carefully weighed before choosing a different course.""")),
                EField(
                    "ShouldNot",
                    GenTuDoc("""SHOULD NOT This phrase, or the phrase \"NOT RECOMMENDED\" mean that
   there may exist valid reasons in particular circumstances when the
   particular behavior is acceptable or even useful, but the full
   implications should be understood and the case carefully weighed
   before implementing any behavior described with this label.""")),
                EField("Required", GenTuDoc("")),
                EField(
                    "Optional",
                    GenTuDoc("""MAY This word, or the adjective \"OPTIONAL\", mean that an item is
   truly optional. One vendor may choose to include the item because a
   particular marketplace requires it or because the vendor feels that
   it enhances the product while another vendor may omit the same
   item. An implementation which does not include a particular option
   MUST be prepared to interoperate with another implementation which
   does include the option, though perhaps with reduced functionality.
   In the same vein an implementation which does include a particular
   option MUST be prepared to interoperate with another implementation
   which does not include the option (except, of course, for the
   feature the option provides.)""")),
                EField("ReallyShouldNot", GenTuDoc("")),
                EField("OughtTo", GenTuDoc("")),
                EField("WouldProbably", GenTuDoc("")),
                EField("MayWishTo", GenTuDoc("")),
                EField("Could", GenTuDoc("")),
                EField("Might", GenTuDoc("")),
                EField("Possible", GenTuDoc("")),
                EField("Todo", GenTuDoc("")),
                EField("Idea", GenTuDoc("")),
                EField("Error", GenTuDoc("")),
                EField("Fixme", GenTuDoc("")),
                EField("Doc", GenTuDoc("")),
                EField("Refactor", GenTuDoc("")),
                EField("Review", GenTuDoc("")),
                EField("Hack", GenTuDoc("")),
                EField("Implement", GenTuDoc("")),
                EField("Example", GenTuDoc("")),
                EField("Question", GenTuDoc("")),
                EField("Assume", GenTuDoc("")),
                EField("Internal", GenTuDoc("")),
                EField("Design", GenTuDoc("")),
                EField("Why", GenTuDoc("")),
                EField("Wip", GenTuDoc("")),
                EField("Fix", GenTuDoc("")),
                EField("Clean", GenTuDoc("")),
                EField("Feature", GenTuDoc("")),
                EField("Style", GenTuDoc("")),
                EField("Repo", GenTuDoc("")),
                EField("Skip", GenTuDoc("")),
                EField("Break", GenTuDoc("")),
                EField("Poc", GenTuDoc("")),
                EField("Next", GenTuDoc("")),
                EField("Later", GenTuDoc("")),
                EField("Postponed", GenTuDoc("")),
                EField("Stalled", GenTuDoc("")),
                EField("Done", GenTuDoc("")),
                EField("Partially", GenTuDoc("")),
                EField("Cancelled", GenTuDoc("")),
                EField("Failed", GenTuDoc("")),
                EField("Note", GenTuDoc("")),
                EField("Tip", GenTuDoc("")),
                EField("Important", GenTuDoc("")),
                EField("Caution", GenTuDoc("")),
                EField("Warning", GenTuDoc("")),
                EField("UserCodeComment", GenTuDoc("User-defined comment message")),
                EField("UserCommitMsg", GenTuDoc("User-defined commit message ident")),
                EField("UserTaskState", GenTuDoc("User-defined task state")),
                EField("UserAdmonition", GenTuDoc("User-defined admonition label")),
                EField("Other", GenTuDoc("User-defined big-idents, not included in default set.")),
                # ;; It is not hard to support
                # ;; https://en.wikipedia.org/wiki/Structured_English keywords. Maybe I
                # ;; will merge it with haxdoc somehow, maybe not, for not I just placed
                # ;; them here as a reminder to myself. My current idea is to overlay
                # ;; semi-structured explanation in the documenation with actual code.
                # ;; Structured keywords can be used as an anchor points (e.g. `IF` maps
                # ;; to real condition, `THEN` to the body and so on).
                EField("StructIf", GenTuDoc("")),
                EField("StructAnd", GenTuDoc("")),
                EField("StructOr", GenTuDoc("")),
                EField("StructNot", GenTuDoc("")),
                EField("StructGet", GenTuDoc("")),
                EField("StructSet", GenTuDoc("")),
                EField("StructThen", GenTuDoc("")),
                EField("StructElse", GenTuDoc("")),
                EField("StructWhile", GenTuDoc(""))
            ]),
        Enum("OrgTokenKind", GenTuDoc(""), [
            EField("None", GenTuDoc("")),
            EField("Eof", GenTuDoc("")),
            EField("GroupStart", GenTuDoc("Start of the tokenizer token group")),
            EField("GroupEnd", GenTuDoc("Tokenizer token group end")),
            EField("ErrorTerminator", GenTuDoc("")),
            EField("CommandPrefix", GenTuDoc("")),
            EField("LineCommand", GenTuDoc("")),
            EField(
                "CommandBegin",
                GenTuDoc("`#+begin` part of the multiline command. `begin_<block-type>` is split into two tokens - `begin_` prefix and `ockBegin<block-type>` section."
                   )),
            EField("CommandEnd", GenTuDoc("")),
            EField("DoubleColon", GenTuDoc("")),
            EField("Text", GenTuDoc("")),
            EField("StmtList", GenTuDoc("Unlexed group of statements - used in the list content to enable secondary parsing.")),
            EField("StmtListOpen", GenTuDoc("Start of the expanded statement list content")),
            EField("StmtListClose", GenTuDoc("End of the expanded statement list content")),
            EField("ListStart", GenTuDoc("Start of the list token group")),
            EField("ListItemStart", GenTuDoc("Start of the list item element")),
            EField("ListClock", GenTuDoc("`CLOCK:` entry at the start of the logbook entry list")),
            EField("ListPlus", GenTuDoc("")),
            EField("ListStar", GenTuDoc("")),
            EField("ListDescOpen", GenTuDoc("Start of the description list key,")),
            EField("ListDescClose", GenTuDoc("End of the description list key `::`")),
            EField("ListItemEnd", GenTuDoc("End of the list item")),
            EField("ListEnd", GenTuDoc("Complete end of the list token group")),
            EField("Checkbox", GenTuDoc("List or subtree checkbox")),
            EField("SubtreeTodoState", GenTuDoc("")),
            EField("SubtreeUrgency", GenTuDoc("Subtree importance marker")),
            EField("SubtreeCompletion", GenTuDoc("Subtree completion marker")),
            EField("SubtreeStars", GenTuDoc("Subtree prefix")),
            EField("SubtreeTagSeparator", GenTuDoc("")),
            EField("SubtreeTime", GenTuDoc("")),
            EField("SubtreeEnd", GenTuDoc("")),
            EField(
                "ImplicitTime",
                GenTuDoc("""You can write time ranges without any additional formatting for
   subtrees that have a diary timestamps. For example, you have a
   complex date predicate, but event occurs for `18:00-21:00`, so you
   write it in the random place in the subtree.""")),
            EField("TimeDuration", GenTuDoc("Time duration for the `effort` property or time range length evaluation")),
            EField("InactiveTimeBegin", GenTuDoc("Start of the inactive timestamp (`[2022-03-12]`)")),
            EField("InactiveTimeEnd", GenTuDoc("")),
            EField("ActiveTimeBegin", GenTuDoc("Start of the active timestamp `<2030-02-03>`")),
            EField("ActiveTimeEnd", GenTuDoc("")),
            EField("DynamicTimeContent", GenTuDoc("Dynamic time content")),
            EField("StaticTimeDatePart", GenTuDoc("year-month-day part of the timestamp")),
            EField("StaticTimeDayPart", GenTuDoc("weekday part of the timestamp")),
            EField("StaticTimeClockPart", GenTuDoc("Clock part of the timestamp")),
            EField("StaticTimeRepeater", GenTuDoc("Type of the time repeater: `+`, `++`, `.+`")),
            EField("TimeDash", GenTuDoc("Separator dash between two periods in the time range (`<start>--<finish.`)")),
            EField("TimeArrow", GenTuDoc("Time range evaluation arrow `[from]--[to] =>`")),
            EField("Comment", GenTuDoc("line or inline comment")),
            EField("ListDoubleColon", GenTuDoc("Double colon between description list tag and body")),
            EField("CommandArgumentsBegin", GenTuDoc("List of command arguments")),
            EField("CommandArgumentsEnd", GenTuDoc("End of the command arguments list")),
            EField("CommandKey", GenTuDoc("")),
            EField("CommandValue", GenTuDoc("")),
            EField("CommandFlag", GenTuDoc("")),
            EField("CommandBracket", GenTuDoc("`#+results[HASH...]`")),
            EField("ColonLiteral", GenTuDoc("Literal block with `:`")),
            EField("ColonIdent", GenTuDoc("Drawer or source code block wrappers with colon-wrapped identifiers. `:results:`, `:end:` etc.")),
            EField("ColonProperties", GenTuDoc("Start of the `:PROPERTIES:` block drawer block")),
            EField("ColonDescription", GenTuDoc("Start of the `:description:` drawer block")),
            EField("ColonEnd", GenTuDoc("")),
            EField("ColonLogbook", GenTuDoc("")),
            EField("RawLogbook", GenTuDoc("")),
            EField("LogbookStart", GenTuDoc("")),
            EField("LogbookEnd", GenTuDoc("")),
            EField("RawProperty", GenTuDoc("")),
            EField("Link", GenTuDoc("Any kind of link")),
            EField("CommandContentStart", GenTuDoc("")),
            EField("CommandContentEnd", GenTuDoc("")),
            EField("CodeContent", GenTuDoc("Block of code inside `#+begin_src`")),
            EField("CodeContentBegin", GenTuDoc("Start of the expanded code content")),
            EField("CodeContentEnd", GenTuDoc("End of the expanded code content")),
            EField(
                "CodeText",
                GenTuDoc("Uninterrupted text span without newlines - either a whole line or sub subsection of it if callout or tangle elements were detected"
                   )),
            EField("TableContent", GenTuDoc("Block of text inside `#+table`")),
            EField("QuoteContent", GenTuDoc("`#+quote` content")),
            EField("BackendPass", GenTuDoc("Backend-specific passthrough")),
            EField("LogBook", GenTuDoc("Logbook including content")),
            EField("Drawer", GenTuDoc("Drawer including content")),
            EField("Indent", GenTuDoc("Increase in indentation")),
            EField("Dedent", GenTuDoc("Decrease in indentation")),
            EField("SameIndent", GenTuDoc("")),
            EField("NoIndent", GenTuDoc("")),
            EField("BoldOpen", GenTuDoc("")),
            EField("BoldClose", GenTuDoc("")),
            EField("BoldInline", GenTuDoc("")),
            EField("BoldInlineOpen", GenTuDoc("")),
            EField("BoldInlineClose", GenTuDoc("")),
            EField("ItalicOpen", GenTuDoc("")),
            EField("ItalicClose", GenTuDoc("")),
            EField("ItalicInline", GenTuDoc("")),
            EField("ItalicInlineOpen", GenTuDoc("")),
            EField("ItalicInlineClose", GenTuDoc("")),
            EField("VerbatimOpen", GenTuDoc("")),
            EField("VerbatimClose", GenTuDoc("")),
            EField("VerbatimInline", GenTuDoc("")),
            EField("VerbatimInlineOpen", GenTuDoc("")),
            EField("VerbatimInlineClose", GenTuDoc("")),
            EField("MonospaceOpen", GenTuDoc("")),
            EField("MonospaceClose", GenTuDoc("")),
            EField("MonospaceInline", GenTuDoc("")),
            EField("MonospaceInlineOpen", GenTuDoc("")),
            EField("MonospaceInlineClose", GenTuDoc("")),
            EField("BacktickOpen", GenTuDoc("")),
            EField("BacktickClose", GenTuDoc("")),
            EField("BacktickInline", GenTuDoc("")),
            EField("BacktickInlineOpen", GenTuDoc("")),
            EField("BacktickInlineClose", GenTuDoc("")),
            EField("UnderlineOpen", GenTuDoc("")),
            EField("UnderlineClose", GenTuDoc("")),
            EField("UnderlineInline", GenTuDoc("")),
            EField("UnderlineInlineOpen", GenTuDoc("")),
            EField("UnderlineInlineClose", GenTuDoc("")),
            EField("StrikeOpen", GenTuDoc("")),
            EField("StrikeClose", GenTuDoc("")),
            EField("StrikeInline", GenTuDoc("")),
            EField("StrikeInlineOpen", GenTuDoc("")),
            EField("StrikeInlineClose", GenTuDoc("")),
            EField("QuoteOpen", GenTuDoc("")),
            EField("QuoteClose", GenTuDoc("")),
            EField("Punctuation", GenTuDoc("")),
            EField("LinkOpen", GenTuDoc("")),
            EField("LinkClose", GenTuDoc("")),
            EField("RawUrl", GenTuDoc("")),
            EField("LinkTargetOpen", GenTuDoc("")),
            EField("LinkTargetClose", GenTuDoc("")),
            EField("LinkInternal", GenTuDoc("No protocol is used in the link, it is targeting some internal named entry.")),
            EField("LinkProtocol", GenTuDoc("Protocol used by the link - `file:`, `https:` etc.")),
            EField(
                "LinkFull",
                GenTuDoc("Full token for the link, used in cases where it does not make sense to fracture the token - regular https URLs etc.")),
            EField("LinkPath", GenTuDoc("Link path for searches in file")),
            EField(
                "LinkTarget",
                GenTuDoc("Target of the link protocol that does not follow regular URI encoding scheme - for example `id:`, `elisp`, or `shell` links."
                   )),
            EField("LinkExtraSeparator", GenTuDoc("Separator of the extra content in the link, `::`")),
            EField("LinkExtra", GenTuDoc("Additional parametrization for the link search")),
            EField("LinkDescriptionOpen", GenTuDoc("")),
            EField("LinkDescriptionClose", GenTuDoc("")),
            EField("TextSeparator", GenTuDoc("")),
            EField("ParagraphStart", GenTuDoc("Fake token inserted by the lexer to delimit start of the paragraph")),
            EField("ParagraphEnd", GenTuDoc("")),
            EField("FootnoteStart", GenTuDoc("")),
            EField("FootnoteEnd", GenTuDoc("")),
            EField("Word", GenTuDoc("Regular word in the paragraph")),
            EField(
                "Escaped",
                GenTuDoc("Escaped character in plain text - `\\*`, `\\/` etc. Escaped characters and sequences thereof are treated like a regular plain text."
                   )),
            EField(
                "DoubleSlash",
                GenTuDoc("Put at the end of the lexer first logbook line to separate the  note, otherwise is treated as standalone escaped slash."
                   )),
            EField("Newline", GenTuDoc("Explicit newline a paragraph")),
            EField("SkipSpace", GenTuDoc("")),
            EField("SkipNewline", GenTuDoc("")),
            EField("SkipAny", GenTuDoc("")),
            EField("MaybeWord", GenTuDoc("")),
            EField("Space", GenTuDoc("Space in the paragraph")),
            EField("BigIdent", GenTuDoc("`TODO`, `NOTE` and similar capitalized words")),
            EField("RawText", GenTuDoc("Unparsed raw text, either as a part of paragraph or some embedded construction such as link address.")),
            EField("InlineSrc", GenTuDoc("Start of an inline source code block: `src_nim[]{}`")),
            EField("InlineCall", GenTuDoc("Start of an inline call block: `call_name[]{}`")),
            EField("CurlyStart", GenTuDoc("Start of the curly section of an inline source/call")),
            EField("CurlyEnd", GenTuDoc("End of the curly section of an inline source/call")),
            EField("SymbolStart", GenTuDoc("Unquoted `\\symbol` directly in the text")),
            EField("Ident", GenTuDoc("")),
            EField("DollarOpen", GenTuDoc("Opening dollar inline latex math")),
            EField("DollarClose", GenTuDoc("Closing dollar for inline latex math")),
            EField("DoubleDollarOpen", GenTuDoc("Opening `$` for inline latex")),
            EField("DoubleDollarClose", GenTuDoc("Closing `$` for inline latex")),
            EField("LatexParOpen", GenTuDoc("Opening `\\(` for inline latex math")),
            EField("LatexParClose", GenTuDoc("Closing `\\)` for inline latex math")),
            EField("LatexBraceOpen", GenTuDoc("Opening `\\[` for inline display latex equation")),
            EField("LatexBraceClose", GenTuDoc("Closing `\\]` for inline display latex equation")),
            EField("LatexInlineRaw", GenTuDoc("Content of the brace/par-enclosed math")),
            EField("DoubleAt", GenTuDoc("Inline backend passthrough `@@`")),
            EField("AtBracket", GenTuDoc("Inline annotation")),
            EField("AtMention", GenTuDoc("`@user` mention in the text")),
            EField("HashTag", GenTuDoc("Start of the inline hashtag `#tag`")),
            EField("HashTagSub", GenTuDoc("Nested hashtag separator")),
            EField("HashTagOpen", GenTuDoc("Start of the nested hashtag grop bracket")),
            EField("HashTagClose", GenTuDoc("End of the nested hashtag group separator")),
            EField("Comma", GenTuDoc("Comma - punctuation or a syntax element (e.g. for macro arguments)")),
            EField("ParOpen", GenTuDoc("Paren open - punctuation or a syntax element")),
            EField("ParClose", GenTuDoc("Paren close - punctuation or a syntax element")),
            EField("Colon", GenTuDoc("")),
            EField("Circumflex", GenTuDoc("`^` possible superscript in the text")),
            EField("MacroOpen", GenTuDoc("Start of the macro call `{{{`")),
            EField("MacroClose", GenTuDoc("Close of the macro call `}}}`")),
            EField("MetaBraceOpen", GenTuDoc("")),
            EField("MetaBraceBody", GenTuDoc("")),
            EField("MetaBraceClose", GenTuDoc("")),
            EField("MetaArgsOpen", GenTuDoc("")),
            EField("MetaArgsBody", GenTuDoc("")),
            EField("MetaArgsClose", GenTuDoc("")),
            EField("SrcOpen", GenTuDoc("")),
            EField("SrcName", GenTuDoc("")),
            EField("SrcArgs", GenTuDoc("")),
            EField("SrcBody", GenTuDoc("")),
            EField("SrcClose", GenTuDoc("")),
            EField("CallOpen", GenTuDoc("")),
            EField("CallName", GenTuDoc("")),
            EField("CallInsideHeader", GenTuDoc("")),
            EField("CallArgs", GenTuDoc("")),
            EField("EndHeader", GenTuDoc("")),
            EField("CallClose", GenTuDoc("")),
            EField("CmdArguments", GenTuDoc("")),
            EField("TableBegin", GenTuDoc("")),
            EField("TableEnd", GenTuDoc("")),
            EField("CellBody", GenTuDoc("Unformatted table cell body")),
            EField("RowSpec", GenTuDoc("`#+row` command together with parameters")),
            EField("CellSpec", GenTuDoc("`#+cell` command with parameters")),
            EField("Content", GenTuDoc("Temporary token created during initial content lexing")),
            EField("ContentStart", GenTuDoc("Start of the table cell content section")),
            EField("ContentEnd", GenTuDoc("End of the table cell content section")),
            EField("PipeOpen", GenTuDoc("")),
            EField("PipeSeparator", GenTuDoc("Vertical pipe (`|`) cell separator")),
            EField("PipeClose", GenTuDoc("")),
            EField("PipeCellOpen", GenTuDoc("")),
            EField("DashSeparator", GenTuDoc("Horizontal dash (`---`, `:---`, `---:` or `:---:`) row separator")),
            EField("CornerPlus", GenTuDoc("Corner plus (`+`)")),
            EField("Command", GenTuDoc("")),
            EField("CommandArgs", GenTuDoc("")),
            EField("Body", GenTuDoc("")),
            EField("LangName", GenTuDoc("")),
            EField("DoubleAngleOpen", GenTuDoc("`<<` - open for noweb or anchor placeholder")),
            EField("DoubleAngleClose", GenTuDoc("`>>` - close for noweb or anchor placeholder")),
            EField("TripleAngleOpen", GenTuDoc("`<<<` - radio target open")),
            EField("TripleAngleClose", GenTuDoc("`>>>` - radio target close")),
            EField("AngleOpen", GenTuDoc("Placeholder open")),
            EField("AngleClose", GenTuDoc("Placeholder close")),
            EField(
                "TextBlock",
                GenTuDoc("Code before noweb placeholder. Requires separate token to handle `##<<commented>>` - prefix comment should be duplicated for each line of the placeholder expansion."
                   ))
        ]),
        Enum("OrgCommandKind", GenTuDoc(""), [
            EField("None", GenTuDoc("")),
            EField("Include", GenTuDoc("")),
            EField("Filetags", GenTuDoc("")),
            EField("Setupfile", GenTuDoc("")),
            EField("Columns", GenTuDoc("")),
            EField("OtherProperty", GenTuDoc("")),
            EField("BeginTable", GenTuDoc("")),
            EField("EndTable", GenTuDoc("`#+table`")),
            EField("Row", GenTuDoc("`#+row`")),
            EField("Cell", GenTuDoc("`#+cell`")),
            EField("BeginAdmonition", GenTuDoc("")),
            EField("EndAdmonition", GenTuDoc("")),
            EField("BeginDynamic", GenTuDoc("")),
            EField("EndDynamic", GenTuDoc("`#+begin:`")),
            EField("BeginCenter", GenTuDoc("")),
            EField("EndCenter", GenTuDoc("`#+begin_center`")),
            EField("BeginQuote", GenTuDoc("")),
            EField("EndQuote", GenTuDoc("`#+quote`")),
            EField("BeginSrc", GenTuDoc("")),
            EField("EndSrc", GenTuDoc("`#+begin_src`")),
            EField("BeginExport", GenTuDoc("")),
            EField("EndExport", GenTuDoc("`#+end_export`")),
            EField("BeginExample", GenTuDoc("")),
            EField("EndExample", GenTuDoc("")),
            EField("BeginDetails", GenTuDoc("")),
            EField("EndDetails", GenTuDoc("")),
            EField("BeginSummary", GenTuDoc("")),
            EField("EndSummary", GenTuDoc("")),
            EField("LatexClassOptions", GenTuDoc("`#+latex_class_options`")),
            EField("LatexClass", GenTuDoc("")),
            EField("LatexCompiler", GenTuDoc("")),
            EField("AttrLatex", GenTuDoc("`#+attr_latex:`")),
            EField("AttrImg", GenTuDoc("`#+attr_img:`")),
            EField("AttrHtml", GenTuDoc("`#+attr_html:`")),
            EField("HtmlHead", GenTuDoc("`#+html_head:`")),
            EField("Language", GenTuDoc("`#+language:`")),
            EField("Options", GenTuDoc("`#+options: `")),
            EField("Title", GenTuDoc("`#+title:`")),
            EField("Property", GenTuDoc("`#+property:`")),
            EField("Author", GenTuDoc("`#+author:`")),
            EField("Bind", GenTuDoc("`#+bind:`")),
            EField("Creator", GenTuDoc("`#+creator:`")),
            EField("LatexHeader", GenTuDoc("`#+latex_header`")),
            EField("Results", GenTuDoc("`#+results:`")),
            EField("Call", GenTuDoc("`#+call:`")),
            EField("Name", GenTuDoc("`#+name:`")),
            EField("Caption", GenTuDoc("`#+caption:`")),
            EField("Header", GenTuDoc("`#+header:`")),
            EField("TableFormula", GenTuDoc("`#+tblfm:`")),
        ]),
        Enum("OrgPropertyKind", GenTuDoc(""), [
            EField("Title", GenTuDoc("")),
            EField("Author", GenTuDoc("")),
            EField("Date", GenTuDoc("")),
            EField("Email", GenTuDoc("")),
            EField("Language", GenTuDoc("")),
            EField("Url", GenTuDoc("")),
            EField("SourceUrl", GenTuDoc("")),
            EField("AttrImg", GenTuDoc("")),
            EField("Toplevel", GenTuDoc("")),
            EField("Blocker", GenTuDoc("")),
            EField("Created", GenTuDoc("")),
            EField("Unnumbered", GenTuDoc("")),
            EField("Trigger", GenTuDoc("")),
            EField("Ordered", GenTuDoc("")),
            EField("Noblocking", GenTuDoc("")),
            EField("ExportOptions", GenTuDoc("")),
            EField("BackendExportOptions", GenTuDoc("")),
            EField("AttrBackend", GenTuDoc("")),
            EField("ColumnSpec", GenTuDoc("")),
            EField("Name", GenTuDoc("")),
            EField("Caption", GenTuDoc("")),
            EField("LinkAbbrev", GenTuDoc("")),
            EField("Filetags", GenTuDoc("")),
            EField("TagConf", GenTuDoc("")),
            EField("LatexHeader", GenTuDoc("")),
            EField("OtherProperty", GenTuDoc("")),
            EField("Id", GenTuDoc(""))
        ]),
        Enum(
            "OrgUnnumberedKind", GenTuDoc(""),
            [EField("Notoc", GenTuDoc("")), EField("True", GenTuDoc("")), EField("False", GenTuDoc(""))]),
        Enum("OrgBlockLexerState", GenTuDoc(""), [
            EField("None", GenTuDoc("")),
            EField("InHeader", GenTuDoc("")),
            EField("InBody", GenTuDoc("")),
            EField("Ended", GenTuDoc("")),
            EField("Complete", GenTuDoc(""))
        ])
    ]


def get_nlp_enums():
    return [
        Enum("NlpDepKind", GenTuDoc("Dependency kind"), [
            EField("ROOT", GenTuDoc("")),
            EField("acl", GenTuDoc("")),
            EField("advcl", GenTuDoc("")),
            EField("advmod", GenTuDoc("")),
            EField("amod", GenTuDoc("")),
            EField("appos", GenTuDoc("")),
            EField("aux", GenTuDoc("")),
            EField("_case", GenTuDoc("")),
            EField("cc", GenTuDoc("")),
            EField("ccomp", GenTuDoc("")),
            EField("compound", GenTuDoc("")),
            EField("conj", GenTuDoc("")),
            EField("cop", GenTuDoc("")),
            EField("csubj", GenTuDoc("")),
            EField("dep", GenTuDoc("")),
            EField("det", GenTuDoc("")),
            EField("discourse", GenTuDoc("")),
            EField("expl", GenTuDoc("")),
            EField("fixed", GenTuDoc("")),
            EField("iobj", GenTuDoc("")),
            EField("mark", GenTuDoc("")),
            EField("nmod", GenTuDoc("")),
            EField("nsubj", GenTuDoc("")),
            EField("nummod", GenTuDoc("")),
            EField("obj", GenTuDoc("")),
            EField("obl", GenTuDoc("")),
            EField("parataxis", GenTuDoc("")),
            EField("punct", GenTuDoc("")),
            EField("ref", GenTuDoc("")),
            EField("xcomp", GenTuDoc("")),
        ]),
        Enum("NlpPosTag", GenTuDoc("Part of speech tag"), [
            EField("ADJP", GenTuDoc("")),
            EField("ADVP", GenTuDoc("")),
            EField("ADD", GenTuDoc("")),
            EField("AFX", GenTuDoc("")),
            EField("CC", GenTuDoc("")),
            EField("CD", GenTuDoc("")),
            EField("CONJP", GenTuDoc("")),
            EField("DT", GenTuDoc("")),
            EField("EX", GenTuDoc("")),
            EField("FRAG", GenTuDoc("")),
            EField("FW", GenTuDoc("")),
            EField("HYPH", GenTuDoc("")),
            EField("IN", GenTuDoc("")),
            EField("INTJ", GenTuDoc("")),
            EField("JJ", GenTuDoc("")),
            EField("JJR", GenTuDoc("")),
            EField("JJS", GenTuDoc("")),
            EField("LRB", GenTuDoc("")),
            EField("LS", GenTuDoc("")),
            EField("LST", GenTuDoc("")),
            EField("MD", GenTuDoc("")),
            EField("META", GenTuDoc("")),
            EField("NAC", GenTuDoc("")),
            EField("NFP", GenTuDoc("")),
            EField("NML", GenTuDoc("")),
            EField("NN", GenTuDoc("")),
            EField("NNP", GenTuDoc("")),
            EField("NNPS", GenTuDoc("")),
            EField("NNS", GenTuDoc("")),
            EField("NP", GenTuDoc("")),
            EField("NPS", GenTuDoc("")),
            EField("NP_TMP", GenTuDoc("")),
            EField("PDT", GenTuDoc("")),
            EField("POS", GenTuDoc("")),
            EField("PP", GenTuDoc("")),
            EField("PPZ", GenTuDoc("")),
            EField("PRN", GenTuDoc("")),
            EField("PRP", GenTuDoc("")),
            EField("PRT", GenTuDoc("")),
            EField("PUNCT_COLON", GenTuDoc("")),
            EField("PUNCT_COMMA", GenTuDoc("")),
            EField("PUNCT_PERIOD", GenTuDoc("")),
            EField("PUNCT_QUOTE_CLOSE", GenTuDoc("")),
            EField("PUNCT_QUOTE_OPEN", GenTuDoc("")),
            EField("QP", GenTuDoc("")),
            EField("RB", GenTuDoc("")),
            EField("RBR", GenTuDoc("")),
            EField("RBS", GenTuDoc("")),
            EField("ROOT", GenTuDoc("")),
            EField("RP", GenTuDoc("")),
            EField("RRB", GenTuDoc("")),
            EField("RRC", GenTuDoc("")),
            EField("S", GenTuDoc("")),
            EField("SBAR", GenTuDoc("")),
            EField("SBARQ", GenTuDoc("")),
            EField("SENT", GenTuDoc("")),
            EField("SINV", GenTuDoc("")),
            EField("SQ", GenTuDoc("")),
            EField("SYM", GenTuDoc("")),
            EField("TO", GenTuDoc("")),
            EField("UCP", GenTuDoc("")),
            EField("UH", GenTuDoc("")),
            EField("VB", GenTuDoc("")),
            EField("VBD", GenTuDoc("")),
            EField("VBG", GenTuDoc("")),
            EField("VBN", GenTuDoc("")),
            EField("VBP", GenTuDoc("")),
            EField("VBZ", GenTuDoc("")),
            EField("VH", GenTuDoc("")),
            EField("VHD", GenTuDoc("")),
            EField("VHG", GenTuDoc("")),
            EField("VHN", GenTuDoc("")),
            EField("VHP", GenTuDoc("")),
            EField("VHZ", GenTuDoc("")),
            EField("VP", GenTuDoc("")),
            EField("VV", GenTuDoc("")),
            EField("VVD", GenTuDoc("")),
            EField("VVG", GenTuDoc("")),
            EField("VVN", GenTuDoc("")),
            EField("VVP", GenTuDoc("")),
            EField("VVZ", GenTuDoc("")),
            EField("WDT", GenTuDoc("")),
            EField("WHADJP", GenTuDoc("")),
            EField("WHADVP", GenTuDoc("")),
            EField("WHNP", GenTuDoc("")),
            EField("WHPP", GenTuDoc("")),
            EField("WP", GenTuDoc("")),
            EField("WP_POS", GenTuDoc("Possessive wh-pronoun")),
            EField("WRB", GenTuDoc("")),
            EField("X", GenTuDoc(""))
        ])
    ]


def with_enum_reflection_api(body: List[Any]) -> List[Any]:
    return [
        Pass("#pragma once"),
        Pass("#include <hstd/system/basic_templates.hpp>"),
        Pass("#include <hstd/system/reflection.hpp>"),
        Pass("#include <hstd/stdlib/Opt.hpp>")
    ] + body


def iterate_object_tree(tree, callback, context: List[Any]):
    callback(tree)
    context.append(tree)

    if isinstance(tree, list):
        for it in tree:
            iterate_object_tree(it, callback, context)

    elif isinstance(tree, dict):
        for key, value in tree.items():
            iterate_object_tree(value, callback, context)

    # Primitive types cannot be walked over, end iteration
    elif tree is True or tree is False or tree is None or isinstance(tree, str) or isinstance(tree, type):
        pass

    elif isinstance(tree, object):
        # If any object -- walk all slots (attributes)
        class_of_obj = type(tree)
        name = class_of_obj.__name__
        slots = vars(tree)
        for slot, value in slots.items():
            iterate_object_tree(value, callback, context)

    # Walk over every item in list
    # Otherwise, print the value -- if something is missing it will be added later
    else:
        print(f"? {tree}")

    context.pop()

def get_type_base_fields(value, base_map):
    fields = []
    for base_sym in value.bases:
        base = base_map.get(base_sym)
        if base:
            fields.extend(base.fields)
            fields.extend(get_type_base_fields(base, base_map))

    return fields

def get_type_group_fields(value):
    return [GenTuField(group.variantName, group.variantField, GenTuDoc("")) for group in get_nested_groups(value)]

def get_nested_groups(value):
    return [nested for nested in value.nested if isinstance(nested, Group) and nested.variantField]

def get_base_map():
    base_map = {}
    def callback(obj):
        if isinstance(obj, Struct):
            base_map[obj.name] = obj
            
    context = []
    iterate_object_tree(get_types(), callback, context)
    base_map['Org'] = Struct(
        'Org', "",
        [
            GenTuField("OrgSemPlacement", "placementContext", ""),
            GenTuField(t_vec(""), "subnodes", "")
        ]
    )

    return base_map

def get_exporter_methods(forward):
    methods = []
    iterate_tree_context = []
    base_map = get_base_map()

    def callback(value):
        nonlocal methods  
        nonlocal base_map
        nonlocal iterate_tree_context
        if isinstance(value, Struct):
            scope_full = [scope for scope in iterate_tree_context if isinstance(scope, Struct)]
            scope_names = [scope.name for scope in scope_full]
            name = value.name
            full_scoped_name = scope_names + [name]
            fields = [field for field in (value.fields + get_type_base_fields(value, base_map) +  get_type_group_fields(value)) if not(field.isStatic)] 
            
            scoped_target = f"CR<sem::{'::'.join(full_scoped_name)}>"
            decl_scope = "" if forward else "Exporter<V, R>::"
            t_params = None if forward else [GenTuParam("V"), GenTuParam("R")]

            variant_methods = [
                GenTuFunction("void",
                         f"{decl_scope}visit",
                         GenTuDoc(""),
                         params=t_params,
                         arguments=[
                             GenTuIdent("R&", "res"),
                             GenTuIdent(f"CR<sem::{'::'.join(full_scoped_name)}::{group.variantName}>", "object")
                         ],
                         impl=None if forward else
                         f"visitVariants(res, sem::{'::'.join(full_scoped_name)}::{group.kindGetter}(object), object);")
                for group in get_nested_groups(value)
            ]

            if len(scope_full) == 0:
                method = GenTuFunction("void",
                                  f"{decl_scope}visit{name}",
                                  GenTuDoc(""),
                                  params=t_params,
                                  arguments=[GenTuIdent("R&", "res"), GenTuIdent(f"In<sem::{name}>", "object")],
                                  impl=None if forward else f"__visit_specific_kind(res, object);\n%s" %
                                  '\n'.join([f"__org_field(res, object, {a.name});" for a in fields]))
            else:
                method = GenTuFunction("void",
                                  f"{decl_scope}visit",
                                  GenTuDoc(""),
                                  params=t_params,
                                  arguments=[GenTuIdent("R&", "res"), GenTuIdent(scoped_target, "object")],
                                  impl=None if forward else '\n'.join([f"__obj_field(res, object, {a.name});" for a in fields]))

            methods += variant_methods + [method]

    iterate_object_tree(get_types(), callback, iterate_tree_context)
    return methods


def get_concrete_types():
    return [struct for struct in get_types() if struct.concreteKind]


def gen_value():
    full_enums = get_enums() + [Enum(t_osk(), GenTuDoc(""),fields= [EField(struct.name, GenTuDoc("")) for struct in get_concrete_types()])]

    return GenFiles([
        GenUnit(GenTu("${base}/exporters/exporternlp_enums.hpp", with_enum_reflection_api(get_nlp_enums())),
                GenTu("${base}/exporters/exporternlp_enums.cpp", [Pass("#include \"exporternlp_enums.hpp\"")] + get_nlp_enums())),
        GenUnit(GenTu("${base}/exporters/Exporter.tcc", get_exporter_methods(False))),
        GenUnit(GenTu("${base}/exporters/ExporterMethods.tcc", get_exporter_methods(True))),
        GenUnit(
            GenTu("${base}/sem/SemOrgEnums.hpp", with_enum_reflection_api([
                Pass("#define EACH_SEM_ORG_KIND(__IMPL) \\\n" +
                     (" \\\n".join([f"    __IMPL({struct.name})" for struct in get_concrete_types()])))]) + full_enums
                ), 
            GenTu("${base}/sem/SemOrgEnums.cpp", [Pass('#include "SemOrgEnums.hpp"')] + full_enums)),
        GenUnit(
            GenTu("${base}/sem/SemOrgTypes.hpp", [
                Pass("#pragma once"),
                GenTuInclude("sem/SemOrgEnums.hpp", True),
                GenTuInclude("hstd/stdlib/Vec.hpp", True),
                GenTuInclude("hstd/stdlib/Variant.hpp", True),
                GenTuInclude("hstd/stdlib/Time.hpp", True),
                GenTuInclude("hstd/stdlib/Opt.hpp", True),
                GenTuInclude("hstd/stdlib/Str.hpp", True),
                GenTuInclude("parse/OrgTypes.hpp", True),
                GenTuInclude("boost/describe.hpp", True),
                GenTuInclude("hstd/system/macros.hpp", True),
                GenTuInclude("functional", True),
                GenTuInclude("QDateTime", True),
                GenTuInclude("sem/SemOrgBase.hpp", True),
                GenTuInclude("sem/SemOrgEnums.hpp", True),
                GenTuNamespace("sem", [Group(get_types(), enumName="")])
            ]))
    ])


if __name__ == "__main__":
    from pprint import pprint
    gen_value()
    print("done")
