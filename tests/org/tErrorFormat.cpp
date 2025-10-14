#include <hstd/ext/error_write.hpp>
#include <gtest/gtest.h>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/diffs.hpp>
#include "../common.hpp"

using namespace hstd::ext;
using namespace hstd;

TEST(PrintError, Simple) {
    StrCache sources;
    Id       a_id = 1;

    sources.add(
        a_id,
        R"(def five = match () in {
        () => 5,
        () => "5",
}

def six =
    five
    + 1
)",
        "a_tao");

    auto report //
        = Report(ReportKind::Error, a_id, 10)
              .with_config(Config{} //
                               .with_compact(true)
                               .with_char_set(Config::unicode()))
              .with_message("Incompatible types"_ss)
              .with_label(Label{1}
                              .with_span(a_id, slice(0, 1))
                              .with_color(ColStyle{}.red()))
              .with_label(Label{2}
                              .with_span(a_id, slice(2, 3))
                              .with_color(ColStyle{}.red())
                              .with_message("`b` for banana"_ss)
                              .with_order(1))
              .with_label(Label{3}
                              .with_span(a_id, slice(4, 5))
                              .with_color(ColStyle{}.green()))
              .with_label(Label{4}
                              .with_span(a_id, slice(7, 9))
                              .with_color(ColStyle{}.cyan())
                              .with_message("`e` for emerald"_ss))
              .with_note(
                  "Outputs of {} expressions must coerce to the same type"_ss);


    writeFile(
        getDebugFile("error_Simple.txt"),
        report.to_string(sources, false));
}

Pair<Vec<Label>, Str> labelPair(Vec<Label> const& it, Str const& it2) {
    return {it, it2};
}

Pair<Vec<Label>, Str> labelList(
    Vec<Pair<Vec<Label>, Str>> const& text,
    Id                                source) {
    Str        str;
    Vec<Label> labels;
    int        label_idx = 0;

    for (auto const& [in_labels, in_str] : text) {
        int first = str.size();
        str += in_str;
        int last = str.size() - 1;
        for (auto const& label : in_labels) {
            labels.push_back(label.clone()
                                 .with_id(++label_idx)
                                 .with_span(source, slice(first, last)));
        }
    }

    return {labels, str};
}


std::string pivotStringTable(const std::string& input) {
    std::stringstream ss(input);
    std::string       line;
    Vec<Vec<char>>    matrix;
    int               max_length = 0;

    while (std::getline(ss, line)) {
        max_length = std::max<int>(max_length, line.size());
        matrix.push_back(Vec<char>(line.begin(), line.end()));
    }

    std::stringstream result;
    for (int in_col = 0; in_col < max_length; ++in_col) {
        for (int in_row = 0; in_row < matrix.size(); ++in_row) {
            result << matrix.at(in_row).at_or(in_col, ' ');
        }
        result << "\n";
    }

    return result.str();
}

struct PrintErrorTestSetup {
    StrCache   sources;
    Id         id = 1;
    Report     report;
    Str        str;
    Vec<Label> labels;

    Str report_text;
    Str pivoted;

    PrintErrorTestSetup(
        Vec<Pair<Vec<Label>, Str>> list,
        Characters const&          chars)
        : report{ReportKind::Error, id, 12} //
    {
        report.with_config(Config{}.with_char_set(chars));
        auto [_labels, _str] = labelList(list, id);
        labels               = _labels;
        str                  = _str;
        sources.add(id, str, "file");
        for (auto const& label : labels) { report.with_label(label); }
    }


    void build_report() {
        report_text = report.to_string(sources, false);
        pivoted     = pivotStringTable(report_text);
    }

    void write_report(hstd::fs::path const& path) {
        writeFile(
            path,
            fmt(R"(- - - - - -
{}
- - - - - -
{}
{}
- - - - - -
{}
)",

                own_view(rune_chunks(str)) //
                    | rv::enumerate
                    | rv::transform(
                        [](Pair<int, std::string> const& l)
                            -> std::string {
                            return fmt(
                                "[{}] {}",
                                l.first,
                                escape_literal(l.second));
                        })
                    | rv::intersperse("\n") //
                    | rv::join              //
                    | rs::to<std::string>(),
                labels //
                    | rv::transform([](Label const& l) { return fmt1(l); })
                    | rv::intersperse("\n") //
                    | rv::join              //
                    | rs::to<std::string>(),
                report_text,
                report.config.char_set.uarrow == "^" ? pivoted : ""));
    }
};

TEST(PrintError, StringBuilder1) {
    StrCache sources;
    Id       id = 1;

    auto [labels, str] = labelList(
        {
            labelPair({}, "012\n"),
            labelPair({Label{}.with_message("MSG"_ss)}, "456"),
            labelPair({}, "\n890\n"),
        },
        id);

    EXPECT_EQ(str, "012\n456\n890\n");

    sources.add(id, str, "file");

    auto report = Report(ReportKind::Error, id, 12);

    for (auto const& label : labels) { report.with_label(label); }
    report.with_config(Config{} //
                           .with_char_set(Config::ascii())
                       // .with_debug_writes(true)
    );


    {
        SPtr<Source> src = sources.fetch(id);
        {
            auto line = src->get_offset_line(4);
            EXPECT_EQ(str.at(4), '4');
            EXPECT_TRUE(line.has_value());
            EXPECT_EQ(line.value().idx, 1);
        }

        {
            auto line = src->get_offset_line(6);
            EXPECT_EQ(str.at(6), '6');
            EXPECT_TRUE(line.has_value());
            EXPECT_EQ(line.value().idx, 1);
        }

        Vec<SourceGroup> groups = report.get_source_groups(&sources);
        EXPECT_EQ(groups.size(), 1);
        SourceGroup const& group = groups[0];
        EXPECT_EQ(group.labels.size(), 1);
        EXPECT_EQ(group.span.first, 4);
        EXPECT_EQ(group.span.last, 6);
        LabelInfo const& label = group.labels.at(0);
        EXPECT_EQ(label.kind, LabelKind::Inline);
        Vec<Label> multi_labels = Report::build_multi_labels(group.labels);
    }

    Str report_text = report.to_string(sources, false);
    Str pivoted     = pivotStringTable(report_text);

    writeFile(
        getDebugFile(fmt("error_{}.txt", "StringBuilder1")),
        fmt(R"(- - - - - -
{}
- - - - - -
{}
{}
- - - - - -
{}
)",

            own_view(rune_chunks(str)) //
                | rv::enumerate
                | rv::transform(
                    [](Pair<int, std::string> const& l) -> std::string {
                        return fmt(
                            "[{}] {}", l.first, escape_literal(l.second));
                    })
                | rv::intersperse("\n") //
                | rv::join              //
                | rs::to<std::string>(),
            labels //
                | rv::transform([](Label const& l) { return fmt1(l); })
                | rv::intersperse("\n") //
                | rv::join              //
                | rs::to<std::string>(),
            report_text,
            pivoted));

    EXPECT_TRUE(pivoted.contains("4^"));
    EXPECT_TRUE(pivoted.contains("5|"));
    EXPECT_TRUE(pivoted.contains("6^"));
    EXPECT_TRUE(report_text.contains("`-- MSG"));
    EXPECT_TRUE(report_text.contains("^|^"));
}

TEST(PrintError, StringBuilderSetup1) {
    auto                __scope = getDebugLogScope();
    PrintErrorTestSetup s{
        {
            labelPair({}, "012\n"),
            labelPair({Label{}.with_message("MSG"_ss)}, "456"),
            labelPair({}, "\n890\n"),
        },
        Config::ascii(),
    };

    s.build_report();

    // s.write_report(getDebugFile"error_StringBuilderSetup1.txt");

    EXPECT_TRUE(s.pivoted.contains("4^"));
    EXPECT_TRUE(s.pivoted.contains("5|"));
    EXPECT_TRUE(s.pivoted.contains("6^"));
    EXPECT_TRUE(s.report_text.contains("`-- MSG"));
    EXPECT_TRUE(s.report_text.contains("^|^"));
}

TEST(PrintError, StringBuilderSetup_MultiLabels) {
    auto                __scope = getDebugLogScope();
    PrintErrorTestSetup s{
        {
            labelPair({Label{}.with_message("MSG"_ss)}, "AA"),
            labelPair({}, " "),
            labelPair({Label{}.with_message("MSG"_ss)}, "AA"),
            labelPair({}, " "),
            labelPair({Label{}.with_message("MSG"_ss)}, "AA"),
            labelPair({}, "\n"),
        },
        Config::ascii(),
    };

    // s.report.config.with_debug_writes(true);
    s.build_report();

    s.write_report(getDebugFile("res.txt"));
    EXPECT_TRUE(s.report_text.contains(",^ ,^ ,^"));
    // overlapping arrows under the last 'A' group
    EXPECT_TRUE(s.pivoted.contains("A,-|-|"));
}

TEST(PrintError, StringBuilderSetup_MultiLabels_ManyLines) {
    auto                __scope = getDebugLogScope();
    PrintErrorTestSetup s{
        {
            labelPair({Label{}.with_message("MSG"_ss)}, "AA"),
            labelPair({}, " "),
            labelPair({Label{}.with_message("MSG"_ss)}, "AA"),
            labelPair({}, " "),
            labelPair({Label{}.with_message("MSG"_ss)}, "AA"),
            labelPair({}, "\n\n"),
            labelPair({Label{}.with_message("MSG"_ss)}, "BB"),
            labelPair({}, " "),
            labelPair({Label{}.with_message("MSG"_ss)}, "BB"),
            labelPair({}, " "),
            labelPair({Label{}.with_message("MSG"_ss)}, "BB"),
            labelPair({}, "\n"),
        },
        Config::ascii(),
    };

    // s.report.config.with_debug_writes(true);
    s.build_report();
    // s.write_report(getDebugFile"StringBuilderSetup_MultiLabels_ManyLines.txt");
    EXPECT_TRUE(s.pivoted.contains("A,-|-|` B,-|-|` "));
}


TEST(PrintError, RepoExample) {
    auto     __scope = getDebugLogScope();
    StrCache sources;
    Id       a_id = 1;

    sources.add(
        a_id,
        R"(def five = match () in {
    () => 5,
    () => "5",
}

def six =
    five
    + 1
)",
        "a_tao");

    auto a = ColStyle{}.red();
    auto b = ColStyle{}.green();
    auto report //
        = Report(ReportKind::Error, a_id, 12)
              // .with_config(Config{}.with_debug(true))
              .with_message("Incompatible types"_ss)
              .with_label(
                  Label{1}
                      .with_span(a_id, slice(30, 30))
                      .with_message(fmt("This is of type {}", "Nat"))
                      .with_color(a))
              .with_label(
                  Label{2}
                      .with_span(a_id, slice(42, 45))
                      .with_message(fmt("This is of type {}", "Str"))
                      .with_color(b))
              .with_label(
                  Label{3}
                      .with_span(a_id, slice(11, 48))
                      .with_message(fmt(
                          "The values are outputs of this {} expression",
                          "match")))
              .with_note(fmt(
                  "Outputs of {} expressions must coerce to the same type",
                  "match"));

    writeFile(getDebugFile("res.txt"), report.to_string(sources, false));
}

TEST(PrintError, MultilineAnnotations) {
    auto     __scope = getDebugLogScope();
    StrCache sources;
    Id       a_id = 1;

    sources.add(
        a_id,
        R"(def five = match () in {
    () => 5,
    () => "5",
}

def six =
    five
    + 1
)",
        "a_tao");

    auto a = ColStyle{}.red();
    auto b = ColStyle{}.green();
    auto report //
        = Report(ReportKind::Error, a_id, 12)
              .with_message(
                  "Multi-line note\nthat has four\nseparate lines\nto visualize"_ss)
              .with_label(
                  Label{1}
                      .with_span(a_id, slice(30, 30))
                      .with_message(fmt(
                          "Single line label on the base range", "Nat"))
                      .with_color(a))
              .with_label(
                  Label{2}
                      .with_span(a_id, slice(31, 31))
                      .with_message(fmt("Multiple line label\nwith at "
                                        "least\nthree separate lines"))
                      .with_color(b))
              .with_label(
                  Label{3}
                      .with_span(a_id, slice(32, 32))
                      .with_message(
                          fmt("Another multiline\nannotation "
                              "immediately\nfollowing the previous\none"))
                      .with_color(b))
              .with_note(fmt("Single line note"));

    writeFile(getDebugFile("res.txt"), report.to_string(sources, false));
}

TEST(PrintError, MultipleFiles) {
    auto        __scope = getDebugLogScope();
    std::string a_tao   = R"''(def five = 5)''";
    std::string b_tao   = R"''(def six = five + "1")''";

    ColText natColorized  = "Nat"_qs;
    ColText strColorized  = "Str"_qs;
    ColText fiveColorized = "5"_qs;

    Id a_id = 1;
    Id b_id = 2;

    ColStyle a;
    ColStyle b;
    ColStyle c;

    StrCache sources;
    sources.add(a_id, a_tao, "a_tao");
    sources.add(b_id, b_tao, "b_tao");

    auto report //
        = Report(ReportKind::Error, b_id, 10)
              .with_code("3")
              .with_message("Cannot add types Nat and Str"_qs)
              .with_label(
                  Label(1, CodeSpan(b_id, slice(10, 14)))
                      .with_message(
                          ColText("This is of type ") + natColorized)
                      .with_color(a))
              .with_label(
                  Label(2, CodeSpan(b_id, slice(17, 20)))
                      .with_message(
                          ColText("This is of typee ") + strColorized)
                      .with_color(b))
              .with_label(Label(3, CodeSpan(b_id, slice(15, 16)))
                              .with_message(
                                  natColorized + ColText(" and ")
                                  + strColorized
                                  + ColText(" undergo addition here"))
                              .with_color(c)
                              .with_order(10))
              .with_label(Label(4, CodeSpan(a_id, slice(4, 8)))
                              .with_message(
                                  ColText("Original definition of ")
                                  + fiveColorized + ColText(" is here"))
                              .with_color(a))
              .with_note(
                  natColorized
                  + ColText(" is a number and can only be added "
                            "to other numbers"))
              .with_note(ColText{"Multiline notes test\nsomething otherh "
                                 "whatever\nother things"});


    report.with_config(Config{}.with_debug_report_info(true));

    writeFile(getDebugFile("res.txt"), report.to_string(sources, false));
}

TEST(PrintError, MultipleAnnotations) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = R"(def fives = ["5", 5]

def sixes = ["6", 6, True, (), []]

def multiline :: Str = match Some 5 in {
    | Some x => x
    | None => 0

})";
    StrCache    sources;
    sources.add(id, code, "tao");
    std::stringstream os;
    int               label_counter = 0;

    auto label = [&](Slice<int>  range,
                     int         line     = __builtin_LINE(),
                     char const* function = __builtin_FUNCTION()) {
        return Label{++label_counter, CodeSpan(id, range)}.with_message(
            fmt("MSG {} {}", range, line));
    };

    auto report //
        = Report(ReportKind::Error, id, 13)
              .with_code("3")
              .with_message(("Incompatible types"_qs))
              .with_label(label(slice(0, 1)))
              .with_label(label(slice(1, 2)))
              .with_label(label(slice(2, 3)))
              .with_label(label(slice(3, 4)))
              .with_label(label(slice(4, 5)))
              .with_label(label(slice(5, 6)))
              .with_label(label(slice(6, 7)))
              .with_label(label(slice(7, 8)))
              .with_label(label(slice(8, 9)))
              .with_label(label(slice(9, 10)))
              .with_label(label(slice(10, 11)))
              .with_label(label(slice(11, 12)))
              .with_label(label(slice(12, 13)))
              .with_label(label(slice(13, 14)))
              .with_label(label(slice(14, 15)))
              .with_label(label(slice(15, 16)))
              .with_label(label(slice(16, 17)))
              .with_label(label(slice(17, 18)))
              .with_label(label(slice(18, 19)))
              .with_label(label(slice(19, 20)))
              .with_label(label(slice(20, 21)))
              .with_label(label(slice(18, 19)))
              .with_label(label(slice(13, 16)))
              .with_label(label(slice(40, 41)))
              .with_label(label(slice(43, 47)))
              .with_label(label(slice(49, 51)))
              .with_label(label(slice(53, 55)))
              .with_label(label(slice(25, 78)))
              .with_label(label(slice(81, 124)))
              .with_label(label(slice(100, 126)))
              .with_label(label(slice(106, 119)))
              .with_label(label(slice(108, 121)))
              .with_label(label(slice(110, 111)))
              .with_label(label(slice(111, 112)))
              .with_label(label(slice(103, 123)))
              .with_label(label(slice(105, 125)))
              .with_label(label(slice(112, 116)))
              .with_label(label(slice(26, 100)))
              .with_label(label(slice(85, 110)))
              .with_label(label(slice(84, 114)))
              .with_label(label(slice(89, 113)))
              .with_config(Config()
                               .with_cross_gap(false)
                               .with_compact(true)
                               .with_underlines(true)
                               .with_tab_width(4));

    writeFile(getDebugFile("res.txt"), report.to_string(sources, false));
}

TEST(PrintError, MultipleAnnotations2) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = R"(def fives = ["5", 5]

def sixes = ["6", 6, True, (), []]1

def multiline :: Str = match Some 5 in {
    # Some x => x
    # None => 0

})";
    StrCache    sources;
    sources.add(id, code, "tao");
    std::stringstream os;
    int               label_counter = 0;

    auto label = [&](Slice<int>  range,
                     int         line     = __builtin_LINE(),
                     char const* function = __builtin_FUNCTION()) {
        return Label{++label_counter, CodeSpan(id, range)}.with_message(
            fmt("MSG {} {}", range, line));
    };

    auto report //
        = Report(ReportKind::Error, id, 13)
              .with_code("3")
              .with_message(("Incompatible types"_qs))
              .with_label(label(slice(108, 124)))
              // .with_label(label(slice(105, 125)))
              // .with_label(label(slice(112, 116)))
              .with_config(Config()
                               .with_cross_gap(false)
                               .with_compact(true)
                               .with_underlines(true)
                               .with_tab_width(4));

    // report.config.with_debug_writes(true);

    writeFile(
        getDebugFile("res.txt"),
        fmt("{}\n{}..{}\n",
            report.to_string(sources, false),
            code.at(108),
            code.at(122)));
}

hstd::Str remove_trailing(hstd::Str const& in) {
    hstd::Str noLeadTail = hstd::strip(
        in, CharSet{'\n', ' '}, CharSet{'\n', ' '});
    return hstd::own_view(noLeadTail.split('\n'))
         | rv::transform([](hstd::Str const& str) -> hstd::Str {
               return hstd::strip(str, CharSet{}, CharSet{' '});
           })
         | hstd::rv_intersperse_newline_join;
}

TEST(PrintError, OneMessageWrite) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = R"()";
    StrCache    sources;
    sources.add(id, code, "tao");

    auto report //
        = Report(ReportKind::Error, id, 13)
              .with_message("can't compare apples with oranges"_qs)
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ(
        remove_trailing(report.to_string(sources, false)),
        "Error: can't compare apples with oranges"_ss);
}

template <typename T>
hstd::ColText __gtest_assert_eq_seq_fail_message(
    T const& lhs,
    T const& rhs) {
    return hstd::formatDiffed(
        lhs,
        rhs,
        FormattedDiff::Conf{
            .formatLine = FormattedDiff::getSequenceFormatterCb(
                &lhs, &rhs, true)});
}

template <typename T>
hstd::ColText __gtest_assert_eq_seq_format_text_compare(
    hstd::ColText const& diff,
    T const&             lhs,
    T const&             rhs) {
    hstd::ColStream os;
    os << diff;
    os << "\nGiven lhs:\n";
    os << hstd::Str("+").repeated(32) << "\n";
    os << lhs;
    os << "\n" << hstd::Str("+").repeated(32) << "\n";
    os << "\nExpected rhs:\n";
    os << hstd::Str("-").repeated(32) << "\n";
    os << rhs;
    os << "\n" << hstd::Str("-").repeated(32) << "\n";
    return os.getBuffer();
}

template <>
hstd::ColText __gtest_assert_eq_seq_fail_message<std::string>(
    std::string const& lhs,
    std::string const& rhs) {
    return __gtest_assert_eq_seq_format_text_compare(
        __gtest_assert_eq_seq_fail_message(
            hstd::split(lhs, '\n'), hstd::split(rhs, '\n')),
        lhs,
        rhs);
}

template <>
hstd::ColText __gtest_assert_eq_seq_fail_message<hstd::Str>(
    hstd::Str const& lhs,
    hstd::Str const& rhs) {
    return __gtest_assert_eq_seq_format_text_compare(
        __gtest_assert_eq_seq_fail_message(
            hstd::split(lhs, '\n'), hstd::split(rhs, '\n')),
        lhs,
        rhs);
}

template <>
hstd::ColText __gtest_assert_eq_seq_fail_message<hstd::ColText>(
    hstd::ColText const& lhs,
    hstd::ColText const& rhs) {
    return __gtest_assert_eq_seq_format_text_compare(
        __gtest_assert_eq_seq_fail_message(
            lhs.split('\n'), lhs.split('\n')),
        lhs,
        rhs);
}


#define GTEST_ASSERT_EQ_SEQ(__lhs_arg, __rhs_arg)                         \
    {                                                                     \
        auto const __lhs = __lhs_arg;                                     \
        auto const __rhs = __rhs_arg;                                     \
        if (!(__lhs == __rhs)) {                                          \
            FAIL() << __gtest_assert_eq_seq_fail_message(__lhs, __rhs)    \
                          .toString(false);                               \
        }                                                                 \
    }

TEST(PrintError, TwoLabelsWithoutMessageWrite) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = R"(apple == orange;)";
    StrCache    sources;
    sources.add(id, code, "tao");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare apples with oranges"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 4))
                              .with_message("This is an apple"_ss))
              .with_label(Label{2}
                              .with_span(id, slice(9, 14))
                              .with_message("This is an orange"_ss))
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare apples with oranges
   ,-[ tao:1:1 ]
   |
 1 | apple == orange;
   | ^^|^^    ^^|^^^
   |   `------------- This is an apple
   |            |
   |            `---- This is an orange
---'
)"_ss));
}


TEST(PrintError, TwoLabelsWithMessages) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = R"(apple == orange;)";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare apples with oranges"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 4))
                              .with_message("This is an apple"_ss))
              .with_label(Label{2}
                              .with_span(id, slice(9, 14))
                              .with_message("This is an orange"_ss))
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare apples with oranges
   ,-[ <unknown>:1:1 ]
   |
 1 | apple == orange;
   | ^^|^^    ^^|^^^
   |   `------------- This is an apple
   |            |
   |            `---- This is an orange
---'
)"_ss));
}

TEST(PrintError, MultiByteChars) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = R"(äpplë == örängë;)";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare äpplës with örängës"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 4))
                              .with_message("This is an äpplë"_ss))
              .with_label(Label{2}
                              .with_span(id, slice(9, 14))
                              .with_message("This is an örängë"_ss))
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare äpplës with örängës
   ,-[ <unknown>:1:1 ]
   |
 1 | äpplë == örängë;
   | ^^|^^    ^^|^^^
   |   `------------- This is an äpplë
   |            |
   |            `---- This is an örängë
---'
)"_ss));
}

TEST(PrintError, ByteLabel) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = R"(äpplë == örängë;)";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare äpplës with örängës"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 6))
                              .with_message("This is an äpplë"_ss))
              .with_label(Label{2}
                              .with_span(id, slice(9, 14))
                              .with_message("This is an örängë"_ss))
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare äpplës with örängës
   ,-[ <unknown>:1:1 ]
   |
 1 | äpplë == örängë;
   | ^^^|^^^  ^^|^^^
   |    `------------ This is an äpplë
   |            |
   |            `---- This is an örängë
---'
)"_ss));
}

TEST(PrintError, ByteColumn) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = R"(äpplë == örängë;)";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 11)
              .with_message("can't compare äpplës with örängës"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 6))
                              .with_message("This is an äpplë"_ss))
              .with_label(Label{2}
                              .with_span(id, slice(9, 14))
                              .with_message("This is an örängë"_ss))
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare äpplës with örängës
   ,-[ <unknown>:1:12 ]
   |
 1 | äpplë == örängë;
   | ^^^|^^^  ^^|^^^
   |    `------------ This is an äpplë
   |            |
   |            `---- This is an örängë
---'
)"_ss));
}

TEST(PrintError, LabelAtEndOfLongLine) {
    auto      __scope  = getDebugLogScope();
    Id        id       = 0;
    hstd::Str repeated = "";
    for (int i = 0; i < 100; ++i) { repeated += "apple == "; }
    hstd::Str code = repeated + "orange"_ss;
    StrCache  sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare apples with oranges"_qs)
              .with_label(
                  Label{1}
                      .with_span(
                          id, slice(code.size() - 5, code.size() - 1))
                      .with_message("This is an orange"_ss))
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare apples with oranges
   ,-[ <unknown>:1:1 ]
   |
 1 | apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == apple == orange
   |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      ^^|^^
   |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        `--- This is an orange
---'
)"_ss));
}

TEST(PrintError, LabelOfWidthZeroAtEndOfLine) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "apple ==\n";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("unexpected end of file"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(8, 9))
                              .with_message("Unexpected end of file"_ss))
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: unexpected end of file
   ,-[ <unknown>:1:1 ]
   |
 1 | apple ==
   |         ,^
   |         `-- Unexpected end of file
---'
)"_ss));
}

TEST(PrintError, EmptyInput) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("unexpected end of file"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 0))
                              .with_message("No more fruit!"_ss))
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: unexpected end of file
   ,-[ <unknown>:1:1 ]
   |
 1 |
   | |
   | `- No more fruit!
---'
)"_ss));
}

TEST(PrintError, EmptyInputHelp) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("unexpected end of file"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 0))
                              .with_message("No more fruit!"_ss))
              .with_help("have you tried going to the farmer's market?"_ss)
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: unexpected end of file
   ,-[ <unknown>:1:1 ]
   |
 1 |
   | |
   | `- No more fruit!
   |
   | Help: have you tried going to the farmer's market?
---'
)"_ss));
}


TEST(PrintError, EmptyInputNote) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("unexpected end of file"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 0))
                              .with_message("No more fruit!"_ss))
              .with_note("eat your greens!"_ss)
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: unexpected end of file
   ,-[ <unknown>:1:1 ]
   |
 1 |
   | |
   | `- No more fruit!
   |
   | Note: eat your greens!
---'
)"_ss));
}

TEST(PrintError, EmptyInputHelpNote) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("unexpected end of file"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 0))
                              .with_message("No more fruit!"_ss))
              .with_note("eat your greens!"_ss)
              .with_help("have you tried going to the farmer's market?"_ss)
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: unexpected end of file
   ,-[ <unknown>:1:1 ]
   |
 1 |
   | |
   | `- No more fruit!
   |
   | Help: have you tried going to the farmer's market?
   |
   | Note: eat your greens!
---'
)"_ss));
}

TEST(PrintError, MultilineLabel) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "apple\n==\norange";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_label(
                  Label{1}
                      .with_span(id, slice1<int>(0, code.size() - 1))
                      .with_message("illegal comparison"_ss))
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error:
   ,-[ <unknown>:1:1 ]
   |
 1 | ,-> apple
   : :
 3 | |-> orange
   | |
   | `----------- illegal comparison
---'
)"_ss));
}

TEST(PrintError, PartiallyOverlappingLabels) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "https://example.com/";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto colon_pos = code.find(':');
    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_label(
                  Label{1}
                      .with_span(id, slice1<int>(0, code.length() - 1))
                      .with_message("URL"_ss))
              .with_label(Label{2}
                              .with_span(id, slice1<int>(0, colon_pos - 1))
                              .with_message("scheme"_ss))
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error:
   ,-[ <unknown>:1:1 ]
   |
 1 | https://example.com/
   | ^^|^^^^^^|^^^^^^^^^^
   |   `------------------ scheme
   |          |
   |          `----------- URL
---'
)"_ss));
}

TEST(PrintError, MultipleLabelsSameSpan) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "apple == orange;";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare apples with oranges"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 4))
                              .with_message("This is an apple"_ss))
              .with_label(
                  Label{2}
                      .with_span(id, slice(0, 4))
                      .with_message(
                          "Have I mentioned that this is an apple?"_ss))
              .with_label(Label{3}
                              .with_span(id, slice(0, 4))
                              .with_message(
                                  "No really, have I mentioned that?"_ss))
              .with_label(Label{4}
                              .with_span(id, slice(9, 14))
                              .with_message("This is an orange"_ss))
              .with_label(
                  Label{5}
                      .with_span(id, slice(9, 14))
                      .with_message(
                          "Have I mentioned that this is an orange?"_ss))
              .with_label(Label{6}
                              .with_span(id, slice(9, 14))
                              .with_message(
                                  "No really, have I mentioned that?"_ss))
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare apples with oranges
   ,-[ <unknown>:1:1 ]
   |
 1 | apple == orange;
   | ^^|^^    ^^|^^^
   |   `------------- This is an apple
   |   |        |
   |   `------------- Have I mentioned that this is an apple?
   |   |        |
   |   `------------- No really, have I mentioned that?
   |            |
   |            `---- This is an orange
   |            |
   |            `---- Have I mentioned that this is an orange?
   |            |
   |            `---- No really, have I mentioned that?
---'
)"_ss));
}

TEST(PrintError, Note) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "apple == orange;";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare apples with oranges"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 4))
                              .with_message("This is an apple"_ss))
              .with_label(Label{2}
                              .with_span(id, slice(9, 14))
                              .with_message("This is an orange"_ss))
              .with_note("stop trying ... this is a fruitless endeavor"_ss)
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare apples with oranges
   ,-[ <unknown>:1:1 ]
   |
 1 | apple == orange;
   | ^^|^^    ^^|^^^
   |   `------------- This is an apple
   |            |
   |            `---- This is an orange
   |
   | Note: stop trying ... this is a fruitless endeavor
---'
)"_ss));
}

TEST(PrintError, Help) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "apple == orange;";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare apples with oranges"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 4))
                              .with_message("This is an apple"_ss))
              .with_label(Label{2}
                              .with_span(id, slice(9, 14))
                              .with_message("This is an orange"_ss))
              .with_help("have you tried peeling the orange?"_ss)
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare apples with oranges
   ,-[ <unknown>:1:1 ]
   |
 1 | apple == orange;
   | ^^|^^    ^^|^^^
   |   `------------- This is an apple
   |            |
   |            `---- This is an orange
   |
   | Help: have you tried peeling the orange?
---'
)"_ss));
}

TEST(PrintError, HelpAndNote) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "apple == orange;";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare apples with oranges"_qs)
              .with_label(Label{1}
                              .with_span(id, slice(0, 4))
                              .with_message("This is an apple"_ss))
              .with_label(Label{2}
                              .with_span(id, slice(9, 14))
                              .with_message("This is an orange"_ss))
              .with_help("have you tried peeling the orange?"_ss)
              .with_note("stop trying ... this is a fruitless endeavor"_ss)
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare apples with oranges
   ,-[ <unknown>:1:1 ]
   |
 1 | apple == orange;
   | ^^|^^    ^^|^^^
   |   `------------- This is an apple
   |            |
   |            `---- This is an orange
   |
   | Help: have you tried peeling the orange?
   |
   | Note: stop trying ... this is a fruitless endeavor
---'
)"_ss));
}

TEST(PrintError, SingleNoteSingleLine) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "apple == orange;";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare apples with oranges"_qs)
              .with_label(
                  Label{1}
                      .with_span(id, slice(0, 14))
                      .with_message("This is a strange comparison"_ss))
              .with_note("No need to try, they can't be compared."_ss)
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare apples with oranges
   ,-[ <unknown>:1:1 ]
   |
 1 | apple == orange;
   | ^^^^^^^|^^^^^^^
   |        `-------- This is a strange comparison
   |
   | Note: No need to try, they can't be compared.
---'
)"_ss));
}

TEST(PrintError, MultiNotesSingleLines) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "apple == orange;";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare apples with oranges"_qs)
              .with_label(
                  Label{1}
                      .with_span(id, slice(0, 14))
                      .with_message("This is a strange comparison"_ss))
              .with_note("No need to try, they can't be compared."_ss)
              .with_note("Yeah, really, please stop."_ss)
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare apples with oranges
   ,-[ <unknown>:1:1 ]
   |
 1 | apple == orange;
   | ^^^^^^^|^^^^^^^
   |        `-------- This is a strange comparison
   |
   | Note 1: No need to try, they can't be compared.
   |
   | Note 2: Yeah, really, please stop.
---'
)"_ss));
}

TEST(PrintError, MultiNotesMultiLines) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "apple == orange;";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare apples with oranges"_qs)
              .with_label(
                  Label{1}
                      .with_span(id, slice(0, 14))
                      .with_message("This is a strange comparison"_ss))
              .with_note("No need to try, they can't be compared."_ss)
              .with_note(
                  "Yeah, really, please stop.\nIt has no resemblance."_ss)
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare apples with oranges
   ,-[ <unknown>:1:1 ]
   |
 1 | apple == orange;
   | ^^^^^^^|^^^^^^^
   |        `-------- This is a strange comparison
   |
   | Note 1: No need to try, they can't be compared.
   |
   | Note 2: Yeah, really, please stop.
   |         It has no resemblance.
---'
)"_ss));
}

TEST(PrintError, MultiHelpsMultiLines) {
    auto        __scope = getDebugLogScope();
    Id          id      = 0;
    std::string code    = "apple == orange;";
    StrCache    sources;
    sources.add(id, code, "<unknown>");

    auto report //
        = Report(ReportKind::Error, id, 0)
              .with_message("can't compare apples with oranges"_qs)
              .with_label(
                  Label{1}
                      .with_span(id, slice(0, 14))
                      .with_message("This is a strange comparison"_ss))
              .with_help("No need to try, they can't be compared."_ss)
              .with_help(
                  "Yeah, really, please stop.\nIt has no resemblance."_ss)
              .with_config(Config().with_color(false).with_char_set(
                  Config::ascii()));

    GTEST_ASSERT_EQ_SEQ(
        remove_trailing(report.to_string(sources, false)),
        remove_trailing(R"(
Error: can't compare apples with oranges
   ,-[ <unknown>:1:1 ]
   |
 1 | apple == orange;
   | ^^^^^^^|^^^^^^^
   |        `-------- This is a strange comparison
   |
   | Help 1: No need to try, they can't be compared.
   |
   | Help 2: Yeah, really, please stop.
   |         It has no resemblance.
---'
)"_ss));
}
