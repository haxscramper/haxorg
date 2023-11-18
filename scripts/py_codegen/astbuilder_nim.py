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
    Exported: bool = False


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
    Value: Optional[BlockId] = None


@beartype
@dataclass
class EnumParams:
    Name: str
    Fields: List[EnumFieldParams]
    Pragmas: List[PragmaParams] = field(default_factory=list)


class FunctionKind(Enum):
    PROC = 0
    FUNC = 1
    CONVERTER = 2
    MACRO = 3
    TEMPLATE = 4
    METHOD = 5


@beartype
@dataclass
class FunctionParams:
    Name: str
    Exported: bool = True
    ReturnTy: Type = field(default_factory=lambda: Type("void"))
    Arguments: List[IdentParams] = field(default_factory=list)
    Pragmas: List[PragmaParams] = field(default_factory=list)
    Implementation: Optional[BlockId] = None
    Kind: FunctionKind = FunctionKind.PROC
    OneLineImpl: bool = False


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
            head: BlockId = self.string(t.Name)

            if 0 < len(t.Parameters):
                if t.Name == "ptr":
                    return self.b.line(
                        [head, self.string(" "),
                         self.Type(t.Parameters[0])])

                else:
                    return self.b.line([
                        head,
                        self.pars(self.csv([self.Type(p) for p in t.Parameters])),
                    ])

            else:
                return head

    def Typedef(self, typedef: TypedefParams) -> BlockId:
        return self.b.line([
            self.string(typedef.Name),
            self.string(" = "),
            self.Type(typedef.Base),
        ])

    def EnumField(self, f: EnumFieldParams, padTo: int = 0) -> BlockId:
        return self.b.line([
            self.string(f.Name.ljust(padTo)),
            *([] if f.Value is None else [self.string(" = "), f.Value]),
        ])

    def Enum(self, enum: EnumParams) -> BlockId:
        head = self.b.line([
            self.string(enum.Name),
            self.Pragmas(enum.Pragmas),
            self.string(" = "),
            self.string("enum"),
        ])

        field_widths: int = max([len(f.Name) for f in enum.Fields] + [0])

        return self.b.stack([
            head,
            self.b.indent(
                2,
                self.b.stack([self.EnumField(f, padTo=field_widths) for f in enum.Fields
                             ]))
        ])

    def Function(self, func: FunctionParams) -> BlockId:
        head = self.b.line([
            self.string(str(func.Kind.name).lower() + " "),
            self.string(func.Name) if all([(c.isalnum() or c == "_") for c in func.Name])
            else self.string(f"`{func.Name}`"),
            self.string("*" if func.Exported else "")
        ])

        tail = self.b.line([
            self.string(": "),
            self.Type(func.ReturnTy),
            self.Pragmas(func.Pragmas),
        ])

        result = self.b.line([
            head,
            self.pars(self.csv([self.Field(Arg) for Arg in func.Arguments])),
            tail,
        ])

        if func.Implementation is None:
            return result

        else:
            if func.OneLineImpl:
                return self.b.line([result, self.string(" = "), func.Implementation])

            else:
                return self.b.stack([
                    self.b.line([result, self.string(" = ")]),
                    self.b.indent(2, func.Implementation),
                ])

    def Field(self, f: IdentParams, padTo: int = 0) -> BlockId:
        return self.b.line([
            self.string(f.Name.ljust(padTo)),
            self.string("*" if f.Exported else ""),
            self.string(": "),
            self.Type(f.Type),
        ])

    def Pragma(self, p: PragmaParams) -> BlockId:
        return self.b.line([
            self.string(p.Name), *([] if len(p.Arguments) == 0 else [
                self.string(": "),
                *p.Arguments,
            ])
        ])

    def Pragmas(self, pragmas: List[PragmaParams]) -> BlockId:
        return self.b.line([
            self.string(" {."),
            self.csv([self.Pragma(p) for p in pragmas]),
            self.string(".}"),
        ]) if 0 < len(pragmas) else self.string("")

    def Object(self, Obj: ObjectParams) -> BlockId:
        head = self.b.line([
            self.string(Obj.Name),
            self.string("*" if Obj.Exported else ""),
            self.Pragmas(Obj.Pragmas),
            self.string(" = "),
            self.string("object"),
        ])

        field_widths: int = max([len(f.Name) for f in Obj.Fields] + [0]) + 1

        return self.b.stack([
            head,
            self.b.indent(
                2, self.b.stack([self.Field(f, padTo=field_widths) for f in Obj.Fields]))
        ])
