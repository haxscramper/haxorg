#include <parse/OrgTokenizer.hpp>

void OrgTokenizer::report(CR<Report> in) {
    if (!TraceState) { return; }

    if (reportHook) { reportHook(in); }

    if (traceUpdateHook) { traceUpdateHook(in, TraceState, true); }

    if (!TraceState) {
        if (traceUpdateHook) { traceUpdateHook(in, TraceState, false); }
        return;
    }


    using fg = TermColorFg8Bit;
    if (in.kind == ReportKind::Enter) { ++depth; }

    ColStream os = getStream();
    os << repeat("  ", depth);


    auto getLoc = [&]() -> std::string {
        std::string res;
        return res;
    };

    auto printString = [&]() {
        if (in.msg) { os << " [" << in.msg.value() << "]"; }

        if (in.lex) {
            os << " ";
            in.lex->print(
                os,
                [](ColStream& os, BaseToken const& t) {
                    os << " " << os.yellow()
                       << escape_for_write(t.value.text) << os.end();
                },
                BaseLexer::PrintParams{});
        }
    };

    switch (in.kind) {
        case ReportKind::Print: {
            os << "  " << fmt("{}:{}", in.name, in.line) << getLoc() << ":"
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
                os << "  + buffer token " << fmt1(getLoc())
                   << std::format("{}", in.tok.kind);
            } else {
                os << "  + add token " << fmt1(getLoc())
                   << fmt1(in.id.getIndex()) << " "
                   << std::format("{}", at(in.id).kind);
            }
            os << " at " << fg::Cyan << fmt1(in.line) << os.end();
            if (in.msg) { os << " " << *in.msg; }
            break;
        }
        case ReportKind::Enter:
        case ReportKind::Leave: {
            os << (in.kind == ReportKind::Enter ? "> " : "< ") << fg::Green
               << getLoc() << in.name << os.end() << ":" << fg::Cyan
               << fmt1(in.line) << os.end();

            if (in.subname.has_value()) {
                os << " " << in.subname.value();
            }

            printString();

            break;
        }
    }


    endStream(os);

    if (in.kind == ReportKind::Leave) { --depth; }

    if (traceUpdateHook) { traceUpdateHook(in, TraceState, false); }
}
