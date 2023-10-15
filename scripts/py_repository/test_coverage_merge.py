#!/usr/bin/env python

import json
import logging
from dataclasses import dataclass
from typing import List
from plumbum import local
import os

from pydantic import BaseModel, root_validator
from typing import Optional
from py_scriptutils.files import IsNewInput, pickle_or_new
from py_scriptutils import tracer


class LLVMSegment(BaseModel):
    line: int
    column: int
    count: int
    has_count: bool
    in_region_entry: bool
    is_gap_region: bool

    @root_validator(pre=True)
    def parse_list_to_fields(cls, values):
        if isinstance(values, list):
            return {
                'line': values[0],
                'column': values[1],
                'count': values[2],
                'has_count': values[3],
                'in_region_entry': values[4],
                'is_gap_region': values[5]
            }
        return values


class LLVMBranch(BaseModel):
    line_start: int
    column_start: int
    line_end: int
    column_end: int
    count: int
    file_id: int
    expanded_file_id: int
    kind: int

    @root_validator(pre=True)
    def parse_list_to_fields(cls, values):
        if isinstance(values, list):
            return {
                'line_start': values[0],
                'column_start': values[1],
                'line_end': values[2],
                'column_end': values[3],
                'count': values[4],
                'file_id': values[5],
                'expanded_file_id': values[6],
                'kind': values[7],
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
    branches: List[LLVMBranch]
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
        f for f in os.listdir(directory)
        if os.path.isfile(os.path.join(directory, f)) and f.startswith(prefix) and
        not (f.endswith("profdata") or f.endswith("json") or f.endswith("pickle"))
    ]


CAT = "cov-merge"


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
        if IsNewInput(pgo_file, pgo_tmp_file):
            with tracer.GlobCompleteEvent(CAT, "Merge raw profile data"):
                local["llvm-profdata"][
                    "merge",
                    "-output=" + pgo_tmp_file,
                    os.path.join(directory, pgo_file),
                ].run()

        base_binary = "/mnt/workspace/repos/haxorg/build/haxorg/bin/tests"

        if IsNewInput(pgo_tmp_file, pgo_output_file):
            with tracer.GlobCompleteEvent(CAT, "convert profile data to json"):
                logging.info(f"Converting PGO data for {pgo_output_file}...")
                llvm_cov = local["llvm-cov"][
                    "export",
                    base_binary,
                    "-format=text",
                    "-instr-profile=" + pgo_tmp_file,
                ] > pgo_output_file

                llvm_cov.run()

        xray_output_file = os.path.join(directory, f"{xray_file}.json")
        if IsNewInput(xray_file, xray_output_file):
            with tracer.GlobCompleteEvent(CAT, "convert xray data"):
                logging.info(f"Converting Xray data for {xray_output_file}...")
                llvm_xray = local["llvm-xray"][
                    "convert",
                    "-symbolize",
                    "-output-format=trace_event",
                    "--instr_map=" + base_binary,
                    "--output=" + xray_output_file,
                    os.path.join(directory, xray_file),
                ]

                # llvm_xray.run()

        results.append(
            RunRecord(pgo_converted=pgo_output_file, xray_converted=xray_output_file))

    return results


if __name__ == "__main__":
    local.env.path.append("/mnt/workspace/repos/haxorg/toolchain/llvm/bin")
    logging.getLogger("plumbum.local").setLevel(logging.DEBUG)

    with tracer.GlobCompleteEvent(CAT, "convert profiling data"):
        converted_records = convert_profiling_data("/tmp/compact_records.json")

    with tracer.GlobCompleteEvent(CAT, "parse records"):
        for record in converted_records:
            print(record)
            coverage_model: LLVMCovData = pickle_or_new(record.pgo_converted,
                                                        record.pgo_converted + ".pickle",
                                                        read_llvm_cov_from_json)

    tracer.GlobExportJson("/tmp/profile_converter.json")
