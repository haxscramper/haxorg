#include "common.hpp"
#include "org_parse_aux.hpp"

#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <parse/OrgSpec.hpp>

#include <lexbase/NodeIO.hpp>
#include <lexbase/NodeTest.hpp>

#include <hstd/stdlib/Filesystem.hpp>

#include <hstd/stdlib/diffs.hpp>

#include <fnmatch.h>

#define CB(name)                                                          \
    { Str(#name), &OrgTokenizer::lex##name }

const UnorderedMap<Str, MockFull::LexerMethod> lexers({
    CB(Angle),
    CB(Time),
    CB(LinkTarget),
    CB(Bracket),
    CB(TextChars),
    CB(ParenArguments),
    CB(Text),
    CB(Logbook),
    CB(Properties),
    CB(Description),
    CB(Drawer),
    CB(SubtreeTodo),
    CB(SubtreeUrgency),
    CB(SubtreeTitle),
    CB(SubtreeTimes),
    CB(Subtree),
    CB(SourceBlockContent),
    CB(CommandBlock),
    CB(List),
    CB(Paragraph),
    CB(Comment),
    CB(Table),
    CB(Structure),
});
#undef CB

#define CB(name)                                                          \
    { Str(#name), &OrgParser::parse##name }
const UnorderedMap<Str, MockFull::ParserMethod> parsers({
    CB(HashTag),
    CB(CSVArguments),
    CB(Macro),
    CB(RawUrl),
    CB(Link),
    CB(InlineMath),
    CB(Symbol),
    CB(HashTag),
    CB(Time),
    CB(Ident),
    CB(SrcInline),
    CB(Table),
    CB(CommandArguments),
    CB(SrcArguments),
    CB(Src),
    CB(ListItemBody),
    CB(ListItem),
    CB(TopParagraph),
    CB(InlineParagraph),
    CB(NestedList),
    CB(List),
    CB(LogbookClockEntry),
    CB(LogbookListEntry),
    CB(Logbook),
    CB(Drawer),
    CB(Subtree),
    CB(OrgFile),
    CB(LineCommand),
    CB(ToplevelItem),
    CB(Top),
});
#undef CB


MockFull::ParserMethod getParser(CR<Opt<Str>> name) {
    if (name.has_value()) {
        if (parsers.contains(name.value())) {
            return parsers.at(name.value());
        } else {
            throw GetterError(
                name.value() + " is missing from method table");
        }
    } else {
        return &OrgParser::parseTop;
    }
}

MockFull::LexerMethod getLexer(CR<Opt<Str>> name) {
    if (name.has_value()) {
        if (lexers.contains(name.value())) {
            return lexers.at(name.value());
        } else {
            throw GetterError(
                name.value() + " is missing from method table");
        }
    } else {
        return &OrgTokenizer::lexText;
    }
}

void compareNodes(
    CR<NodeGroup<OrgNodeKind, OrgTokenKind>> parsed,
    CR<NodeGroup<OrgNodeKind, OrgTokenKind>> expected) {
    BacktrackRes nodeSimilarity = longestCommonSubsequence<OrgNode>(
        parsed.nodes.content,
        expected.nodes.content,
        [](CR<OrgNode> lhs, CR<OrgNode> rhs) -> bool {
            if (lhs.kind != rhs.kind) {
                return false;
            } else {
                if (lhs.isTerminal()) {
                    return lhs.getToken() == rhs.getToken();
                } else {
                    return lhs.getExtent() == rhs.getExtent();
                }
            }
        })[0];


    ShiftedDiff nodeDiff{nodeSimilarity, parsed.size(), expected.size()};


    if (nodeSimilarity.lhsIndex.size() != parsed.size()
        || nodeSimilarity.rhsIndex.size() != expected.size()) {
        ShiftedDiff nodeDiff{
            nodeSimilarity, parsed.size(), expected.size()};

        Func<Str(CR<OrgNode>)> conv = [](CR<OrgNode> tok) -> Str {
            return to_string(tok);
        };

        FormattedDiff text{nodeDiff};
        // std::cout << "node differences\n";
        // std::cout << text << std::endl;
        // std::cout << "--------\n";
    }
}

void compareTokens(
    CR<TokenGroup<OrgTokenKind>> lexed,
    CR<TokenGroup<OrgTokenKind>> expected) {
    BacktrackRes tokenSimilarity = longestCommonSubsequence<OrgToken>(
        lexed.tokens.content,
        expected.tokens.content,
        [](CR<OrgToken> lhs, CR<OrgToken> rhs) -> bool {
            if (lhs.kind != rhs.kind) {
                return false;
            } else if (lhs.hasData() != rhs.hasData()) {
                return false;
            } else if (lhs.hasData() && Str(lhs.text) != Str(rhs.text)) {
                return false;
            } else {
                return true;
            }
        })[0];

    if (tokenSimilarity.lhsIndex.size() != lexed.size()
        || tokenSimilarity.rhsIndex.size() != expected.size()) {
        ShiftedDiff tokenDiff{
            tokenSimilarity, lexed.size(), expected.size()};

        Func<Str(CR<OrgToken>)> conv = [](CR<OrgToken> tok) -> Str {
            return to_string(tok);
        };

        // Vec<Str> lexedStr    = map(lexed.tokens.content, conv);
        // Vec<Str> expectedStr = map(expected.tokens.content, conv);

        FormattedDiff text{tokenDiff};

        std::cout << "token differences\n";
        if (text.isUnified()) {
            std::cout << "unified\n";
            for (const auto& [lhs, rhs] : text.unifiedLines()) {
                auto lhsStyle = toStyle(lhs.prefix);
                auto rhsStyle = toStyle(rhs.prefix);
                std::cout
                    //
                    << merge(
                           lhsStyle, left_aligned(toPrefix(lhs.prefix), 2))
                    << merge(
                           lhsStyle,
                           left_aligned(
                               to_string(lexed.tokens.content.at(
                                   lhs.originalIndex)),
                               48))
                    << merge(
                           rhsStyle, left_aligned(toPrefix(rhs.prefix), 2))
                    << merge(
                           rhsStyle,
                           left_aligned(
                               to_string(expected.tokens.content.at(
                                   rhs.originalIndex)),
                               16))
                    << std::endl;
            }
        }
        // std::cout << text << std::endl;
        // std::cout << "--------\n";
    }
}

void runSpec(CR<YAML::Node> group) {
    ParseSpecGroup parsed(group);

    for (const auto& spec : parsed.specs) {
        MockFull::LexerMethod  lexCb   = getLexer(spec.lexImplName);
        MockFull::ParserMethod parseCb = getParser(spec.parseImplName);

        MockFull p;
        p.tokenize(spec.source, lexCb);
        YAML::Emitter emitter;
        p.parse(parseCb);
        // std::cout << "\nLexed tokens\n" << yamlRepr(p.tokens) <<
        // std::endl; std::cout << "\nParsed nodes\n" << yamlRepr(p.nodes)
        // << std::endl; p.treeRepr(); p.yamlRepr();

        if (spec.subnodes.has_value()) {
            Str           buffer;
            OrgNodeGroup  nodes;
            OrgTokenGroup tokens;

            if (spec.expectedMode == ParseSpec::ExpectedMode::Nested) {
                auto tree = fromHomogeneous<OrgNodeKind, OrgTokenKind>(
                    spec.subnodes.value());
                auto flatResult = tree.flatten(buffer);
                nodes           = flatResult.first;
                tokens          = flatResult.second;
            } else {
                nodes = fromFlatNodes<OrgNodeKind, OrgTokenKind>(
                    spec.subnodes.value());
                if (spec.tokens.has_value()) {
                    tokens = fromFlatTokens<OrgTokenKind>(
                        spec.tokens.value(), buffer);
                }
            }

            // std::cout << "----------------\n";
            // std::cout << "[" << buffer << "]" << std::endl;
            // std::cout << tokens << std::endl;
            // nodes.tokens = &tokens;
            // std::cout << "nodes yaml repr:\n"
            //           << yamlRepr(nodes) << std::endl;
            // std::cout << "tokens yaml repr:\n"
            //           << yamlRepr(tokens) << std::endl;

            // std::cout << "----------------\n";
            // std::cout << p.tokens << std::endl;
            // std::cout << tokens << std::endl;
            // std::cout << "^^^^^^^^^^^\n";


            // std::cout << "token similarity " << tokenSimilarity << "\n";
            // std::cout << "node similarity " << nodeSimilarity << "\n";


            compareTokens(p.tokens, tokens);
            compareNodes(p.nodes, nodes);
        }
    }
}

TEST_CASE("Parse corpus", "[corpus]") {
    for (fs::directory_entry const& path :
         fs::recursive_directory_iterator(
             __CURRENT_FILE_DIR__ / "corpus")) {

        if (path.is_regular_file()) {
            if (testParameters.corpusGlob.empty()) {
                YAML::Node spec = YAML::LoadFile(path.path());
                runSpec(spec);
            } else {
                std::string path_str = path.path();
                int         matchRes = fnmatch(
                    testParameters.corpusGlob.c_str(),
                    path_str.c_str(),
                    FNM_EXTMATCH);
                if (!(matchRes == FNM_NOMATCH)) {
                    YAML::Node spec = YAML::LoadFile(path.path());
                    runSpec(spec);
                }
            }
        }
    }
};
