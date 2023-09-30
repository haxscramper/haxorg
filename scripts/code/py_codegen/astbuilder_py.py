import setup_imports
from py_textlayout import *
from dataclasses import dataclass, field
from beartype.typing import *
from enum import Enum
from beartype import beartype
import inspect
import os
import astbuilder_base as base

if not TYPE_CHECKING:
    BlockId = NewType('BlockId', int)

@beartype
@dataclass
class PyType:
    Name: str
    Params: List['PyType'] = field(default_factory=list)

@beartype
@dataclass
class IdentParams:
    Type: PyType
    Name: str

@beartype
@dataclass
class DecoratorParams:
    Name: str

@beartype
@dataclass
class FunctionDefParams:
    Name: str
    ResultTy: PyType
    Args: List[PyType] = field(default_factory=list)
    Decorators: List[DecoratorParams] = field(default_factory=list)
    Doc: str = ""
    Body: List[BlockId] = field(default_factory=list)
    IsStub: bool = False
    

@beartype
@dataclass
class MethodParams:
    Func: FunctionDefParams


@beartype
@dataclass
class ClassParams:
    Name: str
    Methods: List[MethodParams] = field(default_factory=list)
    Bases: List[PyType] = field(default_factory=list)
    

@beartype
class AstBuilder(base.AstbuilderBase):
    def Decorator(self, p: DecoratorParams) -> BlockId:
        return self.b.line([self.string("@"), self.string(p.Name)])

    def Type(self, p: PyType) -> BlockId:
        if p.Params:
            return self.b.line(self.string(p.Name, [
                self.string("["),
                *[self.Type(T) for T in p.Params],
                self.string("]")
            ]))

        else:
            return self.string(p.Name)

    def Arg(self, p: IdentParams) -> BlockId:
        return self.b.line([self.string(p.Name), self.string(": "), self.Type(p.Type)])

    def FuncHead(self, p: FunctionDefParams) -> List[BlockId]:
        b = self.b
        return [
            b.text("def "), 
            b.text(p.Name), 
            self.pars(self.csv([self.Arg(A) for A in p.Args])),
            b.text(" -> "),
            self.Type(p.ResultTy),
            b.text(":")
        ]

    def Method(self, p: MethodParams) -> BlockId:
        b = self.b

        def_head = self.FuncHead(p.Func)

        if p.Func.IsStub:
            def_head.append(b.text("..."))
            return b.line(def_head)

        else:
            return b.stack([
                b.line(def_head),
                b.indent(4, b.stack([
                    p.Func.Body
                ]))
            ])

    def Class(self, p: ClassParams) -> BlockId:
        b = self.b

        methods: List[BlockId] = [self.Method(M) for M in p.Methods]

        return self.b.stack([
            b.line([b.text("class "), b.text(p.Name), b.text(":")]),
            b.indent(4, b.stack(methods))
        ])




