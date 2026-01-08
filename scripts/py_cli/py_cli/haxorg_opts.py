from pydantic import BaseModel, Field, AfterValidator
from beartype.typing import Optional, List, Annotated, TypeVar
from pathlib import Path
from py_cli.haxorg_cli import CliField


def validate_readable_path(value: str | Path) -> Path:
    """Validate and return a Path object"""
    file_path = Path(value)

    if not file_path.exists():
        raise ValueError(f"File does not exist: {value}")

    if not file_path.is_file():
        raise ValueError(f"Path is not a file: {value}")

    return file_path


T = TypeVar('T')

ReadableFilePath = Annotated[Path, AfterValidator(validate_readable_path)]
SubcommandField = Annotated[Optional[T], CliField(is_option=False)]


class ExportUltraplainOptions(BaseModel, extra="forbid"):
    infile: ReadableFilePath = Field(default_factory=lambda: Path())
    outfile: Path = Field(default_factory=lambda: Path())


class ExportSQliteOptions(BaseModel, extra="forbid"):
    infile: List[ReadableFilePath]
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
    ultraplain: SubcommandField[ExportUltraplainOptions] = None
    sqlite: SubcommandField[ExportSQliteOptions] = None
    html: SubcommandField[ExportHtmlOptions] = None
    pandoc: SubcommandField[ExportPandocOptions] = None
    typst: SubcommandField[TypstExportOptions] = None
    tex: SubcommandField[TexExportOptions] = None

    exportTraceFile: Optional[str] = Field(
        description="Write python export trace to this file",
        default=None,
        alias="export_trace_file")


class GenerateActivityAnalysisOptions(BaseModel):
    infile: List[ReadableFilePath]
    outdir: Path
    force_db: bool = False
    db_path: Optional[Path] = Field(
        default=None,
        description="Path to the generated SQLite DB, defaults to outdir/db.sqlite")


class GenerateMindMapOptions(BaseModel, extra="forbid"):
    infile: ReadableFilePath = Field(default_factory=lambda: Path())
    auto_build_elk: bool = True
    org_diagram_tool: Path = Field(default_factory=lambda: Path(
        "build/example_qt_gui_org_diagram_release/org_diagram"))

    group_hyperedges: bool = True
    group_single_item_hyperedge: bool = True
    hyperedge_width: float = 2.0

    wrapper_dir: Path = Field(default_factory=lambda: Path(
        "scripts/py_cli/py_cli/generate/mind_map/elk_cli_wrapper"))


class GenerateNodeCloudOptions(BaseModel, extra="forbid"):
    infile: List[ReadableFilePath]
    outfile: Path = Field(default_factory=lambda: Path())


class ClockTimeAnalysisOptions(BaseModel, extra="forbid"):
    infile: List[ReadableFilePath]
    outfile: Path = Field(default_factory=lambda: Path())


class TagSortingOptions(BaseModel, extra="forbid"):
    input_dir: Path = Field(
        description="Input file or directory to analyze files in",
        default_factory=lambda: Path(),
    )

    tag_glossary_file: ReadableFilePath = Field(
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
    infile: ReadableFilePath = Field(default_factory=lambda: Path())
    outfile: Path = Field(default_factory=lambda: Path())


class CodexTrackingOptions(BaseModel):
    target_file: ReadableFilePath
    codex_files: List[ReadableFilePath]
    outfile: Path
    cachedir: Optional[Path] = None


class GenerateOptions(BaseModel, extra="forbid"):
    node_clouds: SubcommandField[GenerateNodeCloudOptions] = None
    subtree_clocking: SubcommandField[ClockTimeAnalysisOptions] = None
    sort_tags: SubcommandField[TagSortingOptions] = None
    story_grid: SubcommandField[StoryGridOpts] = None
    activity_analysis: SubcommandField[GenerateActivityAnalysisOptions] = None
    codex_tracking: SubcommandField[CodexTrackingOptions] = None
    mind_map: SubcommandField[GenerateMindMapOptions] = None


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

    tmp_dir: Path = Field(default_factory=lambda: Path("/tmp/haxorg_cli/tmp"))

    generate: SubcommandField[GenerateOptions] = None
    export: SubcommandField[ExportOptions] = None
