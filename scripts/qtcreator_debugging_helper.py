#!/usr/bin/env python

from utils import DisplayFormat
from dumper import Children, SubItem, DumperBase

print("Running debugger helper scrpt")

def sem_id_dump_common(d, value):
    print("Running dumper for ", value.type)
    try:
        d.putValue("sem::SemId")
        d.putExpandable()
        d.putNumChild(3)
        if d.isExpanded():
            with Children(d, 3):
                print("Starting subnodes")
                d.putSubItem("ID", value["id"])
                print("One ok")
                d.putCallItem("Readable ID", "QString", value, "getReadableId")
                print("Two ok")
                d.putCallItem("SEM", "psem::Org", value, "get")
                print("Three ok")
                print("Done with subnodes")

        else:
            print("Not expanded")

    except Exception as e:
        print("__________ Sem ID dumper had error ________")
        print(e)

def qdump_sem_SemIdT(d, value, regex="^<.*?>"):
    sem_id_dump_common(d, value)

def qdump__sem__SemId(d, value):
    sem_id_dump_common(d, value)


def qdump__A(d, value):
    t = value.members(True)[0].type
    dptr, base_v = value.split("p{%s}" % t.name)
    d.putItem(base_v)
