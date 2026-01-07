from pydantic import BaseModel, Field
from beartype.typing import Optional, List
from pathlib import Path


class ExportUltraplainOptions(BaseModel, extra="forbid"):
    infile: Path = Field(default_factory=lambda: Path())
    outfile: Path = Field(default_factory=lambda: Path())


class ExportSQliteOptions(BaseModel, extra="forbid"):
    infile: List[Path]
    outfile: Path = Field(default_factory=lambda: Path())


class ExportHtmlOptions(BaseModel, extra="forbid"):
    infile: Path = Field(default_factory=lambda: Path())
    outfile: Path = Field(default_factory=lambda: Path())


class ExportPandocOptions(BaseModel, extra="forbid"):
    infile: Path = Field(default_factory=lambda: Path())
    outfile: Path = Field(default_factory=lambda: Path())
    debug_tree: Optional[Path] = None


class TexExportOptions(BaseModel, extra="forbid"):
    infile: Path = Field(default_factory=lambda: Path())
    outfile: Path = Field(default_factory=lambda: Path())
    do_compile: bool = Field(
        description="Compile the tex document if the export was successful", default=True)

    backend: str = Field(
        description="TeX backend to use",
        default="pdflatex",
    )


class TypstExportOptions(BaseModel, extra="forbid"):
    infile: Path = Field(default_factory=lambda: Path())
    outfile: Path = Field(default_factory=lambda: Path())
    trace_dir: Optional[str] = Field(
        description="Write processing logs to the directory",
        default=None,
    )

    do_compile: bool = Field(
        description="Compile the typst document if the export was successful",
        default=True)

    backend: str = Field(
        description="TeX backend to use",
        default="pdflatypst",
    )

    exportTraceFile: Optional[str] = Field(
        description="Write python export trace to this file",
        default=None,
        alias="export_trace_file")


class ExportOptions(BaseModel, extra="forbid"):
    ultraplain: Optional[ExportUltraplainOptions] = None
    sqlite: Optional[ExportSQliteOptions] = None
    html: Optional[ExportHtmlOptions] = None
    pandoc: Optional[ExportPandocOptions] = None
    typst: Optional[TypstExportOptions] = None
    tex: Optional[TexExportOptions] = None

    exportTraceFile: Optional[str] = Field(
        description="Write python export trace to this file",
        default=None,
        alias="export_trace_file")


class GenerateActivityAnalysisOptions(BaseModel):
    infile: List[Path]
    outdir: Path
    force_db: bool = False
    db_path: Optional[Path] = Field(
        default=None,
        description="Path to the generated SQLite DB, defaults to outdir/db.sqlite")


class GenerateMindMapOptions(BaseModel, extra="forbid"):
    infile: Path = Field(default_factory=lambda: Path())
    auto_build_elk: bool = True
    org_diagram_tool: Path = Field(
        default_factory=lambda: Path("build/example_qt_gui_org_diagram_release/org_diagram"))

    wrapper_dir: Path = Field(default_factory=lambda: Path(
        "scripts/py_scriptutils/py_scriptutils/graph_utils/elk_cli_wrapper"))


class GenerateNodeCloudOptions(BaseModel, extra="forbid"):
    infile: List[Path]
    outfile: Path = Field(default_factory=lambda: Path())


class ClockTimeAnalysisOptions(BaseModel, extra="forbid"):
    infile: List[Path]
    outfile: Path = Field(default_factory=lambda: Path())


class TagSortingOptions(BaseModel, extra="forbid"):
    input_dir: Path = Field(
        description="Input file or directory to analyze files in",
        default_factory=lambda: Path(),
    )

    tag_glossary_file: Path = Field(
        description=
        "org-mode file describing the tags. The structure of the file is not important, just that it uses tags in some way",
        default_factory=lambda: Path(),
    )

    output_dir: Optional[Path] = Field(default=None,
                                       description="Directory for all output files")

    autocomplete_file: Optional[Path] = Field(
        default=None,
        description="Optional file with one tag per line for autocomplete purposes")


class StoryGridOpts(BaseModel, extra="forbid"):
    infile: Path = Field(default_factory=lambda: Path())
    outfile: Path = Field(default_factory=lambda: Path())


class CodexTrackingOptions(BaseModel):
    target_file: Path
    codex_files: List[Path]
    outfile: Path
    cachedir: Optional[Path] = None


class GenerateOptions(BaseModel, extra="forbid"):
    node_clouds: Optional[GenerateNodeCloudOptions] = None
    subtree_clocking: Optional[ClockTimeAnalysisOptions] = None
    sort_tags: Optional[TagSortingOptions] = None
    story_grid: Optional[StoryGridOpts] = None
    activity_analysis: Optional[GenerateActivityAnalysisOptions] = None
    codex_tracking: Optional[CodexTrackingOptions] = None
    mind_map: Optional[GenerateMindMapOptions] = None


class RootOptions(BaseModel, extra="forbid"):
    baseToken_traceDir: Optional[str] = Field(
        description="Write lexer operation trace into the directory", default=None)
    tokenizer_traceDir: Optional[str] = None
    parse_traceDir: Optional[str] = None
    sem_traceDir: Optional[str] = None
    config: Optional[str] = None
    cache: Optional[Path] = Field(
        description=
        "Optional directory to cache file parsing to speed up large corpus processing",
        default=None)

    trace_path: Optional[str] = Field(
        description="Trace execution of the CLI to the file", default=None)

    generate: Optional[GenerateOptions] = None
    export: Optional[ExportOptions] = None
