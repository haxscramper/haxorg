import pydantic
import py_repository.gen_documentation as gen
from pydantic import BaseModel
from py_scriptutils.rich_utils import render_rich_pprint

def dbg(map: BaseModel) -> str:
    return render_rich_pprint(map.model_dump(), width=200, color=False)

def parse(code: str) -> gen.DocCxxFile:
    return gen.convert_cxx_tree(gen.parse_cxx(code))

def test_structure_extraction():
    record = parse("struct A {}; ").Content[0]
    assert isinstance(record, gen.DocCxxRecord)
    assert record.Name.model_dump() == "A", dbg(record)
    print(dbg(record))
