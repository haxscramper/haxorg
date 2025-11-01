from beartype.typing import Any, Dict, List, Optional, Union
from pydantic import BaseModel, Field
from beartype import beartype


class TypstNode(BaseModel):
    """Base class for all Typst AST nodes"""
    pass


class PtSize(TypstNode):
    size: Union[int, float]


class Text(TypstNode):
    """Plain text content"""
    content: str


class Command(TypstNode):
    """Typst command (prefixed with #)"""
    name: str
    args: Optional[List[Union['Expression',
                              'NamedArg']]] = Field(default_factory=list)
    content: Optional[List['TypstNode']] = None


class NamedArg(TypstNode):
    """Named argument in a function call"""
    name: str
    value: 'Expression'


class Expression(TypstNode):
    """Base class for expressions"""
    pass


class Literal(Expression):
    """Literal value (string, number, boolean, none)"""
    value: Union[str, int, float, bool, None, PtSize, dict]


class RawLiteral(Expression):
    """Raw literal that should be inserted as-is without quotes"""
    value: str


class Array(Expression):
    """Array expression"""
    items: List[Expression]


class Dictionary(Expression):
    """Dictionary expression"""
    items: Dict[str, Expression]


class Content(TypstNode):
    """Content block [...]"""
    body: List[TypstNode]


class Set(TypstNode):
    """Set rule (#set ...)"""
    target: str
    args: Dict[str, Expression] = Field(default_factory=dict)


class Show(TypstNode):
    """Show rule (#show ...)"""
    selector: Optional[Expression] = None
    transform: Optional[TypstNode] = None


class Let(TypstNode):
    """Variable binding (#let ...)"""
    name: str
    value: Expression


class Import(TypstNode):
    """Import statement (#import ...)"""
    path: str
    items: Optional[List[str]] = None


class Include(TypstNode):
    """Include statement (#include ...)"""
    path: str


class Document(TypstNode):
    """Root document node"""
    subnodes: List[TypstNode] = Field(default_factory=list)


# Update forward references
Command.model_rebuild()
Content.model_rebuild()
Document.model_rebuild()

from typing import Any, List, Union


@beartype
class TypstGenerator:
    """Generates Typst document from schema"""

    def __init__(self, indent_size: int = 2):
        self.indent_size = indent_size

    def generate(self, node: TypstNode, indent: int = 0) -> str:
        """Generate Typst code from a node"""
        method_name = f"_generate_{node.__class__.__name__.lower()}"
        method = getattr(self, method_name, self._generate_default)
        return method(node, indent)

    def _indent(self, level: int) -> str:
        """Generate indentation string"""
        return " " * (level * self.indent_size)

    def _escape(self, text: str) -> str:
        """Escape special characters in text"""
        chars_to_escape = ["@", "#", "<", "*", "[", "$", "]", "\\"]
        result = text
        for char in chars_to_escape:
            result = result.replace(char, "\\" + char)
        return result

    def _escape_string(self, text: str) -> str:
        """Escape characters in string literals"""
        return text.replace("\\", "\\\\").replace('"', '\\"')

    def _generate_document(self, node: Document, indent: int) -> str:
        """Generate complete document"""
        parts = []
        for child in node.subnodes:
            parts.append(self.generate(child, indent))
        return "\n".join(parts)

    def _normalize(self, str: str) -> str:
        return str.replace(".", "_")

    def _generate_text(self, node: Text, indent: int) -> str:
        """Generate plain text"""
        return self._indent(indent) + self._escape(node.content)

    def _generate_command(self, node: Command, indent: int) -> str:
        """Generate command call"""
        result = self._indent(indent) + "#" + node.name

        # Add arguments if present
        if node.args:
            args_str = self._generate_args(node.args)
            result += f"({args_str})"

        # Add content blocks if present
        if node.content:
            for content_node in node.content:
                content_str = self._generate_content_block(
                    content_node, indent)
                result += content_str

        return result

    def _generate_args(self, args: List[Union[Expression, NamedArg]]) -> str:
        """Generate function arguments"""
        parts = []

        # Separate positional and named arguments
        positional = []
        named = []

        for arg in args:
            if isinstance(arg, NamedArg):
                named.append(arg)
            else:
                positional.append(arg)

        # Add positional arguments first
        for arg in positional:
            parts.append(self._generate_expression(arg))

        # Add named arguments
        for arg in named:
            parts.append(f"{arg.name}: {self._generate_expression(arg.value)}")

        return ", ".join(parts)

    def _generate_expression(self, expr: Expression) -> str:
        """Generate expression"""
        if isinstance(expr, Literal):
            return self._generate_literal(expr.value)
        elif isinstance(expr, RawLiteral):
            return expr.value
        elif isinstance(expr, Array):
            items = [self._generate_expression(item) for item in expr.items]
            return f"({', '.join(items)})"
        elif isinstance(expr, Dictionary):
            items = [
                f"{self._normalize(key)}: {self._generate_expression(value)}"
                for key, value in expr.items.items()
            ]
            return f"({', '.join(items)})"
        else:
            return str(expr)

    def _generate_literal(self, value: Any) -> str:
        """Generate literal value"""
        if value is None:
            return "none"
        elif isinstance(value, bool):
            return "true" if value else "false"
        elif isinstance(value, str):
            return f'"{self._escape_string(value)}"'
        elif isinstance(value, (int, float)):
            return str(value)
        elif isinstance(value, PtSize):
            return f"{value.size}pt"

        elif isinstance(value, dict):
            return "(" + ", ".join(
                self._normalize(key) + ": " + self._generate_literal(it)
                for key, it in value.items()) + ("," if value else "") + ")"

        elif isinstance(value, list):
            return "(" + ", ".join(
                self._generate_literal(it)
                for it in value) + ("," if value else "") + ")"

        else:
            return str(value)

    def _generate_content_block(self, node: TypstNode, indent: int) -> str:
        """Generate content block [...]"""
        if isinstance(node, Content):
            return self._generate_content(node, indent)
        else:
            # Single node content
            content = self.generate(node, 0).strip()
            return f"[{content}]"

    def _generate_content(self, node: Content, indent: int) -> str:
        """Generate content block"""
        if not node.body:
            return "[]"

        # Check if content is simple enough for single line
        is_simple = len(node.body) == 1 and isinstance(node.body[0],
                                                       (Text, Command))

        if is_simple:
            content = "".join(
                self.generate(child, 0).strip() for child in node.body)
            return f"[{content}]"
        else:
            # Multi-line content
            lines = ["["]
            for child in node.body:
                child_str = self.generate(child, indent + 1)
                if child_str.strip():
                    lines.append(child_str)
            lines.append(self._indent(indent) + "]")
            return "\n".join(lines)

    def _generate_set(self, node: Set, indent: int) -> str:
        """Generate set rule"""
        result = self._indent(indent) + f"#set {node.target}"

        if node.args:
            args_parts = []
            for key, value in node.args.items():
                args_parts.append(f"{key}: {self._generate_expression(value)}")
            result += f"({', '.join(args_parts)})"
        else:
            result += "()"

        return result

    def _generate_show(self, node: Show, indent: int) -> str:
        """Generate show rule"""
        result = self._indent(indent) + "#show"

        if node.selector:
            result += f" {self._generate_expression(node.selector)}"

        if node.transform:
            result += ": " + self.generate(node.transform, 0).strip()

        return result

    def _generate_let(self, node: Let, indent: int) -> str:
        """Generate let binding"""
        value_str = self._generate_expression(node.value)
        return self._indent(indent) + f"#let {node.name} = {value_str}"

    def _generate_import(self, node: Import, indent: int) -> str:
        """Generate import statement"""
        result = self._indent(indent) + f'#import "{node.path}"'

        if node.items:
            result += f": {', '.join(node.items)}"

        return result

    def _generate_include(self, node: Include, indent: int) -> str:
        """Generate include statement"""
        return self._indent(indent) + f'#include "{node.path}"'

    def _generate_namedarg(self, node: NamedArg, indent: int) -> str:
        """Generate named argument"""
        return f"{node.name}: {self._generate_expression(node.value)}"

    def _generate_default(self, node: TypstNode, indent: int) -> str:
        """Default generator for unknown node types"""
        return self._indent(
            indent) + f"// Unknown node type: {type(node).__name__}"


def generate_typst(document: Union[Document, TypstNode]) -> str:
    """Main entry point for generating Typst document"""
    generator = TypstGenerator()

    if isinstance(document, Document):
        return generator.generate(document)
    else:
        # Wrap single node in document
        doc = Document(subnodes=[document])
        return generator.generate(doc)


# Example usage:
if __name__ == "__main__":
    # Create a simple document
    doc = Document(subnodes=[
        Set(target="text",
            args={
                "font": Literal(value="Arial"),
                "size": RawLiteral(value="12pt")
            }),
        Command(name="heading",
                args=[Literal(value="My Document")],
                content=[Content(body=[Text(content="Introduction")])]),
        Text(content="This is a paragraph with "),
        Command(name="strong",
                content=[Content(body=[Text(content="bold text")])]),
        Text(content="."),
    ])

    print(generate_typst(doc))
