#include <algorithm>
#include <functional>
#include <optional>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <fmt/format.h>
#include <gtest/gtest.h>

#include <hstd_cpp_lib/extra/error_format/gtest_utils.hpp>

#include "hstd_cpp_lib/proto_serde/hstd_unidata_validate.hpp"
#include "tUnidataDSLModel.hpp"

namespace M = hstd::unidata_dsl::test;

namespace {

template <typename T>
void expect_messages(
    T const&                 value,
    std::vector<std::string> expected,
    int                      line     = __builtin_LINE(),
    char const*              function = __builtin_FUNCTION(),
    char const*              file     = __builtin_FILE()) {
    auto failures = hstd::ext::unidata::verify_all(value).getFail();

    std::vector<std::string> actual;
    for (auto const& failure : failures) { actual.push_back(failure.message); }

    std::ranges::sort(actual);
    std::ranges::sort(expected);

    EXPECT_EQ(actual, expected) << hstd::fmt("Failed at {}:{}", file, line);
}

M::OperationChecks make_checks(M::CheckKind kind) {
    M::OperationChecks result{};

    result.operation = kind;
    result.number    = 6;
    result.real      = 2.5;
    result.flag      = true;
    result.text      = "six";
    result.numbers   = {1, 2, 3};

    using Optional = decltype(result.optional);

    result.optionals = {
        Optional{1},
        Optional{},
        Optional{3},
    };

    result.mapping.insert_or_assign(hstd::Str{"a"}, 1);
    result.mapping.insert_or_assign(hstd::Str{"b"}, 2);

    result.optional = 3;
    result.coords   = decltype(result.coords){6, hstd::Str{"six"}};
    result.status   = M::Status::Ready;

    result.base.id        = 6;
    result.derived.id     = 6;
    result.derived.weight = 3;

    result.choice.data = M::Choice::First{.value = 6};

    return result;
}

struct OperationCase {
    M::CheckKind                             kind;
    std::string                              name;
    std::function<void(M::OperationChecks&)> invalidate;
};

OperationCase operation_case(
    M::CheckKind                             kind,
    std::string                              name,
    std::function<void(M::OperationChecks&)> invalidate = {}) {
    return OperationCase{
        .kind       = kind,
        .name       = std::move(name),
        .invalidate = std::move(invalidate),
    };
}

std::vector<OperationCase> operation_cases() {
    using K = M::CheckKind;
    using C = M::OperationChecks;

    return {
        operation_case(K::Eq, "Eq", [](C& value) { value.number = 8; }),
        operation_case(K::Ne, "Ne", [](C& value) { value.number = 8; }),
        operation_case(K::Lt, "Lt", [](C& value) { value.number = 8; }),
        operation_case(K::Le, "Le", [](C& value) { value.number = 8; }),
        operation_case(K::Add, "Add", [](C& value) { value.number = 8; }),
        operation_case(K::Sub, "Sub", [](C& value) { value.number = 8; }),
        operation_case(K::Mul, "Mul", [](C& value) { value.number = 8; }),
        operation_case(K::Div, "Div", [](C& value) { value.number = 9; }),
        operation_case(K::ConstFloat, "ConstFloat", [](C& value) { value.real = 3.5; }),
        operation_case(K::ConstBool, "ConstBool", [](C& value) { value.flag = false; }),
        operation_case(K::And, "And", [](C& value) { value.number = 8; }),
        operation_case(K::Or, "Or", [](C& value) { value.number = 8; }),
        operation_case(K::Not, "Not", [](C& value) { value.number = 8; }),
        operation_case(K::Cond, "Cond", [](C& value) { value.number = 8; }),
        operation_case(
            K::CondLazy,
            "CondLazy",
            [](C& value) { value.mapping.insert_or_assign(hstd::Str{"a"}, 9); }),
        operation_case(K::Let, "Let", [](C& value) { value.number = 8; }),
        operation_case(K::All, "All", [](C& value) { value.numbers = {1, 2, 4}; }),
        operation_case(K::Exists, "Exists", [](C& value) { value.numbers = {1, 2, 4}; }),
        operation_case(
            K::ExistsOne, "ExistsOne", [](C& value) { value.numbers = {1, 3, 3}; }),
        operation_case(K::Map, "Map", [](C& value) { value.numbers = {1, 2, 4}; }),
        operation_case(K::Filter, "Filter", [](C& value) { value.numbers = {1, 1, 3}; }),
        operation_case(
            K::FilterMap,
            "FilterMap",
            [](C& value) {
                value.optionals = {
                    std::nullopt,
                    std::nullopt,
                    std::nullopt,
                };
            }),
        operation_case(
            K::TakeWhile, "TakeWhile", [](C& value) { value.numbers = {1, 3, 2}; }),
        operation_case(
            K::GroupBy, "GroupBy", [](C& value) { value.numbers = {1, 2, 2}; }),
        operation_case(K::Fold, "Fold", [](C& value) { value.numbers = {1, 2, 4}; }),
        operation_case(K::Walk, "Walk", [](C& value) { value.derived.id = 8; }),
        operation_case(K::Sum, "Sum", [](C& value) { value.numbers = {1, 2, 4}; }),
        operation_case(K::Min, "Min", [](C& value) { value.numbers = {2, 3, 4}; }),
        operation_case(K::Max, "Max", [](C& value) { value.numbers = {1, 2, 4}; }),
        operation_case(K::StrSize, "StrSize", [](C& value) { value.text = "other"; }),
        operation_case(K::StrMatches, "StrMatches", [](C& value) { value.text = "bad"; }),
        operation_case(K::StrFormat, "StrFormat", [](C& value) { value.number = 8; }),
        operation_case(K::ListSize, "ListSize", [](C& value) { value.numbers = {1, 2}; }),
        operation_case(
            K::ListContains, "ListContains", [](C& value) { value.numbers = {1, 2, 4}; }),
        operation_case(K::ListAt, "ListAt", [](C& value) { value.numbers = {1, 2, 4}; }),
        operation_case(
            K::ListSlice, "ListSlice", [](C& value) { value.numbers = {1, 4, 3}; }),
        operation_case(
            K::ListSliceBounds,
            "ListSliceBounds",
            [](C& value) { value.numbers = {1, 4, 3}; }),
        operation_case(
            K::ListConcat, "ListConcat", [](C& value) { value.numbers = {1, 2}; }),
        operation_case(K::ListEmpty, "ListEmpty"),
        operation_case(
            K::MapSize, "MapSize", [](C& value) { value.mapping.erase(hstd::Str{"b"}); }),
        operation_case(
            K::MapContains,
            "MapContains",
            [](C& value) { value.mapping.erase(hstd::Str{"a"}); }),
        operation_case(
            K::MapGet,
            "MapGet",
            [](C& value) { value.mapping.insert_or_assign(hstd::Str{"a"}, 9); }),
        operation_case(
            K::MapInsert,
            "MapInsert",
            [](C& value) { value.mapping.erase(hstd::Str{"b"}); }),
        operation_case(
            K::MapReplace,
            "MapReplace",
            [](C& value) { value.mapping.insert_or_assign(hstd::Str{"a"}, 9); }),
        operation_case(
            K::MapKeys, "MapKeys", [](C& value) { value.mapping.erase(hstd::Str{"a"}); }),
        operation_case(
            K::MapValues,
            "MapValues",
            [](C& value) { value.mapping.insert_or_assign(hstd::Str{"b"}, 9); }),
        operation_case(K::MapEmpty, "MapEmpty"),
        operation_case(
            K::OptHasValue,
            "OptHasValue",
            [](C& value) { value.optional = std::nullopt; }),
        operation_case(K::OptValue, "OptValue", [](C& value) { value.optional = 4; }),
        operation_case(
            K::CaseIs,
            "CaseIs",
            [](C& value) { value.choice.data = M::Choice::Second{.label = "second"}; }),
        operation_case(
            K::CaseWhich,
            "CaseWhich",
            [](C& value) { value.choice.data = M::Choice::Second{.label = "second"}; }),
        operation_case(
            K::CaseField,
            "CaseField",
            [](C& value) { value.choice.data = M::Choice::First{.value = 8}; }),
        operation_case(
            K::EnumIs, "EnumIs", [](C& value) { value.status = M::Status::Other; }),
        operation_case(
            K::NthGet, "NthGet", [](C& value) { std::get<0>(value.coords) = 8; }),
        operation_case(K::IsDerived, "IsDerived"),
        operation_case(K::TypeCond, "TypeCond", [](C& value) { value.derived.id = 8; }),
        operation_case(
            K::TypeCondOptional,
            "TypeCondOptional",
            [](C& value) { value.derived.id = 8; }),
        operation_case(K::TypeOf, "TypeOf"),
        operation_case(K::PathOf, "PathOf"),
        operation_case(K::EmptyCollections, "EmptyCollections"),
    };
}

M::MessageChecks make_message_checks() {
    M::MessageChecks result{};

    result.number  = 6;
    result.real    = 2.5;
    result.flag    = true;
    result.text    = "six";
    result.numbers = {1, 2, 3};

    return result;
}

M::Graph make_graph() {
    return M::Graph{
        .nodes = {
            M::Node{.id = "a"},
            M::Node{.id = "b"},
        },
        .edges = {
            M::Edge{.source = "a", .target = "b"},
        },
    };
}

} // namespace

TEST(UnidataDSL, TrivialStringField) {
    expect_messages(M::TrivialText{.text = "non-empty"}, {});
    expect_messages(M::TrivialText{.text = ""}, {"text must not be empty"});
}

TEST(UnidataDSL, EveryOperationAcceptsItsValidInput) {
    for (auto const& entry : operation_cases()) {
        SCOPED_TRACE(entry.name);

        auto value = make_checks(entry.kind);
        expect_messages(value, {});
    }
}

TEST(UnidataDSL, EveryMutableOperationRejectsItsInvalidInput) {
    for (auto const& entry : operation_cases()) {
        if (!entry.invalidate) { continue; }

        SCOPED_TRACE(entry.name);

        auto value = make_checks(entry.kind);
        entry.invalidate(value);

        expect_messages(value, {fmt::format("poc.{}", entry.name)});
    }
}

TEST(UnidataDSL, AndDoesNotEvaluateLaterOperandsAfterFalse) {
    auto value = make_checks(M::CheckKind::And);

    value.flag = false;
    value.mapping.clear();

    expect_messages(value, {"poc.And"});
}

TEST(UnidataDSL, OrDoesNotEvaluateLaterOperandsAfterTrue) {
    auto value = make_checks(M::CheckKind::Or);

    value.mapping.clear();

    expect_messages(value, {});
}

TEST(UnidataDSL, CondDoesNotEvaluateItsUnselectedDefault) {
    auto value = make_checks(M::CheckKind::CondLazy);

    EXPECT_FALSE(value.mapping.contains(hstd::Str{"absent"}));
    expect_messages(value, {});
}

TEST(UnidataDSL, CondEvaluatesItsSelectedDefault) {
    auto value = make_checks(M::CheckKind::CondLazy);

    value.flag = false;
    value.mapping.insert_or_assign(hstd::Str{"absent"}, 1);

    expect_messages(value, {});

    value.mapping.insert_or_assign(hstd::Str{"absent"}, 9);

    expect_messages(value, {"poc.CondLazy"});
}

TEST(UnidataDSL, CondPropagatesErrorsFromItsSelectedBranch) {
    auto value = make_checks(M::CheckKind::CondLazy);

    value.flag = false;

    EXPECT_ANY_THROW(hstd::ext::unidata::verify_all(value));
}

TEST(UnidataDSL, LetBinderShadowingDoesNotChangeTheModel) {
    auto value = make_checks(M::CheckKind::Let);

    expect_messages(value, {});
    EXPECT_EQ(value.number, 6);
}

TEST(UnidataDSL, ExistsOneRejectsZeroMatches) {
    auto value = make_checks(M::CheckKind::ExistsOne);

    value.numbers = {1, 2, 4};

    expect_messages(value, {"poc.ExistsOne"});
}

TEST(UnidataDSL, ExistsOneRejectsMultipleMatches) {
    auto value = make_checks(M::CheckKind::ExistsOne);

    value.numbers = {3, 2, 3};

    expect_messages(value, {"poc.ExistsOne"});
}

TEST(UnidataDSL, TakeWhileStopsAtTheFirstRejectedElement) {
    auto value = make_checks(M::CheckKind::TakeWhile);

    value.numbers = {1, 3, 2};

    expect_messages(value, {"poc.TakeWhile"});
}

TEST(UnidataDSL, GroupByPreservesFirstOccurrenceOrder) {
    auto value = make_checks(M::CheckKind::GroupBy);

    value.numbers = {3, 1, 2};

    expect_messages(value, {});
}

TEST(UnidataDSL, MapInsertionDoesNotMutateTheInput) {
    auto value = make_checks(M::CheckKind::MapInsert);

    expect_messages(value, {});

    EXPECT_FALSE(value.mapping.contains(hstd::Str{"c"}));
    EXPECT_EQ(static_cast<int>(value.mapping.size()), 2);
    EXPECT_EQ(value.mapping.at(hstd::Str{"a"}), 1);
    EXPECT_EQ(value.mapping.at(hstd::Str{"b"}), 2);
}

TEST(UnidataDSL, MapReplacementDoesNotMutateTheInput) {
    auto value = make_checks(M::CheckKind::MapReplace);

    expect_messages(value, {});

    EXPECT_EQ(value.mapping.at(hstd::Str{"a"}), 1);
    EXPECT_EQ(static_cast<int>(value.mapping.size()), 2);
}

TEST(UnidataDSL, OptionalValueIsNotEvaluatedWhenMissing) {
    auto value = make_checks(M::CheckKind::OptValue);

    value.optional = std::nullopt;

    expect_messages(value, {"poc.OptValue"});
}

TEST(UnidataDSL, VariantFieldIsNotAccessedForAnotherCase) {
    auto value = make_checks(M::CheckKind::CaseField);

    value.choice.data = M::Choice::Second{.label = "second"};

    expect_messages(value, {"poc.CaseField"});
}

TEST(UnidataDSL, TupleStringElementIsChecked) {
    auto value = make_checks(M::CheckKind::NthGet);

    std::get<1>(value.coords) = "other";

    expect_messages(value, {"poc.NthGet"});
}

TEST(UnidataDSL, TypeCondUsesTheFirstMatchingCase) {
    auto value = make_checks(M::CheckKind::TypeCond);

    expect_messages(value, {});
}

TEST(UnidataDSL, TypeOfRetainsTheConcreteTypeAfterBaseNarrowing) {
    auto value = make_checks(M::CheckKind::TypeOf);

    expect_messages(value, {});
}

TEST(UnidataDSL, PathsSurviveMappingAndTypeNarrowing) {
    auto value = make_checks(M::CheckKind::PathOf);

    expect_messages(value, {});
}

TEST(UnidataDSL, EmptyCollectionsDoNotEvaluateTheirBodies) {
    auto value = make_checks(M::CheckKind::EmptyCollections);

    value.numbers.clear();
    value.optionals.clear();
    value.mapping.clear();
    value.optional = std::nullopt;

    expect_messages(value, {});
}

TEST(UnidataDSL, ListAtPropagatesOutOfRange) {
    auto value = make_checks(M::CheckKind::ListAt);

    value.numbers.clear();

    EXPECT_ANY_THROW(hstd::ext::unidata::verify_all(value));
}

TEST(UnidataDSL, MapGetPropagatesMissingKey) {
    auto value = make_checks(M::CheckKind::MapGet);

    value.mapping.clear();

    EXPECT_ANY_THROW(hstd::ext::unidata::verify_all(value));
}

TEST(UnidataDSL, MinRejectsAnEmptyCollection) {
    auto value = make_checks(M::CheckKind::Min);

    value.numbers.clear();

    EXPECT_ANY_THROW(hstd::ext::unidata::verify_all(value));
}

TEST(UnidataDSL, MaxRejectsAnEmptyCollection) {
    auto value = make_checks(M::CheckKind::Max);

    value.numbers.clear();

    EXPECT_ANY_THROW(hstd::ext::unidata::verify_all(value));
}

TEST(UnidataDSL, FieldChecksUseTheContainingObjectPointer) {
    M::FieldChecks value{
        .padding = 123,
        .text    = "non-empty",
        .numbers = {1, 2, 3},
    };

    expect_messages(value, {});

    value.text = "";

    expect_messages(value, {"text length is 0"});
}

TEST(UnidataDSL, MultipleFieldFailuresHaveIndependentMessages) {
    M::FieldChecks value{
        .padding = 123,
        .text    = "",
        .numbers = {1, -2},
    };

    expect_messages(
        value,
        {
            "text length is 0",
            "values=[1, -2]",
        });
}

TEST(UnidataDSL, BaseChecksRunForDerivedObjects) {
    M::Derived value{};

    value.id     = 6;
    value.weight = 3;

    expect_messages(value, {});

    value.id = 0;

    expect_messages(value, {"base id must be positive"});
}

TEST(UnidataDSL, DerivedChecksRunAlongsideBaseChecks) {
    M::Derived value{};

    value.id     = 0;
    value.weight = 0;

    expect_messages(
        value,
        {
            "base id must be positive",
            "derived weight must be positive",
        });
}

TEST(UnidataDSL, SuccessfulChecksDoNotEvaluateTheirMessage) {
    auto value = make_message_checks();

    EXPECT_TRUE(value.details.empty());
    expect_messages(value, {});
}

TEST(UnidataDSL, FailureMessagesFormatAllSupportedConversions) {
    auto value = make_message_checks();

    value.number = 8;
    value.details.insert_or_assign(hstd::Str{"detail"}, 17);

    expect_messages(
        value,
        {"n=8 real=2.5 sci=2.500000e+00 hex=8 oct=8 flag=true text=six list=[1, 2, 3] "
         "lookup=17"});
}

TEST(UnidataDSL, FailureMessagesFormatFalseBooleans) {
    auto value = make_message_checks();

    value.number = 8;
    value.flag   = false;
    value.details.insert_or_assign(hstd::Str{"detail"}, 17);

    expect_messages(
        value,
        {"n=8 real=2.5 sci=2.500000e+00 hex=8 oct=8 flag=false text=six list=[1, 2, 3] "
         "lookup=17"});
}

TEST(UnidataDSL, FailureMessagesPropagateExpressionErrors) {
    auto value = make_message_checks();

    value.number = 8;

    EXPECT_ANY_THROW(hstd::ext::unidata::verify_all(value));
}

TEST(UnidataDSL, CompositeGraphAcceptsValidReferences) {
    auto value = make_graph();

    expect_messages(value, {});
}

TEST(UnidataDSL, CompositeGraphReportsDuplicateObjectPaths) {
    auto value = make_graph();

    value.nodes.push_back(M::Node{.id = "a"});

    expect_messages(value, {"duplicate node ids at [[/nodes/0, /nodes/2]]"});
}

TEST(UnidataDSL, CompositeGraphReportsDanglingEdgePaths) {
    auto value = make_graph();

    value.edges.push_back(M::Edge{.source = "a", .target = "missing"});

    expect_messages(value, {"dangling edges at [/edges/1]"});
}

TEST(UnidataDSL, CompositeGraphReportsMultipleDanglingEdges) {
    auto value = make_graph();

    value.edges.at(0).source = "missing-source";
    value.edges.push_back(M::Edge{.source = "a", .target = "missing-target"});

    expect_messages(value, {"dangling edges at [/edges/0, /edges/1]"});
}

TEST(UnidataDSL, CompositeGraphReportsIndependentFailures) {
    auto value = make_graph();

    value.nodes.push_back(M::Node{.id = "a"});
    value.edges.push_back(M::Edge{.source = "missing", .target = "b"});

    expect_messages(
        value,
        {
            "duplicate node ids at [[/nodes/0, /nodes/2]]",
            "dangling edges at [/edges/1]",
        });
}

TEST(UnidataDSL, CompositeGraphAcceptsEmptyCollections) {
    M::Graph value{};

    expect_messages(value, {});
}

TEST(UnidataDSL, CompositeGraphRejectsReferencesWithoutNodes) {
    M::Graph value{
        .nodes = {},
        .edges = {
            M::Edge{.source = "a", .target = "b"},
        },
    };

    expect_messages(value, {"dangling edges at [/edges/0]"});
}
