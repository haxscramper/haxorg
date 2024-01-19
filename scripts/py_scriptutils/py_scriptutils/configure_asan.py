from py_scriptutils.repo_files import get_haxorg_repo_root_path

import os 
import sys

root = get_haxorg_repo_root_path()
ld_preload = root.joinpath("toolchain/llvm/lib/clang/17/lib/x86_64-unknown-linux-gnu/libclang_rt.asan.so")
os.environ["LD_PRELOAD"] = str(ld_preload)
os.environ["ASAN_OPTIONS"] = "detect_leaks=0"
print("Configuring asan", ld_preload)
