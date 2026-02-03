from typing import Any


class HasAnyAttr():

    def __getattribute__(self, name: str) -> "HasAnyAttr":
        return HasAnyAttr()

    def __getattr__(self, name: str) -> "HasAnyAttr":
        return HasAnyAttr()

    def __getitem__(self, key: Any) -> "HasAnyAttr":
        return HasAnyAttr()

    def __call__(self, *args: Any, **kwargs: Any) -> "HasAnyAttr":
        return HasAnyAttr()

    def __bool__(self) -> bool:
        return True

    def __str__(self) -> str:
        return "HasAnyAttr()"

    def __repr__(self) -> str:
        return "HasAnyAttr()"
