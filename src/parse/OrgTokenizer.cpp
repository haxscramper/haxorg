#include "OrgTokenizer.hpp"

import hstd.stdlib.algorithms;
import hstd.stdlib.Debug;
import std.wrappers.perfetto_aux;

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
import hstd.stdlib.Ranges;

using ock = OrgCommandKind;
using otk = OrgTokenKind;
using obt = BaseTokenKind;

void OrgTokenizer::rewriteIndents(BaseLexer& lex) {
    while (lex.hasNext()) {
        lex.next();
    }
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

    Vec<Mark>  mark;
    Vec<State> state;
    BaseLexer& lex;


    RecombineState(OrgTokenizer* d, BaseLexer& lex) : d(d), lex(lex) {}

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
        (void)add_as(__to);
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
        (void)add_as(__to);
        lex.next();
    }

    OrgTokenId add_fake(OrgTokenKind __to) {
        return d->out->add(OrgToken{__to});
    }

    void recombine_markup() {
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

                if (prev && next) {
                    if (prev->kind == obt::Whitespace
                        && next->kind == obt::Word) {
                        mark_toggle(mark, open);
                    } else if (
                        prev->kind == obt::Word
                        && in_set(
                            next->kind, obt::Asterisk, obt::Whitespace)) {
                        mark_toggle(mark, close);
                    } else {
                        LOG(INFO) << fmt("prev={} next={}", prev, next);
                    }

                } else if (!prev) {
                    mark_push(mark, open);

                } else if (!next) {
                    mark_push(mark, close);

                } else {
                    LOG(WARNING) << "Not mapped markup recombination";
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

    void map_interpreted_token() {
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
            direct(obt::HashIdent, otk::HashTag);

            case obt::Colon: {
                map_colon();
                break;
            }

            case obt::ForwardSlash:
            case obt::Equals:
            case obt::Asterisk: {
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
                            (void)add_fake(otk::ParagraphEnd);
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
                if (state_top() == State::None) {
                    (void)add_fake(otk::ParagraphStart);
                    state_push(State::Paragraph);
                }

                pop_as(otk::Word);
                break;
            }

            case obt::MediumNewline: {
                if (state_top() == State::Paragraph) {
                    (void)add_fake(otk::ParagraphEnd);
                    state_pop();
                }

                pop_as(otk::SkipNewline);
                break;
            }

            case obt::BraceOpen: {
                map_open_brace();
                break;
            }

            case obt::SubtreeStars: {
                pop_as(otk::SubtreeStars);
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

void OrgTokenizer::recombine(BaseLexer& lex) {
    RecombineState state{this, lex};
    state.recombine_impl();
}

void OrgTokenizer::convert(BaseTokenGroup& input) {
    Lexer<BaseTokenKind, BaseFill> lex(&input);
    return convert(lex);
}

void OrgTokenizer::convert(BaseLexer& lex) {
    rewriteIndents(lex);
    lex.pos = TokenId<BaseTokenKind, BaseFill>::FromValue(1);
    recombine(lex);
}
