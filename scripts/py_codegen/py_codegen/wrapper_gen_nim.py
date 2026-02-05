from dataclasses import dataclass, field, replace
import itertools
import math
from pathlib import Path
import re
from typing import TYPE_CHECKING

from beartype import beartype
from beartype.typing import Callable, List, NewType, Optional, Set, Tuple, Union
import py_codegen.astbuilder_nim as nim
from py_codegen.gen_tu_cpp import (
    GenTuEnum,
    GenTuEnumField,
    GenTuField,
    GenTuFunction,
    GenTuStruct,
    GenTuTypedef,
    QualType,
    QualTypeKind,
)
from py_codegen.refl_wrapper_graph import GenGraph, GenTuUnion
from py_scriptutils.files import file_relpath
from py_scriptutils.script_logging import log
from py_textlayout.py_textlayout_wrap import TextLayout, TextOptions
from pydantic import BaseModel, Field

if TYPE_CHECKING:
    from py_textlayout.py_textlayout_wrap import BlockId
else:
    BlockId = NewType('BlockId', int)


class WrapRenameRule(BaseModel):
    original: str = Field(description="Regex pattern for input text matching")
    renamed: str = Field(description="Replacement pattern")


class NimOptions(BaseModel):
    function_renames: List[WrapRenameRule] = Field(
        default=[], description="List of renaming rules for generated wrappers")
    universal_import: List[str] = Field(default=[],
                                        description="Import added to all generated files")

    common_function_pragmas: List[str] = Field(
        default=[],
        description="List of pragma annotations added to every function",
    )

    with_header_imports: bool = Field(
        default=True,
        description="Add header pragma annotations to generated entry wraps",
    )

    is_cpp_wrap: bool = Field(
        default=False,
        description="Generating wrappers for C++ or C code",
    )

    importx_structs: bool = Field(
        default=True, description="Generate 'importcpp' or 'import' for structures")

    def get_function_pragmas(self, func: GenTuFunction) -> List[nim.PragmaParams]:
        return [nim.PragmaParams(pragma) for pragma in self.common_function_pragmas]

    path_resolution_impl: Optional[Callable[[Path], str]] = None

    def get_header_str_for_path(self, path: Path) -> str:
        if self.path_resolution_impl:
            return self.path_resolution_impl(path)

        else:
            return str(path)


@beartype
def apply_rename(name: str, renames: List[WrapRenameRule]) -> str:
    for rule in renames:
        if re.match(rule.original, name):
            return re.sub(rule.original, rule.renamed, name)

    return name


@beartype
@dataclass
class ConvRes:
    # Result of the single entry conversion: main declaration and
    # additional wrapper structures and procedures accompanying it.
    procs: List[nim.FunctionParams] = field(default_factory=list)
    types: List[Union[nim.EnumParams, nim.ObjectParams,
                      nim.TypedefParams]] = field(default_factory=list)


@beartype
def type_to_nim(b: nim.ASTBuilder, t: QualType) -> nim.Type:
    if t.func:
        return nim.Type(Name="",
                        Kind=nim.TypeKind.Function,
                        Parameters=[
                            type_to_nim(b, t.func.ReturnTy),
                        ] + [type_to_nim(b, arg) for arg in t.func.Args])
    elif t.name == "char" and t.isConst and t.ptrCount == 1:
        return nim.Type("cstring")

    elif t.name == "char" and t.ptrCount == 2:
        return nim.Type("cstringArray")

    elif t.name == "void" and 1 <= t.ptrCount:
        result = nim.Type("pointer")
        for i in range(t.ptrCount - 1):
            result = nim.Type("ptr", Parameters=[result])

        return result

    elif t.Kind == QualTypeKind.Array:
        return nim.Type("array",
                        Parameters=[
                            type_to_nim(b, t.Parameters[1]),
                            type_to_nim(b, t.Parameters[0]),
                        ])

    elif t.Kind == QualTypeKind.TypeExpr:
        return nim.Type("", Kind=nim.TypeKind.Expr, Expr=b.string(t.expr))

    else:
        assert (t.Kind == QualTypeKind.RegularType)
        t_map = t.name
        match t.name:
            case "int":
                t_map = "cint"
            case "short":
                t_map = "cshort"
            case "unsigned short":
                t_map = "cushort"

            case "int":
                t_map = "cint"
            case "unsigned" | "unsigned int":
                t_map = "cuint"

            case "long":
                t_map = "clong"
            case "unsigned long":
                t_map = "culong"

            case "long long":
                t_map = "clonglong"
            case "unsigned long long":
                t_map = "culonglong"

            case "void":
                t_map = "void"

            case "char":
                t_map = "char"
            case "unsigned char":
                t_map = "uint8"

            case "float":
                t_map = "cfloat"
            case "double":
                t_map = "cdouble"
            case "bool":
                t_map = "bool"
            case "size_t":
                t_map = "csize_t"
            case "ssize_t":
                t_map = "csize_t"

            case "int8_t":
                t_map = "int8"
            case "int16_t":
                t_map = "int16"
            case "int32_t":
                t_map = "int32"
            case "int64_t":
                t_map = "int64"

            case "uint8_t":
                t_map = "uint8"
            case "uint16_t":
                t_map = "uint16"
            case "uint32_t":
                t_map = "uint32"
            case "uint64_t":
                t_map = "uint64"
            case "auto":
                t_map = "auto"

        result = nim.Type(Name=t_map)

        for i in range(t.ptrCount):
            result = nim.Type(Name="ptr", Parameters=[result])

        return result


@beartype
# Generate import from file placed in `result` to the content defined in `sub`
def gen_file_import(import_source: Path,
                    import_target: Path) -> Optional[nim.ImportParams]:
    if import_target.resolve() != import_source.resolve():
        return nim.ImportParams([
            nim.ImportParamsFile(file_relpath(import_source, import_target),
                                 "From gen file")
        ],
                                FormatMode=nim.ImportParamsMode.Single)


@beartype
def to_nim_imports(graph: GenGraph, sub: GenGraph.Sub,
                   get_out_path: Callable[[Path], Path]) -> nim.ImportParams:
    external: Set[int] = set()
    for _id in sub.nodes:
        for out in graph.graph.incident(_id, mode="out"):
            target = graph.graph.es[out].target
            if target not in sub.nodes:
                external.add(target)

    target_groups = [
        sub for sub in graph.subgraphs if 0 < len(sub.nodes.intersection(external))
    ]
    result = nim.ImportParams(QuoteImport=True, FormatMode=nim.ImportParamsMode.Single)
    for target in target_groups:
        import_source = get_out_path(sub.original)
        import_target = get_out_path(target.original)
        if import_source.resolve() != import_target.resolve():
            result.Imported.append(
                nim.ImportParamsFile(Name=file_relpath(import_source, import_target)))

    return result


@beartype
def enum_to_nim(b: nim.ASTBuilder, enum: GenTuEnum) -> ConvRes:
    result = ConvRes()
    c_name = "c_" + enum.name.name

    def f_name(f: GenTuEnumField) -> str:
        return nim.sanitize_name(f.name)

    def c_enum_field(idx: int, f: GenTuEnumField) -> nim.EnumFieldParams:
        if f.value == idx:
            value = str(f.value)

        elif f.value == 0:
            value = "0 shl 0"

        elif 0 < f.value and math.log2(f.value).is_integer():
            value = f"1 shl {int(math.log2(f.value))}"

        else:
            value = str(f.value)

        return nim.EnumFieldParams(Name="c_" + f_name(f), Value=b.string(value))

    fields: List[GenTuEnumField] = []

    for key, group in itertools.groupby(
            sorted(enum.fields, key=lambda f: f.value),
            key=lambda f: f.value,
    ):
        group: List[GenTuEnumField] = list(group)
        fields.append(group[0])
        if 1 < len(group):
            log("refl.nim").debug(
                f"More than one enum field for value {key}: [{[it.name for it in group]}]"
            )

    to_cint_name = "toCInt"

    w = max([len(f_name(f)) for f in fields] + [0])
    for config in [
            dict(kind=nim.FunctionKind.CONVERTER,
                 in_name=c_name,
                 out_name=enum.name.name,
                 is_c=True),
            dict(kind=nim.FunctionKind.PROC,
                 in_name=enum.name.name,
                 out_name=c_name,
                 is_c=False),
    ]:
        result.procs.append(
            nim.FunctionParams(
                Kind=config["kind"],
                Name="to_" + config["out_name"],
                Arguments=[nim.IdentParams(Name="arg", Type=nim.Type(config["in_name"]))],
                ReturnTy=nim.Type(config["out_name"]),
                Implementation=b.stack([
                    b.string("case arg:"),
                    b.indent(
                        2,
                        b.stack([
                            b.string(f"of c_{f_name(f).ljust(w)}: {f_name(f).ljust(w)}"
                                     if config["is_c"] else
                                     f"of {f_name(f).ljust(w)}: c_{f_name(f).ljust(w)}")
                            for f in fields
                        ]))
                ]),
            ))

    for expr, name in [
            # Implicit conversion of the C enum value to cint type
        ("cint(ord(arg))", c_name),
            # Implicit conversion of the Nim enum values to the cint type
        (f"cint(ord(to_{c_name}(arg)))", enum.name.name),
    ]:
        result.procs.append(
            nim.FunctionParams(
                Kind=nim.FunctionKind.CONVERTER,
                Name=to_cint_name,
                Arguments=[nim.IdentParams(Name="arg", Type=nim.Type(name))],
                ReturnTy=nim.Type("cint"),
                Implementation=b.string(expr),
                OneLineImpl=True,
            ))

    # Implicit map of the enum set to cint value
    result.procs.append(
        nim.FunctionParams(
            Kind=nim.FunctionKind.CONVERTER,
            Name=to_cint_name,
            Arguments=[
                nim.IdentParams(Name="args",
                                Type=nim.Type("set",
                                              Parameters=[nim.Type(enum.name.name)]))
            ],
            ReturnTy=nim.Type("cint"),
            Implementation=b.stack(
                b.string("for value in items(args):"),
                b.indent(
                    2,
                    b.string("case value:"),
                    b.indent(
                        2, *[
                            b.string(
                                f"of {f_name(f).ljust(w)}: result = cint(result or {f.value})"
                            ) for f in fields
                        ]),
                ),
            )))

    for op in ["-", "+"]:
        for arguments in [
            [
                nim.IdentParams("arg", nim.Type(c_name)),
                nim.IdentParams("offset", nim.Type("int"))
            ],
            [
                nim.IdentParams("offset", nim.Type("int")),
                nim.IdentParams("arg", nim.Type(c_name))
            ],
        ]:

            result.procs.append(
                nim.FunctionParams(
                    Kind=nim.FunctionKind.FUNC,
                    Name=op,
                    Arguments=arguments,
                    ReturnTy=nim.Type(c_name),
                    Implementation=b.string(f"cast[{c_name}](ord(arg) {op} offset)"),
                    OneLineImpl=True,
                ))

    result.types.append(
        nim.EnumParams(
            Name=c_name,
            Exported=True,
            Pragmas=[
                nim.PragmaParams(Name="size", Arguments=[
                    b.string("sizeof(cint)"),
                ]),
            ],
            Fields=[c_enum_field(idx, f) for idx, f in enumerate(fields)],
        ))

    result.types.append(
        nim.EnumParams(
            Name=enum.name.name,
            Exported=True,
            Fields=[
                nim.EnumFieldParams(Name=f_name(f), Value=b.string(str(idx)))
                for idx, f in enumerate(fields)
            ],
        ))

    return result


@beartype
def field_to_nim(
    b: nim.ASTBuilder,
    f: GenTuField,
    rec: GenTuStruct,
    conf: NimOptions,
) -> Tuple[nim.IdentParams, Optional[ConvRes]]:
    decl: Optional[ConvRes] = None
    if f.isTypeDecl:
        DeclType = f.decl.name.model_copy(update=dict(
            name=f"{rec.name.name}_{f.name}_field"))
        match f.decl:
            case GenTuStruct():
                decl = struct_to_nim(b, replace(f.decl, name=DeclType), conf)

            case GenTuEnum():
                decl = enum_to_nim(b, replace(f.decl, name=DeclType))

        result = nim.IdentParams(
            Name=nim.sanitize_name(f.name),
            Exported=True,
            Type=type_to_nim(b, DeclType),
        )

    else:
        result = nim.IdentParams(
            Name=nim.sanitize_name(f.name),
            Exported=True,
            Type=type_to_nim(b, f.type),
        )

    if result.Name != f.name:
        result.Pragmas.append(nim.PragmaParams("importc", [b.Lit(f.name)]))

    return (result, decl)


@beartype
def struct_to_nim(b: nim.ASTBuilder, rec: GenTuStruct, conf: NimOptions) -> ConvRes:
    pragmas: List[nim.PragmaParams] = []

    if conf.with_header_imports:
        pragmas.append(
            nim.PragmaParams("header",
                             [b.Lit(conf.get_header_str_for_path(rec.original))]))

    if conf.importx_structs:
        if conf.is_cpp_wrap:
            pragmas.append(nim.PragmaParams("importcpp"))

        else:
            pragmas.append(nim.PragmaParams("importc"))

    if rec.IsForwardDecl:
        pragmas.append(nim.PragmaParams("incompleteStruct"))

    else:
        pragmas.append(nim.PragmaParams("bycopy"))

    FieldDecls: List[nim.IdentParams] = []
    SubConvs: List[ConvRes] = []
    for f in rec.fields:
        Ident, Decls = field_to_nim(b, f, rec=rec, conf=conf)
        if Decls:
            SubConvs.append(Decls)

        FieldDecls.append(Ident)

    NestedTypes = list(itertools.chain(*[Sub.types for Sub in SubConvs]))
    Procs = list(
        itertools.chain(*[function_to_nim(b, meth, conf).procs
                          for meth in rec.methods])) + list(
                              itertools.chain(*[Sub.procs for Sub in SubConvs]))

    return ConvRes(
        types=[nim.ObjectParams(
            Name=rec.name.name,
            Pragmas=pragmas,
            Fields=FieldDecls,
        )] + NestedTypes,
        procs=Procs,
    )


@beartype
def typedef_to_nim(b: nim.ASTBuilder, typdef: GenTuTypedef) -> ConvRes:
    return ConvRes(types=[
        nim.TypedefParams(
            Name=typdef.name.name, Exported=True, Base=type_to_nim(b, typdef.base))
    ])


@beartype
def function_to_nim(b: nim.ASTBuilder, func: GenTuFunction, conf: NimOptions) -> ConvRes:
    arguments: List[nim.IdentParams] = []
    if conf.is_cpp_wrap:
        arguments.append(nim.IdentParams("self", type_to_nim(b, func.parentClass.name)))

    for Arg in func.arguments:
        arguments.append(nim.IdentParams(Arg.name, type_to_nim(b, Arg.type)))

    pragmas: List[nim.PragmaParams] = []

    pragmas += conf.get_function_pragmas(func)
    if conf.is_cpp_wrap:
        pragmas.append(nim.PragmaParams("importcpp", [b.Lit(f"#.{func.name}(@)")]))

    else:
        pragmas.append(nim.PragmaParams("importc", [b.Lit(func.name)]))

    if conf.with_header_imports:
        pragmas.append(
            nim.PragmaParams("header",
                             [b.Lit(conf.get_header_str_for_path(func.original))]))

    return ConvRes(procs=[
        nim.FunctionParams(
            Name=nim.sanitize_name(apply_rename(func.name, conf.function_renames)),
            ReturnTy=type_to_nim(b, func.result),
            Pragmas=pragmas,
            Arguments=arguments,
        )
    ])


@beartype
def conv_res_to_nim(builder: nim.ASTBuilder, decl: GenTuUnion,
                    conf: NimOptions) -> ConvRes:
    match decl:
        case GenTuEnum():
            return enum_to_nim(builder, decl)

        case GenTuStruct():
            return struct_to_nim(builder, decl, conf)

        case GenTuTypedef():
            return typedef_to_nim(builder, decl)

        case GenTuFunction():
            return function_to_nim(builder, decl, conf)

        case _:
            assert False


@beartype
@dataclass
class GenNimResult:
    content: Optional[str]
    conv: List[ConvRes]


@beartype
def to_nim(
    graph: GenGraph,
    sub: GenGraph.Sub,
    conf: NimOptions,
    get_out_path: Callable[[Path], Path],
    output_directory: Path,
) -> GenNimResult:
    t = TextLayout()
    builder = nim.ASTBuilder(t)

    types: List[BlockId] = []
    procs: List[BlockId] = []
    header: List[BlockId] = []
    depend_on: List[nim.ImportParams] = []

    for imp in sorted(conf.universal_import):
        gen = gen_file_import(get_out_path(sub.original), output_directory.joinpath(imp))
        if gen is not None:
            depend_on.append(gen)

    imports = to_nim_imports(graph, sub, get_out_path=get_out_path)
    if 0 < len(imports.Imported):
        depend_on.append(imports)

    collected_conv_res: List[ConvRes] = []

    for _id in sub.nodes:
        conv: ConvRes = conv_res_to_nim(builder, graph.id_to_entry[_id], conf)

        collected_conv_res.append(conv)

        for proc in conv.procs:
            procs.append(builder.Function(proc))

        for _type in sorted(conv.types, key=lambda it: it.Name):
            if isinstance(_type, nim.EnumParams):
                types.append(builder.Enum(_type))

            elif isinstance(_type, nim.ObjectParams):
                types.append(builder.Object(_type))

            elif isinstance(_type, nim.TypedefParams):
                types.append(builder.Typedef(_type))

    for item in depend_on:
        header.append(builder.Import(item))

    if 0 < len(types) or 0 < len(procs):
        opts = TextOptions()
        opts.rightMargin = 160
        stacked: BlockId
        if 0 < len(types):
            stacked = builder.sep_stack([
                *([t.stack(header)] if 0 < len(header) else []),
                t.stack([
                    t.text("type"),
                    t.indent(2, builder.sep_stack(types)),
                ]),
                t.text(""),
            ] + procs)

        else:
            stacked = t.stack(header + [builder.sep_stack(procs)])

        return GenNimResult(content=t.toString(stacked, opts), conv=collected_conv_res)

    else:
        return GenNimResult(content=None, conv=[])
