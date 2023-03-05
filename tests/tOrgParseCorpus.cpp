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
#include <ranges>

namespace rs = std::views;

#define CB(name)                                                          \
    { Str(#name), &OrgTokenizer::lex##name }

void writeFileOrStdout(
    fs::path const& target,
    QString const&  content,
    bool            useStdout) {
    if (useStdout) {
        writeFile(target, content);
    } else {
        QFile file;
        file.open(stdout, QIODevice::WriteOnly);
        QTextStream stream{&file};
        stream << content;
    }
}


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
    CB(Global),
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


MockFull::ParserMethod getParser(CR<Str> name) {
    if (parsers.contains(name)) {
        return parsers.at(name);
    } else {
        throw GetterError(
            "'$#$#' is missing from parser method table"
            % to_string_vec(name, name.empty() ? "(empty)" : ""));
    }
}

MockFull::LexerMethod getLexer(CR<Str> name) {
    if (lexers.contains(name)) {
        return lexers.at(name);
    } else {
        throw GetterError(
            "'$#$#' is missing from lexer method table"
            % to_string_vec(name, name.empty() ? "(empty)" : ""));
    }
}

inline void format(
    QTextStream&             os,
    CR<FormattedDiff>        text,
    Func<QString(int, bool)> formatCb,
    int                      lhsSize = 48,
    int                      rhsSize = 16) {
    if (text.isUnified()) {
        qDebug() << text.unified().lhs.size() << text.unified().rhs.size();
        os << (ColText("Given") <<= lhsSize) << (ColText("Expected"))
           << "\n";
        for (const auto& [lhs, rhs] : text.unifiedLines()) {
            auto lhsStyle = toStyle(lhs.prefix);
            auto rhsStyle = toStyle(rhs.prefix);
            os
                //
                << (ColText(lhsStyle, toPrefix(lhs.prefix)) <<= 2)
                << ((lhs.empty() ? ColText("")
                                 : ColText(
                                     lhsStyle,
                                     formatCb(lhs.index().value(), true)))
                    <<= lhsSize)
                << (ColText(rhsStyle, toPrefix(rhs.prefix)) <<= 2)
                << ((rhs.empty() ? ColText("")
                                 : ColText(
                                     rhsStyle,
                                     formatCb(rhs.index().value(), false)))
                    <<= rhsSize)
                << Qt::endl;
        }
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


    if (nodeSimilarity.lhsIndex.size() == parsed.size()
        && nodeSimilarity.rhsIndex.size() == expected.size()) {
        SUCCEED("Parsed tree structure match");
    } else {
        ShiftedDiff nodeDiff{
            nodeSimilarity, parsed.size(), expected.size()};

        Func<Str(CR<OrgNode>)> conv = [](CR<OrgNode> tok) -> Str {
            return to_string(tok);
        };

        FormattedDiff text{nodeDiff};
        QString       buffer;
        QTextStream   os{&buffer};
        format(os, text, [&](int id, bool isLhs) -> QString {
            auto node = isLhs ? parsed.nodes.content.at(id)
                              : expected.nodes.content.at(id);

            auto group = isLhs ? &parsed : &expected;

            return "$# $# $#($# $# $#)"
                 % to_string_vec(
                       id,
                       node.kind,
                       hshow(group->strVal(OrgId(id))).toString(false),
                       node.kind,
                       node.isTerminal(),
                       node.isTerminal() ? to_string(node.getToken())
                                         : to_string(node.getExtent()));
        });

        qcout << buffer << Qt::endl;
        FAIL("Parsed tree structure mismatch");
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
            } else if (
                lhs.hasData()
                && Str(lhs.getText()) != Str(rhs.getText())) {
                return false;
            } else {
                return true;
            }
        })[0];

    if (tokenSimilarity.lhsIndex.size() == lexed.size()
        && tokenSimilarity.rhsIndex.size() == expected.size()) {
        SUCCEED("Token lexer execution correct");
    } else {
        ShiftedDiff tokenDiff{
            tokenSimilarity, lexed.size(), expected.size()};

        Func<Str(CR<OrgToken>)> conv = [](CR<OrgToken> tok) -> Str {
            return to_string(tok);
        };

        // Vec<Str> lexedStr    = map(lexed.tokens.content, conv);
        // Vec<Str> expectedStr = map(expected.tokens.content, conv);

        FormattedDiff text{tokenDiff};

        QString     buffer;
        QTextStream os{&buffer};
        format(os, text, [&](int id, bool isLhs) -> QString {
            auto tok = isLhs ? lexed.tokens.content.at(id)
                             : expected.tokens.content.at(id);


            return "$# $# $#"
                 % to_string_vec(
                       id,
                       tok.kind,
                       hshow(tok.strVal()).toString(false),
                       tok.hasData());
        });

        qcout << buffer << Qt::endl;
        FAIL("Lexed token mismatch");
    }
}

void runSpec(CR<ParseSpec> spec, CR<QString> from) {
    MockFull::LexerMethod lexCb = getLexer(spec.lexImplName);
    MockFull              p;

    p.trace = spec.dbg.traceParse;
    if (spec.dbg.parseToFile) {
        p.setTraceFile("/tmp/parse.txt");
    }

    p.tokenizer.trace = spec.dbg.traceLex;
    if (spec.dbg.lexToFile) {
        p.tokenizer.setTraceFile("/tmp/random.txt");
    }

    if (spec.dbg.printSource) {
        qDebug().noquote().nospace()
            << "\n------------------\n"
            << spec.source << "\n------------------\n";
    }

    if (spec.dbg.doLex) {
        p.tokenize(spec.source, lexCb);
    }
    YAML::Emitter emitter;

    Str           buffer;
    OrgNodeGroup  nodes;
    OrgTokenGroup tokens;

    if (spec.expectedMode == ParseSpec::ExpectedMode::Nested) {
        if (spec.subnodes.has_value()) {
            auto tree = fromHomogeneous<OrgNodeKind, OrgTokenKind>(
                spec.subnodes.value());
            auto flatResult = tree.flatten(buffer);
            nodes           = flatResult.first;
            tokens          = flatResult.second;
        }
    } else {
        if (spec.tokens.has_value()) {
            tokens = fromFlatTokens<OrgTokenKind>(
                spec.tokens.value(), buffer);
        }

        if (spec.subnodes.has_value()) {
            nodes = fromFlatNodes<OrgNodeKind, OrgTokenKind>(
                spec.subnodes.value());
        }
    }

    p.nodes.tokens = &p.tokens;
    nodes.tokens   = &tokens;

    if (spec.dbg.printLexed) {
        writeFileOrStdout(
            "/tmp/lexed.yaml",
            to_string(yamlRepr(p.tokens)),
            spec.dbg.printLexedToFile);
    }

    if (spec.dbg.doLex) {
        if (spec.tokens.has_value()) {
            compareTokens(p.tokens, tokens);
        }

        if (spec.dbg.doParse) {
            MockFull::ParserMethod parseCb = getParser(spec.parseImplName);

            p.parse(parseCb);

            if (spec.dbg.printParsed) {
                writeFileOrStdout(
                    "/tmp/parsed.yaml",
                    to_string(yamlRepr(p.nodes)),
                    spec.dbg.printParsedToFile);
            }

            if (spec.subnodes.has_value()) {
                compareNodes(p.nodes, nodes);
            }
        }
    }
}

void runSpec(CR<YAML::Node> group, CR<QString> from) {
    ParseSpecGroup parsed{group, from};
    auto           sectionName = [&](CR<ParseSpec> spec) {
        return ("$# at $#"
                % to_string_vec(
                    spec.testName.has_value() ? spec.testName.value()
                                              : QString("<spec>"),
                    from))
            .toStdString();
    };


    for (const auto& spec : parsed.specs) {
        SECTION(sectionName(spec)) { runSpec(spec, from); }
    }
}

TEST_CASE("Parse corpus", "[corpus]") {
    std::string glob = testParameters.corpusGlob.toStdString();
    for (fs::directory_entry const& path :
         fs::recursive_directory_iterator(
             __CURRENT_FILE_DIR__ / "corpus")) {

        if (path.is_regular_file()) {
            if (testParameters.corpusGlob.empty()) {
                YAML::Node spec = YAML::LoadFile(path.path());
                runSpec(spec, QString::fromStdString(path.path()));
            } else {
                std::string path_str = path.path();
                int         matchRes = fnmatch(
                    glob.c_str(), path_str.c_str(), FNM_EXTMATCH);
                if (!(matchRes == FNM_NOMATCH)) {
                    YAML::Node spec = YAML::LoadFile(path.path());
                    runSpec(spec, QString::fromStdString(path.path()));
                }
            }
        }
    }
};
