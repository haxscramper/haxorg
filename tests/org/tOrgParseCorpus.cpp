#include <haxorg/test/corpusrunner.hpp>

#include <haxorg/parse/OrgParser.hpp>
#include <haxorg/parse/OrgTokenizer.hpp>
#include <haxorg/lexbase/NodeIO.hpp>
#include <haxorg/test/NodeTest.hpp>
#include <haxorg/sem/ErrorWrite.hpp>
#include <gtest/gtest.h>

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <haxorg/sem/SemConvert.hpp>

#include <fnmatch.h>
#include "../testprofiler.hpp"

#include <haxorg/sem/perfetto_org.hpp>

// std::string corpusGlob = "*text.yaml";
std::string corpusGlob = "";

bool enableFullTraceOnCli = false;
void enable_full_trace_on_cli() { enableFullTraceOnCli = true; }


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

        if (nameCounts.contains(spec.testName())) {
            LOG(ERROR) << fmt(
                "Found test with duplicate name: '{}', name comes from "
                "'{}' "
                "at {}:{}:{}",
                spec.testName(),
                spec.file.stem(),
                spec.spec.name,
                spec.spec.specLocation.line,
                spec.spec.specLocation.column);

        } else {
            nameCounts.insert_or_assign(spec.testName(), 1);
        }
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
    CHECK(fs::is_regular_file(canary))
        << fmt("{} does not contains tasks.py", root);
    std::stringstream ss;
    ss << YamlSchemaBuilder<ParseSpec>::get();
    writeFile(root / "corpus_schema.yaml", ss.str());
}

TEST_P(TestOrgParseCorpus, CorpusAll) {
    TestParams params = GetParam();
    if (enableFullTraceOnCli) { params.spec.debug.traceAll = true; }
    TestResult result = gtest_run_spec(params);
    switch (result.getKind()) {
        case TestResult::Kind::Fail: {
            FAIL() << result.getFail().msg;
            break;
        }

        case TestResult::Kind::Success: {
            GTEST_SUCCEED() << result.getSuccess().msg;
            break;
        }

        case TestResult::Kind::Skip: {
            GTEST_SKIP() << result.getSkip().msg;
            break;
        }
    }
}

INSTANTIATE_TEST_SUITE_P(
    CorpusAllParametrized,
    TestOrgParseCorpus,
    ::testing::ValuesIn(generateTestRuns()),
    getTestName);
