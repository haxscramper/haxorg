#include <gtest/gtest.h>
#include <base_lexer/base_token.hpp>
#include <fstream>
#include <hstd/stdlib/Json.hpp>

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
    std::vector<BaseToken> tokens = tokenize(
        content.data(), content.size());
    DLOG(INFO) << "Constructing JSON object";
    json out = json::array();
    for (const BaseToken& token : tokens) {
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
}
