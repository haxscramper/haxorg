#pragma once

#include <functional>
#include "macros.hpp"

namespace hstd {

/// Trigger callback when exiting the scope. Ad-hoc RAII
/// implementation
template <typename Func>
struct finally {
    /// Callback function called in destructor
    Func action;

    /// Default constructor, use as ~funally{[](){ callback-action(); }}~
    explicit finally(Func _action) : action(_action) {}

    /// Overloaded constructor to run scope finalizer with some captured
    /// value
    template <typename T, typename Func1>
    static finally init(Func1 _action, T const& value) {
        return finally([value, _action]() { _action(value); });
    }

    /// Constructor for do-nothing default action
    static finally nop() { return finally{finally::nop_impl}; }

    ~finally() { action(); }

  private:
    static void nop_impl() {}
};

using finally_std = finally<std::function<void(void)>>;

/// Overloading support for `std::visit`
template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

/// Helper base type for defining CRTP classes
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


/// Check if ~ptr~ falls in ~[start, start + size]~ range. Start and size
/// addition will use pointer arichmetics to compute the size.
template <typename T>
bool is_within_memory_block(
    T const*    ptr,
    T const*    start,
    std::size_t size) {
    T const* end = start + size;
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

} // namespace hstd
