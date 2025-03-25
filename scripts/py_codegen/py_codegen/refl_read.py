from copy import copy

import py_codegen.proto_lib.reflection_tool.reflection_defs as pb
import re

from beartype import beartype
from py_codegen.gen_tu_cpp import *
from pathlib import Path
import json


@beartype
def conv_proto_default(value: pb.Expr) -> Optional[str]:
    if value.kind == pb.ExprKind.Lit and 0 < len(value.value):
        return value.value

    else:
        return None


@beartype
def strip_comment_prefixes(comment: str) -> List[str]:

    def drop_leading(prefix: re.Pattern, text: str) -> List[str]:
        result: List[str] = []
        for line in text.strip().splitlines():
            result.append(re.sub(prefix, "", line))

        return result

    # Identify and strip comment markers, then delegate to process_content
    if comment.startswith("///") or comment.startswith("//!"):
        return drop_leading("///?<?!?\\s*", comment)
    elif comment.startswith("/**") or comment.startswith("/*!"):
        # Removing the leading /** or /*! and trailing */
        content = comment[3:-2].strip()
        # Remove any '*' prefixes that might exist on each line
        content = '\n'.join(line.strip().lstrip('* ') for line in content.splitlines())
        return content.splitlines()
    elif comment.startswith("//"):
        return comment[2:].splitlines()
    elif comment.startswith("/*"):
        # Removing the leading /* and potential trailing */
        content = comment[2:]
        if content.endswith("*/"):
            content = content[:-2]
        content = '\n'.join(line.strip().lstrip('* ') for line in content.splitlines())
        return content.splitlines()
    else:
        raise ValueError(f"Unrecognized comment style: {comment}")


@beartype
def conv_doc_comment(comment: str) -> GenTuDoc:
    if not comment:
        return GenTuDoc("")

    # Helper function to process content after stripping comment markers
    def process_content(content: List[str]) -> GenTuDoc:
        brief, full = [], []
        is_brief = True

        for line in content:
            line = line.strip()
            if not line:
                is_brief = False
                continue

            if is_brief:
                brief.append(line)
            else:
                full.append(line)

        return GenTuDoc('\n'.join(brief), '\n'.join(full))

    return process_content(strip_comment_prefixes(comment))


@beartype
def conv_proto_type(typ: pb.QualType, is_anon_name: bool = False) -> QualType:
    res: QualType = QualType(name=typ.name)
    res.dbg_origin = typ.dbg_origin

    for space in typ.spaces:
        res.Spaces.append(conv_proto_type(space))

    match typ.kind:
        case pb.TypeKind.RegularType:
            res.isBuiltin = typ.is_builtin
            for param in typ.parameters:
                res.Parameters.append(conv_proto_type(param))

            # if not is_anon_name:
            #     assert res.name != "", typ

        case pb.TypeKind.FunctionPtr:
            res.Kind = QualTypeKind.FunctionPtr
            res.func = QualType.Function(
                ReturnTy=conv_proto_type(typ.parameters[0]),
                Args=[conv_proto_type(Arg) for Arg in typ.parameters[1:]]
                if 1 < len(typ.parameters) else [])

        case pb.TypeKind.Array:
            res.Kind = QualTypeKind.Array
            res.Parameters = [conv_proto_type(t) for t in typ.parameters]

        case pb.TypeKind.TypeExpr:
            res.Kind = QualTypeKind.TypeExpr
            res.expr = typ.type_value.value

    res.isConst = any([it.is_const for it in typ.qualifiers])
    res.isNamespace = typ.is_namespace
    res.RefKind = {
        pb.ReferenceKind.NotRef: ReferenceKind.NotRef,
        pb.ReferenceKind.LValue: ReferenceKind.LValue,
        pb.ReferenceKind.RValue: ReferenceKind.RValue,
    }[typ.ref_kind]

    res.ptrCount = len([it for it in typ.qualifiers if it.is_pointer])

    return res


@beartype
def conv_proto_record(record: pb.Record, original: Optional[Path]) -> GenTuStruct:
    result = GenTuStruct(
        conv_proto_type(record.name, is_anon_name=not record.has_name),
        GenTuDoc(""),
    )

    if record.reflection_params:
        try:
            result.reflectionParams = json.loads(record.reflection_params)

        except json.JSONDecodeError as e:
            e.add_note(f"While parsing reflection parameters for {result.name.format()}")
            e.add_note(f"Original text is '{record.reflection_params}'")

            raise e from None


    result.IsExplicitInstantiation = record.is_explicit_instantiation
    result.IsTemplateRecord = record.is_template_record
    result.original = copy(original)
    result.IsForwardDecl = record.is_forward_decl
    result.IsAbstract = record.is_abstract
    result.has_name = record.has_name

    for arg in record.explicit_template_params:
        result.ExplicitTemplateParams.append(conv_proto_type(arg))

    for _field in record.fields:
        if _field.is_type_decl:
            result.fields.append(
                GenTuField(type=None,
                           name=_field.name,
                           doc=conv_doc_comment(_field.doc),
                           isTypeDecl=True,
                           decl=conv_proto_record(_field.type_decl, original)))

        else:
            result.fields.append(
                GenTuField(
                    type=conv_proto_type(_field.type),
                    name=_field.name,
                    doc=conv_doc_comment(_field.doc),
                ))

    for base in record.bases:
        result.bases.append(conv_proto_type(base.name))

    for meth in record.methods:
        if meth.kind != pb.RecordMethodKind.Base:
            continue

        result.methods.append(
            GenTuFunction(result=conv_proto_type(meth.return_ty),
                          name=meth.name,
                          doc=conv_doc_comment(meth.doc),
                          isConst=meth.is_const,
                          isStatic=meth.is_static,
                          original=original,
                          arguments=[conv_proto_arg(arg) for arg in meth.args],
                          parentClass=result))

    for record in record.nested_rec:
        result.nested.append(conv_proto_record(record, original))

    for _enum in record.nested_enum:
        result.nested.append(conv_proto_enum(_enum, original))

    return result


@beartype
def conv_proto_enum(en: pb.Enum, original: Optional[Path]) -> GenTuEnum:
    result = GenTuEnum(conv_proto_type(en.name), GenTuDoc(""), [])
    result.IsForwardDecl = en.is_forward_decl
    result.original = copy(original)
    for _field in en.fields:
        result.fields.append(GenTuEnumField(_field.name, GenTuDoc(""),
                                            value=_field.value))

    if en.reflection_params:
        result.reflectionParams = json.loads(en.reflection_params)

    return result


@beartype
def conv_proto_arg(arg: pb.Arg) -> GenTuIdent:
    return GenTuIdent(name=arg.name,
                      type=conv_proto_type(arg.type),
                      value=conv_proto_default(arg.default))


@beartype
def conv_proto_function(rec: pb.Function, original: Optional[Path]) -> GenTuFunction:
    result = GenTuFunction(
        result=conv_proto_type(rec.result_ty),
        name=rec.name,
        arguments=[conv_proto_arg(arg) for arg in rec.arguments],
        doc=GenTuDoc(""),
        original=copy(original),
        spaces=[conv_proto_type(T) for T in rec.spaces],
    )

    if rec.reflection_params:
        result.reflectionParams = json.loads(rec.reflection_params)

    return result


@beartype
def conv_proto_typedef(rec: pb.Typedef, original: Optional[Path]) -> GenTuTypedef:
    return GenTuTypedef(
        name=conv_proto_type(rec.name),
        base=conv_proto_type(rec.base_type),
        original=original,
    )


@beartype
@dataclass
class ConvTu:
    structs: List[GenTuStruct]
    functions: List[GenTuFunction]
    enums: List[GenTuEnum]
    typedefs: List[GenTuTypedef]


@beartype
def open_proto_file(path: Path) -> pb.TU:
    unit = pb.TU()
    assert path.exists()

    with open(path, "rb") as f:
        unit = pb.TU.FromString(f.read())

    return unit


@beartype
def conv_proto_file(path: Path, original: Optional[Path] = None) -> ConvTu:
    unit = open_proto_file(path)
    return ConvTu(
        structs=[conv_proto_record(rec, original) for rec in unit.records],
        enums=[conv_proto_enum(rec, original) for rec in unit.enums],
        typedefs=[conv_proto_typedef(rec, original) for rec in unit.typedefs],
        functions=[conv_proto_function(rec, original) for rec in unit.functions],
    )
