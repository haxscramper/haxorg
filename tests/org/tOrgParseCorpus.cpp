#include <haxorg/test/corpusrunner.hpp>

#include <haxorg/parse/OrgParser.hpp>
#include <haxorg/parse/OrgTokenizer.hpp>
#include <haxorg/lexbase/NodeIO.hpp>
#include <haxorg/test/NodeTest.hpp>
#include <hstd/ext/error_write.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <gtest/gtest.h>
#include <iostream>

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <haxorg/sem/SemConvert.hpp>

#include <fnmatch.h>
#include "../testprofiler.hpp"

#include <haxorg/sem/perfetto_org.hpp>
#include "tOrgTestCommon.hpp"

#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/MapFormatter.hpp>

using namespace hstd;
using namespace org::test;

// std::string corpusGlob = "*text.yaml";
std::string corpusGlob = "";


Vec<TestParams> generateTestRuns() {
    Vec<TestParams> results;

    auto addSpecs = [&](fs::path const& path) {
        YAML::Node     group = YAML::LoadFile(path.native());
        ParseSpecGroup parsed{
            group, path.native(), __CURRENT_FILE_DIR__ / "corpus"};
        for (const auto& spec : parsed.specs) {
            results.push_back({spec, path});
        }
    };

    for (fs::directory_entry const& it : fs::recursive_directory_iterator(
             __CURRENT_FILE_DIR__ / "corpus")) {
        fs::path path{it.path()};
        if (fs::is_regular_file(path)
            && path.native().ends_with(".yaml")) {
            std::string p = path.native();
            if (corpusGlob.empty()) {
                addSpecs(path);
            } else {
                int matchRes = fnmatch(
                    corpusGlob.c_str(), p.c_str(), FNM_EXTMATCH);
                if (!(matchRes == FNM_NOMATCH)) { addSpecs(path); }
            }
        }
    }

    UnorderedMap<std::string, int> nameCounts;

    for (auto& spec : results) {
        if (spec.spec.debug.debugOutDir.size() == 0) {
            spec.spec.debug.debugOutDir = "/tmp/corpus_runs/"
                                        + spec.testName();
        }

        LOGIC_ASSERTION_CHECK_FMT(
            !nameCounts.contains(spec.testName()),
            "Found test with duplicate name: '{}', name comes from "
            "'{}' "
            "at {}:{}:{}",
            spec.testName(),
            spec.file.stem(),
            spec.spec.name,
            spec.spec.specLocation.line,
            spec.spec.specLocation.column);

        nameCounts.insert_or_assign(spec.testName(), 1);
    }

    return results;
}

class TestOrgParseCorpus : public ::testing::TestWithParam<TestParams> {
  protected:
    Opt<TestProfiler> profiler;


    void SetUp() override {
        profiler = TestProfiler{
            ("/tmp/" + GetParam().testName() + "_xray"),
            ("/tmp/" + GetParam().testName() + "_pgo"),
            json::object({
                {"meta", GetParam().fullName()},
            })};
        profiler->SetUp();
    }
    void TearDown() override { profiler->TearDown(); }
};


std::string getTestName(
    const testing::TestParamInfo<TestOrgParseCorpus::ParamType>& info) {
    return info.param.testName();
}

template <typename T>
struct YamlSchemaBuilder;

template <>
struct YamlSchemaBuilder<bool> {
    static yaml get() { return yaml{"bool"}; }
};

template <>
struct YamlSchemaBuilder<std::string> {
    static yaml get() { return yaml{"str"}; }
};

template <>
struct YamlSchemaBuilder<Str> {
    static yaml get() { return yaml{"str"}; }
};

template <>
struct YamlSchemaBuilder<int> {
    static yaml get() { return yaml{"int"}; }
};

template <>
struct YamlSchemaBuilder<yaml> {
    static yaml get() { return yaml{"any"}; }
};

template <>
struct YamlSchemaBuilder<json> {
    static yaml get() { return yaml{"any"}; }
};

template <>
struct YamlSchemaBuilder<YAML::Mark> {
    static yaml get() { return yaml{"any"}; }
};


template <typename T>
struct YamlSchemaBuilder<Opt<T>> {
    static yaml get() { return YamlSchemaBuilder<T>::get(); }
};

template <DescribedEnum T>
struct YamlSchemaBuilder<T> {
    static yaml get() {
        yaml values;
        for (auto const& name : enumerator_names<T>()) {
            values.push_back(name);
        }

        yaml result;
        result["type"] = "str";
        result["enum"] = values;

        return result;
    }
};

template <typename T>
struct YamlSchemaBuilder<Vec<T>> {
    static yaml get() {
        yaml values;
        values.push_back(YamlSchemaBuilder<T>::get());
        yaml result;
        result["type"] = "seq";
        result["enum"] = values;

        return result;
    }
};

template <DescribedRecord T>
struct YamlSchemaBuilder<T> {
    static yaml get() {
        yaml map_content;
        for_each_field_with_bases<T>([&](auto const& field) {
            map_content[field.name] = YamlSchemaBuilder<
                std::remove_cvref_t<
                    decltype(std::declval<T>().*field.pointer)>>::get();
        });

        yaml result;
        result["type"]    = "map";
        result["mapping"] = map_content;

        return result;
    }
};

TEST(ParseFileAux, GenerateYamlSchema) {
    auto root   = __CURRENT_FILE_DIR__.parent_path().parent_path();
    auto canary = root / "tasks.py";
    if (fs::is_regular_file(canary)) {
        std::stringstream ss;
        ss << YamlSchemaBuilder<ParseSpec>::get();
        writeFile(root / "corpus_schema.yaml", ss.str());
    }
}

TEST_P(TestOrgParseCorpus, CorpusAll) {
    auto       testDir = getDebugDir("", false);
    TestParams params  = GetParam();
    if (is_full_trace_on_cli_enabled()) {
        params.spec.debug.traceAll = true;
    }
    TestResult result = gtest_run_spec(params, getDebugDir());

    auto add_gtest_prefix = [](hstd::Str const& text) {
        auto                     lines = text.split("\n");
        std::vector<std::string> filtered;

        int start = 0;
        int end   = lines.size() - 1;

        while (
            start < lines.size()
            && ranges::all_of(
                lines.at(start), [](char c) { return std::isspace(c); })) {
            ++start;
        }

        while (0 <= end && ranges::all_of(lines.at(end), [](char c) {
                   return std::isspace(c);
               })) {
            --end;
        }

        for (int i = start; i <= end; ++i) {
            filtered.push_back(lines.at(i));
        }

        // if (!filtered.empty()) { __builtin_debugtrap(); }

        return filtered | hstd::rv::transform([](hstd::Str const& s) {
                   return "[          ] <"_ss + s + ">"_ss;
               })
             | hstd::rv_intersperse_newline_join;
    };


    switch (result.getKind()) {
        case TestResult::Kind::Fail: {
            std::cout << "[          ] ";
            GTEST_FAIL() << add_gtest_prefix(result.getFail().msg);
            break;
        }

        case TestResult::Kind::Success: {
            GTEST_SUCCEED() << add_gtest_prefix(result.getSuccess().msg);
            break;
        }

        case TestResult::Kind::Skip: {
            std::cout << "[          ] ";
            GTEST_SKIP() << add_gtest_prefix(result.getSkip().msg);
            break;
        }
    }
}

INSTANTIATE_TEST_SUITE_P(
    CorpusAllParametrized,
    TestOrgParseCorpus,
    ::testing::ValuesIn(generateTestRuns()),
    getTestName);
