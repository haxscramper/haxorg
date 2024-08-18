#include <hstd/stdlib/TraceBase.hpp>
#include <hstd/stdlib/Json.hpp>
#include <fstream>

void OperationsTracer::setTraceFile(const fs::path& outfile) {
    CHECK(outfile.native().size() != 0)
        << "setTraceFile" << "Expected non-empty filename for the output";
    TraceState  = true;
    traceToFile = true;
    stream      = std::make_shared<std::ofstream>(
        std::ofstream{outfile.native()});
}

ColStream OperationsTracer::getStream() {
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

void OperationsTracer::endStream(ColStream& stream) {
    if (traceToBuffer) {
        stream << "\n";
        traceBuffer += stream.toString(traceColored);
    } else {
        (*stream.ostream) << std::endl;
    }
}

void OperationsTracer::message(const std::string& value) {
    if(TraceState) {
    auto os = getStream();
    os << value;
    endStream(os);
    }
}

void OperationsTracer::message(const OperationsMsg& value) {
    if (TraceState) {

    auto os = getStream();
    if (traceStructured) {
        os << to_json_eval(value).dump();
    } else {
        os << fmt(
            "{}:{}:{} @{} {}",
            value.file ? fs::path{value.file}.filename().native() : "",
            value.line,
            value.column,
            value.function ? value.function : "?",
            value.msg ? value.msg : "");
    }
    endStream(os);
    }
}
