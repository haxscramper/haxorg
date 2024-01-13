#pragma once

#include <string>

#include <hstd/stdlib/Array.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/ColText.hpp>

#include <parse/OrgTypes.hpp>

#include <lexbase/TraceBase.hpp>

#ifdef ORG_USE_PERFETTO
#    define __perf_trace(name) TRACE_EVENT("lexing", name)
#else
#    define __perf_trace(a)
#endif


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
    : public OperationsTracer
    , public Tokenizer<OrgTokenKind, OrgFill> {
    // TODO at the moment the assumption is that adding conditional checks
    // all over the place in each lexer function would hinder the
    // performance quite a bit. Since indent/dedent relies on the RAII
    // triggers they would be executed no matter what -- but now without
    // any purpose. It is not exactly checked whether the performance drop
    // is large enough to justify all the hacks with explicit
    // initialization, but for the time being I don't want to get into this
    // and try and check what is really going on.
    using Base = Tokenizer<OrgTokenKind, BaseToken>;


  public:
    enum class ReportKind
    {
        Enter,
        Leave,
        Push,
        SetBuffer,
        ClearBuffer,
        PushResolved,
        Print,
        Error
    };

    struct Report : OperationsMsg {
        bool       addBuffered = false;
        ReportKind kind;
        OrgToken   tok;
        OrgTokenId id      = OrgTokenId::Nil();
        Opt<Str>   subname = std::nullopt;
        BaseLexer* lex     = nullptr;
    };


  public:
    using ReportHookCb      = Func<void(CR<Report>)>;
    using TraceUpdateHookCb = Func<void(CR<Report>, bool&, bool)>;

    OrgTokenizer::ReportHookCb reportHook;
    /// Update trace enable/disable state. Called before and after each
    /// report is processed. First argument is the report, second is the
    /// reference to the `trace` member and the last one provides
    /// information about call location (before report or after report).
    OrgTokenizer::TraceUpdateHookCb traceUpdateHook;

    void       push(CR<std::span<OrgToken>> tok) { out->add(tok); }
    void       push(CR<Vec<OrgToken>> tok) { out->add(tok); }
    OrgTokenId push(CR<OrgToken> tok) { return out->add(tok); }

    OrgTokenizer(OrgTokenGroup* out)
        : Tokenizer<OrgTokenKind, OrgFill>(out) {}

    /// Rewrite stream of base lexer tokens to the org token stream, adding
    /// boundaries for the paragraph elements, closing unterminated
    /// elements that can be detected on this stage.
    void recombine(BaseLexer& lex);

    void convert(BaseTokenGroup& input);
    void convert(BaseLexer& lex);

    int  depth = 0;
    void report(CR<Report> in);

    void print(
        const std::string& msg,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION());
};
