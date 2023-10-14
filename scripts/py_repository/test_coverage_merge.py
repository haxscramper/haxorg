#!/usr/bin/env python

import json
import logging
from dataclasses import dataclass
from typing import List
from plumbum import local
import os

logging.basicConfig(level=logging.INFO)


@dataclass
class RunRecord:
    pgo_converted: str
    xray_converted: str


def find_files_with_prefix(directory: str, prefix: str) -> List[str]:
    return [
        f for f in os.listdir(directory)
        if os.path.isfile(os.path.join(directory, f)) and f.startswith(prefix)
    ]


def convert_profiling_data(file_path: str) -> List[RunRecord]:
    directory = os.path.dirname(file_path)
    with open(file_path, 'r') as f:
        records = json.load(f)

    results = []
    for record in records:
        pgo_files = find_files_with_prefix(directory,
                                           os.path.basename(record["pgo_path"]))
        xray_files = find_files_with_prefix(directory,
                                            os.path.basename(record["xray_path"]))

        assert len(pgo_files) == 1
        assert len(
            xray_files
        ) == 1, f"Expected single Xray file matching path {record['xray_path']}, but found {xray_files}"
        pgo_file = pgo_files[0]
        xray_file = xray_files[0]

        logging.info(f"Converting PGO data for {pgo_file}...")
        pgo_output_file = os.path.join(directory, f"{pgo_file}.json")
        local["llvm-profdata"]["show", "-output-format=json",
                               os.path.join(directory, pgo_file)] > pgo_output_file

        logging.info(f"Converting Xray data for {xray_file}...")
        xray_output_file = os.path.join(directory, f"{xray_file}.json")
        local["llvm-xray"]["convert", "-symbolize", "-output-format=json",
                           os.path.join(directory, xray_file)] > xray_output_file

        results.append(
            RunRecord(pgo_converted=pgo_output_file, xray_converted=xray_output_file))

    return results


if __name__ == "__main__":
    converted_records = convert_profiling_data("/tmp/compact_records.json")
    for record in converted_records:
        print(record)
