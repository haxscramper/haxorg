import importlib
import shutil
import subprocess
from pathlib import Path


def verify(expected_version: int) -> dict:
    executable = shutil.which("ex_cpp_binary")
    assert executable is not None

    result = subprocess.run(
        [executable],
        check=True,
        stdout=subprocess.PIPE,
        text=True,
    )
    assert int(result.stdout.strip()) == expected_version

    binary = importlib.import_module(f"{__name__}.proto.ex_binary")
    shared = importlib.import_module(f"{__name__}.proto.ex_shared")
    well_known = importlib.import_module(f"{__name__}.proto.google.protobuf")

    resource = shared.SharedResource(label=f"shared-{expected_version}")
    message = binary.Record(
        payload=f"binary-{expected_version}",
        shared=resource,
        metadata=well_known.Struct(
            fields={
                "label": well_known.Value(string_value=resource.label),
            }
        ),
    )

    has_revision = 2 <= expected_version
    assert hasattr(resource, "revision") is has_revision
    assert hasattr(message, "revision") is has_revision

    if has_revision:
        resource.revision = expected_version
        message.revision = expected_version

    restored = binary.Record().parse(bytes(message))

    assert restored.payload == message.payload
    assert isinstance(restored.shared, shared.SharedResource)
    assert restored.shared.label == resource.label
    assert isinstance(restored.metadata, well_known.Struct)
    assert restored.metadata.fields["label"].string_value == resource.label

    if has_revision:
        assert restored.shared.revision == expected_version
        assert restored.revision == expected_version

    return {
        "version": expected_version,
        "packages": {
            __name__: str(Path(__file__).resolve()),
        },
        "executable_file": str(Path(executable).resolve()),
        "binary_protobuf_file": str(Path(binary.__file__).resolve()),
        "binary_shared_label": restored.shared.label,
        "binary_revision_field": has_revision,
    }
