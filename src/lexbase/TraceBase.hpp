#pragma once

#include <memory>
#include <fstream>
#include <string>
#include <QFile>

#include <hstd/stdlib/ColText.hpp>

struct OperationsTracer {
    bool trace         = false;
    bool traceToFile   = false;
    bool traceToBuffer = false;

    Pair<QFile, QTextStream> file;

    inline void setTraceFile(QString const& outfile) {
        traceToFile = true;
        file.first.setFileName(outfile);
        if (file.first.open(QIODevice::ReadWrite)) {
            file.second.setDevice(&file.first);
        } else {
            std::cerr << "Could not open file " << outfile << "\n";
            abort();
        }
    }

    ColStream getStream() {
        if (traceToBuffer) {
            return ColStream{};
        } else if (traceToFile) {
            auto os    = ColStream{file.second};
            os.colored = false;
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
