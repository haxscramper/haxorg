#include "OrgTokenizer.hpp"

#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/wrappers/perfetto_aux.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <hstd/stdlib/Ranges.hpp>

#include "OrgTokenizerMacros.hpp"

namespace rep {
struct Builder {
    OrgTokenizer::Report report;

    Builder& with_msg(Str const& msg) {
        report.msg = msg;
        return *this;
    }

    Builder& with_name(Str const& name) {
        report.name = name;
        return *this;
    }


    Builder(
        BaseLexer&               lex,
        OrgTokenizer::ReportKind kind,
        fs::path   location = fs::path{__builtin_FILE_NAME()},
        int        line     = __builtin_LINE(),
        Str const& function = __builtin_FUNCTION()) {
        this->report = OrgTokenizer::Report{
            .location = location,
            .line     = line,
            .name     = function,
            .lex      = &lex,
            .kind     = kind,
        };
    }
};

#define x_trace(...)                                                      \
    if (TraceState) {                                                     \
        this->report(                                                     \
            (::rep::Builder(lex, OrgTokenizer::ReportKind::Enter)         \
                 __VA_ARGS__)                                             \
                .report);                                                 \
    }                                                                     \
                                                                          \
    finally CONCAT(close, __COUNTER__) = finally::init<Str>(              \
        ([&](CR<Str> name) {                                              \
            if (TraceState) {                                             \
                this->report(((::rep::Builder(                            \
                                   lex, OrgTokenizer::ReportKind::Leave)  \
                                   __VA_ARGS__)                           \
                                  .with_name(name))                       \
                                 .report);                                \
            }                                                             \
        }),                                                               \
        Str(__func__));


} // namespace rep

using ock = OrgCommandKind;
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

DECL_DESCRIBED_ENUM_STANDALONE(
    State,
    None,
    Paragraph,
    RawMonospace,
    Subtree);
DECL_DESCRIBED_ENUM_STANDALONE(
    MarkKind,
    Bold,
    Italic,
    Markup,
    Parens,
    Curly,
    Verbatim,
    Quotes);


OrgFill fill(BaseLexer& lex) { return OrgFill{.base = lex.tok().value}; }


namespace {

struct RecombineState {
    OrgTokenizer* d;
    struct Mark {
        MarkKind   kind;
        OrgTokenId set;
    };

    Vec<Mark>   mark;
    Vec<State>  state;
    BaseLexer&  lex;
    bool const& TraceState;

    void report(OrgTokenizer::Report const& report) { d->report(report); }


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


    void state_push(State value) { state.push_back(value); };

    State state_top() {
        return state.empty() ? State::None : state.back();
    };

    State state_pop() {
        return state.empty() ? State::None : state.pop_back_v();
    };

    // Push new markup token from the current lexer position and
    // remember the opening location in the stack.
    void mark_push(MarkKind value, OrgTokenKind __to) {
        OrgTokenId added = add_as(__to);
        mark.push_back(Mark{.kind = value, .set = added});
        lex.next();
    };

    // Get top known markup token from the stack of markup openings
    Opt<Mark> mark_top() {
        return mark.empty() ? std::nullopt : Opt<Mark>(mark.back());
    };

    // Finalize the markup token pair
    Opt<Mark> mark_pop(MarkKind value, OrgTokenKind __to) {
        add_as(__to);
        lex.next();
        CHECK(!mark.empty())
            << "Expected the markup stack to not be empty";
        CHECK(mark.back().kind == value)
            << fmt("Expected markup stack to have value {} but top is {}. "
                   "Pushed from {}",
                   fmt1(value),
                   mark.back().kind,
                   mark.back().set);

        return mark.empty() ? std::nullopt : Opt<Mark>(mark.pop_back_v());
    };

    void mark_toggle(MarkKind value, OrgTokenKind to) {
        // Check if there has already been an opening markup token
        // somewhere in the stack.
        if (std::any_of(mark.begin(), mark.end(), [&value](Mark const& m) {
                return m.kind == value;
            })) {
            if (mark.back().kind == value) {
                // If it is the last one, then close it properly
                mark_pop(value, to);
            } else {
                // If it is something internal, it means there is an
                // unbalanced content, like `{[}` -- opening `[` will add
                // something to the stack, but surrounding `{}` would not
                // allow the proper tree to be formed.
                CHECK(false) << "TODO FAIL";
            }
        } else {
            mark_push(value, to);
        }
    }

    OrgTokenId add_as(OrgTokenKind __to) {
        return d->out->add(OrgToken{__to, fill(lex)});
    }

    void pop_as(OrgTokenKind __to) {
        add_as(__to);
        lex.next();
    }

    OrgTokenId add_fake(OrgTokenKind __to) {
        return d->out->add(OrgToken{__to});
    }

    void recombine_markup() {
        __trace();
        // TODO Check if we are in the paragraph element or some other
        // place.
        auto prev = prev_token();
        auto next = next_token();
        switch (lex.kind()) {
            case obt::ForwardSlash:
            case obt::Equals:
            case obt::Asterisk: {
                MarkKind mark{};
                otk      open{};
                otk      close{};

                switch (lex.kind()) {
                    case obt::Asterisk:
                        mark  = MarkKind::Bold;
                        open  = otk::BoldClose;
                        close = otk::BoldClose;
                        break;
                    case obt::ForwardSlash:
                        mark  = MarkKind::Italic;
                        open  = otk::ItalicOpen;
                        close = otk::ItalicClose;
                        break;
                    case obt::Equals:
                        mark  = MarkKind::Verbatim;
                        open  = otk::VerbatimOpen;
                        close = otk::VerbatimClose;
                        break;
                    default: break;
                }

                IntSet<BaseTokenKind> EmptyToken{
                    obt::Whitespace,
                    obt::EndOfFile,
                    obt::Newline,
                    obt::MediumNewline,
                    obt::LongNewline,
                    obt::AnyPunct,
                };

                bool prev_empty = !prev || EmptyToken.contains(prev->kind);
                bool next_empty = !next || EmptyToken.contains(next->kind);

                if (prev_empty && !next_empty) {
                    mark_toggle(mark, open);
                } else if (!prev_empty && next_empty) {
                    mark_toggle(mark, close);
                } else {
                    pop_as(otk::Punctuation);
                }

                break;
            }
            default: {
                CHECK(false) << fmt(
                    "Unexpected kind of the markup recombine input {}",
                    lex.kind());
            }
        }
    }

#define direct(__from, __to)                                              \
    case __from: {                                                        \
        pop_as(__to);                                                     \
        break;                                                            \
    }


    const IntSet<BaseTokenKind> tree_tags{
        obt::Colon,
        obt::Word,
        obt::DoubleHash,
    };

    const IntSet<BaseTokenKind> line_end{
        obt::Newline,
        obt::MediumNewline,
        obt::LongNewline,
        obt::EndOfFile,
    };


    void map_open_brace() {
        if (lex.hasNext(-1)) {
            switch (lex.tok(-1).kind) {
                case obt::HashIdent: pop_as(otk::HashTagOpen); break;
                default: pop_as(otk::Punctuation);
            }
            // } else if (lex.at(obt::BraceOpen, +1)) {

        } else {
            pop_as(otk::Punctuation);
        }
    }

    void map_colon() {
        __trace();
        auto const& state_1 = state.get(1_B);
        auto const& state_2 = state.get(2_B);
        if (state_1 && state_2 && state_1.value() == State::Paragraph
            && state_2.value() == State::Subtree) {


            auto ahead = lex.whole_fixed().range()
                       | rv::take_while([&](BaseToken const& t) -> bool {
                             return tree_tags.contains(t.kind);
                         })
                       | rs::to<std::vector>;

            LOG(INFO) << fmt("Tokens ahead for subtree {}", ahead);

            if (line_end.contains((lex.begin() + ahead.size())->kind)) {
                while (!line_end.contains(lex.kind())) {
                    switch (lex.kind()) {
                        case obt::Colon:
                            pop_as(otk::SubtreeTagSeparator);
                            break;
                        case obt::Word: pop_as(otk::HashTag); break;
                        case obt::DoubleHash: pop_as(otk::HashTag); break;
                        default:
                    }
                }
            } else {
                pop_as(otk::Colon);
            }

        } else {
            pop_as(otk::Colon);
        }
    }

    void maybe_paragraph_start() {
        bool matching_state = state_top() == State::None
                           || state_top() == State::Subtree;

        x_trace(.with_msg(fmt("match:{}", matching_state)));

        if (matching_state) {
            add_fake(otk::ParagraphStart);
            state_push(State::Paragraph);
        }
    }

    void maybe_paragraph_end() {
        __trace();
        if (state_top() == State::Paragraph) {
            add_fake(otk::ParagraphEnd);
            state_pop();
        }
    }

    IntSet<BaseTokenKind> HashTagTokens{
        obt::DoubleHash,
        obt::BraceOpen,
        obt::BraceClose,
        obt::Whitespace,
        obt::Indent,
    };

    void map_hashtag() {
        LOG(INFO) << "Trace state " << TraceState;
        if (lex.hasNext(+1)) {
            if (opt_equal_kind(lex.opt(+1), obt::DoubleHash)) {
                pop_as(otk::HashTag);
                auto while_tag = lex.whole().range()
                               | rv::take_while(
                                     [&](BaseToken const& tok) -> bool {
                                         return HashTagTokens.contains(
                                             tok.kind);
                                     });

                // TODO minimize size of the range ahead by
                // dropping unnecessary tokens, counting balancing
                // elements in the tree.

                for (auto const& tok : while_tag) {
                    switch (lex.kind()) {
                        case obt::BraceOpen:
                            pop_as(otk::HashTagOpen);
                            break;
                        case obt::BraceClose:
                            pop_as(otk::HashTagClose);
                            break;
                        case obt::Word: pop_as(otk::HashTag); break;
                        case obt::DoubleHash:
                            pop_as(otk::HashTagSub);
                            break;
                        case obt::Whitespace:
                            pop_as(otk::SkipSpace);
                            break;
                        default:
                    }
                }

            } else {
                pop_as(otk::HashTag);
            }
        } else {
            pop_as(otk::HashTag);
        }
    }

    void map_interpreted_token() {
        x_trace(.with_msg(std::format("state: {}", state)));
        BaseTokenId        start = lex.pos;
        BaseToken const&   tok   = lex.tok();
        BaseFill const&    val   = tok.value;
        std::string const& str   = tok.value.text;

        switch (lex.kind()) {
            direct(obt::Ampersand, otk::Punctuation);
            direct(obt::Whitespace, otk::Space);
            direct(obt::AnyPunct, otk::Punctuation);
            direct(obt::Newline, otk::Newline);
            direct(obt::Comment, otk::Comment);

            case obt::HashIdent: {
                maybe_paragraph_start();
                map_hashtag();
                break;
            }

            case obt::Colon: {
                map_colon();
                break;
            }

            case obt::ForwardSlash:
            case obt::Equals:
            case obt::Asterisk: {
                maybe_paragraph_start();
                recombine_markup();
                break;
            }

            case obt::Tilda: {
                if (state_top() == State::RawMonospace) {
                    state_pop();
                } else {
                    state_push(State::RawMonospace);
                }
                lex.next();
                break;
            }

            case obt::EndOfFile: {
                while (!state.empty()) {
                    switch (state_top()) {
                        case State::Paragraph: {
                            add_fake(otk::ParagraphEnd);
                            break;
                        }
                        case State::Subtree: {
                            add_fake(otk::SubtreeEnd);
                            break;
                        }
                        case State::None: {
                            break;
                        }
                        default: {
                            CHECK(false) << fmt(
                                "Encountered end of file while state "
                                "stack was not completely closed, the "
                                "top element was {}. Expected 'none' "
                                "or 'paragraph'.",
                                state_top());
                        }
                    }
                    state_pop();
                }
                lex.next();
                break;
            }

            case obt::Word: {
                maybe_paragraph_start();
                pop_as(otk::Word);
                break;
            }

            case obt::MediumNewline: {
                maybe_paragraph_end();
                pop_as(otk::SkipNewline);
                break;
            }

            case obt::BraceOpen: {
                map_open_brace();
                break;
            }

            case obt::SubtreeStars: {
                state_push(State::Subtree);
                pop_as(otk::SubtreeStars);
                break;
            }

            case obt::LeadingMinus: {
                pop_as(otk::ListStart);
                break;
            }

            default: {
                DLOG(ERROR) << std::format(
                    "Unhanled kind for token conversion, got {}:{} {} "
                    "\"{}\", top state was {}, lexer context {}",
                    val.line,
                    val.col,
                    lex.kind(),
                    val.text,
                    state_top(),
                    lex);
                lex.next();
            }
        }
    }

    void recombine_impl() {
        while (lex.hasNext(0)) {
            BaseTokenId     start = lex.pos;
            BaseFill const& val   = lex.tok().value;

            if (state_top() == State::RawMonospace
                && lex.kind() != obt::Tilda) {
                pop_as(otk::RawText);

            } else {
                map_interpreted_token();
            }

            CHECK((lex.pos != start)) << std::format(
                "Non-terminating token conversion case, got kind '{}' "
                "text '{}' at id {} with no movement. This is a bug in "
                "the implementation -- we iterated over baseline tokens, "
                "but did not find where to map the item to. The current "
                "conversion state top is {} and the lexer was {}",
                lex.kind(),
                val.text,
                lex.pos.format(),
                state_top(),
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
        Line,
        ListItem,
        Subtree,
        BlockOpen,
        BlockClose,
        IndentedLine,
        Property);

    Span<BaseToken> tokens;
    int             indent = 0;
    Kind            kind;
};

struct GroupToken {
    DECL_DESCRIBED_ENUM(
        Kind,
        Line,
        ListItem,
        Block,
        Content,
        Subtree,
        Properties);

    Span<LineToken> lines;
    Kind            kind;
};

template <std::random_access_iterator Iter>
auto make_span(Iter begin, Iter end) -> Span<typename Iter::value_type> {
    return Span<typename Iter::value_type>{
        &*begin, static_cast<int>(std::distance(begin, end))};
}

Vec<LineToken> to_lines(BaseLexer& lex) {
    Vec<LineToken> lines;
    {
        auto const& tokens = lex.in;
        auto        start  = tokens->begin();

        for (auto it = tokens->begin(); it != tokens->end(); ++it) {
            if (it->kind == BaseTokenKind::Newline) {
                lines.push_back(LineToken{make_span(start, it)});
                start = std::next(it);
            }
        }

        if (start != tokens->end()) {
            lines.push_back(LineToken{make_span(start, tokens->end())});
        }
    }

    for (auto& gr : lines) {
        CR<BaseToken> first = gr.tokens.at(0);
        switch (first.kind) {
            case obt::LeadingSpace:
                gr.indent = first->text.length();
                if (auto next = gr.tokens.get(1);
                    next && next->get().kind == obt::Minus) {
                    gr.kind = LineToken::Kind::ListItem;
                } else {
                    gr.kind = LineToken::Kind::IndentedLine;
                }
                break;
            case obt::LeadingMinus:
            case obt::LeadingPlus:
                gr.kind = LineToken::Kind::ListItem;
                break;

            default: break;
        }
    }

    return lines;
}

using LK = LineToken::Kind;
using GK = GroupToken::Kind;

Vec<GroupToken> to_groups(Vec<LineToken>& lines) {
    Vec<GroupToken> groups;


    auto it  = lines.begin();
    auto end = lines.end();
    while (it != lines.end()) {
        auto start = it;
        ++it;
        switch (start->kind) {
            case LK::Line: {
                while (it != end && it->kind == LK::Line) { ++it; }
                groups.push_back({make_span(start, it), GK::Line});
            }
            case LK::ListItem: {
                while (it != end && it->kind == LK::IndentedLine
                       && start->indent <= it->indent) {
                    ++it;
                }

                groups.push_back({make_span(start, it), GK::ListItem});

                break;
            }

            case LK::BlockOpen: {
                while (it != end && it->kind != LK::BlockClose) { ++it; }
                groups.push_back({make_span(start, it), GK::Block});
                break;
            }
        }

        CHECK(start != it)
            << fmt("No movement on the line kind {}", it->kind);
    }

    return groups;
}

void OrgTokenizer::recombine(BaseLexer& lex) {
    // Convert stream of leading space indentations into indent, dedent
    // and 'same indent' tokens.
    Vec<LineToken>  lines  = to_lines(lex);
    Vec<GroupToken> groups = to_groups(lines);


    BaseTokenGroup regroup;
    regroup.tokens.reserve(lex.in->size());
    for (CR<GroupToken> gr : groups) {
        for (CR<LineToken> line : gr.lines) {
            for (CR<BaseToken> tok : line.tokens) {
                switch (tok.kind) {
                    default: {
                        regroup.add(tok);
                    }
                }
            }
        }
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
