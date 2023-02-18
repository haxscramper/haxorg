#include "common.hpp"
#include "org_parse_aux.hpp"

#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <parse/OrgSpec.hpp>

#include <lexbase/NodeIO.hpp>
#include <lexbase/NodeTest.hpp>

#include <hstd/stdlib/Filesystem.hpp>

#include <hstd/stdlib/diffs.hpp>

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

void runSpec(CR<YAML::Node> group) {
    ParseSpecGroup parsed(group);

    for (const auto& spec : parsed.specs) {
        MockFull::LexerMethod  lexCb   = getLexer(spec.lexImplName);
        MockFull::ParserMethod parseCb = getParser(spec.parseImplName);

        MockFull p;
        p.tokenize(spec.source, lexCb);
        std::cout << "\n---\n" << p.tokens << std::endl;
        p.parse(parseCb);

        // p.treeRepr();
        // p.yamlRepr();

        if (spec.subnodes.has_value()) {
            auto tree = fromHomogeneous<OrgNodeKind, OrgTokenKind>(
                spec.subnodes.value());
            Str buffer;
            auto [nodes, tokens] = tree.flatten(buffer);
            std::cout << "----------------\n";
            std::cout << "[" << buffer << "]" << std::endl;
            std::cout << tokens << std::endl;
            nodes.tokens = &tokens;
            std::cout << "nodes yaml repr:\n"
                      << yamlRepr(nodes) << std::endl;
            std::cout << "tokens yaml repr:\n"
                      << yamlRepr(tokens) << std::endl;

            BacktrackRes tokenSimilarity = longestCommonSubsequence<
                OrgToken>(
                p.tokens.tokens.content,
                tokens.tokens.content,
                [](CR<OrgToken> lhs, CR<OrgToken> rhs) -> bool {
                    std::cout << lhs << " " << rhs << "\n";
                    return lhs.kind == rhs.kind
                        && Str(lhs.text) == Str(rhs.text);
                })[0];

            std::cout << "token similarity " << tokenSimilarity << "\n";

            BacktrackRes nodeSimilarity = longestCommonSubsequence<
                OrgNode>(
                p.nodes.nodes.content,
                nodes.nodes.content,
                [](CR<OrgNode> lhs, CR<OrgNode> rhs) -> bool {
                    return lhs.kind == rhs.kind;
                })[0];

            std::cout << "node similarity " << nodeSimilarity << "\n";
        }
    }
}

TEST_CASE("Parse corpus") {
    for (fs::directory_entry const& path :
         fs::recursive_directory_iterator(
             __CURRENT_FILE_DIR__ / "corpus")) {

        if (path.is_regular_file()) {
            std::cout << path;
            YAML::Node spec = YAML::LoadFile(path.path());
            runSpec(spec);
        }
    }
};
