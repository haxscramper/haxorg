#pragma once

#include <cstddef>

namespace hstd {

/// Check if ~ptr~ falls in ~[start, start + size]~ range. Start and size
/// addition will use pointer arichmetics to compute the size.
template <typename T>
bool is_within_memory_block(T const* ptr, T const* start, std::size_t size) {
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
