#pragma once

#include <hstd/stdlib/Ptrs.hpp>



template <typename T>
struct std::formatter<hstd::SPtr<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const hstd::SPtr<T>& p, FormatContext& ctx) const {
        if (p.get() == nullptr) {
            return ::hstd::fmt_ctx("nullptr", ctx);
        } else {
          return ::hstd::fmt_ctx(p.get(), ctx);
        }
    }
};

template <typename T>
struct std::formatter<hstd::UPtr<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const hstd::UPtr<T>& p, FormatContext& ctx) const {
        if (p.get() == nullptr) {
            return ::hstd::fmt_ctx("nullptr", ctx);
        } else {
            return ::hstd::fmt_ctx(p.get(), ctx);
        }
    }
};
