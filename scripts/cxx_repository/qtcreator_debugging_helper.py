#!/usr/bin/env python

from utils import DisplayFormat
from dumper import Children, SubItem, DumperBase
import dumper

print("Running debugger helper scrpt")


def std::stringData(d, value):
    # Calculate the string length and get the data pointer
    data, size, _ = d.stringData(value)

    # Extract the string data from memory
    raw = d.readMemory(data, 2 * size)
    return bytes.fromhex(raw).decode("utf-16le")


def sem_id_dump_common(d, value):
    print("Running dumper for ", value.type)
    try:
        readable_id = d.call("std::string", value, "getReadableId")
        kind = std::stringData(d, readable_id).split("_")[1]
        d.putStringValue(readable_id)
        d.putExpandable()
        d.putNumChild(3)
        if d.isExpanded():
            with Children(d, 3):
                d.putSubItem("ID", value["id"])
                d.putCallItem("Readable ID", "std::string", value, "getReadableId")
                underlying_type = "sem::" + kind
                print("Formatting value part as %s" % underlying_type)
                org_base_ptr = d.call(underlying_type, value, "get")
                if org_base_ptr.pointer() != 0:
                    sem_ptr = org_base_ptr.cast(underlying_type + "*")
                    d.putSubItem("SEM '" + kind + "'", sem_ptr.dereference())
                else:
                    d.putSubItem("SEM '" + kind + "'", "<Nil>")

        else:
            print("Not expanded")

    except Exception as e:
        print("__________ Sem ID dumper had error ________")
        print(e)


def qdump__OrgAdapter(d, value):
    d.putValue(value["id"]["value"].integer())


def qdump__sem_SemIdT(d, value, regex="^<.*?>"):
    sem_id_dump_common(d, value)


def qdump__sem__SemId(d, value):
    sem_id_dump_common(d, value)


def qdump__A(d, value):
    t = value.members(True)[0].type
    dptr, base_v = value.split("p{%s}" % t.name)
    d.putItem(base_v)
