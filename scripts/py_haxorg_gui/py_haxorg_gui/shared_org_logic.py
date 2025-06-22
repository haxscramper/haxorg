import py_haxorg.pyhaxorg_wrap as org
from beartype import beartype
from beartype.typing import Any, List, Optional, Iterator, Tuple, Dict
from pathlib import Path
import json
import traceback
from py_scriptutils.script_logging import log, pprint_to_file, to_debug_json
import functools
from py_haxorg.pyhaxorg_utils import evalDateTime, getFlatTags
from datetime import datetime, timedelta

CAT = __name__

COMPLETED_TASK_SET = set(["DONE", "FAILED", "COMPLETED", "CANCELED"])
AGENDA_NODE_TYPES = [
    org.OrgSemKind.Subtree,
    org.OrgSemKind.Document,
    org.OrgSemKind.Directory,
    org.OrgSemKind.File,
    org.OrgSemKind.Symlink,
]

@beartype
def get_org_file_times(infile: Path) -> Dict[str, float]:
    current_times: Dict[str, float] = {}
    for org_file in infile.glob("*.org"):
        current_times[str(org_file)] = org_file.stat().st_mtime
    return current_times

@beartype
def check_org_files_changed(infile: Path, cache_file: Path) -> bool:
    current_times = get_org_file_times(infile)

    if not cache_file.exists():
        return True

    with open(cache_file, "r") as f:
        cached_times: Dict[str, float] = json.load(f)

    return current_times != cached_times

@beartype
def write_org_file_cache(infile: Path, cache_file: Path) -> None:
    current_times = get_org_file_times(infile)

    with open(cache_file, "w") as f:
        json.dump(current_times, f)


@beartype
def load_cached_imm_node(
    infile: Path,
    graph_path: Path,
    context_path: Path,
    epoch_path: Path,
    cache_file: Path,
) -> org.Org:
    dir_opts = org.OrgDirectoryParseParameters()
    parse_opts = org.OrgParseParameters()
    stack_file = open("/tmp/stack_dumps.txt", "w")

    if check_org_files_changed(infile, cache_file):

        def parse_node_impl(path: str):
            try:
                return org.parseStringOpts(Path(path).read_text(), parse_opts)

            except Exception as e:
                print(f"Parsing {path}", file=stack_file)
                traceback.print_exc(file=stack_file)
                # log(CAT).info(f"Failed parsing {path}", exc_info=e, stack_info=True, )
                return org.Empty()

        org.setGetParsedNode(dir_opts, parse_node_impl)

        node = org.parseDirectoryOpts(str(infile), dir_opts)
        initial_context = org.initImmutableAstContext()
        log(CAT).info("Adding immutable AST root")
        version = initial_context.addRoot(node)

        graph_state: org.graphMapGraphState = org.graphMapGraphState.FromAstContextStatic(
            version.getContext())

        conf = org.graphMapConfig()
        root = version.getRootAdapter()

        log(CAT).info("Recursively adding graph state node")
        graph_state.addNodeRec(version.getContext(), root, conf)

        log(CAT).info("Serialize graph state to binary")
        graph_path.write_bytes(org.serializeMapGraphToText(graph_state.graph))
        log(CAT).info("Serialize context to binary")
        context_path.write_bytes(org.serializeAstContextToText(version.getContext()))
        epoch_path.write_bytes(org.serializeAstReplaceEpochToText(version.getEpoch()))
        write_org_file_cache(infile, cache_file)

    else:
        initial_context: org.ImmAstContext = org.initImmutableAstContext()
        org.serializeAstContextFromText(context_path.read_bytes(), initial_context)
        version: org.ImmAstVersion = initial_context.getEmptyVersion()
        org.serializeAstReplaceEpochFromText(epoch_path.read_bytes(), version.getEpoch())
        node = initial_context.get(version.getRoot())

        graph_state: org.graphMapGraphState = org.graphMapGraphState.FromAstContextStatic(
            version.getContext())

        org.serializeMapGraphFromText(graph_path.read_bytes(), graph_state.graph)

    return node


@beartype
class OrgAgendaNode:

    def __init__(self,
                 data: org.Org,
                 parent: Optional["OrgAgendaNode"] = None,
                 children: List["OrgAgendaNode"] = []):
        assert data.getKind() in AGENDA_NODE_TYPES
        self.data = data
        self.parent = parent
        if not children:
            children = list()

        self.children: List["OrgAgendaNode"] = children

    @functools.cache
    def get_priority(self) -> str:
        if isinstance(self.data, org.Subtree):
            return self.data.priority or ""

        else:
            return ""

    @functools.cache
    def get_clock_periods(self,
                          recursive: bool = False) -> List[Tuple[datetime, datetime]]:
        result = []

        def aux(node: OrgAgendaNode):
            nonlocal result
            if isinstance(node.data, org.Subtree):
                time: org.SubtreePeriod
                for time in node.data.getTimePeriods(
                        org.IntSetOfSubtreePeriodKind([org.SubtreePeriodKind.Clocked])):
                    if time.to and time.from_:
                        from_ = evalDateTime(time.from_)
                        to = evalDateTime(time.to)
                        result.append((from_, to))

            if recursive:
                for sub in node.children:
                    aux(sub)

        aux(self)

        return result

    @functools.cache
    def get_clocked_seconds(self, recursive: bool = True) -> int:
        result = 0

        for from_, to in self.get_clock_periods(self, recursive):
            result += (to - from_).seconds

        return result

    def is_event(self) -> bool:
        return bool(self.get_scheduled_time() or self.get_deadline_time())

    def get_duration(self) -> Optional[timedelta]:
        if isinstance(self.data, org.Subtree):
            return None
            # return self.data.du

    def get_scheduled_time(self) -> Optional[datetime]:
        if isinstance(self.data, org.Subtree):
            return self.data.scheduled and evalDateTime(self.data.scheduled)

    def get_deadline_time(self) -> Optional[datetime]:
        if isinstance(self.data, org.Subtree):
            return self.data.deadline and evalDateTime(self.data.deadline)

    def get_closed_time(self) -> Optional[datetime]:
        if isinstance(self.data, org.Subtree):
            return self.data.closed and evalDateTime(self.data.closed)

    def get_created_time(self) -> Optional[datetime]:
        return None

        
    @functools.cache
    def get_recursive_completion(self) -> Tuple[int, int]:
        nom = 0
        denom = 0

        def aux(node: OrgAgendaNode):
            nonlocal nom
            nonlocal denom
            if node.get_todo() != "":
                if node.get_todo() in COMPLETED_TASK_SET:
                    nom += 1
                    denom += 1

                else:
                    denom += 1

            for sub in node.children:
                aux(sub)

        aux(self)

        return (nom, denom)

    @functools.cache
    def get_priority_order(self) -> int:
        priority = self.get_priority()
        priority_order = {
            "X": 0,
            "S": 1,
            "A": 2,
            "B": 3,
            "C": 4,
            "D": 5,
            "E": 6,
            "F": 7,
        }
        return priority_order.get(priority, -1)

    @functools.cache
    def get_tags(self) -> List[str]:
        if isinstance(self.data, org.Subtree):
            result = []
            for tag in self.data.tags:
                for flat in getFlatTags(tag):
                    result.append("##".join(flat))

            return result

        else:
            return []

    @functools.cache
    def get_age_seconds(self) -> int:
        if isinstance(self.data, org.Subtree):
            created: List[org.SubtreePeriod] = self.data.getTimePeriods(
                org.IntSetOfSubtreePeriodKind([org.SubtreePeriodKind.Created]))
            if created:
                return int(
                    (datetime.now() - evalDateTime(created[0].from_)).total_seconds())

        return 0

    @functools.cache
    def get_age_display(self) -> str:
        seconds = self.get_age_seconds()

        if seconds == 0:
            return ""

        units = [
            ("y", 365 * 24 * 3600),
            ("mo", 30 * 24 * 3600),
            ("w", 7 * 24 * 3600),
            ("d", 24 * 3600),
            ("h", 3600),
            ("m", 60),
            ("s", 1),
        ]

        parts = []
        for unit_name, unit_seconds in units:
            if seconds >= unit_seconds:
                count = seconds // unit_seconds
                parts.append(f"{count}{unit_name}")
                seconds %= unit_seconds
                if len(parts) == 2:
                    break

        return "".join(parts) if parts else "0s"

    def push_back(self, other: "OrgAgendaNode"):
        assert other.data.getKind() in AGENDA_NODE_TYPES
        self.children.append(other)

    def __iter__(self) -> Iterator["OrgAgendaNode"]:
        return self.children.__iter__()

    def __getitem__(self, idx: int) -> "OrgAgendaNode":
        return self.children[idx]

    def __len__(self) -> int:
        return len(self.children)

    @functools.cache
    def get_title(self) -> str:
        if isinstance(self.data, org.Subtree):
            return self.data.getCleanTitle()

        elif isinstance(self.data, org.File):
            return self.data.relPath

        elif isinstance(self.data, org.Directory):
            return self.data.relPath

        else:
            return str(self.data.getKind())

    @functools.cache
    def get_todo(self) -> str:
        if isinstance(self.data, org.Subtree):
            return self.data.todo or ""

        else:
            return ""

    @functools.cache
    def get_level(self) -> int:
        try:
            if hasattr(self.data, "getLevel"):
                return self.data.getLevel()
            return 0
        except (AttributeError, TypeError):
            return 0

    @functools.cache
    def get_creation_date(self) -> str:
        if isinstance(self.data, org.Subtree):
            created: List[org.SubtreePeriod] = self.data.getTimePeriods(
                org.IntSetOfSubtreePeriodKind([org.SubtreePeriodKind.Created]))
            if created:
                return evalDateTime(created[0].from_).strftime("%Y-%m-%d %H:%M")

        return ""

    def is_closed(self) -> bool:
        try:
            if hasattr(self.data, "isClosed"):
                return self.data.isClosed()
            return False
        except (AttributeError, TypeError):
            return False

    def get_kind(self) -> org.OrgSemKind:
        return self.data.getKind()


@beartype
def build_genda_tree(node: org.Org, parent: Optional[OrgAgendaNode]) -> OrgAgendaNode:
    result = OrgAgendaNode(data=node, parent=parent)
    for sub in node:
        if sub.getKind() in AGENDA_NODE_TYPES:
            added = build_genda_tree(sub, result)
            completion = added.get_recursive_completion()
            if completion[1] != 0:
                result.push_back(added)

    return result


@beartype
def pprint_node(node: org.Org, path: Path):

    def override_node(n: Any):
        if isinstance(n, org.Org):
            return str(n.getKind())

    pprint_to_file(
        to_debug_json(
            node,
            override_callback=override_node,
        ),
        str(path),
    )
