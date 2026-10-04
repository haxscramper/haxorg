import importlib
from pathlib import Path


def verify(expected_version: int) -> dict:
    extension = importlib.import_module(f"{__name__}.ex_cpp_nanobind")
    assert extension.value() == expected_version

    definitions = importlib.import_module(f"{__name__}.proto.ex_shared")
    message = definitions.SharedResource(label=f"nanobind-{expected_version}")

    has_revision = 2 <= expected_version
    assert hasattr(message, "revision") is has_revision

    if has_revision:
        message.revision = expected_version

    restored = definitions.SharedResource().parse(bytes(message))
    assert restored.label == message.label

    if has_revision:
        assert restored.revision == expected_version

    return {
        "version": expected_version,
        "packages": {
            __name__: str(Path(__file__).resolve()),
        },
        "nanobind_file": str(Path(extension.__file__).resolve()),
        "nanobind_protobuf_file": str(Path(definitions.__file__).resolve()),
        "nanobind_shared_label": restored.label,
        "nanobind_revision_field": has_revision,
    }
