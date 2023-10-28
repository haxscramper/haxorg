#include <gtest/gtest.h>
#include <base_lexer/base_token.hpp>
#include <fstream>

TEST(BaseLexTest, WriteOut) {
    std::ifstream inFile("/home/haxscramper/tmp/doc2.org");

    if (!inFile.is_open()) {
        FAIL() << "Failed to open input.txt\n";
    }

    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string content = buffer.str();
    //    std::cout << std::format("Content:\n--->{}<---\n", content);

    std::vector<BaseToken> tokens = tokenize(
        content.data(), content.size());
    std::ofstream out{"/tmp/token.csv"};
    out << "Line,Column,Text,Kind\n";
    for (const BaseToken& token : tokens) {
        out << token->line << "," << token->col << ", \""
            << escape_for_write(token->text, false) << "\", "
            << enum_serde<BaseTokenKind>::to_string(token.kind) << "\n";
    }
    std::cout << "Found " << tokens.size() << " tokens\n";
}
