import json
import shutil
import sys
from pathlib import Path
from typing import Any


def _select_file(
    directories: list[Path],
    pattern: str,
    *,
    recursive: bool = False,
) -> Path:
    matches: set[Path] = set()

    for directory in directories:
        paths = directory.rglob(pattern) if recursive else directory.glob(pattern)
        matches.update(path.resolve() for path in paths if path.is_file())

    if len(matches) != 1:
        formatted = "\n".join(f"  {path}" for path in sorted(matches))
        raise RuntimeError(
            f"Expected exactly one file matching {pattern!r}, "
            f"found {len(matches)}.\n"
            f"Searched directories: {directories}\n"
            f"Matches:\n{formatted}"
        )

    return next(iter(matches))


def _artifact_source(
    dependency: Any,
    config: dict[str, Any],
) -> Path:
    package_type = config.get("package_type")
    pattern = config["artifact"]

    if package_type == "application":
        return _select_file(
            [Path(directory) for directory in dependency.cpp_info.bindirs],
            pattern,
        )

    if package_type in ("shared-library", "static-library"):
        return _select_file(
            [Path(directory) for directory in dependency.cpp_info.libdirs],
            pattern,
        )

    if package_type is not None:
        raise ValueError(f"Unsupported artifact package_type: {package_type!r}")

    # Preserve existing package-relative artifact configurations.
    if dependency.package_folder is None:
        raise RuntimeError(
            f"{dependency.ref}: no package folder for legacy artifact lookup"
        )

    return _select_file(
        [Path(dependency.package_folder)],
        pattern,
        recursive=True,
    )


def deploy(
    graph: Any,
    output_folder: str,
    **kwargs: Any,
) -> None:
    root = graph.root.conanfile

    configuration_path = root.conf.get(
        "user.haxorg:hatch_deployment",
        check_type=str,
    )

    if not configuration_path:
        raise ValueError("Missing user.haxorg:hatch_deployment configuration")

    with Path(configuration_path).open(encoding="utf-8") as file:
        configuration = json.load(file)

    reference = configuration["reference"].split("#", maxsplit=1)[0]
    dependencies = list(root.dependencies.host.values())

    matching_dependencies = [
        dependency
        for dependency in dependencies
        if str(dependency.ref).split("#", maxsplit=1)[0] == reference
    ]

    if len(matching_dependencies) != 1:
        raise RuntimeError(
            f"Expected exactly one host dependency for {reference!r}, "
            f"found {len(matching_dependencies)}"
        )

    dependency = matching_dependencies[0]
    output = Path(output_folder)
    output.mkdir(parents=True, exist_ok=True)

    manifest: dict[str, Any] = {
        "artifacts": [],
        "protobuf": None,
    }

    for index, artifact_config in enumerate(configuration["artifacts"]):
        source = _artifact_source(dependency, artifact_config)

        print(
            f"[hatch-conan-deployer] "
            f"reference={dependency.ref} "
            f"package_folder={dependency.package_folder} "
            f"bindirs={dependency.cpp_info.bindirs} "
            f"source={source} "
            f"size={source.stat().st_size}",
            file=sys.stderr,
            flush=True,
        )

        relative_destination = Path("artifacts") / str(index) / source.name
        destination = output / relative_destination
        destination.parent.mkdir(parents=True, exist_ok=True)

        shutil.copy2(source, destination)

        manifest["artifacts"].append(
            {
                "source": relative_destination.as_posix(),
                "destination": (
                    Path(artifact_config.get("destination", "")) / source.name
                ).as_posix(),
                "package_type": artifact_config.get("package_type"),
            }
        )

    protobuf_config = configuration.get("protobuf")

    if protobuf_config is not None:
        resource_roots: dict[Path, Path] = {}

        # Protobuf dependency resolution is transitive for all
        # packages.
        resource_dependencies = [
            node.conanfile
            for node in graph.nodes
            if node is not graph.root
            and node.conanfile is not None
            and node.conanfile.package_folder is not None
        ]

        for dependency_index, resource_dependency in enumerate(resource_dependencies):
            for resource_index, directory in enumerate(
                resource_dependency.cpp_info.resdirs
            ):
                source_root = Path(directory).resolve()

                if not source_root.is_dir():
                    continue

                if not any(source_root.rglob("*.proto")):
                    continue

                if source_root not in resource_roots:
                    relative_root = (
                        Path("schemas") / str(dependency_index) / str(resource_index)
                    )
                    shutil.copytree(source_root, output / relative_root)
                    resource_roots[source_root] = relative_root

        sources = []
        source_roots = list(resource_roots)

        for relative_source in protobuf_config["sources"]:
            source = _select_file(source_roots, relative_source)

            containing_roots = [
                directory
                for directory in source_roots
                if source.is_relative_to(directory)
            ]

            if len(containing_roots) != 1:
                raise RuntimeError(
                    f"Expected one owning resource directory for {source}, "
                    f"found {len(containing_roots)}"
                )

            source_root = containing_roots[0]
            staged_source = resource_roots[source_root] / source.relative_to(source_root)
            sources.append(staged_source.as_posix())

        manifest["protobuf"] = {
            "include-roots": [
                directory.as_posix() for directory in resource_roots.values()
            ],
            "sources": sources,
        }

    with (output / "manifest.json").open("w", encoding="utf-8") as file:
        json.dump(manifest, file, indent=2)
