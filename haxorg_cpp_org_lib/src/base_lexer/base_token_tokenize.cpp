#include "base_token_tokenize.hpp"
#include <cctype>
#include <haxorg/lexbase/TraceStructured.hpp>
#include <hstd_cpp_lib/stdlib/formatting/Debug.hpp>

#include <haxorg/sem/perfetto_org.hpp>
#include <hstd_cpp_lib/stdlib/algorithms/strutils.hpp>
#include <hstd_cpp_lib/stdlib/formatting/Formatter.hpp>
#include <lexy/action/parse.hpp>
#include <lexy/action/trace.hpp>
#include <lexy/callback.hpp>
#include <lexy/callback/container.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>


#pragma clang diagnostic error "-Wswitch"

using namespace hstd;
using namespace org::parse;
using namespace org::report;

namespace dsl = lexy::dsl;

namespace {

inline bool is_alpha_fast(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

inline bool is_digit_fast(char c) { return '0' <= c && c <= '9'; }
inline bool is_alnum_fast(char c) { return is_alpha_fast(c) || is_digit_fast(c); }
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
        if (enable_guards) { LOGIC_ASSERTION_CHECK_FMT(has_pos(offset), "{}", format()); }
        return text[pos + offset];
    }

    /// \brief Check if there is at least `offset` characters more to read
    bool has_pos(int offset) const { return pos + offset < text.size(); }
    bool has_text() const { return has_pos(0); }

    void skip(
        char        c,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        if (enable_guards) { LOGIC_ASSERTION_CHECK_FMT(get() == c, "{}", c); }
        if (p.canTrace()) {
            p.message(
                hstd::fmt("skip {} at {}", escape_literal(std::string{c}), format(5)),
                function,
                line);
        }
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
                std::is_same_v<T, char> || std::is_invocable_r_v<bool, T, char>,
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
                std::is_same_v<T, char> || std::is_invocable_r_v<bool, T, char>,
                "Arguments must be either chars or char predicates");
            return false;
        }

        return matches;
    }

    /// \brief Check if cursor is positioned at the start of the sequence
    /// matching variadic argument list. The first argument is matched for
    /// offset 0, the sceond for offset 1 etc. Arguments can be character
    /// literals like `' '` to check for space, or unary predicates, like
    /// `is_alnum_fast`.
    ///
    /// Usage example `c.is_at_all_of(1, '-', is_alnum_fast)`
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
            if (!has_pos(i + offset) || get(i + offset) != text[i]) { return false; }
        }

        return true;
    }

    bool is_iat(std::string const& text, int offset = 0) const {
        for (int i = 0; i < text.size(); ++i) {
            if (std::tolower(static_cast<unsigned char>(get(i + offset)))
                != std::tolower(static_cast<unsigned char>(text[i]))) {
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

    struct Recall {
        int line     = 0;
        int col      = 0;
        int pos      = 0;
        int char_pos = 0;
    };

    Recall getRecall() const {
        return Recall{.line = line, .col = col, .pos = pos, .char_pos = char_pos};
    }

    void setRecall(Recall const& r) {
        this->line     = r.line;
        this->col      = r.col;
        this->pos      = r.pos;
        this->char_pos = r.char_pos;
    }

    bool next(int line = __builtin_LINE(), char const* function = __builtin_FUNCTION()) {
        return nextUnicode(line, function);
    }

    bool is_at_unicode(int offset = 0) {
        return has_pos(offset) && 0xC0 <= static_cast<unsigned char>(get(offset));
    }

    bool nextUnicode(
        int         code_line     = __builtin_LINE(),
        char const* code_function = __builtin_FUNCTION()) {
        if (text.size() <= pos) { return false; }

        unsigned char firstByte = static_cast<unsigned char>(text[pos]);

        if (firstByte < 0x80) {
            if (firstByte == '\n') {
                if (p.canTrace()) {
                    p.message(
                        hstd::fmt("next line over at {}", format(5)),
                        code_function,
                        code_line);
                }
                line++;
                col = 0;
            } else {
                col++;
            }
            pos++;
            char_pos++;
            return pos < text.size();
        }

        size_t charSize = 1;
        if (0xF0 <= firstByte) {
            charSize = 4;
        } else if (0xE0 <= firstByte) {
            charSize = 3;
        } else if (0xC0 <= firstByte) {
            charSize = 2;
        }

        col++;
        char_pos++;
        pos += charSize;
        if (text.size() < pos) { pos = text.size(); }

        return pos < text.size();
    }


    std::string_view lexy_substr(int offset_start, int size) const {
        auto start = text.begin() + pos + offset_start;
        if (pos + offset_start + size < this->text.size()) {
            auto end = text.begin() + pos + offset_start + size;
            return std::string_view{start, end};
        } else {
            auto end = text.end();
            return std::string_view{start, end};
        }
    }

    std::string_view lexy_view(int offset) const {
        auto start = text.begin() + pos + offset;
        auto end   = text.end();
        return std::string_view{start, end};
    }

    lexy::string_input<lexy::default_encoding> lexy_input(int offset) const {
        auto view = lexy_view(offset);
        return lexy::string_input{view.data(), view.size()};
    }

    template <auto Pattern>
    struct lexeme_completion_rule {
        static constexpr auto value = lexy::callback<int>([](lexy::string_lexeme<> lex) {
            return std::distance(lex.begin(), lex.end());
        });

        static constexpr auto rule = dsl::capture(dsl::token(Pattern));
    };


    template <typename Rule>
    std::optional<int> try_lexy_tok(
        int         offset   = 0,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        if (p.canTrace()) {
            auto               __scope = p.begin_scope(std::nullopt, "lexy");
            std::string        str;
            lexy::string_input input = lexy_input(offset);

            lexy::visualization_options opts{};
            opts.flags = lexy::visualize_use_unicode | lexy::visualize_use_symbols
                       | lexy::visualize_space;
            auto view  = lexy_view(offset);
            lexy::trace_to<Rule>(
                std::back_insert_iterator(str), lexy::zstring_input(input.data()), opts);
            p.message(
                hstd::fmt(
                    "lexy view @ {}:{} {}",
                    line,
                    col,
                    escape_literal(view.substr(0, std::min<int>(40, view.size())))),
                function,
                line);
            p.message(str, function, line);
        }

        auto result = lexy::parse<Rule>(lexy_input(offset), lexy::noop);
        if (result.has_value()) {
            return result.value();
        } else {
            return std::nullopt;
        }
    }

    template <auto Pattern>
    std::optional<int> try_lexy_patt(
        int         offset   = 0,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        return try_lexy_tok<lexeme_completion_rule<Pattern>>(offset, line, function);
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

    bool is_last_line_char() const { return !has_pos(+1) || is_at('\n', +1); }

    int position() const { return pos; }
    int getLine() const { return line; }
    int getColumn() const { return col; }

    void reset() {
        pos  = 0;
        line = 1;
        col  = 1;
    }

    LexerParams              p;
    OrgTokenGroup*           group;
    StrView                  text;
    int                      pos           = 0; // byte offset
    int                      char_pos      = 0; // character offset
    int                      line          = 0;
    int                      col           = 0;
    org::parse::SourceFileId file_id       = org::parse::SourceFileId::Nil();
    bool                     enable_guards = true;

    void unhandled(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) const {
        LOGIC_ASSERTION_CHECK_FMT(
            false, "unhandled {} at {}:{}", format(), function, line);
    }

    std::string format(int ahead = 20) const {
        hstd::validate_utf8(text);
        int  end    = std::min<int>(ahead, text.size() - pos);
        auto result = fmt::format(
            "col:{} line:{} pos:{}/{} text:{}",
            col,
            line,
            pos,
            text.size(),
            pos + end < text.size() ? escape_literal(text.substr(pos, end)) : "[EOL]");
        hstd::validate_utf8(result);
        return result;
    }

    void range_token(
        OrgTokenKind kind,
        Recall       start,
        Recall       end,
        int          line     = __builtin_LINE(),
        char const*  function = __builtin_FUNCTION()) {

        OrgToken tok;
        tok->loc = org::parse::SourceLoc{
            .line    = start.line,
            .column  = start.col,
            .file_id = file_id,
            .pos     = start.char_pos,
        };

        tok.kind = kind;

        tok.value.setText(
            std::string_view{text.begin() + start.pos, text.begin() + end.pos});

        token(tok, line, function);
    }

    void token(
        OrgToken const& tok,
        int             line     = __builtin_LINE(),
        char const*     function = __builtin_FUNCTION()) {
        if (p.canTrace()) {
            p.message(hstd::fmt("{} {}", tok, format(10)), function, line);
        }
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
        tok->loc = org::parse::SourceLoc{
            .line    = this->line,
            .column  = this->col,
            .file_id = this->file_id,
            .pos     = this->char_pos,
        };

        tok.kind = kind;

        int start = pos;
        {
            auto __guard = advance_guard();
            adv(*this, args...);
        }
        int end = pos;
        LOGIC_ASSERTION_CHECK_FMT(
            start != end,
            "Token callback at {}:{} produced token of size 0 for the current state {}",
            function,
            line,
            format());

        tok.value.setText(std::string_view{text.begin() + start, text.begin() + end});

        // validate_utf8(tok.value.text);
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

    struct advance_guard_obj {
        Cursor*     c;
        int         start_pos;
        int         line;
        char const* function;
        ~advance_guard_obj() {
            if (c != nullptr) {
                if (start_pos == c->pos) {
                    OP_TRACER_MESSAGE(
                        c->p, "No movement around pos {}: {}", start_pos, c->format());
                }

                LOGIC_ASSERTION_CHECK_FMT(
                    start_pos != c->pos,
                    "No movement around pos {}: {}, advance guard failed at "
                    "{}:{}",
                    start_pos,
                    c->format(),
                    function,
                    line);
            }
        }
    };

    advance_guard_obj advance_guard(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        if (enable_guards) {
            return advance_guard_obj{
                .c         = this,
                .line      = line,
                .function  = function,
                .start_pos = this->pos,
            };
        } else {
            return advance_guard_obj{};
        }
    }
};

using otk = OrgTokenKind;

void advance_count(Cursor& c, int count) {
    for (int i = 0; i < count; ++i) { c.next(); }
}

void advance1(Cursor& c) { c.next(); }


void advance_word(Cursor& c) {
    while (c.has_text() && is_alnum_fast(c.get())) { c.next(); }
    while (c.is_at_any_of(0, '-', '_') && c.has_pos(+1) && is_alnum_fast(c.get(+1))) {
        while (c.is_at_any_of(0, '-', '_') && c.has_pos(+1) && is_alnum_fast(c.get(+1))) {
            c.next();
        }
        while (c.has_text() && is_alnum_fast(c.get())) { c.next(); }
    }

    if (c.is_at('\'')) { c.next(); }
    while (c.has_text() && is_alnum_fast(c.get())) { c.next(); }
}

void advance_number(Cursor& c) {
    if (c.is_at('-')) { c.next(); }
    while (c.has_text() && (is_digit_fast(c.get()) || c.get() == '_')) { c.next(); }
}

void advance_ident(Cursor& c) {
    while (c.has_text() && (is_alnum_fast(c.get()) || c.get() == '_' || c.get() == '-')) {
        c.next();
    }
}

void advance_char1(Cursor& c, char ch) {
    while (c.has_text() && c.get() == ch) { c.next(); }
}

void advace_charset(Cursor& c, CharSet const& set) {
    while (c.has_text() && set.contains(c.get())) { c.next(); }
}


namespace {
void switch_cmd_argument(Cursor& c) {
    switch (c.get()) {
        case '(': c.token0(otk::ParBegin, &advance1); break;
        case ')': c.token0(otk::ParEnd, &advance1); break;
        case ']': c.token0(otk::BraceEnd, &advance1); break;
        case '=': c.token0(otk::Equals, &advance1); break;
        case ',': c.token0(otk::Comma, &advance1); break;
        case '\'': c.token0(otk::SingleQuote, &advance1); break;
        case ' ': c.token1(otk::Whitespace, &advance_char1, ' '); break;
        case '\n': c.unhandled(); break;
        case '[': c.token0(otk::BraceBegin, &advance1); break;
        case '"': {
            c.token0(otk::CmdRawArg, [](Cursor& c) {
                c.next();
                while (c.can_search('"')) {
                    if (c.is_at('\n')) {
                        break;
                    } else if (c.is_at_all_of(0, '\\', '"')) {
                        c.next();
                        c.next();
                    } else {
                        c.next();
                    }
                }
                if (c.is_at('"')) { c.next(); }
            });

            break;
        }
        case ':': {
            if (c.has_pos(+1) && is_alnum_fast(c.get(+1))) {
                c.token0(otk::CmdColonIdent, [](Cursor& c) {
                    c.skip(':');
                    while (
                        c.has_text()
                        && (is_alnum_fast(c.get()) || c.get() == '_' || c.get() == '-')) {
                        c.next();
                    }
                });
            } else {
                c.token0(otk::CmdRawArg, [](Cursor& c) {
                    c.next();
                    while (!c.is_at_any_of(0, '(', ')', ']', '[', '=', ',', ' ', '\n')) {
                        c.next();
                    }
                });
            }
            break;
        }
        default: {
            c.token0(otk::CmdRawArg, [](Cursor& c) {
                while (c.has_text()
                       && !c.is_at_any_of(0, '(', ')', ']', '[', '=', ',', ' ', '\n')) {
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
    {"columns", CommandSpec{.token = otk::CmdColumns, .type = CommandType::Raw}},
    {"tblfm", CommandSpec{.token = otk::CmdTblfm, .type = CommandType::Raw}},
    {"options", CommandSpec{.token = otk::CmdOptions, .type = CommandType::Raw}},
    {"tags", CommandSpec{.token = otk::CmdTagsRaw, .type = CommandType::Raw}},
    {"drawers", CommandSpec{.token = otk::CmdDrawersRaw, .type = CommandType::Raw}},
    {"category", CommandSpec{.token = otk::CmdCategoryRaw, .type = CommandType::Raw}},
    {"priorities", CommandSpec{.token = otk::CmdPrioritiesRaw, .type = CommandType::Raw}},
    {"htmlhead", CommandSpec{.token = otk::CmdHtmlHeadRaw, .type = CommandType::Raw}},
    {"latexheaderextra",
     CommandSpec{.token = otk::CmdLatexHeaderExtraRaw, .type = CommandType::Raw}},
    {"title", CommandSpec{.token = otk::CmdTitle, .type = CommandType::Text}},
    {"author", CommandSpec{.token = otk::CmdAuthor, .type = CommandType::Text}},
    {"filetags", CommandSpec{.token = otk::CmdFiletags, .type = CommandType::Text}},
    {"caption", CommandSpec{.token = otk::CmdCaption, .type = CommandType::Text}},
    {"date", CommandSpec{.token = otk::CmdDateRaw, .type = CommandType::Text}},
    {"link", CommandSpec{.token = otk::CmdLinkRaw, .type = CommandType::Text}},
    {"description", CommandSpec{.token = otk::CmdDescription, .type = CommandType::Text}},
    {"language", CommandSpec{.token = otk::CmdLanguage, .type = CommandType::Text}},
    {"creator", CommandSpec{.token = otk::CmdCreator, .type = CommandType::Text}},
    {"name", CommandSpec{.token = otk::CmdName, .type = CommandType::Args}},
    {"email", CommandSpec{.token = otk::CmdEmailRaw, .type = CommandType::Raw}},
    {"macro", CommandSpec{.token = otk::CmdMacroRaw, .type = CommandType::Raw}},
    {"bind", CommandSpec{.token = otk::CmdBindRaw, .type = CommandType::Raw}},
    {"excludetags",
     CommandSpec{.token = otk::CmdExcludeTagsRaw, .type = CommandType::Raw}},
    {"selecttags", CommandSpec{.token = otk::CmdSelectTagsRaw, .type = CommandType::Raw}},
    {"keywords", CommandSpec{.token = otk::CmdKeywordsRaw, .type = CommandType::Raw}},
    {"setupfile", CommandSpec{.token = otk::CmdSetupfileRaw, .type = CommandType::Raw}},
    {"startup", CommandSpec{.token = otk::CmdStartup, .type = CommandType::Raw}},
    {"seqtodo", CommandSpec{.token = otk::CmdSeqTodoRaw, .type = CommandType::Raw}},
    {"constants", CommandSpec{.token = otk::CmdConstants, .type = CommandType::Args}},
    {"results", CommandSpec{.token = otk::CmdResults, .type = CommandType::Args}},
    {"include", CommandSpec{.token = otk::CmdInclude, .type = CommandType::Args}},
    {"header", CommandSpec{.token = otk::CmdHeader, .type = CommandType::Args}},
    {"call", CommandSpec{.token = otk::CmdCall, .type = CommandType::Args}},
    {"row", CommandSpec{.token = otk::CmdRow, .type = CommandType::Args}},
    {"cell", CommandSpec{.token = otk::CmdCell, .type = CommandType::Args}},
    {"latex_class", CommandSpec{.token = otk::CmdLatexClass, .type = CommandType::Args}},
    {"latex_compiler",
     CommandSpec{.token = otk::CmdLatexCompiler, .type = CommandType::Args}},
    {"latex_header",
     CommandSpec{.token = otk::CmdLatexHeader, .type = CommandType::Args}},
    {"latex_class_options",
     CommandSpec{.token = otk::CmdLatexClassOptions, .type = CommandType::Args}},
};


struct org_ident {
    static constexpr auto oident = LEXY_CHAR_CLASS(
        "oident",
        dsl::ascii::alpha_digit_underscore / LEXY_LIT("-"));

    static constexpr auto rule = dsl::identifier(oident);
};

void switch_command(Cursor& c) {
    __perf_trace("tokens", "command");
    auto __scope = c.p.begin_scope("switch command");
    c.token1(otk::LineCommand, &advance_count, 2);
    c.token0(otk::Word, [](Cursor& c) {
        advance_ident(c);
        if (c.is_at(':')) { c.next(); }
    });

    auto head = c.pop_token();

    auto norm_head  = hstd::normalize(head->text());
    auto lower_head = hstd::lower(head->text());

    // `#+begin:` -- ok
    // `#+begin_src` -- ok
    // `#+begin` -- not ok, re-map to paragraph
    // `#+end` -- not ok, to paragraph
    // `#+end_src` -- ok
    if (!head->text().ends_with(":")
        && !(lower_head.starts_with("begin_") || lower_head.starts_with("end_"))) {
        // [[lex/backtracking-fallback]]
        auto line_start = c.pop_token();
        line_start.kind = otk::Punctuation;
        // not a keyword: push the head token back as a punctuation followed by the
        // regular word
        c.token(line_start);
        c.token(head);
        return;
    }

    auto head_raw = [&](int         line     = __builtin_LINE(),
                        char const* function = __builtin_FUNCTION()) {
        c.token(head, line, function);
        if (c.can_search('\n')) {
            c.token0(
                otk::RawText,
                [](Cursor& c) {
                    while (c.can_search('\n')) { c.next(); }
                },
                line,
                function);
        }
    };

    auto head_args = [&](int         line     = __builtin_LINE(),
                         char const* function = __builtin_FUNCTION()) {
        c.token(head, line, function);
        while (c.has_text() && !c.is_at('\n')) {
            auto __guard = c.advance_guard();
            switch_cmd_argument(c);
        }
    };

    auto head_text = [&](int         line     = __builtin_LINE(),
                         char const* function = __builtin_FUNCTION()) {
        c.token(head, line, function);
        while (c.has_text() && !c.is_at('\n')) {
            auto __guard = c.advance_guard();
            switch_regular_char(c);
        }
    };

    /// \brief Scan forward for a line matching `^[ \t]*#+end_<name>[ \t]*$` (case-insensitive).
    /// Returns absolute position of the end line start, or nullopt if the block is
    /// unclosed.
    auto find_block_end = [&](std::string const& name) -> std::optional<int> {
        int off = 0;
        while (c.has_pos(off)) {
            int p = off;
            while (c.is_at(' ', p) || c.is_at('\t', p)) { ++p; }
            if (c.is_at('#', p) && c.is_at('+', p + 1) && c.is_iat("end", p + 2)) {
                p += 5;
                if (c.is_at('_', p)) { ++p; }
                if (c.is_iat(name, p)) {
                    p += name.size();
                    while (c.is_at(' ', p) || c.is_at('\t', p)) { ++p; }
                    // org requires [ \t]*$ after the name — trailing junk disqualifies
                    // the line
                    if (!c.has_pos(p) || c.is_at('\n', p)) { return c.position() + off; }
                }
            }
            while (c.has_pos(off) && !c.is_at('\n', off)) { ++off; }
            if (c.is_at('\n', off)) { ++off; }
        }
        return std::nullopt;
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
            OP_TRACER_MESSAGE(c.p, "end {} {}", pos, c.format());
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
    } else if (norm_head == "begin") {
        // bare "#+begin:" — dynamic block, name in args
        int off = 0;
        while (c.is_at(' ', off)) { ++off; }
        if (c.has_pos(off) && !c.is_at('\n', off)) {
            head.kind = otk::CmdDynamicBlockBegin;
            head_args();
        } else {
            // name required: "#+begin:" alone is a paragraph
            // TODO: Come up with some sort of warning-level token to denote the
            // ambiguities in the parser logic. [[lex/backtracking-fallback]]
            auto line_start = c.pop_token();
            line_start.kind = otk::Punctuation;
            c.token(line_start);
            c.token(head);
        }
    } else if (norm_head == "end") { // bare "#+end:" — dynamic block end
        head.kind = otk::CmdDynamicBlockEnd;
        head_args();
    } else if (norm_head.starts_with("begin")) {
        auto block_kind = norm_head.substr(5);
        if (block_kind == "quote") {
            head.kind = otk::CmdQuoteBegin;
            head_args();
        } else if (block_kind == "cell") {
            head.kind = otk::CmdCellBegin;
            head_args();
        } else if (block_kind == "center") {
            head.kind = otk::CmdCenterBegin;
            head_args();
        } else if (block_kind == "verse") {
            head.kind = otk::CmdVerseBegin;
            head_args();
        } else if (block_kind == "comment") {
            head.kind = otk::CmdCommentBegin;
            head_args();
        } else if (block_kind == "row") {
            head.kind = otk::CmdRowBegin;
            head_args();
        } else if (block_kind == "table") {
            head.kind = otk::CmdTableBegin;
            head_args();
        } else if (block_kind == "export") {
            head.kind = otk::CmdExportBegin;
            head_args();
            c.token0(otk::Newline, &advance1);
            auto end_pos = find_block_end("export");
            if (!end_pos) {
                OP_TRACER_MESSAGE(
                    c.p, "Could not find the closing block for the export block");
                return;
            }
            while (c.position() < *end_pos) {
                auto __guard = c.advance_guard();
                if (c.is_at('\n')) {
                    c.token0(otk::Newline, &advance1);
                } else {
                    c.token0(otk::CmdExportLine, [](Cursor& c) {
                        while (c.can_search('\n')) { c.next(); }
                    });
                }
            }
            c.token1(otk::CmdExportEnd, &advance_count, get_end_block_offset("export"));
        } else if (block_kind == "example") {
            head.kind = otk::CmdExampleBegin;
            head_args();
            c.token0(otk::Newline, &advance1);
            auto end_pos = find_block_end("example");
            if (!end_pos) {
                OP_TRACER_MESSAGE(
                    c.p, "Could not find the closing block for the example block");
                return;
            }
            while (c.position() < *end_pos) {
                auto __guard = c.advance_guard();
                if (c.is_at('\n')) {
                    c.token0(otk::Newline, &advance1);
                } else {
                    c.token0(otk::CmdExampleLine, [](Cursor& c) {
                        while (c.can_search('\n')) { c.next(); }
                    });
                }
            }
            c.token1(otk::CmdExampleEnd, &advance_count, get_end_block_offset("example"));
        } else if (block_kind == "src") {
            head.kind = otk::CmdSrcBegin;
            head_args();
            c.token0(otk::Newline, &advance1);
            auto end_pos = find_block_end("src");
            if (!end_pos) {
                OP_TRACER_MESSAGE(
                    c.p, "Could not find the closing block for the source code");
                return;
            }
            while (c.position() < *end_pos) {
                auto __guard = c.advance_guard();
                if (c.is_at('\n')) {
                    c.token0(otk::Newline, &advance1);
                } else if (c.is_at_all_of(0, '<', '<')) {
                    c.token1(otk::DoubleAngleBegin, &advance_count, 2);
                } else if (c.is_at_all_of(0, '>', '>')) {
                    c.token1(otk::DoubleAngleEnd, &advance_count, 2);
                } else {
                    c.token0(otk::SrcContent, [](Cursor& c) {
                        while (c.has_text()
                               && !(
                                   c.is_at('\n') || c.is_at_all_of(0, '>', '>')
                                   || c.is_at_all_of(0, '<', '<'))) {
                            c.next();
                        }
                    });
                }
            }
            c.token1(otk::CmdSrcEnd, &advance_count, get_end_block_offset("src"));
        } else if (lower_head.starts_with("begin_")) {
            hstd::Vec<hstd::Str> raw_blocks{"begin_custom_raw_block"};
            // NOTE: This is a possible customization point for the extra raw blocks. For
            // now this is hardcoded and not customizable, in the future I will need to
            // decide if this makes sense.
            hstd::Opt<std::string> found_raw_block;
            for (auto const& raw_block : raw_blocks) {
                if (lower_head == raw_block) { found_raw_block = raw_block; }
            }

            if (found_raw_block.has_value()) {
                head.kind = otk::CmdCustomRawBlockBegin;
                head_args();
                c.token0(otk::Newline, &advance1);
                auto block_name = found_raw_block->substr("begin_"_str_view.size());
                auto end_pos    = find_block_end(block_name);
                if (!end_pos) {
                    OP_TRACER_MESSAGE(
                        c.p, "Could not find the closing block for the example block");
                    return;
                }
                while (c.position() < *end_pos) {
                    auto __guard = c.advance_guard();
                    if (c.is_at('\n')) {
                        c.token0(otk::Newline, &advance1);
                    } else {
                        c.token0(otk::CmdExampleLine, [](Cursor& c) {
                            while (c.can_search('\n')) { c.next(); }
                        });
                    }
                }
                c.token1(
                    otk::CmdCustomRawBlockEnd,
                    &advance_count,
                    get_end_block_offset(block_name));
            } else {
                head.kind = otk::CmdCustomTextBlockBegin;
                head_args();
            }
        } else {
            // e.g. "#+beginner:" is a plain keyword, not a block
            head.kind = otk::CmdCustomRaw;
            head_raw();
        }
    } else if (norm_head.starts_with("end")) {
        auto block_kind = norm_head.substr(3);
        if (block_kind == "quote") {
            head.kind = otk::CmdQuoteEnd;
            head_args();
        } else if (block_kind == "cell") {
            head.kind = otk::CmdCellEnd;
            head_args();
        } else if (block_kind == "center") {
            head.kind = otk::CmdCenterEnd;
            head_args();
        } else if (block_kind == "comment") {
            head.kind = otk::CmdCommentEnd;
            head_args();
        } else if (block_kind == "verse") {
            head.kind = otk::CmdVerseEnd;
            head_args();
        } else if (block_kind == "row") {
            head.kind = otk::CmdRowEnd;
            head_args();
        } else if (block_kind == "table") {
            head.kind = otk::CmdTableEnd;
            head_args();
        } else if (lower_head.starts_with("end_")) {
            // No explicit handling for the custom raw block end -- it is lexer
            // immediately in the same block as the begin
            head.kind = otk::CmdCustomTextBlockEnd;
            head_raw();
        } else {
            // e.g. "#+endnote:" is a plain keyword, not a block end
            head.kind = otk::CmdCustomRaw;
            head_raw();
        }
    } else if (norm_head == "begin") { // `#+begin:` w/o clarifications
        head.kind = otk::CmdDynamicBlockBegin;
        head_args();
    } else if (norm_head == "end") {
        head.kind = otk::CmdDynamicBlockEnd;
    } else if (norm_head.starts_with("property")) {
        auto span = c.try_lexy_patt<
            dsl::whitespace(dsl::ascii::space) + dsl::p<org_ident>>();
        if (span) {
            auto property_kind = normalize(Str{c.lexy_substr(0, *span)});
            OP_TRACER_MESSAGE(c.p, "property kind {}", property_kind);
            if (property_kind == "description" || property_kind == "created"
                || property_kind == "hashtag" || property_kind == "hashtagdef") {
                head.kind = otk::CmdPropertyText;
                head_text();
            } else if (property_kind == "headerargs" || property_kind == "propargs") {
                head.kind = otk::CmdPropertyArgs;
                head_args();
            } else {
                head.kind = otk::CmdCustomRaw;
                head_raw();
            }
        } else {
            head.kind = otk::CmdCustomRaw;
            head_raw();
        }

    } else {
        head.kind = otk::CmdCustomRaw;
        head_raw();
    }
}

void switch_subtree_head(Cursor& c) {
    __perf_trace("tokens", "subtree head");
    switch (c.get()) {
        case '[': {
            if (c.is_at('#', +1) && c.has_pos(+2) && is_alnum_fast(c.get(+2))) {
                c.token0(otk::SubtreePriority, [](Cursor& c) {
                    c.skip('[');
                    c.skip('#');
                    advance_word(c);
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

#define LEXY_ILIT(__text) dsl::ascii::case_folding(LEXY_LIT(__text))

void switch_word(Cursor& c) {
    __perf_trace("tokens", "word");

    auto lex_inline_src = [&]() {
        c.token_adv(otk::CurlyBegin, 1);
        c.token0(otk::RawText, [](Cursor& c) {
            int open = 1;
            while (c.has_text()) {
                OP_TRACER_MESSAGE(c.p, "{}", c.format());
                switch (c.get()) {
                    case '{': {
                        ++open;
                        c.next();
                        break;
                    }
                    case '}': {
                        --open;
                        if (open == 0) {
                            return;
                        } else {
                            c.next();
                        }
                        break;
                    }
                    case '\\': {
                        if (c.is_at_any_of(+1, '{', '}')) {
                            c.next();
                            c.next();
                        } else {
                            c.next();
                        }
                        break;
                    }
                    default: {
                        c.next();
                    }
                }
            }
        });

        c.token_adv(otk::CurlyEnd, 1);
    };

    switch (c.get()) {
        case 'h':
        case 'H': {
            if (c.is_iat("https:") || c.is_iat("http:")) {
                c.token0(otk::LinkProtocolHttp, [](Cursor& c) {
                    advance_count(c, 4);
                    if (c.is_at_any_of(0, 's', 'S')) { c.next(); }
                });

                c.token0(otk::LinkTarget, [](Cursor& c) {
                    while (c.has_text() && !(c.is_at_any_of(0, ' ', ']', '\n'))) {
                        c.next();
                    }
                });
                return;
            }
            break;
        }
        case 's':
        case 'S':
            // Scheduled etc. are only considered a proper subtree times at the start of
            // the line, but tracking the `SCHEDULED: [complex multi-token timestamp]
            // DEADLINE: [...` in the lexer is not very practical the decision is
            // postponed until the `parseSubtreeTimes` in the parser;
            if (c.is_at("SCHEDULED:")) {
                c.token_adv(otk::TreeTime, 10);
                return;
            } else if (
                auto span = c.try_lexy_patt<
                            dsl::ascii::case_folding(LEXY_LIT("src"))
                            + dsl::opt(dsl::lit_c<'_'>)
                            + dsl::while_one(dsl::ascii::alpha_digit_underscore)
                            + dsl::lit_c<'{'>>()) {
                c.token_adv(otk::TextSrcBegin, *span);
                lex_inline_src();
                return;
            }
            break;
        case 'D':
            if (c.is_at("DEADLINE:")) {
                c.token_adv(otk::TreeTime, 9);
                return;
            }
            break;
        case 'C':
            if (c.is_at("CLOSED:")) {
                c.token_adv(otk::TreeTime, 7);
                return;
            } /*else if (
                auto span = c.try_lexy_patt<
                            dsl::ascii::case_folding(LEXY_LIT("call"))
                            + dsl::opt(dsl::lit_c<'_'>)
                            + dsl::while_one(
                                dsl::ascii::alpha_digit_underscore)>()) {
                c.token_adv(otk::Call, *span);
                lex_inline_src();
                return;
            }*/
            break;
    }

    c.token0(otk::Word, &advance_word);
}

auto check_leading(Cursor& c, char ch, int skip) -> std::optional<int> {
    if (c.is_at(ch, skip) && c.is_at_any_of(1 + skip, ' ', '\n')) {
        return 1;
    } else {
        return std::nullopt;
    }
};


struct text_properties {
    static constexpr auto rule //
        = dsl::literal_set(
            LEXY_ILIT("description"),
            LEXY_ILIT("created"),
            LEXY_ILIT("hashtag"),
            LEXY_ILIT("hashtag_def"),
            LEXY_ILIT("hashtag-def"));
};

struct argument_properties {
    static constexpr auto rule //
        = dsl::literal_set(
            LEXY_ILIT("header-args"),
            LEXY_ILIT("header_args"),
            LEXY_ILIT("prop_args"),
            LEXY_ILIT("prop-args"));
};

static constexpr auto time_repeater_pattern //
    = dsl::literal_set(LEXY_LIT(".+"), LEXY_LIT("++"), LEXY_LIT("+"))
    + dsl::while_one(dsl::while_one(dsl::digit<>) + dsl::ascii::alpha);

void switch_time_repeater(Cursor& c) {
    c.token0(otk::TimeRepeaterSpec, [](Cursor& c) {
        if (c.is_at('.')) { c.next(); }
        while (c.is_at('+')) { c.next(); }
    });

    c.token0(otk::TimeRepeaterDuration, [](Cursor& c) {
        while (c.has_text() && is_digit_fast(c.get())) {
            advance_number(c);
            advance_ident(c);
        }
    });
}

std::optional<int> is_at_table_separator(Cursor& c, int skip) {
    int pos = skip;
    if (c.is_at('|', pos)) { pos += 1; }

    int column_count = 0;

    while (true) {
        if (!c.is_at('-', pos)) { break; }
        while (c.is_at('-', pos)) { ++pos; }
        if (c.is_at('+', pos) || c.is_at('|', pos)) {
            ++pos;
        } else {
            break;
        }
        ++column_count;
    }

    if (0 < column_count) {
        return pos;
    } else {
        return std::nullopt;
    }
}


void lex_latex_inline(Cursor& c, std::string const& close, OrgTokenKind end) {
    int offset = 0;
    while (c.has_pos(offset) && !c.is_at('\n', offset)) {
        if (c.is_at(close, offset)
            // for delimiters not starting with a backslash (`$`, `$$`),
            // skip escaped occurrences like `\$`
            && !(close.at(0) != '\\' && 0 < offset && c.is_at('\\', offset - 1))) {
            break;
        }
        ++offset;
    }

    if (c.is_at(close, offset)) {
        if (0 < offset) { c.token_adv(otk::LatexInlineRaw, offset); }
        c.token_adv(end, close.size());
    }
}

inline bool is_monospace_pre_ok(Cursor const& c) {
    // org opening set: bol/whitespace or - ( ' " {
    if (c.pos == 0) { return true; }
    char p = c.text[c.pos - 1];
    return p == ' ' || p == '\n' || p == '\t' || p == '-' || p == '(' || p == '{'
        || p == '\'' || p == '"';
}

inline bool is_monospace_post_char(char c) {
    switch (c) {
        case ' ':
        case '\t':
        case '\n':
        case '-':
        case ')':
        case ']':
        case '}':
        case '[':
        case '.':
        case ',':
        case ';':
        case ':':
        case '!':
        case '?':
        case '\\':
        case '\'':
        case '"': return true;
        default: return false;
    }
}


/// \brief Find the offset of the closing `delim` relative to the opening
/// `delim` at the current cursor position, or nullopt. Never scans past the
/// end of the current paragraph: stops at blank lines and at lines that
/// would start a new element (command, subtree, list item, table row).
///
/// Org-mode parser/lexer/whatever seems to scan the buffer and segment it into the
/// regions and only then identify paragraphs to parse in the buffer. This approach is not
/// possible with the haxorg parser logic, so instead the monospace code has to scan ahead
/// and determine the real boundary.
static std::optional<int> find_monospace_close(Cursor& c, char delim) {
    if (!is_monospace_pre_ok(c)) { return std::nullopt; }
    // Body must open with a non-space, non-delimiter char on the same line.
    if (!c.has_pos(+1) || c.is_at(' ', +1) || c.is_at('\n', +1) || c.is_at(delim, +1)) {
        return std::nullopt;
    }

    for (int offset = 1; c.has_pos(offset); ++offset) {
        if (c.is_at('\n', offset)) {
            // May cross a line break only if the next line continues the
            // same paragraph.
            int look = offset + 1;
            while (c.has_pos(look) && c.is_at(' ', look)) { ++look; }
            if (!c.has_pos(look)) { return std::nullopt; }
            // approximation of the logic in the `org-element-paragraph-parser` to find
            // the region edges.
            if (c.is_at('\n', look)                              // blank line
                || c.is_at_any_of(look, '#', '*', '|')           // cmd/stars/table
                || c.is_at_all_of(look, '-', ' ')                // list item
                || c.is_at_all_of(look, '+', ' ')                // list item
                || c.is_at_all_of(look, is_digit_fast, '.', ' ') // 1. item
                || c.is_at_all_of(look, is_digit_fast, ')', ' ')) {
                return std::nullopt;
            }
            continue;
        }

        if (c.is_at(delim, offset)) {
            // org: body cannot contain the delimiter at all — any occurrence
            // that is not a valid close invalidates the whole opening.
            if (c.is_at(' ', offset - 1) || c.is_at('\n', offset - 1)) {
                return std::nullopt;
            }
            if (!c.has_pos(offset + 1) || is_monospace_post_char(c.get(offset + 1))) {
                return offset;
            }
            return std::nullopt;
        }
    }
    return std::nullopt;
}
bool switch_start_of_the_line(Cursor& c) {
    auto __scope = c.p.begin_scope("switch start of the line:");
    int  skip    = 0;

    auto leading_space = [&](int         line     = __builtin_LINE(),
                             char const* function = __builtin_FUNCTION()) {
        if (0 < skip) { c.token_adv(otk::LeadingSpace, skip, line, function); }
    };

    while (c.is_at(' ', skip)) { ++skip; }

    auto property_subname = [&](int pos) -> int {
        if (auto sub = c.try_lexy_patt<dsl::p<org_ident> + dsl::lit_c<':'>>(pos)) {
            pos += *sub;
        }
        return pos;
    };

    if (auto span = check_leading(c, '-', skip)) {
        c.token1(otk::LeadingMinus, &advance_count, *span + skip);
    } else if (auto span = check_leading(c, '+', skip)) {
        c.token_adv(otk::LeadingPlus, *span + skip);
    } else if (auto span = check_leading(c, '|', skip)) {
        c.token_adv(otk::LeadingPipe, *span + skip);
    } else if (auto span = is_at_table_separator(c, skip)) {
        c.token_adv(otk::TableSeparator, *span + skip);
    } else if (c.is_at('|', skip)) {
        // `|-` is allowed as a table separator
        c.token_adv(otk::LeadingPipe, 1 + skip);
    } else if (auto span = c.try_lexy_patt<LEXY_ILIT("clock:")>(skip)) {
        c.token_adv(otk::TreeClock, *span + skip);
        while (c.can_search('\n')) { switch_regular_char(c); }
    } else if (auto span = c.try_lexy_patt<LEXY_ILIT("%%(")>(skip)) {
        leading_space();
        c.token_adv(otk::AgendaDiaryTimeContent, 2);
        c.token0(otk::ParBegin, &advance1);
    } else if (auto span = c.try_lexy_patt<LEXY_ILIT(":end:")>(skip)) {
        c.token_adv(otk::ColonEnd, *span + skip);
    } else if (auto span = c.try_lexy_patt<LEXY_ILIT(":properties:")>(skip)) {
        // The lexer does not check for the follow-up after the line, the
        // proper diagnostics and handling is done at in the
        // [[parser/missing-continuation-lines]] code in the final parser. Elisp
        // org-mode parser just treats it as a paragraph, but I prefer to have a
        // proper diagnostics to disambiguate the intention without fallbacks to the
        // paragraphs.
        c.token_adv(otk::ColonProperties, *span + skip);
    } else if (
        auto span = c.try_lexy_patt<
                    dsl::digits<> + (dsl::lit_c<'.'> | dsl::lit_c<')'>)+dsl::lit_c<' '>>(
            skip)) {
        c.token_adv(otk::LeadingNumber, *span - 1 + skip);
    } else if (auto span = c.try_lexy_patt<LEXY_ILIT(":logbook:")>(skip)) {
        c.token_adv(otk::ColonLogbook, *span + skip);
    } else if (
        auto span = c.try_lexy_patt<
                    dsl::lit_c<':'> + dsl::p<argument_properties> + dsl::lit_c<':'>>(
            skip)) {
        c.token_adv(otk::ColonArgumentsProperty, property_subname(*span + skip));
        while (c.can_search('\n')) { switch_cmd_argument(c); }
    } else if (
        auto span = c.try_lexy_patt<
                    dsl::lit_c<':'> + dsl::p<text_properties> + dsl::lit_c<':'>>(skip)) {
        c.token_adv(otk::ColonPropertyText, property_subname(*span + skip));
        while (c.can_search('\n')) { switch_regular_char(c); }
    } else if (
        auto
            span = c.try_lexy_patt<dsl::lit_c<':'> + dsl::p<org_ident> + dsl::lit_c<':'>>(
                skip)) {

        c.token_adv(otk::ColonLiteralProperty, property_subname(*span + skip));
        // literal property might have no value at all
        if (c.can_search('\n')) {
            c.token0(otk::RawText, [](Cursor& c) {
                while (c.can_search('\n')) { c.next(); }
            });
        }
    } else if (auto span = check_leading(c, ':', skip)) {
        leading_space();
        int pos = *span;
        while (c.can_search('\n', pos)) { ++pos; }
        c.token_adv(otk::ColonExampleLine, pos);
    } else if (c.is_at_all_of(skip, '#', '+')) {
        leading_space();
        switch_command(c);
    } else if (c.is_at_all_of(skip, '#', ' ')) {
        c.token0(otk::Comment, [](Cursor& c) {
            while (c.can_search('\n')) { c.next(); }
        });
    } else if (0 < skip) {
        leading_space();
    } else if (c.is_at("-----")) {
        int off = 0;
        while (c.is_at('-', off)) { ++off; }
        while (c.is_at(' ', off)) { ++off; }
        if (!c.has_pos(off) || c.is_at('\n', off)) {
            c.token1(otk::TextSeparator, &advance_char1, '-');
        } else {
            c.token0(otk::Minus, &advance1);
        }
    } else {
        return false;
    }

    return true;
}

void switch_opening_bracket(Cursor& c) {
    static constexpr auto link_continuation = LEXY_CHAR_CLASS(
        "oident",
        dsl::ascii::alpha_digit_underscore //
            / LEXY_LIT("-")                //
            / LEXY_LIT("*")                //
            / LEXY_LIT("#")                //
            / LEXY_LIT("*")                //
            / LEXY_LIT(".")                //
            / LEXY_LIT("/")                //
    );

    static constexpr auto link_end = dsl::literal_set(LEXY_LIT("]]"), LEXY_LIT("]["));

    if (auto span = c.try_lexy_patt<
                    dsl::lit_c<'['> + dsl::digits<> + dsl::lit_c<'%'>
                    + dsl::lit_c<']'>>()) {
        c.token_adv(otk::SubtreeCompletion, *span);

    } else if (
        auto span = c.try_lexy_patt<
                    dsl::lit_c<'['> + dsl::digits<> + dsl::lit_c<'/'> + dsl::digits<>
                    + dsl::lit_c<']'>>()) {
        c.token_adv(otk::SubtreeCompletion, *span);
    } else if (c.is_at_all_of(0, '[', '%', '%')) {
        c.token1(otk::InactiveDynamicTimeContent, &advance_count, 3);
    } else if (
        auto span = c.try_lexy_patt<
                    dsl::lit_c<'['> + dsl::lit_c<'#'>
                    + dsl::ascii::alpha_underscore + dsl::lit_c<']'>>()) {
        c.token_adv(otk::SubtreePriority, *span);
    } else if (
        auto span = c.try_lexy_patt<
                    dsl::lit_c<'['>
                    + (dsl::lit_c<'x'>   //
                       | dsl::lit_c<'X'> //
                       | dsl::lit_c<' '> //
                       | dsl::lit_c<'-'> //
                       )
                    + dsl::lit_c<']'>>()) {
        c.token_adv(otk::Checkbox, *span);
    } else if (
        auto span = c.try_lexy_patt<
                    dsl::not_followed_by(LEXY_ILIT("[fn:"), dsl::lit_c<':'>)
                    + dsl::p<org_ident> + dsl::lit_c<']'>>()) {
        c.token_adv(otk::FootnoteLinked, *span);
    } else if (auto span = c.try_lexy_patt<LEXY_ILIT("[fn::")>()) {
        c.token_adv(otk::FootnoteInlineBegin, *span);
    } else if (
        auto span = c.try_lexy_patt<
                    LEXY_ILIT("[fn:") + dsl::p<org_ident> + dsl::lit_c<':'>>()) {
        // labeled inline definition
        c.token_adv(otk::FootnoteInlineBegin, *span);
    } else if (
        auto span = c.try_lexy_patt<
                    LEXY_LIT("[[") + dsl::p<org_ident> + dsl::lit_c<':'>>()) {
        c.token_adv(otk::LinkBegin, 2);

        if (c.is_iat("http")) {
            switch_word(c);
        } else if (c.is_iat("file")) {
            c.token_adv(otk::LinkProtocolFile, 4);
            auto span = c.try_lexy_patt<dsl::until(link_end)>();
            c.token_adv(otk::LinkTarget, *span - 2);
        } else if (c.is_iat("attachment")) {
            c.token0(otk::LinkProtocolAttachment, &advance_ident);
            auto span = c.try_lexy_patt<dsl::until(link_end)>();
            c.token_adv(otk::LinkTarget, *span - 2);
        } else if (c.is_iat("id")) {
            c.token0(otk::LinkProtocolId, &advance_ident);
            auto span = c.try_lexy_patt<dsl::until(link_end)>();
            c.token_adv(otk::LinkTarget, *span - 2);
        } else if (c.is_iat("id")) {
            c.token0(otk::LinkProtocolId, &advance_ident);
            auto span = c.try_lexy_patt<dsl::until(link_end)>();
            c.token_adv(otk::LinkTarget, *span - 2);
        } else {
            // All other link protocols don't require special handling and can be
            // processed as a sequence of basic token words.
            int offset = 0;
            while (c.has_pos(offset) && !c.is_at_any_of(offset, ']', ':', '\n')) {
                ++offset;
            }

            if (c.is_at(':', offset)) {
                c.token_adv(otk::LinkProtocol, offset + 1);
            } else {
                c.token_adv(otk::LinkProtocolInternal, offset);
            }
        }

    } else if (
        auto span = c.try_lexy_patt<
                    LEXY_LIT("[[") + link_continuation + dsl::until(link_end)>()) {
        c.token_adv(otk::LinkBegin, 2);
        switch (c.get()) {
            case '*': {
                auto span = c.try_lexy_patt<dsl::until(link_end)>();
                c.token_adv(otk::LinkProtocolTitle, *span - 2);

                break;
            }
            case '#': {
                c.token_adv(otk::LinkProtocolCustomId, 1);
                auto span = c.try_lexy_patt<dsl::until(link_end)>();
                c.token_adv(otk::LinkTarget, *span - 2);
                break;
            }
            case '/': {
                auto span = c.try_lexy_patt<dsl::until(link_end)>();
                c.token_adv(otk::LinkTargetFile, *span - 2);
                break;
            }
            case '.': {
                auto span = c.try_lexy_patt<dsl::until(link_end)>();
                c.token_adv(otk::LinkTargetFile, *span - 2);
                break;
            }
            default: {
                int offset = 0;
                while (c.has_pos(offset) && !c.is_at_any_of(offset, ']', ':', '\n')) {
                    ++offset;
                }

                if (c.is_at(':', offset)) {
                    c.token_adv(otk::LinkProtocol, offset + 1);
                } else {
                    c.token_adv(otk::LinkProtocolInternal, offset);
                }
                break;
            }
        }

    } else {
        c.token0(otk::BraceBegin, &advance1);
    }
}

void switch_regular_char(Cursor& c) {
    if (c.col == 0) {
        if (switch_start_of_the_line(c)) { return; }
    }

    auto __scope = c.p.begin_scope("switch regular char");
    switch (c.get()) {
        case '*': {
            if (c.col == 0
                && c.try_lexy_patt<dsl::while_one(dsl::lit_c<'*'>) + dsl::lit_c<' '>>()) {
                c.token0(otk::SubtreeStars, [](Cursor& c) { advance_char1(c, '*'); });
            } else {
                c.token0(otk::Asterisk, &advance1);
            }
            break;
        }

        case '+': {
            if (c.is_at_all_of(1, '+', '}')) {
                c.token_adv(otk::CriticAddEnd, 3);
            } else if (c.try_lexy_patt<time_repeater_pattern>()) {
                switch_time_repeater(c);
            } else {
                c.token0(otk::Plus, &advance1);
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
        case ',': c.token0(otk::Comma, &advance1); break;
        case '^': c.token0(otk::Circumflex, &advance1); break;
        case '|': {
            if (c.is_last_line_char()) {
                c.token_adv(otk::TrailingPipe, 1);
            } else {
                c.token0(otk::Pipe, &advance1);
            }
            break;
        }
        case '`': c.token0(otk::Backtick, &advance1); break;
        case '$': {
            if (c.is_at('$', +1) && c.is_at_any_of(+2, ' ', '\t', '\n', ',', '.', ';')) {
                c.token_adv(otk::LatexDollar2Begin, 2);
                lex_latex_inline(c, "$$", otk::LatexDollar2End);
            } else if (c.is_at_any_of(+1, ' ', '\t', '\n', ',', '.', ';')) {
                c.token_adv(otk::LatexDollar1Begin, 1);
                lex_latex_inline(c, "$", otk::LatexDollar1End);
            } else {
                c.token0(otk::Dollar, &advance1);
            }
            break;
        }

        case '!': c.token0(otk::Exclamation, &advance1); break;
        case '&': c.token0(otk::Ampersand, &advance1); break;
        case '/': c.token0(otk::ForwardSlash, &advance1); break;
        case ']': {
            if (c.is_at_all_of(0, ']', ']')) {
                c.token_adv(otk::LinkEnd, 2);
            } else if (c.is_at_all_of(0, ']', '[')) {
                c.token_adv(otk::LinkSplit, 2);
            } else {
                c.token0(otk::BraceEnd, &advance1);
            }
            break;
        }
        case '\\': {
            if (c.is_at_all_of(0, '\\', '(')) {
                c.token_adv(otk::LatexParBegin, 2);
                lex_latex_inline(c, "\\)", otk::LatexParEnd);
            } else if (c.is_at_all_of(0, '\\', '[')) {
                c.token_adv(otk::LatexBraceBegin, 2);
                lex_latex_inline(c, "\\]", otk::LatexBraceEnd);
            } else if (c.is_at_all_of(1, &is_alpha_fast)) {
                // Full symbol syntax expression is handled in the parser, lexer only
                // detects the `\\xyz` syntax. Org-mode has a list of allowed entities
                // that is pulled from runtime variable, but for a general-purpose parser
                // this is not a good approach.
                c.token0(otk::Symbol, [](Cursor& c) {
                    c.skip('\\');
                    advance_word(c);
                });
            } else if (c.is_at('\\', +1)) {
                c.token_adv(otk::DoubleSlash, 2);
            } else {
                c.token_adv(otk::Escaped, 2);
            }
            break;
        }

        case '[': {
            switch_opening_bracket(c);
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
        case '.': {
            if (c.try_lexy_patt<time_repeater_pattern>()) {
                switch_time_repeater(c);
            } else {
                c.token_adv(otk::Punctuation, 1);
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
                c.token1(otk::ActiveDynamicTimeContent, &advance_count, 3);
            } else if (
                auto span = c.try_lexy_patt<
                            dsl::lit_c<'<'> + dsl::times<4>(dsl::digit<>)
                            + dsl::lit_c<'-'> + dsl::times<2>(dsl::digit<>)
                            + dsl::lit_c<'-'> + dsl::times<2>(dsl::digit<>)>()) {
                c.token_adv(otk::AngleBegin, 1);
            } else if (
                auto span = c.try_lexy_patt<
                            dsl::lit_c<'<'> + dsl::p<org_ident> + dsl::lit_c<'>'>>()) {
                c.token_adv(otk::Placeholder, *span);
            } else {
                c.token0(otk::AngleBegin, &advance1);
            }
            break;
        }
        case '#': {
            if (c.is_at('#', +1)) {
                c.token1(otk::DoubleHash, &advance_count, 2);
            } else if (c.is_at_all_of(1, &is_alpha_fast)) {
                c.token0(otk::HashIdent, [](Cursor& c) {
                    c.skip('#');
                    advance_word(c);
                });
            } else {
                c.token0(otk::Punctuation, &advance1);
            }
            break;
        }
        case '@': {
            if (c.has_pos(1) && is_alpha_fast(c.get(1))) {
                c.token0(otk::At, [](Cursor& c) {
                    c.next();
                    advance_word(c);
                });
            } else if (
                auto span = c.try_lexy_patt<
                            dsl::lit_c<'@'> + dsl::lit_c<'@'>
                            + dsl::while_one(dsl::ascii::word) + dsl::lit_c<':'>
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
            } else if (auto close = find_monospace_close(c, '=')) {
                // org verbatim: same delimiter rules as ~ code
                c.token_adv(otk::VerbatimBegin, 1);
                if (1 < *close) { c.token_adv(otk::RawText, *close - 1); }
                c.token_adv(otk::VerbatimEnd, 1);
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
            } else if (auto close = find_monospace_close(c, '~')) {
                c.token_adv(otk::Tilda, 1);
                if (1 < *close) { c.token_adv(otk::RawText, *close - 1); }
                c.token_adv(otk::Tilda, 1);
            } else {
                c.token0(otk::Tilda, &advance1);
            }
            break;
        }


        case '-': {
            if (c.is_at("--}")) {
                c.token1(otk::CriticDeleteEnd, &advance_count, 3);
            } else if (c.is_at("--")) {
                c.token1(otk::DoubleDash, &advance_count, 2);
            } else if (
                auto span = c.try_lexy_patt<
                            dsl::lit_c<'-'> + dsl::digits<>
                            + dsl::identifier(dsl::ascii::alpha)>()) {
                c.token_adv(otk::TimeWarnPeriod, *span);
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
                // Macro parsing and lexing is handled in the parser layer.
                c.token1(otk::CurlyBegin, &advance_count, 1);
            }
            break;
        }
        case '\n': {
            auto start        = c.getRecall();
            auto end          = c.getRecall();
            int  newlineCount = 0;
            while (c.is_at('\n')) {
                ++newlineCount;
                c.next();
                end         = c.getRecall();
                auto recall = c.getRecall();
                while (c.is_at(' ')) { c.next(); }

                if (!c.is_at('\n')) {
                    c.setRecall(recall);
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
            if (is_alpha_fast(c.get())) {
                switch_word(c);
            } else if (is_digit_fast(c.get())) {
                if (auto span = c.try_lexy_patt<
                                dsl::digit<> + dsl::digit<> + dsl::lit_c<':'>
                                + dsl::digit<> + dsl::digit<> + dsl::lit_c<':'>
                                + dsl::digit<> + dsl::digit<>>()) {
                    int pos = *span;
                    if (c.is_iat("am", pos) || c.is_iat("pm", pos)) { pos += 2; }
                    c.token_adv(otk::Time, pos);
                } else if (
                    auto span = c.try_lexy_patt<
                                dsl::while_one(dsl::digit<>) + dsl::lit_c<':'>
                                + dsl::digit<> + dsl::digit<>>()) {
                    int pos = *span;
                    if (c.is_iat("am", pos) || c.is_iat("pm", pos)) { pos += 2; }
                    c.token_adv(otk::Time, pos);
                } else if (
                    auto span = c.try_lexy_patt<
                                dsl::times<4>(dsl::digit<>) + dsl::lit_c<'-'>
                                + dsl::times<2>(dsl::digit<>) + dsl::lit_c<'-'>
                                + dsl::times<2>(dsl::digit<>)>()) {
                    c.token_adv(otk::Date, *span);
                } else if (
                    auto span = c.try_lexy_patt<
                                dsl::integer<int> + dsl::opt(LEXY_LIT("_"))
                                + dsl::while_one(dsl::ascii::alpha)>()) {
                    c.token_adv(otk::Word, *span);
                } else if (
                    auto span = c.try_lexy_patt<
                                dsl::integer<int>
                                + dsl::while_one(dsl::lit_c<'_'> >> dsl::digits<>)>()) {
                    c.token_adv(otk::Word, *span);
                } else {
                    c.token0(otk::Number, [](Cursor& c) {
                        while (c.is_at_all_of(0, is_digit_fast)) { c.next(); }
                    });
                }
            } else {
                if (c.is_at_unicode()) {
                    c.token0(otk::Word, [](Cursor& c) {
                        while (c.is_at_unicode()) { c.nextUnicode(); }
                    });
                } else {
                    c.token0(otk::AnyPunct, [](Cursor& c) { c.nextUnicode(); });
                }
            }
        }
    }
}
} // namespace

namespace {

struct TokenAlignmentFailure {
    int         tokenIndex;
    std::string tokenKind;
    std::string tokenText;
    int         expectedLine;
    int         expectedCol;
    int         expectedPos;
    int         providedLine;
    int         providedCol;
    int         providedPos;
    bool        hasProvidedLoc;
    std::string sourceContext;
    std::string details;
};

struct TokenAlignmentReport {
    int                                processedTokens;
    int                                failingTokens;
    std::vector<TokenAlignmentFailure> failures;
};

static void advanceLoc(
    std::string_view segment,
    int&             line,
    int&             col,
    int&             bytePos,
    int&             charPos) {
    for (char ch : segment) {
        if (ch == '\n') {
            line += 1;
            col = 0;
            charPos += 1;
        } else if ((static_cast<unsigned char>(ch) & 0xC0) != 0x80) {
            // not a UTF-8 continuation byte: new character
            col += 1;
            charPos += 1;
        }
        bytePos += 1;
    }
}


static std::string sourceLineAt(std::string const& text, int targetLine) {
    int line     = 0;
    int start    = 0;
    int textSize = static_cast<int>(text.size());
    for (int i = 0; i <= textSize; i += 1) {
        if (i == textSize || text.at(i) == '\n') {
            if (line == targetLine) {
                return text.substr(
                    static_cast<std::string::size_type>(start),
                    static_cast<std::string::size_type>(i - start));
            }
            line += 1;
            start = i + 1;
        }
    }
    return {};
}

template <typename K>
TokenAlignmentReport validateOrgFillTokens(
    std::string const&                    text,
    std::vector<Token<K, OrgFill>> const& tokens,
    int                                   maxFailures,
    org::parse::SourceFileId              file_id) {
    if (maxFailures <= 0) {
        throw std::invalid_argument{
            fmt::format("maxFailures must be positive, got {}", maxFailures)};
    }

    TokenAlignmentReport report{
        .processedTokens = 0,
        .failingTokens   = 0,
        .failures        = {},
    };

    int textSize = static_cast<int>(text.size());
    int line     = 0;
    int col      = 0;
    int pos      = 0; // byte offset into text
    int charPos  = 0; // character (codepoint) offset

    auto contextAt = [&](int ctxPos) -> std::string {
        if (ctxPos <= textSize) {
            int len = std::min(60, textSize - ctxPos);
            return text.substr(
                static_cast<std::string::size_type>(ctxPos),
                static_cast<std::string::size_type>(len));
        } else {
            return {};
        }
    };

    int tokenCount = static_cast<int>(tokens.size());
    for (int tokenIndex = 0; tokenIndex < tokenCount; tokenIndex += 1) {
        auto const& token = tokens.at(tokenIndex);
        report.processedTokens += 1;

        std::string tokenText = fmt::format("{}", token.value.text());
        int         tokenLen  = static_cast<int>(tokenText.size());
        std::string tokenDesc = fmt::format(
            "{}({})", token.kind, escape_literal(token.value.text()));

        std::vector<std::string> details;

        bool directMatch = false;
        if (pos <= textSize) {
            if (tokenLen == 0) {
                directMatch = true;
            } else if (pos + tokenLen <= textSize) {
                directMatch = text.compare(
                                  static_cast<std::string::size_type>(pos),
                                  static_cast<std::string::size_type>(tokenLen),
                                  tokenText)
                           == 0;
            }
        }

        int matchPos = pos;
        if (!directMatch) {
            int foundPos = -1;

            if (tokenLen != 0 && pos <= textSize) {
                auto found = text.find(
                    tokenText, static_cast<std::string::size_type>(pos));
                if (found != std::string::npos) { foundPos = static_cast<int>(found); }
            }

            if (foundPos == -1) {
                if (pos == textSize && 0 < tokenLen) {
                    details.push_back(
                        fmt::format(
                            "source exhausted at pos {}, token text has len {} and "
                            "cannot be matched for {}",
                            pos,
                            tokenLen,
                            tokenDesc));
                } else {
                    std::string actualSlice;
                    if (pos <= textSize) {
                        int actualLen = std::min(tokenLen, textSize - pos);
                        actualSlice   = text.substr(
                            static_cast<std::string::size_type>(pos),
                            static_cast<std::string::size_type>(actualLen));
                    }
                    details.push_back(
                        fmt::format(
                            "token text not found in remaining source from pos {}, "
                            "expected `{}`, got `{}` for {}",
                            pos,
                            tokenText,
                            actualSlice,
                            tokenDesc));
                }
            } else {
                matchPos            = foundPos;
                std::string skipped = text.substr(
                    static_cast<std::string::size_type>(pos),
                    static_cast<std::string::size_type>(foundPos - pos));
                details.push_back(
                    fmt::format(
                        "misalignment before token: skipped {} chars before next "
                        "token match at pos {}: `{}` for {}",
                        foundPos - pos,
                        foundPos,
                        skipped,
                        tokenDesc));
                advanceLoc(
                    std::string_view{text}.substr(
                        static_cast<std::string::size_type>(pos),
                        static_cast<std::string::size_type>(foundPos - pos)),
                    line,
                    col,
                    pos,
                    charPos);
            }
        }

        int expectedLine = line;
        int expectedCol  = col;
        int expectedPos  = charPos;

        bool hasProvidedLoc = token.value.loc.has_value();
        int  providedLine   = -1;
        int  providedCol    = -1;
        int  providedPos    = -1;

        if (hasProvidedLoc) {
            auto const& provided = token.value.loc.value();
            providedLine         = provided.line;
            providedCol          = provided.column;
            providedPos          = provided.pos;

            if (provided.line != expectedLine || provided.column != expectedCol
                || provided.pos != expectedPos) {
                details.push_back(
                    fmt::format(
                        "location mismatch: provided (line={}, col={}, pos={}) expected "
                        "(line={}, col={}, pos={}) for {}",
                        provided.line,
                        provided.column,
                        provided.pos,
                        expectedLine,
                        expectedCol,
                        expectedPos,
                        tokenDesc));
            }
        } else {
            details.push_back(
                fmt::format(
                    "token has no source location, expected (line={}, col={}, "
                    "pos={}) for {}",
                    expectedLine,
                    expectedCol,
                    expectedPos,
                    tokenDesc));
        }

        // Advance the expected cursor past the token text without touching
        // the token itself.
        if (tokenLen != 0 && matchPos + tokenLen <= textSize) {
            advanceLoc(
                std::string_view{text}.substr(
                    static_cast<std::string::size_type>(matchPos),
                    static_cast<std::string::size_type>(tokenLen)),
                line,
                col,
                pos,
                charPos);
        } else if (tokenLen != 0 && matchPos < textSize) {
            int remaining = textSize - matchPos;
            advanceLoc(
                std::string_view{text}.substr(
                    static_cast<std::string::size_type>(matchPos),
                    static_cast<std::string::size_type>(remaining)),
                line,
                col,
                pos,
                charPos);
        }

        int tokenEndLine = line;

        if (!details.empty()) {
            report.failingTokens += 1;

            if (tokenEndLine == expectedLine) {
                details.push_back(
                    fmt::format(
                        "token line {}: `{}`",
                        expectedLine,
                        sourceLineAt(text, expectedLine)));
            } else {
                details.push_back(
                    fmt::format(
                        R"(token spans lines {}..{}:
start `{}`
end `{}`)",
                        expectedLine,
                        tokenEndLine,
                        sourceLineAt(text, expectedLine),
                        sourceLineAt(text, tokenEndLine)));
            }

            std::string neighbors;
            int         neighborStart = std::max(0, tokenIndex - 2);
            int         neighborEnd   = std::min(tokenCount - 1, tokenIndex + 2);
            for (int neighborIndex = neighborStart; neighborIndex <= neighborEnd;
                 neighborIndex += 1) {
                if (neighborIndex == tokenIndex) { continue; }
                auto const& neighbor = tokens.at(neighborIndex);
                if (!neighbors.empty()) { neighbors += ", "; }
                neighbors += fmt::format(
                    "\n  [{}]{}({})",
                    neighborIndex,
                    neighbor.kind,
                    escape_literal(neighbor.value.text()));
            }
            details.push_back(fmt::format("\nneighbor tokens: {}", neighbors));

            std::string allDetails;
            int         detailCount = static_cast<int>(details.size());
            for (int detailIndex = 0; detailIndex < detailCount; detailIndex += 1) {
                if (detailIndex != 0) { allDetails += " | "; }
                allDetails += details.at(detailIndex);
            }

            report.failures.push_back(
                TokenAlignmentFailure{
                    .tokenIndex     = tokenIndex,
                    .tokenKind      = fmt::format("{}", token.kind),
                    .tokenText      = tokenText,
                    .expectedLine   = expectedLine,
                    .expectedCol    = expectedCol,
                    .expectedPos    = expectedPos,
                    .providedLine   = providedLine,
                    .providedCol    = providedCol,
                    .providedPos    = providedPos,
                    .hasProvidedLoc = hasProvidedLoc,
                    .sourceContext  = contextAt(expectedPos),
                    .details        = allDetails,
                });

            if (maxFailures <= static_cast<int>(report.failures.size())) { break; }
        }
    }

    return report;
}

} // namespace

OrgTokenGroup org::parse::tokenize(
    std::string const&              text,
    org::parse::LexerParams const&  params,
    org::parse::SourceFileId const& file_id) {
    __perf_trace("lexing", "base lexer run");
    OrgTokenGroup result;
    result.tokens.reserve(text.size() / 5);
    LOGIC_ASSERTION_CHECK(!file_id.isNil(), "");

    if (text.empty()) { return result; }

    Cursor c{
        .p             = params,
        .group         = &result,
        .text          = text,
        .file_id       = file_id,
        .enable_guards = params.validateTokens,
    };

    using SFC = hstd::OperationsTracer::ScopeFilter::FilterComponent;
    c.p.setScopeFilters({
        {SFC{SFC::AnyVarargs()}, SFC{SFC::Positive("lexy")}},
    });

    while (!c.eof()) {
        auto __guard = c.advance_guard();
        switch_regular_char(c);
    }

    if (params.validateTokens) {
        auto report = validateOrgFillTokens(text, result.tokens.content, 10, file_id);

        if (0 < report.failures.size()) {
            for (auto const& fail : report.failures) {
                std::cout << fail.details << std::endl;
            }
            LOGIC_ASSERTION_CHECK(false, "");
        }
    }

    if (params.canTrace()) {
        auto os = c.p.getStream();
        result.printToString(os);
    }

    return result;
}
