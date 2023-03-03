#pragma once

#include <memory>
#include <fstream>
#include <string>

#include <hstd/stdlib/ColText.hpp>

struct OperationsTracer {
    bool                            trace         = false;
    bool                            traceToFile   = false;
    std::unique_ptr<std::wofstream> file          = nullptr;
    bool                            traceToBuffer = false;

    inline void setTraceFile(std::string const& outfile) {
        traceToFile                   = true;
        const std::locale utf8_locale = std::locale(
            std::locale(), new std::codecvt_utf8<wchar_t>());
        file.reset(new std::wofstream{outfile});
        file->imbue(utf8_locale);
    }

    ColStream getStream() {
        if (traceToBuffer) {
            return ColStream{};
        } else if (traceToFile) {
            auto os    = ColStream{*file};
            os.colored = false;
            return os;
        } else {
            return ColStream{std::wcout};
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
