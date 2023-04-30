#include <hstd/wrappers/textlayouter.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/Debug.hpp>

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

Str toString(Options& o, Block::Ptr b) { return toString(o, b); }

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
                Event(Event::Newline()),
            }))
            << to_string(formatting);

        Str value = toString(block);
        EXPECT_EQ(value, "A\nB\n");
    }
    EXPECT_EQ(
        toString(b::indent(2, b::line({text("A"), text("B")}))), "  AB");
    {
        auto value = toString(
            b::indent(2, b::stack({text("A"), text("B")})));
        EXPECT_EQ(value, "  A\n  B\n");
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

        EXPECT_EQ(expr, "A\nBC\n D\n");
    }
}
