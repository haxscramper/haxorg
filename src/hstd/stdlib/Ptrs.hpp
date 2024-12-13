#pragma once

#include <memory>
#include <hstd/system/aux_utils.hpp>
#include <hstd/system/Formatter.hpp>

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

extern template class std::unique_ptr<char, void (*)(void*)>;

template <typename T>
struct std::formatter<SPtr<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const SPtr<T>& p, FormatContext& ctx) const {
        if (p.get() == nullptr) {
            return fmt_ctx("nullptr", ctx);
        } else {
            return fmt_ctx(p.get(), ctx);
        }
    }
};

template <typename T>
struct std::formatter<UPtr<T>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const UPtr<T>& p, FormatContext& ctx) const {
        if (p.get() == nullptr) {
            return fmt_ctx("nullptr", ctx);
        } else {
            return fmt_ctx(p.get(), ctx);
        }
    }
};
