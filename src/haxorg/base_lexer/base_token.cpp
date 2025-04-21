#include "base_token.hpp"
#include <haxorg/lexbase/TraceStructured.hpp>
#include <cctype>

#pragma clang diagnostic error "-Wswitch"

using namespace hstd;
using namespace org::parse;
using namespace org::report;

struct Cursor {
    char current() const {
        if (pos < text.size()) {
            return text[pos];
        } else {
            return '\0';
        }
    }

    char get(int offset = 0) const {
        LOGIC_ASSERTION_CHECK(has_pos(offset), "{}", format());
        return text[pos + offset];
    }

    bool has_pos(int offset) const { return pos + offset < text.size(); }
    bool has_text() const { return has_pos(0); }

    bool can_search(char c, int offset = 0) const {
        return has_pos(offset) && !is_at(c, offset);
    }

    bool is_at(char ch, int offset = 0) const {
        return has_pos(offset) && get(offset) == ch;
    }

    bool is_at(std::string const& text, int offset = 0) const {
        for (int i = 0; i < text.size(); ++i) {
            if (get(i + offset) != text.at(i)) { return false; }
        }

        return true;
    }

    std::optional<char> peek(int offset = 1) const {
        if (pos + offset < text.size()) {
            return text[pos + offset];
        } else {
            return std::nullopt;
        }
    }

    bool next() {
        if (text.size() <= pos) {
            return false;
        } else if (current() == '\n') {
            line++;
            col = 1;
        } else {
            col++;
        }

        pos++;
        return pos < text.size();
    }

    bool next(int count) {
        for (int i = 0; i < count; i++) {
            if (!next()) { return false; }
        }
        return true;
    }

    bool nextUnicode() {
        if (pos >= text.size()) { return false; }

        if (current() == '\n') {
            line++;
            col = 1;
            pos++;
            return pos < text.size();
        }

        unsigned char firstByte = static_cast<unsigned char>(text[pos]);
        size_t        charSize  = 1;

        if (firstByte >= 0xF0) {
            charSize = 4;
        } else if (firstByte >= 0xE0) {
            charSize = 3;
        } else if (firstByte >= 0xC0) {
            charSize = 2;
        }

        col++;
        pos += charSize;
        pos = std::min<int>(pos, text.size());

        return pos < text.size();
    }

    template <typename Func>
    std::string_view readWhile(Func const& predicate) {
        int start = pos;
        while (pos < text.size() && predicate(text[pos])) { next(); }
        return text.substr(start, pos - start);
    }

    template <typename Func>
    std::string_view readUntil(Func const& predicate) {
        return readWhile([&predicate](char c) { return !predicate(c); });
    }

    bool eof() const { return text.size() <= pos; }

    int position() const { return pos; }
    int getLine() const { return line; }
    int getColumn() const { return col; }

    void reset() {
        pos  = 0;
        line = 1;
        col  = 1;
    }

    LexerParams      p;
    OrgTokenGroup*   group;
    std::string_view text;
    int              pos  = 0;
    int              line = 0;
    int              col  = 0;

    std::string format() const {
        int end = std::min<int>(20, text.size() - pos);
        return std::format(
            "col:{} line:{} pos:{}/{} text:{}",
            col,
            line,
            pos,
            text.size(),
            pos < text.size() ? escape_literal(text.substr(pos, end))
                              : "<eol>");
    }

    void range_token(
        OrgTokenKind kind,
        int          start,
        int          end,
        int          line     = __builtin_LINE(),
        char const*  function = __builtin_FUNCTION()) {
        OrgToken tok;
        tok->col  = col;
        tok->line = line;
        tok.kind  = kind;

        tok.value.text = std::string{
            text.begin() + start,
            text.begin() + end,
        };

        token(tok, line, function);
    }

    void token(
        OrgToken const& tok,
        int             line     = __builtin_LINE(),
        char const*     function = __builtin_FUNCTION()) {
        if (p.TraceState) { p.message(fmt1(tok), function, line); }
        group->add(tok);
    }

    template <typename Func, typename... Args>
    void token_cb(
        OrgTokenKind kind,
        int          line,
        char const*  function,
        Func const&  adv,
        Args&&... args) {
        int start = pos;
        adv(*this, args...);
        int end = pos;
        range_token(kind, start, end, line, function);
    }

    template <typename Func, typename Arg1>
    void token1(
        OrgTokenKind kind,
        Func const&  cb,
        Arg1 const&  arg,
        int          line     = __builtin_LINE(),
        char const*  function = __builtin_FUNCTION()) {
        token_cb(kind, line, function, cb, arg);
    }

    template <typename Func>
    void token0(
        OrgTokenKind kind,
        Func const&  cb,
        int          line     = __builtin_LINE(),
        char const*  function = __builtin_FUNCTION()) {
        token_cb(kind, line, function, cb);
    }

    OrgToken pop_token() { return group->tokens.content.pop_back_v(); }

    hstd::finally_std advance_guard(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        int start_pos = this->pos;

        std::string function_{function};
        int         line_{line};

        return finally_std{[this, start_pos, function_, line_]() {
            if (start_pos == this->pos) {
                if (p.TraceState) {
                    p.message(
                        fmt("No movement around pos {}: {}",
                            start_pos,
                            this->format()));
                }
            }

            LOGIC_ASSERTION_CHECK(
                start_pos != this->pos,
                "No movement around pos {}: {}, advance guard failed at "
                "{}:{}",
                start_pos,
                this->format(),
                function_,
                line_);
        }};
    }
};

using otk = OrgTokenKind;

void advance_count(Cursor& c, int count) {
    for (int i = 0; i < count; ++i) { c.next(); }
}

void advance1(Cursor& c) { c.next(); }

void advance_alnum(Cursor& c) {
    while (c.has_text() && std::isalnum(c.get())) { c.next(); }
}

void advance_ident(Cursor& c) {
    while (c.has_text() && (std::isalnum(c.get()) || c.get() == '_')) {
        c.next();
    }
}

void advance_char1(Cursor& c, char ch) {
    while (c.has_text() && c.get() == ch) { c.next(); }
}

void advace_charset(Cursor& c, CharSet const& set) {
    while (c.has_text() && set.contains(c.get())) { c.next(); }
}

#define MSG(__text)                                                       \
    if (c.p.TraceState) { c.p.message(__text); }

namespace {

void switch_cmd_argument(Cursor& c) {}

void switch_command(Cursor& c) {
    auto __scope = c.p.scopeLevel();
    c.token1(otk::LineCommand, &advance_count, 2);
    c.token0(otk::Word, [](Cursor& c) {
        advance_ident(c);
        if (c.is_at(':')) { c.next(); }
        advance_char1(c, ' ');
    });
    auto head      = c.pop_token();
    auto norm_head = normalize(head->text);

    auto head_raw = [&]() {
        c.token(head);
        c.token0(otk::RawText, [](Cursor& c) {
            while (c.can_search('\n')) { c.next(); }
        });
    };

    auto head_args = [&]() {
        c.token(head);
        while (c.has_text() && !c.is_at('\n')) {
            auto __guard = c.advance_guard();
            switch_cmd_argument(c);
        }
    };

    if (norm_head == "columns") {
        head.kind = otk::CmdColumns;
        head_raw();
    } else if (norm_head == "options") {
        head.kind = otk::CmdOptions;
        head_raw();
    } else if (norm_head == "tblfm") {
        head.kind = otk::CmdTblfm;
        head_raw();
    } else if (norm_head == "property") {
        head.kind = otk::CmdTblfm;
        head_raw();
    } else if (norm_head == "tags") {
        head.kind = otk::CmdTagsRaw;
        head_raw();
    }
}


void switch_regular_char(Cursor& c) {
    switch (c.get()) {
        case '*': c.token0(otk::Asterisk, &advance1); break;
        case '(': c.token0(otk::ParBegin, &advance1); break;
        case ')': c.token0(otk::ParEnd, &advance1); break;
        case '%': c.token0(otk::Percent, &advance1); break;
        case '\'': c.token0(otk::SingleQuote, &advance1); break;
        case '"': c.token0(otk::DoubleQuote, &advance1); break;
        case '_': c.token0(otk::Underline, &advance1); break;
        case ';': c.token0(otk::Semicolon, &advance1); break;
        case ',': c.token0(otk::Colon, &advance1); break;
        case '^': c.token0(otk::Circumflex, &advance1); break;
        case ':': c.token0(otk::Colon, &advance1); break;
        case '$': c.token0(otk::Dollar, &advance1); break;
        case '#': {
            if (c.is_at('+', +1)) {
                switch_command(c);
            } else {
                c.token0(otk::Punctuation, &advance1);
            }
            break;
        }
        case '@': {
            if (c.has_pos(1) && std::isalpha(c.get(1))) {
                c.token0(otk::At, [](Cursor& c) {
                    c.next();
                    advance_alnum(c);
                });
            } else {
                c.token0(otk::Punctuation, &advance1);
            }
            break;
        }
        case '=': {
            if (c.is_at("==}")) {
                c.token1(otk::CriticHighlightEnd, &advance_count, 3);
            } else {
                c.token0(otk::Equals, &advance1);
            }
            break;
        }
        case '~': {
            if (c.is_at("~~}")) {
                c.token1(otk::CriticReplaceEnd, &advance_count, 3);
            } else if (c.is_at("~>")) {
                c.token1(otk::CriticReplaceMiddle, &advance_count, 2);
            } else {
                c.token0(otk::Tilda, &advance1);
            }
            break;
        }
        case '-': {
            if (c.is_at("-----")) {
                c.token1(otk::TextSeparator, &advance_char1, '-');
            } else if (c.is_at("--}")) {
                c.token1(otk::CriticDeleteEnd, &advance_count, 3);
            } else if (c.is_at("--")) {
                c.token1(otk::DoubleDash, &advance_count, 2);
            } else {
                c.token0(otk::Minus, &advance1);
            }
            break;
        }
        case '{': {
            if (c.is_at("++", 1)) {
                c.token1(otk::CriticAddBegin, &advance_count, 3);
            } else if (c.is_at("--", 1)) {
                c.token1(otk::CriticDeleteBegin, &advance_count, 3);
            } else if (c.is_at("==", 1)) {
                c.token1(otk::CriticHighlightBegin, &advance_count, 3);
            } else if (c.is_at("~~", 1)) {
                c.token1(otk::CriticReplaceBegin, &advance_count, 3);
            } else if (c.is_at(">>", 1)) {
                c.token1(otk::CriticCommentBegin, &advance_count, 3);
            } else {
                c.token1(otk::CurlyBegin, &advance_count, 1);
            }
            break;
        }
        case '\n': {
            int start        = c.pos;
            int end          = c.pos;
            int newlineCount = 0;
            while (c.is_at('\n')) {
                ++newlineCount;
                c.next();
                end = c.pos;
                while (c.is_at(' ')) { c.next(); }

                if (!c.is_at('\n')) {
                    c.pos = end;
                    break;
                }
            }

            if (newlineCount == 1) {
                c.range_token(otk::Newline, start, end);
            } else if (newlineCount == 2) {
                c.range_token(otk::MediumNewline, start, end);
            } else {
                c.range_token(otk::LongNewline, start, end);
            }

            break;
        }
        case ' ': {
            c.token1(otk::Whitespace, &advance_char1, ' ');
            break;
        }
        default: {
            if (std::isalpha(c.get())) {
                c.token0(otk::Word, &advance_alnum);
            } else {
                MSG(fmt("Unknown c {}", c.format()));
                c.next();
            }
        }
    }
}
} // namespace

OrgTokenGroup org::parse::tokenize(
    const std::string&             text,
    org::parse::LexerParams const& params) {
    OrgTokenGroup result;

    if (text.empty()) { return result; }

    Cursor c{
        .p     = params,
        .group = &result,
        .text  = text,
    };

    while (!c.eof()) {
        auto __guard = c.advance_guard();
        switch_regular_char(c);
    }

    return result;
}
