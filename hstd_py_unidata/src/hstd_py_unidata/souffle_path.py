from pathlib import Path


def get_serde_library_path() -> Path:
    library_path = Path(__file__).resolve().parent / "libhstd_cpp_souffle_serde.so"

    if not library_path.is_file():
        raise FileNotFoundError(library_path)

    return library_path
