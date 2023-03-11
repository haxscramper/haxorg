#pragma once

#include <functional>

struct finally {
    std::function<void(void)> action;
    explicit finally(std::function<void(void)> _action)
        : action(_action) {}

    template <typename T>
    static finally init(
        std::function<void(T const&)> _action,
        T const&                      value) {
        return finally([value, _action]() { _action(value); });
    }

    ~finally() { action(); }
};

template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;


template <typename T>
bool notNil(T* ptr) {
    return ptr != nullptr;
}

template <typename T>
bool isNil(T* ptr) {
    return ptr == nullptr;
}

template <typename T>
struct CRTP_this_method {
  protected:
    inline T*       _this() { return static_cast<T*>(this); }
    inline T const* _this() const { return static_cast<T const*>(this); }
};

#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b


#define __ploc()                                                          \
    std::cout << __FILE__ << ":" << __LINE__ << " at " << __func__        \
              << std::endl;


template <typename T>
bool is_within_memory_block(
    T const*    ptr,
    T const*    start,
    std::size_t size) {
    // calculate the end of the memory block
    T const* end = start + size;

    // check if the pointer is within the memory block
    return start <= ptr && ptr < end;
}

template <typename T>
bool is_pointer_valid(T const* ptr, T const* start, std::size_t size) {
    // check if the pointer is null or not within the memory block
    return ptr != nullptr && is_within_memory_block(ptr, start, size);
}

template <typename T>
std::ptrdiff_t pointer_distance(T const* first, T const* last) {
    return last - first;
}
