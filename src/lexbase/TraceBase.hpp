#pragma once

#include <memory>
#include <fstream>
#include <string>
#include <QFile>
#include <QFileInfo>

#include <hstd/stdlib/ColText.hpp>

struct OperationsTracer {
    bool trace         = false;
    bool traceToFile   = false;
    bool traceToBuffer = false;

    Pair<QFile, QTextStream> file;

    inline void setTraceFile(QFileInfo const& outfile) {
        trace       = true;
        traceToFile = true;
        file.first.setFileName(outfile.canonicalFilePath());
        if (file.first.open(QIODevice::ReadWrite | QFile::Truncate)) {
            file.second.setDevice(&file.first);
            qDebug() << "Opened file" << outfile.canonicalFilePath()
                     << "for writing trace";
        } else {
            qCritical() << "Could not open file "
                        << outfile.canonicalFilePath() << "\n";
            abort();
        }
    }

    ColStream getStream() {
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

    void endStream(ColStream& stream) {
        if (traceToBuffer) {
            stream << "\n";
        } else {
            (*stream.ostream) << Qt::endl;
        }
    }
};
