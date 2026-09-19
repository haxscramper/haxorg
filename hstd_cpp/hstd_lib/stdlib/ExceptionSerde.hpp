#pragma once

#include <hstd/stdlib/JsonSerde.hpp>

namespace hstd {

template <typename E>
struct JsonSerdeHexception {
    static E from_json(json const& j) {
        throw std::runtime_error("cannot deser exceptions");
    }

    static json to_json(E const& value) {
        auto j = json::object();
#if !ORG_BUILD_EMCC
        nlohmann::json frames = nlohmann::json::array();

        for (const cpptrace::stacktrace_frame& frame : value.eager.frames) {
            frames.push_back({
                {"raw_address", frame.raw_address},
                {"object_address", frame.object_address},
                {"filename", nlohmann::json(frame.filename)},
                {"line",
                 frame.line.has_value() ? nlohmann::json(frame.line.value()) : nullptr},
                {"column",
                 frame.column.has_value() ? nlohmann::json(frame.column.value())
                                          : nullptr},
                {"symbol", nlohmann::json(frame.symbol)},
                {"is_inline", frame.is_inline},
            });
        }
        j["frames"] = frames;
#endif

        j["message"] = value.message();

        return j;
    }
};


} // namespace hstd
