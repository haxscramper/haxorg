#include "base_token.hpp"
#include <haxorg/lexbase/TraceStructured.hpp>
#include <cctype>

#include <lexy/dsl.hpp>
#include <lexy/callback.hpp>
#include <lexy/action/parse.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy/action/trace.hpp>
#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy/action/parse.hpp>
#include <lexy/callback.hpp>
#include <lexy/callback/container.hpp>
#include <lexy/action/trace.hpp>


#pragma clang diagnostic error "-Wswitch"

using namespace hstd;
using namespace org::parse;
using namespace org::report;

namespace dsl = lexy::dsl;


namespace {
bool is_digit_char(char c) { return std::isdigit(c); }
} // namespace


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

    /// \brief Check if there is at least `offset` characters more to read
    bool has_pos(int offset) const { return pos + offset < text.size(); }
    bool has_text() const { return has_pos(0); }

    void skip(char c) {
        LOGIC_ASSERTION_CHECK(get() == c, "{}", c);
        next();
    }

    bool can_search(char c, int offset = 0) const {
        return has_pos(offset) && !is_at(c, offset);
    }

    /// \brief Check if the current cursor positioned at any of the
    /// characters or matches any of the boolean predicates.
    template <typename T, typename... Args>
    bool is_at_any_of(int offset, T first, Args... rest) {
        if (!has_pos(offset)) { return false; }

        char c = get(offset);

        if constexpr (std::is_same_v<T, char>) {
            if (c == first) { return true; }
        } else if constexpr (std::is_invocable_r_v<bool, T, char>) {
            if (first(c)) { return true; }
        } else {
            static_assert(
                std::is_same_v<T, char>
                    || std::is_invocable_r_v<bool, T, char>,
                "Arguments must be either chars or char predicates");
            return false;
        }

        if constexpr (sizeof...(rest) > 0) {
            return is_at_any_of(offset, rest...);
        } else {
            return false;
        }
    }

    template <typename... Args>
    bool is_at_all_of(int offset = 0) const {
        return true;
    }

    template <typename T>
    bool is_at_thing(int offset, T first) const {
        if (!has_pos(offset)) { return false; }

        bool matches = false;
        if constexpr (std::is_same_v<T, char>) {
            matches = text[pos + offset] == first;
        } else if constexpr (std::is_invocable_r_v<bool, T, char>) {
            matches = first(text[pos + offset]);
        } else {
            static_assert(
                std::is_same_v<T, char>
                    || std::is_invocable_r_v<bool, T, char>,
                "Arguments must be either chars or char predicates");
            return false;
        }

        return matches;
    }

    /// \brief Check if cursor is positioned at the start of the sequence
    /// matching variadic argument list. The first argument is matched for
    /// offset 0, the sceond for offset 1 etc. Arguments can be character
    /// literals like `' '` to check for space, or unary predicates, like
    /// `std::isalnum`.
    ///
    /// Usage example `c.is_at_all_of(1, '-', std::isalnum)`
    template <typename T, typename... Args>
    bool is_at_all_of(int offset, T first, Args... rest) const {
        bool matches = is_at_thing(offset, first);

        if (!matches) {
            return false;
        } else {
            return is_at_all_of(offset + 1, rest...);
        }
    }

    template <typename T>
    bool is_at_all_of(int offset, T first) const {
        return is_at_thing(offset, first);
    }

    /// \brief Check if the cursor+offset is at the specified character
    bool is_at(char ch, int offset = 0) const {
        return has_pos(offset) && get(offset) == ch;
    }

    bool is_at(std::string const& text, int offset = 0) const {
        for (int i = 0; i < text.size(); ++i) {
            if (get(i + offset) != text.at(i)) { return false; }
        }

        return true;
    }

    bool is_iat(std::string const& text, int offset = 0) const {
        for (int i = 0; i < text.size(); ++i) {
            if (std::tolower(static_cast<unsigned char>(get(i + offset)))
                != std::tolower(static_cast<unsigned char>(text.at(i)))) {
                return false;
            }
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
        } else if (get() == '\n') {
            line++;
            col = 0;
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

    lexy::string_input<lexy::default_encoding> lexy_input() const {
        return lexy::string_input{text.data() + pos, text.size() - pos};
    }

    template <auto Pattern>
    struct lexeme_completion_rule {
        static constexpr auto value = lexy::callback<int>(
            [](lexy::string_lexeme<> lex) {
                return std::distance(lex.begin(), lex.end());
            });

        static constexpr auto rule = dsl::capture(dsl::token(Pattern));
    };


    template <typename Rule>
    std::optional<int> try_lexy_tok(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        if (p.TraceState) {
            std::string        str;
            lexy::string_input input = lexy_input();

            lexy::visualization_options opts{};
            opts.flags = lexy::visualize_use_unicode
                       | lexy::visualize_use_symbols
                       | lexy::visualize_space;
            lexy::trace_to<Rule>(
                std::back_insert_iterator(str),
                lexy::zstring_input(input.data()),
                opts);
            p.message(str);
        }

        auto result = lexy::parse<Rule>(lexy_input(), lexy::noop);
        if (result.has_value()) {
            return result.value();
        } else {
            return std::nullopt;
        }
    }

    template <auto Pattern>
    std::optional<int> try_lexy_patt(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        return try_lexy_tok<lexeme_completion_rule<Pattern>>(
            line, function);
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

    void unhandled(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) const {
        LOGIC_ASSERTION_CHECK(
            false, "unhandled {} at {}:{}", format(), function, line);
    }

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
        tok->col  = this->col;
        tok->line = this->line;
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
        OrgToken tok;
        tok->col  = this->col;
        tok->line = this->line;
        tok.kind  = kind;

        int start = pos;
        adv(*this, args...);
        int end = pos;

        tok.value.text = std::string{
            text.begin() + start,
            text.begin() + end,
        };

        token(tok, line, function);
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

    void token_adv(
        OrgTokenKind kind,
        int          count,
        int          line     = __builtin_LINE(),
        char const*  function = __builtin_FUNCTION()) {
        token_cb(kind, line, function, [&](Cursor& c) {
            for (int i = 0; i < count; ++i) { c.next(); }
        });
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


void switch_cmd_argument(Cursor& c) {
    switch (c.get()) {
        case '(': c.token0(otk::ParBegin, &advance1); break;
        case ')': c.token0(otk::ParEnd, &advance1); break;
        case ']': c.token0(otk::BraceEnd, &advance1); break;
        case '=': c.token0(otk::Equals, &advance1); break;
        case ',': c.token0(otk::Comma, &advance1); break;
        case ' ': c.token1(otk::Whitespace, &advance_char1, ' '); break;
        case '\n': c.unhandled(); break;
        case '[': c.token0(otk::BraceBegin, &advance1); break;
        case ':': {
            if (c.has_pos(+1) && std::isalnum(c.get(+1))) {
                c.token0(otk::CmdColonIdent, [](Cursor& c) {
                    c.skip(':');
                    while (c.has_text()
                           && (std::isalnum(c.get()) || c.get() == '_'
                               || c.get() == '-')) {
                        c.next();
                    }
                });
            } else {
                c.token0(otk::CmdRawArg, [](Cursor& c) {
                    c.next();
                    while (!c.is_at_any_of(
                        0, '(', ')', ']', '[', '=', ',', ' ', '\n')) {
                        c.next();
                    }
                });
            }
            break;
        }
        default: {
            c.token0(otk::CmdRawArg, [](Cursor& c) {
                while (!c.is_at_any_of(
                    0, '(', ')', ']', '[', '=', ',', ' ', '\n')) {
                    c.next();
                }
            });
        }
    }
}

void switch_regular_char(Cursor& c);

enum class CommandType
{
    Raw,
    Text,
    Args,
};

struct CommandSpec {
    OrgTokenKind token;
    CommandType  type;
};

UnorderedMap<std::string, CommandSpec> CmdSpec{
    {"columns",
     CommandSpec{.token = otk::CmdColumns, .type = CommandType::Raw}},
    {"tblfm",
     CommandSpec{.token = otk::CmdTblfm, .type = CommandType::Raw}},
    {"options",
     CommandSpec{.token = otk::CmdOptions, .type = CommandType::Raw}},
    {"tags",
     CommandSpec{.token = otk::CmdTagsRaw, .type = CommandType::Raw}},
    {"title",
     CommandSpec{.token = otk::CmdTitle, .type = CommandType::Text}},
    {"author",
     CommandSpec{.token = otk::CmdAuthor, .type = CommandType::Text}},
    {"filetags",
     CommandSpec{.token = otk::CmdFiletags, .type = CommandType::Text}},
    {"caption",
     CommandSpec{.token = otk::CmdCaption, .type = CommandType::Text}},
    {"date",
     CommandSpec{.token = otk::CmdDateRaw, .type = CommandType::Text}},
    {"link",
     CommandSpec{.token = otk::CmdLinkRaw, .type = CommandType::Text}},
    {"description",
     CommandSpec{.token = otk::CmdDescription, .type = CommandType::Text}},
    {"language",
     CommandSpec{.token = otk::CmdLanguage, .type = CommandType::Text}},
    {"creator",
     CommandSpec{.token = otk::CmdCreator, .type = CommandType::Text}},
    {"name",
     CommandSpec{.token = otk::CmdName, .type = CommandType::Args}},
    {"constants",
     CommandSpec{.token = otk::CmdConstants, .type = CommandType::Args}},
    {"results",
     CommandSpec{.token = otk::CmdResults, .type = CommandType::Args}},
    {"include",
     CommandSpec{.token = otk::CmdInclude, .type = CommandType::Args}},
    {"header",
     CommandSpec{.token = otk::CmdHeader, .type = CommandType::Args}},
    {"call",
     CommandSpec{.token = otk::CmdCall, .type = CommandType::Args}},
    {"row", CommandSpec{.token = otk::CmdRow, .type = CommandType::Args}},
    {"cell",
     CommandSpec{.token = otk::CmdCell, .type = CommandType::Args}},
    {"latex_class",
     CommandSpec{.token = otk::CmdLatexClass, .type = CommandType::Args}},
    {"latex_compiler",
     CommandSpec{
         .token = otk::CmdLatexCompiler,
         .type  = CommandType::Args}},
    {"latex_header",
     CommandSpec{.token = otk::CmdLatexHeader, .type = CommandType::Args}},
    {"latex_class_options",
     CommandSpec{
         .token = otk::CmdLatexClassOptions,
         .type  = CommandType::Args}},
};

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

    auto head_text = [&]() {
        c.token(head);
        while (c.has_text() && !c.is_at('\n')) {
            auto __guard = c.advance_guard();
            switch_regular_char(c);
        }
    };


    auto get_end_block_offset = [&](std::string const& end) -> int {
        int pos = 0;
        while (c.is_at(' ', pos)) { ++pos; }
        if (c.is_at('#', pos)) {
            ++pos;
        } else {
            return -1;
        }

        if (c.is_at('+', pos)) {
            ++pos;
        } else {
            return -1;
        }

        if (c.is_iat("end", pos)) {
            pos += 3;
        } else {
            return -1;
        }

        if (c.is_at('_', pos)) { ++pos; }

        if (c.is_iat(end, pos)) {
            c.p.message(fmt("end {} {}", pos, c.format()));
            pos += end.size();
            return pos;
        } else {
            return -1;
        }
    };

    if (auto it = CmdSpec.get(norm_head)) {
        head.kind = it->token;
        switch (it->type) {
            case CommandType::Args: head_args(); break;
            case CommandType::Raw: head_raw(); break;
            case CommandType::Text: head_text(); break;
        }
    } else if (norm_head.starts_with("attr")) {
        head.kind = otk::CmdAttr;
        head_args();
    } else if (norm_head.starts_with("begin")) {
        auto block_kind = norm_head.substr(5);
        if (block_kind == "quote") {
            head.kind = otk::CmdQuoteBegin;
            head_args();
        } else if (block_kind == "export") {
            head.kind = otk::CmdExportBegin;
            head_args();
            c.skip('\n');
            int offset;
            while ((offset = get_end_block_offset("export")) == -1) {
                auto __guard = c.advance_guard();
                c.token0(otk::CmdExportLine, [](Cursor& c) {
                    while (c.can_search('\n')) { c.next(); }
                });
                if (c.is_at('\n')) { c.token0(otk::Newline, &advance1); }
            }
            c.token1(otk::CmdExportEnd, &advance_count, offset);
        } else {
            head.kind = otk::CmdDynamicBlockBegin;
            head_args();
        }
    } else if (norm_head.starts_with("end")) {
        auto block_kind = norm_head.substr(3);
        if (block_kind == "quote") {
            head.kind = otk::CmdQuoteEnd;
        } else {
            head.kind = otk::CmdDynamicBlockEnd;
        }
        head_args();
    } else {
        LOGIC_ASSERTION_CHECK(false, "{}", escape_literal(norm_head));
    }
}

void switch_subtree_head(Cursor& c) {
    switch (c.get()) {
        case '[': {
            if (c.is_at('#', +1) && c.has_pos(+2)
                && std::isalnum(c.get(+2))) {
                c.token0(otk::SubtreePriority, [](Cursor& c) {
                    c.skip('[');
                    c.skip('#');
                    advance_alnum(c);
                    c.skip(']');
                });
            } else {
                switch_regular_char(c);
            }
            break;
        }
        default: {
            switch_regular_char(c);
        }
    }
}


void switch_regular_char(Cursor& c) {
    if (c.col == 0) {
        int skip = 0;
        if (c.is_at('-')) {
            c.p.message(fmt("leading minus at col 0 {}", c.format()));
        }
        while (c.is_at(' ', skip)) { ++skip; }
        if (c.is_at('-', skip) && c.is_at(' ', skip + 1)) {
            skip += 2;
            while (c.is_at(' ', skip)) { ++skip; }
            c.token1(otk::LeadingMinus, &advance_count, skip);
            return;
        } else if (c.is_at('+', skip) && c.is_at(' ', skip + 1)) {
            skip += 2;
            while (c.is_at(' ', skip)) { ++skip; }
            c.token1(otk::LeadingPlus, &advance_count, skip);
            return;
        }
    }


    switch (c.get()) {
        case '*': {
            if (c.col == 0) {
                c.token0(otk::SubtreeStars, [](Cursor& c) {
                    advance_char1(c, '*');
                    advance_char1(c, ' ');
                });
            } else {
                c.token0(otk::Asterisk, &advance1);
            }
            break;
        }
        case '(': c.token0(otk::ParBegin, &advance1); break;
        case ')': c.token0(otk::ParEnd, &advance1); break;
        case '%': c.token0(otk::Percent, &advance1); break;
        case '\'': c.token0(otk::SingleQuote, &advance1); break;
        case '"': c.token0(otk::DoubleQuote, &advance1); break;
        case '_': c.token0(otk::Underline, &advance1); break;
        case ';': c.token0(otk::Semicolon, &advance1); break;
        case ',': c.token0(otk::Colon, &advance1); break;
        case '^': c.token0(otk::Circumflex, &advance1); break;
        case '|': c.token0(otk::Pipe, &advance1); break;
        case '`': c.token0(otk::Backtick, &advance1); break;
        case '$': c.token0(otk::Dollar, &advance1); break;
        case '!': c.token0(otk::Exclamation, &advance1); break;
        case '&': c.token0(otk::Ampersand, &advance1); break;
        case '/': c.token0(otk::ForwardSlash, &advance1); break;
        case '[': {
            if (auto span = c.try_lexy_patt<
                            dsl::lit_c<'['> + dsl::digits<>
                            + dsl::lit_c<'%'> + dsl::lit_c<']'>>()) {
                c.token_adv(otk::SubtreeCompletion, *span);

            } else if (
                auto span = c.try_lexy_patt<
                            dsl::lit_c<'['> + dsl::digits<>
                            + dsl::lit_c<'/'> + dsl::digits<>
                            + dsl::lit_c<']'>>()) {
                c.token_adv(otk::SubtreeCompletion, *span);
            } else {
                c.token0(otk::BraceBegin, &advance1);
            }
            break;
        }
        case ':': {
            if (c.is_at(':', +1)) {
                c.token1(otk::DoubleColon, &advance_count, 2);
            } else {
                c.token0(otk::Colon, &advance1);
            }
            break;
        }
        case '>': {
            if (c.is_at_all_of(0, '>', '>', '>')) {
                c.token1(otk::TripleAngleEnd, &advance_count, 3);
            } else if (c.is_at_all_of(0, '>', '>')) {
                c.token1(otk::DoubleAngleEnd, &advance_count, 2);
            } else {
                c.token0(otk::AngleEnd, &advance1);
            }
            break;
        }
        case '<': {
            if (c.is_at_all_of(0, '<', '<', '<')) {
                c.token1(otk::TripleAngleBegin, &advance_count, 3);
            } else if (c.is_at_all_of(0, '<', '<', '}')) {
                c.token1(otk::CriticCommentEnd, &advance_count, 3);
            } else if (c.is_at_all_of(0, '<', '<')) {
                c.token1(otk::DoubleAngleBegin, &advance_count, 2);
            } else if (c.is_at_all_of(0, '<', '%', '%')) {
                c.token1(otk::DynamicTimeContent, &advance_count, 3);
            } else {
                c.token0(otk::AngleEnd, &advance1);
            }
            break;
        }
        case '#': {
            if (c.is_at('+', +1)) {
                switch_command(c);
            } else if (c.is_at('#', +1)) {
                c.token1(otk::DoubleHash, &advance_count, 2);
            } else if (c.is_at(' ', +1)) {
                c.token0(otk::Comment, [](Cursor& c) {
                    while (c.can_search('\n')) { c.next(); }
                });
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
            } else if (
                auto span = c.try_lexy_patt<
                            dsl::lit_c<'@'> + dsl::lit_c<'@'>
                            + dsl::while_one(dsl::ascii::word)
                            + dsl::lit_c<':'>
                            + dsl::until(LEXY_LIT("@@"))>()) {
                c.token0(otk::InlineExportBackend, [](Cursor& c) {
                    c.skip('@');
                    c.skip('@');
                    advance_ident(c);
                });

                c.token0(otk::InlineExportContent, [](Cursor& c) {
                    c.skip(':');
                    while (!c.is_at_all_of(0, '@', '@')) { c.next(); }
                    c.skip('@');
                    c.skip('@');
                });
            } else {
                c.token0(otk::Punctuation, &advance1);
            }
            break;
        }
        case '=': {
            if (c.is_at_all_of(1, '=', '}')) {
                c.token1(otk::CriticHighlightEnd, &advance_count, 3);
            } else if (c.is_at('>', +1)) {
                c.token1(otk::TimeArrow, &advance_count, 2);
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
        case '}': {
            c.token1(otk::CurlyEnd, &advance_count, 1);
            break;
        }
        case '{': {
            if (c.is_at_all_of(1, '+', '+')) {
                c.token1(otk::CriticAddBegin, &advance_count, 3);
            } else if (c.is_at_all_of(1, '-', '-')) {
                c.token1(otk::CriticDeleteBegin, &advance_count, 3);
            } else if (c.is_at_all_of(1, '=', '=')) {
                c.token1(otk::CriticHighlightBegin, &advance_count, 3);
            } else if (c.is_at_all_of(1, '~', '~')) {
                c.token1(otk::CriticReplaceBegin, &advance_count, 3);
            } else if (c.is_at_all_of(1, '>', '>')) {
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
