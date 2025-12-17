#pragma once

#include <memory>
#include <hstd/system/aux_utils.hpp>
#include <hstd/stdlib/Exception.hpp>

namespace hstd {

template <typename T>
using UPtr = std::unique_ptr<T>;

template <typename T>
using SPtr = std::shared_ptr<T>;

template <typename T>
using UPtrIn = std::unique_ptr<T>&&;

template <typename T>
using WPtr = std::weak_ptr<T>;

template <typename T>
struct SharedPtrApi
    : public std::enable_shared_from_this<T>
    , public CRTP_this_method<T> {
    using CRTP_this_method<T>::_this;
    template <typename... Args>
    static std::shared_ptr<T> shared(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    std::shared_ptr<T> clone_this() {
        return std::make_shared<T>(*_this());
    }

    using Ptr  = std::shared_ptr<T>;
    using WPtr = std::weak_ptr<T>;

    std::shared_ptr<T> mshared_from_this() const {
        return const_cast<T*>(_this())->shared_from_this();
    }

    std::weak_ptr<T> mweak_from_this() const {
        return const_cast<T*>(_this())->weak_from_this();
    }
};

template <typename T>
SPtr<T> safe_wptr_lock(WPtr<T> const& ptr) {
    SPtr<T> result = ptr.lock();
    LOGIC_ASSERTION_CHECK(
        result != nullptr,
        "could not lock weak pointer -- managed object has already been "
        "destroyed");
    return result;
}


template <typename T>
struct remove_smart_pointer {
    using type = T;
};

template <typename T>
struct remove_smart_pointer<std::shared_ptr<T>> {
    using type = T;
};

template <typename T>
struct remove_smart_pointer<std::unique_ptr<T>> {
    using type = T;
};

template <typename T>
struct remove_smart_pointer<std::weak_ptr<T>> {
    using type = T;
};

template <class T, class D, class U>
    requires(requires(std::unique_ptr<U, D>::pointer p) {
                dynamic_cast<std::unique_ptr<T, D>::pointer>(p);
            })
constexpr auto dynamic_pointer_cast(std::unique_ptr<U, D>&& r) noexcept
    -> std::unique_ptr<T, D> {
    static_assert(
        !std::is_array_v<T> && !std::is_array_v<U>,
        "don't work with array of polymorphic objects");
    if (auto p = dynamic_cast<std::unique_ptr<T, D>::pointer>(r.get())) {
        r.release();
        return std::unique_ptr<T, D>(p, std::forward<D>(r.get_deleter()));
    } else if constexpr (
        !std::is_pointer_v<D> && std::is_default_constructible_v<D>) {
        return {};
    } else if constexpr (std::is_copy_constructible_v<D>) {
        return std::unique_ptr<T, D>(nullptr, r.get_deleter());
    } else {
        static_assert(false, "unable to create an empty unique_ptr");
    }
}


} // namespace hstd

extern template class std::unique_ptr<char, void (*)(void*)>;


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
