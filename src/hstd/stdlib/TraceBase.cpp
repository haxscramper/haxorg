#include <hstd/stdlib/TraceBase.hpp>
#include <hstd/stdlib/Json.hpp>
#include <fstream>
#include <hstd/stdlib/Exception.hpp>

void OperationsTracer::setTraceFile(const fs::path& outfile) {
    CHECK(outfile.native().size() != 0)
        << "setTraceFile" << "Expected non-empty filename for the output";
    TraceState  = true;
    traceToFile = true;
    stream      = std::make_shared<std::ofstream>(
        std::ofstream{outfile.native()});
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
    int                level,
    int                line,
    const char*        function,
    const char*        file) const {
    if (TraceState) {
        message(OperationsMsg{
            .level    = level,
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
            os << fmt(
                "{0}{1}{2}{3} @{4} {5}",
                /*0*/ Str{"  "}.repeated(value.level),
                /*1*/ value.file
                    ? fmt("{:_<24}",
                          fs::path{value.file}.filename().native())
                    : "",
                /*2*/ value.line == 0 ? "" : fmt(":{:<4}", value.line),
                /*3*/ value.column == 0 ? "" : fmt(":{}", value.column),
                /*4*/ value.function ? fmt("{:_<24}", value.function)
                                     : "?",
                /*5*/ value.msg ? value.msg.value() : "");
        }
        endStream(os);
    }
}

finally OperationsScope::scopeLevel() {
    ++activeLevel;
    return finally{[&]() { --activeLevel; }};
}

finally OperationsScope::scopeTrace(bool state) {
    LOGIC_ASSERTION_CHECK(
        TraceState != nullptr,
        "use operations tracer `.TraceState` field as a pointer base");
    bool initialTrace = TraceState;
    *TraceState       = state;
    return finally{[initialTrace, this]() { *TraceState = initialTrace; }};
}
