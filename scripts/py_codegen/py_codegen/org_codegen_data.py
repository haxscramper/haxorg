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
def t_str() -> QualType:
    return t("Str", [n_hstd()])


@beartype
def t_bool() -> QualType:
    return t("bool")


@beartype
def t_int() -> QualType:
    return t("int")


@beartype
def t_user_time() -> QualType:
    return t("UserTime", [n_hstd()])


@beartype
def t_nest_shared(name: Union[str, QualType], Spaces: List[QualType] = []) -> QualType:
    return t_nest(name=name, Spaces=Spaces)


@beartype
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
    return QualType(name="Variant", Parameters=[*args], Spaces=[n_hstd()])


def t_map(key: QualType, val: QualType) -> QualType:
    return QualType(name="UnorderedMap", Parameters=[key, val], Spaces=[n_hstd()])


#endregion


@beartype
def org_struct(
    typ: QualType,
    doc: AnyDoc = GenTuDoc(""),
    fields: List[GenTuField] = [],
    nested: List[GenTuEntry] = [],
    methods: List[GenTuFunction] = [],
    bases: List[QualType] = [],
) -> GenTuStruct:
    return GenTuStruct(
        name=typ,
        doc=org_doc(doc),
        fields=fields,
        nested=nested,
        methods=methods,
        bases=bases,
        IsDescribedRecord=True,
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
def org_function(result: QualType, name: str, *args, **kwargs) -> GenTuFunction:
    return GenTuFunction(result, name, *args, **kwargs)


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
    return GenTuIdent(type=typ, name=name, value=value)


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


@beartype
def int_field(name: str, doc: AnyDoc = GenTuDoc(""), default: str = 0) -> GenTuField:
    return org_field(t_int(), name, doc, default)


@beartype
def eq_method(name: QualType) -> GenTuFunction:
    return GenTuFunction(
        result=t_bool(),
        name="operator==",
        arguments=[GenTuIdent(type=name.asConstRef(), name="other")],
        isConst=True,
    )


@beartype
def default_constructor(name: str) -> GenTuPass:
    return GenTuPass(f"{name} () {{}}")


@beartype
def default_constructor_method(name: str) -> GenTuFunction:
    return GenTuFunction(
        name=name,
        impl="",
        result=None,
        IsConstructor=True,
    )


#endregion


def d_org(name: str, *args, **kwargs) -> GenTuStruct:
    res = GenTuStruct(
        QualType(
            name=name,
            meta=dict(isOrgType=True),
            Spaces=[n_sem()],
            dbg_origin="d_org",
        ),
        *args,
        **kwargs,
    )

    res.__setattr__("isOrgType", True)
    kind: str = res.name.name
    base = res.bases[0]
    res.nested = [
        GenTuPass(f"using {base.name}::{base.name};"),
        GenTuPass(f"virtual ~{name}() = default;")
    ] + res.nested

    res.reflectionParams.backend.python.holder_type = QualType(
        name="SemId",
        Spaces=[
            QualType(name="org"),
            QualType(name="sem"),
        ],
    )

    res.reflectionParams.backend.wasm.holder_type = QualType(
        name="SemId",
        Spaces=[
            QualType(name="org"),
            QualType(name="sem"),
        ],
    )

    res.reflectionParams.type_api = GenTuTypeApiTraits(is_org_ast_value=True,)

    res.IsDescribedRecord = True

    if not res.IsAbstract:
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
def d_simple_enum(name: QualType, doc: AnyDoc, *args):
    return GenTuEnum(
        name,
        org_doc(doc),
        fields=[
            GenTuEnumField(arg, GenTuDoc("")) if isinstance(arg, str) else arg
            for arg in args
        ],
    )


@beartype
def get_diagnostic_types() -> List[GenTuStruct]:
    return [
        org_struct(
            t_nest_shared("ParseTokenError", [t("OrgDiagnostics")]),
            GenTuDoc(
                "Parser errors for situations when failure can be attributed to specific token"
            ),
            fields=[
                org_field(t_str(), "brief"),
                org_field(t_str(), "detail"),
                org_field(t_str(), "parserFunction"),
                org_field(t_int(), "parserLine"),
                org_field(t("OrgTokenKind"), "tokenKind"),
                org_field(t_str(), "tokenText"),
                org_field(t_nest_shared("SourceLocation"), "loc"),
                org_field(t_str(), "errName"),
                org_field(t_str(), "errCode"),
            ],
            nested=[GenTuPass("ParseTokenError() {}")],
            methods=[eq_method(t_nest_shared("ParseTokenError", [t("OrgDiagnostics")]))],
        ),
        org_struct(
            t_nest_shared("ParseError", [t("OrgDiagnostics")]),
            GenTuDoc("General parser errors"),
            fields=[
                org_field(t_str(), "brief"),
                org_field(t_str(), "detail"),
                org_field(t_str(), "parserFunction"),
                org_field(t_int(), "parserLine"),
                org_field(t_str(), "errName"),
                org_field(t_str(), "errCode"),
            ],
            nested=[GenTuPass("ParseError() {}")],
            methods=[eq_method(t_nest_shared("ParseError", [t("OrgDiagnostics")]))],
        ),
        org_struct(
            t_nest_shared("IncludeError", [t("OrgDiagnostics")]),
            GenTuDoc("Cannot convert parsed tree into"),
            fields=[
                org_field(t_str(), "brief"),
                org_field(t_str(), "targetPath"),
                org_field(t_str(), "workingFile"),
            ],
            nested=[GenTuPass("IncludeError() {}")],
            methods=[eq_method(t_nest_shared("IncludeError", [t("OrgDiagnostics")]))],
        ),
        org_struct(
            t_nest_shared("ConvertError", [t("OrgDiagnostics")]),
            GenTuDoc("Cannot convert parsed tree into"),
            fields=[
                org_field(t_str(), "brief"),
                org_field(t_str(), "detail"),
                org_field(t_str(), "convertFunction"),
                org_field(t_int(), "convertLine"),
                org_field(t_str(), "convertFile"),
                org_field(t_str(), "errName"),
                org_field(t_str(), "errCode"),
                opt_field(t_nest_shared("SourceLocation"), "loc"),
            ],
            nested=[GenTuPass("ConvertError() {}")],
            methods=[eq_method(t_nest_shared("ConvertError", [t("OrgDiagnostics")]))],
        ),
        org_struct(
            t_nest_shared("InternalError", [t("OrgDiagnostics")]),
            GenTuDoc(
                "Internal implementation error: should not be visible to the end-user."),
            fields=[
                org_field(t_str(), "message"),
                org_field(t_str(), "function"),
                org_field(t_int(), "line"),
                org_field(t_str(), "file"),
                opt_field(t_nest_shared("SourceLocation"), "loc"),
            ],
            nested=[GenTuPass("InternalError() {}")],
            methods=[eq_method(t_nest_shared("InternalError", [t("OrgDiagnostics")]))],
        ),
    ]


@beartype
def get_subtree_property_types() -> List[GenTuStruct]:
    return [
        org_struct(
            t_nest_shared("Nonblocking", [t("NamedProperty")]),
            GenTuDoc(""),
            fields=[GenTuField(t_bool(), "isBlocking", GenTuDoc(""))],
            nested=[GenTuPass("Nonblocking() {}")],
            methods=[eq_method(t_nest_shared("Nonblocking", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("ArchiveTime", [t("NamedProperty")]),
            GenTuDoc(""),
            nested=[GenTuPass("ArchiveTime() {}")],
            methods=[eq_method(t_nest_shared("ArchiveTime", [t("NamedProperty")]))],
            fields=[GenTuField(t_user_time(), "time")],
        ),
        org_struct(
            t_nest_shared("ArchiveFile", [t("NamedProperty")]),
            GenTuDoc(""),
            nested=[GenTuPass("ArchiveFile() {}")],
            methods=[eq_method(t_nest_shared("ArchiveFile", [t("NamedProperty")]))],
            fields=[GenTuField(t_str(), "file")],
        ),
        org_struct(
            t_nest_shared("ArchiveOlpath", [t("NamedProperty")]),
            GenTuDoc(""),
            nested=[GenTuPass("ArchiveOlpath() {}")],
            methods=[eq_method(t_nest_shared("ArchiveOlpath", [t("NamedProperty")]))],
            fields=[GenTuField(t_nest_shared("SubtreePath"), "path")],
        ),
        org_struct(
            t_nest_shared("ArchiveTarget", [t("NamedProperty")]),
            GenTuDoc(""),
            nested=[GenTuPass("ArchiveTarget() {}")],
            methods=[eq_method(t_nest_shared("ArchiveTarget", [t("NamedProperty")]))],
            fields=[
                GenTuField(t_nest_shared("SubtreePath"), "path"),
                GenTuField(t_str(), "pattern"),
            ],
        ),
        org_struct(
            t_nest_shared("ArchiveCategory", [t("NamedProperty")]),
            GenTuDoc(""),
            nested=[GenTuPass("ArchiveCategory() {}")],
            methods=[eq_method(t_nest_shared("ArchiveCategory", [t("NamedProperty")]))],
            fields=[GenTuField(t_str(), "category")],
        ),
        org_struct(
            t_nest_shared("ArchiveTodo", [t("NamedProperty")]),
            GenTuDoc(""),
            nested=[GenTuPass("ArchiveTodo() {}")],
            methods=[eq_method(t_nest_shared("ArchiveTodo", [t("NamedProperty")]))],
            fields=[GenTuField(t_str(), "todo")],
        ),
        org_struct(
            t_nest_shared("Trigger", [t("NamedProperty")]),
            GenTuDoc(""),
            nested=[GenTuPass("Trigger() {}")],
            methods=[eq_method(t_nest_shared("Trigger", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("ExportLatexClass", [t("NamedProperty")]),
            GenTuDoc(""),
            fields=[GenTuField(t_str(), "latexClass", GenTuDoc(""))],
            nested=[GenTuPass("ExportLatexClass() {}")],
            methods=[eq_method(t_nest_shared("ExportLatexClass", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("CookieData", [t("NamedProperty")]),
            GenTuDoc("`:COOKIE_DATA:` for the subtree completion calculation"),
            nested=[],
            fields=[
                org_field(t_bool(), "isRecursive"),
                org_field(t("SubtreeTodoSource"), "source"),
            ],
            methods=[eq_method(t_nest_shared("CookieData", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("ExportLatexClassOptions", [t("NamedProperty")]),
            GenTuDoc(""),
            fields=[GenTuField(t_vec(t_str()), "options", GenTuDoc(""))],
            nested=[GenTuPass("ExportLatexClassOptions() {}")],
            methods=[
                eq_method(t_nest_shared("ExportLatexClassOptions", [t("NamedProperty")]))
            ],
        ),
        org_struct(
            t_nest_shared("ExportLatexHeader", [t("NamedProperty")]),
            GenTuDoc(""),
            fields=[GenTuField(t_str(), "header", GenTuDoc(""))],
            nested=[GenTuPass("ExportLatexHeader() {}")],
            methods=[eq_method(t_nest_shared("ExportLatexHeader", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("ExportLatexCompiler", [t("NamedProperty")]),
            GenTuDoc(""),
            fields=[GenTuField(t_str(), "compiler", GenTuDoc(""))],
            nested=[GenTuPass("ExportLatexCompiler() {}")],
            methods=[
                eq_method(t_nest_shared("ExportLatexCompiler", [t("NamedProperty")]))
            ],
        ),
        org_struct(
            t_nest_shared("Ordered", [t("NamedProperty")]),
            GenTuDoc(""),
            fields=[GenTuField(t_bool(), "isOrdered", GenTuDoc(""))],
            nested=[GenTuPass("Ordered() {}")],
            methods=[eq_method(t_nest_shared("Ordered", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("Effort", [t("NamedProperty")]),
            GenTuDoc(""),
            fields=[
                GenTuField(t_int(), "hours", GenTuDoc(""), value="0"),
                GenTuField(t_int(), "minutes", GenTuDoc(""), value="0"),
            ],
            nested=[GenTuPass("Effort() {}")],
            methods=[eq_method(t_nest_shared("Effort", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("Visibility", [t("NamedProperty")]),
            GenTuDoc(""),
            nested=[
                GenTuPass("Visibility() {}"),
                d_simple_enum(
                    t_nest_shared(
                        "Level", [t("NamedProperty"), t("Visibility")]),
                    GenTuDoc(""),
                    "Folded",
                    "Children",
                    "Content",
                    "All",
                )
            ],
            fields=[
                GenTuField(
                    t_nest_shared(
                        "Level", [t("NamedProperty"), t("Visibility")]),
                    "level",
                    GenTuDoc(""),
                )
            ],
            methods=[eq_method(t_nest_shared("Visibility", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("ExportOptions", [t("NamedProperty")]),
            GenTuDoc(""),
            nested=[GenTuPass("ExportOptions() {}")],
            methods=[eq_method(t_nest_shared("ExportOptions", [t("NamedProperty")]))],
            fields=[
                GenTuField(t_str(), "backend", GenTuDoc("")),
                GenTuField(t_map(t_str(), t_str()), "values", GenTuDoc("")),
            ],
        ),
        org_struct(
            t_nest_shared("Blocker", [t("NamedProperty")]),
            GenTuDoc(""),
            nested=[GenTuPass("Blocker() {}")],
            fields=[GenTuField(t_vec(t_str()), "blockers", GenTuDoc(""))],
            methods=[eq_method(t_nest_shared("Blocker", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("Unnumbered", [t("NamedProperty")]),
            GenTuDoc(""),
            nested=[GenTuPass("Unnumbered() {}")],
            methods=[eq_method(t_nest_shared("Unnumbered", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("Created", [t("NamedProperty")]),
            GenTuDoc(""),
            nested=[GenTuPass("Created() {}")],
            fields=[GenTuField(t_user_time(), "time", GenTuDoc(""))],
            methods=[eq_method(t_nest_shared("Created", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("RadioId", [t("NamedProperty")]),
            GenTuDoc("Radio target ID"),
            nested=[GenTuPass("RadioId() {}")],
            fields=[vec_field(t_str(), "words")],
            methods=[eq_method(t_nest_shared("RadioId", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("HashtagDef", [t("NamedProperty")]),
            GenTuDoc("Definition of a hashtag entry"),
            nested=[GenTuPass("HashtagDef() {}")],
            fields=[org_field(t_nest_shared("HashTagText"), "hashtag")],
            methods=[eq_method(t_nest_shared("HashtagDef", [t("NamedProperty")]))],
        ),
        org_struct(
            t_nest_shared("CustomArgs", [t("NamedProperty")]),
            GenTuDoc("Custop property with unparsed arguments"),
            nested=[GenTuPass("CustomArgs() {}")],
            methods=[eq_method(t_nest_shared("CustomArgs", [t("NamedProperty")]))],
            fields=[
                str_field("name", GenTuDoc("Original name of the property")),
                opt_field(t_str(), "sub", GenTuDoc("Property target specialization")),
                org_field(t_nest_shared("AttrGroup"), "attrs",
                          GenTuDoc("Property parameters")),
            ],
        ),
        org_struct(
            t_nest_shared("CustomRaw", [t("NamedProperty")]),
            GenTuDoc("Custom property with unparsed arguments"),
            nested=[GenTuPass("CustomRaw() {}")],
            methods=[eq_method(t_nest_shared("CustomRaw", [t("NamedProperty")]))],
            fields=[
                str_field("name", GenTuDoc("Original name of the property")),
                str_field("value", GenTuDoc("Property value")),
            ],
        ),
        org_struct(
            t_nest_shared("CustomId", [t("NamedProperty")]),
            GenTuDoc("Custom property with unparsed arguments"),
            nested=[GenTuPass("CustomId() {}")],
            methods=[eq_method(t_nest_shared("CustomId", [t("NamedProperty")]))],
            fields=[
                str_field("value", GenTuDoc("Property value")),
            ],
        ),
        org_struct(
            t_nest_shared("CustomSubtreeJson", [t("NamedProperty")]),
            GenTuDoc("Free-form JSON"),
            methods=[eq_method(t_nest_shared("CustomSubtreeJson", [t("NamedProperty")]))],
            fields=[
                org_field(t_str(), "name"),
                org_field(t_nest_shared("OrgJson"), "value")
            ],
        ),
        org_struct(
            t_nest_shared("CustomSubtreeFlags", [t("NamedProperty")]),
            GenTuDoc("Free-form flags"),
            methods=[
                eq_method(t_nest_shared("CustomSubtreeFlags", [t("NamedProperty")]))
            ],
            fields=[
                org_field(t_str(), "name"),
                org_field(t_nest_shared("AttrGroup"), "value")
            ],
        ),
    ]


#region org-types


def get_sem_bases():
    return [
        d_org(
            "ErrorItem",
            doc=org_doc(""),
            bases=[t_nest(t_org("Org"))],
            fields=[
                org_field(t_nest_shared("OrgDiagnostics", []), "diag"),
            ],
        ),
        d_org(
            "ErrorGroup",
            doc=org_doc("Group of value conversion errors"),
            bases=[t_nest(t_org("Org"))],
            fields=[
                vec_field(t_id("ErrorItem"), "diagnostics"),
            ],
        ),
        d_org(
            "Stmt",
            GenTuDoc(
                "Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)"
            ),
            bases=[t_nest(t_org("Org"))],
            IsAbstract=True,
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
                    t_vec(t_id()),
                    "getCaption",
                    isConst=True,
                ),
                GenTuFunction(
                    t_vec(t_str()),
                    "getName",
                    isConst=True,
                ),
                GenTuFunction(
                    t_vec(t_nest_shared("AttrValue")),
                    "getAttrs",
                    GenTuDoc(
                        "Get all named arguments for the command, across all attached properties. "
                        "If kind is nullopt returns all attached arguments for all properties."
                    ),
                    arguments=[opt_ident(t_str(), "kind", GenTuDoc(""))],
                    isConst=True,
                    isVirtual=True,
                ),
                GenTuFunction(
                    t_opt(t_nest_shared("AttrValue")),
                    "getFirstAttr",
                    GenTuDoc(
                        "Get the first parameter for the statement. "
                        "In case there is a longer list of values matching given kind"
                        "different node kinds can implement different priorities "),
                    arguments=[arg_ident(t_cr(t_str()), "kind")],
                    isConst=True,
                    isVirtual=True,
                ),
                GenTuFunction(
                    t_opt(t_str()),
                    "getFirstAttrString",
                    arguments=[arg_ident(t_cr(t_str()), "kind")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_int()),
                    "getFirstAttrInt",
                    arguments=[arg_ident(t_cr(t_str()), "kind")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_bool()),
                    "getFirstAttrBool",
                    arguments=[arg_ident(t_cr(t_str()), "kind")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(QualType(name="double")),
                    "getFirstAttrDouble",
                    arguments=[arg_ident(t_cr(t_str()), "kind")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_nest_shared("LispValue", [t("AttrValue")])),
                    "getFirstAttrLisp",
                    arguments=[arg_ident(t_cr(t_str()), "kind")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_nest_shared("Kind", [t("AttrValue")])),
                    "getFirstAttrKind",
                    arguments=[arg_ident(t_cr(t_str()), "kind")],
                    isConst=True,
                ),
            ],
            nested=[
                GenTuPass("Stmt() {}"),
                GenTuPass(
                    "Stmt(hstd::Vec<SemId<Org>> const& attached, hstd::Vec<SemId<Org>> const& subnodes) : Org(subnodes), attached(attached) {}"
                ),
            ],
        ),
        d_org(
            "Inline",
            GenTuDoc("Base class for all inline elements"),
            bases=[t_nest(t_org("Org"))],
            IsAbstract=True,
        ),
        d_org(
            "StmtList",
            GenTuDoc("Zero or more statement nodes"),
            bases=[t_nest(t_org("Org"))],
        ),
        d_org(
            "Empty",
            GenTuDoc("Node without content"),
            bases=[t_nest(t_org("Org"))],
        ),
        d_org(
            "Cmd",
            GenTuDoc("Base class for block or line commands"),
            bases=[t_nest(t_org("Stmt"))],
            IsAbstract=True,
            fields=[
                org_field(
                    t_nest_shared("AttrGroup"),
                    "attrs",
                    GenTuDoc("Additional parameters aside from 'exporter',"),
                ),
            ],
            methods=[
                GenTuFunction(
                    t_vec(t_nest_shared("AttrValue")),
                    "getAttrs",
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
                    t_opt(t_nest_shared("AttrValue")),
                    "getFirstAttr",
                    GenTuDoc(
                        "Override of the base statement argument get, prioritizing the explicit command parameters"
                    ),
                    arguments=[arg_ident(t_cr(t_str()), "kind")],
                    isConst=True,
                    isVirtual=True,
                    isOverride=True,
                ),
            ],
        ),
        d_org(
            "Block",
            GenTuDoc("Block command type"),
            bases=[t_nest(t_org("Cmd"))],
            IsAbstract=True,
        ),
        d_org(
            "LineCommand",
            GenTuDoc("Line commands"),
            bases=[t_nest(t_org("Cmd"))],
            IsAbstract=True,
        ),
        d_org(
            "Attached",
            GenTuDoc("Line command that might get attached to some block element"),
            bases=[t_nest(t_org("LineCommand"))],
            IsAbstract=True,
        ),
        d_org(
            "Leaf",
            GenTuDoc("Final node"),
            bases=[t_nest(t_org("Org"))],
            IsAbstract=True,
            fields=[
                GenTuField(t_str(), "text", GenTuDoc("Final leaf value"), value='""')
            ],
            methods=[
                GenTuFunction(t_str(), "getText", isConst=True, impl="return text;"),
            ],
        ),
    ]


def get_sem_commands():
    return [
        d_org(
            "CmdCaption",
            GenTuDoc("Caption annotation for any subsequent node"),
            bases=[t_nest(t_org("Attached"))],
            fields=[id_field("Paragraph", "text", GenTuDoc("Content description"))],
        ),
        d_org(
            "CmdColumns",
            GenTuDoc("Caption annotation for any subsequent node"),
            bases=[t_nest(t_org("Attached"))],
            fields=[org_field(t_nest_shared("ColumnView"), "view")],
        ),
        d_org(
            "CmdName",
            GenTuDoc("Name identifier for the statement elements."),
            bases=[t_nest(t_org("Attached"))],
            fields=[
                GenTuField(t_str(), "name", GenTuDoc("")),
            ],
        ),
        d_org(
            "CmdCustomArgs",
            doc=org_doc("Custom line command with list of parsed arguments"),
            bases=[t_nest(t_org("Cmd"))],
            fields=[
                org_field(t_str(), "name"),
                bool_field("isAttached"),
            ],
        ),
        d_org(
            "CmdCustomRaw",
            doc=org_doc("Custom command with raw unparsed string value"),
            bases=[t_nest(t_org("Stmt"))],
            fields=[
                org_field(t_str(), "name"),
                bool_field("isAttached"),
                org_field(t_str(), "text"),
            ],
        ),
        d_org(
            "CmdCustomText",
            doc=org_doc("Custom line command with text paragraph value"),
            bases=[t_nest(t_org("Stmt"))],
            fields=[
                org_field(t_str(), "name"),
                bool_field("isAttached"),
                id_field("Paragraph", "text"),
            ],
        ),
        d_org(
            "CmdCall",
            GenTuDoc(""),
            bases=[t_nest(t_org("Attached"))],
            fields=[
                str_field("name", "Code block call name"),
                opt_field(t_str(), "fileName", "Which file code block should come from"),
                org_field(
                    t_nest_shared("AttrGroup"),
                    "insideHeaderAttrs",
                    GenTuDoc("Additional parameters aside from 'exporter',"),
                ),
                org_field(
                    t_nest_shared("AttrGroup"),
                    "callAttrs",
                    GenTuDoc("Additional parameters aside from 'exporter',"),
                ),
                org_field(
                    t_nest_shared("AttrGroup"),
                    "endHeaderAttrs",
                    GenTuDoc("Additional parameters aside from 'exporter',"),
                ),
                vec_field(t_id("BlockCodeEvalResult"), "result",
                          "Code evaluation results"),
            ],
        ),
        d_org("CmdTblfm",
              GenTuDoc("Tblfm command type"),
              bases=[t_nest(t_org("Cmd"))],
              fields=[org_field(t_nest_shared("Tblfm"), "expr")]),
    ]


def get_sem_block():
    return [
        d_org("BlockCenter",
              GenTuDoc("Center nested content in export"),
              bases=[t_nest(t_org("Block"))]),
        d_org(
            "BlockQuote",
            GenTuDoc("Quotation block"),
            bases=[t_nest(t_org("Block"))],
        ),
        d_org(
            "BlockComment",
            GenTuDoc("Comment block"),
            bases=[t_nest(t_org("Stmt"))],
        ),
        d_org(
            "BlockVerse",
            GenTuDoc("Verse quotation block"),
            bases=[t_nest(t_org("Block"))],
        ),
        d_org(
            "BlockDynamicFallback",
            GenTuDoc(""),
            bases=[t_nest(t_org("Block"))],
            fields=[
                str_field("name"),
            ],
        ),
        d_org("BlockExample", GenTuDoc("Example block"), bases=[t_nest(t_org("Block"))]),
        d_org(
            "BlockExport",
            GenTuDoc("Direct export passthrough"),
            bases=[t_nest(t_org("Block"))],
            fields=[
                str_field("exporter"),
                str_field("content"),
            ],
            methods=[
                GenTuFunction(
                    t_opt(t_str()),
                    "getPlacement",
                    org_doc("Return value of the :placement attribute if present"),
                    isConst=True,
                )
            ],
        ),
        d_org(
            "BlockAdmonition",
            GenTuDoc("Block of text with admonition tag: 'note',', 'warning','"),
            bases=[t_nest(t_org("Block"))],
        ),
        d_org("BlockCodeEvalResult",
              org_doc("Parsed results of code block evaluation"),
              bases=[t_nest(t_org("Block"))],
              fields=[
                  org_field(t_vec(t_nest_shared("OrgCodeEvalOutput")), "raw"),
                  id_field("Org", "node"),
              ]),
        d_org(
            "BlockCode",
            GenTuDoc("Base class for all code blocks"),
            bases=[t_nest(t_org("Block"))],
            methods=[
                GenTuFunction(
                    t_opt(t_nest_shared("AttrValue")),
                    "getVariable",
                    arguments=[arg_ident(t_cr(t_str()), "varname")],
                    isConst=True,
                ),
            ],
            fields=[
                org_field(
                    t_opt(t_str()),
                    "lang",
                    "Code block language name",
                    value="std::nullopt",
                ),
                vec_field(t_id("BlockCodeEvalResult"), "result",
                          "Code evaluation results"),
                vec_field(t_nest_shared("BlockCodeLine",), "lines",
                          "Collected code lines"),
                org_field(
                    t_nest_shared("AttrGroup"),
                    "switches",
                    "Dash-based switches for code block execution",
                ),
            ],
        ),
    ]


def get_sem_text():
    return [
        d_org("HashTag",
              bases=[t_nest(t_org("Inline"))],
              fields=[
                  org_field(t_nest_shared("HashTagText"), "text"),
              ]),
        d_org(
            "InlineFootnote",
            GenTuDoc(
                "Inline footnote definition",
                full=
                "\\note in-text link to the footnotes are implemented using `Link` nodes",
            ),
            bases=[t_nest(t_org("Inline"))],
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
        d_org("InlineExport",
              GenTuDoc("Inline export"),
              bases=[t_nest(t_org("Inline"))],
              fields=[
                  str_field("exporter"),
                  str_field("content"),
              ]),
        d_org(
            "Time",
            GenTuDoc("Single static or dynamic timestamp (active or inactive)"),
            bases=[t_nest(t_org("Org"))],
            fields=[
                GenTuField(t_bool(),
                           "isActive",
                           GenTuDoc("<active> vs [inactive]"),
                           value="false")
            ],
            methods=[
                GenTuFunction(t_opt(t_int()), "getYear", isConst=True),
                GenTuFunction(t_opt(t_int()), "getMonth", isConst=True),
                GenTuFunction(t_opt(t_int()), "getDay", isConst=True),
                GenTuFunction(t_opt(t_int()), "getHour", isConst=True),
                GenTuFunction(t_opt(t_int()), "getMinute", isConst=True),
                GenTuFunction(t_opt(t_int()), "getSecond", isConst=True),
                GenTuFunction(t_user_time(), "getStaticTime", isConst=True),
                # default_constructor_method("Time"),
            ],
            nested=[
                org_struct(
                    t_nest("Repeat", [t_org("Time")]),
                    GenTuDoc("Repetition information for static time"),
                    methods=[
                        default_constructor_method("Repeat"),
                    ],
                    nested=[
                        GenTuEnum(
                            t_nest("Mode", [t_org("Time"), t("Repeat")]),
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
                            t_nest("Period", [t_org("Time"), t("Repeat")]),
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
                            t_nest("Mode", [t_org("Time"), t("Repeat")]),
                            "mode",
                            GenTuDoc("mode"),
                        ),
                        GenTuField(
                            t_nest("Period", [t_org("Time"), t("Repeat")]),
                            "period",
                            GenTuDoc("period"),
                        ),
                        GenTuField(t_int(), "count", GenTuDoc("count")),
                    ],
                ),
                GenTuTypeGroup(
                    [
                        org_struct(
                            t_nest("Static", [t_org("Time")]),
                            GenTuDoc(""),
                            fields=[
                                vec_field(t_nest("Repeat", [t_org("Time")]), "repeat"),
                                opt_field(t_nest("Repeat", [t_org("Time")]), "warn"),
                                GenTuField(t_user_time(), "time"),
                            ],
                            methods=[
                                default_constructor_method("Static"),
                            ],
                        ),
                        org_struct(
                            t_nest("Dynamic", [t_org("Time")]),
                            GenTuDoc(""),
                            fields=[
                                GenTuField(t_nest_shared("LispCode"), "expr",
                                           GenTuDoc(""))
                            ],
                            methods=[
                                default_constructor_method("Dynamic"),
                            ],
                        ),
                    ],
                    kindGetter="getTimeKind",
                    enumName=t_nest("TimeKind", [t_org("Time")]),
                    variantField="time",
                    variantName=t_nest("TimeVariant", [t_org("Time")]),
                ),
            ],
        ),
        d_org(
            "TimeRange",
            GenTuDoc("Range of time delimited by two points"),
            bases=[t_nest(t_org("Org"))],
            fields=[
                id_field("Time", "from", GenTuDoc("Starting time")),
                id_field("Time", "to", GenTuDoc("Finishing time")),
            ],
            methods=[
                GenTuFunction(
                    t_opt(t("int64_t")),
                    "getClockedTimeSeconds",
                    isConst=True,
                ),
            ],
        ),
        d_org(
            "Macro",
            GenTuDoc("Inline macro invocation"),
            bases=[t_nest(t_org("Org"))],
            fields=[
                GenTuField(t_str(), "name", GenTuDoc("Macro name"), value='""'),
                org_field(
                    t_nest_shared("AttrGroup"),
                    "attrs",
                    GenTuDoc("Additional parameters aside from 'exporter',"),
                ),
            ],
        ),
        d_org(
            "Symbol",
            GenTuDoc("Text symbol or symbol command"),
            bases=[t_nest(t_org("Org"))],
            nested=[
                org_struct(
                    t_nest("Param", [t_org("Symbol")]),
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
                GenTuField(t_vec(t_nest("Param", [t_org("Symbol")])), "parameters",
                           GenTuDoc("Optional list of parameters")),
                GenTuField(t_vec(t_id()), "positional",
                           GenTuDoc("Positional parameters")),
            ],
        ),
        d_org("Escaped", GenTuDoc("Escaped text"), bases=[t_nest(t_org("Leaf"))]),
        d_org("Newline", GenTuDoc("\\n newline"), bases=[t_nest(t_org("Leaf"))]),
        d_org("Space", GenTuDoc('\' "space",'), bases=[t_nest(t_org("Leaf"))]),
        d_org("Word", GenTuDoc("word"), bases=[t_nest(t_org("Leaf"))]),
        d_org("AtMention", GenTuDoc("`@mention`"), bases=[t_nest(t_org("Leaf"))]),
        d_org("RawText", GenTuDoc(""), bases=[t_nest(t_org("Leaf"))]),
        d_org("Punctuation", GenTuDoc(""), bases=[t_nest(t_org("Leaf"))]),
        d_org("Placeholder", GenTuDoc(""), bases=[t_nest(t_org("Leaf"))]),
        d_org("BigIdent", GenTuDoc(""), bases=[t_nest(t_org("Leaf"))]),
        d_org("TextTarget", GenTuDoc("`<<target>>`"), bases=[t_nest(t_org("Leaf"))]),
        d_org(
            "Markup",
            GenTuDoc(""),
            bases=[t_nest(t_org("Org"))],
            IsAbstract=True,
        ),
        d_org("Bold", GenTuDoc(""), bases=[t_nest(t_org("Markup"))]),
        d_org("Underline", GenTuDoc(""), bases=[t_nest(t_org("Markup"))]),
        d_org("Monospace", GenTuDoc(""), bases=[t_nest(t_org("Markup"))]),
        d_org("MarkQuote", GenTuDoc(""), bases=[t_nest(t_org("Markup"))]),
        d_org("Verbatim", GenTuDoc(""), bases=[t_nest(t_org("Markup"))]),
        d_org("Italic", GenTuDoc(""), bases=[t_nest(t_org("Markup"))]),
        d_org("Strike", GenTuDoc(""), bases=[t_nest(t_org("Markup"))]),
        d_org("Par", GenTuDoc(""), bases=[t_nest(t_org("Markup"))]),
        d_org(
            "RadioTarget",
            GenTuDoc("`<<<target>>>`"),
            bases=[t_nest(t_org("Org"))],
            fields=[vec_field(t_str(), "words")],
        ),
        d_org("Latex", GenTuDoc("Latex code body"), bases=[t_nest(t_org("Org"))]),
        d_org(
            "Link",
            GenTuDoc(""),
            bases=[t_nest(t_org("Stmt"))],
            fields=[
                opt_field(t_id("Paragraph"), "description"),
                org_field(t_nest_shared("LinkTarget"), "target"),
            ],
        ),
    ]


def get_sem_subtree():
    return [
        d_org("SubtreeLog",
              GenTuDoc("Single subtree log entry"),
              bases=[t_nest(t_org("Org"))],
              methods=[
                  GenTuFunction(
                      t("void"),
                      "setDescription",
                      GenTuDoc(""),
                      arguments=[GenTuIdent(t_id("StmtList"), "desc")],
                  )
              ],
              fields=[
                  org_field(t_nest_shared("SubtreeLogHead"), "head"),
                  opt_field(
                      t_id("StmtList"),
                      "desc",
                      GenTuDoc("Optional description of the log entry"),
                  ),
              ]),
        d_org(
            "Subtree",
            GenTuDoc("Subtree"),
            bases=[t_nest(t_org("Org"))],
            fields=[
                GenTuField(t_int(), "level", GenTuDoc("Subtree level"), value="0"),
                opt_field(t_str(), "treeId", GenTuDoc(":ID: property")),
                opt_field(t_str(), "todo", GenTuDoc("Todo state of the tree")),
                opt_field(t_nest_shared("SubtreeCompletion"), "completion",
                          GenTuDoc("Task completion state")),
                opt_field(t_id("Paragraph"), "description", GenTuDoc("")),
                vec_field(t_id("HashTag"), "tags", GenTuDoc("Trailing tags")),
                id_field("Paragraph", "title", GenTuDoc("Main title")),
                vec_field(t_id("SubtreeLog"), "logbook",
                          GenTuDoc("Associated subtree log")),
                vec_field(t_nest_shared(t("NamedProperty"), []), "properties",
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
                    t_vec(t_nest_shared(t("SubtreePeriod"), [])),
                    "getTimePeriods",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(
                            QualType(
                                name="IntSet",
                                Parameters=[t_nest_shared("Kind", [t("SubtreePeriod")])],
                                Spaces=[n_hstd()],
                            ),
                            "kinds",
                        )
                    ],
                ),
                GenTuFunction(
                    t_vec(t_nest_shared(t("NamedProperty"), [])),
                    "getProperties",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "kind"),
                        GenTuIdent(t_cr(t_opt(t_str())), "subkind", value="std::nullopt"),
                    ],
                ),
                GenTuFunction(
                    t_opt(t_nest_shared(t("NamedProperty"), [])),
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
                        GenTuIdent(t_cr(t_nest_shared(t("NamedProperty"), [])), "value"),
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
                GenTuFunction(
                    t_str(),
                    "getCleanTitle",
                    GenTuDoc(
                        "Get subtree title as a flat string, without markup nodes, but with all left strings"
                    ),
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_str()),
                    "getTodoKeyword",
                    GenTuDoc(""),
                    isConst=True,
                ),
            ],
        )
    ]


def get_shared_sem_enums() -> Sequence[GenTuEnum]:
    return [
        d_simple_enum(
            t("CheckboxState"),
            GenTuDoc(""),
            "None",
            "Done",
            "Empty",
            "Partial",
        ),
        d_simple_enum(
            t("SubtreeTodoSource"),
            org_doc("Where to take todo completion statistics from"),
            efield("Checkbox", "Only count checkbox subnodes as a progress completion"),
            efield("Todo", "Use subtrees with todo keywords"),
            efield("Both", "Use both subtrees and todo keywords"),
        ),
        d_simple_enum(
            t("ListFormattingMode"), GenTuDoc(""),
            efield("None", "Default, no custom formatting"),
            efield("Table1D1Col", "one column, each table item is an individual row"),
            efield("Table1D2Col",
                   "for description lists, treat header row as an individual column"),
            efield(
                "Table2DColFirst",
                "for tables tables with arbitrary column count, treat the first level of items as "
                "column names, treat all nested elements in these columns as row values"),
            efield(
                "Table2DRowFirst",
                "for tables with arbitrary column count, each top-level list item is an individual "
                "row, then each item in the nested list is a cell on this row.")),
        d_simple_enum(
            t("InitialSubtreeVisibility"),
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
    ]


def get_shared_sem_types() -> Sequence[GenTuStruct]:
    cell_format_enum = GenTuEnum(
        t_nest_shared("Flag", [t("Tblfm"), t("Assign")]),
        org_doc("Flags for table format expression cell formulas"),
        fields=[
            efield("CellLeftAlign", "Left-align the result"),
            efield("CellRightAlign", "Right-align the result"),
            efield("CellCenterAlign", "Center-align the result"),
            efield("CellNumber", "Convert result to number/currency format"),
            efield("CellExponential", "Use exponential notation for numbers"),
            efield("CellFloating", "Use floating point format"),
            efield("CellUnformat", "Unformat values before calculating"),
            efield("CellText", "Convert result to text"),
            efield("CellBool", "Display boolean values as t/nil"),
            efield("CellDecimal",
                   "Fixed format with specified decimal places (e.g., ;D2)"),
            efield("CellPercentage", "Percentage format"),
            efield("CellHours", "Convert to hours/minutes (HH:MM)"),
            efield("CellZero", "Display zero as empty cell"),
            efield("CellMarkInvalid", "Mark field as invalid if conversion fails"),
            efield("CellQuote", "Quote field contents"),
        ])

    axis_ref_types = org_struct(
        t_nest_shared("Position",
                      [t("Tblfm"), t("Expr"), t("AxisRef")]),
        methods=[
            eq_method(t_nest_shared(
                "Position", [t("Tblfm"), t("Expr"), t("AxisRef")]))
        ],
        nested=[
            GenTuTypeGroup(
                [
                    org_struct(
                        t_nest_shared(
                            "Index", [t("Tblfm"),
                                      t("Expr"),
                                      t("AxisRef"),
                                      t("Position")]),
                        fields=[org_field(t_int(), "index")],
                        methods=[
                            eq_method(
                                t_nest_shared(
                                    "Index",
                                    [t("Tblfm"),
                                     t("Expr"),
                                     t("AxisRef"),
                                     t("Position")]))
                        ],
                        nested=[default_constructor("Index")],
                    ),
                    org_struct(
                        t_nest_shared(
                            "Name", [t("Tblfm"),
                                     t("Expr"),
                                     t("AxisRef"),
                                     t("Position")]),
                        fields=[str_field("name")],
                        methods=[
                            eq_method(
                                t_nest_shared(
                                    "Name",
                                    [t("Tblfm"),
                                     t("Expr"),
                                     t("AxisRef"),
                                     t("Position")]))
                        ],
                        nested=[default_constructor("Name")],
                    ),
                ],
                enumName=t_nest_shared(
                    "Kind",
                    [t("Tblfm"), t("Expr"),
                     t("AxisRef"), t("Position")]),
                variantName=t_nest_shared(
                    "Data",
                    [t("Tblfm"), t("Expr"),
                     t("AxisRef"), t("Position")]),
            ),
            default_constructor("Position"),
        ],
    )

    return [
        org_struct(t_nest_shared("SourceLocation"),
                   methods=[
                       eq_method(t_nest_shared("SourceLocation")),
                       default_constructor_method("SourceLocation"),
                   ],
                   fields=[
                       org_field(t_int(), "line", value="-1"),
                       opt_field(t_int(), "column"),
                       opt_field(t_str(), "file"),
                   ]),
        org_struct(
            t_nest_shared("LispCode"),
            methods=[
                eq_method(t_nest_shared("LispCode")),
                default_constructor_method("LispCode"),
            ],
            nested=[
                GenTuTypeGroup(
                    [
                        org_struct(
                            t_nest_shared("Call", [t("LispCode")]),
                            fields=[
                                str_field("name"),
                                vec_field(t_nest_shared("LispCode"), "args"),
                            ],
                            methods=[
                                eq_method(t_nest_shared("Call", [t("LispCode")])),
                                default_constructor_method("Call"),
                            ],
                        ),
                        org_struct(
                            t_nest_shared("List", [t("LispCode")]),
                            fields=[
                                vec_field(t_nest_shared("LispCode"), "items"),
                            ],
                            methods=[
                                eq_method(t_nest_shared("List", [t("LispCode")])),
                                default_constructor_method("List"),
                            ],
                        ),
                        org_struct(
                            t_nest_shared("KeyValue", [t("LispCode")]),
                            fields=[
                                str_field("name"),
                                vec_field(t_nest_shared("LispCode"), "value")
                            ],
                            methods=[
                                eq_method(t_nest_shared("KeyValue", [t("LispCode")])),
                                default_constructor_method("KeyValue"),
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Number", [t("LispCode")]),
                            fields=[
                                int_field("value"),
                            ],
                            methods=[
                                eq_method(t_nest_shared("Number", [t("LispCode")])),
                                default_constructor_method("Number"),
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Text", [t("LispCode")]),
                            fields=[
                                str_field("value"),
                            ],
                            methods=[
                                eq_method(t_nest_shared("Text", [t("LispCode")])),
                                default_constructor_method("Text"),
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Ident", [t("LispCode")]),
                            fields=[
                                str_field("name"),
                            ],
                            methods=[
                                eq_method(t_nest_shared("Ident", [t("LispCode")])),
                                default_constructor_method("Ident"),
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Boolean", [t("LispCode")]),
                            fields=[
                                bool_field("value"),
                            ],
                            methods=[
                                eq_method(t_nest_shared("Boolean", [t("LispCode")])),
                                default_constructor_method("Boolean"),
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Real", [t("LispCode")]),
                            fields=[
                                org_field(t("float"), "value"),
                            ],
                            methods=[
                                eq_method(t_nest_shared("Real", [t("LispCode")])),
                                default_constructor_method("Real"),
                            ],
                        ),
                    ],
                    enumName=t_nest_shared("Kind", [t("LispCode")]),
                    variantName=t_nest_shared("Data", [t("LispCode")]),
                )
            ],
        ),
        org_struct(
            t_nest_shared("Tblfm"),
            fields=[
                vec_field(t_nest_shared("Assign", [t("Tblfm")]), "exprs"),
            ],
            nested=[
                org_struct(
                    t_nest_shared("Expr", [t("Tblfm")]),
                    nested=[
                        GenTuTypeGroup(
                            [
                                org_struct(
                                    t_nest_shared("AxisRef",
                                                  [t("Tblfm"), t("Expr")]),
                                    nested=[axis_ref_types],
                                    fields=[
                                        org_field(
                                            t_nest_shared(
                                                "Position",
                                                [t("Tblfm"),
                                                 t("Expr"),
                                                 t("AxisRef")]), "col"),
                                        opt_field(
                                            t_nest_shared(
                                                "Position",
                                                [t("Tblfm"),
                                                 t("Expr"),
                                                 t("AxisRef")]), "row"),
                                    ],
                                    methods=[
                                        eq_method(
                                            t_nest_shared(
                                                "AxisRef",
                                                [t("Tblfm"), t("Expr")])),
                                    ],
                                ),
                                org_struct(
                                    t_nest_shared("AxisName",
                                                  [t("Tblfm"), t("Expr")]),
                                    fields=[str_field("name")],
                                    methods=[
                                        eq_method(
                                            t_nest_shared(
                                                "AxisName",
                                                [t("Tblfm"), t("Expr")]))
                                    ],
                                ),
                                org_struct(
                                    t_nest_shared("IntLiteral",
                                                  [t("Tblfm"), t("Expr")]),
                                    fields=[org_field(t_int(), "value")],
                                    methods=[
                                        eq_method(
                                            t_nest_shared(
                                                "IntLiteral",
                                                [t("Tblfm"), t("Expr")]))
                                    ],
                                ),
                                org_struct(
                                    t_nest_shared("FloatLiteral",
                                                  [t("Tblfm"), t("Expr")]),
                                    fields=[org_field(t("float"), "value")],
                                    methods=[
                                        eq_method(
                                            t_nest_shared(
                                                "FloatLiteral",
                                                [t("Tblfm"), t("Expr")]))
                                    ],
                                ),
                                org_struct(
                                    t_nest_shared("RangeRef",
                                                  [t("Tblfm"), t("Expr")]),
                                    fields=[
                                        opt_field(
                                            t_nest_shared(
                                                "AxisRef",
                                                [t("Tblfm"), t("Expr")]), "first"),
                                        opt_field(
                                            t_nest_shared(
                                                "AxisRef",
                                                [t("Tblfm"), t("Expr")]), "last"),
                                    ],
                                    methods=[
                                        eq_method(
                                            t_nest_shared(
                                                "RangeRef",
                                                [t("Tblfm"), t("Expr")])),
                                    ],
                                ),
                                org_struct(
                                    t_nest_shared("Call",
                                                  [t("Tblfm"), t("Expr")]),
                                    fields=[
                                        str_field("name"),
                                        vec_field(t_nest_shared(t("Expr"), [t("Tblfm")]),
                                                  "args"),
                                    ],
                                    methods=[
                                        eq_method(
                                            t_nest_shared("Call", [t("Tblfm"),
                                                                   t("Expr")])),
                                    ],
                                ),
                                org_struct(
                                    t_nest_shared("Elisp",
                                                  [t("Tblfm"), t("Expr")]),
                                    fields=[
                                        str_field("value"),
                                    ],
                                    methods=[
                                        eq_method(
                                            t_nest_shared(
                                                "Elisp",
                                                [t("Tblfm"), t("Expr")])),
                                    ],
                                ),
                            ],
                            enumName=t_nest_shared("Kind",
                                                   [t("Tblfm"), t("Expr")]),
                            variantName=t_nest_shared("Data",
                                                      [t("Tblfm"), t("Expr")]),
                        )
                    ],
                    methods=[
                        eq_method(t_nest_shared("Expr", [t("Tblfm")])),
                    ],
                ),
                org_struct(
                    t_nest_shared("Assign", [t("Tblfm")]),
                    nested=[cell_format_enum],
                    fields=[
                        org_field(t_nest_shared("AxisRef",
                                                [t("Tblfm"), t("Expr")]), "target"),
                        vec_field(t_nest_shared("Expr", [t("Tblfm")]), "expr"),
                        vec_field(t_nest_shared("Flag",
                                                [t("Tblfm"), t("Assign")]), "flags"),
                    ],
                    methods=[
                        eq_method(t_nest_shared("Assign", [t("Tblfm")])),
                    ]),
            ],
            methods=[
                eq_method(t_nest_shared("Tblfm")),
            ]),
        org_struct(
            t_nest_shared("AttrValue"),
            nested=[
                org_struct(t_nest_shared("DimensionSpan", [t("AttrValue")]),
                           fields=[
                               int_field("first"),
                               opt_field(t_int(), "last"),
                           ],
                           methods=[
                               default_constructor_method("DimensionSpan"),
                               eq_method(t_nest_shared("DimensionSpan",
                                                       [t("AttrValue")])),
                           ]),
                GenTuTypeGroup(
                    [
                        org_struct(
                            t_nest_shared("TextValue", [t("AttrValue")]),
                            fields=[
                                str_field("value"),
                            ],
                            methods=[
                                eq_method(t_nest_shared("TextValue", [t("AttrValue")])),
                                default_constructor_method("TextValue"),
                            ],
                        ),
                        org_struct(
                            t_nest_shared("FileReference", [t("AttrValue")]),
                            fields=[
                                str_field("file"),
                                str_field("reference"),
                            ],
                            methods=[
                                default_constructor_method("FileReference"),
                                eq_method(t_nest_shared("FileReference",
                                                        [t("AttrValue")])),
                            ],
                        ),
                        org_struct(
                            t_nest_shared("LispValue", [t("AttrValue")]),
                            fields=[
                                org_field(t_nest_shared("LispCode"), "code"),
                            ],
                            methods=[
                                eq_method(t_nest_shared("LispValue", [t("AttrValue")])),
                                default_constructor_method("LispValue"),
                            ],
                        ),
                    ],
                    kindGetter="getKind",
                    enumName=t_nest_shared("Kind", [t("AttrValue")]),
                    variantField="data",
                    variantName=t_nest_shared("DataVariant", [t("AttrValue")]),
                )
            ],
            fields=[
                opt_field(t_str(), "name"),
                opt_field(t_str(), "varname"),
                vec_field(t_nest_shared("DimensionSpan", [t("AttrValue")]), "span"),
                bool_field(
                    "isQuoted",
                    "If the original value was explicitly quoted in the org-mode code"),
            ],
            methods=[
                org_function(t_opt(t_bool()), "getBool", isConst=True),
                org_function(t_opt(t_int()), "getInt", isConst=True),
                org_function(t_str(), "getString", isConst=True),
                org_function(t_opt(QualType(name="double")), "getDouble", isConst=True),
                eq_method(t_nest_shared("AttrValue")),
                default_constructor_method("AttrValue")
            ],
        ),
        org_struct(
            t_nest_shared("HashTagFlat"),
            fields=[vec_field(t_str(), "tags")],
            methods=[
                eq_method(t_nest_shared("HashTagFlat")),
                org_function(
                    result=t_bool(),
                    name="operator<",
                    arguments=[arg_ident(t_cr(t_nest_shared("HashTagFlat")), "other")],
                    isConst=True,
                ),
            ],
        ),
        org_struct(
            t_nest_shared("TodoKeyword"),
            fields=[
                str_field("name"),
                opt_field(t_str(), "shortcut"),
                org_field(t_nest_shared("Transition", [t("TodoKeyword")]), "onEnter"),
                org_field(t_nest_shared("Transition", [t("TodoKeyword")]), "onLeave"),
            ],
            nested=[
                d_simple_enum(
                    t_nest_shared("Transition", [t("TodoKeyword")]),
                    GenTuDoc(""),
                    efield("None"),
                    efield("NoteWithTimestamp"),
                    efield("Timestamp"),
                ),
            ],
            methods=[
                eq_method(t_nest_shared("TodoKeyword")),
            ],
        ),
        org_struct(
            t_nest_shared("HashTagText"),
            org_doc("Single or nested inline hash-tag"),
            fields=[
                org_field(t_str(), "head", org_doc("Main part of the tag")),
                org_field(
                    t_vec(t_nest_shared("HashTagText")),
                    "subtags",
                    org_doc("List of nested tags"),
                    value="{}",
                ),
            ],
            methods=[
                eq_method(t_nest_shared("HashTagText")),
                org_function(
                    t("bool"),
                    "prefixMatch",
                    org_doc(
                        "Check if list of tag names is a prefix for either of the nested hash tags in this one"
                    ),
                    isConst=True,
                    arguments=[arg_ident(t_cr(t_vec(t_str())), "prefix")],
                ),
                org_function(
                    t_vec(t_nest_shared("HashTagFlat")),
                    "getFlatHashes",
                    arguments=[arg_ident(t_bool(), "withIntermediate", value="true")],
                    isConst=True,
                    doc=org_doc("Get flat list of expanded hashtags"),
                ),
            ],
        ),
        org_struct(
            t_nest_shared("SubtreePath"),
            fields=[
                vec_field(t_str(), "path"),
            ],
            methods=[
                eq_method(t_nest_shared("SubtreePath")),
            ],
        ),
        org_struct(
            t_nest_shared("LinkTarget"),
            methods=[eq_method(t_nest_shared("LinkTarget"))],
            nested=[
                GenTuTypeGroup(
                    [
                        org_struct(
                            t_nest_shared("Raw", [t("LinkTarget")]),
                            org_doc(""),
                            fields=[(GenTuField(t_str(), "text", GenTuDoc("")))],
                            methods=[eq_method(t_nest_shared("Raw", [t("LinkTarget")]))],
                        ),
                        org_struct(
                            t_nest_shared("Id", [t("LinkTarget")]),
                            GenTuDoc(""),
                            fields=[(GenTuField(t_str(), "text", GenTuDoc("")))],
                            methods=[eq_method(t_nest_shared("Id", [t("LinkTarget")]))],
                        ),
                        org_struct(
                            t_nest_shared("CustomId", [t("LinkTarget")]),
                            GenTuDoc(""),
                            fields=[(GenTuField(t_str(), "text", GenTuDoc("")))],
                            methods=[
                                eq_method(t_nest_shared("CustomId", [t("LinkTarget")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("SubtreeTitle", [t("LinkTarget")]),
                            fields=[
                                org_field(t_nest_shared("SubtreePath"), "title"),
                                org_field(t_int(), "level"),
                            ],
                            methods=[
                                eq_method(t_nest("SubtreeTitle", [t("LinkTarget")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Person", [t("LinkTarget")]),
                            GenTuDoc(""),
                            fields=[(GenTuField(t_str(), "name", GenTuDoc("")))],
                            methods=[
                                eq_method(t_nest_shared("Person", [t("LinkTarget")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("UserProtocol", [t("LinkTarget")]),
                            GenTuDoc(""),
                            fields=[
                                GenTuField(t_str(), "protocol", GenTuDoc("")),
                                GenTuField(t_str(), "target", GenTuDoc("")),
                            ],
                            methods=[
                                eq_method(t_nest_shared("UserProtocol",
                                                        [t("LinkTarget")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Internal", [t("LinkTarget")]),
                            GenTuDoc(""),
                            fields=[
                                GenTuField(t_str(), "target", GenTuDoc("")),
                            ],
                            methods=[
                                eq_method(t_nest_shared("Internal", [t("LinkTarget")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Footnote", [t("LinkTarget")]),
                            GenTuDoc(""),
                            fields=[(GenTuField(t_str(), "target", GenTuDoc("")))],
                            methods=[
                                eq_method(t_nest_shared("Footnote", [t("LinkTarget")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("File", [t("LinkTarget")]),
                            GenTuDoc(""),
                            fields=[(GenTuField(t_str(), "file", GenTuDoc("")))],
                            methods=[eq_method(t_nest_shared("File", [t("LinkTarget")]))],
                        ),
                        org_struct(
                            t_nest_shared("Attachment", [t("LinkTarget")]),
                            GenTuDoc(""),
                            fields=[(GenTuField(t_str(), "file", GenTuDoc("")))],
                            methods=[
                                eq_method(t_nest_shared("Attachment", [t("LinkTarget")]))
                            ],
                        ),
                    ],
                    kindGetter="getKind",
                    variantName=t_nest_shared("Data", [t("LinkTarget")]),
                    enumName=t_nest_shared("Kind", [t("LinkTarget")]),
                )
            ]),
        org_struct(
            t_nest_shared("SubtreeLogHead"),
            methods=[eq_method(t_nest_shared("SubtreeLogHead"))],
            nested=[
                GenTuTypeGroup(
                    [
                        org_struct(
                            t_nest_shared("Priority", [t("SubtreeLogHead")]),
                            GenTuDoc("Priority added"),
                            methods=[
                                eq_method(t_nest("Priority", [t("SubtreeLogHead")])),
                            ],
                            nested=[
                                GenTuEnum(
                                    t_nest_shared("Action",
                                                  [t("SubtreeLogHead"),
                                                   t("Priority")]),
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
                                    t_space("string", [t_namespace("std")]),
                                    "oldPriority",
                                    GenTuDoc("Previous priority for change and removal"),
                                ),
                                opt_field(
                                    t_space("string", [t_namespace("std")]),
                                    "newPriority",
                                    GenTuDoc("New priority for change and addition"),
                                ),
                                org_field(t_user_time(), "on",
                                          GenTuDoc("When priority was changed")),
                                GenTuField(
                                    t_nest_shared("Action",
                                                  [t("SubtreeLogHead"),
                                                   t("Priority")]), "action",
                                    GenTuDoc("Which action taken")),
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Note", [t("SubtreeLogHead")]),
                            GenTuDoc("Timestamped note"),
                            fields=[
                                org_field(t_user_time(), "on",
                                          GenTuDoc("Where log was taken"))
                            ],
                            nested=[GenTuPass("Note() {}")],
                            methods=[
                                eq_method(t_nest_shared("Note", [t("SubtreeLogHead")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Refile", [t("SubtreeLogHead")]),
                            GenTuDoc("Refiling action"),
                            fields=[
                                org_field(t_user_time(), "on",
                                          GenTuDoc("When the refiling happened")),
                                org_field(t_nest_shared("LinkTarget"), "from",
                                          GenTuDoc("Link to the original subtree")),
                            ],
                            nested=[GenTuPass("Refile() {}")],
                            methods=[
                                eq_method(t_nest_shared("Refile", [t("SubtreeLogHead")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Clock", [t("SubtreeLogHead")]),
                            GenTuDoc(
                                "Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`"
                            ),
                            fields=[
                                org_field(t_user_time(), "from",
                                          GenTuDoc("Clock start time")),
                                opt_field(t_user_time(), "to",
                                          GenTuDoc("Optional end of the clock")),
                            ],
                            nested=[GenTuPass("Clock() {}")],
                            methods=[
                                eq_method(t_nest_shared("Clock", [t("SubtreeLogHead")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("State", [t("SubtreeLogHead")]),
                            GenTuDoc(
                                'Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`'
                            ),
                            fields=[
                                org_field(t_str(), "from", GenTuDoc("")),
                                org_field(t_str(), "to", GenTuDoc("")),
                                org_field(t_user_time(), "on", GenTuDoc("")),
                            ],
                            nested=[GenTuPass("State() {}")],
                            methods=[
                                eq_method(t_nest_shared("State", [t("SubtreeLogHead")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Deadline", [t("SubtreeLogHead")]),
                            GenTuDoc('Change of the subtree deadline'),
                            fields=[
                                opt_field(t_user_time(), "from", GenTuDoc("")),
                                org_field(t_user_time(), "to", GenTuDoc("")),
                                org_field(t_user_time(), "on", GenTuDoc("")),
                            ],
                            nested=[GenTuPass("Deadline() {}")],
                            methods=[
                                eq_method(t_nest_shared("Deadline",
                                                        [t("SubtreeLogHead")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Schedule", [t("SubtreeLogHead")]),
                            GenTuDoc('Change of the subtree Schedule'),
                            fields=[
                                opt_field(t_user_time(), "from", GenTuDoc("")),
                                org_field(t_user_time(), "to", GenTuDoc("")),
                                org_field(t_user_time(), "on", GenTuDoc("")),
                            ],
                            nested=[GenTuPass("Schedule() {}")],
                            methods=[
                                eq_method(t_nest_shared("Schedule",
                                                        [t("SubtreeLogHead")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Tag", [t("SubtreeLogHead")]),
                            GenTuDoc(
                                'Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`'
                            ),
                            fields=[
                                org_field(t_user_time(), "on",
                                          GenTuDoc("When the log was assigned")),
                                org_field(t_nest_shared("HashTagText"), "tag",
                                          GenTuDoc("Tag in question")),
                                GenTuField(t_bool(),
                                           "added",
                                           GenTuDoc("Added/removed?"),
                                           value="false"),
                            ],
                            nested=[GenTuPass("Tag() {}")],
                            methods=[
                                eq_method(t_nest_shared("Tag", [t("SubtreeLogHead")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("Unknown", [t("SubtreeLogHead")]),
                            GenTuDoc("Unknown subtree log entry kind"),
                            fields=[],
                            nested=[GenTuPass("Unknown() {}")],
                            methods=[
                                eq_method(t_nest_shared("Unknown", [t("SubtreeLogHead")]))
                            ],
                        ),
                    ],
                    kindGetter="getLogKind",
                    variantField="log",
                    variantValue="Note{}",
                    variantName=t_nest_shared("LogEntry", [t("SubtreeLogHead")]),
                    enumName=t_nest_shared("Kind", [t("SubtreeLogHead")]),
                ),
            ]),
        org_struct(
            t_nest_shared("SubtreeCompletion"),
            GenTuDoc("Completion status of the subtree list element"),
            fields=[
                GenTuField(
                    t_int(),
                    "done",
                    GenTuDoc("Number of completed tasks"),
                    value="0",
                ),
                GenTuField(
                    t_int(),
                    "full",
                    GenTuDoc("Full number of tasks"),
                    value="0",
                ),
                GenTuField(
                    t_bool(),
                    "isPercent",
                    GenTuDoc("Use fraction or percent to display completion"),
                    value="false",
                ),
            ],
            methods=[eq_method(t_nest_shared("SubtreeCompletion"))],
        ),
        org_struct(
            t_nest_shared("AttrList"),
            fields=[
                vec_field(t_nest_shared("AttrValue"), "items"),
            ],
            methods=[eq_method(t_nest_shared("AttrList"))],
        ),
        org_struct(
            t_nest_shared("AttrGroup"),
            fields=[
                org_field(
                    t_nest_shared("AttrList"),
                    "positional",
                    GenTuDoc("Positional arguments with no keys"),
                ),
                org_field(
                    t_map(t_str(), t_nest_shared("AttrList")),
                    "named",
                    GenTuDoc("Stored key-value mapping"),
                ),
            ],
            methods=[
                GenTuFunction(
                    t_vec(t_nest_shared("AttrValue")),
                    "getFlatArgs",
                    isConst=True,
                ),
                GenTuFunction(
                    t_vec(t_nest_shared("AttrValue")),
                    "getAttrs",
                    GenTuDoc(""),
                    arguments=[opt_ident(t_str(), "key", GenTuDoc(""))],
                    isConst=True,
                ),
                GenTuFunction(
                    t("void"),
                    "setNamedAttr",
                    GenTuDoc(""),
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "key"),
                        GenTuIdent(t_cr(t_vec(t_nest_shared("AttrValue"))), "attrs"),
                    ],
                ),
                GenTuFunction(
                    t("void"),
                    "setPositionalAttr",
                    GenTuDoc(""),
                    arguments=[
                        GenTuIdent(t_cr(t_vec(t_nest_shared("AttrValue"))), "items"),
                    ],
                ),
                GenTuFunction(
                    t_int(),
                    "getPositionalSize",
                    isConst=True,
                ),
                GenTuFunction(
                    t_int(),
                    "getNamedSize",
                    isConst=True,
                ),
                GenTuFunction(
                    t_bool(),
                    "isEmpty",
                    isConst=True,
                ),
                GenTuFunction(
                    t_nest_shared("AttrList"),
                    "getAll",
                    isConst=True,
                ),
                GenTuFunction(
                    t_cr(t_nest_shared("AttrValue")),
                    "atPositional",
                    arguments=[GenTuIdent(t_int(), "index")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_nest_shared("AttrValue")),
                    "getPositional",
                    arguments=[GenTuIdent(t_int(), "index")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_cr(t_nest_shared("AttrList")),
                    "atNamed",
                    arguments=[GenTuIdent(t_cr(t_str()), "index")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_nest_shared("AttrList")),
                    "getNamed",
                    arguments=[GenTuIdent(t_cr(t_str()), "index")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_cr(t_nest_shared("AttrValue")),
                    "atFirstNamed",
                    arguments=[GenTuIdent(t_cr(t_str()), "index")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_nest_shared("AttrValue")),
                    "getFirstNamed",
                    arguments=[GenTuIdent(t_cr(t_str()), "index")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_nest_shared("AttrList"),
                    "atVarNamed",
                    arguments=[GenTuIdent(t_cr(t_str()), "index")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_nest_shared("AttrList")),
                    "getVarNamed",
                    arguments=[GenTuIdent(t_cr(t_str()), "index")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_nest_shared("AttrValue"),
                    "atFirstVarNamed",
                    arguments=[GenTuIdent(t_cr(t_str()), "index")],
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_nest_shared("AttrValue")),
                    "getFirstVarNamed",
                    arguments=[GenTuIdent(t_cr(t_str()), "index")],
                    isConst=True,
                ),
                eq_method(t_nest_shared("AttrGroup")),
            ],
        ),
        org_struct(
            t_nest_shared("OrgCodeEvalInput"),
            methods=[
                eq_method(t_nest_shared("OrgCodeEvalInput")),
                org_function(
                    t_opt(t_nest_shared("Var", [t("OrgCodeEvalInput")])),
                    "getVariable",
                    arguments=[GenTuIdent(t_cr(t_str()), "name")],
                    isConst=True,
                ),
            ],
            fields=[
                org_field(t_nest_shared("AttrGroup"), "blockAttrs"),
                org_field(t_str(), "tangledCode"),
                opt_field(t_str(), "exportType"),
                org_field(
                    t_nest_shared("ResultType", [t("OrgCodeEvalInput")]),
                    "resultType",
                    value="ResultType::None",
                ),
                org_field(
                    t_nest_shared("ResultFormat", [t("OrgCodeEvalInput")]),
                    "resultFormat",
                    value="ResultFormat::None",
                ),
                org_field(
                    t_nest_shared("ResultHandling", [t("OrgCodeEvalInput")]),
                    "resultHandling",
                    value="ResultHandling::None",
                ),
                str_field("language"),
                vec_field(t_nest_shared("Var", [t("OrgCodeEvalInput")]), "argList"),
            ],
            nested=[
                org_struct(t_nest_shared("Var", [t("OrgCodeEvalInput")]),
                           fields=[
                               str_field("name"),
                               org_field(t_nest_shared("OrgJson"), "value"),
                           ],
                           methods=[
                               eq_method(t_nest_shared("Var", [t("OrgCodeEvalInput")])),
                               default_constructor_method("Var"),
                           ]),
                d_simple_enum(
                    t_nest_shared("ResultType", [t("OrgCodeEvalInput")]),
                    "What context to use for results",
                    efield("None"),
                    efield(
                        "Table",
                        "Interpret the results as an Org table. If the result is a single value, create a table with one row and one column."
                    ),
                    efield(
                        "List",
                        "Interpret the results as an Org list. If the result is a single value, create a list of one element."
                    ),
                    efield(
                        "Scalar",
                        "Interpret literally and insert as quoted text. Do not create a table."
                    ),
                    efield(
                        "SaveFile",
                        "Interpret as a filename. Save the results of execution of the code block to that file, then insert a link to it."
                    ),
                ),
                d_simple_enum(
                    t_nest_shared("ResultFormat", [t("OrgCodeEvalInput")]),
                    "How to interpret output from the script",
                    efield("None"),
                    efield(
                        "Raw",
                        "Interpreted as raw Org mode. Inserted directly into the buffer."
                    ),
                    efield("Code", "Result enclosed in a code block."),
                    efield(
                        "Drawer",
                        "Results are added directly to the Org file as with ‘raw’, but are wrapped in a ‘RESULTS’ drawer or results macro (for inline code blocks), for later scripting and automated processing."
                    ),
                    efield("ExportType", "Results enclosed in a ‘BEGIN_EXPORT’ block."),
                    efield("Link"),
                ),
                d_simple_enum(
                    t_nest_shared("ResultHandling", [t("OrgCodeEvalInput")]),
                    "What to do with the final evaluation results",
                    efield("None"),
                    efield("Replace"),
                    efield("Silent"),
                    efield("Discard"),
                    efield("Append"),
                    efield("Prepend"),
                ),
            ],
        ),
        org_struct(
            t_nest_shared("OrgCodeEvalOutput"),
            doc="Single command/subprocess executed to evaluate org babel code entry",
            fields=[
                str_field("stdoutText"),
                str_field("stderrText"),
                int_field("code"),
                opt_field(
                    t_str(), "cmd",
                    "Command evaluated, if none then eval output did not run CLI subprocess"
                ),
                vec_field(
                    t_str(),
                    "args",
                    "Command line arguments provided for execution",
                ),
                str_field("cwd", "Working directory where command was executed"),
                org_field(
                    t_nest_shared("AttrGroup"),
                    "appliedHeaderArg",
                    "Final set of header arguments applied during evaluation",
                ),
            ],
            methods=[
                eq_method(t_nest_shared("OrgCodeEvalOutput")),
            ]),
        org_struct(
            t_nest_shared("ColumnView"),
            methods=[eq_method(t_nest_shared("ColumnView"))],
            fields=[vec_field(t_nest_shared("Column", [t("ColumnView")]), "columns")],
            nested=[
                org_struct(
                    t_nest_shared("Summary", [t("ColumnView")]),
                    methods=[eq_method(t_nest_shared("Summary", [t("ColumnView")]))],
                    nested=[
                        GenTuTypeGroup(
                            [
                                org_struct(
                                    t_nest_shared(
                                        "CheckboxAggregate",
                                        [t("ColumnView"), t("Summary")]),
                                    nested=[
                                        GenTuEnum(
                                            t_nest_shared("Kind", [
                                                t("ColumnView"),
                                                t("Summary"),
                                                t("CheckboxAggregate"),
                                            ]),
                                            GenTuDoc(""),
                                            fields=[
                                                efield("IfAllNested"),
                                                efield("AggregateFractionRec"),
                                                efield("AggregatePercentRec"),
                                            ],
                                        )
                                    ],
                                    fields=[
                                        org_field(
                                            t_nest_shared("Kind", [
                                                t("ColumnView"),
                                                t("Summary"),
                                                t("CheckboxAggregate"),
                                            ]), "kind"),
                                    ],
                                    methods=[
                                        eq_method(
                                            t_nest_shared("CheckboxAggregate",
                                                          [t("ColumnView"),
                                                           t("Summary")]))
                                    ],
                                ),
                                org_struct(
                                    t_nest_shared("MathAggregate",
                                                  [t("ColumnView"),
                                                   t("Summary")]),
                                    nested=[
                                        GenTuEnum(
                                            t_nest_shared("Kind", [
                                                t("ColumnView"),
                                                t("Summary"),
                                                t("MathAggregate"),
                                            ]),
                                            GenTuDoc(""),
                                            fields=[
                                                efield("Min"),
                                                efield("Max"),
                                                efield("Mean"),
                                                efield("Sum"),
                                                efield("LowHighEst"),
                                            ],
                                        ),
                                    ],
                                    fields=[
                                        org_field(
                                            t_nest_shared("Kind", [
                                                t("ColumnView"),
                                                t("Summary"),
                                                t("MathAggregate"),
                                            ]), "kind"),
                                        opt_field(t_int(), "formatDigits"),
                                        opt_field(t_int(), "formatPrecision"),
                                    ],
                                    methods=[
                                        eq_method(
                                            t_nest_shared("MathAggregate", [
                                                t("ColumnView"),
                                                t("Summary"),
                                            ])),
                                    ])
                            ],
                            enumName=t_nest_shared(
                                "Kind", [t("ColumnView"), t("Summary")]),
                            variantName=t_nest_shared(
                                "Data", [t("ColumnView"), t("Summary")]),
                        ),
                    ],
                ),
                org_struct(
                    t_nest_shared("Column", [t("ColumnView")]),
                    fields=[
                        opt_field(t_nest_shared("Summary", [t("ColumnView")]), "summary"),
                        opt_field(t_int(), "width"),
                        opt_field(t_str(), "property"),
                        opt_field(t_str(), "propertyTitle"),
                    ],
                    methods=[eq_method(t_nest_shared("Column", [t("ColumnView")]))],
                ),
            ],
        ),
        org_struct(
            t_nest_shared("BlockCodeLine"),
            methods=[eq_method(t_nest_shared("BlockCodeLine"))],
            nested=[
                org_struct(
                    t_nest_shared("Part", [t("BlockCodeLine")]),
                    methods=[eq_method(t_nest_shared("Part", [t("BlockCodeLine")]))],
                    nested=[
                        GenTuTypeGroup(
                            [
                                org_struct(
                                    t_nest_shared("Raw", [
                                        t("BlockCodeLine"),
                                        t("Part"),
                                    ]),
                                    fields=[GenTuField(t_str(), "code")],
                                    methods=[
                                        eq_method(
                                            t_nest_shared("Raw", [
                                                t("BlockCodeLine"),
                                                t("Part"),
                                            ]))
                                    ],
                                ),
                                org_struct(
                                    t_nest_shared("Callout", [
                                        t("BlockCodeLine"),
                                        t("Part"),
                                    ]),
                                    fields=[GenTuField(t_str(), "name")],
                                    methods=[
                                        eq_method(
                                            t_nest_shared("Callout", [
                                                t("BlockCodeLine"),
                                                t("Part"),
                                            ]))
                                    ],
                                ),
                                org_struct(
                                    t_nest_shared("Tangle", [
                                        t("BlockCodeLine"),
                                        t("Part"),
                                    ]),
                                    fields=[GenTuField(t_str(), "target")],
                                    methods=[
                                        eq_method(
                                            t_nest_shared("Tangle", [
                                                t("BlockCodeLine"),
                                                t("Part"),
                                            ]))
                                    ],
                                ),
                            ],
                            enumName=t_nest_shared("Kind", [
                                t("BlockCodeLine"),
                                t("Part"),
                            ]),
                            variantName=t_nest_shared("Data", [
                                t("BlockCodeLine"),
                                t("Part"),
                            ]),
                        ),
                    ],
                )
            ],
            fields=[
                vec_field(
                    t_nest_shared("Part", [t("BlockCodeLine")]),
                    "parts",
                    GenTuDoc("parts of the single line"),
                )
            ],
        ),
        org_struct(
            t_nest_shared("DocumentExportConfig", []),
            methods=[
                eq_method(t_nest_shared("DocumentExportConfig", [])),
            ],
            fields=[
                opt_field(t_bool(), "inlinetasks"),
                opt_field(t_bool(), "footnotes"),
                opt_field(t_bool(), "clock"),
                opt_field(t_bool(), "author"),
                opt_field(t_bool(), "emphasis"),
                opt_field(t_bool(), "specialStrings"),
                opt_field(t_bool(), "propertyDrawers"),
                opt_field(t_bool(), "statisticsCookies"),
                opt_field(t_bool(), "todoText", "Include todo keywords in export"),
                org_field(t_nest("BrokenLinks", [t("DocumentExportConfig")]),
                          "brokenLinks",
                          value="sem::DocumentExportConfig::BrokenLinks::None"),
                org_field(t_nest("TocExport", [t("DocumentExportConfig")]), "tocExport"),
                org_field(t_nest("TagExport", [t("DocumentExportConfig")]),
                          "tagExport",
                          value="org::sem::DocumentExportConfig::TagExport::NotInToc"),
            ],
            nested=[
                org_struct(
                    t_nest_shared("TaskExport", [t("DocumentExportConfig")]),
                    org_doc(),
                    fields=[vec_field(t_str(), "taskWhitelist")],
                    methods=[
                        eq_method(t_nest_shared("TaskExport",
                                                [t("DocumentExportConfig")]))
                    ],
                ),
                d_simple_enum(
                    t_nest("TagExport", [t("DocumentExportConfig")]),
                    org_doc(""),
                    "None",
                    "All",
                    efield(
                        "NotInToc",
                        "Expot tags in subtree titles but not in the table of content",
                    ),
                ),
                d_simple_enum(
                    t_nest("TaskFiltering", [t("DocumentExportConfig")]),
                    GenTuDoc(""),
                    efield("Whitelist", "Include tasks from the whitelist"),
                    efield("Done", "Include tasks marked as done"),
                    efield("None", "Exclude all task subtrees from export"),
                    efield("All", "Add all task subtrees to export"),
                ),
                d_simple_enum(
                    t_nest("BrokenLinks", [t("DocumentExportConfig")]),
                    GenTuDoc(""),
                    "None",
                    "Mark",
                    "Raise",
                    "Ignore",
                ),
                GenTuTypeGroup(
                    [
                        org_struct(
                            t_nest_shared("DoExport", [t("DocumentExportConfig")]),
                            fields=[org_field(t_bool(), "exportToc")],
                            methods=[
                                eq_method(
                                    t_nest_shared("DoExport",
                                                  [t("DocumentExportConfig")]))
                            ],
                        ),
                        org_struct(
                            t_nest_shared("ExportFixed", [t("DocumentExportConfig")]),
                            fields=[org_field(t_int(), "exportLevels")],
                            methods=[
                                eq_method(
                                    t_nest_shared("ExportFixed",
                                                  [t("DocumentExportConfig")]))
                            ],
                        ),
                    ],
                    variantName=t_nest("TocExport", [t("DocumentExportConfig")]),
                    enumName=t_nest("TocExportKind", [t("DocumentExportConfig")]),
                    kindGetter="getTocExportKind",
                ),
            ]),
        org_struct(
            t_nest_shared("SubtreePeriod", []),
            GenTuDoc("Type of the subtree associated time periods"),
            methods=[
                eq_method(t_nest_shared("SubtreePeriod", [])),
            ],
            fields=[
                GenTuField(
                    t_nest_shared("Kind", [t("SubtreePeriod")]),
                    "kind",
                    GenTuDoc(
                        "Time period kind -- not associated with point/range distinction"
                    ),
                ),
                GenTuField(t_user_time(), "from", GenTuDoc("Clock start time")),
                opt_field(t_user_time(), "to", GenTuDoc("Optional end of the clock")),
            ],
            nested=[
                GenTuPass("SubtreePeriod() {}"),
                GenTuEnum(
                    t_nest_shared("Kind", [t("SubtreePeriod")]),
                    GenTuDoc("Period kind"),
                    [
                        GenTuEnumField("Clocked",
                                       GenTuDoc("Time period of the task execution.")),
                        GenTuEnumField("Closed", GenTuDoc("Task marked as closed")),
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
                                "Date of task completion. Must be a single time point"),
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
        org_struct(
            t_nest_shared("NamedProperty", []),
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
                        GenTuIdent(t_cr(t_opt(t_str())), "subKind", value="std::nullopt"),
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
                eq_method(t_nest_shared("NamedProperty", [])),
            ],
            nested=[
                GenTuPass("NamedProperty() {}"),
                GenTuTypeGroup(
                    get_subtree_property_types(),
                    enumName=t_nest_shared("Kind", [t("NamedProperty")]),
                    variantName=t_nest_shared("Data", [t("NamedProperty")]),
                ),
                GenTuPass("NamedProperty(Data const& data) : data(data) {}"),
            ],
        ),
        org_struct(
            t_nest_shared("OrgDiagnostics", []),
            GenTuDoc(
                "Structure to store all diagnostics data collected by the parser, sem, eval etc."
            ),
            methods=[
                eq_method(t_nest_shared("OrgDiagnostics", [])),
            ],
            nested=[
                GenTuPass("OrgDiagnostics() {}"),
                GenTuTypeGroup(
                    get_diagnostic_types(),
                    enumName=t_nest_shared("Kind", [t("OrgDiagnostics")]),
                    variantName=t_nest_shared("Data", [t("OrgDiagnostics")]),
                ),
                GenTuPass("OrgDiagnostics(Data const& data) : data(data) {}"),
            ]),
    ]


def get_types() -> Sequence[GenTuStruct]:
    return [
        d_org("None", GenTuDoc("No node"), bases=[t_nest(t_org("Org"))]),
        *get_sem_bases(),
        *get_sem_commands(),
        *get_sem_text(),
        *get_sem_block(),
        *get_sem_subtree(),
        d_org("Cell",
              GenTuDoc("Table cell"),
              bases=[t_nest(t_org("Cmd"))],
              fields=[
                  bool_field(
                      "isBlock",
                      GenTuDoc("Single-line pipe cell or `#+cell:` command"),
                  ),
              ]),
        d_org("Row",
              GenTuDoc("Table row"),
              bases=[t_nest(t_org("Cmd"))],
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
            bases=[t_nest(t_org("Block"))],
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
            bases=[t_nest(t_org("Stmt"))],
            methods=[
                GenTuFunction(t_bool(), "isFootnoteDefinition", isConst=True),
                GenTuFunction(t_opt(t_str()), "getFootnoteName", isConst=True),
                GenTuFunction(t_bool(), "hasAdmonition", isConst=True),
                GenTuFunction(t_vec(t_str()), "getAdmonitions", isConst=True),
                GenTuFunction(t_vec(t_id("BigIdent")), "getAdmonitionNodes",
                              isConst=True),
                GenTuFunction(t_bool(), "hasTimestamp", isConst=True),
                GenTuFunction(t_vec(t_user_time()), "getTimestamps", isConst=True),
                GenTuFunction(t_vec(t_id("Time")), "getTimestampNodes", isConst=True),
                GenTuFunction(t_bool(), "hasLeadHashtags", isConst=True),
                GenTuFunction(t_vec(t_id("HashTag")), "getLeadHashtags", isConst=True),
                GenTuFunction(
                    t_vec(t_id()),
                    "getBody",
                    isConst=True,
                    doc=org_doc(
                        "Return content of the paragraph, without prefix idents, hashtags, footnotes etc. "
                    )),
            ]),
        d_org(
            "ColonExample",
            GenTuDoc("Shortened colon example block"),
            bases=[t_nest(t_org("Org"))],
        ),
        d_org(
            "CmdAttr",
            GenTuDoc("Caption annotation for any subsequent node"),
            bases=[t_nest(t_org("Attached"))],
            fields=[
                GenTuField(t_str(), "target", GenTuDoc("")),
            ],
        ),
        d_org("CmdExport",
              GenTuDoc("Single line of passthrough code"),
              bases=[t_nest(t_org("Attached"))],
              fields=[
                  str_field("exporter"),
                  str_field("content"),
              ]),
        d_org(
            "Call",
            GenTuDoc("Inline, statement or block call"),
            bases=[t_nest(t_org("Org"))],
            fields=[
                org_field(
                    t_str(),
                    "name",
                    "Call target name",
                ),
                org_field(
                    t_nest_shared("AttrGroup"),
                    "attrs",
                    "Additional parameters aside from 'exporter'",
                ),
                bool_field("isCommand"),
            ],
        ),
        d_org(
            "List",
            GenTuDoc(""),
            bases=[t_nest(t_org("Stmt"))],
            methods=[
                GenTuFunction(
                    t_vec(t_nest_shared("AttrValue")),
                    "getListAttrs",
                    GenTuDoc(""),
                    arguments=[GenTuIdent(t_str().asConstRef(), "key")],
                    isConst=True,
                ),
                GenTuFunction(
                    t("ListFormattingMode"),
                    "getListFormattingMode",
                    GenTuDoc(""),
                    isConst=True,
                ),
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
            bases=[t_nest(t_org("Org"))],
            fields=[
                GenTuField(t("CheckboxState"),
                           "checkbox",
                           GenTuDoc(""),
                           value="CheckboxState::None"),
                opt_field(
                    t_id("Paragraph"),
                    "header",
                    GenTuDoc("Description list item header"),
                ),
                opt_field(
                    t_str(), "bullet",
                    GenTuDoc("Full text of the numbered list item, e.g. `a)`, `a.`",))
            ],
            methods=[
                GenTuFunction(
                    t_bool(),
                    "isDescriptionItem",
                    GenTuDoc(""),
                    isConst=True,
                ),
                GenTuFunction(
                    t_opt(t_str()),
                    "getCleanHeader",
                    GenTuDoc("Return flat text for the description list header"),
                    isConst=True,
                )
            ],
        ),
        d_org(
            "DocumentOptions",
            GenTuDoc(""),
            bases=[t_nest(t_org("Org"))],
            methods=[
                GenTuFunction(
                    t_vec(t_nest_shared("NamedProperty", [])),
                    "getProperties",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "kind"),
                        GenTuIdent(t_cr(t_opt(t_str())), "subKind", value="std::nullopt"),
                    ],
                ),
                GenTuFunction(
                    t_opt(t_nest_shared("NamedProperty", [])),
                    "getProperty",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "kind"),
                        GenTuIdent(t_cr(t_opt(t_str())), "subKind", value="std::nullopt"),
                    ],
                ),
            ],
            fields=[
                org_field(
                    t("InitialSubtreeVisibility"),
                    "initialVisibility",
                    value="InitialSubtreeVisibility::ShowEverything",
                ),
                vec_field(t_nest_shared("NamedProperty", []), "properties", GenTuDoc("")),
                org_field(t_nest_shared("DocumentExportConfig", []), "exportConfig"),
                opt_field(t_bool(), "fixedWidthSections"),
                opt_field(t_bool(), "startupIndented"),
                opt_field(t_str(), "category"),
                opt_field(t_str(), "setupfile"),
                opt_field(t_int(), "maxSubtreeLevelExport"),
                opt_field(t_nest_shared("ColumnView"), "columns"),
                vec_field(t_nest_shared("TodoKeyword"), "todoKeywords"),
                vec_field(t_nest_shared("TodoKeyword"), "doneKeywords"),
            ],
        ),
        d_org(
            "DocumentFragment",
            GenTuDoc("Part of the document embedded in a larger file (e.g. in comments)"),
            bases=[t_nest(t_org("Org"))],
            fields=[
                int_field("baseLine"),
                int_field("baseCol"),
            ]),
        d_org(
            "CriticMarkup",
            GenTuDoc("https://fletcher.github.io/MultiMarkdown-6/syntax/critic.html"),
            bases=[t_nest(t_org("Org"))],
            nested=[
                d_simple_enum(
                    t_nest("Kind", [t_org("CriticMarkup")]),
                    GenTuDoc(""),
                    efield("Deletion"),
                    efield("Addition"),
                    efield("Substitution"),
                    efield("Highlighting"),
                    efield("Comment"),
                )
            ],
            fields=[
                org_field(t_nest("Kind", [t_org("CriticMarkup")]), "kind"),
            ],
        ),
        d_org(
            "Document",
            GenTuDoc(""),
            bases=[t_nest(t_org("Org"))],
            methods=[
                GenTuFunction(
                    t_vec(t_nest_shared("NamedProperty", [])),
                    "getProperties",
                    GenTuDoc(""),
                    isConst=True,
                    arguments=[
                        GenTuIdent(t_cr(t_str()), "kind"),
                        GenTuIdent(t_cr(t_opt(t_str())), "subKind", value="std::nullopt"),
                    ],
                ),
                GenTuFunction(
                    t_opt(t_nest_shared("NamedProperty", [])),
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
            bases=[t_nest(t_org("Org"))],
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
            bases=[t_nest(t_org("Org"))],
        ),
        d_org(
            "DocumentGroup",
            bases=[t_nest(t_org("Org"))],
        ),
        d_org("File",
              bases=[t_nest(t_org("Org"))],
              fields=[
                  str_field("relPath", "Relative path from the root directory"),
                  str_field("absPath", "Absolute resolved path to physical file"),
              ],
              nested=[
                  GenTuTypeGroup(
                      [
                          org_struct(t_nest("Document", [t_org("File")])),
                          org_struct(t_nest("Attachment", [t_org("File")])),
                          org_struct(t_nest("Source", [t_org("File")]))
                      ],
                      enumName=t_nest("Kind", [t_org("File")]),
                      kindGetter="getFileKind",
                      variantName=t_nest("Data", [t_org("File")]),
                  )
              ]),
        d_org(
            "Directory",
            bases=[t_nest(t_org("Org"))],
            fields=[
                str_field(
                    "relPath",
                    "Relative path from the root directory, empty if this is the root directory"
                ),
                str_field("absPath", "Absolute resolved path to physical directory"),
            ]),
        d_org(
            "Symlink",
            bases=[t_nest(t_org("Org"))],
            fields=[
                org_field(t_bool(), "isDirectory"),
                str_field(
                    "absPath", "Absolute path to the symlinked target directory. "
                    "All relative paths under symlink node use its absolute path as a root."
                )
            ]),
        d_org(
            "CmdInclude",
            bases=[t_nest(t_org("Org"))],
            nested=[
                org_struct(
                    t_nest("IncludeBase", [t_org("CmdInclude")]),
                    methods=[default_constructor_method("IncludeBase")],
                    fields=[],
                ),
                GenTuTypeGroup(
                    [
                        org_struct(
                            t_nest("Example", [t_org("CmdInclude")]),
                            methods=[default_constructor_method("Example")],
                            bases=[t_nest("IncludeBase", [t_org("CmdInclude")])],
                        ),
                        org_struct(
                            t_nest("Export", [t_org("CmdInclude")]),
                            methods=[default_constructor_method("Export")],
                            bases=[t_nest("IncludeBase", [t_org("CmdInclude")])],
                            fields=[
                                org_field(t_str(), "language",
                                          "Source code language for export"),
                            ],
                        ),
                        org_struct(
                            t_nest("Custom", [t_org("CmdInclude")]),
                            doc=
                            "Second positional argument in the include command can have any arbitrary value -- "
                            "default src/export/example have additional properties, but user "
                            "can provide anything else there.",
                            methods=[default_constructor_method("Custom")],
                            bases=[t_nest("IncludeBase", [t_org("CmdInclude")])],
                            fields=[
                                org_field(t_str(), "blockName",
                                          "Block name not covered by the default values")
                            ]),
                        org_struct(
                            t_nest("Src", [t_org("CmdInclude")]),
                            methods=[default_constructor_method("Src")],
                            bases=[t_nest("IncludeBase", [t_org("CmdInclude")])],
                            fields=[
                                org_field(t_str(), "language",
                                          "Source code language for code block"),
                            ],
                        ),
                        org_struct(
                            t_nest("OrgDocument", [t_org("CmdInclude")]),
                            methods=[default_constructor_method("OrgDocument")],
                            bases=[t_nest("IncludeBase", [t_org("CmdInclude")])],
                            fields=[
                                opt_field(
                                    t_bool(),
                                    "onlyContent",
                                    "omits any planning lines or property drawers",
                                ),
                                opt_field(
                                    t_nest_shared("SubtreePath"),
                                    "subtreePath",
                                    "Include first subtree matching path with `file.org::* tree`",
                                ),
                                opt_field(
                                    t_int(),
                                    "minLevel",
                                    "The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.",
                                ),
                                opt_field(
                                    t_str(),
                                    "customIdTarget",
                                    "Include target subtree content with `file.org::#custom`",
                                ),
                            ]),
                    ],
                    kindGetter="getIncludeKind",
                    enumName=t_nest("Kind", [t_org("CmdInclude")]),
                    variantName=t_nest("Data", [t_org("CmdInclude")]),
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
    ]


#endregion


#region OrgNodeKind
def get_org_node_kind_text():
    return [
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
        efield("ErrorInfoToken",
               "Error leaf node inserted into the parse tree on failure"),
        efield("ErrorSkipGroup",
               "Parent node for one or more tokens skipped during error recovery"),
        efield("ErrorSkipToken",
               "Single token node skipped while the parser searched for recovery point"),
        efield("Italic"),
        efield("Verbatim"),
        efield("Backtick"),
        efield("Underline"),
        efield("Strike"),
        efield("Quote"),
        efield("Angle"),
        efield("Monospace"),
        efield("Par"),
        efield("CriticMarkStructure"),
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
        efield("BlockDynamicFallback", "#+begin_<any> section"),
    ]


def get_org_node_kind_commands():
    return [
        efield(
            "Cmd",
            "Undefined single-line command -- most likely custom user-provided oe",
        ),
        efield("Attrs", "Arguments for the command block"),
        efield("AttrValue", ":key name=value syntax"),
        efield("AttrLisp", "S-expression as an attribute value value"),
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
        efield("CmdKeywords", ""),
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


def get_org_token_kind():
    return [
        efield("Ampersand", ""),
        efield("AngleBegin", ""),
        efield("AngleEnd", ""),
        efield("AnyPunct", ""),
        efield("Asterisk", ""),
        efield("At", ""),
        efield("Backtick", ""),
        efield("BigIdent", ""),
        efield("BoldBegin", ""),
        efield("BoldEnd", ""),
        efield("BoldUnknown", ""),
        efield("BraceBegin", ""),
        efield("BraceEnd", ""),
        efield("Checkbox", ""),
        efield("Circumflex", ""),
        efield("CmdAdmonitionEnd", ""),
        efield("CmdAttr", ""),
        efield("CmdAuthor", ""),
        efield("CmdBindRaw", ""),
        efield("CmdCall", ""),
        efield("CmdCaption", ""),
        efield("CmdCategoryRaw", ""),
        efield("CmdCell", ""),
        efield("CmdCellBegin", ""),
        efield("CmdCellEnd", ""),
        efield("CmdCenterBegin", ""),
        efield("CmdCenterEnd", ""),
        efield("CmdColonIdent", ""),
        efield("CmdColumns", ""),
        efield("CmdCommentBegin", ""),
        efield("CmdCommentEnd", ""),
        efield("CmdConstants", ""),
        efield("CmdContentBegin", ""),
        efield("CmdContentEnd", ""),
        efield("CmdCreator", ""),
        efield("CmdCustomRaw", ""),
        efield("CmdDateRaw", ""),
        efield("CmdDescription", ""),
        efield("CmdDrawersRaw", ""),
        efield("CmdDynamicBegin", ""),
        efield("CmdDynamicBlockBegin", ""),
        efield("CmdDynamicBlockEnd", ""),
        efield("CmdDynamicEnd", ""),
        efield("CmdEmailRaw", ""),
        efield("CmdExampleBegin", ""),
        efield("CmdExampleEnd", ""),
        efield("CmdExampleLine", ""),
        efield("CmdExcludeTagsRaw", ""),
        efield("CmdExportBegin", ""),
        efield("CmdExportEnd", ""),
        efield("CmdExportLine", ""),
        efield("CmdFiletags", ""),
        efield("CmdFlag", ""),
        efield("CmdHeader", ""),
        efield("CmdHtmlHeadRaw", ""),
        efield("CmdInclude", ""),
        efield("CmdLanguage", ""),
        efield("CmdLatexClass", ""),
        efield("CmdLatexClassOptions", ""),
        efield("CmdLatexCompiler", ""),
        efield("CmdLatexHeader", ""),
        efield("CmdLatexHeaderExtraRaw", ""),
        efield("CmdLinkRaw", ""),
        efield("CmdMacroRaw", ""),
        efield("CmdName", ""),
        efield("CmdOptions", ""),
        efield("CmdPrefix", ""),
        efield("CmdPrioritiesRaw", ""),
        efield("CmdPropertyArgs", ""),
        efield("CmdPropertyRaw", ""),
        efield("CmdPropertyText", ""),
        efield("CmdQuoteBegin", ""),
        efield("CmdQuoteEnd", ""),
        efield("CmdRawArg", ""),
        efield("CmdResults", ""),
        efield("CmdRow", ""),
        efield("CmdRowBegin", ""),
        efield("CmdRowEnd", ""),
        efield("CmdSelectTagsRaw", ""),
        efield("CmdSeqTodoRaw", ""),
        efield("CmdKeywordsRaw", ""),
        efield("CmdSetupfileRaw", ""),
        efield("CmdSrcBegin", ""),
        efield("CmdSrcEnd", ""),
        efield("CmdStartup", ""),
        efield("CmdTableBegin", ""),
        efield("CmdTableEnd", ""),
        efield("CmdTagsRaw", ""),
        efield("CmdTblfm", ""),
        efield("CmdTitle", ""),
        efield("CmdVerseBegin", ""),
        efield("CmdVerseEnd", ""),
        efield("Colon", ""),
        efield("ColonArgumentsProperty", ""),
        efield("ColonEnd", ""),
        efield("ColonExampleLine", ""),
        efield("ColonLiteralProperty", ""),
        efield("ColonLogbook", ""),
        efield("ColonProperties", ""),
        efield("ColonPropertyText", ""),
        efield("Comma", ""),
        efield("Comment", ""),
        efield("CriticAddBegin", ""),
        efield("CriticAddEnd", ""),
        efield("CriticCommentBegin", ""),
        efield("CriticCommentEnd", ""),
        efield("CriticDeleteBegin", ""),
        efield("CriticDeleteEnd", ""),
        efield("CriticHighlightBegin", ""),
        efield("CriticHighlightEnd", ""),
        efield("CriticReplaceBegin", ""),
        efield("CriticReplaceEnd", ""),
        efield("CriticReplaceMiddle", ""),
        efield("CurlyBegin", ""),
        efield("CurlyEnd", ""),
        efield("Date", ""),
        efield("Dedent", ""),
        efield("Dollar", ""),
        efield("DoubleAngleBegin", ""),
        efield("DoubleAngleEnd", ""),
        efield("DoubleColon", ""),
        efield("DoubleDash", ""),
        efield("DoubleHash", ""),
        efield("DoubleQuote", ""),
        efield("DoubleSlash", ""),
        efield("ActiveDynamicTimeContent", ""),
        efield("InactiveDynamicTimeContent", ""),
        efield("EndOfFile", ""),
        efield("Equals", ""),
        efield("Escaped", ""),
        efield("Exclamation", ""),
        efield("FootnoteInlineBegin", ""),
        efield("FootnoteLinked", ""),
        efield("ForwardSlash", ""),
        efield("HashIdent", ""),
        efield("HashTagBegin", ""),
        efield("Indent", ""),
        efield("InlineExportBackend", ""),
        efield("InlineExportContent", ""),
        efield("ItalicBegin", ""),
        efield("ItalicEnd", ""),
        efield("ItalicUnknown", ""),
        efield("LatexInlineRaw", ""),
        efield("LatexParBegin", ""),
        efield("LatexParEnd", ""),
        efield("LeadingMinus", ""),
        efield("LeadingNumber", ""),
        efield("LeadingPipe", ""),
        efield("LeadingPlus", ""),
        efield("LeadingSpace", ""),
        efield("LineCommand", ""),
        efield("LinkBegin", ""),
        efield("LinkDescriptionBegin", ""),
        efield("LinkDescriptionEnd", ""),
        efield("LinkEnd", ""),
        efield("LinkFull", ""),
        efield("LinkProtocol", ""),
        efield("LinkProtocolAttachment", ""),
        efield("LinkProtocolCustomId", ""),
        efield("LinkProtocolFile", ""),
        efield("LinkProtocolHttp", ""),
        efield("LinkProtocolId", ""),
        efield("LinkProtocolInternal", ""),
        efield("LinkProtocolTitle", ""),
        efield("LinkSplit", ""),
        efield("LinkTarget", ""),
        efield("LinkTargetBegin", ""),
        efield("LinkTargetEnd", ""),
        efield("LinkTargetFile", ""),
        efield("ListBegin", ""),
        efield("ListEnd", ""),
        efield("ListItemBegin", ""),
        efield("ListItemEnd", ""),
        efield("LongNewline", ""),
        efield("MediumNewline", ""),
        efield("Minus", ""),
        efield("MiscUnicode", ""),
        efield("MonospaceBegin", ""),
        efield("MonospaceEnd", ""),
        efield("MonospaceUnknown", ""),
        efield("Newline", ""),
        efield("Number", ""),
        efield("ParBegin", ""),
        efield("ParEnd", ""),
        efield("Percent", ""),
        efield("Pipe", ""),
        efield("Placeholder", ""),
        efield("Plus", ""),
        efield("Punctuation", ""),
        efield("RawText", ""),
        efield("SameIndent", ""),
        efield("Semicolon", ""),
        efield("SingleQuote", ""),
        efield("SrcContent", ""),
        efield("StmtListBegin", ""),
        efield("StmtListEnd", ""),
        efield("StrikeBegin", ""),
        efield("StrikeEnd", ""),
        efield("StrikeUnknown", ""),
        efield("SubtreeCompletion", ""),
        efield("SubtreePriority", ""),
        efield("SubtreeStars", ""),
        efield("Symbol", ""),
        efield("TableSeparator", ""),
        efield("TextSeparator", ""),
        efield("TextSrcBegin", ""),
        efield("Tilda", ""),
        efield("Time", ""),
        efield("TimeArrow", ""),
        efield("TimeRepeaterDuration", ""),
        efield("TimeRepeaterSpec", ""),
        efield("TimeWarnPeriod", ""),
        efield("TrailingPipe", ""),
        efield("TreeClock", ""),
        efield("TreeTime", ""),
        efield("TripleAngleBegin", ""),
        efield("TripleAngleEnd", ""),
        efield("Underline", ""),
        efield("UnderlineBegin", ""),
        efield("UnderlineEnd", ""),
        efield("UnderlineUnknown", ""),
        efield("Unknown", ""),
        efield("VerbatimBegin", ""),
        efield("VerbatimEnd", ""),
        efield("VerbatimUnknown", ""),
        efield("Whitespace", ""),
        efield("Word", ""),
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
                efield("Warn"),
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
            ],
        ),
        GenTuEnum(
            t("OrgNodeKind"),
            #region OrgNodeKind
            GenTuDoc(""),
            get_org_node_kind(),
            #endregion
        ),
        GenTuEnum(
            t("OrgTokenKind"),
            GenTuDoc(""),
            get_org_token_kind(),
        ),
        d_simple_enum(
            t("OrgJsonKind"),
            GenTuDoc(""),
            efield("Null"),
            efield("Object"),
            efield("Array"),
            efield("String"),
            efield("Boolean"),
            efield("Int"),
            efield("Float"),
        ),
    ]
