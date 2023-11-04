#include <gtest/gtest.h>
#include <base_lexer/base_token.hpp>
#include <fstream>
#include <hstd/stdlib/Json.hpp>
#include <absl/log/log.h>
#include <parse/OrgTokenizer.hpp>

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
    DLOG(INFO) << "Constructing JSON object";
    json out = json::array();
    for (const BaseToken& token : tokens.tokens.content) {
        out.push_back(json(
            {{"line", token->line},
             {"col", token->col},
             {"text", token->text},
             {"kind", enum_serde<BaseTokenKind>::to_string(token.kind)}}));
    }
    DLOG(INFO) << "Writing file out";
    std::ofstream file{"/tmp/token.json"};
    CHECK(file.is_open());
    file << json::object({{"tokens", out}}) << std::endl;
    std::cout << "Found " << tokens.size() << " tokens\n";

    OrgTokenGroup target;
    OrgTokenizer  tok(&target);
    tok.convert(tokens);
    std::cout << std::format(
        "Converterd to {} org tokens\n", target.size());
}