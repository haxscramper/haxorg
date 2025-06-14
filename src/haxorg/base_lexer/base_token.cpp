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
#include <haxorg/sem/perfetto_org.hpp>


#pragma clang diagnostic error "-Wswitch"

using namespace hstd;
using namespace org::parse;
using namespace org::report;

namespace dsl = lexy::dsl;


namespace {
bool is_digit_char(char c) { return std::isdigit(c); }
bool is_alpha_char(char c) { return std::isalpha(c); }
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

    void skip(
        char        c,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        LOGIC_ASSERTION_CHECK(get() == c, "{}", c);
        if (p.TraceState) {
            p.message(
                fmt("skip {} at {}",
                    escape_literal(std::string{c}),
                    format(5)),
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
            if (!has_pos(i + offset) || get(i + offset) != text.at(i)) {
                return false;
            }
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

    struct Recall {
        int line = 0;
        int col  = 0;
        int pos  = 0;
    };

    Recall getRecall() const {
        return Recall{.line = line, .col = col, .pos = pos};
    }

    void setRecall(Recall const& r) {
        this->line = r.line;
        this->col  = r.col;
        this->pos  = r.pos;
    }

    bool next(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        if (text.size() <= pos) {
            return false;
        } else if (get() == '\n') {
            if (p.TraceState) {
                p.message(
                    fmt("next line over at {}", format(5)),
                    function,
                    line);
            }

            this->line++;
            col = 0;
        } else {
            col++;
        }


        pos++;
        return pos < text.size();
    }

    int is_at_unicode(int offset = 0) {
        return 0xF0 <= static_cast<unsigned char>(get(offset));
    }

    bool nextUnicode() {
        if (text.size() <= pos) {
            return false;
        } else if (current() == '\n') {
            line++;
            col = 1;
            pos++;
            return pos < text.size();
        } else {
            unsigned char firstByte = static_cast<unsigned char>(
                text[pos]);
            size_t charSize = 1;

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

    lexy::string_input<lexy::default_encoding> lexy_input(
        int offset) const {
        auto view = lexy_view(offset);
        return lexy::string_input{view.data(), view.size()};
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
        int         offset   = 0,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        if (p.TraceState) {
            std::string        str;
            lexy::string_input input = lexy_input(offset);

            lexy::visualization_options opts{};
            opts.flags = lexy::visualize_use_unicode
                       | lexy::visualize_use_symbols
                       | lexy::visualize_space;
            auto view = lexy_view(offset);
            lexy::trace_to<Rule>(
                std::back_insert_iterator(str),
                lexy::zstring_input(input.data()),
                opts);
            p.message(
                fmt("lexy view @ {}:{} {}",
                    line,
                    col,
                    escape_literal(
                        view.substr(0, std::min<int>(40, view.size())))),
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
        return try_lexy_tok<lexeme_completion_rule<Pattern>>(
            offset, line, function);
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

    bool is_last_line_char() const {
        return !has_pos(+1) || is_at('\n', +1);
    }

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

    std::string format(int ahead = 20) const {
        int end = std::min<int>(ahead, text.size() - pos);
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
        if (p.TraceState) {
            p.message(fmt("{} {}", tok, format(10)), function, line);
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

void advance_word(Cursor& c) {
    while (c.has_text() && std::isalnum(c.get())) { c.next(); }
    while (c.is_at_any_of(0, '-', '_') && c.has_pos(+1)
           && std::isalnum(c.get(+1))) {
        while (c.is_at_any_of(0, '-', '_') && c.has_pos(+1)
               && std::isalnum(c.get(+1))) {
            c.next();
        }
        while (c.has_text() && std::isalnum(c.get())) { c.next(); }
    }

    if (c.is_at('\'')) { c.next(); }
    while (c.has_text() && std::isalnum(c.get())) { c.next(); }
}

void advance_number(Cursor& c) {
    if (c.is_at('-')) { c.next(); }
    while (c.has_text() && (std::isdigit(c.get()) || c.get() == '_')) {
        c.next();
    }
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
                while (c.has_text()
                       && !c.is_at_any_of(
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
    {"drawers",
     CommandSpec{.token = otk::CmdDrawersRaw, .type = CommandType::Raw}},
    {"category",
     CommandSpec{.token = otk::CmdCategoryRaw, .type = CommandType::Raw}},
    {"priorities",
     CommandSpec{
         .token = otk::CmdPrioritiesRaw,
         .type  = CommandType::Raw}},
    {"htmlhead",
     CommandSpec{.token = otk::CmdHtmlHeadRaw, .type = CommandType::Raw}},
    {"latexheaderextra",
     CommandSpec{
         .token = otk::CmdLatexHeaderExtraRaw,
         .type  = CommandType::Raw}},
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
    {"email",
     CommandSpec{.token = otk::CmdEmailRaw, .type = CommandType::Raw}},
    {"macro",
     CommandSpec{.token = otk::CmdMacroRaw, .type = CommandType::Raw}},
    {"bind",
     CommandSpec{.token = otk::CmdBindRaw, .type = CommandType::Raw}},
    {"excludetags",
     CommandSpec{
         .token = otk::CmdExcludeTagsRaw,
         .type  = CommandType::Raw}},
    {"selecttags",
     CommandSpec{
         .token = otk::CmdSelectTagsRaw,
         .type  = CommandType::Raw}},
    {"keywords",
     CommandSpec{.token = otk::CmdKeywordsRaw, .type = CommandType::Raw}},
    {"setupfile",
     CommandSpec{.token = otk::CmdSetupfileRaw, .type = CommandType::Raw}},
    {"startup",
     CommandSpec{.token = otk::CmdStartup, .type = CommandType::Raw}},
    {"seqtodo",
     CommandSpec{.token = otk::CmdSeqTodoRaw, .type = CommandType::Raw}},
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


struct org_ident {
    static constexpr auto oident = LEXY_CHAR_CLASS(
        "oident",
        dsl::ascii::alpha_digit_underscore / LEXY_LIT("-"));

    static constexpr auto rule = dsl::identifier(oident);
};

void switch_command(Cursor& c) {
    __perf_trace("tokens", "command");
    auto __scope = c.p.scopeLevel();
    c.token1(otk::LineCommand, &advance_count, 2);
    c.token0(otk::Word, [](Cursor& c) {
        advance_ident(c);
        if (c.is_at(':')) { c.next(); }
    });
    auto head      = c.pop_token();
    auto norm_head = normalize(head->text);

    auto head_raw = [&](int         line     = __builtin_LINE(),
                        char const* function = __builtin_FUNCTION()) {
        c.token(head, line, function);
        c.token0(
            otk::RawText,
            [](Cursor& c) {
                while (c.can_search('\n')) { c.next(); }
            },
            line,
            function);
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
            int offset;
            while ((offset = get_end_block_offset("export")) == -1) {
                auto __guard = c.advance_guard();
                c.token0(otk::CmdExportLine, [](Cursor& c) {
                    while (c.can_search('\n')) { c.next(); }
                });
                if (c.is_at('\n')) { c.token0(otk::Newline, &advance1); }
            }
            c.token1(otk::CmdExportEnd, &advance_count, offset);
        } else if (block_kind == "example") {
            head.kind = otk::CmdExampleBegin;
            head_args();
            c.token0(otk::Newline, &advance1);
            int offset;
            while ((offset = get_end_block_offset("example")) == -1) {
                auto __guard = c.advance_guard();
                c.token0(otk::CmdExampleLine, [](Cursor& c) {
                    while (c.can_search('\n')) { c.next(); }
                });
                if (c.is_at('\n')) { c.token0(otk::Newline, &advance1); }
            }
            c.token1(otk::CmdExampleEnd, &advance_count, offset);
        } else if (block_kind == "src") {
            head.kind = otk::CmdSrcBegin;
            head_args();
            c.token0(otk::Newline, &advance1);
            int offset;
            while ((offset = get_end_block_offset("src")) == -1) {
                auto __guard = c.advance_guard();
                if (c.is_at_all_of(0, '<', '<')) {
                    c.token1(otk::DoubleAngleBegin, &advance_count, 2);
                } else if (c.is_at_all_of(0, '>', '>')) {
                    c.token1(otk::DoubleAngleEnd, &advance_count, 2);
                } else {
                    c.token0(otk::SrcContent, [](Cursor& c) {
                        while (c.has_text()
                               && !(
                                   c.is_at('\n')
                                   || c.is_at_all_of(0, '>', '>')
                                   || c.is_at_all_of(0, '<', '<'))) {
                            c.next();
                        }
                    });
                }
                if (c.is_at('\n')) { c.token0(otk::Newline, &advance1); }
            }
            c.token1(otk::CmdSrcEnd, &advance_count, offset);
        } else {
            head.kind = otk::CmdDynamicBlockBegin;
            head_args();
        }
    } else if (norm_head.starts_with("end")) {
        auto block_kind = norm_head.substr(3);
        if (block_kind == "quote") {
            head.kind = otk::CmdQuoteEnd;
        } else if (block_kind == "cell") {
            head.kind = otk::CmdCellEnd;
        } else if (block_kind == "center") {
            head.kind = otk::CmdCenterEnd;
        } else if (block_kind == "comment") {
            head.kind = otk::CmdCommentEnd;
        } else if (block_kind == "verse") {
            head.kind = otk::CmdVerseEnd;
        } else if (block_kind == "row") {
            head.kind = otk::CmdRowEnd;
        } else if (block_kind == "table") {
            head.kind = otk::CmdTableEnd;
        } else {
            head.kind = otk::CmdDynamicBlockEnd;
        }
        head_args();
    } else if (norm_head == "begin") { // `#+begin:` w/o clarifications
        head.kind = otk::CmdDynamicBegin;
        head_args();
    } else if (norm_head == "end") {
        head.kind = otk::CmdDynamicEnd;
    } else if (norm_head.starts_with("property")) {
        auto span = c.try_lexy_patt<
            dsl::whitespace(dsl::ascii::space) + dsl::p<org_ident>>();
        if (span) {
            auto property_kind = normalize(Str{c.lexy_substr(0, *span)});
            c.p.message(fmt("property kind {}", property_kind));
            if (property_kind == "description"
                || property_kind == "created" || property_kind == "hashtag"
                || property_kind == "hashtagdef") {
                head.kind = otk::CmdPropertyText;
                head_text();
            } else if (
                property_kind == "headerargs"
                || property_kind == "propargs") {
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
            if (c.is_at('#', +1) && c.has_pos(+2)
                && std::isalnum(c.get(+2))) {
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
                c.p.message(c.format());
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
            if (c.is_iat("http")) {
                c.token0(otk::LinkProtocolHttp, [](Cursor& c) {
                    advance_count(c, 4);
                    if (c.is_at_any_of(0, 's', 'S')) { c.next(); }
                });

                c.token0(otk::LinkTarget, [](Cursor& c) {
                    while (c.has_text()
                           && !(c.is_at_any_of(0, ' ', ']', '\n'))) {
                        c.next();
                    }
                });
                return;
            }
            break;
        }
        case 's':
        case 'S':
            if (c.is_at("SCHEDULED:")) {
                c.token_adv(otk::TreeTime, 10);
                return;
            } else if (
                auto span = c.try_lexy_patt<
                            dsl::ascii::case_folding(LEXY_LIT("src"))
                            + dsl::opt(dsl::lit_c<'_'>)
                            + dsl::while_one(
                                dsl::ascii::alpha_digit_underscore)>()) {
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
        while (c.has_text() && std::isdigit(c.get())) {
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

void switch_regular_char(Cursor& c) {
    if (c.col == 0) {
        int skip = 0;

        auto leading_space =
            [&](int         line     = __builtin_LINE(),
                char const* function = __builtin_FUNCTION()) {
                if (0 < skip) {
                    c.token_adv(otk::LeadingSpace, skip, line, function);
                }
            };

        while (c.is_at(' ', skip)) { ++skip; }

        auto property_subname = [&](int pos) -> int {
            if (auto sub = c.try_lexy_patt<
                           dsl::p<org_ident> + dsl::lit_c<':'>>(pos)) {
                pos += *sub;
            }
            return pos;
        };

        if (auto span = check_leading(c, '-', skip)) {
            c.token1(otk::LeadingMinus, &advance_count, *span + skip);
            return;
        } else if (auto span = check_leading(c, '+', skip)) {
            c.token_adv(otk::LeadingPlus, *span + skip);
            return;
        } else if (auto span = check_leading(c, '|', skip)) {
            c.token_adv(otk::LeadingPipe, *span + skip);
            return;
        } else if (auto span = is_at_table_separator(c, skip)) {
            c.token_adv(otk::TableSeparator, *span + skip);
            return;
        } else if (
            auto span = c.try_lexy_patt<LEXY_ILIT("clock:")>(skip)) {
            c.token_adv(otk::TreeClock, *span + skip);
            while (c.can_search('\n')) { switch_regular_char(c); }
            return;
        } else if (auto span = c.try_lexy_patt<LEXY_ILIT(":end:")>(skip)) {
            c.token_adv(otk::ColonEnd, *span + skip);
            return;
        } else if (
            auto span = c.try_lexy_patt<LEXY_ILIT(":properties:")>(skip)) {
            c.token_adv(otk::ColonProperties, *span + skip);
            return;
        } else if (
            auto span = c.try_lexy_patt<
                        dsl::digits<>
                        + (dsl::lit_c<'.'>
                           | dsl::lit_c<')'>)+dsl::lit_c<' '>>(skip)) {
            c.token_adv(otk::LeadingNumber, *span - 1 + skip);
            return;
        } else if (
            auto span = c.try_lexy_patt<LEXY_ILIT(":logbook:")>(skip)) {
            c.token_adv(otk::ColonLogbook, *span + skip);
            return;
        } else if (
            auto span = c.try_lexy_patt<
                        dsl::lit_c<':'> + dsl::p<argument_properties>
                        + dsl::lit_c<':'>>(skip)) {
            c.token_adv(
                otk::ColonArgumentsProperty,
                property_subname(*span + skip));
            while (c.can_search('\n')) { switch_cmd_argument(c); }
            return;
        } else if (
            auto span = c.try_lexy_patt<
                        dsl::lit_c<':'> + dsl::p<text_properties>
                        + dsl::lit_c<':'>>(skip)) {
            c.token_adv(
                otk::ColonPropertyText, property_subname(*span + skip));
            while (c.can_search('\n')) { switch_regular_char(c); }
            return;
        } else if (
            auto span = c.try_lexy_patt<
                        dsl::lit_c<':'> + dsl::p<org_ident>
                        + dsl::lit_c<':'>>(skip)) {

            c.token_adv(
                otk::ColonLiteralProperty, property_subname(*span + skip));
            c.token0(otk::RawText, [](Cursor& c) {
                while (c.can_search('\n')) { c.next(); }
            });
            return;
        } else if (auto span = check_leading(c, ':', skip)) {
            leading_space();
            int pos = *span;
            while (c.can_search('\n', pos)) { ++pos; }
            c.token_adv(otk::ColonExampleLine, pos);
            return;
        } else if (c.is_at_all_of(skip, '#', '+')) {
            leading_space();
            switch_command(c);
            return;
        } else if (0 < skip) {
            leading_space();
            return;
        }
    }


    switch (c.get()) {
        case '*': {
            if (c.col == 0
                && c.try_lexy_patt<
                    dsl::while_one(dsl::lit_c<'*'>) + dsl::lit_c<' '>>()) {
                c.token0(otk::SubtreeStars, [](Cursor& c) {
                    advance_char1(c, '*');
                });
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
        case '$': c.token0(otk::Dollar, &advance1); break;
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
            if (c.is_at_all_of(1, &is_alpha_char)) {
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

            static constexpr auto link_end = dsl::literal_set(
                LEXY_LIT("]]"), LEXY_LIT("]["));

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
            } else if (
                auto span = c.try_lexy_patt<
                            dsl::lit_c<'['> + dsl::lit_c<'#'>
                            + dsl::ascii::alpha_underscore
                            + dsl::lit_c<']'>>()) {
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
                            dsl::not_followed_by(
                                LEXY_ILIT("[fn:"), dsl::lit_c<':'>)
                            + dsl::p<org_ident> + dsl::lit_c<']'>>()) {
                c.token_adv(otk::FootnoteLinked, *span);
            } else if (auto span = c.try_lexy_patt<LEXY_ILIT("[fn::")>()) {
                c.token_adv(otk::FootnoteInlineBegin, *span);
            } else if (
                auto span = c.try_lexy_patt<
                            LEXY_LIT("[[") + dsl::p<org_ident>
                            + dsl::lit_c<':'>>()) {
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
                    int offset = 0;
                    while (c.has_pos(offset)
                           && !c.is_at_any_of(offset, ']', ':', '\n')) {
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
                            LEXY_LIT("[[") + link_continuation
                            + dsl::until(link_end)>()) {
                c.token_adv(otk::LinkBegin, 2);
                switch (c.get()) {
                    case '*': {
                        auto span = c.try_lexy_patt<dsl::until(
                            link_end)>();
                        c.token_adv(otk::LinkProtocolTitle, *span - 2);

                        break;
                    }
                    case '#': {
                        c.token_adv(otk::LinkProtocolCustomId, 1);
                        auto span = c.try_lexy_patt<dsl::until(
                            link_end)>();
                        c.token_adv(otk::LinkTarget, *span - 2);
                        break;
                    }
                    case '/': {
                        auto span = c.try_lexy_patt<dsl::until(
                            link_end)>();
                        c.token_adv(otk::LinkTargetFile, *span - 2);
                        break;
                    }
                    case '.': {
                        auto span = c.try_lexy_patt<dsl::until(
                            link_end)>();
                        c.token_adv(otk::LinkTargetFile, *span - 2);
                        break;
                    }
                    default: {
                        int offset = 0;
                        while (
                            c.has_pos(offset)
                            && !c.is_at_any_of(offset, ']', ':', '\n')) {
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
                c.token1(otk::DynamicTimeContent, &advance_count, 3);
            } else if (
                auto span = c.try_lexy_patt<
                            dsl::lit_c<'<'> + dsl::p<org_ident>
                            + dsl::lit_c<'>'>>()) {
                c.token_adv(otk::Placeholder, *span);
            } else {
                c.token0(otk::AngleBegin, &advance1);
            }
            break;
        }
        case '#': {
            if (c.is_at('#', +1)) {
                c.token1(otk::DoubleHash, &advance_count, 2);
            } else if (c.is_at(' ', +1)) {
                c.token0(otk::Comment, [](Cursor& c) {
                    while (c.can_search('\n')) { c.next(); }
                });
            } else if (c.is_at_all_of(1, &is_alpha_char)) {
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
            if (c.has_pos(1) && std::isalpha(c.get(1))) {
                c.token0(otk::At, [](Cursor& c) {
                    c.next();
                    advance_word(c);
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
                if (c.has_pos(-1) && c.is_at(' ', -1)) {
                    c.token0(otk::Tilda, &advance1);

                    int offset = 0;
                    while (c.has_pos(offset + +1)) {
                        if (c.is_at('~', offset)
                            && !(std::isalnum(c.get(offset + 1)))) {
                            break;
                        } else if (c.is_at('\n', offset)) {
                            int newlineOffset = offset;
                            int newlineCount  = 0;
                            while (c.is_at('\n', newlineOffset)) {
                                ++newlineCount;
                                ++newlineOffset;
                                while (c.is_at(' ', newlineOffset)) {
                                    ++newlineOffset;
                                }

                                if (!c.is_at('\n', newlineOffset)) {
                                    break;
                                }
                            }

                            if (newlineCount == 1) {
                                offset = newlineOffset;
                            } else {
                                break;
                            }
                        } else {
                            ++offset;
                        }
                    }

                    if (c.is_at('~', offset)) {
                        c.token_adv(otk::RawText, offset);
                        c.token0(otk::Tilda, &advance1);
                    }
                } else {
                    c.token0(otk::Tilda, &advance1);
                }
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
                end         = c.pos;
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
            if (std::isalpha(c.get())) {
                switch_word(c);
            } else if (std::isdigit(c.get())) {
                if (auto span = c.try_lexy_patt<
                                dsl::digit<> + dsl::digit<>
                                + dsl::lit_c<':'> + dsl::digit<>
                                + dsl::digit<> + dsl::lit_c<':'>
                                + dsl::digit<> + dsl::digit<>>()) {
                    int pos = *span;
                    if (c.is_iat("am", pos) || c.is_iat("pm", pos)) {
                        pos += 2;
                    }
                    c.token_adv(otk::Time, pos);
                } else if (
                    auto span = c.try_lexy_patt<
                                dsl::while_one(dsl::digit<>)
                                + dsl::lit_c<':'> + dsl::digit<>
                                + dsl::digit<>>()) {
                    int pos = *span;
                    if (c.is_iat("am", pos) || c.is_iat("pm", pos)) {
                        pos += 2;
                    }
                    c.token_adv(otk::Time, pos);
                } else if (
                    auto span = c.try_lexy_patt<
                                dsl::times<4>(dsl::digit<>)
                                + dsl::lit_c<'-'>
                                + dsl::times<2>(dsl::digit<>)
                                + dsl::lit_c<'-'>
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
                                + dsl::while_one(
                                    dsl::lit_c<'_'> >> dsl::digits<>)>()) {
                    c.token_adv(otk::Word, *span);
                } else {
                    c.token0(otk::Number, [](Cursor& c) {
                        while (c.is_at_all_of(0, is_digit_char)) {
                            c.next();
                        }
                    });
                }
            } else {
                if (c.is_at_unicode()) {
                    c.token0(otk::Word, [](Cursor& c) {
                        while (c.is_at_unicode()) { c.nextUnicode(); }
                    });
                } else {
                    c.token0(
                        otk::AnyPunct, [](Cursor& c) { c.nextUnicode(); });
                }
            }
        }
    }
}
} // namespace

OrgTokenGroup org::parse::tokenize(
    const std::string&             text,
    org::parse::LexerParams const& params) {
    __perf_trace("lexing", "base lexer run");
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
