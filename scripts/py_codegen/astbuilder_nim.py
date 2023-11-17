from py_textlayout.py_textlayout import TextLayout
from dataclasses import dataclass, field
from typing import TYPE_CHECKING, NewType
from beartype.typing import List, Optional
from beartype import beartype
import astbuilder_base as base
from enum import Enum

if TYPE_CHECKING:
    from py_textlayout.py_textlayout import BlockId
else:
    BlockId = NewType('BlockId', int)


class ExprKind(Enum):
    StrLit = 0
    IntLit = 1


class TypeKind(Enum):
    RegularType = 0
    Function = 1


@beartype
@dataclass
class Type:
    Name: str
    Kind: TypeKind = TypeKind.RegularType
    Parameters: List['Type'] = field(default_factory=list)
    Expr: Optional[BlockId] = None


@beartype
@dataclass
class PragmaParams:
    Name: str
    Arguments: List[BlockId] = field(default_factory=list)


@beartype
@dataclass
class IdentParams:
    Name: str
    Type: Type
    Exported: bool = True


@beartype
@dataclass
class ObjectParams:
    Name: str
    Exported: bool = True
    Pragmas: List[PragmaParams] = field(default_factory=list)
    Fields: List[IdentParams] = field(default_factory=list)


@beartype
@dataclass
class TypedefParams:
    Name: str
    Base: Type


@beartype
@dataclass
class EnumFieldParams:
    Name: str
    Value: BlockId


@beartype
@dataclass
class EnumParams:
    Name: str
    Fields: List[EnumFieldParams]


@beartype
@dataclass
class FunctionParams:
    Name: str
    ReturnTy: Type = field(default_factory=lambda: Type("void"))
    Arguments: List[IdentParams] = field(default_factory=list)


@beartype
class ASTBuilder(base.AstbuilderBase):

    def __init__(self, in_b: TextLayout):
        self.b = in_b

    def Type(self, t: Type) -> BlockId:
        if t.Kind == TypeKind.Function:
            return self.b.line([
                self.string("proc "),
                self.pars(
                    self.csv([
                        self.b.line([
                            self.string("a" + str(idx)),
                            self.string(": "),
                            self.Type(t),
                        ]) for idx, t in enumerate(t.Parameters[1:])
                    ])),
                self.string(": "),
                self.Type(t.Parameters[0])
            ])

        else:
            return self.string(t.Name)

    def Typedef(self, typedef: TypedefParams) -> BlockId:
        return self.b.line([
            self.string(typedef.Name),
            self.string(" = "),
            self.Type(typedef.Base),
        ])

    def EnumField(self, f: EnumFieldParams, padTo: int = 0) -> BlockId:
        return self.b.line([
            self.string(f.Name.ljust(padTo)),
            self.string(" = "),
            f.Value,
        ])

    def Enum(self, enum: EnumParams) -> BlockId:
        head = self.b.line([
            self.string(enum.Name),
            self.string(" = "),
            self.string("enum"),
        ])

        field_widths: int = max([len(f.Name) for f in enum.Fields] + [0])

        return self.b.stack([
            head,
            self.b.indent(2, self.b.stack([self.EnumField(f, padTo=field_widths) for f in enum.Fields]))
        ])

    def Function(self, func: FunctionParams) -> BlockId:
        head = self.b.line([
            self.string("proc "),
            self.string(func.Name),
        ])

        tail = self.b.line([
            self.string(": "),
            self.Type(func.ReturnTy),
        ])

        return self.b.line([
            head,
            self.pars(self.csv([self.Field(Arg) for Arg in func.Arguments])), 
            tail
        ])

    def Field(self, f: IdentParams, padTo: int = 0) -> BlockId:
        return self.b.line([
            self.string(f.Name.ljust(padTo)),
            self.string("*" if f.Exported else ""),
            self.string(": "),
            self.Type(f.Type),
        ])

    def Object(self, Obj: ObjectParams) -> BlockId:
        head = self.b.line([
            self.string(Obj.Name),
            self.string("*" if Obj.Exported else ""),
            self.string(" = "),
            self.string("object"),
        ])

        field_widths: int = max([len(f.Name) for f in Obj.Fields] + [0]) + 1

        return self.b.stack([
            head,
            self.b.indent(
                2, self.b.stack([self.Field(f, padTo=field_widths) for f in Obj.Fields]))
        ])
