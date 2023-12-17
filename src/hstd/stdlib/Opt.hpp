#pragma once

import hstd.system.Formatter;

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
            with_std_formatter(p.value());
            std::formatter<T>{}.format(p.value(), ctx);
            return fmt.format(")", ctx);
        } else {
            return fmt.format("none()", ctx);
        }
    }
};
