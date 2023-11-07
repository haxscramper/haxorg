#!/usr/bin/env python

from refl_read import conv_proto_file
from pprint import pprint

gen_structs, gen_enums = conv_proto_file("/tmp/result.pb")

with open("/tmp/reflection_data.py", "w") as file:
    pprint(gen_structs, width=200, stream=file)
    pprint(gen_enums, width=200, stream=file)
