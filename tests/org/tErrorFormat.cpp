#include <sem/ErrorWrite.hpp>
#include <gtest/gtest.h>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Ranges.hpp>

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
              .with_label(Label{}
                              .with_span(a_id, slice(0, 1))
                              .with_color(ColStyle{}.red()))
              .with_label(Label{}
                              .with_span(a_id, slice(2, 3))
                              .with_color(ColStyle{}.red())
                              .with_message("`b` for banana"_ss)
                              .with_order(1))
              .with_label(Label{}
                              .with_span(a_id, slice(4, 5))
                              .with_color(ColStyle{}.green()))
              .with_label(Label{}
                              .with_span(a_id, slice(7, 9))
                              .with_color(ColStyle{}.cyan())
                              .with_message("`e` for emerald"_ss))
              .with_note(
                  "Outputs of {} expressions must coerce to the same type"_ss);


    writeFile("/tmp/error_Simple.txt", report.to_string(sources, false));
}

Pair<Vec<Label>, Str> labelPair(Vec<Label> const& it, Str const& it2) {
    return {it, it2};
}

Pair<Vec<Label>, Str> labelList(
    Vec<Pair<Vec<Label>, Str>> const& text,
    Id                                source) {
    Str        str;
    Vec<Label> labels;

    for (auto const& [in_labels, in_str] : text) {
        int first = str.size();
        str += in_str;
        int last = str.size() - 1;
        for (auto const& label : in_labels) {
            labels.push_back(
                label.clone().with_span(source, slice(first, last)));
        }
    }

    return {labels, str};
}

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

    sources.add(id, str, "file");

    auto report = Report(ReportKind::Error, id, 12);

    for (auto const& label : labels) { report.with_label(label); }
    // report.with_config(Config{}.with_debug_writes(true));

    {
        Vec<SourceGroup> groups = report.get_source_groups(&sources);
        EXPECT_EQ(groups.size(), 1);
        SourceGroup const& group = groups[0];
        EXPECT_EQ(group.labels.size(), 1);
        EXPECT_EQ(group.span.first, 4);
        EXPECT_EQ(group.span.last, 6);
        LabelInfo const& label  = group.labels.at(0);
        Vec<Label> multi_labels = Report::build_multi_labels(group.labels);
    }

    writeFile(
        fmt("/tmp/error_{}.txt", "StringBuilder1"),
        fmt(R"(- - - - - -
{}
- - - - - -
{}
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
            report.to_string(sources, false)));
}

TEST(PrintError, RepoExample) {
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
                  Label{}
                      .with_span(a_id, slice(30, 30))
                      .with_message(fmt("This is of type {}", "Nat"))
                      .with_color(a))
              .with_label(
                  Label{}
                      .with_span(a_id, slice(42, 45))
                      .with_message(fmt("This is of type {}", "Str"))
                      .with_color(b))
              .with_label(
                  Label{}
                      .with_span(a_id, slice(11, 48))
                      .with_message(fmt(
                          "The values are outputs of this {} expression",
                          "match")))
              .with_note(fmt(
                  "Outputs of {} expressions must coerce to the same type",
                  "match"));

    writeFile(
        "/tmp/error_RepoExample.txt", report.to_string(sources, false));
}

TEST(PrintError, MultipleFiles) {
    std::string a_tao = R"''(def five = 5)''";
    std::string b_tao = R"''(def six = five + "1")''";

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
                  Label(CodeSpan(b_id, slice(10, 14)))
                      .with_message(
                          ColText("This is of type ") + natColorized)
                      .with_color(a))
              .with_label(
                  Label(CodeSpan(b_id, slice(17, 20)))
                      .with_message(
                          ColText("This is of typee ") + strColorized)
                      .with_color(b))
              .with_label(Label(CodeSpan(b_id, slice(15, 16)))
                              .with_message(
                                  natColorized + ColText(" and ")
                                  + strColorized
                                  + ColText(" undergo addition here"))
                              .with_color(c)
                              .with_order(10))
              .with_label(Label(CodeSpan(a_id, slice(4, 8)))
                              .with_message(
                                  ColText("Original definition of ")
                                  + fiveColorized + ColText(" is here"))
                              .with_color(a))
              .with_note(
                  natColorized
                  + ColText(" is a number and can only be added "
                            "to other numbers"));


    writeFile(
        "/tmp/error_MultipleFiles.txt", report.to_string(sources, false));
}

TEST(PrintError, MultipleAnnotations) {
    Id          id   = 0;
    std::string code = R"(def fives = ["5", 5]

def sixes = ["6", 6, True, (), []]

def multiline :: Str = match Some 5 in {
    | Some x => x
    | None => 0

})";
    StrCache    sources;
    sources.add(id, code, "tao");
    std::stringstream os;

    auto report //
        = Report(ReportKind::Error, id, 13)
              .with_code("3")
              .with_message(("Incompatible types"_qs))
              .with_label(Label(CodeSpan(id, slice(0, 1 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(1, 2 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(2, 3 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(3, 4 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(4, 5 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(5, 6 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(6, 7 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(7, 8 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(8, 9 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(9, 10 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(10, 11 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(11, 12 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(12, 13 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(13, 14 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(14, 15 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(15, 16 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(16, 17 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(17, 18 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(18, 19 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(19, 20 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(20, 21 + 1)))
                              .with_message("Color"_qs))
              .with_label(Label(CodeSpan(id, slice(18, 19 + 1)))
                              .with_message("This is of type Nat"_qs))
              .with_label(Label(CodeSpan(id, slice(13, 16 + 1)))
                              .with_message("This is of type Str"_qs))
              .with_label(Label(CodeSpan(id, slice(40, 41 + 1)))
                              .with_message("This is of type Nat"_qs))
              .with_label(Label(CodeSpan(id, slice(43, 47 + 1)))
                              .with_message("This is of type Bool"_qs))
              .with_label(Label(CodeSpan(id, slice(49, 51 + 1)))
                              .with_message("This is of type ()"_qs))
              .with_label(Label(CodeSpan(id, slice(53, 55 + 1)))
                              .with_message("This is of type [_]"_qs))
              .with_label(Label(CodeSpan(id, slice(25, 78 + 1)))
                              .with_message("This is of type Str"_qs))
              .with_label(Label(CodeSpan(id, slice(81, 124 + 1)))
                              .with_message("This is of type Nat"_qs))
              .with_label(
                  Label(CodeSpan(id, slice(100, 126 + 1)))
                      .with_message("This is an inner multi-line"_qs))
              .with_label(
                  Label(CodeSpan(id, slice(106, 120 + 1)))
                      .with_message("This is another inner multi-line"_qs))
              .with_label(Label(CodeSpan(id, slice(108, 122 + 1)))
                              .with_message(
                                  "This is *really* nested multi-line"_qs))
              .with_label(
                  Label(CodeSpan(id, slice(110, 111 + 1)))
                      .with_message(
                          "This is an inline within the ne  b   bsting!"_qs))
              .with_label(Label(CodeSpan(id, slice(111, 112 + 1)))
                              .with_message("And another!"_qs))
              .with_label(Label(CodeSpan(id, slice(103, 123 + 1)))
                              .with_message(
                                  "This is *really* nested multi-line"_qs))
              .with_label(Label(CodeSpan(id, slice(105, 125 + 1)))
                              .with_message(
                                  "This is *really* nested multi-line"_qs))
              .with_label(Label(CodeSpan(id, slice(112, 116 + 1)))
                              .with_message(
                                  "This is *really* nested multi-line"_qs))
              .with_label(Label(CodeSpan(id, slice(26, 100 + 1)))
                              .with_message("Hahaha!"_qs))
              .with_label(Label(CodeSpan(id, slice(85, 110 + 1)))
                              .with_message("Oh god, no more 1"_qs))
              .with_label(Label(CodeSpan(id, slice(84, 114 + 1)))
                              .with_message("Oh god, no more 2"_qs))
              .with_label(Label(CodeSpan(id, slice(89, 113 + 1)))
                              .with_message("Oh god, no more 3"_qs))
              .with_config(Config()
                               .with_cross_gap(false)
                               .with_compact(true)
                               .with_underlines(true)
                               .with_tab_width(4));

    writeFile(
        "/tmp/error_MultipleAnnotations.txt",
        report.to_string(sources, false));
}
