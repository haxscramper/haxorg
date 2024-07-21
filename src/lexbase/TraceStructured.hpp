#pragma once

#include <hstd/system/reflection.hpp>

namespace org::report {

struct ValueToken {
    Str kind;
    Str value;
    int index;
    DESC_FIELDS(ValueToken, (kind, value, index));
};

struct ValueLexPosition {
    int nowPos;
    int maxPos;
    /// \brief First N tokens visible ahead of the lexer position
    Vec<ValueToken> tokens;
    int             line;
    int             column;
    DESC_FIELDS(ValueLexPosition, (nowPos, maxPos, line, column, tokens));
};

struct ValueOrgNode {
    Str id;
    Str kind;
    DESC_FIELDS(ValueOrgNode, (id, kind));
};

struct EntryParser {
    DECL_DESCRIBED_ENUM(
        Kind,
        EnterParse,
        LeaveParse,
        StartNode,
        EndNode,
        AddToken,
        Error,
        Print,
        FailTree);

    /// \brief String render of the node id, for reports related to
    /// start/end events of the nodes
    Opt<ValueOrgNode>     node;
    Opt<ValueLexPosition> lex;
    int                   depth;
    Kind                  kind;
    Opt<Str>              codeFunction;
    Opt<int>              codeLine;
    Opt<Str>              message;

    DESC_FIELDS(
        EntryParser,
        (node, depth, kind, lex, codeFunction, codeLine, message));
};

struct EntryTokenizer {
    DECL_DESCRIBED_ENUM(Kind, Enter, Leave, Push, Print, Error);

    Kind            kind;
    Opt<Str>        codeFunction;
    Opt<int>        codeLine;
    Opt<Str>        message;
    int             depth;
    Opt<ValueToken> token;
    Opt<int>        line;
    Opt<int>        column;

    DESC_FIELDS(
        EntryTokenizer,
        (kind,
         codeFunction,
         codeLine,
         message,
         depth,
         token,
         line,
         column));
};


} // namespace org::report
