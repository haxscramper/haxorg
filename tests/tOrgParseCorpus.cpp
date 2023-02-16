#include "common.hpp"
#include "org_parse_aux.hpp"

#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <parse/OrgSpec.hpp>

#include <lexbase/NodeIO.hpp>
#include <lexbase/NodeTest.hpp>

#include <hstd/stdlib/Filesystem.hpp>

#define CB(name)                                                          \
    { Str(#name), &OrgTokenizer::lex##name }

const UnorderedMap<Str, MockFull::LexerMethod> lexers({
    CB(Text),
    CB(List),
    CB(Paragraph),
});
#undef CB

#define CB(name)                                                          \
    { Str(#name), &OrgParser::parse##name }
const UnorderedMap<Str, MockFull::ParserMethod> parsers{
    CB(HashTag),
};
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
        p.run(spec.source, lexCb, parseCb);

        p.treeRepr();
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
