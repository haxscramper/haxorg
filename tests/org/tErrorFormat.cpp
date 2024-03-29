#include <sem/ErrorWrite.hpp>
#include <gtest/gtest.h>

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

    std::stringstream os;
    Report(ReportKind::Error, b_id, 10)
        .with_code("3")
        .with_message("Cannot add types Nat and Str"_qs)
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(b_id, slice(10, 14)))
                .with_message(ColText("This is of type ") + natColorized)
                .with_color(a))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(b_id, slice(17, 20)))
                .with_message(ColText("This is of typee ") + strColorized)
                .with_color(b))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(b_id, slice(15, 16)))
                .with_message(
                    natColorized + ColText(" and ") + strColorized
                    + ColText(" undergo addition here"))
                .with_color(c)
                .with_order(10))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(a_id, slice(4, 8)))
                .with_message(
                    ColText("Original definition of ") + fiveColorized
                    + ColText(" is here"))
                .with_color(a))
        .with_note(
            natColorized
            + ColText(
                " is a number and can only be added to other numbers"))
        .write(sources, os);
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
    Report(ReportKind::Error, id, 13)
        .with_code("3")
        .with_message(("Incompatible types"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(0, 1 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(1, 2 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(2, 3 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(3, 4 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(4, 5 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(5, 6 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(6, 7 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(7, 8 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(8, 9 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(9, 10 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(10, 11 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(11, 12 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(12, 13 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(13, 14 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(14, 15 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(15, 16 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(16, 17 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(17, 18 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(18, 19 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(19, 20 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(20, 21 + 1)))
                .with_message("Color"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(18, 19 + 1)))
                .with_message("This is of type Nat"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(13, 16 + 1)))
                .with_message("This is of type Str"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(40, 41 + 1)))
                .with_message("This is of type Nat"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(43, 47 + 1)))
                .with_message("This is of type Bool"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(49, 51 + 1)))
                .with_message("This is of type ()"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(53, 55 + 1)))
                .with_message("This is of type [_]"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(25, 78 + 1)))
                .with_message("This is of type Str"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(81, 124 + 1)))
                .with_message("This is of type Nat"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(100, 126 + 1)))
                .with_message("This is an inner multi-line"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(106, 120 + 1)))
                .with_message("This is another inner multi-line"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(108, 122 + 1)))
                .with_message("This is *really* nested multi-line"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(110, 111 + 1)))
                .with_message(
                    "This is an inline within the ne  b   bsting!"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(111, 112 + 1)))
                .with_message("And another!"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(103, 123 + 1)))
                .with_message("This is *really* nested multi-line"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(105, 125 + 1)))
                .with_message("This is *really* nested multi-line"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(112, 116 + 1)))
                .with_message("This is *really* nested multi-line"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(26, 100 + 1)))
                .with_message("Hahaha!"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(85, 110 + 1)))
                .with_message("Oh god, no more 1"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(84, 114 + 1)))
                .with_message("Oh god, no more 2"_qs))
        .with_label(
            Label(std::make_shared<TupleCodeSpan>(id, slice(89, 113 + 1)))
                .with_message("Oh god, no more 3"_qs))
        .with_config(Config()
                         .with_cross_gap(false)
                         .with_compact(true)
                         .with_underlines(true)
                         .with_tab_width(4))
        //.write(sources, os)
        ;
}
