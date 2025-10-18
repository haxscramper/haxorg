#pragma once

#include "org_parse_aux.hpp"


#include <string>

#include <haxorg/test/NodeTest.hpp>
#include <hstd/ext/textlayouter.hpp>

namespace org::test {

/// Whole result of the specification test run
struct TestResult {
    struct File {
        hstd::Str path;
        bool      rerun = false;
        BOOST_DESCRIBE_CLASS(File, (), (path, rerun), (), ());
    };

    struct Skip {
        hstd::Str msg;
        BOOST_DESCRIBE_CLASS(Skip, (), (msg), (), ());
    };

    struct Fail {
        hstd::Str msg;
        BOOST_DESCRIBE_CLASS(Fail, (), (msg), (), ());
    };

    struct Success {
        hstd::Str msg;
        BOOST_DESCRIBE_CLASS(Success, (), (msg), (), ());
    };

    hstd::Vec<File> debugFiles;

    SUB_VARIANTS(Kind, Data, data, getKind, Skip, Fail, Success);
    Data data;

    BOOST_DESCRIBE_CLASS(TestResult, (), (debugFiles, data), (), ());
};

struct RunContext {};


class CorpusRunner : public hstd::OperationsTracer {
  public:
    // Define environment variable in the QT app run environment to get
    // better-formatted test diff output.

    hstd::Vec<TestResult::File> files;
    bool                        inRerun = false;

    void writeFile(
        hstd::CR<ParseSpec> spec,
        hstd::CR<hstd::Str> name,
        hstd::CR<hstd::Str> content,
        hstd::CR<hstd::Str> relDebug);

    json toTextLyt(
        hstd::layout::BlockStore&                   b,
        hstd::layout::BlockId                       block,
        hstd::Func<hstd::Str(hstd::layout::LytStr)> getStr);


    struct RunResult {
        struct CompareBase {
            bool          isOk = false;
            hstd::ColText failDescribe;
            BOOST_DESCRIBE_STRUCT(CompareBase, (), (isOk, failDescribe));
        };

        struct NodeCompare : CompareBase {
            BOOST_DESCRIBE_STRUCT(NodeCompare, (CompareBase), ());
        };
        struct LexCompare : CompareBase {
            BOOST_DESCRIBE_STRUCT(LexCompare, (CompareBase), ());
        };
        struct SemCompare : CompareBase {
            BOOST_DESCRIBE_STRUCT(
                SemCompare,
                (CompareBase),
                (unexpectedParseErrors, expectedParseErrors));

            /// \brief Parsed sem content has unexpected error nodes. This
            /// field is populated if the parse had errors but no expected
            /// sem structure. If there *is* an expected sem structure,
            /// regular comparison takes precedence.
            bool unexpectedParseErrors = false;

            /// \brief If the sem compare is successful, but the tree
            /// contains parsing errors. If this is the case, the rest of
            /// the test will be skipped, as formatter is not going to
            /// correctly reproduce the document back -- as is intended.
            bool expectedParseErrors = false;
        };
        struct Skip {};
        struct None {};

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            None,
            Skip,
            NodeCompare,
            LexCompare,
            SemCompare);

        RunResult() {}
        RunResult(hstd::CR<Data> data) : data(data) {}
        Data data;

        bool isOk() const {
            return std::visit(
                hstd::overloaded{
                    [](hstd::CR<CompareBase> n) { return n.isOk; },
                    [](hstd::CR<Skip> n) { return true; },
                    [](hstd::CR<None> n) { return true; },
                },
                data);
        }
    };


    RunResult::NodeCompare compareNodes(
        hstd::CR<org::parse::OrgNodeGroup> parsed,
        hstd::CR<org::parse::OrgNodeGroup> expected);

    hstd::Opt<RunResult> runSpecInitial(
        hstd::CR<ParseSpec>   spec,
        hstd::CR<std::string> from,
        hstd::CR<hstd::Str>   relDebug,
        MockFull&             p);

    RunResult runSpecFormatted(
        hstd::CR<ParseSpec>   spec,
        hstd::CR<std::string> from,
        hstd::CR<hstd::Str>   relDebug,
        MockFull&             p);


    RunResult::SemCompare compareSem(
        hstd::CR<ParseSpec>  spec,
        sem::SemId<sem::Org> node,
        json                 expected);

    RunResult runSpec(
        hstd::CR<ParseSpec>   spec,
        hstd::CR<std::string> from,
        hstd::CR<hstd::Str>   relDebug);

    RunResult::LexCompare runSpecBaseLex(
        MockFull&           p,
        hstd::CR<ParseSpec> spec,
        hstd::CR<hstd::Str> relDebug);
    RunResult::LexCompare runSpecLex(
        MockFull&           p,
        hstd::CR<ParseSpec> spec,
        hstd::CR<hstd::Str> relDebug);
    RunResult::NodeCompare runSpecParse(
        MockFull&           p,
        hstd::CR<ParseSpec> spec,
        hstd::CR<hstd::Str> relDebug);
    RunResult::SemCompare runSpecSem(
        MockFull&           p,
        hstd::CR<ParseSpec> spec,
        hstd::CR<hstd::Str> relDebug);
};

struct TestParams {
    ParseSpec      spec;
    hstd::fs::path file;
    std::string    testName() const;
    std::string    fullName() const;
    void           PrintToImpl(std::ostream* os) const;
    friend void    PrintTo(const TestParams& point, std::ostream* os) {
        point.PrintToImpl(os);
    }
};


TestResult gtest_run_spec(
    hstd::CR<TestParams>  params,
    const hstd::fs::path& testDir);

hstd::Func<void(org::parse::OrgNodeGroup::TreeReprConf::WriteParams const& params)> getOrgParseWriteParams(
    OrgSpec const*                               spec,
    org::parse::OrgNodeGroup const*              nodes,
    hstd::UnorderedMap<parse::OrgId, int> const* parseAddedOnLine);

} // namespace org::test


template <>
struct hstd::JsonSerde<YAML::Mark> {
    static YAML::Mark from_json(json const& j) {
        auto res   = YAML::Mark();
        res.line   = JsonSerde<int>::from_json(j["line"]);
        res.column = JsonSerde<int>::from_json(j["column"]);
        res.pos    = JsonSerde<int>::from_json(j["pos"]);
        return res;
    }

    static json to_json(YAML::Mark const& value) {
        return json::object({
            {"line", JsonSerde<int>::to_json(value.line)},
            {"column", JsonSerde<int>::to_json(value.column)},
            {"pos", JsonSerde<int>::to_json(value.pos)},
        });
    }
};

template <>
struct hstd::JsonSerde<YAML::Node> {
    static YAML::Node from_json(json const& j) {
        return org::test::toYaml(j);
    }
    static json to_json(YAML::Node const& j) {
        return org::test::toJson(j);
    }
};
