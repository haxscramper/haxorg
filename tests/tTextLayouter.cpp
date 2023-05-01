#include <hstd/wrappers/textlayouter.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/strformat.hpp>

#include <QDebug>

std::ostream& operator<<(std::ostream& os, CR<Str> s) {
    return os << to_string(s);
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>


using namespace layout;
using namespace testing;

// FIXME despite documentation claim that 'PrintTo' must only be defined
// in the same namespace as the type (`Str`) I had to explicitly specialize
// the internal template for this to work. It does not seem like a big
// issue but https://github.com/google/googletest/blob/main/docs/advanced.md#teaching-googletest-how-to-print-your-values
// this still needs to be investigated.
/// \internal
template <>
void internal::PrintTo(const Str& str, ::std::ostream* os) {
    std::ostringstream escaped_str;
    for (QChar c : str) {
        if (c == '\n') {
            *os << "\\n";
        } else if (c == '\t') {
            *os << "\\t";
        } else {
            *os << QString(c).toStdString();
        }
    }
}

/// \internal
template <>
void internal::PrintTo(CR<Event> e, ::std::ostream* os) {
    *os << to_string(e);
}


struct StrStore {
    Vec<Str> strings;
};

LytStr str(StrStore& store, const Str& str) {
    LytStr result(store.strings.size(), str.length());
    store.strings.push_back(str);
    return result;
}

Str str(const StrStore& s, const LytStr& str) {
    if (str.isSpaces()) {
        return Str(" ").repeated(str.len);
    } else {
        return s.strings[str.toIndex()];
    }
}

Str toString(StrStore& s, Options const& opts, Block::Ptr& blc) {
    Layout::Ptr lyt = blc->toLayout(opts);
    Str         result;
    for (const auto& event : formatEvents(lyt)) {
        switch (event.getKind()) {
            case Event::Kind::Newline: {
                result += "\n";
                break;
            }

            case Event::Kind::Spaces: {
                result += std::string(event.getSpaces().spaces, ' ');
                break;
            }

            case Event::Kind::Text: {
                result += str(s, event.getText().str);
                break;
            }
        }
    }

    Vec<Str> fin;
    for (const auto& line : result.split("\n")) {
        fin.push_back(strip(line, CharSet{}, CharSet{QChar(' ')}));
    }
    return join("\n", fin);
}

Vec<Event> toEvents(Block::Ptr blc, Options const& opts = Options{}) {
    Layout::Ptr lyt = blc->toLayout(opts);
    Vec<Event>  res;
    for (const auto& event : formatEvents(lyt)) {
        res.push_back(event);
    }
    return res;
}

StrStore s;

Str toString(Block::Ptr b, int width = 80) {
    return toString(s, Options{.rightMargin = width}, b);
}

Str toString(Block::Ptr b, Options const& o) { return toString(s, o, b); }

Layout::Ptr toLyt(Block::Ptr& b) { return b->toLayout(Options{}); }

using b = Block;

LytStr     str(const Str& arg) { return str(s, arg); }
Block::Ptr text(const Str& arg) { return b::text(str(s, arg)); }


Block::Ptr lytProc(const Vec<Block::Ptr>& args, Block::Ptr& body) {
    Str        h    = "proc (";
    Str        t    = ") = ";
    Block::Ptr hsep = b::horizontal(args, text(", "));
    Block::Ptr vsep = b::vertical(args, text(", "));

    return b::choice({
        b::line({
            text(h),
            hsep,
            text(t),
            body,
        }),
        b::stack({
            b::line({text(h), hsep, text(t), b::indent(2, body)}),
        }),
        b::stack({
            text(h),
            b::indent(4, vsep),
            text(t),
            b::indent(2, body),
        }),
    });
}

TEST(TextLayouterTest, BasicFormattingOperations) {
    {
        auto res = toString(text("S"));
        EXPECT_EQ(res, "S");
    }
    EXPECT_EQ(toString(b::indent(4, text("S"))), "    S");
    EXPECT_EQ(toString(b::line({text("A"), text("B")})), "AB");
    {
        LytStr A = str("A");
        LytStr B = str("B");

        auto       block      = b::stack({b::text(A), b::text(B)});
        Vec<Event> formatting = toEvents(block);
        EXPECT_THAT(
            formatting,
            ElementsAreArray({
                Event(Event::Text{A}),
                Event(Event::Newline()),
                Event(Event::Text{B}),
            }));

        Str value = toString(block);
        EXPECT_EQ(value, "A\nB");
    }
    EXPECT_EQ(
        toString(b::indent(2, b::line({text("A"), text("B")}))), "  AB");
    {
        auto value = toString(
            b::indent(2, b::stack({text("A"), text("B")})));
        EXPECT_EQ(value, "  A\n  B");
    }
    {
        Str expr = toString(b::line({
            b::stack({
                text("A"),
                text("B"),
            }),
            b::stack({
                text("C"),
                text("D"),
            }),
        }));

        EXPECT_EQ(expr, "A\nBC\n D");
    }

    EXPECT_EQ(
        toString(b::choice({
            text("123456"),
            text("123"),
        })),
        Str("123"));

    EXPECT_EQ(
        toString(b::choice({
            b::stack({
                text("123"),
                text("456"),
            }),
            text("123456"),
        })),
        Str("123456"));

    EXPECT_EQ(
        toString(
            b::choice({
                b::stack({text("12"), text("34"), text("56")}),
                text("132456"),
            }),
            Options{.linebreakCost = 1, .rightMargin = 2}),
        "12\n34\n56");

    EXPECT_EQ(
        toString(
            b::wrap(
                {
                    text("[###]"),
                    text("[###]"),
                },
                str("@+")),
            {.rightMargin = 2}),
        "[###]@+\n[###]");
}

using namespace std::ranges;

// TEST(TextLayouterTest, ProcLayoutForWidth) {
//     Vec<Str> res;
//     for (const auto& args : Vec{1, 2}) {
//         for (const auto& body : Vec{20, 60}) {
//             Block::Ptr block = lytProc(
//                 rs::iota_view(0, args - 1)
//                     | rv::transform([](int i) -> Str {
//                          return "arg$#: arg$#_type" % to_string_vec(i, i);
//                      }),
//                text(Str("?").repeated(body)));

//            res.push_back(toString(block));
//        }
//    }

//    EXPECT_EQ(res[0], "proc (arg0: arg0_type) = ????????????????????");
//    EXPECT_EQ(res[1], R"(
// proc (
//    arg0: arg0_type
//) =
//  ????????????????????????????????????????????????????????????)");

//    EXPECT_EQ(res[2], R"(
// proc (arg0: arg0_type, arg1: arg1_type) = ????????????????????)");

//    EXPECT_EQ(res[3], R"(
// proc (
//    arg0: arg0_type,
//    arg1: arg1_type
//) =
//  ????????????????????????????????????????????????????????????)");
//}

TEST(TextLayouterTest, FnNameWithWrap) {
    auto wrapArgs = []() {
        return b::wrap(
            {
                text("argument1"),
                text("argument2"),
                text("argument3"),
                text("argument4"),
                text("argument5"),
                text("argument6"),
                text("argument7"),
                text("argument8"),
                text("argument9"),
                text("argument10"),
            },
            str(", "));
    };
    {
        Str res = toString(
            b::line({
                b::line({text("FnName"), text("(")}),
                wrapArgs(),
                text(")"),
            }),
            60);

        Str val
            = "FnName(argument1, argument2, argument3, argument4,\n"
              "       argument5, argument6, argument7, argument8,\n"
              "       argument9, argument10)";

        EXPECT_EQ(res, val);
    }

    {
        Str res = toString(
            b::line({
                b::line({text("FnName"), text("(")}),
                wrapArgs(),
                text(")"),
            }),
            30);

        Str val
            = "FnName(argument1, argument2,\n"
              "       argument3, argument4,\n"
              "       argument5, argument6,\n"
              "       argument7, argument8,\n"
              "       argument9, argument10)";

        EXPECT_EQ(res, val);
    }

    {
        Str res = toString(
            b::choice({
                b::line({
                    b::line({
                        text("AVeryLongAndDescriptiveFunctionName"),
                        text("("),
                    }),
                    b::indent(4, wrapArgs()),
                    text(")"),
                }),
                b::stack({
                    b::line({
                        text("AVeryLongAndDescriptiveFunctionName"),
                        text("("),
                    }),
                    b::indent(4, wrapArgs()),
                    text(")"),
                }),
            }),
            50);

        EXPECT_EQ(
            res,
            "AVeryLongAndDescriptiveFunctionName(\n"
            "    argument1, argument2, argument3, argument4,\n"
            "    argument5, argument6, argument7, argument8,\n"
            "    argument9, argument10\n"
            ")");
    }
}

TEST(TextLayouterTest, CodeLayout) {
    {
        auto bl = toString(b::line({
            text("stmtPragmas* = "),
            b::line({
                text("{ "),
                b::stack({
                    text("wChecks"),
                    text("wOverflowChecks"),
                    text("wNilChecks"),
                }),
                text(" }"),
            }),
        }));

        EXPECT_EQ(
            bl,
            "stmtPragmas* = { wChecks\n"
            "                 wOverflowChecks\n"
            "                 wNilChecks }");
    }
}
