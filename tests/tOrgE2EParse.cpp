#include "common.hpp"

#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <lexbase/AstSpec.hpp>
#include <lexbase/AstDiff.hpp>
#include <lexbase/AstGraph.hpp>
#include <hstd/stdlib/diffs.hpp>
#include <sem/SemOrg.hpp>

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
        org::HashTag,
        OrgPattern({Field(Range(0, "head"), OrgPattern(org::BigIdent))})},
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

    OrgAdapter a(int idx) { return OrgAdapter(&nodes, OrgId(idx)); }

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


template <
    /// Node kind
    typename N,
    /// Token kind
    typename K,
    /// Node value kind
    typename Val>
diff::ComparisonOptions<NodeId<N, K>, Val> nodeAdapterComparisonOptions(
    /// Map DOD node ID to the node object
    Func<CR<Node<N, K>>(NodeId<N, K>)> getNode,
    /// Map DOD node value from node object
    Func<CR<Val>(NodeId<N, K>)> getValue) {
    return {
        .getNodeValueImpl =
            [getValue](NodeId<N, K> id) { return getValue(id); },
        .getNodeKindImpl =
            [getNode](NodeId<N, K> id) {
                return static_cast<int>(getNode(id).kind);
            }};
}


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
        std::cout << "start validation output" << std::endl;
        std::cout << spec.validateSelf(p.a(0)) << "\n";
        std::cout << spec.validateSub(p.a(0), 0) << "\n";
        std::cout << spec.getSingleSubnodeIdx(p.a(0), "head");
        spec.getSingleSubnodeIdx(org::HashTag, "head");
        spec.getMultipleSubnode(p.a(0), "head");
        spec.fieldName(p.a(0), 0);
        spec.isSingleField(p.a(0), 0);
        spec.fieldDoc(p.a(0), 0);
    }

    SECTION("Nested hash tag") {
        p.run("#test##[a, b]", &T::lexText, &P::parseHashTag);
        p.treeRepr();
    }

    SECTION("Diff compilation") {
        p.run("#test##[a, b]", &T::lexText, &P::parseHashTag);
        auto cmp = nodeAdapterComparisonOptions<
            OrgNodeKind,
            OrgTokenKind,
            Str>(
            [&p](OrgId id) -> OrgNode { return p.nodes.at(id); },
            [&p](OrgId id) -> Str { return p.nodes.strVal(id); });
    }


    SECTION("Graph repr") {
        p.run("#test##[a, b]", &T::lexText, &P::parseHashTag);
        auto g = graphRepr(&p.nodes, OrgId(0));

        boost::write_graphviz(
            std::cout,
            g,
            [&g, &p](
                std::ostream&                       os,
                VertDesc<OrgNodeKind, OrgTokenKind> vert) {
                os << "[label=\"" << to_string(p.nodes.at(g[vert].id).kind)
                   << "\"]";
            });
    }

    SECTION("LCS compile") {
        Vec<int> first{1, 2, 3};
        Vec<int> second{1, 2, 3};
        std::cout << first << "\n";
        auto res = lcs<int>(first, second, [](CR<int> lhs, CR<int> rhs) {
            return lhs == rhs;
        });

        std::cout << res[0].xIndex << res[0].yIndex;
    }

    SECTION("Myers diff compile") {
        Vec<int> first{1, 2, 3};
        Vec<int> second{1, 2, 3};
        auto     res = myersDiff<int>(
            first, second, [](CR<int> lhs, CR<int> rhs) {
                return lhs == rhs;
            });
    }
}

template <typename T>
Vec<T> expandOn(CR<BacktrackRes> back, CR<Vec<T>> in, bool onX) {
    Vec<T> result;
    if (onX) {
        for (int i : back.xIndex) {
            result.push_back(in[i]);
        }
    } else {
        for (int i : back.yIndex) {
            result.push_back(in[i]);
        }
    }
    return result;
}


TEST_CASE("longestCommonSubsequence", "[LCS]") {
    Func<bool(CR<int>, CR<int>)> cmp =
        [](CR<int> lhs, CR<int> rhs) -> bool { return lhs == rhs; };

    SECTION("Both input sequences are empty") {
        Vec<int> a1       = {};
        Vec<int> b1       = {};
        Vec<int> expected = {};
        REQUIRE(expandOn(lcs(a1, b1, cmp)[0], a1, true) == expected);
    }

    SECTION("One of the input sequences is empty") {
        Vec<int> a2       = {1, 2, 3};
        Vec<int> b2       = {};
        Vec<int> expected = {};
        REQUIRE(expandOn(lcs(a2, b2, cmp)[0], a2, true) == expected);
    }

    // SECTION("Input sequences have common elements") {
    //     Vec<int> a3       = {1, 2, 3, 4};
    //     Vec<int> b3       = {2, 4, 3, 1};
    //     Vec<int> expected = {1, 2, 3, 4};
    //     REQUIRE(expandOn(lcs(a3, b3, cmp)[0], a3, true) == expected);
    // }

    SECTION("Input sequences do not have any common elements") {
        Vec<int> a4       = {1, 2, 3, 4};
        Vec<int> b4       = {5, 6, 7, 8};
        Vec<int> expected = {};
        REQUIRE(expandOn(lcs(a4, b4, cmp)[0], a4, true) == expected);
    }
}

TEST_CASE("Fuzzy match configurable", "[fuzzy]") {
    FuzzyMatcher<char const> matcher;
    matcher.isEqual = [](CR<char> lhs, CR<char> rhs) -> bool {
        std::cout << lhs << " == " << rhs << "\n";
        return lhs == rhs;
    };
    matcher.isSeparator = [](CR<char> sep) -> bool { return false; };

    auto getMatches = [&](Str lhs, Str rhs) -> Array<int, 256> {
        std::cout << "score "
                  << matcher.get_score(lhs.toSpan(), rhs.toSpan()) << "\n";
        return matcher.matches;
    };

    SECTION("Full match") {
        auto m = getMatches("123", "010233");
        std::cout << std::endl << "---\n" << m << std::endl;
    }
}


using namespace diff;


TEST_CASE("Ast diff") {
    SECTION("Pointer-based nodes") {
        struct RealNode {
            std::string   value;
            int           kind;
            Vec<RealNode> sub;

            using IdT  = RealNode*;
            using ValT = std::string;

            TreeMirror<IdT, ValT> toMirror() {
                Vec<TreeMirror<IdT, ValT>> subMirror;
                for (auto& it : sub) {
                    subMirror.push_back(it.toMirror());
                }
                return TreeMirror<IdT, ValT>{this, subMirror};
            }
        };

        using IdT  = RealNode::IdT;
        using ValT = RealNode::ValT;

        Func<Str(CR<ValT>)> toStr = [](CR<ValT> arg) -> Str {
            return to_string(arg);
        };

        auto src = RealNode{
            "",
            6,
            {RealNode{
                 "",
                 8,
                 {RealNode{"**", 18},
                  RealNode{"CLI", 39},
                  RealNode{"", 3},
                  RealNode{"", 55, {RealNode{"tools", 69}}},
                  RealNode{"", 3},
                  RealNode{"", 3},
                  RealNode{"", 3},
                  RealNode{"", 94, {RealNode{"", 3}, RealNode{"", 3}}},
                  RealNode{"", 6, {}}}},
             RealNode{
                 "",
                 55,
                 {RealNode{"Nested", 69},
                  RealNode{" ", 67},
                  RealNode{"content", 69}}}}};

        auto dst = RealNode{
            "",
            6,
            {RealNode{
                "",
                8,
                {RealNode{"**", 18},
                 RealNode{"CLI", 39},
                 RealNode{"", 3},
                 RealNode{"", 55, {RealNode{"tools", 69}}},
                 RealNode{"", 3},
                 RealNode{"", 3},
                 RealNode{"", 3},
                 RealNode{"", 94, {RealNode{"", 3}, RealNode{"", 3}}},
                 RealNode{
                     "",
                     6,
                     {RealNode{
                         "",
                         55,
                         {RealNode{"Nested", 69},
                          RealNode{" ", 67},
                          RealNode{"content", 69}}}}}}}}};

        auto Src = src.toMirror();
        auto Dst = dst.toMirror();

        ComparisonOptions<IdT, ValT> Options{
            .getNodeValueImpl = [](IdT id) { return id->value; },
            .getNodeKindImpl  = [](IdT id) { return id->kind; },
            .isMatchingAllowedImpl =
                [](IdT id1, IdT id2) { return id1->kind == id2->kind; }};

        SyntaxTree<IdT, ValT>::WalkParameters<TreeMirror<IdT, ValT>> walk{
            .getSubnodeAt     = diff::getSubnodeAtTreeMirror<IdT, ValT>,
            .getSubnodeNumber = diff::
                getSubnodeNumberTreeMirror<IdT, ValT>,
            .getSubnodeId = diff::getSubnodeIdTreeMirror<IdT, ValT>,
        };

        SyntaxTree<IdT, ValT> SrcTree{Options};
        SrcTree.FromNode<TreeMirror<IdT, ValT>>(Src, walk);
        SyntaxTree<IdT, ValT> DstTree{Options};
        DstTree.FromNode(Dst, walk);

        ASTDiff<IdT, ValT> Diff{SrcTree, DstTree, Options};

        for (diff::NodeId Dst : DstTree) {
            diff::NodeId Src = Diff.getMapped(DstTree, Dst);
            if (Src.isValid()) {
                COUT << "Match [\033[33m";
                printNode(std::cout, SrcTree, Src, toStr);
                std::cout << "\033[0m] to [\033[33m";
                printNode(std::cout, DstTree, Dst, toStr);
                std::cout << "\033[0m] ";
            } else {
                COUT << "Dst to [\033[32m";
                printNode(std::cout, DstTree, Dst, toStr);
                std::cout << "\033[0m] ";
            }

            printDstChange(std::cout, Diff, SrcTree, DstTree, Dst, toStr);
            std::cout << "\n";
        }
    }

    SECTION("Pointer-based nodes with variant") {
        struct RealNode {
            std::variant<int, double, std::string> value;
            Vec<RealNode>                          sub;
        };

        auto src = RealNode{
            "toplevel", {RealNode{1}, RealNode{1.2}, RealNode{"subnode"}}};

        auto dst = RealNode{
            "toplevel",
            {RealNode{22}, RealNode{1.2}, RealNode{"subnode'"}}};

        using IdT  = RealNode*;
        using ValT = decltype(src.value);


        Func<Str(CR<ValT>)> toStr = [](CR<ValT> arg) -> Str {
            return variant_to_string(arg);
        };

        auto Src = TreeMirror<IdT, ValT>{
            &src,
            {TreeMirror<IdT, ValT>{&src.sub[0]},
             TreeMirror<IdT, ValT>{&src.sub[1]}}};

        auto Dst = TreeMirror<IdT, ValT>{
            &dst,
            {TreeMirror<IdT, ValT>{&dst.sub[0]},
             TreeMirror<IdT, ValT>{&dst.sub[1]},
             TreeMirror<IdT, ValT>{&dst.sub[2]}}};

        ComparisonOptions<IdT, ValT> Options{
            .getNodeValueImpl = [](IdT id) { return id->value; },
            .getNodeKindImpl  = [](IdT id) { return 0; }};

        SyntaxTree<IdT, ValT>::WalkParameters<TreeMirror<IdT, ValT>> walk{
            .getSubnodeAt     = diff::getSubnodeAtTreeMirror<IdT, ValT>,
            .getSubnodeNumber = diff::
                getSubnodeNumberTreeMirror<IdT, ValT>,
            .getSubnodeId = diff::getSubnodeIdTreeMirror<IdT, ValT>,
        };

        SyntaxTree<IdT, ValT> SrcTree{Options};
        SrcTree.FromNode<TreeMirror<IdT, ValT>>(Src, walk);
        SyntaxTree<IdT, ValT> DstTree{Options};
        DstTree.FromNode(Dst, walk);

        ASTDiff<IdT, ValT> Diff{SrcTree, DstTree, Options};

        for (diff::NodeId Dst : DstTree) {
            diff::NodeId Src = Diff.getMapped(DstTree, Dst);
            if (Src.isValid()) {
                std::cout << "Match ";
                printNode(std::cout, SrcTree, Src, toStr);
                std::cout << " to ";
                printNode(std::cout, DstTree, Dst, toStr);
                std::cout << "\n";
            }

            printDstChange(std::cout, Diff, SrcTree, DstTree, Dst, toStr);
        }
    }
}
