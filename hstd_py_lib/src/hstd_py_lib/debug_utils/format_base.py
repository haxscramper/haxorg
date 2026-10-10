import sys
import traceback
from typing import ClassVar

import lldb

from hstd_py_lib.debug_utils.config import Settings


class FormatterMeta(type):
    registry: list[type["SyntheticProvider"]] = []

    def __new__(
        metaclass,
        name: str,
        bases: tuple[type, ...],
        namespace: dict,
    ) -> type:
        cls = super().__new__(metaclass, name, bases, namespace)

        if namespace.get("type_regex"):
            metaclass.registry.append(cls)

        return cls


class SyntheticProvider(metaclass=FormatterMeta):
    type_regex: ClassVar[str] = ""
    extract_as_leaf: ClassVar[bool] = False

    def __init__(self, value: lldb.SBValue, internal_dict: dict) -> None:
        self.value = value.GetNonSyntheticValue()
        self.children: list[lldb.SBValue] = []

    @property
    def settings(self) -> Settings:
        # Local import avoids an integration -> format_base -> integration cycle.
        from hstd_py_lib.debug_utils.integration import get_runtime

        debugger = self.value.GetTarget().GetDebugger()
        runtime = get_runtime(debugger)

        if runtime.target != self.value.GetTarget():
            raise RuntimeError(
                "Formatter value does not belong to the selected LLDB target"
            )

        return runtime.settings

    def build_children(self) -> list[lldb.SBValue]:
        return []

    def update(self) -> None:
        self.children = self.build_children()

    def num_children(self) -> int:
        return len(self.children)

    def has_children(self) -> bool:
        return bool(self.children)

    def get_child_index(self, name: str) -> int:
        for index, child in enumerate(self.children):
            if child.GetName() == name:
                return index

        return -1

    def get_child_at_index(self, index: int) -> lldb.SBValue | None:
        if 0 <= index < len(self.children):
            return self.children[index]

        return None

    def summary_text(self) -> str:
        return ""

    @classmethod
    def summary(
        cls,
        value: lldb.SBValue,
        internal_dict: dict,
    ) -> str:
        try:
            return cls(value, internal_dict).summary_text()
        except Exception:
            traceback.print_exc(file=sys.stderr)
            raise


def register_formatters(debugger: lldb.SBDebugger) -> None:
    category = debugger.GetCategory("hstd-python")

    if not category.IsValid():
        category = debugger.CreateCategory("hstd-python")

    for provider in FormatterMeta.registry:
        # LLDB resolves callbacks through importable module attributes.
        if "." in provider.__qualname__:
            raise TypeError(
                f"{provider.__qualname__} must be a module-level provider class"
            )

        qualified_name = f"{provider.__module__}.{provider.__qualname__}"
        specification = lldb.SBTypeNameSpecifier(
            provider.type_regex,
            True,
        )

        category.AddTypeSynthetic(
            specification,
            lldb.SBTypeSynthetic.CreateWithClassName(qualified_name),
        )
        category.AddTypeSummary(
            specification,
            lldb.SBTypeSummary.CreateWithFunctionName(f"{qualified_name}.summary"),
        )

    category.SetEnabled(True)
