#include <hstd/stdlib/TraceBase.hpp>
#include <hstd/stdlib/Json.hpp>
#include <fstream>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/VariantSerde.hpp>
#include <hstd/stdlib/TraceBaseStructuredLog.hpp>

#if !ORG_BUILD_EMCC
#    include <cpptrace/cpptrace.hpp>
#endif

using namespace hstd;

SPtr<std::ostream> OperationsTracer::getTraceFile() { return stream; }

hstd::Opt<fs::path> OperationsTracer::getTraceFileDir() const {
    if (traceFile) {
        return traceFile->parent_path();
    } else {
        return std::nullopt;
    }
}

hstd::fs::path OperationsTracer::getAdjacentToTraceFile(Str const& suffix) const {
    auto outdir = getTraceFileDir();
    LOGIC_ASSERTION_CHECK(outdir.has_value(), "must be writing to file");
    auto result = outdir.value() / suffix.toBase();
    createDirectory(result.parent_path(), true, true);
    return result;
}

void OperationsTracer::writeToTraceFile(
    hstd::fs::path const& path,
    Str const&            text,
    bool                  with_message,
    char const*           function,
    int                   line,
    char const*           file) const {
    writeFile(path, text);
    if (with_message) {
        message(hstd::fmt("wrote debug file to {}", path), function, line, file);
    }
}

void OperationsTracer::writeAdjacentToTraceFile(
    Str const&  suffix,
    Str const&  text,
    bool        with_message,
    char const* function,
    int         line,
    char const* file) const {
    if (TraceState) {
        auto result = getAdjacentToTraceFile(suffix);
        writeToTraceFile(result, text, with_message, function, line, file);
    }
}

void OperationsTracer::setTraceFile(SPtr<std::ostream> stream) {
    TraceState   = true;
    traceToFile  = true;
    this->stream = stream;
}

void OperationsTracer::setTraceFile(fs::path const& outfile, bool overwrite) {
    LOGIC_ASSERTION_CHECK(
        outfile.native().size() != 0, "Expected non-empty filename for the output");
    traceFile   = outfile;
    TraceState  = true;
    traceToFile = true;
    createDirectory(outfile.parent_path(), true, true);
    if (overwrite) {
        stream = std::make_shared<std::ofstream>(
            std::ofstream{outfile.native(), std::ios_base::out | std::ios_base::trunc});
    } else {
        stream = std::make_shared<std::ofstream>(
            std::ofstream{outfile.native(), std::ios_base::out | std::ios_base::app});
    }
    traceColored = false;
}

ColStream OperationsTracer::getStream() const {
    if (traceToBuffer) {
        auto os    = ColStream{};
        os.colored = traceColored;
        return os;
    } else if (traceToFile) {
        auto os     = ColStream{*stream};
        os.colored  = traceColored;
        os.buffered = false;
        return os;
    } else {
        auto os    = ColStream{std::cout};
        os.colored = traceColored;
        return os;
    }
}

void OperationsTracer::endStream(ColStream& stream) const {
    if (traceToBuffer) {
        stream << "\n";
        const_cast<OperationsTracer*>(this)->traceBuffer += stream.toString(traceColored);
    } else {
        (*stream.ostream) << std::endl;
    }
}

void OperationsTracer::message(
    std::string const& value,
    char const*        function,
    int                line,
    char const*        file) const {
    if (TraceState) {
        message(
            OperationsMsg{
                .level    = activeLevel,
                .function = function,
                .line     = line,
                .msg      = value,
                .file     = file,
            });
    }
}

void OperationsTracer::message(OperationsMsg const& value) const {
    if (TraceState) {
        auto os = getStream();
        if (traceStructured) {
            log::record::InstantEvent event;
            event.init_ids();
            event.init_location(value.function, value.line, value.file);
            event.args.message = value.msg;
            os << log::record::format_event_to_json(event).dump();
        } else {
            std::string prefix = fmt(
                "{0}{1}{2}{3} @{4}",
                /*0*/ Str{"  "}.repeated(value.level),
                /*1*/ value.file
                    ? fmt("{:_<24}", fs::path{value.file}.filename().native())
                    : "",
                /*2*/ value.line == 0 ? "" : fmt(":{:<4}", value.line),
                /*3*/ value.column == 0 ? "" : fmt(":{}", value.column),
                /*4*/ value.function ? fmt("{:_<24}", value.function) : "?");
            os << prefix;
            if (value.msg) {
                if (value.msg.value().find('\n') == -1) {
                    os << " " << value.msg.value();
                    if (value.metadata) { os << " " << value.metadata->dump(); }
                } else {
                    bool isFirst = true;
                    for (auto const& line : split(*value.msg, '\n')) {
                        if (isFirst) {
                            if (!value.metadata || value.metadata->is_null()) {
                                os << " " << line;
                            } else {
                                os << " "                              //
                                   << value.metadata->dump()           //
                                   << "\n"                             //
                                   << Str(" ").repeated(prefix.size()) //
                                   << " "                              //
                                   << line;
                            }
                            isFirst = false;
                        } else {
                            os << "\n" << Str(" ").repeated(prefix.size()) << " " << line;
                        }
                    }
                }
            }
        }
        endStream(os);
    }
}

void OperationsTracer::stacktraceMessage() const {
#if !ORG_BUILD_EMCC
    auto trace = cpptrace::generate_trace();
    for (auto const& it : trace) {
        message(
            it.symbol,
            fmt("{}", it.raw_address).c_str(),
            it.line.value_or(-1),
            it.filename.c_str());
    }
#endif
}


void OperationsTracer::begin_scope_event(
    Opt<std::string> const& value,
    char const*             function,
    int                     line,
    char const*             file) const {
    if (traceStructured) {
        auto                            os = getStream();
        log::record::DurationBeginEvent e;
        e.init_ids();
        e.init_location(function, line, file);
        e.args.message = value;
        os << log::record::format_event_to_json(e).dump();
        endStream(os);
    } else {
        if (value) { message(value.value(), function, line, file); }
        ++activeLevel;
    }
}

void OperationsTracer::end_scope_event(
    Opt<std::string> const& value,
    char const*             function,
    int                     line,
    char const*             file) const {
    if (traceStructured) {
        auto                          os = getStream();
        log::record::DurationEndEvent e;
        e.init_ids();
        e.init_location(function, line, file);
        e.args.message = value;
        os << log::record::format_event_to_json(e).dump();
        endStream(os);
    } else {
        --activeLevel;
        if (value) { message(value.value(), function, line, file); }
    }
}

hstd::OperationsTracer::ScopeHandle OperationsTracer::begin_scope(
    Opt<std::string> const& value,
    char const*             function,
    int                     line,
    char const*             file) const {

    ScopeHandle res{const_cast<OperationsTracer*>(this)};
    res.start(value, function, line, file);
    return res;
}

finally_std OperationsTracer::scopeTrace(bool state) {
    bool initialTrace = TraceState;
    TraceState        = state;
    return finally_std{[initialTrace, this]() { TraceState = initialTrace; }};
}

void OperationsMsg::use_stacktrace_as_msg() {
#if !ORG_BUILD_EMCC
    this->msg = cpptrace::generate_trace().to_string(false);
#endif
}

void hstd::OperationsTracer::ScopeHandle::start(
    Opt<std::string> const& value,
    char const*             function,
    int                     line,
    char const*             file) {
    tracer->begin_scope_event(value, function, line, file);
}

void hstd::OperationsTracer::ScopeHandle::end(
    Opt<std::string> const& value,
    char const*             function,
    int                     line,
    char const*             file) {
    tracer->end_scope_event(value, function, line, file);
    tracer = nullptr;
}
