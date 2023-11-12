import proto_lib.reflection_defs as pb
import re

from beartype import beartype
from gen_tu_cpp import *
from pprint import pprint


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

    def drop_leading(prefix: re.Pattern, text: str) -> List[str]:
        result: List[str] = []
        for line in text.strip().splitlines():
            result.append(re.sub(prefix, "", line))

        return result

    # Identify and strip comment markers, then delegate to process_content
    if comment.startswith("///") or comment.startswith("//!"):
        return process_content(drop_leading("///", comment))
    elif comment.startswith("/**") or comment.startswith("/*!"):
        # Removing the leading /** or /*! and trailing */
        content = comment[3:-2].strip()
        # Remove any '*' prefixes that might exist on each line
        content = '\n'.join(line.strip().lstrip('* ') for line in content.splitlines())
        return process_content(content.splitlines())
    elif comment.startswith("//"):
        return process_content(comment[2:].splitlines())
    elif comment.startswith("/*"):
        # Removing the leading /* and potential trailing */
        content = comment[2:]
        if content.endswith("*/"):
            content = content[:-2]
        content = '\n'.join(line.strip().lstrip('* ') for line in content.splitlines())
        return process_content(content.splitlines())
    else:
        raise ValueError(f"Unrecognized comment style: {comment}")


@beartype
def conv_proto_type(typ: pb.QualType) -> QualType:
    res: QualType = QualType(typ.name)
    res.dbg_origin = typ.dbg_origin

    for space in typ.spaces:
        res.Spaces.append(conv_proto_type(space))

    match typ.kind:
        case pb.TypeKind.RegularType:
            for param in typ.parameters:
                res.Parameters.append(conv_proto_type(param))

            assert res.name != "", typ

        case pb.TypeKind.FunctionPtr:
            res.func = QualType.Function(
                ReturnTy=conv_proto_type(typ.parameters[0]),
                Args=[conv_proto_type(Arg) for Arg in typ.parameters[1:]]
                if 1 < len(typ.parameters) else [])

        case pb.TypeKind.Array:
            res.isArray = True
            res.Parameters = [ conv_proto_type(t) for t in typ.parameters ]


    res.isConst = typ.is_const
    res.isNamespace = typ.is_namespace
    res.isRef = typ.ref_kind != pb.ReferenceKind.NotRef
    

    return res


@beartype
def conv_proto_record(record: pb.Record) -> GenTuStruct:
    result = GenTuStruct(conv_proto_type(record.name), GenTuDoc(""))
    for _field in record.fields:
        result.fields.append(
            GenTuField(type=conv_proto_type(_field.type),
                       name=_field.name,
                       doc=conv_doc_comment(_field.doc)))

    for meth in record.methods:
        if meth.kind != pb.RecordMethodKind.Base:
            continue

        result.methods.append(
            GenTuFunction(
                result=conv_proto_type(meth.return_ty),
                name=meth.name,
                doc=conv_doc_comment(meth.doc),
                isConst=meth.is_const,
                arguments=[
                    GenTuIdent(conv_proto_type(arg.type), arg.name) for arg in meth.args
                ]))

    return result


@beartype
def conv_proto_enum(en: pb.Enum) -> GenTuEnum:
    result = GenTuEnum(conv_proto_type(en.name), GenTuDoc(""), [])
    for _field in en.fields:
        result.fields.append(GenTuEnumField(_field.name, GenTuDoc("")))

    return result


@beartype
def conv_proto_typedef(rec: pb.Typedef) -> GenTuTypedef:
    return GenTuTypedef(
        name=conv_proto_type(rec.name),
        base=conv_proto_type(rec.base_type),
    )


@beartype
@dataclass
class ConvTu:
    structs: List[GenTuStruct]
    functions: List[GenTuFunction]
    enums: List[GenTuEnum]
    typedefs: List[GenTuTypedef]


@beartype
def conv_proto_file(path: str) -> ConvTu:
    unit = pb.TU()
    assert os.path.exists(path)

    with open(path, "rb") as f:
        unit = pb.TU.FromString(f.read())

    with open("/tmp/reflection-structs.py", "w") as file:
        pprint(unit, width=200, stream=file)

    return ConvTu(structs=[conv_proto_record(rec) for rec in unit.records],
                  enums=[conv_proto_enum(rec) for rec in unit.enums],
                  typedefs=[conv_proto_typedef(rec) for rec in unit.typedefs],
                  functions=[])
