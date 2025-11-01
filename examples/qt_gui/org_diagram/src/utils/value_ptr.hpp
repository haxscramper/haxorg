#pragma once

#include <memory>
#include <type_traits>
#include <utility>
#include <memory>
#include <type_traits>
#include <utility>

namespace hstd {

template <typename T>
struct abstract_cloner {};

template <typename T>
concept HasPtrCopyMethod = requires(const T& t) {
    { t.copy() } -> std::same_as<T*>;
} || requires(const T& t) {
    { t.copy() } -> std::same_as<const T*>;
} || requires(const T& t) {
    requires std::is_pointer_v<decltype(t.copy())>;
    requires std::is_base_of_v<
                 std::remove_pointer_t<decltype(t.copy())>,
                 T>
                 || std::is_same_v<
                     std::remove_pointer_t<decltype(t.copy())>,
                     T>;
};

template <HasPtrCopyMethod T>
struct abstract_cloner<T> {
    static T const* copy(T const* other) {
        return static_cast<T const*>(other->copy());
    }
};

template <typename T>
struct value_ptr {
    std::unique_ptr<T> storage;

    explicit value_ptr() : storage{} {}

    explicit value_ptr(const T* ptr) {
        if (ptr) {
            storage = std::unique_ptr<T>(abstract_cloner<T>::copy(ptr));
        }
    }

    explicit value_ptr(const T& value)
        : storage{std::make_unique<T>(value)} {}

    value_ptr(const value_ptr& other) {
        if (other.storage) {
            storage = std::make_unique<T>(
                abstract_cloner<T>::copy(other.storage.get()));
        }
    }

    template <typename... Args>
    static value_ptr<T> init(Args&&... args) {
        return value_ptr<T>(Dest(std::forward<Args>(args))...);
    }

    template <typename Construct, typename... Args>
    static value_ptr<T> init_as(Args&&... args) {
        return value_ptr<Construct>(Construct(std::forward<Args>(args))...)
            .template cast<T>();
    }

    value_ptr(value_ptr&& other) noexcept
        : storage{std::move(other.storage)} {}

    ~value_ptr() = default;

    value_ptr& operator=(const value_ptr& other) {
        if (this != &other) {
            if (other.storage) {
                storage = std::make_unique<T>(*other.storage);
            } else {
                storage.reset();
            }
        }
        return *this;
    }

    value_ptr& operator=(value_ptr&& other) noexcept {
        if (this != &other) { storage = std::move(other.storage); }
        return *this;
    }

    value_ptr copy() const { return value_ptr(get()); }
    T*        get() const { return storage.get(); }

    T* release() { return storage.release(); }

    void reset(const T* ptr = nullptr) {
        if (ptr) {
            storage = std::make_unique<T>(*ptr);
        } else {
            storage.reset();
        }
    }

    T& operator*() const { return *storage; }
    T* operator->() const { return storage.get(); }
    operator bool() const { return storage != nullptr; }

    template <typename U>
    value_ptr<U> cast() const {
        if constexpr (std::is_base_of_v<T, U>) {
            if (auto* casted = dynamic_cast<U*>(storage.get())) {
                return value_ptr<U>{casted};
            }
        } else if constexpr (std::is_base_of_v<U, T>) {
            return value_ptr<U>{static_cast<U*>(storage.get())};
        }
        return value_ptr<U>{};
    }

    template <typename U>
    U* cast_raw() const {
        if constexpr (std::is_base_of_v<T, U>) {
            return dynamic_cast<U*>(storage.get());
        } else if constexpr (std::is_base_of_v<U, T>) {
            return static_cast<U*>(storage.get());
        }
        return nullptr;
    }

    bool operator==(const value_ptr& other) const {
        if (!storage && !other.storage) { return true; }
        if (!storage || !other.storage) { return false; }
        return *storage == *other.storage;
    }

    bool operator!=(const value_ptr& other) const {
        return !(*this == other);
    }

    bool operator<(const value_ptr& other) const {
        if (!other.storage) { return false; }
        if (!storage) { return true; }
        return *storage < *other.storage;
    }

    bool operator<=(const value_ptr& other) const {
        return (*this < other) || (*this == other);
    }
};
} // namespace hstd
