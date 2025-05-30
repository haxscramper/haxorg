#include "OrgTokenizer.hpp"

#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <haxorg/sem/perfetto_org.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/system/Formatter.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/stdlib/Enumerate.hpp>

using namespace hstd;
using namespace org::parse;

struct Builder : OperationsMsgBulder<Builder, OrgTokenizer::Report> {
    Builder& with_id(OrgTokenId const& id) {
        report.id = id;
        return *this;
    }

    Builder(
        OrgLexer&                lex,
        OrgTokenizer::ReportKind kind,
        char const*              file     = __builtin_FILE_NAME(),
        int                      line     = __builtin_LINE(),
        char const*              function = __builtin_FUNCTION()) {
        this->report = OrgTokenizer::Report{
            OperationsMsg{
                .file     = file,
                .line     = line,
                .function = function,
            },
            .lex  = &lex,
            .kind = kind,
        };
    }
};

#define x_report(kind, ...)                                               \
    if (TraceState) {                                                     \
        this->report(                                                     \
            (::Builder(lex, OrgTokenizer::ReportKind::kind) __VA_ARGS__)  \
                .report);                                                 \
    }


struct tokenizer_error : CRTP_hexception<tokenizer_error> {};

using otk = OrgTokenKind;

template <typename T>
bool opt_equal(CR<Opt<T>> opt, CR<T> value) {
    return opt.has_value() && opt.value() == value;
}

template <typename T>
bool opt_equal(CR<Opt<CRw<T>>> opt, CR<T> value) {
    return opt.has_value() && opt.value() == value;
}

template <typename K, typename V>
bool opt_equal_kind(CR<Opt<CRw<Token<K, V>>>> opt, CR<K> value) {
    return opt.has_value() && opt.value().get().kind == value;
}


#define IN_SET(value, first, ...)                                         \
    (IntSet<decltype((first))>{first, __VA_ARGS__}.contains((value)))

template <typename T, typename... Args>
auto in_set(T const& value, Args&&... args) -> bool {
    IntSet<T> set = IntSet<T>{std::forward<Args>(args)...};
    return set.contains(value);
}

OrgFill fill(OrgLexer& lex) {
    return OrgFill{
        .text = lex.tok()->text,
        .line = lex.tok()->line,
        .col  = lex.tok()->col,
    };
}

template <typename T>
struct std::formatter<rs::subrange<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        rs::subrange<T> const& p,
        FormatContext&         ctx) const {
        fmt_ctx("[", ctx);
        bool first = true;
        for (auto begin = rs::begin(p); begin != rs::end(p);
             begin      = std::next(begin)) {
            if (!first) { fmt_ctx(", ", ctx); }
            fmt_ctx(*begin, ctx);
            first = false;
        }
        return fmt_ctx("]", ctx);
    }
};

const IntSet<OrgTokenKind> line_end{
    otk::Newline,
    otk::MediumNewline,
    otk::LongNewline,
    otk::EndOfFile,
};


namespace {


struct RecombineState {
    OrgTokenizer* d;
    OrgLexer&     lex;
    bool const&   TraceState;

    void report(OrgTokenizer::Report const& report) { d->report(report); }

    finally_std trace(
        std::optional<std::string> msg      = std::nullopt,
        int                        line     = __builtin_LINE(),
        char const*                function = __builtin_FUNCTION()) {
        if (TraceState) {
            ::OrgTokenizer::Report rep;
            rep.line     = line;
            rep.function = function;
            rep.kind     = ::OrgTokenizer::ReportKind::Enter;
            rep.msg      = msg;
            rep.lex      = &lex;
            report(rep);
            return finally_std([line, function, this]() {
                ::OrgTokenizer::Report rep;
                rep.function = function;
                rep.line     = line;
                rep.kind     = ::OrgTokenizer::ReportKind::Leave;
                rep.lex      = &lex;
                report(rep);
            });
        } else {
            return finally_std::nop();
        }
    }


    RecombineState(OrgTokenizer* d, OrgLexer& lex)
        : d(d), lex(lex), TraceState(d->TraceState) {}

    auto prev_token() -> Opt<OrgToken> {
        if (lex.hasNext(-1)) {
            return lex.tok(-1);
        } else {
            return std::nullopt;
        }
    };

    auto next_token() -> Opt<OrgToken> {
        if (lex.hasNext(1)) {
            return lex.tok(1);
        } else {
            return std::nullopt;
        }
    };


    void next(OrgLexer& lex, int line = __builtin_LINE()) {
        x_report(
            Print, .with_line(line).with_msg(fmt("next {}", lex.tok())));
        lex.next();
    }

    void print(std::string msg, int line = __builtin_LINE()) {
        x_report(Print, .with_line(line).with_msg(msg));
    }

    std::string const& tok_str(int offset = 0) const {
        return lex.tok(offset)->text;
    }


    void skip(
        OrgLexer&    lex,
        OrgTokenKind kind,
        int          line = __builtin_LINE()) {
        x_report(
            Print, .with_line(line).with_msg(fmt("skip {}", lex.tok())));
        lex.skip(kind);
    }

    OrgTokenId add_as(OrgTokenKind __to, int line = __builtin_LINE()) {
        auto res = d->out->add(OrgToken{__to, fill(lex)});
        x_report(
            Push,
            .with_id(res).with_line(line).with_msg(
                fmt("add {} from {}", __to, lex.tok())));
        return res;
    }

    void pop(
        Opt<OrgTokenKind> expected = std::nullopt,
        int               line     = __builtin_LINE()) {
        auto res = d->out->add(lex.tok());
        x_report(
            Push,
            .with_id(res).with_line(line).with_msg(
                fmt("pop {}", lex.tok())));
        if (expected) {
            lex.skip(*expected);
        } else {
            lex.next();
        }
    }

    OrgTokenId add(OrgToken const& tok, int line = __builtin_LINE()) {
        auto res = d->out->add(tok);
        x_report(
            Push,
            .with_id(res).with_line(line).with_msg(
                fmt("add {} from {}", tok, lex.tok())));
        return res;
    }

    void pop_as(
        OrgTokenKind      __to,
        Opt<OrgTokenKind> expected = std::nullopt,
        int               line     = __builtin_LINE()) {
        auto res = d->out->add(OrgToken{__to, fill(lex)});
        x_report(
            Push,
            .with_id(res).with_line(line).with_msg(
                fmt("pop {} from {}", __to, lex.tok())));
        if (expected) {
            lex.skip(*expected);
        } else {
            lex.next();
        }
    }

    OrgFill loc_fill(CR<Str> text = "") {
        return OrgFill{
            .text = text,
            .line = lex.tok()->line,
            .col  = lex.tok()->col,
        };
    }


    OrgTokenId add_fake(OrgTokenKind __to, int line = __builtin_LINE()) {
        auto res = d->out->add(OrgToken{__to});
        x_report(
            Push,
            .with_id(res).with_line(line).with_msg(
                fmt("fake {} from {}", __to, lex.tok())));
        return res;
    }

    OrgTokenId add_fake(
        OrgTokenKind __to,
        OrgFill      fill,
        int          line = __builtin_LINE()) {
        auto res = d->out->add(OrgToken{__to, fill});
        x_report(
            Push,
            .with_id(res).with_line(line).with_msg(
                fmt("fake {} from {}", __to, lex.tok())));
        return res;
    }


    IntSet<OrgTokenKind> EmptyToken{
        otk::Whitespace,
        otk::EndOfFile,
        otk::Newline,
        otk::MediumNewline,
        otk::LongNewline,
        otk::AnyPunct,
        otk::LeadingSpace,
        otk::Colon,
        otk::Semicolon,
        otk::Comma,
        otk::StmtListBegin,
        otk::ParBegin,
        otk::ParEnd,
        otk::AnyPunct,
        otk::ForwardSlash,
        otk::Asterisk,
        otk::Underline,
        otk::Punctuation,
    };

    void recombine_markup() {
        auto tr   = trace();
        auto prev = prev_token();
        auto next = next_token();

        auto [open, close, unknown] = //
            UnorderedMap<otk, std::tuple<otk, otk, otk>>{
                {otk::Asterisk,
                 {otk::BoldBegin, otk::BoldEnd, otk::BoldUnknown}},
                {otk::ForwardSlash,
                 {otk::ItalicBegin, otk::ItalicEnd, otk::ItalicUnknown}},
                {otk::Underline,
                 {otk::UnderlineBegin,
                  otk::UnderlineEnd,
                  otk::UnderlineUnknown}},
                {otk::Equals,
                 {otk::VerbatimBegin,
                  otk::VerbatimEnd,
                  otk::VerbatimUnknown}},
                {otk::Plus,
                 {otk::StrikeBegin, otk::StrikeEnd, otk::StrikeUnknown}},
                {otk::Tilda,
                 {otk::MonospaceBegin,
                  otk::MonospaceEnd,
                  otk::MonospaceUnknown}},
            }
                .at(lex.kind());


        bool prev_empty = !prev || EmptyToken.contains(prev->kind);
        bool next_empty = !next || EmptyToken.contains(next->kind);

        if (TraceState) {
            print(fmt(
                "prev kind {} next kind {} prev_empty={} next_empty={}",
                prev ? prev->kind : otk::Unknown,
                next ? next->kind : otk::Unknown,
                prev_empty,
                next_empty));
        }

        if (prev_empty && !next_empty) {
            add_fake(open, {lex.tok().value});
            lex.next();
        } else if (!prev_empty && next_empty) {
            add_fake(close, {lex.tok().value});
            lex.next();
        } else if (
            prev_empty
            && (lex.kind() == otk::Tilda || lex.kind() == otk::Equals)) {
            add_fake(open, {lex.tok().value});
            lex.next();
        } else if (
            next_empty
            && (lex.kind() == otk::Tilda || lex.kind() == otk::Equals)) {
            add_fake(close, {lex.tok().value});
            lex.next();
        } else if (next_empty && prev_empty) {
            pop_as(unknown);
        } else if (lex.kind() == otk::Equals) {
            pop_as(otk::Equals);
        } else {
            pop_as(otk::Punctuation);
        }
    }

    const IntSet<OrgTokenKind> tree_tags{
        otk::Colon,
        otk::Word,
        otk::DoubleHash,
    };


    void map_line_command() {
        auto next = lex.tok(+1);
        pop_as(otk::CmdPrefix);
        switch (next.kind) {
                // case otk::CmdPropertyArgs: {
                //     auto split = next->text.split(' ');
                //     add_fake(
                //         otk::CmdPropertyArgs, OrgFill{.text =
                //         split.at(0)});
                //     add_fake(otk::CmdRawArg, OrgFill{.text =
                //     split.at(1)}); lex.next(); break;
                // }

            case otk::CmdAttr: {
                auto text = lex.tok().value.text;
                text      = text.substr(("attr"_ss).size());
                text      = lstrip(text, CharSet{'_'});
                text      = rstrip(text, CharSet{' ', ':'});
                add_fake(otk::CmdAttr, loc_fill(text));
                lex.next();
                break;
            }
            default: {
                pop_as(next.kind);
            }
        }

        switch (next.kind) {
            case otk::CmdExampleBegin:
            case otk::CmdExportBegin:
            case otk::CmdSrcBegin: {
                map_command_args();
                break;
            }

            case otk::CmdPropertyArgs: {
                map_command_args();
                break;
            }


            case otk::CmdTitle:
                while (lex.at(otk::Whitespace)) { lex.next(); }
                break;
            case otk::CmdPropertyText:
                pop_as(otk::CmdRawArg);
                while (!lex.at(line_end)) { map_interpreted_token(); }
                break;
            default:
        }

        switch (next.kind) {
            case otk::CmdSrcBegin:
                add_fake(otk::CmdContentBegin);
                if (lex.at(line_end)) { lex.next(); }
                break;
            default:
        }
    }

    IntSet<OrgTokenKind> HashTagTokens{
        otk::DoubleHash,
        otk::BraceBegin,
        otk::BraceEnd,
        otk::Whitespace,
        otk::Indent,
    };

    void map_command_args() {
        while (lex.can_search(line_end)) { pop_as(lex.kind()); }
    }

    void map_interpreted_token() {
        auto               __trace  = trace("", __LINE__, "[map]");
        OrgTokenId         start    = lex.pos;
        OrgToken const&    tok      = lex.tok();
        OrgFill const&     val      = tok.value;
        std::string const& str      = tok.value.text;
        auto               map_kind = lex.kind();

        switch (map_kind) {
            case otk::LineCommand: map_line_command(); break;
            case otk::CmdExampleEnd: {
                add_fake(otk::CmdPrefix, loc_fill());
                pop_as(otk::CmdExampleEnd);
                break;
            }

            case otk::CmdRawArg: {
                if (tok_str().starts_with('"')
                    && !tok_str().ends_with('"')) {
                    Vec<OrgToken> buf;
                    buf.push_back(lex.tok());
                    lex.pop();
                    while (lex.tok().kind == OrgTokenKind::Whitespace
                           || lex.tok().kind == OrgTokenKind::CmdRawArg) {
                        buf.push_back(lex.tok());
                        lex.pop();
                        if (buf.back().value.text.ends_with('"')) {
                            break;
                        }
                    }

                    if (buf.back().value.text.ends_with('"')) {
                        OrgToken merged = buf.front();
                        merged->text    = "";
                        for (auto const& it : enumerator(buf)) {
                            merged->text += it.value()->text;
                        }
                        add(merged);
                    } else {
                        for (auto const& tok : buf) { add(tok); }
                    }
                } else {
                    pop();
                }
                break;
            }

            case otk::CmdExportEnd: {
                add_fake(otk::CmdPrefix, loc_fill());
                pop_as(otk::CmdExportEnd);
                break;
            }

            case otk::CmdSrcEnd: {
                add_fake(otk::CmdPrefix, loc_fill());
                pop_as(otk::CmdSrcEnd);
                break;
            }

            case otk::At: {
                add_fake(
                    otk::At, loc_fill(lex.tok().value.text.substr(1)));
                lex.next();
                break;
            }

            case otk::LinkTarget: {
                pop_as(otk::LinkTarget);
                break;
            }

            case otk::Plus:
            case otk::ForwardSlash:
            case otk::Equals:
            case otk::Tilda:
            case otk::Underline:
            case otk::Asterisk: {
                recombine_markup();
                break;
            }
            case otk::EndOfFile: {
                lex.next();
                break;
            }

            case otk::Escaped: {
                add_fake(otk::Escaped, loc_fill(lex.val().text.substr(1)));
                lex.next();
                break;
            }

            case otk::Placeholder: {
                add_fake(
                    otk::Placeholder,
                    loc_fill(lex.val().text.substr(
                        1, lex.val().text.size() - 2)));
                lex.next();
                break;
            }

            case otk::TextSrcBegin: {
                add_fake(
                    otk::TextSrcBegin, loc_fill(lex.val().text.substr(4)));
                lex.next();
                break;
            }

            case otk::Word: {
                if (rs::all_of(lex.tok().value.text, [](char c) {
                        return isupper(c) || c == '_';
                    })) {
                    pop_as(otk::BigIdent);
                } else {
                    pop_as(otk::Word);
                }
                break;
            }


            case otk::SubtreeStars: {
                pop_as(otk::SubtreeStars);
                break;
            }

            case otk::ColonExampleLine: {
                add_fake(
                    otk::ColonExampleLine,
                    loc_fill(
                        1 < lex.val().text.size()
                            ? lex.val().text.substr(2)
                            : ""));
                lex.next();
                break;
            }

            case otk::FootnoteLinked: {
                auto text = lex.val().text.dropPrefix("[fn:").dropSuffix(
                    "]");
                add_fake(otk::FootnoteLinked, loc_fill(text));
                lex.next();
                break;
            }

            default: {
                pop();
            }
        }
    }

    void recombine_impl() {
        while (lex.hasNext(0)) {
            OrgTokenId     start = lex.pos;
            OrgFill const& val   = lex.tok().value;

            map_interpreted_token();

            LOGIC_ASSERTION_CHECK(
                (lex.pos != start),
                "Non-terminating token conversion case, got kind '{}' "
                "text '{}' at id {} with no movement. This is a bug in "
                "the implementation -- we iterated over baseline tokens, "
                "but did not find where to map the item to. The lexer was "
                "{}",
                lex.kind(),
                val.text,
                lex.pos.format(),
                lex.printToString([](ColStream& os, OrgToken const& t) {
                    os << os.yellow() << escape_for_write(t.value.text)
                       << os.end();
                }));
        }
    }
};

} // namespace


struct LineToken {
    DECL_DESCRIBED_ENUM(
        Kind,
        None,
        Line,
        ListItem,
        Subtree,
        BlockOpen,
        BlockClose,
        IndentedLine,
        Property);

    Span<OrgToken> tokens;
    int            indent = 0;
    Kind           kind   = Kind::None;

    bool isListBreakingItem() const {
        if (auto last = tokens.get(1_B)) {
            return kind == Kind::ListItem
                && last->get().kind == otk::LongNewline;
        } else {
            return false;
        }
    }

    BOOST_DESCRIBE_CLASS(LineToken, (), (kind, tokens, indent), (), ());

    IntSet<OrgTokenKind> CmdBlockClose{
        otk::CmdSrcEnd,
        otk::CmdCenterEnd,
        otk::CmdExampleEnd,
        otk::CmdQuoteEnd,
        otk::CmdExportEnd,
        otk::CmdVerseEnd,
        otk::CmdCommentEnd,
        otk::CmdTableEnd,
        otk::CmdRowEnd,
        otk::CmdCellEnd,
        otk::CmdDynamicBlockEnd,
    };

    IntSet<OrgTokenKind> CmdBlockOpen{
        otk::CmdCenterBegin,
        otk::CmdExportBegin,
        otk::CmdExampleBegin,
        otk::CmdSrcBegin,
        otk::CmdQuoteBegin,
        otk::CmdVerseBegin,
        otk::CmdCommentBegin,
        otk::CmdTableBegin,
        otk::CmdRowBegin,
        otk::CmdCellBegin,
        otk::CmdDynamicBlockBegin,
    };

    IntSet<OrgTokenKind> CmdBlockLine{
        otk::CmdTitle,         otk::CmdHeader,
        otk::CmdName,          otk::CmdInclude,
        otk::CmdResults,       otk::CmdCaption,
        otk::CmdColumns,       otk::CmdAttr,
        otk::CmdAttr,          otk::CmdPropertyArgs,
        otk::CmdPropertyRaw,   otk::CmdPropertyText,
        otk::CmdOptions,       otk::CmdFiletags,
        otk::CmdTblfm,         otk::CmdLatexClass,
        otk::CmdLatexCompiler, otk::CmdLatexClassOptions,
        otk::CmdLatexHeader,   otk::CmdStartup,
        otk::CmdRow,           otk::CmdCell,
        otk::CmdAuthor,        otk::CmdCustomRaw,
        otk::CmdDescription,   otk::CmdLinkRaw,
        otk::CmdEmailRaw,      otk::CmdLatexHeaderExtraRaw,
        otk::CmdDateRaw,       otk::CmdLanguage,
        otk::CmdBindRaw,       otk::CmdCategoryRaw,
        otk::CmdSeqTodoRaw,    otk::CmdTagsRaw,
        otk::CmdPrioritiesRaw, otk::CmdMacroRaw,
        otk::CmdSetupfileRaw,  otk::CmdExcludeTagsRaw,
        otk::CmdHtmlHeadRaw,   otk::CmdSelectTagsRaw,
        otk::CmdDrawersRaw,    otk::CmdConstants,
        otk::CmdCreator,       otk::CmdCall,
        otk::CmdKeywordsRaw,
    };

    Opt<Kind> whichBlockLineKind(OrgTokenKind kind) {
        if (CmdBlockLine.contains(kind)) {
            return Kind::Line;
        } else if (CmdBlockOpen.contains(kind)) {
            return Kind::BlockOpen;
        } else if (CmdBlockClose.contains(kind)) {
            return Kind::BlockClose;
        } else {
            return std::nullopt;
        }
    }

    void setLineCommandKind(CR<Span<OrgToken>> tokens, int tokensOffset) {
        CR<OrgToken> current = tokens.at(tokensOffset);
        if (current.kind == otk::LineCommand) {
            if (auto next = whichBlockLineKind(
                    tokens.at(tokensOffset + 1).kind);
                next) {
                kind = *next;
            } else {
                throw tokenizer_error::init(
                    fmt("Unknown line command kind mapping {}, {}",
                        tokens.at(tokensOffset + 1),
                        tokens));
            }


        } else if (CmdBlockClose.contains(current.kind)) {
            kind = Kind::BlockClose;
        } else {
            throw tokenizer_error::init(
                fmt("Expected line command or closing block, but got {}",
                    current.kind));
        }
    }

    void setLeadingSpaceKind(CR<Span<OrgToken>> tokens) {
        if (auto next = tokens.get(1); next) {
            switch (next->get().kind) {
                case otk::TreeClock: kind = Kind::ListItem; break;
                case otk::Minus: {
                    if (auto next2 = tokens.get(2);
                        next2 && next2->get().kind == otk::Whitespace) {
                        kind = Kind::ListItem;
                    } else {
                        kind = Kind::IndentedLine;
                    }
                    break;
                }

                case otk::ColonEnd:
                case otk::ColonPropertyText:
                case otk::ColonProperties:
                case otk::ColonLogbook: kind = Kind::Property; break;

                case otk::LineCommand:

                    setLineCommandKind(tokens, 1);
                    break;

                default: {
                    kind = CmdBlockClose.contains(next->get().kind)
                             ? Kind::BlockClose
                             : Kind::IndentedLine;
                    break;
                }
            }
        } else {
            kind = Kind::IndentedLine;
        }
    }

    void setIndent() {
        CR<OrgToken> first = tokens.at(0);
        switch (first.kind) {
            case otk::CmdExampleLine:
            case otk::SrcContent: {
                for (auto const& ch : first->text) {
                    if (ch == ' ') {
                        ++indent;
                    } else {
                        break;
                    }
                }
                break;
            }

            case otk::LeadingSpace: {
                indent = first->text.length();
                break;
            }

            case otk::LeadingPlus:
            case otk::LeadingNumber:
            case otk::TreeClock:
            case otk::LeadingMinus: {
                indent = rs::count(first->text, ' ') + 2;
                break;
            }
            default:
        }
    }

    void updateForTokens() {
        CR<OrgToken> first = tokens.at(0);
        setIndent();
        switch (first.kind) {
            case otk::LeadingSpace: {
                setLeadingSpaceKind(tokens);
                break;
            }

            case otk::Minus: {
                if (auto next = tokens.get(1);
                    next && next->get().kind == otk::Whitespace) {
                    kind = Kind::ListItem;
                } else {
                    kind = Kind::Line;
                }
                break;
            }

            case otk::LeadingNumber:
            case otk::LeadingMinus:
            case otk::LeadingPlus: kind = Kind::ListItem; break;
            case otk::LineCommand: setLineCommandKind(tokens, 0); break;
            case otk::TreeClock: kind = Kind::ListItem; break;

            default: {
                kind = CmdBlockClose.contains(first.kind)
                         ? Kind::BlockClose
                         : Kind::Line;
                break;
            }
        }
    }

    LineToken(CR<Span<OrgToken>> tokens) : tokens(tokens) {
        if (!tokens.empty()) { updateForTokens(); }
    }
};


struct GroupToken {
    DECL_DESCRIBED_ENUM(Kind, Line, ListItem, Subtree, Properties, Block);

    struct Nested {
        Vec<GroupToken> subgroups{};
        LineToken       begin{{}};
        LineToken       end{{}};
        DESC_FIELDS(Nested, (subgroups, begin, end));
    };

    struct Leaf {
        Span<LineToken> lines{};
        DESC_FIELDS(Leaf, (lines));
    };

    SUB_VARIANTS(DataKind, Data, data, getDataKind, Leaf, Nested);
    BOOST_DESCRIBE_CLASS(GroupToken, (), (kind, data), (), ());

    Kind kind;
    Data data;

    bool isSrc() const {
        if (!(isNested() && getNested().subgroups.has(0))) {
            return false;
        }

        auto const& gr1 = getNested().subgroups.at(0);
        if (gr1.isNested()) { return false; }

        auto const& first = gr1.getLeaf().lines.get(0);

        if (first) {
            auto const& token = first->get().tokens.get(0);
            if (token) {
                return OrgTokSet{otk::SrcContent, otk::CmdExampleLine}
                    .contains(token->get().kind);
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    void push_back(Span<LineToken> lines, Kind kind) {
        getNested().subgroups.push_back(
            GroupToken{.data = Leaf{lines}, .kind = kind});
    }


    int indent() const {
        if (isNested()) {
            return getNested().begin.indent;
        } else {
            return getLeaf().lines.at(0).indent;
        }
    }
};

using LK = LineToken::Kind;
using GK = GroupToken::Kind;


struct TokenVisitor {
    OrgTokenizer*  d;
    bool const&    TraceState;
    Vec<LineToken> to_lines(OrgLexer& lex) {
        __perf_trace("tokens", "to_lines");
        Vec<LineToken> lines;
        auto const&    tokens = lex.in;
        auto           start  = tokens->begin();

        for (auto it = tokens->begin(); it != tokens->end(); ++it) {
            if (line_end.contains(it->kind)) {
                auto span = IteratorSpan(start, std::next(it));
                auto line = LineToken{span};
                if (TraceState) {
                    d->print(lex, fmt("{} {}", line.kind, line.tokens));
                }
                lines.push_back(line);
                start = std::next(it);
            }
        }

        if (start != tokens->end()) {
            auto span = IteratorSpan(start, tokens->end());
            if (TraceState) { d->print(lex, fmt("{}", span)); }
            lines.push_back(LineToken{span});
        }

        return lines;
    }


    Vec<GroupToken> to_groups(Vec<LineToken>& lines) {
        __perf_trace("tokens", "to_groups");
        using Iter = Vec<LineToken>::iterator;
        Func<Opt<GroupToken>(Iter & it)> rec_group;
        rec_group = [&](Iter& it) -> Opt<GroupToken> {
            auto __scope  = d->scopeLevel();
            auto end      = lines.end();
            auto nextline = [&]() { ++it; };
            if (TraceState) {
                d->message(fmt("{} {}", it->kind, it->tokens));
            }

            auto start = it;
            switch (start->kind) {
                case LK::IndentedLine:
                case LK::Line: {
                    int start_indent = start->indent;
                    while (it != end
                           && (it->kind == LK::Line
                               || it->kind == LK::IndentedLine)
                           && (start_indent <= it->indent)) {
                        nextline();
                    }

                    return GroupToken{
                        .data = GroupToken::Leaf{IteratorSpan(start, it)},
                        .kind = GK::Line};
                }

                case LK::ListItem: {
                    nextline();
                    while (it != end && it->kind == LK::IndentedLine
                           && start->indent <= it->indent) {
                        nextline();
                    }

                    return GroupToken{
                        .data = GroupToken::Leaf{IteratorSpan(start, it)},
                        .kind = GK::ListItem};
                }

                case LK::BlockOpen: {
                    GroupToken::Nested sub;
                    sub.begin = *it;
                    nextline();
                    while (it != end && it->kind != LK::BlockClose) {
                        auto res = rec_group(it);
                        if (res) { sub.subgroups.push_back(*res); }
                    }
                    if (it != end) {
                        sub.end = *it;
                        nextline();
                    }

                    return GroupToken{.data = sub, .kind = GK::Block};
                }

                case LK::Property: {
                    while (it != end && it->kind == LK::Property) {
                        nextline();
                    }

                    return GroupToken{
                        .data = GroupToken::Leaf{IteratorSpan(start, it)},
                        .kind = GK::Properties};
                }

                case LK::BlockClose: {
                    nextline();
                    return GroupToken{
                        .data = GroupToken::Leaf{IteratorSpan(start, it)},
                        .kind = GK::Line};
                }

                default: {
                    throw tokenizer_error::init(
                        fmt("Unhandled line kind {} {}",
                            start->kind,
                            it->tokens));
                    return std::nullopt;
                }
            }
        };

        Vec<GroupToken> root{};

        auto it = lines.begin();
        while (it != lines.end()) {
            auto start = it;
            auto rec   = rec_group(it);
            if (rec) {
                LOGIC_ASSERTION_CHECK(start != it, "");
                root.push_back(rec.value());
            }
        }

        return root;
    }
};


struct GroupVisitorState {
    OrgTokenizer* d;
    OrgLexer&     lex;
    bool const&   TraceState;
    OrgTokenGroup regroup;

    GroupVisitorState(OrgTokenizer* d, OrgLexer& lex)
        : d(d), lex(lex), TraceState(d->TraceState) {
        regroup.tokens.reserve(lex.in->size());
    }

    void add_fake(
        OrgTokenKind kind,
        CVec<int>    indentStack,
        int          line     = __builtin_LINE(),
        char const*  function = __builtin_FUNCTION()) {
        auto idx = regroup.add(OrgToken{kind});
        if (TraceState) {
            d->print(
                lex,
                fmt("    [{:<3}] fake  {:<48} indents {:<32}",
                    idx.getIndex(),
                    fmt1(kind),
                    fmt1(indentStack)),
                line,
                function);
        }
    }

    void add_base(
        OrgToken const& tok,
        CVec<int>       indentStack,
        int             line     = __builtin_LINE(),
        char const*     function = __builtin_FUNCTION()) {
        auto idx = regroup.add(tok);
        if (TraceState) {
            d->print(
                lex,
                fmt("    [{:<3}] token {:<48} indents {:<32}",
                    idx.getIndex(),
                    fmt1(tok),
                    fmt1(indentStack)),
                line,
                function);
        }
    }

    void rec_add_line(
        CR<GroupToken> gr,
        CR<LineToken>  line,
        CVec<int>      ind,
        int            code_line = __builtin_LINE(),
        char const*    function  = __builtin_FUNCTION()) {
        if (TraceState) {
            d->print(
                lex,
                fmt("  ADD LINE: indent={} kind={}",
                    line.indent,
                    line.kind),
                code_line,
                function);
        }

        auto const& tokens = line.tokens;
        for (int tok_idx = 0; tok_idx < tokens.size(); ++tok_idx) {
            auto const& tok = tokens.at(tok_idx);
            switch (tok.kind) {
                case otk::TreeClock:
                case otk::Minus: {
                    // Is the first token on the line or preceded
                    // by leading space.
                    if ((tok_idx == 0
                         || tokens.get(tok_idx - 1).value().get().kind
                                == otk::LeadingSpace)
                        && tokens.get(tok_idx + 1)
                        && tokens.get(tok_idx + 1)->get().kind
                               == otk::Whitespace
                        && gr.kind == GK::ListItem) {
                        add_base(tok, ind);

                        if (auto next = tokens.get(tok_idx + 1);
                            next->get().kind == otk::Whitespace) {
                            add_base(next->get(), ind);
                            ++tok_idx;
                        }

                    } else {
                        add_base(tok, ind);
                    }
                    break;
                }

                case otk::LeadingPlus:
                case otk::LeadingNumber:
                case otk::LeadingMinus: {
                    add_base(tok, ind);
                    if (auto next = tokens.get(tok_idx + 1);
                        next->get().kind == otk::Whitespace) {
                        add_base(next->get(), ind);
                        ++tok_idx;
                    }

                    break;
                }
                default: {
                    add_base(tok, ind);
                }
            }
        }
    }

    /// Recursively convert group and line tokens into a stream of org-mode
    /// tokens, adding the indent and dedent. The function recurses only on
    /// the block nodes, the regular list items are flat in the group.
    void rec_convert_groups(CR<Vec<GroupToken>> groups) {
        Vec<int> ind{};
        for (auto gr_index = 0; gr_index < groups.size(); ++gr_index) {
            auto const& gr  = groups.at(gr_index);
            auto        dbg = [&](int         line = __builtin_LINE(),
                           char const* function = __builtin_FUNCTION()) {
                if (TraceState) {
                    print1(
                        fmt("indent: {}, gr.indent(): {} index {}",
                            ind,
                            gr.indent(),
                            gr_index),
                        2,
                        line,
                        function);
                }
            };

            // Add indent or dedent items that precede the content
            if (gr.kind == GK::ListItem) {
                dbg();
                if (ind.empty()) {
                    add_fake(otk::Indent, ind);
                    ind.push_back(gr.indent());
                } else if (ind.back() < gr.indent()) {
                    add_fake(otk::Indent, ind);
                    ind.push_back(gr.indent());
                } else if (gr.indent() < ind.back()) {
                    while (!ind.empty() && gr.indent() < ind.back()) {
                        add_fake(otk::Dedent, ind);
                        ind.pop_back();
                    }

                    /*
                     * ```
                     * - top1
                     *   - nested 1
                     * - top2
                     * ```
                     *
                     * This nested list arrangement causes ambiguity --
                     * there is a 'dedent' for a nested list 1, but the
                     * parser does not have enough information to figure
                     * out that the whole top1 item is done and top2 must
                     * be parsed as a part of different item.
                     *
                     */
                    if (!ind.empty() && ind.back() == gr.indent()) {
                        add_fake(otk::ListItemEnd, ind);
                    }
                } else if (ind.back() == gr.indent()) {
                    // If the previoust list item ended with a long
                    // trailing newline, insert a list break (dedent and
                    // then indent) instead of marking it as a 'same
                    // indent' which would just continue the list.
                    if (auto prev = groups.get(gr_index - 1);
                        prev && prev.value().get().kind == GK::ListItem) {
                        auto const& it = prev.value().get();
                        if (it.isLeaf()
                            && it.getLeaf()
                                   .lines.back()
                                   .isListBreakingItem()) {
                            add_fake(otk::Dedent, ind);
                            add_fake(otk::Indent, ind);
                        } else {
                            add_fake(otk::SameIndent, ind);
                        }
                    } else {
                        add_fake(otk::SameIndent, ind);
                    }
                }
                dbg();

            } else if (!ind.empty()) {
                /* List item content can be indented like this, but
                 * it will still be added to the current list content.
                 * `ind.back() < gr.indent()` is not checked
                 *                  * ```
                 * - List Item
                 *                  *   #+begin_src
                 *                  *   #+end_src
                 * ```
                 */

                while (!ind.empty() && gr.indent() < ind.back()) {
                    dbg();
                    ind.pop_back();

                    add_fake(otk::Dedent, ind);
                }
                dbg();
            }

            // Org-mode allows effectively any form of the source code
            // indentation and because of the base lexer does not have
            // enough context to figure out where indentation ends and
            // source code begins, so token regrouping must do the
            // transform here.
            if (gr.isSrc()) {
                auto const& nest = gr.getNested();
                rec_add_line(gr, nest.begin, ind);
                // Find minimun indent. Org-mode allows the source code
                // content to have indentation that is less than the
                // `#+begin_src` start
                int minIndent = nest.begin.indent;
                for (auto const& sub : nest.subgroups) {
                    for (auto const& line : sub.getLeaf().lines) {
                        auto const& t = line.tokens;
                        if ((t.size() == 2 && t.at(0)->text.empty()
                             && line_end.contains(t.at(1).kind))
                            || (t.size() == 1
                                && line_end.contains(t.at(0).kind))) {
                            continue;
                        } else if (!line.tokens.empty()) {
                            minIndent = std::min(line.indent, minIndent);
                        }
                    }
                }

                // Implement source code content push directly here, there
                // are no additional variations that must be mapped --
                // SrcContent with leading indentation is the first element
                // on any line
                for (auto const& sub : nest.subgroups) {
                    for (auto const& line : sub.getLeaf().lines) {
                        for (auto const& [idx, tok] :
                             enumerate(line.tokens)) {
                            if (idx == 0) {
                                OrgToken tmp;
                                tmp.kind  = tok.kind;
                                tmp.value = OrgFill{
                                    .col  = tok.value.col,
                                    .line = tok.value.line,
                                    .text = tok.value.text.empty()
                                              ? tok.value.text
                                              : tok.value.text.substr(
                                                    minIndent),
                                };

                                add_base(tmp, ind);
                            } else {
                                add_base(tok, ind);
                            }
                        }
                    }
                }

                rec_add_line(gr, nest.end, ind);
            } else if (gr.isNested()) {
                rec_add_line(gr, gr.getNested().begin, ind);
                rec_convert_groups(gr.getNested().subgroups);
                rec_add_line(gr, gr.getNested().end, ind);
            } else {
                for (CR<LineToken> line : gr.getLeaf().lines) {
                    rec_add_line(gr, line, ind);
                }
            }
        }


        if (!ind.empty()) {
            for (auto const& _ : ind) {
                ind.pop_back();
                if (!ind.empty()) { add_fake(otk::Dedent, ind); }
            }
            add_fake(otk::Dedent, ind);
        }
    }

    void print1(
        Str         text,
        int         level,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {

        int  width   = 96 + 9;
        auto aligned = text
                     + Str(" ").repeated(std::clamp<int>(
                         width - (text.runeLen() + level * 2), 0, width));

        d->print(lex, aligned, line, "group", level);
    };

    void print_line(
        CR<LineToken> line,
        Str           prefix,
        int           level,
        int           code_line = __builtin_LINE(),
        char const*   function  = __builtin_FUNCTION()) {
        if (TraceState) {
            print1(
                fmt("[{}] line:{} indent={}{}",
                    prefix,
                    line.kind,
                    line.indent,
                    line.kind == LK::ListItem
                        ? fmt(" ListBreak:{}", line.isListBreakingItem())
                        : ""),
                level,
                code_line,
                function);

            for (int token_idx = 0; token_idx < line.tokens.size();
                 ++token_idx) {
                print1(
                    fmt("[{}] {}", token_idx, line.tokens.at(token_idx)),
                    level + 1,
                    code_line,
                    function);
            }
        }
    };

    void print_groups(CR<Vec<GroupToken>> groups) {
        Func<void(CR<Vec<GroupToken>> groups, int level)> rec_print_group;
        rec_print_group = [&](CR<Vec<GroupToken>> groups, int level) {
            for (int gr_index = 0; gr_index < groups.size(); ++gr_index) {
                auto const& gr = groups.at(gr_index);
                if (TraceState) {
                    print1(
                        fmt("[{}] group:{} indent {}",
                            gr_index,
                            gr.kind,
                            gr.indent()),
                        level);
                }

                if (gr.isNested()) {
                    print_line(gr.getNested().begin, "begin", level + 2);
                    rec_print_group(gr.getNested().subgroups, level + 2);
                    print_line(gr.getNested().end, "end", level + 2);
                } else {
                    for (int line_index = 0;
                         line_index < gr.getLeaf().lines.size();
                         ++line_index) {
                        print_line(
                            gr.getLeaf().lines.at(line_index),
                            fmt1(line_index),
                            level + 2);
                    }
                }
            }
        };

        rec_print_group(groups, 2);
    }
};

void OrgTokenizer::recombine(OrgLexer& lex) {
    // Convert stream of leading space indentations into indent, dedent
    // and 'same indent' tokens.
    TokenVisitor      token{this, this->TraceState};
    Vec<LineToken>    lines = token.to_lines(lex);
    Vec<GroupToken>   root  = token.to_groups(lines);
    GroupVisitorState visitor{this, lex};

    if (TraceState) {
        for (auto const& line : lines) { visitor.print_line(line, "", 0); }
    }
    if (TraceState) { visitor.print_groups(root); }
    {
        __perf_trace("tokens", "rec convert groups");
        visitor.rec_convert_groups(root);
    }
    Lexer<OrgTokenKind, OrgFill> relex{&visitor.regroup};
    RecombineState               recombine_state{this, relex};
    {
        __perf_trace("tokens", "recombine");
        recombine_state.recombine_impl();
    }
}

void OrgTokenizer::convert(OrgTokenGroup& input) {
    Lexer<OrgTokenKind, OrgFill> lex(&input);
    return convert(lex);
}

void OrgTokenizer::convert(OrgLexer& lex) {
    __perf_trace("tokens", "Org tokenizer convert");
    lex.pos = TokenId<OrgTokenKind, OrgFill>::FromValue(1);
    recombine(lex);
}

void OrgTokenizer::print(
    OrgLexer&          lex,
    const std::string& msg,
    int                line,
    const char*        function,
    int                extraIndent) {
    if (TraceState) {
        auto rep = Builder(
                       lex,
                       OrgTokenizer::ReportKind::Print,
                       __FILE__,
                       line,
                       function)
                       .with_msg(msg)
                       .report;

        rep.extraIndent = extraIndent;
        report(rep);
    }
}
