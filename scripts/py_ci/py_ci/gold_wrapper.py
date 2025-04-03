#!/usr/bin/env python

import sys
import subprocess
import time
import os
import logging
from pathlib import Path
from datetime import datetime
from typing import List, Dict, Any, Optional

logging.basicConfig(level=logging.INFO,
                    format="%(asctime)s - %(levelname)s - %(message)s")
logger = logging.getLogger(__name__)


def run_gold_linker(args: List[str]) -> int:
    start_time = time.time()

    # Extract the output file name from arguments
    output_file: Optional[str] = None
    for i, arg in enumerate(args):
        if arg == "-o" and i + 1 < len(args):
            output_file = args[i + 1]
            break

    if not output_file:
        logger.error("Could not find output file in linker arguments")
        return 1

    # Create a unique profile name based on the output filename
    target_name = Path(output_file).name
    profile_path = Path(f"/tmp/{target_name}_link_profile.log")

    # Run the actual gold linker and capture its output
    cmd = ["ld.gold"] + args

    logger.info(f"Running gold linker for target: {target_name}")
    logger.info(f"Profile will be saved to: {profile_path}")

    # Start profiling
    profile_data: Dict[str, Any] = {
        "target": target_name,
        "command": " ".join(cmd),
        "start_time": datetime.now().isoformat(),
        "args": args
    }

    # Run the linker with stats enabled
    process = subprocess.run(cmd + ["--stats"],
                             stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE,
                             text=True)

    end_time = time.time()
    duration = end_time - start_time

    # Update profile data
    profile_data["duration"] = duration
    profile_data["exit_code"] = process.returncode
    profile_data["end_time"] = datetime.now().isoformat()
    profile_data["stdout"] = process.stdout
    profile_data["stderr"] = process.stderr

    # Write profile to file
    with open(profile_path, "w") as f:
        f.write(f"Target: {target_name}\n")
        f.write(f"Command: {' '.join(cmd)}\n")
        f.write(f"Duration: {duration:.2f} seconds\n\n")
        f.write("=== STDOUT ===\n")
        f.write(process.stdout)
        f.write("\n=== STDERR ===\n")
        f.write(process.stderr)

    logger.info(
        f"Linking completed in {duration:.2f} seconds with exit code {process.returncode}"
    )
    return process.returncode


if __name__ == "__main__":
    sys.exit(run_gold_linker(sys.argv[1:]))
