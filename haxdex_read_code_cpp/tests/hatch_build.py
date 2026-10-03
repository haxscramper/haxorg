import sys
from pathlib import Path

import grpc_tools
from beartype import beartype
from beartype.typing import Any
from hatchling.builders.hooks.plugin.interface import BuildHookInterface
from plumbum import local


class ProtoBuildHook(BuildHookInterface):
    @beartype
    def initialize(self, version: str, build_data: dict[str, Any]) -> None:
        root = Path(self.root)
        schema_dir = root.parent / "proto" / "haxdex_read_code_cpp"
        schema = schema_dir / "reflection_defs.proto"

        if not schema.is_file():
            raise FileNotFoundError(
                f"Reflection protobuf schema does not exist: {schema}"
            )

        output_dir = root / self.config["output-dir"]
        python_package = output_dir / "haxdex_read_code_cpp"
        proto_package = python_package / "proto"
        proto_package.mkdir(parents=True, exist_ok=True)
        (python_package / "__init__.py").write_text("", encoding="utf-8")

        protobuf_include = Path(grpc_tools.__file__).resolve().parent / "_proto"

        local[sys.executable](
            "-m",
            "grpc_tools.protoc",
            f"--proto_path={schema_dir}",
            f"--proto_path={protobuf_include}",
            f"--python_betterproto2_out={proto_package}",
            str(schema),
            str(protobuf_include / "google" / "protobuf" / "struct.proto"),
        )
