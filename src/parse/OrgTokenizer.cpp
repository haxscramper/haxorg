#include "OrgTokenizer.hpp"

#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/wrappers/perfetto_aux.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/system/Formatter.hpp>


struct Builder : OperationsMsgBulder<Builder, OrgTokenizer::Report> {
    Builder& with_id(OrgTokenId const& id) {
        report.id = id;
        return *this;
    }

    Builder(
        BaseLexer&               lex,
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


using otk = OrgTokenKind;
using obt = BaseTokenKind;

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

OrgFill fill(BaseLexer& lex) { return OrgFill{.base = lex.tok().value}; }

template <typename T>
struct std::formatter<std::reference_wrapper<T>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        std::reference_wrapper<T> const& p,
        FormatContext&                   ctx) const {
        return fmt_ctx(p.get(), ctx);
    }
};

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

const IntSet<BaseTokenKind> line_end{
    obt::Newline,
    obt::MediumNewline,
    obt::LongNewline,
    obt::EndOfFile,
};


namespace {


struct RecombineState {
    OrgTokenizer* d;
    BaseLexer&    lex;
    bool const&   TraceState;

    void report(OrgTokenizer::Report const& report) { d->report(report); }

    finally trace(
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
            return finally([line, function, this]() {
                ::OrgTokenizer::Report rep;
                rep.function = function;
                rep.line     = line;
                rep.kind     = ::OrgTokenizer::ReportKind::Leave;
                rep.lex      = &lex;
                report(rep);
            });
        } else {
            return finally::nop();
        }
    }


    RecombineState(OrgTokenizer* d, BaseLexer& lex)
        : d(d), lex(lex), TraceState(d->TraceState) {}

    auto prev_token() -> Opt<BaseToken> {
        if (lex.hasNext(-1)) {
            return lex.tok(-1);
        } else {
            return std::nullopt;
        }
    };

    auto next_token() -> Opt<BaseToken> {
        if (lex.hasNext(1)) {
            return lex.tok(1);
        } else {
            return std::nullopt;
        }
    };


    void next(BaseLexer& lex, int line = __builtin_LINE()) {
        x_report(
            Print, .with_line(line).with_msg(fmt("next {}", lex.tok())));
        lex.next();
    }

    void print(std::string msg, int line = __builtin_LINE()) {
        x_report(Print, .with_line(line).with_msg(msg));
    }


    void skip(BaseLexer& lex, obt kind, int line = __builtin_LINE()) {
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

    void pop_as(
        OrgTokenKind __to,
        Opt<obt>     expected = std::nullopt,
        int          line     = __builtin_LINE()) {
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


    IntSet<BaseTokenKind> EmptyToken{
        obt::Whitespace,
        obt::EndOfFile,
        obt::Newline,
        obt::MediumNewline,
        obt::LongNewline,
        obt::AnyPunct,
        obt::LeadingSpace,
    };

    void recombine_markup() {
        auto tr   = trace();
        auto prev = prev_token();
        auto next = next_token();
        switch (lex.kind()) {
            case obt::ForwardSlash:
            case obt::Equals:
            case obt::Plus:
            case obt::Asterisk: {
                otk open{};
                otk close{};

                switch (lex.kind()) {
                    case obt::Asterisk:
                        open  = otk::BoldBegin;
                        close = otk::BoldEnd;
                        break;
                    case obt::ForwardSlash:
                        open  = otk::ItalicBegin;
                        close = otk::ItalicEnd;
                        break;
                    case obt::Equals:
                        open  = otk::VerbatimBegin;
                        close = otk::VerbatimEnd;
                        break;
                    case obt::Plus:
                        open  = otk::StrikeBegin;
                        close = otk::StrikeEnd;
                        break;
                    default: break;
                }


                bool prev_empty = !prev || EmptyToken.contains(prev->kind);
                bool next_empty = !next || EmptyToken.contains(next->kind);

                print(
                    fmt("prev kind {} next kind {}",
                        prev ? prev->kind : obt::Unknown,
                        next ? next->kind : obt::Unknown));

                if (prev_empty && !next_empty) {
                    add_fake(open, {lex.tok().value});
                    lex.next();
                } else if (!prev_empty && next_empty) {
                    add_fake(close, {lex.tok().value});
                    lex.next();
                } else {
                    pop_as(otk::Punctuation);
                }

                break;
            }
            default: {
                LOG(FATAL) << fmt(
                    "Unexpected kind of the markup recombine input {}",
                    lex.kind());
            }
        }
    }

    const IntSet<BaseTokenKind> tree_tags{
        obt::Colon,
        obt::Word,
        obt::DoubleHash,
    };


    void map_open_brace() {
        auto tr   = trace();
        auto prev = lex.opt(-1);
        if (prev && prev->get().kind == obt::HashIdent) {
            pop_as(otk::HashTagBegin);
        } else if (auto date = lex.opt(+1);
                   date && date->get().kind == obt::Date) {
            pop_as(otk::BraceBegin);
            pop_as(otk::StaticTimeDatePart, obt::Date);
            // maybe day in  [yyyy-mm-dd Mon hh:mm:ss]
            if (lex.at(Vec{obt::Whitespace, obt::Word})) {
                skip(lex, obt::Whitespace);
                skip(lex, obt::Word);
            }

            if (lex.at(Vec{obt::Whitespace, obt::Time})) {
                skip(lex, obt::Whitespace);
                pop_as(otk::StaticTimeClockPart);
            }

            if (lex.at(Vec{obt::Whitespace, obt::Plus, obt::Number})) {
                next(lex);
                next(lex);
                pop_as(otk::Number);
            }

            pop_as(otk::BraceEnd, obt::BraceClose);
        } else if (auto time = lex.opt(+1);
                   time && time->get().kind == obt::Time) {
            pop_as(otk::BraceBegin);
            pop_as(otk::StaticTimeDatePart, obt::Time);
            if (lex.at(Vec{obt::Whitespace, obt::Plus, obt::Number})) {
                next(lex);
                next(lex);
                pop_as(otk::Number);
            }
            pop_as(otk::BraceEnd, obt::BraceClose);
        } else {
            pop_as(otk::BraceBegin);
        }
    }

    void map_line_command() {
        auto next = lex.tok(+1);
        pop_as(otk::CmdPrefix);
        switch (next.kind) {
            case obt::CmdCenterBegin: pop_as(otk::CmdCenterBegin); break;
            case obt::CmdCenterEnd: pop_as(otk::CmdCenterEnd); break;
            case obt::CmdSrcBegin: pop_as(otk::CmdSrcBegin); break;
            case obt::CmdTitle: pop_as(otk::CmdTitle); break;
            case obt::CmdCaption: pop_as(otk::CmdCaption); break;
            case obt::CmdFiletags: pop_as(otk::CmdFiletags); break;
            case obt::CmdColumns: pop_as(otk::CmdColumns); break;
            case obt::CmdQuoteBegin: pop_as(otk::CmdQuoteBegin); break;
            case obt::CmdQuoteEnd: pop_as(otk::CmdQuoteEnd); break;
            case obt::CmdExampleBegin: pop_as(otk::CmdExampleBegin); break;
            case obt::CmdExampleEnd: pop_as(otk::CmdExampleEnd); break;
            case obt::CmdExportBegin: pop_as(otk::CmdExportBegin); break;
            case obt::CmdExportEnd: pop_as(otk::CmdExportEnd); break;
            case obt::CmdPropertyArgs: {
                auto split = next->text.split(' ');
                add_fake(
                    otk::CmdPropertyArgs,
                    OrgFill{.base = BaseFill{.text = split.at(0)}});
                add_fake(
                    otk::CmdValue,
                    OrgFill{.base = BaseFill{.text = split.at(1)}});
                lex.next();
                break;
            }
            case obt::CmdPropertyText: pop_as(otk::CmdPropertyText); break;
            case obt::CmdPropertyRaw: pop_as(otk::CmdPropertyRaw); break;
            case obt::CmdOptions: pop_as(otk::CmdOptions); break;
            default: {
                LOG(FATAL) << fmt(
                    "Unhandled line command conversion rules {}", next);
            }
        }

        switch (next.kind) {
            case obt::CmdExampleBegin:
            case obt::CmdExportBegin:
            case obt::CmdSrcBegin: {
                map_command_args();
                break;
            }

            case obt::CmdPropertyArgs: {
                map_command_args();
                break;
            }


            case obt::CmdTitle:
                while (lex.at(obt::Whitespace)) { lex.next(); }
                break;
            case obt::CmdPropertyText:
                pop_as(otk::CmdValue);
                while (!lex.at(line_end)) { map_interpreted_token(); }
                break;
            default:
        }

        switch (next.kind) {
            case obt::CmdSrcBegin:
                add_fake(otk::CmdContentBegin);
                if (lex.at(line_end)) { lex.next(); }
                break;
            default:
        }
    }

    IntSet<BaseTokenKind> HashTagTokens{
        obt::DoubleHash,
        obt::BraceOpen,
        obt::BraceClose,
        obt::Whitespace,
        obt::Indent,
    };

    void map_command_args() {
        while (!line_end.contains(lex.kind())) {
            switch (lex.kind()) {
                case obt::CmdColonIdent: pop_as(otk::CmdKey); break;
                case obt::CmdRawArg:
                case obt::CmdIdent: pop_as(otk::CmdValue); break;
                case obt::Whitespace: lex.next(); break;
                default: {
                    LOG(FATAL) << fmt(
                        "Unhandled command argument kind {}", lex.kind());
                }
            }
        }
    }

    void map_interpreted_token() {
        auto               __trace  = trace("", __LINE__, "[map]");
        BaseTokenId        start    = lex.pos;
        BaseToken const&   tok      = lex.tok();
        BaseFill const&    val      = tok.value;
        std::string const& str      = tok.value.text;
        auto               map_kind = lex.kind();

        switch (map_kind) {
            case obt::Comma: pop_as(otk::Comma); break;
            case obt::Colon: pop_as(otk::Colon); break;
            case obt::BraceOpen: map_open_brace(); break;
            case obt::LeadingMinus: pop_as(otk::ListItemBegin); break;
            case obt::LeadingSpace: lex.next(); break;
            case obt::Minus: pop_as(otk::Punctuation); break;
            case obt::LineCommand: map_line_command(); break;
            case obt::TreePropertyLiteral: pop_as(otk::PropRawKey); break;
            case obt::TreePropertyText: pop_as(otk::PropTextKey); break;
            case obt::TreePropertyLogbook:
                pop_as(otk::ColonLogbook);
                break;
            case obt::DoubleHash: pop_as(otk::HashTagSub); break;
            case obt::CmdIdent: pop_as(otk::Word); break;

            case obt::DoubleSlash: pop_as(otk::DoubleSlash); break;
            case obt::TimeArrow: pop_as(otk::TimeArrow); break;
            case obt::TreeClock: pop_as(otk::ListClock); break;
            case obt::Comment: pop_as(otk::Comment); break;
            case obt::Indent: pop_as(otk::Indent); break;
            case obt::Dedent: pop_as(otk::Dedent); break;
            case obt::SameIndent: pop_as(otk::SameIndent); break;
            case obt::ListStart: pop_as(otk::ListBegin); break;
            case obt::ListEnd: pop_as(otk::ListEnd); break;
            case obt::StmtListOpen: pop_as(otk::StmtListBegin); break;
            case obt::ListItemEnd: pop_as(otk::ListItemEnd); break;
            case obt::SrcContent: pop_as(otk::CodeText); break;
            case obt::CmdExampleLine: pop_as(otk::RawText); break;
            case obt::Ampersand: pop_as(otk::Punctuation); break;
            case obt::AnyPunct: pop_as(otk::Punctuation); break;
            case obt::Symbol: pop_as(otk::SymbolBegin); break;
            case obt::TreePropertyProperties:
                pop_as(otk::ColonProperties);
                break;

            case obt::TreePropertyEnd: pop_as(otk::ColonEnd); break;
            case obt::RawText: pop_as(otk::RawText); break;
            // On top level, base tokens like `2020-01-10` are not
            // registered as proper timestamp elements and are converted to
            // the regular words.
            case obt::Number: pop_as(otk::Word); break;
            // FIXME why two tokens of the same kind?
            case obt::Date: pop_as(otk::Word); break;
            case obt::Percent: pop_as(otk::Punctuation); break;
            // FIXME Some weird name transitions here, cleanup later
            case obt::LeftPar: pop_as(otk::ParBegin); break;
            case obt::RightPar: pop_as(otk::ParEnd); break;
            // When not used in the timestamps, these are just pieces of
            // punctuation
            case obt::BraceClose: pop_as(otk::BraceEnd); break;
            case obt::MacroBegin: pop_as(otk::MacroBegin); break;
            case obt::MacroEnd: pop_as(otk::MacroEnd); break;
            case obt::At: pop_as(otk::AtMention); break;
            case obt::FootnoteBegin: pop_as(otk::FootnoteBegin); break;
            case obt::TextSeparator: pop_as(otk::TextSeparator); break;
            case obt::SingleQuote: pop_as(otk::Punctuation); break;
            case obt::DoubleDash: pop_as(otk::TimeDash); break;
            case obt::Time: pop_as(otk::TimeDuration); break;
            case obt::Semicolon: pop_as(otk::Punctuation); break;
            case obt::MiscUnicode: pop_as(otk::Word); break;
            case obt::Whitespace: pop_as(otk::Space); break;
            case obt::MediumNewline: pop_as(otk::MediumNewline); break;
            case obt::LongNewline: pop_as(otk::LongNewline); break;
            case obt::Newline: pop_as(otk::Newline); break;
            case obt::CmdSrcBegin: pop_as(otk::CmdSrcBegin); break;


            case obt::CmdExampleEnd: {
                add_fake(otk::CmdPrefix);
                pop_as(otk::CmdExampleEnd);
                break;
            }

            case obt::CmdExportEnd: {
                add_fake(otk::CmdPrefix);
                pop_as(otk::CmdExportEnd);
                break;
            }

            case obt::CmdSrcEnd: {
                add_fake(otk::CmdPrefix);
                pop_as(otk::CmdSrcEnd);
                break;
            }


            case obt::HashIdent: pop_as(otk::HashTag); break;


            case obt::Plus:
            case obt::ForwardSlash:
            case obt::Equals:
            case obt::Asterisk: {
                recombine_markup();
                break;
            }

            case obt::Tilda: {
                pop_as(otk::MonospaceBegin);
                while (!(!lex.at(EmptyToken, -1) && lex.at(obt::Tilda))) {
                    pop_as(otk::RawText);
                }
                pop_as(otk::MonospaceEnd);
                break;
            }

            case obt::StmtListClose: {
                pop_as(otk::StmtListEnd);
                break;
            }

            case obt::EndOfFile: {
                lex.next();
                break;
            }

            case obt::Word: {
                pop_as(otk::Word);
                break;
            }


            case obt::SubtreeStars: {
                pop_as(otk::SubtreeStars);
                break;
            }

            case obt::LeftCurly: pop_as(otk::CurlyStart); break;
            case obt::RightCurly: pop_as(otk::CurlyEnd); break;
            case obt::EscapedChar: pop_as(otk::Escaped); break;
            case obt::LinkEnd: pop_as(otk::LinkEnd); break;
            case obt::DoubleQuote: pop_as(otk::Punctuation); break;
            case obt::LeftAngle: pop_as(otk::AngleBegin); break;
            case obt::RightAngle: pop_as(otk::AngleEnd); break;
            case obt::DoubleLeftAngle:
                pop_as(otk::DoubleAngleBegin);
                break;
            case obt::DoubleRightAngle: pop_as(otk::DoubleAngleEnd); break;


            case obt::LinkBegin: {
                add_fake(otk::LinkBegin);
                add_fake(otk::LinkTargetBegin);
                auto text = strip(
                    lex.val().text, CharSet{'['}, CharSet{']', '[', ':'});

                add_fake(otk::LinkProtocol, {BaseFill{.text = text}});
                lex.next();
                break;
            }

            case obt::DslLinkBegin:
            case obt::DslLink: {
                add_fake(otk::LinkBegin);
                add_fake(otk::LinkTargetBegin);
                auto text = strip(
                    lex.val().text, CharSet{'['}, CharSet{']', '['});

                auto split = text.split(':');

                add_fake(
                    otk::LinkProtocol, {BaseFill{.text = split.at(0)}});
                add_fake(
                    otk::LinkTarget,
                    {BaseFill{
                        .text = join(":", split.at(slice(1, 1_B)))}});

                lex.next();
                add_fake(otk::LinkTargetEnd);
                if (map_kind == obt::DslLink) { add_fake(otk::LinkEnd); }
                break;
            }


            default: {
                LOG(FATAL) << std::format(
                    "Unhanled kind for token conversion, got {}:{} {} "
                    "\"{}\", lexer context {}",
                    val.line,
                    val.col,
                    lex.kind(),
                    val.text,
                    lex);
                lex.next();
            }
        }
    }

    void recombine_impl() {
        while (lex.hasNext(0)) {
            BaseTokenId     start = lex.pos;
            BaseFill const& val   = lex.tok().value;

            map_interpreted_token();

            CHECK((lex.pos != start)) << std::format(
                "Non-terminating token conversion case, got kind '{}' "
                "text '{}' at id {} with no movement. This is a bug in "
                "the implementation -- we iterated over baseline tokens, "
                "but did not find where to map the item to. The lexer was "
                "{}",
                lex.kind(),
                val.text,
                lex.pos.format(),
                lex.printToString([](ColStream& os, BaseToken const& t) {
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

    Span<BaseToken> tokens;
    int             indent = 0;
    Kind            kind   = Kind::None;

    BOOST_DESCRIBE_CLASS(LineToken, (), (kind, tokens, indent), (), ());

    IntSet<BaseTokenKind> CmdBlockClose{
        obt::CmdSrcEnd,
        obt::CmdCenterEnd,
        obt::CmdExampleEnd,
        obt::CmdQuoteEnd,
        obt::CmdExportEnd,
    };

    IntSet<BaseTokenKind> CmdBlockOpen{
        obt::CmdCenterBegin,
        obt::CmdExportBegin,
        obt::CmdExampleBegin,
        obt::CmdSrcBegin,
        obt::CmdQuoteBegin,
    };

    IntSet<BaseTokenKind> CmdBlockLine{
        obt::CmdTitle,
        obt::CmdCaption,
        obt::CmdColumns,
        obt::CmdPropertyArgs,
        obt::CmdPropertyRaw,
        obt::CmdPropertyText,
        obt::CmdOptions,
        obt::CmdFiletags,
    };

    Opt<Kind> whichBlockLineKind(obt kind) {
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

    void setLineCommandKind(CR<Span<BaseToken>> tokens, int tokensOffset) {
        CR<BaseToken> current = tokens.at(tokensOffset);
        if (current.kind == obt::LineCommand) {
            if (auto next = whichBlockLineKind(
                    tokens.at(tokensOffset + 1).kind);
                next) {
                kind = *next;
            } else {
                LOG(FATAL)
                    << fmt("Unknown line command kind mapping {}, {}",
                           tokens.at(tokensOffset + 1),
                           tokens);
            }


        } else if (CmdBlockClose.contains(current.kind)) {
            kind = Kind::BlockClose;
        } else {
            LOG(FATAL) << fmt(
                "Expected line command or closing block, but got {}",
                current.kind);
        }
    }

    void setLeadingSpaceKind(CR<Span<BaseToken>> tokens) {
        if (auto next = tokens.get(1); next) {
            switch (next->get().kind) {
                case obt::TreeClock:
                case obt::Minus: kind = Kind::ListItem; break;

                case obt::TreePropertyEnd:
                case obt::TreePropertyText:
                case obt::TreePropertyProperties:
                case obt::TreePropertyLiteral:
                    kind = Kind::Property;
                    break;

                case obt::LineCommand:

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

    void updateForTokens() {
        CR<BaseToken> first = tokens.at(0);
        switch (first.kind) {
            case obt::LeadingSpace: {
                indent = first->text.length();
                setLeadingSpaceKind(tokens);
                break;
            }

            case obt::Minus: {
                if (auto next = tokens.get(1);
                    next && next->get().kind == obt::Whitespace) {
                    kind = Kind::ListItem;
                } else {
                    kind = Kind::Line;
                }
                break;
            }

            case obt::LeadingMinus:
            case obt::LeadingPlus: kind = Kind::ListItem; break;
            case obt::LineCommand: setLineCommandKind(tokens, 0); break;
            case obt::TreeClock: kind = Kind::ListItem; break;

            default: {
                kind = CmdBlockClose.contains(first.kind)
                         ? Kind::BlockClose
                         : Kind::Line;
                break;
            }
        }
    }

    void decreaseIndent(int level) {
        CHECK(level <= indent);
        if (indent == level) {
            tokens = Span<BaseToken>(tokens.begin() + 1, tokens.end());
            updateForTokens();
        }
        indent -= level;
    }

    LineToken(CR<Span<BaseToken>> tokens) : tokens(tokens) {
        updateForTokens();
    }
};


struct GroupToken {
    DECL_DESCRIBED_ENUM(Kind, Line, ListItem, Subtree, Properties);

    Span<LineToken> lines;
    Kind            kind;

    BOOST_DESCRIBE_CLASS(GroupToken, (), (kind, lines), (), ());

    int indent() const { return lines.at(0).indent; }
};

using LK = LineToken::Kind;
using GK = GroupToken::Kind;

template <std::random_access_iterator Iter>
auto make_span(Iter begin, Iter end) -> Span<typename Iter::value_type> {
    return Span<typename Iter::value_type>{
        &*begin, static_cast<int>(std::distance(begin, end))};
}

Vec<LineToken> to_lines(BaseLexer& lex) {
    Vec<LineToken> lines;
    auto const&    tokens = lex.in;
    auto           start  = tokens->begin();

    for (auto it = tokens->begin(); it != tokens->end(); ++it) {
        if (line_end.contains(it->kind)) {
            lines.push_back(LineToken{make_span(start, std::next(it))});
            start = std::next(it);
        }
    }

    if (start != tokens->end()) {
        lines.push_back(LineToken{make_span(start, tokens->end())});
    }

    return lines;
}


Vec<GroupToken> to_groups(Vec<LineToken>& lines) {
    Vec<GroupToken> groups;


    auto it             = lines.begin();
    auto end            = lines.end();
    int  stable_counter = 0;
    while (it != lines.end()) {
        auto nextline   = [&]() { ++it; };
        auto skip_block = [&]() {
            // LOG(INFO) << "SKIP BEGIN";
            while (it != end && it->kind != LK::BlockClose) { nextline(); }
            if (it != end) { nextline(); }
            // LOG(INFO) << "SKIP END";
        };

        IntSet<LK> regular_kinds{
            LK::IndentedLine, LK::BlockClose, LK::BlockOpen};

        auto start = it;
        nextline();
        switch (start->kind) {
            case LK::Line: {
                while (it != end && regular_kinds.contains(it->kind)) {
                    if (it->kind == LK::BlockOpen) {
                        skip_block();
                    } else {
                        nextline();
                    }
                }
                groups.push_back({make_span(start, it), GK::Line});
                break;
            }

            case LK::ListItem: {
                while (it != end && regular_kinds.contains(it->kind)
                       && start->indent <= it->indent) {
                    if (it->kind == LK::BlockOpen) {
                        skip_block();
                    } else {
                        nextline();
                    }
                }

                groups.push_back({make_span(start, it), GK::ListItem});

                break;
            }

            case LK::BlockOpen: {
                skip_block();
                groups.push_back({make_span(start, it), GK::Line});
                break;
            }

            case LK::Property: {
                while (it != end && it->kind == LK::Property) {
                    nextline();
                }
                groups.push_back({make_span(start, it), GK::Properties});
                break;
            }

            case LK::IndentedLine: {
                it               = start;
                int start_indent = start->indent;
                while (it != end && start_indent <= it->indent) {
                    it->decreaseIndent(start_indent);
                    ++it;
                }
                it = start;
                break;
            }

            default: {
                LOG(FATAL) << fmt(
                    "Unhandled line kind {} {}", start->kind, it->tokens);
            }
        }

        if (start != it) {
            stable_counter = 0;
        } else {
            ++stable_counter;
            CHECK(stable_counter < 2) << fmt(
                "No movement on the line kind {} stable_counter={} {}",
                it->kind,
                stable_counter,
                it->tokens);
        }
    }

    return groups;
}

void OrgTokenizer::recombine(BaseLexer& lex) {
    // Convert stream of leading space indentations into indent, dedent
    // and 'same indent' tokens.
    Vec<LineToken>  lines  = to_lines(lex);
    Vec<GroupToken> groups = to_groups(lines);
    BaseTokenGroup  regroup;
    Vec<int>        indentStack{};
    regroup.tokens.reserve(lex.in->size());

    auto add_fake = [&](BaseTokenKind kind,
                        int           line     = __builtin_LINE(),
                        char const*   function = __builtin_FUNCTION()) {
        auto idx = regroup.add(BaseToken{kind});
        print(
            lex,
            fmt("    [{:<3}] fake  {:<48} indents {:<32}",
                idx.getIndex(),
                fmt1(kind),
                fmt1(indentStack)),
            line,
            function);
    };

    auto add_base = [&](BaseToken const& tok,
                        int              line     = __builtin_LINE(),
                        char const*      function = __builtin_FUNCTION()) {
        auto idx = regroup.add(tok);
        print(
            lex,
            fmt("    [{:<3}] token {:<48} indents {:<32}",
                idx.getIndex(),
                fmt1(tok),
                fmt1(indentStack)),
            line,
            function);
    };

    if (TraceState) {
        std::stringstream ss;
        for (int gr_index = 0; gr_index < groups.size(); ++gr_index) {
            auto const& gr = groups.at(gr_index);
            ss << fmt(
                "[{}] group:{} indent {}\n",
                gr_index,
                gr.kind,
                gr.indent());
            for (int line_index = 0; line_index < gr.lines.size();
                 ++line_index) {
                auto const& line = gr.lines.at(line_index);
                ss << fmt(
                    "  [{}] line:{} indent={}\n",
                    line_index,
                    line.kind,
                    line.indent);
                for (int token_idx = 0; token_idx < line.tokens.size();
                     ++token_idx) {
                    ss << fmt(
                        "    [{}] {}\n",
                        token_idx,
                        line.tokens.at(token_idx));
                }
            }
        }

        print(lex, "\n" + ss.str());
    }

    for (auto gr_index = 0; gr_index < groups.size(); ++gr_index) {
        auto const& gr = groups.at(gr_index);
        print(
            lex,
            fmt("GROUP [{:<2}] indent={} kind={}",
                gr_index,
                gr.indent(),
                gr.kind));

        if (gr.kind == GK::ListItem) {
            if (indentStack.empty()) {
                add_fake(obt::ListStart);
                indentStack.push_back(gr.indent());
            } else if (indentStack.back() < gr.indent()) {
                add_fake(obt::StmtListClose);
                add_fake(obt::ListItemEnd);
                add_fake(obt::Indent);
                indentStack.push_back(gr.indent());
            } else if (gr.indent() < indentStack.back()) {
                while (!indentStack.empty()
                       && gr.indent() < indentStack.back()) {
                    add_fake(obt::StmtListClose);
                    add_fake(obt::ListItemEnd);
                    add_fake(obt::Dedent);
                    indentStack.pop_back();
                }
            } else if (indentStack.back() == gr.indent()) {
                add_fake(obt::StmtListClose);
                add_fake(obt::ListItemEnd);
                add_fake(obt::SameIndent);
            }

        } else if (!indentStack.empty()) {
            /* List item content can be indented like this, but
             * it will still be added to the current list content.
             * `indentStack.back() < gr.indent()` is not checked
             *
             * ```
             * - List Item
             *
             *   #+begin_src
             *
             *   #+end_src
             * ```
             */

            while (!indentStack.empty()
                   && gr.indent() <= indentStack.back()) {
                add_fake(obt::StmtListClose);
                add_fake(obt::ListItemEnd);
                indentStack.pop_back();

                if (indentStack.empty()) {
                    add_fake(obt::ListEnd);
                } else {
                    add_fake(obt::Dedent);
                }
            }
        }

        for (CR<LineToken> line : gr.lines) {
            print(
                lex,
                fmt("  LINE: indent={} kind={}", line.indent, line.kind));

            auto const& tokens = line.tokens;
            for (int tok_idx = 0; tok_idx < tokens.size(); ++tok_idx) {
                auto const& tok = tokens.at(tok_idx);
                switch (tok.kind) {
                    case obt::TreeClock:
                    case obt::Minus: {
                        // Is the first token on the line or preceded by
                        // leading space.
                        if ((tok_idx == 0
                             || tokens.get(tok_idx - 1).value().get().kind
                                    == obt::LeadingSpace)
                            && gr.kind == GK::ListItem) {
                            add_base((BaseToken{
                                tok.kind == obt::TreeClock
                                    ? obt::TreeClock
                                    : obt::LeadingMinus,
                                tok.value}));

                            if (auto next = tokens.get(tok_idx + 1);
                                next->get().kind == obt::Whitespace) {
                                add_base(next->get());
                                ++tok_idx;
                            }

                            add_fake(obt::StmtListOpen);
                        } else {
                            add_base(tok);
                        }
                        break;
                    }
                    case obt::LeadingMinus: {
                        add_base(tok);
                        if (auto next = tokens.get(tok_idx + 1);
                            next->get().kind == obt::Whitespace) {
                            add_base(next->get());
                            ++tok_idx;
                        }

                        if (gr.kind == GK::ListItem) {
                            add_fake(obt::StmtListOpen);
                        }
                        break;
                    }
                    default: {
                        add_base(tok);
                    }
                }
            }
        }
    }

    if (!indentStack.empty()) {
        for (auto const& _ : indentStack) {
            add_fake(obt::StmtListClose);
            add_fake(obt::ListItemEnd);
            indentStack.pop_back();
        }
        add_fake(obt::ListEnd);
    }


    Lexer<obt, BaseFill> relex{&regroup};
    RecombineState       recombine_state{this, relex};
    recombine_state.recombine_impl();
}

void OrgTokenizer::convert(BaseTokenGroup& input) {
    Lexer<BaseTokenKind, BaseFill> lex(&input);
    return convert(lex);
}

void OrgTokenizer::convert(BaseLexer& lex) {
    lex.pos = TokenId<BaseTokenKind, BaseFill>::FromValue(1);
    recombine(lex);
}

void OrgTokenizer::print(
    BaseLexer&         lex,
    const std::string& msg,
    int                line,
    const char*        function) {
    if (TraceState) {
        report(Builder(
                   lex,
                   OrgTokenizer::ReportKind::Print,
                   __FILE__,
                   line,
                   function)
                   .with_msg(msg)
                   .report);
    }
}
