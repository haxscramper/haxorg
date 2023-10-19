#pragma once

#include <optional>
#include <format>

template <typename T>
using Opt = std::optional<T>;

template <typename T>
struct std::formatter<Opt<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(Opt<T> const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        if (p.has_value()) {
            fmt.format("some(", ctx);
            fmt.format(p.value(), ctx);
            return fmt.format(")", ctx);
        } else {
            return fmt.format("none()", ctx);
        }
    }
};
