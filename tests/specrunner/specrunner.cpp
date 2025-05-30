#include <haxorg/test/corpusrunner.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>

using namespace org::parse;
using namespace org::test;

template <>
struct hstd::JsonSerde<YAML::Mark> {
    static YAML::Mark from_json(json const& j) { return YAML::Mark(); }
};

template <>
struct hstd::JsonSerde<YAML::Node> {
    static YAML::Node from_json(json const& j) { return toYaml(j); }
};


template <>
struct hstd::JsonSerde<TestResult::Data> {
    static json to_json(TestResult::Data const& data) {
        json j    = json::object();
        j["kind"] = fmt1(TestResult::getKind(data));
        std::visit(
            overloaded{
                [&](CR<TestResult::Fail> file) {
                    j["fail"] = to_json_eval(file);
                },
                [&](CR<TestResult::Success> file) {
                    j["success"] = to_json_eval(file);
                },
                [&](CR<TestResult::Skip> file) {
                    j["skip"] = to_json_eval(file);
                },
            },
            data);
        return j;
    }
};

int main(int argc, char** argv) {
    LOGIC_ASSERTION_CHECK(argc == 2, "");
    auto spec = hstd::JsonSerde<ParseSpec>::from_json(
        json::parse(std::string(argv[1])));

    TestResult result      = gtest_run_spec(TestParams{.spec = spec});
    json       json_result = hstd::to_json_eval(result);
    std::cout << json_result.dump() << std::endl;
    return 0;
}
