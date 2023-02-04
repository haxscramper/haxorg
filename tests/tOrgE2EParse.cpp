#include "common.hpp"

#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <lexbase/AstSpec.hpp>

using org = OrgNodeKind;
using otk = OrgTokenKind;


using OrgAdapter = NodeAdapter<OrgNodeKind, OrgTokenKind>;
using OrgSpec    = astspec::AstSpec<OrgAdapter, OrgNodeKind>;
using OrgPattern = astspec::AstPattern<OrgAdapter, OrgNodeKind>;
using SpecPair   = Pair<org, OrgPattern>;
using Field      = astspec::AstPatternRange<OrgAdapter, OrgNodeKind>;
using Range      = astspec::AstRange;

const OrgSpec spec = OrgSpec(Vec<SpecPair>{
    SpecPair{
        org::Subtree,
        OrgPattern(
            {Field(Range(0, "prefix"), OrgPattern(org::RawText)),
             Field(
                 Range(1, "todo"),
                 OrgPattern({org::BigIdent, org::Empty})),
             Field(
                 Range(2, "urgency"),
                 OrgPattern({org::UrgencyStatus, org::Empty})),
             Field(Range(3, "title"), OrgPattern(org::Paragraph)),
             Field(
                 Range(4, "completion"),
                 OrgPattern({org::Completion, org::Empty}))})},
    SpecPair{
        org::Drawer,
        OrgPattern(
            {Field(
                 Range(0, "properties"),
                 OrgPattern({org::PropertyList, org::Empty})),
             Field(
                 Range(1, "logbook"),
                 OrgPattern({org::Logbook, org::Empty})),
             Field(
                 Range(2, "description"),
                 OrgPattern({org::SubtreeDescription, org::Empty}))})},
    SpecPair{
        org::SubtreeDescription,
        OrgPattern({Field(Range(0, "text"), OrgPattern(org::Paragraph))})},
    SpecPair{
        org::AnnotatedParagraph,
        OrgPattern(
            {Field(
                 Range(0, "prefix"),
                 OrgPattern(
                     {org::ListTag, org::Footnote, org::AdmonitionTag})),
             Field(
                 Range(1, "body"),
                 OrgPattern({org::Paragraph, org::Empty}))})},
    SpecPair{
        org::Logbook,
        OrgPattern({Field(
            Range(slice(0, 1_B), "logs"),
            OrgPattern(
                {org::LogbookStateChange,
                 org::LogbookNote,
                 org::LogbookRefile,
                 org::LogbookClock}))})},
    SpecPair{
        org::LogbookStateChange,
        OrgPattern(
            {Field(
                 Range(0, "newstate"),
                 OrgPattern({org::BigIdent, org::Empty})),
             Field(
                 Range(1, "oldstate"),
                 OrgPattern({org::BigIdent, org::Empty})),
             Field(
                 Range(2, "time"),
                 OrgPattern({org::TimeStamp, org::Empty})),
             Field(
                 Range(3, "text"),
                 OrgPattern({org::StmtList, org::Empty}))})},
    SpecPair{
        org::LogbookRefile,
        OrgPattern({
            Field(Range(0, "time"), OrgPattern(org::TimeStamp)),
            Field(Range(1, "from"), OrgPattern(org::Link)),
            Field(
                Range(2, "text"),
                OrgPattern({org::StmtList, org::Empty})),
        })},
    SpecPair{
        org::CallCode,
        OrgPattern({
            Field(Range(0, "name"), OrgPattern({org::Ident})),
            Field(
                Range(1, "header-args"),
                OrgPattern({org::CmdArguments, org::Empty})),
            Field(Range(2, "args")),
            Field(Range(3, "end-args")),
            Field(
                Range(4, "result"),
                OrgPattern({org::RawText, org::Empty})),
        })},
    SpecPair{
        org::LogbookNote,
        OrgPattern({
            Field(Range(0, "time"), OrgPattern(org::TimeStamp)),
            Field(
                Range(1, "text"),
                OrgPattern({org::StmtList, org::Empty})),
        })},
    SpecPair{
        org::SrcInlineCode,
        OrgPattern({
            Field(Range(0, "lang"), OrgPattern({org::Ident, org::Empty})),
            Field(
                Range(1, "header-args"),
                OrgPattern({org::CmdArguments, org::Empty})),
            Field(Range(2, "body"), OrgPattern({org::CodeLine})),
            Field(
                Range(3, "result"),
                OrgPattern({org::RawText, org::Empty})),
        })},
    SpecPair{
        org::CmdArguments,
        OrgPattern({
            Field(
                Range(0, "flags"),
                {OrgPattern(org::InlineStmtList)
                     .sub({Field(
                         Range(slice(0, 1_B), "flags"),
                         OrgPattern(org::CmdFlag))})}),
        })},
    SpecPair{
        org::CmdValue,
        OrgPattern({Field(Range(0, "name")), Field(Range(1, "value"))}),
    },
    SpecPair{
        org::AssocStmtList,
        OrgPattern({Field(Range(0, "assoc")), Field(Range(1, "main"))})},
    SpecPair{
        org::Result,
        OrgPattern({Field(Range(0, "hash")), Field(Range(1, "body"))})},
    SpecPair{
        org::ListItem,
        OrgPattern(
            {Field(Range(0, "bullet")
                       .doc("List prefix - either dash/plus/star (for "
                            "unordered lists), or `<idx>.`/`<name>.`")),

             Field(Range(1, "counter")),

             Field(
                 Range(2, "checkbox").doc("Optional checkbox"),
                 OrgPattern({org::Checkbox, org::Empty})),
             Field(
                 Range(3, "header").doc("Main part of the list"),
                 OrgPattern(
                     {org::Paragraph,
                      org::AnnotatedParagraph,
                      org::Empty})),
             Field(
                 Range(4, "completion")
                     .doc("Cumulative completion progress for all "
                          "subnodes"),
                 OrgPattern({org::Completion, org::Empty})),
             Field(
                 Range(5, "body").doc(
                     "Additional list items - more sublists, extended "
                     "body (with code blocks, extra parargaphs etc.)"),
                 OrgPattern({org::StmtList, org::Empty}))})},
    SpecPair{
        org::TimeAssoc,
        OrgPattern({
            Field(
                Range(0, "name"),
                OrgPattern({org::BigIdent, org::Empty})),
            Field(
                Range(1, "time"),
                OrgPattern({org::TimeStamp, org::TimeRange})),
        })},
    SpecPair{
        org::LogbookClock,
        OrgPattern({
            Field(
                Range(0, "time"),
                OrgPattern({org::TimeRange, org::TimeStamp})),
        })},
    SpecPair{
        org::TimeRange,
        OrgPattern({
            Field(Range(0, "from"), OrgPattern({org::TimeStamp})),
            Field(Range(1, "to"), OrgPattern({org::TimeStamp})),
            Field(
                Range(2, "diff"),
                OrgPattern({org::SimpleTime, org::Empty})),
        })},

    SpecPair{
        org::PropertyList,
        OrgPattern({Field(
            Range(slice(0, 1_B), ""),
            OrgPattern({org::Property, org::PropertyAdd}))})},
    SpecPair{
        org::PropertyAdd,
        OrgPattern({
            Field(Range(0, "name"), OrgPattern({org::RawText})),
            Field(
                Range(1, "subname"),
                OrgPattern({org::Empty, org::Ident})),
            Field(Range(2, "values"), OrgPattern({org::RawText})),
        })},
    SpecPair{
        org::TableRow,
        OrgPattern(
            {Field(
                 Range(0, "args").doc(
                     "Optional arguments for row - can be specified using "
                     "`#+row`. For pipe formatting this is not supported, "
                     "so arguments would be an empty node."),
                 OrgPattern({org::CmdArguments, org::Empty})),
             Field(
                 Range(1, "text").doc(
                     "It is possible to put text on the *row* level."),
                 OrgPattern({org::Paragraph, org::Empty})),
             Field(
                 Range(2, "body"),
                 OrgPattern({Field(
                     Range(slice(0, 1_B), "cells"),
                     OrgPattern(org::TableCell))}))})},
    SpecPair{
        org::Property,
        OrgPattern({
            Field(Range(0, "name"), OrgPattern({org::RawText})),
            Field(
                Range(1, "subname"),
                OrgPattern({org::Empty, org::Ident})),
            Field(Range(2, "values"), OrgPattern({org::RawText})),
        })},
    SpecPair{
        org::MultilineCommand,
        OrgPattern(
            {Field(Range(0, "name"), OrgPattern({org::Ident})),
             Field(
                 Range(1, "args"),
                 OrgPattern({org::CmdArguments, org::Empty})),
             Field(Range(2, "body"))})},
    SpecPair{
        org::MetaSymbol,
        OrgPattern({
            Field(Range(0, "name"), OrgPattern({org::Ident})),
            Field(
                Range(1, "args"),
                OrgPattern({org::CmdArguments, org::Empty})),
            Field(Range(2, "body"), OrgPattern({org::RawText})),
        })},
    SpecPair{
        org::Table,
        OrgPattern({
            Field(
                Range(0, "args"),
                OrgPattern({org::CmdArguments, org::Empty})),
            Field(
                Range(slice(1, 1_B), "rows"),
                OrgPattern({org::TableRow})),
        })},
    SpecPair{
        org::TableCell,
        OrgPattern({
            Field(
                Range(0, "args"),
                OrgPattern({org::CmdArguments, org::Empty})),
            Field(
                Range(1, "text"),
                OrgPattern({org::Empty, org::StmtList})),
        })},
    SpecPair{
        org::Command,
        OrgPattern({
            Field(Range(0, "name"), OrgPattern({org::Ident})),
            Field(
                Range(1, "args"),
                OrgPattern({org::CmdArguments, org::Empty})),
        })},
    SpecPair{
        org::CommandCaption,
        OrgPattern({
            Field(Range(0, "text"), OrgPattern({org::Paragraph})),
        })},
    SpecPair{
        org::CommandInclude,
        OrgPattern({
            Field(Range(0, "file"), OrgPattern({org::File})),
            Field(Range(1, "kind"), OrgPattern({org::Empty, org::Ident})),
            Field(Range(2, "lang"), OrgPattern({org::Empty, org::Ident})),
            Field(
                Range(3, "args"),
                OrgPattern({org::Empty, org::CmdArguments})),
        })},
    SpecPair{
        org::SrcCode,
        OrgPattern(
            {Field(Range(0, "lang"), OrgPattern({org::Ident, org::Empty})),
             Field(
                 Range(1, "header-args"),
                 OrgPattern({org::CmdArguments, org::Empty})),
             Field(
                 Range(2, "body"),
                 OrgPattern(org::StmtList)
                     .sub({Field(
                         Range(slice(0, 1_B), "lines"),
                         OrgPattern(org::CodeLine))})),
             Field(
                 Range(3, "result"),
                 OrgPattern({org::RawText, org::Empty}))})},
    SpecPair{
        org::Footnote,
        OrgPattern(
            {Field(Range(0, "name")), Field(Range(1, "definition"))})},
    SpecPair{
        org::CommandHeader,
        OrgPattern({
            Field(
                Range(0, "args"),
                OrgPattern({org::Empty, org::CmdArguments})),
        })},
    SpecPair{
        org::CommandOptions,
        OrgPattern({Field(
            Range(slice(0, 1_B), "args"),
            OrgPattern(org::RawText))})},
    SpecPair{
        org::CodeLine,
        OrgPattern({Field(
            Range(slice(0, 1_B), "chunks"),
            OrgPattern(
                {org::CodeText,
                 org::CodeTangle,
                 org::CodeCallout,
                 org::Empty}))})},
    SpecPair{
        org::Link,
        OrgPattern(
            {Field(Range(0, "protocol")),
             Field(Range(1, "link")),
             Field(Range(2, "desc"))})}

    //
});

struct MockFull : public OrgParser {
    OrgTokenGroup       tokens;
    OrgTokenizer        tokenizer;
    OrgNodeGroup        nodes;
    std::string         base;
    Lexer<OrgTokenKind> lex;

    MockFull()
        : tokenizer(nullptr)
        , OrgParser(&nodes)
        , nodes(nullptr)
        , lex(&tokens) {
        nodes.tokens  = &tokens;
        tokenizer.out = &tokens;
    }

    using LexerMethod  = void (OrgTokenizer::*)(PosStr&);
    using ParserMethod = OrgId (OrgParser::*)(OrgLexer&);


    OrgNode&    n(int idx) { return nodes.at(OrgId(idx)); }
    OrgToken&   t(int idx) { return tokens.at(OrgTokenId(idx)); }
    OrgNodeKind k(int idx) { return n(idx).kind; }

    std::string s(int idx) {
        if (nodes.at(OrgId(idx)).isTerminal()) {
            return nodes.strVal(OrgId(idx));
        } else {
            return "";
        }
    }

    void tokenize(CR<std::string> content, LexerMethod lexMethod) {
        base = content;
        PosStr str{base};
        (tokenizer.*lexMethod)(str);
    }

    void parse(ParserMethod parseMethod) {
        (this->*parseMethod)(this->lex);
    }

    void run(
        CR<std::string> content,
        LexerMethod     lexMethod,
        ParserMethod    parseMethod) {
        tokenize(content, lexMethod);
        parse(parseMethod);
    }
    void treeRepr() {
        nodes.treeRepr(std::cout, OrgId(0), 0, {.fullBase = base.data()});
        std::cout << std::endl;
    }

    void tokenRepr() {
        for (const auto& [idx, tok] : tokens.tokens.pairs()) {
            std::cout << left_aligned(to_string(idx), 16) << " | " << *tok
                      << std::endl;
        }
    }
};

using T = OrgTokenizer;
using P = OrgParser;

TEST_CASE("Simple node conversion") {
    MockFull p;
    SECTION("Single hash tag token") {
        p.run("#test", &T::lexText, &P::parseHashTag);
        REQUIRE(p.n(0).kind == org::HashTag);
        REQUIRE(p.n(1).kind == org::RawText);
    };

    SECTION("Double has tag") {
        p.run("#test##a", &T::lexText, &P::parseHashTag);
        REQUIRE(p.k(0) == org::HashTag);
        REQUIRE(p.k(1) == org::RawText);
        REQUIRE(p.s(1) == "#test");
    }

    SECTION("Nested hash tag") {
        p.run("#test##[a, b]", &T::lexText, &P::parseHashTag);
        p.treeRepr();
    }
}
