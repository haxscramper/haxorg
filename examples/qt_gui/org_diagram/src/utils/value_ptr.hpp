#pragma once

#include <memory>
#include <type_traits>
#include <utility>
#include <cstring>

namespace hstd {


template <typename T, int SmallSize = 0>
struct value_ptr {
    static constexpr bool use_small_buffer = (sizeof(T) <= SmallSize)
                                          && std::is_trivially_copyable_v<
                                                 T>;

    using storage_type = std::conditional_t<
        use_small_buffer,
        std::aligned_storage_t<SmallSize, alignof(T)>,
        std::unique_ptr<T>>;

    storage_type storage;

    explicit value_ptr() : storage{} {}

    explicit value_ptr(T const* ptr) {
        if constexpr (use_small_buffer) {
            if (ptr) { new (&storage) T(*ptr); }
        } else {
            storage = std::make_unique<T>(*ptr);
        }
    }

    explicit value_ptr(const T& value) {
        if constexpr (use_small_buffer) {
            new (&storage) T(value);
        } else {
            storage = std::make_unique<T>(value);
        }
    }

    value_ptr(const value_ptr& other) {
        if constexpr (use_small_buffer) {
            if (other.get()) { new (&storage) T(*other.get()); }
        } else {
            if (other.storage) {
                storage = std::make_unique<T>(*other.storage);
            }
        }
    }

    value_ptr(value_ptr&& other) noexcept {
        if constexpr (use_small_buffer) {
            if (other.get()) { new (&storage) T(std::move(*other.get())); }
        } else {
            storage = std::move(other.storage);
        }
    }

    ~value_ptr() {
        if constexpr (use_small_buffer) {
            if (get()) { get()->~T(); }
        }
    }

    value_ptr& operator=(const value_ptr& other) {
        if (this != &other) {
            this->~value_ptr();
            new (this) value_ptr(other);
        }
        return *this;
    }

    value_ptr& operator=(value_ptr&& other) noexcept {
        if (this != &other) {
            this->~value_ptr();
            new (this) value_ptr(std::move(other));
        }
        return *this;
    }

    T* get() const {
        if constexpr (use_small_buffer) {
            return const_cast<T*>(reinterpret_cast<const T*>(&storage));
        } else {
            return storage.get();
        }
    }

    T* release() {
        if constexpr (use_small_buffer) {
            T* result = new T(*get());
            get()->~T();
            std::memset(&storage, 0, sizeof(storage));
            return result;
        } else {
            return storage.release();
        }
    }

    void reset(T* ptr = nullptr) {
        this->~value_ptr();
        new (this) value_ptr(ptr);
    }

    T&       operator*() const { return *get(); }
    T*       operator->() const { return get(); }
    explicit operator bool() const { return get() != nullptr; }

    template <typename U>
    value_ptr<U, SmallSize> cast() const {
        if constexpr (std::is_base_of_v<T, U>) {
            if (auto* casted = dynamic_cast<U*>(get())) {
                return value_ptr<U, SmallSize>{*casted};
            }
        } else if constexpr (std::is_base_of_v<U, T>) {
            return value_ptr<U, SmallSize>{*static_cast<U*>(get())};
        }
        return value_ptr<U, SmallSize>{};
    }

    template <typename U>
    U* cast_raw() const {
        if constexpr (std::is_base_of_v<T, U>) {
            return dynamic_cast<U*>(get());
        } else if constexpr (std::is_base_of_v<U, T>) {
            return static_cast<U*>(get());
        }
        return nullptr;
    }

    bool operator==(const value_ptr& other) const {
        if (!get() && !other.get()) { return true; }
        if (!get() || !other.get()) { return false; }
        return *get() == *other.get();
    }

    bool operator!=(const value_ptr& other) const {
        return !(*this == other);
    }

    bool operator<(const value_ptr& other) const {
        if (!other.get()) { return false; }
        if (!get()) { return true; }
        return *get() < *other.get();
    }

    bool operator<=(const value_ptr& other) const {
        return (*this < other) || (*this == other);
    }
};
} // namespace hstd
