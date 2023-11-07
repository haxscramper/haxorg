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
        content = '\n'.join(line.lstrip('* ') for line in content.splitlines())
        return process_content(content.splitlines())
    elif comment.startswith("//"):
        return process_content(comment[2:].splitlines())
    elif comment.startswith("/*"):
        # Removing the leading /* and potential trailing */
        content = comment[2:]
        if content.endswith("*/"):
            content = content[:-2]
        content = '\n'.join(line.lstrip('* ') for line in content.splitlines())
        return process_content(content.splitlines())
    else:
        raise ValueError(f"Unrecognized comment style: {comment}")


@beartype
def conv_proto_type(typ: pb.QualType) -> QualType:
    res: QualType = QualType(typ.name)
    for space in typ.spaces:
        res.Spaces.append(conv_proto_type(space))

    for param in typ.parameters:
        res.Parameters.append(conv_proto_type(param))

    res.isConst = typ.is_const
    res.isNamespace = typ.is_namespace
    res.isRef = typ.is_ref

    return res


@beartype
def conv_proto_record(record: pb.Record) -> GenTuStruct:
    result = GenTuStruct(record.name, GenTuDoc(""))
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
    result = GenTuEnum(en.name, GenTuDoc(""), [])
    for _field in en.fields:
        result.fields.append(GenTuEnumField(_field.name, GenTuDoc("")))

    return result

@beartype
@dataclass
class ConvTu:
    structs: List[GenTuStruct]
    functions: List[GenTuFunction]
    enums: List[GenTuEnum]

@beartype
def conv_proto_file(path: str) -> ConvTu:
    unit = pb.TU()
    assert os.path.exists(path)


    with open(path, "rb") as f:
        unit = pb.TU.FromString(f.read())

    with open("/tmp/reflection-structs.py", "w") as file:
        pprint(unit, width=200, stream=file)

    gen_structs: List[GenTuStruct] = [conv_proto_record(rec) for rec in unit.records]
    gen_enums: List[GenTuEnum] = [conv_proto_enum(rec) for rec in unit.enums]
    return ConvTu(structs=gen_structs, enums=gen_enums, functions=[])
