import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
import hstd_py_codegen.lang_build.astbuilder_proto as pb
from repo_py_orchestrate.codegen_config.codegen_type_groups import (
    PyhaxorgTypeGroups,
)
from repo_py_orchestrate.codegen_config.org_codegen_data import *


def gen(ast: cpp.ASTBuilder, groups: PyhaxorgTypeGroups, proto_out_root: Path):
    proto = pb.ProtoBuilder(
        wrapped=groups.get_protobuf_target_entires(),
        ast=ast,
        type_map=groups.type_map,
    )

    protobuf = proto.build_protobuf()

    return GenFiles(
        [
            GenUnit(
                header=GenTu(
                    proto_out_root.joinpath("SemOrgProto.proto"),
                    [
                        GenTuPass('syntax = "proto3";'),
                        GenTuPass("package orgproto;"),
                        GenTuPass('import "haxorg_cpp_org_lib/SemOrgProtoManual.proto";'),
                        GenTuPass(protobuf),
                    ],
                )
            ),
        ]
    )
