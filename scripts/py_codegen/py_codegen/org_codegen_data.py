from dataclasses import field, dataclass, replace
from copy import deepcopy
from beartype.typing import *
from enum import Enum

# Now you should be able to import your C++ library
from py_codegen.astbuilder_cpp import *
from py_codegen.gen_tu_cpp import *


@beartype
def t(name: str) -> QualType:
    return QualType(name=name)


def t_str() -> QualType:
    return t("Str")


def t_bool() -> QualType:
    return t("bool")


def t_int() -> QualType:
    return t("int")


@beartype
def t_space(name: str, Spaces: List[str]) -> QualType:
    return QualType(name=name,
                    Spaces=[QualType(name=S, isNamespace=True) for S in Spaces])


def n_sem() -> QualType:
    return QualType(name="sem", isNamespace=True)


def t_org(name: str, extraSpaces: List[QualType] = []) -> QualType:
    return QualType(name=name, Spaces=[n_sem()] + extraSpaces)


def t_nest(name: Union[str, QualType]) -> QualType:
    result = QualType(name=name) if isinstance(name, str) else name
    result.meta["isNested"] = True
    return result


def k_args(obj: Any, **kwargs) -> Any:
    for key, value in kwargs.items():
        obj.__setattr__(key, value)

    return obj


@beartype
def t_vec(arg: QualType) -> QualType:
    return QualType(name="Vec", Parameters=[arg])


@beartype
def t_id(target: Optional[Union[QualType, str]] = None) -> QualType:
    return (QualType(name="SemIdT",
                     Parameters=[(target if isinstance(target, QualType) else QualType(
                         name=target, Spaces=[n_sem()]))],
                     Spaces=[n_sem()]) if target else QualType(name="SemId",
                                                               Spaces=[n_sem()]))


@beartype
def t_opt(arg: QualType) -> QualType:
    return QualType(name="Opt", Parameters=[arg])


@beartype
def t_osk() -> QualType:
    return t("OrgSemKind")


@beartype
def t_cr(arg: QualType) -> QualType:
    return arg.model_copy(update=dict(RefKind=ReferenceKind.LValue, isConst=True))


def t_var(*args) -> QualType:
    return QualType(name="Variant", Parameters=[*args])


def t_map(key: QualType, val: QualType) -> QualType:
    return QualType(name="UnorderedMap", Parameters=[key, val])


@beartype
def id_field(id: str, name: str, doc: GenTuDoc) -> GenTuField:
    return GenTuField(t_id(id), name, doc, value=f"SemIdT<{id}>::Nil()")


def vec_field(typ, name, doc):
    return GenTuField(t_vec(typ), name, doc, value="{}")


def opt_field(typ, name, doc):
    return GenTuField(t_opt(typ), name, doc, value="std::nullopt")


def d_org(name: str, *args, **kwargs) -> GenTuStruct:
    res = GenTuStruct(QualType(name=name), *args, **kwargs)
    res.__setattr__("isOrgType", True)
    kind: str = res.name.name
    base = res.bases[0]
    res.nested = [GenTuPass(f"using {base.name}::{base.name};")] + res.nested
    if res.concreteKind:
        res.fields.insert(
            0,
            GenTuField(t_osk(),
                       "staticKind",
                       GenTuDoc("Document"),
                       isConst=True,
                       isStatic=True),
        )

        res.methods.insert(
            0,
            GenTuFunction(
                t_osk(),
                "getKind",
                GenTuDoc(""),
                isConst=True,
                isVirtual=True,
                isPureVirtual=False,
                impl=f"return {t_osk().name}::{kind};",
            ),
        )

        res.methods.insert(
            0,
            GenTuFunction(
                t_id(QualType(name=name)),
                "create",
                GenTuDoc(""),
                isStatic=True,
                arguments=[
                    GenTuIdent(t_id(), "parent"),
                    GenTuIdent(t_opt(t("OrgAdapter")), "original", value="std::nullopt"),
                ],
            ),
        )

    return res


@beartype
def d_simple_enum(name: str, doc: GenTuDoc, *args):
    return GenTuEnum(t(name),
                     doc,
                     fields=[GenTuEnumField(arg, GenTuDoc("")) for arg in args])


def get_types() -> Sequence[GenTuStruct]:
    return [
        d_org(
            "Stmt",
            GenTuDoc(
                "Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)"
            ),
            bases=[t_org("Org")],
            concreteKind=False,
            fields=[GenTuField(t_vec(t_id()), "attached", GenTuDoc(""))],
            methods=[
                GenTuFunction(
                    t_opt(t_id()),
                    "getAttached",
                    GenTuDoc(""),
                    arguments=[GenTuIdent(t_osk(), "kind")],
                )
            ],
            nested=[
                GenTuPass("Stmt() {}"),
                GenTuPass(
                    "Stmt(SemId parent, CVec<SemId> attached, CVec<SemId> subnodes) : Org(parent, subnodes), attached(attached) {}"
                ),
            ],
        ),
        d_org(
            "Inline",
            GenTuDoc("Base class for all inline elements"),
            bases=[t_org("Org")],
            concreteKind=False,
        ),
        d_org(
            "StmtList",
            GenTuDoc("Zero or more statement nodes"),
            bases=[t_org("Org")],
        ),
        d_org(
            "Empty",
            GenTuDoc("Node without content"),
            bases=[t_org("Org")],
        ),
        d_org(
            "Row",
            GenTuDoc("Table row"),
            bases=[t_org("Org")],
        ),
        d_org(
            "Table",
            GenTuDoc("Table"),
            bases=[t_org("Stmt")],
            fields=[
                GenTuField(
                    t_vec(t_id("Row")),
                    "rows",
                    GenTuDoc("List of rows for the table"),
                    value="{}",
                )
            ],
        ),
        d_org(
            "HashTag",
            GenTuDoc("Single or nested inline hash-tag"),
            bases=[t_org("Inline")],
            fields=[
                GenTuField(t_str(), "head", GenTuDoc("Main part of the tag")),
                GenTuField(
                    t_vec(t_id("HashTag")),
                    "subtags",
                    GenTuDoc("List of nested tags"),
                    value="{}",
                ),
            ],
            methods=[
                GenTuFunction(
                    t("bool"),
                    "prefixMatch",
                    GenTuDoc(
                        "Check if list of tag names is a prefix for either of the nested hash tags in this one"
                    ),
                    isConst=True,
                    arguments=[GenTuIdent(t_cr(t_vec(t_str())), "prefix")],
                )
            ],
        ),
        d_org(
            "Footnote",
            GenTuDoc(
                "Inline and regular footnote definition",
                full=
                "\\note in-text link to the footnotes are implemented using `Link` nodes",
            ),
            bases=[t_org("Inline")],
            fields=[
                GenTuField(t_str(),
                           "tag",
                           GenTuDoc("Footnote text target name"),
                           value='""'),
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
            bases=[t_org("Inline")],
            fields=[
                GenTuField(t_int(),
                           "done",
                           GenTuDoc("Number of completed tasks"),
                           value="0"),
                GenTuField(t_int(), "full", GenTuDoc("Full number of tasks"), value="0"),
                GenTuField(
                    t_bool(),
                    "isPercent",
                    GenTuDoc("Use fraction or percent to display completion"),
                    value="false",
                ),
            ],
        ),
        d_org(
            "Paragraph",
            GenTuDoc("Top-level or inline paragraph"),
            bases=[t_org("Stmt")],
            methods=[
                GenTuFunction(
                    t_bool(),
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
            bases=[t_org("Org")],
            concreteKind=False,
        ),
        d_org("Center",
              GenTuDoc("Center nested content in export"),
              bases=[t_org("Format")]),
        d_org(
            "Command",
            GenTuDoc("Base class for block or line commands"),
            bases=[t_org("Org")],
            concreteKind=False,
        ),
        d_org(
            "LineCommand",
            GenTuDoc("Line commands"),
            bases=[t_org("Command")],
            concreteKind=False,
        ),
        # ;; TODO rename to the standalone command
        d_org(
            "Standalone",
            GenTuDoc(
                "Standalone commands that can be placed individuall on the the top level and don't have to be attached to any subsequent elements"
            ),
            bases=[t_org("LineCommand")],
            concreteKind=False,
        ),
        d_org(
            "Attached",
            GenTuDoc("Line command that might get attached to some block element"),
            bases=[t_org("LineCommand")],
            concreteKind=False,
        ),
        d_org(
            "Caption",
            GenTuDoc("Caption annotation for any subsequent node"),
            bases=[t_org("Attached")],
            fields=[id_field("Paragraph", "text", GenTuDoc("Content description"))],
        ),
        d_org(
            "CommandGroup",
            GenTuDoc(
                "Multiple attachable commands will get grouped into this element unless it is possible to attached them to some adjacent block command"
            ),
            bases=[t_org("Stmt")],
        ),
        d_org(
            "Block",
            GenTuDoc("Block command type"),
            bases=[t_org("Command")],
            concreteKind=False,
        ),
        d_org(
            "Quote",
            GenTuDoc("Quotation block"),
            bases=[t_org("Org")],
            fields=[id_field("Paragraph", "text", GenTuDoc("Quote content"))],
        ),
        d_org("Example", GenTuDoc("Example block"), bases=[t_org("Block")]),
        d_org(
            "CmdArguments",
            GenTuDoc("Additional arguments for command blocks"),
            bases=[t_org("Org")],
            methods=[
                GenTuFunction(
                    t_opt(t_id("CmdArgument")),
                    "popArg",
                    GenTuDoc(
                        "Remove argument value from the map and return it if present",
                        full=
                        "Some argument values can be processed directly during convert, others will be mapped in respective exporter backends. This is a convenience method to remove things during convert stage",
                    ),
                    arguments=[GenTuIdent(t_str(), "key")],
                )
            ],
            fields=[
                GenTuField(
                    t_vec(t_id("CmdArgument")),
                    "positional",
                    GenTuDoc("Positional arguments that had no keys"),
                ),
                GenTuField(
                    t_map(t_str(), t_id("CmdArgument")),
                    "named",
                    GenTuDoc("Stored key-value mapping"),
                ),
            ],
        ),
        d_org(
            "CmdArgument",
            GenTuDoc("Single key-value (or positional)"),
            bases=[t_org("Org")],
            fields=[
                opt_field(t_str(), "key", GenTuDoc("Key")),
                GenTuField(t_str(), "value", GenTuDoc("Value")),
            ],
            methods=[
                GenTuFunction(
                    t_opt(t_int()),
                    "getInt",
                    GenTuDoc("Parse argument as integer value"),
                    isConst=True,
                ),
                GenTuFunction(t_opt(t_bool()),
                              "getBool",
                              GenTuDoc("Get argument as bool"),
                              isConst=True),
                GenTuFunction(t_str(),
                              "getString",
                              GenTuDoc("Get original string"),
                              isConst=True),
            ],
        ),
        d_org(
            "Export",
            GenTuDoc("Direct export passthrough"),
            bases=[t_org("Block")],
            nested=[
                GenTuEnum(
                    t("Format"),
                    GenTuDoc("Export block format type"),
                    [
                        GenTuEnumField("Inline",
                                       GenTuDoc("Export directly in the paragraph")),
                        GenTuEnumField("Line", GenTuDoc("Single line of export")),
                        GenTuEnumField("Block", GenTuDoc("Multiple lines of export")),
                    ],
                )
            ],
            fields=[
                GenTuField(
                    t_nest("Format"),
                    "format",
                    GenTuDoc("Export block type"),
                    value="Format::Inline",
                ),
                GenTuField(t_str(), "exporter", GenTuDoc("Exporter backend name")),
                id_field(
                    "CmdArguments",
                    "parameters",
                    GenTuDoc("Additional parameters aside from 'exporter',"),
                ),
                opt_field(
                    t_str(),
                    "placement",
                    GenTuDoc(
                        "Customized position of the text in the final exporting document."
                    ),
                ),
                GenTuField(t_str(), "content", GenTuDoc("Raw exporter content string")),
            ],
        ),
        d_org(
            "AdmonitionBlock",
            GenTuDoc("Block of text with admonition tag: 'note',', 'warning','"),
            bases=[t_org("Block")],
        ),
        d_org(
            "Code",
            GenTuDoc("Base class for all code blocks"),
            bases=[t_org("Block")],
            nested=[
                GenTuStruct(
                    t("Switch"),
                    GenTuDoc(
                        "Extra configuration switches that can be used to control representation of the rendered code block. This field does not exactly correspond to the `-XX` parameters that can be passed directly in the field, but also works with attached `#+options` from the block"
                    ),
                    nested=[
                        GenTuPass("Switch() {}"),
                        GenTuTypeGroup([
                            GenTuStruct(
                                t("LineStart"),
                                GenTuDoc(
                                    "Enumerate code lines starting from `start` value instead of default indexing."
                                ),
                                fields=[
                                    GenTuField(t_int(), "start",
                                               GenTuDoc("First line number")),
                                    GenTuField(
                                        t_bool(),
                                        "extendLast",
                                        GenTuDoc(
                                            "Continue numbering from the previous block nstead of starting anew"
                                        ),
                                        value="false",
                                    ),
                                ],
                                nested=[GenTuPass("LineStart() {}")]),
                            GenTuStruct(t("CalloutFormat"),
                                        GenTuDoc(""),
                                        fields=[
                                            GenTuField(t_str(),
                                                       "format",
                                                       GenTuDoc(""),
                                                       value='""')
                                        ],
                                        nested=[GenTuPass("CalloutFormat() {}")]),
                            GenTuStruct(t("RemoveCallout"),
                                        GenTuDoc(""),
                                        fields=[
                                            GenTuField(t_bool(),
                                                       "remove",
                                                       GenTuDoc(""),
                                                       value="true")
                                        ],
                                        nested=[GenTuPass("RemoveCallout() {}")]),
                            GenTuStruct(
                                t("EmphasizeLine"),
                                GenTuDoc(
                                    "Emphasize single line -- can be repeated multiple times"
                                ),
                                fields=[
                                    GenTuField(t_vec(t_int()),
                                               "line",
                                               GenTuDoc(""),
                                               value="{}")
                                ],
                                nested=[GenTuPass("EmphasizeLine() {}")]),
                            GenTuStruct(t("Dedent"),
                                        GenTuDoc(""),
                                        fields=[
                                            GenTuField(t_int(),
                                                       "value",
                                                       GenTuDoc(""),
                                                       value="0")
                                        ],
                                        nested=[GenTuPass("Dedent() {}")]),
                        ])
                    ],
                ),
                GenTuEnum(
                    t("Results"),
                    GenTuDoc("What to do with newly evaluated result"),
                    [
                        GenTuEnumField(
                            "Replace",
                            GenTuDoc("Remove old result, replace with new value"))
                    ],
                ),
                GenTuEnum(
                    t("Exports"),
                    GenTuDoc("What part of the code block should be visible in export"),
                    [
                        GenTuEnumField(
                            "None", GenTuDoc("Hide both original code and run result")),
                        GenTuEnumField("Both", GenTuDoc("Show output and code")),
                        GenTuEnumField("Code", GenTuDoc("Show only code")),
                        GenTuEnumField("Results",
                                       GenTuDoc("Show only evaluation results")),
                    ],
                ),
            ],
            fields=[
                GenTuField(
                    t_opt(t_str()),
                    "lang",
                    GenTuDoc("Code block language name"),
                    value="std::nullopt",
                ),
                GenTuField(
                    t_vec(t_nest("Switch")),
                    "switches",
                    GenTuDoc("Switch options for block"),
                    value="{}",
                ),
                GenTuField(t_nest("Exports"),
                           "exports",
                           GenTuDoc("What to export"),
                           value="Exports::Both"),
                id_field(
                    "CmdArguments",
                    "parameters",
                    GenTuDoc("Additional parameters that are language-specific"),
                ),
                GenTuField(t_bool(), "cache", GenTuDoc("Do cache values?"),
                           value="false"),
                GenTuField(t_bool(), "eval", GenTuDoc("Eval on export?"), value="false"),
                GenTuField(t_bool(),
                           "noweb",
                           GenTuDoc("Web-tangle code on export/run"),
                           value="false"),
                GenTuField(t_bool(), "hlines", GenTuDoc("?"), value="false"),
                GenTuField(t_bool(), "tangle", GenTuDoc("?"), value="false"),
            ],
        ),
        d_org(
            "Time",
            GenTuDoc("Single static or dynamic timestamp (active or inactive)"),
            bases=[t_org("Org")],
            fields=[
                GenTuField(t_bool(),
                           "isActive",
                           GenTuDoc("<active> vs [inactive]"),
                           value="false")
            ],
            nested=[
                GenTuPass(
                    "bool isStatic() const { return std::holds_alternative<Static>(time); }"
                ),
                GenTuStruct(
                    t("Repeat"),
                    GenTuDoc("Repetition information for static time"),
                    nested=[
                        GenTuEnum(
                            t("Mode"),
                            GenTuDoc("Timestamp repetition mode"),
                            [
                                GenTuEnumField(
                                    "None", GenTuDoc("Do not repeat task on completion")),
                                GenTuEnumField("Exact", GenTuDoc("?")),
                                GenTuEnumField(
                                    "FirstMatch",
                                    GenTuDoc(
                                        "Repeat on the first matching day in the future"),
                                ),
                                GenTuEnumField(
                                    "SameDay",
                                    GenTuDoc(
                                        "Repeat task on the same day next week/month/year"
                                    ),
                                ),
                            ],
                        ),
                        GenTuEnum(
                            t("Period"),
                            GenTuDoc(
                                "Repetition period. Temporary placeholder for now, until I figure out what would be the proper way to represent whatever org can do ... which is to be determined as well"
                            ),
                            [
                                GenTuEnumField("Year", GenTuDoc("")),
                                GenTuEnumField("Month", GenTuDoc("")),
                                GenTuEnumField("Week", GenTuDoc("")),
                                GenTuEnumField("Day", GenTuDoc("")),
                                GenTuEnumField("Hour", GenTuDoc("")),
                                GenTuEnumField("Minute", GenTuDoc("")),
                            ],
                        ),
                    ],
                    fields=[
                        GenTuField(t_nest("Mode"), "mode", GenTuDoc("mode")),
                        GenTuField(t_nest("Period"), "period", GenTuDoc("period")),
                        GenTuField(t_int(), "count", GenTuDoc("count")),
                    ],
                ),
                GenTuTypeGroup(
                    [
                        GenTuStruct(
                            t("Static"),
                            GenTuDoc(""),
                            fields=[
                                GenTuField(t_opt(t_space("Repeat", ["sem", "Time"])),
                                           "repeat", GenTuDoc("")),
                                GenTuField(t("UserTime"), "time", GenTuDoc("")),
                            ],
                        ),
                        GenTuStruct(
                            t("Dynamic"),
                            GenTuDoc(""),
                            fields=[GenTuField(t_str(), "expr", GenTuDoc(""))],
                        ),
                    ],
                    kindGetter="getTimeKind",
                    enumName="TimeKind",
                    variantField="time",
                    variantName="TimeVariant",
                ),
            ],
        ),
        d_org(
            "TimeRange",
            GenTuDoc("Range of time delimited by two points"),
            bases=[t_org("Org")],
            fields=[
                id_field("Time", "from", GenTuDoc("Starting time")),
                id_field("Time", "to", GenTuDoc("Finishing time")),
            ],
        ),
        d_org(
            "Macro",
            GenTuDoc("Inline macro invocation"),
            bases=[t_org("Org")],
            fields=[
                GenTuField(t_str(), "name", GenTuDoc("Macro name"), value='""'),
                GenTuField(
                    t_vec(t_str()),
                    "arguments",
                    GenTuDoc("Raw uninterpreted macro arguments"),
                    value="{}",
                ),
            ],
        ),
        d_org(
            "Symbol",
            GenTuDoc("Text symbol or symbol command"),
            bases=[t_org("Org")],
            nested=[
                GenTuStruct(
                    t("Param"),
                    GenTuDoc("Symbol parameters"),
                    fields=[
                        GenTuField(t_opt(t_str()), "key",
                                   GenTuDoc("Key -- for non-positional")),
                        GenTuField(t_str(), "value", GenTuDoc("Uninterpreted value")),
                    ],
                )
            ],
            fields=[
                GenTuField(t_str(), "name", GenTuDoc("Name of the symbol")),
                GenTuField(t_vec(t_nest("Param")), "parameters",
                           GenTuDoc("Optional list of parameters")),
                GenTuField(t_vec(t_id()), "positional",
                           GenTuDoc("Positional parameters")),
            ],
        ),
        d_org(
            "SubtreeLog",
            GenTuDoc("Single subtree log entry"),
            bases=[t_org("Org")],
            methods=[
                GenTuFunction(
                    t("void"),
                    "setDescription",
                    GenTuDoc(""),
                    arguments=[GenTuIdent(t_id("StmtList"), "desc")],
                )
            ],
            nested=[
                GenTuStruct(t("DescribedLog"),
                            GenTuDoc("Base value for the log variant"),
                            fields=[
                                GenTuField(
                                    t_opt(t_id("StmtList")),
                                    "desc",
                                    GenTuDoc("Optional description of the log entry"),
                                    value="SemIdT<StmtList>::Nil()",
                                )
                            ],
                            nested=[GenTuPass("DescribedLog() {}")]),
                GenTuTypeGroup(
                    [
                        GenTuStruct(
                            t("Priority"),
                            GenTuDoc("Priority added"),
                            bases=[t_org("DescribedLog", [t("SubtreeLog")])],
                            nested=[
                                d_simple_enum(
                                    "Action",
                                    GenTuDoc("Priority change action"),
                                    "Added",
                                    "Removed",
                                    "Changed",
                                ),
                                GenTuPass("Priority() {}")
                            ],
                            fields=[
                                opt_field(
                                    t_space("string", ["std"]),
                                    "oldPriority",
                                    GenTuDoc("Previous priority for change and removal"),
                                ),
                                opt_field(
                                    t_space("string", ["std"]),
                                    "newPriority",
                                    GenTuDoc("New priority for change and addition"),
                                ),
                                id_field("Time", "on",
                                         GenTuDoc("When priority was changed")),
                            ],
                        ),
                        GenTuStruct(
                            t("Note"),
                            GenTuDoc("Timestamped note"),
                            bases=[t_org("DescribedLog", [t("SubtreeLog")])],
                            fields=[
                                id_field("Time", "on", GenTuDoc("Where log was taken"))
                            ],
                            nested=[GenTuPass("Note() {}")],
                        ),
                        GenTuStruct(
                            t("Refile"),
                            GenTuDoc("Refiling action"),
                            bases=[t_org("DescribedLog", [t("SubtreeLog")])],
                            fields=[
                                id_field("Time", "on",
                                         GenTuDoc("When the refiling happened")),
                                id_field("Link", "from",
                                         GenTuDoc("Link to the original subtree")),
                            ],
                            nested=[GenTuPass("Refile() {}")],
                        ),
                        GenTuStruct(
                            t("Clock"),
                            GenTuDoc(
                                "Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`"
                            ),
                            bases=[t_org("DescribedLog", [t("SubtreeLog")])],
                            fields=[
                                k_args(GenTuField(
                                    t_var(t_id("Time"), t_id("TimeRange")),
                                    "range",
                                    GenTuDoc("Start-end or only start period"),
                                    value="SemIdT<Time>::Nil()",
                                ),
                                       ignore=True)
                            ],
                            nested=[GenTuPass("Clock() {}")],
                        ),
                        GenTuStruct(
                            t("State"),
                            GenTuDoc(
                                'Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`'
                            ),
                            bases=[t_org("DescribedLog", [t("SubtreeLog")])],
                            fields=[
                                GenTuField(t("OrgBigIdentKind"), "from", GenTuDoc("")),
                                GenTuField(t("OrgBigIdentKind"), "to", GenTuDoc("")),
                                id_field("Time", "on", GenTuDoc("")),
                            ],
                            nested=[GenTuPass("State() {}")],
                        ),
                        GenTuStruct(
                            t("Tag"),
                            GenTuDoc(
                                'Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`'
                            ),
                            bases=[t_org("DescribedLog", [t("SubtreeLog")])],
                            fields=[
                                id_field("Time", "on",
                                         GenTuDoc("When the log was assigned")),
                                id_field("HashTag", "tag", GenTuDoc("Tag in question")),
                                GenTuField(t_bool(),
                                           "added",
                                           GenTuDoc("Added/removed?"),
                                           value="false"),
                            ],
                            nested=[GenTuPass("Tag() {}")],
                        ),
                    ],
                    kindGetter="getLogKind",
                    variantField="log",
                    variantValue="Note{}",
                    variantName="LogEntry",
                ),
            ],
        ),
        d_org(
            "Subtree",
            GenTuDoc("Subtree"),
            bases=[t_org("Org")],
            fields=[
                GenTuField(t_int(), "level", GenTuDoc("Subtree level"), value="0"),
                opt_field(t_str(), "treeId", GenTuDoc(":ID: property")),
                opt_field(t_str(), "todo", GenTuDoc("Todo state of the tree")),
                opt_field(t_id("Completion"), "completion",
                          GenTuDoc("Task completion state")),
                opt_field(t_id("Paragraph"), "description", GenTuDoc("")),
                vec_field(t_id("HashTag"), "tags", GenTuDoc("Trailing tags")),
                id_field("Paragraph", "title", GenTuDoc("Main title")),
                vec_field(t_id("SubtreeLog"), "logbook",
                          GenTuDoc("Associated subtree log")),
                vec_field(t_nest(t("Property")), "properties",
                          GenTuDoc("Immediate properties")),
                opt_field(t_id("Time"), "closed",
                          GenTuDoc("When subtree was marked as closed")),
                opt_field(t_id("Time"), "deadline", GenTuDoc("When is the deadline")),
                opt_field(t_id("Time"), "scheduled",
                          GenTuDoc("When the event is scheduled")),
            ],
            methods=[
                GenTuFunction(
                    t_vec(t_nest(t("Period"))),
                    "getTimePeriods",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(
                            QualType(name="IntSet",
                                     Parameters=[
                                         t_nest(
                                             QualType(name="Kind", Spaces=[t("Period")]))
                                     ]),
                            "kinds",
                        )
                    ],
                ),
                GenTuFunction(
                    t_vec(t_nest(t("Property"))),
                    "getProperties",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_space("Kind", ["sem", "Subtree", "Property"]),
                                   "kind"),
                        GenTuIdent(t_cr(t_str()), "subkind", value='""'),
                    ],
                ),
                GenTuFunction(
                    t_opt(t_nest(t("Property"))),
                    "getProperty",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_space("Kind", ["sem", "Subtree", "Property"]),
                                   "kind"),
                        GenTuIdent(t_cr(t_str()), "subkind", value='""'),
                    ],
                ),
                GenTuFunction(
                    t_vec(t_nest(t("Property"))),
                    "getContextualProperties",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_nest(t_space("Kind", ["Property"])), "kind"),
                        GenTuIdent(t_cr(t_str()), "subkind", value='""'),
                    ],
                ),
                GenTuFunction(
                    t_opt(t_nest("Property")),
                    "getContextualProperty",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_nest(t_space("Kind", ["Property"])), "kind"),
                        GenTuIdent(t_cr(t_str()), "subkind", value='""'),
                    ],
                ),
            ],
            nested=[
                GenTuStruct(
                    t("Period"),
                    GenTuDoc("Type of the subtree associated time periods"),
                    fields=[
                        GenTuField(
                            t("Kind"),
                            "kind",
                            GenTuDoc(
                                "Time period kind -- not associated with point/range distinction"
                            ),
                        ),
                        k_args(GenTuField(t_var(t_id("Time"), t_id("TimeRange")),
                                          "period",
                                          GenTuDoc("Stored time point/range"),
                                          value="sem::SemIdT<sem::Time>::Nil()"),
                               ignore=True),
                    ],
                    methods=[
                        GenTuFunction(
                            t_id("Time"),
                            "getTime",
                            GenTuDoc("Get associated time point"),
                            impl="return std::get<SemIdT<Time>>(period);",
                        ),
                        GenTuFunction(
                            t_id("Time"),
                            "getTimeRange",
                            GenTuDoc("Get associated time period"),
                            impl="return std::get<SemIdT<TimeRange>>(period);",
                        ),
                    ],
                    #  ;; TODO constructors
                    nested=[
                        GenTuPass("Period() {}"),
                        GenTuEnum(
                            t("Kind"),
                            GenTuDoc("Period kind"),
                            [
                                GenTuEnumField(
                                    "Clocked",
                                    GenTuDoc("Time period of the task execution.")),
                                GenTuEnumField(
                                    "Scheduled",
                                    GenTuDoc(
                                        "Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned"
                                    ),
                                ),
                                GenTuEnumField(
                                    "Titled",
                                    GenTuDoc(
                                        "Single point or time range used in title. Single point can also be a simple time, such as `12:20`"
                                    ),
                                ),
                                GenTuEnumField(
                                    "Deadline",
                                    GenTuDoc(
                                        "Date of task completion. Must be a single time point"
                                    ),
                                ),
                                GenTuEnumField("Created",
                                               GenTuDoc("When the subtree was created")),
                                GenTuEnumField(
                                    "Repeated",
                                    GenTuDoc("Last repeat time of the recurring tasks")),
                            ],
                        ),
                        GenTuPass(
                            "Period(CR<Variant<SemIdT<Time>, SemIdT<TimeRange>>> period, Kind kind) : period(period), kind(kind) {}"
                        ),
                    ],
                ),
                GenTuStruct(
                    t("Property"),
                    GenTuDoc("Single subtree property"),
                    fields=[
                        GenTuField(
                            t_nest("SetMode"),
                            "mainSetRule",
                            GenTuDoc(""),
                            value="SetMode::Override",
                        ),
                        GenTuField(t_nest("SetMode"),
                                   "subSetRule",
                                   GenTuDoc(""),
                                   value="SetMode::Override"),
                        GenTuField(
                            t_nest("InheritanceMode"),
                            "inheritanceMode",
                            GenTuDoc(""),
                            value="InheritanceMode::ThisAndSub",
                        ),
                    ],
                    nested=[
                        GenTuPass("Property() {}"),
                        d_simple_enum("SetMode", GenTuDoc(""), "Override", "Add",
                                      "Subtract"),
                        d_simple_enum("InheritanceMode", GenTuDoc(""), "ThisAndSub",
                                      "OnlyThis", "OnlySub"),
                        GenTuTypeGroup([
                            GenTuStruct(
                                t("Nonblocking"),
                                GenTuDoc(""),
                                fields=[GenTuField(t_bool(), "isBlocking", GenTuDoc(""))],
                                nested=[GenTuPass("Nonblocking() {}")]),
                            GenTuStruct(t("Trigger"),
                                        GenTuDoc(""),
                                        nested=[GenTuPass("Trigger() {}")]),
                            GenTuStruct(
                                t("Origin"),
                                GenTuDoc(""),
                                fields=[GenTuField(t_str(), "text", GenTuDoc(""))],
                                nested=[GenTuPass("Origin() {}")]),
                            GenTuStruct(
                                t("ExportLatexClass"),
                                GenTuDoc(""),
                                fields=[GenTuField(t_str(), "latexClass", GenTuDoc(""))],
                                nested=[GenTuPass("ExportLatexClass() {}")]),
                            GenTuStruct(
                                t("ExportLatexClassOptions"),
                                GenTuDoc(""),
                                fields=[
                                    GenTuField(t_vec(t_str()), "options", GenTuDoc(""))
                                ],
                                nested=[GenTuPass("ExportLatexClassOptions() {}")]),
                            GenTuStruct(
                                t("ExportLatexHeader"),
                                GenTuDoc(""),
                                fields=[GenTuField(t_str(), "header", GenTuDoc(""))],
                                nested=[GenTuPass("ExportLatexHeader() {}")]),
                            GenTuStruct(
                                t("ExportLatexCompiler"),
                                GenTuDoc(""),
                                fields=[GenTuField(t_str(), "compiler", GenTuDoc(""))],
                                nested=[GenTuPass("ExportLatexCompiler() {}")]),
                            GenTuStruct(
                                t("Ordered"),
                                GenTuDoc(""),
                                fields=[GenTuField(t_bool(), "isOrdered", GenTuDoc(""))],
                                nested=[GenTuPass("Ordered() {}")]),
                            GenTuStruct(t("Effort"),
                                        GenTuDoc(""),
                                        fields=[
                                            GenTuField(t_int(),
                                                       "hours",
                                                       GenTuDoc(""),
                                                       value="0"),
                                            GenTuField(t_int(),
                                                       "minutes",
                                                       GenTuDoc(""),
                                                       value="0"),
                                        ],
                                        nested=[GenTuPass("Effort() {}")]),
                            GenTuStruct(
                                t("Visibility"),
                                GenTuDoc(""),
                                nested=[
                                    GenTuPass("Visibility() {}"),
                                    d_simple_enum(
                                        "Level",
                                        GenTuDoc(""),
                                        "Folded",
                                        "Children",
                                        "Content",
                                        "All",
                                    )
                                ],
                                fields=[
                                    GenTuField(t_nest("Level"), "level", GenTuDoc(""))
                                ],
                            ),
                            GenTuStruct(
                                t("ExportOptions"),
                                GenTuDoc(""),
                                nested=[GenTuPass("ExportOptions() {}")],
                                fields=[
                                    GenTuField(t_str(), "backend", GenTuDoc("")),
                                    GenTuField(t_map(t_str(), t_str()), "values",
                                               GenTuDoc("")),
                                ],
                            ),
                            GenTuStruct(
                                t("Blocker"),
                                GenTuDoc(""),
                                nested=[GenTuPass("Blocker() {}")],
                                fields=[
                                    GenTuField(t_vec(t_str()), "blockers", GenTuDoc(""))
                                ],
                            ),
                            GenTuStruct(t("Unnumbered"),
                                        GenTuDoc(""),
                                        nested=[GenTuPass("Unnumbered() {}")]),
                            GenTuStruct(
                                t("Created"),
                                GenTuDoc(""),
                                nested=[GenTuPass("Created() {}")],
                                fields=[id_field("Time", "time", GenTuDoc(""))],
                            ),
                        ]),
                        GenTuPass("Property(CR<Data> data) : data(data) {}"),
                        GenTuPass(
                            'bool matches(Kind kind, CR<std::string> subkind = "") const;'
                        ),
                    ],
                ),
            ],
        ),
        d_org("LatexBody",
              GenTuDoc("Latex code body"),
              bases=[t_org("Org")],
              concreteKind=False),
        d_org("InlineMath", GenTuDoc("Inline math"), bases=[t_org("LatexBody")]),
        d_org(
            "Leaf",
            GenTuDoc("Final node"),
            bases=[t_org("Org")],
            concreteKind=False,
            fields=[
                GenTuField(t_str(), "text", GenTuDoc("Final leaf value"), value='""')
            ],
        ),
        d_org("Escaped", GenTuDoc("Escaped text"), bases=[t_org("Leaf")]),
        d_org("Newline", GenTuDoc("\\n newline"), bases=[t_org("Leaf")]),
        d_org("Space", GenTuDoc('\' "space",'), bases=[t_org("Leaf")]),
        d_org("Word", GenTuDoc("word"), bases=[t_org("Leaf")]),
        d_org("AtMention", GenTuDoc("@mention"), bases=[t_org("Leaf")]),
        d_org("RawText", GenTuDoc(""), bases=[t_org("Leaf")]),
        d_org("Punctuation", GenTuDoc(""), bases=[t_org("Leaf")]),
        d_org("Placeholder", GenTuDoc(""), bases=[t_org("Leaf")]),
        d_org("BigIdent", GenTuDoc(""), bases=[t_org("Leaf")]),
        d_org(
            "Markup",
            GenTuDoc(""),
            bases=[t_org("Org")],
            concreteKind=False,
        ),
        d_org("Bold", GenTuDoc(""), bases=[t_org("Markup")]),
        d_org("Underline", GenTuDoc(""), bases=[t_org("Markup")]),
        d_org("Monospace", GenTuDoc(""), bases=[t_org("Markup")]),
        d_org("MarkQuote", GenTuDoc(""), bases=[t_org("Markup")]),
        d_org("Verbatim", GenTuDoc(""), bases=[t_org("Markup")]),
        d_org("Italic", GenTuDoc(""), bases=[t_org("Markup")]),
        d_org("Strike", GenTuDoc(""), bases=[t_org("Markup")]),
        d_org("Par", GenTuDoc(""), bases=[t_org("Markup")]),
        d_org(
            "List",
            GenTuDoc(""),
            bases=[t_org("Org")],
            methods=[
                GenTuFunction(t_bool(), "isDescriptionList", GenTuDoc(""), isConst=True)
            ],
        ),
        d_org(
            "ListItem",
            GenTuDoc(""),
            bases=[t_org("Org")],
            fields=[
                GenTuField(t_nest("Checkbox"),
                           "checkbox",
                           GenTuDoc(""),
                           value="Checkbox::None"),
                GenTuField(t_opt(t_id("Paragraph")),
                           "header",
                           GenTuDoc(""),
                           value="std::nullopt"),
            ],
            nested=[d_simple_enum("Checkbox", GenTuDoc(""), "None", "Done", "Empty")],
            methods=[
                GenTuFunction(
                    t_bool(),
                    "isDescriptionItem",
                    GenTuDoc(""),
                    isConst=True,
                    impl="return header.has_value();",
                )
            ],
        )
        # ;; TODO
        ,
        d_org(
            "Link",
            GenTuDoc(""),
            bases=[t_org("Org")],
            fields=[
                GenTuField(t_opt(t_id("Paragraph")),
                           "description",
                           GenTuDoc(""),
                           value="std::nullopt")
            ],
            methods=[
                GenTuFunction(
                    t_opt(t_id()),
                    "resolve",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[GenTuIdent(t_cr(t_space("Document", ["sem"])), "doc")],
                ),
                GenTuFunction(t_opt(t_id()), "resolve", GenTuDoc(""), isConst=True),
            ],
            nested=[
                GenTuTypeGroup(
                    [
                        GenTuStruct(
                            t("Raw"),
                            GenTuDoc(""),
                            fields=[(GenTuField(t_str(), "text", GenTuDoc("")))],
                        ),
                        GenTuStruct(t("Id"),
                                    GenTuDoc(""),
                                    fields=[(GenTuField(t_str(), "text", GenTuDoc("")))]),
                        GenTuStruct(
                            t("Person"),
                            GenTuDoc(""),
                            fields=[(GenTuField(t_str(), "name", GenTuDoc("")))],
                        ),
                        GenTuStruct(
                            t("Footnote"),
                            GenTuDoc(""),
                            fields=[(GenTuField(t_str(), "target", GenTuDoc("")))],
                        ),
                        GenTuStruct(
                            t("File"),
                            GenTuDoc(""),
                            fields=[(GenTuField(t_str(), "file", GenTuDoc("")))],
                        ),
                    ],
                    kindGetter="getLinkKind",
                )
            ],
        ),
        d_org(
            "Document",
            GenTuDoc(""),
            bases=[t_org("Org")],
            methods=[
                GenTuFunction(
                    t_opt(t_id()),
                    "resolve",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[GenTuIdent(t_cr(t_id()), "node")],
                ),
                GenTuFunction(
                    t_opt(t_id("Subtree")),
                    "getSubtree",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[GenTuIdent(t_cr(t_str()), "id")],
                ),
                GenTuFunction(
                    t_vec(t_space("Property", ["sem", "Subtree"])),
                    "getProperties",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_space("Kind", ["sem", "Subtree", "Property"]),
                                   "kind"),
                        GenTuIdent(t_cr(t_str()), "subKind", value='""'),
                    ],
                ),
                GenTuFunction(
                    t_opt(t_space("Property", ["sem", "Subtree"])),
                    "getProperty",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_space("Kind", ["sem", "Subtree", "Property"]),
                                   "kind"),
                        GenTuIdent(t_cr(t_str()), "subKind", value='""'),
                    ],
                ),
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
                opt_field(t_str(), "exportFileName", GenTuDoc("")),
            ],
        ),
        d_org(
            "ParseError",
            GenTuDoc(""),
            bases=[t_org("Org")],
        ),
        d_org(
            "FileTarget",
            GenTuDoc(""),
            bases=[t_org("Org")],
            fields=[
                GenTuField(t_str(), "path", GenTuDoc("")),
                opt_field(t_int(), "line", GenTuDoc("")),
                opt_field(t_str(), "searchTarget", GenTuDoc("")),
                GenTuField(t_bool(), "restrictToHeadlines", GenTuDoc(""), value="false"),
                opt_field(t_str(), "targetId", GenTuDoc("")),
                opt_field(t_str(), "regexp", GenTuDoc("")),
            ],
        ),
        d_org(
            "TextSeparator",
            GenTuDoc(""),
            bases=[t_org("Org")],
        ),
        d_org(
            "Include",
            GenTuDoc(""),
            bases=[t_org("Org")],
            nested=[
                GenTuTypeGroup(
                    [
                        GenTuStruct(t("Example"), GenTuDoc("")),
                        GenTuStruct(t("Export"), GenTuDoc("")),
                        GenTuStruct(t("Src"), GenTuDoc("")),
                        GenTuStruct(t("OrgDocument"), GenTuDoc("")),
                    ],
                    kindGetter="getIncludeKind",
                )
            ],
        ),
        d_org(
            "DocumentOptions",
            GenTuDoc(""),
            bases=[t_org("Org")],
            methods=[
                GenTuFunction(
                    t_vec(t_space("Property", ["sem", "Subtree"])),
                    "getProperties",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_space("Kind", ["sem", "Subtree", "Property"]),
                                   "kind"),
                        GenTuIdent(t_cr(t_str()), "subKind", value='""'),
                    ],
                ),
                GenTuFunction(
                    t_opt(t_space("Property", ["sem", "Subtree"])),
                    "getProperty",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_space("Kind", ["sem", "Subtree", "Property"]),
                                   "kind"),
                        GenTuIdent(t_cr(t_str()), "subKind", value='""'),
                    ],
                ),
            ],
            nested=[
                GenTuPass("using TocExport = Variant<bool, int>;"),
                d_simple_enum("BrokenLinks", GenTuDoc(""), "Raise", "Ignore", "Mark"),
                d_simple_enum(
                    "Visibility",
                    GenTuDoc(""),
                    "Overview",
                    "Content",
                    "ShowAll",
                    "Show2Levels",
                    "Show3Levels",
                    "Show4Levels",
                    "Show5Levels",
                    "ShowEverything",
                ),
            ],
            fields=[
                GenTuField(t_nest("BrokenLinks"),
                           "brokenLinks",
                           GenTuDoc(""),
                           value="BrokenLinks::Mark"),
                GenTuField(
                    t_nest("Visibility"),
                    "initialVisibility",
                    GenTuDoc(""),
                    value="Visibility::ShowEverything",
                ),
                GenTuField(t_nest(t("TocExport")),
                           "tocExport",
                           GenTuDoc(""),
                           value="false"),
                GenTuField(t_vec(t_space("Property", ["sem", "Subtree"])), "properties",
                           GenTuDoc("")),
                GenTuField(t_bool(), "smartQuotes", GenTuDoc(""), value="false"),
                GenTuField(t_bool(), "emphasizedText", GenTuDoc(""), value="false"),
                GenTuField(t_bool(), "specialStrings", GenTuDoc(""), value="false"),
                GenTuField(t_bool(), "fixedWidthSections", GenTuDoc(""), value="false"),
                GenTuField(t_bool(), "includeTimestamps", GenTuDoc(""), value="false"),
                GenTuField(t_bool(), "preserveLineBreaks", GenTuDoc(""), value="false"),
                GenTuField(t_bool(), "plaintextSubscripts", GenTuDoc(""), value="false"),
                GenTuField(t_bool(), "exportArchived", GenTuDoc(""), value="false"),
                GenTuField(t_bool(), "exportWithAuthor", GenTuDoc(""), value="false"),
                GenTuField(t_bool(), "exportBrokenLinks", GenTuDoc(""), value="false"),
                GenTuField(t_bool(), "exportWithClock", GenTuDoc(""), value="false"),
                GenTuField(t_bool(), "exportWithCreator", GenTuDoc(""), value="false"),
            ],
        ),
        d_org(
            "DocumentGroup",
            GenTuDoc(""),
            bases=[t_org("Org")],
        ),
    ]

def get_org_token_kind() -> GenTuEnum:
    fields = [
        GenTuEnumField("None", GenTuDoc("")),
        GenTuEnumField("Eof", GenTuDoc("")),
        GenTuEnumField("CmdPrefix", GenTuDoc("`#+` prefix token for the command")),
        #region Commands
        #region Line-commands
        GenTuEnumField("CmdLine", GenTuDoc("Generic line command")),
        GenTuEnumField("CmdTitle", GenTuDoc("#+title: line command token")),
        GenTuEnumField("CmdCaption", GenTuDoc("#+caption")),
        GenTuEnumField("CmdFiletags", GenTuDoc("#+filetags")),
        GenTuEnumField("CmdColumns", GenTuDoc("#+columns")),
        GenTuEnumField("CmdPropertyArgs", GenTuDoc("#+property")),
        GenTuEnumField("CmdPropertyText", GenTuDoc("#+property")),
        GenTuEnumField("CmdPropertyRaw", GenTuDoc("#+property")),
        GenTuEnumField("CmdOptions", GenTuDoc("#+options")),
        GenTuEnumField("CmdSetupfile", GenTuDoc("")),
        GenTuEnumField("CmdInclude", GenTuDoc("")),
        GenTuEnumField("CmdAttrLatex", GenTuDoc("`#+attr_latex:`")),
        GenTuEnumField("CmdAttrImg", GenTuDoc("`#+attr_img:`")),
        GenTuEnumField("CmdAttrHtml", GenTuDoc("`#+attr_html:`")),
        GenTuEnumField("CmdHtmlHead", GenTuDoc("`#+html_head:`")),
        GenTuEnumField("CmdLanguage", GenTuDoc("`#+language:`")),
        GenTuEnumField("CmdLatexClassOptions", GenTuDoc("`#+latex_class_options`")),
        GenTuEnumField("CmdLatexClass", GenTuDoc("")),
        GenTuEnumField("CmdLatexCompiler", GenTuDoc("")),
        GenTuEnumField("CmdAuthor", GenTuDoc("`#+author:`")),
        GenTuEnumField("CmdBind", GenTuDoc("`#+bind:`")),
        GenTuEnumField("CmdCreator", GenTuDoc("`#+creator:`")),
        GenTuEnumField("CmdLatexHeader", GenTuDoc("`#+latex_header`")),
        GenTuEnumField("CmdResults", GenTuDoc("`#+results:`")),
        GenTuEnumField("CmdCall", GenTuDoc("`#+call:`")),
        GenTuEnumField("CmdName", GenTuDoc("`#+name:`")),
        GenTuEnumField("CmdHeader", GenTuDoc("`#+header:`")),
        #endregion
        #region Command-arguments
        GenTuEnumField("CmdArgumentsBegin", GenTuDoc("List of command arguments")),
        GenTuEnumField("CmdArgumentsEnd",
                       GenTuDoc("End of the command arguments list")),
        GenTuEnumField("CmdKey", GenTuDoc("")),
        GenTuEnumField("CmdValue", GenTuDoc("")),
        GenTuEnumField("CmdFlag", GenTuDoc("")),
        GenTuEnumField("CmdBracket", GenTuDoc("`#+results[HASH...]`")),
        #endregion
        #region Block-commands
        #tag begin-end
        GenTuEnumField("CmdBegin", GenTuDoc("`#+begin` part of generic multiline command.")),
        GenTuEnumField("CmdEnd", GenTuDoc("")),
        GenTuEnumField("CmdSrcBegin", GenTuDoc("")),
        GenTuEnumField("CmdSrcEnd", GenTuDoc("")),
        GenTuEnumField("CmdQuoteBegin", GenTuDoc("")),
        GenTuEnumField("CmdQuoteEnd", GenTuDoc("")),
        GenTuEnumField("CmdCenterBegin", GenTuDoc("")),
        GenTuEnumField("CmdCenterEnd", GenTuDoc("")),
        GenTuEnumField("CmdTableBegin", GenTuDoc("")),
        GenTuEnumField("CmdTableEnd", GenTuDoc("")),
        GenTuEnumField("CmdAdmonitionBegin", GenTuDoc("")),
        GenTuEnumField("CmdAdmonitionEnd", GenTuDoc("")),
        GenTuEnumField("CmdDynamicBegin", GenTuDoc("")),
        GenTuEnumField("CmdDynamicEnd", GenTuDoc("`#+begin:`")),
        GenTuEnumField("CmdExampleBegin", GenTuDoc("")),
        GenTuEnumField("CmdExampleEnd", GenTuDoc("`#+begin:`")),
        GenTuEnumField("CmdExportBegin", GenTuDoc("")),
        GenTuEnumField("CmdExportEnd", GenTuDoc("`#+begin:`")),
        GenTuEnumField("CmdDetailsBegin", GenTuDoc("")),
        GenTuEnumField("CmdDetailsEnd", GenTuDoc("`#+begin:`")),
        GenTuEnumField("CmdSummaryBegin", GenTuDoc("")),
        GenTuEnumField("CmdSummaryEnd", GenTuDoc("`#+begin:`")),
        GenTuEnumField("CmdTblfm", GenTuDoc("#+tblfm:")),
        #tag Inner
        GenTuEnumField("QuoteContent", GenTuDoc("`#+quote` content")),
        GenTuEnumField("CmdBackendPass", GenTuDoc("Backend-specific passthrough")),
        GenTuEnumField("CmdContentBegin", GenTuDoc("Content wrapper for the block commands")),
        GenTuEnumField("CmdContentEnd", GenTuDoc("End of content wrapper")),
        GenTuEnumField("CmdSrcCodeContent", GenTuDoc("Block of code inside `#+begin_src`")),
        GenTuEnumField("CmdSrcLangName", GenTuDoc("Source code block language name")),
        GenTuEnumField(
            "CmdSrcTextBlock",
            GenTuDoc(
                "Code before noweb placeholder. Requires separate token to handle `##<<commented>>` - prefix comment should be duplicated for each line of the placeholder expansion."
            ),
        ),
        #endregion
        #region Table
        GenTuEnumField("TblContent", GenTuDoc("Block of text inside `#+table`")),
        GenTuEnumField("TblBegin", GenTuDoc("")),
        GenTuEnumField("TblEnd", GenTuDoc("")),
        GenTuEnumField("TblCellBody", GenTuDoc("Unformatted table cell body")),
        GenTuEnumField("TblRowSpec", GenTuDoc("`#+row` command together with parameters")),
        GenTuEnumField("TblCellSpec", GenTuDoc("`#+cell` command with parameters")),
        GenTuEnumField("TblPipeBegin", GenTuDoc("")),
        GenTuEnumField("TblPipeSeparator", GenTuDoc("Vertical pipe (`|`) cell separator")),
        GenTuEnumField("TblPipeEnd", GenTuDoc("")),
        GenTuEnumField("TblPipeCellBegin", GenTuDoc("")),
        GenTuEnumField(
            "TblDashSeparator",
            GenTuDoc("Horizontal dash (`---`, `:---`, `---:` or `:---:`) row separator"),
        ),
        GenTuEnumField("TblCornerPlus", GenTuDoc("Corner plus (`+`)")),
        GenTuEnumField("TblCellContentBegin", GenTuDoc("Start of the table cell content section")),
        GenTuEnumField("TblCellContentEnd", GenTuDoc("End of the table cell content section")),
        #endregion
        #endregion
        GenTuEnumField(
            "CodeText",
            GenTuDoc(
                "Uninterrupted text span without newlines - either a whole line or sub subsection of it if callout or tangle elements were detected"
            ),
        ),
        GenTuEnumField("Text", GenTuDoc("")),
        GenTuEnumField(
            "StmtList",
            GenTuDoc(
                "Unlexed group of statements - used in the list content to enable secondary parsing."
            ),
        ),
        GenTuEnumField("StmtListBegin",
                       GenTuDoc("Start of the expanded statement list content")),
        GenTuEnumField("StmtListEnd",
                       GenTuDoc("End of the expanded statement list content")),
        #region List-items
        GenTuEnumField("Indent", GenTuDoc("Increase in indentation")),
        GenTuEnumField("Dedent", GenTuDoc("Decrease in indentation")),
        GenTuEnumField("SameIndent", GenTuDoc("")),
        GenTuEnumField("NoIndent", GenTuDoc("")),
        GenTuEnumField("ListBegin", GenTuDoc("Start of the list token group")),
        GenTuEnumField("ListItemBegin", GenTuDoc("Start of the list item element")),
        GenTuEnumField("ListClock",
                       GenTuDoc("`CLOCK:` entry at the start of the logbook entry list")),
        GenTuEnumField("ListPlus", GenTuDoc("")),
        GenTuEnumField("ListStar", GenTuDoc("")),
        GenTuEnumField("ListDescBegin", GenTuDoc("Start of the description list key,")),
        GenTuEnumField("ListDescEnd", GenTuDoc("End of the description list key `::`")),
        GenTuEnumField("ListItemEnd", GenTuDoc("End of the list item")),
        GenTuEnumField("ListEnd", GenTuDoc("Complete end of the list token group")),
        GenTuEnumField("Checkbox", GenTuDoc("List or subtree checkbox")),
        GenTuEnumField(
            "ListDoubleColon",
            GenTuDoc("Double colon between description list tag and body"),
        ),
        #endregion
        #region Subtree
        GenTuEnumField("SubtreeTodoState", GenTuDoc("")),
        GenTuEnumField("SubtreeUrgency", GenTuDoc("Subtree importance marker")),
        GenTuEnumField("SubtreeCompletion", GenTuDoc("Subtree completion marker")),
        GenTuEnumField("SubtreeStars", GenTuDoc("Subtree prefix")),
        GenTuEnumField("SubtreeTagSeparator", GenTuDoc("")),
        GenTuEnumField("SubtreeTime", GenTuDoc("")),
        GenTuEnumField("SubtreeEnd", GenTuDoc("")),
        #region Subtree-properties
        GenTuEnumField("LogBook", GenTuDoc("Logbook including content")),
        GenTuEnumField("Drawer", GenTuDoc("Drawer including content")),
        GenTuEnumField("ColonLiteral", GenTuDoc("Literal block with `:`")),
        GenTuEnumField(
            "ColonIdent",
            GenTuDoc(
                "Drawer or source code block wrappers with colon-wrapped identifiers. `:results:`, `:end:` etc."
            ),
        ),
        GenTuEnumField("ColonProperties",
                       GenTuDoc("Start of the `:PROPERTIES:` block drawer block")),
        GenTuEnumField("ColonDescription",
                       GenTuDoc("Start of the `:description:` drawer block")),
        GenTuEnumField("ColonEnd", GenTuDoc("")),
        GenTuEnumField("ColonLogbook", GenTuDoc("")),
        GenTuEnumField("RawLogbook", GenTuDoc("")),
        GenTuEnumField("LogbookBegin", GenTuDoc("")),
        GenTuEnumField("LogbookEnd", GenTuDoc("")),
        GenTuEnumField("RawProperty", GenTuDoc("")),
        GenTuEnumField("PropRawKey", GenTuDoc("Properties with raw string literal values")),
        GenTuEnumField("PropTextKey", GenTuDoc("Properties with text (paragraph) values")),
        #endregion
        #endregion
        #region Time
        GenTuEnumField(
            "ImplicitTime",
            GenTuDoc("""You can write time ranges without any additional formatting for
   subtrees that have a diary timestamps. For example, you have a
   complex date predicate, but event occurs for `18:00-21:00`, so you
   write it in the random place in the subtree."""),
        ),
        GenTuEnumField(
            "TimeDuration",
            GenTuDoc(
                "Time duration for the `effort` property or time range length evaluation"
            ),
        ),
        GenTuEnumField("DynamicTimeContent", GenTuDoc("Dynamic time content")),
        GenTuEnumField("StaticTimeDatePart",
                       GenTuDoc("year-month-day part of the timestamp")),
        GenTuEnumField("StaticTimeDayPart", GenTuDoc("weekday part of the timestamp")),
        GenTuEnumField("StaticTimeClockPart", GenTuDoc("Clock part of the timestamp")),
        GenTuEnumField("StaticTimeRepeater",
                       GenTuDoc("Type of the time repeater: `+`, `++`, `.+`")),
        GenTuEnumField(
            "TimeDash",
            GenTuDoc(
                "Separator dash between two periods in the time range (`<start>--<finish.`)"
            ),
        ),
        GenTuEnumField("TimeArrow",
                       GenTuDoc("Time range evaluation arrow `[from]--[to] =>`")),
        #endregion
        #region Text
        GenTuEnumField("Comment", GenTuDoc("line or inline comment")),

        GenTuEnumField("Link", GenTuDoc("Any kind of link")),
        #tag Markup
        GenTuEnumField("BoldBegin", GenTuDoc("")),
        GenTuEnumField("BoldEnd", GenTuDoc("")),
        GenTuEnumField("ItalicBegin", GenTuDoc("")),
        GenTuEnumField("ItalicEnd", GenTuDoc("")),
        GenTuEnumField("VerbatimBegin", GenTuDoc("")),
        GenTuEnumField("VerbatimEnd", GenTuDoc("")),
        GenTuEnumField("MonospaceBegin", GenTuDoc("")),
        GenTuEnumField("MonospaceEnd", GenTuDoc("")),
        GenTuEnumField("BacktickBegin", GenTuDoc("")),
        GenTuEnumField("BacktickEnd", GenTuDoc("")),
        GenTuEnumField("UnderlineBegin", GenTuDoc("")),
        GenTuEnumField("UnderlineEnd", GenTuDoc("")),
        GenTuEnumField("StrikeBegin", GenTuDoc("")),
        GenTuEnumField("StrikeEnd", GenTuDoc("")),
        GenTuEnumField("QuoteBegin", GenTuDoc("")),
        GenTuEnumField("QuoteEnd", GenTuDoc("")),
        GenTuEnumField("Punctuation", GenTuDoc("")),
        #tag Link
        GenTuEnumField("AngleBegin", GenTuDoc("Placeholder Begin")),
        GenTuEnumField("AngleEnd", GenTuDoc("Placeholder End")),
        GenTuEnumField("DoubleAngleBegin", GenTuDoc("`<<` - open for noweb or anchor placeholder")),
        GenTuEnumField("DoubleAngleEnd", GenTuDoc("`>>` - close for noweb or anchor placeholder")),
        GenTuEnumField("TripleAngleBegin", GenTuDoc("`<<<` - radio target Begin")),
        GenTuEnumField("TripleAngleEnd", GenTuDoc("`>>>` - radio target End")),
        GenTuEnumField("LinkBegin", GenTuDoc("")),
        GenTuEnumField("LinkEnd", GenTuDoc("")),
        GenTuEnumField("RawUrl", GenTuDoc("")),
        GenTuEnumField("LinkTargetBegin", GenTuDoc("")),
        GenTuEnumField("LinkTargetEnd", GenTuDoc("")),
        GenTuEnumField(
            "LinkInternal",
            GenTuDoc(
                "No protocol is used in the link, it is targeting some internal named entry."
            ),
        ),
        GenTuEnumField("LinkProtocol",
                       GenTuDoc("Protocol used by the link - `file:`, `https:` etc.")),
        GenTuEnumField(
            "LinkFull",
            GenTuDoc(
                "Full token for the link, used in cases where it does not make sense to fracture the token - regular https URLs etc."
            ),
        ),
        GenTuEnumField("LinkPath", GenTuDoc("Link path for searches in file")),
        GenTuEnumField(
            "LinkTarget",
            GenTuDoc(
                "Target of the link protocol that does not follow regular URI encoding scheme - for example `id:`, `elisp`, or `shell` links."
            ),
        ),
        GenTuEnumField(
            "LinkExtraSeparator",
            GenTuDoc("Separator of the extra content in the link, `::`"),
        ),
        GenTuEnumField("LinkExtra",
                       GenTuDoc("Additional parametrization for the link search")),
        GenTuEnumField("LinkDescriptionBegin", GenTuDoc("")),
        GenTuEnumField("LinkDescriptionEnd", GenTuDoc("")),
        #tag Paragraph
        GenTuEnumField("TextSeparator", GenTuDoc("")),
        GenTuEnumField(
            "ParagraphBegin",
            GenTuDoc(
                "Fake token inserted by the lexer to delimit start of the paragraph"),
        ),
        GenTuEnumField("ParagraphEnd", GenTuDoc("")),
        GenTuEnumField("FootnoteBegin", GenTuDoc("")),
        GenTuEnumField("FootnoteEnd", GenTuDoc("")),
        #tag Paragraph-tokens
        GenTuEnumField("Word", GenTuDoc("Regular word in the paragraph")),
        GenTuEnumField("DoubleColon", GenTuDoc("")),
        GenTuEnumField("Number", GenTuDoc("")),
        GenTuEnumField(
            "Escaped",
            GenTuDoc(
                "Escaped character in plain text - `\\*`, `\\/` etc. Escaped characters and sequences thereof are treated like a regular plain text."
            ),
        ),
        GenTuEnumField(
            "DoubleSlash",
            GenTuDoc(
                "Put at the end of the lexer first logbook line to separate the  note, otherwise is treated as standalone escaped slash."
            ),
        ),
        GenTuEnumField("Newline", GenTuDoc("Explicit newline a paragraph")),
        GenTuEnumField("MaybeWord", GenTuDoc("")),
        GenTuEnumField("Space", GenTuDoc("Space in the paragraph")),
        GenTuEnumField("BigIdent",
                       GenTuDoc("`TODO`, `NOTE` and similar capitalized words")),
        GenTuEnumField(
            "RawText",
            GenTuDoc(
                "Unparsed raw text, either as a part of paragraph or some embedded construction such as link address."
            ),
        ),
        GenTuEnumField("Ident", GenTuDoc("")),
        #tag Latex
        GenTuEnumField("SymbolBegin",
                GenTuDoc("Unquoted `\\symbol` directly in the text")),
        GenTuEnumField("DollarBegin", GenTuDoc("Opening dollar inline latex math")),
        GenTuEnumField("DollarEnd", GenTuDoc("Closing dollar for inline latex math")),
        GenTuEnumField("DoubleDollarBegin", GenTuDoc("Opening `$` for inline latex")),
        GenTuEnumField("DoubleDollarEnd", GenTuDoc("Closing `$` for inline latex")),
        GenTuEnumField("LatexParBegin", GenTuDoc("Opening `\\(` for inline latex math")),
        GenTuEnumField("LatexParEnd", GenTuDoc("Closing `\\)` for inline latex math")),
        GenTuEnumField("LatexBraceBegin",
                       GenTuDoc("Opening `\\[` for inline display latex equation")),
        GenTuEnumField("LatexBraceEnd",
                       GenTuDoc("Closing `\\]` for inline display latex equation")),
        GenTuEnumField("LatexInlineRaw",
                       GenTuDoc("Content of the brace/par-enclosed math")),
        #tag Hashtag
        GenTuEnumField("AtBracket", GenTuDoc("Inline annotation")),
        GenTuEnumField("AtMention", GenTuDoc("`@user` mention in the text")),
        GenTuEnumField("HashTag", GenTuDoc("Start of the inline hashtag `#tag`")),
        GenTuEnumField("HashTagSub", GenTuDoc("Nested hashtag separator")),
        GenTuEnumField("HashTagBegin",
                       GenTuDoc("Start of the nested hashtag grop bracket")),
        GenTuEnumField("HashTagEnd",
                       GenTuDoc("End of the nested hashtag group separator")),
        #tag Punctuation
        GenTuEnumField(
            "Comma",
            GenTuDoc(
                "Comma - punctuation or a syntax element (e.g. for macro arguments)"),
        ),
        GenTuEnumField("ParBegin",
                       GenTuDoc("Paren open - punctuation or a syntax element")),
        GenTuEnumField("ParEnd",
                       GenTuDoc("Paren close - punctuation or a syntax element")),
        GenTuEnumField("BraceBegin",
                       GenTuDoc("`[`")),
        GenTuEnumField("BraceEnd",
                       GenTuDoc("`]`")),
        GenTuEnumField("Colon", GenTuDoc("")),
        GenTuEnumField("Circumflex", GenTuDoc("`^` possible superscript in the text")),
        #tag Macro
        GenTuEnumField("MacroBegin", GenTuDoc("Start of the macro call `{{{`")),
        GenTuEnumField("MacroEnd", GenTuDoc("Close of the macro call `}}}`")),
        GenTuEnumField("MetaBraceBegin", GenTuDoc("")),
        GenTuEnumField("MetaBraceBody", GenTuDoc("")),
        GenTuEnumField("MetaBraceEnd", GenTuDoc("")),
        GenTuEnumField("MetaArgsBegin", GenTuDoc("")),
        GenTuEnumField("MetaArgsBody", GenTuDoc("")),
        GenTuEnumField("MetaArgsEnd", GenTuDoc("")),
        #region Inline-code
        GenTuEnumField("InlineSrc",
                       GenTuDoc("Start of an inline source code block: `src_nim[]{}`")),
        GenTuEnumField("InlineCall",
                       GenTuDoc("Start of an inline call block: `call_name[]{}`")),
        GenTuEnumField("CurlyStart",
                       GenTuDoc("Start of the curly section of an inline source/call")),
        GenTuEnumField("CurlyEnd",
                       GenTuDoc("End of the curly section of an inline source/call")),
        GenTuEnumField("DoubleAt", GenTuDoc("Inline backend passthrough `@@`")),
        #tag Inline-src
        GenTuEnumField("SrcBegin", GenTuDoc("")),
        GenTuEnumField("SrcName", GenTuDoc("")),
        GenTuEnumField("SrcArgs", GenTuDoc("")),
        GenTuEnumField("SrcBody", GenTuDoc("")),
        GenTuEnumField("SrcEnd", GenTuDoc("")),
        #tag Inline-call
        GenTuEnumField("CallBegin", GenTuDoc("")),
        GenTuEnumField("CallName", GenTuDoc("")),
        GenTuEnumField("CallInsideHeader", GenTuDoc("")),
        GenTuEnumField("CallArgs", GenTuDoc("")),
        GenTuEnumField("EndHeader", GenTuDoc("")),
        GenTuEnumField("CallEnd", GenTuDoc("")),
        GenTuEnumField("CmdArguments", GenTuDoc("")),
        #endregion
        #endregion
    ]

    return GenTuEnum(t("OrgTokenKind"), GenTuDoc(""), fields)


def get_enums():
    return [
        #tag org placement kind
        GenTuEnum(
            t("OrgSemPlacement"),
            GenTuDoc("Semantic location of the sem org node in the parent tree"),
            [
                GenTuEnumField("TreeTitle", GenTuDoc("Subtree title")),
                GenTuEnumField("TreeBody", GenTuDoc("Inner content of the subtree")),
                GenTuEnumField("LinkDescription",
                               GenTuDoc("Description paragraph for the link")),
                GenTuEnumField(
                    "ListItemBody",
                    GenTuDoc("Statement list or inner content of the list item body"),
                ),
                GenTuEnumField("ListItemDesc",
                               GenTuDoc("Description part of the list item")),
                GenTuEnumField("DocBody", GenTuDoc("Toplevel document")),
            ],
        ),
        #tag Org spec name
        GenTuEnum(
            t("OrgSpecName"),
            GenTuDoc(""),
            [
                GenTuEnumField("Unnamed", GenTuDoc("")),
                GenTuEnumField("Result", GenTuDoc("")),
                GenTuEnumField("Year", GenTuDoc("")),
                GenTuEnumField("Day", GenTuDoc("")),
                GenTuEnumField("Clock", GenTuDoc("")),
                GenTuEnumField("Repeater", GenTuDoc("")),
                GenTuEnumField("Link", GenTuDoc("")),
                GenTuEnumField("Tags", GenTuDoc("")),
                GenTuEnumField("Tag", GenTuDoc("")),
                GenTuEnumField("State", GenTuDoc("")),
                GenTuEnumField("Protocol", GenTuDoc("")),
                GenTuEnumField("Desc", GenTuDoc("")),
                GenTuEnumField("Times", GenTuDoc("")),
                GenTuEnumField("Drawer", GenTuDoc("")),
                GenTuEnumField("Args", GenTuDoc("")),
                GenTuEnumField("Name", GenTuDoc("")),
                GenTuEnumField("Definition", GenTuDoc("")),
                GenTuEnumField("Body", GenTuDoc("")),
                GenTuEnumField("HeaderArgs", GenTuDoc("")),
                GenTuEnumField("File", GenTuDoc("")),
                GenTuEnumField("Kind", GenTuDoc("")),
                GenTuEnumField("Lang", GenTuDoc("")),
                GenTuEnumField("Prefix", GenTuDoc("")),
                GenTuEnumField("Text", GenTuDoc("")),
                GenTuEnumField("Todo", GenTuDoc("")),
                GenTuEnumField("Urgency", GenTuDoc("")),
                GenTuEnumField("Title", GenTuDoc("")),
                GenTuEnumField("Completion", GenTuDoc("")),
                GenTuEnumField("Head", GenTuDoc("")),
                GenTuEnumField("Subnodes", GenTuDoc("")),
                GenTuEnumField("Properties", GenTuDoc("")),
                GenTuEnumField("Logbook", GenTuDoc("")),
                GenTuEnumField("Description", GenTuDoc("")),
                GenTuEnumField("Logs", GenTuDoc("")),
                GenTuEnumField("Newstate", GenTuDoc("")),
                GenTuEnumField("Oldstate", GenTuDoc("")),
                GenTuEnumField("Time", GenTuDoc("")),
                GenTuEnumField("From", GenTuDoc("")),
                GenTuEnumField("EndArgs", GenTuDoc("")),
                GenTuEnumField("Flags", GenTuDoc("")),
                GenTuEnumField("Value", GenTuDoc("")),
                GenTuEnumField("Assoc", GenTuDoc("")),
                GenTuEnumField("Main", GenTuDoc("")),
                GenTuEnumField("Hash", GenTuDoc("")),
                GenTuEnumField("Bullet", GenTuDoc("")),
                GenTuEnumField("Counter", GenTuDoc("")),
                GenTuEnumField("Checkbox", GenTuDoc("")),
                GenTuEnumField("Header", GenTuDoc("")),
                GenTuEnumField("To", GenTuDoc("")),
                GenTuEnumField("Diff", GenTuDoc("")),
                GenTuEnumField("Property", GenTuDoc("")),
                GenTuEnumField("Subname", GenTuDoc("")),
                GenTuEnumField("Values", GenTuDoc("")),
                GenTuEnumField("Cells", GenTuDoc("")),
                GenTuEnumField("Rows", GenTuDoc("")),
                GenTuEnumField("Lines", GenTuDoc("")),
                GenTuEnumField("Chunks", GenTuDoc("")),
                GenTuEnumField("InheritanceMode", GenTuDoc("")),
                GenTuEnumField("MainSetRule", GenTuDoc("")),
                GenTuEnumField("SubSetRule", GenTuDoc("")),
            ],
        ),
        GenTuEnum(
            t("OrgNodeKind"),
            GenTuDoc(""),
            [
                GenTuEnumField("None",
                               GenTuDoc("Default valye for node - invalid state")),
                GenTuEnumField(
                    "Document",
                    GenTuDoc(
                        "Toplevel part of the ast, not created by parser, and only used in `semorg` stage"
                    ),
                ),
                GenTuEnumField("UserNode",
                               GenTuDoc("User-defined node [[code:OrgUserNode]]")),
                GenTuEnumField(
                    "Empty",
                    GenTuDoc("Empty node - valid state that does not contain any value")),
                GenTuEnumField(
                    "Error",
                    GenTuDoc(
                        "Failed node parse",
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
   """,
                    ),
                ),
                GenTuEnumField(
                    "ErrorTerminator",
                    GenTuDoc("Terminator node for failure in nested structure parsing"),
                ),
                GenTuEnumField("ErrorToken", GenTuDoc("Single invalid token")),
                GenTuEnumField("InlineStmtList", GenTuDoc("")),
                GenTuEnumField(
                    "StmtList",
                    GenTuDoc(
                        "List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together."
                    ),
                ),
                GenTuEnumField(
                    "AssocStmtList",
                    GenTuDoc(
                        "Associated list of statements - AST elements like commands and links are grouped together if placed on adjacent lines"
                    ),
                ),
                GenTuEnumField("Subtree", GenTuDoc("Section subtree")),
                GenTuEnumField("SubtreeTimes",
                               GenTuDoc("Time? associated with subtree entry")),
                GenTuEnumField("SubtreeStars", GenTuDoc("")),
                GenTuEnumField(
                    "Completion",
                    GenTuDoc(
                        "Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio."
                    ),
                ),
                GenTuEnumField("Checkbox",
                               GenTuDoc("Single checkbox item like `[X]` or `[-]`")),
                GenTuEnumField("List", GenTuDoc("")),
                GenTuEnumField("Bullet", GenTuDoc("List item prefix")),
                GenTuEnumField("ListItem", GenTuDoc("")),
                GenTuEnumField(
                    "ListTag",
                    GenTuDoc(
                        "Auxilliary wrapper for the paragraph placed at the start of the description list."
                    ),
                ),
                GenTuEnumField("Counter", GenTuDoc("")),
                GenTuEnumField(
                    "Comment",
                    GenTuDoc(
                        "Inline or trailling comment. Can be used addition to `#+comment:` line or `#+begin-comment` section. Nested comment syntax is allowed (`#[ level1 #[ level2 ]# ]#`), but only outermost one is represented as separate AST node, everything else is a `.text`"
                    ),
                ),
                GenTuEnumField(
                    "RawText",
                    GenTuDoc(
                        "Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers "
                    ),
                ),
                GenTuEnumField(
                    "Unparsed",
                    GenTuDoc(
                        "Part of the org-mode document that is yet to be parsed. This node should not be created manually, it is only used for handling mutually recursive DSLs such as tables, which might include lists, which in turn might contain more tables in different bullet points."
                    ),
                ),
                GenTuEnumField(
                    "Command",
                    GenTuDoc(
                        "Undefined single-line command -- most likely custom user-provided oe"
                    ),
                ),
                GenTuEnumField("CommandArguments",
                               GenTuDoc("Arguments for the command block")),
                GenTuEnumField("CommandTitle",
                               GenTuDoc("`#+title:` - full document title")),
                GenTuEnumField("CommandAuthor", GenTuDoc("`#+author:` Document author")),
                GenTuEnumField("CommandCreator",
                               GenTuDoc("`#+creator:` Document creator")),
                GenTuEnumField(
                    "CommandInclude",
                    GenTuDoc(
                        "`#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk."
                    ),
                ),
                GenTuEnumField("CommandLanguage", GenTuDoc("`#+language:`")),
                GenTuEnumField("CommandAttrHtml", GenTuDoc("`#+attr_html:`")),
                GenTuEnumField("CommandName",
                               GenTuDoc("`#+name:` - name of the associated entry")),
                GenTuEnumField(
                    "CommandHeader",
                    GenTuDoc(
                        "`#+header:` - extended list of parameters passed to associated block"
                    ),
                ),
                GenTuEnumField(
                    "CommandOptions",
                    GenTuDoc("`#+options:` - document-wide formatting options")),
                GenTuEnumField("CommandTblfm", GenTuDoc("")),
                GenTuEnumField(
                    "CommandBackendOptions",
                    GenTuDoc(
                        "Backend-specific configuration options like `#+latex_header` `#+latex_class` etc."
                    ),
                ),
                GenTuEnumField("AttrImg", GenTuDoc("")),
                GenTuEnumField("CommandCaption", GenTuDoc("`#+caption:` command")),
                GenTuEnumField("File", GenTuDoc("")),
                GenTuEnumField("BlockExport", GenTuDoc("")),
                GenTuEnumField("InlineExport", GenTuDoc("")),
                GenTuEnumField(
                    "MultilineCommand",
                    GenTuDoc(
                        "Multiline command such as code block, latex equation, large block of passthrough code. Some built-in org-mode commands do not requires `#+begin` prefix, (such as `#+quote` or `#+example`) are represented by this type of block as well."
                    ),
                ),
                GenTuEnumField("Result", GenTuDoc("Command evaluation result")),
                GenTuEnumField(
                    "Ident",
                    GenTuDoc(
                        "regular identifier - `alnum + [-_]` characters for punctuation. Identifiers are compared and parsed in style-insensetive manner, meaning `CODE_BLOCK`, `code-block` and `codeblock` are identical."
                    ),
                ),
                GenTuEnumField("BareIdent",
                               GenTuDoc("Bare identifier - any characters are allowed")),
                GenTuEnumField(
                    "AdmonitionTag",
                    GenTuDoc(
                        "Big ident used in conjunction with colon at the start of paragraph is considered an admonition tag: `NOTE: Text`, `WARNING: text` etc."
                    ),
                ),
                GenTuEnumField(
                    "BigIdent",
                    GenTuDoc("full-uppsercase identifier such as `MUST` or `TODO`")),
                GenTuEnumField(
                    "VerbatimMultilineBlock",
                    GenTuDoc(
                        "Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks."
                    ),
                ),
                GenTuEnumField("CodeLine", GenTuDoc("Single line of source code")),
                GenTuEnumField("CodeText", GenTuDoc("Block of source code text")),
                GenTuEnumField("CodeTangle",
                               GenTuDoc("Single tangle target in the code block")),
                GenTuEnumField("CodeCallout",
                               GenTuDoc("`(refs:` callout in the source code")),
                GenTuEnumField("QuoteBlock", GenTuDoc("`#+quote:` block in code")),
                GenTuEnumField("AdmonitionBlock", GenTuDoc("")),
                GenTuEnumField("CenterBlock", GenTuDoc("'")),
                GenTuEnumField("Example", GenTuDoc("Verbatim example text block")),
                GenTuEnumField(
                    "SrcCode",
                    GenTuDoc("Block of source code - can be multiline, single-line and")),
                GenTuEnumField(
                    "SrcInlineCode",
                    GenTuDoc(
                        "inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc."
                    ),
                ),
                GenTuEnumField(
                    "CallCode",
                    GenTuDoc(
                        "Call to named source code block. Inline, multiline, or single-line."
                    ),
                ),
                GenTuEnumField(
                    "PassCode",
                    GenTuDoc(
                        "Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively"
                    ),
                ),
                GenTuEnumField("CmdArguments", GenTuDoc("Command arguments")),
                GenTuEnumField(
                    "CmdFlag",
                    GenTuDoc(
                        "Flag for source code block. For example `-n`, which is used to to make source code block export with lines"
                    ),
                ),
                GenTuEnumField("CmdKey", GenTuDoc("")),
                GenTuEnumField("CmdValue", GenTuDoc("")),
                GenTuEnumField("CmdNamedValue",
                               GenTuDoc("Key-value pair for source code block call.")),
                GenTuEnumField(
                    "UrgencyStatus",
                    GenTuDoc(
                        "Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`."
                    ),
                ),
                GenTuEnumField("TextSeparator", GenTuDoc("Long horizontal line `----`")),
                GenTuEnumField(
                    "Paragraph",
                    GenTuDoc(
                        "Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph"
                    ),
                ),
                GenTuEnumField(
                    "AnnotatedParagraph",
                    GenTuDoc(
                        "Annotated paragraph -- a wrapper around a regular paragraph kind with added admonition, footnote, list tag prefix and similar types. `[fn:ID] Some Text` is an annotated paragraph, just like `NOTE: Text` or `- Prefix :: Body` (in this case list header is an annotated paragraph)"
                    ),
                ),
                GenTuEnumField(
                    "Bold",
                    GenTuDoc(
                        """Region of text with formatting, which contains standalone words -
     can itself contain subnodes, which allows to represent nested
     formatting regions, such as `*bold /italic/*` text. Particular type
     of identifier is stored in string form in `str` field for `OrgNode`
     -- bold is represented as `\"*\"`, italic as `/` and so on. In case
     of explicit open/close pairs only opening one is stored.

     NOTE: when structured sentences are enabled, regular punctuation
     elements like `some text (notes)` are also represented as `Word,
     Word, Markup(str: \"(\", [Word])` - e.g. structure is not fully flat."""),
                ),
                GenTuEnumField("Italic", GenTuDoc("")),
                GenTuEnumField("Verbatim", GenTuDoc("")),
                GenTuEnumField("Backtick", GenTuDoc("")),
                GenTuEnumField("Underline", GenTuDoc("")),
                GenTuEnumField("Strike", GenTuDoc("")),
                GenTuEnumField("Quote", GenTuDoc("")),
                GenTuEnumField("Angle", GenTuDoc("")),
                GenTuEnumField("Monospace", GenTuDoc("")),
                GenTuEnumField("Par", GenTuDoc("")),
                GenTuEnumField(
                    "InlineMath",
                    GenTuDoc(
                        "Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\\(paren-wrapped\\)` inline text."
                    ),
                ),
                GenTuEnumField(
                    "DisplayMath",
                    GenTuDoc(
                        "Inline display latex math from `$$double-dollar$$` or `\\[bracket-wrapped\\]` code."
                    ),
                ),
                GenTuEnumField("Space",
                               GenTuDoc("Space or tab character in regular text")),
                GenTuEnumField("Punctuation", GenTuDoc("")),
                GenTuEnumField("Colon", GenTuDoc("")),
                GenTuEnumField(
                    "Word",
                    GenTuDoc(
                        "Regular word - technically not different from `orgIdent`, but defined separately to disiguish between places where special syntax is required and free-form text."
                    ),
                ),
                GenTuEnumField("Escaped",
                               GenTuDoc("Escaped formatting character in the text")),
                GenTuEnumField("Newline", GenTuDoc("")),
                GenTuEnumField("SkipNewline", GenTuDoc("")),
                GenTuEnumField("SkipSpace", GenTuDoc("")),
                GenTuEnumField("SkipAny", GenTuDoc("")),
                GenTuEnumField("RawLink",
                               GenTuDoc("Raw unwrapped link that was pasted in text")),
                GenTuEnumField(
                    "Link",
                    GenTuDoc(
                        """External or internal link. Consists of one or two elements - target
     (url, file location etc.) and description (`orgParagraph` of text).
     Description might be empty, and represented as empty node in this
     case. For external links particular formatting of the address is
     not handled by parser and instead contains raw string from input
     text."""),
                ),
                GenTuEnumField(
                    "Macro",
                    GenTuDoc(
                        """Org-mode macro replacement - during export each macro is expanded
     and evaluated according to it's environment. Body of the macro is
     not parsed fully during org-mode evaluation, but is checked for
     correct parenthesis balance (as macro might contain elisp code)"""),
                ),
                GenTuEnumField(
                    "BackendRaw",
                    GenTuDoc(
                        """Raw content to be passed to a particular backend. This is the most
     compact way of quoting export strings, after `#+<backend>:
     <single-backend-line>` and `#+begin-export <backend>`
     `<multiple-lines>`."""),
                ),
                GenTuEnumField(
                    "Symbol",
                    GenTuDoc(
                        "Special symbol that should be exported differently to various backends - greek letters (`\alpha`), mathematical notations and so on."
                    ),
                ),
                GenTuEnumField(
                    "TimeAssoc",
                    GenTuDoc("Time association pair for the subtree deadlines.")),
                GenTuEnumField("StaticActiveTime", GenTuDoc("")),
                GenTuEnumField("StaticInactiveTime", GenTuDoc("")),
                GenTuEnumField("DynamicActiveTime", GenTuDoc("")),
                GenTuEnumField(
                    "DynamicInactiveTime",
                    GenTuDoc(
                        "Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later"
                    ),
                ),
                GenTuEnumField(
                    "TimeRange",
                    GenTuDoc("Date and time range format - two `orgDateTime` entries")),
                GenTuEnumField(
                    "SimpleTime",
                    GenTuDoc(
                        "Result of the time range evaluation or trailing annotation a subtree"
                    ),
                ),
                GenTuEnumField("Details", GenTuDoc("`#+begin_details`  section")),
                GenTuEnumField("Summary", GenTuDoc("`#+begin_summary` section")),
                GenTuEnumField(
                    "Table",
                    GenTuDoc(
                        """Org-mode table. Tables can be writtein in different formats, but in
   the end they are all represented using single ast type. NOTE: it is
   not guaranteed that all subnodes for table are exactly
   `orgTableRow` - sometimes additional property metadata might be
   used, making AST like `Table[AssocStmtList[Command[_],
   TableRow[_]]]` possible"""),
                ),
                GenTuEnumField("TableRow", GenTuDoc("Horizontal table row")),
                GenTuEnumField(
                    "TableCell",
                    GenTuDoc(
                        "Single cell in row. Might contain anyting, including other tables, simple text paragraph etc."
                    ),
                ),
                GenTuEnumField(
                    "InlineFootnote",
                    GenTuDoc(
                        "Inline footnote with text placed directly in the node body."),
                ),
                GenTuEnumField(
                    "Footnote",
                    GenTuDoc(
                        "Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node."
                    ),
                ),
                GenTuEnumField(
                    "Horizontal",
                    GenTuDoc(
                        "Horizotal rule. Rule body might contain other subnodes, to represnt `---- some text ----` kind of formatting."
                    ),
                ),
                GenTuEnumField("Filetags", GenTuDoc("`#+filetags:` line command")),
                GenTuEnumField(
                    "OrgTag",
                    GenTuDoc(
                        """Original format of org-mode tags in form of `:tagname:`. Might
   contain one or mode identifgiers, but does not provide support for
   nesting - `:tag1:tag2:`. Can only be placed within restricted set
   of places such as subtree headings and has separate place in AST
   when allowed (`orgSubtree` always has subnode `№4` with either
   `orgEmpty` or `orgOrgTag`)"""),
                ),
                GenTuEnumField(
                    "HashTag",
                    GenTuDoc("""More commonly used `#hashtag` format, with some additional
   extension. Can be placed anywere in the document (including section
   headers), but does not have separate place in AST (e.g. considered
   regular part of the text)"""),
                ),
                GenTuEnumField("MetaSymbol",
                               GenTuDoc("`\\sym{}` with explicit arguments")),
                GenTuEnumField("AtMention", GenTuDoc("`@user`")),
                GenTuEnumField(
                    "BracTag",
                    GenTuDoc(
                        "Custom extension to org-mode. Similarly to `BigIdent` used to have something like informal keywords `MUST`, `OPTIONAL`, but instead aimed /specifically/ at commit message headers - `[FEATURE]`, `[FIX]` and so on."
                    ),
                ),
                GenTuEnumField(
                    "Drawer",
                    GenTuDoc(
                        "Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`"
                    ),
                ),
                GenTuEnumField("LatexClass", GenTuDoc("")),
                GenTuEnumField("LatexHeader", GenTuDoc("")),
                GenTuEnumField("LatexCompiler", GenTuDoc("")),
                GenTuEnumField("LatexClassOptions", GenTuDoc("")),
                GenTuEnumField("HtmlHead", GenTuDoc("")),
                GenTuEnumField(
                    "Columns",
                    GenTuDoc(
                        "`#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis."
                    ),
                ),
                GenTuEnumField("CmdPropertyArgs", GenTuDoc( "`#+property:` command")),
                GenTuEnumField("CmdPropertyText", GenTuDoc( "`#+property:` command")),
                GenTuEnumField("CmdPropertyRaw", GenTuDoc( "`#+property:` command")),
                GenTuEnumField("PropertyList", GenTuDoc("")),
                GenTuEnumField("Property", GenTuDoc( "`:property:` drawer")),
                GenTuEnumField(
                    "Placeholder",
                    GenTuDoc(
                        "Placeholder entry in text, usually writte like `<text to replace>`"
                    ),
                ),
                GenTuEnumField("SubtreeDescription", GenTuDoc("`:description:` entry")),
                GenTuEnumField("SubtreeUrgency", GenTuDoc("")),
                GenTuEnumField("Logbook",
                               GenTuDoc("`:logbook:` entry storing note information")),
                GenTuEnumField("LogbookEntry", GenTuDoc("")),
                GenTuEnumField(
                    "LogbookStateChange",
                    GenTuDoc("Annotation about change in the subtree todo state"),
                ),
                GenTuEnumField("LogbookNote",
                               GenTuDoc("Timestamped log note on the subtree")),
                GenTuEnumField("LogbookClock", GenTuDoc("`CLOCK` entry in the subtree")),
                GenTuEnumField("LogbookRefile",
                               GenTuDoc("`Refile` entry in the subtree logbook drawer")),
                GenTuEnumField("LogbookPriority",
                               GenTuDoc("Change in the subtree priority")),
                GenTuEnumField("LogbookPriorityChangeAction",
                               GenTuDoc("Action to change subtree")),
                GenTuEnumField("LogbookReschedule", GenTuDoc("")),
                GenTuEnumField("LogbookTagChange", GenTuDoc("")),
                GenTuEnumField("LogbookTagChangeAction", GenTuDoc("")),
                GenTuEnumField("RadioTarget", GenTuDoc("`<<<RADIO>>>`")),
                GenTuEnumField("Target", GenTuDoc("`<<TARGET>>`")),
            ],
        ),
        GenTuEnum(
            t("OrgBigIdentKind"),
            GenTuDoc(""),
            [
                GenTuEnumField("None", GenTuDoc("")),
                GenTuEnumField(
                    "Must",
                    GenTuDoc(
                        'MUST This word, or the terms "REQUIRED" or "SHALL", mean that the definition is an absolute requirement of the specification.'
                    ),
                ),
                GenTuEnumField(
                    "MustNot",
                    GenTuDoc(
                        'MUST NOT This phrase, or the phrase "SHALL NOT", mean that the definition is an absolute prohibition of the specification.'
                    ),
                ),
                GenTuEnumField(
                    "Should",
                    GenTuDoc(
                        """SHOULD This word, or the adjective \"RECOMMENDED\", mean that there
   may exist valid reasons in particular circumstances to ignore a
   particular item, but the full implications must be understood and
   carefully weighed before choosing a different course."""),
                ),
                GenTuEnumField(
                    "ShouldNot",
                    GenTuDoc(
                        """SHOULD NOT This phrase, or the phrase \"NOT RECOMMENDED\" mean that
   there may exist valid reasons in particular circumstances when the
   particular behavior is acceptable or even useful, but the full
   implications should be understood and the case carefully weighed
   before implementing any behavior described with this label."""),
                ),
                GenTuEnumField("Required", GenTuDoc("")),
                GenTuEnumField(
                    "Optional",
                    GenTuDoc(
                        """MAY This word, or the adjective \"OPTIONAL\", mean that an item is
   truly optional. One vendor may choose to include the item because a
   particular marketplace requires it or because the vendor feels that
   it enhances the product while another vendor may omit the same
   item. An implementation which does not include a particular option
   MUST be prepared to interoperate with another implementation which
   does include the option, though perhaps with reduced functionality.
   In the same vein an implementation which does include a particular
   option MUST be prepared to interoperate with another implementation
   which does not include the option (except, of course, for the
   feature the option provides.)"""),
                ),
                GenTuEnumField("ReallyShouldNot", GenTuDoc("")),
                GenTuEnumField("OughtTo", GenTuDoc("")),
                GenTuEnumField("WouldProbably", GenTuDoc("")),
                GenTuEnumField("MayWishTo", GenTuDoc("")),
                GenTuEnumField("Could", GenTuDoc("")),
                GenTuEnumField("Might", GenTuDoc("")),
                GenTuEnumField("Possible", GenTuDoc("")),
                GenTuEnumField("Todo", GenTuDoc("")),
                GenTuEnumField("Idea", GenTuDoc("")),
                GenTuEnumField("Error", GenTuDoc("")),
                GenTuEnumField("Fixme", GenTuDoc("")),
                GenTuEnumField("Doc", GenTuDoc("")),
                GenTuEnumField("Refactor", GenTuDoc("")),
                GenTuEnumField("Review", GenTuDoc("")),
                GenTuEnumField("Hack", GenTuDoc("")),
                GenTuEnumField("Implement", GenTuDoc("")),
                GenTuEnumField("Example", GenTuDoc("")),
                GenTuEnumField("Question", GenTuDoc("")),
                GenTuEnumField("Assume", GenTuDoc("")),
                GenTuEnumField("Internal", GenTuDoc("")),
                GenTuEnumField("Design", GenTuDoc("")),
                GenTuEnumField("Why", GenTuDoc("")),
                GenTuEnumField("Wip", GenTuDoc("")),
                GenTuEnumField("Fix", GenTuDoc("")),
                GenTuEnumField("Clean", GenTuDoc("")),
                GenTuEnumField("Feature", GenTuDoc("")),
                GenTuEnumField("Style", GenTuDoc("")),
                GenTuEnumField("Repo", GenTuDoc("")),
                GenTuEnumField("Skip", GenTuDoc("")),
                GenTuEnumField("Break", GenTuDoc("")),
                GenTuEnumField("Poc", GenTuDoc("")),
                GenTuEnumField("Next", GenTuDoc("")),
                GenTuEnumField("Later", GenTuDoc("")),
                GenTuEnumField("Postponed", GenTuDoc("")),
                GenTuEnumField("Stalled", GenTuDoc("")),
                GenTuEnumField("Done", GenTuDoc("")),
                GenTuEnumField("Partially", GenTuDoc("")),
                GenTuEnumField("Cancelled", GenTuDoc("")),
                GenTuEnumField("Failed", GenTuDoc("")),
                GenTuEnumField("Note", GenTuDoc("")),
                GenTuEnumField("Tip", GenTuDoc("")),
                GenTuEnumField("Important", GenTuDoc("")),
                GenTuEnumField("Caution", GenTuDoc("")),
                GenTuEnumField("Warning", GenTuDoc("")),
                GenTuEnumField("UserCodeComment",
                               GenTuDoc("User-defined comment message")),
                GenTuEnumField("UserCommitMsg",
                               GenTuDoc("User-defined commit message ident")),
                GenTuEnumField("UserTaskState", GenTuDoc("User-defined task state")),
                GenTuEnumField("UserAdmonition",
                               GenTuDoc("User-defined admonition label")),
                GenTuEnumField(
                    "Other",
                    GenTuDoc("User-defined big-idents, not included in default set.")),
                # ;; It is not hard to support
                # ;; https://en.wikipedia.org/wiki/Structured_English keywords. Maybe I
                # ;; will merge it with haxdoc somehow, maybe not, for not I just placed
                # ;; them here as a reminder to myself. My current idea is to overlay
                # ;; semi-structured explanation in the documenation with actual code.
                # ;; Structured keywords can be used as an anchor points (e.g. `IF` maps
                # ;; to real condition, `THEN` to the body and so on).
                GenTuEnumField("StructIf", GenTuDoc("")),
                GenTuEnumField("StructAnd", GenTuDoc("")),
                GenTuEnumField("StructOr", GenTuDoc("")),
                GenTuEnumField("StructNot", GenTuDoc("")),
                GenTuEnumField("StructGet", GenTuDoc("")),
                GenTuEnumField("StructSet", GenTuDoc("")),
                GenTuEnumField("StructThen", GenTuDoc("")),
                GenTuEnumField("StructElse", GenTuDoc("")),
                GenTuEnumField("StructWhile", GenTuDoc("")),
            ],
        ),
        get_org_token_kind(),
    ]
