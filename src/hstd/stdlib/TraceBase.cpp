#include <hstd/stdlib/TraceBase.hpp>
#include <hstd/stdlib/Json.hpp>
#include <fstream>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/stdlib/strutils.hpp>
#if !ORG_EMCC_BUILD
#    include <cpptrace.hpp>
#endif

using namespace hstd;

SPtr<std::ostream> OperationsTracer::getTraceFile() { return stream; }

void OperationsTracer::setTraceFile(SPtr<std::ostream> stream) {
    TraceState   = true;
    traceToFile  = true;
    this->stream = stream;
}

void OperationsTracer::setTraceFile(
    const fs::path& outfile,
    bool            overwrite) {
    LOGIC_ASSERTION_CHECK(
        outfile.native().size() != 0,
        "Expected non-empty filename for the output");
    TraceState  = true;
    traceToFile = true;
    createDirectory(outfile.parent_path(), true, true);
    if (overwrite) {
        stream = std::make_shared<std::ofstream>(std::ofstream{
            outfile.native(), std::ios_base::out | std::ios_base::trunc});
    } else {
        stream = std::make_shared<std::ofstream>(std::ofstream{
            outfile.native(), std::ios_base::out | std::ios_base::app});
    }
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
        const_cast<OperationsTracer*>(this)->traceBuffer += stream.toString(
            traceColored);
    } else {
        (*stream.ostream) << std::endl;
    }
}

void OperationsTracer::message(
    const std::string& value,
    const char*        function,
    int                line,
    const char*        file) const {
    if (TraceState) {
        message(OperationsMsg{
            .level    = activeLevel,
            .function = function,
            .line     = line,
            .msg      = value,
            .file     = file,
        });
    }
}

void OperationsTracer::message(const OperationsMsg& value) const {
    if (TraceState) {
        auto os = getStream();
        if (traceStructured) {
            os << to_json_eval(value).dump();
        } else {
            std::string prefix = fmt(
                "{0}{1}{2}{3} @{4}",
                /*0*/ Str{"  "}.repeated(value.level),
                /*1*/ value.file
                    ? fmt("{:_<24}",
                          fs::path{value.file}.filename().native())
                    : "",
                /*2*/ value.line == 0 ? "" : fmt(":{:<4}", value.line),
                /*3*/ value.column == 0 ? "" : fmt(":{}", value.column),
                /*4*/ value.function ? fmt("{:_<24}", value.function)
                                     : "?");
            os << prefix;
            if (value.msg) {
                if (value.msg.value().find('\n') == -1) {
                    os << " " << value.msg.value();
                    if (!value.metadata.is_null()) {
                        os << " " << value.metadata.dump();
                    }
                } else {
                    bool isFirst = true;
                    for (auto const& line : split(*value.msg, '\n')) {
                        if (isFirst) {
                            if (value.metadata.is_null()) {
                                os << " " << line;
                            } else {
                                os << " "                              //
                                   << value.metadata.dump()            //
                                   << "\n"                             //
                                   << Str(" ").repeated(prefix.size()) //
                                   << " "                              //
                                   << line;
                            }
                            isFirst = false;
                        } else {
                            os << "\n"
                               << Str(" ").repeated(prefix.size()) << " "
                               << line;
                        }
                    }
                }
            }
        }
        endStream(os);
    }
}

finally_std OperationsTracer::scopeLevel() const {
    ++(const_cast<OperationsTracer*>(this)->activeLevel);
    return finally_std{
        [&]() { --(const_cast<OperationsTracer*>(this)->activeLevel); }};
}

finally_std OperationsTracer::scopeTrace(bool state) {
    bool initialTrace = TraceState;
    TraceState        = state;
    return finally_std{
        [initialTrace, this]() { TraceState = initialTrace; }};
}


void OperationsMsg::use_stacktrace_as_msg() {
#if !ORG_EMCC_BUILD
    this->msg = cpptrace::generate_trace().to_string(false);
#endif
}
