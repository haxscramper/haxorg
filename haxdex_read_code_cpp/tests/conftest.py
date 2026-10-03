import sys
from pathlib import Path
from tempfile import TemporaryDirectory

import grpc_tools
import pytest
from beartype import beartype
from plumbum import local


@beartype
def pytest_configure(config: pytest.Config) -> None:
    package_dir = Path(__file__).resolve().parent.parent
    schema_dir = package_dir / "proto" / "haxdex_read_code_cpp"
    schema = schema_dir / "reflection_defs.proto"

    if not schema.is_file():
        raise FileNotFoundError(f"Reflection protobuf schema does not exist: {schema}")

    temporary = TemporaryDirectory(prefix="haxdex_read_code_cpp_proto_")
    config.add_cleanup(temporary.cleanup)

    generated_dir = Path(temporary.name)
    python_package = generated_dir / "haxdex_read_code_cpp"
    proto_package = python_package / "proto"
    proto_package.mkdir(parents=True)
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

    generated_path = str(generated_dir)
    sys.path.insert(0, generated_path)
    config.add_cleanup(lambda: sys.path.remove(generated_path))
