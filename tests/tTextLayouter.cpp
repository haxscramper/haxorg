#include <hstd/wrappers/textlayouter.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/strutils.hpp>

using namespace layout;

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

    Str final;
    for (const auto& line : result.split("\n")) {
        strip(line, CharSet{}, CharSet{QChar(' ')});
    }
    return final;
}

StrStore s;

Str toString(Block::Ptr& b, int width = 80) {
    return toString(s, Options{.rightMargin = width}, b);
}

Str toString(Options& o, Block::Ptr& b) { return toString(o, b); }

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
