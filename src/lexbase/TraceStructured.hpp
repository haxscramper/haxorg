#pragma once

#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Json.hpp>

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


struct EntryLexer {
    struct State {
        std::string matched;
        std::string name;
        int         line;   ///< Lexed text line where state was started
        int         column; ///< Same for column
        int         rule;
        DESC_FIELDS(State, (matched, name, line, column, rule));
    };

    struct View {
        int         line;
        int         column;
        std::string state;
        Vec<State>  states;
        DESC_FIELDS(View, (line, column, state, states));
    };

    struct Pop {
        int  indent;
        Str  currentState;
        Str  nextState;
        int  yamlLine;
        View view;
        DESC_FIELDS(
            Pop,
            (view, indent, currentState, nextState, yamlLine));
    };

    struct Add {
        int        indent;
        ValueToken token;
        DESC_FIELDS(Add, (indent, token));
    };

    SUB_VARIANTS(Kind, Data, data, getKind, Add, Pop);
    Data data;
};


} // namespace org::report

template <>
struct JsonSerde<org::report::EntryLexer> {
    static json to_json(org::report::EntryLexer const& it) {
        json result    = json::object();
        result["kind"] = fmt1(it.getKind());
        std::visit(
            [&](auto const& value) {
                result["data"] = to_json_eval(value);
            },
            it.data);

        return result;
    }
    static org::report::EntryLexer from_json(json const& j) {
        return org::report::EntryLexer{};
    }
};
