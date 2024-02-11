#include "SemBaseApi.hpp"
#include <parse/OrgTokenizer.hpp>
#include <parse/OrgParser.hpp>
#include <sem/SemConvert.hpp>
#include <fstream>

using namespace org;
using namespace sem;

sem::SemId<sem::Document> org::parseString(
    CR<std::string> text,
    CR<ParseParams> params) {
    LexerParams p;
    p.traceStream            = params.lexBaseTrace.get();
    p.maxUnknown             = params.lexBaseMaxUnknown;
    OrgTokenGroup baseTokens = ::tokenize(text.data(), text.size(), p);
    OrgTokenGroup tokens;
    OrgTokenizer  tokenizer{&tokens};

    tokenizer.convert(baseTokens);
    Lexer<OrgTokenKind, OrgFill> lex{&tokens};

    OrgNodeGroup nodes{&tokens};
    OrgParser    parser{&nodes};
    (void)parser.parseFull(lex);

    sem::OrgConverter converter{};

    return converter.toDocument(OrgAdapter(&nodes, OrgId(0)));
}

ParseParams& ParseParams::withLexBaseTrace(CR<fs::path> file) {
    lexBaseTrace = std::static_pointer_cast<std::ostream>(
        std::make_shared<std::ofstream>(file.native()));
    return *this;
}
