from dataclasses import field, dataclass, replace
from copy import deepcopy
from beartype.typing import *
from enum import Enum

# Now you should be able to import your C++ library
from py_codegen.astbuilder_cpp import *
from py_codegen.gen_tu_cpp import *


@beartype
def org_doc(text: Union[str, GenTuDoc] = GenTuDoc(""), full: str = "") -> GenTuDoc:
    return GenTuDoc(text, full) if isinstance(text, str) else text


AnyDoc = Union[str, GenTuDoc]


@beartype
def efield(name: str,
           doc: AnyDoc = GenTuDoc(""),
           value: Optional[int] = None) -> GenTuEnumField:
    return GenTuEnumField(name=name, doc=org_doc(doc), value=value)


#region cxx-types


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
def t_space(name: str | QualType, Spaces: List[str]) -> QualType:
    Spaces = [QualType(name=S, isNamespace=True) for S in Spaces]
    if isinstance(name, QualType):
        return name.model_copy(update=dict(Spaces=Spaces))
    else:
        return QualType(name=name, Spaces=Spaces)


def t_org(name: str, extraSpaces: List[QualType] = []) -> QualType:
    return QualType(name=name, Spaces=[n_sem()] + extraSpaces)


def t_nest(name: Union[str, QualType], Spaces: List[str]) -> QualType:
    return t_space(name, ["sem"] + Spaces)


def k_args(obj: Any, **kwargs) -> Any:
    for key, value in kwargs.items():
        obj.__setattr__(key, value)

    return obj


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


#endregion


@beartype
def org_struct(
    typ: QualType,
    doc: AnyDoc = GenTuDoc(""),
    fields: List[GenTuField] = [],
    nested: List[GenTuEntry] = [],
) -> GenTuStruct:
    return GenTuStruct(
        name=typ,
        doc=org_doc(doc),
        fields=fields,
        nested=nested,
    )


#region cxx-fields


@beartype
def id_field(id: str, name: str, doc: AnyDoc = GenTuDoc("")) -> GenTuField:
    return GenTuField(
        t_id(id),
        name,
        org_doc(doc),
        value=f"sem::SemId<sem::{id}>::Nil()",
    )


@beartype
def vec_field(typ: QualType, name: str, doc: AnyDoc = GenTuDoc("")):
    return GenTuField(t_vec(typ), name, org_doc(doc), value="{}")


@beartype
def opt_field(typ: QualType, name: str, doc: AnyDoc = GenTuDoc("")):
    return GenTuField(
        type=t_opt(typ),
        name=name,
        doc=org_doc(doc),
        value="std::nullopt",
    )


@beartype
def org_field(
        typ: QualType,
        name: str,
        doc: AnyDoc = GenTuDoc(""),
        value: Optional[Union[BlockId, str]] = None,
):
    return GenTuField(type=typ, name=name, doc=org_doc(doc), value=value)


@beartype
def arg_ident(
        typ: QualType,
        name: str,
        doc: GenTuDoc = GenTuDoc(""),
        value: Optional[str] = None,
) -> GenTuIdent:
    return GenTuIdent(type=t_cr(typ), name=name, value=value)


@beartype
def opt_ident(typ: QualType,
              name: str,
              doc: GenTuDoc = GenTuDoc(""),
              value: str = "std::nullopt") -> GenTuIdent:
    return GenTuIdent(type=t_cr(t_opt(typ)), name=name, value=value)


@beartype
def bool_field(name: str,
               doc: AnyDoc = GenTuDoc(""),
               default: str = "false") -> GenTuField:
    return GenTuField(t("bool"), name, doc=org_doc(doc), value=default)


@beartype
def str_field(name: str, doc: AnyDoc = GenTuDoc(""), default: str = '""') -> GenTuField:
    return org_field(t_str(), name, doc, default)


#endregion


def d_org(name: str, *args, **kwargs) -> GenTuStruct:
    res = GenTuStruct(QualType(name=name), *args, **kwargs)
    res.__setattr__("isOrgType", True)
    kind: str = res.name.name
    base = res.bases[0]
    res.nested = [
        GenTuPass(f"using {base.name}::{base.name};"),
        GenTuPass(f"virtual ~{name}() = default;")
    ] + res.nested
    if res.concreteKind:
        res.fields.insert(
            0,
            GenTuField(
                t_osk(),
                "staticKind",
                GenTuDoc(""),
                isConst=True,
                isStatic=True,
                isExposedForWrap=False,
            ),
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
                isExposedForWrap=False,
            ),
        )

    return res


@beartype
def d_simple_enum(name: str, doc: GenTuDoc, *args):
    return GenTuEnum(
        t(name),
        doc,
        fields=[
            GenTuEnumField(arg, GenTuDoc("")) if isinstance(arg, str) else arg
            for arg in args
        ],
    )


def get_subtree_property_types():
    return [
        GenTuStruct(t("Nonblocking"),
                    GenTuDoc(""),
                    fields=[GenTuField(t_bool(), "isBlocking", GenTuDoc(""))],
                    nested=[GenTuPass("Nonblocking() {}")]),
        GenTuStruct(t("Trigger"), GenTuDoc(""), nested=[GenTuPass("Trigger() {}")]),
        GenTuStruct(t("Origin"),
                    GenTuDoc(""),
                    fields=[id_field("Paragraph", "text", GenTuDoc(""))],
                    nested=[GenTuPass("Origin() {}")]),
        GenTuStruct(t("ExportLatexClass"),
                    GenTuDoc(""),
                    fields=[GenTuField(t_str(), "latexClass", GenTuDoc(""))],
                    nested=[GenTuPass("ExportLatexClass() {}")]),
        GenTuStruct(t("ExportLatexClassOptions"),
                    GenTuDoc(""),
                    fields=[GenTuField(t_vec(t_str()), "options", GenTuDoc(""))],
                    nested=[GenTuPass("ExportLatexClassOptions() {}")]),
        GenTuStruct(t("ExportLatexHeader"),
                    GenTuDoc(""),
                    fields=[GenTuField(t_str(), "header", GenTuDoc(""))],
                    nested=[GenTuPass("ExportLatexHeader() {}")]),
        GenTuStruct(t("ExportLatexCompiler"),
                    GenTuDoc(""),
                    fields=[GenTuField(t_str(), "compiler", GenTuDoc(""))],
                    nested=[GenTuPass("ExportLatexCompiler() {}")]),
        GenTuStruct(t("Ordered"),
                    GenTuDoc(""),
                    fields=[GenTuField(t_bool(), "isOrdered", GenTuDoc(""))],
                    nested=[GenTuPass("Ordered() {}")]),
        GenTuStruct(t("Effort"),
                    GenTuDoc(""),
                    fields=[
                        GenTuField(t_int(), "hours", GenTuDoc(""), value="0"),
                        GenTuField(t_int(), "minutes", GenTuDoc(""), value="0"),
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
                GenTuField(t_nest("Level", ["Subtree", "Property", "Visibility"]),
                           "level", GenTuDoc(""))
            ],
        ),
        GenTuStruct(
            t("ExportOptions"),
            GenTuDoc(""),
            nested=[GenTuPass("ExportOptions() {}")],
            fields=[
                GenTuField(t_str(), "backend", GenTuDoc("")),
                GenTuField(t_map(t_str(), t_str()), "values", GenTuDoc("")),
            ],
        ),
        GenTuStruct(
            t("Blocker"),
            GenTuDoc(""),
            nested=[GenTuPass("Blocker() {}")],
            fields=[GenTuField(t_vec(t_str()), "blockers", GenTuDoc(""))],
        ),
        GenTuStruct(t("Unnumbered"), GenTuDoc(""), nested=[GenTuPass("Unnumbered() {}")]),
        GenTuStruct(
            t("Created"),
            GenTuDoc(""),
            nested=[GenTuPass("Created() {}")],
            fields=[id_field("Time", "time", GenTuDoc(""))],
        ),
        GenTuStruct(
            t("CustomArgs"),
            GenTuDoc("Custop property with unparsed arguments"),
            nested=[GenTuPass("CustomArgs() {}")],
            fields=[
                str_field("name", GenTuDoc("Original name of the property")),
                opt_field(t_str(), "sub", GenTuDoc("Property target specialization")),
                id_field("CmdArguments", "parameters", GenTuDoc("Property parameters")),
            ],
        ),
        GenTuStruct(
            t("CustomRaw"),
            GenTuDoc("Custop property with unparsed arguments"),
            nested=[GenTuPass("CustomRaw() {}")],
            fields=[
                str_field("name", GenTuDoc("Original name of the property")),
                str_field("value", GenTuDoc("Property value")),
            ],
        )
    ]


#region org-types


def get_sem_misc():
    return [
        d_org(
            "CmdArgument",
            GenTuDoc("Single key-value (or positional)"),
            bases=[t_org("Org")],
            fields=[
                opt_field(t_str(), "key", GenTuDoc("Key")),
                opt_field(
                    t_str(), "varname",
                    GenTuDoc(
                        "When used in the `:var` assignment, this stores variable name")),
                GenTuField(t_str(), "value", GenTuDoc("Value")),
            ],
            methods=[
                GenTuFunction(
                    t_opt(t_int()),
                    "getInt",
                    GenTuDoc("Parse argument as integer value"),
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_bool()),
                    "getBool",
                    GenTuDoc("Get argument as bool"),
                    isConst=True,
                ),
                GenTuFunction(
                    t_str(),
                    "getString",
                    GenTuDoc("Get original string"),
                    isConst=True,
                ),
            ],
        ),
        d_org(
            "CmdArgumentList",
            GenTuDoc("Data type to wrap list of identical command arguments"),
            bases=[t_org("Org")],
            fields=[
                vec_field(
                    t_id("CmdArgument"),
                    "args",
                    GenTuDoc("List of arguments"),
                ),
            ],
        ),
        d_org(
            "CmdArguments",
            GenTuDoc("Additional arguments for command blocks"),
            bases=[t_org("Org")],
            methods=[
                GenTuFunction(
                    t_opt(t_id("CmdArgumentList")),
                    "getArguments",
                    GenTuDoc(""),
                    arguments=[opt_ident(t_str(), "key", GenTuDoc(""))],
                    isConst=True,
                )
            ],
            fields=[
                id_field("CmdArgumentList", "positional",
                         GenTuDoc("Positional arguments with no keys")),
                GenTuField(
                    t_map(t_str(), t_id("CmdArgumentList")),
                    "named",
                    GenTuDoc("Stored key-value mapping"),
                ),
            ],
        ),
    ]


def get_sem_bases():
    return [
        d_org(
            "ErrorItem",
            doc=org_doc(""),
            bases=[t_org("Org")],
            fields=[
                org_field(t_str(), "message"),
                opt_field(
                    t_str(),
                    "function",
                    "Conversion function name where the error was created",
                ),
                opt_field(
                    t_int(),
                    "line",
                    "Line number for the conversion where the error was created",
                ),
            ],
        ),
        d_org(
            "ErrorGroup",
            doc=org_doc("Group of value conversion errors"),
            bases=[t_org("Org")],
            fields=[
                vec_field(t_id("ErrorItem"), "diagnostics"),
                opt_field(
                    t_str(),
                    "function",
                    "Conversion function name where the error was created",
                ),
                opt_field(
                    t_str(),
                    "line",
                    "Line number for the conversion where the error was created",
                ),
            ],
        ),
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
                    t_vec(t_id()),
                    "getAttached",
                    GenTuDoc(
                        "Return attached nodes of a specific kinds or all attached (if kind is nullopt)"
                    ),
                    arguments=[opt_ident(t_str(), "kind", GenTuDoc(""))],
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_id("CmdArgumentList")),
                    "getArguments",
                    GenTuDoc(
                        "Get all named arguments for the command, across all attached properties. "
                        "If kind is nullopt returns all attached arguments for all properties."
                    ),
                    arguments=[opt_ident(t_str(), "kind", GenTuDoc(""))],
                    isConst=True,
                    isVirtual=True,
                ),
                GenTuFunction(
                    t_opt(t_id("CmdArgument")),
                    "getFirstArgument",
                    GenTuDoc(
                        "Get the first parameter for the statement. "
                        "In case there is a longer list of values matching given kind"
                        "different node kinds can implement different priorities "),
                    arguments=[arg_ident(t_str(), "kind")],
                    isConst=True,
                    isVirtual=True,
                ),
            ],
            nested=[
                GenTuPass("Stmt() {}"),
                GenTuPass(
                    "Stmt(CVec<SemId<Org>> attached, CVec<SemId<Org>> subnodes) : Org(subnodes), attached(attached) {}"
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
            "Cmd",
            GenTuDoc("Base class for block or line commands"),
            bases=[t_org("Stmt")],
            concreteKind=False,
            fields=[
                opt_field(
                    t_id("CmdArguments"),
                    "parameters",
                    GenTuDoc("Additional parameters aside from 'exporter',"),
                ),
            ],
            methods=[
                GenTuFunction(
                    t_opt(t_id("CmdArgumentList")),
                    "getArguments",
                    GenTuDoc(
                        "Return all parameters with keys matching name. "
                        "This is an override implementation that accounts for the explicit command parameters if any."
                    ),
                    arguments=[opt_ident(t_str(), "key", GenTuDoc(""))],
                    isConst=True,
                    isVirtual=True,
                    isOverride=True,
                ),
                GenTuFunction(
                    t_opt(t_id("CmdArgument")),
                    "getFirstArgument",
                    GenTuDoc(
                        "Override of the base statement argument get, prioritizing the explicit command parameters"
                    ),
                    arguments=[arg_ident(t_str(), "kind")],
                    isConst=True,
                    isVirtual=True,
                    isOverride=True,
                ),
            ],
        ),
        d_org(
            "Block",
            GenTuDoc("Block command type"),
            bases=[t_org("Cmd")],
            concreteKind=False,
        ),
        d_org(
            "LineCommand",
            GenTuDoc("Line commands"),
            bases=[t_org("Cmd")],
            concreteKind=False,
        ),
        d_org(
            "Attached",
            GenTuDoc("Line command that might get attached to some block element"),
            bases=[t_org("LineCommand")],
            concreteKind=False,
        ),
        d_org(
            "Leaf",
            GenTuDoc("Final node"),
            bases=[t_org("Org")],
            concreteKind=False,
            fields=[
                GenTuField(t_str(), "text", GenTuDoc("Final leaf value"), value='""')
            ],
        ),
    ]


def get_sem_commands():
    return [
        d_org(
            "CmdCaption",
            GenTuDoc("Caption annotation for any subsequent node"),
            bases=[t_org("Attached")],
            fields=[id_field("Paragraph", "text", GenTuDoc("Content description"))],
        ),
        d_org(
            "CmdName",
            GenTuDoc("Name identifier for the statement elements."),
            bases=[t_org("Attached")],
            fields=[
                GenTuField(t_str(), "name", GenTuDoc("")),
            ],
        ),
        d_org(
            "CmdCustomArgs",
            doc=org_doc("Custom line command with list of parsed arguments"),
            bases=[t_org("Cmd")],
            fields=[
                org_field(t_str(), "name"),
                bool_field("isAttached"),
            ],
        ),
        d_org(
            "CmdCustomRaw",
            doc=org_doc("Custom command with raw unparsed string value"),
            bases=[t_org("Stmt")],
            fields=[
                org_field(t_str(), "name"),
                bool_field("isAttached"),
                org_field(t_str(), "text"),
            ],
        ),
        d_org(
            "CmdCustomText",
            doc=org_doc("Custom line command with text paragraph value"),
            bases=[t_org("Stmt")],
            fields=[
                org_field(t_str(), "name"),
                bool_field("isAttached"),
                id_field("Paragraph", "text"),
            ],
        ),
        d_org(
            "CmdResults",
            GenTuDoc(""),
            bases=[t_org("Attached")],
        ),
        d_org(
            "CmdTblfm",
            GenTuDoc("Tblfm command type"),
            bases=[t_org("Cmd")],
        ),
    ]


def get_sem_block():
    return [
        d_org("BlockCenter",
              GenTuDoc("Center nested content in export"),
              bases=[t_org("Block")]),
        d_org(
            "BlockQuote",
            GenTuDoc("Quotation block"),
            bases=[t_org("Block")],
        ),
        d_org(
            "BlockComment",
            GenTuDoc("Comment block"),
            bases=[t_org("Stmt")],
        ),
        d_org(
            "BlockVerse",
            GenTuDoc("Verse quotation block"),
            bases=[t_org("Block")],
        ),
        d_org("BlockExample", GenTuDoc("Example block"), bases=[t_org("Block")]),
        d_org(
            "BlockExport",
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
                    t_nest("Format", ["BlockExport"]),
                    "format",
                    GenTuDoc("Export block type"),
                    value="sem::BlockExport::Format::Inline",
                ),
                GenTuField(t_str(), "exporter", GenTuDoc("Exporter backend name")),
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
            "BlockAdmonition",
            GenTuDoc("Block of text with admonition tag: 'note',', 'warning','"),
            bases=[t_org("Block")],
        ),
        d_org(
            "BlockCode",
            GenTuDoc("Base class for all code blocks"),
            bases=[t_org("Block")],
            nested=[
                GenTuStruct(
                    t("Line"),
                    nested=[
                        GenTuStruct(
                            t("Part"),
                            nested=[
                                GenTuTypeGroup([
                                    GenTuStruct(t("Raw"),
                                                fields=[GenTuField(t_str(), "code")]),
                                    GenTuStruct(t("Callout"),
                                                fields=[GenTuField(t_str(), "name")]),
                                    GenTuStruct(t("Tangle"),
                                                fields=[GenTuField(t_str(), "target")]),
                                ],),
                            ],
                        )
                    ],
                    fields=[
                        vec_field(
                            t_nest("Part", ["BlockCode", "Line"]),
                            "parts",
                            GenTuDoc("parts of the single line"),
                        )
                    ],
                ),
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
                                nested=[GenTuPass("LineStart() {}")],
                            ),
                            GenTuStruct(
                                t("CalloutFormat"),
                                GenTuDoc(""),
                                fields=[
                                    GenTuField(t_str(),
                                               "format",
                                               GenTuDoc(""),
                                               value='""')
                                ],
                                nested=[GenTuPass("CalloutFormat() {}")],
                            ),
                            GenTuStruct(
                                t("RemoveCallout"),
                                GenTuDoc(""),
                                fields=[
                                    GenTuField(t_bool(),
                                               "remove",
                                               GenTuDoc(""),
                                               value="true")
                                ],
                                nested=[GenTuPass("RemoveCallout() {}")],
                            ),
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
                                nested=[GenTuPass("EmphasizeLine() {}")],
                            ),
                            GenTuStruct(
                                t("Dedent"),
                                GenTuDoc(""),
                                fields=[
                                    GenTuField(t_int(), "value", GenTuDoc(""), value="0")
                                ],
                                nested=[GenTuPass("Dedent() {}")],
                            ),
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
                    t_nest("Exports", ["Include", "Export"]),
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
                GenTuStruct(
                    t("EvalResult"),
                    nested=[
                        GenTuTypeGroup([
                            GenTuStruct(
                                t("None"),
                                GenTuDoc("Default value"),
                            ),
                            GenTuStruct(
                                t("OrgValue"),
                                GenTuDoc(
                                    "Source code block evaluated to an org-mode node element"
                                ),
                                fields=[
                                    id_field(
                                        "Org", "value",
                                        GenTuDoc("Parsed value of the evaluation result"))
                                ],
                            ),
                            GenTuStruct(
                                t("File"),
                                GenTuDoc("Output evaluation results to a file"),
                                fields=[
                                    GenTuField(t_str(), "path"),
                                ],
                            ),
                            GenTuStruct(
                                t("Raw"),
                                GenTuDoc("Evaluation output is a raw text"),
                                fields=[GenTuField(t_str(), "text")],
                            ),
                        ]),
                    ])
            ],
            fields=[
                GenTuField(
                    t_opt(t_str()),
                    "lang",
                    GenTuDoc("Code block language name"),
                    value="std::nullopt",
                ),
                GenTuField(
                    t_vec(t_nest("Switch", ["BlockCode"])),
                    "switches",
                    GenTuDoc("Switch options for block"),
                    value="{}",
                ),
                GenTuField(t_nest("Exports", ["BlockCode"]),
                           "exports",
                           GenTuDoc("What to export"),
                           value="sem::BlockCode::Exports::Both"),
                opt_field(t_nest("EvalResult", ["BlockCode"]), "result",
                          GenTuDoc("Code evaluation results")),
                vec_field(t_nest("Line", ["BlockCode"]), "lines",
                          GenTuDoc("Collected code lines")),
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
    ]


def get_sem_text():
    return [
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
                        GenTuField(
                            t_nest("Mode", ["Time", "Repeat"]),
                            "mode",
                            GenTuDoc("mode"),
                        ),
                        GenTuField(
                            t_nest("Period", ["Time", "Repeat"]),
                            "period",
                            GenTuDoc("period"),
                        ),
                        GenTuField(t_int(), "count", GenTuDoc("count")),
                    ],
                ),
                GenTuTypeGroup(
                    [
                        GenTuStruct(
                            t("Static"),
                            GenTuDoc(""),
                            fields=[
                                GenTuField(t_opt(t_nest("Repeat", ["Time"])), "repeat",
                                           GenTuDoc("")),
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
                id_field(
                    "CmdArguments",
                    "parameters",
                    GenTuDoc("Additional parameters aside from 'exporter',"),
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
                GenTuField(t_vec(t_nest("Param", ["Symbol"])), "parameters",
                           GenTuDoc("Optional list of parameters")),
                GenTuField(t_vec(t_id()), "positional",
                           GenTuDoc("Positional parameters")),
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
        d_org("RadioTarget", GenTuDoc("~<<<target>>>~"), bases=[t_org("Leaf")]),
        d_org("TextTarget", GenTuDoc("~<<target>>~"), bases=[t_org("Leaf")]),
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
        d_org("Latex", GenTuDoc("Latex code body"), bases=[t_org("Org")]),
        d_org(
            "Link",
            GenTuDoc(""),
            bases=[t_org("Stmt")],
            fields=[
                GenTuField(t_opt(t_id("Paragraph")),
                           "description",
                           GenTuDoc(""),
                           value="std::nullopt")
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
                            t("UserProtocol"),
                            GenTuDoc(""),
                            fields=[
                                GenTuField(t_str(), "protocol", GenTuDoc("")),
                                GenTuField(t_str(), "target", GenTuDoc("")),
                            ],
                        ),
                        GenTuStruct(
                            t("Internal"),
                            GenTuDoc(""),
                            fields=[
                                GenTuField(t_str(), "target", GenTuDoc("")),
                            ],
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
                        GenTuStruct(
                            t("Attachment"),
                            GenTuDoc(""),
                            fields=[(GenTuField(t_str(), "file", GenTuDoc("")))],
                        ),
                    ],
                    kindGetter="getLinkKind",
                )
            ],
        ),
    ]


def get_sem_subtree():
    return [
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
                                opt_field(
                                    t_id("StmtList"),
                                    "desc",
                                    GenTuDoc("Optional description of the log entry"),
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
                                GenTuEnum(
                                    t("Action"),
                                    GenTuDoc("Priority change action"),
                                    fields=[
                                        GenTuEnumField(
                                            "Added",
                                            GenTuDoc(
                                                "`Priority B added on [timestamp]`")),
                                        GenTuEnumField(
                                            "Removed",
                                            GenTuDoc(
                                                "`Priority C removed on [timestamp]`")),
                                        GenTuEnumField(
                                            "Changed",
                                            GenTuDoc(
                                                "`Priority B changed from C on [timestamp]`"
                                            )),
                                    ]),
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
                                GenTuField(t_nest("Action", ["SubtreeLog", "Priority"]),
                                           "action", GenTuDoc("Which action taken")),
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
                                id_field("Time", "from", GenTuDoc("Clock start time")),
                                opt_field(t_id("Time"), "to",
                                          GenTuDoc("Optional end of the clock")),
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
                                GenTuField(t_str(), "from", GenTuDoc("")),
                                GenTuField(t_str(), "to", GenTuDoc("")),
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
                        GenTuStruct(
                            t("Unknown"),
                            GenTuDoc("Unknown subtree log entry kind"),
                            bases=[t_org("DescribedLog", [t("SubtreeLog")])],
                            fields=[],
                            nested=[GenTuPass("Unknown() {}")],
                        ),
                    ],
                    kindGetter="getLogKind",
                    variantField="log",
                    variantValue="sem::SubtreeLog::Note{}",
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
                opt_field(t_id("SubtreeCompletion"), "completion",
                          GenTuDoc("Task completion state")),
                opt_field(t_id("Paragraph"), "description", GenTuDoc("")),
                vec_field(t_id("HashTag"), "tags", GenTuDoc("Trailing tags")),
                id_field("Paragraph", "title", GenTuDoc("Main title")),
                vec_field(t_id("SubtreeLog"), "logbook",
                          GenTuDoc("Associated subtree log")),
                vec_field(t_nest(t("Property"), ["Subtree"]), "properties",
                          GenTuDoc("Immediate properties")),
                opt_field(t_id("Time"), "closed",
                          GenTuDoc("When subtree was marked as closed")),
                opt_field(t_id("Time"), "deadline", GenTuDoc("When is the deadline")),
                opt_field(t_id("Time"), "scheduled",
                          GenTuDoc("When the event is scheduled")),
                bool_field("isComment",
                           GenTuDoc("Subtree is annotated with the COMMENT keyword")),
                bool_field("isArchived",
                           GenTuDoc("Subtree is tagged with `:ARCHIVE:` tag")),
                opt_field(t_str(), "priority", GenTuDoc("")),
            ],
            methods=[
                GenTuFunction(
                    t_vec(t_nest(t("Period"), ["Subtree"])),
                    "getTimePeriods",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(
                            QualType(name="IntSet",
                                     Parameters=[t_nest("Kind", ["Subtree", "Period"])]),
                            "kinds",
                        )
                    ],
                ),
                GenTuFunction(
                    t_vec(t_nest(t("Property"), ["Subtree"])),
                    "getProperties",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "kind"),
                        GenTuIdent(t_cr(t_opt(t_str())), "subkind", value="std::nullopt"),
                    ],
                ),
                GenTuFunction(
                    t_opt(t_nest(t("Property"), ["Subtree"])),
                    "getProperty",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "kind"),
                        GenTuIdent(t_cr(t_opt(t_str())), "subkind", value="std::nullopt"),
                    ],
                ),
                GenTuFunction(
                    t("void"),
                    "removeProperty",
                    GenTuDoc(
                        "Remove all instances of the property with matching kind/subkind from the property list"
                    ),
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "kind"),
                        GenTuIdent(t_cr(t_opt(t_str())), "subkind", value="std::nullopt"),
                    ],
                ),
                GenTuFunction(
                    t("void"),
                    "setProperty",
                    GenTuDoc(
                        "Create or override existing property value in the subtree property list"
                    ),
                    arguments=[
                        GenTuIdent(t_cr(t_nest(t("Property"), ["Subtree"])), "value"),
                    ],
                ),
                GenTuFunction(
                    t("void"),
                    "setPropertyStrValue",
                    GenTuDoc(
                        "Assign a raw string literal to a property.",
                        "This function will not do the conversion or parsing of the assigned value, so if it is a 'created' or some other property with a typed value, it will still remain as string until the file is written and then parsed back from scratch."
                    ),
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "value"),
                        GenTuIdent(t_cr(t_str()), "kind"),
                        GenTuIdent(t_cr(t_opt(t_str())), "subkind", value="std::nullopt"),
                    ],
                ),
            ],
            nested=[
                GenTuStruct(
                    t("Period"),
                    GenTuDoc("Type of the subtree associated time periods"),
                    fields=[
                        GenTuField(
                            t_nest("Kind", ["Subtree", "Period"]),
                            "kind",
                            GenTuDoc(
                                "Time period kind -- not associated with point/range distinction"
                            ),
                        ),
                        id_field("Time", "from", GenTuDoc("Clock start time")),
                        opt_field(t_id("Time"), "to",
                                  GenTuDoc("Optional end of the clock")),
                    ],
                    nested=[
                        GenTuPass("Period() {}"),
                        GenTuEnum(
                            t("Kind"),
                            GenTuDoc("Period kind"),
                            [
                                GenTuEnumField(
                                    "Clocked",
                                    GenTuDoc("Time period of the task execution.")),
                                GenTuEnumField("Closed",
                                               GenTuDoc("Task marked as closed")),
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
                    ],
                ),
                GenTuStruct(
                    t("Property"),
                    GenTuDoc("Single subtree property"),
                    methods=[
                        GenTuFunction(
                            t_bool(),
                            "isMatching",
                            GenTuDoc(
                                "Check if property matches specified kind and optional subkind. "
                                "Built-in property checking is also done with this function -- 'created' etc."
                            ),
                            isConst=True,
                            arguments=[
                                GenTuIdent(t_cr(t_str()), "kind"),
                                GenTuIdent(t_cr(t_opt(t_str())),
                                           "subKind",
                                           value="std::nullopt"),
                            ],
                        ),
                        GenTuFunction(
                            t_str(),
                            "getName",
                            GenTuDoc(
                                "Get non-normalized name of the property (for built-in and user)"
                            ),
                            isConst=True,
                        ),
                        GenTuFunction(
                            t_opt(t_str()),
                            "getSubKind",
                            GenTuDoc("Get non-normalized sub-kind for the property."),
                            isConst=True,
                        ),
                    ],
                    fields=[
                        GenTuField(
                            t_nest("SetMode", ["Subtree", "Property"]),
                            "mainSetRule",
                            GenTuDoc(""),
                            value="sem::Subtree::Property::SetMode::Override",
                        ),
                        GenTuField(t_nest("SetMode", ["Subtree", "Property"]),
                                   "subSetRule",
                                   GenTuDoc(""),
                                   value="sem::Subtree::Property::SetMode::Override"),
                        GenTuField(
                            t_nest("InheritanceMode", ["Subtree", "Property"]),
                            "inheritanceMode",
                            GenTuDoc(""),
                            value="sem::Subtree::Property::InheritanceMode::ThisAndSub",
                        ),
                    ],
                    nested=[
                        GenTuPass("Property() {}"),
                        d_simple_enum("SetMode", GenTuDoc(""), "Override", "Add",
                                      "Subtract"),
                        d_simple_enum("InheritanceMode", GenTuDoc(""), "ThisAndSub",
                                      "OnlyThis", "OnlySub"),
                        GenTuTypeGroup(get_subtree_property_types()),
                        GenTuPass("Property(CR<Data> data) : data(data) {}"),
                    ],
                ),
            ],
        ),
        d_org(
            "SubtreeCompletion",
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
    ]


def get_types() -> Sequence[GenTuStruct]:
    return [
        *get_sem_misc(),
        *get_sem_bases(),
        *get_sem_commands(),
        *get_sem_text(),
        *get_sem_block(),
        *get_sem_subtree(),
        d_org("Cell",
              GenTuDoc("Table cell"),
              bases=[t_org("Cmd")],
              fields=[
                  bool_field(
                      "isBlock",
                      GenTuDoc("Single-line pipe cell or `#+cell:` command"),
                  ),
              ]),
        d_org("Row",
              GenTuDoc("Table row"),
              bases=[t_org("Cmd")],
              fields=[
                  vec_field(t_id("Cell"), "cells", GenTuDoc("List of cells on the row")),
                  bool_field(
                      "isBlock",
                      GenTuDoc("Single-line pipe cell or `#+cell:` command"),
                  ),
              ]),
        d_org(
            "Table",
            GenTuDoc("Table"),
            bases=[t_org("Block")],
            fields=[
                vec_field(
                    t_id("Row"),
                    "rows",
                    GenTuDoc("List of rows for the table"),
                ),
                bool_field(
                    "isBlock",
                    GenTuDoc("Single-line pipe cell or `#+cell:` command"),
                ),
            ],
        ),
        d_org(
            "Paragraph",
            GenTuDoc("Top-level or inline paragraph"),
            bases=[t_org("Stmt")],
        ),
        d_org(
            "AnnotatedParagraph",
            GenTuDoc("Top-level or inline paragraph with prefix annotation"),
            bases=[t_org("Stmt")],
            nested=[
                GenTuTypeGroup(
                    [
                        GenTuStruct(t("None")),
                        GenTuStruct(t("Footnote"), fields=[GenTuField(t_str(), "name")]),
                        GenTuStruct(
                            t("Admonition"),
                            fields=[
                                id_field("BigIdent", "name",
                                         GenTuDoc("Prefix admonition for the paragraph"))
                            ]),
                        GenTuStruct(
                            t("Timestamp"),
                            fields=[
                                id_field("Time", "time",
                                         GenTuDoc("Leading timestamp for the paragraph"))
                            ]),
                    ],
                    kindGetter="getAnnotationKind",
                    enumName="AnnotationKind",
                )
            ]),
        d_org(
            "ColonExample",
            GenTuDoc("Shortened colon example block"),
            bases=[t_org("Org")],
        ),
        d_org(
            "CmdAttr",
            GenTuDoc("Caption annotation for any subsequent node"),
            bases=[t_org("Attached")],
            fields=[
                GenTuField(t_str(), "target", GenTuDoc("")),
            ],
        ),
        d_org(
            "Call",
            GenTuDoc("Inline, statement or block call"),
            bases=[t_org("Org")],
            fields=[
                org_field(
                    t_str(),
                    "name",
                    GenTuDoc("Call target name"),
                ),
                id_field(
                    "CmdArguments",
                    "parameters",
                    GenTuDoc("Additional parameters aside from 'exporter',"),
                ),
                bool_field("isCommand"),
            ],
        ),
        d_org(
            "List",
            GenTuDoc(""),
            bases=[t_org("Stmt")],
            methods=[
                GenTuFunction(
                    t_bool(),
                    "isDescriptionList",
                    GenTuDoc(
                        "List is marked as description if any list item has a header"),
                    isConst=True,
                ),
                GenTuFunction(
                    t_bool(),
                    "isNumberedList",
                    GenTuDoc(
                        "List is marked as numbered if any list item has bullet text set"
                    ),
                    isConst=True,
                )
            ],
        ),
        d_org(
            "ListItem",
            GenTuDoc(""),
            bases=[t_org("Org")],
            fields=[
                GenTuField(t_nest("Checkbox", ["ListItem"]),
                           "checkbox",
                           GenTuDoc(""),
                           value="sem::ListItem::Checkbox::None"),
                opt_field(
                    t_id("Paragraph"),
                    "header",
                    GenTuDoc("Description list item header"),
                ),
                opt_field(
                    t_str(), "bullet",
                    GenTuDoc("Full text of the numbered list item, e.g. `a)`, `a.`",))
            ],
            nested=[
                d_simple_enum("Checkbox", GenTuDoc(""), "None", "Done", "Empty",
                              "Partial")
            ],
            methods=[
                GenTuFunction(
                    t_bool(),
                    "isDescriptionItem",
                    GenTuDoc(""),
                    isConst=True,
                    impl="return header.has_value();",
                )
            ],
        ),
        d_org(
            "DocumentOptions",
            GenTuDoc(""),
            bases=[t_org("Org")],
            methods=[
                GenTuFunction(
                    t_vec(t_nest("Property", ["Subtree"])),
                    "getProperties",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "kind"),
                        GenTuIdent(t_cr(t_opt(t_str())), "subKind", value="std::nullopt"),
                    ],
                ),
                GenTuFunction(
                    t_opt(t_nest("Property", ["Subtree"])),
                    "getProperty",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "kind"),
                        GenTuIdent(t_cr(t_opt(t_str())), "subKind", value="std::nullopt"),
                    ],
                ),
            ],
            nested=[
                org_struct(
                    t("ExportConfig"),
                    fields=[
                        opt_field(t_bool(), "inlinetasks"),
                        opt_field(t_bool(), "footnotes"),
                        opt_field(t_bool(), "clock"),
                        opt_field(t_bool(), "author"),
                        opt_field(t_bool(), "emphasis"),
                        opt_field(t_bool(), "specialStrings"),
                        opt_field(t_bool(), "propertyDrawers"),
                        opt_field(t_bool(), "statisticsCookies"),
                        opt_field(t_bool(), "todoText",
                                  "Include todo keywords in export"),
                        org_field(
                            t_nest("BrokenLinks", ["DocumentOptions", "ExportConfig"]),
                            "brokenLinks",
                            value="sem::DocumentOptions::ExportConfig::BrokenLinks::Mark",
                        ),
                        org_field(
                            t_nest("TocExport", ["DocumentOptions", "ExportConfig"]),
                            "tocExport",
                            value="sem::DocumentOptions::ExportConfig::DoExport{false}",
                        ),
                        org_field(
                            t_nest("TagExport", ["DocumentOptions", "ExportConfig"]),
                            "tagExport",
                            value="sem::DocumentOptions::ExportConfig::TagExport::All",
                        ),
                    ],
                    nested=[
                        org_struct(
                            t("TaskExport"),
                            org_doc(),
                            [
                                vec_field(t_str(), "taskWhitelist"),
                            ],
                        ),
                        d_simple_enum(
                            "TagExport",
                            org_doc(""),
                            "None",
                            "All",
                            efield(
                                "NotInToc",
                                "Expot tags in subtree titles but not in the table of content",
                            ),
                        ),
                        d_simple_enum(
                            "TaskFiltering",
                            GenTuDoc(""),
                            efield("Whitelist", "Include tasks from the whitelist"),
                            efield("Done", "Include tasks marked as done"),
                            efield("None", "Exclude all task subtrees from export"),
                            efield("All", "Add all task subtrees to export"),
                        ),
                        d_simple_enum("BrokenLinks", GenTuDoc(""), "Raise", "Ignore",
                                      "Mark"),
                        GenTuTypeGroup(
                            [
                                org_struct(
                                    t("DoExport"),
                                    fields=[org_field(t_bool(), "exportToc")],
                                ),
                                org_struct(
                                    t("ExportFixed"),
                                    fields=[org_field(t_int(), "exportLevels")],
                                ),
                            ],
                            variantName="TocExport",
                            enumName="TocExportKind",
                            kindGetter="getTocExportKind",
                        ),
                    ]),
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
                org_field(
                    t_nest("Visibility", ["DocumentOptions"]),
                    "initialVisibility",
                    value="sem::DocumentOptions::Visibility::ShowEverything",
                ),
                vec_field(t_nest("Property", ["Subtree"]), "properties", GenTuDoc("")),
                org_field(t_nest("ExportConfig", ["DocumentOptions"]), "exportConfig"),
                opt_field(t_bool(), "fixedWidthSections"),
                opt_field(t_bool(), "startupIndented"),
                opt_field(t_str(), "category"),
                opt_field(t_str(), "setupfile"),
                opt_field(t_int(), "maxSubtreeLevelExport"),
            ],
        ),
        d_org(
            "Document",
            GenTuDoc(""),
            bases=[t_org("Org")],
            methods=[
                GenTuFunction(
                    t_vec(t_nest("Property", ["Subtree"])),
                    "getProperties",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "kind"),
                        GenTuIdent(t_cr(t_opt(t_str())), "subKind", value="std::nullopt"),
                    ],
                ),
                GenTuFunction(
                    t_opt(t_nest("Property", ["Subtree"])),
                    "getProperty",
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "kind"),
                        GenTuIdent(t_cr(t_opt(t_str())), "subKind", value="std::nullopt"),
                    ],
                ),
            ],
            fields=[
                opt_field(t_id("Paragraph"), "title"),
                opt_field(t_id("Paragraph"), "author"),
                opt_field(t_id("Paragraph"), "creator"),
                vec_field(t_id("HashTag"), "filetags"),
                opt_field(t_id("RawText"), "email"),
                vec_field(t_str(), "language"),
                id_field("DocumentOptions", "options"),
                opt_field(t_str(), "exportFileName"),
            ],
        ),
        d_org(
            "FileTarget",
            bases=[t_org("Org")],
            fields=[
                org_field(t_str(), "path"),
                opt_field(t_int(), "line"),
                opt_field(t_str(), "searchTarget"),
                org_field(t_bool(), "restrictToHeadlines", value="false"),
                opt_field(t_str(), "targetId"),
                opt_field(t_str(), "regexp"),
            ],
        ),
        d_org(
            "TextSeparator",
            bases=[t_org("Org")],
        ),
        d_org(
            "Include",
            bases=[t_org("Org")],
            nested=[
                GenTuTypeGroup(
                    [
                        org_struct(t("Example")),
                        org_struct(t("Export")),
                        org_struct(t("Src")),
                        org_struct(
                            t("OrgDocument"),
                            fields=[
                                opt_field(
                                    t_int(),
                                    "minLevel",
                                    "The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.",
                                )
                            ]),
                    ],
                    kindGetter="getIncludeKind",
                )
            ],
            fields=[
                org_field(t_str(), "path", "Path to include"),
                opt_field(
                    t_int(), "firstLine",
                    "0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text"
                ),
                opt_field(
                    t_int(),
                    "lastLine",
                    "0-based index of the last line to include",
                ),
            ],
        ),
        d_org(
            "DocumentGroup",
            bases=[t_org("Org")],
        ),
    ]


#endregion


#region OrgNodeKind
def get_org_node_kind_text():
    return [
        efield(
            "Ident",
            "regular identifier - `alnum + [-_]` characters for punctuation. Identifiers are compared and parsed in style-insensetive manner, meaning `CODE_BLOCK`, `code-block` and `codeblock` are identical.",
        ),
        efield("BigIdent", "full-uppsercase identifier such as `MUST` or `TODO`"),
        efield(
            "Bold",
            """Region of text with formatting, which contains standalone words -
     can itself contain subnodes, which allows to represent nested
     formatting regions, such as `*bold /italic/*` text. Particular type
     of identifier is stored in string form in `str` field for `OrgNode`
     -- bold is represented as `\"*\"`, italic as `/` and so on. In case
     of explicit open/close pairs only opening one is stored.

     NOTE: when structured sentences are enabled, regular punctuation
     elements like `some text (notes)` are also represented as `Word,
     Word, Markup(str: \"(\", [Word])` - e.g. structure is not fully flat.""",
        ),
        efield("Italic"),
        efield("Verbatim"),
        efield("Backtick"),
        efield("Underline"),
        efield("Strike"),
        efield("Quote"),
        efield("Angle"),
        efield("Monospace"),
        efield("Par"),
        efield(
            "InlineMath",
            "Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\\(paren-wrapped\\)` inline text.",
        ),
        efield(
            "DisplayMath",
            "Inline display latex math from `$$double-dollar$$` or `\\[bracket-wrapped\\]` code.",
        ),
        efield("Space", "Space or tab character in regular text"),
        efield("Punctuation"),
        efield("Colon"),
        efield(
            "Word",
            "Regular word - technically not different from `orgIdent`, but defined separately to disiguish between places where special syntax is required and free-form text.",
        ),
        efield("Escaped", "Escaped formatting character in the text"),
        efield("Newline"),
        efield("RawLink", "Raw unwrapped link that was pasted in text"),
        efield(
            "Link",
            """External or internal link. Consists of one or two elements - target
     (url, file location etc.) and description (`orgParagraph` of text).
     Description might be empty, and represented as empty node in this
     case. For external links particular formatting of the address is
     not handled by parser and instead contains raw string from input
     text.""",
        ),
        efield(
            "Macro",
            """Org-mode macro replacement - during export each macro is expanded
     and evaluated according to it's environment. Body of the macro is
     not parsed fully during org-mode evaluation, but is checked for
     correct parenthesis balance (as macro might contain elisp code)""",
        ),
        efield(
            "Symbol",
            "Special symbol that should be exported differently to various backends - greek letters (`\alpha`), mathematical notations and so on.",
        ),
        efield("StaticActiveTime"),
        efield("StaticInactiveTime"),
        efield("DynamicActiveTime"),
        efield(
            "DynamicInactiveTime",
            "Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later",
        ),
        efield(
            "TimeRange",
            "Date and time range format - two `orgDateTime` entries",
        ),
        efield(
            "SimpleTime",
            "Result of the time range evaluation or trailing annotation a subtree",
        ),
        efield("HashTag"),
        efield("MetaSymbol", "`\\sym{}` with explicit arguments"),
        efield("AtMention", "`@user`"),
        efield(
            "Placeholder",
            "Placeholder entry in text, usually writte like `<text to replace>`",
        ),
        efield("RadioTarget", "`<<<RADIO>>>`"),
        efield("Target", "`<<TARGET>>`"),
        efield(
            "SrcInlineCode",
            "inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc.",
        ),
        efield(
            "InlineCallCode",
            "Call to named source code block.",
        ),
        efield(
            "InlineExport",
            "Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively",
        ),
        efield("InlineComment"),
        efield(
            "RawText",
            "Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers ",
        ),
    ]


def get_org_node_kind_blocks():
    return [
        efield(
            "BlockVerbatimMultiline",
            "Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks.",
        ),
        efield("CodeLine", "Single line of source code"),
        efield("CodeText", "Block of source code text"),
        efield("CodeTangle", "Single tangle target in the code block"),
        efield("CodeCallout", "`(refs:` callout in the source code"),
        efield("BlockCode"),
        efield("BlockQuote", "`#+begin_quote:` block in code"),
        efield("BlockComment", "`#+begin_comment:` block in code"),
        efield("BlockCenter"),
        efield("BlockVerse"),
        efield("BlockExample", "Verbatim example text block"),
        efield("BlockExport"),
        efield("BlockDetails", "`#+begin_details`  section"),
        efield("BlockSummary", "`#+begin_summary` section"),
    ]


def get_org_node_kind_commands():
    return [
        efield(
            "Cmd",
            "Undefined single-line command -- most likely custom user-provided oe",
        ),
        efield("CmdArguments", "Arguments for the command block"),
        efield("CmdTitle", "`#+title:` - full document title"),
        efield("CmdAuthor", "`#+author:` Document author"),
        efield("CmdCreator", "`#+creator:` Document creator"),
        efield(
            "CmdInclude",
            "`#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk.",
        ),
        efield("CmdLanguage", "`#+language:`"),
        efield("CmdAttr", "`#+attr_html:`, `#+attr_image` etc."),
        efield("CmdStartup", "`#+startup:`"),
        efield("CmdName", "`#+name:` - name of the associated entry"),
        efield("CmdCustomTextCommand", "Line command with parsed text value"),
        efield("CmdCustomArgsCommand", "Line command with parsed argument list"),
        efield("CmdCustomRawCommand", "Line command with raw text argument"),
        efield("CmdResults", "`#+results:` - source code block evaluation results"),
        efield("CmdHeader",
               "`#+header:` - extended list of parameters passed to associated block"),
        efield("CmdOptions", "`#+options:` - document-wide formatting options"),
        efield("CmdTblfm"),
        efield("CmdCaption", "`#+caption:` command"),
        efield("CmdResult", "Command evaluation result"),
        efield("CmdCallCode", "Call to named source code block."),
        efield(
            "CmdFlag",
            "Flag for source code block. For example `-n`, which is used to to make source code block export with lines",
        ),
        efield("CmdKey"),
        efield("CmdValue"),
        efield("CmdNamedValue", "Key-value pair for source code block call."),
        efield("CmdLatexClass"),
        efield("CmdLatexHeader"),
        efield("CmdLatexCompiler"),
        efield("CmdLatexClassOptions"),
        efield("CmdHtmlHead"),
        efield(
            "CmdColumns",
            "`#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis.",
        ),
        efield("CmdPropertyArgs", "`#+property:` command"),
        efield("CmdPropertyText", "`#+property:` command"),
        efield("CmdPropertyRaw", "`#+property:` command"),
        efield("CmdFiletags", "`#+filetags:` line command"),
    ]


def get_org_node_kind_subtree():
    return [
        efield("SubtreeDescription", "`:description:` entry"),
        efield("SubtreeUrgency"),
        efield("DrawerLogbook", "`:logbook:` entry storing note information"),
        efield(
            "Drawer",
            "Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`",
        ),
        efield("DrawerPropertyList"),
        efield("DrawerProperty", "`:property:` drawer"),
        efield("Subtree", "Section subtree"),
        efield("SubtreeTimes", "Time? associated with subtree entry"),
        efield("SubtreeStars"),
        efield(
            "SubtreeCompletion",
            "Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio.",
        ),
        efield(
            "SubtreeImportance",
            "Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`.",
        ),
    ]


def get_org_node_kind():
    return [
        #tag org-structural
        efield("None", "Default valye for node - invalid state"),
        efield(
            "Document",
            "Toplevel part of the ast, not created by parser, and only used in `semorg` stage",
        ),
        efield(
            "Empty",
            "Empty node - valid state that does not contain any value",
        ),
        efield("InlineStmtList"),
        efield(
            "StmtList",
            "List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together.",
        ),

        #tag org-list
        efield("Checkbox", "Single checkbox item like `[X]` or `[-]`"),
        efield("List"),
        efield("Bullet", "List item prefix"),
        efield("ListItem"),
        efield(
            "ListTag",
            "Auxilliary wrapper for the paragraph placed at the start of the description list.",
        ),
        efield("Counter"),
        #tag org-doclevel
        efield("File"),
        efield("ColonExample", "Colon example block"),
        efield("TextSeparator", "Long horizontal line `----`"),
        efield(
            "Paragraph",
            "Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph",
        ),
        efield(
            "AnnotatedParagraph",
            "Annotated paragraph -- a wrapper around a regular paragraph kind with added admonition, footnote, list tag prefix and similar types. `[fn:ID] Some Text` is an annotated paragraph, just like `NOTE: Text` or `- Prefix :: Body` (in this case list header is an annotated paragraph)",
        ),
        efield("TableRow", "Horizontal table row"),
        efield(
            "TableCell",
            "Single cell in row. Might contain anyting, including other tables, simple text paragraph etc.",
        ),
        efield("Table", "Org-mode table"),
        efield(
            "InlineFootnote",
            "Inline footnote with text placed directly in the node body.",
        ),
        efield(
            "Footnote",
            "Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node.",
        ),
        *get_org_node_kind_commands(),
        *get_org_node_kind_blocks(),
        *get_org_node_kind_text(),
        *get_org_node_kind_subtree(),
    ]


#endregion


def get_enums():
    return [
        #tag Org spec name
        GenTuEnum(
            t("OrgSpecName"),
            GenTuDoc(""),
            [
                efield("Unnamed"),
                efield("Result"),
                efield("Year"),
                efield("Day"),
                efield("Clock"),
                efield("Repeater"),
                efield("Zone"),
                efield("Link"),
                efield("Tags"),
                efield("Tag"),
                efield("State"),
                efield("Protocol"),
                efield("Desc"),
                efield("Times"),
                efield("Drawer"),
                efield("Args"),
                efield("Name"),
                efield("Definition"),
                efield("Body"),
                efield("HeaderArgs"),
                efield("File"),
                efield("Kind"),
                efield("Lang"),
                efield("Prefix"),
                efield("Text"),
                efield("Todo"),
                efield("Importance"),
                efield("Title"),
                efield("Completion"),
                efield("Head"),
                efield("Subnodes"),
                efield("Properties"),
                efield("Logbook"),
                efield("Description"),
                efield("Logs"),
                efield("Newstate"),
                efield("Oldstate"),
                efield("Time"),
                efield("From"),
                efield("EndArgs"),
                efield("Flags"),
                efield("Value"),
                efield("Assoc"),
                efield("Main"),
                efield("Hash"),
                efield("Bullet"),
                efield("Counter"),
                efield("Checkbox"),
                efield("Header"),
                efield("To"),
                efield("Diff"),
                efield("Property"),
                efield("Subname"),
                efield("Values"),
                efield("Cells"),
                efield("Rows"),
                efield("Lines"),
                efield("Chunks"),
                efield("InheritanceMode"),
                efield("MainSetRule"),
                efield("SubSetRule"),
            ],
        ),
        GenTuEnum(
            t("OrgNodeKind"),
            #region OrgNodeKind
            GenTuDoc(""),
            get_org_node_kind(),
            #endregion
        ),
    ]
