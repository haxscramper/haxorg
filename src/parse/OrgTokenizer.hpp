#pragma once

#include <string>
#include <fstream>

#include <hstd/stdlib/Array.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/ColText.hpp>

#include <parse/OrgTypes.hpp>

#include <lexbase/TraceBase.hpp>

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
struct OrgTokenizer : public OperationsTracer {
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
    /// \brief Create tokenizer implementation object
    static SPtr<OrgTokenizer> initImpl(OrgTokenGroup* out, bool doTrace);


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

    struct Report {
        bool       addBuffered = false;
        ReportKind kind;
        Str        name;
        OrgToken   tok;
        OrgTokenId id = OrgTokenId::Nil();
        fs::path   location;
        int        line;
        Opt<Str>   subname;
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
    bool                            TraceState = false;

    void       push(CR<std::span<OrgToken>> tok) { out->add(tok); }
    void       push(CR<Vec<OrgToken>> tok) { out->add(tok); }
    OrgTokenId push(CR<OrgToken> tok) { return out->add(tok); }

    int  depth = 0;
    void report(CR<Report> in) {
        if (!TraceState) {
            return;
        }

        if (reportHook) {
            reportHook(in);
        }

        if (traceUpdateHook) {
            traceUpdateHook(in, trace, true);
        }

        if (!trace) {
            if (traceUpdateHook) {
                traceUpdateHook(in, trace, false);
            }
            return;
        }


        using fg = TermColorFg8Bit;
        if (in.kind == ReportKind::Enter) {
            ++depth;
        }

        ColStream os = getStream();
        os << repeat("  ", depth);


        auto getLoc = [&]() -> std::string {
            std::string res;
            return res;
        };

        auto printString = [&]() {

        };

        switch (in.kind) {
            case ReportKind::Print: {
                os << "  " << in.line << getLoc() << ":"
                   << in.subname.value();
                printString();
                break;
            }

            case ReportKind::SetBuffer: {
                os << "  ! set buffer";
                break;
            }

            case ReportKind::Error: {
                break;
            }

            case ReportKind::ClearBuffer: {
                os << "  ! clear buffer" << getLoc();
                break;
            }

            case ReportKind::PushResolved: {
                os << "  + push resolved" << getLoc();
                break;
            }

            case ReportKind::Push: {
                if (in.id.isNil()) {
                    os << "  + buffer token " << getLoc() << in.tok;
                } else {
                    os << "  + add token " << getLoc() << in.id.getIndex()
                       << " " << at(in.id);
                }
                os << " at " << fg::Cyan << in.line << os.end();
                break;
            }
            case ReportKind::Enter:
            case ReportKind::Leave: {
                os << (in.kind == ReportKind::Enter ? "> " : "< ")
                   << fg::Green << getLoc() << in.name << os.end() << ":"
                   << fg::Cyan << in.line << os.end();

                if (in.subname.has_value()) {
                    os << " " << in.subname.value();
                }

                printString();

                break;
            }
        }


        endStream(os);

        if (in.kind == ReportKind::Leave) {
            --depth;
        }

        if (traceUpdateHook) {
            traceUpdateHook(in, trace, false);
        }
    }
};
