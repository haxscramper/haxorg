from hashlib import sha256
import json
import os
from pathlib import Path
import shutil
import subprocess
import time
from typing import Any, Dict, List, Union

import docker.types
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.workflow_utils import TaskContext

_MANIFEST_NAME = ".fuse_overlayfs_manifest.json"
_MANIFEST_VERSION = 1

# Notes that matter operationally on Arch:
# - Ensure `fuse-overlayfs` is installed.
# - If `allow_other=True`, `/etc/fuse.conf` must contain `user_allow_other` (uncommented), otherwise mounting will fail.
# - `squash_to_user=True` forces new/modified files in the COW layer to be owned by your host user (prevents root-owned artifacts).


def _is_mountpoint(p: Path) -> bool:
    # st_dev differs from parent for mountpoints
    try:
        return p.is_dir() and os.stat(p).st_dev != os.stat(p.parent).st_dev
    except FileNotFoundError:
        return False


def _ensure_dir(p: Path, mode: int = 0o755) -> None:
    p.mkdir(parents=True, exist_ok=True)
    # Ensure searchable by docker daemon (root) when using allow_other
    os.chmod(p, mode)


def _mount_to_dict(m: Any) -> Dict[str, Any]:
    # docker.types.Mount has to_dict(); sometimes you might have plain dicts too.
    if hasattr(m, "to_dict"):
        return m.to_dict()
    if isinstance(m, dict):
        return m
    raise TypeError(f"Unsupported mount object: {type(m)!r}")


def _stable_overlay_id(mount_dict: Dict[str, Any]) -> str:
    """
    Stable ID derived from bind source+target+ro to reuse the same COW dirs
    across repeated runs within a session (same cow_root).
    """
    src = str(mount_dict.get("Source", ""))
    tgt = str(mount_dict.get("Target", ""))
    ro = bool(mount_dict.get("ReadOnly", False))
    key = f"{src}\n{tgt}\n{int(ro)}\n"
    return sha256(key.encode("utf-8")).hexdigest()[:16]


def _load_manifest(cow_root: Path) -> Dict[str, Any]:
    mf = cow_root / _MANIFEST_NAME
    if not mf.exists():
        return {"version": _MANIFEST_VERSION, "overlays": []}
    with mf.open("r", encoding="utf-8") as f:
        data = json.load(f)
    return data


def _save_manifest(cow_root: Path, data: Dict[str, Any]) -> None:
    mf = cow_root / _MANIFEST_NAME
    tmp = cow_root / (mf.name + ".tmp")
    with tmp.open("w", encoding="utf-8") as f:
        json.dump(data, f, indent=2, sort_keys=True)
        f.write("\n")
    os.replace(tmp, mf)


def create_overlay_mount_points(
    ctx: TaskContext,
    *,
    mounts: List[docker.types.Mount],
    cow_root: Union[str, Path],
    allow_other: bool = True,
    squash_to_user: bool = True,
    mount_timeout_s: float = 2.0,
) -> List[docker.types.Mount]:
    """
    Replace eligible bind mounts with a bind mount of a FUSE overlay (copy-on-write).

    - Only processes mounts with Type='bind' and Source being an existing directory.
    - ReadOnly bind mounts are kept as-is (no overlay).
    - Overlay state is stored under `cow_root/overlays/<id>/{upper,work,merged}`.
    - A manifest is written to `cow_root/.fuse_overlayfs_manifest.json` so cleanup
      can be done later in a separate process.

    Requirements:
      - `fuse-overlayfs` installed
      - (recommended) /etc/fuse.conf has `user_allow_other` if allow_other=True
    """
    cow_root = Path(cow_root).resolve()
    _ensure_dir(cow_root, 0o755)
    overlays_root = cow_root / "overlays"
    _ensure_dir(overlays_root, 0o755)

    manifest = _load_manifest(cow_root)
    existing = {(o["id"], o["merged_dir"]): o for o in manifest.get("overlays", [])}

    out: List[docker.types.Mount] = []

    for m in mounts:
        md = _mount_to_dict(m)

        mtype = md.get("Type") or md.get("type")
        if mtype != "bind":
            out.append(m)
            continue

        src = md.get("Source")
        tgt = md.get("Target")
        ro = bool(md.get("ReadOnly", False))

        if not src or not tgt:
            out.append(m)
            continue

        src_path = Path(str(src)).resolve()
        if ro or (not src_path.exists()) or (not src_path.is_dir()):
            # Can't overlay files/nonexistent, and RO doesn't need COW
            out.append(m)
            continue

        oid = _stable_overlay_id(md)
        base = overlays_root / oid
        upper = base / "upper"
        work = base / "work"
        merged = base / "merged"
        _ensure_dir(base, 0o755)
        _ensure_dir(upper, 0o755)
        _ensure_dir(work, 0o755)
        _ensure_dir(merged, 0o755)

        if not _is_mountpoint(merged):
            opts = [
                f"lowerdir={src_path}",
                f"upperdir={upper}",
                f"workdir={work}",
            ]
            if squash_to_user:
                opts.append(f"squash_to_uid={os.getuid()}")
                opts.append(f"squash_to_gid={os.getgid()}")
            cmd = ["-o", ",".join(opts)]
            if allow_other:
                cmd += ["-o", "allow_other"]
            cmd += [str(merged)]
            run_command(ctx, "fuse-overlayfs", cmd)

            deadline = time.time() + mount_timeout_s
            while time.time() < deadline and not _is_mountpoint(merged):
                time.sleep(0.02)
            if not _is_mountpoint(merged):
                raise RuntimeError(f"Overlay mount did not become ready: {merged}")

        # Record/refresh manifest entry
        entry = {
            "id": oid,
            "lower_dir": str(src_path),
            "upper_dir": str(upper),
            "work_dir": str(work),
            "merged_dir": str(merged),
            "container_target": str(tgt),
            "created_uid": os.getuid(),
            "created_gid": os.getgid(),
        }
        # De-duplicate by id+merged_dir
        if (oid, str(merged)) not in existing:
            manifest.setdefault("overlays", []).append(entry)

        # Keep original propagation if set; default to rshared (safer for FUSE bind mounts)
        propagation = md.get("BindOptions", {}).get("Propagation") or getattr(
            m, "propagation", None) or "rshared"

        out.append(
            docker.types.Mount(
                target=str(tgt),
                source=str(merged),
                type="bind",
                read_only=False,
                propagation=propagation,
            ))

    manifest["version"] = _MANIFEST_VERSION
    _save_manifest(cow_root, manifest)
    return out


def cleanup_overlay_mount_points(
    ctx: TaskContext,
    *,
    cow_root: Union[str, Path],
    remove_cow_root: bool = False,
    lazy_umount: bool = False,
) -> None:
    """
    Unmount all overlay merged mountpoints recorded under cow_root and optionally
    remove the entire cow_root directory.

    This is intentionally separate from container lifecycle: call it whenever
    you're done with the session.
    """
    cow_root = Path(cow_root).resolve()
    manifest = _load_manifest(cow_root)
    overlays = manifest.get("overlays", [])

    # Unmount in reverse order to be safe
    for o in reversed(overlays):
        merged = Path(o["merged_dir"])
        if _is_mountpoint(merged):
            try:
                run_command(ctx, "fusermount3", ["-u", str(merged)])
            except subprocess.CalledProcessError:
                if lazy_umount:
                    run_command(ctx, "umount", ["-l", str(merged)])
                else:
                    raise

    if remove_cow_root:
        shutil.rmtree(cow_root, ignore_errors=True)
    else:
        # Keep state dirs, but remove manifest so next session can start clean if desired
        mf = cow_root / _MANIFEST_NAME
        if mf.exists():
            mf.unlink()
