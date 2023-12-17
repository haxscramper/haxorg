#include <gtest/gtest.h>
#include <base_lexer/base_token.hpp>
import std;
import std.stdlib.Json;
#include <absl/log/log.h>
import org.parse.OrgTokenizer;
import org.parse.OrgParser;
import org.sem.SemConvert;
import org.exporters.exporteryaml;

TEST(BaseLexTest, WriteOut) {
    std::ifstream inFile("/home/haxscramper/tmp/doc2.org");

    if (!inFile.is_open()) {
        FAIL() << "Failed to open input.txt\n";
    }

    DLOG(INFO) << "Reading file";
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string content = buffer.str();
    //    std::cout << std::format("Content:\n--->{}<---\n", content);

    DLOG(INFO) << "Tokenizing string";
    BaseTokenGroup tokens = tokenize(content.data(), content.size());
    {
        DLOG(INFO) << "Constructing JSON object";
        json out = json::array();
        for (const BaseToken& token : tokens.tokens.content) {
            out.push_back(json(
                {{"line", token->line},
                 {"col", token->col},
                 {"text", token->text},
                 {"kind",
                  enum_serde<BaseTokenKind>::to_string(token.kind)}}));
        }
        DLOG(INFO) << "Writing file out";
        std::ofstream file{"/tmp/token.json"};
        CHECK(file.is_open());
        file << to_compact_json(json::object({{"tokens", out}}))
             << std::endl;
    }

    std::cout << "Found " << tokens.size() << " tokens\n";

    OrgTokenGroup target;
    OrgTokenizer  tok(&target);
    tok.convert(tokens);
    std::cout << std::format(
        "Converterd to {} org tokens\n", target.size());

    {
        json out = json::array();
        for (OrgToken const& token : target) {
            out.push_back(json(
                {{"line", token->base ? json(token->base->line) : json()},
                 {"col", token->base ? json(token->base->col) : json()},
                 {"text", token->base ? json(token->base->text) : json()},
                 {"kind",
                  enum_serde<OrgTokenKind>::to_string(token.kind)}}));
        }
        DLOG(INFO) << "Writing second file out";
        std::ofstream file{"/tmp/token2.json"};
        CHECK(file.is_open());
        file << to_compact_json(json::object({{"tokens", out}}))
             << std::endl;
    }
    OrgNodeGroup nodes{&target};
    {
        OrgParser                    parser{&nodes};
        Lexer<OrgTokenKind, OrgFill> lex{&target};
        parser.setTraceFile("/tmp/parse_trace.txt");
        parser.TraceState = true;
        (void)parser.parseFull(lex);
    }
    {
        sem::ContextStore context;
        sem::OrgConverter converter(&context);
        converter.setTraceFile("/tmp/trace_convert.txt");
        auto document = converter.toDocument(OrgAdapter(&nodes, OrgId(0)));
        ExporterYaml exporter;
        exporter.skipNullFields  = true;
        exporter.skipFalseFields = true;
        exporter.skipZeroFields  = true;
        exporter.skipLocation    = true;
        exporter.skipId          = true;
        writeFileOrStdout(
            "/tmp/sem.yaml",
            std::format("{}", exporter.evalTop(document)) + "\n",
            true);
    }
}
