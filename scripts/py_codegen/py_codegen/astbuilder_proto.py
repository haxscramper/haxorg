import py_codegen.gen_tu_cpp as tu
import py_codegen.astbuilder_cpp as cpp
from py_textlayout.py_textlayout_wrap import TextOptions, TextLayout, BlockId

from beartype.typing import (List, Iterable, Generator, Dict, Tuple, Optional, Union,
                             Final)

from beartype import beartype
import itertools
from py_scriptutils.algorithm import drop_none, iterate_object_tree

PROTO_VALUE_NAME = "out"
ORG_VALUE_NAME = "in"


def pascal_case(s: str) -> str:
    return s[0].upper() + s[1:].lower() if s else ""


@beartype
class ProtoBuilder():

    def __init__(self, wrapped: List[tu.GenTuUnion], ast: cpp.ASTBuilder):
        self.base_map = tu.get_base_map(wrapped)
        self.ast = ast
        self.t = ast.b

        self.enum_type_list: List[tu.QualType] = []
        self.variant_type_list: Dict[Tuple[str, ...], tu.GenTuTypedef] = {}
        self.types_list = wrapped

        context = []

        def find_enums(obj):
            if isinstance(obj, tu.GenTuEnum):
                filter = tu.filter_walk_scope(context)
                self.enum_type_list.append(obj.name)

            elif isinstance(obj, tu.GenTuTypedef):
                if obj.base.name == "variant":
                    self.variant_type_list[tuple(obj.name.flatQualName())] = obj

        iterate_object_tree(self.types_list, find_enums, context)

    def oneof_field_name(self, it: tu.GenTuField) -> str:
        if it.type.name == "Variant":
            return it.name + "_kind"

        else:
            return "kind"

    def build_protobuf(self) -> BlockId:

        def braced(name: str, content: Iterable[BlockId]) -> BlockId:
            return self.t.stack([
                self.t.text(f"{name} {{"),
                self.t.indent(2, self.t.stack(list(content))),
                self.t.text("}"),
            ])

        field_name_width = 32
        field_type_width = 48
        enum_field_width = field_name_width + field_type_width

        def aux_field(it: tu.GenTuField, indexer: Generator[int], indent: int) -> BlockId:
            if it.type.name == "Variant":
                return self.t.stack([
                    braced(
                        f"oneof {self.oneof_field_name(it)}",
                        aux_field_list(
                            self.build_protobuf_fields_for_variant(it.type),
                            indexer=indexer,
                            indent=indent + 1,
                        ))
                ])

            else:
                type_width = field_type_width - (2 * indent)
                idx = next(indexer)
                return self.t.text(
                    f"{self.rewrite_for_proto_grammar(it.type):<{type_width}} {it.name:<{field_name_width}} = {idx + 1};"
                )

        def aux_enum(parent: tu.GenTuEnum, it: tu.GenTuEnumField, idx: int,
                     indent: int) -> BlockId:
            # _f suffix to avoid clashes with OrgSpecName_Name method generated by protoc
            name = f"{parent.name.name}_{it.name}_f"
            enum_width = enum_field_width - 2 * indent
            return self.t.text(f"{name:<{enum_width}}  = {idx};")

        def aux_field_list(fields: Iterable[tu.GenTuField], indexer: Generator[int],
                           indent: int) -> Iterable[BlockId]:
            return (aux_field(field, indexer, indent=indent) for field in fields)

        def make_full_enumerator() -> Generator[int]:

            def full_enumerator() -> Generator[int]:
                value = 0
                while True:
                    yield value
                    value += 1

            return full_enumerator()

        def aux_item(it: tu.GenTuUnion | tu.GenTuField, indent: int) -> Optional[BlockId]:
            match it:
                case tu.GenTuStruct():
                    return braced(
                        "message " + it.name.name,
                        itertools.chain(
                            drop_none(
                                aux_item(sub, indent=indent + 1) for sub in it.nested),
                            aux_field_list(
                                (tu.get_type_base_fields(it, self.base_map) + it.fields),
                                indexer=make_full_enumerator(),
                                indent=indent),
                            [
                                aux_field(
                                    it=tu.GenTuField(tu.QualType.ForName("Str"), "debug"),
                                    indexer=(it for it in [999]),
                                    indent=indent,
                                )
                            ]))

                case tu.GenTuEnum():
                    return braced("enum " + it.name.name, [
                        aux_enum(it, sub, idx, indent)
                        for idx, sub in enumerate(it.fields)
                    ])

                case tu.GenTuPass():
                    return None

                case tu.GenTuTypedef():
                    match it.base:
                        case tu.QualType(name="variant"):
                            return braced("message " + it.name.name, [
                                braced(
                                    "oneof kind",
                                    aux_field_list(
                                        (tu.GenTuField(name=par.name.lower(), type=par)
                                         for par in it.base.Parameters),
                                        indexer=make_full_enumerator(),
                                        indent=indent + 1))
                            ])

                        case _:
                            return None

                case _:
                    assert False, type(it)

        any_node = braced("message AnyNode", [
            braced(
                "oneof kind",
                aux_field_list((tu.GenTuField(name=rec.name.name.lower(), type=rec.name)
                                for rec in self.get_all_concrete_types()),
                               indent=0,
                               indexer=make_full_enumerator()),
            )
        ])

        return self.t.stack(
            list(
                itertools.chain(*([it, self.t.text("")] for it in drop_none(
                    aux_item(it, indent=0) for it in self.types_list)))) + [any_node])

    @beartype
    def get_all_concrete_types(self) -> Iterable[tu.GenTuStruct]:
        return (rec for rec in self.types_list
                if isinstance(rec, tu.GenTuStruct) and rec.concreteKind)

    @beartype
    def get_any_node_field_mapping(self) -> cpp.MacroParams:
        return cpp.MacroParams(
            name="EACH_ANY_NODE_PROTO_FIELD",
            params=[cpp.MacroParams.Param("__MAP")],
            definition=[
                "__MAP(k{}, {}, {})".format(
                    pascal_case(rec.name.name),
                    self.sanitize_ident_for_protobuf(rec.name.name),
                    rec.name.name,
                ) for rec in self.get_all_concrete_types()
            ],
        )

    @beartype
    def rewrite_for_proto_grammar(self, it: tu.QualType) -> str:
        match it.name:
            case "Vec":
                return "repeated " + self.rewrite_for_proto_grammar(it.Parameters[0])

            case "Str" | "string":
                return "string"

            case "int":
                return "int32"

            case "Opt":
                if it.Parameters[0].name == "Vec":
                    return self.rewrite_for_proto_grammar(it.Parameters[0])

                else:
                    return "optional " + self.rewrite_for_proto_grammar(it.Parameters[0])

            case "UnorderedMap":
                return "map<{}, {}>".format(
                    self.rewrite_for_proto_grammar(it.Parameters[0]),
                    self.rewrite_for_proto_grammar(it.Parameters[1]),
                )

            case "SemId":
                if it.par0().name == "Org":
                    return "AnyNode"
                
                else:
                    return self.rewrite_for_proto_grammar(it.Parameters[0])

            case _:
                spaces = [s.name for s in it.Spaces if s.name != "sem"]
                return ".".join(spaces + [it.name])

    @beartype
    def rewrite_for_proto_serde(
        self,
        typ: tu.QualType,
    ) -> tu.QualType:

        def aux_parameters(typ) -> List[tu.QualType]:
            return [self.rewrite_for_proto_serde(p) for p in typ.Parameters]

        match typ:
            case tu.QualType(name="SemId", Parameters=[nodeType]):
                if nodeType.name == "Org":
                    return tu.QualType.ForName("AnyNode").withExtraSpace("orgproto")
                
                else:
                    return nodeType.withoutSpace("sem").withExtraSpace("orgproto")

            case tu.QualType(name="bool"):
                return typ

            case tu.QualType(name="Str"):
                return tu.QualType.ForName("string").withExtraSpace("std")

            case tu.QualType(name="int"):
                return tu.QualType.ForName("int32_t").withGlobalSpace()

            case tu.QualType(name="Vec"):
                if typ.Parameters[0].name in ["int", "bool"]:
                    wrap_type = "RepeatedField"

                else:
                    wrap_type = "RepeatedPtrField"

                return typ.model_copy(update=dict(
                    Parameters=aux_parameters(typ),
                    name=wrap_type,
                    Spaces=[
                        tu.QualType.ForName("google"),
                        tu.QualType.ForName("protobuf")
                    ],
                    isGlobalNamespace=True,
                ))

            case tu.QualType(name="UnorderedMap"):
                return typ.model_copy(update=dict(
                    Parameters=aux_parameters(typ),
                    name="Map",
                    Spaces=[
                        tu.QualType.ForName("google"),
                        tu.QualType.ForName("protobuf")
                    ],
                    isGlobalNamespace=True,
                ))

            case _:
                if tu.in_type_list(typ, self.enum_type_list):
                    return tu.QualType.ForName("_".join(
                        typ.withoutSpace("sem").flatQualName())).withExtraSpace(
                            "orgproto")

                else:
                    result = typ.model_copy(update=dict(Parameters=aux_parameters(typ)))
                    if "sem" in result.flatSpaces() or typ.name in [
                            "UserTime", "LineCol"
                    ]:
                        result = result.withoutSpace("sem").withExtraSpace("orgproto")

                    return result

    @beartype
    def build_protobuf_cxx_field_read(
        self,
        field: tu.GenTuField,
        dot_field: BlockId,
        is_read_getter: bool,
    ) -> Tuple[BlockId, tu.QualType, tu.QualType]:
        if not is_read_getter and field.type.name in ["Opt"]:
            field_read = self.t.line([self.t.text("*"), dot_field])
            field_type = field.type.Parameters[0]

        else:
            field_read = dot_field
            field_type = field.type

        # if not is_read_getter and field_type.name == "SemId":
        #     field_read = self.t.line(
        #         [self.t.text("*(("), field_read,
        #          self.t.text(").get())")])
        #     field_type = field_type.Parameters[0]

        field_proto_type = self.rewrite_for_proto_serde(field_type)
        is_enum_field = tu.in_type_list(field_type, self.enum_type_list)

        if not is_read_getter and is_enum_field:
            field_read = self.ast.XCall(
                "static_cast",
                args=[field_read],
                Params=[field_proto_type],
            )

        return (field_read, field_type, field_proto_type)

    def is_enum_type(self, typ: tu.QualType) -> bool:
        return tu.in_type_list(typ, self.enum_type_list)

    def is_direct_set_type(self, typ: tu.QualType) -> bool:
        return typ.name in ["int", "string", "bool"] or self.is_enum_type(typ)

    def get_field_read_op(
        self,
        field: tu.GenTuField,
        dot_field: BlockId,
        parent_field: Optional[tu.GenTuField] = None,
    ) -> BlockId:
        field_read, field_type, field_proto_type = self.build_protobuf_cxx_field_read(
            field,
            dot_field,
            is_read_getter=True,
        )

        proto_ptr = self.ast.b.text(PROTO_VALUE_NAME)

        if self.is_direct_set_type(field_type):
            read_expr = self.ast.XCallRef(proto_ptr,
                                          self.sanitize_ident_for_protobuf(field.name))
            if self.is_enum_type(field_type):
                read_expr = self.ast.XCall(
                    "static_cast",
                    args=[read_expr],
                    Params=[field_type],
                )

            read_op = self.t.line([
                self.ast.XCallRef(field_read, "get"),
                self.t.text(" = "),
                read_expr,
                self.t.text(";"),
            ])

        else:
            opc = self.sanitize_ident_for_protobuf(field.name)

            if parent_field:
                opc = self.sanitize_ident_for_protobuf(parent_field.name) + "()." + opc

            read_op = self.ast.CallStatic(
                tu.QualType(
                    name="proto_serde",
                    Parameters=[field_proto_type, field_type],
                ),
                "read",
                [
                    self.ast.XCallRef(proto_ptr, opc),
                    field_read,
                ],
                Stmt=True,
            )

        if field.type.name in ["Opt"]:
            if field.type.par0().name not in ["Vec"]:
                read_op = self.ast.IfStmt(
                    cpp.IfStmtParams([
                        cpp.IfStmtParams.Branch(
                            Cond=self.ast.XCallRef(
                                proto_ptr,
                                "has_" + self.sanitize_ident_for_protobuf(field.name),
                            ),
                            Then=read_op,
                        )
                    ]))

        return read_op

    def get_field_write_op(
        self,
        field: tu.GenTuField,
        dot_field: BlockId,
        parent_field: Optional[tu.GenTuField] = None,
    ) -> BlockId:
        field_read, field_type, field_proto_type = self.build_protobuf_cxx_field_read(
            field,
            dot_field,
            is_read_getter=False,
        )

        if self.is_direct_set_type(field_type):
            write_op = self.ast.XCallPtr(
                self.ast.b.text(PROTO_VALUE_NAME),
                "set_" + self.sanitize_ident_for_protobuf(field.name),
                [field_read],
                Stmt=True,
            )

        else:
            if parent_field:
                opc = f"mutable_{self.sanitize_ident_for_protobuf(parent_field.name)}()->mutable_{self.sanitize_ident_for_protobuf(field.name)}"

            else:
                opc = "mutable_" + self.sanitize_ident_for_protobuf(field.name)

            if self.sanitize_ident_for_protobuf(field.name) in ["static", "export"]:
                opc += "_"

            write_op = self.ast.CallStatic(
                tu.QualType(
                    name="proto_serde",
                    Parameters=[field_proto_type, field_type],
                ),
                "write",
                [self.ast.XCallPtr(self.ast.b.text(PROTO_VALUE_NAME), opc), field_read],
                Stmt=True,
            )

        if field.type.name in ["Opt"]:
            write_op = self.ast.IfStmt(
                cpp.IfStmtParams(
                    [cpp.IfStmtParams.Branch(
                        Cond=dot_field,
                        Then=write_op,
                    )]))

        elif field.type.name.startswith("SemId"):
            write_op = self.ast.IfStmt(
                cpp.IfStmtParams([
                    cpp.IfStmtParams.Branch(
                        Cond=self.t.line([
                            self.t.text("!"),
                            self.ast.XCallRef(dot_field, "isNil"),
                        ]),
                        Then=write_op,
                    )
                ]))

        return write_op

    @beartype
    def build_protobuf_writer_for_field(
        self,
        field: tu.GenTuField,
        proto_type: tu.QualType,
        org_type: tu.QualType,
    ) -> Tuple[BlockId, BlockId]:
        t = self.ast.b
        field_ptr = self.t.line([
            self.t.text("&"),
            self.ast.Type(org_type),
            self.t.text("::"),
            t.text(field.name),
        ])

        dot_write = self.ast.Dot(t.text(ORG_VALUE_NAME), t.text(field.name))
        dot_read = self.ast.XCallRef(
            t.text(ORG_VALUE_NAME),
            "for_field",
            [field_ptr],
        )

        flat = tuple(field.type.flatQualName())
        if flat in self.variant_type_list or field.type.name in [
                "variant", "Variant", "Var"
        ]:
            is_typedef = flat in self.variant_type_list
            variant = self.variant_type_list[flat].base if is_typedef else field.type
            if is_typedef:
                reader_switch = cpp.SwitchStmtParams(Expr=self.ast.XCallRef(
                    t.text(PROTO_VALUE_NAME),
                    self.sanitize_ident_for_protobuf(field.name) + "()." +
                    self.oneof_field_name(field) + "_case"))

            else:
                reader_switch = cpp.SwitchStmtParams(
                    Expr=self.ast.XCallRef(t.text(PROTO_VALUE_NAME),
                                           self.oneof_field_name(field) + "_case"))

            writer_switch = cpp.SwitchStmtParams(
                Expr=t.line([dot_write, t.text(".index()")]))

            if is_typedef:
                kind_type = proto_type.asSpaceFor(field.type.withoutAllSpaces())

            else:
                kind_type = proto_type

            for idx, var_field in enumerate(
                    self.build_protobuf_fields_for_variant(variant)):

                var_dot_write = t.line(
                    [t.text(f"std::get<{idx}>("), dot_write,
                     t.text(")")])
                var_dot_read = t.line([
                    self.ast.XCallRef(
                        t.text(ORG_VALUE_NAME),
                        "for_field_variant",
                        [field_ptr],
                        Params=[tu.QualType.ForExpr(str(idx))],
                    )
                ])

                writer_switch.Cases.append(
                    cpp.CaseStmtParams(
                        Expr=t.text(str(idx)),
                        Body=[
                            self.get_field_write_op(
                                var_field,
                                var_dot_write,
                                parent_field=field if is_typedef else None,
                            )
                        ],
                        OneLine=False,
                        Compound=False,
                        Autobreak=True,
                    ))

                field_enum_value = kind_type.asSpaceFor(
                    cpp.QualType.ForName(f"k{pascal_case(var_field.name)}"))

                reader_switch.Cases.append(
                    cpp.CaseStmtParams(
                        Expr=self.ast.Type(field_enum_value),
                        Body=[
                            self.get_field_read_op(
                                var_field,
                                var_dot_read,
                                parent_field=field if is_typedef else None,
                            ),
                        ],
                        OneLine=False,
                        Compound=False,
                        Autobreak=True,
                    ))

            return (
                self.ast.SwitchStmt(writer_switch),
                self.ast.SwitchStmt(reader_switch),
            )

        else:
            return (
                self.get_field_write_op(
                    field,
                    dot_write,
                ),
                self.get_field_read_op(
                    field,
                    dot_read,
                ),
            )

    @beartype
    def sanitize_ident_for_protobuf(self, ident: str) -> str:
        result = ident.lower().replace(" ", "_")
        if result in ["export", "static"]:
            result += "_"

        return result

    @beartype
    def build_protobuf_fields_for_variant(
        self,
        typ: tu.QualType,
    ) -> Iterable[tu.GenTuField]:
        return (tu.GenTuField(
            name=self.rewrite_for_proto_grammar(sub.withoutAllSpaces()).lower().replace(
                " ", "_"),
            type=sub,
        ) for sub in typ.Parameters)

    @beartype
    def build_protobuf_serde_object(
            self, it: tu.GenTuUnion | tu.GenTuPass
    ) -> List[Tuple[cpp.RecordParams, tu.QualType]]:
        result: List[Tuple[cpp.RecordParams, tu.QualType]] = []
        match it:
            case tu.GenTuStruct():
                if not it.concreteKind:
                    return []

                out = self.t.text(PROTO_VALUE_NAME)
                _in = self.t.text(ORG_VALUE_NAME)
                org_cleaned = it.name.withoutSpace("sem").withExtraSpace("orgproto")
                proto_param_type = org_cleaned.withGlobalSpace()
                org_param_type = it.name

                writer_body: List[BlockId] = []
                reader_body: List[BlockId] = []
                for base in tu.get_base_list(it, self.base_map):
                    if base.name in self.base_map and len(
                            self.base_map[base.name].fields) == 0:
                        continue

                    writer_body.append(
                        self.ast.CallStatic(
                            tu.QualType(name="proto_serde",
                                        Parameters=[proto_param_type, base]),
                            "write",
                            [out, _in],
                            Stmt=True,
                        ))

                    reader_body.append(
                        self.ast.CallStatic(
                            tu.QualType(name="proto_serde",
                                        Parameters=[proto_param_type, base]),
                            "read",
                            [
                                out,
                                self.ast.XCallRef(_in, "as", Params=[base]),
                            ],
                            Stmt=True,
                        ))

                for field in it.fields:
                    if field.name == "staticKind":
                        continue

                    write_op, read_op = self.build_protobuf_writer_for_field(
                        field,
                        proto_type=proto_param_type,
                        org_type=org_param_type,
                    )

                    writer_body.append(write_op)
                    reader_body.append(read_op)

                reader = cpp.MethodDeclParams(
                    Params=cpp.FunctionParams(
                        Name="read",
                        Args=[
                            cpp.ParmVarParams(
                                name=PROTO_VALUE_NAME,
                                type=proto_param_type.asConstRef(),
                            ),
                            cpp.ParmVarParams(
                                name=ORG_VALUE_NAME,
                                type=tu.QualType(
                                    name="proto_write_accessor",
                                    Parameters=[org_param_type],
                                ),
                            ),
                        ],
                        doc=cpp.DocParams(""),
                        Body=reader_body,
                        AllowOneLine=False,
                    ),
                    isStatic=True,
                )

                writer = cpp.MethodDeclParams(
                    Params=cpp.FunctionParams(
                        Name="write",
                        Args=[
                            cpp.ParmVarParams(
                                name=PROTO_VALUE_NAME,
                                type=proto_param_type.asPtr(),
                            ),
                            cpp.ParmVarParams(
                                name=ORG_VALUE_NAME,
                                type=org_param_type.asConstRef(),
                            ),
                        ],
                        doc=cpp.DocParams(""),
                        Body=writer_body,
                        AllowOneLine=False,
                    ),
                    isStatic=True,
                )

                for sub in it.nested:
                    result += self.build_protobuf_serde_object(sub)

                writer_specialization = tu.QualType(
                    name="proto_serde",
                    Parameters=[proto_param_type, org_param_type],
                )

                result.append((
                    cpp.RecordParams(
                        name="proto_serde",
                        doc=cpp.DocParams(""),
                        NameParams=[proto_param_type, org_param_type],
                        members=[
                            writer,
                            reader,
                        ],
                        Template=cpp.TemplateParams(Stacks=[cpp.TemplateGroup(
                            Params=[])]),
                    ),
                    writer_specialization,
                ))

        return result

    @beartype
    def build_protobuf_writer(
            self) -> Tuple[Iterable[cpp.RecordParams], Iterable[cpp.MethodDefParams]]:

        item: cpp.RecordParams
        name: tu.QualType
        writer_types: List[cpp.RecordParams] = []
        writer_methods: List[cpp.MethodDefParams] = []
        for item, name in itertools.chain(
                *(self.build_protobuf_serde_object(it) for it in self.types_list)):
            writer_types.append(item)

            for meth in item.methods():
                writer_methods.append(meth.asMethodDef(name))
                meth.Params.Body = None

        return (writer_types, writer_methods)
