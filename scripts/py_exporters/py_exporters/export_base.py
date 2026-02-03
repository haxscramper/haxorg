import contextlib
import functools
import inspect
import re

from beartype import beartype
from beartype.typing import Any
from beartype.typing import Callable
from beartype.typing import Generator
from beartype.typing import List
from beartype.typing import Set
import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils import algorithm
from py_scriptutils.script_logging import log
from py_textlayout.py_textlayout_wrap import *


def with_export_context(func: Callable) -> Callable:

    @functools.wraps(func)
    def wrapper(self: Any, node: Any) -> Any:
        with self.WithContext(node):
            result = func(self, node)

        return result

    return wrapper


@beartype
class ExporterBase:
    context: List[org.Org]

    def evalTop(self, node: org.Org) -> Any:
        return self.exp.evalTop(node)

    def eval(self, node: org.Org) -> Any:
        return self.exp.eval(node)

    def enableFileTrace(self, path: str, colored: bool = False) -> Any:
        self.exp.enableFileTrace(path, colored)

    def printTrace(self, text: str) -> Any:
        frame = inspect.currentframe().f_back  # type: ignore
        assert frame
        info = inspect.getframeinfo(frame)
        self.exp.print_trace(text, info.filename, info.function, info.lineno)

    def getContextOfKind(self,
                         kind: org.OrgSemKind | Set[org.OrgSemKind]) -> List[org.Org]:
        if isinstance(kind, set):
            return [it for it in self.context if it.getKind() in kind]

        else:
            return [it for it in self.context if it.getKind() == kind]

    def isInInclude(self) -> bool:
        return 0 < len(self.getContextOfKind(org.OrgSemKind.CmdInclude))

    def isDefaultAdmonition(self, node: org.Paragraph) -> bool:
        return node.hasAdmonition() and 0 < len(
            set(node.getAdmonitions()).intersection(set(self.admonitionNames)))

    def getRealSubtreeLevel(self, node: org.Subtree) -> int:
        compound_level = 0
        for group in algorithm.partition_list(
                self.getContextOfKind(
                    set([org.OrgSemKind.Subtree, org.OrgSemKind.CmdInclude])),
                lambda it: it.getKind() == org.OrgSemKind.CmdInclude,
        ):
            if node != group[-1]:
                compound_level += group[-1].level

        return node.level + compound_level

    @contextlib.contextmanager
    def WithContext(self, node: org.Org) -> Generator[None, Any, Any]:
        self.context.append(node)
        yield
        self.context.pop()

    def __init__(self, derived: Any) -> None:
        self.exp = org.ExporterPython()
        self.context = []
        self.admonitionNames = [
            "IMPORTANT",
            "TODO",
            "DONE",
            "DOC",
            "FIXME",
            "HACK",
            "IDEA",
            "NOTE",
            "DEPRECATED",
            "REFACTOR",
            "STYLE",
            "BUG",
            "XXX",
            "XXXX",
            "IMPLEMENT",
            "IMPORTANT",
            "QUESTION",
            "TEST",
            "WARNING",
            "ERROR",
            "TEMP",
            "CONCLUSION",
            "NOTIFICATION",
            "GOAL",
            "DANGER",
            "MEMORIZE",
            "SUCCESS",
            "EXPERIMENT",
            "INFO",
            "ABSTRACT",
            "TIP",
        ]

        direct_mappings = {
            "visitAnyIdAround": self.exp.setVisitAnyIdAround,
            "visitAnyIdIn": self.exp.setVisitAnyIdIn,
            "visitAnyField": self.exp.setVisitAnyField,
            "evalTopCb": self.exp.setEvalTopCb,
            "setPushVisitAnyId": self.exp.setPushVisitAnyId,
            "setPopVisitAnyId": self.exp.setPopVisitAnyId,
            "visitAnyHook": self.exp.setVisitAnyHookCb,
            "newOrg": self.exp.setNewAnyOrgRes,
            "newLeaf": self.exp.setNewAnyLeafRes,
        }
        for method_name, setter in direct_mappings.items():
            if hasattr(derived, method_name):
                setter(getattr(type(derived), method_name))

        prefix_to_setter_with_kind = [
            (r"visit(.*)", self.exp.setVisitIdInCb),
            (r"eval(.*)", self.exp.setEvalIdIn),
            (r"visit(.*?)Around", self.exp.setVisitIdAround),
            (r"eval(.*?)Around", self.exp.setEvalIdAround),
            (r"visit(.*?)LeafField", self.exp.setVisitLeafField),
            (r"eval(.*?)LeafField", self.exp.setEvalLeafField),
            (r"visit(.*?)OrgField", self.exp.setVisitOrgField),
            (r"eval(.*?)OrgField", self.exp.setEvalOrgField),
            (r"setPushVisitId", self.exp.setPushVisitId),
            (r"setPopVisitIdCb", self.exp.setPopVisitIdCb),
            (r"visit(.*?)Hook", self.exp.setVisitIdHook),
            (r"newOrg(.*)", self.exp.setNewOrgRes),
            (r"newLeaf(.*)", self.exp.setNewLeafRes),
        ]

        for method_name in dir(derived):
            if method_name.startswith(
                    "__") or method_name in direct_mappings or method_name in ["evalTop"]:
                continue

            for (prefix, setter) in prefix_to_setter_with_kind:
                match = re.match(prefix, method_name)
                if match:
                    kind_str = match.group(1)
                    kind_enum = getattr(org.OrgSemKind, kind_str, None)

                    if len(kind_str) == 0:
                        continue

                    if not kind_enum:
                        kind_enum = getattr(org.LeafFieldType, kind_str, None)

                    if kind_enum:
                        setter(kind_enum, getattr(type(derived), method_name))
                        break

                    else:
                        log("haxorg.export").warning(
                            f"Method {method_name} (kind {kind_str}) of {type(derived)} is not a kind enum visitor, not OrgSemKind, not LeafFieldType"
                        )

        self.exp.setSelf(self)
