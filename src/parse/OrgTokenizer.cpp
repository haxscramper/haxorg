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

    OrgFill loc_fill() {
        return OrgFill{
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
    };

    void recombine_markup() {
        auto tr   = trace();
        auto prev = prev_token();
        auto next = next_token();

        auto [open, close] = //
            UnorderedMap<otk, Pair<otk, otk>>{
                {otk::Asterisk, {otk::BoldBegin, otk::BoldEnd}},
                {otk::ForwardSlash, {otk::ItalicBegin, otk::ItalicEnd}},
                {otk::Equals, {otk::VerbatimBegin, otk::VerbatimEnd}},
                {otk::Plus, {otk::StrikeBegin, otk::StrikeEnd}},
                {otk::Tilda, {otk::MonospaceBegin, otk::MonospaceEnd}},
            }
                .at(lex.kind());


        bool prev_empty = !prev || EmptyToken.contains(prev->kind);
        bool next_empty = !next || EmptyToken.contains(next->kind);

        print(
            fmt("prev kind {} next kind {}",
                prev ? prev->kind : otk::Unknown,
                next ? next->kind : otk::Unknown));

        if (prev_empty && !next_empty) {
            add_fake(open, {lex.tok().value});
            lex.next();
        } else if (!prev_empty && next_empty) {
            add_fake(close, {lex.tok().value});
            lex.next();
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
            case otk::CmdCenterBegin: pop_as(otk::CmdCenterBegin); break;
            case otk::CmdCenterEnd: pop_as(otk::CmdCenterEnd); break;
            case otk::CmdSrcBegin: pop_as(otk::CmdSrcBegin); break;
            case otk::CmdTitle: pop_as(otk::CmdTitle); break;
            case otk::CmdCaption: pop_as(otk::CmdCaption); break;
            case otk::CmdFiletags: pop_as(otk::CmdFiletags); break;
            case otk::CmdColumns: pop_as(otk::CmdColumns); break;
            case otk::CmdQuoteBegin: pop_as(otk::CmdQuoteBegin); break;
            case otk::CmdQuoteEnd: pop_as(otk::CmdQuoteEnd); break;
            case otk::CmdExampleBegin: pop_as(otk::CmdExampleBegin); break;
            case otk::CmdExampleEnd: pop_as(otk::CmdExampleEnd); break;
            case otk::CmdExportBegin: pop_as(otk::CmdExportBegin); break;
            case otk::CmdExportEnd: pop_as(otk::CmdExportEnd); break;
            case otk::CmdPropertyArgs: {
                auto split = next->text.split(' ');
                add_fake(
                    otk::CmdPropertyArgs, OrgFill{.text = split.at(0)});
                add_fake(otk::CmdValue, OrgFill{.text = split.at(1)});
                lex.next();
                break;
            }
            case otk::CmdPropertyText: pop_as(otk::CmdPropertyText); break;
            case otk::CmdPropertyRaw: pop_as(otk::CmdPropertyRaw); break;
            case otk::CmdOptions: pop_as(otk::CmdOptions); break;
            default: {
                LOG(FATAL) << fmt(
                    "Unhandled line command conversion rules {}", next);
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
                pop_as(otk::CmdValue);
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
        while (!line_end.contains(lex.kind())) {
            switch (lex.kind()) {
                case otk::CmdColonIdent: pop_as(otk::CmdKey); break;
                case otk::CmdRawArg:
                case otk::CmdIdent: pop_as(otk::CmdValue); break;
                case otk::Whitespace: lex.next(); break;
                default: {
                    LOG(FATAL) << fmt(
                        "Unhandled command argument kind {}", lex.kind());
                }
            }
        }
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

            case otk::Plus:
            case otk::ForwardSlash:
            case otk::Equals:
            case otk::Tilda:
            case otk::Asterisk: {
                recombine_markup();
                break;
            }
            case otk::EndOfFile: {
                lex.next();
                break;
            }

            case otk::Word: {
                pop_as(otk::Word);
                break;
            }


            case otk::SubtreeStars: {
                pop_as(otk::SubtreeStars);
                break;
            }

            case otk::LinkBegin: {
                add_fake(otk::LinkBegin);
                add_fake(otk::LinkTargetBegin);
                auto text = strip(
                    lex.val().text, CharSet{'['}, CharSet{']', '[', ':'});

                add_fake(otk::LinkProtocol, OrgFill{.text = text});
                lex.next();
                break;
            }

            case otk::LinkSplit: {
                add_fake(otk::LinkTargetEnd);
                pop_as(otk::LinkDescriptionBegin);
                break;
            }

            case otk::DslLinkBegin:
            case otk::DslLink: {
                add_fake(otk::LinkBegin);
                add_fake(otk::LinkTargetBegin);
                auto text = strip(
                    lex.val().text, CharSet{'['}, CharSet{']', '['});

                auto split = text.split(':');

                add_fake(otk::LinkProtocol, OrgFill{.text = split.at(0)});
                add_fake(
                    otk::RawText,
                    OrgFill{.text = join(":", split.at(slice(1, 1_B)))});

                lex.next();
                add_fake(otk::LinkTargetEnd);
                if (map_kind == otk::DslLink) { add_fake(otk::LinkEnd); }
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

            CHECK((lex.pos != start)) << std::format(
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

    BOOST_DESCRIBE_CLASS(LineToken, (), (kind, tokens, indent), (), ());

    IntSet<OrgTokenKind> CmdBlockClose{
        otk::CmdSrcEnd,
        otk::CmdCenterEnd,
        otk::CmdExampleEnd,
        otk::CmdQuoteEnd,
        otk::CmdExportEnd,
    };

    IntSet<OrgTokenKind> CmdBlockOpen{
        otk::CmdCenterBegin,
        otk::CmdExportBegin,
        otk::CmdExampleBegin,
        otk::CmdSrcBegin,
        otk::CmdQuoteBegin,
    };

    IntSet<OrgTokenKind> CmdBlockLine{
        otk::CmdTitle,
        otk::CmdCaption,
        otk::CmdColumns,
        otk::CmdPropertyArgs,
        otk::CmdPropertyRaw,
        otk::CmdPropertyText,
        otk::CmdOptions,
        otk::CmdFiletags,
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

    void setLeadingSpaceKind(CR<Span<OrgToken>> tokens) {
        if (auto next = tokens.get(1); next) {
            switch (next->get().kind) {
                case otk::TreeClock:
                case otk::Minus: kind = Kind::ListItem; break;

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

    void updateForTokens() {
        CR<OrgToken> first = tokens.at(0);
        switch (first.kind) {
            case otk::LeadingSpace: {
                indent = first->text.length();
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

    void decreaseIndent(int level) {
        CHECK(level <= indent);
        if (indent == level) {
            tokens = Span<OrgToken>(tokens.begin() + 1, tokens.end());
            updateForTokens();
        }
        indent -= level;
    }

    LineToken(CR<Span<OrgToken>> tokens) : tokens(tokens) {
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

Vec<LineToken> to_lines(OrgLexer& lex) {
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

void OrgTokenizer::recombine(OrgLexer& lex) {
    // Convert stream of leading space indentations into indent, dedent
    // and 'same indent' tokens.
    Vec<LineToken>  lines  = to_lines(lex);
    Vec<GroupToken> groups = to_groups(lines);
    OrgTokenGroup   regroup;
    Vec<int>        indentStack{};
    regroup.tokens.reserve(lex.in->size());

    auto add_fake = [&](OrgTokenKind kind,
                        int          line     = __builtin_LINE(),
                        char const*  function = __builtin_FUNCTION()) {
        auto idx = regroup.add(OrgToken{kind});
        print(
            lex,
            fmt("    [{:<3}] fake  {:<48} indents {:<32}",
                idx.getIndex(),
                fmt1(kind),
                fmt1(indentStack)),
            line,
            function);
    };

    auto add_base = [&](OrgToken const& tok,
                        int             line     = __builtin_LINE(),
                        char const*     function = __builtin_FUNCTION()) {
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
                add_fake(otk::ListBegin);
                indentStack.push_back(gr.indent());
            } else if (indentStack.back() < gr.indent()) {
                add_fake(otk::StmtListBegin);
                add_fake(otk::ListItemEnd);
                add_fake(otk::Indent);
                indentStack.push_back(gr.indent());
            } else if (gr.indent() < indentStack.back()) {
                while (!indentStack.empty()
                       && gr.indent() < indentStack.back()) {
                    add_fake(otk::StmtListEnd);
                    add_fake(otk::ListItemEnd);
                    add_fake(otk::Dedent);
                    indentStack.pop_back();
                }
            } else if (indentStack.back() == gr.indent()) {
                add_fake(otk::StmtListEnd);
                add_fake(otk::ListItemEnd);
                add_fake(otk::SameIndent);
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
                add_fake(otk::StmtListEnd);
                add_fake(otk::ListItemEnd);
                indentStack.pop_back();

                if (indentStack.empty()) {
                    add_fake(otk::ListEnd);
                } else {
                    add_fake(otk::Dedent);
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
                    case otk::TreeClock:
                    case otk::Minus: {
                        // Is the first token on the line or preceded by
                        // leading space.
                        if ((tok_idx == 0
                             || tokens.get(tok_idx - 1).value().get().kind
                                    == otk::LeadingSpace)
                            && gr.kind == GK::ListItem) {
                            add_base(tok);

                            if (auto next = tokens.get(tok_idx + 1);
                                next->get().kind == otk::Whitespace) {
                                add_base(next->get());
                                ++tok_idx;
                            }

                            add_fake(otk::StmtListBegin);
                        } else {
                            add_base(tok);
                        }
                        break;
                    }

                    case otk::LeadingNumber:
                    case otk::LeadingMinus: {
                        add_base(tok);
                        if (auto next = tokens.get(tok_idx + 1);
                            next->get().kind == otk::Whitespace) {
                            add_base(next->get());
                            ++tok_idx;
                        }

                        if (gr.kind == GK::ListItem) {
                            add_fake(otk::StmtListBegin);
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
            add_fake(otk::StmtListEnd);
            add_fake(otk::ListItemEnd);
            indentStack.pop_back();
        }
        add_fake(otk::ListEnd);
    }


    Lexer<OrgTokenKind, OrgFill> relex{&regroup};
    RecombineState               recombine_state{this, relex};
    recombine_state.recombine_impl();
}

void OrgTokenizer::convert(OrgTokenGroup& input) {
    Lexer<OrgTokenKind, OrgFill> lex(&input);
    return convert(lex);
}

void OrgTokenizer::convert(OrgLexer& lex) {
    lex.pos = TokenId<OrgTokenKind, OrgFill>::FromValue(1);
    recombine(lex);
}

void OrgTokenizer::print(
    OrgLexer&          lex,
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
