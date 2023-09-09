#!/ usr / bin / env python

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
class Param:
    name: str = ""


@dataclass
class GenUnit:
    header: GenTu = field(default_factory=lambda: GenTu())
    source: GenTu = field(default_factory=lambda: GenTu())


@dataclass
class GenFiles:
    files: List[GenUnit] = field(default_factory=list)


@dataclass
class Doc:
    brief: str
    full: str = ""


@dataclass
class Include:
    what: str
    isSystem: bool
    kind: str = "Include"


@dataclass
class Namespace:
    name: str
    entries: List[Any]
    kind: str = "Namespace"


@dataclass
class Field:
    type: str
    name: str
    doc: Doc
    value: Optional[str] = None
    kind: str = "Field"
    isStatic: bool = False
    isConst: bool = False


@dataclass
class Ident:
    type: str
    name: str
    value: Optional[str] = None


@dataclass
class Method:
    result: str
    name: str
    doc: Doc
    arguments: List[Ident] = field(default_factory=list)
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
    doc: Doc
    fields: List[Field] = field(default_factory=list)
    nested: List[Any] = field(default_factory=list)
    methods: List[Method] = field(default_factory=list)
    bases: List[str] = field(default_factory=list)
    concreteKind: bool = True
    kind: str = "Struct"


@dataclass
class EField:
    name: str
    doc: Doc
    value: Optional[str] = None


@dataclass
class Enum:
    name: str
    doc: Doc
    fields: List[EField] = field(default_factory=list)
    base: Optional[str] = None
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
    return Field(t_id(id), name, doc, value=f"SemIdT<{id}>::Nil()")


def vec_field(typ, name, doc):
    return Field(t_vec(typ), name, doc, value="{}")


def opt_field(typ, name, doc):
    return Field(t_opt(typ), name, doc, value="std::nullopt")


def d_org(*args, **kwargs):
    res = Struct(*args, **kwargs)
    kind = res.name
    base = res.bases[0]
    res.nested = [Pass("using {base}::{base}")] + res.nested
    if res.concreteKind:
        res.fields.insert(
            0,
            Field(t_osk(), "staticKind", Doc("Document"), isConst=True, isStatic=True),
        )

    return res


def d_simple_enum(name, doc, *args):
    return Enum(name, doc, fields=[EField(arg, Doc("")) for arg in args])


def get_types():
    return [
        d_org(
            "Stmt",
            Doc("Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)"
               ),
            bases=["Org"],
            concreteKind=False,
            fields=[Field(t_vec(t_id()), "attached", Doc(""))],
            methods=[Method(
                t_opt(t_id()),
                "getAttached",
                Doc(""),
                arguments=[Ident(t_osk(), "kind")],
            )],
            nested=[
                Pass("Stmt() {}"),
                Pass("Stmt(SemId parent, CVec<SemId> attached, CVec<SemId> subnodes) : Org(parent, subnodes), attached(attached) {}"),
            ],
        ),
        d_org(
            "Inline",
            Doc("Base class for all inline elements"),
            bases=["Org"],
            concreteKind=False,
        ),
        d_org(
            "StmtList",
            Doc("Zero or more statement nodes"),
            bases=["Org"],
        ),
        d_org(
            "Empty",
            Doc("Node without content"),
            bases=["Org"],
        ),
        d_org(
            "Row",
            Doc("Table row"),
            bases=["Org"],
        ),
        d_org(
            "Table",
            Doc("Table"),
            bases=["Stmt"],
            fields=[Field(
                t_vec(t_id("Row")),
                "rows",
                Doc("List of rows for the table"),
                value="{}",
            )],
        ),
        d_org(
            "HashTag",
            Doc("Single or nested inline hash-tag"),
            bases=["Inline"],
            fields=[
                Field("Str", "head", Doc("Main part of the tag")),
                Field(
                    t_vec(t_id("HashTag")),
                    "subtags",
                    Doc("List of nested tags"),
                    value="{}",
                ),
            ],
            methods=[
                Method(
                    "bool",
                    "prefixMatch",
                    Doc("Check if list of tag names is a prefix for either of the nested hash tags in this one"),
                    isConst=True,
                    arguments=[Ident(t_cr(t_vec(t_str())), "prefix")],
                )
            ],
        ),
        d_org(
            "Footnote",
            Doc(
                "Inline and regular footnote definition",
                full="\\note in-text link to the footnotes are implemented using `Link` nodes",
            ),
            bases=["Inline"],
            fields=[
                Field("Str", "tag", Doc("Footnote text target name"), value='""'),
                Field(
                    t_opt(t_id()),
                    "definition",
                    Doc("Link to possibly resolved definition"),
                    value="std::nullopt",
                ),
            ],
        ),
        d_org(
            "Completion",
            Doc("Completion status of the subtree list element"),
            bases=["Inline"],
            fields=[
                Field("int", "done", Doc("Number of completed tasks"), value="0"),
                Field("int", "full", Doc("Full number of tasks"), value="0"),
                Field(
                    "bool",
                    "isPercent",
                    Doc("Use fraction or percent to display completion"),
                    value="false",
                ),
            ],
        ),
        d_org(
            "Paragraph",
            Doc("Top-level or inline paragraph"),
            bases=["Stmt"],
            methods=[
                Method(
                    "bool",
                    "isFootnoteDefinition",
                    Doc("Check if paragraph defines footnote"),
                    isConst=True,
                    impl="return !subnodes.empty() && at(0)->is(OrgSemKind::Footnote);",
                )
            ],
        ),
        d_org(
            "Format",
            Doc("Base class for branch of formatting node classes"),
            bases=["Org"],
            concreteKind=False,
        ),
        d_org("Center", Doc("Center nested content in export"), bases=["Format"]),
        d_org(
            "Command",
            Doc("Base class for block or line commands"),
            bases=["Org"],
            concreteKind=False,
        ),
        d_org(
            "LineCommand",
            Doc("Line commands"),
            bases=["Command"],
            concreteKind=False,
        ),
        #;; TODO rename to the standalone command
        d_org(
            "Standalone",
            Doc("Standalone commands that can be placed individuall on the the top level and don't have to be attached to any subsequent elements"
               ),
            bases=["LineCommand"],
            concreteKind=False,
        ),
        d_org(
            "Attached",
            Doc("Line command that might get attached to some block element"),
            bases=["LineCommand"],
            concreteKind=False,
        ),
        d_org(
            "Caption",
            Doc("Caption annotation for any subsequent node"),
            bases=["Attached"],
            fields=[id_field("Paragraph", "text", Doc("Content description"))],
        ),
        d_org(
            "CommandGroup",
            Doc("Multiple attachable commands will get grouped into this element unless it is possible to attached them to some adjacent block command"
               ),
            bases=["Stmt"],
        ),
        d_org(
            "Block",
            Doc("Block command type"),
            bases=["Command"],
            concreteKind=False,
        ),
        d_org(
            "Quote",
            Doc("Quotation block"),
            bases=["Org"],
            fields=[id_field("Paragraph", "text", Doc("Quote content"))],
        ),
        d_org("Example", Doc("Example block"), bases=["Block"]),
        d_org(
            "CmdArguments",
            Doc("Additional arguments for command blocks"),
            bases=["Org"],
            methods=[
                Method(
                    t_opt(
                        t_id("CmdArgument")),
                    "popArg",
                    Doc("Remove argument value from the map and return it if present",
                        full=
                        "Some argument values can be processed directly during convert, others will be mapped in respective exporter backends. This is a convenience method to remove things during convert stage"
                       ),
                    arguments=[Ident(t_str(), "key")])
            ],
            fields=[
                Field(t_vec(t_id("CmdArgument")), "positional", Doc("Positional arguments that had no keys")),
                Field(t_map(t_str(), t_id("CmdArgument")), "named", Doc("Stored key-value mapping"))
            ]),
        d_org("CmdArgument",
              Doc("Single key-value (or positional)"),
              bases=["Org"],
              fields=[opt_field(t_str(), "key", Doc("Key")), Field(t_str(), "value", Doc("Value"))],
              methods=[
                  Method(t_opt("int"), "getInt", Doc("Parse argument as integer value"), isConst=True),
                  Method(t_opt("bool"), "getBool", Doc("Get argument as bool"), isConst=True),
                  Method(t_str(), "getString", Doc("Get original string"), isConst=True)
              ]),
        d_org("Export",
              Doc("Direct export passthrough"),
              bases=["Block"],
              nested=[
                  Enum("Format", Doc("Export block format type"), [
                      EField("Inline", Doc("Export directly in the paragraph")),
                      EField("Line", Doc("Single line of export")),
                      EField("Block", Doc("Multiple lines of export"))
                  ])
              ],
              fields=[
                  Field("Format", "format", Doc("Export block type"), value="Format::Inline"),
                  Field(t_str(), "exporter", Doc("Exporter backend name")),
                  id_field("CmdArguments", "parameters", Doc("Additional parameters aside from 'exporter',")),
                  opt_field(t_str(), "placement", Doc("Customized position of the text in the final exporting document.")),
                  Field(t_str(), "content", Doc("Raw exporter content string"))
              ]),
        d_org("AdmonitionBlock", Doc("Block of text with admonition tag: 'note',', 'warning','"), bases=["Block"]),
        d_org(
            "Code",
            Doc("Base class for all code blocks"),
            bases=["Block"],
            nested=[
                Struct(
                    "Switch",
                    Doc("Extra configuration switches that can be used to control representation of the rendered code block. This field does not exactly correspond to the `-XX` parameters that can be passed directly in the field, but also works with attached `#+options` from the block"
                       ),
                    nested=[
                        Group([
                            Struct("LineStart",
                                   Doc("Enumerate code lines starting from `start` value instead of default indexing."),
                                   fields=[
                                       Field("int", "start", Doc("First line number")),
                                       Field("bool",
                                             "extendLast",
                                             Doc("Continue numbering from the previous block nstead of starting anew"),
                                             value="false")
                                   ]),
                            Struct("CalloutFormat", Doc(""), fields=[Field("Str", "format", Doc(""), value="\"\"")]),
                            Struct("RemoveCallout", Doc(""), fields=[Field("bool", "remove", Doc(""), value="true")]),
                            Struct("EmphasizeLine",
                                   Doc("Emphasize single line -- can be repeated multiple times"),
                                   fields=[Field(t_vec("int"), "line", Doc(""), value="{}")]),
                            Struct("Dedent", Doc(""), fields=[Field("int", "value", Doc(""), value="0")])
                        ])
                    ]),
                Enum("Results", Doc("What to do with newly evaluated result"),
                     [EField("Replace", Doc("Remove old result, replace with new value"))]),
                Enum("Exports", Doc("What part of the code block should be visible in export"), [
                    EField("None", Doc("Hide both original code and run result")),
                    EField("Both", Doc("Show output and code")),
                    EField("Code", Doc("Show only code")),
                    EField("Results", Doc("Show only evaluation results"))
                ])
            ],
            fields=[
                Field(t_opt(t_str()), "lang", Doc("Code block language name"), value="std::nullopt"),
                Field(t_vec("Switch"), "switches", Doc("Switch options for block"), value="{}"),
                Field("Exports", "exports", Doc("What to export"), value="Exports::Both"),
                id_field("CmdArguments", "parameters", Doc("Additional parameters that are language-specific")),
                Field("bool", "cache", Doc("Do cache values?"), value="false"),
                Field("bool", "eval", Doc("Eval on export?"), value="false"),
                Field("bool", "noweb", Doc("Web-tangle code on export/run"), value="false"),
                Field("bool", "hlines", Doc("?"), value="false"),
                Field("bool", "tangle", Doc("?"), value="false")
            ]),
        d_org(
            "Time",
            Doc("Single static or dynamic timestamp (active or inactive)"),
            bases=["Org"],
            fields=[Field("bool", "isActive", Doc("<active> vs [inactive]"), value="false")],
            nested=[
                Pass("bool isStatic() const { return std::holds_alternative<Static>(time); }"),
                Struct(
                    "Repeat",
                    Doc("Repetition information for static time"),
                    nested=[
                        Enum("Mode", Doc("Timestamp repetition mode"), [
                            EField("None", Doc("Do not repeat task on completion")),
                            EField("Exact", Doc("?")),
                            EField("FirstMatch", Doc("Repeat on the first matching day in the future")),
                            EField("SameDay", Doc("Repeat task on the same day next week/month/year"))
                        ]),
                        Enum(
                            "Period",
                            Doc("Repetition period. Temporary placeholder for now, until I figure out what would be the proper way to represent whatever org can do ... which is to be determined as well"
                               ), [
                                   EField("Year", Doc("")),
                                   EField("Month", Doc("")),
                                   EField("Week", Doc("")),
                                   EField("Day", Doc("")),
                                   EField("Hour", Doc("")),
                                   EField("Minute", Doc(""))
                               ])
                    ],
                    fields=[
                        Field("Mode", "mode", Doc("mode")),
                        Field("Period", "period", Doc("period")),
                        Field("int", "count", Doc("count"))
                    ]),
                Group([
                    Struct("Static", Doc(""), fields=[Field(t_opt("Repeat"), "repeat", Doc("")),
                                                        Field("UserTime", "time", Doc(""))]),
                    Struct("Dynamic", Doc(""), fields=[Field(t_str(), "expr", Doc(""))])
                ],
                      kindGetter="getTimeKind",
                      enumName="TimeKind",
                      variantField="time",
                      variantName="TimeVariant")
            ]),
        d_org("TimeRange",
              Doc("Range of time delimited by two points"),
              bases=["Org"],
              fields=[id_field("Time", "from", Doc("Starting time")),
                      id_field("Time", "to", Doc("Finishing time"))]),
        d_org("Macro",
              Doc("Inline macro invocation"),
              bases=["Org"],
              fields=[
                  Field(t_str(), "name", Doc("Macro name"), value="\"\""),
                  Field(t_vec(t_str()), "arguments", Doc("Raw uninterpreted macro arguments"), value="{}")
              ]),
        d_org("Symbol",
              Doc("Text symbol or symbol command"),
              bases=["Org"],
              nested=[
                  Struct("Param",
                         Doc("Symbol parameters"),
                         fields=[
                             Field(t_opt(t_str()), "key", Doc("Key -- for non-positional")),
                             Field(t_str(), "value", Doc("Uninterpreted value"))
                         ])
              ],
              fields=[
                  Field(t_str(), "name", Doc("Name of the symbol")),
                  Field(t_vec("Param"), "parameters", Doc("Optional list of parameters")),
                  Field(t_vec(t_id()), "positional", Doc("Positional parameters"))
              ]),
        d_org("SubtreeLog",
              Doc("Single subtree log entry"),
              bases=["Org"],
              methods=[Method("void", "setDescription", Doc(""), arguments=[Ident(t_id("StmtList"), "desc")])],
              nested=[
                  Struct("DescribedLog",
                         Doc("Base value for the log variant"),
                         fields=[
                             Field(t_opt(t_id("StmtList")),
                                   "desc",
                                   Doc("Optional description of the log entry"),
                                   value="SemIdT<StmtList>::Nil()")
                         ]),
                  Group([
                      Struct("Priority",
                             Doc("Priority added"),
                             bases=["DescribedLog"],
                             nested=[d_simple_enum("Action", Doc("Priority change action"), "Added", "Removed", "Changed")],
                             fields=[
                                 opt_field("QString", "oldPriority", Doc("Previous priority for change and removal")),
                                 opt_field("QString", "newPriority", Doc("New priority for change and addition")),
                                 id_field("Time", "on", Doc("When priority was changed"))
                             ]),
                      Struct("Note",
                             Doc("Timestamped note"),
                             bases=["DescribedLog"],
                             fields=[id_field("Time", "on", Doc("Where log was taken"))]),
                      Struct("Refile",
                             Doc("Refiling action"),
                             bases=["DescribedLog"],
                             fields=[
                                 id_field("Time", "on", Doc("When the refiling happened")),
                                 id_field("Link", "from", Doc("Link to the original subtree"))
                             ]),
                      Struct("Clock",
                             Doc("Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`"),
                             bases=["DescribedLog"],
                             fields=[
                                 Field(t_var(t_id("Time"), t_id("TimeRange")),
                                       "range",
                                       Doc("Start-end or only start period"),
                                       value="SemIdT<Time>::Nil()")
                             ]),
                      Struct("State",
                             Doc("Change of the subtree state -- `- State \"WIP\" from \"TODO\" [2023-04-30 Sun 13:29:04]`"),
                             bases=["DescribedLog"],
                             fields=[
                                 Field("OrgBigIdentKind", "from", Doc("")),
                                 Field("OrgBigIdentKind", "to", Doc("")),
                                 id_field("Time", "on", Doc(""))
                             ]),
                      Struct("Tag",
                             Doc("Assign tag to the subtree `- Tag \"project##haxorg\" Added on [2023-04-30 Sun 13:29:06]`"),
                             bases=["DescribedLog"],
                             fields=[
                                 id_field("Time", "on", Doc("When the log was assigned")),
                                 id_field("HashTag", "tag", Doc("Tag in question")),
                                 Field("bool", "added", Doc("Added/removed?"), value="false")
                             ])
                  ],
                        kindGetter="getLogKind",
                        variantField="log",
                        variantValue="Note{}",
                        variantName="LogEntry")
              ]),
        d_org(
            "Subtree",
            Doc("Subtree"),
            bases=["Org"],
            fields=[
                Field("int", "level", Doc("Subtree level"), value="0"),
                opt_field(t_str(), "treeId", Doc(":ID: property")),
                opt_field(t_str(), "todo", Doc("Todo state of the tree")),
                opt_field(t_id("Completion"), "completion", Doc("Task completion state")),
                opt_field(t_id("Paragraph"), "description", Doc("")),
                vec_field(t_id("HashTag"), "tags", Doc("Trailing tags")),
                id_field("Paragraph", "title", Doc("Main title")),
                vec_field(t_id("SubtreeLog"), "logbook", Doc("Associated subtree log")),
                vec_field("Property", "properties", Doc("Immediate properties")),
                opt_field(t_id("Time"), "closed", Doc("When subtree was marked as closed")),
                opt_field(t_id("Time"), "deadline", Doc("When is the deadline")),
                opt_field(t_id("Time"), "scheduled", Doc("When the event is scheduled"))
            ],
            methods=[
                Method(t_vec("Period"), "getTimePeriods", Doc(""), isConst=True, arguments=[Ident("IntSet<Period::Kind>", "kinds")]),
                Method(t_vec("Property"),
                       "getProperties",
                       Doc(""),
                       isConst=True,
                       arguments=[Ident("Property::Kind", "kind"),
                                  Ident(t_cr(t_str()), "subkind", value="\"\"")]),
                Method(t_opt("Property"),
                       "getProperty",
                       Doc(""),
                       isConst=True,
                       arguments=[Ident("Property::Kind", "kind"),
                                  Ident(t_cr(t_str()), "subkind", value="\"\"")]),
                Method(t_vec("Property"),
                       "getContextualProperties",
                       Doc(""),
                       isConst=True,
                       arguments=[Ident("Property::Kind", "kind"),
                                  Ident(t_cr(t_str()), "subkind", value="\"\"")]),
                Method(t_opt("Property"),
                       "getContextualProperty",
                       Doc(""),
                       isConst=True,
                       arguments=[Ident("Property::Kind", "kind"),
                                  Ident(t_cr(t_str()), "subkind", value="\"\"")])
            ],
            nested=[
                Struct(
                    "Period",
                    Doc("Type of the subtree associated time periods"),
                    fields=[
                        Field("Kind", "kind", Doc("Time period kind -- not associated with point/range distinction")),
                        Field(t_var(t_id("Time"), t_id("TimeRange")), "period", Doc("Stored time point/range"))
                    ],
                    methods=[
                        Method(t_id("Time"), "getTime", Doc("Get associated time point"), impl="return std::get<SemIdT<Time>>(period);"),
                        Method(t_id("Time"),
                               "getTimeRange",
                               Doc("Get associated time period"),
                               impl="return std::get<SemIdT<TimeRange>>(period);")
                    ],
                    #  ;; TODO constructors
                    nested=[
                        Enum("Kind", Doc("Period kind"), [
                            EField("Clocked", Doc("Time period of the task execution.")),
                            EField(
                                "Scheduled",
                                Doc("Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned"
                                   )),
                            EField(
                                "Titled",
                                Doc("Single point or time range used in title. Single point can also be a simple time, such as `12:20`")),
                            EField("Deadline", Doc("Date of task completion. Must be a single time point")),
                            EField("Created", Doc("When the subtree was created")),
                            EField("Repeated", Doc("Last repeat time of the recurring tasks"))
                        ]),
                        Pass("Period(CR<Variant<SemIdT<Time>, SemIdT<TimeRange>>> period, Kind kind) : period(period), kind(kind) ")
                    ]),
                Struct("Property",
                       Doc("Single subtree property"),
                       fields=[
                           Field("SetMode", "mainSetRule", Doc(""), value="SetMode::Override"),
                           Field("SetMode", "subSetRule", Doc(""), value="SetMode::Override"),
                           Field("InheritanceMode", "inheritanceMode", Doc(""), value="InheritanceMode::ThisAndSub")
                       ],
                       nested=[
                           d_simple_enum("SetMode", Doc(""), "Override", "Add", "Subtract"),
                           d_simple_enum("InheritanceMode", Doc(""), "ThisAndSub", "OnlyThis", "OnlySub"),
                           Group([
                               Struct( "Nonblocking" , Doc(""), fields=[Field("bool", "isBlocking", Doc(""))]),
                               Struct( "Trigger" , Doc("")),
                               Struct( "Origin" , Doc(""), fields=[Field(t_str(), "text", Doc(""))]),
                               Struct( "ExportLatexClass" , Doc(""), fields=[Field(t_str(), "latexClass", Doc(""))]),
                               Struct( "ExportLatexClassOptions" , Doc(""), fields=[Field(t_vec(t_str()), "options", Doc(""))]),
                               Struct( "ExportLatexHeader" , Doc(""), fields=[Field(t_str(), "header", Doc(""))]),
                               Struct( "ExportLatexCompiler" , Doc(""), fields=[Field(t_str(), "compiler", Doc(""))]),
                               Struct( "Ordered" , Doc(""), fields=[Field("bool", "isOrdered", Doc(""))]),
                               Struct( "Effort" ,
                                      Doc(""),
                                      fields=[Field("int", "hours", Doc(""), value="0"),
                                              Field("int", "minutes", Doc(""), value="0")]),
                               Struct( "Visibility" ,
                                      Doc(""),
                                      nested=[d_simple_enum("Level", Doc(""), "Folded", "Children", "Content", "All")],
                                      fields=[Field("Level", "level", Doc(""))]),
                               Struct( "ExportOptions" ,
                                      Doc(""),
                                      fields=[Field(t_str(), "backend", Doc("")),
                                              Field("UnorderedMap<Str, Str>", "values", Doc(""))]),
                               Struct( "Blocker" , Doc(""), fields=[Field(t_vec(t_str()), "blockers", Doc(""))]),
                               Struct( "Unnumbered" , Doc("")),
                               Struct( "Created" , Doc(""), fields=[id_field("Time", "time", Doc(""))])
                           ]),
                           Pass("Property(CR<Data> data) : data(data) {}"),
                           Pass("bool matches(Kind kind, CR<QString> subkind = \"\") const;"),
                       ])
            ]),
        d_org("LatexBody", Doc("Latex code body"), bases=["Org"], concreteKind=False),
        d_org("InlineMath", Doc("Inline math"), bases=["LatexBody"]),
        d_org("Leaf",
              Doc("Final node"),
              bases=["Org"],
              concreteKind=False,
              fields=[Field(t_str(), "text", Doc("Final leaf value"), value="\"\"")]),
        d_org("Escaped", Doc("Escaped text"), bases=["Leaf"]),
        d_org("Newline", Doc("\\n newline"), bases=["Leaf"]),
        d_org("Space", Doc("' \"space\","), bases=["Leaf"]),
        d_org("Word", Doc("word"), bases=["Leaf"]),
        d_org("AtMention", Doc("@mention"), bases=["Leaf"]),
        d_org("RawText", Doc(""), bases=["Leaf"]),
        d_org("Punctuation", Doc(""), bases=["Leaf"]),
        d_org("Placeholder", Doc(""), bases=["Leaf"]),
        d_org("BigIdent", Doc(""), bases=["Leaf"]),
        d_org(
            "Markup",
            Doc(""),
            bases=["Org"],
            concreteKind=False,
        ),
        d_org("Bold", Doc(""), bases=["Markup"]),
        d_org("Underline", Doc(""), bases=["Markup"]),
        d_org("Monospace", Doc(""), bases=["Markup"]),
        d_org("MarkQuote", Doc(""), bases=["Markup"]),
        d_org("Verbatim", Doc(""), bases=["Markup"]),
        d_org("Italic", Doc(""), bases=["Markup"]),
        d_org("Strike", Doc(""), bases=["Markup"]),
        d_org("Par", Doc(""), bases=["Markup"]),
        d_org("List", Doc(""), bases=["Org"], methods=[Method("bool", "isDescriptionList", Doc(""), isConst=True)]),
        d_org("ListItem",
              Doc(""),
              bases=["Org"],
              fields=[
                  Field("Checkbox", "checkbox", Doc(""), value="Checkbox::None"),
                  Field(t_opt(t_id("Paragraph")), "header", Doc(""), value="std::nullopt")
              ],
              nested=[d_simple_enum("Checkbox", Doc(""), "None", "Done", "Empty")],
              methods=[Method("bool", "isDescriptionItem", Doc(""), isConst=True, impl="return header.has_value();")])
        #;; TODO
        ,
        d_org("Link",
              Doc(""),
              bases=["Org"],
              fields=[Field(t_opt(t_id("Paragraph")), "description", Doc(""), value="std::nullopt")],
              methods=[
                  Method(t_opt(t_id()), "resolve", Doc(""), isConst=True, arguments=[Ident(t_cr("Document"), "doc")]),
                  Method(t_opt(t_id()), "resolve", Doc(""), isConst=True)
              ],
              nested=[
                  Group([
                      Struct( "Raw" , Doc(""), fields=[(Field(t_str(), "text", Doc("")))]),
                      Struct( "Id" , Doc(""), fields=[(Field(t_str(), "text", Doc("")))]),
                      Struct( "Person" , Doc(""), fields=[(Field(t_str(), "name", Doc("")))]),
                      Struct( "Footnote" , Doc(""), fields=[(Field(t_str(), "target", Doc("")))]),
                      Struct( "File" , Doc(""), fields=[(Field(t_str(), "file", Doc("")))])
                  ],
                        kindGetter="getLinkKind")
              ]),
        d_org("Document",
              Doc(""),
              bases=["Org"],
              methods=[
                  Method(t_opt(t_id()), "resolve", Doc(""), isConst=True, arguments=[Ident(t_cr(t_id()), "node")]),
                  Method(t_opt(t_id("Subtree")), "getSubtree", Doc(""), isConst=True, arguments=[Ident(t_cr(t_str()), "id")]),
                  Method(t_vec("Subtree::Property"),
                         "getProperties",
                         Doc(""),
                         isConst=True,
                         arguments=[Ident("Subtree::Property::Kind", "kind"),
                                    Ident(t_cr(t_str()), "subKind", value="\"\"")]),
                  Method(t_opt("Subtree::Property"),
                         "getProperty",
                         Doc(""),
                         isConst=True,
                         arguments=[Ident("Subtree::Property::Kind", "kind"),
                                    Ident(t_cr(t_str()), "subKind", value="\"\"")])
              ],
              fields=[
                  Field(t_map(t_str(), t_id()), "idTable", Doc("")),
                  Field(t_map(t_str(), t_id()), "nameTable", Doc("")),
                  Field(t_map(t_str(), t_id()), "footnoteTable", Doc("")),
                  Field(t_map(t_str(), t_id()), "anchorTable", Doc("")),
                  opt_field(t_id("Paragraph"), "title", Doc("")),
                  opt_field(t_id("Paragraph"), "author", Doc("")),
                  opt_field(t_id("Paragraph"), "creator", Doc("")),
                  opt_field(t_id("RawText"), "email", Doc("")),
                  opt_field(t_vec(t_str()), "language", Doc("")),
                  id_field("DocumentOptions", "options", Doc("")),
                  opt_field(t_str(), "exportFileName", Doc(""))
              ]),
        d_org(
            "ParseError",
            Doc(""),
            bases=["Org"],
        ),
        d_org("FileTarget",
              Doc(""),
              bases=["Org"],
              fields=[
                  Field(t_str(), "path", Doc("")),
                  opt_field("int", "line", Doc("")),
                  opt_field(t_str(), "searchTarget", Doc("")),
                  Field("bool", "restrictToHeadlines", Doc(""), value="false"),
                  opt_field(t_str(), "targetId", Doc("")),
                  opt_field(t_str(), "regexp", Doc(""))
              ]),
        d_org(
            "TextSeparator",
            Doc(""),
            bases=["Org"],
        ),
        d_org(
            "Include",
            Doc(""),
            bases=["Org"],
            nested=[
                Group(
                    [Struct( "Example" , Doc("")),
                     Struct( "Export" , Doc("")),
                     Struct( "Src" , Doc("")),
                     Struct( "OrgDocument" , Doc(""))],
                    kindGetter="getIncludeKind")
            ]),
        d_org("DocumentOptions",
              Doc(""),
              bases=["Org"],
              methods=[
                  Method(t_vec("Subtree::Property"),
                         "getProperties",
                         Doc(""),
                         isConst=True,
                         arguments=[Ident("Subtree::Property::Kind", "kind"),
                                    Ident(t_cr(t_str()), "subKind", value="\"\"")]),
                  Method(t_opt("Subtree::Property"),
                         "getProperty",
                         Doc(""),
                         isConst=True,
                         arguments=[Ident("Subtree::Property::Kind", "kind"),
                                    Ident(t_cr(t_str()), "subKind", value="\"\"")])
              ],
              nested=[
                  Pass("using TocExport = Variant<bool, int>;"),
                  d_simple_enum("BrokenLinks", Doc(""), "Raise", "Ignore", "Mark"),
                  d_simple_enum("Visibility", Doc(""), "Overview", "Content", "ShowAll", "Show2Levels", "Show3Levels", "Show4Levels",
                                "Show5Levels", "ShowEverything")
              ],
              fields=[
                  Field("BrokenLinks", "brokenLinks", Doc(""), value="BrokenLinks::Mark"),
                  Field("Visibility", "initialVisibility", Doc(""), value="Visibility::ShowEverything"),
                  Field("TocExport", "tocExport", Doc(""), value="false"),
                  Field(t_vec("Subtree::Property"), "properties", Doc("")),
                  Field("bool", "smartQuotes", Doc(""), value="false"),
                  Field("bool", "emphasizedText", Doc(""), value="false"),
                  Field("bool", "specialStrings", Doc(""), value="false"),
                  Field("bool", "fixedWidthSections", Doc(""), value="false"),
                  Field("bool", "includeTimestamps", Doc(""), value="false"),
                  Field("bool", "preserveLineBreaks", Doc(""), value="false"),
                  Field("bool", "plaintextSubscripts", Doc(""), value="false"),
                  Field("bool", "exportArchived", Doc(""), value="false"),
                  Field("bool", "exportWithAuthor", Doc(""), value="false"),
                  Field("bool", "exportBrokenLinks", Doc(""), value="false"),
                  Field("bool", "exportWithClock", Doc(""), value="false"),
                  Field("bool", "exportWithCreator", Doc(""), value="false")
              ]),
        d_org(
            "DocumentGroup",
            Doc(""),
            bases=["Org"],
        )
    ]


def get_enums():
    return [
        Enum("OrgSemPlacement", Doc("Semantic location of the sem org node in the parent tree"), [
            EField("TreeTitle", Doc("Subtree title")),
            EField("TreeBody", Doc("Inner content of the subtree")),
            EField("LinkDescription", Doc("Description paragraph for the link")),
            EField("ListItemBody", Doc("Statement list or inner content of the list item body")),
            EField("ListItemDesc", Doc("Description part of the list item")),
            EField("DocBody", Doc("Toplevel document"))
        ]),
        Enum("OrgHorizontalDirection", Doc(""), [
            EField("ohdNone", Doc("No specific positioning requirements")),
            EField("ohdLeft", Doc("Align to the left")),
            EField("ohdRight", Doc("Align to the right")),
            EField("ohdCenter", Doc("Align to the center"))
        ]),
        Enum("OrgVerticalDirection", Doc(""), [
            EField("ovdNone", Doc("No specific positioning")),
            EField("ovdTop", Doc("Align to the top")),
            EField("ovdCenter", Doc("Center")),
            EField("ovdBottom", Doc("Bottom"))
        ]),
        Enum("OrgSpecName", Doc(""), [
            EField("Unnamed", Doc("")),
            EField("Result", Doc("")),
            EField("Year", Doc("")),
            EField("Day", Doc("")),
            EField("Clock", Doc("")),
            EField("Repeater", Doc("")),
            EField("Link", Doc("")),
            EField("Tags", Doc("")),
            EField("Tag", Doc("")),
            EField("State", Doc("")),
            EField("Protocol", Doc("")),
            EField("Desc", Doc("")),
            EField("Times", Doc("")),
            EField("Drawer", Doc("")),
            EField("Args", Doc("")),
            EField("Name", Doc("")),
            EField("Definition", Doc("")),
            EField("Body", Doc("")),
            EField("HeaderArgs", Doc("")),
            EField("File", Doc("")),
            EField("Kind", Doc("")),
            EField("Lang", Doc("")),
            EField("Prefix", Doc("")),
            EField("Text", Doc("")),
            EField("Todo", Doc("")),
            EField("Urgency", Doc("")),
            EField("Title", Doc("")),
            EField("Completion", Doc("")),
            EField("Head", Doc("")),
            EField("Subnodes", Doc("")),
            EField("Properties", Doc("")),
            EField("Logbook", Doc("")),
            EField("Description", Doc("")),
            EField("Logs", Doc("")),
            EField("Newstate", Doc("")),
            EField("Oldstate", Doc("")),
            EField("Time", Doc("")),
            EField("From", Doc("")),
            EField("EndArgs", Doc("")),
            EField("Flags", Doc("")),
            EField("Value", Doc("")),
            EField("Assoc", Doc("")),
            EField("Main", Doc("")),
            EField("Hash", Doc("")),
            EField("Bullet", Doc("")),
            EField("Counter", Doc("")),
            EField("Checkbox", Doc("")),
            EField("Header", Doc("")),
            EField("To", Doc("")),
            EField("Diff", Doc("")),
            EField("Property", Doc("")),
            EField("Subname", Doc("")),
            EField("Values", Doc("")),
            EField("Cells", Doc("")),
            EField("Rows", Doc("")),
            EField("Lines", Doc("")),
            EField("Chunks", Doc("")),
            EField("InheritanceMode", Doc("")),
            EField("MainSetRule", Doc("")),
            EField("SubSetRule", Doc(""))
        ]),
        Enum("OrgNodeKind", Doc(""), [
            EField("None", Doc("Default valye for node - invalid state")),
            EField("Document", Doc("Toplevel part of the ast, not created by parser, and only used in `semorg` stage")),
            EField("UserNode", Doc("User-defined node [[code:OrgUserNode]]")),
            EField("Empty", Doc("Empty node - valid state that does not contain any value")),
            EField(
                "Error",
                Doc("Failed node parse",
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
            EField("ErrorTerminator", Doc("Terminator node for failure in nested structure parsing")),
            EField("ErrorToken", Doc("Single invalid token")),
            EField("InlineStmtList", Doc("")),
            EField(
                "StmtList",
                Doc("List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together."
                   )),
            EField(
                "AssocStmtList",
                Doc("Associated list of statements - AST elements like commands and links are grouped together if placed on adjacent lines")
            ),
            EField("Subtree", Doc("Section subtree")),
            EField("SubtreeTimes", Doc("Time? associated with subtree entry")),
            EField("SubtreeStars", Doc("")),
            EField("Completion", Doc("Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio.")),
            EField("Checkbox", Doc("Single checkbox item like `[X]` or `[-]`")),
            EField("List", Doc("")),
            EField("Bullet", Doc("List item prefix")),
            EField("ListItem", Doc("")),
            EField("ListTag", Doc("Auxilliary wrapper for the paragraph placed at the start of the description list.")),
            EField("Counter", Doc("")),
            EField(
                "Comment",
                Doc("Inline or trailling comment. Can be used addition to `#+comment:` line or `#+begin-comment` section. Nested comment syntax is allowed (`#[ level1 #[ level2 ]# ]#`), but only outermost one is represented as separate AST node, everything else is a `.text`"
                   )),
            EField(
                "RawText",
                Doc("Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers "
                   )),
            EField(
                "Unparsed",
                Doc("Part of the org-mode document that is yet to be parsed. This node should not be created manually, it is only used for handling mutually recursive DSLs such as tables, which might include lists, which in turn might contain more tables in different bullet points."
                   )),
            EField("Command", Doc("Undefined single-line command -- most likely custom user-provided oe")),
            EField("CommandArguments", Doc("Arguments for the command block")),
            EField("CommandTitle", Doc("`#+title:` - full document title")),
            EField("CommandAuthor", Doc("`#+author:` Document author")),
            EField("CommandCreator", Doc("`#+creator:` Document creator")),
            EField("CommandInclude",
                   Doc("`#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk.")),
            EField("CommandLanguage", Doc("`#+language:`")),
            EField("CommandAttrHtml", Doc("`#+attr_html:`")),
            EField("CommandName", Doc("`#+name:` - name of the associated entry")),
            EField("CommandHeader", Doc("`#+header:` - extended list of parameters passed to associated block")),
            EField("CommandOptions", Doc("`#+options:` - document-wide formatting options")),
            EField("CommandTblfm", Doc("")),
            EField("CommandBackendOptions", Doc("Backend-specific configuration options like `#+latex_header` `#+latex_class` etc.")),
            EField("AttrImg", Doc("")),
            EField("CommandCaption", Doc("`#+caption:` command")),
            EField("File", Doc("")),
            EField("BlockExport", Doc("")),
            EField("InlineExport", Doc("")),
            EField(
                "MultilineCommand",
                Doc("Multiline command such as code block, latex equation, large block of passthrough code. Some built-in org-mode commands do not requires `#+begin` prefix, (such as `#+quote` or `#+example`) are represented by this type of block as well."
                   )),
            EField("Result", Doc("Command evaluation result")),
            EField(
                "Ident",
                Doc("regular identifier - `alnum + [-_]` characters for punctuation. Identifiers are compared and parsed in style-insensetive manner, meaning `CODE_BLOCK`, `code-block` and `codeblock` are identical."
                   )),
            EField("BareIdent", Doc("Bare identifier - any characters are allowed")),
            EField(
                "AdmonitionTag",
                Doc("Big ident used in conjunction with colon at the start of paragraph is considered an admonition tag: `NOTE: Text`, `WARNING: text` etc."
                   )),
            EField("BigIdent", Doc("full-uppsercase identifier such as `MUST` or `TODO`")),
            EField(
                "VerbatimMultilineBlock",
                Doc("Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks."
                   )),
            EField("CodeLine", Doc("Single line of source code")),
            EField("CodeText", Doc("Block of source code text")),
            EField("CodeTangle", Doc("Single tangle target in the code block")),
            EField("CodeCallout", Doc("`(refs:` callout in the source code")),
            EField("QuoteBlock", Doc("`#+quote:` block in code")),
            EField("AdmonitionBlock", Doc("")),
            EField("CenterBlock", Doc("'")),
            EField("Example", Doc("Verbatim example text block")),
            EField("SrcCode", Doc("Block of source code - can be multiline, single-line and")),
            EField(
                "SrcInlineCode",
                Doc("inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc."
                   )),
            EField("CallCode", Doc("Call to named source code block. Inline, multiline, or single-line.")),
            EField(
                "PassCode",
                Doc("Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively"
                   )),
            EField("CmdArguments", Doc("Command arguments")),
            EField("CmdFlag",
                   Doc("Flag for source code block. For example `-n`, which is used to to make source code block export with lines")),
            EField("CmdKey", Doc("")),
            EField("CmdValue", Doc("")),
            EField("CmdNamedValue", Doc("Key-value pair for source code block call.")),
            EField(
                "UrgencyStatus",
                Doc("Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`."
                   )),
            EField("TextSeparator", Doc("Long horizontal line `----`")),
            EField(
                "Paragraph",
                Doc("Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph"
                   )),
            EField(
                "AnnotatedParagraph",
                Doc("Annotated paragraph -- a wrapper around a regular paragraph kind with added admonition, footnote, list tag prefix and similar types. `[fn:ID] Some Text` is an annotated paragraph, just like `NOTE: Text` or `- Prefix :: Body` (in this case list header is an annotated paragraph)"
                   )),
            EField(
                "Bold",
                Doc("""Region of text with formatting, which contains standalone words -
     can itself contain subnodes, which allows to represent nested
     formatting regions, such as `*bold /italic/*` text. Particular type
     of identifier is stored in string form in `str` field for `OrgNode`
     -- bold is represented as `\"*\"`, italic as `/` and so on. In case
     of explicit open/close pairs only opening one is stored.

     NOTE: when structured sentences are enabled, regular punctuation
     elements like `some text (notes)` are also represented as `Word,
     Word, Markup(str: \"(\", [Word])` - e.g. structure is not fully flat.""")),
            EField("Italic", Doc("")),
            EField("Verbatim", Doc("")),
            EField("Backtick", Doc("")),
            EField("Underline", Doc("")),
            EField("Strike", Doc("")),
            EField("Quote", Doc("")),
            EField("Angle", Doc("")),
            EField("Monospace", Doc("")),
            EField("Par", Doc("")),
            EField(
                "InlineMath",
                Doc("Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\\(paren-wrapped\\)` inline text.")),
            EField("DisplayMath", Doc("Inline display latex math from `$$double-dollar$$` or `\\[bracket-wrapped\\]` code.")),
            EField("Space", Doc("Space or tab character in regular text")),
            EField("Punctuation", Doc("")),
            EField("Colon", Doc("")),
            EField(
                "Word",
                Doc("Regular word - technically not different from `orgIdent`, but defined separately to disiguish between places where special syntax is required and free-form text."
                   )),
            EField("Escaped", Doc("Escaped formatting character in the text")),
            EField("Newline", Doc("")),
            EField("SkipNewline", Doc("")),
            EField("SkipSpace", Doc("")),
            EField("SkipAny", Doc("")),
            EField("RawLink", Doc("Raw unwrapped link that was pasted in text")),
            EField(
                "Link",
                Doc("""External or internal link. Consists of one or two elements - target
     (url, file location etc.) and description (`orgParagraph` of text).
     Description might be empty, and represented as empty node in this
     case. For external links particular formatting of the address is
     not handled by parser and instead contains raw string from input
     text.""")),
            EField(
                "Macro",
                Doc("""Org-mode macro replacement - during export each macro is expanded
     and evaluated according to it's environment. Body of the macro is
     not parsed fully during org-mode evaluation, but is checked for
     correct parenthesis balance (as macro might contain elisp code)""")),
            EField(
                "BackendRaw",
                Doc("""Raw content to be passed to a particular backend. This is the most
     compact way of quoting export strings, after `#+<backend>:
     <single-backend-line>` and `#+begin-export <backend>`
     `<multiple-lines>`.""")),
            EField(
                "Symbol",
                Doc("Special symbol that should be exported differently to various backends - greek letters (`\alpha`), mathematical notations and so on."
                   )),
            EField("TimeAssoc", Doc("Time association pair for the subtree deadlines.")),
            EField("StaticActiveTime", Doc("")),
            EField("StaticInactiveTime", Doc("")),
            EField("DynamicActiveTime", Doc("")),
            EField(
                "DynamicInactiveTime",
                Doc("Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later"
                   )),
            EField("TimeRange", Doc("Date and time range format - two `orgDateTime` entries")),
            EField("SimpleTime", Doc("Result of the time range evaluation or trailing annotation a subtree")),
            EField("Details", Doc("`#+begin_details`  section")),
            EField("Summary", Doc("`#+begin_summary` section")),
            EField(
                "Table",
                Doc("""Org-mode table. Tables can be writtein in different formats, but in
   the end they are all represented using single ast type. NOTE: it is
   not guaranteed that all subnodes for table are exactly
   `orgTableRow` - sometimes additional property metadata might be
   used, making AST like `Table[AssocStmtList[Command[_],
   TableRow[_]]]` possible""")),
            EField("TableRow", Doc("Horizontal table row")),
            EField("TableCell", Doc("Single cell in row. Might contain anyting, including other tables, simple text paragraph etc.")),
            EField("InlineFootnote", Doc("Inline footnote with text placed directly in the node body.")),
            EField(
                "Footnote",
                Doc("Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node."
                   )),
            EField("Horizontal",
                   Doc("Horizotal rule. Rule body might contain other subnodes, to represnt `---- some text ----` kind of formatting.")),
            EField("Filetags", Doc("`#+filetags:` line command")),
            EField(
                "OrgTag",
                Doc("""Original format of org-mode tags in form of `:tagname:`. Might
   contain one or mode identifgiers, but does not provide support for
   nesting - `:tag1:tag2:`. Can only be placed within restricted set
   of places such as subtree headings and has separate place in AST
   when allowed (`orgSubtree` always has subnode `№4` with either
   `orgEmpty` or `orgOrgTag`)""")),
            EField(
                "HashTag",
                Doc("""More commonly used `#hashtag` format, with some additional
   extension. Can be placed anywere in the document (including section
   headers), but does not have separate place in AST (e.g. considered
   regular part of the text)""")),
            EField("MetaSymbol", Doc("`\\sym{}` with explicit arguments")),
            EField("AtMention", Doc("`@user`")),
            EField(
                "BracTag",
                Doc("Custom extension to org-mode. Similarly to `BigIdent` used to have something like informal keywords `MUST`, `OPTIONAL`, but instead aimed /specifically/ at commit message headers - `[FEATURE]`, `[FIX]` and so on."
                   )),
            EField("Drawer", Doc("Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`")),
            EField("LatexClass", Doc("")),
            EField("LatexHeader", Doc("")),
            EField("LatexCompiler", Doc("")),
            EField("LatexClassOptions", Doc("")),
            EField("HtmlHead", Doc("")),
            EField("Columns",
                   Doc("`#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis.")),
            EField("PropertyList", Doc("")),
            EField("Property", Doc("Property entry, either in `#+property:` command, or in `:property:` drawer")),
            EField("Placeholder", Doc("Placeholder entry in text, usually writte like `<text to replace>`")),
            EField("SubtreeDescription", Doc("`:description:` entry")),
            EField("SubtreeUrgency", Doc("")),
            EField("Logbook", Doc("`:logbook:` entry storing note information")),
            EField("LogbookEntry", Doc("")),
            EField("LogbookStateChange", Doc("Annotation about change in the subtree todo state")),
            EField("LogbookNote", Doc("Timestamped log note on the subtree")),
            EField("LogbookClock", Doc("`CLOCK` entry in the subtree")),
            EField("LogbookRefile", Doc("`Refile` entry in the subtree logbook drawer")),
            EField("LogbookPriority", Doc("Change in the subtree priority")),
            EField("LogbookPriorityChangeAction", Doc("Action to change subtree")),
            EField("LogbookReschedule", Doc("")),
            EField("LogbookTagChange", Doc("")),
            EField("LogbookTagChangeAction", Doc("")),
            EField("RadioTarget", Doc("`<<<RADIO>>>`")),
            EField("Target", Doc("`<<TARGET>>`"))
        ]),
        Enum("OrgTextContext", Doc(""), [
            EField("otcPlain", Doc("")),
            EField("otcSubtree0", Doc("")),
            EField("otcSubtree1", Doc("")),
            EField("otcSubtree2", Doc("")),
            EField("otcSubtree3", Doc("")),
            EField("otcSubtree4", Doc("")),
            EField("otcSubtree5", Doc("")),
            EField("otcSubtree6", Doc("")),
            EField("otcSubtree7", Doc("")),
            EField("otcSubtree8", Doc("")),
            EField("otcSubtree9", Doc("")),
            EField("otcSubtree10", Doc("")),
            EField("otcSubtree11", Doc("")),
            EField("otcSubtree12", Doc("")),
            EField("otcSubtreeOther", Doc("")),
            EField("otcBold", Doc("")),
            EField("otcItalic", Doc("")),
            EField("otcStrike", Doc("")),
            EField("otcUnderline", Doc("")),
            EField("otcMonospaceInline", Doc("")),
            EField("otcMonospaceBlock", Doc(""))
        ]),
        Enum(
            "OrgBigIdentKind",
            Doc(""),
            [
                EField("None", Doc("")),
                EField(
                    "Must",
                    Doc("MUST This word, or the terms \"REQUIRED\" or \"SHALL\", mean that the definition is an absolute requirement of the specification."
                       )),
                EField(
                    "MustNot",
                    Doc("MUST NOT This phrase, or the phrase \"SHALL NOT\", mean that the definition is an absolute prohibition of the specification."
                       )),
                EField(
                    "Should",
                    Doc("""SHOULD This word, or the adjective \"RECOMMENDED\", mean that there
   may exist valid reasons in particular circumstances to ignore a
   particular item, but the full implications must be understood and
   carefully weighed before choosing a different course.""")),
                EField(
                    "ShouldNot",
                    Doc("""SHOULD NOT This phrase, or the phrase \"NOT RECOMMENDED\" mean that
   there may exist valid reasons in particular circumstances when the
   particular behavior is acceptable or even useful, but the full
   implications should be understood and the case carefully weighed
   before implementing any behavior described with this label.""")),
                EField("Required", Doc("")),
                EField(
                    "Optional",
                    Doc("""MAY This word, or the adjective \"OPTIONAL\", mean that an item is
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
                EField("ReallyShouldNot", Doc("")),
                EField("OughtTo", Doc("")),
                EField("WouldProbably", Doc("")),
                EField("MayWishTo", Doc("")),
                EField("Could", Doc("")),
                EField("Might", Doc("")),
                EField("Possible", Doc("")),
                EField("Todo", Doc("")),
                EField("Idea", Doc("")),
                EField("Error", Doc("")),
                EField("Fixme", Doc("")),
                EField("Doc", Doc("")),
                EField("Refactor", Doc("")),
                EField("Review", Doc("")),
                EField("Hack", Doc("")),
                EField("Implement", Doc("")),
                EField("Example", Doc("")),
                EField("Question", Doc("")),
                EField("Assume", Doc("")),
                EField("Internal", Doc("")),
                EField("Design", Doc("")),
                EField("Why", Doc("")),
                EField("Wip", Doc("")),
                EField("Fix", Doc("")),
                EField("Clean", Doc("")),
                EField("Feature", Doc("")),
                EField("Style", Doc("")),
                EField("Repo", Doc("")),
                EField("Skip", Doc("")),
                EField("Break", Doc("")),
                EField("Poc", Doc("")),
                EField("Next", Doc("")),
                EField("Later", Doc("")),
                EField("Postponed", Doc("")),
                EField("Stalled", Doc("")),
                EField("Done", Doc("")),
                EField("Partially", Doc("")),
                EField("Cancelled", Doc("")),
                EField("Failed", Doc("")),
                EField("Note", Doc("")),
                EField("Tip", Doc("")),
                EField("Important", Doc("")),
                EField("Caution", Doc("")),
                EField("Warning", Doc("")),
                EField("UserCodeComment", Doc("User-defined comment message")),
                EField("UserCommitMsg", Doc("User-defined commit message ident")),
                EField("UserTaskState", Doc("User-defined task state")),
                EField("UserAdmonition", Doc("User-defined admonition label")),
                EField("Other", Doc("User-defined big-idents, not included in default set.")),
                # ;; It is not hard to support
                # ;; https://en.wikipedia.org/wiki/Structured_English keywords. Maybe I
                # ;; will merge it with haxdoc somehow, maybe not, for not I just placed
                # ;; them here as a reminder to myself. My current idea is to overlay
                # ;; semi-structured explanation in the documenation with actual code.
                # ;; Structured keywords can be used as an anchor points (e.g. `IF` maps
                # ;; to real condition, `THEN` to the body and so on).
                EField("StructIf", Doc("")),
                EField("StructAnd", Doc("")),
                EField("StructOr", Doc("")),
                EField("StructNot", Doc("")),
                EField("StructGet", Doc("")),
                EField("StructSet", Doc("")),
                EField("StructThen", Doc("")),
                EField("StructElse", Doc("")),
                EField("StructWhile", Doc(""))
            ]),
        Enum("OrgTokenKind", Doc(""), [
            EField("None", Doc("")),
            EField("Eof", Doc("")),
            EField("GroupStart", Doc("Start of the tokenizer token group")),
            EField("GroupEnd", Doc("Tokenizer token group end")),
            EField("ErrorTerminator", Doc("")),
            EField("CommandPrefix", Doc("")),
            EField("LineCommand", Doc("")),
            EField(
                "CommandBegin",
                Doc("`#+begin` part of the multiline command. `begin_<block-type>` is split into two tokens - `begin_` prefix and `ockBegin<block-type>` section."
                   )),
            EField("CommandEnd", Doc("")),
            EField("DoubleColon", Doc("")),
            EField("Text", Doc("")),
            EField("StmtList", Doc("Unlexed group of statements - used in the list content to enable secondary parsing.")),
            EField("StmtListOpen", Doc("Start of the expanded statement list content")),
            EField("StmtListClose", Doc("End of the expanded statement list content")),
            EField("ListStart", Doc("Start of the list token group")),
            EField("ListItemStart", Doc("Start of the list item element")),
            EField("ListClock", Doc("`CLOCK:` entry at the start of the logbook entry list")),
            EField("ListPlus", Doc("")),
            EField("ListStar", Doc("")),
            EField("ListDescOpen", Doc("Start of the description list key,")),
            EField("ListDescClose", Doc("End of the description list key `::`")),
            EField("ListItemEnd", Doc("End of the list item")),
            EField("ListEnd", Doc("Complete end of the list token group")),
            EField("Checkbox", Doc("List or subtree checkbox")),
            EField("SubtreeTodoState", Doc("")),
            EField("SubtreeUrgency", Doc("Subtree importance marker")),
            EField("SubtreeCompletion", Doc("Subtree completion marker")),
            EField("SubtreeStars", Doc("Subtree prefix")),
            EField("SubtreeTagSeparator", Doc("")),
            EField("SubtreeTime", Doc("")),
            EField("SubtreeEnd", Doc("")),
            EField(
                "ImplicitTime",
                Doc("""You can write time ranges without any additional formatting for
   subtrees that have a diary timestamps. For example, you have a
   complex date predicate, but event occurs for `18:00-21:00`, so you
   write it in the random place in the subtree.""")),
            EField("TimeDuration", Doc("Time duration for the `effort` property or time range length evaluation")),
            EField("InactiveTimeBegin", Doc("Start of the inactive timestamp (`[2022-03-12]`)")),
            EField("InactiveTimeEnd", Doc("")),
            EField("ActiveTimeBegin", Doc("Start of the active timestamp `<2030-02-03>`")),
            EField("ActiveTimeEnd", Doc("")),
            EField("DynamicTimeContent", Doc("Dynamic time content")),
            EField("StaticTimeDatePart", Doc("year-month-day part of the timestamp")),
            EField("StaticTimeDayPart", Doc("weekday part of the timestamp")),
            EField("StaticTimeClockPart", Doc("Clock part of the timestamp")),
            EField("StaticTimeRepeater", Doc("Type of the time repeater: `+`, `++`, `.+`")),
            EField("TimeDash", Doc("Separator dash between two periods in the time range (`<start>--<finish.`)")),
            EField("TimeArrow", Doc("Time range evaluation arrow `[from]--[to] =>`")),
            EField("Comment", Doc("line or inline comment")),
            EField("ListDoubleColon", Doc("Double colon between description list tag and body")),
            EField("CommandArgumentsBegin", Doc("List of command arguments")),
            EField("CommandArgumentsEnd", Doc("End of the command arguments list")),
            EField("CommandKey", Doc("")),
            EField("CommandValue", Doc("")),
            EField("CommandFlag", Doc("")),
            EField("CommandBracket", Doc("`#+results[HASH...]`")),
            EField("ColonLiteral", Doc("Literal block with `:`")),
            EField("ColonIdent", Doc("Drawer or source code block wrappers with colon-wrapped identifiers. `:results:`, `:end:` etc.")),
            EField("ColonProperties", Doc("Start of the `:PROPERTIES:` block drawer block")),
            EField("ColonDescription", Doc("Start of the `:description:` drawer block")),
            EField("ColonEnd", Doc("")),
            EField("ColonLogbook", Doc("")),
            EField("RawLogbook", Doc("")),
            EField("LogbookStart", Doc("")),
            EField("LogbookEnd", Doc("")),
            EField("RawProperty", Doc("")),
            EField("Link", Doc("Any kind of link")),
            EField("CommandContentStart", Doc("")),
            EField("CommandContentEnd", Doc("")),
            EField("CodeContent", Doc("Block of code inside `#+begin_src`")),
            EField("CodeContentBegin", Doc("Start of the expanded code content")),
            EField("CodeContentEnd", Doc("End of the expanded code content")),
            EField(
                "CodeText",
                Doc("Uninterrupted text span without newlines - either a whole line or sub subsection of it if callout or tangle elements were detected"
                   )),
            EField("TableContent", Doc("Block of text inside `#+table`")),
            EField("QuoteContent", Doc("`#+quote` content")),
            EField("BackendPass", Doc("Backend-specific passthrough")),
            EField("LogBook", Doc("Logbook including content")),
            EField("Drawer", Doc("Drawer including content")),
            EField("Indent", Doc("Increase in indentation")),
            EField("Dedent", Doc("Decrease in indentation")),
            EField("SameIndent", Doc("")),
            EField("NoIndent", Doc("")),
            EField("BoldOpen", Doc("")),
            EField("BoldClose", Doc("")),
            EField("BoldInline", Doc("")),
            EField("BoldInlineOpen", Doc("")),
            EField("BoldInlineClose", Doc("")),
            EField("ItalicOpen", Doc("")),
            EField("ItalicClose", Doc("")),
            EField("ItalicInline", Doc("")),
            EField("ItalicInlineOpen", Doc("")),
            EField("ItalicInlineClose", Doc("")),
            EField("VerbatimOpen", Doc("")),
            EField("VerbatimClose", Doc("")),
            EField("VerbatimInline", Doc("")),
            EField("VerbatimInlineOpen", Doc("")),
            EField("VerbatimInlineClose", Doc("")),
            EField("MonospaceOpen", Doc("")),
            EField("MonospaceClose", Doc("")),
            EField("MonospaceInline", Doc("")),
            EField("MonospaceInlineOpen", Doc("")),
            EField("MonospaceInlineClose", Doc("")),
            EField("BacktickOpen", Doc("")),
            EField("BacktickClose", Doc("")),
            EField("BacktickInline", Doc("")),
            EField("BacktickInlineOpen", Doc("")),
            EField("BacktickInlineClose", Doc("")),
            EField("UnderlineOpen", Doc("")),
            EField("UnderlineClose", Doc("")),
            EField("UnderlineInline", Doc("")),
            EField("UnderlineInlineOpen", Doc("")),
            EField("UnderlineInlineClose", Doc("")),
            EField("StrikeOpen", Doc("")),
            EField("StrikeClose", Doc("")),
            EField("StrikeInline", Doc("")),
            EField("StrikeInlineOpen", Doc("")),
            EField("StrikeInlineClose", Doc("")),
            EField("QuoteOpen", Doc("")),
            EField("QuoteClose", Doc("")),
            EField("Punctuation", Doc("")),
            EField("LinkOpen", Doc("")),
            EField("LinkClose", Doc("")),
            EField("RawUrl", Doc("")),
            EField("LinkTargetOpen", Doc("")),
            EField("LinkTargetClose", Doc("")),
            EField("LinkInternal", Doc("No protocol is used in the link, it is targeting some internal named entry.")),
            EField("LinkProtocol", Doc("Protocol used by the link - `file:`, `https:` etc.")),
            EField(
                "LinkFull",
                Doc("Full token for the link, used in cases where it does not make sense to fracture the token - regular https URLs etc.")),
            EField("LinkPath", Doc("Link path for searches in file")),
            EField(
                "LinkTarget",
                Doc("Target of the link protocol that does not follow regular URI encoding scheme - for example `id:`, `elisp`, or `shell` links."
                   )),
            EField("LinkExtraSeparator", Doc("Separator of the extra content in the link, `::`")),
            EField("LinkExtra", Doc("Additional parametrization for the link search")),
            EField("LinkDescriptionOpen", Doc("")),
            EField("LinkDescriptionClose", Doc("")),
            EField("TextSeparator", Doc("")),
            EField("ParagraphStart", Doc("Fake token inserted by the lexer to delimit start of the paragraph")),
            EField("ParagraphEnd", Doc("")),
            EField("FootnoteStart", Doc("")),
            EField("FootnoteEnd", Doc("")),
            EField("Word", Doc("Regular word in the paragraph")),
            EField(
                "Escaped",
                Doc("Escaped character in plain text - `\\*`, `\\/` etc. Escaped characters and sequences thereof are treated like a regular plain text."
                   )),
            EField(
                "DoubleSlash",
                Doc("Put at the end of the lexer first logbook line to separate the  note, otherwise is treated as standalone escaped slash."
                   )),
            EField("Newline", Doc("Explicit newline a paragraph")),
            EField("SkipSpace", Doc("")),
            EField("SkipNewline", Doc("")),
            EField("SkipAny", Doc("")),
            EField("MaybeWord", Doc("")),
            EField("Space", Doc("Space in the paragraph")),
            EField("BigIdent", Doc("`TODO`, `NOTE` and similar capitalized words")),
            EField("RawText", Doc("Unparsed raw text, either as a part of paragraph or some embedded construction such as link address.")),
            EField("InlineSrc", Doc("Start of an inline source code block: `src_nim[]{}`")),
            EField("InlineCall", Doc("Start of an inline call block: `call_name[]{}`")),
            EField("CurlyStart", Doc("Start of the curly section of an inline source/call")),
            EField("CurlyEnd", Doc("End of the curly section of an inline source/call")),
            EField("SymbolStart", Doc("Unquoted `\\symbol` directly in the text")),
            EField("Ident", Doc("")),
            EField("DollarOpen", Doc("Opening dollar inline latex math")),
            EField("DollarClose", Doc("Closing dollar for inline latex math")),
            EField("DoubleDollarOpen", Doc("Opening `$` for inline latex")),
            EField("DoubleDollarClose", Doc("Closing `$` for inline latex")),
            EField("LatexParOpen", Doc("Opening `\\(` for inline latex math")),
            EField("LatexParClose", Doc("Closing `\\)` for inline latex math")),
            EField("LatexBraceOpen", Doc("Opening `\\[` for inline display latex equation")),
            EField("LatexBraceClose", Doc("Closing `\\]` for inline display latex equation")),
            EField("LatexInlineRaw", Doc("Content of the brace/par-enclosed math")),
            EField("DoubleAt", Doc("Inline backend passthrough `@@`")),
            EField("AtBracket", Doc("Inline annotation")),
            EField("AtMention", Doc("`@user` mention in the text")),
            EField("HashTag", Doc("Start of the inline hashtag `#tag`")),
            EField("HashTagSub", Doc("Nested hashtag separator")),
            EField("HashTagOpen", Doc("Start of the nested hashtag grop bracket")),
            EField("HashTagClose", Doc("End of the nested hashtag group separator")),
            EField("Comma", Doc("Comma - punctuation or a syntax element (e.g. for macro arguments)")),
            EField("ParOpen", Doc("Paren open - punctuation or a syntax element")),
            EField("ParClose", Doc("Paren close - punctuation or a syntax element")),
            EField("Colon", Doc("")),
            EField("Circumflex", Doc("`^` possible superscript in the text")),
            EField("MacroOpen", Doc("Start of the macro call `{{{`")),
            EField("MacroClose", Doc("Close of the macro call `}}}`")),
            EField("MetaBraceOpen", Doc("")),
            EField("MetaBraceBody", Doc("")),
            EField("MetaBraceClose", Doc("")),
            EField("MetaArgsOpen", Doc("")),
            EField("MetaArgsBody", Doc("")),
            EField("MetaArgsClose", Doc("")),
            EField("SrcOpen", Doc("")),
            EField("SrcName", Doc("")),
            EField("SrcArgs", Doc("")),
            EField("SrcBody", Doc("")),
            EField("SrcClose", Doc("")),
            EField("CallOpen", Doc("")),
            EField("CallName", Doc("")),
            EField("CallInsideHeader", Doc("")),
            EField("CallArgs", Doc("")),
            EField("EndHeader", Doc("")),
            EField("CallClose", Doc("")),
            EField("CmdArguments", Doc("")),
            EField("TableBegin", Doc("")),
            EField("TableEnd", Doc("")),
            EField("CellBody", Doc("Unformatted table cell body")),
            EField("RowSpec", Doc("`#+row` command together with parameters")),
            EField("CellSpec", Doc("`#+cell` command with parameters")),
            EField("Content", Doc("Temporary token created during initial content lexing")),
            EField("ContentStart", Doc("Start of the table cell content section")),
            EField("ContentEnd", Doc("End of the table cell content section")),
            EField("PipeOpen", Doc("")),
            EField("PipeSeparator", Doc("Vertical pipe (`|`) cell separator")),
            EField("PipeClose", Doc("")),
            EField("PipeCellOpen", Doc("")),
            EField("DashSeparator", Doc("Horizontal dash (`---`, `:---`, `---:` or `:---:`) row separator")),
            EField("CornerPlus", Doc("Corner plus (`+`)")),
            EField("Command", Doc("")),
            EField("CommandArgs", Doc("")),
            EField("Body", Doc("")),
            EField("LangName", Doc("")),
            EField("DoubleAngleOpen", Doc("`<<` - open for noweb or anchor placeholder")),
            EField("DoubleAngleClose", Doc("`>>` - close for noweb or anchor placeholder")),
            EField("TripleAngleOpen", Doc("`<<<` - radio target open")),
            EField("TripleAngleClose", Doc("`>>>` - radio target close")),
            EField("AngleOpen", Doc("Placeholder open")),
            EField("AngleClose", Doc("Placeholder close")),
            EField(
                "TextBlock",
                Doc("Code before noweb placeholder. Requires separate token to handle `##<<commented>>` - prefix comment should be duplicated for each line of the placeholder expansion."
                   ))
        ]),
        Enum("OrgCommandKind", Doc(""), [
            EField("None", Doc("")),
            EField("Include", Doc("")),
            EField("Filetags", Doc("")),
            EField("Setupfile", Doc("")),
            EField("Columns", Doc("")),
            EField("OtherProperty", Doc("")),
            EField("BeginTable", Doc("")),
            EField("EndTable", Doc("`#+table`")),
            EField("Row", Doc("`#+row`")),
            EField("Cell", Doc("`#+cell`")),
            EField("BeginAdmonition", Doc("")),
            EField("EndAdmonition", Doc("")),
            EField("BeginDynamic", Doc("")),
            EField("EndDynamic", Doc("`#+begin:`")),
            EField("BeginCenter", Doc("")),
            EField("EndCenter", Doc("`#+begin_center`")),
            EField("BeginQuote", Doc("")),
            EField("EndQuote", Doc("`#+quote`")),
            EField("BeginSrc", Doc("")),
            EField("EndSrc", Doc("`#+begin_src`")),
            EField("BeginExport", Doc("")),
            EField("EndExport", Doc("`#+end_export`")),
            EField("BeginExample", Doc("")),
            EField("EndExample", Doc("")),
            EField("BeginDetails", Doc("")),
            EField("EndDetails", Doc("")),
            EField("BeginSummary", Doc("")),
            EField("EndSummary", Doc("")),
            EField("LatexClassOptions", Doc("`#+latex_class_options`")),
            EField("LatexClass", Doc("")),
            EField("LatexCompiler", Doc("")),
            EField("AttrLatex", Doc("`#+attr_latex:`")),
            EField("AttrImg", Doc("`#+attr_img:`")),
            EField("AttrHtml", Doc("`#+attr_html:`")),
            EField("HtmlHead", Doc("`#+html_head:`")),
            EField("Language", Doc("`#+language:`")),
            EField("Options", Doc("`#+options: `")),
            EField("Title", Doc("`#+title:`")),
            EField("Property", Doc("`#+property:`")),
            EField("Author", Doc("`#+author:`")),
            EField("Bind", Doc("`#+bind:`")),
            EField("Creator", Doc("`#+creator:`")),
            EField("LatexHeader", Doc("`#+latex_header`")),
            EField("Results", Doc("`#+results:`")),
            EField("Call", Doc("`#+call:`")),
            EField("Name", Doc("`#+name:`")),
            EField("Caption", Doc("`#+caption:`")),
            EField("Header", Doc("`#+header:`")),
            EField("TableFormula", Doc("`#+tblfm:`")),
        ]),
        Enum("OrgPropertyKind", Doc(""), [
            EField("Title", Doc("")),
            EField("Author", Doc("")),
            EField("Date", Doc("")),
            EField("Email", Doc("")),
            EField("Language", Doc("")),
            EField("Url", Doc("")),
            EField("SourceUrl", Doc("")),
            EField("AttrImg", Doc("")),
            EField("Toplevel", Doc("")),
            EField("Blocker", Doc("")),
            EField("Created", Doc("")),
            EField("Unnumbered", Doc("")),
            EField("Trigger", Doc("")),
            EField("Ordered", Doc("")),
            EField("Noblocking", Doc("")),
            EField("ExportOptions", Doc("")),
            EField("BackendExportOptions", Doc("")),
            EField("AttrBackend", Doc("")),
            EField("ColumnSpec", Doc("")),
            EField("Name", Doc("")),
            EField("Caption", Doc("")),
            EField("LinkAbbrev", Doc("")),
            EField("Filetags", Doc("")),
            EField("TagConf", Doc("")),
            EField("LatexHeader", Doc("")),
            EField("OtherProperty", Doc("")),
            EField("Id", Doc(""))
        ]),
        Enum(
            "OrgUnnumberedKind", Doc(""),
            [EField("Notoc", Doc("")), EField("True", Doc("")), EField("False", Doc(""))]),
        Enum("OrgBlockLexerState", Doc(""), [
            EField("None", Doc("")),
            EField("InHeader", Doc("")),
            EField("InBody", Doc("")),
            EField("Ended", Doc("")),
            EField("Complete", Doc(""))
        ])
    ]


def get_nlp_enums():
    return [
        Enum("NlpDepKind", Doc("Dependency kind"), [
            EField("ROOT", Doc("")),
            EField("acl", Doc("")),
            EField("advcl", Doc("")),
            EField("advmod", Doc("")),
            EField("amod", Doc("")),
            EField("appos", Doc("")),
            EField("aux", Doc("")),
            EField("_case", Doc("")),
            EField("cc", Doc("")),
            EField("ccomp", Doc("")),
            EField("compound", Doc("")),
            EField("conj", Doc("")),
            EField("cop", Doc("")),
            EField("csubj", Doc("")),
            EField("dep", Doc("")),
            EField("det", Doc("")),
            EField("discourse", Doc("")),
            EField("expl", Doc("")),
            EField("fixed", Doc("")),
            EField("iobj", Doc("")),
            EField("mark", Doc("")),
            EField("nmod", Doc("")),
            EField("nsubj", Doc("")),
            EField("nummod", Doc("")),
            EField("obj", Doc("")),
            EField("obl", Doc("")),
            EField("parataxis", Doc("")),
            EField("punct", Doc("")),
            EField("ref", Doc("")),
            EField("xcomp", Doc("")),
        ]),
        Enum("NlpPosTag", Doc("Part of speech tag"), [
            EField("ADJP", Doc("")),
            EField("ADVP", Doc("")),
            EField("ADD", Doc("")),
            EField("AFX", Doc("")),
            EField("CC", Doc("")),
            EField("CD", Doc("")),
            EField("CONJP", Doc("")),
            EField("DT", Doc("")),
            EField("EX", Doc("")),
            EField("FRAG", Doc("")),
            EField("FW", Doc("")),
            EField("HYPH", Doc("")),
            EField("IN", Doc("")),
            EField("INTJ", Doc("")),
            EField("JJ", Doc("")),
            EField("JJR", Doc("")),
            EField("JJS", Doc("")),
            EField("LRB", Doc("")),
            EField("LS", Doc("")),
            EField("LST", Doc("")),
            EField("MD", Doc("")),
            EField("META", Doc("")),
            EField("NAC", Doc("")),
            EField("NFP", Doc("")),
            EField("NML", Doc("")),
            EField("NN", Doc("")),
            EField("NNP", Doc("")),
            EField("NNPS", Doc("")),
            EField("NNS", Doc("")),
            EField("NP", Doc("")),
            EField("NPS", Doc("")),
            EField("NP_TMP", Doc("")),
            EField("PDT", Doc("")),
            EField("POS", Doc("")),
            EField("PP", Doc("")),
            EField("PPZ", Doc("")),
            EField("PRN", Doc("")),
            EField("PRP", Doc("")),
            EField("PRT", Doc("")),
            EField("PUNCT_COLON", Doc("")),
            EField("PUNCT_COMMA", Doc("")),
            EField("PUNCT_PERIOD", Doc("")),
            EField("PUNCT_QUOTE_CLOSE", Doc("")),
            EField("PUNCT_QUOTE_OPEN", Doc("")),
            EField("QP", Doc("")),
            EField("RB", Doc("")),
            EField("RBR", Doc("")),
            EField("RBS", Doc("")),
            EField("ROOT", Doc("")),
            EField("RP", Doc("")),
            EField("RRB", Doc("")),
            EField("RRC", Doc("")),
            EField("S", Doc("")),
            EField("SBAR", Doc("")),
            EField("SBARQ", Doc("")),
            EField("SENT", Doc("")),
            EField("SINV", Doc("")),
            EField("SQ", Doc("")),
            EField("SYM", Doc("")),
            EField("TO", Doc("")),
            EField("UCP", Doc("")),
            EField("UH", Doc("")),
            EField("VB", Doc("")),
            EField("VBD", Doc("")),
            EField("VBG", Doc("")),
            EField("VBN", Doc("")),
            EField("VBP", Doc("")),
            EField("VBZ", Doc("")),
            EField("VH", Doc("")),
            EField("VHD", Doc("")),
            EField("VHG", Doc("")),
            EField("VHN", Doc("")),
            EField("VHP", Doc("")),
            EField("VHZ", Doc("")),
            EField("VP", Doc("")),
            EField("VV", Doc("")),
            EField("VVD", Doc("")),
            EField("VVG", Doc("")),
            EField("VVN", Doc("")),
            EField("VVP", Doc("")),
            EField("VVZ", Doc("")),
            EField("WDT", Doc("")),
            EField("WHADJP", Doc("")),
            EField("WHADVP", Doc("")),
            EField("WHNP", Doc("")),
            EField("WHPP", Doc("")),
            EField("WP", Doc("")),
            EField("WP_POS", Doc("Possessive wh-pronoun")),
            EField("WRB", Doc("")),
            EField("X", Doc(""))
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
    return [Field(group.variantName, group.variantField, Doc("")) for group in get_nested_groups(value)]

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
            Field("OrgSemPlacement", "placementContext", ""),
            Field(t_vec(""), "subnodes", "")
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
            t_params = None if forward else [Param("V"), Param("R")]

            variant_methods = [
                Method("void",
                         f"{decl_scope}avisit",
                         Doc(""),
                         params=t_params,
                         arguments=[
                             Ident("R&", "res"),
                             Ident(f"CR<sem::~{'::'.join(full_scoped_name)}::{group.variantName}>", "object")
                         ],
                         impl=None if forward else
                         f"visitVariants(res, sem::{'::'.join(full_scoped_name)}::{group.kindGetter}(object), object);")
                for group in get_nested_groups(value)
            ]

            if len(scope_full) == 0:
                method = Method("void",
                                  f"{decl_scope}avisit{name}",
                                  Doc(""),
                                  params=t_params,
                                  arguments=[Ident("R&", "res"), Ident(f"In<sem::{name}>", "object")],
                                  impl=None if forward else f"__visit_specific_kind(res, object);\n %s" %
                                  '\n'.join([f"__org_field(res, object, {a.name});" for a in fields]))
            else:
                method = Method("void",
                                  f"{decl_scope}avisit",
                                  Doc(""),
                                  params=t_params,
                                  arguments=[Ident("R&", "res"), Ident(scoped_target, "object")],
                                  impl=None if forward else ''.join([f"__obj_field(res, object, {a.name});" for a in fields]))

            methods += variant_methods + [method]

    iterate_object_tree(get_types(), callback, iterate_tree_context)
    return methods


def get_concrete_types():
    return [struct for struct in get_types() if struct.concreteKind]


def gen_value():
    full_enums = get_enums() + [Enum(t_osk(), Doc(""),fields= [EField(struct.name, Doc("")) for struct in get_concrete_types()])]

    return GenFiles([
        GenUnit(GenTu("/tmp/exporters/exporternlp_enums.hpp", with_enum_reflection_api(get_nlp_enums())),
                GenTu("/tmp/exporters/exporternlp_enums.cpp", [Pass("#include \"exporternlp_enums.hpp\"")] + get_nlp_enums())),
        GenUnit(GenTu("/tmp/exporters/Exporter.tcc", get_exporter_methods(False))),
        GenUnit(GenTu("/tmp/exporters/ExporterMethods.tcc", get_exporter_methods(True))),
        GenUnit(
            GenTu("/tmp/sem/SemOrgEnums.hpp", [
                Pass("#define EACH_SEM_ORG_KIND(__IMPL) \n" +
                     ("\n".join([f"    __IMPL({struct.name})" for struct in get_concrete_types()])))
            ] + full_enums), GenTu("/tmp/sem/SemOrgEnums.hpp", [Pass('#include "SemOrgEnums.hpp"')] + full_enums)),
        GenUnit(
            GenTu("/tmp/sem/SemOrgTypes.hpp", [
                Pass("#pragma once"),
                Include("sem/SemOrgEnums.hpp", True),
                Include("hstd/stdlib/Vec.hpp", True),
                Include("hstd/stdlib/Variant.hpp", True),
                Include("hstd/stdlib/Time.hpp", True),
                Include("hstd/stdlib/Opt.hpp", True),
                Include("hstd/stdlib/Str.hpp", True),
                Include("parse/OrgTypes.hpp", True),
                Include("boost/describe.hpp", True),
                Include("hstd/system/macros.hpp", True),
                Include("functional", True),
                Include("QDateTime", True),
                Include("sem/SemOrgBase.hpp", True),
                Include("sem/SemOrgEnums.hpp", True),
                Namespace("sem", [Group(get_types(), enumName="")])
            ]))
    ])


if __name__ == "__main__":
    from pprint import pprint
    gen_value()
    print("done")
