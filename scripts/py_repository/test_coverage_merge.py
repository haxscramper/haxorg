#!/usr/bin/env python

import json
import logging
from dataclasses import dataclass, field
from dominate import document, tags
from plumbum import local
import os
from beartype import beartype
import csv

from pydantic import BaseModel, root_validator
from beartype.typing import Optional, List, Dict
from py_scriptutils.files import IsNewInput, pickle_or_new
from py_scriptutils import tracer
from py_scriptutils.script_logging import log
from collections import defaultdict


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


@dataclass
class RunRecord:
    pgo_converted: str
    xray_converted: str
    name: str


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
        force_convert = False
        if force_convert or IsNewInput(pgo_file, pgo_tmp_file):
            with tracer.GlobCompleteEvent(CAT, "Merge raw profile data"):
                local["llvm-profdata"][
                    "merge",
                    "-output=" + pgo_tmp_file,
                    os.path.join(directory, pgo_file),
                ].run()

        base_binary = "/mnt/workspace/repos/haxorg/build/haxorg/bin/tests"

        if force_convert or IsNewInput(pgo_tmp_file, pgo_output_file):
            with tracer.GlobCompleteEvent(CAT, "convert profile data to json"):
                log.info(f"Converting PGO data for {pgo_output_file}...")
                llvm_cov = local["llvm-cov"][
                    "export",
                    base_binary,
                    "-format=text",
                    "-instr-profile=" + pgo_tmp_file,
                ] > pgo_output_file

                llvm_cov.run()

        xray_output_file = os.path.join(directory, f"{xray_file}.json")
        if force_convert or IsNewInput(xray_file, xray_output_file):
            with tracer.GlobCompleteEvent(CAT, "convert xray data"):
                log.info(f"Converting Xray data for {xray_output_file}...")
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
            RunRecord(pgo_converted=pgo_output_file,
                      xray_converted=xray_output_file,
                      name=record["metadata"]["meta"]))

    return results


@beartype
@dataclass
class TestRunInfo:
    name: str


@beartype
@dataclass
class CoverReference:
    testname: str
    count: int


@beartype
@dataclass
class FileLine:
    text: str
    index: int
    covered_by: List[CoverReference] = field(default_factory=list)


@beartype
@dataclass
class FileCover:
    path: str
    lines: List[FileLine] = field(default_factory=list)

    @staticmethod
    def from_path(path: str) -> "FileCover":
        res = FileCover(path=path)
        with open(path, "r") as file:
            for idx, line in enumerate(file.readlines()):
                res.lines.append(FileLine(line, idx))

        return res


@beartype
@dataclass
class FullData:
    files: Dict[str, FileCover] = field(default_factory=dict)
    test_map: Dict[str, TestRunInfo] = field(default_factory=dict)


@beartype
def merge_coverage(data: FullData, cover: LLVMCovData, name: str):
    for entry in cover.data:
        for file in entry.files:
            path = file.filename
            if path not in data.files:
                data.files[path] = FileCover.from_path(path)

            file_cover = data.files[path]

            for segment in file.segments:
                file_cover.lines[segment.line - 1].covered_by.append(
                    CoverReference(testname=name, count=segment.count))


@beartype
def generate_html_table(file: FileCover) -> tags.table:
    table = tags.table()

    # Extract unique tests.
    test_set: set[str] = set()
    for line in file.lines:
        for cover in line.covered_by:
            test_set.add(cover.testname)

    tests: List[str] = sorted([t for t in test_set])

    with table:
        # Create table header.
        with tags.thead():
            with tags.tr():
                short = "width: 20px; background-color: #f2f2f2; writing-mode: vertical-rl; transform: rotate(180deg);"
                tags.th("Idx", style=short)

                for test in tests:
                    tags.th(test, style=short)

                tags.th(f'{file.path}')

        # Create table body.
        with tags.tbody():
            for line in file.lines:
                with tags.tr():
                    cover_map = defaultdict(int)  # Default to 0 for tests not present.
                    for cover in line.covered_by:
                        cover_map[cover.testname] = cover.count

                    tags.td(str(line.index))

                    for test in tests:
                        tags.td(cover_map[test])

                    tags.td(tags.pre(line.text))

    return table


@beartype
def write_as_csv(file: FileCover, outpath: str) -> tags.table:
    table = tags.table()

    # Extract unique tests.
    test_set: set[str] = set()
    for line in file.lines:
        for cover in line.covered_by:
            test_set.add(cover.testname)

    tests: List[str] = sorted([t for t in test_set])

    with open(outpath, "w", newline="") as f:
        writer = csv.writer(f, delimiter="\t", quoting=csv.QUOTE_ALL)

        writer.writerow(["Idx", *tests, "Path"])

        cover_map = defaultdict(int)
        for cover in line.covered_by:
            cover_map[cover.testname] = cover.count

        writer.writerow([line.index, *[cover_map[test] for test in tests], line.text])

    return table


@beartype
def generate_html_page(datasets: List[FileCover]) -> str:
    doc = document(title='Coverage Table')

    # Add table styling
    with doc.head:
        tags.style("""
        table { border-collapse: collapse; width: 100%; margin-bottom: 0px; }
        th, td { border: 0px; padding: 0px; margin: 0px; }
        pre { margin: 0; }

        thead th {
            position: sticky;
            top: 0;  /* Adjust this value based on where you want the header to stick */
            background-color: white;  /* Ensures the header remains opaque and content below doesn't show through */
            z-index: 10;  /* Keeps the header above other content */
        }

        tr:hover {
            background-color: #f5f5f5;  /* Change to your preferred highlight color */
        }
        """)

    with doc:
        for data in datasets:
            generate_html_table(data)

    return str(doc)


if __name__ == "__main__":
    local.env.path.append("/mnt/workspace/repos/haxorg/toolchain/llvm/bin")
    logging.getLogger("plumbum.local").setLevel(logging.DEBUG)

    with tracer.GlobCompleteEvent(CAT, "convert profiling data"):
        converted_records = convert_profiling_data("/tmp/compact_records.json")

    cover: FullData = FullData()
    with tracer.GlobCompleteEvent(CAT, "parse records"):
        for record in converted_records:
            print(record)
            coverage_model: LLVMCovData = pickle_or_new(record.pgo_converted,
                                                        record.pgo_converted + ".pickle",
                                                        read_llvm_cov_from_json)

            with tracer.GlobCompleteEvent(CAT, "merge coverage information"):
                merge_coverage(cover, coverage_model, record.name)

    with tracer.GlobCompleteEvent(CAT, "generate HTML page"):
        page = generate_html_page(
            [f for _, f in cover.files.items() if "Tokenizer" in f.path])
        with open("/tmp/result.html", "w") as file:
            file.write(page)
            log.info("Wrote HTML table")

    tracer.GlobExportJson("/tmp/profile_converter.json")
