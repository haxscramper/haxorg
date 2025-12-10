#pragma once

#include <string>

#include <hstd/stdlib/Array.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/ColText.hpp>

#include <haxorg/parse/OrgTypes.hpp>

#include <hstd/stdlib/TraceBase.hpp>
#include <haxorg/lexbase/Lexer.hpp>
#include <haxorg/parse/OrgParserTypes.hpp>

namespace org::parse {

struct ImplementError : public std::runtime_error {
    explicit inline ImplementError(const std::string& message = "")
        : std::runtime_error(message) {}
};

/// \brief Base implementation of the tokenizer.
///
/// There are two intended implementations of the tokenizer -- with and
/// without tracing. They differ only in the presence of the tracing calls
/// and implemented as explicitly specialized templates with static bool
/// argument.
struct OrgTokenizer
    : public hstd::OperationsTracer
    , public Tokenizer<OrgTokenKind, OrgFill> {
    // TODO at the moment the assumption is that adding conditional checks
    // all over the place in each lexer function would hinder the
    // performance quite a bit. Since indent/dedent relies on the RAII
    // triggers they would be executed no matter what -- but now without
    // any purpose. It is not exactly checked whether the performance drop
    // is large enough to justify all the hacks with explicit
    // initialization, but for the time being I don't want to get into this
    // and try and check what is really going on.
    using Base = Tokenizer<OrgTokenKind, OrgToken>;


  public:
    enum class ReportKind
    {
        Enter,
        Leave,
        Push,
        Print,
        Error
    };

    struct Report : hstd::OperationsMsg {
        bool                 addBuffered = false;
        ReportKind           kind;
        OrgToken             tok;
        OrgTokenId           id          = OrgTokenId::Nil();
        hstd::Opt<hstd::Str> subname     = std::nullopt;
        OrgLexer*            lex         = nullptr;
        int                  extraIndent = 0;
    };


  public:
    using ReportHookCb      = hstd::Func<void(Report const&)>;
    using TraceUpdateHookCb = hstd::Func<void(Report const&, bool&, bool)>;

    OrgTokenizer::ReportHookCb reportHook;

    void       push(std::span<OrgToken> const& tok) { out->add(tok); }
    void       push(hstd::Vec<OrgToken> const& tok) { out->add(tok); }
    OrgTokenId push(OrgToken tok) { return out->add(tok); }

    OrgTokenizer(OrgTokenGroup* out)
        : Tokenizer<OrgTokenKind, OrgFill>(out) {}

    /// Rewrite stream of base lexer tokens to the org token stream, adding
    /// boundaries for the paragraph elements, closing unterminated
    /// elements that can be detected on this stage.
    void recombine(OrgLexer& lex);

    void convert(OrgTokenGroup& input);
    void convert(OrgLexer& lex);

    void report(Report const& in);

    void print(
        OrgLexer&          lex,
        const std::string& msg,
        int                line        = __builtin_LINE(),
        char const*        function    = __builtin_FUNCTION(),
        int                extraIndent = 0);
};

} // namespace org::parse
