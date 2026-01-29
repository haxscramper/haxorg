#pragma once

#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/VariantSerde.hpp>
#include <haxorg/lexbase/SourceManager.hpp>

/// \brief Structured org-mode processing report types.
namespace org::report {

struct ValueToken {
    hstd::Str kind;
    hstd::Str value;
    int       index;
    DESC_FIELDS(ValueToken, (kind, value, index));
};

struct ValueLexPosition {
    int nowPos;
    int maxPos;
    /// \brief First N tokens visible ahead of the lexer position
    hstd::Vec<ValueToken>            tokens;
    hstd::Opt<org::parse::SourceLoc> loc;
    DESC_FIELDS(ValueLexPosition, (nowPos, maxPos, loc, tokens));
};

struct ValueOrgNode {
    hstd::Str            id;
    hstd::Str            kind;
    hstd::Opt<hstd::Str> value;
    DESC_FIELDS(ValueOrgNode, (id, kind, value));
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
    hstd::Opt<ValueOrgNode>     node;
    hstd::Opt<ValueLexPosition> lex;
    int                         depth;
    Kind                        kind;
    hstd::Opt<hstd::Str>        codeFunction;
    hstd::Opt<int>              codeLine;
    hstd::Opt<hstd::Str>        message;

    DESC_FIELDS(
        EntryParser,
        (node, depth, kind, lex, codeFunction, codeLine, message));
};

struct EntrySem {
    DECL_DESCRIBED_ENUM(
        Kind,
        Enter,
        EnterField,
        LeaveField,
        Json,
        Print,
        Leave);

    Kind                    kind;
    hstd::Opt<ValueOrgNode> node;
    hstd::Opt<std::string>  field;
    int                     indent;
    hstd::Opt<hstd::Str>    message;
    hstd::Opt<hstd::Str>    codeFunction;
    hstd::Opt<int>          codeLine;
    DESC_FIELDS(
        EntrySem,
        (kind, node, field, indent, message, codeFunction, codeLine));
};

struct EntryTokenizer {
    DECL_DESCRIBED_ENUM(Kind, Enter, Leave, Push, Print, Error);

    Kind                             kind;
    hstd::Opt<hstd::Str>             codeFunction;
    hstd::Opt<int>                   codeLine;
    hstd::Opt<hstd::Str>             message;
    int                              depth;
    hstd::Opt<ValueToken>            token;
    hstd::Opt<org::parse::SourceLoc> loc;

    DESC_FIELDS(
        EntryTokenizer,
        (kind, codeFunction, codeLine, message, depth, token, loc));
};


/// \brief definition for the structured message records produced in the
/// org visit exporter.
struct EntryExport {
    DECL_DESCRIBED_ENUM(
        Kind,
        VisitField,
        VisitSubnode,
        NewRes,
        VisitToEval,
        VisitValue,
        VisitDispatchHook,
        VisitStart,
        VisitEnd,
        VisitDispatch,
        VisitSpecificKind,
        PushVisit,
        PopVisit,
        VisitGeneric,
        VisitTop,
        VisitVariant,
        Print);

    Kind                   kind;
    hstd::Opt<hstd::Str>   visitedKind = std::nullopt;
    int                    level       = 0;
    int                    codeLine    = 0;
    hstd::Opt<std::string> field;
    hstd::Opt<std::string> codeFunction;
    bool                   isStart = true;
    hstd::Opt<std::string> type;
    hstd::Opt<std::string> msg;

    DESC_FIELDS(
        EntryExport,
        (kind,
         visitedKind,
         level,
         codeLine,
         field,
         codeFunction,
         isStart,
         type,
         msg));
};

} // namespace org::report
