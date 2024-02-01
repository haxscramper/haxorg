#include <gtest/gtest.h>
#include <base_lexer/base_token.hpp>
#include <hstd/stdlib/Json.hpp>
#include <absl/log/log.h>
#include <parse/OrgTokenizer.hpp>
#include <parse/OrgParser.hpp>
#include <sem/SemConvert.hpp>
#include <exporters/exporteryaml.hpp>
#include "corpusrunner.hpp"

TEST(ManualFileRun, TestDoc1) {
    fs::path file{"/home/haxscramper/tmp/doc1.org"};
    if (fs::exists(file)) {
        std::string content = readFile(file);
        auto        spec    = ParseSpec::FromSource(std::move(content));
        spec.debug.traceAll = true;
        gtest_run_spec(TestParams{
            .spec = spec,
            .file = "doc1",
        });
    }
}


TEST(ManualFileRun, TestDoc2) {
    std::string content = readFile("/home/haxscramper/tmp/doc2.org");
    auto        spec    = ParseSpec::FromSource(std::move(content));
    // spec.debug.traceLex  = true;
    // spec.debug.lexToFile = true;
    gtest_run_spec(TestParams{
        .spec = spec,
        .file = "doc2",
    });
}
