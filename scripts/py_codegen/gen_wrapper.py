#!/usr/bin/env python

from refl_read import conv_proto_file, ConvTu
from pprint import pprint

tu: ConvTu = conv_proto_file("/tmp/result.pb")

with open("/tmp/reflection_data.py", "w") as file:
    pprint(tu, width=200, stream=file)

print("Done")
