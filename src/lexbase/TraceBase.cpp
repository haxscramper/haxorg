#include <lexbase/TraceBase.hpp>

void OperationsTracer::setTraceFile(const QFileInfo& outfile) {
    Q_ASSERT_X(
        outfile.absoluteFilePath().length() != 0,
        "setTraceFile",
        "Expected non-empty filename for the output");
    trace       = true;
    traceToFile = true;
    file        = std::make_shared<QFile>();
    stream      = std::make_shared<QTextStream>();
    file->setFileName(outfile.absoluteFilePath());
    if (file->open(QIODevice::ReadWrite | QFile::Truncate)) {
        //        qDebug() << "Opened" << outfile.absoluteFilePath()
        //                 << "for writing";
        stream->setDevice(file.get());
    } else {
        qCritical() << "Could not open file "
                    << outfile.absoluteFilePath();
        abort();
    }
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
