import std.wrappers.textlayouter;
import hstd.stdlib.Str;
import hstd.stdlib.strutils;
import hstd.stdlib.Debug;
import hstd.stdlib.Ranges;
import hstd.stdlib.strformat;

#include <absl/log/log.h>

#include "../common.hpp"

using namespace layout;
using namespace testing;


/// \internal
//template <> // FIXME COMPILATION
//void internal::PrintTo(CR<Event> e, ::std::ostream* os) {
//    *os << to_string(e);
//}


using b = Block;
using S = layout::SimpleStringStore;
using B = layout::BlockStore;

layout::BlockId lytProc(
    B&                          b,
    S&                          s,
    const Vec<layout::BlockId>& args,
    layout::BlockId&            body) {
    Str             h    = "proc (";
    Str             t    = ") = ";
    layout::BlockId hsep = b.horizontal(args, s.text(", "));
    layout::BlockId vsep = b.vertical(args, s.text(", "));

    return b.choice({
        b.line({
            s.text(h),
            hsep,
            s.text(t),
            body,
        }),
        b.stack({
            b.line({s.text(h), hsep, s.text(t), b.indent(2, body)}),
        }),
        b.stack({
            s.text(h),
            b.indent(4, vsep),
            s.text(t),
            b.indent(2, body),
        }),
    });
}


TEST(TextLayouterTest, BasicFormattingOperations) {
    {
        B    b;
        S    s{&b};
        auto res = s.toString(s.text("S"));
        EXPECT_EQ(res, "S");
    }
    {
        B b;
        S s{&b};
        EXPECT_EQ(s.toString(b.indent(4, s.text("S"))), "    S");
    }
    {
        B b;
        S s{&b};
        EXPECT_EQ(s.toString(b.line({s.text("A"), s.text("B")})), "AB");
    }
    {
        B    b;
        S    s{&b};
        auto block = b.stack({s.text("A"), s.text("B")});
        Str  value = s.toString(block);
        EXPECT_EQ(value, "A\nB");
    }
    {
        B b;
        S s{&b};
        EXPECT_EQ(
            s.toString(b.indent(2, b.line({s.text("A"), s.text("B")}))),
            "  AB");
    }
    {
        B    b;
        S    s{&b};
        auto value = s.toString(
            b.indent(2, b.stack({s.text("A"), s.text("B")})));
        EXPECT_EQ(value, "  A\n  B");
    }
    {
        B   b;
        S   s{&b};
        Str expr = s.toString(b.line({
            b.stack({
                s.text("A"),
                s.text("B"),
            }),
            b.stack({
                s.text("C"),
                s.text("D"),
            }),
        }));

        EXPECT_EQ(expr, "A\nBC\n D");
    }

    {
        B b;
        S s{&b};
        EXPECT_EQ(
            s.toString(b.choice({
                s.text("123456"),
                s.text("123"),
            })),
            Str("123"));
    }

    {
        B b;
        S s{&b};
        EXPECT_EQ(
            s.toString(b.choice({
                b.stack({
                    s.text("123"),
                    s.text("456"),
                }),
                s.text("123456"),
            })),
            Str("123456"));
    }

    {
        B b;
        S s{&b};
        EXPECT_EQ(
            s.toString(
                b.choice({
                    b.stack({s.text("12"), s.text("34"), s.text("56")}),
                    s.text("132456"),
                }),
                Options{.linebreakCost = 1, .rightMargin = 2}),
            "12\n34\n56");
    }

    {
        B b;
        S s{&b};
        EXPECT_EQ(
            s.toString(
                b.wrap(
                    {
                        s.text("[###]"),
                        s.text("[###]"),
                    },
                    s.str("@+")),
                {.rightMargin = 2}),
            "[###]@+\n[###]");
    }
}

using namespace std::ranges;

// TEST(TextLayouterTest, ProcLayoutForWidth) {
//     Vec<Str> res;
//     for (const auto& args : Vec{1, 2}) {
//         for (const auto& body : Vec{20, 60}) {
//             layout::BlockId block = lytProc(
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
    auto wrapArgs = [](B& b, S& s) {
        return b.wrap(
            {
                s.text("argument1"),
                s.text("argument2"),
                s.text("argument3"),
                s.text("argument4"),
                s.text("argument5"),
                s.text("argument6"),
                s.text("argument7"),
                s.text("argument8"),
                s.text("argument9"),
                s.text("argument10"),
            },
            s.str(", "));
    };

    {
        B    b;
        S    s{&b};
        auto id  = b.line({
            b.line({s.text("FnName"), s.text("(")}),
            wrapArgs(b, s),
            s.text(")"),
        });
        Str  res = s.toString(id, {.rightMargin = 60});

        Str val
            = "FnName(argument1, argument2, argument3, argument4,\n"
              "       argument5, argument6, argument7, argument8,\n"
              "       argument9, argument10)";

        EXPECT_EQ(res, val);
    }

    {
        B   b;
        S   s{&b};
        Str res = s.toString(
            b.line({
                b.line({s.text("FnName"), s.text("(")}),
                wrapArgs(b, s),
                s.text(")"),
            }),
            {.rightMargin = 30});

        Str val
            = "FnName(argument1, argument2,\n"
              "       argument3, argument4,\n"
              "       argument5, argument6,\n"
              "       argument7, argument8,\n"
              "       argument9, argument10)";

        EXPECT_EQ(res, val);
    }

    {
        B   b;
        S   s{&b};
        Str res = s.toString(
            b.choice({
                b.line({
                    b.line({
                        s.text("AVeryLongAndDescriptiveFunctionName"),
                        s.text("("),
                    }),
                    b.indent(4, wrapArgs(b, s)),
                    s.text(")"),
                }),
                b.stack({
                    b.line({
                        s.text("AVeryLongAndDescriptiveFunctionName"),
                        s.text("("),
                    }),
                    b.indent(4, wrapArgs(b, s)),
                    s.text(")"),
                }),
            }),
            {.rightMargin = 50});

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
        B    b;
        S    s{&b};
        auto bl = s.toString(b.line({
            s.text("stmtPragmas* = "),
            b.line({
                s.text("{ "),
                b.stack({
                    s.text("wChecks"),
                    s.text("wOverflowChecks"),
                    s.text("wNilChecks"),
                }),
                s.text(" }"),
            }),
        }));

        EXPECT_EQ(
            bl,
            "stmtPragmas* = { wChecks\n"
            "                 wOverflowChecks\n"
            "                 wNilChecks }");
    }
}
