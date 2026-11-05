#pragma once

#include <concepts>

namespace hstd {
template <typename T>
concept UnsignedInteger = std::unsigned_integral<T>;

template <UnsignedInteger T>
constexpr bool masked_equals(T base, T mask, T set_value) {
    return (base & mask) == set_value;
}

template <UnsignedInteger T>
constexpr T assign_masked(T base, T mask, T set_value) {
    return (base & ~mask) | (set_value & mask);
}

template <UnsignedInteger T>
constexpr T without_masked_bits(T base, T mask) {
    return base & ~mask;
}

template <UnsignedInteger T>
constexpr T masked_bits_right(T value, T mask, unsigned mask_size) {
    return (value & mask) >> (sizeof(T) * 8 - mask_size);
}
} // namespace hstd
