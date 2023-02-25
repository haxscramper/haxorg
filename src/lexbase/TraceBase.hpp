#pragma once

#include <memory>
#include <fstream>
#include <string>

#include <hstd/stdlib/ColText.hpp>

struct OperationsTracer {
    bool                           trace         = false;
    bool                           traceToFile   = false;
    std::unique_ptr<std::ofstream> file          = nullptr;
    bool                           traceToBuffer = false;

    inline void setTraceFile(std::string const& outfile) {
        traceToFile = true;
        file.reset(new std::ofstream{outfile});
    }

    ColStream getStream() {
        if (traceToBuffer) {
            return ColStream{};
        } else if (traceToFile) {
            auto os    = ColStream{*file};
            os.colored = false;
            return os;
        } else {
            return ColStream{std::cout};
        }
    }

    void endStream(ColStream& stream) {
        if (traceToBuffer) {
            stream << "\n";
        } else {
            *(stream.ostream) << std::endl;
            if (traceToFile) {
                file->flush();
            }
        }
    }
};
