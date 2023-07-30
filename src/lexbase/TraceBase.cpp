#include <lexbase/TraceBase.hpp>

void OperationsTracer::setTraceFile(const QFileInfo& outfile) {
    Q_ASSERT_X(
        outfile.absoluteFilePath().length() != 0,
        "setTraceFile",
        "Expected non-empty filename for the output");
    trace       = true;
    traceToFile = true;
    file.first.setFileName(outfile.absoluteFilePath());
    if (file.first.open(QIODevice::ReadWrite | QFile::Truncate)) {
        file.second.setDevice(&file.first);
    } else {
        qCritical() << "Could not open file " << outfile.absoluteFilePath()
                    << "\n";
        abort();
    }
}

ColStream OperationsTracer::getStream() {
    if (traceToBuffer) {
        return ColStream{};
    } else if (traceToFile) {
        auto os     = ColStream{file.second};
        os.colored  = false;
        os.buffered = false;
        return os;
    } else {
        return ColStream{qcout};
    }
}

void OperationsTracer::endStream(ColStream& stream) {
    if (traceToBuffer) {
        stream << "\n";
    } else {
        (*stream.ostream) << Qt::endl;
    }
}
