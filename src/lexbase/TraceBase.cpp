import org.lexbase.TraceBase;

void OperationsTracer::setTraceFile(const fs::path& outfile) {
    CHECK(outfile.native().size() != 0)
        << "setTraceFile"
        << "Expected non-empty filename for the output";
    trace       = true;
    traceToFile = true;
    stream      = std::make_shared<std::ofstream>(
        std::ofstream{outfile.native()});
}

ColStream OperationsTracer::getStream() {
    if (traceToBuffer) {
        return ColStream{};
    } else if (traceToFile) {
        auto os     = ColStream{*stream};
        os.colored  = false;
        os.buffered = false;
        return os;
    } else {
        return ColStream{std::cout};
    }
}

void OperationsTracer::endStream(ColStream& stream) {
    if (traceToBuffer) {
        stream << "\n";
    } else {
        (*stream.ostream) << std::endl;
    }
}
