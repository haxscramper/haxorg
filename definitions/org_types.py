#!/ usr / bin / env python

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


@dataclass
class Doc:
    short: str
    full: str = ""


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
    kind: str = "Method"


@dataclass
class Pass:
    text: str
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

@dataclass 
class Enum:
    name: str
    doc: Doc
    fields: List[EField] = field(default_factory=list)

@dataclass
class Group:
    types: List[Any] = field(default_factory=list)
    enumName: str = "Kind"
    iteratorMacroName: str = ""
    variantName: str = "Data"
    variantField: str = "data"
    variantValue: Optional[str] = None
    kindGetter: str = "getKind"
    kind: str = "Group"

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
            [Field(t_osk(), "staticKind", Doc("Document"), isConst=True, isStatic=True)],
        )


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
                    ["Switch"],
                    Doc("Extra configuration switches that can be used to control representation of the rendered code block. This field does not exactly correspond to the `-XX` parameters that can be passed directly in the field, but also works with attached `#+options` from the block"
                       ),
                    nested=[
                        Group([
                            Struct(["LineStart"],
                                   Doc("Enumerate code lines starting from `start` value instead of default indexing."),
                                   fields=[
                                       Field("int", "start", Doc("First line number")),
                                       Field("bool",
                                             "extendLast",
                                             Doc("Continue numbering from the previous block nstead of starting anew"),
                                             value="false")
                                   ]),
                            Struct(["CalloutFormat"], Doc(""), fields=[Field("Str", "format", Doc(""), value="\"\"")]),
                            Struct(["RemoveCallout"], Doc(""), fields=[Field("bool", "remove", Doc(""), value="true")]),
                            Struct(["EmphasizeLine"],
                                   Doc("Emphasize single line -- can be repeated multiple times"),
                                   fields=[Field(t_vec("int"), "line", Doc(""), value="{}")]),
                            Struct(["Dedent"], Doc(""), fields=[Field("int", "value", Doc(""), value="0")])
                        ])
                    ]),
                Enum(["Results"], Doc("What to do with newly evaluated result"),
                     [EField("Replace", Doc("Remove old result, replace with new value"))]),
                Enum(["Exports"], Doc("What part of the code block should be visible in export"), [
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
                    ["Repeat"],
                    Doc("Repetition information for static time"),
                    nested=[
                        Enum(["Mode"], Doc("Timestamp repetition mode"), [
                            EField("None", Doc("Do not repeat task on completion")),
                            EField("Exact", Doc("?")),
                            EField("FirstMatch", Doc("Repeat on the first matching day in the future")),
                            EField("SameDay", Doc("Repeat task on the same day next week/month/year"))
                        ]),
                        Enum(
                            ["Period"],
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
                    Struct(["Static"], Doc(""), fields=[Field(t_opt("Repeat"), "repeat", Doc("")),
                                                        Field("UserTime", "time", Doc(""))]),
                    Struct(["Dynamic"], Doc(""), fields=[Field(t_str(), "expr", Doc(""))])
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
                  Struct(["Param"],
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
                  Struct(["DescribedLog"],
                         Doc("Base value for the log variant"),
                         fields=[
                             Field(t_opt(t_id("StmtList")),
                                   "desc",
                                   Doc("Optional description of the log entry"),
                                   value="SemIdT<StmtList>::Nil()")
                         ]),
                  Group([
                      Struct(["Priority"],
                             Doc("Priority added"),
                             bases=["DescribedLog"],
                             nested=[d_simple_enum("Action", Doc("Priority change action"), "Added", "Removed", "Changed")],
                             fields=[
                                 opt_field("QString", "oldPriority", Doc("Previous priority for change and removal")),
                                 opt_field("QString", "newPriority", Doc("New priority for change and addition")),
                                 id_field("Time", "on", Doc("When priority was changed"))
                             ]),
                      Struct(["Note"],
                             Doc("Timestamped note"),
                             bases=["DescribedLog"],
                             fields=[id_field("Time", "on", Doc("Where log was taken"))]),
                      Struct(["Refile"],
                             Doc("Refiling action"),
                             bases=["DescribedLog"],
                             fields=[
                                 id_field("Time", "on", Doc("When the refiling happened")),
                                 id_field("Link", "from", Doc("Link to the original subtree"))
                             ]),
                      Struct(["Clock"],
                             Doc("Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`"),
                             bases=["DescribedLog"],
                             fields=[
                                 Field(t_var(t_id("Time"), t_id("TimeRange")),
                                       "range",
                                       Doc("Start-end or only start period"),
                                       value="SemIdT<Time>::Nil()")
                             ]),
                      Struct(["State"],
                             Doc("Change of the subtree state -- `- State \"WIP\" from \"TODO\" [2023-04-30 Sun 13:29:04]`"),
                             bases=["DescribedLog"],
                             fields=[
                                 Field("OrgBigIdentKind", "from", Doc("")),
                                 Field("OrgBigIdentKind", "to", Doc("")),
                                 id_field("Time", "on", Doc(""))
                             ]),
                      Struct(["Tag"],
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
                    ["Period"],
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
                        Enum(["Kind"], Doc("Period kind"), [
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
                Struct(["Property"],
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
                               Struct(["Nonblocking"], Doc(""), fields=[Field("bool", "isBlocking", Doc(""))]),
                               Struct(["Trigger"], Doc("")),
                               Struct(["Origin"], Doc(""), fields=[Field(t_str(), "text", Doc(""))]),
                               Struct(["ExportLatexClass"], Doc(""), fields=[Field(t_str(), "latexClass", Doc(""))]),
                               Struct(["ExportLatexClassOptions"], Doc(""), fields=[Field(t_vec(t_str()), "options", Doc(""))]),
                               Struct(["ExportLatexHeader"], Doc(""), fields=[Field(t_str(), "header", Doc(""))]),
                               Struct(["ExportLatexCompiler"], Doc(""), fields=[Field(t_str(), "compiler", Doc(""))]),
                               Struct(["Ordered"], Doc(""), fields=[Field("bool", "isOrdered", Doc(""))]),
                               Struct(["Effort"],
                                      Doc(""),
                                      fields=[Field("int", "hours", Doc(""), value="0"),
                                              Field("int", "minutes", Doc(""), value="0")]),
                               Struct(["Visibility"],
                                      Doc(""),
                                      nested=[d_simple_enum("Level", Doc(""), "Folded", "Children", "Content", "All")],
                                      fields=[Field("Level", "level", Doc(""))]),
                               Struct(["ExportOptions"],
                                      Doc(""),
                                      fields=[Field(t_str(), "backend", Doc("")),
                                              Field("UnorderedMap<Str, Str>", "values", Doc(""))]),
                               Struct(["Blocker"], Doc(""), fields=[Field(t_vec(t_str()), "blockers", Doc(""))]),
                               Struct(["Unnumbered"], Doc("")),
                               Struct(["Created"], Doc(""), fields=[id_field("Time", "time", Doc(""))])
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
                      Struct(["Raw"], Doc(""), fields=[(Field(t_str(), "text", Doc("")))]),
                      Struct(["Id"], Doc(""), fields=[(Field(t_str(), "text", Doc("")))]),
                      Struct(["Person"], Doc(""), fields=[(Field(t_str(), "name", Doc("")))]),
                      Struct(["Footnote"], Doc(""), fields=[(Field(t_str(), "target", Doc("")))]),
                      Struct(["File"], Doc(""), fields=[(Field(t_str(), "file", Doc("")))])
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
                    [Struct(["Example"], Doc("")),
                     Struct(["Export"], Doc("")),
                     Struct(["Src"], Doc("")),
                     Struct(["OrgDocument"], Doc(""))],
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


def gen_value():
    get_types()
    return GenFiles()


if __name__ == "__main__":
    print(gen_value())
