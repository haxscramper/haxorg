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
        ParseSpec const& spec,
        hstd::Str const& name,
        hstd::Str const& content,
        hstd::Str const& relDebug);

    json toTextLyt(
        hstd::layout::BlockStore&                   b,
        hstd::layout::BlockId                       block,
        hstd::Func<hstd::Str(hstd::layout::LytStr)> getStr);


    struct RunResult {
        struct CompareBase {
            bool          isOk = false;
            hstd::ColText failDescribe;
            BOOST_DESCRIBE_CLASS(
                CompareBase,
                (),
                (isOk, failDescribe),
                (),
                ());
        };

        struct NodeCompare : CompareBase {
            BOOST_DESCRIBE_CLASS(NodeCompare, (CompareBase), (), (), ());
        };
        struct LexCompare : CompareBase {
            BOOST_DESCRIBE_CLASS(LexCompare, (CompareBase), (), (), ());
        };
        struct SemCompare : CompareBase {
            BOOST_DESCRIBE_CLASS(
                SemCompare,
                (CompareBase),
                (unexpectedParseErrors, expectedParseErrors),
                (),
                ());

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
        struct Skip {
            DESC_FIELDS(Skip, ());
        };
        struct None {
            DESC_FIELDS(None, ());
        };

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
        RunResult(Data const& data) : data(data) {}
        Data data;

        DESC_FIELDS(RunResult, (data));

        bool isOk() const {
            return std::visit(
                hstd::overloaded{
                    [](CompareBase const& n) { return n.isOk; },
                    [](Skip const& n) { return true; },
                    [](None const& n) { return true; },
                },
                data);
        }
    };


    RunResult::NodeCompare compareNodes(
        org::parse::OrgNodeGroup const& parsed,
        org::parse::OrgNodeGroup const& expected);

    hstd::Opt<RunResult> runSpecInitial(
        ParseSpec const&   spec,
        std::string const& from,
        hstd::Str const&   relDebug,
        MockFull&          p);

    RunResult runSpecFormatted(
        ParseSpec const&   spec,
        std::string const& from,
        hstd::Str const&   relDebug,
        MockFull&          p);


    RunResult::SemCompare compareSem(
        ParseSpec const&              spec,
        sem::SemId<sem::Org>          node,
        json                          expected,
        org::parse::ParseContext::Ptr parse_context);

    RunResult runSpec(
        ParseSpec const&   spec,
        std::string const& from,
        hstd::Str const&   relDebug);

    RunResult::LexCompare runSpecBaseLex(
        MockFull&        p,
        ParseSpec const& spec,
        hstd::Str const& relDebug);
    RunResult::LexCompare runSpecLex(
        MockFull&        p,
        ParseSpec const& spec,
        hstd::Str const& relDebug);
    RunResult::NodeCompare runSpecParse(
        MockFull&        p,
        ParseSpec const& spec,
        hstd::Str const& relDebug);
    RunResult::SemCompare runSpecSem(
        MockFull&        p,
        ParseSpec const& spec,
        hstd::Str const& relDebug);
};

struct TestParams {
    ParseSpec      spec;
    hstd::fs::path file;
    std::string    testName() const;
    std::string    fullName() const;
    void           PrintToImpl(std::ostream* os) const;
    friend void    PrintTo(TestParams const& point, std::ostream* os) {
        point.PrintToImpl(os);
    }
};


TestResult gtest_run_spec(
    TestParams const&     params,
    hstd::fs::path const& testDir);

hstd::Func<void(org::parse::OrgNodeGroup::TreeReprConf::WriteParams const& params)> getOrgParseWriteParams(
    OrgSpec const*                               spec,
    org::parse::OrgNodeGroup const*              nodes,
    hstd::UnorderedMap<parse::OrgId, int> const* parseAddedOnLine);

} // namespace org::test
