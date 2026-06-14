#pragma once

#include <hstd/stdlib/Ptrs.hpp>


template <typename T>
struct fmt::formatter<hstd::SPtr<T>> : fmt::formatter<std::string> {

    hstd::fmt_iter format(hstd::SPtr<T> const& p, fmt::format_context& ctx) const {
        if (p.get() == nullptr) {
            return ::hstd::fmt_ctx("nullptr", ctx);
        } else {
            return ::hstd::fmt_ctx(p.get(), ctx);
        }
    }
};

template <typename T>
struct fmt::formatter<hstd::UPtr<T>> : fmt::formatter<std::string> {

    hstd::fmt_iter format(hstd::UPtr<T> const& p, fmt::format_context& ctx) const {
        if (p.get() == nullptr) {
            return ::hstd::fmt_ctx("nullptr", ctx);
        } else {
            return ::hstd::fmt_ctx(p.get(), ctx);
        }
    }
};
