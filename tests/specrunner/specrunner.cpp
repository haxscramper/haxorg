#include <test/corpusrunner.hpp>

namespace YAML {
void from_json(json const& j, YAML::Node& out) { out = toYaml(j); }
void from_json(json const& j, YAML::Mark& out) { ; }
} // namespace YAML

namespace nlohmann {
void from_json(json const& j, json& out) { out = j; }

void to_json(json& j, TestResult::Data const& data) {
    j         = json::object();
    j["kind"] = fmt1(TestResult::getKind(data));
    std::visit(
        overloaded{
            [&](CR<TestResult::Fail> file) { j["fail"] = file; },
            [&](CR<TestResult::Success> file) { j["success"] = file; },
            [&](CR<TestResult::Skip> file) { j["skip"] = file; },
        },
        data);
}
} // namespace nlohmann

int main(int argc, char** argv) {
    CHECK(argc == 2);
    json      json_spec = json::parse(std::string(argv[1]));
    ParseSpec spec;
    from_json(json_spec, spec);

    TestResult result = gtest_run_spec(TestParams{.spec = spec});
    json       json_result;
    to_json(json_result, result);
    std::cout << json_result.dump() << std::endl;
    return 0;
}
