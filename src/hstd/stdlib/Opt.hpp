#pragma once

#include <optional>
#include <format>

template <typename T>
using Opt = std::optional<T>;

template <typename T>
struct std::formatter<Opt<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const Opt<T>& p, FormatContext& ctx) {
        if (p.has_value()) {
            return std::format("some({})", p.value());
        } else {
            return "none()";
        }
        return std::formatter<std::string>::format(p.to_string(), ctx);
    }
};
