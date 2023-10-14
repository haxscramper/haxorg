#!/usr/bin/env python

import json
import logging
from dataclasses import dataclass
from typing import List
from plumbum import local
import os

from pydantic import BaseModel, root_validator
from typing import Optional

class LLVMSegment(BaseModel):
    line_number: int
    count: int
    another_number: int  # You can replace with an appropriate name.
    bool_val1: bool
    bool_val2: bool
    bool_val3: bool
    
    # Use a root validator to transform the list into the model's fields.
    @root_validator(pre=True)
    def parse_list_to_fields(cls, values):
        if isinstance(values, list):
            return {
                'line_number': values[0],
                'count': values[1],
                'another_number': values[2],
                'bool_val1': values[3],
                'bool_val2': values[4],
                'bool_val3': values[5]
            }
        return values


class LLVMCoverSummary(BaseModel):
    count: int
    covered: int
    percent: float
    notcovered: Optional[int] = None

class LLVMFileCoverageSummary(BaseModel):
    branches: LLVMCoverSummary
    functions: LLVMCoverSummary
    instantiations: LLVMCoverSummary
    lines: LLVMCoverSummary
    regions: LLVMCoverSummary

class LLVMFileCov(BaseModel):
    branches: List
    expansions: List
    filename: str
    segments: List[LLVMSegment]
    summary: LLVMFileCoverageSummary

class LLVMFunctionCov(BaseModel):
    branches: List[List[int]]
    count: int
    filenames: List[str]
    name: str
    regions: List[List[int]]

class LLVMCovInner(BaseModel):
    files: List[LLVMFileCov]
    functions: List[LLVMFunctionCov]

class LLVMCovData(BaseModel):
    type: str
    version: str
    data: List[LLVMCovInner]

def read_llvm_cov_from_json(filepath: str) -> LLVMCovData:
    with open(filepath, 'r') as f:
        data = f.read()
        return LLVMCovData.model_validate_json(data)

logging.basicConfig(level=logging.INFO)


@dataclass
class RunRecord:
    pgo_converted: str
    xray_converted: str


def find_files_with_prefix(directory: str, prefix: str) -> List[str]:
    return [
        f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f)) and
        f.startswith(prefix) and not (f.endswith("profdata") or f.endswith("json"))
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

        assert len(pgo_files
                  ) == 1, f"Expected single PGO file matching path, but found {pgo_files}"
        assert len(
            xray_files
        ) == 1, f"Expected single Xray file matching path {record['xray_path']}, but found {xray_files}"
        pgo_file = pgo_files[0]
        xray_file = xray_files[0]

        pgo_output_file = os.path.join(directory, f"{pgo_file}.json")
        pgo_tmp_file = pgo_output_file + ".profdata"
        local["llvm-profdata"][
            "merge",
            "-output=" + pgo_tmp_file,
            os.path.join(directory, pgo_file),
        ].run()

        base_binary = "/mnt/workspace/repos/haxorg/build/haxorg/bin/tests"

        logging.info(f"Converting PGO data for {pgo_output_file}...")
        llvm_cov = local["llvm-cov"][
            "export",
            base_binary,
            "-format=text",
            "-instr-profile=" + pgo_tmp_file,
        ] > pgo_output_file

        llvm_cov.run()

        xray_output_file = os.path.join(directory, f"{xray_file}.json")
        logging.info(f"Converting Xray data for {xray_output_file}...")
        local["llvm-xray"][
            "convert",
            "-symbolize",
            "-output-format=trace_event",
            "--instr_map=" + base_binary,
            "--output=" + xray_output_file,
            os.path.join(directory, xray_file),
        ].run()

        results.append(
            RunRecord(pgo_converted=pgo_output_file, xray_converted=xray_output_file))

    return results


if __name__ == "__main__":
    local.env.path.append("/mnt/workspace/repos/haxorg/toolchain/llvm/bin")
    logging.getLogger("plumbum.local").setLevel(logging.DEBUG)
    converted_records = convert_profiling_data("/tmp/compact_records.json")
    for record in converted_records:
        print(record)
        coverage_model = read_llvm_cov_from_json(record.pgo_converted)
