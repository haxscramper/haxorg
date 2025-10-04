#!/usr/bin/env python

from utils import DisplayFormat
from dumper import Children, SubItem, DumperBase
import dumper

print("Running debugger helper scrpt")


def std_string_Data(d, value):
    # Calculate the string length and get the data pointer
    data, size, _ = d.stringData(value)

    # Extract the string data from memory
    raw = d.readMemory(data, 2 * size)
    return bytes.fromhex(raw).decode("utf-16le")


def sem_id_dump_common(d, value):
    print("Running dumper for ", value.type)
    try:
        readable_id = d.call("std_string_", value, "getReadableId")
        kind = std_string_Data(d, readable_id).split("_")[1]
        d.putStringValue(readable_id)
        d.putExpandable()
        d.putNumChild(3)
        if d.isExpanded():
            with Children(d, 3):
                d.putSubItem("ID", value["id"])
                d.putCallItem("Readable ID", "std_string_", value, "getReadableId")
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

def qdump__DiaIdBase(d, value):
    print("Running dumper for DiaIdBase")
    try:
        # Get the raw value
        raw_value = value["value"].integer()
        
        # Constants from your code
        DiaIdMaskSize = 4 * 6  # 24 bits
        DiaIdMaskOffset = 8 * 8 - DiaIdMaskSize  # 64 - 24 = 40 bits
        
        # Extract the masked portion (upper 24 bits)
        mask = (1 << DiaIdMaskSize) - 1  # 0xFFFFFF
        masked_value = (raw_value >> DiaIdMaskOffset) & mask
        
        # Extract the lower portion (lower 40 bits)
        lower_mask = (1 << DiaIdMaskOffset) - 1  # 0xFFFFFFFFFF
        lower_value = raw_value & lower_mask
        
        # Display the raw value as hex
        d.putValue("0x%016x" % raw_value)
        d.putExpandable()
        d.putNumChild(3)
        
        if d.isExpanded():
            with Children(d, 3):
                d.putSubItem("Raw Value", "0x%016x (%d)" % (raw_value, raw_value))
                d.putSubItem("Masked Value (upper 24 bits)", "0x%06x (%d)" % (masked_value, masked_value))
                d.putSubItem("Lower Value (lower 40 bits)", "0x%010x (%d)" % (lower_value, lower_value))
    
    except Exception as e:
        print("__________ DiaIdBase dumper had error ________")
        print(e)
        d.putValue("<Error: %s>" % str(e))
